
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
		memset(data, size, 0);
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

void arena_pop(Arena *arena, u64 size)
{
	arena->pos -= size;
}
void arena_set(Arena *arena, u64 pos)
{
	arena->pos = pos;	
}
