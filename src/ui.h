


typedef enum{
	UI_ELEMENT_BOX,
	UI_ELEMENT_BUTTON,
	UI_ELEMENT_SLIDER,
	UI_ELEMENT_
}UIElementType;

typedef struct UIElement{
	struct UIElement *parent;
	struct UIElement **child_array;

	u64 frame_accum;
	u64 random_seed;

	String8 local_name;
	String8 name;


	f32x2 fixed_position;
	f32x2 fixed_size;
	f32x2 min_size;

	b32 active;
	b32 disabled;
	b32 focused;

	f32x4 background_color;
	f32x4 border_color;
	f32x4 text_color;
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
