
#include "particle_test_1.c"


typedef struct{
	u32 particles_pointer;
	u32 grid_offsets_pointer;
	u32 grid_square_size;
	u32 particle_count;

	u32 update_accum;


}UpdateGlobals;

typedef struct{
	f32m3p world_affine;
	f32m3p overlay_affine;
	f32 world_zoom;
	f32 overlay_zoom;

	u32 frame_accum;
	u32 show_circles;
	u32 image_x;
	u32 image_y;
}RenderGlobals;

void cmd_general_compute_memory_barrier(GraphicsCommandBuffer cb)
{
	VkMemoryBarrier barrier = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER,
		.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
		.dstAccessMask = VK_ACCESS_MEMORY_READ_BIT | VK_ACCESS_MEMORY_WRITE_BIT,
	};
	vkCmdPipelineBarrier(cb.handle, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, 0, 1, &barrier, 0,0, 0,0);
}
	
void update_descriptor_target_images(GraphicsDescriptorPool *pool, u32 binidng, GraphicsDeviceImage* render_target_images)
{
	const u32 frame_count = 2;
	Scratch scratch = find_scratch(0,0,0);

	
	arena_push_name(scratch.arena, 0, frame_count, VkDescriptorImageInfo, images);
	arena_push_name(scratch.arena, 0, frame_count, VkWriteDescriptorSet, writes);
	for(u32 i = 0; i < frame_count ;i++)
	{
		images[i] = (VkDescriptorImageInfo)
		{
			.imageView= render_target_images[i].view,
			.imageLayout = VK_IMAGE_LAYOUT_GENERAL,
		};
		writes[i] = (VkWriteDescriptorSet)
		{
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.dstSet = pool->descriptor_sets[i].handle,
			.dstBinding = 1,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
			.pImageInfo = images + i,
		};
	}

	vkUpdateDescriptorSets(pool->device->handle, frame_count, writes,0,0);
	regress_scratch(scratch);
	
}


s32 run_unified(void)
{

	AudioDevice *audio_device = create_audio_device(main_arena);

	Window *window = create_window(main_arena);
	GraphicsInstance *instance = create_graphics_instance(main_arena);
	GraphicsSurface surface = create_graphics_surface(window, instance);
	GraphicsDevice *device = create_graphics_device(main_arena, instance, 0);
	GraphicsSwapchain swapchain = create_graphics_swapchain(main_arena, surface, device);

	Event *event_ring_buffer = allocate_ring_buffer(main_arena, Event, 1024);

	const u32 frame_count = 2; // Will crash if not 2.
	u64 frame_accum = 0;
	u64 frame_index = 0;


	arena_push_name(main_arena, 0, frame_count * 2, Arena*, frame_arenas);
	for(u32 i = 0; i < frame_count * 2; i++)
	{
		u64 size = MiB(64);
		frame_arenas[i] = init_arena(size, arena_push(main_arena, 0, size));
	}

	u32 resize_count = 2;
	u64 resize_accum = 0;
	u64 resize_index = 0;
	arena_push_name(main_arena, 0, resize_count, Arena*, resize_arenas);
	for(u32 i = 0; i < resize_count; i++)
	{
		u64 size = MiB(8);
		resize_arenas[i] = init_arena(size, arena_push(main_arena, 0, size));
	}

	const u32 update_count = 2; // Expect program to crash when this is changed.
	u64 update_accum = 0;
	u64 update_index = 0;

	arena_push_name(main_arena, 0, update_count, Arena*, update_arenas);
	for(u32 i = 0; i < update_count; i++)
	{
		u64 size = MiB(1024);
		update_arenas[i] = init_arena(size, arena_push(main_arena, 0, size));
	}


	Arena *frame_arena = frame_arenas[frame_accum % (frame_count * 2)];
	Arena *resize_arena = resize_arenas[resize_index];
	
	GraphicsSemaphore *swapchain_semaphores = create_graphics_semaphores(main_arena, device, frame_count);
	GraphicsSemaphore *render_semaphores = create_graphics_semaphores(main_arena, device, frame_count);

	GraphicsFence *render_fences = create_graphics_fences(main_arena, device, frame_count, true);

	GraphicsCommandPool **render_command_pools = create_graphics_command_pools(main_arena, device->main_queue_family, frame_count, 1);
	GraphicsDeviceQueue render_queue = device->main_queue_family->queues[0];


	Camera camera = init_camera();
	Camera inspect_camera = init_camera();
	FixedCamera fixed_camera = create_fixed_camera(window->size);

	u32 hardware_wave_count = 32;

	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceBuffer, render_globals);
	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceImage, render_target_images);

	u32 particle_count = 1024 * 102;
	u64 update_buffer_size = particle_test1_buffer_size(particle_count);

	GraphicsDeviceBuffer update_buffer = create_graphics_device_buffer(device->host_cached_heap,update_buffer_size , VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);


	if(0){
		particle_test_1(particle_count, (u32*)update_buffer.memory.mapping,true);
		flush_graphics_device_memory(update_buffer.memory);
		GraphicsDeviceBuffer temp_buffer = create_graphics_device_buffer(device->device_heap ,update_buffer_size , VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);

		GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
		GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);
		

		VkBufferCopy region = {
			.size = update_buffer_size,
		};
		
		vkCmdCopyBuffer(cb.handle, update_buffer.handle, temp_buffer.handle, 1, &region);


		end_graphics_command_buffer(cb);
		reset_graphics_fence(render_fences[frame_index]);
		submit_command_buffers(
			render_queue,
			0, 0,
			0, 0,
			1, &cb, 
			0,
			render_fences[frame_index]
		);
		wait_for_graphics_fence(render_fences[frame_index]);
		update_buffer = temp_buffer;
	}





	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceBuffer, update_globals);
	for(u32 i = 0; i < frame_count; i++)
	{
		render_globals[i] = create_graphics_device_buffer(device->host_coherent_heap, sizeof(RenderGlobals), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
		render_target_images[i] = create_graphics_device_image_explicit(device->device_heap, swapchain.size, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_TRANSFER_DST_BIT| VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_STORAGE_BIT, VK_IMAGE_TILING_OPTIMAL, VK_SAMPLE_COUNT_1_BIT);

		update_globals[i] = create_graphics_device_buffer(device->host_cached_heap, sizeof(UpdateGlobals), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
	}


	GraphicsDescriptorSetLayout render_descriptor_set_layout = {0};
	{
		VkDescriptorSetLayoutBinding bindings[] = {
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT, 0},
			{1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,  1, VK_SHADER_STAGE_COMPUTE_BIT, 0},
		};
		render_descriptor_set_layout = create_graphics_descriptor_set_layout(device, Arrlen(bindings), bindings);
	}
	GraphicsDescriptorSetLayout update_descriptor_set_layout = {0};
	{
		VkDescriptorSetLayoutBinding bindings[] = {
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT, 0},
			{1, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT, 0},
			{2, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT, 0},
			{3, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1, VK_SHADER_STAGE_COMPUTE_BIT, 0},
		};
		update_descriptor_set_layout = create_graphics_descriptor_set_layout(device, Arrlen(bindings), bindings);
	}

	VkPipelineLayout pipeline_layout = 0;
	{
		VkDescriptorSetLayout set_layouts[] = {render_descriptor_set_layout.handle, update_descriptor_set_layout.handle};
		VkPipelineLayoutCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.setLayoutCount = Arrlen(set_layouts),
			.pSetLayouts = set_layouts,
		};
		VK_ASSERT(vkCreatePipelineLayout(device->handle, &info, vkb, &pipeline_layout));
	}
	GraphicsDescriptorPool *render_descriptor_pool = 0;
	{
		GraphicsDescriptorSetLayout set_layouts[frame_count];
		for(u32 i = 0; i < frame_count; i++)
		{
			set_layouts[i] = render_descriptor_set_layout;
		}
		render_descriptor_pool = create_graphics_descriptor_pool(main_arena, device, frame_count, set_layouts);
	}
	GraphicsDescriptorPool *update_descriptor_pool = 0;
	{
		GraphicsDescriptorSetLayout set_layouts[frame_count];
		for(u32 i = 0; i < update_count; i++)
		{
			set_layouts[i] = update_descriptor_set_layout;
		}
		update_descriptor_pool = create_graphics_descriptor_pool(main_arena, device, frame_count, set_layouts);
	}


	UnifiedPipelineSpecialization unified_specialization = {
 		.const_timestamp_period = 10,
 		.const_buffer_count = 2,
 		.const_buffer_granularity = (u32)MiB(64),
	};
	
	VkShaderModule unified_shader_module = read_shader_file(device, "build/unified.spv");
	UnifiedPipelines unified_pipelines = compile_unified_pipelines(device, unified_shader_module, pipeline_layout, unified_specialization);

	{
		u32 write_count = frame_count * 2;
		VkWriteDescriptorSet writes[write_count];
		VkDescriptorBufferInfo uniform_buffer_infos[2];
		VkDescriptorImageInfo target_image_infos[2];
		for(u32 i = 0; i < frame_count; i++)
		{
			uniform_buffer_infos[i] = (VkDescriptorBufferInfo){
				.buffer = render_globals[i].handle,
				.offset = 0,
				.range = VK_WHOLE_SIZE,
			};
			target_image_infos[i] = (VkDescriptorImageInfo){
				.imageView = render_target_images[i].view,
				.imageLayout = VK_IMAGE_LAYOUT_GENERAL,
			};
			writes[i * 2] = (VkWriteDescriptorSet){
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = render_descriptor_pool->descriptor_sets[i].handle,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.dstBinding = 0,
				.descriptorCount = 1,
				.pBufferInfo = &uniform_buffer_infos[i],
			};
			writes[i * 2 + 1] = (VkWriteDescriptorSet){
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
				.dstSet = render_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 1,
				.descriptorCount = 1,
				.pImageInfo = &target_image_infos[i],
			};
		}
		vkUpdateDescriptorSets(device->handle, write_count, writes, 0,0);
	}


	{
		u32 write_count = update_count * 4;
		VkWriteDescriptorSet writes[write_count];
		VkDescriptorBufferInfo uniform_buffer_infos[2];
		VkDescriptorBufferInfo uniform_table_buffer_infos[2];
		VkDescriptorBufferInfo storage_buffer_infos[2];
		for(u32 i = 0; i < update_count; i++)
		{
			uniform_buffer_infos[i] = (VkDescriptorBufferInfo){
				.buffer = update_globals[i].handle,
				.offset = 0,
				.range = VK_WHOLE_SIZE,
			};
			uniform_table_buffer_infos[i] = (VkDescriptorBufferInfo){
				.buffer = update_globals[i].handle,
				.offset = 0,
				.range = VK_WHOLE_SIZE,
			};
			storage_buffer_infos[i] = (VkDescriptorBufferInfo){
				.buffer = update_buffer.handle,
				.offset = 0,
				.range = VK_WHOLE_SIZE,
			};
			writes[i * 4] = (VkWriteDescriptorSet){
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = update_descriptor_pool->descriptor_sets[i].handle,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.dstBinding = 0,
				.descriptorCount = 1,
				.pBufferInfo = &uniform_buffer_infos[i],
			};
			writes[i * 4 + 1] = (VkWriteDescriptorSet){
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = update_descriptor_pool->descriptor_sets[i].handle,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.dstBinding = 1,
				.descriptorCount = 1,
				.pBufferInfo = &uniform_table_buffer_infos[i],
			};
			writes[i * 4 + 2] = (VkWriteDescriptorSet){
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.dstSet = update_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 2,
				.descriptorCount = 1,
				.pBufferInfo = &storage_buffer_infos[i],
			};
			writes[i * 4 + 3] = (VkWriteDescriptorSet){
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.dstSet = update_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 3,
				.descriptorCount = 1,
				.pBufferInfo = &storage_buffer_infos[i],
			};
		}
		vkUpdateDescriptorSets(device->handle, write_count, writes, 0,0);
	}


	GraphicsQueryPool query_pools[frame_count];
	for(u32 i = 0; i < frame_count; i++)
	{
		query_pools[i] = create_graphics_query_pool(main_arena, device, VK_QUERY_TYPE_TIMESTAMP, 1024, 0);
	}




	u64 frame_start_time = get_epoch_ns() - window->refresh_rate;
	u64 frame_end_time = 0;
	b32 just_resized = false;
	u64 resize_frame_accum = 0;;
	PolledEvents pe = {0};
	u64 frame_elapsed_time = window->refresh_rate;
	u64 frame_time = window->refresh_rate;
	while(true)
	{
		frame_end_time = get_epoch_ns();
		frame_elapsed_time = frame_end_time - frame_start_time;
		u64 frame_sleep_time = 0;
		if(frame_elapsed_time < window->refresh_rate && (swapchain.create_info.presentMode == VK_PRESENT_MODE_FIFO_KHR))
		{
			frame_sleep_time = window->refresh_rate - frame_elapsed_time;

			u64 us = frame_sleep_time / 1000;
			usleep(us);
		}

		frame_start_time = get_epoch_ns();
		if(frame_accum % 100 == 0)
			print("Time = %t\n", frame_elapsed_time);
		frame_time = frame_elapsed_time + frame_sleep_time;
		
		frame_index = frame_accum % frame_count;
		frame_arena = frame_arenas[frame_accum % (frame_count * 2)];
		reset_arena(frame_arena);

		poll_audio_device(audio_device, event_ring_buffer);
		poll_window(window, event_ring_buffer);
		poll_events(frame_arena, event_ring_buffer, &pe);
		if(pe.escape.pressed)
			break;
		fixed_camera = create_fixed_camera(window->size);


		VkResult result = vkAcquireNextImageKHR(device->handle, swapchain.handle, U64_MAX, swapchain_semaphores[frame_index].handle, 0, &swapchain.image_index);
		if(result == VK_ERROR_OUT_OF_DATE_KHR)
			pe.window_should_resize = true;
		if(pe.window_should_resize)
		{
			resize_accum++;
			resize_index = resize_accum % resize_count;
			resize_arena = resize_arenas[resize_index];
			reset_arena(resize_arena);

			wait_for_graphics_fences(frame_count, render_fences);

			VkSurfaceCapabilitiesKHR capabilities = {0};
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->physical.handle, swapchain.create_info.surface, &capabilities);
			swapchain.create_info.imageExtent = capabilities.minImageExtent;
			

			swapchain = recreate_graphics_swapchain(resize_arena, swapchain);
			for(u32 i = 0; i < frame_count; i++)
			{
				render_target_images[i] = resize_graphics_device_image(render_target_images[i], u32x2_div1(swapchain.size, 1));
			}
			update_descriptor_target_images(render_descriptor_pool, 1, render_target_images);


			destroy_graphics_semaphore(swapchain_semaphores[frame_index]);
			swapchain_semaphores[frame_index] = create_graphics_semaphore(device);
			frame_start_time = get_epoch_ns() - window->refresh_rate;
			just_resized = true;
			resize_frame_accum = frame_accum;
			continue;
		}
		if(just_resized || (frame_accum == 0))
		{
		}

		GraphicsDeviceImage swapchain_image = swapchain.images[swapchain.image_index];
		update_camera(&camera, pe, window->size, false);
		wait_for_graphics_fences(frame_count, render_fences);
		wait_and_reset_graphics_fence(render_fences[frame_index]);

		
		if(pe.a.pressed ){
			TimestampQueryResult *qr = get_graphics_timestamp_query_pool_results(frame_arena, query_pools[frame_index]);
			for(u32 i = 0; i < TOTAL(qr); i++)
			{
				print("%s, %t\n", qr[i].name, qr[i].elapsed);
			}
		}



		GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
		GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);
		cmd_reset_graphics_query_pool(cb, query_pools[frame_index]);

		{
			GraphicsBufferMemoryBarrier buffer_barrier = {
				.buffer = update_buffer,	
				.offset = 0,
				.size = update_buffer.size,
				.src_access = VK_ACCESS_HOST_READ_BIT | VK_ACCESS_HOST_WRITE_BIT,
				.dst_access = VK_ACCESS_SHADER_READ_BIT,
			};
			cmd_graphics_pipeline_buffer_barrier(cb, 1, &buffer_barrier, VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
		}


		if((frame_accum - resize_frame_accum < swapchain.image_count))
		{
			GraphicsImageMemoryBarrier barrier = {
				.image = swapchain.images[swapchain.image_index],
				.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
				.src_access = VK_ACCESS_NONE,
				.dst_access = VK_ACCESS_MEMORY_READ_BIT,
				.old_layout = VK_IMAGE_LAYOUT_UNDEFINED,
				.new_layout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
			};
			cmd_graphics_pipeline_image_barrier(cb, 1, &barrier, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
		}
		if((frame_accum - resize_frame_accum < frame_count))
		{
			GraphicsImageMemoryBarrier barrier = {
				.image = render_target_images[frame_index],
				.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
				.src_access = VK_ACCESS_NONE,
				.dst_access = VK_ACCESS_TRANSFER_WRITE_BIT,
				.old_layout = VK_IMAGE_LAYOUT_UNDEFINED,
				.new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			};
			cmd_graphics_pipeline_image_barrier(cb, 1, &barrier, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
		}

		cmd_clear_graphics_device_image(cb, render_target_images[frame_index], f32x4_set1(0.0));

		{
			GraphicsImageMemoryBarrier image_barriers[1] = {
				{
					.image = render_target_images[frame_index],
					.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
					.src_access = VK_ACCESS_TRANSFER_WRITE_BIT,
					.dst_access = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT,
					.old_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.new_layout = VK_IMAGE_LAYOUT_GENERAL,
				},
			};
			cmd_graphics_pipeline_image_barrier(cb, Arrlen(image_barriers), image_barriers, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
		}

		update_index = update_accum & 1;
		vkCmdBindDescriptorSets(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline_layout, 0, 1, &render_descriptor_pool->descriptor_sets[frame_index].handle, 0,0);
		vkCmdBindDescriptorSets(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline_layout, 1, 1, &update_descriptor_pool->descriptor_sets[update_index].handle, 0,0);
		u32x2 target_size = render_target_images[frame_index].size;

		u32 kernel_index = 0;
		if(pe.n1.pressed)
		{
			kernel_index = 1;	
		}



		const u32 wave_size = 64;
		u32 resets_per_thread = 64;
		u32 counts_per_thread = 64;

		*(UpdateGlobals*)(update_globals[update_index].memory.mapping) = (UpdateGlobals)
		{
			.update_accum = (u32)update_accum,
			.particle_count = particle_count,
		};

		

		// Reset
		if(pe.r.pressed || (frame_accum == 0))
		{
		//	vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, unified_pipelines.reset);
		}
		// Count
		cmd_general_compute_memory_barrier(cb);
		{
		}
		// Prefix 
		cmd_general_compute_memory_barrier(cb);
		{
		}
		// Fill
		cmd_general_compute_memory_barrier(cb);
		{
		}
		// Resolve
		cmd_general_compute_memory_barrier(cb);
		{
		}



		cmd_general_compute_memory_barrier(cb);

		cmd_timestamp_graphics_query_name(cb, query_pools[frame_index], str8_lit("Small Simulate"),  VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
		vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, unified_pipelines.small_simulate);
		vkCmdDispatch(cb.handle, 1,1,1);
		cmd_timestamp_graphics_query_name(cb, query_pools[frame_index], str8_lit("Small Simulate"),  VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

		cmd_general_compute_memory_barrier(cb);

		cmd_timestamp_graphics_query_name(cb, query_pools[frame_index], str8_lit("Small Draw"),  VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
		vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, unified_pipelines.small_draw);
		vkCmdDispatch(cb.handle, 1,1,1);
		cmd_timestamp_graphics_query_name(cb, query_pools[frame_index], str8_lit("Small Draw"),  VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

		{

			*(RenderGlobals*)(render_globals[frame_index].memory.mapping) = (RenderGlobals)
			{
				.world_affine = f32m3_padding(camera.inverse_current_affine),
				.overlay_affine = f32m3_padding(fixed_camera.affine),
				.world_zoom = camera.current_zoom,
				.overlay_zoom = 1.0,
				.frame_accum = (u32)frame_accum,
				.show_circles = !pe.d.pressed,

			};

		}
		cmd_general_compute_memory_barrier(cb);

		{
			GraphicsImageMemoryBarrier image_barriers[2] = {
				{
					.image = swapchain.images[swapchain.image_index],
					.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
					.src_access = VK_ACCESS_NONE,
					.dst_access = VK_ACCESS_TRANSFER_WRITE_BIT,
					.old_layout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
					.new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				},
				{
					.image = render_target_images[frame_index],
					.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
					.src_access = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT,
					.dst_access = VK_ACCESS_TRANSFER_READ_BIT,
					.old_layout = VK_IMAGE_LAYOUT_GENERAL,
					.new_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				},
			};
			cmd_graphics_pipeline_image_barrier(cb, Arrlen(image_barriers), image_barriers, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
		}

		cmd_blit_graphics_device_image(cb, render_target_images[frame_index], swapchain.images[swapchain.image_index]);

		{
			GraphicsImageMemoryBarrier image_barriers[2] = {
				{
					.image = swapchain.images[swapchain.image_index],
					.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
					.src_access = VK_ACCESS_TRANSFER_WRITE_BIT,
					.dst_access = VK_ACCESS_NONE,
					.old_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.new_layout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
				},
				{
					.image = render_target_images[frame_index],
					.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
					.src_access = VK_ACCESS_TRANSFER_READ_BIT,
					.dst_access = VK_ACCESS_TRANSFER_WRITE_BIT,
					.old_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
					.new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
				},
			};
			cmd_graphics_pipeline_image_barrier(cb, Arrlen(image_barriers), image_barriers, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
		}

		end_graphics_command_buffer(cb);
		
		submit_command_buffers(
			render_queue,
			1, &swapchain_semaphores[frame_index], 
			1, &render_semaphores[frame_index], 
			1, &cb, 
			0,
			render_fences[frame_index]
		);

		present_swapchain(render_queue, 1, &render_semaphores[frame_index], 1, &swapchain);
		just_resized = false;
		frame_accum++;
		update_accum++;

	}

	vkDeviceWaitIdle(device->handle);

	for(u32 i = 0; i < frame_count; i++)
	{
		destroy_graphics_query_pool(query_pools[i]);
	}

	destroy_unified_pipelines(unified_pipelines);
	destroy_graphics_descriptor_pool(render_descriptor_pool);
	destroy_graphics_descriptor_set_layout(render_descriptor_set_layout);

	destroy_graphics_descriptor_pool(update_descriptor_pool);
	destroy_graphics_descriptor_set_layout(update_descriptor_set_layout);

	vkDestroyPipelineLayout(device->handle, pipeline_layout, vkb);


	for(u32 i = 0; i < frame_count; i++)
	{
		destroy_graphics_device_buffer(render_globals[i]);
		destroy_graphics_device_image(render_target_images[i]);
	}
	for(u32 i = 0; i < update_count; i++)
	{
		destroy_graphics_device_buffer(update_globals[i]);
	}
	destroy_graphics_device_buffer(update_buffer);

	destroy_graphics_semaphores(frame_count, swapchain_semaphores);
	destroy_graphics_semaphores(frame_count, render_semaphores);
	destroy_graphics_fences(frame_count, render_fences);
	destroy_graphics_command_pools(frame_count, render_command_pools); 
	destroy_graphics_swapchain(swapchain);
	destroy_graphics_device(device);
	destroy_graphics_surface(surface);
	destroy_graphics_instance(instance);
	destroy_window(window);
	destroy_audio_device(audio_device);
	return 0;

}


