

#if !(defined(COMPILER_GCC) || defined(COMPILER_CLANG))
	#error hello
#endif

#include <immintrin.h>
#ifdef SSE_CORE
#endif
#ifdef AVX2_CORE
#endif
#ifdef AVX512_CORE
#endif

