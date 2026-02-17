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

#include "window.h"
#include "vk_instance.h"
#include "vk_device.h"
#include "vk_sync.h"
#include "vk_command.h"
#include "vk_memory.h"
#include "vk_image.h"
#include "vk_buffer.h"
#include "vk_barrier.h"
#include "vk_surface.h"
#include "vk_swapchain.h"
#include "vk_queue.h"
#include "vk_rasterize.h"
#include "vk_pipeline.h"

#include <ft2build.h>
#include FT_FREETYPE_H

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

Arena *main_arena;
Thread *main_thread;
Mutex thread_table_mutex;
u32 max_thread_count = 1024;
Thread **thread_table;

#include "vector.c"
#include "string.c"
#include "process.c"
#include "time.c"
#include "arena.c"
#include "thread.c"
#include "file.c"
#include "print.c"
#include "window.c"
#include "collatz.c"

void init(void)
{
	main_arena = allocate_arena(GiB(64));
	main_thread = allocate_thread(main_arena, MiB(64));

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

	GraphicsDevice *device = create_graphics_device(main_arena, instance, DISCRETE_GRAPHICS_DEVICE);
	GraphicsSwapchain swapchain = create_graphics_swapchain(main_arena, surface, device);
	Event *event_ring_buffer = allocate_ring_buffer(main_arena, Event, 1024);

	u32 frame_count = 2;
	u64 frame_accum = 0;
	u64 frame_index = 0;

	arena_push_type(main_arena, 0, frame_count * 2, Arena*, frame_arenas);
	for(u32 i = 0; i < frame_count * 2; i++)
	{
		u64 size = MiB(8);
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

	b32 running = true;

	RasterizationPipelines rasterization_pipelines = create_rasterization_pipelines(device, VK_SAMPLE_COUNT_1_BIT, VK_FORMAT_R8G8B8A8_UNORM);


	
	Vertex2 vertices[3] = {
		{.color = {{{1.0, 0.0, 0.0, 1.0}}}, .position = {{ 0.0, -0.5}}},
		{.color = {{{0.0, 1.0, 0.0, 1.0}}}, .position = {{-0.5,  0.5}}},
		{.color = {{{0.0, 0.0, 1.0, 1.0}}}, .position = {{ 0.5,  0.5}}},
	};
	GraphicsDeviceBuffer vb = create_graphics_device_buffer(device->host_cached_heap, sizeof(vertices), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
	memcpy(vb.memory.mapping, vertices, vb.size);


	const u32 max_swapchain_image_count = 8;
	arena_push_type(main_arena, 0, max_swapchain_image_count, GraphicsDeviceImage, target_images);
	for(u32 i = 0; i < swapchain.image_count; i++)
	{
		target_images[i] = create_graphics_device_image(device, swapchain.size, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
	}
	VkFramebuffer *framebuffers = create_rasterization_framebuffers(resize_arena, rasterization_pipelines, swapchain.image_count, target_images, 0);

	Event e = {0};
	while(running)
	{
		frame_index = frame_accum % frame_count;
		frame_arena = frame_arenas[frame_accum % (frame_count * 2)];


		poll_window(window, event_ring_buffer);
		b32 should_resize = false;
		while(ring_buffer_pop(event_ring_buffer, &e))
		{
			if(e.type == EVENT_KEYBOARD) 
			{
				if(e.keyboard.key == KEY_ESCAPE)
				{
					running = false;
				}
			}
			if(e.type == EVENT_WINDOW)
			{
				if(e.window.type == WINDOW_RESIZE)
				{
					should_resize = true;
					resize_accum++;
					resize_index = resize_accum % resize_count;
					resize_arena = resize_arenas[resize_index];
					reset_arena(resize_arena);
				}
			}
		}

		u32 image_index = 0;
		GraphicsDeviceImage swapchain_image = swapchain.images[image_index];
		GraphicsDeviceImage target_image = target_images[image_index];

		{
			VkResult result = vkAcquireNextImageKHR(device->handle, swapchain.handle, U64_MAX, swapchain_semaphores[frame_index].handle, 0, &swapchain.image_index);
			if(should_resize || (result != VK_SUCCESS))
			{
				wait_for_graphics_fences(frame_count, render_fences);
				VkSurfaceCapabilitiesKHR capabilities = {0};
				vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->physical.handle, swapchain.create_info.surface, &capabilities);
				swapchain.create_info.imageExtent = capabilities.minImageExtent;
				for(u32 i = 0; i < swapchain.image_count; i++)
				{
					destroy_graphics_device_image(target_images[i]);
					vkDestroyFramebuffer(device->handle, framebuffers[i], vkb);
				}
				
				swapchain = recreate_graphics_swapchain(resize_arena, swapchain);

				for(u32 i = 0; i < swapchain.image_count; i++)
				{
					target_images[i] = create_graphics_device_image(device, swapchain.size, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
				}
				framebuffers = create_rasterization_framebuffers(resize_arena, rasterization_pipelines, swapchain.image_count, target_images, 0);

				destroy_graphics_semaphore(swapchain_semaphores[frame_index]);
				swapchain_semaphores[frame_index] = create_graphics_semaphore(device);
				continue;
			}
			image_index = swapchain.image_index;
			swapchain_image = swapchain.images[image_index];
			target_image = target_images[image_index];
		}

		{
			wait_and_reset_graphics_fence(render_fences[frame_index]);
			GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
			GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);

			cmd_begin_rasterization_render_pass(cb, rasterization_pipelines.render_pass, framebuffers[image_index], swapchain.size, f32x4_set(0.1, 0.1, 0.1, 1.0));
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
				f32m3 m = f32m3_identity();
				f32m3p mp = f32m3_padding(m);
				vkCmdPushConstants(cb.handle, rasterization_pipelines.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(f32m3p), &mp);
				vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_GRAPHICS, rasterization_pipelines.vertex2);
				u64 offset = 0;
				vkCmdBindVertexBuffers(cb.handle, 0, 1, &vb.handle, &offset);
				vkCmdDraw(cb.handle, Arrlen(vertices),1, 0,0);
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
					.dst_stage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
				};
				
				cmd_graphics_pipeline_barrier(cb, barrier);
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
		}

		present_swapchain(render_queue, 1, &render_semaphores[frame_index], 1, &swapchain);

		frame_accum++;
	}
	vkDeviceWaitIdle(device->handle);

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
