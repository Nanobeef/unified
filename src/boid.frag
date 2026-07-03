#version 460

layout(location = 0) in vec4 in_color;
layout(location = 1) in vec2 in_velocity;

layout(location = 0) out vec4 out_color;

layout(push_constant) uniform PushConstant{
	vec4 color;
}PC;

void main()
{
	out_color = in_color;


}
