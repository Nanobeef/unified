


Camera init_camera(void)
{
	f32 zoom = 0.5f;
	f32x2 pan = f32x2_set(0.0, 0.0);
	Camera camera = {
		.aspect = 1.0f,

		.src_pan = pan,
		.current_pan = pan,
		.dst_pan = pan,

		.src_zoom = zoom,
		.current_zoom = zoom,
		.dst_zoom = zoom,

		.zoom_sensitivity = 2.0f,
		.transition_time = 100000000,
		.transition = false,
	};


	return camera;
}

void update_camera(Camera *camera, PolledEvents pe, u32x2 window_size, b32 force_disable)
{
	camera->aspect = (f32)window_size.y / (f32)window_size.x;
	f32x2 ws = f32x2_set(window_size.x, window_size.y);

	if(pe.left_mouse.pressed && pe.mouse.moved)
	{
		f32x2 unzoomed_delta = f32x2_mul(f32x2_1div(2.0, ws), pe.mouse.pixel_delta);

		{
			f32x2 delta = f32x2_div(unzoomed_delta, f32x2_set(camera->src_zoom * camera->aspect, camera->src_zoom));
			camera->src_pan = f32x2_sub(camera->src_pan, delta);
		}
		{
			f32x2 delta = f32x2_div(unzoomed_delta, f32x2_set(camera->dst_zoom * camera->aspect, camera->dst_zoom));
			camera->dst_pan = f32x2_sub(camera->dst_pan, delta);
		}
		{
			f32x2 delta = f32x2_div(unzoomed_delta, f32x2_set(camera->current_zoom * camera->aspect, camera->current_zoom));
			camera->current_pan = f32x2_sub(camera->current_pan, delta);
		}
		camera->src_affine = f32m3_mul(
			f32m3_affine_scale(camera->src_zoom * camera->aspect, camera->src_zoom),
			f32m3_affine_translate(camera->src_pan.x, camera->src_pan.y)
		);
		camera->dst_affine = f32m3_mul(
			f32m3_affine_scale(camera->dst_zoom * camera->aspect, camera->dst_zoom),
			f32m3_affine_translate(camera->dst_pan.x, camera->dst_pan.y)
		);
		camera->current_affine = f32m3_mul(
			f32m3_affine_scale(camera->current_zoom * camera->aspect, camera->current_zoom),
			f32m3_affine_translate(camera->current_pan.x, camera->current_pan.y)
		);
	}
	if(pe.wheel.moved)
	{
		f32 v = 1.0 + pe.wheel.velocity * 0.1f * camera->zoom_sensitivity;
		f32 src_zoom = camera->current_zoom;
		f32 dst_zoom = camera->dst_zoom * v;


		f32x2 mouse = f32x2_mul(f32x2_1div(2.0, ws), pe.mouse.pixel_position);
		mouse = f32x2_sub(mouse, f32x2_set(1.0, 1.0));

		f32x2 src = f32x2_div(mouse, f32x2_set(src_zoom * camera->aspect, src_zoom));
		f32x2 dst = f32x2_div(mouse, f32x2_set(dst_zoom * camera->aspect, dst_zoom));
		f32x2 delta = f32x2_sub(dst, src);

		f32x2 dst_pan = f32x2_add(camera->current_pan, delta);

		camera->dst_pan = dst_pan;
		camera->dst_zoom = dst_zoom;
		camera->dst_affine = f32m3_mul(
			f32m3_affine_scale(camera->dst_zoom * camera->aspect, camera->dst_zoom),
			f32m3_affine_translate(camera->dst_pan.x, camera->dst_pan.y)
		);

		camera->src_zoom = camera->current_zoom;
		camera->src_pan = camera->current_pan;
		camera->src_affine = f32m3_mul(
			f32m3_affine_scale(camera->src_zoom * camera->aspect, camera->src_zoom),
			f32m3_affine_translate(camera->src_pan.x, camera->src_pan.y)
		);

		camera->transition_start = get_time_ns();
		camera->transition_end = camera->transition_start + camera->transition_time;
		camera->transition = true;
	}

	if(camera->transition)
	{
		u64 current_time = get_time_ns();
		if(current_time > camera->transition_end)
		{
			camera->transition = false;
			camera->current_affine = camera->dst_affine;
			camera->current_zoom = camera->dst_zoom;
			camera->current_pan = camera->dst_pan;
		}
		else
		{
			f64 t = (f64)(camera->transition_end - current_time) / (f64)(camera->transition_time); 
			t = 1.0 - t;
			f32 tt = lerp(t, 1.0, t);
			if(pe.mouse.moved)
			{
				f32 pan_t = 1.0 - tt;
				if(pe.left_mouse.pressed == false)
				{
					f32x2 unzoomed_delta = f32x2_mul(f32x2_1div(2.0, ws), pe.mouse.pixel_delta);
					unzoomed_delta = f32x2_mul1(unzoomed_delta, pan_t);
					{
						f32x2 delta = f32x2_div(unzoomed_delta, f32x2_set(camera->current_zoom * camera->aspect, camera->current_zoom));
						camera->current_pan = f32x2_sub(camera->current_pan, delta);
					}
					camera->current_affine = f32m3_mul(
						f32m3_affine_scale(camera->current_zoom * camera->aspect, camera->current_zoom),
						f32m3_affine_translate(camera->current_pan.x, camera->current_pan.y)
					);
					{
						f32x2 delta = f32x2_div(unzoomed_delta, f32x2_set(camera->dst_zoom * camera->aspect, camera->dst_zoom));
						camera->dst_pan = f32x2_sub(camera->dst_pan, delta);
					}
					camera->dst_affine = f32m3_mul(
						f32m3_affine_scale(camera->dst_zoom * camera->aspect, camera->dst_zoom),
						f32m3_affine_translate(camera->dst_pan.x, camera->dst_pan.y)
					);
				}
			}

			camera->current_affine = f32m3_lerp(camera->src_affine, camera->dst_affine, tt);
			camera->current_zoom = lerp(camera->src_zoom, camera->dst_zoom, tt);
			camera->current_pan = 
			f32x2_mul1(
				f32x2_mul_f32m3(
					f32x2_set(0.0, 0.0), 
					f32m3_affine_inverse(camera->current_affine)), 
					-1.0
				);
		}
	}
	camera->current_affine = f32m3_mul(
		f32m3_affine_scale(camera->current_zoom * camera->aspect, camera->current_zoom),
		f32m3_affine_translate(camera->current_pan.x, camera->current_pan.y)
	);
}
