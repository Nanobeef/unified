
typedef union s32x2{
	struct{s32 s[2];};
	struct{s32 x,y;};
	struct{s32 a,b;};
}s32x2;

s32x2 s32x2_set1(s32 a);
s32x2 s32x2_set(s32 a, s32 b);
s32x2 s32x2_load(const s32 *src);
void s32x2_scatter(s32 *a, s32 *b, s32x2 v);
s32x2 s32x2_add(s32x2 v0, s32x2 v1);
s32x2 s32x2_add1(s32x2 v0, s32 s);
s32x2 s32x2_sub(s32x2 v0, s32x2 v1);
s32x2 s32x2_sub1(s32x2 v0, s32 s);
s32x2 s32x2_1sub(s32 s, s32x2 v0);
s32x2 s32x2_mul(s32x2 v0, s32x2 v1);
s32x2 s32x2_mul1(s32x2 v0, s32 s);
s32x2 s32x2_div(s32x2 v0, s32x2 v1);
s32x2 s32x2_div1(s32x2 v0, s32 s);
s32x2 s32x2_1div(s32 s, s32x2 v0);
s32x2 s32x2_abs(s32x2 v);
s32 s32x2_dot(s32x2 v0, s32x2 v1);
s32 s32x2_cross(s32x2 v0, s32x2 v1);
s32x2 s32x2_perp_cw(s32x2 v);
s32x2 s32x2_perp_ccw(s32x2 v);



