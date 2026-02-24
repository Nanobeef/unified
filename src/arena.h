
struct Thread;



typedef struct{
	u64 pos;		
	u64 last;
	u64 size;		
}Arena;

typedef struct{
	Arena *arena;
	u64 regress;
}Scratch;

void reset_arena(Arena *arena);
Arena *init_arena(u64 size, void *data);
Arena* allocate_arena(u64 size);
void free_arena(Arena *arena);
void* arena_push(Arena *arena, b32 zero, u64 size);
void* arena_push_aligned(Arena *arena, u64 size, u64 alignment);
void arena_pop(Arena *arena, u64 size);
void arena_set(Arena *arena, u64 pos);
Scratch find_scratch(struct Thread *thread, u32 conflict_count, Arena **conflicts);
Scratch force_scratch(u32 index);
void regress_scratch(Scratch scratch);

#define arena_push_type( ARENA, ZERO, COUNT , TYPE , NAME) TYPE* NAME = (TYPE*)arena_push(ARENA, ZERO, (COUNT) * sizeof(TYPE));


#define TOTAL( VARIABLE ) (*(((u64*)(VARIABLE))-1))
#define USED( VARIABLE ) (*(((u64*)(VARIABLE))-2))

typedef struct{
	u64 used;
	u64 total;
}Array;

#define allocate_array( ARENA , TYPE , COUNT ) (TYPE*)allocate_array_stride((ARENA), sizeof(TYPE), (COUNT))
#define inherit_array( ARENA , TYPE ) (TYPE*)allocate_array_stride((ARENA), sizeof(TYPE), ((ARENA)->size - sizeof(Array)) / sizeof(TYPE))

#define append_array( ARENA, TYPE, PTR_PTR, SRC)\
({\
	TYPE* PTR = *(PTR_PTR);\
	if(USED(PTR) == TOTAL(PTR))\
	{\
		u64 used = USED(PTR);\
		u64 new_total = TOTAL(PTR) * 2;\
		TYPE *NEW_PTR = 0;\
		if((u8*)(ARENA) + (ARENA)->last == (u8*)(PTR) - sizeof(Array))\
		{\
			arena_set(ARENA, (ARENA)->last);\
			NEW_PTR = allocate_array(ARENA, TYPE, new_total);\
			USED(NEW_PTR) = used;\
		}\
		else\
		{\
			NEW_PTR = allocate_array(ARENA, TYPE, new_total);\
			memcpy(NEW_PTR, PTR, USED(PTR) * sizeof(TYPE));\
			USED(NEW_PTR) = used;\
		}\
		(PTR_PTR)[0] = NEW_PTR;\
	}\
	TYPE s = SRC;\
	memcpy(*(PTR_PTR) + USED(*(PTR_PTR)), &s, sizeof(TYPE));\
	USED(*(PTR_PTR))++;\
})

void *allocate_array_stride(Arena *arena, u64 stride, u64 count);

typedef struct{
	u64 total;
}Buffer;

#define allocate_buffer( ARENA , TYPE , COUNT ) (TYPE*)allocate_buffer_stride((ARENA), sizeof(TYPE), (COUNT))
#define inherit_buffer( ARENA , TYPE ) (TYPE*)allocate_buffer_stride((ARENA), sizeof(TYPE), ((ARENA)->size - sizeof(Buffer)) / sizeof(TYPE))

void *allocate_buffer_stride(Arena *arena, u64 stride, u64 count);

typedef struct{
	u64 a,b;
	u64 mask;
	u64 used;
	u64 total;
}RingBuffer;

#define allocate_ring_buffer( ARENA, TYPE, COUNT ) (TYPE*)allocate_ring_buffer_stride(ARENA, sizeof(TYPE), COUNT)

#define ring_buffer_push( VARIABLE , VAL )\
({\
	RingBuffer *ring_buffer = ((RingBuffer*)(VARIABLE))-1;\
	if(ring_buffer->used == ring_buffer->total)\
	{\
		print("ERROR: Ring buffer overflow\n");\
		ring_buffer->used = 0;\
	}\
	(VARIABLE)[ring_buffer->a] = (VAL);\
	ring_buffer->a++;\
	ring_buffer->a &= ring_buffer->mask;\
	ring_buffer->used++;\
	VARIABLE;\
})

#define ring_buffer_pop( VARIABLE, VAL_PTR )\
({\
	b32 ret = false;\
	RingBuffer *ring_buffer = (RingBuffer*)(VARIABLE)-1;\
	if((ring_buffer->used != 0))\
	{\
		*(VAL_PTR) = (VARIABLE)[ring_buffer->b];\
		ring_buffer->b++;\
		ring_buffer->b &= ring_buffer->mask;\
		ring_buffer->used--;\
		ret = true;\
	}\
	ret;\
})

void *allocate_ring_buffer_stride(Arena *arena, u64 stride, u64 count);


















