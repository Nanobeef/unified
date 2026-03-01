


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

	u32x2 screen_size_in_mm = u32x2_set(
		screen->width_in_millimeters,
		screen->height_in_millimeters
	);
	u32x2 screen_size_in_pixels = u32x2_set(
		screen->width_in_pixels,
		screen->height_in_pixels
	);

	f32 mm_per_inch = 25.4;
	f32x2 screen_dpi = f32x2_set1(96.0);
	if((screen_size_in_mm.x != 0) && (screen_size_in_mm.y != 0))
	{
		screen_dpi = f32x2_set(
			screen_size_in_pixels.x * mm_per_inch / screen_size_in_mm.x,
			screen_size_in_pixels.y * mm_per_inch / screen_size_in_mm.y
		);
	}

	xcb_visualid_t visual = 0;
	if(0)
	{

		xcb_depth_iterator_t depth_iter = xcb_screen_allowed_depths_iterator(screen);	
		while(depth_iter.rem)
		{
			if(depth_iter.data->depth == 32)
			{
				xcb_visualtype_iterator_t vis_iter = xcb_depth_visuals_iterator(depth_iter.data);
				while(vis_iter.rem)
				{
					if(vis_iter.data->_class == XCB_VISUAL_CLASS_TRUE_COLOR)
					{
						//print("%u32\n", vis_iter.data->_class);
						visual = vis_iter.data->visual_id;
						goto VISUAL_FOUND;
					}
					xcb_visualtype_next(&vis_iter);
				}
			}
			xcb_depth_next(&depth_iter);
		}
		VISUAL_FOUND:
	}

	u64 refresh_rate = 0;
	{
		xcb_randr_get_screen_resources_current_cookie_t resource_cookie = 
		xcb_randr_get_screen_resources_current(connection, screen->root);
		xcb_randr_get_screen_resources_current_reply_t *reply = 
		xcb_randr_get_screen_resources_current_reply(connection, resource_cookie, NULL);
		if(!reply)
		{
			print("Failed to get screen resources (xcb-randr)\n");
		}

		xcb_randr_output_t *outputs = xcb_randr_get_screen_resources_current_outputs(reply);
		s32 output_count = xcb_randr_get_screen_resources_current_outputs_length(reply);

		for(s32 i = 0; i < (output_count) && (refresh_rate == 0); i++)
		{
			xcb_randr_get_output_info_cookie_t out_cookie = 
			xcb_randr_get_output_info(connection, outputs[i], reply->config_timestamp);
			xcb_randr_get_output_info_reply_t *out = 
			xcb_randr_get_output_info_reply(connection, out_cookie, NULL);

			if(out && out->connection == XCB_RANDR_CONNECTION_CONNECTED && out->crtc != XCB_NONE)
			{
				xcb_randr_get_crtc_info_cookie_t crtc_cookie = 
				xcb_randr_get_crtc_info(connection, out->crtc, reply->config_timestamp);
				xcb_randr_get_crtc_info_reply_t *crtc = 
				xcb_randr_get_crtc_info_reply(connection, crtc_cookie, NULL);

				if(crtc && crtc->mode != XCB_NONE)
				{
					xcb_randr_mode_t mode_id = crtc->mode;

					xcb_randr_mode_info_iterator_t mode_iter = 
					xcb_randr_get_screen_resources_current_modes_iterator(reply);

					while(mode_iter.rem)
					{
						xcb_randr_mode_info_t *mode = mode_iter.data;
						if(mode->id == mode_id)
						{
							f64 rr =  (f64)(mode->htotal * mode->vtotal) / (f64)mode->dot_clock;
							refresh_rate = (u64)(rr * 1000000000.0);
							goto INFO_FOUND;
						}
					}
				}
			}

		}
INFO_FOUND:
	}




	xcb_colormap_t colormap = xcb_generate_id(connection);
	xcb_create_colormap(connection, XCB_COLORMAP_ALLOC_NONE, colormap, screen->root, visual);

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


	u32 value_list[] = {XCB_NONE, XCB_GRAVITY_STATIC,  event_mask};
	u32 value_mask = XCB_CW_BACK_PIXEL | XCB_CW_BIT_GRAVITY | XCB_CW_EVENT_MASK;


	u32x2 size = {1024, 1024};

	xcb_create_window(
		connection,
		XCB_COPY_FROM_PARENT,
		handle,
		screen->root,
		0,0,
		size.x, size.y,
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
		.size = size,
		.screen_size_in_mm = screen_size_in_mm,
		.screen_size_in_pixels = screen_size_in_pixels,
		.screen_dpi = screen_dpi,
		.refresh_rate = refresh_rate,
	};

	return window;
}


u32 poll_window(Window *window, Event *event_ring_buffer)
{
	xcb_generic_event_t *event;
	u32 event_count = 0;
	u64 time = get_time_ns();
	while((event = xcb_poll_for_event(window->connection)))
	{
		event_count++;
		Event e = {.time = time, .window_pointer = window};
		u32 response = event->response_type & ~0x80;
		switch(response)
		{
			case XCB_KEY_PRESS:{
			case XCB_KEY_RELEASE:
				xcb_keysym_t sym;
				if(response == XCB_KEY_PRESS)
				{
					xcb_key_press_event_t *kp = (xcb_key_press_event_t*)event;
					sym = xcb_key_symbols_get_keysym(window->key_symbols, kp->detail, 0);
					e.keyboard.type = KEYBOARD_PRESS;
				}
				else
				{
					xcb_key_release_event_t *kr = (xcb_key_release_event_t*)event;
					sym = xcb_key_symbols_get_keysym(window->key_symbols, kr->detail, 0);
					e.keyboard.type = KEYBOARD_RELEASE;
				}
				e.type = EVENT_KEYBOARD;
				switch(sym)
				{
					case XK_Escape: e.keyboard.key = KEY_ESCAPE; break;
					case XK_a: e.keyboard.key = KEY_A; break;
					case XK_b: e.keyboard.key = KEY_B; break;
					case XK_c: e.keyboard.key = KEY_C; break;
					case XK_d: e.keyboard.key = KEY_D; break;
					case XK_e: e.keyboard.key = KEY_E; break;
					case XK_f: e.keyboard.key = KEY_F; break;
					case XK_g: e.keyboard.key = KEY_G; break;
					case XK_h: e.keyboard.key = KEY_H; break;
					case XK_i: e.keyboard.key = KEY_I; break;
					case XK_j: e.keyboard.key = KEY_J; break;
					case XK_k: e.keyboard.key = KEY_K; break;
					case XK_l: e.keyboard.key = KEY_L; break;
					case XK_n: e.keyboard.key = KEY_M; break;
					case XK_m: e.keyboard.key = KEY_M; break;
					case XK_o: e.keyboard.key = KEY_O; break;
					case XK_p: e.keyboard.key = KEY_P; break;
					case XK_q: e.keyboard.key = KEY_Q; break;
					case XK_r: e.keyboard.key = KEY_R; break;
					case XK_s: e.keyboard.key = KEY_S; break;
					case XK_t: e.keyboard.key = KEY_T; break;
					case XK_u: e.keyboard.key = KEY_U; break;
					case XK_v: e.keyboard.key = KEY_V; break;
					case XK_w: e.keyboard.key = KEY_W; break;
					case XK_x: e.keyboard.key = KEY_X; break;
					case XK_y: e.keyboard.key = KEY_Y; break;
					case XK_z: e.keyboard.key = KEY_Z; break;

					case XK_0: e.keyboard.key = KEY_0; break;
					case XK_1: e.keyboard.key = KEY_1; break;
					case XK_2: e.keyboard.key = KEY_2; break;
					case XK_3: e.keyboard.key = KEY_3; break;
					case XK_4: e.keyboard.key = KEY_4; break;
					case XK_5: e.keyboard.key = KEY_5; break;
					case XK_6: e.keyboard.key = KEY_6; break;
					case XK_7: e.keyboard.key = KEY_7; break;
					case XK_8: e.keyboard.key = KEY_9; break;
					case XK_9: e.keyboard.key = KEY_9; break;

					case XK_grave: e.keyboard.key = KEY_GRAVE; break;
					case XK_Control_L: e.keyboard.key = KEY_LEFT_CONTROL; break;
					case XK_Control_R: e.keyboard.key = KEY_RIGHT_CONTROL; break;
					case XK_Shift_L: e.keyboard.key = KEY_LEFT_SHIFT; break;
					case XK_Shift_R: e.keyboard.key = KEY_RIGHT_SHIFT; break;

					case XK_Left: e.keyboard.key = KEY_LEFT; break;
					case XK_Right: e.keyboard.key = KEY_RIGHT; break;
					case XK_Up: e.keyboard.key = KEY_UP; break;
					case XK_Down: e.keyboard.key = KEY_DOWN; break;

					case XK_F1: e.keyboard.key = KEY_F1; break;
					case XK_F2: e.keyboard.key = KEY_F2; break;
					case XK_F3: e.keyboard.key = KEY_F3; break;
					case XK_F4: e.keyboard.key = KEY_F4; break;
					case XK_F5: e.keyboard.key = KEY_F5; break;
					case XK_F6: e.keyboard.key = KEY_F6; break;
					case XK_F7: e.keyboard.key = KEY_F7; break;
					case XK_F8: e.keyboard.key = KEY_F8; break;
					case XK_F9: e.keyboard.key = KEY_F9; break;
					case XK_F10: e.keyboard.key = KEY_F10; break;
					case XK_F11: e.keyboard.key = KEY_F11; break;
					case XK_F12: e.keyboard.key = KEY_F12; break;

					case XK_Super_L: e.keyboard.key = KEY_LEFT_HOME; break;
					case XK_Super_R: e.keyboard.key = KEY_RIGHT_HOME; break;

					case XK_Alt_L: e.keyboard.key = KEY_LEFT_ALT; break;
					case XK_Alt_R: e.keyboard.key = KEY_RIGHT_ALT; break;
					case XK_Return: e.keyboard.key = KEY_ENTER; break;

					default:{
						print("Unknown Key: %s32\n", sym);
						e.keyboard.key = KEY_NONE;
					};
					break;
				}
				ring_buffer_push(event_ring_buffer, e);
			}break;
			case XCB_CONFIGURE_NOTIFY:{
				xcb_configure_notify_event_t *ce = (xcb_configure_notify_event_t*)event;
				e.type = EVENT_WINDOW;
				if(window->size.x != ce->width || window->size.y != ce->height)
				{
					e.window.type = WINDOW_RESIZE;
					e.window.width = ce->width;
					e.window.height = ce->height;
					ring_buffer_push(event_ring_buffer, e);
				}
				if(window->position.x != ce->y || window->position.y != ce->x)
				{
					e.window.type = WINDOW_MOVE;
					e.window.x = ce->x;
					e.window.y = ce->y;
					ring_buffer_push(event_ring_buffer, e);
				}
			}break;
			case XCB_BUTTON_PRESS:
			case XCB_BUTTON_RELEASE:
			{
				e.type = EVENT_MOUSE;
				xcb_button_t button = 0;
				if(response == XCB_BUTTON_PRESS)
				{
					xcb_button_press_event_t *be = (xcb_button_press_event_t*)event;
					button = be->detail;
					e.mouse.type = MOUSE_PRESS;
				}
				else
				{
					xcb_button_release_event_t *be = (xcb_button_release_event_t*)event;
					button = be->detail;
					e.mouse.type = MOUSE_RELEASE;
				}
				switch(button)
				{
					case XCB_BUTTON_INDEX_1: e.mouse.button = MOUSE_BUTTON_LEFT;  break;
					case XCB_BUTTON_INDEX_2: e.mouse.button = MOUSE_BUTTON_RIGHT;  break;
					case XCB_BUTTON_INDEX_3: e.mouse.button = MOUSE_BUTTON_MIDDLE; break;
					case 8: e.mouse.button = MOUSE_BUTTON_BACK; break;
					case 9: e.mouse.button = MOUSE_BUTTON_FORWARD; break;

					case XCB_BUTTON_INDEX_4: e.mouse.button = MOUSE_BUTTON_SCROLL_POSITIVE; e.mouse.type = MOUSE_SCROLL; break;
					case XCB_BUTTON_INDEX_5: e.mouse.button = MOUSE_BUTTON_SCROLL_NEGATIVE; e.mouse.type = MOUSE_SCROLL; break;
					case 6: e.mouse.button = MOUSE_BUTTON_TRACKPAD_POSITIVE; e.mouse.type = MOUSE_PINCH; break;
					case 7: e.mouse.button = MOUSE_BUTTON_TRACKPAD_NEGATIVE; e.mouse.type = MOUSE_PINCH; break;
					default:
						print("Unknown mouse button: %u8\n", button);
					break;
				}
				if(e.mouse.type)
					ring_buffer_push(event_ring_buffer, e);

			}break;
			case XCB_MOTION_NOTIFY:{
				xcb_motion_notify_event_t *me = (xcb_motion_notify_event_t*)event;
				e.type = EVENT_MOUSE;
				e.mouse.type = MOUSE_MOVE;
				e.mouse.x = me->event_x;
				e.mouse.y = me->event_y;
				ring_buffer_push(event_ring_buffer, e);
			}break;
			case XCB_ENTER_NOTIFY:{
				xcb_enter_notify_event_t *en = (xcb_enter_notify_event_t*)event;
				e.type = EVENT_MOUSE;
				e.mouse.type = MOUSE_ENTER;
				e.mouse.x = en->event_x;
				e.mouse.y = en->event_y;
				ring_buffer_push(event_ring_buffer, e);
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
