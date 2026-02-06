

#define VK_ASSERT( call )\
{\
	if((call) != VK_SUCCESS)\
	{\
		printf("VK_ASSERT %d\n", (call));\
		exit(80085);\
	}\
}

VkAllocationCallbacks* vkb = 0;

typedef struct{
	VkInstance handle;	
	VkDebugUtilsMessengerEXT debug_messenger;
}GraphicsInstance;

GraphicsInstance *create_graphics_instance(Arena *arena);
void destroy_graphics_instance(GraphicsInstance *instance);



