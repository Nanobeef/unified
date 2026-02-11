

#ifndef NO_INTRINSICS



void test_collatz(Arena *arena)
{

	__m512i a = _mm512_set_epi64(1,2,3,4,5,6,7,8);
	__m512i one = _mm512_set1_epi64(1);
	__m512i eight = _mm512_set1_epi64(8);
	__m512i five = _mm512_set1_epi64(5);
	__m512i three = _mm512_set1_epi64(3);

	__m512i start = a;
	
	u64 c = 0;

	__m512i finish = _mm512_set1_epi64(0);

	while(true)
	{
		__m512i and = _mm512_and_epi64(a, one);
		__mmask8 odd_mask = _mm512_cmpeq_epi64_mask(and, one);

		__m512i even_results = _mm512_srli_epi64(a, 1);
		__m512i odd_results = _mm512_mullo_epi64(a, three);
		odd_results = _mm512_add_epi64(odd_results, one);

		a = _mm512_mask_load_epi64(even_results, odd_mask, &odd_results);

		__mmask8 status = _mm512_cmpeq_epi64_mask(a, eight);
		__mmask8 is_finished = _mm512_cmp_epi64_mask(a, five, _MM_CMPINT_LT);
		__m512i count = _mm512_set1_epi64(c);
		_mm512_mask_store_epi64(&finish, status, count);
		if(is_finished == 0xFF)
			break;
		print("%u64: (", c);
		for(u32 i = 0; i < 8; i++)
		{
			print("%u64, ", ((u64*)&a)[i]);
		}
		print("\b\b)\n");
		c++;
	}

	printf("\nDONE:\n");
	print("%u64: (", c);
	for(u32 i = 0; i < 8; i++)
	{
		u64 f = ((u64*)&finish)[i] + 4;
		print("%u64, ", f);
	}
	print("\b\b)\n");
}

void collatz_avx512(u64 start, u64 end)
{
	u64 d = end - start;
	d = ForwardAlign(d, 16);
	end = start + d;

	__m512i one = _mm512_set1_epi32(1);
	__m512i eight = _mm512_set1_epi32(8);
	__m512i five = _mm512_set1_epi32(5);
	__m512i three = _mm512_set1_epi32(3);
	__m512i spread = _mm512_set_epi32(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);

	for(u64 i = start; i < end; i+=16)
	{
		u64 c = 0;
		__m512i finish = _mm512_set1_epi32(0);
		__m512i start = _mm512_set1_epi32(i);
		__m512i a = _mm512_add_epi32(start, spread);
		while(true)
		{
			__m512i and = _mm512_and_epi32(a, one);
			__mmask8 odd_mask = _mm512_cmpeq_epi32_mask(and, one);

			__m512i even_results = _mm512_srli_epi32(a, 1);
			__m512i odd_results = _mm512_mullo_epi32(a, three);
			odd_results = _mm512_add_epi32(odd_results, one);

			a = _mm512_mask_load_epi32(even_results, odd_mask, &odd_results);

			__mmask8 status = _mm512_cmpeq_epi32_mask(a, eight);
			__mmask8 is_finished = _mm512_cmp_epi32_mask(a, five, _MM_CMPINT_LT);
			__m512i count = _mm512_set1_epi32(c);
			_mm512_mask_store_epi32(&finish, status, count);
			if(is_finished == 0xFF)
				break;
			c++;
		}
	}
}


void collatz(u64 start, u64 end)
{
	u64 d = end - start;
	d = ForwardAlign(d, 16);
	end = start + d;
	for(u32 i = start; i < end; i++)
	{
		u64 c = 0;
		u64 x = i;

		while(x!=1)
		{
			if(x & 1)
				x=x*3+1;
			else
				x>>=1;
			c++;
		}
	}
}

void time_collatz(Arena *arena)
{
	u64 time;
	time = get_time_ns();
	u64 start = 8;
	u64 end = MiB(1);
	collatz_avx512(start, end);
	time = get_time_ns() - time;
	print("avx512: %u64 ms\n", time / 1000000);

	time = get_time_ns();
	collatz(start, end);
	time = get_time_ns() - time;
	print("scalar: %u64 ms\n", time / 1000000);
}
#endif
