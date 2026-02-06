
typedef struct{
	VkPhysicalDevice handle;
	VkPhysicalDeviceProperties properties;
}PhysicalGraphicsDevice;

typedef struct{
	VkDevice handle;	
	PhysicalGraphicsDevice physical;
}GraphicsDevice;


typedef enum{
	INTEGRATED_GRAPHICS_DEVICE,
	DISCRETE_GRAPHICS_DEVICE,
	FASTEST_GRAHPICS_DEVICE,
	SLOWEST_GRAPHICS_DEVICE,
}GraphicsDeviceType;

typedef enum{
	GRAPHICS_DEVICE_GRAPHICS_QUEUES = (1<<0),
	GRAPHICS_DEVICE_COMPUTE_QUEUES = (1<<1),
	GRAPHICS_DEVICE_TRANSFER_QUEUES = (1<<2),
	GRAPHICS_DEVICE_ASYNC_COMPUTE_QUEUES = (1<<3),
	GRAPHICS_DEVICE_ALL_QUEUES = (1<<10),
	GRAPHICS_DEVICE_ONE_OF_EACH_QUEUE = (1<<11),
}GraphicsDeviceQueueType;

GraphicsDevice *create_graphics_device(Arena* arena, GraphicsDeviceType type_request);
void destroy_graphics_device(GraphicsDevice *device);

