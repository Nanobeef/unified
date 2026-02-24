

GraphicsDescriptorSetLayout create_graphics_descriptor_set_layout(GraphicsDevice *device, u32 binding_count, VkDescriptorSetLayoutBinding *bindings)
{
	GraphicsDescriptorSetLayout layout = {.device = device};
	for(u32 i = 0; i < binding_count; i++)
	{
		if(bindings[i].descriptorType <= VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT)
		{
			layout.pool_sizes[bindings[i].descriptorType] += bindings[i].descriptorCount;
		}
		else
		{
			print("Descriptor type (%s32) is not supported\n", bindings[i].descriptorType);
		}
	}

	VkDescriptorSetLayoutCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,
		.bindingCount = binding_count,
		.pBindings = bindings,
	};
	VK_ASSERT(vkCreateDescriptorSetLayout(device->handle, &info, vkb, &layout.handle));
	return layout;
}

void destroy_graphics_descriptor_set_layout(GraphicsDescriptorSetLayout layout)
{
	vkDestroyDescriptorSetLayout(layout.device->handle, layout.handle, vkb);
}

GraphicsDescriptorPool* create_graphics_descriptor_pool(Arena *arena, GraphicsDevice *device, u32 layout_count, GraphicsDescriptorSetLayout *layouts)
{
	arena_push_type(arena, 0, 1, GraphicsDescriptorPool, pool);
	*pool = (GraphicsDescriptorPool){
		.device = device,
		.set_count = layout_count,
	};

	GraphicsDescriptorSetLayout temp_layout = {0};
	for(u32 i = 0; i < layout_count; i++)
	{
		for(u32 j = 0; j < Arrlen(temp_layout.pool_sizes); j++)
		{
			temp_layout.pool_sizes[j] += layouts[i].pool_sizes[j];
		}
	}
	u32 pool_size_count = 0;
	u32 max_set_count = 0;
	for(u32 i = 0; i < Arrlen(temp_layout.pool_sizes); i++)
	{
		if(temp_layout.pool_sizes[i])
		{
			pool_size_count++;
			max_set_count += temp_layout.pool_sizes[i];
		}
	}

	Scratch scratch = find_scratch(0,0,0);
	arena_push_type(scratch.arena, 0, pool_size_count, VkDescriptorPoolSize, pool_sizes);
	u32 pool_index = 0;
	for(u32 i = 0; i < Arrlen(temp_layout.pool_sizes); i++)
	{
		if(temp_layout.pool_sizes[i])
		{
			pool_sizes[pool_index++] = (VkDescriptorPoolSize){
				.type = (VkDescriptorType)i,
				.descriptorCount = temp_layout.pool_sizes[i],
			};
		}
	}

	VkDescriptorPoolCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.flags = VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT,
		.maxSets = max_set_count,
		.poolSizeCount = pool_size_count,
		.pPoolSizes = pool_sizes,
	};
	VK_ASSERT(vkCreateDescriptorPool(device->handle, &info, vkb, &pool->handle));
	
	pool->descriptor_sets = arena_push(arena, 0, sizeof(GraphicsDescriptorSet) * layout_count);
	arena_push_type(scratch.arena, 0, layout_count, VkDescriptorSetLayout, layout_handles);
	for(u32 i = 0; i < layout_count; i++)
	{
		layout_handles[i] = layouts[i].handle;
	}
	arena_push_type(scratch.arena, 0, layout_count, VkDescriptorSet, set_handles);
	for(u32 i = 0; i < layout_count; i++)
	{
		VkDescriptorSetAllocateInfo alloc_info = {
			.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
			.descriptorPool = pool->handle,
			.descriptorSetCount = layout_count,
			.pSetLayouts = layout_handles,
		};
		VK_ASSERT(vkAllocateDescriptorSets(device->handle, &alloc_info, set_handles));
	}
	for(u32 i = 0; i < layout_count; i++)
	{
		pool->descriptor_sets[i] = (GraphicsDescriptorSet){
			.pool = pool,
			.handle = set_handles[i],
		};
	}
	regress_scratch(scratch);
	return pool;
}

void destroy_graphics_descriptor_pool(GraphicsDescriptorPool *pool)
{
	Scratch scratch = find_scratch(0,0,0);
	arena_push_type(scratch.arena, 0, pool->set_count, VkDescriptorSet, set_handles);
	for(u32 i = 0; i < pool->set_count; i++)
	{
		set_handles[i] = pool->descriptor_sets[i].handle;
	}
	vkFreeDescriptorSets(pool->device->handle, pool->handle, pool->set_count, set_handles);
	regress_scratch(scratch);
	vkDestroyDescriptorPool(pool->device->handle, pool->handle, vkb);
}
