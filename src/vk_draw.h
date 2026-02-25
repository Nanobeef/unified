
void draw_glyph(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, u32 code, f32 pt, f32x4 color);
void draw_str8(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, String8 str, f32 pt, f32x4 color);
void draw_str8_wrap(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 wrap, String8 str, f32 pt, f32x4 color);
void draw_str8_cutoff(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 cutoff, String8 str, f32 pt, f32x4 color);
void draw_str8_cutoff_relaxed(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 cutoff, String8 str, f32 pt, f32x4 color);
