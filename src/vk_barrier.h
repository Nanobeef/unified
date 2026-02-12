
typedef struct{
	u32 memory_barrier_count;
	u32 buffer_memory_barrier_count;
	u32 image_memory_barrier_count;		

	VkMemoryBarrier *memory_barriers;
	VkBufferMemoryBarrier *buffer_memory_barriers;
	VkImageMemoryBarrier *image_memory_barriers;

	VkDependencyFlags dependency_flags;

	VkPipelineStageFlags src_stage;
	VkPipelineStageFlags dst_stage; 
}GraphicsPipelineBarrier;

void cmd_graphics_pipeline_barrier(GraphicsCommandBuffer cb, GraphicsPipelineBarrier barrier);

VkImageMemoryBarrier graphics_device_image_barrier(GraphicsDeviceImage image, VkImageLayout old_layout, VkImageLayout new_layout, VkAccessFlags src_access, VkAccessFlags dst_access);
VkImageMemoryBarrier graphics_device_image_queue_barrier(GraphicsDeviceImage image, VkImageLayout old_layout, VkImageLayout new_layout, VkAccessFlags src_access, VkAccessFlags dst_access, GraphicsDeviceQueueFamily *src_queue, GraphicsDeviceQueueFamily *dst_queue_family);

	
