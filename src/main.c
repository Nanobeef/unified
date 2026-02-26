#include "base.h"
#include "vector.h"
#include "time.h"
#include "arena.h"
#include "string.h"
#include "process.h"
#include "print.h"
#include "thread.h"
#include "file.h"
#include "event.h"

#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define VK_USE_PLATFORM_XCB_KHR
#include <vulkan/vulkan.h>

#include <xcb/xcb_keysyms.h>
#include <xcb/xproto.h>
#include <X11/keysym.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "window.h"
#include "vk_instance.h"
#include "vk_device.h"
#include "vk_command.h"
#include "vk_sync.h"
#include "vk_memory.h"
#include "vk_image.h"
#include "vk_buffer.h"
#include "vk_barrier.h"
#include "vk_surface.h"
#include "vk_swapchain.h"
#include "vk_queue.h"
#include "vk_descriptor.h"
#include "vk_rasterize.h"
#include "vk_pipeline.h"
#include "camera.h"
#include "random.h"
#include "vk_font.h"
#include "vk_vertex_buffer.h"
#include "vk_draw.h"


#include "vk_instance.c"
#include "vk_device.c"
#include "vk_command.c"
#include "vk_sync.c"
#include "vk_queue.c"
#include "vk_surface.c"
#include "vk_swapchain.c"
#include "vk_image.c"
#include "vk_buffer.c"
#include "vk_memory.c"
#include "vk_barrier.c"
#include "vk_rasterize.c"
#include "camera.c"
#include "random.c"
#include "vk_vertex_buffer.c"
#include "vk_font.c"
#include "vk_descriptor.c"
#include "vk_draw.c"

Arena *main_arena;
Thread *main_thread;
Mutex thread_table_mutex;
u32 max_thread_count = 1024;
Thread **thread_table;
u64 epoch_time_ns;

#include "vector.c"
#include "string.c"
#include "process.c"
#include "time.c"
#include "arena.c"
#include "thread.c"
#include "file.c"
#include "event.c"
#include "print.c"
#include "window.c"
#include "collatz.c"

void init(void)
{
	epoch_time_ns = get_time_ns();
	main_arena = allocate_arena(GiB(64));
	main_thread = allocate_thread(main_arena, MiB(64));
#if defined(thread_local)
	CURRENT_THREAD = main_thread;
#endif

	thread_table = arena_push(main_arena, true, max_thread_count * sizeof(Thread*));
	thread_table_mutex = create_mutex();
}

void cleanup(void)
{
	destroy_mutex(thread_table_mutex);
	free_arena(main_arena);
	exit(0);
}




s32 main(void)
{
	init();

	Window *window = create_window(main_arena);
	GraphicsInstance *instance = create_graphics_instance(main_arena);
	GraphicsSurface surface = create_graphics_surface(window, instance);

	GraphicsDevice *device = create_graphics_device(main_arena, instance, 1);
	GraphicsSwapchain swapchain = create_graphics_swapchain(main_arena, surface, device);
	Event *event_ring_buffer = allocate_ring_buffer(main_arena, Event, 1024);

	u32 frame_count = 2;
	u64 frame_accum = 0;
	u64 frame_index = 0;

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

	GraphicsEvent *font_cache_events = create_graphics_events(main_arena, device, frame_count);


	VkFormat target_format = VK_FORMAT_B8G8R8A8_UNORM;
	VkSampleCountFlags sample_count = VK_SAMPLE_COUNT_8_BIT;
	RasterizationPipelines rasterization_pipelines = create_rasterization_pipelines(device, sample_count, target_format);

	GraphicsDeviceFontCache *font_cache = create_graphics_device_font_cache(main_arena, device, window->screen_dpi);

	arena_push_type(main_arena, 0, frame_count, GraphicsDeviceVertexBuffer, world_vertex_buffers);
	arena_push_type(main_arena, 0, frame_count, GraphicsDeviceVertexBuffer, overlay_vertex_buffers);
	for(u32 i = 0; i < frame_count; i++)
	{
		u64 vb_size = MiB(16);
		world_vertex_buffers[i] = create_graphics_device_vertex_buffer(device->host_cached_heap, vb_size, sizeof(Vertex2), font_cache);
		overlay_vertex_buffers[i] = create_graphics_device_vertex_buffer(device->host_cached_heap, vb_size, sizeof(Vertex2), font_cache);
	}
	const u32 max_swapchain_image_count = 8;
	arena_push_type(main_arena, 0, max_swapchain_image_count, GraphicsDeviceImage, target_images);
	GraphicsDeviceImage *msaa_images = 0;
	if(sample_count > VK_SAMPLE_COUNT_1_BIT)
		msaa_images = arena_push(main_arena, 0, max_swapchain_image_count * sizeof(GraphicsDeviceImage));
	for(u32 i = 0; i < swapchain.image_count; i++)
	{
		target_images[i] = create_graphics_device_image(device, swapchain.size, target_format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
		if(sample_count > VK_SAMPLE_COUNT_1_BIT)
			msaa_images[i] = create_graphics_device_image_explicit(device->device_heap, swapchain.size, target_format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_IMAGE_TILING_OPTIMAL, sample_count);
	}
	VkFramebuffer *framebuffers = create_rasterization_framebuffers(resize_arena, rasterization_pipelines, swapchain.image_count, target_images, msaa_images);

	arena_push_type(main_arena, 0, frame_count, GraphicsDescriptorPool*, frame_descriptor_pools);
	for(u32 i = 0; i < frame_count; i++)
	{
		frame_descriptor_pools[i] = create_graphics_descriptor_pool(main_arena, device, 1, &rasterization_pipelines.descriptor_set_layout);
		VkDescriptorImageInfo image_info = {
			.imageView = font_cache->linear_image.view,
			.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		};
		VkWriteDescriptorSet write = {
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.dstSet = frame_descriptor_pools[i]->descriptor_sets[0].handle,
			.dstBinding = 0,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.pImageInfo = &image_info,
		};
		vkUpdateDescriptorSets(device->handle, 1, &write, 0, 0);
	}

	Camera camera = init_camera();
	FixedCamera fixed_camera = create_fixed_camera(window->size);

	{
		wait_and_reset_graphics_fence(render_fences[frame_index]);
		GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
		GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);
		{
			GraphicsImageMemoryBarrier image_barrier = {
				.image = font_cache->linear_image,
				.old_layout = VK_IMAGE_LAYOUT_UNDEFINED,
				.new_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				.src_access = VK_ACCESS_NONE,
				.dst_access = VK_ACCESS_HOST_WRITE_BIT,
			};

			GraphicsPipelineBarrier barrier = {
				.image_memory_barrier_count = 1,
				.image_memory_barriers = &image_barrier,
				.src_stage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
				.dst_stage = VK_PIPELINE_STAGE_HOST_BIT,
			};
			cmd_graphics_pipeline_barrier(cb, barrier);
		}
		end_graphics_command_buffer(cb);
		submit_command_buffers(
			render_queue,
			0, 0,
			0, 0,
			1, &cb, 
			0,
			render_fences[frame_index]
		);

	}


	u64 desired_frame_time = 1000000000/144;
	u64 start_time = get_time_ns();;
	u64 end_time = 0;
	u64 elapsed_time = 0;
	u64 sleep_time = 0;
	u64 frame_time = 0;
	while(true)
	{
		end_time = get_time_ns();
		elapsed_time = end_time - start_time;
		sleep_time = 0;
		if(elapsed_time < desired_frame_time)
		{
			sleep_time = desired_frame_time - elapsed_time;
			usleep(sleep_time / 1000);
		}
		frame_time = elapsed_time + sleep_time;
		start_time = get_time_ns();
		
		frame_index = frame_accum % frame_count;
		frame_arena = frame_arenas[frame_accum % (frame_count * 2)];
		reset_arena(frame_arena);

		poll_window(window, event_ring_buffer);
		PolledEvents pe = poll_events(frame_arena, event_ring_buffer);
		if(pe.escape.pressed)
			break;

		update_camera(&camera, pe, window->size, false);
		fixed_camera = create_fixed_camera(window->size);


		u32 image_index = 0;
		GraphicsDeviceImage swapchain_image = swapchain.images[image_index];
		GraphicsDeviceImage target_image = target_images[image_index];
		{
			VkResult result = vkAcquireNextImageKHR(device->handle, swapchain.handle, U64_MAX, swapchain_semaphores[frame_index].handle, 0, &swapchain.image_index);
			if(pe.window_should_resize || (result != VK_SUCCESS))
			{
				resize_accum++;
				resize_index = resize_accum % resize_count;
				resize_arena = resize_arenas[resize_index];
				reset_arena(resize_arena);

				wait_for_graphics_fences(frame_count, render_fences);
				VkSurfaceCapabilitiesKHR capabilities = {0};
				vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->physical.handle, swapchain.create_info.surface, &capabilities);
				swapchain.create_info.imageExtent = capabilities.minImageExtent;
				for(u32 i = 0; i < swapchain.image_count; i++)
				{
					if(sample_count > VK_SAMPLE_COUNT_1_BIT)
						destroy_graphics_device_image(msaa_images[i]);
					destroy_graphics_device_image(target_images[i]);
					vkDestroyFramebuffer(device->handle, framebuffers[i], vkb);
				}
				
				swapchain = recreate_graphics_swapchain(resize_arena, swapchain);

				for(u32 i = 0; i < swapchain.image_count; i++)
				{
					target_images[i] = create_graphics_device_image(device, swapchain.size, target_format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
					if(sample_count > VK_SAMPLE_COUNT_1_BIT)
						msaa_images[i] = create_graphics_device_image_explicit(device->device_heap, swapchain.size, target_format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_IMAGE_TILING_OPTIMAL, sample_count);
				}
				framebuffers = create_rasterization_framebuffers(resize_arena, rasterization_pipelines, swapchain.image_count, target_images, msaa_images);

				destroy_graphics_semaphore(swapchain_semaphores[frame_index]);
				swapchain_semaphores[frame_index] = create_graphics_semaphore(device);
				continue;
			}
			image_index = swapchain.image_index;
			swapchain_image = swapchain.images[image_index];
			target_image = target_images[image_index];

		}
		{
			GraphicsDeviceVertexBuffer *vb = begin_graphics_device_vertex_buffer(overlay_vertex_buffers + frame_index, font_cache, frame_arena);
			Scratch scratch = find_scratch(0,0,0);
			String8 str = str8_print(scratch.arena, "Time:\t\t%ets\nElapsed Time:\t%tus\nSleep Time:\t%tus\nFrame Time:\t%tus\nTarget Time:\t%tus", elapsed_time, sleep_time, frame_time, desired_frame_time);
			draw_str8_wrap(vb, fixed_camera, f32x2_set(10,0), window->size.x, str, 20, f32x4_color_white);
			regress_scratch(scratch);
			end_graphics_device_vertex_buffer(vb);
		}

		{
			GraphicsDeviceVertexBuffer *vb = begin_graphics_device_vertex_buffer(world_vertex_buffers + frame_index, font_cache, frame_arena);
			
			RomuQuad rq = romu_quad_seed(get_epoch_ms() / 250);
			u64 triangle_count = 10000;
			for(u32 i = 0; i < triangle_count * 3; i+=3)
			{
				f32x2 point = romu_quad_f32x2(&rq);
				point = f32x2_mul1(point, 0.9f);
				f64 d = romu_quad_f64(&rq);
				int ds = signbit(d);
				d *= 2.0;
				d = d * fabs(d);
				f64 t = (f64)(get_epoch_ms()) / 1000.0 * d;
				f32 scale = sinf(t * 6.0) * 0.02 + 0.1 + 1;
				scale = 0.05;
				f32m2 rotate = f32m2_rotate(t);
				rotate = f32m2_mul(rotate, f32m2_scale(scale, scale));

				/*
				Vertex2 vertices[3] = {
					{.color = {{{1.0, 0.0, 0.0, 1.0}}}, .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
					{.color = {{{0.0, 1.0, 0.0, 1.0}}}, .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
					{.color = {{{0.0, 0.0, 1.0, 1.0}}}, .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
				};
				*/
				Vertex2 vertices[3] = {
					{.color = romu_quad_color(&rq), .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
					{.color = romu_quad_color(&rq), .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
					{.color = romu_quad_color(&rq), .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
				};
				graphics_device_vertex_buffer_push(vb, 3, vertices);
			}
			end_graphics_device_vertex_buffer(vb);
		}

		wait_and_reset_graphics_fence(render_fences[frame_index]);
		GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);

			
		{
			GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);
			vkCmdBindDescriptorSets(cb.handle, VK_PIPELINE_BIND_POINT_GRAPHICS, rasterization_pipelines.layout, 0, 1, &frame_descriptor_pools[frame_index]->descriptor_sets[0].handle, 0,0);

			{
				GraphicsImageMemoryBarrier image_barrier = {
					.image = font_cache->linear_image,
					.old_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					.new_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					.src_access = VK_ACCESS_HOST_WRITE_BIT,
					.dst_access = VK_ACCESS_SHADER_READ_BIT,
				};

				GraphicsPipelineBarrier barrier = {
					.image_memory_barrier_count = 1,
					.image_memory_barriers = &image_barrier,
					.src_stage = VK_PIPELINE_STAGE_HOST_BIT,
					.dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
				};
				cmd_graphics_pipeline_barrier(cb, barrier);
			}

			cmd_begin_rasterization_render_pass(cb, rasterization_pipelines.render_pass, framebuffers[image_index], swapchain.size, f32x4_set(0.01, 0.01, 0.01, 1.0));
			{
				VkRect2D scissor = {
					.offset = {0,0},
					.extent = {swapchain.size.x, swapchain.size.y},
				};
				vkCmdSetScissor(cb.handle, 0,1,&scissor);
				VkViewport viewport = {
					.maxDepth = 1.0,
					.x = 0,
					.y = 0,
					.width = (f32)swapchain.size.x,
					.height= (f32)swapchain.size.y,
				};
				vkCmdSetViewport(cb.handle, 0,1,&viewport);
			}
			{
				vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_GRAPHICS, rasterization_pipelines.vertex2);

				{
					f32m3p mp = f32m3_padding(camera.current_affine);
					vkCmdPushConstants(cb.handle, rasterization_pipelines.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(f32m3p), &mp);
					cmd_draw_graphics_device_vertex_buffer(cb, world_vertex_buffers[frame_index]);
				}
				{
					f32m3p mp = f32m3_padding(fixed_camera.affine);
					vkCmdPushConstants(cb.handle, rasterization_pipelines.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(f32m3p), &mp);
					cmd_draw_graphics_device_vertex_buffer(cb, overlay_vertex_buffers[frame_index]);
				}
			}
			vkCmdEndRenderPass(cb.handle);

			{
				GraphicsImageMemoryBarrier image_barrier = {
					.image = swapchain_image,
					.old_layout = VK_IMAGE_LAYOUT_UNDEFINED,
					.new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.src_access = VK_ACCESS_NONE,
					.dst_access = VK_ACCESS_TRANSFER_WRITE_BIT,
				};

				GraphicsPipelineBarrier barrier = {
					.image_memory_barrier_count = 1,
					.image_memory_barriers = &image_barrier,
					.src_stage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
					.dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT,
				};
				
				cmd_graphics_pipeline_barrier(cb, barrier);
			}

			cmd_blit_graphics_device_image(cb, target_image, swapchain_image);

			{
				GraphicsImageMemoryBarrier image_barrier = {
					.image = swapchain_image,
					.old_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
					.new_layout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
					.src_access = VK_ACCESS_TRANSFER_WRITE_BIT,
					.dst_access = VK_ACCESS_NONE,
				};

				GraphicsPipelineBarrier barrier = {
					.image_memory_barrier_count = 1,
					.image_memory_barriers = &image_barrier,
					.src_stage = VK_PIPELINE_STAGE_TRANSFER_BIT,
					.dst_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
				};
				
				cmd_graphics_pipeline_barrier(cb, barrier);
			}

			end_graphics_command_buffer(cb);

			{
				resolve_graphics_device_font_cache(font_cache);
			}
		
			submit_command_buffers(
				render_queue,
				1, &swapchain_semaphores[frame_index], 
				1, &render_semaphores[frame_index], 
				1, &cb, 
				0,
				render_fences[frame_index]
			);
		}

		present_swapchain(render_queue, 1, &render_semaphores[frame_index], 1, &swapchain);

		frame_accum++;
	}
	vkDeviceWaitIdle(device->handle);


	for(u32 i = 0; i < swapchain.image_count; i++)
	{
		vkDestroyFramebuffer(device->handle, framebuffers[i], vkb);
		destroy_graphics_device_image(target_images[i]);
		if(sample_count > VK_SAMPLE_COUNT_1_BIT)
			destroy_graphics_device_image(msaa_images[i]);
			
	}
	destroy_graphics_device_font_cache(font_cache);
	for(u32 i = 0; i < frame_count; i++)
	{
		destroy_graphics_descriptor_pool(frame_descriptor_pools[i]);
		destroy_graphics_device_vertex_buffer(world_vertex_buffers[i]);
		destroy_graphics_device_vertex_buffer(overlay_vertex_buffers[i]);
	}
	destroy_graphics_events(frame_count, font_cache_events);

	destroy_rasterization_pipelines(rasterization_pipelines);
	destroy_graphics_semaphores(frame_count, swapchain_semaphores);
	destroy_graphics_semaphores(frame_count, render_semaphores);
	destroy_graphics_fences(frame_count, render_fences);
	destroy_graphics_command_pools(frame_count, render_command_pools); 
	destroy_graphics_swapchain(swapchain);
	destroy_graphics_device(device);
	destroy_graphics_surface(surface);
	destroy_graphics_instance(instance);
	destroy_window(window);

	cleanup();
}
