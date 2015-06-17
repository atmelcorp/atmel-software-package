#ifndef _COMPILER_H_
#define _COMPILER_H_

#if defined(__CC_ARM)
	#define WEAK __attribute__((weak))
	#define CONSTRUCTOR __attribute__((constructor))
	#define SECTION(a) __attribute__((__section__(a)))
	#define ALIGNED(a) __attribute__((__aligned__(a)))
#elif defined(__ICCARM__)
	#define WEAK __weak
	#define CONSTRUCTOR
	#define SECTION(a) _Pragma(location = a)
	#define ALIGNED(a) _Pragma(data_alignment = a)
#elif defined(__GNUC__)
	#define WEAK __attribute__((weak))
	#define CONSTRUCTOR __attribute__((constructor))
	#define SECTION(a) __attribute__((__section__(a)))
	#define ALIGNED(a) __attribute__((__aligned__(a)))
#else
	#error Unknown compiler!
#endif

#if defined(__ICCARM__)
	#define DSB()  asm("dsb")
	#define ISB()  asm("isb")
	#define COMPILER_BARRIER()
#elif defined(__GNUC__) || defined(__CC_ARM)
	#define DSB()  asm volatile ("dsb":::"memory")
	#define ISB()  asm volatile ("isb":::"memory")
	#define COMPILER_BARRIER()  asm volatile ("":::"memory")
#else
	#error Unknown compiler!
#endif


#ifndef NULL
	#define NULL ((void*)0)
#endif

#define ARRAY_SIZE(x) (sizeof ((x)) / sizeof(*(x)))

#define _STRINGY_EXPAND(x) #x
#define STRINGIFY(x) _STRINGY_EXPAND(x)

#define BIG_ENDIAN_TO_HOST(x) (((x) & 0xFF) << 24) | (((x) & 0xFF00) << 8) \
		| (((x) & 0xFF0000) >> 8) | (((x) & 0xFF000000) >> 24)

#endif /* _COMPILER_H_ */
