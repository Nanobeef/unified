
typedef void (VKAPI_PTR *PFN_vkCmdPipelineBarrier)(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier* pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier* pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier* pImageMemoryBarriers);
s32 run_unified(void)
{

	AudioDevice *audio_device = create_audio_device(main_arena);

	Window *window = create_window(main_arena);
	GraphicsInstance *instance = create_graphics_instance(main_arena);
	GraphicsSurface surface = create_graphics_surface(window, instance);
	GraphicsDevice *device = create_graphics_device(main_arena, instance, 0);
	GraphicsSwapchain swapchain = create_graphics_swapchain(main_arena, surface, device);

	Event *event_ring_buffer = allocate_ring_buffer(main_arena, Event, 1024);

	u32 frame_count = 2;
	u64 frame_accum = 0;
	u64 frame_index = 0;
	u64 last_frame_index = 1;

	arena_push_type(main_arena, 0, frame_count * 2, Arena*, frame_arenas);
	for(u32 i = 0; i < frame_count * 2; i++)
	{
		u64 size = MiB(64);
		frame_arenas[i] = init_arena(size, arena_push(main_arena, 0, size));
	}

	u32 resize_count = 2;
	u64 resize_accum = 0;
	u64 resize_index = 0;
	arena_push_type(main_arena, 0, frame_count, Arena*, resize_arenas);
	for(u32 i = 0; i < resize_count; i++)
	{
		u64 size = MiB(8);
		resize_arenas[i] = init_arena(size, arena_push(main_arena, 0, size));
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

	arena_push_type(main_arena, 0, frame_count, GraphicsDeviceImage, target_images);
	for(u32 i = 0; i < frame_count; i++)
	{
		target_images[i] = create_graphics_device_image_explicit(device->device_heap, swapchain.size, VK_FORMAT_B8G8R8A8_UNORM, VK_IMAGE_USAGE_TRANSFER_DST_BIT| VK_IMAGE_USAGE_TRANSFER_SRC_BIT | VK_IMAGE_USAGE_STORAGE_BIT, VK_IMAGE_TILING_OPTIMAL, VK_SAMPLE_COUNT_1_BIT);
	}




	VkPipelineLayout pipeline_layout = 0;
	GraphicsDescriptorSetLayout render_descriptor_set_layout;
	{
		VkDescriptorSetLayoutBinding bindings[] = {
			{0, VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1, VK_SHADER_STAGE_COMPUTE_BIT, 0},
		};
		render_descriptor_set_layout = create_graphics_descriptor_set_layout(device, Arrlen(bindings), bindings);
		VkPipelineLayoutCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.setLayoutCount = 1,
			.pSetLayouts = &render_descriptor_set_layout.handle,
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

	VkPipeline test_compute = create_compute_pipeline_from_file(device, pipeline_layout, "build/test_comp.spv");



	u64 frame_start_time = get_epoch_ns() - window->refresh_rate;
	u64 frame_end_time = 0;
	b32 just_resized = false;
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
		frame_time = frame_elapsed_time + frame_sleep_time;
		
		last_frame_index = frame_index;
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
		if(pe.window_should_resize || (result != VK_SUCCESS))
		{
			mark_time();
			resize_accum++;
			resize_index = resize_accum % resize_count;
			resize_arena = resize_arenas[resize_index];
			reset_arena(resize_arena);

			wait_for_graphics_fences(frame_count, render_fences);
			for(u32 i = 0; i < frame_count; i++)
			{
				destroy_graphics_device_image(target_images[i]);
			}

			VkSurfaceCapabilitiesKHR capabilities = {0};
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->physical.handle, swapchain.create_info.surface, &capabilities);
			swapchain.create_info.imageExtent = capabilities.minImageExtent;
			
			swapchain = recreate_graphics_swapchain(resize_arena, swapchain);

			for(u32 i = 0; i < frame_count; i++)
			{
				target_images[i] = resize_graphics_device_image(target_images[i], swapchain.size);
			}
			{
				VkWriteDescriptorSet writes[frame_count];
				VkDescriptorImageInfo image_infos[frame_count];
				for(u32 i = 0; i < frame_count; i++)
				{
					image_infos[i] = (VkDescriptorImageInfo)
					{
						.imageView = target_images[i].view,
						.imageLayout = VK_IMAGE_LAYOUT_GENERAL,
					};
					writes[i] = (VkWriteDescriptorSet)
					{
						.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
						.dstSet = render_descriptor_pool->descriptor_sets[i].handle,
						.dstBinding = 0,
						.descriptorCount = 1,
						.descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
						.pImageInfo = &image_infos[i],
					};
							
				}
				vkUpdateDescriptorSets(device->handle, frame_count, writes, 0,0);
			}

			destroy_graphics_semaphore(swapchain_semaphores[frame_index]);
			swapchain_semaphores[frame_index] = create_graphics_semaphore(device);
			frame_start_time = get_epoch_ns() - window->refresh_rate;
			just_resized = true;
			continue;
		}
		GraphicsDeviceImage swapchain_image = swapchain.images[swapchain.image_index];
		update_camera(&camera, pe, window->size, false);
		wait_and_reset_graphics_fence(render_fences[frame_index]);
		GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
		GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);



		vkCmdBindDescriptorSets(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, pipeline_layout, 0, 1, &render_descriptor_pool->descriptor_sets[frame_index].handle, 0,0);
		vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_COMPUTE, test_compute);
		u32x2 dispatch_size = u32x2_set(
			(swapchain.size.x / 32) + ((swapchain.size.x % 32) != 0),
			(swapchain.size.y / 32) + ((swapchain.size.y % 32) != 0)
		);
		print("%u32 %u32 %u32\n", swapchain.size.x, swapchain.size.x / 32, dispatch_size.x);


		vkCmdDispatch(cb.handle, dispatch_size.x, dispatch_size.y,1);


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
					.image = target_images[frame_index],
					.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
					.src_access = VK_ACCESS_SHADER_READ_BIT | VK_ACCESS_SHADER_WRITE_BIT,
					.dst_access = VK_ACCESS_TRANSFER_READ_BIT,
					.old_layout = VK_IMAGE_LAYOUT_GENERAL,
					.new_layout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
				},
			};
			cmd_graphics_pipeline_image_barrier(cb, Arrlen(image_barriers), image_barriers, VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);
		}

		cmd_blit_graphics_device_image(cb, target_images[frame_index], swapchain.images[swapchain.image_index]);


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
					.image = target_images[frame_index],
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


		frame_accum++;
	}
	vkDeviceWaitIdle(device->handle);


	vkDestroyPipeline(device->handle, test_compute, vkb);;
	destroy_graphics_descriptor_pool(render_descriptor_pool);
	destroy_graphics_descriptor_set_layout(render_descriptor_set_layout);
	vkDestroyPipelineLayout(device->handle, pipeline_layout, vkb);


	for(u32 i = 0; i < frame_count; i++)
	{
		destroy_graphics_device_image(target_images[i]);
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
