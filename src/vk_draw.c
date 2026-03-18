

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

f32x2 draw_str8(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, String8 str, f32 pt, f32x4 color)
{
	return draw_str8_wrap(vb, camera, pen, (f32)U32_MAX, str, pt, color);
}


f32x2 draw_str8_wrap(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 wrap, String8 str, f32 pt, f32x4 color)
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
	return pen;
}

f32x2 draw_str8_cutoff(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 cutoff, String8 str, f32 pt, f32x4 color)
{
	GraphicsDeviceFontCache *font_cache = vb->font_cache;
	GraphicsDeviceFont *font = graphics_device_font_compute_metrics(font_cache->default_font, pt);
	for(u32 i = 0; i < str.len; i++)
	{
		u32 code = str.data[i];
		GraphicsDeviceGlyph *glyph = load_graphics_device_glyph(vb->frame_arena, font_cache, 0, code, pt);
		if(pen.x + glyph->glyph.advance > cutoff)
		{
			return pen;
		}
		draw_glyph_internal(font_cache, font, glyph, camera, vb, pen, color);
		pen.x += glyph->glyph.advance;
	}
	return pen;
}

f32x2 draw_str8_cutoff_relaxed(GraphicsDeviceVertexBuffer *vb, FixedCamera camera, f32x2 pen, f32 cutoff, String8 str, f32 pt, f32x4 color)
{
	GraphicsDeviceFontCache *font_cache = vb->font_cache;
	GraphicsDeviceFont *font = graphics_device_font_compute_metrics(font_cache->default_font, pt);
	for(u32 i = 0; i < str.len; i++)
	{
		u32 code = str.data[i];
		GraphicsDeviceGlyph *glyph = load_graphics_device_glyph(vb->frame_arena, font_cache, 0, code, pt);
		if(pen.x > glyph->glyph.advance + cutoff)
		{
			return pen;
		}
		draw_glyph_internal(font_cache, font, glyph, camera, vb, pen, color);
		pen.x += glyph->glyph.advance;
	}
	return pen;
}

void draw_solid_triangle(GraphicsDeviceVertexBuffer *vb, f32x2 p[3], f32x4 color)
{
	Vertex2 v[3];
	for(u32 i = 0; i < 3; i++)
	{
		v[i].position = p[i];
		v[i].color = color;
		v[i].texture = f32x2_set1(0.0f);
	}
	graphics_device_vertex_buffer_push(vb, 3, v);
}

void draw_solid_texture_triangle(GraphicsDeviceVertexBuffer *vb, f32x2 p[3], f32x2 t[3], f32x4 color)
{
	Vertex2 v[3];
	for(u32 i = 0; i < 3; i++)
	{
		v[i].position = p[i];
		v[i].color = color;
		v[i].texture = t[i];
	}
	graphics_device_vertex_buffer_push(vb, 3, v);
}

void draw_color_triangle(GraphicsDeviceVertexBuffer *vb, f32x2 p[3], f32x4 c[3])
{
	Vertex2 v[3];
	for(u32 i = 0; i < 3; i++)
	{
		v[i].position = p[i];
		v[i].color = c[i];
		v[i].texture = f32x2_set1(0.0f);
	}
	graphics_device_vertex_buffer_push(vb, 3, v);
}

void draw_triangle(GraphicsDeviceVertexBuffer *vb, f32x2 p[3], f32x2 t[3], f32x4 c[3])
{
	Vertex2 v[3];
	for(u32 i = 0; i < 3; i++)
	{
		v[i].position = p[i];
		if(c)
			v[i].color = c[i];
		else
			v[i].color = f32x4_set1(1.0f);
		if(t)
			v[i].texture = t[i];
		else
			v[i].texture = f32x2_set1(0.0f);

	}
	graphics_device_vertex_buffer_push(vb, 3, v);
}

void draw_quad(GraphicsDeviceVertexBuffer *vb, f32x2 p[4], f32x2 t[4], f32x4 c[4])
{
	Vertex2 v[4];
	for(u32 i = 0; i < 4; i++)
	{
		v[i].position = p[i];
		if(c)
			v[i].color = c[i];
		else
			v[i].color = f32x4_set1(1.0f);
		if(t)
			v[i].texture = t[i];
		else
			v[i].texture = f32x2_set1(0.0f);

	}
	u32 indices[6] = {0,1,2,2,3,0};
	graphics_device_vertex_buffer_push_indexed(vb, 3, indices, 4, v);
}

void draw_circle(GraphicsDeviceVertexBuffer *vb, u32 n, f32x2 p, f32 pr, f32x2 t, f32 tr, f32x4 inner_color, f32x4 outer_color)
{
	if(n < 3)
		return;
	b32 texture_enable = (tr != 0.0f);
	Scratch scratch = find_scratch(0,0,0);
	Vertex2 *v = arena_push(scratch.arena, 0, sizeof(Vertex2) * (n+1) * 2);
	v[0].position = p;
	v[0].texture = t;
	v[0].color = inner_color;
	Vertex2 *outside = v+1;
	f32 da = PI2 / (f32)n;
	f32 angle = 0.0;
	for(u32 i = 0; i < n; i++)
	{
		angle += da;
		f32 x = cosf(angle);
		f32 y = sinf(angle);
		outside[i].position = f32x2_set(p.x + x * pr, p.y + y * pr);
		if(texture_enable)
			outside[i].texture = f32x2_set(t.x + x * tr, t.y + y * tr);
		else
			outside[i].texture = f32x2_set1(0.0f);
		outside[i].color = outer_color;
	}
	u32 *indices = arena_push(scratch.arena, 0, sizeof(u32) * n * 3);
	u32 i = 0;
	for(u32 j = 0; j < n-1; j++)
	{
		indices[i++] = 0;
		indices[i++] = j+1;
		indices[i++] = j+2;
	}
	indices[i++] = 0;
	indices[i++] = n;
	indices[i++] = 1;
	graphics_device_vertex_buffer_push_indexed(vb, n*3,indices, n+1,v);
	regress_scratch(scratch);
}

typedef struct{
	f32 angle;
	f32 delta_angle;
	f32 radius;
	u32 quality;
	f32x2 center;
}CircleMaker;

CircleMaker circle_make(u32 quality, f32 radius, f32x2 position);
f32x2 circle_make_next(CircleMaker *m);

typedef struct{
	f32 angle;
	f32 delta_angle;
	f32x2 radius;
	u32 quality;
	f32x2 center;
}EllipseMaker;

EllipseMaker ellipse_make(u32 quality, f32x2 radius, f32x2 position);
f32x2 ellipse_make_next(EllipseMaker *m);



u32 perfect_rounding(Camera camera, f32 radius)
{
	u32 quality = radius / camera.unit_pixel.x;
	quality = Max(quality, 4);
	quality = Min(quality, camera.pixel_size.x);
	return quality;
}

u32 perfect_circle(Camera camera, f32 radius)
{
	u32 quality = radius / camera.unit_pixel.x;
	quality = Max(quality, 1);
	quality = Min(quality, camera.pixel_size.x);
	quality *= 4;
	return quality;
}


typedef struct{
	f32 angle;
	f32 delta_angle;
	f32 radius;
	u32 quality;
	u32 index, major_index, major_increment;
	u32 itterations;
	f32x2 p;
	f32x2 ptable[4];
}RoundedRectangleMaker;

RoundedRectangleMaker rounded_rectangle_make(u32 quality, f32 radius, f32x2 a, f32x2 b)
{
	a = f32x2_add1(a, radius);
	b = f32x2_add1(b, -radius);
	quality *= 4;
	RoundedRectangleMaker m = {
		.angle = 0.0f,
		.delta_angle = (2 * 3.1415926) / (f32)(quality),
		.radius = radius, 
		.index = 0,
		.major_index = (quality) / 4, 
		.major_increment = quality / 4,
		.itterations = quality + 4,
		.p = b,
		.ptable[0] = f32x2_set(b.x, b.y),
		.ptable[1] = f32x2_set(a.x, b.y),
		.ptable[2] = f32x2_set(a.x, a.y),
		.ptable[3] = f32x2_set(b.x, a.y),
	};
	return m;
}
f32x2 rounded_rectangle_make_next(RoundedRectangleMaker *m)
{
	f32 x = cosf(m->angle) * m->radius;
	f32 y = sinf(m->angle) * m->radius;
	f32x2 p = f32x2_set(x,y);
	p = f32x2_add(p, m->p);
	if((m->index == m->major_index))
	{
		m->p = m->ptable[(m->major_index / m->major_increment) & 3];
		m->major_index += m->major_increment;
		m->angle -= m->delta_angle;
		m->index--;	
	}
	m->index++;	
	m->angle += m->delta_angle;
	return p;
}

void draw_rounded_rectangle(GraphicsDeviceVertexBuffer *vb, u32 quality, f32 radius, f32x2 p[2], f32x2 t[2], f32x4 color)
{
	Scratch scratch = find_scratch(0,0,0);
	
	if(p == 0)
		return;
	if(t)
		print("Texture parameter is unused.\n");

	f32x2 ta, tb;;
	ta.x = fmin(p[0].x,p[1].x);
	ta.y = fmin(p[0].y,p[1].y);
	tb.x = fmax(p[0].x,p[1].x);
	tb.y = fmax(p[0].y,p[1].y);
	f32x2 a = ta;
	f32x2 b = tb;


	RoundedRectangleMaker maker = rounded_rectangle_make(quality, radius, a, b);
	u32 point_count = maker.itterations + 2;
	Vertex2* points = arena_push(scratch.arena, 0, sizeof(Vertex2) * point_count);
	for(u32 i = 0; i < point_count; i++)
	{
		points[i].position = rounded_rectangle_make_next(&maker);	
	}
	for(u32 i = 0; i < point_count; i++)
	{
		points[i].texture = f32x2_set1(0.0f);
		points[i].color = color;
	}
	u32 triangle_count = point_count - 2;
	u32 index_count = triangle_count * 3;
	u32 *indices = arena_push(scratch.arena, 0, sizeof(u32) * index_count);
	for(u32 i = 0; i < triangle_count; i++)
	{
		indices[i*3] = 0;
		for(u32 j = 1; j < 3; j++)
		{
			indices[i*3+j] = i+j;
		}
	}
	graphics_device_vertex_buffer_push_indexed(vb, index_count, indices, point_count, points);
	regress_scratch(scratch);
}

void draw_rounded_rectangle_outline(GraphicsDeviceVertexBuffer *vb, u32 quality, f32 radius, f32 thickness, f32x2 p[2], f32x2 t[2], f32x4 color)
{
	Scratch scratch = find_scratch(0,0,0);
	
	if(p == 0)
		return;
	if(t)
		print("Texture parameter is unused.\n");

	f32x2 ta, tb;;
	ta.x = fmin(p[0].x,p[1].x);
	ta.y = fmin(p[0].y,p[1].y);
	tb.x = fmax(p[0].x,p[1].x);
	tb.y = fmax(p[0].y,p[1].y);
	f32x2 a = ta;
	f32x2 b = tb;


	RoundedRectangleMaker m_inner = rounded_rectangle_make(quality, radius, a, b);
	a = f32x2_add1(a, -thickness);
	b = f32x2_add1(b, thickness);
	RoundedRectangleMaker m_outer = rounded_rectangle_make(quality, radius + thickness/2, a,b);
	u32 point_count = m_inner.itterations * 2 + 2;
	Vertex2* points = arena_push(scratch.arena, 0, sizeof(Vertex2) * point_count);
	for(u32 i = 0; i < point_count; i++)
	{
		if(i & 1)
		{
			points[i].position = rounded_rectangle_make_next(&m_outer);	
		}
		else
		{
			points[i].position = rounded_rectangle_make_next(&m_inner);	
		}
	}
	for(u32 i = 0; i < point_count; i++)
	{
		points[i].texture = f32x2_set1(0.0f);
		points[i].color = color;
	}
	u32 triangle_count = point_count - 2;
	u32 index_count = triangle_count * 3;
	u32 *indices = arena_push(scratch.arena, 0, sizeof(u32) * index_count);
	for(u32 i = 0; i < triangle_count; i++)
	{
		for(u32 j = 0; j < 3; j++)
		{
			indices[i*3+j] = i+j;
		}
	}
	graphics_device_vertex_buffer_push_indexed(vb, index_count, indices, point_count, points);
	regress_scratch(scratch);
}

