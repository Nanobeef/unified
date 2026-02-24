



typedef struct{
	GraphicsDeviceBuffer buffer;
	void *data;
	u32 index_stride;
	u32 vertex_stride;
	u32 vertex_count;
	u32 index_count;
	u32 vertex_total;
	u64 size;

	GraphicsDeviceFontCache *font_cache;
}GraphicsDeviceVertexBuffer;

GraphicsDeviceVertexBuffer create_graphics_device_vertex_buffer(GraphicsDeviceMemoryHeap* heap, u64 size, u64 vertex_stride, GraphicsDeviceFontCache *font_cache);
void destroy_graphics_device_vertex_buffer(GraphicsDeviceVertexBuffer vb);
void graphics_device_vertex_buffer_push(GraphicsDeviceVertexBuffer *vb, u32 count, const Vertex2 *vertices);
void graphics_device_vertex_buffer_push_indexed(GraphicsDeviceVertexBuffer *vb, u32 index_count, u32 *indices, u32 vertex_count, const Vertex2 *vertices);
void reset_graphics_device_vertex_buffer(GraphicsDeviceVertexBuffer *vb);
void flush_graphics_device_vertex_buffer(GraphicsDeviceVertexBuffer *vb);
void cmd_draw_graphics_device_vertex_buffer(GraphicsCommandBuffer cb, GraphicsDeviceVertexBuffer vb);
