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

ifeq ($(CONFIG_SAMBA_APPLET),y)

BINNAME := $(BINNAME)_$(TARGET)_$(VARIANT)

CFLAGS_INC += -I$(TOP)/samba_applets/common

CFLAGS += -mno-unaligned-access -DDMA_SG_ITEM_POOL_SIZE=2

obj-y += samba_applets/common/applet_main.o
obj-y += samba_applets/common/applet_legacy.o
obj-y += samba_applets/common/console_pin_defs_$(chip-family).o

ifeq ($(VARIANT),sram)
gnu-linker-script-$(CONFIG_SOC_SAM9XX5) = $(TOP)/samba_applets/common/sam9xx5/sram.ld
gnu-debug-script-$(CONFIG_SOC_SAM9XX5) = $(TOP)/samba_applets/common/sam9xx5/sram.gdb
iar-linker-script-$(CONFIG_SOC_SAM9XX5) = $(TOP)/samba_applets/common/sam9xx5/sram.icf

gnu-linker-script-$(CONFIG_SOC_SAMA5D2) = $(TOP)/samba_applets/common/sama5d2/sram.ld
gnu-debug-script-$(CONFIG_SOC_SAMA5D2) = $(TOP)/samba_applets/common/sama5d2/sram.gdb
iar-linker-script-$(CONFIG_SOC_SAMA5D2) = $(TOP)/samba_applets/common/sama5d2/sram.icf

gnu-linker-script-$(CONFIG_SOC_SAMA5D3) = $(TOP)/samba_applets/common/sama5d3/sram.ld
gnu-debug-script-$(CONFIG_SOC_SAMA5D3) = $(TOP)/samba_applets/common/sama5d3/sram.gdb
iar-linker-script-$(CONFIG_SOC_SAMA5D3) = $(TOP)/samba_applets/common/sama5d3/sram.icf

gnu-linker-script-$(CONFIG_SOC_SAMA5D4) = $(TOP)/samba_applets/common/sama5d4/sram.ld
gnu-debug-script-$(CONFIG_SOC_SAMA5D4) = $(TOP)/samba_applets/common/sama5d4/sram.gdb
iar-linker-script-$(CONFIG_SOC_SAMA5D4) = $(TOP)/samba_applets/common/sama5d4/sram.icf

gnu-linker-script-$(CONFIG_SOC_SAMV71) = $(TOP)/samba_applets/common/samv71/sram.ld
gnu-debug-script-$(CONFIG_SOC_SAMV71) = $(TOP)/samba_applets/common/samv71/sram.gdb
iar-linker-script-$(CONFIG_SOC_SAMV71) = $(TOP)/samba_applets/common/samv71/sram.icf
endif

ifeq ($(VARIANT),ddram)
gnu-linker-script-$(CONFIG_SOC_SAM9XX5) = $(TOP)/samba_applets/common/sam9xx5/ddram.ld
gnu-debug-script-$(CONFIG_SOC_SAM9XX5) = $(TOP)/samba_applets/common/sam9xx5/ddram.gdb
iar-linker-script-$(CONFIG_SOC_SAM9XX5) = $(TOP)/samba_applets/common/sam9xx5/ddram.icf

gnu-linker-script-$(CONFIG_SOC_SAMA5D2) = $(TOP)/samba_applets/common/sama5d2/ddram.ld
gnu-debug-script-$(CONFIG_SOC_SAMA5D2) = $(TOP)/samba_applets/common/sama5d2/ddram.gdb
iar-linker-script-$(CONFIG_SOC_SAMA5D2) = $(TOP)/samba_applets/common/sama5d2/ddram.icf

gnu-linker-script-$(CONFIG_SOC_SAMA5D3) = $(TOP)/samba_applets/common/sama5d3/ddram.ld
gnu-debug-script-$(CONFIG_SOC_SAMA5D3) = $(TOP)/samba_applets/common/sama5d3/ddram.gdb
iar-linker-script-$(CONFIG_SOC_SAMA5D3) = $(TOP)/samba_applets/common/sama5d3/ddram.icf

gnu-linker-script-$(CONFIG_SOC_SAMA5D4) = $(TOP)/samba_applets/common/sama5d4/ddram.ld
gnu-debug-script-$(CONFIG_SOC_SAMA5D4) = $(TOP)/samba_applets/common/sama5d4/ddram.gdb
iar-linker-script-$(CONFIG_SOC_SAMA5D4) = $(TOP)/samba_applets/common/sama5d4/ddram.icf

gnu-linker-script-$(CONFIG_SOC_SAMV71) = $(TOP)/samba_applets/common/samv71/ddram.ld
gnu-debug-script-$(CONFIG_SOC_SAMV71) = $(TOP)/samba_applets/common/samv71/ddram.gdb
iar-linker-script-$(CONFIG_SOC_SAMV71) = $(TOP)/samba_applets/common/samv71/ddram.icf
endif

gnu-cstartup-$(CONFIG_ARCH_ARMV5TE) = samba_applets/common/cstartup_gnu_v5te_v7a.o
iar-cstartup-$(CONFIG_ARCH_ARMV5TE) = samba_applets/common/cstartup_iar_v5te_v7a.o
gnu-cstartup-$(CONFIG_ARCH_ARMV7A) = samba_applets/common/cstartup_gnu_v5te_v7a.o
iar-cstartup-$(CONFIG_ARCH_ARMV7A) = samba_applets/common/cstartup_iar_v5te_v7a.o
gnu-cstartup-$(CONFIG_ARCH_ARMV7M) = samba_applets/common/cstartup_gnu_v7m.o
iar-cstartup-$(CONFIG_ARCH_ARMV7M) = samba_applets/common/cstartup_iar_v7m.o

iar-debug-script-y =
iar-flashloader-script-y =

CONFIG_BOOTSTRAP=n

endif
