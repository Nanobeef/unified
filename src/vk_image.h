


typedef struct{
	GraphicsDevice *device;
	VkImage handle;
	VkImageView view;	
	u32x2 size;
	VkFormat format;
	VkImageTiling tiling;
	VkImageUsageFlags usage;
	VkSampleCountFlags sample_count;
	VkImageSubresourceRange subresource_range;
	GraphicsDeviceMemory memory;
}GraphicsDeviceImage;

GraphicsDeviceImage create_graphics_device_image_explicit(GraphicsDeviceMemoryHeap *heap, u32x2 size, VkFormat format, VkImageUsageFlags usage, VkImageTiling tiling, VkSampleCountFlags sample_count);
GraphicsDeviceImage create_graphics_device_image(GraphicsDevice *device, u32x2 size, VkFormat format, VkImageUsageFlags usage);
void destroy_graphics_device_image(GraphicsDeviceImage image);
