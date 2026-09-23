

u32x16 u32x16_set1(u32 a)
{
	u32x16 v;
	#ifdef U32X16_AVX
		v.v = _mm512_set1_epi32(a);		
	#else 
		for(u32 i = 0; i < 16; i++)
			v.s[i] = a;
	#endif
	return v;
}

u32x16 u32x16_set(u32 r, u32 g, u32 b, u32 a);
u32x16 u32x16_load(const u32 *src);
void u32x16_scatter(u32 *r, u32 *g, u32 *b, u32 *a, u32x16 v);
u32x16 u32x16_add(u32x16 v0, u32x16 v1);
u32x16 u32x16_add1(u32x16 v0, u32 s);
u32x16 u32x16_sub(u32x16 v0, u32x16 v1);
u32x16 u32x16_sub1(u32x16 v0, u32 s);
u32x16 u32x16_1sub(u32 s, u32x16 v0);
u32x16 u32x16_mul(u32x16 v0, u32x16 v1);
u32x16 u32x16_mul1(u32x16 v0, u32 s);
u32x16 u32x16_div(u32x16 v0, u32x16 v1);
u32x16 u32x16_div1(u32x16 v0, u32 s);
u32x16 u32x16_1div(u32 s, u32x16 v0);
