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

# Makefile for compiling the ETH LWIP example
AVAILABLE_TARGETS = sama5d2-ptc-ek sama5d2-xplained sama5d27-som1-ek\
                    sama5d3-xplained sama5d3-ek \
                    sama5d4-xplained sama5d4-ek \
                    sam9g25-ek sam9g35-ek sam9x25-ek sam9x35-ek \
                    same70-xplained samv71-xplained \
                    sam9x60-ek sam9x60-curiosity

AVAILABLE_VARIANTS = ddram qspi0

VARIANT ?= ddram

TOP := ../..

BINNAME = eth_lwip

CONFIG_NET = y
CONFIG_TWI = y
CONFIG_TWI_AT24 = y
CONFIG_LIB_LWIP = y
CONFIG_LIB_LWIP_DEFAULT_CONFIG = n # Use lwip_config.h instead of default lib/lwip/softpack/include/arch/lwipopts.h
CONFIG_LIB_LWIP_IPV4 = y
CONFIG_LIB_LWIP_HTTP = y
CONFIG_LIB_LWIP_HTTP_FSDATA = y # Embed default webpages from lwip
CONFIG_LIB_LWIP_IPERF = y

# To include "lwip_config.h"
CFLAGS_INC += -I.

obj-y += examples/eth_lwip/main.o

include $(TOP)/scripts/Makefile.rules
