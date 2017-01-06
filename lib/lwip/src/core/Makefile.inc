# ----------------------------------------------------------------------------
#         SAM Software Package License
# ----------------------------------------------------------------------------
# Copyright (c) 2015, Atmel Corporation
#
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# - Redistributions of source code must retain the above copyright notice,
# this list of conditions and the disclaimer below.
#
# Atmel's name may not be used to endorse or promote products derived from
# this software without specific prior written permission.
#
# DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
# DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
# LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
# OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
# LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
# NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
# EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

lwip-y += lib/lwip/src/core/dns.o
lwip-y += lib/lwip/src/core/init.o
lwip-y += lib/lwip/src/core/mem.o
lwip-y += lib/lwip/src/core/memp.o
lwip-y += lib/lwip/src/core/netif.o
lwip-y += lib/lwip/src/core/pbuf.o
lwip-y += lib/lwip/src/core/raw.o
lwip-y += lib/lwip/src/apps/snmp/snmp_asn1.o
lwip-y += lib/lwip/src/apps/snmp/snmp_mib2.o
lwip-y += lib/lwip/src/apps/snmp/snmp_mib2_interfaces.o
lwip-y += lib/lwip/src/apps/snmp/snmp_msg.o
lwip-y += lib/lwip/src/core/stats.o
lwip-y += lib/lwip/src/core/def.o
lwip-y += lib/lwip/src/core/sys.o
lwip-y += lib/lwip/src/core/tcp.o
lwip-y += lib/lwip/src/core/tcp_in.o
lwip-y += lib/lwip/src/core/tcp_out.o
lwip-y += lib/lwip/src/core/udp.o
lwip-y += lib/lwip/src/core/inet_chksum.o
lwip-y += lib/lwip/src/core/ip.o
lwip-y += lib/lwip/src/core/timeouts.o

lwip-$(CONFIG_LIB_LWIP_IPV4) += lib/lwip/src/core/ipv4/dhcp.o
lwip-$(CONFIG_LIB_LWIP_IPV4) += lib/lwip/src/core/ipv4/autoip.o
lwip-$(CONFIG_LIB_LWIP_IPV4) += lib/lwip/src/core/ipv4/etharp.o
lwip-$(CONFIG_LIB_LWIP_IPV4) += lib/lwip/src/core/ipv4/icmp.o
lwip-$(CONFIG_LIB_LWIP_IPV4) += lib/lwip/src/core/ipv4/igmp.o
lwip-$(CONFIG_LIB_LWIP_IPV4) += lib/lwip/src/core/ipv4/ip4_addr.o
lwip-$(CONFIG_LIB_LWIP_IPV4) += lib/lwip/src/core/ipv4/ip4_frag.o
lwip-$(CONFIG_LIB_LWIP_IPV4) += lib/lwip/src/core/ipv4/ip4.o

lwip-$(CONFIG_LIB_LWIP_IPV6) += lib/lwip/src/core/ipv6/icmp6.o
lwip-$(CONFIG_LIB_LWIP_IPV6) += lib/lwip/src/core/ipv6/inet6.o
lwip-$(CONFIG_LIB_LWIP_IPV6) += lib/lwip/src/core/ipv6/ip6_addr.o
lwip-$(CONFIG_LIB_LWIP_IPV6) += lib/lwip/src/core/ipv6/ip6.o
