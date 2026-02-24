


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
		VK_IMAGE_TILING_LINEAR, VK_SAMPLE_COUNT_1_BIT
	);
	memset(linear_image.memory.mapping, 255, linear_image.memory.size);

	arena_push_type(arena, 0, 1, GraphicsDeviceFontCache, cache);
	*cache = (GraphicsDeviceFontCache){
		.device = device,
		.ft_library = ft_library,
		.linear_image = linear_image,

	};

	cache->font_capacity = 1024;
	cache->font_count = 0;
	cache->font_map = arena_push(arena, true, cache->font_capacity * sizeof(GraphicsDeviceFont));

	cache->glyph_capacity = 1024 * 8;
	cache->glyph_count = 0;
	cache->glyph_map = arena_push(arena, true, cache->glyph_capacity * sizeof(GraphicsDeviceGlyph));

	cache->size = linear_image.size,
	cache->position = u32x2_set(0,0);
	cache->max_row_height = 0;

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
			cache->font_count++;
			goto SLOT_FOUND;
		}
	}
SLOT_FOUND:
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

u64 font_hash(u32 code, f32 pt)
{
	u64 d;
	memcpy((u8*)&d + 0, &code, 4);
	memcpy((u8*)&d + 4, &pt, 4);
	return splitmix(d);
}

GraphicsDeviceGlyph *load_graphics_device_glyph(Arena *arena, GraphicsDeviceFontCache *cache, GraphicsDeviceFont *font, u32 code, f32 pt)
{
	u64 hash = font_hash(code, pt) % cache->glyph_capacity;
	b32 duplicate = false;
	GraphicsDeviceGlyph *slot = 0;
	{
		u32 a[2] = {hash, 0};
		u32 b[2] = {cache->glyph_capacity, hash};
		for(u32 j = 0; j < 2; j++)
		{
			for(u32 i = a[j]; i < b[j]; i++)
			{
				if((cache->glyph_map[i].filled == false) && (cache->glyph_map[i].removed == false))
				{
					slot = cache->glyph_map + i;	
					slot->filled = true;
					slot->code = code;
					slot->pt = pt;
					goto SLOT_FOUND;
				}
				else if(cache->glyph_map[i].filled == true)
				{
					if((cache->glyph_map[i].pt == pt) && (cache->glyph_map[i].code == code))
					{
						duplicate = true;
						slot = cache->glyph_map + i;
						goto SLOT_FOUND;
					}
				}
			}
		}
		print("Out of glyph slots!\n");
		return 0;
	}
	SLOT_FOUND:
	if(duplicate == false)
	{
		FT_Error fterror = {0};
		if(font->pt != pt)
		{
			font->pt = pt;
			if(fterror = FT_Set_Char_Size(font->face, 0, font->pt * 64, font->dpi.x, font->dpi.y))
			{
				print("Failed to set char size\n");	
			}
		}
		if((fterror = FT_Load_Char(font->face, code, FT_LOAD_COMPUTE_METRICS)))
		{
			print("Failed to load metrics\n");
		}

		FT_GlyphSlot gs = font->face->glyph;
		slot->glyph = (Glyph){
			.code = code,
			.pt = pt,
			.size = f32x2_set((f32)gs->metrics.width/64.0, (f32)gs->metrics.height/64.0),
			.bearing = f32x2_set((f32)gs->metrics.horiBearingX/64.0, (f32)gs->metrics.horiBearingY/64.0),
			.advance = (f32)gs->metrics.horiAdvance/64.0,
		};
		slot->font = font;
		u32x2 bitmap_size = u32x2_set(font->face->glyph->bitmap.width, font->face->glyph->bitmap.rows);
		slot->cache_size = bitmap_size;
		if(cache->size.x < cache->position.x + slot->cache_size.x)
		{
			cache->position.x = 0;
			cache->position.y += cache->max_row_height;
			cache->max_row_height = 0;
		}
		else
		slot->cache_position = cache->position;
		cache->position.x += bitmap_size.x;
		cache->max_row_height = Max(slot->cache_size.y, cache->max_row_height);

		if(cache->new_glyph_array == 0)
		{
			cache->new_glyph_array = allocate_array(arena, GraphicsDeviceGlyph*, 16);
		}

		append_array(arena, GraphicsDeviceGlyph*, &cache->new_glyph_array, slot);
	}

	return slot;
}

void resolve_graphics_device_font_cache(GraphicsDeviceFontCache *cache)
{
	RomuQuad rq = romu_quad_seed(get_epoch_ms());
	u32x2 size = cache->linear_image.size;
	size = u32x2_set1(256);

	if(cache->new_glyph_array)
	{
		for(u32 i = 0; i < USED(cache->new_glyph_array); i++)
		{
			GraphicsDeviceGlyph *glyph = cache->new_glyph_array[i];
	//		print("%u32:\n %u32x2\n%u32x2\n-------\n", i, glyph->cache_position, glyph->cache_size);
			
			GraphicsDeviceFont *font = glyph->font;
			if(font == 0)
			{
				print("This glyph does not have a valid font!\n");
				continue;
			}
			FT_Error fterror = {0};
			if(font->pt != glyph->pt)
			{
				font->pt = glyph->pt;
				if(fterror = FT_Set_Char_Size(font->face, 0, font->pt * 64, font->dpi.x, font->dpi.y))
				{
					print("Failed to set char size\n");	
				}
			}
			if((fterror = FT_Load_Char(font->face, glyph->code, FT_LOAD_RENDER)))
			{
				print("Failed to render bitmap\n");
			}
			FT_GlyphSlot gs = font->face->glyph;
			u8* src = gs->bitmap.buffer;
			u8* dst = cache->linear_image.memory.mapping;
			u32x2 dst_size = cache->linear_image.size;
			for(u32 y = 0; y < gs->bitmap.rows; y++)
			{
				for(u32 x = 0; x < gs->bitmap.width; x++)
				{
					u32 xx = glyph->cache_position.x + x;
					u32 yy =  glyph->cache_position.y + y;
					dst[xx + dst_size.x * yy] = src[x];
				}
				src += gs->bitmap.pitch;
			}



		}
	}

	if(0)
	{
		u8 *data = cache->linear_image.memory.mapping;
		for(u32 y = 0; y < size.y; y++)
		{
			for(u32 x = 0; x < size.x; x++)
			{
				data[y * cache->linear_image.size.x + x] = (u8)romu_quad(&rq);
			}
		}
	}
	flush_graphics_device_memory(cache->linear_image.memory);
	cache->position = u32x2_set(0,0);
	cache->max_row_height = 0;
	cache->new_glyph_array = 0;
}


