

typedef struct{
	f32m3 src_affine;
	f32m3 dst_affine;
	f32m3 current_affine;
	f32m3 inverse_affine;

	f32 src_zoom;
	f32 dst_zoom;
	f32 current_zoom;

	f32x2 src_pan;
	f32x2 dst_pan;
	f32x2 current_pan;

	u64 src_time;
	u64 dst_time;
	u64 current_time;
	
	f32 aspect;
	f32 zoom_sensitivity;

	u64 transition_time;
	u64 transition_start;
	u64 transition_end;
	b32 transition;
}Camera;

void update_camera(Camera *camera, PolledEvents pe, u32x2 window_size, b32 force_disable);


typedef struct{
	u32x2 pixel_size;
	f32x2 unit_pixel;

	f32x2 top_left;
	f32x2 bottom_right;
	f32x2 top_right;
	f32x2 bottom_left;

	f32x2 center;

	f32m3 affine;
}FixedCamera;

FixedCamera create_fixed_camera(u32x2 pixel_size);

