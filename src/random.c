


// Random Numbers:
// As measured on a Zen4 CPU, romu_quad is about 4x faster than splitmix when using scalars.


// Fast Splittable Pseudorandom Number Generators (Steele, Lea, Flood)
u64 splitmix(u64 s)
{
    u64 x = s + 0x9e3779b97f4a7c15lu;
    x ^= x >> 30;
    x *= 0xbf58476d1ce4e5b9lu;
    x ^= x >> 27;
    x *= 0x94d049bb133111eblu;
    x ^= x >> 31;
    return x;
}

RomuQuad romu_quad_seed(u64 seed)
{
	RomuQuad rq = {0};
	for(u32 i = 0; i < 4; i++)
		for(u32 j = 0; j < 4; j++)
			rq.state[i] = seed = splitmix(seed);
	return rq;
}


// https://www.romu-random.org
#define ROMU_ROTL(d, l) ((d<<(l)) |  (d>>(8*sizeof(d)-(l))))
u64 romu_quad(RomuQuad *rq)
{
	u64 *s = rq->state;
	u64 w = s[0];
	u64 x = s[1];
	u64 y = s[2];
	u64 z = s[3];
	s[0] = 15241094284759029579lu * z;
	s[1] = z + ROMU_ROTL(w, 52);
	s[2] = y - x;
	s[3] = y + w;
	s[3] = ROMU_ROTL(s[3], 19);
	return x;
}

f32 romu_quad_f32(RomuQuad *rq)
{
	u64 v = romu_quad(rq);
	u32 u = 0x40000000 | (v & (0x7FFFFF));
	f32 f;
	memcpy(&f,&u, 4);
	f = f - 3.0f;
	return f;
}

f64 romu_quad_f64(RomuQuad *rq)
{
	u64 v = romu_quad(rq);
	u64 u = 0x4000000000000000 | (v & (0xFFFFFFFFFFFFF));
	f64 f;
	memcpy(&f,&u, 8);
	f = f - 3.0;
	return f;
}

f32x2 romu_quad_f32x2(RomuQuad *rq)
{
	u64 v = romu_quad(rq);
	u64 u = 0x4000000040000000 | (v & (0x007FFFFF007FFFFF));
	f32x2 f;
	memcpy(&f,&u, 8);
	f = f32x2_sub(f, f32x2_set1(3.0f));
	return f;
}


f32 romu_quad_positive_f32(RomuQuad *rq)
{
	u64 v = romu_quad(rq);
	u32 u = 0x3F800000 | (v & (0x7FFFFF));
	f32 f;
	memcpy(&f,&u, 4);
	f = f - 1.0f;
	return f;
}
f64 romu_quad_positive_f64(RomuQuad *rq)
{
	u64 v = romu_quad(rq);
	u64 u = 0x3FF0000000000000 | (v & (0xFFFFFFFFFFFFF));
	f64 f;
	memcpy(&f,&u, 8);
	f = f - 1.0;
	return f;
}
f32x2 romu_quad_positive_f32x2(RomuQuad *rq)
{
	u64 v = romu_quad(rq);
	u64 u = 0x3F8000003F800000 | (v & (0x007FFFFF007FFFFF));
	f32x2 f;
	memcpy(&f,&u, 8);
	f = f32x2_sub(f, f32x2_set1(1.0f));
	return f;
}

f32x4 romu_quad_color(RomuQuad *rq)
{
	f32x4 ret;
	f32x2 a[2] = {romu_quad_positive_f32x2(rq),romu_quad_positive_f32x2(rq)};
	memcpy(&ret, a, 16);
	return ret;
}

f32x4 romu_quad_solid_color(RomuQuad *rq)
{
	f32x4 c = romu_quad_color(rq);
	c.a = 1.0;
	return c;
}
