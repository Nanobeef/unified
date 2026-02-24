


#define BERKELEY_PATH "bin/BerkeleyMono-Regular.ttf"

GraphicsDeviceFontCache* create_graphics_device_font_cache(Arena *arena, GraphicsDevice *device)
{
	FT_Error fterror = {0};
	FT_Library ft_library;
	if(fterror = FT_Init_FreeType(&ft_library))
	{
		
	}

	GraphicsDeviceImage linear_image = create_graphics_device_image_explicit(
		device->host_and_device_heap, u32x2_set(2048, 4096),
		VK_FORMAT_R8_UNORM,  VK_IMAGE_USAGE_SAMPLED_BIT,
		VK_IMAGE_TILING_OPTIMAL, VK_SAMPLE_COUNT_1_BIT
	);

	arena_push_type(arena, 0, 1, GraphicsDeviceFontCache, cache);
	*cache = (GraphicsDeviceFontCache){
		.device = device,
		.ft_library = ft_library,
		.linear_image = linear_image,

	};

	cache->font_capacity = 1024;
	cache->font_count = 0;
	cache->font_map = arena_push(arena, true, cache->font_capacity * sizeof(GraphicsDeviceFont));

	cache->glyph_capacity = 1024 * 4;
	cache->glyph_count = 0;
	cache->glyph_map = arena_push(arena, true, cache->glyph_capacity * sizeof(GraphicsDeviceGlyph));

	Scratch scratch = find_scratch(0,1, &arena);
	cache->default_font = create_graphics_device_font(arena, read_file(scratch.arena, str8_lit(BERKELEY_PATH)), cache);
	regress_scratch(scratch);

	return cache;
}

void destroy_graphics_device_font_cache(GraphicsDeviceFontCache *cache)
{
	destroy_graphics_device_image(cache->linear_image);

	destroy_graphics_device_font(cache->default_font);
	FT_Done_FreeType(cache->ft_library);
}

GraphicsDeviceFont *create_graphics_device_font(Arena *arena, const u8 *file_array, GraphicsDeviceFontCache *cache)
{
	FT_Face face = {0};
	FT_Error fterror = {0};
	
	FT_Open_Args args = {
		.flags = FT_OPEN_MEMORY,
		.memory_base = file_array,
		.memory_size = USED(file_array),
	};
	if(fterror = FT_Open_Face(cache->ft_library, &args, 0, &face))
	{
		print("unable to open font face.\n");
	}

	GraphicsDeviceFont font = {
		.cache = cache,
		.face = face,
		.units_per_em = face->units_per_EM,
		.ascender = face->ascender / 64,
		.descender = face->descender / 64,
		.height = face->height / 64,
		.max_advance_width = face->max_advance_width / 64,
		.bbox_xmin = face->bbox.xMin / 64,
		.bbox_xmax= face->bbox.xMax / 64,
		.bbox_ymin = face->bbox.yMin / 64,
		.bbox_ymax= face->bbox.yMax / 64,
		.underline_position = face->underline_position / 64,
	};

	GraphicsDeviceFont *dst = 0;
	for(u32 i = 0; i < cache->font_capacity; i++)
	{
		if(cache->font_map[i].cache == 0)
		{
			font.index = i;
			cache->font_map[i] = font;		
			dst = cache->font_map + i;
		}
	}
	cache->font_count++;
	return dst;
}

void destroy_graphics_device_font(GraphicsDeviceFont *font)
{
	GraphicsDeviceFontCache *cache = font->cache;
	for(u32 i = 0; i < cache->font_capacity; i++)
	{
		if((cache->font_map[i].index == font->index) && (cache->font_map[i].cache != 0))
		{
			cache->font_map[i].cache = 0;
		}
	}
	FT_Done_Face(font->face);
	cache->font_count--;
}

GraphicsDeviceGlyph *load_graphics_device_glyph(GraphicsDeviceFontCache *cache, GraphicsDeviceFont *font, f32x2 dpi, u32 code, f32 pt)
{
	FT_Error fterror = {0};
	if(fterror = FT_Set_Char_Size(font->face, 0, 12 * 64, dpi.x, dpi.y))
	{
	}
	return 0;
}

void resolve_graphics_device_font_cache(GraphicsDeviceFontCache *cache)
{
	flush_graphics_device_memory(cache->linear_image.memory);
	RomuQuad rq = romu_quad_seed(get_epoch_ms());
	for(u32 i = 0; i < cache->linear_image.size.x * cache->linear_image.size.y; i++)
	{
		u8 *data = cache->linear_image.memory.mapping;
		data[i] = romu_quad(&rq);
	}
}


