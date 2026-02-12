
GraphicsDeviceImage create_graphics_device_image_explicit(GraphicsDeviceMemoryHeap *heap, u32x2 size, VkFormat format, VkImageUsageFlags usage, VkImageTiling tiling, VkSampleCountFlags sample_count)
{
	GraphicsDevice *device = heap->device;
	GraphicsDeviceImage image = {
		.device = device,
		.size = size,
		.format = format,
		.tiling = tiling,
		.usage = usage,
		.sample_count = sample_count,
		.subresource_range = {VK_IMAGE_ASPECT_COLOR_BIT,0,1,0,1},
	};
	{
		VkImageCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			.imageType = VK_IMAGE_TYPE_2D,
			.format = format,
			.extent = (VkExtent3D){size.x, size.y, 1},
			.mipLevels = 1,
			.arrayLayers = 1,
			.samples = sample_count,
			.tiling = tiling,
			.usage = usage,
			.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
		};
		VK_ASSERT(vkCreateImage(device->handle, &info, vkb, &image.handle));
	}

	VkMemoryRequirements requirements = {0};
	vkGetImageMemoryRequirements(device->handle, image.handle, &requirements);
	image.memory = allocate_graphics_device_memory(heap, requirements.size);
	VK_ASSERT(vkBindImageMemory(device->handle, image.handle, image.memory.handle, image.memory.offset));

	{
		VkImageViewCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,	
			.image = image.handle,
			.viewType = VK_IMAGE_VIEW_TYPE_2D,
			.format = format,
			.subresourceRange = image.subresource_range,
		};
		VK_ASSERT(vkCreateImageView(device->handle, &info, vkb, &image.view));
	}

	return image;
}

GraphicsDeviceImage create_graphics_device_image(GraphicsDevice *device, u32x2 size, VkFormat format, VkImageUsageFlags usage)
{
	return create_graphics_device_image_explicit(device->device_heap, size, format, usage, VK_IMAGE_TILING_OPTIMAL, VK_SAMPLE_COUNT_1_BIT);
}


void destroy_graphics_device_image(GraphicsDeviceImage image)
{
	free_graphics_device_memory(image.memory);
	vkDestroyImageView(image.device->handle, image.view, vkb);
	vkDestroyImage(image.device->handle, image.handle, vkb);
}

