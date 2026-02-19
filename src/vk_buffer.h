


typedef struct{
	GraphicsDevice *device;
	VkBuffer handle;
	VkDeviceSize size;
	VkBufferUsageFlags usage;
	GraphicsDeviceMemory memory;
}GraphicsDeviceBuffer;

GraphicsDeviceBuffer create_graphics_device_buffer(GraphicsDeviceMemoryHeap *heap, u64 size, VkBufferUsageFlags usage);
void destroy_graphics_device_buffer(GraphicsDeviceBuffer buffer);
