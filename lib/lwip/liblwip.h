#ifndef _LIB_LWIP_H_
#define _LIB_LWIP_H_

/* Define NO_INIT attribute */
#if defined   ( __CC_ARM   )
    #define NO_INIT
#elif defined ( __ICCARM__ )
    #define NO_INIT __no_init
#elif defined (  __GNUC__  )
    #define NO_INIT
#endif

/*
 * drivers
 */

#include "src/include/lwip/opt.h"
#include "src/include/lwip/tcp.h"
#include "src/include/lwip/init.h"
#include "src/include/lwip/memp.h"
#include "src/include/lwip/udp.h"
#include "src/include/lwip/dhcp.h"
#include "src/include/lwip/def.h"
#include "arch/sys_arch.h"
#include "netif/ethif.h"

#endif /* _LIB_LWIP_H */
