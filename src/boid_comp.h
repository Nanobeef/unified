#extension GL_KHR_shader_subgroup_basic : enable


layout(push_constant) uniform PushConstant{
	mat3 affine;
	float scale;
	uint boid_count;
	uint kernel_index;
	uint padding;
	uint src_index;
	uint dst_index;
	uvec2 grid_size;
	uvec2 pixel_size;
}PC;

struct Boid{
	vec2 position;
	vec2 velocity;
};

struct GridIndex{
	uint offset_index;
	uint index_in_cell;
};

layout (binding = 0) buffer ReadonlyBoids{
	Boid data[];
}readonly_boids;

layout (binding = 1) buffer WriteonlyBoids{
	Boid data[];
}writeonly_boids;

layout (binding = 2) buffer ReadonlyIndices{
	uint data[];
}readonly_indices;

layout (binding = 3) buffer WriteonlyIndices{
	uint data[];
}writeonly_indices;

layout (binding = 4) buffer GridCounters{
	uint data[];
}grid_counters;

layout (binding = 5) buffer GridOffsets{
	uint data[];
}grid_offsets;

layout (binding = 6) buffer GridIndices{
	GridIndex data[];
}grid_indices;

layout (binding = 7) buffer GridOffsetSums{
	uint data[];
}grid_offset_sums;

vec2 transform_position(vec2 v)
{
	vec2 pos = v;
	pos = (vec3(v, 1.0) * PC.affine).xy;
	return pos.xy;
}


uint splitmix32(inout uint state)
{
	state += 2654435769u;
	uint s = state;
	s ^= s >> 16;
	s *= 0x85ebca6b;
	s ^= s >> 13;
	s *= 0xc2b2ae35;
	s ^= s >> 16;
	return s;
}

// https://www.romu-random.org
#define ROMU_ROTL32(d, l) ((d<<(l)) |  (d>>(8*4-(l))))

uint romu_mono_init(uint seed)
{
	seed = splitmix32(seed);
	return (seed & 0x1fffffffu) + 1156979152u;
}

// Only use the low 16 bits
uint romu_mono(inout uint state)
{
	uint result = state >> 16;
	state *= 3611795771u;
	state = ROMU_ROTL32(state, 12);
	return result;
}

float romu_mono_float(inout uint state)
{
	uint high = romu_mono(state) & 0x0000FFFF;
	uint low = romu_mono(state) & 0x0000FFFF;
	uint data = (low) | (high << 16);
	data &= 0x007FFFFF;
	data |= 0x40000000;
	return uintBitsToFloat(data) - 3.0f;
}

float lerp(float a, float b, float t)
{
	return (b-a) * t + a;
}
