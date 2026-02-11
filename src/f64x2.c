
f64x2 f64x2_set1(f64 a)
{
	f64x2 v;
#ifdef F64X2_SSE
	v.v = _mm_set1_pd(a);	
#else
	v = (f64x2){.a = a, .b = a};
#endif
	return v;
}

f64x2 f64x2_set(f64 a, f64 b)
{
	f64x2 v;
#ifdef F64X2_SSE
	v.v = _mm_set_pd(b,a);	
#else
	v = (f64x2){.a = a, .b = b};
#endif
	return v;
}

f64x2 f64x2_load(const f64 *src)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_load_pd(src);
#else
	memcpy(&dst, src, sizeof(f64) * 2);
#endif
	return dst;
}

void f64x2_scatter(f64 *a, f64 *b, f64x2 v)
{
	*a = v.x;
	*b = v.y;
}

f64x2 f64x2_add(f64x2 v0, f64x2 v1)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_add_pd(v0.v, v1.v);
#else
	dst.a = v0.a + v1.a;
	dst.b = v0.b + v1.b;
#endif
	return dst;
}
f64x2 f64x2_add1(f64x2 v0, f64 s)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_add_pd(v0.v, f64x2_set1(s).v);
#else
	dst.a = v0.a + s;
	dst.b = v0.b + s;
#endif
	return dst;
}

f64x2 f64x2_sub(f64x2 v0, f64x2 v1)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_sub_pd(v0.v, v1.v);
#else
	dst.a = v0.a - v1.a;
	dst.b = v0.b - v1.b;
#endif
	return dst;
}
f64x2 f64x2_sub1(f64x2 v0, f64 s)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_sub_pd(v0.v, f64x2_set1(s).v);
#else
	dst.a = v0.a - s;
	dst.b = v0.b - s;
#endif
	return dst;
}

f64x2 f64x2_1sub(f64 s, f64x2 v0)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_sub_pd(f64x2_set1(s).v, v0.v);
#else
	dst.a = s - v0.a;
	dst.b = s - v0.b;
#endif
	return dst;
}

f64x2 f64x2_mul(f64x2 v0, f64x2 v1)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_mul_pd(v0.v, v1.v);
#else
	dst.a = v0.a * v1.a;
	dst.b = v0.b * v1.b;
#endif
	return dst;
}
f64x2 f64x2_mul1(f64x2 v0, f64 s)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_mul_pd(v0.v, f64x2_set1(s).v);
#else
	dst.a = v0.a * s;
	dst.b = v0.b * s;
#endif
	return dst;
}

f64x2 f64x2_div(f64x2 v0, f64x2 v1)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_div_pd(v0.v, v1.v);
#else
	dst.a = v0.a / v1.a;
	dst.b = v0.b / v1.b;
#endif
	return dst;
}

f64x2 f64x2_div1(f64x2 v0, f64 s)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_div_pd(v0.v, f64x2_set1(s).v);
#else
	dst.a = v0.a / s;
	dst.b = v0.b / s;
#endif
	return dst;
}
f64x2 f64x2_1div(f64 s, f64x2 v0)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_div_pd(f64x2_set1(s).v, v0.v);
#else
	dst.a = s / v0.a;
	dst.b = s / v0.b;
#endif
	return dst;
}

f64x2 f64x2_sqrt(f64x2 v)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_sqrt_pd(v.v);
#else
	dst.a = sqrtf(v.a);
	dst.b = sqrtf(v.b);
#endif
	return dst;
}

f64x2 f64x2_rsqrt(f64x2 v)
{
	f64x2 dst;
#ifdef F64X2_SSE
	dst.v = _mm_div_pd(_mm_set1_pd(1.0), _mm_sqrt_pd(v.v));
#else
	// TCC does not acceup rsqrtf
	dst.a = 1.0 / sqrt(v.a);
	dst.b = 1.0 / sqrt(v.b);
#endif
	return dst;
}

f64x2 f64x2_abs(f64x2 v)
{
	f64x2 dst;
// No SSE version
	dst.a = fabs(v.a);
	dst.b = fabs(v.b);
	return dst;
}

f64 f64x2_length_squared(f64x2 v)
{
#ifdef F64X2_SSE
	v.v = _mm_mul_pd(v.v,v.v);
	f64 dst = v.a + v.b;
#else
	f64 dst = v.x * v.x + v.y * v.y;
#endif
	return dst;
}

f64 f64x2_length(f64x2 v)
{
#ifdef F64X2_SSE
	v.v = _mm_mul_pd(v.v,v.v);
	f64 dst = sqrt(v.a + v.b);
#else
	f64 dst = sqrt(f64x2_length_squared(v));		
#endif
	return dst;
}

f64x2 f64x2_unit(f64x2 v)
{
	f64x2 norm = f64x2_set1(f64x2_length(v));
	f64x2 dst = f64x2_div(v,norm);
	return dst;
}

f64 f64x2_distance(f64x2 v0, f64x2 v1)
{
	f64x2 dif = f64x2_sub(v1,v0);
	f64 dst = f64x2_length(dif);
	return dst;
}

f64 f64_lerp(f64 a, f64 b, f64 t)
{
	return (b-a)*t+a;
}

f64x2 f64x2_lerp(f64x2 v0, f64x2 v1, f64 t)
{
	f64x2 dst;	
#ifdef F64X2_SSE
	v1 = f64x2_sub(v1,v0);
	v1 = f64x2_mul1(v1,t);
	dst = f64x2_add(v0, v1);
#else
	dst.a = f64_lerp(v0.a, v1.a, t);
	dst.b = f64_lerp(v0.b, v1.b, t);
#endif
	return dst;
}

f64 f64x2_angle(f64x2 v)
{
	f64 dst = atan2(v.y, v.x);
	return dst;
}

f64x2 f64x2_trunc(f64x2 v, f64 max_mag)
{
	f64 mag_sq = f64x2_length_squared(v);	
	if(mag_sq <= max_mag*max_mag)
		return v;
	f64 mag = sqrtf(mag_sq);
	f64 scale = max_mag / mag;
	f64x2 dst = f64x2_mul1(v, scale);
	return dst;
}

f64 f64x2_dot(f64x2 v0, f64x2 v1)
{
#ifdef F64X2_SSE
	v0 = f64x2_mul(v0,v1);
	f64 dst = v0.x + v0.y;
#else
	f64 dst = v0.x * v1.x + v0.y * v1.y;
#endif
	return dst;
}

f64 f64x2_cross(f64x2 v0, f64x2 v1)
{
	f64 dst = v0.x * v1.y - v0.y * v1.x;
	return dst;
}

f64x2 f64x2_perp_cw(f64x2 v)
{
	f64x2 dst;
	dst.x = -v.y;
	dst.y = v.x;
	return dst;
}
f64x2 f64x2_perp_ccw(f64x2 v)
{
	f64x2 dst;
	dst.x = v.y;
	dst.y = -v.x;
	return dst;
}

f64x2 f64x2_unit_perp(f64x2 v) // CCW convention
{
	f64x2 dst;
	dst = f64x2_unit(v);
	dst = f64x2_perp_ccw(dst);
	return dst;
}

f64x2 f64x2_reflect(f64x2 incident, f64x2 normal)
{
	printf("TODO: Test f64x2_reflect for correctness\n");
#ifdef F64X2_SSE
	f64x2 dot2 = f64x2_set1(f64x2_dot(incident, normal) * 2);
	f64x2 dst = f64x2_sub(
			incident, 
			f64x2_mul(dot2, normal)
		);
#else
	f64 dot = f64x2_dot(incident, normal);
	f64x2 dst;			
	dst.x = incident.x - 2.0f * dot * normal.x;
	dst.y = incident.y - 2.0f * dot * normal.y;
#endif
	return dst;
}





