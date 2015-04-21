#ifndef _COMPILER_DEFINES_HEADER_
#define _COMPILER_DEFINES_HEADER_

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

#endif				/* _COMPILER_DEFINES_HEADER_ */
