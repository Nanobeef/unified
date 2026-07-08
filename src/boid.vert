#version 460

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_velocity; 

layout(location = 0) out vec4 out_color;

layout(push_constant) uniform PushConstant{
	mat3 affine;
	float scale;
	uint boid_count;
	uint padding;
	uint kernel_index;
	uint src_index;
	uint dst_index;
	uvec2 grid_size;
	uvec2 pixel_size;
}PC;

vec2 transform_position(vec2 v)
{
	vec2 pos = v;
	pos = (vec3(v, 1.0) * PC.affine).xy;
	return pos.xy;
}

const vec2 vertices[3] = {
	vec2(0.0, -1.0),
	vec2(-0.5, 1.0),
	vec2(0.5, 1.0)
};
const vec4 colors[3] = {
	vec4(1.0, 0.0, 0.0, 1.0),
	vec4(0.0, 1.0, 0.0, 1.0),
	vec4(0.0, 0.0, 1.0, 1.0)
};
const vec2 center = vec2(0.0, 0.25);

void main()
{

	vec2 u = normalize(in_velocity);

	vec2 p = vertices[gl_VertexIndex % 3];

	p += center;
	p *= PC.scale * 0.0001;

	p *= mat2(
		-u.y, -u.x,
		u.x, -u.y
	);
	
	p += vec2(in_position);
	p = transform_position(p);

	gl_Position = vec4(p, 1.0, 1.0);

	out_color = colors[gl_VertexIndex % 3];
//	out_color = vec4(1.0, vec2(float(gl_InstanceIndex) / (PC.boid_count)), 1.0);
}
