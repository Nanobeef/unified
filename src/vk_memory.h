

typedef struct{
	GraphicsDeviceMemoryHeap *heap;
	VkDeviceMemory handle;
	VkDeviceSize size;
	VkDeviceSize offset;
	void *mapping;
}GraphicsDeviceMemory;

GraphicsDeviceMemory allocate_graphics_device_memory(GraphicsDeviceMemoryHeap *heap, u64 size);
void free_graphics_device_memory(GraphicsDeviceMemory memory);

void flush_graphics_device_memory(GraphicsDeviceMemory memory);
void invalidate_graphics_device_memory(GraphicsDeviceMemory memory);
