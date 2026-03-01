
void print_str8(String8 s)
{
	printf("str8(");
	for(u32 i = 0; i < s.len; i++)
		printf("%c", s.data[i]); 
	printf(")\n");
}

String8 str8_print(Arena *arena, const char *format, ...)
{
	va_list l;
	va_start(l, format);
	String8 str = str8_vprint(arena, format, l);
	va_end(l);
	return str;
}
String8 str8_vprint(Arena *arena, const char *format, va_list l)
{
	u64 size = arena->size - arena->pos;
	u8* data = (u8*)arena + arena->pos;
	u64 len = vmemprint(arena, size, data, format, l);
	arena_push(arena, 0, len);
	return (String8){
		.len = len,
		.data = data,
	};
}

u64 print(const char *format, ...)
{
	va_list l;
	va_start(l, format);
	Scratch scratch = find_scratch(0,0,0);
	u64 len = vprint(scratch.arena, format, l);
	regress_scratch(scratch);
	va_end(l);
	return len;
}
u64 vprint(Arena *arena, const char *format, va_list l)
{
	String8 str = str8_vprint(arena, format, l);
	TerminalColor color = current_thread()->print.terminal_color;
	if(color)
	{
		if(color > TERMINAL_COLOR_MAX)
			color++;

		printf("\033[38;5;%dm", color - 1);
	}
	fwrite((const void*)str.data, 1, str.len, stdout);
	fflush(stdout);
	if(color)
	{
		printf("\033[0m");
	}
	return str.len;
}

u64 memprint(Arena *conflict, u64 size, u8* buffer, const char *format, ...)
{
	va_list l;
	va_start(l, format);
	u64 len = vmemprint(conflict, size, buffer, format, l);
	va_end(l);
	return len;
}

typedef u64 EpochTimeNS;
typedef u64 EpochTimeUS;
typedef u64 EpochTimeMS;
typedef u64 EpochTimeS;
typedef u64 EpochTime;

typedef u64 TimeNS;
typedef u64 TimeUS;
typedef u64 TimeMS;
typedef u64 TimeS;
typedef u64 Time;

typedef enum{
	PRINT_KEYWORD_NONE,
	PRINT_KEYWORD_u8,	
	PRINT_KEYWORD_u16,	
	PRINT_KEYWORD_u32,	
	PRINT_KEYWORD_u64,	
	PRINT_KEYWORD_s8,	
	PRINT_KEYWORD_s16,	
	PRINT_KEYWORD_s32,	
	PRINT_KEYWORD_s64,	
	PRINT_KEYWORD_f32,	
	PRINT_KEYWORD_f64,	

	PRINT_KEYWORD_f32x4,

	PRINT_KEYWORD_u32x2,	
	PRINT_KEYWORD_s32x2,	
	PRINT_KEYWORD_f32x2,	

	PRINT_KEYWORD_String8,
	PRINT_KEYWORD_Cstring,


	PRINT_KEYWORD_Time,
	PRINT_KEYWORD_TimeNS,
	PRINT_KEYWORD_TimeUS,
	PRINT_KEYWORD_TimeS,
	PRINT_KEYWORD_TimeMS,

	PRINT_KEYWORD_EpochTime,
	PRINT_KEYWORD_EpochTimeMS,
	PRINT_KEYWORD_EpochTimeNS,
	PRINT_KEYWORD_EpochTimeUS,
	PRINT_KEYWORD_EpochTimeS,

	PRINT_KEYWORD_void_pointer,
}PrintKeywordFlags;
typedef u32 PrintKeywordIndex;

typedef const char* Cstring;
typedef void* void_pointer;

typedef struct{
	String8 string;	
	PrintKeywordIndex index;
}PrintKeyword;


#define p1( A ) {str8_lit(#A), PRINT_KEYWORD_##A}
#define p2( A , B ) {str8_lit(#A), PRINT_KEYWORD_##B}

PrintKeyword keywords[] = {
	p1(u8),
	p1(u16),
	p1(u32),
	p1(u64),
	p1(s8),
	p1(s16),
	p1(s32),
	p1(s64),
	p1(f32),
	p1(f64),
	p1(f32x4),
	p1(u32x2),
	p1(s32x2),
	p1(f32x2),
	p2(s, String8),
	p2(cs, Cstring),

	p2(et, EpochTime),
	p2(ets, EpochTimeS),
	p2(etms, EpochTimeMS),
	p2(etus, EpochTimeUS),
	p2(etns, EpochTimeNS),

	p2(t, Time),
	p2(ts, TimeS),
	p2(tms, TimeMS),
	p2(tus, TimeUS),
	p2(tns, TimeNS),
};
#undef pk

u64 keyword_to_buffer(u64 size, u8* dst, PrintKeywordIndex index, const void *data)
{
	u64 len = 0;
	switch(index)
	{
	case PRINT_KEYWORD_u8:{
		u8 d = *(u8*)data;
		len = snprintf((char*)dst, size, "%u", (u32)d);
	}break;
	case PRINT_KEYWORD_u16:{
		u16 d = *(u16*)data;
		len = snprintf((char*)dst, size, "%u", (u32)d);
	}break;
	case PRINT_KEYWORD_u32:{
		u32 d = *(u32*)data;
		len = snprintf((char*)dst, size, "%u", (u32)d);
	}break;
	case PRINT_KEYWORD_u64:{
		u64 d = *(u64*)data;
		len = snprintf((char*)dst, size, "%lu", (u64)d);
	}break;
	case PRINT_KEYWORD_s8:{
		s8 d = *(s8*)data;
		len = snprintf((char*)dst, size, "%d", (s32)d);
	}break;
	case PRINT_KEYWORD_s16:{
		s16 d = *(s16*)data;
		len = snprintf((char*)dst, size, "%d", (s32)d);
	}break;
	case PRINT_KEYWORD_s32:{
		s32 d = *(s32*)data;
		len = snprintf((char*)dst, size, "%d", (s32)d);
	}break;
	case PRINT_KEYWORD_s64:{
		s64 d = *(s64*)data;
		len = snprintf((char*)dst, size, "%ld", (s64)d);
	}break;
	case PRINT_KEYWORD_f32:{

		f32 d = *(f32*)data;
		len = snprintf((char*)dst, size, "%f", (f64)d);
	}break;
	case PRINT_KEYWORD_f64:{
		f64 d = *(f64*)data;
		len = snprintf((char*)dst, size, "%f", (f64)d);
	}break;
	case PRINT_KEYWORD_u32x2:{
		u32x2 d = *(u32x2*)data;
		len = snprintf((char*)dst, size, "(%u %u)", d.x, d.y);
	}break;
	case PRINT_KEYWORD_s32x2:{
		s32x2 d = *(s32x2*)data;
		len = snprintf((char*)dst, size, "(%d %d)", d.x, d.y);
	}break;
	case PRINT_KEYWORD_f32x2:{
		f32x2 d = *(f32x2*)data;
		len = snprintf((char*)dst, size, "(%f %f)", d.x, d.y);
	}break;
	case PRINT_KEYWORD_f32x4:{
		f32x4 d = *(f32x4*)data;
		len = snprintf((char*)dst, size, "(%f %f %f %f)", d.r, d.g, d.b, d.a);
	}break;
	case PRINT_KEYWORD_String8:{
		String8 d = *(String8*)data;
		u32 i = 0;
		for(; i < Min(d.len, size); i++) 
			dst[i] = d.data[i]; 
		len = i;
	}break;
	case PRINT_KEYWORD_Cstring:{
		const char *d = *(const char **)data;
		u32 i = 0;
		for(; (i < size) && (d[i]); i++)
			dst[i] = d[i];
		len = i;
	}break;
	case PRINT_KEYWORD_EpochTimeNS:{
		u64 d = *(u64*)data;
		len = snprintf((char*)dst, size, "%lu ns", d);
	}break;
	case PRINT_KEYWORD_EpochTimeUS:{
		u64 d = *(u64*)data;
		len = snprintf((char*)dst, size, "%lu us", d);
	}break;
	case PRINT_KEYWORD_EpochTimeMS:{
		u64 d = *(u64*)data;
		len = snprintf((char*)dst, size, "%lu ms", d);
	}break;
	case PRINT_KEYWORD_EpochTimeS:{
		u64 d = *(u64*)data;
		len = snprintf((char*)dst, size, "%lu s", d);
	}break;
	case PRINT_KEYWORD_TimeNS:{
		u64 d = *(u64*)data;
		len = snprintf((char*)dst, size, "%lu ns", d);
	}break;
	case PRINT_KEYWORD_TimeUS:{
		u64 d = *(u64*)data;
		len = snprintf((char*)dst, size, "%lu us", d);
	}break;
	case PRINT_KEYWORD_TimeMS:{
		u64 d = *(u64*)data;
		len = snprintf((char*)dst, size, "%lu ms", d);
	}break;
	case PRINT_KEYWORD_TimeS:{
		u64 d = *(u64*)data;
		len = snprintf((char*)dst, size, "%lu s", d);
	}break;
	case PRINT_KEYWORD_Time:{
		u64 d = *(u64*)data;
		if(d < 1000)
		{
			len = snprintf((char*)dst, size, "%lu ns", (u64)d);
		}
		else if(d < 1000000)
		{
			len = snprintf((char*)dst, size, "%lu us", (u64)d/1000);
		}
		else if(d < 1000000000lu * 10lu)
		{
			len = snprintf((char*)dst, size, "%lu ms", (u64)d/1000000);
		}
		else if(d < 1000000000lu * 600lu)
		{
			len = snprintf((char*)dst, size, "%lu s", (u64)d/1000000000);
		}
		else
		{
			len = snprintf((char*)dst, size, "%lu m", (u64)d/(1000000000lu * 60lu));
		}
	}break;

		default:
		break;
	}
	return len;
}

u64 variadic_scalar_to_buffer(u64 size, u8* dst, PrintKeywordIndex index, va_list l)
{
	u64 len = 0;
	switch(index)
	{
	case PRINT_KEYWORD_u8:{
		u8 d = va_arg(l, u32);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_u16:{
		u16 d = va_arg(l, u32);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_u32:{
		u32 d = va_arg(l, u32);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_u64:{
		u64 d = va_arg(l, u64);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_s8:{
		s8 d = va_arg(l, s32);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_s16:{
		s16 d = va_arg(l, s32);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_s32:{
		s32 d = va_arg(l, s32);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_s64:{
		s64 d = va_arg(l, s64);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_f32:{
		f32 d = (f32)va_arg(l, f64);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_f64:{
		f64 d = va_arg(l, f64);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_u32x2:{
		u32x2 d = va_arg(l, u32x2);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_s32x2:{
		s32x2 d = va_arg(l, s32x2);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_f32x2:{
		f32x2 d = va_arg(l, f32x2);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_f32x4:{
		f32x4 d = va_arg(l, f32x4);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_String8:{
		String8 d = va_arg(l, String8);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_Cstring:{
		const char* d = va_arg(l, const char*);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_EpochTimeNS:{
		u64 t = get_epoch_ns();
		len = keyword_to_buffer(size, dst, index, &t);
	}break;
	case PRINT_KEYWORD_EpochTimeUS:{
		u64 t = get_epoch_us();
		len = keyword_to_buffer(size, dst, index, &t);
	}break;
	case PRINT_KEYWORD_EpochTimeMS:{
		u64 t = get_epoch_ms();
		len = keyword_to_buffer(size, dst, index, &t);
	}break;
	case PRINT_KEYWORD_EpochTimeS:{
		u64 t = get_epoch_s();
		len = keyword_to_buffer(size, dst, index, &t);
	}break;
	case PRINT_KEYWORD_EpochTime:{
		u64 t = get_epoch_ms();
		len = keyword_to_buffer(size, dst, PRINT_KEYWORD_EpochTimeMS, &t);
	}break;
	case PRINT_KEYWORD_TimeNS:{
		u64 d = va_arg(l, u64);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_TimeUS:{
		u64 d = va_arg(l, u64) / 1000;
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_TimeMS:{
		u64 d = va_arg(l, u64) / 1000000;
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_TimeS:{
		u64 d = va_arg(l, u64) / 1000000000;
		len = keyword_to_buffer(size, dst, index, &d);
	}break;
	case PRINT_KEYWORD_Time:{
		u64 d = va_arg(l, u64);
		len = keyword_to_buffer(size, dst, index, &d);
	}break;

		default:
		break;
	}
	return len;
}
	








PrintKeyword search_print_keywords1(String8 s)
{
	const u8* c = s.data+1;	
	PrintKeyword match = {0};
	u64 shortest_match_len = U32_MAX;
	for(u32 i = 0; i < Arrlen(keywords); i++)
	{
		String8 s = keywords[i].string;
		u32 j = 0;

		for(j = 0; j < s.len; j++)
		{
			if(c[j] != s.data[j])
				break;
				
		}
		if(( j != 0) && (j == shortest_match_len))
		{
			if(s.len == shortest_match_len)
			{
				match = keywords[i];
				shortest_match_len = j;
			}
		}
		if(j > match.string.len)
		{
			shortest_match_len = j;
			match = keywords[i];
		}
	}
	return match;
}

PrintKeyword search_print_keywords(String8 s)
{
	const u8* c = s.data+1;	
	PrintKeyword match = {0};
	u64 longest_match = 0;
	for(u32 i = 0; i < Arrlen(keywords); i++)
	{
		String8 s = keywords[i].string;
		u32 j = 0;

		for(j = 0; j < s.len; j++)
		{
			if(c[j] != s.data[j])
				break;
				
		}
		if(j == 0)
			continue;
		if(j > longest_match)
		{
			longest_match = j;
			match = keywords[i];
		}
	}
	return match;
}


typedef enum{
	PRINT_TOKEN_NULL,	
	PRINT_TOKEN_ESCAPE, // %	
	PRINT_TOKEN_RETURN,	// %%
	PRINT_TOKEN_STRING,
}PrintTokenTypeFlags;
typedef u32 PrintTokenType;

typedef struct{
	PrintTokenType type;	
	String8 string;
	PrintKeywordIndex index;
}PrintToken;


u64 vmemprint(Arena *conflict, u64 size, u8* buffer, const char *format, va_list l)
{
	if(format == 0)
		return 0;
	if(buffer == 0)
		return 0;
	if(size == 0)
		return 0;

	Scratch scratch = find_scratch(0, 1, &conflict);

	String8 fmt = str8_cstr(scratch.arena, format);

	PrintToken *tokens = arena_push(scratch.arena, false, fmt.len * sizeof(PrintToken));
	u32 ti = 0;

	const char *f = format;
	char c;
	while((c = (f)[0]))
	{
		if(c == '%')
		{
			tokens[ti++] = (PrintToken){
				.type = PRINT_TOKEN_ESCAPE,
				.string = {
					.data = (u8*)f,
					.len = fmt.len - (u64)(f - format),
				},
			};
		}
		else
		{
			char cc;
			const char *start = f;
			while((cc = (f)[0]))
			{
				if(cc == '%')
					break;
				f++;
			}
			tokens[ti++] = (PrintToken){
				.type = PRINT_TOKEN_STRING,	
				.string = (String8){
					.data = (u8*)start,
					.len = (u64)(f - start),
				},
			};
			f--;
		}
		f++;
	}

	for(u32 i = 0; i < ti; i++)
	{
		if(tokens[i].type == PRINT_TOKEN_ESCAPE)
		{
			PrintKeyword kw = search_print_keywords(tokens[i].string);
			tokens[i].index = kw.index;

			if(i+1 < ti)
			{
				if(tokens[i+1].type == PRINT_TOKEN_STRING)
				{
					u32 len = kw.string.len;
					tokens[i+1].string.data+=len;
					tokens[i+1].string.len-=len;
				}
			}
		}
	}
	u8* b = buffer;
	u64 s = size;
	for(u32 i = 0; i < ti; i++)
	{
		u64 len = 0;
		if(tokens[i].type == PRINT_TOKEN_ESCAPE)
		{
			len = variadic_scalar_to_buffer(s,b, tokens[i].index, l);
		}
		else if(tokens[i].type == PRINT_TOKEN_STRING)
		{
			len = keyword_to_buffer(s,b, PRINT_KEYWORD_String8, &tokens[i].string);
		}
			s -= len;
			b += len;
	}

	u64 evaluated_len = (u64)(b - buffer);

	regress_scratch(scratch);
	return evaluated_len;	
}
