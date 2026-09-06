


void submit_command_buffers(GraphicsDeviceQueue queue, u32 wait_count, GraphicsSemaphore *wait_semaphores, u32 signal_count, GraphicsSemaphore *signal_semaphores, u32 command_buffer_count, GraphicsCommandBuffer *command_buffers, VkPipelineStageFlags *wait_stages, GraphicsFence fence);
void present_swapchain(GraphicsDeviceQueue queue, u32 wait_count, GraphicsSemaphore *semaphores, u32 swapchain_count, GraphicsSwapchain *swapchains);
