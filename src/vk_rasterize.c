

VkShaderModule read_shader_file(GraphicsDevice *device, const char *name)
{
	Scratch scratch = find_scratch(0,0,0);
	s32 fd = open(name, O_RDONLY);
	if(fd == -1)
	{
		print("Failed to open shader: %cs\n", name);
		return 0;
	}
	struct stat st;
	if(fstat(fd, &st) == -1)
	{
		print("Failed to get shader size: %cs\n", name);
		return 0;
	}

	u64 size = st.st_size;
	u32 *code = arena_push(scratch.arena, 0, size);
	
	u64 read_size = read(fd, code, size);
	if(read_size != size)
	{
		print("Incorrect shader read size: %cs\n", name);
		return 0;
	}

	VkShaderModuleCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
		.pCode = code,
		.codeSize = size,
	};
	VkShaderModule module = 0;
	VK_ASSERT(vkCreateShaderModule(device->handle, &info, vkb, &module));
	regress_scratch(scratch);
	return module;
}



RasterizationPipelines create_rasterization_pipelines(GraphicsDevice *device, VkSampleCountFlags sample_count, VkFormat format)
{
	
	RasterizationPipelines pipelines = 	{
		.device = device,
		.format = format,
		.sample_count = sample_count
	};
	{
		VkSamplerCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO,
			.magFilter = VK_FILTER_LINEAR,
			.minFilter = VK_FILTER_LINEAR,
			.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST,
			.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
			.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
			.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER,
			.mipLodBias = 1.0f,
			.anisotropyEnable = VK_FALSE,
			.maxAnisotropy = 1.0f,
			.compareEnable = VK_FALSE,
			.compareOp = VK_COMPARE_OP_LESS,
			.minLod = 1.0f,
			.maxLod = 1.0f,
			.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK,
			.unnormalizedCoordinates = VK_FALSE,
		};
		VK_ASSERT(vkCreateSampler(device->handle, &info, vkb, &pipelines.mono_sampler));
	}
	if(pipelines.sample_count == VK_SAMPLE_COUNT_1_BIT){
		VkAttachmentReference color_reference = {
			.attachment = 0,
			.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		};

		VkAttachmentDescription attachments[] = {
			{
				.format = pipelines.format,
				.samples = VK_SAMPLE_COUNT_1_BIT,
				.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
				.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
				.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
				.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			},
		};

		VkSubpassDescription subpasses[] = {
			{
				.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
				.colorAttachmentCount = 1,
				.pColorAttachments = &color_reference,
			},
		};

		VkSubpassDependency dependencies[] = {
			{
				.srcSubpass = 0,
				.dstSubpass = VK_SUBPASS_EXTERNAL,
				.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
				.dstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT,
				.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
				.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT,
				.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT,
			},
		};

		VkRenderPassCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
			.attachmentCount = Arrlen(attachments),
			.pAttachments = attachments,
			.subpassCount = Arrlen(subpasses),
			.pSubpasses = subpasses,
			.dependencyCount = Arrlen(dependencies),
			.pDependencies = dependencies,

		};

		VK_ASSERT(vkCreateRenderPass(device->handle, &info, vkb, &pipelines.render_pass));
	}
	else
	{
		VkAttachmentReference color_reference = {
			.attachment = 0,
			.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		};
		VkAttachmentReference resolve_reference = {
			.attachment = 1,
			.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
		};

		VkAttachmentDescription attachments[] = {
			{
				.format = pipelines.format,
				.samples = pipelines.sample_count,
				.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
				.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
				.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
				.finalLayout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL,
			},
			{
				.format = pipelines.format,
				.samples = VK_SAMPLE_COUNT_1_BIT,
				.loadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
				.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
				.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
				.finalLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
			},
		};

		VkSubpassDescription subpasses[] = {
			{
				.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS,
				.colorAttachmentCount = 1,
				.pColorAttachments = &color_reference,
				.pResolveAttachments = &resolve_reference,
			},
		};

		VkSubpassDependency dependencies[] = {
			{
				.srcSubpass = 0,
				.dstSubpass = VK_SUBPASS_EXTERNAL,
				.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
				.dstStageMask = VK_PIPELINE_STAGE_TRANSFER_BIT,
				.srcAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
				.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT,
				.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT,
			},
		};

		VkRenderPassCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
			.attachmentCount = Arrlen(attachments),
			.pAttachments = attachments,
			.subpassCount = Arrlen(subpasses),
			.pSubpasses = subpasses,
			.dependencyCount = Arrlen(dependencies),
			.pDependencies = dependencies,

		};
		VK_ASSERT(vkCreateRenderPass(device->handle, &info, vkb, &pipelines.render_pass));
	}
	{
		VkPushConstantRange range = {
			.size = sizeof(f32m3p),
			.offset = 0,
			.stageFlags = VK_SHADER_STAGE_VERTEX_BIT,
		};

		VkDescriptorSetLayoutBinding bindings[] = {
			{0, VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1, VK_SHADER_STAGE_FRAGMENT_BIT, &pipelines.mono_sampler},
		};
		pipelines.descriptor_set_layout = create_graphics_descriptor_set_layout(device, Arrlen(bindings), bindings);

		VkPipelineLayoutCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
			.pushConstantRangeCount = 1,
			.pPushConstantRanges = &range,
			.setLayoutCount = 1,
			.pSetLayouts = &pipelines.descriptor_set_layout.handle,
		};
		VK_ASSERT(vkCreatePipelineLayout(device->handle, &info, vkb, &pipelines.layout));
	}

	VkShaderModule vertex2_vert_module = read_shader_file(device, "src/vertex2_vert.spv");
	VkShaderModule vertex2_frag_module = read_shader_file(device, "src/vertex2_frag.spv");

	VkPipelineShaderStageCreateInfo vertex2_vertex_stage = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,	
		.stage = VK_SHADER_STAGE_VERTEX_BIT,
		.module = vertex2_vert_module,
		.pName = "main",
	};

	VkPipelineShaderStageCreateInfo vertex2_fragment_stage = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,	
		.stage = VK_SHADER_STAGE_FRAGMENT_BIT,
		.module = vertex2_frag_module,
		.pName = "main",
	};

	VkPipelineShaderStageCreateInfo vertex2_stages[] = {
		vertex2_vertex_stage,
		vertex2_fragment_stage,
	};

	VkVertexInputBindingDescription vertex2_bindings[] = {
		{
			.binding = 0,
			.stride = sizeof(Vertex2),
			.inputRate = VK_VERTEX_INPUT_RATE_VERTEX,
		},
	};

	VkVertexInputAttributeDescription vertex2_attributes[] = {
		{
			.binding = 0,
			.location = 0,
			.format = VK_FORMAT_R32G32B32A32_SFLOAT,
			.offset = offsetof(Vertex2, color),
		},
		{
			.binding = 0,
			.location = 1,
			.format = VK_FORMAT_R32G32_SFLOAT,
			.offset = offsetof(Vertex2, position),
		},
		{
			.binding = 0,
			.location = 2,
			.format = VK_FORMAT_R32G32_SFLOAT,
			.offset = offsetof(Vertex2, texture),
		},
	};

		VkPipelineVertexInputStateCreateInfo vertex2_input_state = {
			.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,	
			.vertexBindingDescriptionCount = Arrlen(vertex2_bindings),
			.pVertexBindingDescriptions = vertex2_bindings,
			.vertexAttributeDescriptionCount = Arrlen(vertex2_attributes),
			.pVertexAttributeDescriptions = vertex2_attributes,
		};

	VkPipelineInputAssemblyStateCreateInfo point_list_input_assembly_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,	
		.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST,
		.primitiveRestartEnable = VK_FALSE,
	};

	VkPipelineInputAssemblyStateCreateInfo line_list_input_assembly_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,	
		.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST,
		.primitiveRestartEnable = VK_FALSE,
	};

	VkPipelineInputAssemblyStateCreateInfo triangle_list_input_assembly_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,	
		.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
		.primitiveRestartEnable = VK_FALSE,
	};

	VkPipelineTessellationStateCreateInfo tessellation_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO,
		.patchControlPoints = 32,
	};

	VkViewport viewport = {
		.x = 0.00,	
		.y = 0.0,
		.width = 1000.0,
		.height = 1000.0,
		.minDepth = 0.0,
		.maxDepth = 1.0,
	};

	VkRect2D scissor = {
		.offset = (VkOffset2D){0,0},
		.extent = (VkExtent2D){0,0},
	};

	VkPipelineViewportStateCreateInfo viewport_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
		.viewportCount = 1,
		.pViewports = &viewport,
		.scissorCount = 1,
		.pScissors = &scissor,
	};

	VkPipelineRasterizationStateCreateInfo rasterization_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = VK_POLYGON_MODE_FILL,
		.frontFace = VK_FRONT_FACE_CLOCKWISE,
		.depthBiasEnable = VK_FALSE,
		.depthBiasConstantFactor = 1.0f,
		.depthBiasClamp = 0.0f,
		.depthBiasSlopeFactor = 1.0f,
		.lineWidth = 1.0f,
	};

	VkPipelineRasterizationStateCreateInfo line_rasterization_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
		.depthClampEnable = VK_FALSE,
		.rasterizerDiscardEnable = VK_FALSE,
		.polygonMode = VK_POLYGON_MODE_LINE,
		.frontFace = VK_FRONT_FACE_CLOCKWISE,
		.depthBiasEnable = VK_FALSE,
		.depthBiasConstantFactor = 1.0f,
		.depthBiasClamp = 0.0f,
		.depthBiasSlopeFactor = 1.0f,
		.lineWidth = 1.0f,
	};

	VkSampleMask sample_mask = 0xFFFFFFFF;

	VkPipelineMultisampleStateCreateInfo multisample_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
		.rasterizationSamples = sample_count,
		.sampleShadingEnable = VK_FALSE,
		.minSampleShading = 0.0f,
		.pSampleMask = NULL,
		.alphaToCoverageEnable = VK_FALSE,
		.alphaToOneEnable = VK_FALSE,
	};

	VkPipelineDepthStencilStateCreateInfo depth_stencil_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
		.depthTestEnable = VK_FALSE,
		.depthWriteEnable = VK_FALSE,
		.depthCompareOp = VK_COMPARE_OP_LESS,
		.depthBoundsTestEnable = VK_FALSE,
		.stencilTestEnable = VK_FALSE,
		.front = (VkStencilOpState){0},
		.back = (VkStencilOpState){0},
		.minDepthBounds = 0.0f,
		.maxDepthBounds = 1.0f,
	};
	
	VkPipelineColorBlendAttachmentState color_blend_attachments[] = {
		{
			.blendEnable = VK_TRUE,
			.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA,
			.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
			.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
			.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,

			.colorBlendOp = VK_BLEND_OP_ADD,
			.alphaBlendOp = VK_BLEND_OP_ADD,
			.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,  
		},
	};

	VkPipelineColorBlendStateCreateInfo color_blend_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_SET,
		.attachmentCount = Arrlen(color_blend_attachments),
		.pAttachments = color_blend_attachments,
		.blendConstants[0] = 0.0f,
		.blendConstants[1] = 0.0f,
		.blendConstants[2] = 0.0f,
		.blendConstants[3] = 0.0f,
	};

	VkPipelineColorBlendAttachmentState no_blend_attachments[] = {
		{
			.blendEnable = VK_FALSE,
			.srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
			.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
			.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
			.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,

			.colorBlendOp = VK_BLEND_OP_ADD,
			.alphaBlendOp = VK_BLEND_OP_ADD,
			.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,  
		},
	};

	VkPipelineColorBlendStateCreateInfo no_color_blend_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
		.logicOpEnable = VK_FALSE,
		.logicOp = VK_LOGIC_OP_SET,
		.attachmentCount = Arrlen(no_blend_attachments),
		.pAttachments = no_blend_attachments,
		.blendConstants[0] = 0.0f,
		.blendConstants[1] = 0.0f,
		.blendConstants[2] = 0.0f,
		.blendConstants[3] = 0.0f,
	};
	
	VkDynamicState dynamic_states[] = {
		VK_DYNAMIC_STATE_VIEWPORT,
		VK_DYNAMIC_STATE_SCISSOR,
	};

	VkPipelineDynamicStateCreateInfo dynamic_state = {
		.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
		.dynamicStateCount = Arrlen(dynamic_states),
		.pDynamicStates = dynamic_states,
	};

	VkGraphicsPipelineCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
		.stageCount = Arrlen(vertex2_stages),
		.pStages = vertex2_stages,
		.pVertexInputState = &vertex2_input_state,
		.pInputAssemblyState = &triangle_list_input_assembly_state,
		.pTessellationState = &tessellation_state,
		.pViewportState = &viewport_state,
		.pRasterizationState = &rasterization_state,
		.pMultisampleState = &multisample_state,
		.pDepthStencilState = &depth_stencil_state,
		.pColorBlendState = &color_blend_state,
		.pDynamicState = &dynamic_state,
		.renderPass = pipelines.render_pass,
		.subpass = 0,
		.layout = pipelines.layout,
	};
	VkGraphicsPipelineCreateInfo infos[2];
	infos[0] = info;
	infos[1] = info;
	VkPipeline vertex2_pipelines[2];
	VK_ASSERT(vkCreateGraphicsPipelines(device->handle, 0, 2, infos, vkb, vertex2_pipelines));
	pipelines.vertex2 = vertex2_pipelines[0];
	pipelines.vertex2_wireframe = vertex2_pipelines[1];

	vkDestroyShaderModule(device->handle, vertex2_vert_module, vkb);
	vkDestroyShaderModule(device->handle, vertex2_frag_module, vkb);
		
	return pipelines;
}

void destroy_rasterization_pipelines(RasterizationPipelines pipelines)
{
	GraphicsDevice *device = pipelines.device;
	destroy_graphics_descriptor_set_layout(pipelines.descriptor_set_layout);
	vkDestroyRenderPass(device->handle, pipelines.render_pass, vkb);
	vkDestroySampler(device->handle, pipelines.mono_sampler, vkb);
	vkDestroyPipeline(device->handle, pipelines.vertex2, vkb);
	vkDestroyPipeline(device->handle, pipelines.vertex2_wireframe, vkb);
	vkDestroyPipelineLayout(device->handle, pipelines.layout, vkb);
}

VkFramebuffer *create_rasterization_framebuffers(Arena *arena, RasterizationPipelines pipelines, u32 count, GraphicsDeviceImage *target_images, GraphicsDeviceImage *msaa_images)
{
	Scratch scratch = find_scratch(0,0,0);
	u32 attachment_count = (target_images != 0) + (msaa_images != 0);
	VkFramebuffer *framebuffers = arena_push(arena, 0, sizeof(VkFramebuffer) * count);
	for(u32 i = 0; i < count; i++)
	{
		VkImageView *attachments = arena_push(scratch.arena, 0, attachment_count * sizeof(VkImageView));
		if(attachment_count == 1)
		{
			attachments[0] = target_images[i].view;
		}
		else if(attachment_count == 2)
		{
			attachments[0] = msaa_images[i].view;
			attachments[1] = target_images[i].view;
		}
		else
		{
			print("Create framebuffer: unsupported attachment count!\n");
		}
		VkFramebufferCreateInfo info = {
			.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
			.renderPass = pipelines.render_pass,
			.attachmentCount = attachment_count,
			.pAttachments = attachments,
			.width = target_images[i].size.x,
			.height = target_images[i].size.y,
			.layers = 1,
		};
		VK_ASSERT(vkCreateFramebuffer(pipelines.device->handle, &info, vkb, &framebuffers[i]));
	}
	regress_scratch(scratch);
	return framebuffers;
}

void cmd_begin_rasterization_render_pass(GraphicsCommandBuffer cb, VkRenderPass render_pass, VkFramebuffer framebuffer, u32x2 size, f32x4 color)
{
	VkClearValue cv = (VkClearValue){.color = {{color.r, color.g, color.b, color.a}}};
	VkRenderPassBeginInfo info = {
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
		.renderPass = render_pass,
		.framebuffer = framebuffer,
		.renderArea = {.offset = {0,0},.extent = {size.x, size.y}},
		.clearValueCount = 1,
		.pClearValues = &cv,
	};
	vkCmdBeginRenderPass(cb.handle, &info, VK_SUBPASS_CONTENTS_INLINE);
}
