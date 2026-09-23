
	#include <xcb/xcb_keysyms.h>
	#include <xcb/xproto.h>
	#include <xcb/randr.h>
	#include <xcb/xkb.h>
	#include <X11/keysym.h>
	#include <xcb/xcb_ewmh.h>

	#define VK_USE_PLATFORM_XCB_KHR
	#include <vulkan/vulkan.h>

	#include <ft2build.h>
	#include FT_FREETYPE_H

// PROCESS
	#include <dirent.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sched.h>

// BASE
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
	#include "camera.h"
	#include "info.h"
	#include "random.h"

Arena *main_arena;
Thread *main_thread;
Mutex thread_table_mutex;
u32 max_thread_count = 1024;
u64 physical_thread_count = 1;
Thread **thread_table;
u64 epoch_time_ns;

// SURFACE
	#include "window.h"

// GRAPHICS
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
	#include "vk_pipeline.h"
	#include "vk_font.h"
	#include "vk_vertex_buffer.h"
	#include "vk_draw.h"
	#include "vk_query.h"
	#include "ui.h"

// AUDIO 
	#include <alsa/asoundlib.h>
	#include "audio.h"

// PILE
	#include "pile.h"

	#include "boid.h"

// GRAPHICS
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
	#include "vk_pipeline.c"
	#include "vk_compute.c"
	#include "camera.c"
	#include "vk_vertex_buffer.c"
	#include "vk_font.c"
	#include "vk_descriptor.c"
	#include "vk_draw.c"
	#include "vk_query.c"
	#include "ui.c"

// BASE
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
	#include "random.c"

// AUDIO 
	#include "audio.c"

// PILE
	#include "pile.c"

 	#include "boid.c"

	
#include "font.h"
#include "font.c"
#include "perf.h"
#include "perf.c"
#include "perfground.h"
#include "perfground.c"

#include "run_boids.c"
#include "run_unified.c"

void init(void)
{
	epoch_time_ns = get_time_ns();
	main_arena = allocate_arena(GiB(64));
	main_thread = allocate_thread(main_arena, MiB(64));
#if defined(thread_local)
	CURRENT_THREAD = main_thread;
#endif

	thread_table = arena_push(main_arena, true, max_thread_count * sizeof(Thread*));
	if(1)
	{
		struct sched_param param = {.sched_priority = sched_get_priority_max(SCHED_FIFO)};
		pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
	}
	physical_thread_count = get_physical_thread_count();
	b32 t = set_thread_affinity(main_thread, physical_thread_count - 1);
}

void cleanup(void)
{
	destroy_mutex(thread_table_mutex);
	free_arena(main_arena);
	exit(0);
}

void rng_test()
{
	RomuQuad rq = romu_quad_seed(5354);
	u64 n = MiB(128);
	u64 *dst  = malloc(n * sizeof(u64));


	// First few itterations for warm up.

	for(u32 j = 0; j < 100; j++)
	{
		u64 elapsed = get_time_ns();

		for(u64 i = 0; i < n; i++)
		{
			if(1)
			{
				dst[i] = romu_quad(&rq);		
			}
			else
			{
				u16 temp[4];
				for(u32 k = 0; k < 4; k++)
				{
					temp[k] = rand();	
				}
				memcpy(dst + i, temp, 8);
			}
		}

		elapsed = get_time_ns() - elapsed;
		f64 rate = (f64)n / (f64)elapsed;
		rate *= 8.0;

		print("Itteration %u32\n\t%u64 in %t\n\t%f64 bytes / ns\n", j,n, elapsed, rate);

	}


	// Set 'a' so results are not optimized out.
	u64 a = 0;

	for(u64 i = 0; i < n; i++)
	{
		a += dst[i];		
	}
	print("%u64\n", a);
}

s32 main()
{
	init();
	run_unified();
	cleanup();
}

