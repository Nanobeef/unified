
struct Thread;



typedef struct{
	u64 pos;		
	u64 size;		
}Arena;

typedef struct{
	Arena *arena;
	u64 regress;
}Scratch;

void reset_arena(Arena *arena);
Arena *init_arena(void *data, u64 size);
Arena* allocate_arena(u64 size);
void free_arena(Arena *arena);
void* arena_push(Arena *arena, b32 zero, u64 size);
void* arena_push_aligned(Arena *arena, u64 size, u64 alignment);
void arena_pop(Arena *arena, u64 size);
void arena_set(Arena *arena, u64 pos);
Scratch find_scratch(struct Thread *thread, u32 conflict_count, Arena **conflicts);
void regress_scratch(Scratch scratch);


#define TOTAL( VARIABLE ) (*(((u64*)(VARIABLE))-1))
#define USED( VARIABLE ) (*(((u64*)(VARIABLE))-2))

typedef struct{
	u64 used;
	u64 total;
}Array;

#define allocate_array( ARENA , TYPE , COUNT ) (TYPE*)allocate_array_stride((ARENA), sizeof(TYPE), (COUNT))
#define inherit_array( ARENA , TYPE ) (TYPE*)allocate_array_stride((ARENA), sizeof(TYPE), ((ARENA)->size - sizeof(Array)) / sizeof(TYPE))

void *allocate_array_stride(Arena *arena, u64 stride, u64 count);

typedef struct{
	u64 total;
}Buffer;

#define allocate_buffer( ARENA , TYPE , COUNT ) (TYPE*)allocate_buffer_stride((ARENA), sizeof(TYPE), (COUNT))
#define inherit_buffer( ARENA , TYPE ) (TYPE*)allocate_buffer_stride((ARENA), sizeof(TYPE), ((ARENA)->size - sizeof(Buffer)) / sizeof(TYPE))

void *allocate_buffer_stride(Arena *arena, u64 stride, u64 count);
