

VkImageView create_graphics_swapchain_image_view(GraphicsDevice *device, VkImage image, VkFormat format)
{
	VkImageViewCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,	
		.image = image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = format,
		.subresourceRange = {1,0,1,0, VK_IMAGE_ASPECT_COLOR_BIT},
	};
	VkImageView handle = 0;
	VK_ASSERT(vkCreateImageView(device->handle, &info, vkb, &handle));
	return handle;
}



GraphicsSwapchain create_graphics_swapchain(Arena *arena, GraphicsSurface surface, GraphicsDevice *device)
{
	Scratch scratch = find_scratch(0,0,0);
	GraphicsSwapchain swapchain = {.device = device};

	VkBool32 supported = false;
	vkGetPhysicalDeviceSurfaceSupportKHR(device->physical.handle, device->main_queue_family->family_index, surface.handle, &supported);
	if(supported == false)
	{
		print("This physical device does not support a graphics surface\n");
		regress_scratch(scratch);
		return (GraphicsSwapchain){0};
	}

	u32 surface_format_count = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device->physical.handle, surface.handle, &surface_format_count, 0);
	arena_push_type(scratch.arena, 0, surface_format_count, VkSurfaceFormatKHR, surface_formats);
	vkGetPhysicalDeviceSurfaceFormatsKHR(device->physical.handle, surface.handle, &surface_format_count, surface_formats);
	VkSurfaceFormatKHR chosen_surface_format = surface_formats[0];
	for(u32 i = 0; i < surface_format_count; i++)
	{
		if(
			surface_formats[i].format == VK_FORMAT_R8G8B8A8_SRGB || 
			surface_formats[i].format == VK_FORMAT_B8G8R8A8_SRGB
		)
		{
			chosen_surface_format = surface_formats[i];
		}
	}

	u32 present_mode_count = 0;
	vkGetPhysicalDeviceSurfacePresentModesKHR(device->physical.handle, surface.handle, &present_mode_count, 0);
	arena_push_type(scratch.arena, 0, present_mode_count, VkPresentModeKHR, present_modes);
	vkGetPhysicalDeviceSurfacePresentModesKHR(device->physical.handle, surface.handle, &present_mode_count, present_modes);
	VkPresentModeKHR chosen_present_mode = present_modes[0];
	for(u32 i = 0; i < present_mode_count; i++)
	{
		if(present_modes[i] == VK_PRESENT_MODE_FIFO_KHR)
		{
			chosen_present_mode = present_modes[i];	
		}
	}

	VkSurfaceCapabilitiesKHR surface_capabilities = {0};
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->physical.handle, surface.handle, &surface_capabilities);


	VkImageUsageFlags image_usage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;

	VkSwapchainCreateInfoKHR info = {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = surface.handle,
		.minImageCount = 2,
		.imageFormat = chosen_surface_format.format,
		.imageColorSpace = chosen_surface_format.colorSpace,
		.imageExtent = surface_capabilities.minImageExtent,
		.imageArrayLayers = 1,
		.imageUsage = image_usage,
		.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
		.preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,
		.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
		.presentMode = chosen_present_mode,
		.clipped = VK_FALSE,
	};
	VK_ASSERT(vkCreateSwapchainKHR(device->handle, &info, vkb, &swapchain.handle));

	vkGetSwapchainImagesKHR(device->handle, swapchain.handle, &swapchain.image_count, 0);
	arena_push_type(scratch.arena, 0, swapchain.image_count, VkImage, images);
	vkGetSwapchainImagesKHR(device->handle, swapchain.handle, &swapchain.image_count, images);

	swapchain.images = arena_push(arena, 0, swapchain.image_count * sizeof(GraphicsDeviceImage));

	for(u32 i = 0; i < swapchain.image_count; i++)
	{
		swapchain.images[i] = (GraphicsDeviceImage){
			.handle = images[i],
			.view = create_graphics_swapchain_image_view(device, images[i], info.imageFormat),
			.size = u32x2_set(info.imageExtent.width, info.imageExtent.height),
			.format = info.imageFormat,
			.tiling = VK_IMAGE_TILING_OPTIMAL,
			.subresource_range = {0,1,0,1, VK_IMAGE_ASPECT_COLOR_BIT},
		};
	}




	swapchain.create_info = info;


	regress_scratch(scratch);
	return swapchain;	
}

void destroy_graphics_swapchain(GraphicsSwapchain swapchain)
{
	for(u32 i = 0; i < swapchain.image_count; i++)
	{
		vkDestroyImageView(swapchain.device->handle, swapchain.images[i].view, vkb);
	}
	vkDestroySwapchainKHR(swapchain.device->handle, swapchain.handle, vkb);
}
