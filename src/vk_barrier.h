
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
