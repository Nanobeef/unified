

void draw_glyph_internal(GraphicsDeviceFontCache *font_cache, GraphicsDeviceFont *font, GraphicsDeviceGlyph *glyph, FixedCamera camera, GraphicsDeviceVertexBuffer *vb, f32x2 pen, f32x4 color)
{
	f32x2 bearing = f32x2_set(glyph->glyph.bearing.x, -glyph->glyph.bearing.y);
	f32x2 offset = bearing;
	offset.y += font->unit_em.y;

	Vertex2 vertices[4];
	memset(vertices, 0, sizeof(vertices));

	for(u32 i = 0; i < 4; i++)
	{
		vertices[i].color = color;
		vertices[i].texture = f32x2_set(glyph->cache_position.x, glyph->cache_position.y);
	}

	vertices[0].texture = f32x2_add(vertices[0].texture, f32x2_set(0, 0));
	vertices[1].texture = f32x2_add(vertices[1].texture, f32x2_set(glyph->cache_size.x, 0));
	vertices[2].texture = f32x2_add(vertices[2].texture, f32x2_set(0, glyph->cache_size.y));
	vertices[3].texture = f32x2_add(vertices[3].texture, f32x2_set(glyph->cache_size.x, glyph->cache_size.y));

	for(u32 i = 0; i < 4; i++)
	{
		vertices[i].position = f32x2_sub(vertices[i].texture, f32x2_cast_u32x2(glyph->cache_position));	
		vertices[i].position = f32x2_mul(vertices[i].position, camera.unit_pixel);
		vertices[i].position = f32x2_add(vertices[i].position, camera.top_left);
		f32x2 o = f32x2_mul(f32x2_add(offset, pen), camera.unit_pixel);
		vertices[i].position = f32x2_add(vertices[i].position, o);
		if(glyph->in_cache == false)
		{
			vertices[i].texture = f32x2_set1(0.0f);
			vertices[i].color = f32x4_set(1.0, 0.0, 1.0, 1.0);
		}
	}

	u32 indices[] = {
		0,1,2,2,1,3,
	};


	graphics_device_vertex_buffer_push_indexed(vb, 6, indices, 4, vertices);
}

void draw_glyph(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, u32 code, f32 pt, f32x4 color)
{
	GraphicsDeviceFontCache *font_cache = vb->font_cache;
	GraphicsDeviceFont *font = graphics_device_font_compute_metrics(font_cache->default_font, pt);
	GraphicsDeviceGlyph *glyph = load_graphics_device_glyph(vb->frame_arena, font_cache, 0, code, pt);

	draw_glyph_internal(font_cache, font, glyph, camera, vb, pen, color);
}

void draw_str8(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, String8 str, f32 pt, f32x4 color)
{
	draw_str8_wrap(vb, camera, pen, (f32)U32_MAX, str, pt, color);
}


void draw_str8_wrap(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 wrap, String8 str, f32 pt, f32x4 color)
{
	f32x2 a = pen;
	GraphicsDeviceFontCache *font_cache = vb->font_cache;
	GraphicsDeviceFont *font = graphics_device_font_compute_metrics(font_cache->default_font, pt);
	f32 line_spacing = 1.0;
	u32 tabstop = 8;
	u32 last_newline = -1;
	u32 index = 0;
	for(u32 i = 0; i < str.len; i++)
	{
		u32 code = str.data[i];
		GraphicsDeviceGlyph *glyph = load_graphics_device_glyph(vb->frame_arena, font_cache, 0, code, pt);
		if(code == '\n')
		{
			pen.y += font->unit_em.y * line_spacing;
			pen.x = a.x;
			last_newline = index;
			index++;
			continue;
		}
		if(code == '\t')
		{
			u32 m = tabstop-((index - last_newline)%tabstop);
			index+=m;
			pen.x += font->max_advance_width * m;
			continue;
		}
		if(pen.x + glyph->glyph.advance > wrap)
		{
			pen.y += font->unit_em.y * line_spacing;
			pen.x = a.x;
		}
		draw_glyph_internal(font_cache, font, glyph, camera, vb, pen, color);
		pen.x += glyph->glyph.advance;
		index++;
	}
}

void draw_str8_cutoff(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 cutoff, String8 str, f32 pt, f32x4 color)
{
	GraphicsDeviceFontCache *font_cache = vb->font_cache;
	GraphicsDeviceFont *font = graphics_device_font_compute_metrics(font_cache->default_font, pt);
	for(u32 i = 0; i < str.len; i++)
	{
		u32 code = str.data[i];
		GraphicsDeviceGlyph *glyph = load_graphics_device_glyph(vb->frame_arena, font_cache, 0, code, pt);
		if(pen.x + glyph->glyph.advance > cutoff)
		{
			return;
		}
		draw_glyph_internal(font_cache, font, glyph, camera, vb, pen, color);
		pen.x += glyph->glyph.advance;
	}
}

void draw_str8_cutoff_relaxed(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 cutoff, String8 str, f32 pt, f32x4 color)
{
	GraphicsDeviceFontCache *font_cache = vb->font_cache;
	GraphicsDeviceFont *font = graphics_device_font_compute_metrics(font_cache->default_font, pt);
	for(u32 i = 0; i < str.len; i++)
	{
		u32 code = str.data[i];
		GraphicsDeviceGlyph *glyph = load_graphics_device_glyph(vb->frame_arena, font_cache, 0, code, pt);
		if(pen.x > glyph->glyph.advance + cutoff)
		{
			return;
		}
		draw_glyph_internal(font_cache, font, glyph, camera, vb, pen, color);
		pen.x += glyph->glyph.advance;
	}
}






