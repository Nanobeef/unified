#include "base.h"
#include "vector.h"
#include "string.h"
#include "process.h"
#include "time.h"
#include "arena.h"
#include "thread.h"

#include "vector.c"
#include "string.c"
#include "process.c"
#include "time.c"
#include "arena.c"
#include "thread.c"

static Arena *main_arena;
static Thread *main_thread;
static u32 max_thread_count = 64;
static Thread *thread_table;

void init()
{
	main_arena = allocate_arena(GiB(64));
	main_thread = allocate_thread(main_arena, MiB(64));
#ifdef COMPILER_TCC
	thread_table = arena_push(main_arena, 0, max_thread_count * sizeof(Thread));
#endif
}

void cleanup()
{
	free_arena(main_arena);
}

s32 main(void)
{
	init();
	cleanup();
	return 0;
}


