

String8 str8_alloc(u64 size)
{
	String8 str = {
		.size = size,
		.data = malloc(size),
	};
	return str;
}
