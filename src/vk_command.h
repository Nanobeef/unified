


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
GraphicsCommandPool** create_graphics_command_pools(Arena *arena, GraphicsDeviceQueueFamily *queue_family, u32 command_pool_count, u32 command_buffer_count);
void destroy_graphics_command_pools(u32 command_pool_count, GraphicsCommandPool **pools);

GraphicsCommandPool* reset_graphics_command_pool(GraphicsCommandPool *pool, b32 realloc_buffers);

GraphicsCommandBuffer begin_graphics_command_buffer(GraphicsCommandBuffer cb);
GraphicsCommandBuffer end_graphics_command_buffer(GraphicsCommandBuffer cb);
