
u64 get_time_ns(void);
u64 get_time_us(void);
u64 get_time_ms(void);
u64 get_time_s(void);

u64 get_epoch_ns(void);
u64 get_epoch_us(void);
u64 get_epoch_ms(void);
u64 get_epoch_s(void);

#define TIME_CALL( CALL ) ({u64 time = get_time_ns(); CALL; time = get_time_ns() - time; time;})
