
GraphicsCommandPool* create_graphics_command_pool(Arena *arena, GraphicsDeviceQueueFamily *queue_family, u32 command_buffer_count)
{
	GraphicsCommandPool *pool = arena_push(arena, true, sizeof(GraphicsCommandPool));
	pool->queue_family = queue_family;
	Scratch scratch = find_scratch(0,0,0);
	VkCommandPoolCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
		.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
		.queueFamilyIndex = queue_family->family_index,
	};
	VK_ASSERT(vkCreateCommandPool(queue_family->device->handle, &info, vkb, &pool->handle));


	pool->command_buffer_count = command_buffer_count;
	pool->command_buffers = arena_push(arena, 0, command_buffer_count * sizeof(GraphicsCommandBuffer));

	arena_push_type(scratch.arena, 0, command_buffer_count, VkCommandBuffer, command_buffers);

	VkCommandBufferAllocateInfo alloc_info = {
		.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
		.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
		.commandPool = pool->handle,
		.commandBufferCount = command_buffer_count,
	};
	VK_ASSERT(vkAllocateCommandBuffers(queue_family->device->handle, &alloc_info, command_buffers));

	for(u32 i = 0; i < command_buffer_count; i++)
	{
		pool->command_buffers[i] = (GraphicsCommandBuffer){
			.pool = pool,
			.handle = command_buffers[i],
		};
	}

	regress_scratch(scratch);
	return pool;
}

void destroy_graphics_command_pool(GraphicsCommandPool *pool)
{
	vkDestroyCommandPool(pool->queue_family->device->handle, pool->handle, vkb);
}
