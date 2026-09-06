


GraphicsSurface create_graphics_surface(Window *window, GraphicsInstance *instance)
{
	GraphicsSurface surface = {.instance = instance};	
	VkXcbSurfaceCreateInfoKHR info = {
		.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR,
		.connection = window->connection,
		.window = window->handle,
	};
	VK_ASSERT(vkCreateXcbSurfaceKHR(instance->handle, &info, vkb, &surface.handle));
	return surface;
}

void destroy_graphics_surface(GraphicsSurface surface)
{
	vkDestroySurfaceKHR(surface.instance->handle, surface.handle, vkb);
}
