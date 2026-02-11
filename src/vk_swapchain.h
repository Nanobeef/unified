


typedef struct{
	VkDeviceMemory handle;
	VkDeviceSize size;
	VkDeviceSize offset;
}GraphicsDeviceMemory;

typedef struct{
	VkImage handle;
	VkImageView view;	
	u32x2 size;
	VkFormat format;
	VkImageTiling tiling;
	VkImageSubresourceRange subresource_range;
	GraphicsDeviceMemory memory;
}GraphicsDeviceImage;

typedef struct{
	GraphicsDevice *device;
	VkSwapchainKHR handle;

	u32 image_index;
	u32 image_count;
	GraphicsDeviceImage *images;
	VkResult result;
	VkSwapchainCreateInfoKHR create_info;
}GraphicsSwapchain;

