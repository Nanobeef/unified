
PolledEvents last_polled_events = {0};

void press_button(Arena *arena, Button *b, u64 time, ButtonEventType action)
{
	if(b->previous)
	{
		Button *p = b->previous;
		b->previous = arena_push(arena, 0, sizeof(Button));
		memcpy(b->previous, b, sizeof(Button));
		b->previous->previous = p;
	}
	else
	{
		b->previous = (Button*)1;
	}
	if(action == KEYBOARD_PRESS)
	{
		b->pressed = true;
		b->released = false;
		b->press_time = time;
	}
	else
	{
		b->pressed = false;
		b->released = true;
		b->release_time = time;
	}
	b->action_time = time;
}

void press_key(Arena *arena, Button *b, u64 time, KeyboardEventType action)
{
	press_button(arena, b, time, (ButtonEventType)action);
}

void press_mouse_button(Arena *arena, Button *b, u64 time, MouseEventType action)
{
	press_button(arena, b, time, (ButtonEventType)action);
}

void move_wheel(Arena *arena, Wheel *w, u64 time, f64 val)
{
	if(w->velocity != 0.0)
	{
		Wheel *p = w->previous;
		w->previous = arena_push(arena, 0, sizeof(Wheel));
		memcpy(w->previous, w, sizeof(Wheel));
		w->previous->previous = p;
	}
	w->time = time;	
	w->accum += val;
	w->velocity = val;
}

PolledEvents poll_events(Arena *arena, Event *event_ring_buffer)
{
	PolledEvents pe = last_polled_events;
	for(u32 i = 0; i < offsetof(PolledEvents, last_button) - offsetof(PolledEvents, first_button); i++)
	{
		Button *b = &pe.first_button + 1;
		b->previous = 0;
	}
	pe.window_should_resize = false;
	pe.application_should_stop = false;
	Event e;
	while(ring_buffer_pop(event_ring_buffer, &e))
	{
		switch(e.type)
		{
			case EVENT_WINDOW:{
				Window *window = e.window_pointer;
				if(window == 0)
				{
					print("Window is NULL\n"); 
					exit(0);
				}
				switch(e.window.type)
				{
				 	case WINDOW_RESIZE:{
						pe.window_should_resize = true;
						window->size = u32x2_set(e.window.width, e.window.height);
					}break;
				 	case WINDOW_MOVE:{
						window->position = u32x2_set(e.window.x, e.window.y);
					}break;
					default:
					break;
				}
			}break;
			case EVENT_MOUSE:{
				switch(e.mouse.type)
				{
					case MOUSE_PRESS:
					case MOUSE_RELEASE:
					switch(e.mouse.button)
					{
						case MOUSE_BUTTON_LEFT: press_mouse_button(arena, &pe.left_mouse, e.time, e.mouse.type); break;
						case MOUSE_BUTTON_RIGHT: press_mouse_button(arena, &pe.right_mouse, e.time, e.mouse.type); break;
						case MOUSE_BUTTON_MIDDLE: press_mouse_button(arena, &pe.middle_mouse, e.time, e.mouse.type); break;
						case MOUSE_BUTTON_BACK: press_mouse_button(arena, &pe.back_mouse, e.time, e.mouse.type); break;
						case MOUSE_BUTTON_FORWARD: press_mouse_button(arena, &pe.forward_mouse, e.time, e.mouse.type); break;
						default:break;
					}
					default:
					break;
					case MOUSE_SCROLL:
						switch(e.mouse.button)
						{
							case MOUSE_BUTTON_SCROLL_POSITIVE: move_wheel(arena, &pe.wheel, e.time, 0.5); break;
							case MOUSE_BUTTON_SCROLL_NEGATIVE: move_wheel(arena, &pe.wheel, e.time, -0.5); break;
							default:break;
						}
					case MOUSE_PINCH:
					{
						switch(e.mouse.button)
						{
							case MOUSE_BUTTON_TRACKPAD_POSITIVE: move_wheel(arena, &pe.wheel, e.time, 0.1); break;
							case MOUSE_BUTTON_TRACKPAD_NEGATIVE: move_wheel(arena, &pe.wheel, e.time, -0.1); break;
							default:break;
						}
					}
					break;
				}
			}break;;
			case EVENT_KEYBOARD:{
				switch(e.keyboard.key)
				{
					case KEY_ESCAPE:{
						press_key(arena, &pe.escape, e.time, e.keyboard.type);
						pe.application_should_stop = true;
					}break;
					case KEY_A: press_key(arena, &pe.a, e.time, e.keyboard.type); break;
					case KEY_B: press_key(arena, &pe.b, e.time, e.keyboard.type); break;
					case KEY_C: press_key(arena, &pe.c, e.time, e.keyboard.type); break;
					case KEY_D: press_key(arena, &pe.d, e.time, e.keyboard.type); break;
					case KEY_E: press_key(arena, &pe.e, e.time, e.keyboard.type); break;
					case KEY_F: press_key(arena, &pe.f, e.time, e.keyboard.type); break;
					case KEY_G: press_key(arena, &pe.g, e.time, e.keyboard.type); break;
					case KEY_H: press_key(arena, &pe.h, e.time, e.keyboard.type); break;
					case KEY_I: press_key(arena, &pe.i, e.time, e.keyboard.type); break;
					case KEY_J: press_key(arena, &pe.j, e.time, e.keyboard.type); break;
					case KEY_K: press_key(arena, &pe.k, e.time, e.keyboard.type); break;
					case KEY_L: press_key(arena, &pe.l, e.time, e.keyboard.type); break;
					case KEY_M: press_key(arena, &pe.m, e.time, e.keyboard.type); break;
					case KEY_N: press_key(arena, &pe.n, e.time, e.keyboard.type); break;
					case KEY_O: press_key(arena, &pe.o, e.time, e.keyboard.type); break;
					case KEY_P: press_key(arena, &pe.p, e.time, e.keyboard.type); break;
					case KEY_Q: press_key(arena, &pe.q, e.time, e.keyboard.type); break;
					case KEY_R: press_key(arena, &pe.r, e.time, e.keyboard.type); break;
					case KEY_S: press_key(arena, &pe.s, e.time, e.keyboard.type); break;
					case KEY_T: press_key(arena, &pe.t, e.time, e.keyboard.type); break;
					case KEY_U: press_key(arena, &pe.u, e.time, e.keyboard.type); break;
					case KEY_V: press_key(arena, &pe.v, e.time, e.keyboard.type); break;
					case KEY_W: press_key(arena, &pe.w, e.time, e.keyboard.type); break;
					case KEY_X: press_key(arena, &pe.x, e.time, e.keyboard.type); break;
					case KEY_Y: press_key(arena, &pe.y, e.time, e.keyboard.type); break;
					case KEY_Z: press_key(arena, &pe.z, e.time, e.keyboard.type); break;
					case KEY_0: press_key(arena, &pe.n0, e.time, e.keyboard.type); break;
					case KEY_1: press_key(arena, &pe.n1, e.time, e.keyboard.type); break;
					case KEY_2: press_key(arena, &pe.n2, e.time, e.keyboard.type); break;
					case KEY_3: press_key(arena, &pe.n3, e.time, e.keyboard.type); break;
					case KEY_4: press_key(arena, &pe.n4, e.time, e.keyboard.type); break;
					case KEY_5: press_key(arena, &pe.n5, e.time, e.keyboard.type); break;
					case KEY_6: press_key(arena, &pe.n6, e.time, e.keyboard.type); break;
					case KEY_7: press_key(arena, &pe.n7, e.time, e.keyboard.type); break;
					case KEY_8: press_key(arena, &pe.n8, e.time, e.keyboard.type); break;
					case KEY_9: press_key(arena, &pe.n9, e.time, e.keyboard.type); break;

					case KEY_F1: press_key(arena, &pe.f1, e.time, e.keyboard.type); break;
					case KEY_F2: press_key(arena, &pe.f2, e.time, e.keyboard.type); break;
					case KEY_F3: press_key(arena, &pe.f3, e.time, e.keyboard.type); break;
					case KEY_F4: press_key(arena, &pe.f4, e.time, e.keyboard.type); break;
					case KEY_F5: press_key(arena, &pe.f5, e.time, e.keyboard.type); break;
					case KEY_F6: press_key(arena, &pe.f6, e.time, e.keyboard.type); break;
					case KEY_F7: press_key(arena, &pe.f7, e.time, e.keyboard.type); break;
					case KEY_F8: press_key(arena, &pe.f8, e.time, e.keyboard.type); break;
					case KEY_F9: press_key(arena, &pe.f9, e.time, e.keyboard.type); break;
					case KEY_F10: press_key(arena, &pe.f10, e.time, e.keyboard.type); break;
					case KEY_F11: press_key(arena, &pe.f11, e.time, e.keyboard.type); break;
					case KEY_F12: press_key(arena, &pe.f12, e.time, e.keyboard.type); break;

					case KEY_LEFT_SHIFT:{
						press_key(arena, &pe.left_shift, e.time, e.keyboard.type);
						press_key(arena, &pe.shift, e.time, e.keyboard.type);
					}break;
					case KEY_RIGHT_SHIFT:{
						press_key(arena, &pe.right_shift, e.time, e.keyboard.type);
						press_key(arena, &pe.shift, e.time, e.keyboard.type);
					}break;
					case KEY_LEFT_CONTROL:{
						press_key(arena, &pe.left_control, e.time, e.keyboard.type);
						press_key(arena, &pe.control, e.time, e.keyboard.type);
					}break;
					case KEY_RIGHT_CONTROL:{
						press_key(arena, &pe.right_control, e.time, e.keyboard.type);
						press_key(arena, &pe.control, e.time, e.keyboard.type);
					}break;

					case KEY_LEFT_ALT:{
						press_key(arena, &pe.left_alt, e.time, e.keyboard.type);
						press_key(arena, &pe.alt, e.time, e.keyboard.type);
					}break;
					case KEY_RIGHT_ALT:{
						press_key(arena, &pe.right_alt, e.time, e.keyboard.type);
						press_key(arena, &pe.alt, e.time, e.keyboard.type);
					}break;

					case KEY_ENTER: press_key(arena, &pe.enter, e.time, e.keyboard.type); break;
					case KEY_GRAVE: press_key(arena, &pe.grave, e.time, e.keyboard.type); break;

					case KEY_LEFT: press_key(arena, &pe.left, e.time, e.keyboard.type); break;
					case KEY_RIGHT: press_key(arena, &pe.right, e.time, e.keyboard.type); break;
					case KEY_UP: press_key(arena, &pe.up, e.time, e.keyboard.type); break;
					case KEY_DOWN: press_key(arena, &pe.down, e.time, e.keyboard.type); break;
					default:
					break;
				}
			}break;
			default:
			break;
		}
	}
	last_polled_events = pe;
	return pe;
}
