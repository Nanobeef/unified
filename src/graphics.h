
typedef enum{
	// Create (positive)
	// Destory (negaitve)
	GRAPHICS_STAGE_NONE = 0,
	GRAPHICS_STAGE_INSTANCE,
	GRAPHICS_STAGE_DEVICE,
	GRAPHICS_STAGE_SURFACE,
	GRAPHICS_STAGE_WINDOW,
	GRAPHICS_STAGE_SWAPCHAIN,
	GRAPHICS_STAGE_PIPELINE,
	GRAPHICS_STAGE_FONT_CACHE,
	GRAPHICS_STAGE_FRAME,

	GRAPHICS_RECREATE = S32_MAX,
}GraphicsStage;



typedef struct{

	GraphicsStage stage;

	GraphicsInstance *instance;
	GraphicsDevice *device;
	Window *window;
	GraphicsSurface surface;
	GraphicsSwapchain swapchain;

	u32 frame_count;
	u64 frame_accum;
	u64 frame_index;
	u64 last_frame_index;

	u32 resize_count;
	u64 resize_accum;
	u64 resize_index;

	u64 frame_arena_size;
	u64 resize_arena_size;
	Arena **frame_arenas;
	Arena **resize_arenas;

	GraphicsSemaphore *swapchain_semaphores;
	GraphicsSemaphore *render_semaphores;
	GraphicsFence *render_fences;
	GraphicsCommandPool **render_command_pools;
	GraphicsDeviceQueue render_queue;

	VkFormat target_format;
	VkSampleCountFlags target_sample_count;

	VkImageFormatProperties target_format_properties;
	RasterizationPipelines rasterization_pipelines;
	GraphicsDeviceFontCache *font_cache;

	u64 world_vertex_buffer_size;
	u64 overlay_vertex_buffer_size;
	GraphicsDeviceVertexBuffer *world_vertex_buffers;
	GraphicsDeviceVertexBuffer *overlay_vertex_buffers;

	u32 max_swapchain_image_count;

	GraphicsDeviceImage *msaa_images;
	VkFramebuffer *framebuffers;

	GraphicsDescriptorPool *frame_descriptor_pools;

	Camera world_camera;
	FixedCamera overlay_camera;

	GraphicsQueryPool *timestamp_query_pools;
	GraphicsQueryPool *invocation_query_pools;
}Graphics;





