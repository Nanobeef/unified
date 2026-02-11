


typedef struct{
	xcb_connection_t *connection;
	xcb_window_t handle;
	xcb_key_symbols_t *key_symbols;
}Window;

Window *create_window(Arena *arena);
void destroy_window(Window *window);
u32 poll_window(Window *window, Event *event_ring_buffer);
