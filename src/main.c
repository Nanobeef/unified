// EXTERNAL
	#include <xcb/xcb_keysyms.h>
	#include <xcb/xproto.h>
	#include <xcb/randr.h>
	#include <X11/keysym.h>

	#define VK_USE_PLATFORM_XCB_KHR
	#include <vulkan/vulkan.h>

	#include <ft2build.h>
	#include FT_FREETYPE_H

// PROCESS
	#include <dirent.h>
	#include <sys/stat.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <sched.h>

// BASE
	#include "base.h"
	#include "vector.h"
	#include "time.h"
	#include "arena.h"
	#include "string.h"
	#include "process.h"
	#include "print.h"
	#include "thread.h"
	#include "file.h"
	#include "event.h"
	#include "camera.h"
	#include "info.h"
	#include "random.h"

Arena *main_arena;
Thread *main_thread;
Mutex thread_table_mutex;
u32 max_thread_count = 1024;
u64 physical_thread_count = 1;
Thread **thread_table;
u64 epoch_time_ns;

// SURFACE
	#include "window.h"

// GRAPHICS
#include "vk_instance.h"
#include "vk_device.h"
#include "vk_command.h"
#include "vk_sync.h"
#include "vk_memory.h"
#include "vk_image.h"
#include "vk_buffer.h"
#include "vk_barrier.h"
#include "vk_surface.h"
#include "vk_swapchain.h"
#include "vk_queue.h"
#include "vk_descriptor.h"
#include "vk_rasterize.h"
#include "vk_pipeline.h"
#include "vk_font.h"
#include "vk_vertex_buffer.h"
#include "vk_draw.h"
#include "vk_query.h"
#include "ui.h"

// AUDIO 
#include <alsa/asoundlib.h>
#include "audio.h"

// PILE
#include "pile.h"

// GRAPHICS
#include "vk_instance.c"
#include "vk_device.c"
#include "vk_command.c"
#include "vk_sync.c"
#include "vk_queue.c"
#include "vk_surface.c"
#include "vk_swapchain.c"
#include "vk_image.c"
#include "vk_buffer.c"
#include "vk_memory.c"
#include "vk_barrier.c"
#include "vk_rasterize.c"
#include "camera.c"
#include "vk_vertex_buffer.c"
#include "vk_font.c"
#include "vk_descriptor.c"
#include "vk_draw.c"
#include "vk_query.c"
#include "ui.c"

// BASE
#include "vector.c"
#include "string.c"
#include "process.c"
#include "time.c"
#include "arena.c"
#include "thread.c"
#include "file.c"
#include "event.c"
#include "print.c"
#include "window.c"
#include "collatz.c"
#include "random.c"

// AUDIO 
#include "audio.c"

// PILE
#include "pile.c"

void init(void)
{
	epoch_time_ns = get_time_ns();
	main_arena = allocate_arena(GiB(64));
	main_thread = allocate_thread(main_arena, MiB(64));
#if defined(thread_local)
	CURRENT_THREAD = main_thread;
#endif

	thread_table = arena_push(main_arena, true, max_thread_count * sizeof(Thread*));
	if(1)
	{
		struct sched_param param = {.sched_priority = sched_get_priority_max(SCHED_FIFO)};
		pthread_setschedparam(pthread_self(), SCHED_FIFO, &param);
	}
	physical_thread_count = get_physical_thread_count();
	b32 t = set_thread_affinity(main_thread, physical_thread_count - 1);
}

void cleanup(void)
{
	destroy_mutex(thread_table_mutex);
	free_arena(main_arena);
	exit(0);
}

s32 main(void)
{
	init();
	test_pile();
	AudioDevice *audio_device = create_audio_device(main_arena);

	tidings.startup_time = mark_time();
	Window *window = create_window(main_arena);
	tidings.window_create_time = record_time();
	GraphicsInstance *instance = create_graphics_instance(main_arena);
	tidings.vk_instance_create_time = record_time();
	GraphicsSurface surface = create_graphics_surface(window, instance);
	tidings.vk_surface_create_time = record_time();
	GraphicsDevice *device = create_graphics_device(main_arena, instance, 0);
	tidings.vk_device_create_time = record_time();
	GraphicsSwapchain swapchain = create_graphics_swapchain(main_arena, surface, device);
	tidings.vk_swapchain_create_time = record_time();

	Event *event_ring_buffer = allocate_ring_buffer(main_arena, Event, 1024);

	u32 frame_count = 2;
	u64 frame_accum = 0;
	u64 frame_index = 0;
	u64 last_frame_index = 1;

	arena_push_type(main_arena, 0, frame_count * 2, Arena*, frame_arenas);
	for(u32 i = 0; i < frame_count * 2; i++)
	{
		u64 size = MiB(64);
		frame_arenas[i] = init_arena(size, arena_push(main_arena, 0, size));
	}

	u32 resize_count = 2;
	u64 resize_accum = 0;
	u64 resize_index = 0;
	arena_push_type(main_arena, 0, frame_count, Arena*, resize_arenas);
	for(u32 i = 0; i < resize_count; i++)
	{
		u64 size = MiB(8);
		resize_arenas[i] = init_arena(size, arena_push(main_arena, 0, size));
	}

	Arena *frame_arena = frame_arenas[frame_accum % (frame_count * 2)];
	Arena *resize_arena = resize_arenas[resize_index];
	
	GraphicsSemaphore *swapchain_semaphores = create_graphics_semaphores(main_arena, device, frame_count);
	GraphicsSemaphore *render_semaphores = create_graphics_semaphores(main_arena, device, frame_count);

	GraphicsFence *render_fences = create_graphics_fences(main_arena, device, frame_count, true);

	GraphicsCommandPool **render_command_pools = create_graphics_command_pools(main_arena, device->main_queue_family, frame_count, 1);
	GraphicsDeviceQueue render_queue = device->main_queue_family->queues[0];

	VkFormat target_format = VK_FORMAT_B8G8R8A8_SRGB;
	//VkFormat target_format = VK_FORMAT_B8G8R8A8_UNORM;
	VkImageFormatProperties target_format_properties;
	vkGetPhysicalDeviceImageFormatProperties(device->physical.handle, target_format, VK_IMAGE_TYPE_2D, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, 0, &target_format_properties);
	VkSampleCountFlags sample_count = most_significant_bit((u64)target_format_properties.sampleCounts);
	RasterizationPipelines rasterization_pipelines = create_rasterization_pipelines(device, sample_count, target_format, target_format == swapchain.format);

	GraphicsDeviceFontCache *font_cache = create_graphics_device_font_cache(main_arena, device, window->screen_dpi);

	arena_push_type(main_arena, 0, frame_count, GraphicsDeviceVertexBuffer, world_vertex_buffers);
	arena_push_type(main_arena, 0, frame_count, GraphicsDeviceVertexBuffer, overlay_vertex_buffers);
	for(u32 i = 0; i < frame_count; i++)
	{
		u64 vb_size = MiB(64);
		world_vertex_buffers[i] = create_graphics_device_vertex_buffer(device->host_cached_heap, vb_size, sizeof(Vertex2), font_cache);
		overlay_vertex_buffers[i] = create_graphics_device_vertex_buffer(device->host_cached_heap, vb_size, sizeof(Vertex2), font_cache);
	}
	const u32 max_swapchain_image_count = 8;
	arena_push_type(main_arena, 0, max_swapchain_image_count, GraphicsDeviceImage, target_images);
	GraphicsDeviceImage *msaa_images = 0;
	if(sample_count > VK_SAMPLE_COUNT_1_BIT)
		msaa_images = arena_push(main_arena, 0, max_swapchain_image_count * sizeof(GraphicsDeviceImage));
	for(u32 i = 0; i < swapchain.image_count; i++)
	{
		if(target_format == swapchain.create_info.imageFormat)
			target_images[i] = swapchain.images[i];
		else
			target_images[i] = create_graphics_device_image(device, swapchain.size, target_format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT);

		if(sample_count > VK_SAMPLE_COUNT_1_BIT)
			msaa_images[i] = create_graphics_device_image_explicit(device->device_heap, swapchain.size, target_format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_IMAGE_TILING_OPTIMAL, sample_count);
	}
	VkFramebuffer *framebuffers = create_rasterization_framebuffers(resize_arena, rasterization_pipelines, swapchain.image_count, target_images, msaa_images);

	arena_push_type(main_arena, 0, frame_count, GraphicsDescriptorPool*, frame_descriptor_pools);
	for(u32 i = 0; i < frame_count; i++)
	{
		frame_descriptor_pools[i] = create_graphics_descriptor_pool(main_arena, device, 1, &rasterization_pipelines.descriptor_set_layout);
		VkDescriptorImageInfo image_info = {
			.imageView = font_cache->linear_image.view,
			.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
		};
		VkWriteDescriptorSet write = {
			.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
			.dstSet = frame_descriptor_pools[i]->descriptor_sets[0].handle,
			.dstBinding = 0,
			.descriptorCount = 1,
			.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			.pImageInfo = &image_info,
		};
		vkUpdateDescriptorSets(device->handle, 1, &write, 0, 0);
	}

	Camera camera = init_camera();
	FixedCamera fixed_camera = create_fixed_camera(window->size);

	{
		wait_and_reset_graphics_fence(render_fences[frame_index]);
		GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
		GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);
		{
			GraphicsImageMemoryBarrier image_barrier = {
				.image = font_cache->linear_image,
				.old_layout = VK_IMAGE_LAYOUT_UNDEFINED,
				.new_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
				.src_access = VK_ACCESS_NONE,
				.dst_access = VK_ACCESS_HOST_WRITE_BIT,
			};

			GraphicsPipelineBarrier barrier = {
				.image_memory_barrier_count = 1,
				.image_memory_barriers = &image_barrier,
				.src_stage = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
				.dst_stage = VK_PIPELINE_STAGE_HOST_BIT,
			};
			cmd_graphics_pipeline_barrier(cb, barrier);
		}
		end_graphics_command_buffer(cb);
		submit_command_buffers(
			render_queue,
			0, 0,
			0, 0,
			1, &cb, 
			0,
			render_fences[frame_index]
		);

	}

	arena_push_type(main_arena, false, frame_count, GraphicsQueryPool, timestamp_query_pools);
	arena_push_type(main_arena, false, frame_count, GraphicsQueryPool, invocation_query_pools);
	for(u32 i = 0; i < frame_count; i++)
	{
		timestamp_query_pools[i] = create_graphics_query_pool(main_arena, device, VK_QUERY_TYPE_TIMESTAMP, 64, 0);
		invocation_query_pools[i] = create_graphics_query_pool(main_arena, device, VK_QUERY_TYPE_PIPELINE_STATISTICS, 64, 
		VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT |
		VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT
		);
	}


	end_time(&tidings.startup_time);


	tidings.desired_frame_time = window->refresh_rate;
	u64 frame_start_time = get_epoch_ns() - tidings.desired_frame_time;
	u64 frame_end_time = 0;
	b32 just_resized = false;
	PolledEvents pe = {0};
	u64 vertex_data_size = 0;
	UIContext *ui_context = initialize_ui_context(main_arena);
	while(true)
	{
		frame_end_time = get_epoch_ns();
		tidings.frame_elapsed_time = frame_end_time - frame_start_time;
		tidings.frame_sleep_time = mark_time();
		if(pe.a.pressed)
		{
			u64 frame_sleep_time = 0;
			if(tidings.frame_elapsed_time < tidings.desired_frame_time  && (swapchain.create_info.presentMode == VK_PRESENT_MODE_FIFO_KHR))
			{
				frame_sleep_time = tidings.desired_frame_time - tidings.frame_elapsed_time;

				u64 us = frame_sleep_time / 1000;
				usleep(us);
			}
		}

		frame_start_time = end_time(&tidings.frame_sleep_time);
		tidings.frame_time = tidings.frame_elapsed_time + tidings.frame_sleep_time;
		
		last_frame_index = frame_index;
		frame_index = frame_accum % frame_count;
		frame_arena = frame_arenas[frame_accum % (frame_count * 2)];
		reset_arena(frame_arena);

		poll_audio_device(audio_device, event_ring_buffer);
		poll_window(window, event_ring_buffer);
		poll_events(frame_arena, event_ring_buffer, &pe);
		if(pe.escape.pressed)
			break;
		fixed_camera = create_fixed_camera(window->size);

		ui_context_next_frame(ui_context, frame_arena, fixed_camera, pe);
		if(frame_accum == 1){
			UIElement *e;
			RomuQuad rq = romu_quad_seed(24);
			for(u32 i = 0; i < 5 ;i++)
			{
				e = ui_element(0, (String8){0});
				UIElement **child_array = create_all_child_element_array(frame_arena, ui_context->root);
				for(u32 j = 0; j < USED(child_array); j++)
				{
					u64 r = romu_quad(&rq);
					if(r % 2 == 0)
					{
						ui_element(child_array[j], (String8){0});	
					}
				}
			}

			draw_ui_element(ui_context->root);
		}



		u32 image_index = 0;
		GraphicsDeviceImage swapchain_image = swapchain.images[image_index];
		GraphicsDeviceImage target_image = target_images[image_index];
		{
			VkResult result = vkAcquireNextImageKHR(device->handle, swapchain.handle, U64_MAX, swapchain_semaphores[frame_index].handle, 0, &swapchain.image_index);
			if(pe.window_should_resize || (result != VK_SUCCESS))
			{
				mark_time();
				resize_accum++;
				resize_index = resize_accum % resize_count;
				resize_arena = resize_arenas[resize_index];
				reset_arena(resize_arena);

				wait_for_graphics_fences(frame_count, render_fences);
				VkSurfaceCapabilitiesKHR capabilities = {0};
				vkGetPhysicalDeviceSurfaceCapabilitiesKHR(device->physical.handle, swapchain.create_info.surface, &capabilities);
				swapchain.create_info.imageExtent = capabilities.minImageExtent;
				for(u32 i = 0; i < swapchain.image_count; i++)
				{
					if(sample_count > VK_SAMPLE_COUNT_1_BIT)
						destroy_graphics_device_image(msaa_images[i]);
					if(swapchain.format != target_format)
						destroy_graphics_device_image(target_images[i]);
					vkDestroyFramebuffer(device->handle, framebuffers[i], vkb);
				}
				
				swapchain = recreate_graphics_swapchain(resize_arena, swapchain);

				for(u32 i = 0; i < swapchain.image_count; i++)
				{
					if(target_format == swapchain.create_info.imageFormat)
						target_images[i] = swapchain.images[i];
					else
						target_images[i] = create_graphics_device_image(device, swapchain.size, target_format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
					if(sample_count > VK_SAMPLE_COUNT_1_BIT)
						msaa_images[i] = create_graphics_device_image_explicit(device->device_heap, swapchain.size, target_format, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_IMAGE_TILING_OPTIMAL, sample_count);
				}
				framebuffers = create_rasterization_framebuffers(resize_arena, rasterization_pipelines, swapchain.image_count, target_images, msaa_images);

				destroy_graphics_semaphore(swapchain_semaphores[frame_index]);
				swapchain_semaphores[frame_index] = create_graphics_semaphore(device);
				tidings.resize_time = record_time();
				frame_start_time = get_epoch_ns() - tidings.desired_frame_time;
				just_resized = true;
				continue;
			}
			image_index = swapchain.image_index;
			swapchain_image = swapchain.images[image_index];
			target_image = target_images[image_index];

		}
		tidings.poll_time = record_time();
		update_camera(&camera, pe, window->size, false);

		{
			GraphicsDeviceVertexBuffer *vb = begin_graphics_device_vertex_buffer(world_vertex_buffers + frame_index, font_cache, frame_arena);
			if(0){
				f32x2 points[] = {{0.0, 0.0},{1.0, 1.0}};
				f32 radius = 0.1;
				draw_rounded_rectangle(vb, perfect_rounding(camera, radius), radius, points, 0, f32x4_color_white);
			}
			RomuQuad rq = romu_quad_seed(0);
			f32 radius = 0.9;
			for(u32 i = 0; i < 10; i++)
			{
				f32x2 p;
				f32 r = fabs(romu_quad_f32(&rq)) * 1 + 0.01;
				u32 try_count = 0;
				do{
					try_count++;
					p = romu_quad_f32x2(&rq);
				}while(f32x2_length(p) > radius + r);
				f32 left = camera.top_left.x;
				f32 top = camera.top_left.y;
				f32 right = camera.bottom_right.x;
				f32 bottom = camera.bottom_right.y;
				if(p.x + r < left)
					continue;
				if(p.x - r > right)
					continue;
				if(p.y + r < top)
					continue;
				if(p.y - r > bottom)
					continue;
				draw_circle(vb, perfect_circle(camera, r), p, r, f32x2_set1(0.0), 0.0, f32x4_set1(1.0), f32x4_set1(0.5));
			}
			
			u64 triangle_count = 0;
			for(u32 i = 0; i < triangle_count * 3; i+=3)
			{
				f32x2 point;
				do{
					point = romu_quad_f32x2(&rq);
					point = f32x2_mul1(point, radius);
				}while(f32x2_length(point) > radius);
				point = camera.center;

				f64 d = romu_quad_f64(&rq);
				int ds = signbit(d);
				d *= 2.0;
				d = d * fabs(d);
				f64 t = (f64)(get_epoch_ms()) / 1000.0 * d;
				f32 scale = sinf(t * 6.0) * 0.02 + 0.1 + 1;
				scale = 0.05;
				f32m2 rotate = f32m2_rotate(t);
				rotate = f32m2_mul(rotate, f32m2_scale(scale, scale));

				if(0)
				{
					Vertex2 vertices[3] = {
						{.color = {{{1.0, 0.0, 0.0, 1.0}}}, .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
						{.color = {{{0.0, 1.0, 0.0, 1.0}}}, .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
						{.color = {{{0.0, 0.0, 1.0, 1.0}}}, .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
					};
					graphics_device_vertex_buffer_push(vb, 3, vertices);
				}
				else
				{
					Vertex2 vertices[3] = {
						{.color = romu_quad_color(&rq), .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
						{.color = romu_quad_color(&rq), .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
						{.color = romu_quad_color(&rq), .position = f32x2_add(point, f32x2_mul_f32m2(romu_quad_f32x2(&rq), rotate))},
					};
					graphics_device_vertex_buffer_push(vb, 3, vertices);
				}
			}
			end_graphics_device_vertex_buffer(vb);
		}
		tidings.draw_time = record_time();
		resolve_graphics_device_font_cache(font_cache);
		tidings.font_resolve_time = record_time();
		wait_and_reset_graphics_fence(render_fences[frame_index]);
		{
			GraphicsDeviceVertexBuffer *vb = begin_graphics_device_vertex_buffer(overlay_vertex_buffers + frame_index, font_cache, frame_arena);
			u64 draw_time = 0;
			{
				String8 str;
				Scratch scratch = find_scratch(0,0,0);
				str = str8_print(scratch.arena, "Startup \t%tus\n Window \t%tus\n Instance \t%tus\n Surface \t%tus\n Device \t%tus\n Swapchain \t%tus\n"
				"Frame  \t%tus\n Desired \t%tus\n Elapsed \t%tus\n Sleep \t%tus\n Resize \t%tus\n Poll    \t%tus\n Draw   \t%t\n Font Resolve\t%t\n CB Wait \t%t\n CB Record \t%t\n", 
				tidings.startup_time, tidings.window_create_time, tidings.vk_instance_create_time, tidings.vk_surface_create_time, tidings.vk_device_create_time, tidings.vk_swapchain_create_time,
				tidings.frame_time, tidings.desired_frame_time, tidings.frame_elapsed_time, tidings.frame_sleep_time, tidings.resize_time, tidings.poll_time, tidings.draw_time, tidings.font_resolve_time, 
				tidings.cb_wait_time, tidings.cb_record_time);
				f32x2 pen = f32x2_set(1,0);
				pen = draw_str8_wrap(vb, fixed_camera, pen, window->size.x, str, 16, f32x4_color_ao);

				u64 cb_time = 0;
				{
					TimestampQueryResult *results = get_graphics_timestamp_query_pool_results(scratch.arena, timestamp_query_pools[last_frame_index]);
					{
						for(u32 i = 0; i < USED(results); i++)
						{
							if(str8_equal(results[i].name, str8_lit("Buffer")))
							{
								cb_time = results[i].elapsed;
							}
						}
					}
					str = str8_print(scratch.arena, "Queue:\n");
					pen = draw_str8_wrap(vb, fixed_camera, pen, window->size.x, str, 16, f32x4_color_ao);
					for(u32 i = 0; i < USED(results); i++)
					{
						str = str8_print(scratch.arena, " %s \t%tus\n",results[i].name, results[i].elapsed);
						pen = draw_str8_wrap(vb, fixed_camera, pen, window->size.x, str, 16, f32x4_color_ao);
						if(str8_equal(results[i].name, str8_lit("Draw World")))
							draw_time += results[i].elapsed;
						else if(str8_equal(results[i].name, str8_lit("Draw Overlay")))
							draw_time += results[i].elapsed;
					}

				}
				{
					PipelineStatisticQueryResult *results = get_graphics_pipeline_statistic_query_pool_results(scratch.arena, invocation_query_pools[last_frame_index]);
					for(u32 i = 0; i < USED(results); i++)
					{
						str = str8_print(scratch.arena, "%s = %u64\n", results[i].name, results[i].count);
						pen = draw_str8_wrap(vb, fixed_camera, pen, window->size.x, str, 16, f32x4_color_ao);
					}
				}
				{
					f64 rate = ((f64)vertex_data_size / (f64)GiB(1)) / ((f64)cb_time / 1000000000.0);
					str = str8_print(scratch.arena, "Transfer Rate = %f64 GiB/s\nSize to Transfer = %u64 KiB\n", rate, vertex_data_size / KiB(1));
					pen = draw_str8_wrap(vb, fixed_camera, pen, window->size.x, str, 16, f32x4_color_ao);
				}
				regress_scratch(scratch);
			}

			end_graphics_device_vertex_buffer(vb);
		}
		tidings.cb_wait_time = record_time();
		GraphicsCommandPool *command_pool = reset_graphics_command_pool(render_command_pools[frame_index], false);
		{
			GraphicsCommandBuffer cb = begin_graphics_command_buffer(command_pool->command_buffers[0]);

			cmd_reset_graphics_query_pool(cb, timestamp_query_pools[frame_index]);
			cmd_reset_graphics_query_pool(cb, invocation_query_pools[frame_index]);
			cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("Buffer"), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
			vkCmdBindDescriptorSets(cb.handle, VK_PIPELINE_BIND_POINT_GRAPHICS, rasterization_pipelines.layout, 0, 1, &frame_descriptor_pools[frame_index]->descriptor_sets[0].handle, 0,0);

			{
				GraphicsImageMemoryBarrier image_barrier = {
					.image = font_cache->linear_image,
					.old_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					.new_layout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
					.src_access = VK_ACCESS_HOST_WRITE_BIT,
					.dst_access = VK_ACCESS_SHADER_READ_BIT,
				};

				GraphicsPipelineBarrier barrier = {
					.image_memory_barrier_count = 1,
					.image_memory_barriers = &image_barrier,
					.src_stage = VK_PIPELINE_STAGE_HOST_BIT,
					.dst_stage = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
				};
				cmd_graphics_pipeline_barrier(cb, barrier);
			}

			cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("Render Pass"), VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT);

			cmd_begin_rasterization_render_pass(cb, rasterization_pipelines.render_pass, framebuffers[image_index], swapchain.size, f32x4_set(0.00, 0.00, 0.00, 1.0));
			{
				VkRect2D scissor = {
					.offset = {0,0},
					.extent = {swapchain.size.x, swapchain.size.y},
				};
				vkCmdSetScissor(cb.handle, 0,1,&scissor);
				VkViewport viewport = {
					.maxDepth = 1.0,
					.x = 0,
					.y = 0,
					.width = (f32)swapchain.size.x,
					.height= (f32)swapchain.size.y,
				};
				vkCmdSetViewport(cb.handle, 0,1,&viewport);
			}
			if(0)
			{
				// I sill need to test this, and refactor it.
				if(poll_window(window, event_ring_buffer))
				{
					RingBuffer *rb = (RingBuffer*)event_ring_buffer - 1;
					for(u32 i = rb->b; i != rb->a; i = (i+1) & rb->mask)
					{
						Event *e = event_ring_buffer + i;
						if(e->type == EVENT_MOUSE && e->mouse.type == MOUSE_MOVE)
						{
							handle_mouse_move_event(frame_arena, e, &pe);
						}
					}
				}
			}
			{
				vkCmdBindPipeline(cb.handle, VK_PIPELINE_BIND_POINT_GRAPHICS, rasterization_pipelines.vertex2);

				vertex_data_size = 0;
				{
					f32m3p mp = f32m3_padding(camera.current_affine);
					vkCmdPushConstants(cb.handle, rasterization_pipelines.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(f32m3p), &mp);

					cmd_begin_graphics_query_name(cb, invocation_query_pools[frame_index], str8_lit("World"));
					cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("Draw World"), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
					vertex_data_size += cmd_draw_graphics_device_vertex_buffer(cb, world_vertex_buffers[frame_index]);
					cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("Draw World"), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
					cmd_end_graphics_query_name(cb, invocation_query_pools[frame_index], str8_lit("World"));
				}
				{
					f32m3p mp = f32m3_padding(fixed_camera.affine);
					vkCmdPushConstants(cb.handle, rasterization_pipelines.layout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(f32m3p), &mp);

					cmd_begin_graphics_query_name(cb, invocation_query_pools[frame_index], str8_lit("Overlay")); cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("Draw Overlay"), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
					vertex_data_size += cmd_draw_graphics_device_vertex_buffer(cb, overlay_vertex_buffers[frame_index]);
					cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("Draw Overlay"), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
					cmd_end_graphics_query_name(cb, invocation_query_pools[frame_index], str8_lit("Overlay"));
				}
			}
			vkCmdEndRenderPass(cb.handle);
			cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("Render Pass"), VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT);

			if(target_format != swapchain.format)
			{
				cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("BLIT"), VK_PIPELINE_STAGE_TRANSFER_BIT);
				{
					GraphicsImageMemoryBarrier image_barrier = {
						.image = swapchain_image,
						.old_layout = VK_IMAGE_LAYOUT_UNDEFINED,
						.new_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
						.src_access = VK_ACCESS_NONE,
						.dst_access = VK_ACCESS_TRANSFER_WRITE_BIT,
					};

					GraphicsPipelineBarrier barrier = {
						.image_memory_barrier_count = 1,
						.image_memory_barriers = &image_barrier,
						.src_stage = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,
						.dst_stage = VK_PIPELINE_STAGE_TRANSFER_BIT,
					};
					
					cmd_graphics_pipeline_barrier(cb, barrier);
				}
				cmd_blit_graphics_device_image(cb, target_image, swapchain_image);
				{
					GraphicsImageMemoryBarrier image_barrier = {
						.image = swapchain_image,
						.old_layout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
						.new_layout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,
						.src_access = VK_ACCESS_TRANSFER_WRITE_BIT,
						.dst_access = VK_ACCESS_NONE,
					};

					GraphicsPipelineBarrier barrier = {
						.image_memory_barrier_count = 1,
						.image_memory_barriers = &image_barrier,
						.src_stage = VK_PIPELINE_STAGE_TRANSFER_BIT,
						.dst_stage = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
					};
					
					cmd_graphics_pipeline_barrier(cb, barrier);
					cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("BLIT"), VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT);
				}
			}

			cmd_timestamp_graphics_query_name(cb, timestamp_query_pools[frame_index], str8_lit("Buffer"), VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);
			end_graphics_command_buffer(cb);
			tidings.cb_record_time = record_time();

		
			submit_command_buffers(
				render_queue,
				1, &swapchain_semaphores[frame_index], 
				1, &render_semaphores[frame_index], 
				1, &cb, 
				0,
				render_fences[frame_index]
			);
		}

		present_swapchain(render_queue, 1, &render_semaphores[frame_index], 1, &swapchain);

		frame_accum++;
	}
	mark_time();
	vkDeviceWaitIdle(device->handle);


	for(u32 i = 0; i < swapchain.image_count; i++)
	{
		vkDestroyFramebuffer(device->handle, framebuffers[i], vkb);
		if(swapchain.format != target_format)
			destroy_graphics_device_image(target_images[i]);
		if(sample_count > VK_SAMPLE_COUNT_1_BIT)
			destroy_graphics_device_image(msaa_images[i]);
			
	}
	destroy_graphics_device_font_cache(font_cache);
	for(u32 i = 0; i < frame_count; i++)
	{
		destroy_graphics_descriptor_pool(frame_descriptor_pools[i]);
		destroy_graphics_device_vertex_buffer(world_vertex_buffers[i]);
		destroy_graphics_device_vertex_buffer(overlay_vertex_buffers[i]);
		destroy_graphics_query_pool(timestamp_query_pools[i]);
		destroy_graphics_query_pool(invocation_query_pools[i]);
	}

	destroy_rasterization_pipelines(rasterization_pipelines);
	destroy_graphics_semaphores(frame_count, swapchain_semaphores);
	destroy_graphics_semaphores(frame_count, render_semaphores);
	destroy_graphics_fences(frame_count, render_fences);
	destroy_graphics_command_pools(frame_count, render_command_pools); 
	destroy_graphics_swapchain(swapchain);
	destroy_graphics_device(device);
	destroy_graphics_surface(surface);
	destroy_graphics_instance(instance);
	destroy_window(window);
	destroy_audio_device(audio_device);
	tidings.cleanup_time = record_time();

	cleanup();
}
