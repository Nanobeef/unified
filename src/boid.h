

typedef struct{
	f32x4 color;			
}BoidFragmentPushConstants;

typedef struct{
	f32m3p affine;
	f32 scale;
	u32 boid_count;
	u32 kernel_index;
	u32 padding;
	u32 src_index;
	u32 dst_index;
	u32x2 grid_size;
	u32x2 pixel_size;
}BoidComputePushConstants;

typedef struct{
	f32x2 position;
	f32x2 velocity;
}Boid;

typedef struct{
	u32 offset_index;
	u32 index_in_cell;
}BoidGridIndex;

typedef struct{

	BoidComputePushConstants compute_pc;

	GraphicsDevice *device;
	u32 buffer_index;			
	u64 max_boid_count;
	u64 boid_count;

	u32x2 grid_size;




	GraphicsDeviceBuffer boid_buffers[2];
	GraphicsDeviceBuffer index_buffers[2];
	GraphicsDeviceBuffer grid_count_buffer;
	GraphicsDeviceBuffer grid_offset_buffer;
	GraphicsDeviceBuffer grid_index_buffer;
	GraphicsDeviceBuffer grid_offset_sum_buffer;

	GraphicsDescriptorSetLayout descriptor_set_layout;
	GraphicsDescriptorPool *descriptor_pool;
	GraphicsDescriptorSet descriptor_sets[2];

	struct{
		VkPipelineLayout layout;
		VkPipeline reset;
		VkPipeline resolve;
		VkPipeline count;
		VkPipeline prefix_sum;
	}pipelines;

}BoidGPUSimulation;

VkShaderStageFlags boid_compute_push_stages = 
	VK_SHADER_STAGE_COMPUTE_BIT |
	VK_SHADER_STAGE_TASK_BIT_EXT |
	VK_SHADER_STAGE_MESH_BIT_EXT |
	VK_SHADER_STAGE_VERTEX_BIT |
	VK_SHADER_STAGE_FRAGMENT_BIT;

BoidGPUSimulation create_boid_gpu_simulation(Arena *arena, GraphicsDevice *device,  u64 max_boid_count);
void destroy_boid_gpu_simulation(BoidGPUSimulation sim);

u32 boid_power_offset(u32 base, u32 subgroup_size, u32 n)
{
	u32 offset = 0;	
	base /= subgroup_size;
	if(n == 0)
		return 0;
	for(uint i = 0; i < n; i++)
	{
		offset += base;
		base /= subgroup_size;
	}
	return offset;
}

