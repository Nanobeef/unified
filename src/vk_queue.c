


void submit_command_buffers(GraphicsDeviceQueue queue, u32 wait_count, GraphicsSemaphore *wait_semaphores, u32 signal_count, GraphicsSemaphore *signal_semaphores, u32 command_buffer_count, GraphicsCommandBuffer *command_buffers, VkPipelineStageFlags *wait_stages, GraphicsFence fence)
{
	Scratch scratch = find_scratch(0,0,0);

	arena_push_type(scratch.arena, true, wait_count, VkSemaphore, wait_semaphore_handles);
	for(u32 i = 0; i < wait_count; i++){wait_semaphore_handles[i] = wait_semaphores[i].handle;}
	arena_push_type(scratch.arena, true, signal_count, VkSemaphore, signal_semaphore_handles);
	for(u32 i = 0; i < signal_count; i++){signal_semaphore_handles[i] = signal_semaphores[i].handle;}
	arena_push_type(scratch.arena, true, command_buffer_count, VkCommandBuffer, command_buffer_handles);
	for(u32 i = 0; i < command_buffer_count; i++){command_buffer_handles[i] = command_buffers[i].handle;}

	if(wait_stages == 0)
	{
		wait_stages = arena_push(scratch.arena, 0, command_buffer_count * sizeof(VkPipelineStageFlags));
		for(u32 i = 0; i < command_buffer_count; i++){wait_stages[i] = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;};
	}
		
	
	VkSubmitInfo info = {
		.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,	
		.waitSemaphoreCount = wait_count,
		.pWaitSemaphores = wait_semaphore_handles,
		.signalSemaphoreCount = signal_count,
		.pSignalSemaphores = signal_semaphore_handles,
		.commandBufferCount = command_buffer_count,
		.pCommandBuffers = command_buffer_handles,
		.pWaitDstStageMask = wait_stages,
	};
	VkResult result = vkQueueSubmit(queue.handle, 1, &info, fence.handle);
	regress_scratch(scratch);
}

void present_swapchain(GraphicsDeviceQueue queue, u32 wait_count, GraphicsSemaphore *semaphores, u32 swapchain_count, GraphicsSwapchain *swapchains)
{
	Scratch scratch = find_scratch(0,0,0);

	arena_push_type(scratch.arena, true, swapchain_count, VkResult, results);
	arena_push_type(scratch.arena, true, swapchain_count, u32, image_indices);
	for(u32 i = 0; i < swapchain_count; i++){image_indices[i] = swapchains[i].image_index;}
	arena_push_type(scratch.arena, true, swapchain_count, VkSwapchainKHR, swapchain_handles);
	for(u32 i = 0; i < swapchain_count; i++){swapchain_handles[i] = swapchains[i].handle;}
	arena_push_type(scratch.arena, true, wait_count, VkSemaphore, semaphore_handles);
	for(u32 i = 0; i < wait_count; i++){semaphore_handles[i] = semaphores[i].handle;}

	VkPresentInfoKHR info = {
		.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
		.waitSemaphoreCount = wait_count,
		.pWaitSemaphores = semaphore_handles,
		.swapchainCount = swapchain_count,
		.pSwapchains = swapchain_handles,
		.pImageIndices = image_indices,
		.pResults = results,
	};
	VkResult result = vkQueuePresentKHR(queue.handle, &info);

	for(u32 i = 0; i < swapchain_count; i++){swapchains[i].result = result;}

	regress_scratch(scratch);
}

