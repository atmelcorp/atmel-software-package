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

ifeq ($(CONFIG_SOC_SAMA5D3),y)

CFLAGS_INC += -I$(TOP)/target/sama5d3

gnu-debug-lib-y ?= $(TOP)/target/sama5d3/toolchain/gnu/common.gdb
gnu-cstartup-y ?= target/sama5d3/toolchain/gnu/cstartup.o
iar-cstartup-y ?= target/sama5d3/toolchain/iar/cstartup.o

# SRAM variant
ifeq ($(VARIANT),sram)
gnu-linker-script-y ?= $(TOP)/target/sama5d3/toolchain/gnu/sram.ld
gnu-debug-script-y ?= $(TOP)/target/sama5d3/toolchain/gnu/sram.gdb
iar-linker-script-y ?= $(TOP)/target/sama5d3/toolchain/iar/sram.icf
iar-debug-script-y ?= $(TOP)/target/sama5d3/toolchain/iar/sram.mac
endif

# DDRAM variant
ifeq ($(VARIANT),ddram)
gnu-linker-script-y ?= $(TOP)/target/sama5d3/toolchain/gnu/ddram.ld
gnu-debug-script-y ?= $(TOP)/target/sama5d3/toolchain/gnu/ddram.gdb
bootstrap-linker-script-y ?= $(TOP)/target/sama5d3/toolchain/gnu/sram.ld
iar-linker-script-y ?= $(TOP)/target/sama5d3/toolchain/iar/ddram.icf
iar-debug-script-y ?= $(TOP)/target/sama5d3/toolchain/iar/ddram.mac
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D3_EK) ?= $(TOP)/flash_loaders/sama5d3-generic/sama5d3-ek.board
iar-flashloader-script-$(CONFIG_BOARD_SAMA5D3_XPLAINED) ?= $(TOP)/flash_loaders/sama5d3-generic/sama5d3-xplained.board
endif

chip-family = sama5d3

target-y += target/sama5d3/chip.o
target-y += target/sama5d3/board_support.o
target-$(CONFIG_BOARD_SAMA5D3_EK) += target/sama5d3/board_sama5d3-ek.o
target-$(CONFIG_BOARD_SAMA5D3_GENERIC) += target/sama5d3/board_sama5d3-generic.o
target-$(CONFIG_BOARD_SAMA5D3_XPLAINED) += target/sama5d3/board_sama5d3-xplained.o

endif
