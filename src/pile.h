
typedef enum {
	PROCESS_PILE = 1,
	SURFACE_PILE,
	GRAPHICS_PILE,
	AUDIO_PILE,
	SIM_PILE,
	PILE_TYPE_COUNT,
}PileType;

typedef enum{
	PROCESS_PILE_INIT = 1,

	SURFACE_PILE_CREATE_WINDOW,
	SURFACE_PILE_CREATE_SURFACE,


	AUDIO_PILE_CREATE_DEVICE,

	PILE_STAGE_COUNT,
}PileStage;


typedef enum{
	GRAPHICS_PILE_CREATE_INSTANCE,
	GRAPHICS_PILE_CREATE_DEVICE,
	GRAPHICS_PILE_CREATE_PIPELINES,
	GRAPHICS_PILE_FONT_CACHE,
	GRAPHICS_PILE_CREATE_FRAME,
	GRAPHICS_PILE_CREATE_SWAPCHAIN,
}GraphicsPileStage;


typedef struct{
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
}GraphicsPile;

typedef struct{
	Window *window;
	GraphicsSurface surface;
	Arena *arena;
}SurfacePile;

typedef struct{
	Arena *arena;
}SimPile;

typedef struct{
	Arena *arena;
}ProcessPile;

typedef struct{
	AudioDevice *device;
}AudioPile;

typedef struct{
	PileStage dependent;
	PileType type;
	PileStage stage;
	b32 is_concurrent;
}PileDependency;

typedef struct{
	PileStage current_stage;
	u32 count;
	PileDependency *data;
}PileDependencyArray;

typedef struct{
	Scratch arena_marker;
	u64 previous_stage_elapsed_time;
}PileMarker;

PileMarker pile_markers[PILE_STAGE_COUNT];
PileDependencyArray pile_dependency_arrays[PILE_TYPE_COUNT];
PileStage pile_stage_ranges[PILE_TYPE_COUNT][2];

ProcessPile process;
SurfacePile surface;
GraphicsPile graphics;
AudioPile audio;

SimPile sim;


void pile_init();
void execute_pile();
void execute_pile_async();
















