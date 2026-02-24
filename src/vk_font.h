
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
	f32x2 dpi;
	f32 pt;
		
}GraphicsDeviceFont;


typedef struct{
	u32 code;
	f32 pt;
	f32x2 size;
	f32x2 bearing;
	f32 advance;
}Glyph;

typedef struct{
	b32 filled;
	b32 removed;
	u32 code;
	f32 pt;
	Glyph glyph;
	u32x2 cache_position;
	u32x2 cache_size;
	GraphicsDeviceFont *font;
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

	GraphicsDeviceGlyph **new_glyph_array;
	

	u32x2 size;
	u32x2 position;
	u32 max_row_height;
}GraphicsDeviceFontCache;


GraphicsDeviceFontCache* create_graphics_device_font_cache(Arena *arena, GraphicsDevice *device);
void destroy_graphics_device_font_cache(GraphicsDeviceFontCache *cache);
GraphicsDeviceFont *create_graphics_device_font(Arena *arena, const u8 *file_array, GraphicsDeviceFontCache *cache);
GraphicsDeviceGlyph *load_graphics_device_glyph(Arena *arena, GraphicsDeviceFontCache *cache, GraphicsDeviceFont *font, u32 code, f32 pt);
void destroy_graphics_device_font(GraphicsDeviceFont *font);
