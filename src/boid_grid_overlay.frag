#version 460

layout(location = 0) in vec2 in_position;

layout(location = 0) out vec4 out_color;

#include "boid_comp.h"

vec4 lerp(vec4 a, vec4 b, float t)
{
	return (b-a) * t + a;
}


void main()
{
	uvec2 grid_index = uvec2(floor(in_position * vec2(PC.grid_size)));
	uint counter_index = PC.grid_size.x * grid_index.y + grid_index.x;


	uint counter = 0;
	float counter_color = 0.0;
	{
		counter = grid_offsets.data[counter_index];
		counter_color = float(counter) / (1024 * 1024 * 64);
	}




	vec2 cell_size = 1.0 / PC.grid_size;
	vec2 gmod = mod(in_position, cell_size);


	{
		float border_size = 0.05;
		gmod = gmod / cell_size;
		gmod = min(gmod, abs(1.0 - gmod));
		float d = min(gmod.x, gmod.y);
		d = smoothstep(border_size * 0.5, border_size, d * 2.0);


		float zoom = pow(pow(PC.affine[0][1],2.0) + pow(PC.affine[1][1], 2.0), 0.5);

		float pixel_area = (1.0 / PC.pixel_size.x) * (1.0 / PC.pixel_size.y);
		float grid_area = (1.0 / PC.grid_size.x) * (1.0 / PC.grid_size.y);
		grid_area *= zoom;
		float cell_area = grid_area / pixel_area;
		float border_strength = cell_area;



		d = lerp(d, 1.0, max(0.0, 1.0 - cell_area * 0.05));

		vec4 color = counter_color * vec4(1.0);
		out_color = vec4(d * color.rgb, 1.0);
	}




}
