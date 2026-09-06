

typedef struct{
	s32 velocity;
	u64 press_time;
	u64 release_time;
	f32 phase;
	f32 amp;
}MidiKey;

typedef struct{
	snd_seq_t *midi_sequencer;
	Event *event_ring_buffer;

	snd_pcm_t *pcm_handle;

	Thread *thread;
	Mutex mutex;
	Semaphore semaphore;
	b32 run_thread;



	u32 buffer_frames;
	u32 channels;
	u32 sample_rate;


	MidiKey *keys;




}AudioDevice;

AudioDevice* create_audio_device(Arena *arena);
void destroy_audio_device(AudioDevice *device);
u32 poll_audio_device(AudioDevice *device, Event *event_ring_buffer);
