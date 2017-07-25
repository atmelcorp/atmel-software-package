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

# Makefile for compiling the Secure Digital Memory Card example
AVAILABLE_TARGETS = sama5d2-xplained sama5d27-som1-ek \
                    sama5d3-ek sama5d3-xplained \
                    sama5d4-ek sama5d4-xplained \
                    sam9g15-ek sam9g25-ek sam9g35-ek sam9x25-ek sam9x35-ek \
                    same70-xplained samv71-xplained
AVAILABLE_VARIANTS = ddram
VARIANT ?= ddram

TOP := ../..

BINNAME = sdcard

CONFIG_SDMMC = y
CONFIG_LIB_SDMMC = y
CONFIG_LIB_FATFS = y
CONFIG_CRYPTO = y
CONFIG_CRYPTO_SHA = y

CFLAGS_INC += -I$(TOP)/examples/sdmmc_sdcard

# Uncomment the definition below when using a board that features an
# ultra high speed device.
#
# CFLAGS_DEFS += -DSDMMC_USE_FASTEST_CLK

# Uncomment selected definitions below if you need the binary to shrink.
#
# CFLAGS_DEFS += -DSDMMC_TRIM_INFO
# CFLAGS_DEFS += -DSDMMC_TRIM_LOW_VOLTAGE
# CFLAGS_DEFS += -DSDMMC_TRIM_MMC
# CFLAGS_DEFS += -DSDMMC_TRIM_SDIO
#
# Uncomment the few definitions below if you wish to selectively override the
# global TRACE_LEVEL, which filters traces out at compile-time.
# Also, consider forcing trace_level=TRACE_LEVEL_DEBUG in utils/trace.c,
# otherwise the default level may filter out your extra traces at runtime.
#
# CFLAGS_DEFS += -DSDMMC_LIB_TRACE_LEVEL=3
# CFLAGS_DEFS += -DSDMMC_DRV_TRACE_LEVEL=3

obj-y += examples/sdmmc_sdcard/main.o

include $(TOP)/scripts/Makefile.rules
