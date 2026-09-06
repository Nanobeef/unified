


GraphicsFence create_graphics_fence(GraphicsDevice *device, b32 signaled)
{
	GraphicsFence fence = {.device = device};
	VkFenceCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
		.flags = signaled ? VK_FENCE_CREATE_SIGNALED_BIT : 0,
	};
	VK_ASSERT(vkCreateFence(device->handle, &info, vkb, &fence.handle));
	return fence;
}

GraphicsFence* create_graphics_fences(Arena *arena, GraphicsDevice *device, u32 count, b32 signaled)
{
	arena_push_type(arena, 0, count, GraphicsFence, fences);
	for(u32 i = 0; i < count; i++){fences[i] = create_graphics_fence(device, signaled);};
	return fences;
}

void destroy_graphics_fence(GraphicsFence fence)
{
	vkDestroyFence(fence.device->handle, fence.handle, vkb);
}

void destroy_graphics_fences(u32 count, GraphicsFence *fences)
{
	for(u32 i = 0; i < count; i++){destroy_graphics_fence(fences[i]);}
}

void wait_for_graphics_fence(GraphicsFence fence)
{
	vkWaitForFences(fence.device->handle, 1, &fence.handle, VK_TRUE, U64_MAX);
}

void wait_for_graphics_fences(u32 count, GraphicsFence *fences)
{
	Scratch scratch = find_scratch(0,0,0);
	arena_push_type(scratch.arena, 0, count, VkFence, handles);
	for(u32 i = 0; i < count; i++){handles[i] = fences[i].handle;}
	vkWaitForFences(fences[0].device->handle, count, handles, VK_TRUE, U64_MAX);
	regress_scratch(scratch);
}

void reset_graphics_fence(GraphicsFence fence)
{
	vkResetFences(fence.device->handle, 1, &fence.handle);
}
void reset_graphics_fences(u32 count, GraphicsFence *fences)
{
	Scratch scratch = find_scratch(0,0,0);
	arena_push_type(scratch.arena, 0, count, VkFence, fence_handles);
	for(u32 i = 0; i < count; i++){fence_handles[i] = fences[i].handle;};
	vkResetFences(fences[0].device->handle, count, fence_handles);
	regress_scratch(scratch);
}
void wait_and_reset_graphics_fence(GraphicsFence fence)
{
	vkWaitForFences(fence.device->handle, 1, &fence.handle, VK_TRUE, U64_MAX);
	vkResetFences(fence.device->handle, 1, &fence.handle);
}
void wait_and_reset_graphics_fences(u32 count, GraphicsFence *fences)
{
	Scratch scratch = find_scratch(0,0,0);
	arena_push_type(scratch.arena, 0, count, VkFence, fence_handles);
	for(u32 i = 0; i < count; i++){fence_handles[i] = fences[i].handle;};
	vkWaitForFences(fences[0].device->handle, count, fence_handles, VK_TRUE, U64_MAX);
	vkResetFences(fences[0].device->handle, count, fence_handles);
	regress_scratch(scratch);
}

GraphicsSemaphore create_graphics_semaphore(GraphicsDevice *device)
{
	GraphicsSemaphore semaphore = {.device = device};
	VkSemaphoreCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO,
	};
	VK_ASSERT(vkCreateSemaphore(device->handle, &info, vkb, &semaphore.handle));
	return semaphore;
}

GraphicsSemaphore* create_graphics_semaphores(Arena *arena, GraphicsDevice *device, u32 count)
{
	arena_push_type(arena, 0, count, GraphicsSemaphore, semaphores);
	for(u32 i = 0; i < count; i++){semaphores[i] = create_graphics_semaphore(device);};
	return semaphores;
}

void destroy_graphics_semaphore(GraphicsSemaphore semaphore)
{
	vkDestroySemaphore(semaphore.device->handle, semaphore.handle, vkb);
}

void destroy_graphics_semaphores(u32 count, GraphicsSemaphore *semaphores)
{
	for(u32 i = 0; i < count; i++){destroy_graphics_semaphore(semaphores[i]);}
}

