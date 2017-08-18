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

ifeq ($(CONFIG_SOC_SAMV71),y)

CFLAGS_INC += -I$(TOP)/target/samv71

gnu-debug-lib-y ?= $(TOP)/target/samv71/toolchain/gnu/common.gdb
gnu-cstartup-y ?= target/samv71/toolchain/cstartup.o

iar-cstartup-y ?= target/samv71/toolchain/cstartup.o
iar-program-entry-y ?= reset_handler

# SRAM variant
ifeq ($(VARIANT),sram)
gnu-linker-script-y ?= $(TOP)/target/samv71/toolchain/gnu/sram.ld
gnu-debug-script-y ?= $(TOP)/target/samv71/toolchain/gnu/sram.gdb
iar-linker-script-y ?= $(TOP)/target/samv71/toolchain/iar/sram.icf
iar-debug-script-y ?= $(TOP)/target/samv71/toolchain/iar/sram.mac
endif

# DDRAM variant
ifeq ($(VARIANT),ddram)
gnu-linker-script-y ?= $(TOP)/target/samv71/toolchain/gnu/ddram.ld
gnu-debug-script-y ?= $(TOP)/target/samv71/toolchain/gnu/ddram.gdb
bootstrap-linker-script-y ?= $(TOP)/target/samv71/toolchain/gnu/sram.ld
iar-linker-script-y ?= $(TOP)/target/samv71/toolchain/iar/ddram.icf
iar-debug-script-y ?= $(TOP)/target/samv71/toolchain/iar/ddram.mac
iar-flashloader-script-$(CONFIG_BOARD_SAMV71_XPLAINED) ?= $(TOP)/flash_loaders/samv71-generic/samv71-xplained.board
iar-flashloader-script-$(CONFIG_BOARD_SAME70_XPLAINED) ?= $(TOP)/flash_loaders/samv71-generic/same70-xplained.board
endif

# FLASH variant
ifeq ($(VARIANT),flash)
gnu-linker-script-y ?= $(TOP)/target/samv71/toolchain/gnu/flash.ld
gnu-debug-script-y ?= $(TOP)/target/samv71/toolchain/gnu/flash.gdb
iar-linker-script-y ?= $(TOP)/target/samv71/toolchain/iar/flash.icf
iar-debug-script-y ?= $(TOP)/target/samv71/toolchain/iar/flash.mac
endif

chip-family = samv71

target-y += target/samv71/chip.o
target-y += target/samv71/board_support.o
target-$(CONFIG_BOARD_SAMV71_GENERIC) += target/samv71/board_samv71-generic.o
target-$(CONFIG_BOARD_SAME70_XPLAINED) += target/samv71/board_same70-xplained.o
target-$(CONFIG_BOARD_SAMV71_XPLAINED) += target/samv71/board_samv71-xplained.o

endif
