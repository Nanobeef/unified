
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


const f32x4 f32x4_color_white = {{1.0, 1.0, 1.0, 1.0}};
const f32x4 f32x4_color_black = {{0.0, 0.0, 0.0, 1.0}};
	const f32x4 f32x4_color_red = {{1.0, 0.0, 0.0, 1.0}};
	const f32x4 f32x4_color_green = {{0.0, 1.0, 0.0, 1.0}};
	const f32x4 f32x4_color_blue = {{0.0, 0.0, 1.0, 1.0}};
		const f32x4 f32x4_color_yellow = {{1.0, 1.0, 0.0, 1.0}};
		const f32x4 f32x4_color_cyan = {{0.0, 1.0, 1.0, 1.0}};
		const f32x4 f32x4_color_magenta = {{0.0, 1.0, 1.0, 1.0}};

const f32x4 f32x4_color_gray = {{0.5, 0.5, 0.5, 1.0}};
	const f32x4 f32x4_color_maroon = {{0.5, 0.0, 0.0, 1.0}};
	const f32x4 f32x4_color_ao = {{0.0, 0.5, 0.0, 1.0}};
	const f32x4 f32x4_color_navy = {{0.0, 0.0, 0.5, 1.0}};
		const f32x4 f32x4_color_olive = {{0.5, 0.5, 0.0, 1.0}};
		const f32x4 f32x4_color_teal = {{0.0, 0.5, 0.5, 1.0}};
		const f32x4 f32x4_color_purple = {{0.0, 0.5, 0.5, 1.0}};


typedef enum{
	F32X4_COLOR_BLACK,	
	F32X4_COLOR_MAROON,	
	F32X4_COLOR_RED,	
	F32X4_COLOR_AO,	
	F32X4_COLOR_OLIVE,	
	F32X4_COLOR_MANGO,	
	F32X4_COLOR_GREEN,	
	F32X4_COLOR_AQUAMARINE,	
	F32X4_COLOR_YELLOW,	
	F32X4_COLOR_NAVY,	
	F32X4_COLOR_PURPLE,	
	F32X4_COLOR_ROSE,
	F32X4_COLOR_TEAL,
	F32X4_COLOR_GRAY,
	F32X4_COLOR_GERALDINE,
	F32X4_COLOR_SPRING_GREEN,
	F32X4_COLOR_ELECTRIC_BLUE,
	F32X4_COLOR_PALE_CANARY,
	F32X4_COLOR_BLUE,
	F32X4_COLOR_VIOLET,
	F32X4_COLOR_MAGENTA,
	F32X4_COLOR_AZURE,
	F32X4_COLOR_LIGHT_COBALT,
	F32X4_COLOR_PINK,
	F32X4_COLOR_CYAN,
	F32X4_COLOR_SPRAY,
	F32X4_COLOR_WHITE,
	F32X4_COLOR_MAX,
}f32x4_color_flags;

const f32x4 f32x4_colors[F32X4_COLOR_MAX] = {
	{{0.0, 0.0, 0.0, 1.0}},
	{{0.5, 0.0, 0.0, 1.0}},
	{{1.0, 0.0, 0.0, 1.0}},
	{{0.0, 0.5, 0.0, 1.0}},
	{{0.5, 0.5, 0.0, 1.0}},
	{{1.0, 0.5, 0.0, 1.0}},
	{{0.0, 1.0, 0.0, 1.0}},
	{{0.5, 1.0, 0.0, 1.0}},
	{{1.0, 1.0, 0.0, 1.0}},
	{{0.0, 0.0, 0.5, 1.0}},
	{{0.5, 0.0, 0.5, 1.0}},
	{{1.0, 0.0, 0.5, 1.0}},
	{{0.0, 0.5, 0.5, 1.0}},
	{{0.5, 0.5, 0.5, 1.0}},
	{{1.0, 0.5, 0.5, 1.0}},
	{{0.0, 1.0, 0.5, 1.0}},
	{{0.5, 1.0, 0.5, 1.0}},
	{{1.0, 1.0, 0.5, 1.0}},
	{{0.0, 0.0, 1.0, 1.0}},
	{{0.5, 0.0, 1.0, 1.0}},
	{{1.0, 0.0, 1.0, 1.0}},
	{{0.0, 0.5, 1.0, 1.0}},
	{{0.5, 0.5, 1.0, 1.0}},
	{{1.0, 0.5, 1.0, 1.0}},
	{{0.0, 1.0, 1.0, 1.0}},
	{{0.5, 1.0, 1.0, 1.0}},
	{{1.0, 1.0, 1.0, 1.0}},
};
