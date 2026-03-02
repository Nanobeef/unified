



typedef struct{
	b32 msaa_enable;
}Settings;

Settings settings = {};


typedef struct{

	u64 startup_time;

	u64 window_create_time;
	u64 vk_instance_create_time;
	u64 vk_device_create_time;
	u64 vk_surface_create_time;
	u64 vk_swapchain_create_time;

	u64 rasterization_pipelines_create_time;
	u64 glyph_cache_create_time;

	u64 frame_time;
	u64 desired_frame_time;
	u64 frame_sleep_time;
	u64 frame_elapsed_time;
	u64 poll_time;
	u64 resize_time;
	u64 draw_time;
	u64 font_resolve_time;
	u64 cb_wait_time;
	u64 cb_record_time;

	u64 update_time;

	u64 cleanup_time;
}Tidings;
Tidings tidings = {};


static u64 mark_time(void) {return (current_thread()->marked_time = get_epoch_ns());}
static u64 end_time(u64 *time) {
	u64 current_time = mark_time();
	*time = current_time - *time;
	return current_time;
};

static u64 record_time(void) 
{
	Thread *thread = current_thread(); 
	u64 current_time = get_epoch_ns(); 
	thread->recorded_time = current_time - thread->marked_time; 
	thread->marked_time = current_time; 
	return thread->recorded_time; 
}



