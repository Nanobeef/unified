
typedef struct{
	VkAccessFlags src_access, dst_access;
}GraphicsMemoryBarrier;

typedef struct{
	GraphicsDeviceBuffer buffer;	
	u64 offset, size;
	VkAccessFlags src_access, dst_access;
	GraphicsDeviceQueueFamily *src_queue_family, *dst_queue_family;
}GraphicsBufferMemoryBarrier;

typedef struct{
	GraphicsDeviceImage image;
	VkImageSubresourceRange subresource_range;
	VkAccessFlags src_access, dst_access;
	VkImageLayout old_layout, new_layout;
	GraphicsDeviceQueueFamily *src_queue_family, *dst_queue_family;
}GraphicsImageMemoryBarrier;

typedef struct{
	u32 memory_barrier_count;
	u32 buffer_memory_barrier_count;
	u32 image_memory_barrier_count;		

	GraphicsMemoryBarrier *memory_barriers;
	GraphicsBufferMemoryBarrier *buffer_memory_barriers;
	GraphicsImageMemoryBarrier *image_memory_barriers;

	VkDependencyFlags dependency_flags;

	VkPipelineStageFlags src_stage;
	VkPipelineStageFlags dst_stage; 
}GraphicsPipelineBarrier;

void cmd_graphics_pipeline_barrier(GraphicsCommandBuffer cb, GraphicsPipelineBarrier barrier);

GraphicsEvent create_graphics_event(GraphicsDevice *device);
GraphicsEvent* create_graphics_events(Arena *arena, GraphicsDevice *device, u32 count);
void destroy_graphics_event(GraphicsEvent event);
void destroy_graphics_events(u32 count, GraphicsEvent *events);
VkResult set_graphics_event(GraphicsEvent event);
VkResult reset_graphics_event(GraphicsEvent event);
VkResult get_graphics_event_status(GraphicsEvent event);
void cmd_set_graphics_event(GraphicsCommandBuffer cb, GraphicsEvent event, VkPipelineStageFlags src_stage);
void cmd_reset_graphics_event(GraphicsCommandBuffer cb, GraphicsEvent event, VkPipelineStageFlags src_stage);
void cmd_wait_graphics_events(GraphicsCommandBuffer cb, u32 event_count, GraphicsEvent *events, GraphicsPipelineBarrier barrier);
