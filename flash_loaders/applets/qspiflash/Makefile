# ----------------------------------------------------------------------------
#         SAM Software Package License
# ----------------------------------------------------------------------------
# Copyright (c) 2016, Atmel Corporation
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

# Makefile for compiling the qpsi initialization flash loader
AVAILABLE_TARGETS = sama5d2-generic sam9x60-generic

AVAILABLE_VARIANTS = sram

VARIANT = sram

TOP := ../../..

BINNAME = flash_loader-qspi

CONFIG_FLASH_LOADER = y
CONFIG_TIMER_POLLING = y
CONFIG_QSPI = y
CONFIG_HAVE_QSPI_DMA = n

obj-y += flash_loaders/applets/qspiflash/qspi_flash_loader.o
obj-y += flash_loaders/applets/qspiflash/pin_config.o

include $(TOP)/scripts/Makefile.rules
