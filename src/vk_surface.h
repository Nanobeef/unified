

typedef struct{
	GraphicsInstance *instance;
	VkSurfaceKHR handle;
}GraphicsSurface;

GraphicsSurface create_graphics_surface(Window *window, GraphicsInstance *instance);
void destroy_graphics_surface(GraphicsSurface surface);

