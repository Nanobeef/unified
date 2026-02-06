



u64 memprint(u64 size, u8* buffer, const char *format, ...)
{
	va_list l;
	va_start(l, format);
	u64 len = vmemprint(size, buffer, format, l);
	va_end(l);
	return len;
}

u64 vmemprint(u64 size, u8* buffer, const char *format, va_list l)
{
	return true;	
}

String8 str8_print(Arena *arena, const char *format, ...)
{
	va_list l;
	va_start(l, format);
	String8 str = str8_print(arena, format, l);
	va_end(l);
	return str;
}
String8 str8_vprint(Arena *arena, const char *format, va_list l)
{
	u8* data  = (u8*)arena + arena->pos;
	u64 len = vmemprint(arena->size - arena->pos, data, format, l);
	arena->pos += len;
	return (String8){
		.len = len,
		.data = data,
	};
}

// TODO: Print directly to a swap buffer.
u64 print(const char *format, ...)
{
	va_list l;
	va_start(l, format);
	Scratch scratch = find_scratch(0,0,0);
	String8 str = str8_print(scratch.arena, format, l);
	regress_scratch(scratch);
	va_end(l);
	return str.len;
}
u64 vprint(const char *format, va_list l);

