
VkBool32 vulkan_debug_callback(
    VkDebugUtilsMessageSeverityFlagBitsEXT severity,
    VkDebugUtilsMessageTypeFlagsEXT type,
    const VkDebugUtilsMessengerCallbackDataEXT* data,
    void* user_data) {

	switch(severity)
	{
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:{
		current_thread()->print.terminal_color = 244;
		break;
		print("VULKAN VERBOSE:\n    %cs\n", data->pMessage);
	}break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:{
		current_thread()->print.terminal_color = 202;
		print("VULKAN WARNING:\n    %cs\n", data->pMessage);
	}break;
	case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:{
		current_thread()->print.terminal_color = 196;
		print("VULKAN ERROR:\n    %cs\n", data->pMessage);
	}break;
	default:
	break;
	}

	current_thread()->print.terminal_color = 0;

	return false;
}

#define load_vulkan_instance_function( INSTANCE , NAME ) PFN_##NAME NAME = (PFN_##NAME)vkGetInstanceProcAddr(INSTANCE, #NAME)

GraphicsInstance *create_graphics_instance(Arena *arena)
{
	GraphicsInstance *instance = arena_push(arena, 0, sizeof(GraphicsInstance));
	{
		VkApplicationInfo appinfo = {
			.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
			.apiVersion = VK_API_VERSION_1_0,
		};

		const char *layers[] = {
			"VK_LAYER_KHRONOS_validation"
		};
		const char *extensions[] = {
			"VK_EXT_debug_utils",
			"VK_KHR_surface",
			"VK_KHR_xcb_surface",
		};

		VkInstanceCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
			.pApplicationInfo = &appinfo,
			.enabledLayerCount = Arrlen(layers),
			.ppEnabledLayerNames = layers,
			.enabledExtensionCount = Arrlen(extensions),
			.ppEnabledExtensionNames = extensions,
		};
		VK_ASSERT(vkCreateInstance(&info, vkb, &instance->handle)); 
		// Accounts for the majority of the application startup time. ~38ms on AMD cards, much longer on Nvidia cards.
	}
	{
		load_vulkan_instance_function(instance->handle, vkCreateDebugUtilsMessengerEXT);
		VkDebugUtilsMessengerCreateInfoEXT info = {
			.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,	
			.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                               VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT,
    		.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                           VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
			.pfnUserCallback = vulkan_debug_callback,
			.pUserData = 0,

		};
		vkCreateDebugUtilsMessengerEXT(instance->handle, &info, vkb, &instance->debug_messenger);
	}

	return instance;
}

void destroy_graphics_instance(GraphicsInstance *instance)
{
	load_vulkan_instance_function(instance->handle, vkDestroyDebugUtilsMessengerEXT);
	vkDestroyDebugUtilsMessengerEXT(instance->handle, instance->debug_messenger, vkb);
	vkDestroyInstance(instance->handle, vkb);
}



