

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
#include "s32x2.h"

#include "f32.h"
#include "f32x2.h"
#include "f32x4.h"
#include "f64x2.h"

#include "u32x2.c"
#include "s32x2.c"

#include "f32.c"
#include "f32x2.c"
#include "f32x4.c"
#include "f64x2.c"


#include "f32m3.h"
#include "f32m3.c"



static f32x2 f32x2_cast_u32x2(u32x2 a)
{
	return f32x2_set(a.x, a.y);
}




















