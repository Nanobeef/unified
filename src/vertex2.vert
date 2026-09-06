#version 450 core
#pragma shader_stage(vertex)

layout(push_constant) uniform PushConstant{
	mat3 affine;
}pc;

vec2 transform_position(vec2 v)
{
	vec2 pos = v;
	pos = (vec3(v, 1.0) * pc.affine).xy;
	return pos.xy;
}

layout(location = 0) in vec4 in_color;
layout(location = 1) in vec2 in_position;
layout(location = 2) in vec2 in_texture;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec2 out_texture;

void main()
{
	vec2 position = transform_position(in_position);
	gl_Position = vec4(position, 1.0, 1.0);	
	out_color = in_color;
	out_texture = in_texture;
}
