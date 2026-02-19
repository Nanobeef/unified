
s32x2 s32x2_set1(s32 a)
{
	s32x2 v = {.a = a, .b = a};
	return v;
}

s32x2 s32x2_set(s32 a, s32 b)
{
	s32x2 v = {.a = a, .b = b};
	return v;
}

s32x2 s32x2_load(const s32 *src)
{
	s32x2 dst;
	memcpy(&dst, src, sizeof(s32) * 2);
	return dst;
}

void s32x2_scatter(s32 *a, s32 *b, s32x2 v)
{
	*a = v.x;
	*b = v.y;
}

s32x2 s32x2_add(s32x2 v0, s32x2 v1)
{
	s32x2 dst;
	dst.a = v0.a + v1.a;
	dst.b = v0.b + v1.b;
	return dst;
}
s32x2 s32x2_add1(s32x2 v0, s32 s)
{
	s32x2 dst;
	dst.a = v0.a + s;
	dst.b = v0.b + s;
	return dst;
}

s32x2 s32x2_sub(s32x2 v0, s32x2 v1)
{
	s32x2 dst;
	dst.a = v0.a - v1.a;
	dst.b = v0.b - v1.b;
	return dst;
}
s32x2 s32x2_sub1(s32x2 v0, s32 s)
{
	s32x2 dst;
	dst.a = v0.a - s;
	dst.b = v0.b - s;
	return dst;
}

s32x2 s32x2_1sub(s32 s, s32x2 v0)
{
	s32x2 dst;
	dst.a = s - v0.a;
	dst.b = s - v0.b;
	return dst;
}

s32x2 s32x2_mul(s32x2 v0, s32x2 v1)
{
	s32x2 dst;
	dst.a = v0.a * v1.a;
	dst.b = v0.b * v1.b;
	return dst;
}
s32x2 s32x2_mul1(s32x2 v0, s32 s)
{
	s32x2 dst;
	dst.a = v0.a * s;
	dst.b = v0.b * s;
	return dst;
}

s32x2 s32x2_div(s32x2 v0, s32x2 v1)
{
	s32x2 dst;
	dst.a = v0.a / v1.a;
	dst.b = v0.b / v1.b;
	return dst;
}

s32x2 s32x2_div1(s32x2 v0, s32 s)
{
	s32x2 dst;
	dst.a = v0.a / s;
	dst.b = v0.b / s;
	return dst;
}
s32x2 s32x2_1div(s32 s, s32x2 v0)
{
	s32x2 dst;
	dst.a = s / v0.a;
	dst.b = s / v0.b;
	return dst;
}

s32x2 s32x2_abs(s32x2 v)
{
	s32x2 dst;
	dst.a = fabsf(v.a);
	dst.b = fabsf(v.b);
	return dst;
}

s32 s32x2_dot(s32x2 v0, s32x2 v1)
{
	s32 dst = v0.x * v1.x + v0.y * v1.y;
	return dst;
}

s32 s32x2_cross(s32x2 v0, s32x2 v1)
{
	s32 dst = v0.x * v1.y - v0.y * v1.x;
	return dst;
}

s32x2 s32x2_perp_cw(s32x2 v)
{
	s32x2 dst;
	dst.x = -v.y;
	dst.y = v.x;
	return dst;
}
s32x2 s32x2_perp_ccw(s32x2 v)
{
	s32x2 dst;
	dst.x = v.y;
	dst.y = -v.x;
	return dst;
}





