

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
	

}Camera;
