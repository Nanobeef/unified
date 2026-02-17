#version 450 core
#pragma shader_stage(fragment)

layout(location = 0) in vec4 in_color;
layout(location = 1) in vec2 in_texture;

layout(location = 0) out vec4 out_color;

void main()
{
	out_color = in_color;
}

