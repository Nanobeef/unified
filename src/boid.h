

typedef struct{
	f32x4 color;			
}BoidFragmentPushConstants;

typedef struct{
	f32m3p affine;
	f32 scale;
	u32 boid_count;
	u32 random_seed;	
}BoidComputePushConstants;

typedef struct{
	f32x2 position;
	f32x2 velocity;
}Boid;

typedef struct{

	BoidComputePushConstants compute_pc;

	GraphicsDevice *device;
	u32 buffer_index;			
	u64 max_boid_count;
	u64 boid_count;
	GraphicsDeviceBuffer boid_buffers[2];
	GraphicsDeviceBuffer index_buffers[2];

	GraphicsDescriptorSetLayout descriptor_set_layout;
	GraphicsDescriptorPool *descriptor_pool;
	GraphicsDescriptorSet descriptor_sets[2];

	struct{
		VkPipelineLayout layout;
		VkPipeline reset;
		VkPipeline resolve;
	}pipelines;

}BoidGPUSimulation;


BoidGPUSimulation create_boid_gpu_simulation(Arena *arena, GraphicsDevice *device,  u64 max_boid_count);
void destroy_boid_gpu_simulation(BoidGPUSimulation sim);
