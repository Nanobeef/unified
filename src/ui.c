
UIContext *initialize_ui_context(Arena *arena, GraphicsDeviceFontCache *font_cache)
{
	UIContext *context = arena_push(arena, true, sizeof(UIContext));
	context->name_map_size = MiB(4);
	context->frame_accum = 1;
	for(u32 i = 0; i < 2; i++)
	{
		context->name_maps[i] = allocate_array(arena, UIBox, context->name_map_size);
		zero_array(context->name_maps[i], UIBox);
	}
	context->root = arena_push(arena, true, sizeof(UIBox));
	context->root[0] = (UIBox){
		.child_array = allocate_array(arena, UIBox*, 64),		
		.name = str8_lit("UI"),
		.fixed_position = f32x2_set(0,0),
		.fixed_size = f32x2_set(1024, 1024),
	};
	context->draw_debug = true;
	context->font_cache = font_cache;

	current_thread()->ui_data = context;

	return context;
}

void ui_context_next_frame(UIContext *context, Arena *frame_arena, FixedCamera fixed)
{
	context->frame_arena = frame_arena;	
	context->root->random_seed = 1234567890;
	context->fixed = fixed;
	context->frame_accum++;
	context->time = get_epoch_ns();
	context->root->fixed_size = f32x2_cast_u32x2(fixed.pixel_size);
	context->root->child_array = 0;
	context->root->name = str8_lit("Root");
	context->pixel_granularity = 1.0f;
	current_thread()->ui_data = context;
}

String8 generate_ui_element_name(Arena *arena, String8 original_name, u64 *seed)
{
	RomuQuad rq = romu_quad_seed(*seed);	
	String8 name = romu_quad_str8(arena, &rq, 4);
	seed[0]++;
	if(original_name.len)
	{
		String8 strings[2] = {original_name, name};
		name = str8_concatenate_and_seperate(arena, 2, strings, str8_lit(":"));
	}
	return name;
}

UIBox* ui_element(UIBox *parent, String8 name)
{
	UIContext *context = current_thread()->ui_data;
	if(parent == 0)
		parent = context->root;	

	if(name.len == 0)
	{
		name = generate_ui_element_name(context->frame_arena, (String8){0}, &parent->random_seed);
	}

	String8 local_name = name;

	{
		String8 strs[] = {parent->name, name};
		name = str8_concatenate_and_seperate(context->frame_arena, 2, strs, str8_lit("/"));
	}

	String8 original_name = name;

	UIBox *name_map = context->name_maps[context->frame_accum & 1];

TABLE_INSERT:
	UIBox *slot = 0; u64 slot_index;
	b32 is_empty_slot = false;
	u64 hash_index = hash_str8(name) % TOTAL(name_map);
	u64 lookup_ranges[4] = {hash_index, TOTAL(name_map), 0, hash_index};

	for(u32 j = 0; j < 2; j++)
	{
		for(slot_index = lookup_ranges[j*2]; slot_index < lookup_ranges[j*2+1]; slot_index++)
		{
			if(name_map[slot_index].frame_accum == context->frame_accum)
			{
				if(str8_equal(name, name_map[slot_index].name))
				{
					name = generate_ui_element_name(context->frame_arena, original_name, &parent->random_seed);
					goto TABLE_INSERT;
				}
			}
			else if(name_map[slot_index].frame_accum == (context->frame_accum - 1))
			{
				if(str8_equal(name, name_map[slot_index].name))
				{
					slot = name_map + slot_index;
					goto SLOT_FOUND;
				}
			}
			else
			{
				slot = name_map + slot_index;
				is_empty_slot = true;
				goto SLOT_FOUND;
			}
		}
	}
	if(slot == 0)
	{
		print("Out of ui space! Could not find an empty element slot. (%u64)\n", context->name_map_size);
		return 0;
	}
SLOT_FOUND:

	name_map = context->name_maps[(context->frame_accum+1) & 1];
	if(is_empty_slot)
	{
		memset(name_map + slot_index, 0, sizeof(UIBox));
	}
	else
	{
		memcpy(name_map + slot_index, slot, sizeof(UIBox));
		memset(slot, 0, sizeof(UIBox));
	}
	slot = name_map + slot_index;

	slot->name = name;
	slot->parent = parent;
	slot->child_array = 0;
	slot->frame_accum = context->frame_accum;
	slot->fixed_position = parent->fixed_position;
	slot->fixed_size = parent->fixed_size;
	slot->local_name = local_name;

	if(slot->parent->child_array == 0)
	{
		slot->parent->child_array = allocate_array(context->frame_arena, UIBox*, 16);	
	}
	append_array(context->frame_arena, UIBox*, &slot->parent->child_array, slot);

	return slot;
}

UIBox* ui_elmt(UIBox *parent) {return ui_element(parent, (String8){0});}

UIBox *ui_box_widget(UIBox *box, UIWidgetType type, u32 count, UIBox **widget_children)
{
	if(NULL == box)
		box = ui_element(0, (String8){0});
	if(type == 0)
		return box;

	UIContext *context = current_thread()->ui_data;
	box->widget_array = allocate_array(context->frame_arena, UIBox*, count);
	box->widget_type = type;
	box->box_bits |= UI_BOX_WIDGET_BIT;

	memcpy(box->widget_array, widget_children, sizeof(UIBox*) * count);
	USED(box->widget_array) = count;

	for(u32 i = 0; i < count; i++)
	{
		box->widget_array[i]->widget_type = type;
	}

	// TODO: Check for all widget requirements. 
	return box;
}

UIBox *ui_box_decoration(UIBox *box, UITheme *theme)
{
	if(NULL == box)
		box = ui_element(0, (String8){0});
	box->box_bits |= UI_BOX_DECORATION_BIT;
	static UITheme default_ui_theme = {
		.background_color = {{0.1, 0.1, 0.1, 0.9}},		
		.monostable_button_background_colors[0] = {{0.5, 0.1, 0.1, 0.3}},
		.monostable_button_background_colors[1] = {{0.1, 0.5, 0.1, 0.3}},
		.hover_tint_color = {{0.1, 0.1, 0.1, 0.1}},
		.border_color = {{0.5, 0.5, 0.5, 0.9}},		
	};
	box->theme = &default_ui_theme;
	if(theme)
		box->theme = theme;
	return box;
}

UIBox *ui_box_text(UIBox *box, f32 pt, String8 text)
{
	UIContext *context = current_thread()->ui_data;
	if(NULL == box)
		box = ui_element(0, (String8){0});
	box->box_bits |= UI_BOX_TEXT_BIT;
	box->text = str8_copy(context->frame_arena, text);
	box->text_point = pt;
	return box;
}

UIBox *ui_box_monostable_button_state(UIBox *box, b32 stable_state, u64 decay_time)
{
	if(NULL == box)
		box = ui_element(0, (String8){0});
	box->box_bits |= UI_BOX_BUTTON_STATE_BIT;
	box->button_state = false;
	box->button_is_monostable = true;
	box->button_decay_time = decay_time = 240000000;
	return box;
}

UIBox *ui_box_mouse_input(UIBox *box, u32 event_count, UIMouseEvent *events)
{
	if(NULL == box)
		box = ui_element(0, (String8){0});
	box->box_bits |= UI_BOX_MOUSE_INPUT_BIT;

	UIContext *context = current_thread()->ui_data;
	box->mouse_event_array = allocate_array(context->frame_arena, UIMouseEvent, event_count);
	memcpy(box->mouse_event_array, events, event_count * sizeof(UIMouseEvent));
	USED(box->mouse_event_array) = event_count;

	return box;
}

UIBox **create_all_child_element_array(Arena *arena, UIBox* e)
{
	u32 count = 0;
	u32 a = 0;
	u32 b = 1;
	UIBox **all_child_array = allocate_array(arena, UIBox*, 16);
	append_array(arena, UIBox*, &all_child_array, e);
	while(a < b)
	{
		u32 bb = b;
		for(u32 j = a; j < b; j++)
		{
			UIBox **current_child_array = all_child_array[j]->child_array;
			if(current_child_array)
			{
				u32 used = USED(current_child_array);
				for(u32 i = 0; i < used; i++)
				{
					append_array(arena, UIBox*, &all_child_array, current_child_array[i]);
				}
				bb += used;
			}
		}
		a = b;
		b = bb;
	}
	return all_child_array;
}

void draw_ui_widget(GraphicsDeviceVertexBuffer *vb, UIBox *widget)
{
	u32 used = 0;
	if(widget->widget_array)
		used = USED(widget->widget_array);

	UIContext *context = current_thread()->ui_data;
	FixedCamera fc = context->fixed;

	for(u32 i = 0; i < used; i++)
	{
		UIBox *box = widget->widget_array[i];
		if(box->box_bits & UI_BOX_DECORATION_BIT)
		{
			f32x2 p[] = {
				fixed_camera_pixels(fc, box->fixed_position),
				fixed_camera_pixels(fc, f32x2_add(box->fixed_position, box->fixed_size))
			};
			draw_rectangle(vb, p, 0, box->background_color);
		}
		if(box->box_bits & UI_BOX_TEXT_BIT)
		{
				
		}
	}

	if(context->draw_debug)
	{
		UIBox *box = widget;
		f32x2 p[] = {
			fixed_camera_pixels(fc, box->fixed_position),
			fixed_camera_pixels(fc, f32x2_add(box->fixed_position, box->fixed_size))
		};
		f32 pixel_granularity = context->pixel_granularity;
		f32 thickness = fixed_camera_pixels1(fc, pixel_granularity * 0.5);
		draw_rectangle_outline(vb, thickness, p, f32x4_set(1.0, 1.0, 1.0, 1.0));
		for(u32 i = 0; i < used; i++)
		{
				
		}
	}
}

void draw_ui(GraphicsDeviceVertexBuffer *vb)
{
	UIContext *context = current_thread()->ui_data;
	Scratch scratch = find_scratch(0,0,0);
	UIBox **all_child_array = create_all_child_element_array(scratch.arena, context->root);
	for(u32 i = 0; i < USED(all_child_array); i++)
	{
		UIBox *e = all_child_array[i];
		if(e->box_bits & UI_BOX_WIDGET_BIT)
		{
			draw_ui_widget(vb, e);
		}
	}
	regress_scratch(scratch);
}



b32 point_is_inside_ui_box(f32x2 p, UIBox *b)
{
	f32x2 pos = b->fixed_position;
	f32x2 size = b->fixed_size;
	if(p.x > pos.x && p.x < pos.x + size.x)
		if(p.y > pos.y && p.y < pos.y + size.y)
			return true;
	return false;
}

void poll_ui_widget(PolledEvents pe, UIBox *widget)
{
	u32 used = 0;
	if(widget->widget_array)
		used = USED(widget->widget_array);
	if(used == 0)
		return;

	UIContext *context = current_thread()->ui_data;
	
	Scratch scratch = find_scratch(0,0,0);

	UIBox ***widget_arrays_by_bit = arena_push(scratch.arena, true, sizeof(UIBox**) * UI_BOX_MAX);
	for(u32 i = 0; i < UI_BOX_MAX; i++)
	{
		widget_arrays_by_bit[i] = allocate_array(scratch.arena, UIBox*, 8);
	}

	for(u32 widget_index = 0; widget_index < used; widget_index++)
	{
		UIBox *widget_child = widget->widget_array[widget_index];
		u32 bits = widget_child->box_bits & (~UI_BOX_WIDGET_BIT);
		u32 bit_pos = 0;
		while(bits)
		{
			if(bits & 1)
			{
				append_array(scratch.arena, UIBox*, &(widget_arrays_by_bit[bit_pos]), widget_child);
			}
			bits>>=1;
			bit_pos++;
		}
	}

	switch(widget->widget_type)
	{
		case UI_WIDGET_MONOSTABLE_BUTTON:
		{
			UIBox *decoration_box = USED(widget_arrays_by_bit[UI_BOX_DECORATION]) ? widget_arrays_by_bit[UI_BOX_DECORATION][0] : widget;
			UIBox *button_state_box = USED(widget_arrays_by_bit[UI_BOX_BUTTON_STATE]) ? widget_arrays_by_bit[UI_BOX_BUTTON_STATE][0] : widget;
			UIBox *mouse_input_box = USED(widget_arrays_by_bit[UI_BOX_MOUSE_INPUT]) ? widget_arrays_by_bit[UI_BOX_MOUSE_INPUT][0] : widget;
			UIBox *collider_box = USED(widget_arrays_by_bit[UI_BOX_COLLIDER]) ? widget_arrays_by_bit[UI_BOX_COLLIDER][0] : widget;


			if(decoration_box->theme == 0)
				break;

			f32x2 pixel_position = pe.mouse.pixel_position;

			b32 was_pressed = collider_box->pressed;
			
			if(point_is_inside_ui_box(pixel_position, collider_box))
			{
				collider_box->hovering = true;	
				collider_box->focused = true;
				if(pe.left_mouse.pressed == true)
					collider_box->pressed = true;
			}
			else
			{
				collider_box->hovering = false;
				if(collider_box->pressed == false)
					collider_box->focused = false;
			}

			if(pe.left_mouse.pressed == false)
			{
				collider_box->pressed = false;
			}

			if(collider_box->pressed)
			{
				button_state_box->button_state = !button_state_box->stable_button_state;
			}
			else
			{
				if(was_pressed)
				{
					button_state_box->button_release_time = context->time;
					button_state_box->is_decaying = true;
				}
				if(button_state_box->is_decaying)
				{
					if(button_state_box->button_release_time + button_state_box->button_decay_time > context->time)
					{
						button_state_box->button_state = !button_state_box->stable_button_state;
					}
					else
					{
						button_state_box->button_state = button_state_box->stable_button_state;
						button_state_box->is_decaying = false;
					}
				}
			}

			decoration_box->background_color = decoration_box->theme->monostable_button_background_colors[button_state_box->button_state];
			
			if(true == collider_box->hovering)
				decoration_box->background_color = f32x4_add(decoration_box->background_color, decoration_box->theme->hover_tint_color);
		}
		break;
		default: break;
	}
	regress_scratch(scratch);
}

void poll_ui(PolledEvents pe)
{
	UIContext *context = current_thread()->ui_data;
	Scratch scratch = find_scratch(0,0,0);
	UIBox **all_child_array = create_all_child_element_array(scratch.arena, context->root);
	for(u32 i = 0; i < USED(all_child_array); i++)
	{
		UIBox *e = all_child_array[i];
		if(e->box_bits & UI_BOX_WIDGET_BIT)
		{
			poll_ui_widget(pe, e);
		}
	}
	regress_scratch(scratch);
}

void ui_test()
{
	RomuQuad rq = romu_quad_seed(323321);
	UIContext *context = current_thread()->ui_data;
	u32 count = (context->frame_accum * 10) % 4000;
	count = 1;
	count = Max(count, 1);
	u64 t = get_time_ns();
	for(u32 i = 0; i < count; i ++)
	{
		UIBox *widget = ui_element(0, (String8){0});
		widget->fixed_size = f32x2_set(32, 32);
		f32x2 rp = romu_quad_positive_f32x2(&rq);
		rp = f32x2_mul(context->root->fixed_size, rp);
		rp.x = floorf(rp.x);
		rp.y = floorf(rp.y);
		widget->fixed_position = rp;

		UIMouseEvent mouse_event = {.event.type = MOUSE_PRESS, .event.button = MOUSE_BUTTON_LEFT, .interactivity = UI_PRESSED};

		UIBox* boxes[] = {
			ui_box_decoration(ui_element(widget, str8_lit("dec")), 0),
			ui_box_monostable_button_state(ui_element(widget, str8_lit("mono")), 0, 0),
			ui_box_mouse_input(ui_element(widget, str8_lit("minput")), 1, &mouse_event),
		};
		ui_box_widget(widget, UI_WIDGET_MONOSTABLE_BUTTON, Arrlen(boxes), boxes);
	}
	t = get_time_ns() - t;
//	print("%u32 buttons at %t\n avg per button: %tns\n", count, t, t / count);
}
