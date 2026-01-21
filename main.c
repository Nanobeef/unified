
#include "base.h"
#include "simd.h"


#include <unistd.h>
#include <time.h>

u64 get_time_ns(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_REALTIME, &ts);
	return (u64)ts.tv_nsec + (u64)ts.tv_sec * 1000000000lu;
}

typedef struct String8{
	u64 size;	
	u8 *data;
}String8;

#define str8_lit( STR ) ((String8){.size = sizeof(STR)-1, .data = (u8*)(STR)})

String8 str8_alloc(u64 size)
{
	String8 str = {
		.size = size,
		.data = malloc(size),
	};
	return str;
}

s32 main(void)
{
	String8 ss = str8_lit("HELLO");
	return 0;
}


