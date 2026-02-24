#version 450 core
#pragma shader_stage(fragment)

layout(location = 0) in vec4 in_color;
layout(location = 1) in vec2 in_texture;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler2D glyph_cache;

void main()
{
	if(in_texture.x != 0.0)
	{
		float c = texture(glyph_cache, in_texture).r;
		out_color = vec4(c) * in_color;
	}
	else
	{
		out_color = in_color;
	}
}

