
u64 get_time_ns(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return (u64)ts.tv_nsec + (u64)ts.tv_sec * 1000000000lu;
}

u64 get_time_us(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return (u64)ts.tv_nsec / 1000lu + (u64)ts.tv_sec * 1000000lu;
}

u64 get_time_ms(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return (u64)ts.tv_nsec / 1000000lu + (u64)ts.tv_sec * 1000lu;
}

u64 get_time_s(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return (u64)ts.tv_sec;
}

