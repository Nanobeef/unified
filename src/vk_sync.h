
typedef struct{
	GraphicsDevice *device;
	VkFence handle;
}GraphicsFence;

typedef struct{
	GraphicsDevice *device;
	VkSemaphore handle;
}GraphicsSemaphore;

typedef struct{
	GraphicsDevice *device;
	VkEvent handle;
}GraphicsEvent;

GraphicsFence create_graphics_fence(GraphicsDevice *device, b32 signaled);
GraphicsFence* create_graphics_fences(Arena *arena, GraphicsDevice *device, u32 count, b32 signaled);
void destroy_graphics_fence(GraphicsFence fence);
void destroy_graphics_fences(u32 count, GraphicsFence *fences);
void wait_for_graphics_fence(GraphicsFence fence);
void wait_for_graphics_fences(u32 count, GraphicsFence *fences);

GraphicsSemaphore create_graphics_semaphore(GraphicsDevice *device);
GraphicsSemaphore* create_graphics_semaphores(Arena *arena, GraphicsDevice *device, u32 count);
void destroy_graphics_semaphore(GraphicsSemaphore semaphore);
void destroy_graphics_semaphores(u32 count, GraphicsSemaphore *semaphores);
