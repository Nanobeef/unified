
typedef struct{
	GraphicsDevice *device;
	VkQueryPool handle;	
	VkQueryType type;
	VkQueryPipelineStatisticFlags statistic_flags;
	u64 total;

	String8 *names_array;
}GraphicsQueryPool;

typedef struct{
	String8 name;
	u64 start;
	u64 end;
	u64 elapsed;
}TimestampQueryResult;
typedef struct{
	String8 name;
	VkQueryPipelineStatisticFlags type;
	u64 count;
}PipelineStatisticQueryResult;

GraphicsQueryPool create_graphics_query_pool(Arena *arena, GraphicsDevice *device, VkQueryType type, u32 max_count, VkQueryPipelineStatisticFlags statistic_flags);
void destroy_graphics_query_pool(GraphicsQueryPool pool);

void cmd_reset_graphics_query_pool(GraphicsCommandBuffer cb, GraphicsQueryPool pool);

void cmd_begin_graphics_query(GraphicsCommandBuffer cb, GraphicsQueryPool pool, u32 index);
void cmd_end_graphics_query(GraphicsCommandBuffer cb, GraphicsQueryPool pool, u32 index);

void cmd_begin_graphics_query_name(GraphicsCommandBuffer cb, GraphicsQueryPool pool, String8 name);
b32 cmd_end_graphics_query_name(GraphicsCommandBuffer cb, GraphicsQueryPool pool, String8 name);

PipelineStatisticQueryResult *get_graphics_pipeline_statistic_query_pool_results(Arena *arena, GraphicsQueryPool pool);

u64 cmd_timestamp_graphics_query(GraphicsCommandBuffer cb, GraphicsQueryPool pool, VkPipelineStageFlagBits stage);
u64 cmd_timestamp_graphics_query_name(GraphicsCommandBuffer cb, GraphicsQueryPool pool, const String8 name, VkPipelineStageFlags stage);

TimestampQueryResult *get_graphics_timestamp_query_pool_results(Arena *arena, GraphicsQueryPool pool);
PipelineStatisticQueryResult *get_graphics_pipeline_statistic_query_pool_results(Arena *arena, GraphicsQueryPool pool);

