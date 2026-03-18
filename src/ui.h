


typedef struct{
	
}UITheme;


typedef struct UIElement{
	struct UIElement *parent;
	struct UIElement *child_array;

	u64 frame_accum;
	u64 random_seed;

	String8 name;

	f32x2 bounding_box[2];

}UIElement;

typedef struct{
	
	FixedCamera fixed;
	PolledEvents pe;

// Most sizes are in pixels

	u64 frame_accum;
	u64 name_map_size;
	UIElement *name_maps[2];

	UIElement *root;

	Arena *frame_arena;
}UIContext;

UIContext *initialize_ui_context(Arena *arena);
void ui_context_next_frame(UIContext *context, Arena *frame_arena, FixedCamera fixed, PolledEvents pe);
UIElement* ui_element(UIElement *parent, String8 name);
