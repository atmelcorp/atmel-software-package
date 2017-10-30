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

# Makefile for compiling the USB Audio Speaker example
AVAILABLE_TARGETS = sam9g15-ek sam9g25-ek sam9g35-ek sam9x25-ek sam9x35-ek \
		    sama5d2-xplained \
		    sama5d3-ek \
		    sama5d4-ek \
		    samv71-xplained

AVAILABLE_VARIANTS = ddram

VARIANT ?= ddram

TOP := ../..

BINNAME = usb_audio_speaker

CONFIG_AUDIO = y
CONFIG_USB = y
CONFIG_LIB_USB = y
CONFIG_LIB_USB_AUDIO = y

obj-y += examples/usb_audio_speaker/main.o
obj-y += examples/usb_audio_speaker/main_descriptors.o
obj-y += examples/usb_common/main_usb_common.o

include $(TOP)/scripts/Makefile.rules
