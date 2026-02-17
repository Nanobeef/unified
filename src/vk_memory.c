
GraphicsDeviceMemory allocate_graphics_device_memory(GraphicsDeviceMemoryHeap *heap, u64 size)
{
	GraphicsDeviceMemory memory = {.heap = heap, .size = size, .offset = 0};
	VkMemoryAllocateInfo info = {
		.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
		.allocationSize = size,
		.memoryTypeIndex = heap->type_index,
	};
	VkResult result = vkAllocateMemory(heap->device->handle, &info, vkb, &memory.handle);
	switch(result)
	{
		case VK_ERROR_OUT_OF_HOST_MEMORY:
			print("Out of HOST memory!!!\n");
			exit(0);
			break;
		case VK_ERROR_OUT_OF_DEVICE_MEMORY:
			memory = allocate_graphics_device_memory(heap->device->host_cached_heap, size);
			break;
		case VK_SUCCESS:
		default:
		break;
	}

	if(heap->property_flags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
	{
		VK_ASSERT(vkMapMemory(heap->device->handle, memory.handle, memory.offset, memory.size, 0, &memory.mapping));
	}
	return memory;
}

void free_graphics_device_memory(GraphicsDeviceMemory memory)
{
	if(memory.handle)
		vkFreeMemory(memory.heap->device->handle, memory.handle, vkb);
}
