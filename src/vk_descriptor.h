





typedef struct{
	GraphicsDevice *device;
	VkDescriptorSetLayout handle;
	u32 pool_sizes[VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT+1];
}GraphicsDescriptorSetLayout;

struct GraphicsDescriptorSet;

typedef struct{
	GraphicsDevice *device;
	VkDescriptorPool handle;
	u32 set_count;
	struct GraphicsDescriptorSet *descriptor_sets;
}GraphicsDescriptorPool;

typedef struct GraphicsDescriptorSet{
	GraphicsDescriptorPool *pool;
	VkDescriptorSet handle;
}GraphicsDescriptorSet;

GraphicsDescriptorSetLayout create_graphics_descriptor_set_layout(GraphicsDevice *device, u32 binding_count, VkDescriptorSetLayoutBinding *bindings);
void destroy_graphics_descriptor_set_layout(GraphicsDescriptorSetLayout layout);
GraphicsDescriptorPool* create_graphics_descriptor_pool(Arena *arena, GraphicsDevice *device, u32 layout_count, GraphicsDescriptorSetLayout *layouts);
void destroy_graphics_descriptor_pool(GraphicsDescriptorPool *pool);
