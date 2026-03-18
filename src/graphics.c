


Graphics stage_graphics(Arena *arena, Graphics g, GraphicsStage stage)
{
	START:
	switch(stage)
	{
		default:{
			if(g.stage < 0)
			{
				stage = -stage;
			}
			else
			{
				stage = +GRAPHICS_STAGE_INSTANCE;
			}
			goto START;
		}
		case -GRAPHICS_STAGE_FRAME:{
			vkDeviceWaitIdle(g.device->handle);
		}
		case -GRAPHICS_STAGE_FONT_CACHE:{
		}
		case -GRAPHICS_STAGE_PIPELINE:{
		}
		case -GRAPHICS_STAGE_SWAPCHAIN:{
		}
		case -GRAPHICS_STAGE_DEVICE:{
		}
		case -GRAPHICS_STAGE_SURFACE:{
		}
		case -GRAPHICS_STAGE_WINDOW:{
		}
		case -GRAPHICS_STAGE_INSTANCE:{
		}

		if((stage & GRAPHICS_RECREATE) == 0)
			break;

		case +GRAPHICS_STAGE_INSTANCE:{
			g.instance = create_graphics_instance(arena);
		}
		case +GRAPHICS_STAGE_WINDOW:{
			g.window = create_window(arena);
		}
		case +GRAPHICS_STAGE_SURFACE:{
			g.surface = create_graphics_surface(g.window, g.instance);
		}
		case +GRAPHICS_STAGE_DEVICE:{
			g.device = create_graphics_device(arena, g.instance, 0);
		}
		case +GRAPHICS_STAGE_SWAPCHAIN:{
			g.swapchain = create_graphics_swapchain(arena, g.surface, g.device);
			g.target_format = g.swapchain.format;
			g.target_sample_count = VK_SAMPLE_COUNT_1_BIT;
		}
		case +GRAPHICS_STAGE_PIPELINE:{
			vkGetPhysicalDeviceImageFormatProperties(g.device->physical.handle, g.target_format, VK_IMAGE_TYPE_2D, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, 0, &g.target_format_properties);
			g.target_sample_count = most_significant_bit((u64)g.target_format_properties.sampleCounts);
			g.rasterization_pipelines = create_rasterization_pipelines(g.device, g.target_sample_count, g.target_format, g.target_format == g.swapchain.format);
		}
		case +GRAPHICS_STAGE_FONT_CACHE:{
			g.font_cache = create_graphics_device_font_cache(arena, g.device, g.window->screen_dpi);
		}
		case +GRAPHICS_STAGE_FRAME:{
		}
	}
	return g;
}
