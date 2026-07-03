

VkPipeline create_compute_pipeline_from_file(GraphicsDevice *device, VkPipelineLayout layout, const char *path)
{
	VkShaderModule module = read_shader_file(device, path);
	VkPipelineShaderStageCreateInfo stage = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,	
		.stage = VK_SHADER_STAGE_COMPUTE_BIT,
		.module = module,
		.pName = "main",
	};
	VkComputePipelineCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO,
		.layout = layout,
		.stage = stage,
	};
	VkPipeline pipeline = 0;
	VK_ASSERT(vkCreateComputePipelines(device->handle, device->pipeline_cache, 1, &info, vkb, &pipeline));
	vkDestroyShaderModule(device->handle, module, vkb);
	return pipeline;
}
