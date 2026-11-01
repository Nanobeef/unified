

VkPipeline create_compute_pipeline_from_file(GraphicsDevice *device, VkPipelineLayout layout, const char *path);



typedef struct{
	u32 const_pipeline_id;		 // For internal use only, leave as zero
 	u32 const_timestamp_period;
 	u32 const_buffer_count;
 	u32 const_buffer_granularity;
}UnifiedPipelineSpecialization;

typedef struct{
	GraphicsDevice *device;
	VkShaderModule module;
	VkPipeline small_simulate;
	VkPipeline small_draw;
}UnifiedPipelines;

/*
typedef struct VkSpecializationMapEntry {
    uint32_t    constantID;
    uint32_t    offset;
    size_t      size;
} VkSpecializationMapEntry;

typedef struct VkSpecializationInfo {
    uint32_t                           mapEntryCount;
    const VkSpecializationMapEntry*    pMapEntries;
    size_t                             dataSize;
    const void*                        pData;
} VkSpecializationInfo;
*/


const u32 const_unified_pipeline_count = 2;

UnifiedPipelines compile_unified_pipelines(GraphicsDevice *device, VkShaderModule module, VkPipelineLayout layout, UnifiedPipelineSpecialization specialization)
{
	
	Scratch scratch = find_scratch(0,0,0);

	u32 constant_count = sizeof(UnifiedPipelineSpecialization) / 4;
	arena_push_name(scratch.arena, 0, constant_count, VkSpecializationMapEntry, map_entries);

	for(u32 i = 0; i < constant_count; i++)
	{
		map_entries[i] = (VkSpecializationMapEntry){
			.constantID = i,
			.offset = i * 4,
			.size = 4,
		};
	}

	VkSpecializationInfo specialization_info = {
		.mapEntryCount = constant_count,
		.pMapEntries = map_entries,
		.dataSize = sizeof(specialization),
		.pData = &specialization,
	};

	arena_push_name(scratch.arena, 0, const_unified_pipeline_count, VkPipeline, pipelines);

	for(u32 i = 0; i < const_unified_pipeline_count; i++)
	{
		specialization.const_pipeline_id = i;
		VkPipelineShaderStageCreateInfo stage = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,	
			.stage = VK_SHADER_STAGE_COMPUTE_BIT,
			.module = module,
			.pName = "main",
			.pSpecializationInfo = &specialization_info,
		};

		VkComputePipelineCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
			.layout = layout,
			.stage = stage,
		};
			
		VK_ASSERT(vkCreateComputePipelines(device->handle, device->pipeline_cache, 1, &info, vkb, pipelines + i));
	}
	
	regress_scratch(scratch);
	UnifiedPipelines ret = {
		.device = device,
		.module = module,
		.small_simulate = pipelines[0],
		.small_draw = pipelines[1],
	};
	return ret;	
}


void destroy_unified_pipelines(UnifiedPipelines up)
{
	VkPipeline *pipelines = &up.small_simulate;
	for(u32 i = 0; i < const_unified_pipeline_count; i++)
	{
		vkDestroyPipeline(up.device->handle, pipelines[i], vkb);	
	}
}

