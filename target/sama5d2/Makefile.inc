# ----------------------------------------------------------------------------
#         SAM Software Package License
# ----------------------------------------------------------------------------
# Copyright (c) 2015-2016, Atmel Corporation
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

ifeq ($(CONFIG_SOC_SAMA5D2),y)

CFLAGS_INC += -I$(TOP)/target/sama5d2

gnu-debug-lib-y ?= $(TOP)/target/sama5d2/toolchain/gnu/common.gdb
gnu-cstartup-y ?= target/sama5d2/toolchain/gnu/cstartup.o
iar-cstartup-y ?= target/sama5d2/toolchain/iar/cstartup.o

# SRAM variant
ifeq ($(VARIANT),sram)
gnu-linker-script-y ?= $(TOP)/target/sama5d2/toolchain/gnu/sram.ld
gnu-debug-script-y ?= $(TOP)/target/sama5d2/toolchain/gnu/sram.gdb
iar-linker-script-y ?= $(TOP)/target/sama5d2/toolchain/iar/sram.icf
iar-debug-script-y ?= $(TOP)/target/sama5d2/toolchain/iar/sram.mac
endif

# DDRAM variant
ifeq ($(VARIANT),ddram)
gnu-linker-script-y ?= $(TOP)/target/sama5d2/toolchain/gnu/ddram.ld
gnu-debug-script-y ?= $(TOP)/target/sama5d2/toolchain/gnu/ddram.gdb
bootstrap-linker-script-y ?= $(TOP)/target/sama5d2/toolchain/gnu/sram.ld
iar-linker-script-y ?= $(TOP)/target/sama5d2/toolchain/iar/ddram.icf
iar-debug-script-y ?= $(TOP)/target/sama5d2/toolchain/iar/ddram.mac
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D2_XPLAINED) ?= $(TOP)/flash_loaders/sama5d2-generic/sama5d2-xplained.board
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D27_SOM1_EK) ?= $(TOP)/flash_loaders/sama5d2-generic/sama5d27-som1-ek.board
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D2_PTC_EK) ?= $(TOP)/flash_loaders/sama5d2-generic/sama5d2-ptc-ek.board
endif

# QSPI0 variant
ifeq ($(VARIANT),qspi0)
gnu-linker-script-y ?= $(TOP)/target/sama5d2/toolchain/gnu/qspi0.ld
iar-linker-script-y ?= $(TOP)/target/sama5d2/toolchain/iar/qspi0.icf
iar-debug-script-y ?= $(TOP)/target/sama5d2/toolchain/iar/qspi.mac
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D2_XPLAINED) ?= $(TOP)/flash_loaders/sama5d2-generic/sama5d2-xplained.board
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D27_SOM1_EK) ?= $(TOP)/flash_loaders/sama5d2-generic/sama5d27-som1-ek.board
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D2_PTC_EK) ?= $(TOP)/flash_loaders/sama5d2-generic/sama5d2-ptc-ek.board
endif

# QSPI1 variant
ifeq ($(VARIANT),qspi1)
gnu-linker-script-y ?= $(TOP)/target/sama5d2/toolchain/gnu/qspi1.ld
iar-linker-script-y ?= $(TOP)/target/sama5d2/toolchain/iar/qspi1.icf
iar-debug-script-y ?= $(TOP)/target/sama5d2/toolchain/iar/qspi.mac
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D2_XPLAINED) ?= $(TOP)/flash_loaders/sama5d2-generic/sama5d2-xplained.board
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D27_SOM1_EK) ?= $(TOP)/flash_loaders/sama5d2-generic/sama5d27-som1-ek.board
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D2_PTC_EK) ?= $(TOP)/flash_loaders/sama5d2-generic/sama5d2-ptc-ek.board
endif

chip-family = sama5d2

target-y += target/sama5d2/chip.o
target-y += target/sama5d2/board_support.o
target-$(CONFIG_BOARD_SAMA5D2_GENERIC) += target/sama5d2/board_sama5d2-generic.o
target-$(CONFIG_BOARD_SAMA5D2_VB_BGA196) += target/sama5d2/board_sama5d2-vb-bga196.o
target-$(CONFIG_BOARD_SAMA5D2_VB_BGA289) += target/sama5d2/board_sama5d2-vb-bga289.o
target-$(CONFIG_BOARD_SAMA5D2_XPLAINED) += target/sama5d2/board_sama5d2-xplained.o
target-$(CONFIG_BOARD_SAMA5D27_SOM1_EK) += target/sama5d2/board_sama5d27-som1-ek.o
target-$(CONFIG_BOARD_SAMA5D2_PTC_EK) += target/sama5d2/board_sama5d2-ptc-ek.o

endif
