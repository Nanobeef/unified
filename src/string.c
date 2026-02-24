

String8 str8_alloc(Arena *arena, u64 len)
{
	String8 str = {
		.len = len,
		.data = arena_push(arena, 0, len),
	};
	return str;
}

String8 str8_cstr(Arena *arena, const char *src)
{
	const char *p = src;
	for(p = src; *p; p++);
	u64 len = (p - src);
	String8 str = str8_alloc(arena, len);
	memcpy(str.data, src, str.len);
	return str;
}

char *cstr_str8(Arena *arena, String8 str)
{
	char *cstr = arena_push(arena, 0, str.len+1);
	memcpy(cstr, str.data, str.len);
	cstr[str.len] = 0;
	return cstr;
}

String8 str8_concatenate(Arena *arena, u32 count, const String8 *strings)
{
	u64 total_len = 1;
	for(u32 i = 0; i < count; i++)
	{
		total_len += strings[i].len;
	}
	String8 cat = str8_alloc(arena, total_len);
	u64 pos = 0;
	for(u32 i = 0; i < count; i++)
	{
		u64 len = strings[i].len;
		memcpy(cat.data + pos, strings[i].data, len);
		pos += len;
	}
	cat.data[pos] = 0;
	return cat;
}

String8 str8_concatenate_and_seperate(Arena *arena, u32 count, const String8 *strings, String8 seperator)
{
	u64 total_len = 1;
	for(u32 i = 0; i < count; i++)
	{
		total_len += strings[i].len;
		total_len += seperator.len;
	}
	total_len-=seperator.len;
	String8 cat = str8_alloc(arena, total_len);
	u64 pos = 0;
	for(u32 i = 0; i < count; i++)
	{
		{
			u64 len = strings[i].len;
			memcpy(cat.data + pos, strings[i].data, len);
			pos += len;
		}
		if(i != count-1){
			u64 len = seperator.len;
			memcpy(cat.data + pos, seperator.data, len);
			pos += len;
		}

	}
	cat.data[pos] = 0;
	return cat;
}

String8 str8_concatenate_and_decorate(Arena *arena, u32 count, const String8 *strings, String8 seperator, String8 prefix, String8 postfix)
{
	u64 total_len = 1;
	total_len += prefix.len;
	total_len += postfix.len;
	for(u32 i = 0; i < count; i++)
	{
		total_len += strings[i].len;
		total_len += seperator.len;
	}

	total_len-=seperator.len;
	String8 cat = str8_alloc(arena, total_len);
	u64 pos = 0;

	{
		u64 len = prefix.len;
		memcpy(cat.data + pos, prefix.data, len);
		pos += len;
	}

	for(u32 i = 0; i < count; i++)
	{
		{
			u64 len = strings[i].len;
			memcpy(cat.data + pos, strings[i].data, len);
			pos += len;
		}
		if(i != count-1){
			u64 len = seperator.len;
			memcpy(cat.data + pos, seperator.data, len);
			pos += len;
		}

	}
	{
		u64 len = postfix.len;
		memcpy(cat.data + pos, postfix.data, len);
		pos += len;
	}
	cat.data[pos] = 0;
	return cat;
}

b32 str8_equal(String8 a, String8 b)
{
	if(a.len != b.len)
		return false;
	for(u32 i = 0; i < a.len; i++)
		if(a.data[i] != b.data[i])
			return false;
	return true;
}

b32 str8_file_type_equal(String8 file, String8 type)
{
	for(u32 i = file.len; i; i--)
	{
		if(file.data[i] == '.')
		{
			u32 file_type_len = file.len - i - 1;
			const u8 *ft = file.data + i + 1;
			u32 type_len = type.len;
			const u8 *t = type.data;
			if(type.data[0] == '.')
			{
				type_len--;
				t++;
			}
			if(type_len != file_type_len)
				return false;
			for(u32 j = 0; j < type_len; j++)
			{
				if(ft[j] != t[j])
				{
					return false;
				}
			}
			return true;
		}
	}
	return false;
}
String8 str8_file_type(Arena* arena, String8 file)
{
	return (String8){0};
}















