

typedef union u32x2{
	struct{u32 s[2];};
	struct{u32 x,y;};
	struct{u32 a,b;};
}u32x2;

u32x2 u32x2_set1(u32 a);
u32x2 u32x2_set(u32 a, u32 b);
u32x2 u32x2_load(const u32 *src);
void u32x2_scatter(u32 *a, u32 *b, u32x2 v);
u32x2 u32x2_add(u32x2 v0, u32x2 v1);
u32x2 u32x2_add1(u32x2 v0, u32 s);
u32x2 u32x2_sub(u32x2 v0, u32x2 v1);
u32x2 u32x2_sub1(u32x2 v0, u32 s);
u32x2 u32x2_1sub(u32 s, u32x2 v0);
u32x2 u32x2_mul(u32x2 v0, u32x2 v1);
u32x2 u32x2_mul1(u32x2 v0, u32 s);
u32x2 u32x2_div(u32x2 v0, u32x2 v1);
u32x2 u32x2_div1(u32x2 v0, u32 s);
u32x2 u32x2_1div(u32 s, u32x2 v0);
u32x2 u32x2_sqrt(u32x2 v);
u32x2 u32x2_rsqrt(u32x2 v);
u32x2 u32x2_abs(u32x2 v);
u32 u32x2_length_squared(u32x2 v);
u32 u32x2_length(u32x2 v);
