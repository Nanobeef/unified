


#define f32 float 
#define u32 uint 
#define s32 int 
#define f32x2 vec2
#define u32x2 uvec2
#define s32x2 ivec2
#define f32x3 vec3
#define u32x3 uvec3
#define s32x3 ivec3
#define f32x4 vec4
#define u32x4 uvec4
#define s32x4 ivec4
#define f32m3 mat3x3
#define f32m2 mat2x2

#define KiB(n) ((u32)(n) << 10)
#define MiB(n) ((u32)(n) << 20)


/* 
	Disabled for now, using software to make the basic compatability version version.

	#extension GL_KHR_shader_subgroup_basic : enable
	#extension GL_KHR_shader_subgroup_ballot : enable
	#extension GL_NV_shader_subgroup_partitioned : enable
*/

#define Arrlen(X) (sizeof((X)[0]) / sizeof(X))

u32 splitmix32(inout u32 state)
{
	state += 2654435769u;
	u32 s = state;
	s ^= s >> 16;
	s *= 0x85ebca6b;
	s ^= s >> 13;
	s *= 0xc2b2ae35;
	s ^= s >> 16;
	return s;
}


u32 lowbias32(u32 x) {
    x ^= x >> 16u;
    x *= 0x7feb352du;
    x ^= x >> 15u;
    x *= 0x846ca68bu;
    x ^= x >> 16u;
    return x;
}

// https://www.romu-random.org
#define ROMU_ROTL32(d,lrot) ((d<<(lrot)) | (d>>(8*4-(lrot))))

u32 romu_mono(inout u32 state)
{
	u32 result = (state >> 16);
	state *= 3611795771u;
	state = ROMU_ROTL32(state, 12);
	return result;
}

u32 romu_mono_init(u32 seed)
{
	seed = (seed & 0x1fffffffu) + 1156979152u;
	romu_mono(seed);
	return seed;
}


u32 romu_mono_u32(inout u32 state)
{
	u32 high = romu_mono(state);
	u32 low = romu_mono(state);
	u32 data = (low) | (high << 16);
	return data;
}

f32 romu_mono_f32(inout u32 state)
{
	u32 data = romu_mono_u32(state);
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
	u32 data;
};

Circle random_circle(inout u32 rs)
{
	Circle c;
	c.position = vec2(
		romu_mono_f32(rs),
		romu_mono_f32(rs)
	);
	c.radius = abs(romu_mono_f32(rs)) / 100;
	c.radius = max(c.radius, 0.005);
	c.data = romu_mono(rs);
	return c;
}
