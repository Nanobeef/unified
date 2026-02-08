
#include "base.h"
#include "vector.h"
#include "time.h"
#include "arena.h"
#include "string.h"
#include "process.h"
#include "print.h"
#include "thread.h"
#include "file.h"

#include <dirent.h>

#include <vulkan/vulkan.h>
#include "vk_instance.h"
#include "vk_device.h"

#include <ft2build.h>
#include FT_FREETYPE_H

#include "vk_instance.c"
#include "vk_device.c"

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

	GraphicsInstance *instance = create_graphics_instance(main_arena);
	destroy_graphics_instance(instance);

	cleanup();
}
