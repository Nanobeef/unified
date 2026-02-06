
void reset_arena(Arena *arena)
{
	arena->pos = sizeof(Arena);
}

Arena *init_arena(void *data, u64 size)
{
	Arena *arena = data;
	arena->size = size;
	reset_arena(arena);
	return arena; }
Arena* allocate_arena(u64 size)
{
	size = ForwardAlign(size, 4096);
	void *data = malloc(size);
	Arena *arena = init_arena(data, size);
	return arena;
}

void free_arena(Arena *arena)
{
	free(arena);
}

void* arena_push(Arena *arena, b32 zero, u64 size)
{
	void *data = (void*)((u64)arena + arena->pos);
	arena->pos += size;
	if(zero)
	{
		memset(data, 0, size);
	}
	return data;
}
void* arena_push_aligned(Arena *arena, u64 size, u64 alignment)
{
	arena->pos = ForwardAlign(arena->pos, alignment);
	void *data = (void*)((u64)arena + arena->pos);
	arena->pos += size;
	return data;
}
void arena_set(Arena *arena, u64 pos)
{
	arena->pos = Max(sizeof(Arena), pos);
}
void arena_pop(Arena *arena, u64 size)
{
	arena_set(arena, arena->pos - size);
}

Scratch find_scratch(struct Thread *thread, u32 conflict_count, Arena **conflicts)
{
	Scratch scratch = {0,0};
	if(thread == 0)
		thread = current_thread();
	if(thread == 0)
		return scratch;
	
	for(u32 i = 0; i < 2; i++)
	{
		b32 has_conflict = false;
		for(u32 j = 0; j < conflict_count; j++)
		{
			if(conflicts[j] == thread->scratch_arenas[i])
			{
				has_conflict = true;
			}
		}
		if(has_conflict == false)
		{
			scratch.arena = thread->scratch_arenas[i];
			break;
		}
	}
	if(scratch.arena == 0)
		printf("Scratch arena is ZERO!!!\n");
	scratch.regress = scratch.arena->pos;
	return scratch;
}
void regress_scratch(Scratch scratch)
{
	scratch.arena->pos = scratch.regress;
}

void *allocate_array_stride(Arena *arena, u64 stride, u64 count)
{
	Array *array = arena_push(arena, 0, count * stride + sizeof(Array));
	array->used = 0;
	array->total = count;
	return (void*)(array + 1);
}

void *allocate_buffer_stride(Arena *arena, u64 stride, u64 count)
{
	Array *buffer = arena_push(arena, 0, count * stride + sizeof(Buffer));
	buffer->total = count;
	return (void*)(buffer + 1);
}
