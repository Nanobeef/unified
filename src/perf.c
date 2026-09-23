



u64 read_tsc()
{
	u32 low, high;
	__asm__ __volatile__("rdtsc" : "=a"(low), "=d"(high));
	return (u64)high << 32 | low;
}

u64 read_tscp()
{
#ifdef COMPILER_TCC
	u32 low, high;
	__asm__ __volatile__("lfence");
	__asm__ __volatile__("rdtsc" : "=a"(low), "=d"(high));
	__asm__ __volatile__("lfence");
#else
	u32 low, high, aux;
	__asm__ __volatile__("rdtscp" : "=a"(low), "=d"(high), "=c"(aux));
#endif 
	return (u64)high << 32 | low;
}


u64 get_tsc_freq()
{
	u64 time = get_time_ns();
	u64 tsc = read_tscp();
	struct timespec req = {0,10};
	nanosleep(&req, NULL);
	tsc = read_tscp() - tsc;
	time = get_time_ns() - time;

	u64 freq = (f64)(tsc) / (f64)(time) * 1000000000.0;
	u64 round = 100000000;
	freq = freq + round - (freq % round);
	return freq;
}

Chronometer init_chronometer(Arena *arena, u32 ring_size)
{
	Chronometer cm = {
		.tsc_freq = get_tsc_freq(),
	};
	print("freq = %u64\n", cm.tsc_freq);
	if(arena)
	{
		cm.ring = allocate_ring_buffer(arena, u64, ring_size);
	}
	return cm;
}

void chron_begin(Chronometer *cm)
{
	cm->begin = read_tscp();
}

void chron_push(Chronometer *cm)
{
	ring_buffer_push(cm->ring, read_tsc());
}

u64 chron_end(Chronometer *cm)
{
	cm->end = read_tscp();
	u64 elapsed = cm->end - cm->begin;
	u64 ps = (elapsed * 1000000000000) / cm->tsc_freq;
	return ps;
}

u64 chron_read(Chronometer *cm)
{
	u64 mark = 0;
	if(ring_buffer_pop(cm->ring, &mark))
	{
		u64 ps = ((mark - cm->begin) * 1000000000000) / cm->tsc_freq;
		return ps;
	}
	return 0;
}

PerfCounter perf_create_list(u32 count, const u64 *configs, PerfCounter* counters)
{
	if(count == 0)
	{
		return (PerfCounter){0};
	}
	struct perf_event_attr attr = {
		.type = PERF_TYPE_HARDWARE,
		.size = sizeof(struct perf_event_attr),
		.disabled = 1,
		.exclude_kernel = 1,
		.exclude_hv = 1,
		.read_format = PERF_FORMAT_TOTAL_TIME_RUNNING | PERF_FORMAT_TOTAL_TIME_ENABLED,
	};

	counters[0].fd = -1;
	counters[0].child_count = count - 1;
	for(u32 i = 0; i < count; i++)
	{
		attr.config = configs[i];
		counters[i].fd = syscall(__NR_perf_event_open, &attr, 0, -1 ,counters[0].fd, 0);
	}
	return counters[0];
}

PerfCounter perf_create(u64 config)
{
	PerfCounter counter = {0};
	perf_create_list(1, &config, &counter); 
	return counter;
}


PerfCounter perf_start(PerfCounter parent)
{
	ioctl(parent.fd, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);	
	ioctl(parent.fd, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);	
	return parent;
}


PerfCounter perf_end(PerfCounter parent)
{
	ioctl(parent.fd, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);	
	return parent;
}

PerfCounter perf_read(PerfCounter counter)
{
	u64 values[4];
	if(read(counter.fd, values, 3 * sizeof(u64)) != (3 * sizeof(u64)))
	{
		return counter;
	}
	counter.value = values[0];
	counter.time_enabled = values[1];
	counter.time_running = values[2];
	return counter;
}

inline void sink(uint64_t x)
{
    __asm__ volatile("" : "+r"(x) :: "memory");
}


u64 chron_convert_ps(Chronometer *cm, u64 ts)
{
	return (ts - cm->begin) * 1000000000000 / cm->tsc_freq;
}
u64 chron_convert_ns(Chronometer *cm, u64 ts)
{
	return (ts - cm->begin) * 1000000000 / cm->tsc_freq;
}

