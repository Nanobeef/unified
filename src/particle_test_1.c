


typedef struct{
	u32x2 pos;
	s32x2 vel;
}Particle1;

const u32 particle_test1_grid_square_size = 64;

u64 particle_test1_buffer_size(u32 particle_count)
{
	return particle_count * sizeof(Particle1) + ((u64)particle_test1_grid_square_size * (u64)particle_test1_grid_square_size) * sizeof(u32) * 2;
}

void particle_test_1(u32 particle_count, u32* buffer, b32 should_init)
{
	u32 grid_square_size = particle_test1_grid_square_size;
	u32 grid_count = grid_square_size * grid_square_size;
	u32 grid_rsh = 32 - 6;

	RomuQuad rq = romu_quad_seed(10233056121);
	Particle1 *particles = (void*)buffer;	
	u32 *counters = (void*)(particles + particle_count);
	u32 *offsets = (void*)(counters + grid_count);
	
	if(should_init)
	{
		for(u32 i = 0; i < particle_count; i++)
		{
			u64 r;
			r = romu_quad(&rq);
			memcpy(particles + i, &r, 8);
			r = romu_quad(&rq);
			memcpy((u8*)(particles + i) + 8, &r, 8);
			particles[i].vel = s32x2_rsh1(particles[i].vel, 12);
		}
	}


	for(u32 i = 0; i < particle_count; i++)
	{
		u32x2 pos = particles[i].pos;
		s32x2 vel = particles[i].vel;

		pos.x += vel.x;
		pos.y += vel.y;

		particles[i].pos = pos;
		particles[i].vel = vel;
		
	}

	for(u32 i = 0; i < grid_count; i++)
	{
		counters[i] = 0;
	}

	for(u32 i = 0; i < particle_count; i++)
	{
		u32x2 shp = u32x2_rsh1(particles[i].pos, grid_rsh);	
		u32 index = (shp.y * 64) + shp.x;
		counters[index]++;
	}

	u32 accum = 0;
	for(u32 i = 0; i < grid_count; i++)
	{
		offsets[i] = accum;
		accum += counters[i];
		counters[i] = 0;
	}

	Particle1 particle = particles[0];
	for(u32 i = 0; i < particle_count; i++)
	{
		u32x2 shp = u32x2_rsh1(particle.pos, grid_rsh);	
		u32 index = (shp.y * 64) + shp.x;
		u32 slot = offsets[index] + counters[index];
		counters[index]++;
		Particle1 temp = particles[slot];
		particles[slot] = particle;
		particle = temp;
	}
}
