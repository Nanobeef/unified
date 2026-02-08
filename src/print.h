


typedef struct{
	u32 sig_figs;	
}Print;

String8 str8_print(Arena *arena, const char *format, ...);
String8 str8_vprint(Arena *arena, const char *format, va_list l); 

u64 print(const char *format, ...);
u64 vprint(Arena *arena, const char *format, va_list l);

u64 vmemprint(Arena *conflict, u64 size, u8* buffer, const char *format, va_list l);
u64 memprint(Arena *conflict, u64 size, u8* buffer, const char *format, ...);
