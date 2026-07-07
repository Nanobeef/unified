

BoidGPUSimulation create_boid_gpu_simulation(Arena *arena, GraphicsDevice *device, u64 max_boid_count)
{
	BoidGPUSimulation sim = {
		.device = device,
		.max_boid_count = max_boid_count,
		.boid_count = max_boid_count,
		.grid_size = u32x2_set(2048,2048),
	};

	for(u32 i = 0; i < 2; i++)
	{
		sim.boid_buffers[i] = create_graphics_device_buffer(device->device_heap, sizeof(Boid) * sim.max_boid_count, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
		sim.index_buffers[i] = create_graphics_device_buffer(device->device_heap, sizeof(u32)  * sim.max_boid_count, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT);
	}

	u32 grid_cell_count = sim.grid_size.x * sim.grid_size.y;
	sim.grid_count_buffer = create_graphics_device_buffer(device->device_heap, sizeof(u32)  * grid_cell_count, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT);
	sim.grid_offset_buffer = create_graphics_device_buffer(device->device_heap, sizeof(u32)  * grid_cell_count, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);
	sim.grid_index_buffer = create_graphics_device_buffer(device->device_heap, sizeof(BoidGridIndex)  * sim.max_boid_count, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);

	sim.grid_offset_sum_buffer = create_graphics_device_buffer(device->device_heap, sizeof(u32) * (grid_cell_count) * 2 , VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);

	{
		VkDescriptorSetLayoutBinding bindings[8];
		for(u32 i = 0; i < Arrlen(bindings); i++)
		{
			bindings[i] = (VkDescriptorSetLayoutBinding){
				.binding = i,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.descriptorCount = 1,
				.stageFlags = boid_compute_push_stages,
			};
		}
		sim.descriptor_set_layout = create_graphics_descriptor_set_layout(device, Arrlen(bindings), bindings);

		GraphicsDescriptorSetLayout layouts[] = {
			sim.descriptor_set_layout,
			sim.descriptor_set_layout,
		};
		
		sim.descriptor_pool = create_graphics_descriptor_pool(arena, device, Arrlen(layouts), layouts);

		for(u32 i = 0; i < 2; i++)
		{
			sim.descriptor_sets[i] = sim.descriptor_pool->descriptor_sets[i];
		}

	}
	
	{
		VkPushConstantRange ranges[] = {
			{
				.stageFlags = boid_compute_push_stages,
				.size = sizeof(BoidComputePushConstants),
			},
		};
		u32 offset = 0;
		for(u32 i = 0; i < Arrlen(ranges); i++)
		{
			ranges[i].offset = offset;
			offset += ranges[i].size;
		}
		VkPipelineLayoutCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.setLayoutCount = 1,
			.pSetLayouts = &sim.descriptor_set_layout.handle,
			.pushConstantRangeCount = Arrlen(ranges),
			.pPushConstantRanges = ranges,
		};
		VK_ASSERT(vkCreatePipelineLayout(device->handle, &info, vkb, &sim.pipelines.layout));
	}


	sim.pipelines.reset = create_compute_pipeline_from_file(device, sim.pipelines.layout, "build/boid_reset_comp.spv");
	sim.pipelines.resolve = create_compute_pipeline_from_file(device, sim.pipelines.layout, "build/boid_resolve_comp.spv");
	sim.pipelines.count = create_compute_pipeline_from_file(device, sim.pipelines.layout, "build/boid_count_comp.spv");
	sim.pipelines.prefix_sum  = create_compute_pipeline_from_file(device, sim.pipelines.layout, "build/boid_prefix_sum_comp.spv");

	VkDescriptorBufferInfo buffer_infos[8] = {
		{
			.buffer = sim.boid_buffers[0].handle,
			.offset = 0,
			.range = VK_WHOLE_SIZE,
		},
		{
			.buffer = sim.boid_buffers[1].handle,
			.offset = 0,
			.range = VK_WHOLE_SIZE,
		},
		{
			.buffer = sim.index_buffers[0].handle,
			.offset = 0,
			.range = VK_WHOLE_SIZE,
		},
		{
			.buffer = sim.index_buffers[1].handle,
			.offset = 0,
			.range = VK_WHOLE_SIZE,
		},

		{
			.buffer = sim.grid_count_buffer.handle,
			.offset = 0,
			.range = VK_WHOLE_SIZE,
		},
		{
			.buffer = sim.grid_offset_buffer.handle,
			.offset = 0,
			.range = VK_WHOLE_SIZE,
		},
		{
			.buffer = sim.grid_index_buffer.handle,
			.offset = 0,
			.range = VK_WHOLE_SIZE,
		},
		{
			.buffer = sim.grid_offset_sum_buffer.handle,
			.offset = 0,
			.range = VK_WHOLE_SIZE,
		},
	};

	VkWriteDescriptorSet writes[Arrlen(buffer_infos) * 2];

	u32 buffer_indices[Arrlen(writes)] = {
		0,1,2,3,4,5,6,7,
		1,0,3,2,4,5,6,7,
	};
	for(u32 i = 0; i < Arrlen(writes); i++)
	{
		writes[i] = (VkWriteDescriptorSet)
		{
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,	
			.dstSet = sim.descriptor_sets[i/Arrlen(buffer_infos)].handle,
			.dstBinding = i % Arrlen(buffer_infos),
			.dstArrayElement = 0,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
			.pBufferInfo = &buffer_infos[buffer_indices[i]],
		};
	}

	vkUpdateDescriptorSets(device->handle, Arrlen(writes), writes, 0, 0);

	return sim;	
}

void destroy_boid_gpu_simulation(BoidGPUSimulation sim)
{
	for(u32 i = 0; i < 2; i++)
	{
		destroy_graphics_device_buffer(sim.boid_buffers[i]);
		destroy_graphics_device_buffer(sim.index_buffers[i]);
	}
	destroy_graphics_device_buffer(sim.grid_index_buffer);
	destroy_graphics_device_buffer(sim.grid_offset_buffer);
	destroy_graphics_device_buffer(sim.grid_count_buffer);
	destroy_graphics_device_buffer(sim.grid_offset_sum_buffer);
	vkDestroyPipeline(sim.device->handle, sim.pipelines.reset, vkb);
	vkDestroyPipeline(sim.device->handle, sim.pipelines.resolve, vkb);
	vkDestroyPipeline(sim.device->handle, sim.pipelines.count, vkb);
	vkDestroyPipeline(sim.device->handle, sim.pipelines.prefix_sum, vkb);
	vkDestroyPipelineLayout(sim.device->handle, sim.pipelines.layout, vkb);
	destroy_graphics_descriptor_pool(sim.descriptor_pool);
	destroy_graphics_descriptor_set_layout(sim.descriptor_set_layout);
}


