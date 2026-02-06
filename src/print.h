


typedef struct{
			
}Print;

u64 memprint(u64 size, u8* buffer, const char *format, ...);
u64 vmemprint(u64 size, u8* buffer, const char *format, va_list l); 

String8 str8_print(Arena *arena, const char *format, ...);
String8 str8_vprint(Arena *arena, const char *format, va_list l); 

u64 print(const char *format, ...);
u64 vprint(const char *format, va_list l);
