

typedef struct{
	GraphicsDevice *device;
	VkSwapchainKHR handle;

	u32x2 size;
	u32 image_index;
	u32 image_count;
	GraphicsDeviceImage *images;
	VkResult result;
	VkSwapchainCreateInfoKHR create_info;
}GraphicsSwapchain;

GraphicsSwapchain recreate_graphics_swapchain(Arena *arena, GraphicsSwapchain swapchain);
GraphicsSwapchain create_graphics_swapchain(Arena *arena, GraphicsSurface surface, GraphicsDevice *device);
void destroy_graphics_swapchain(GraphicsSwapchain swapchain);
