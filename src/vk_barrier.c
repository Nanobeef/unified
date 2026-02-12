
void cmd_graphics_pipeline_barrier(GraphicsCommandBuffer cb, GraphicsPipelineBarrier barrier)
{
	Scratch scratch = find_scratch(0,0,0);
	arena_push_type(scratch.arena, 0, barrier.memory_barrier_count, VkMemoryBarrier, memory_barriers);
	for(u32 i = 0; i < barrier.memory_barrier_count; i++)
	{
		GraphicsMemoryBarrier mb = barrier.memory_barriers[i];
		memory_barriers[i] = (VkMemoryBarrier){
			.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER,
			.srcAccessMask = mb.src_access,
			.dstAccessMask = mb.dst_access,
		};
	}
	arena_push_type(scratch.arena, 0, barrier.buffer_memory_barrier_count, VkBufferMemoryBarrier, buffer_memory_barriers);
	for(u32 i = 0; i < barrier.buffer_memory_barrier_count; i++)
	{
		GraphicsBufferMemoryBarrier bmb = barrier.buffer_memory_barriers[i];
		buffer_memory_barriers[i] = (VkBufferMemoryBarrier){
			.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER,
			.srcAccessMask = bmb.src_access,
			.dstAccessMask = bmb.dst_access,
			.srcQueueFamilyIndex = bmb.src_queue_family ? bmb.src_queue_family->family_index : 0,
			.dstQueueFamilyIndex = bmb.dst_queue_family ? bmb.dst_queue_family->family_index : 0,
			.buffer = bmb.buffer.handle,
			.offset = bmb.offset,
			.size = bmb.size,
		};
	}
	arena_push_type(scratch.arena, 0, barrier.image_memory_barrier_count, VkImageMemoryBarrier, image_memory_barriers);
	for(u32 i = 0; i < barrier.image_memory_barrier_count; i++)
	{
		GraphicsImageMemoryBarrier imb = barrier.image_memory_barriers[i];
		VkImageSubresourceRange subresource_range = imb.subresource_range;
		if(subresource_range.aspectMask == 0)
		{
			subresource_range = imb.image.subresource_range;
		}
		image_memory_barriers[i] = (VkImageMemoryBarrier){
			.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
			.srcAccessMask = imb.src_access,
			.dstAccessMask = imb.dst_access,
			.srcQueueFamilyIndex = imb.src_queue_family ? imb.src_queue_family->family_index : 0,
			.dstQueueFamilyIndex = imb.dst_queue_family ? imb.dst_queue_family->family_index : 0,
			.oldLayout = imb.old_layout,
			.newLayout = imb.new_layout,
			.image = imb.image.handle,
			.subresourceRange = subresource_range,
		};
	}

	vkCmdPipelineBarrier(
		cb.handle, barrier.src_stage, barrier.dst_stage, barrier.dependency_flags, 
		barrier.memory_barrier_count, memory_barriers,
		barrier.buffer_memory_barrier_count, buffer_memory_barriers,
		barrier.image_memory_barrier_count, image_memory_barriers
	);
	regress_scratch(scratch);
}
