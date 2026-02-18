

typedef struct{
	f32 a,b;
	f32 c,d;
}f32m2;

f32m2 f32m2_zero();
f32m2 f32m2_identity();
f32m2 f32m2_mul(f32m2 a, f32m2 b);

// 2D Linear transformations
f32m2 f32m2_scale(f32 x, f32 y);
f32m2 f32m2_shear(f32 x, f32 y);
f32m2 f32m2_rotate(f32 radians);
f32x2 f32x2_mul_f32m2(f32x2 v, f32m2 m);
f32x2 f32x2_scale_rotate(f32x2 v, f32 scale, f32 radians);


typedef struct{
	f32 a,b,c;
	f32 d,e,f;
	f32 g,h,i;
}f32m3;

typedef struct{ 
	f32 a,b,c, padding0;
	f32 d,e,f, padding1;
	f32 g,h,i, padding2;
}f32m3p;

f32m3 f32m3_zero();
f32m3 f32m3_identity();
f32m3 f32m3_add(f32m3 a, f32m3 b);
f32m3 f32m3_affine_translate_add(f32m3 a, f32 x, f32 y);
f32m3 f32m3_mul(f32m3 a, f32m3 b);
f32m3 f32m3_affine_translate(f32 x, f32 y);
f32m3 f32m3_affine_scale(f32 x, f32 y);
f32m3 f32m3_affine_shear(f32 x, f32 y);
f32m3 f32m3_affine_rotate(f32 radians);
f32m3 f32m3_lerp(f32m3 a, f32m3 b, f32 t);
f32x2 f32x2_mul_f32m3(f32x2 v, f32m3 m);
f32m3 f32m3_mul_va(u32 c, ...);
f32m3p f32m3_padding(f32m3 a);


f32x2 f32x2_affine_offset(f32m3 m);

f32 f32m3_affine_det(f32m3 m);
f32 f32m3_det(f32m3 m);
f32m3 f32m3_affine_inverse(f32m3 in);

f32m3 print_f32m3(f32m3 m);


typedef struct{
	f32 a,b,c,d;
	f32 e,f,g,h;
	f32 i,j,k,l;
	f32 m,n,o,p;
}f32m4;
