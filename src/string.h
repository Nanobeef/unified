
typedef struct String8{
	u64 size;	
	u8 *data;
}String8;

#define str8_lit( STR ) ((String8){.size = sizeof(STR)-1, .data = (u8*)(STR)})

String8 str8_alloc(u64 size);
