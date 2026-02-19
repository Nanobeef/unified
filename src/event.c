
PolledEvents last_polled_events = {0};

void press_key(Arena *arena, Button *b, u64 time, KeyboardEventType action)
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

PolledEvents poll_events(Arena *arena, Event *event_ring_buffer)
{
	PolledEvents pe = last_polled_events;
	for(u32 i = 0; i < offsetof(PolledEvents, last_button) - offsetof(PolledEvents, first_button); i++)
	{
		Button *b = &pe.first_button + 1;
		b->previous = 0;
	}
	b32 should_resize = false;
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
			case EVENT_KEYBOARD:{
				switch(e.keyboard.key)
				{
					case KEY_ESCAPE:{
						press_key(arena, &pe.escape, e.time, e.keyboard.type);
						pe.application_should_stop = true;
					}break;
					case KEY_A:{
						
					}break;
					default:
					break;
				}
				if(e.keyboard.key == KEY_ESCAPE)
				{
				}
			}break;
			default:
			break;
		}
	}
	return pe;
}
