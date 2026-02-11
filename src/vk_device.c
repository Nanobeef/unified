




PhysicalGraphicsDevice pick_physical_graphics_device(Arena *arena, GraphicsInstance *instance, GraphicsDeviceType type_request)
{
	PhysicalGraphicsDevice chosen_device = {0};

	Scratch scratch = find_scratch(0,0,0);

	u32 chosen_index = 0;
	u32 physical_device_count = 0;
	vkEnumeratePhysicalDevices(instance->handle, &physical_device_count, 0);

	if(physical_device_count == 0)
	{
		print("There are not GPU drivers available!?\n");
		return chosen_device;
	}


	arena_push_type(scratch.arena, 0, physical_device_count, PhysicalGraphicsDevice, physical_devices);
	arena_push_type(scratch.arena, 0, physical_device_count, VkPhysicalDevice, physical_device_handles);
	vkEnumeratePhysicalDevices(instance->handle, &physical_device_count, physical_device_handles);
	for(u32 i = 0; i < physical_device_count; i++)
	{
		physical_devices[i].handle = physical_device_handles[i];
		vkGetPhysicalDeviceProperties(physical_devices[i].handle, &physical_devices[i].properties);
		vkGetPhysicalDeviceMemoryProperties(physical_devices[i].handle, &physical_devices[i].memory_properties);
		vkGetPhysicalDeviceQueueFamilyProperties(physical_devices[i].handle, &physical_devices[i].queue_family_count, 0);
		physical_devices[i].queue_family_properties = arena_push(scratch.arena, 0, physical_devices[i].queue_family_count * sizeof(VkQueueFamilyProperties));
		vkGetPhysicalDeviceQueueFamilyProperties(physical_devices[i].handle, &physical_devices[i].queue_family_count, physical_devices[i].queue_family_properties);
	}



	if(physical_device_count > INTEGRATED_GRAPHICS_DEVICE)
	{
		print("Why are there 1024 GPUS?");
		chosen_index = 0;
		goto INDEX_CHOSEN;
	}
	if(type_request < physical_device_count)
	{
		chosen_index = (u32)type_request;
		goto INDEX_CHOSEN;
	}
	else
	{
		switch(type_request)
		{
		case INTEGRATED_GRAPHICS_DEVICE:{
			for(u32 i = 0; i < physical_device_count; i++)
			{
				if(physical_devices[i].properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
				{
					chosen_index = 0;
				}
			}
		}break;
		case DISCRETE_GRAPHICS_DEVICE:{
			for(u32 i = 0; i < physical_device_count; i++)
			{
				if(physical_devices[i].properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
				{
					chosen_index = 0;
				}
			}
		}break;
		case FASTEST_GRAPHICS_DEVICE:{
			u32 max_index = 0;
			u64 max_device_memory = 0;
			for(u32 i = 0; i < physical_device_count; i++)
			{
				u64 device_memory = physical_devices[i].memory_properties.memoryHeaps[physical_devices[i].memory_properties.memoryTypes[0].heapIndex].size;
				if((device_memory > max_device_memory) && (physical_devices[i].properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_CPU))
				{
					max_index = i;
					max_device_memory = device_memory;
				}
			}
			chosen_index = max_index;
		}break;
		case SLOWEST_GRAPHICS_DEVICE:{
			u32 min_index = 0;
			u64 min_device_memory = U64_MAX;
			for(u32 i = 0; i < physical_device_count; i++)
			{
				u64 device_memory = physical_devices[i].memory_properties.memoryHeaps[physical_devices[i].memory_properties.memoryTypes[0].heapIndex].size;
				if((device_memory < min_device_memory) && (physical_devices[i].properties.deviceType != VK_PHYSICAL_DEVICE_TYPE_CPU))
				{
					min_index = i;
					min_device_memory = device_memory;
				}
			}
			chosen_index = min_index;

		}break;

		default:{
			chosen_index = 0;
		}break;
		}
	}

INDEX_CHOSEN:

	chosen_device = physical_devices[chosen_index];	
	{
		u32 size = sizeof(VkQueueFamilyProperties) * chosen_device.queue_family_count;
		chosen_device.queue_family_properties = arena_push(arena, 0, size);
		memcpy(chosen_device.queue_family_properties, physical_devices[chosen_index].queue_family_properties, size);
	}

	regress_scratch(scratch);
	return chosen_device;
}
	

GraphicsDevice *create_graphics_device(Arena* arena, GraphicsInstance *instance, GraphicsDeviceType type_request)
{
	GraphicsDevice *device = arena_push(arena, true, sizeof(GraphicsDevice));
	device->instance = instance;
	Scratch scratch = find_scratch(0,0,0);
	device->physical = pick_physical_graphics_device(arena, instance, type_request);


	u32 queue_family_count = device->physical.queue_family_count;
	VkDeviceQueueCreateInfo queue_create_infos[queue_family_count];
	f32 *priorities[queue_family_count];

	for(u32 i = 0; i < queue_family_count; i++)
	{
		u32 queue_count = device->physical.queue_family_properties[i].queueCount;
		priorities[i] = arena_push(scratch.arena, 0, queue_count * sizeof(f32));
		for(u32 j = 0; j < queue_count; j++){priorities[i][j] = 1.0f;};
		queue_create_infos[i] = (VkDeviceQueueCreateInfo){
			.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,			
			.queueFamilyIndex = i,
			.queueCount = queue_count,
			.pQueuePriorities = priorities[i],
		};
	}

	const char *extensions[] = {
		"VK_KHR_swapchain",	
	};

	VkPhysicalDeviceFeatures features = {
	};

	VkDeviceCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
		.queueCreateInfoCount = queue_family_count,
		.pQueueCreateInfos = queue_create_infos,
		.enabledExtensionCount = Arrlen(extensions),
		.ppEnabledExtensionNames = extensions,
		.pEnabledFeatures = &features,
	};

	VK_ASSERT(vkCreateDevice(device->physical.handle, &info, vkb, &device->handle));

	device->queue_families = arena_push(arena, 0, sizeof(GraphicsDeviceQueueFamily));
	for(u32 i = 0; i < queue_family_count; i++)
	{
		u32 queue_count = device->physical.queue_family_properties[i].queueCount;
		device->queue_families[i] = (GraphicsDeviceQueueFamily){
			.device = device,
			.family_index = i,
			.queue_count = queue_count,
			.queues = arena_push(arena, 0, sizeof(GraphicsDeviceQueue) * queue_count),
		};
		for(u32 j = 0; j < device->physical.queue_family_properties[i].queueCount; j++)
		{
			VkQueue handle = 0;
			vkGetDeviceQueue(device->handle, i, j, &handle);
			device->queue_families[i].queues[j] = (GraphicsDeviceQueue){
				.device = device,
				.handle = handle,
				.family_index = i,
				.index = j,
			};
		}
	}

	for(u32 i = 0; i < queue_family_count; i++)
	{
		GraphicsDeviceQueueFamily *q = &device->queue_families[i];
		VkQueueFlags flags = device->physical.queue_family_properties[i].queueCount;
		if(flags & (VK_QUEUE_COMPUTE_BIT | VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_TRANSFER_BIT))
		{
			device->main_queue_family = q;
		}
	}

	device->memory_heap_count = device->physical.memory_properties.memoryTypeCount;
	device->memory_heaps = arena_push(arena, 0, device->memory_heap_count * sizeof(GraphicsDeviceMemoryHeap));

	for(u32 i = 0; i < device->memory_heap_count; i++)
	{
		VkMemoryType type = device->physical.memory_properties.memoryTypes[i];
		VkMemoryHeap heap = device->physical.memory_properties.memoryHeaps[type.heapIndex];
		device->memory_heaps[i] = (GraphicsDeviceMemoryHeap){
			.property_flags = type.propertyFlags,
			.heap_index = type.heapIndex,
			.type_index = i,
			.size = heap.size,
		};
	}
	device->device_heap = &device->memory_heaps[0];

	for(u32 i = 0; i < device->memory_heap_count; i++)
	{
		GraphicsDeviceMemoryHeap *heap = &device->memory_heaps[i];
		if(heap->property_flags & (VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT))
		{
			device->host_and_device_heap = heap;
			break;
		}
	}
	for(u32 i = 0; i < device->memory_heap_count; i++)
	{
		GraphicsDeviceMemoryHeap *heap = &device->memory_heaps[i];
		if(heap->property_flags & (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_CACHED_BIT))
		{
			device->host_cached_heap = heap;
			break;
		}
	}
	for(u32 i = 0; i < device->memory_heap_count; i++)
	{
		GraphicsDeviceMemoryHeap *heap = &device->memory_heaps[i];
		if(heap->property_flags & (VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT))
		{
			device->host_coherent_heap = heap;
			break;
		}
	}

	regress_scratch(scratch);
	return device;
}
void destroy_graphics_device(GraphicsDevice *device)
{
	vkDestroyDevice(device->handle, vkb);	
}
