

f32x2 f32x2_set1(f32 a)
{
	f32x2 v = {.a = a, .b = a};
	return v;
}

f32x2 f32x2_set(f32 a, f32 b)
{
	f32x2 v = {.a = a, .b = b};
	return v;
}

f32x2 f32x2_load(const f32 *src)
{
	f32x2 dst;
	memcpy(&dst, src, sizeof(f32) * 2);
	return dst;
}

void f32x2_scatter(f32 *a, f32 *b, f32x2 v)
{
	*a = v.x;
	*b = v.y;
}

f32x2 f32x2_add(f32x2 v0, f32x2 v1)
{
	f32x2 dst;
	dst.a = v0.a + v1.a;
	dst.b = v0.b + v1.b;
	return dst;
}
f32x2 f32x2_add1(f32x2 v0, f32 s)
{
	f32x2 dst;
	dst.a = v0.a + s;
	dst.b = v0.b + s;
	return dst;
}

f32x2 f32x2_sub(f32x2 v0, f32x2 v1)
{
	f32x2 dst;
	dst.a = v0.a - v1.a;
	dst.b = v0.b - v1.b;
	return dst;
}
f32x2 f32x2_sub1(f32x2 v0, f32 s)
{
	f32x2 dst;
	dst.a = v0.a - s;
	dst.b = v0.b - s;
	return dst;
}

f32x2 f32x2_1sub(f32 s, f32x2 v0)
{
	f32x2 dst;
	dst.a = s - v0.a;
	dst.b = s - v0.b;
	return dst;
}

f32x2 f32x2_mul(f32x2 v0, f32x2 v1)
{
	f32x2 dst;
	dst.a = v0.a * v1.a;
	dst.b = v0.b * v1.b;
	return dst;
}
f32x2 f32x2_mul1(f32x2 v0, f32 s)
{
	f32x2 dst;
	dst.a = v0.a * s;
	dst.b = v0.b * s;
	return dst;
}

f32x2 f32x2_div(f32x2 v0, f32x2 v1)
{
	f32x2 dst;
	dst.a = v0.a / v1.a;
	dst.b = v0.b / v1.b;
	return dst;
}

f32x2 f32x2_div1(f32x2 v0, f32 s)
{
	f32x2 dst;
	dst.a = v0.a / s;
	dst.b = v0.b / s;
	return dst;
}
f32x2 f32x2_1div(f32 s, f32x2 v0)
{
	f32x2 dst;
	dst.a = s / v0.a;
	dst.b = s / v0.b;
	return dst;
}

f32x2 f32x2_sqrt(f32x2 v)
{
	f32x2 dst;
	dst.a = sqrtf(v.a);
	dst.b = sqrtf(v.b);
	return dst;
}

f32x2 f32x2_rsqrt(f32x2 v)
{
	f32x2 dst;
	dst.a = 1.0f / sqrtf(v.a);
	dst.b = 1.0f / sqrtf(v.b);
	return dst;
}

f32x2 f32x2_abs(f32x2 v)
{
	f32x2 dst;
	dst.a = fabsf(v.a);
	dst.b = fabsf(v.b);
	return dst;
}

f32 f32x2_length_squared(f32x2 v)
{
	f32 dst = v.x * v.x + v.y * v.y;
	return dst;
}

f32 f32x2_length(f32x2 v)
{
	f32 dst = sqrtf(f32x2_length_squared(v));		
	return dst;
}

f32x2 f32x2_unit(f32x2 v)
{
	f32x2 norm = f32x2_set1(f32x2_length(v));
	f32x2 dst = f32x2_div(v,norm);
	return dst;
}

f32 f32x2_distance(f32x2 v0, f32x2 v1)
{
	f32x2 dif = f32x2_sub(v1,v0);
	f32 dst = f32x2_length(dif);
	return dst;
}

f32 f32_lerp(f32 a, f32 b, f32 t)
{
	return (b-a)*t+a;
}

f32x2 f32x2_lerp(f32x2 v0, f32x2 v1, f32 t)
{
	f32x2 dst;	
	dst.a = f32_lerp(v0.a, v1.a, t);
	dst.b = f32_lerp(v0.b, v1.b, t);
	return dst;
}

f32 f32x2_angle(f32x2 v)
{
	f32 dst = atan2f(v.y, v.x);
	return dst;
}

f32x2 f32x2_trunc(f32x2 v, f32 max_mag)
{
	f32 mag_sq = f32x2_length_squared(v);	
	if(mag_sq <= max_mag*max_mag)
		return v;
	f32 mag = sqrtf(mag_sq);
	f32 scale = max_mag / mag;
	f32x2 dst = f32x2_mul1(v, scale);
	return dst;
}

f32 f32x2_dot(f32x2 v0, f32x2 v1)
{
	f32 dst = v0.x * v1.x + v0.y * v1.y;
	return dst;
}

f32 f32x2_cross(f32x2 v0, f32x2 v1)
{
	f32 dst = v0.x * v1.y - v0.y * v1.x;
	return dst;
}

f32x2 f32x2_perp_cw(f32x2 v)
{
	f32x2 dst;
	dst.x = -v.y;
	dst.y = v.x;
	return dst;
}
f32x2 f32x2_perp_ccw(f32x2 v)
{
	f32x2 dst;
	dst.x = v.y;
	dst.y = -v.x;
	return dst;
}

f32x2 f32x2_unit_perp(f32x2 v) // CCW convention
{
	f32x2 dst;
	dst = f32x2_unit(v);
	dst = f32x2_perp_ccw(dst);
	return dst;
}

f32x2 f32x2_reflect(f32x2 incident, f32x2 normal)
{
	f32 dot = f32x2_dot(incident, normal);
	f32x2 dst;			
	dst.x = incident.x - 2.0f * dot * normal.x;
	dst.y = incident.y - 2.0f * dot * normal.y;
	return dst;
}





