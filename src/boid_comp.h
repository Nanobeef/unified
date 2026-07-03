
#extension GL_EXT_shader_explicit_arithmetic_types_float16 : require
#extension GL_EXT_shader_16bit_storage : require
#extension GL_KHR_shader_subgroup_basic : enable

layout (local_size_x = 256) in;

layout(push_constant) uniform PushConstant{
	uint boid_count;
	uint random_seed;	
}PC;

struct Boid{
	f16vec2 position;
	f16vec2 velocity;
};

layout (binding = 0) readonly buffer ReadonlyBoids{
	Boid data[];
}readonly_boids;

layout (binding = 1) writeonly buffer WriteonlyBoids{
	Boid data[];
}writeonly_boids;

layout (binding = 2) readonly buffer ReadonlyIndices{
	uint data[];
}readonly_indices;

layout (binding = 3) writeonly buffer WriteonlyIndices{
	uint data[];
}writeonly_indices;


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
