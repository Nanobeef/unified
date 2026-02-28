#version 450 core
#pragma shader_stage(vertex)

layout(push_constant) uniform PushConstant{
	mat4 mvp;
}pc;

layout(location = 0) in vec4 in_color;
layout(location = 1) in vec3 in_position;
layout(location = 2) in vec2 in_texture;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec2 out_texture;

void main()
{
	vec4 position = pc.mvp * vec4(in_position, 1.0);
	gl_Position = position;
	out_color = in_color;
	out_texture = in_texture;
}
