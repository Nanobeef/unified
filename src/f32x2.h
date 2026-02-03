
typedef union f32x2{
	struct{f32 s[2];};
	struct{f32 x,y;};
	struct{f32 a,b;};
}f32x2;

f32x2 f32x2_set1(f32 a);
f32x2 f32x2_set(f32 a, f32 b);
f32x2 f32x2_load(const f32 *src);
void f32x2_scatter(f32 *a, f32 *b, f32x2 v);
f32x2 f32x2_add(f32x2 v0, f32x2 v1);
f32x2 f32x2_add1(f32x2 v0, f32 s);
f32x2 f32x2_sub(f32x2 v0, f32x2 v1);
f32x2 f32x2_sub1(f32x2 v0, f32 s);
f32x2 f32x2_1sub(f32 s, f32x2 v0);
f32x2 f32x2_mul(f32x2 v0, f32x2 v1);
f32x2 f32x2_mul1(f32x2 v0, f32 s);
f32x2 f32x2_div(f32x2 v0, f32x2 v1);
f32x2 f32x2_div1(f32x2 v0, f32 s);
f32x2 f32x2_1div(f32 s, f32x2 v0);
f32x2 f32x2_sqrt(f32x2 v);
f32x2 f32x2_rsqrt(f32x2 v);
f32x2 f32x2_abs(f32x2 v);
f32 f32x2_length_squared(f32x2 v);
f32 f32x2_length(f32x2 v);
f32x2 f32x2_unit(f32x2 v);
f32 f32x2_distance(f32x2 v0, f32x2 v1);
f32 f32_lerp(f32 a, f32 b, f32 t);
f32x2 f32x2_lerp(f32x2 v0, f32x2 v1, f32 t);
f32 f32x2_angle(f32x2 v);
f32x2 f32x2_trunc(f32x2 v, f32 max_mag);
f32 f32x2_dot(f32x2 v0, f32x2 v1);
f32 f32x2_cross(f32x2 v0, f32x2 v1);
f32x2 f32x2_perp_cw(f32x2 v);
f32x2 f32x2_perp_ccw(f32x2 v);
f32x2 f32x2_unit_perp(f32x2 v); // CCW convention
f32x2 f32x2_reflect(f32x2 incident, f32x2 normal);


