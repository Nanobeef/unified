


/*
typedef void (VKAPI_PTR *PFN_vkCmdBeginQuery)(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags);
typedef void (VKAPI_PTR *PFN_vkCmdEndQuery)(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query);
typedef void (VKAPI_PTR *PFN_vkCmdResetQueryPool)(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount);
typedef void (VKAPI_PTR *PFN_vkCmdWriteTimestamp)(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query);
typedef void (VKAPI_PTR *PFN_vkCmdCopyQueryPoolResults)(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags);
VKAPI_ATTR VkResult VKAPI_CALL vkGetQueryPoolResults(
    VkDevice                                    device,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount,
    size_t                                      dataSize,
    void*                                       pData,
    VkDeviceSize                                stride,
    VkQueryResultFlags                          flags);
*/

GraphicsQueryPool create_graphics_query_pool(Arena *arena, GraphicsDevice *device, VkQueryType type, u32 max_count, VkQueryPipelineStatisticFlags statistic_flags)
{
	VkQueryPoolCreateInfo info = {
		.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO,
		.queryType = type,
		.queryCount = max_count,
		.pipelineStatistics = statistic_flags,
	};
	GraphicsQueryPool pool = {.device = device,.total = max_count,.statistic_flags = statistic_flags, .type = type,};
	VK_ASSERT(vkCreateQueryPool(device->handle, &info, vkb, &pool.handle));
	pool.names_array = allocate_array(arena, String8, pool.total);
	return pool;
}

void destroy_graphics_query_pool(GraphicsQueryPool pool)
{
	vkDestroyQueryPool(pool.device->handle, pool.handle, vkb);
}

void cmd_reset_graphics_query_pool(GraphicsCommandBuffer cb, GraphicsQueryPool pool)
{
	vkCmdResetQueryPool(cb.handle, pool.handle, 0, TOTAL(pool.names_array));
	USED(pool.names_array) = 0;
}

void cmd_begin_graphics_query(GraphicsCommandBuffer cb, GraphicsQueryPool pool, u32 index)
{
	vkCmdBeginQuery(cb.handle, pool.handle, index, 0);	
}

void cmd_end_graphics_query(GraphicsCommandBuffer cb, GraphicsQueryPool pool, u32 index)
{
	vkCmdEndQuery(cb.handle, pool.handle, index);	
}

void cmd_begin_graphics_query_name(GraphicsCommandBuffer cb, GraphicsQueryPool pool, String8 name)
{
	u64 index = USED(pool.names_array);
	vkCmdBeginQuery(cb.handle, pool.handle, index, 0);	
	pool.names_array[index] = name;
	USED(pool.names_array) = index+1;
}

b32 cmd_end_graphics_query_name(GraphicsCommandBuffer cb, GraphicsQueryPool pool, String8 name)
{
	u64 index = USED(pool.names_array);
	for(u64 i = index; i != U64_MAX; i--)
	{
		if(str8_equal(name, pool.names_array[i]))
		{
			vkCmdEndQuery(cb.handle, pool.handle, i);	
			return true;
		}
	}
	return false;
}


PipelineStatisticQueryResult *get_graphics_pipeline_statistic_query_pool_results(Arena *arena, GraphicsQueryPool pool)
{
	u64 used = USED(pool.names_array);	
	Scratch scratch = find_scratch(0,1,&arena);
	u32 stat_count = popcount(pool.statistic_flags);
	arena_push_type(scratch.arena, false, used * stat_count, u64, counters);
	PipelineStatisticQueryResult *results = allocate_array(arena, PipelineStatisticQueryResult, used * stat_count);
	if(used)
	{
		vkGetQueryPoolResults(pool.device->handle, pool.handle, 0, used, sizeof(u64) * used * stat_count, (void*)counters, sizeof(u64) * stat_count, VK_QUERY_RESULT_64_BIT);
	}
	for(u32 i = 0; i < used; i++)
	{
		VkQueryPipelineStatisticFlags st = pool.statistic_flags;
		u32 k = 0;
		for(u32 j = 0; j < stat_count; j++)
		{
			while(((st >> k) & 1) == 0)
				k++;
			VkQueryPipelineStatisticFlags type = st & (1 << (k));
			String8 str = str8_lit("Unknown");
			switch(type)
			{
				case VK_QUERY_PIPELINE_STATISTIC_VERTEX_SHADER_INVOCATIONS_BIT: str = str8_lit("Vertex"); break;
				case VK_QUERY_PIPELINE_STATISTIC_FRAGMENT_SHADER_INVOCATIONS_BIT: str = str8_lit("Fragment"); break;
				case VK_QUERY_PIPELINE_STATISTIC_COMPUTE_SHADER_INVOCATIONS_BIT: str = str8_lit("Compute"); break;
				default:break;

			}

			String8 strings[2] = {
				pool.names_array[i],
				str,
			};

			String8 name = str8_concatenate_and_seperate(arena, Arrlen(strings), strings, str8_lit(" "));

			results[j + i * stat_count] = (PipelineStatisticQueryResult){
				.name = name,
				.type = type,
				.count = counters[j + i * stat_count],
			};
			k++;
		}
	}
	regress_scratch(scratch);
	USED(results) = used * stat_count;
	return results;
}

u64 cmd_timestamp_graphics_query(GraphicsCommandBuffer cb, GraphicsQueryPool pool, VkPipelineStageFlagBits stage)
{
	u64 index = USED(pool.names_array);
	vkCmdWriteTimestamp(cb.handle, stage, pool.handle, index);
	USED(pool.names_array) = index+1;
	return index;
}
u64 cmd_timestamp_graphics_query_name(GraphicsCommandBuffer cb, GraphicsQueryPool pool, const String8 name, VkPipelineStageFlags stage)
{
	u64 index = USED(pool.names_array);
	vkCmdWriteTimestamp(cb.handle, stage, pool.handle, index);
	pool.names_array[index] = name;
	USED(pool.names_array) = index+1;
	return index;
}

TimestampQueryResult *get_graphics_timestamp_query_pool_results(Arena *arena, GraphicsQueryPool pool)
{
	u64 used = USED(pool.names_array);
	Scratch scratch = find_scratch(0,1, &arena);
	arena_push_type(scratch.arena, false, used, u64, counters);
	if(used)
	{
		vkGetQueryPoolResults(pool.device->handle, pool.handle, 0, used, sizeof(u64) * used, (void*)counters, sizeof(u64), VK_QUERY_RESULT_64_BIT);
		u64 period = (u64)pool.device->physical.properties.limits.timestampPeriod;
		for(u64 i = 0; i < used; i++)
		{
			counters[i] *= period;
		}
	}
	TimestampQueryResult *results = allocate_array(arena, TimestampQueryResult, used / 2);
	for(u64 i = 0; i < used; i++)
	{
		for(u64 j = i+1; j < used; j++)
		{
			if(str8_equal(pool.names_array[i], pool.names_array[j]))
			{
				TimestampQueryResult result = {
					.name = pool.names_array[i],
					.start = counters[i],
					.end = counters[j],
				};
				result.elapsed = result.end - result.start;
				append_array(arena, TimestampQueryResult, &results, result);
			}
		}
	}
	regress_scratch(scratch);
	return results;
}

