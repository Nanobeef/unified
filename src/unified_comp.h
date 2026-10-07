



#define f16 float16_t
#define f32 float32_t
#define f64 float64_t

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define s8 int8_t
#define s16 int16_t
#define s32 int32_t
#define s64 int64_t

#define f16x2 f16vec2
#define f32x2 f32vec2
#define f64x2 f64vec2

#define u8x2 u8vec2
#define u16x2 u16vec2
#define u32x2 u32vec2
#define u64x2 u64vec2

#define s8x2 i8vec2
#define s16x2 i16vec2
#define s32x2 i32vec2
#define s64x2 i64vec2

#define f16x3 f16vec3
#define f32x3 f32vec3
#define f64x3 f64vec3

#define u8x3 u8vec3
#define u16x3 u16vec3
#define u32x3 u32vec3
#define u64x3 u64vec3

#define s8x3 i8vec3
#define s16x3 i16vec3
#define s32x3 i32vec3
#define s64x3 i64vec3

#define f16x4 f16vec4
#define f32x4 f32vec4
#define f64x4 f64vec4

#define u8x4 u8vec4
#define u16x4 u16vec4
#define u32x4 u32vec4
#define u64x4 u64vec4

#define s8x4 i8vec4
#define s16x4 i16vec4
#define s32x4 i32vec4
#define s64x4 i64vec4

#define f32m3 f32mat3x3
#define f32m2 f32mat2x2

#extension GL_EXT_shader_explicit_arithmetic_types : enable
#extension GL_EXT_debug_printf : enable
#extension GL_EXT_shader_realtime_clock : enable




#define Arrlen(X) (sizeof((X)[0]) / sizeof(X))

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


vec4 lerp(vec4 a, vec4 b, float t)
{
	return (b-a) * t + a;
}


float sd_circle(vec2 p, float r)
{
	return length(p) - r;
}

float sd_hexagram( in vec2 p, in float r )
{
    const vec4 k = vec4(-0.5,0.8660254038,0.5773502692,1.7320508076);
    p = abs(p);
    p -= 2.0*min(dot(k.xy,p),0.0)*k.xy;
    p -= 2.0*min(dot(k.yx,p),0.0)*k.yx;
    p -= vec2(clamp(p.x,r*k.z,r*k.w),r);
    return length(p)*sign(p.y);
}

float sd_rounded_x( in vec2 p, in float w, in float r )
{
    p = abs(p);
    return length(p-min(p.x+p.y,w)*0.5) - r;
}

float dot2(in vec2 v) {return dot(v,v);}

float sd_heart( in vec2 p )
{
    p.x = abs(p.x);

    if( p.y+p.x>1.0 )
        return sqrt(dot2(p-vec2(0.25,0.75))) - sqrt(2.0)/4.0;
    return sqrt(min(dot2(p-vec2(0.00,1.00)),
                    dot2(p-0.5*max(p.x+p.y,0.0)))) * sign(p.x-p.y);
}

struct Circle{
	vec2 position;
	float radius;
	uint data;
};

Circle random_circle(inout uint rs)
{
	Circle c;
	c.position = vec2(
		romu_mono_float(rs),
		romu_mono_float(rs)
	);
	c.radius = abs(romu_mono_float(rs)) / 100;
	c.radius = max(c.radius, 0.005);
	c.data = romu_mono(rs);
	return c;
}
