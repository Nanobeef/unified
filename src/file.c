

u8* read_file(Arena *arena, String8 name)
{
	Scratch scratch = find_scratch(0,1,&arena);
	s32 fd = open(cstr_str8(scratch.arena, name), O_RDONLY);
	if(fd == -1)
	{
		print("Failed to open shader: %s\n", name);
		return 0;
	}
	struct stat st;
	if(fstat(fd, &st) == -1)
	{
		print("Failed to get shader size: %s\n", name);
		return 0;
	}

	u64 size = st.st_size;
	u8* data = allocate_array(arena, u8, size);

	
	u64 read_size = read(fd, data, size);
	USED(data) = read_size;
	if(read_size != size)
	{
		print("Unable to read data\n");
	}
	return data;
}

String8* enumerate_src(Arena *arena)
{
	DIR *dir = opendir("src/");
	if(dir == NULL)
	{
		printf("Failed to open \"src/\"\n");
	}

	Scratch scratch = find_scratch(0,0,0);
	struct dirent* entry = NULL;
	while((entry = readdir(dir)) != NULL)
	{
		String8 str = str8_cstr(scratch.arena, entry->d_name);
		if(
			!str8_equal(str, str8_lit(".")) && 
			!str8_equal(str, str8_lit(".."))
		)
		{
			if(str8_file_type_equal(str, str8_lit(".h")))
			{
				printf("%s\n", str.data);
			}
			else if(str8_file_type_equal(str, str8_lit(".c")))
			{
				printf("  %s\n", str.data);
			}
			else
			{
				printf("              %s\n", str.data);
			}
		}
	}
	regress_scratch(scratch);
	closedir(dir);
	return 0;	
}
