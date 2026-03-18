f32 freq_table[128] = {
    8.175799, 8.661957, 9.177024, 9.722718, 10.300861, 10.913382, 11.562326, 12.249857,
    12.978272, 13.750000, 14.567618, 15.433853, 16.351598, 17.323914, 18.354048, 19.445436,
    20.601722, 21.826764, 23.124651, 24.499715, 25.956544, 27.500000, 29.135235, 30.867706,
    32.703196, 34.647829, 36.708096, 38.890873, 41.203445, 43.653529, 46.249303, 48.999429,
    51.913087, 55.000000, 58.270470, 61.735413, 65.406391, 69.295658, 73.416192, 77.781746,
    82.406889, 87.307058, 92.498606, 97.998859, 103.826174, 110.000000, 116.540940, 123.470825,
    130.812783, 138.591315, 146.832384, 155.563492, 164.813778, 174.614116, 184.997211, 195.997718,
    207.652349, 220.000000, 233.081881, 246.941651, 261.625565, 277.182631, 293.664768, 311.126984,
    329.627557, 349.228231, 369.994423, 391.995436, 415.304698, 440.000000, 466.163762, 493.883301,
    523.251131, 554.365262, 587.329536, 622.253967, 659.255114, 698.456463, 739.988845, 783.990872,
    830.609395, 880.000000, 932.327523, 987.766603, 1046.502261, 1108.730524, 1174.659072, 1244.507935,
    1318.510228, 1396.912926, 1479.977691, 1567.981744, 1661.218790, 1760.000000, 1864.655046, 1975.533205,
    2093.004522, 2217.461048, 2349.318143, 2489.015870, 2637.020455, 2793.825851, 2959.955382, 3135.963488,
    3322.437581, 3520.000000, 3729.310092, 3951.066410, 4186.009045, 4434.922096, 4698.636287, 4978.031740,
    5274.040911, 5587.651703, 5919.910763, 6271.926976, 6644.875161, 7040.000000, 7458.620184, 7902.132820,
    8372.018090, 8869.844191, 9397.272573, 9956.063479, 10548.081821, 11175.303406, 11839.821527, 12543.853951
};

void *audio_thread(Thread *thread)
{
	AudioDevice *device = (AudioDevice*)atomic_load(&thread->data);
	
	Arena *arena = find_scratch(thread,0,0).arena;

	f32 *buffer = arena_push(arena, true, sizeof(f32) * device->buffer_frames * device->channels);
	f32 phase_inc_base = PI2 / device->sample_rate;


	u64 rate = 1000000000 / 1024;
	u64 end_time = get_time_ns(), start_time = get_time_ns();


	RomuQuad rq = romu_quad_seed(42);


	while(atomic_load(&device->run_thread))
	{
		end_time = get_time_ns();
		u64 elapsed_time = end_time - start_time;
		if(elapsed_time < rate && 0)
		{
			u64 sleep_time = rate - elapsed_time;
			print("sleep %t\n", sleep_time);
			usleep(sleep_time / 1000);
		}
		start_time = get_time_ns();

		Event e = {0};

		b32 check_events = true;
		while(check_events)
		{
			lock_mutex(&device->mutex);
			check_events = ring_buffer_pop(device->event_ring_buffer, &e);
			unlock_mutex(&device->mutex);
			if(check_events == false)
				break;

			switch(e.midi.type)
			{
				case MIDI_KEY:{
					MidiEvent m = e.midi;
					print("audio key %u: %t\n",m.key.note,  get_time_ns() - e.time);
					if(m.key.note > 128)
						break;
					device->keys[m.key.note].velocity = m.key.velocity;
					if(m.key.velocity)
					{
						device->keys[m.key.note].press_time = e.time;
						device->keys[m.key.note].phase = 0.0f;
						device->keys[m.key.note].amp = 0.0f;
					}
					else
					{
						device->keys[m.key.note].release_time = e.time;
					}
				};break;
			}
		}

		u64 time = get_time_ns();
		for(u32 i = 0; i < device->buffer_frames; i++)
		{
			f32 sample = 0.0f;
			u64 note_time = 1000000000;
			for(u32 j = 0; j < 128; j++)
			{
				MidiKey *m = device->keys + j;

				f32 target_amp = 0.0f;
				if(m->velocity)
				{
					target_amp = 0.1f;
				}

				f32 ramp_speed = 0.0005f;
				if(m->amp < target_amp)
					m->amp += ramp_speed;
				if(m->amp > target_amp)
					m->amp -= ramp_speed;




				f32 freq = freq_table[j];
				sample += sinf(m->phase) * m->amp;
				m->phase += phase_inc_base * freq;
				if(m->phase > PI2) 
					m->phase -= PI2;
			}
			buffer[i*2  ] = sample;
			buffer[i*2+1] = sample;

		}

		s32 frames = snd_pcm_writei(device->pcm_handle, buffer, device->buffer_frames);
		if(frames < 0) 
			snd_pcm_recover(device->pcm_handle, frames, 0);
		



	}
	return NULL;
}


AudioDevice* create_audio_device(Arena *arena)
{
	snd_seq_t *seq = 0;
	snd_seq_open(&seq, "default", SND_SEQ_OPEN_INPUT, 0);
	if(seq == 0)
	{
		print("Failed to create ALSA sequencer.\n");
		return 0;
	}

	snd_seq_set_client_name(seq, "Synth for Unified");
	s32 input_port = snd_seq_create_simple_port(seq, "input",
			SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
			SND_SEQ_PORT_TYPE_APPLICATION | SND_SEQ_PORT_TYPE_MIDI_GENERIC);
	snd_seq_nonblock(seq, true);

	snd_seq_client_info_t *cinfo;
	snd_seq_port_info_t *pinfo;

	snd_seq_client_info_alloca(&cinfo);
	snd_seq_port_info_alloca(&pinfo);

	snd_seq_client_info_set_client(cinfo, -1);
	Scratch scratch = find_scratch(0,0,0);
	while(snd_seq_query_next_client(seq, cinfo) >= 0)
	{
		String8 name = str8_cstr(scratch.arena, snd_seq_client_info_get_name(cinfo));
		if(str8_equal(name, str8_lit("Impact LX88+")))
		{
			s32 client = snd_seq_client_info_get_client(cinfo);
			snd_seq_port_info_set_client(pinfo, client);
			snd_seq_port_info_set_port(pinfo, -1);
			while(snd_seq_query_next_port(seq, pinfo) >= 0)
			{
				u32 cap = snd_seq_port_info_get_capability(pinfo);
				if((cap & SND_SEQ_PORT_CAP_READ) && (cap & SND_SEQ_PORT_CAP_SUBS_READ))
				{
					s32 port = snd_seq_port_info_get_port(pinfo);
					s32 err = snd_seq_connect_from(seq, input_port, client, port);
					continue;
					if(err >= 0)
						print("Connected port %u32 of %s\n", port + 1, name); 
					else
						print("Failed to connect\n");
				}
			}
			break;
		}
	}

	snd_pcm_t *pcm;
	if(snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0) < 0)
	{
		print("Failed to open alsa driver\n");
		return 0;
	}

	u32 sample_rate = 48000;
	u64 period_size = 256;
	u64 buffer_size = period_size * 4;

	snd_pcm_hw_params_t *params;
	snd_pcm_hw_params_alloca(&params);
	snd_pcm_hw_params_any(pcm, params);
	snd_pcm_hw_params_set_access(pcm, params, SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(pcm, params, SND_PCM_FORMAT_FLOAT_LE);
	snd_pcm_hw_params_set_channels(pcm, params, 2);
	snd_pcm_hw_params_set_rate_near(pcm, params, &sample_rate, 0);
	snd_pcm_hw_params_set_period_size_near(pcm, params, &period_size, 0);
	snd_pcm_hw_params_set_buffer_size_near(pcm, params, &buffer_size);

	snd_pcm_hw_params(pcm, params);

	AudioDevice *device = arena_push(arena, true, sizeof(AudioDevice));
	MidiKey *keys = arena_push(arena, true, sizeof(MidiKey) * 128);
	Event *ring_buffer = allocate_ring_buffer(arena, Event, 1024 * 8);

	*device = (AudioDevice) {
		.midi_sequencer = seq,
		.event_ring_buffer = ring_buffer,
		.mutex = create_mutex(),
		.semaphore = create_semaphore(0),
		.run_thread = true,
		.pcm_handle = pcm,
		.sample_rate = 44100,
		.buffer_frames = 256,
		.channels = 2,
		.keys = keys,
	};

	device->thread = start_thread(arena, 1024 * 1024 * 64, MiB(10), audio_thread, device);

	return device;	
}

void destroy_audio_device(AudioDevice *device)
{
	if(device == 0)
		return;
	
	atomic_store(&device->run_thread, false);
	lock_mutex(&device->mutex);
	binary_signal_semaphore(&device->semaphore);
	unlock_mutex(&device->mutex);

	destroy_thread(device->thread);

	snd_pcm_drain(device->pcm_handle);
	snd_pcm_close(device->pcm_handle);

	snd_seq_close(device->midi_sequencer);
	destroy_mutex(device->mutex);
	destroy_semaphore(device->semaphore);
}

u32 poll_audio_device(AudioDevice *device, Event *event_ring_buffer)
{
	if(device == 0)
		return 0;
	snd_seq_event_t *ev = NULL;
	u32 event_count = 0;
	u64 time = get_time_ns();
	while(snd_seq_event_input(device->midi_sequencer, &ev) > 0)
	{
		Event e = {.time = time, .audio_device_pointer = device, .type = EVENT_MIDI};
		event_count++;
		if(ev->type == SND_SEQ_EVENT_NOTEON || ev->type == SND_SEQ_EVENT_NOTEOFF)
		{
			e.midi.type = MIDI_KEY;
			e.midi.key.channel = ev->data.note.channel + 1;
			e.midi.key.note = ev->data.note.note;
			e.midi.key.velocity = ev->data.note.velocity;
			ring_buffer_push(event_ring_buffer, e);

			lock_mutex(&device->mutex);
			ring_buffer_push(device->event_ring_buffer, e);
			unlock_mutex(&device->mutex);
		}
	}
	return event_count;
}
