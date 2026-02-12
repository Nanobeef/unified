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

#define VK_USE_PLATFORM_XCB_KHR
#include <vulkan/vulkan.h>

#include <xcb/xcb_keysyms.h>
#include <X11/keysym.h>

#include "window.h"
#include "vk_instance.h"
#include "vk_device.h"
#include "vk_sync.h"
#include "vk_command.h"
#include "vk_memory.h"
#include "vk_image.h"
#include "vk_buffer.h"
#include "vk_surface.h"
#include "vk_swapchain.h"
#include "vk_queue.h"


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

	GraphicsDevice *device = create_graphics_device(main_arena, instance, INTEGRATED_GRAPHICS_DEVICE);
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

	GraphicsFence *swapchain_fences = create_graphics_fences(main_arena, device, frame_count, true);
	GraphicsFence *render_fences = create_graphics_fences(main_arena, device, frame_count, true);

	GraphicsCommandPool **render_command_pools = create_graphics_command_pools(main_arena, device->main_queue_family, frame_count, 1);
	GraphicsDeviceQueue render_queue = device->main_queue_family->queues[0];

	

	b32 running = true;

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
				}
			}
		}
		resize_arena = resize_arenas[resize_index];

		wait_and_reset_graphics_fence(swapchain_fences[frame_index]);
		
		u32 image_index = acquire_graphics_swapchain_image(resize_arena, &swapchain, swapchain_semaphores[frame_index], swapchain_fences[frame_index], should_resize);

		{
			wait_and_reset_graphics_fence(render_fences[frame_index]);
			GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
			GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);



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

	destroy_graphics_swapchain(swapchain);
	destroy_graphics_device(device);
	destroy_graphics_surface(surface);
	destroy_graphics_instance(instance);
	destroy_window(window);

	cleanup();
}
