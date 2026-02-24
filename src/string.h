
typedef struct String8{
	u64 len;	
	u8 *data;
}String8;

#define str8_lit( STR ) (String8){.len = sizeof(STR)-1, .data = (u8*)(STR)}

String8 str8_alloc(Arena *arena, u64 len);
String8 str8_cstr(Arena *arena, const char *src);

char *cstr_str8(Arena *arena, String8 str);

// These functions will check the space required before allocating.
String8 str8_concatenate(Arena *arena, u32 count, const String8 *strings);
String8 str8_concatenate_and_seperate(Arena *arena, u32 count, const String8 *strings, String8 seperator);
String8 str8_concatenate_and_decorate(Arena *arena, u32 count, const String8 *strings, String8 seperator, String8 prefix, String8 postfix);

b32 str8_equal(String8 a, String8 b);
b32 str8_file_type_equal(String8 file, String8 type);
String8 str8_file_type(Arena* arena, String8 file);
