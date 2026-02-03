

typedef struct{
	u64 pos;		
	u64 size;		
}Arena;

void reset_arena(Arena *arena);
Arena *init_arena(void *data, u64 size);
Arena* allocate_arena(u64 size);
void free_arena(Arena *arena);
void* arena_push(Arena *arena, b32 zero, u64 size);
void* arena_push_aligned(Arena *arena, u64 size, u64 alignment);
void arena_pop(Arena *arena, u64 size);
void arena_set(Arena *arena, u64 pos);
