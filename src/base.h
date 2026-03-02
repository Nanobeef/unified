#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <stdarg.h>
#include <math.h>
#include <time.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef s8 b8;
typedef s32 b32;
typedef float f32;
typedef double f64;

#define U8_MAX UINT8_MAX
#define U16_MAX UINT16_MAX
#define U32_MAX UINT32_MAX
#define U64_MAX UINT64_MAX

#define S8_MAX INT8_MAX
#define S16_MAX INT16_MAX
#define S32_MAX INT32_MAX
#define S64_MAX INT64_MAX

#define S8_MIN INT8_MIN
#define S16_MIN INT16_MIN
#define S32_MIN INT32_MIN
#define S64_MIN INT64_MIN

#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

#define Min(a,b) (((a) < (b)) ? (a) : (b))
#define Max(a,b) (((a) > (b)) ? (a) : (b))

#define Arrlen( XXX ) (sizeof(XXX) / sizeof((XXX)[0]))

#define ForwardAlign(n, p) (((u64)(n) + ((u64)(p) - 1)) & (~((u64)(p) -1)))

static u64 next_power_of_two(u64 x)
{
    if(x == 0)
    {
        return 1;
    }
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    x |= x >> 32;
    x++;
    return x;
}

#define Align( x ) (__attribute__((aligned(x))))


#if defined(__TINYC__)
	#define COMPILER_TCC 1
	#define DEBUG
#elif defined (__GNUC__)
	#define COMPILER_GCC 1
	#if defined(_DEBUG)
		#define DEBUG
	#endif
#elif defined (__clang__)
	#define COMPILER_CLANG 1
	#define COMPILER_GCC 1
	#if defined(_DEBUG)
		#define DEBUG
	#endif
#else
	#error Compiler unknown
#endif

#if defined(__linux__)
	#define OS_LINUX 1
#elif defined(_WIN64)
	#define OS_WINDOWS 1
#elif defined(__APPLE__) && defined(__MACH__)
	#define OS_MAC 1
#elif defined(__ANDROID__)
	#define OS_ANDROID 1
#else
	#error OS unknown
#endif

#if defined(__x86_64__)
	#define ARCH_X86_64
#elif defined(__aarch64__)
	#define ARCH_ARM64
#else
	#error Architecture unknown
#endif

#if defined(ARCH_X86_64)

#endif


#define CURRENT_FILE __FILE__
#define CURRENT_LINE __LINE__
#define CURRENT_TIME __TIME__
#define CURRENT_DATE __DATE__


#ifdef OS_LINUX
	#include <unistd.h>
	#include <sys/wait.h>
	#include <pthread.h>
#endif


// Sometimes a function pointer will be cast to and from an atomic u64
#if __SIZEOF_POINTER__ != 8
	#error This program only supports 64-bit machines.
#endif




















