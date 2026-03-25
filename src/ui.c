
UIContext *initialize_ui_context(Arena *arena)
{
	UIContext *context = arena_push(arena, true, sizeof(UIContext));
	context->name_map_size = KiB(4);
	context->frame_accum = 1;
	for(u32 i = 0; i < 2; i++)
	{
		context->name_maps[i] = allocate_array(arena, UIElement, context->name_map_size);
		zero_array(context->name_maps[i], UIElement);
	}
	context->root = arena_push(arena, true, sizeof(UIElement));
	context->root[0] = (UIElement){
		.child_array = allocate_array(arena, UIElement*, 64),		
		.name = str8_lit("UI"),
		.fixed_position = f32x2_set(0,0),
		.fixed_size = f32x2_set(1024, 1024),
	};

	current_thread()->ui_data = context;
	return context;
}

void ui_context_next_frame(UIContext *context, Arena *frame_arena, FixedCamera fixed, PolledEvents pe)
{
	context->frame_arena = frame_arena;	
	context->root->random_seed = 1234567890;
	context->fixed = fixed;
	context->pe = pe;
	context->frame_accum++;
	context->root->fixed_size = f32x2_cast_u32x2(fixed.pixel_size);
	context->root->child_array = 0;
	context->root->name = str8_lit("Root");
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

UIElement* ui_element(UIElement *parent, String8 name)
{
	UIContext *context = current_thread()->ui_data;
	if(parent == 0)
		parent = context->root;	

	name = generate_ui_element_name(context->frame_arena, (String8){0}, &parent->random_seed);

	{
		String8 strs[] = {parent->name, name};
		name = str8_concatenate_and_seperate(context->frame_arena, 2, strs, str8_lit("/"));
	}

	String8 original_name = name;



	UIElement *name_map = context->name_maps[context->frame_accum & 1];

TABLE_INSERT:
	UIElement *slot = 0; u64 slot_index;
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
		memset(name_map + slot_index, 0, sizeof(UIElement));
	}
	else
	{
		memcpy(name_map + slot_index, slot, sizeof(UIElement));
		memset(slot, 0, sizeof(UIElement));
	}
	slot = name_map + slot_index;

	slot->name = name;
	slot->parent = parent;
	slot->child_array = 0;
	slot->frame_accum = context->frame_accum;
	slot->fixed_position = parent->fixed_position;
	slot->fixed_size = parent->fixed_size;

	if(slot->parent->child_array == 0)
	{
		slot->parent->child_array = allocate_array(context->frame_arena, UIElement*, 16);	
	}
	append_array(context->frame_arena, UIElement*, &slot->parent->child_array, slot);

	return slot;
}

UIElement **create_all_child_element_array(Arena *arena, UIElement* e)
{
	u32 count = 0;
	u32 a = 0;
	u32 b = 1;
	UIElement **all_child_array = allocate_array(arena, UIElement*, 16);
	append_array(arena, UIElement*, &all_child_array, e);
	while(a < b)
	{
		u32 bb = b;
		for(u32 j = a; j < b; j++)
		{
			UIElement **current_child_array = all_child_array[j]->child_array;
			if(current_child_array)
			{
				u32 used = USED(current_child_array);
				for(u32 i = 0; i < used; i++)
				{
					append_array(arena, UIElement*, &all_child_array, current_child_array[i]);
				}
				bb += used;
			}
		}
		a = b + 1;
		b = bb;
	}
	return all_child_array;
}

void draw_ui_element(UIElement *e)
{
	Scratch scratch = find_scratch(0,0,0);
	UIElement **all_child_array = create_all_child_element_array(scratch.arena, e);
	for(u32 i = 0; i < USED(all_child_array); i++)
	{
		UIElement *e = all_child_array[i];
		print("%s\n", e->name);
	}
	
	regress_scratch(scratch);
}

void poll_ui_element(UIElement *e)
{

}
