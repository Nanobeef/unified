


typedef struct{
	xcb_connection_t *connection;
	xcb_window_t handle;
	xcb_key_symbols_t *key_symbols;

	u32x2 size;
	u32x2 position;

	u32x2 screen_size_in_mm;
	u32x2 screen_size_in_pixels;
	f32x2 screen_dpi;


}Window;

Window *create_window(Arena *arena);
void destroy_window(Window *window);
u32 poll_window(Window *window, Event *event_ring_buffer);
