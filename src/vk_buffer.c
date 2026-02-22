
GraphicsDeviceBuffer create_graphics_device_buffer(GraphicsDeviceMemoryHeap *heap, u64 size, VkBufferUsageFlags usage)
{
	GraphicsDeviceBuffer buffer = {
		.device = heap->device, 
		.size = size, 		
		.usage = usage,
	};

	VkBufferCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
		.size = size,
		.usage = usage,
	};

	VK_ASSERT(vkCreateBuffer(heap->device->handle, &info, vkb, &buffer.handle));

	VkMemoryRequirements requirements = {0};
	vkGetBufferMemoryRequirements(heap->device->handle, buffer.handle, &requirements);

	buffer.memory = allocate_graphics_device_memory(heap, size);

	VK_ASSERT(vkBindBufferMemory(heap->device->handle, buffer.handle, buffer.memory.handle, buffer.memory.offset));

	return buffer;
}

void destroy_graphics_device_buffer(GraphicsDeviceBuffer buffer)
{
	free_graphics_device_memory(buffer.memory);
	vkDestroyBuffer(buffer.device->handle, buffer.handle, vkb);
}

