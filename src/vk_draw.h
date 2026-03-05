
void draw_glyph(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, u32 code, f32 pt, f32x4 color);
f32x2 draw_str8(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, String8 str, f32 pt, f32x4 color);
f32x2 draw_str8_wrap(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 wrap, String8 str, f32 pt, f32x4 color);
f32x2 draw_str8_cutoff(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 cutoff, String8 str, f32 pt, f32x4 color);
f32x2 draw_str8_cutoff_relaxed(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 cutoff, String8 str, f32 pt, f32x4 color);


void draw_triangle(GraphicsDeviceVertexBuffer *vb, f32x2 p[3], f32x2 t[3], f32x4 c[3]);
void draw_quad(GraphicsDeviceVertexBuffer *vb, f32x2 p[4], f32x2 t[4], f32x4 c[4]);
void draw_circle(GraphicsDeviceVertexBuffer *vb, u32 n, f32x2 p, f32 pr, f32x2 t, f32 tr, f32x4 inner_color, f32x4 outer_color);






