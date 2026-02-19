

GraphicsDeviceVertexBuffer create_graphics_device_vertex_buffer(GraphicsDeviceMemoryHeap* heap, u64 size, u64 vertex_stride)
{
	size = (size / (u64)vertex_stride) * vertex_stride;
	GraphicsDeviceVertexBuffer vb = {
		.size = size,
		.vertex_stride = vertex_stride,
		.index_stride = sizeof(u32),
		.vertex_total = size / vertex_stride,
	};
	vb.buffer = create_graphics_device_buffer(heap, size, VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
	vb.data = vb.buffer.memory.mapping;
	return vb;
}

void destroy_graphics_device_vertex_buffer(GraphicsDeviceVertexBuffer vb)
{
	destroy_graphics_device_buffer(vb.buffer);
}

void graphics_device_vertex_buffer_push(GraphicsDeviceVertexBuffer *vb, u32 count, const Vertex2 *vertices)
{	
	Scratch scratch = find_scratch(0,0,0);		
	u32 *indices = arena_push(scratch.arena, 0, count * sizeof(u32));
	for(u32 i = 0; i < count; i++){indices[i] = i;}
	graphics_device_vertex_buffer_push_indexed(vb, count, indices, count, vertices);
	regress_scratch(scratch);
}

void graphics_device_vertex_buffer_push_indexed(GraphicsDeviceVertexBuffer *vb, u32 index_count, u32 *indices, u32 vertex_count, const Vertex2 *vertices)
{	
	if((vb->index_count + index_count) * vb->index_stride + (vb->vertex_count + vertex_count) * vb->vertex_stride > vb->size)
	{
		print("Out of vertex buffer space! %u64 MiB\n", vb->size / MiB(1));
		exit(0);
	}

	Vertex2 *vertex_position = vb->data + vb->size - (vb->vertex_count * vb->vertex_stride);
	for(u32 i = 0; i < vertex_count; i++)
	{
		s32 k = -(s32)(i + 1);
		vertex_position[k] = vertices[i];
	}

	u32 *index_position = vb->data + (vb->index_count * vb->index_stride);
	for(u32 i = 0; i < index_count; i++)
	{
		u32 index = vb->vertex_total - vb->vertex_count - indices[i];
		index_position[i] = index;
	}
	vb->vertex_count += vertex_count;
	vb->index_count += index_count;
}

void cmd_draw_graphics_device_vertex_buffer(GraphicsCommandBuffer cb, GraphicsDeviceVertexBuffer vb)
{
	u64 offset = (vb.vertex_total - vb.vertex_count) * vb.vertex_stride;
	vkCmdBindIndexBuffer(cb.handle, vb.buffer.handle, 0, VK_INDEX_TYPE_UINT32);
	vkCmdBindVertexBuffers(cb.handle, 0,1, &vb.buffer.handle, &offset);
	vkCmdDraw(cb.handle, vb.vertex_count, 1, 0, 0);
}

