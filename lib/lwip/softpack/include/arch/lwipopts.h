#if !defined LWIPOPTS_H
#define LWIPOPTS_H

#define NO_SYS                          1
#define NO_SYS_NO_TIMERS                1

#define LWIP_MPU_COMPATIBLE             0
#define LWIP_TCPIP_CORE_LOCKING         0
#define LWIP_TCPIP_CORE_LOCKING_INPUT   0
#define SYS_LIGHTWEIGHT_PROT            0

#define MEM_ALIGNMENT                   4

#define LWIP_ARP                        1
#define LWIP_ETHERNET                   LWIP_ARP

#define LWIP_IPV4                       1
#define IP_REASSEMBLY                   0
#define IP_FRAG                         0

#define LWIP_ICMP                       1

#define LWIP_RAW                        0

#define LWIP_DHCP                       0

#define LWIP_AUTOIP                     0

#define LWIP_IGMP                       0

#define LWIP_DNS                        0

#define LWIP_UDP                        1

#define LWIP_TCP                        1

#define LWIP_EVENT_API                  0
#define LWIP_CALLBACK_API               1

#define LWIP_NETCONN                    0
#define LWIP_SOCKET                     0
#define LWIP_STATS                      1
#define LWIP_IPV6                       0
#define LWIP_PERF                       0

#endif /* LWIPOPTS_H */
