#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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

#define KiB(n) ((u64)(n) << 10)
#define MiB(n) ((u64)(n) << 20)
#define GiB(n) ((u64)(n) << 30)

#define Min(a,b) (((a) < (b)) ? (a) : (b))
#define Max(a,b) (((a) > (b)) ? (a) : (b))

#define ForwardAlign(n, p) (((u64)(n) + ((u64)(p) - 1)) & (~((u64)(p) -1)))

#define Align( x ) (__attribute__((aligned(x))))

#if defined(__TINYC__)
	#define COMPILER_TCC 1
#elif defined (__GNUC__)
	#define COMPILER_GCC 1
#elif defined (__clang__)
	#define COMPILER_CLANG 1
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



