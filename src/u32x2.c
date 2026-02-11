

u32x2 u32x2_set1(u32 a)
{
	u32x2 v = {.a = a, .b = a};
	return v;
}

u32x2 u32x2_set(u32 a, u32 b)
{
	u32x2 v = {.a = a, .b = b};
	return v;
}

u32x2 u32x2_load(const u32 *src)
{
	u32x2 dst;
	memcpy(&dst, src, sizeof(u32) * 2);
	return dst;
}

void u32x2_scatter(u32 *a, u32 *b, u32x2 v)
{
	*a = v.x;
	*b = v.y;
}

u32x2 u32x2_add(u32x2 v0, u32x2 v1)
{
	u32x2 dst;
	dst.a = v0.a + v1.a;
	dst.b = v0.b + v1.b;
	return dst;
}
u32x2 u32x2_add1(u32x2 v0, u32 s)
{
	u32x2 dst;
	dst.a = v0.a + s;
	dst.b = v0.b + s;
	return dst;
}

u32x2 u32x2_sub(u32x2 v0, u32x2 v1)
{
	u32x2 dst;
	dst.a = v0.a - v1.a;
	dst.b = v0.b - v1.b;
	return dst;
}
u32x2 u32x2_sub1(u32x2 v0, u32 s)
{
	u32x2 dst;
	dst.a = v0.a - s;
	dst.b = v0.b - s;
	return dst;
}

u32x2 u32x2_1sub(u32 s, u32x2 v0)
{
	u32x2 dst;
	dst.a = s - v0.a;
	dst.b = s - v0.b;
	return dst;
}

u32x2 u32x2_mul(u32x2 v0, u32x2 v1)
{
	u32x2 dst;
	dst.a = v0.a * v1.a;
	dst.b = v0.b * v1.b;
	return dst;
}
u32x2 u32x2_mul1(u32x2 v0, u32 s)
{
	u32x2 dst;
	dst.a = v0.a * s;
	dst.b = v0.b * s;
	return dst;
}

u32x2 u32x2_div(u32x2 v0, u32x2 v1)
{
	u32x2 dst;
	dst.a = v0.a / v1.a;
	dst.b = v0.b / v1.b;
	return dst;
}

u32x2 u32x2_div1(u32x2 v0, u32 s)
{
	u32x2 dst;
	dst.a = v0.a / s;
	dst.b = v0.b / s;
	return dst;
}
u32x2 u32x2_1div(u32 s, u32x2 v0)
{
	u32x2 dst;
	dst.a = s / v0.a;
	dst.b = s / v0.b;
	return dst;
}

u32x2 u32x2_sqrt(u32x2 v)
{
	u32x2 dst;
	dst.a = sqrtf(v.a);
	dst.b = sqrtf(v.b);
	return dst;
}

u32x2 u32x2_rsqrt(u32x2 v)
{
	u32x2 dst;
	dst.a = 1.0f / sqrtf(v.a);
	dst.b = 1.0f / sqrtf(v.b);
	return dst;
}

u32x2 u32x2_abs(u32x2 v)
{
	u32x2 dst;
	dst.a = fabsf(v.a);
	dst.b = fabsf(v.b);
	return dst;
}

u32 u32x2_length_squared(u32x2 v)
{
	u32 dst = v.x * v.x + v.y * v.y;
	return dst;
}

u32 u32x2_length(u32x2 v)
{
	u32 dst = sqrtf(u32x2_length_squared(v));		
	return dst;
}

u32x2 u32x2_unit(u32x2 v)
{
	u32x2 norm = u32x2_set1(u32x2_length(v));
	u32x2 dst = u32x2_div(v,norm);
	return dst;
}

u32 u32x2_distance(u32x2 v0, u32x2 v1)
{
	u32x2 dif = u32x2_sub(v1,v0);
	u32 dst = u32x2_length(dif);
	return dst;
}

