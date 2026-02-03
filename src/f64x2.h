

// X87 uses 80 bit intermediate, SSE does not.
// -mfpmath=sse

typedef union f64x2{
	struct{f64 s[2];};
	struct{f64 x,y;};
	struct{f64 a,b;};
#ifdef SSE_CORE
	struct{__m128d v;};
#endif
}f64x2;

f64x2 f64x2_set1(f64 a);
f64x2 f64x2_set(f64 a, f64 b);
f64x2 f64x2_load(const f64 *src);
void f64x2_scatter(f64 *a, f64 *b, f64x2 v);
f64x2 f64x2_add(f64x2 v0, f64x2 v1);
f64x2 f64x2_add1(f64x2 v0, f64 s);
f64x2 f64x2_sub(f64x2 v0, f64x2 v1);
f64x2 f64x2_sub1(f64x2 v0, f64 s);
f64x2 f64x2_1sub(f64 s, f64x2 v0);
f64x2 f64x2_mul(f64x2 v0, f64x2 v1);
f64x2 f64x2_mul1(f64x2 v0, f64 s);
f64x2 f64x2_div(f64x2 v0, f64x2 v1);
f64x2 f64x2_div1(f64x2 v0, f64 s);
f64x2 f64x2_1div(f64 s, f64x2 v0);
f64x2 f64x2_sqrt(f64x2 v);
f64x2 f64x2_rsqrt(f64x2 v);
f64x2 f64x2_abs(f64x2 v);
f64 f64x2_length_squared(f64x2 v);
f64 f64x2_length(f64x2 v);
f64x2 f64x2_unit(f64x2 v);
f64 f64x2_distance(f64x2 v0, f64x2 v1);
f64 f64_lerp(f64 a, f64 b, f64 t);
f64x2 f64x2_lerp(f64x2 v0, f64x2 v1, f64 t);
f64 f64x2_angle(f64x2 v);
f64x2 f64x2_trunc(f64x2 v, f64 max_mag);
f64 f64x2_dot(f64x2 v0, f64x2 v1);
f64 f64x2_cross(f64x2 v0, f64x2 v1);
f64x2 f64x2_perp_cw(f64x2 v);
f64x2 f64x2_perp_ccw(f64x2 v);
f64x2 f64x2_unit_perp(f64x2 v); // CCW convention
f64x2 f64x2_reflect(f64x2 incident, f64x2 normal);





