
typedef enum{
    EVENT_NONE,
    EVENT_WINDOW,
    EVENT_PROCESS,
    EVENT_KEYBOARD,
    EVENT_MOUSE,
    EVENT_SET_CURSOR,
}EventTypeFlags;
typedef u32 EventType;

typedef enum{
    WINDOW_NONE = 0,
    WINDOW_RESIZE,
    WINDOW_MOVE,
}WindowEventTypeFlags;
typedef u32 WindowEventType;

typedef struct{
    WindowEventType type;
    struct{ s32 x,y; };
    struct{ u32 width, height;};
}WindowEvent;

typedef enum{
	BUTTON_NONE = 0,
	BUTTON_PRESS = 1,
	BUTTON_RELEASE = 2,
}ButtonEventTypeFlags;
typedef u32 ButtonEventType;

typedef enum{
    KEYBOARD_NONE = 0,
    KEYBOARD_PRESS = 1,
    KEYBOARD_RELEASE = 2,
}KeyboardEventTypeFlags;
typedef u32 KeyboardEventType;

typedef enum{
    MOUSE_NONE = 0,
    MOUSE_PRESS = 1,
    MOUSE_RELEASE = 2,
    MOUSE_SCROLL,
	MOUSE_PINCH,
    MOUSE_MOVE,
    MOUSE_ENTER,
    MOUSE_LEAVE,
}MouseEventTypeFlags;
typedef u32 MouseEventType;

typedef enum{
    MOUSE_BUTTON_NONE,
    MOUSE_BUTTON_LEFT,
    MOUSE_BUTTON_MIDDLE,
    MOUSE_BUTTON_RIGHT,
    MOUSE_BUTTON_BACK,
    MOUSE_BUTTON_FORWARD,
    MOUSE_BUTTON_SCROLL_POSITIVE,
    MOUSE_BUTTON_SCROLL_NEGATIVE,
    MOUSE_BUTTON_TRACKPAD_POSITIVE,
    MOUSE_BUTTON_TRACKPAD_NEGATIVE,
}MouseButtonTypeFlags;
typedef u32 MouseButtonType;

typedef struct{
    MouseEventType type;
    union{
        struct {s32 x,y;};
        MouseButtonType button;
    };
}MouseEvent;



typedef enum{
    KEY_NONE = 0,
    KEY_A,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_1,
    KEY_2,
    KEY_3,
    KEY_4,
    KEY_5,
    KEY_6,
    KEY_7,
    KEY_8,
    KEY_9,
    KEY_0,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_LEFT_CONTROL,
    KEY_RIGHT_CONTROL,
    KEY_LEFT_SHIFT,
    KEY_RIGHT_SHIFT,
    KEY_GRAVE,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT_ALT,
	KEY_RIGHT_ALT,
	KEY_LEFT_HOME,
	KEY_RIGHT_HOME,
	KEY_ENTER,
    KEY_ESCAPE,
}KeyTypeFlags;
typedef u32 KeyType;

typedef struct{
    KeyboardEventType type;
    KeyType key;
}KeyboardEvent;

typedef enum{
    CURSOR_POINTER = 0,
    CURSOR_HAND,
    CURSOR_X11_GOBBLER,
    CURSOR_X11_GUMBY,
    CURSOR_X11_BOAT,
    CURSOR_FLEUR,
    CURSOR_CIRCLE,
    CURSOR_CROSS,
}CursorTypeFlags;
typedef u32 CursorType;

typedef struct{
    CursorType type;
    f32x4 background_color;
    f32x4 foreground_color;
}CursorSetEvent;

typedef struct{
    EventType type;
    union{
        WindowEvent window;
        KeyboardEvent keyboard;
        MouseEvent mouse;
        CursorSetEvent set_cursor;
    };
    void *window_pointer;
    u64 time;
}Event;

Event init_event();
void post_event(Event *event_ring_buffer, Event event);
void print_event(Event event);

typedef struct Button{
    b32 pressed;
    b32 released;
    u64 press_time;
    u64 release_time;
    u64 action_time;
	struct Button *previous;
}Button;

typedef struct Wheel{
	b32 moved;
	f64 accum;
	f32 velocity;
	u64 time;
	struct Wheel *previous;
}Wheel;

typedef struct Mouse{
	u64 move_time;	
	f32x2 previous_pixel_position;
	f32x2 pixel_position;
	f32x2 pixel_delta;
	b32 moved;
	u64 scroll_time;
	struct Mouse *previous;
}Mouse;

typedef struct{
   Button first_button;
	Button a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z;
	Button n0,n1,n2,n3,n4,n5,n6,n7,n8,n9;
	Button f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12;
	Button left_control, right_control, control;
	Button left_shift, right_shift, shift;
	Button left_alt, right_alt, alt;
	Button left,right,up,down;
	Button enter;
	Button grave;
	Button escape;
	Button	left_mouse;
	Button	right_mouse;
	Button	middle_mouse;
	Button  back_mouse;
	Button  forward_mouse;
   Button  last_button;

	Wheel	wheel;
	Mouse	mouse;

	b32 window_should_resize;
	b32 application_should_stop;
}PolledEvents;

PolledEvents poll_events(Arena *arena, Event *event_ring_buffer);

