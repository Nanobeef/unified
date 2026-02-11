


struct GraphicsCommandBuffer;

typedef struct{
	GraphicsDeviceQueueFamily *queue_family;
	VkCommandPool handle;		
	u32 command_buffer_count;
	struct GraphicsCommandBuffer *command_buffers;
}GraphicsCommandPool;

typedef struct GraphicsCommandBuffer{
	GraphicsCommandPool *pool;	
	VkCommandBuffer handle;
}GraphicsCommandBuffer;

GraphicsCommandPool* create_graphics_command_pool(Arena *arena, GraphicsDeviceQueueFamily *queue_family, u32 command_buffer_count);
void destroy_graphics_command_pool(GraphicsCommandPool *pool);
