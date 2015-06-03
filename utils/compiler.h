#ifndef _COMPILER_H_
#define _COMPILER_H_

/* Define WEAK attribute */
#ifndef WEAK
#if defined   ( __CC_ARM   )
#define WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ )
#define WEAK __weak
#elif defined (  __GNUC__  )
#define WEAK __attribute__ ((weak))
#endif
#endif

#define ARRAY_SIZE(x) (sizeof ((x)) / sizeof(*(x)))

#define _STRINGY_EXPAND(x) #x
#define STRINGIFY(x) _STRINGY_EXPAND(x)

#endif /* _COMPILER_H_ */
