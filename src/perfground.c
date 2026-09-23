

s32 compare_s32(const void *a, const void* b)
{
	s32 x = *(s32*)a;
	s32 y = *(s32*)b;
	if(x < y)
		return -1;
	else if(x > y)
		return 1;
	else
		return 0;
}



void perfground()
{
	set_thread_affinity(0,0);
	Scratch scratch = find_scratch(0,0,0);
	u32 c = 1000;
	Chronometer cm = init_chronometer(scratch.arena, c);
	for(u32 j = 0; j < 3; j++)
	{
		if(j & 1)
		{
			arena_push_type(scratch.arena, 0, c, u64, marks);
			chron_begin(&cm);
			u32 i = 0;
			for(i; i < c; i++)
			{
				marks[i] = read_tsc();
			}
			u64 tsc = chron_end(&cm);
			for(i = 0; i < c; i++)
			{
				print("ns = %u64\n", chron_convert_ns(&cm, marks[i]));
				//print("%u64\n", marks[i] - cm.begin);
			}
			print("tsc %u64\n", tsc);
			print("\n");
			sink(i);
		}
		else
		{
			arena_push_type(scratch.arena, 0, c, u64, marks);
			u64 time = get_time_ns();
			u32 i = 0;
			for(i; i < c; i++)
			{
				marks[i] = get_time_ns() - time;	
			}
			time = get_time_ns() - time;
			print("tim %t\n", time);
			for(i = 0; i < c; i++)
			{
			}
			sink(i);
		}
	}
}


