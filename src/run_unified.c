


typedef struct{
	f32x2 box[2];
	u32 particle_count;
	u32 update_accum;
}UpdateGlobals;

typedef struct{
	f32m3p world_affine;
	f32m3p overlay_affine;
	f32 world_zoom;
	f32 overlay_zoom;

	u32 frame_accum;
}RenderGlobals;

void update_pingpong_descriptor_target_images(GraphicsDescriptorPool *pool, u32 binidng, GraphicsDeviceImage* render_target_images)
{
	u32 frame_count = 2;
	Scratch scratch = find_scratch(0,0,0);

	u32 render_binding_count = 1;
	u32 pingpong[2][2] = {{0,1},{1,0}};
	arena_push_name(scratch.arena, 0, frame_count * render_binding_count, VkWriteDescriptorSet, writes);
	for(u32 i = 0; i < frame_count ;i++)
	{
		arena_push_name(scratch.arena, 0, frame_count, VkDescriptorImageInfo, images);
		for(u32 j = 0; j < frame_count; j++)
		{
			u32 k = pingpong[i][j];
			images[j] = (VkDescriptorImageInfo)
			{
				.imageView= render_target_images[k].view,
				.imageLayout = VK_IMAGE_LAYOUT_GENERAL,
			};
		}
		writes[i * render_binding_count] = (VkWriteDescriptorSet)
		{
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.dstSet = pool->descriptor_sets[i].handle,
			.dstBinding = 1,
			.descriptorCount = 2,
			.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
			.pImageInfo = images,
		};
	}

	vkUpdateDescriptorSets(pool->device->handle, frame_count * render_binding_count, writes,0,0);
	regress_scratch(scratch);
	
}


s32 run_unified(void)
{

	AudioDevice *audio_device = create_audio_device(main_arena);

	Window *window = create_window(main_arena);
	GraphicsInstance *instance = create_graphics_instance(main_arena);
	GraphicsSurface surface = create_graphics_surface(window, instance);
//	GraphicsDevice *device = create_graphics_device(main_arena, instance, INTEGRATED_GRAPHICS_DEVICE);
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

	u32 hardware_wave_count = 1024;

	u32 max_target_buffer_count = MiB(1);
	u32 target_buffer_count = max_target_buffer_count;
	u32 target_buffer_size = max_target_buffer_count * sizeof(u16x2);
	u32 scratch_buffer_size = 4096 * hardware_wave_count * sizeof(u32);
	u32 counter_buffer_size = 4096 * sizeof(u32);
	u32 offset_buffer_size = 4096 * sizeof(u32x2);


	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceBuffer, render_globals);
	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceImage, render_target_images);


	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceBuffer, update_globals);
	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceBuffer, update_target_buffers);
	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceBuffer, update_scratch_buffers);
	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceBuffer, update_counter_buffers);
	arena_push_name(main_arena, 0, frame_count, GraphicsDeviceBuffer, update_offset_buffers);
	for(u32 i = 0; i < frame_count; i++)
	{
		render_globals[i] = create_graphics_device_buffer(device->host_cached_heap, sizeof(RenderGlobals), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
		render_target_images[i] = create_graphics_device_image_explicit(device->device_heap, swapchain.size, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_TRANSFER_DST_BIT| VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_STORAGE_BIT, VK_IMAGE_TILING_OPTIMAL, VK_SAMPLE_COUNT_1_BIT);

		update_globals[i] = create_graphics_device_buffer(device->host_cached_heap, sizeof(UpdateGlobals), VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
		update_target_buffers[i] = create_graphics_device_buffer(device->device_heap, target_buffer_size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);
		update_scratch_buffers[i] = create_graphics_device_buffer(device->device_heap, scratch_buffer_size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);
		update_counter_buffers[i] = create_graphics_device_buffer(device->device_heap, counter_buffer_size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);
		update_offset_buffers[i] = create_graphics_device_buffer(device->device_heap, offset_buffer_size, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT);
	}





	GraphicsDescriptorSetLayout render_descriptor_set_layout = {0};
	{
		VkDescriptorSetLayoutBinding bindings[] = {
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, frame_count, VK_SHADER_STAGE_COMPUTE_BIT, 0},
			{1, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,  frame_count, VK_SHADER_STAGE_COMPUTE_BIT, 0},
		};
		render_descriptor_set_layout = create_graphics_descriptor_set_layout(device, Arrlen(bindings), bindings);
	}
	GraphicsDescriptorSetLayout update_descriptor_set_layout = {0};
	{
		VkDescriptorSetLayoutBinding bindings[] = {
			{0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, frame_count, VK_SHADER_STAGE_COMPUTE_BIT, 0},
			{1, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, frame_count, VK_SHADER_STAGE_COMPUTE_BIT, 0},
			{2, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, frame_count, VK_SHADER_STAGE_COMPUTE_BIT, 0},
			{3, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, frame_count, VK_SHADER_STAGE_COMPUTE_BIT, 0},
			{4, VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, frame_count, VK_SHADER_STAGE_COMPUTE_BIT, 0},
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
		for(u32 i = 0; i < frame_count; i++)
		{
			set_layouts[i] = update_descriptor_set_layout;
		}
		update_descriptor_pool = create_graphics_descriptor_pool(main_arena, device, frame_count, set_layouts);
	}

	VkPipeline reset_pipeline = create_compute_pipeline_from_file(device, pipeline_layout, "build/reset.spv");
	VkPipeline count_pipeline = create_compute_pipeline_from_file(device, pipeline_layout, "build/count.spv");
	VkPipeline prefix_pipeline = create_compute_pipeline_from_file(device, pipeline_layout, "build/prefix.spv");
	VkPipeline fill_pipeline = create_compute_pipeline_from_file(device, pipeline_layout, "build/fill.spv");
	VkPipeline resolve_pipeline = create_compute_pipeline_from_file(device, pipeline_layout, "build/resolve.spv");
	VkPipeline draw_pipeline = create_compute_pipeline_from_file(device, pipeline_layout, "build/draw.spv");


	if(0){
		GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
		GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);

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
	}
	{
		Scratch scratch = find_scratch(0,0,0);

		u32 render_binding_count = 2;
		u32 pingpong[2][2] = {{0,1},{1,0}};
		arena_push_name(scratch.arena, 0, frame_count * render_binding_count, VkWriteDescriptorSet, writes);
		for(u32 i = 0; i < frame_count ;i++)
		{
			arena_push_name(scratch.arena, 0, frame_count, VkDescriptorBufferInfo, buffers);
			arena_push_name(scratch.arena, 0, frame_count, VkDescriptorImageInfo, images);
			for(u32 j = 0; j < frame_count; j++)
			{
				u32 k = pingpong[i][j];
				buffers[j] = (VkDescriptorBufferInfo)
				{
					.buffer = render_globals[k].handle,
					.range = VK_WHOLE_SIZE,
				};
				images[j] = (VkDescriptorImageInfo)
				{
					.imageView= render_target_images[k].view,
					.imageLayout = VK_IMAGE_LAYOUT_GENERAL,
				};
			}
			writes[i * render_binding_count + 0] = (VkWriteDescriptorSet)
			{
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = render_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 0,
				.descriptorCount = 2,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pBufferInfo = buffers,
			};
			writes[i * render_binding_count + 1] = (VkWriteDescriptorSet)
			{
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = render_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 1,
				.descriptorCount = 2,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
				.pImageInfo = images,
			};
		}

		vkUpdateDescriptorSets(device->handle, frame_count * render_binding_count, writes,0,0);
		regress_scratch(scratch);
	}


	{
		Scratch scratch = find_scratch(0,0,0);

		u32 update_binding_count = 5;
		u32 pingpong[2][2] = {{0,1},{1,0}};
		arena_push_name(scratch.arena, 0, update_count * update_binding_count, VkWriteDescriptorSet, writes);
		for(u32 i = 0; i < frame_count ;i++)
		{
			arena_push_name(scratch.arena, 0, update_count * 5, VkDescriptorBufferInfo, buffers);
			//arena_push_name(scratch.arena, 0, update_count, VkDescriptorImageInfo, images);
			for(u32 j = 0; j < update_count; j++)
			{
				u32 k = pingpong[i][j];
				buffers[j + 0 * update_count] = (VkDescriptorBufferInfo)
				{
					.buffer = update_globals[k].handle,
					.range = VK_WHOLE_SIZE,
				};
			}
			for(u32 j = 0; j < update_count; j++)
			{
				u32 k = pingpong[i][j];
				buffers[j + 1 * update_count] = (VkDescriptorBufferInfo)
				{
					.buffer = update_target_buffers[k].handle,
					.range = VK_WHOLE_SIZE,
				};
			}
			for(u32 j = 0; j < update_count; j++)
			{
				u32 k = pingpong[i][j];
				buffers[j + 2 * update_count] = (VkDescriptorBufferInfo)
				{
					.buffer = update_scratch_buffers[k].handle,
					.range = VK_WHOLE_SIZE,
				};
			}
			for(u32 j = 0; j < update_count; j++)
			{
				u32 k = pingpong[i][j];
				buffers[j + 3 * update_count] = (VkDescriptorBufferInfo)
				{
					.buffer = update_counter_buffers[k].handle,
					.range = VK_WHOLE_SIZE,
				};
			}
			for(u32 j = 0; j < update_count; j++)
			{
				u32 k = pingpong[i][j];
				buffers[j + 4 * update_count] = (VkDescriptorBufferInfo)
				{
					.buffer = update_offset_buffers[k].handle,
					.range = VK_WHOLE_SIZE,
				};
			}
			writes[i * update_binding_count + 0] = (VkWriteDescriptorSet)
			{
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = update_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 0,
				.descriptorCount = 2,
				.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
				.pBufferInfo = buffers,
			};
			writes[i * update_binding_count + 1] = (VkWriteDescriptorSet)
			{
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = update_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 1,
				.descriptorCount = 2,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pBufferInfo = buffers + 1 * update_count,
			};
			writes[i * update_binding_count + 2] = (VkWriteDescriptorSet)
			{
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = update_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 1,
				.descriptorCount = 2,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pBufferInfo = buffers + 2 * update_count,
			};
			writes[i * update_binding_count + 3] = (VkWriteDescriptorSet)
			{
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = update_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 1,
				.descriptorCount = 2,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pBufferInfo = buffers + 3 * update_count,
			};
			writes[i * update_binding_count + 4] = (VkWriteDescriptorSet)
			{
				.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
				.dstSet = update_descriptor_pool->descriptor_sets[i].handle,
				.dstBinding = 1,
				.descriptorCount = 2,
				.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
				.pBufferInfo = buffers + 4 * update_count,
			};
		}

		vkUpdateDescriptorSets(device->handle, update_count * update_binding_count, writes,0,0);
		regress_scratch(scratch);
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
				render_target_images[i] = resize_graphics_device_image(render_target_images[i], swapchain.size);
			}
			update_pingpong_descriptor_target_images(render_descriptor_pool, 1, render_target_images);


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
		wait_and_reset_graphics_fence(render_fences[frame_index]);



		GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
		GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);


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
				.dst_access = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT,
				.old_layout = VK_IMAGE_LAYOUT_UNDEFINED,
				.new_layout = VK_IMAGE_LAYOUT_GENERAL,
			};
			cmd_graphics_pipeline_image_barrier(cb, 1, &barrier, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT, VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
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



		const u32 wave_size = 32;
		u32 resets_per_thread = 64;
		u32 counts_per_thread = 64;

		*(UpdateGlobals*)(render_globals[frame_index].memory.mapping) = (UpdateGlobals)
		{
			.update_accum = (u32)update_accum,
			.particle_count = target_buffer_count,
		};


		// Reset
		if(pe.r.pressed || (frame_accum == 0))
		{
			u32 dispatch_size = target_buffer_count / (wave_size * resets_per_thread);
			vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, reset_pipeline);
			vkCmdDispatch(cb.handle, dispatch_size, 1,1);
		}
		// Count
		{
			u32 dispatch_size = target_buffer_count / (wave_size * counts_per_thread);
			vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, count_pipeline);
			vkCmdDispatch(cb.handle, dispatch_size, 1,1);
		}
		// Prefix 
		{
		}
		// Fill
		{
		}
		// Resolve
		{
		}
		// Draw
		{
			u32x2 dispatch_size = u32x2_set(
				(target_size.x / 8) + ((target_size.x % 8) != 0),
				(target_size.y / 4) + ((target_size.y % 4) != 0)
			);


			*(RenderGlobals*)(render_globals[frame_index].memory.mapping) = (RenderGlobals)
			{
				.world_affine = f32m3_padding(camera.current_affine),
				.overlay_affine = f32m3_padding(fixed_camera.affine),
				.world_zoom = camera.current_zoom,
				.overlay_zoom = 1.0,
				.frame_accum = (u32)frame_accum,

			};

			vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, draw_pipeline);
			vkCmdDispatch(cb.handle, dispatch_size.x, dispatch_size.y,1);
		}

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
					.dst_access = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT,
					.old_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
					.new_layout = VK_IMAGE_LAYOUT_GENERAL,
				},
			};
			cmd_graphics_pipeline_image_barrier(cb, Arrlen(image_barriers), image_barriers, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT);
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

	vkDestroyPipeline(device->handle, reset_pipeline, vkb);;
	vkDestroyPipeline(device->handle, count_pipeline, vkb);;
	vkDestroyPipeline(device->handle, prefix_pipeline, vkb);;
	vkDestroyPipeline(device->handle, fill_pipeline, vkb);;
	vkDestroyPipeline(device->handle, resolve_pipeline, vkb);;
	vkDestroyPipeline(device->handle, draw_pipeline, vkb);;
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
		destroy_graphics_device_buffer(update_target_buffers[i]);
		destroy_graphics_device_buffer(update_scratch_buffers[i]);
		destroy_graphics_device_buffer(update_counter_buffers[i]);
		destroy_graphics_device_buffer(update_offset_buffers[i]);
	}


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


