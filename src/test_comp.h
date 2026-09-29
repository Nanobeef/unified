

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
