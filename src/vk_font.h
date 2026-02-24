
struct GraphicsDeviceFontCache;


typedef struct{
	struct GraphicsDeviceFontCache *cache;
	FT_Face face;
	u32 index;

	f32 units_per_em;
	f32 ascender;
	f32 descender;
	f32 height;
	f32 max_advance_width;
	f32 bbox_xmin, bbox_xmax;
	f32 bbox_ymin, bbox_ymax;
	f32 underline_position;
		
}GraphicsDeviceFont;


typedef struct{
	u32 code;
	u32 font_index;
	f32 pt;
	f32 ascender;
	f32 descender;
	f32 height;
	f32x2 ppem;


	u32x2 bitmap_size;
	u8* data;
}Glyph;

typedef struct{
	Glyph glyph;
	u32x2 cache_position;
	u32x2 cache_size;
}GraphicsDeviceGlyph;


typedef struct GraphicsDeviceFontCache{
	GraphicsDevice *device;
	FT_Library ft_library;
	GraphicsDeviceImage linear_image;
	f32x2 screen_dpi;

	GraphicsDeviceFont *default_font;

	u32 font_count;
	u32 font_capacity;
	GraphicsDeviceFont *font_map;

	u32 glyph_count;
	u32 glyph_capacity;
	GraphicsDeviceGlyph *glyph_map;

	u32x2 position;
	u32 max_row_height;
}GraphicsDeviceFontCache;


GraphicsDeviceFontCache* create_graphics_device_font_cache(Arena *arena, GraphicsDevice *device);
void destroy_graphics_device_font_cache(GraphicsDeviceFontCache *cache);
GraphicsDeviceFont *create_graphics_device_font(Arena *arena, const u8 *file_array, GraphicsDeviceFontCache *cache);
GraphicsDeviceGlyph *load_graphics_device_glyph(GraphicsDeviceFontCache *cache, GraphicsDeviceFont *font, f32x2 dpi, u32 code, f32 pt);
void destroy_graphics_device_font(GraphicsDeviceFont *font);
