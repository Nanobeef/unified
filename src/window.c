


Window *create_window(Arena *arena)
{
	xcb_connection_t *connection = xcb_connect(NULL, NULL);
	if(xcb_connection_has_error(connection))
	{
		print("Error: Cannot connect to X server (xcb)\n");
		return 0;
	}

	const xcb_setup_t *setup = xcb_get_setup(connection);
	xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
	xcb_screen_t *screen = iter.data;


	xcb_window_t handle = xcb_generate_id(connection);

	u32 event_mask = 
		XCB_EVENT_MASK_EXPOSURE |
		XCB_EVENT_MASK_KEY_PRESS |
		XCB_EVENT_MASK_KEY_RELEASE |
		XCB_EVENT_MASK_BUTTON_PRESS |
		XCB_EVENT_MASK_BUTTON_RELEASE |
		XCB_EVENT_MASK_POINTER_MOTION |
		XCB_EVENT_MASK_LEAVE_WINDOW |
		XCB_EVENT_MASK_ENTER_WINDOW |
		XCB_EVENT_MASK_STRUCTURE_NOTIFY |
		XCB_EVENT_MASK_FOCUS_CHANGE ;



	u32 value_list[] = {screen->black_pixel, event_mask};
	u32 value_mask = XCB_CW_BACK_PIXEL | XCB_CW_EVENT_MASK;

	xcb_create_window(
		connection,
		XCB_COPY_FROM_PARENT,
		handle,
		screen->root,
		0,0,
		1024, 1024,
		1,
		XCB_WINDOW_CLASS_INPUT_OUTPUT,
		screen->root_visual,
		value_mask, value_list
	);


	xcb_key_symbols_t *key_symbols = xcb_key_symbols_alloc(connection);

	xcb_map_window(connection, handle);
	xcb_flush(connection);

	Window *window = arena_push(arena, 0, sizeof(Window));
	*window = (Window){
		.connection = connection,
		.handle = handle,
		.key_symbols = key_symbols,
	};

	return window;
}


u32 poll_window(Window *window, Event *event_ring_buffer)
{
	xcb_generic_event_t *event;
	u32 event_count = 0;
	while((event = xcb_poll_for_event(window->connection)))
	{
		event_count++;
		switch(event->response_type & ~0x80)
		{
			case XCB_KEY_PRESS:{
			case XCB_KEY_RELEASE:
				xcb_key_press_event_t *kp = (xcb_key_press_event_t*)event;
				xcb_keysym_t sym = xcb_key_symbols_get_keysym(window->key_symbols, kp->detail, 0);
				Event dst = {0};
				dst.type = EVENT_KEYBOARD;
				dst.keyboard.type = XCB_KEY_PRESS ? KEYBOARD_PRESS : KEYBOARD_RELEASE;
				if(sym == XK_Escape)
				{
					dst.keyboard.key = KEY_ESCAPE;
					ring_buffer_push(event_ring_buffer, dst);
				}
			}break;
			case XCB_CONFIGURE_NOTIFY:{
				xcb_configure_notify_event_t *ce = (xcb_configure_notify_event_t*)event;
				Event dst = {0};
				dst.type = EVENT_WINDOW;
				dst.window.type = WINDOW_RESIZE;
				dst.window.width = ce->width;
				dst.window.height = ce->height;
				ring_buffer_push(event_ring_buffer, dst);
			}break;


			default:
			break;
		}
		free(event);
	}
	return event_count;
}

void destroy_window(Window *window)
{
	xcb_disconnect(window->connection);
}
