

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
