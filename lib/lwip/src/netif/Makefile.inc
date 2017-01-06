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

lwip-y += lib/lwip/src/netif/ethernet.o
lwip-y += lib/lwip/src/netif/ethernetif.o
lwip-y += lib/lwip/src/netif/lowpan6.o
lwip-y += lib/lwip/src/netif/slipif.o
lwip-y += lib/lwip/src/netif/ppp/auth.o
lwip-y += lib/lwip/src/netif/ppp/chap_ms.o
lwip-y += lib/lwip/src/netif/ppp/chap-md5.o
lwip-y += lib/lwip/src/netif/ppp/chap-new.o
lwip-y += lib/lwip/src/netif/ppp/fsm.o
lwip-y += lib/lwip/src/netif/ppp/ipcp.o
lwip-y += lib/lwip/src/netif/ppp/lcp.o
lwip-y += lib/lwip/src/netif/ppp/magic.o
lwip-y += lib/lwip/src/netif/ppp/polarssl/md5.o
lwip-y += lib/lwip/src/netif/ppp/upap.o
lwip-y += lib/lwip/src/netif/ppp/ppp.o
lwip-y += lib/lwip/src/netif/ppp/pppoe.o
lwip-y += lib/lwip/src/netif/ppp/vj.o
