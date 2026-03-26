
typedef enum{
	UI_BOX_DECORATION 		= 0,
	UI_BOX_TEXT 			= 1,
	UI_BOX_KEYBOARD_INPUT	= 2,
	UI_BOX_MOUSE_INPUT		= 3,
	UI_BOX_DATA_BUFFER 		= 4,
	UI_BOX_BUTTON_STATE		= 6,
	UI_BOX_SLIDER_STATE		= 7,
	UI_BOX_COLLIDER 		= 8,
	UI_BOX_MAX,
	UI_BOX_WIDGET 			= 30,

}UIBoxType;

typedef enum{
	UI_BOX_DECORATION_BIT 		= (1u<<UI_BOX_DECORATION),
	UI_BOX_TEXT_BIT				= (1u<<UI_BOX_TEXT),
	UI_BOX_KEYBOARD_INPUT_BIT	= (1u<<UI_BOX_KEYBOARD_INPUT),
	UI_BOX_MOUSE_INPUT_BIT		= (1u<<UI_BOX_MOUSE_INPUT),
	UI_BOX_DATA_BUFFER_BIT		= (1u<<UI_BOX_DATA_BUFFER),
	UI_BOX_BUTTON_STATE_BIT		= (1u<<UI_BOX_BUTTON_STATE),
	UI_BOX_SLIDER_STATE_BIT		= (1u<<UI_BOX_SLIDER_STATE),
	UI_BOX_COLLIDER_BIT 		= (1u<<UI_BOX_COLLIDER),

	UI_BOX_MAX_BIT			= (1u<<UI_BOX_MAX),

	UI_BOX_WIDGET_BIT 			= (1u<<UI_BOX_WIDGET),
}UIBoxBits;


// A Widget can be a set of Boxes or a single Box.
// A Box can be a widget or a piece of a Widget.

typedef enum{
	UI_WIDGET_NONE = 0,
	UI_WIDGET_MONOSTABLE_BUTTON,
	UI_WIDGET_ASTABLE_BUTTON,

	UI_NORMAL_WIDGET_SLIDER,
	UI_INTEGER_SLIDER,

	UI_WIDGET_BUTTON_MAP,
}UIWidgetType;

typedef struct{
	f32x4 monostable_button_background_colors[2];
	f32x4 hover_tint_color;

	f32x4 background_color;
	f32x4 border_color;
}UITheme;

typedef enum{
	UI_HOVER,
	UI_PRESSED,
	UI_FOCUSED,
}UIInteractivityType;

typedef struct{
	MouseEvent event;
	UIInteractivityType interactivity;
}UIMouseEvent;

typedef struct{
	KeyboardEvent event;
	UIInteractivityType interactivity;
}UIKeyboardEvent;

typedef struct UIBox{
// Data links
	struct UIBox *parent;
	struct UIBox **child_array;
	struct UIBox *widget;
	struct UIBox **widget_array;

// Box and ordering
	u32 box_bits;
	// TODO: bit order flags

// Widget 
	UIWidgetType widget_type;

// Hash Map
	u64 frame_accum;
	u64 random_seed;
	String8 local_name;
	String8 name;

// Position and shape
	f32x2 fixed_position;
	f32x2 fixed_size;
	f32x2 min_size;
	f32 corner_radii[4];

// Decoration
	UITheme *theme;
	f32x4 background_color;
	f32x4 outline_color;

// Text
	String8 text;
	f32 text_point;
	f32x4 text_color;

	

// Data Buffer
	// TODO: Format
	void *data_buffer;

// KeyboardInput
	UIKeyboardEvent *keyboard_event_array;
// MouseInput
	UIMouseEvent *mouse_event_array;
	
// Collider 
	b32 hovering;
	b32 focused;
	b32 pressed;

// Button stage 
	b32 button_state;
	b32 button_is_monostable;
	u64 button_decay_time;
	u64 button_release_time;
	b32 stable_button_state;
	b32 is_decaying;

}UIBox;

typedef struct{
	
	FixedCamera fixed;

	u64 frame_accum;
	u64 name_map_size;
	UIBox *name_maps[2];

	u64 time;

	UIBox *root;

	b32 draw_debug;

	f32 pixel_granularity;

	GraphicsDeviceFontCache *font_cache;

	Arena *frame_arena;
}UIContext;

UIContext *initialize_ui_context(Arena *arena, GraphicsDeviceFontCache *font_cache);
void ui_context_next_frame(UIContext *context, Arena *frame_arena, FixedCamera fixed);
UIBox* ui_element(UIBox *parent, String8 name);
