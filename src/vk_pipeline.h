
typedef struct{
	f32x4 color;
	f32x2 position;
	f32x2 texture;
}Vertex2;

VkShaderModule read_shader_file(GraphicsDevice *device, const char *name);


typedef struct{
	GraphicsDevice *device;
	VkFramebuffer handle;	
}RasterizationFramebuffer;


typedef struct{
	GraphicsDevice *device;
	VkPipeline pipeline;
	u32 local_x, local_y, local_z;
}ComputePipeline;

ComputePipeline create_compute_pipeline(GraphicsDevice *device, u64 data_size, const void* data);

typedef struct{
	VkShaderModule vertex2_vert;	
	VkShaderModule vertex2_frag;	
}GraphicsShaders;

typedef struct{

}ComputePipelines;

typedef struct{
	GraphicsDevice *device;
	VkRenderPass render_pass;
	VkSampler mono_sampler;
	GraphicsDescriptorSetLayout descriptor_set_layout;
	VkPipelineLayout layout;
	VkPipeline vertex2;	
	VkPipeline vertex2_wireframe;

	VkSampleCountFlags sample_count;
	VkFormat format;
}RasterizationPipelines;;

typedef struct{
	ComputePipelines compute;
	RasterizationPipelines rasterization;
}GraphicsPipelines;

RasterizationPipelines create_rasterization_pipelines(GraphicsDevice *device, VkSampleCountFlags sample_count, VkFormat format);
VkFramebuffer *create_rasterization_framebuffers(Arena *arena, RasterizationPipelines pipelines, u32 count, GraphicsDeviceImage *target_images, GraphicsDeviceImage *msaa_images);
void destroy_rasterization_pipelines(RasterizationPipelines pipelines);
void cmd_begin_rasterization_render_pass(GraphicsCommandBuffer cb, VkRenderPass render_pass, VkFramebuffer framebuffer, u32x2 size, f32x4 color);
