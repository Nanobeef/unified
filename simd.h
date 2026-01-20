
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
#endif
#ifdef AVX2_CORE
#endif
#ifdef AVX512_CORE
#endif

#define align( x ) (__attribute__((aligned(x))))

typedef union Vec2f32{
	struct{f32 s[2];};
	struct{f32 x,y;};
	struct{f32 a,b;};
}Vec2f32;





















