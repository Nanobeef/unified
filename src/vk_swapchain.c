

VkImageView create_graphics_swapchain_image_view(GraphicsDevice *device, VkImage image, VkFormat format)
{
	VkImageViewCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,	
		.image = image,
		.viewType = VK_IMAGE_VIEW_TYPE_2D,
		.format = format,
		.subresourceRange = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
	};
	VkImageView handle = 0;
	VK_ASSERT(vkCreateImageView(device->handle, &info, vkb, &handle));
	return handle;
}


GraphicsSwapchain recreate_graphics_swapchain(Arena *arena, GraphicsSwapchain swapchain)
{
	Scratch scratch = find_scratch(0,0,0);
	GraphicsDevice *device = swapchain.device;
	VkSwapchainCreateInfoKHR info = swapchain.create_info;

	VK_ASSERT(vkCreateSwapchainKHR(swapchain.device->handle, &info, vkb, &swapchain.handle));

	swapchain.size = u32x2_set(info.imageExtent.width, info.imageExtent.height);

	vkGetSwapchainImagesKHR(device->handle, swapchain.handle, &swapchain.image_count, 0);
	arena_push_type(scratch.arena, 0, swapchain.image_count, VkImage, images);
	vkGetSwapchainImagesKHR(device->handle, swapchain.handle, &swapchain.image_count, images);

	if(info.oldSwapchain)
	{
		vkDestroySwapchainKHR(device->handle, info.oldSwapchain, vkb);
		if(swapchain.has_image_view)
		{
			for(u32 i = 0; i < swapchain.image_count; i++)
			{
				vkDestroyImageView(device->handle, swapchain.images[i].view, vkb);
			}
		}
	}
	info.oldSwapchain = swapchain.handle;



	swapchain.images = arena_push(arena, 0, swapchain.image_count * sizeof(GraphicsDeviceImage));

	for(u32 i = 0; i < swapchain.image_count; i++)
	{
		swapchain.images[i] = (GraphicsDeviceImage){
			.handle = images[i],
			.size = u32x2_set(info.imageExtent.width, info.imageExtent.height),
			.format = info.imageFormat,
			.tiling = VK_IMAGE_TILING_OPTIMAL,
			.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT, 0,1,0,1},
		};
		if(swapchain.has_image_view)
		{
			swapchain.images[i].view = create_graphics_swapchain_image_view(device, images[i], info.imageFormat);
		}
	}
	swapchain.create_info = info;
	regress_scratch(scratch);
	return swapchain;	
}


GraphicsSwapchain create_graphics_swapchain(Arena *arena, GraphicsSurface surface, GraphicsDevice *device)
{
	Scratch scratch = find_scratch(0,0,0);

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
//		print("%u32 of %u32 %u32 in %u32\n",i ,surface_format_count, surface_formats[i].format, surface_formats[i].colorSpace);
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
	chosen_present_mode = VK_PRESENT_MODE_FIFO_KHR;

	regress_scratch(scratch);

	VkSurfaceCapabilitiesKHR surface_capabilities = {0};
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->physical.handle, surface.handle, &surface_capabilities);

	VkImageUsageFlags image_usage = VK_IMAGE_USAGE_TRANSFER_DST_BIT;

	VkSwapchainCreateInfoKHR info = {
		.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
		.surface = surface.handle,
		.minImageCount = surface_capabilities.minImageCount,
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
	GraphicsSwapchain swapchain = {.device = device, .create_info = info};
	swapchain.format = info.imageFormat;
	swapchain.size = u32x2_set(info.imageExtent.width, info.imageExtent.height);
	if(swapchain.create_info.imageUsage & (VK_IMAGE_USAGE_SAMPLED_BIT|VK_IMAGE_USAGE_STORAGE_BIT|VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT))
	{
		swapchain.has_image_view = true;	
	}
	swapchain = recreate_graphics_swapchain(arena, swapchain);
	return swapchain;
}

void destroy_graphics_swapchain(GraphicsSwapchain swapchain)
{
	if(swapchain.has_image_view)
	{
		for(u32 i = 0; i < swapchain.image_count; i++)
		{
			vkDestroyImageView(swapchain.device->handle, swapchain.images[i].view, vkb);
		}
	}
	vkDestroySwapchainKHR(swapchain.device->handle, swapchain.handle, vkb);
}

