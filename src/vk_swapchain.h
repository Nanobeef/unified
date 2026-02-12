

typedef struct{
	GraphicsDevice *device;
	VkSwapchainKHR handle;

	u32 image_index;
	u32 image_count;
	GraphicsDeviceImage *images;
	VkResult result;
	VkSwapchainCreateInfoKHR create_info;
}GraphicsSwapchain;

GraphicsSwapchain recreate_graphics_swapchain(Arena *arena, GraphicsDevice *device, VkSwapchainCreateInfoKHR info);
GraphicsSwapchain create_graphics_swapchain(Arena *arena, GraphicsSurface surface, GraphicsDevice *device);
void destroy_graphics_swapchain(GraphicsSwapchain swapchain);
u32 acquire_graphics_swapchain_image(Arena *resize_arena, GraphicsSwapchain *swapchain, GraphicsSemaphore signal_semaphore, GraphicsFence signal_fence, b32 window_resize);




