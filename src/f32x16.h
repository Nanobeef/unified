

typedef union{
	f32 s[4];
	f32x2 x2[8];
	f32x4 x4[4];
}f32x16;

f32x16 f32x16_set(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h, f32 i, f32 j, f32 k, f32 l, f32 m, f32 n, f32 o, f32 p);
f32x16 f32x16_set1(f32 v);

f32x16 f32x16_set_f32x2(f32x2 a, f32x2 b, f32x2 c, f32x2 d, f32x2 e, f32x2 f, f32x2 g, f32x2 h);
f32x16 f32x16_set1_f32x2(f32x2 v);

f32x16 f32x16_set_f32x4(f32x4 a, f32x4 b, f32x4 c, f32x4 d);
f32x16 f32x16_set1_f32x4(f32x4 v);

f32x16 f32x16_load(const f32 *a);
f32x16 f32x16_load_aligned(const f32 *a);

f32x16 f32x16_add(f32x16 a, f32x16 b);
f32x16 f32x16_sub(f32x16 a, f32x16 b);
f32x16 f32x16_sub1(f32x16 a, f32 b);
f32x16 f32x16_1sub(f32 a, f32x16 b);
f32x16 f32x16_div1(f32x16 a, f32 b);
f32x16 f32x16_1div(f32 a, f32x16 b);


