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

# Makefile for compiling the USB Mass Storage example

TOP := ../..

BINNAME = usb_mass_storage

CONFIG_LIB_USB = y
CONFIG_LIB_USB_MSD = y
CONFIG_LIB_STORAGEMEDIA = y
CONFIG_LIB_SDMMC = y

# Uncomment the few definitions below if you wish to selectively override the
# global TRACE_LEVEL, which filters traces out at compile-time.
# Also, consider forcing trace_level=TRACE_LEVEL_DEBUG in utils/trace.c,
# otherwise the default level may filter out your extra traces at runtime.
#
# CFLAGS_DEFS += -DSDMMC_LIB_TRACE_LEVEL=3
# CFLAGS_DEFS += -DSDMMC_DRV_TRACE_LEVEL=3

obj-y += examples/usb_mass_storage/main.o
obj-y += examples/usb_mass_storage/main_descriptors.o
obj-y += examples/usb_common/main_usb_common.o

include $(TOP)/scripts/Makefile.rules
