

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


