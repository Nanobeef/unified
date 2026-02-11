

#if defined(COMPILER_TCC)
	#define NO_INTRINSICS
#else
	#if \
	defined(__SSE__) && \
	defined(__SSE2__)
		#include <xmmintrin.h> // SSE
		#include <emmintrin.h> // SSE2
		#define SSE_CORE
	#endif
	#if (defined(__AVX__) && defined(__AVX2__))
		#include <immintrin.h>
		#define AVX2_CORE
	#endif
	#if (defined(__AVX512F__) && defined(__AVX512CD__) && defined(__AVX512DQ__) \
	 && defined(__AVX512VL__) && defined(__AVX512BW__)) 
		#include <immintrin.h>
		#define AVX512_CORE
	#endif
#endif

#ifdef SSE_CORE
	#define F64X2_SSE
	#define F32X4_SSE
#endif
#ifdef AVX2_CORE
#endif
#ifdef AVX512_CORE
#endif

#include "u32x2.h"

#include "f32.h"
#include "f32x2.h"
#include "f32x4.h"
#include "f64x2.h"

#include "u32x2.c"

#include "f32.c"
#include "f32x2.c"
#include "f32x4.c"
#include "f64x2.c"


/* SIMD Vector Sizes:

	128-bit:
		f32x4, f64x2, s8x8, s16x8, s32x4, s64x2,
	256-bit:
		f32x8, f64x4, s8x32, s16x16, s32x8, s64x4,
	512-bit:
		f32x16, f64x8, s8x64, s16x32, s32x16, s64x8,
*/

/* Useful Vector Sizes:
		
*/






















