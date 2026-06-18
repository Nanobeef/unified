#version 450 core
#pragma shader_stage(fragment)

layout(location = 0) in vec4 in_color;
layout(location = 1) in vec2 in_texture;

layout(location = 0) out vec4 out_color;

layout(set = 0, binding = 0) uniform sampler2D glyph_cache;
layout(set = 0, binding = 1) uniform sampler2D color_image;

void main()
{
	if(in_texture.x < 0.0)
	{
		vec4 texture_color = texture(color_image, -in_texture);
		out_color = texture_color;
		out_color.a = 1.0;
	}
	else if(in_texture.x > 0.0)
	{
		float c = textureLod(glyph_cache, in_texture, 0).r;
		out_color = in_color * c;
	}
	else
	{
		out_color = in_color;
	}
}

