

u64 read_tsc();
u64 read_tscp();
u64 get_tsc_freq();

typedef struct{
	u64 tsc_freq;			
	u64 begin, end;
	u64 *ring;

}Chronometer;


Chronometer init_chronometer(Arena *arena, u32 ring_size);
void chron_begin(Chronometer *cm);
void chron_push(Chronometer *cm);
u64 chron_end(Chronometer *cm);
u64 chron_read(Chronometer *cm);

#include <linux/perf_event.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>

typedef struct{
	s32 fd;
	u32 child_count;
	u64 value;
	u64 time_enabled;
	u64 time_running;;
}PerfCounter;

/* 
	PERF_TYPE_HARDWARE allowed config

			 PERF_COUNT_HW_CPU_CYCLES
					Total cycles.  Be wary of what happens during CPU frequency scaling.

			 PERF_COUNT_HW_INSTRUCTIONS
					Retired instructions.  Be careful, these can be affected by various issues, most notably hardware interrupt counts.

			 PERF_COUNT_HW_CACHE_REFERENCES
					Cache  accesses.  Usually this indicates Last Level Cache accesses but this may vary depending on your CPU.  This may include prefetches and coherency
					messages; again, this depends on the design of your CPU.

			 PERF_COUNT_HW_CACHE_MISSES
					Cache misses.  Usually this indicates Last Level Cache misses; this is intended to be used  in  conjunction  with  the  PERF_COUNT_HW_CACHE_REFERENCES
					event to calculate cache miss rates.

			 PERF_COUNT_HW_BRANCH_INSTRUCTIONS
					Retired branch instructions.  Prior to Linux 2.6.35, this used the wrong event on AMD processors.

			 PERF_COUNT_HW_BRANCH_MISSES
					Mispredicted branch instructions.

			 PERF_COUNT_HW_BUS_CYCLES
					Bus cycles, which can be different from total cycles.

			 PERF_COUNT_HW_STALLED_CYCLES_FRONTEND (since Linux 3.0)
					Stalled cycles during issue.

			 PERF_COUNT_HW_STALLED_CYCLES_BACKEND (since Linux 3.0)
					Stalled cycles during retirement.

			 PERF_COUNT_HW_REF_CPU_CYCLES (since Linux 3.3)
					Total cycles; not affected by CPU frequency scaling.
*/

PerfCounter perf_create_list(u32 count, const u64 *configs, PerfCounter* counters);
PerfCounter perf_create(u64 config);
PerfCounter perf_start(PerfCounter parent);
PerfCounter perf_end(PerfCounter parent);
PerfCounter perf_read(PerfCounter counter);
inline void sink(uint64_t x);
u64 chron_convert_ps(Chronometer *cm, u64 ts);
u64 chron_convert_ns(Chronometer *cm, u64 ts);
