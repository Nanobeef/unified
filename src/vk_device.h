
typedef enum{
	INTEGRATED_GRAPHICS_DEVICE = 1024,
	DISCRETE_GRAPHICS_DEVICE,
	FASTEST_GRAPHICS_DEVICE,
	SLOWEST_GRAPHICS_DEVICE,
}GraphicsDeviceTypeFlags;
typedef u32 GraphicsDeviceType;

typedef struct{
	VkPhysicalDevice handle;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceMemoryProperties memory_properties;
	u32 queue_family_count;
	VkQueueFamilyProperties *queue_family_properties;

	GraphicsDeviceType type_request;
	u32 physical_device_index;
}PhysicalGraphicsDevice;

struct GraphicsDevice;

typedef struct{
	struct GraphicsDevice *device;
	VkQueue handle;
	u32 family_index;
	u32 index;
}GraphicsDeviceQueue;

typedef struct{
	struct GraphicsDevice *device;
	u32 family_index;
	u32 queue_count;
	GraphicsDeviceQueue *queues;
}GraphicsDeviceQueueFamily;

typedef struct DeviceMemoryHeap{
	struct GraphicsDevice *device;
	VkMemoryPropertyFlags property_flags;
	u32 heap_index;
	u32 type_index;
	u64 size;
	struct DeviceMemoryHeap *backup_chain;
}GraphicsDeviceMemoryHeap;

typedef struct GraphicsDevice{
	GraphicsInstance *instance;
	VkDevice handle;	
	PhysicalGraphicsDevice physical;

	u32 queue_family_count;
	GraphicsDeviceQueueFamily *queue_families;

	GraphicsDeviceQueueFamily *main_queue_family;
	GraphicsDeviceQueueFamily *async_queue_family;
	GraphicsDeviceQueueFamily *transfer_queue_family;

	u32 memory_heap_count;
	GraphicsDeviceMemoryHeap *memory_heaps;

	// Memory types can share heaps, but this is a start.
	GraphicsDeviceMemoryHeap *host_coherent_heap;
	GraphicsDeviceMemoryHeap *host_cached_heap;
	GraphicsDeviceMemoryHeap *host_and_device_heap;
	GraphicsDeviceMemoryHeap *device_heap;
}GraphicsDevice;


GraphicsDevice *create_graphics_device(Arena* arena, GraphicsInstance *instance, GraphicsDeviceType type_request);
void destroy_graphics_device(GraphicsDevice *device);
