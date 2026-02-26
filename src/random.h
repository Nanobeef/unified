

u64 splitmix(u64 s);

typedef struct{
	u64 state[4];
}RomuQuad;

RomuQuad romu_quad_seed(u64 seed);
u64 romu_quad(RomuQuad *rq);
f32 romu_quad_f32(RomuQuad *rq);
f64 romu_quad_f64(RomuQuad *rq);
f32x2 romu_quad_f32x2(RomuQuad *rq);

f32 romu_quad_positive_f32(RomuQuad *rq);
f64 romu_quad_positive_f64(RomuQuad *rq);
f32x2 romu_quad_positive_f32x2(RomuQuad *rq);


f32x4 romu_quad_color(RomuQuad *rq);
f32x4 romu_quad_solid_color(RomuQuad *rq);
