

inline Vec2f32 Vec2f32_set1(f32 a)
{
	Vec2f32 v = {.a = a, .b = a};
	return v;
}

inline Vec2f32 Vec2f32_set(f32 a, f32 b)
{
	Vec2f32 v = {.a = a, .b = b};
	return v;
}

inline Vec2f32 Vec2f32_load(const f32 *src)
{
	Vec2f32 dst;
	memcpy(&dst, src, sizeof(f32) * 2);
	return dst;
}

inline void Vec2f32_scatter(f32 *a, f32 *b, Vec2f32 v)
{
	*a = v.x;
	*b = v.y;
}

inline Vec2f32 Vec2f32_add(Vec2f32 v0, Vec2f32 v1)
{
	Vec2f32 dst;
	dst.a = v0.a + v1.a;
	dst.b = v0.b + v1.b;
	return dst;
}
inline Vec2f32 Vec2f32_add1(Vec2f32 v0, f32 s)
{
	Vec2f32 dst;
	dst.a = v0.a + s;
	dst.b = v0.b + s;
	return dst;
}

inline Vec2f32 Vec2f32_sub(Vec2f32 v0, Vec2f32 v1)
{
	Vec2f32 dst;
	dst.a = v0.a - v1.a;
	dst.b = v0.b - v1.b;
	return dst;
}
inline Vec2f32 Vec2f32_sub1(Vec2f32 v0, f32 s)
{
	Vec2f32 dst;
	dst.a = v0.a - s;
	dst.b = v0.b - s;
	return dst;
}

inline Vec2f32 Vec2f32_1sub(f32 s, Vec2f32 v0)
{
	Vec2f32 dst;
	dst.a = s - v0.a;
	dst.b = s - v0.b;
	return dst;
}

inline Vec2f32 Vec2f32_mul(Vec2f32 v0, Vec2f32 v1)
{
	Vec2f32 dst;
	dst.a = v0.a * v1.a;
	dst.b = v0.b * v1.b;
	return dst;
}
inline Vec2f32 Vec2f32_mul1(Vec2f32 v0, f32 s)
{
	Vec2f32 dst;
	dst.a = v0.a * s;
	dst.b = v0.b * s;
	return dst;
}

inline Vec2f32 Vec2f32_div(Vec2f32 v0, Vec2f32 v1)
{
	Vec2f32 dst;
	dst.a = v0.a / v1.a;
	dst.b = v0.b / v1.b;
	return dst;
}

inline Vec2f32 Vec2f32_div1(Vec2f32 v0, f32 s)
{
	Vec2f32 dst;
	dst.a = v0.a / s;
	dst.b = v0.b / s;
	return dst;
}
inline Vec2f32 Vec2f32_1div(f32 s, Vec2f32 v0)
{
	Vec2f32 dst;
	dst.a = s / v0.a;
	dst.b = s / v0.b;
	return dst;
}

inline Vec2f32 Vec2f32_sqrt(Vec2f32 v)
{
	Vec2f32 dst;
	dst.a = sqrtf(v.a);
	dst.b = sqrtf(v.b);
	return dst;
}

inline Vec2f32 Vec2f32_rsqrt(Vec2f32 v)
{
	Vec2f32 dst;
	dst.a = 1.0f / sqrtf(v.a);
	dst.b = 1.0f / sqrtf(v.b);
	return dst;
}

inline Vec2f32 Vec2f32_abs(Vec2f32 v)
{
	Vec2f32 dst;
	dst.a = fabs(v.a);
	dst.b = fabs(v.b);
	return dst;
}

inline f32 Vec2f32_length_squared(Vec2f32 v)
{
	f32 dst = v.x * v.x + v.y * v.y;
	return dst;
}

inline f32 Vec2f32_length(Vec2f32 v)
{
	f32 dst = sqrtf(Vec2f32_length_squared(v));		
	return dst;
}

inline Vec2f32 Vec2f32_unit(Vec2f32 v)
{
	Vec2f32 norm = Vec2f32_set1(Vec2f32_length(v));
	Vec2f32 dst = Vec2f32_div(v,norm);
	return dst;
}

inline f32 Vec2f32_distance(Vec2f32 v0, Vec2f32 v1)
{
	Vec2f32 dif = Vec2f32_sub(v1,v0);
	f32 dst = Vec2f32_length(dif);
	return dst;
}

inline f32 f32_lerp(f32 a, f32 b, f32 t)
{
	return (b-a)*t+a;
}

inline Vec2f32 Vec2f32_lerp(Vec2f32 v0, Vec2f32 v1, f32 t)
{
	Vec2f32 dst;	
	dst.a = f32_lerp(v0.a, v1.a, t);
	dst.b = f32_lerp(v0.b, v1.b, t);
	return dst;
}

inline f32 Vec2f32_angle(Vec2f32 v)
{
	f32 dst = atan2(v.y, v.x);
	return dst;
}

inline Vec2f32 Vec2f32_trunc(Vec2f32 v, f32 max_mag)
{
	f32 mag_sq = Vec2f32_length_squared(v);	
	if(mag_sq <= max_mag*max_mag)
		return v;
	f32 mag = sqrtf(mag_sq);
	f32 scale = max_mag / mag;
	Vec2f32 dst = Vec2f32_mul1(v, scale);
	return dst;
}

inline f32 Vec2f32_dot(Vec2f32 v0, Vec2f32 v1)
{
	f32 dst = v0.x * v1.x + v0.y * v1.y;
	return dst;
}

inline f32 Vec2f32_cross(Vec2f32 v0, Vec2f32 v1)
{
	f32 dst = v0.x * v1.y - v0.y * v1.x;
	return dst;
}

inline Vec2f32 Vec2f32_perp_cw(Vec2f32 v)
{
	Vec2f32 dst;
	dst.x = -v.y;
	dst.y = v.x;
	return dst;
}
inline Vec2f32 Vec2f32_perp_ccw(Vec2f32 v)
{
	Vec2f32 dst;
	dst.x = v.y;
	dst.y = -v.x;
	return dst;
}

inline Vec2f32 Vec2f32_unit_perp(Vec2f32 v) // CCW convention
{
	Vec2f32 dst;
	dst = Vec2f32_unit(v);
	dst = Vec2f32_perp_ccw(dst);
	return dst;
}

inline Vec2f32 Vec2f32_reflect(Vec2f32 incident, Vec2f32 normal)
{
	f32 dot = Vec2f32_dot(incident, normal);
	Vec2f32 dst;			
	dst.x = incident.x - 2.0f * dot * normal.x;
	dst.y = incident.y - 2.0f * dot * normal.y;
	return dst;
}





