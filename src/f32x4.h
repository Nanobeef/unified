
typedef union f32x4{
	struct{f32 s[4];};
	struct{f32 x,y,z,w;};
	struct{f32 r,g,b,a;};
}f32x4;

f32x4 f32x4_set1(f32 a);
f32x4 f32x4_set(f32 r, f32 g, f32 b, f32 a);
f32x4 f32x4_load(const f32 *src);
void f32x4_scatter(f32 *r, f32 *g, f32 *b, f32 *a, f32x4 v);
f32x4 f32x4_add(f32x4 v0, f32x4 v1);
f32x4 f32x4_add1(f32x4 v0, f32 s);
f32x4 f32x4_sub(f32x4 v0, f32x4 v1);
f32x4 f32x4_sub1(f32x4 v0, f32 s);
f32x4 f32x4_1sub(f32 s, f32x4 v0);
f32x4 f32x4_mul(f32x4 v0, f32x4 v1);
f32x4 f32x4_mul1(f32x4 v0, f32 s);
f32x4 f32x4_div(f32x4 v0, f32x4 v1);
f32x4 f32x4_div1(f32x4 v0, f32 s);
f32x4 f32x4_1div(f32 s, f32x4 v0);
f32x4 f32x4_sqrt(f32x4 v);
f32x4 f32x4_rsqrt(f32x4 v);
f32x4 f32x4_abs(f32x4 v);
f32x2 f32x2_lerp(f32x2 v0, f32x2 v1, f32 t);
f32x2 f32x2_trunc(f32x2 v, f32 max_mag);
