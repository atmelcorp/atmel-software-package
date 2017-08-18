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

ifeq ($(CONFIG_SOC_SAM9XX5),y)

CFLAGS_INC += -I$(TOP)/target/sam9xx5

gnu-debug-lib-y ?= $(TOP)/target/sam9xx5/toolchain/gnu/common.gdb
gnu-cstartup-y ?= target/sam9xx5/toolchain/gnu/cstartup.o
iar-cstartup-y ?= target/sam9xx5/toolchain/iar/cstartup.o

# SRAM variant
ifeq ($(VARIANT),sram)
gnu-linker-script-y ?= $(TOP)/target/sam9xx5/toolchain/gnu/sram.ld
gnu-debug-script-y ?= $(TOP)/target/sam9xx5/toolchain/gnu/sram.gdb
iar-linker-script-y ?= $(TOP)/target/sam9xx5/toolchain/iar/sram.icf
iar-debug-script-y ?= $(TOP)/target/sam9xx5/toolchain/iar/sram.mac
endif

# DDRAM variant
ifeq ($(VARIANT),ddram)
gnu-linker-script-y ?= $(TOP)/target/sam9xx5/toolchain/gnu/ddram.ld
gnu-debug-script-y ?= $(TOP)/target/sam9xx5/toolchain/gnu/ddram.gdb
bootstrap-linker-script-y ?= $(TOP)/target/sam9xx5/toolchain/gnu/sram.ld
iar-linker-script-y ?= $(TOP)/target/sam9xx5/toolchain/iar/ddram.icf
iar-debug-script-y ?= $(TOP)/target/sam9xx5/toolchain/iar/ddram.mac
iar-flashloader-script-y ?= $(TOP)/flash_loaders/sam9x25-generic/sam9x25-generic.board
endif

chip-family = sam9xx5

target-y += target/sam9xx5/chip.o
target-y += target/sam9xx5/board_support.o
target-$(CONFIG_BOARD_SAM9G15_GENERIC) += target/sam9xx5/board_sam9xx5-generic.o
target-$(CONFIG_BOARD_SAM9G25_GENERIC) += target/sam9xx5/board_sam9xx5-generic.o
target-$(CONFIG_BOARD_SAM9G35_GENERIC) += target/sam9xx5/board_sam9xx5-generic.o
target-$(CONFIG_BOARD_SAM9X25_GENERIC) += target/sam9xx5/board_sam9xx5-generic.o
target-$(CONFIG_BOARD_SAM9X35_GENERIC) += target/sam9xx5/board_sam9xx5-generic.o
target-$(CONFIG_BOARD_SAM9G15_EK) += target/sam9xx5/board_sam9xx5-ek.o
target-$(CONFIG_BOARD_SAM9G25_EK) += target/sam9xx5/board_sam9xx5-ek.o
target-$(CONFIG_BOARD_SAM9G35_EK) += target/sam9xx5/board_sam9xx5-ek.o
target-$(CONFIG_BOARD_SAM9X25_EK) += target/sam9xx5/board_sam9xx5-ek.o
target-$(CONFIG_BOARD_SAM9X35_EK) += target/sam9xx5/board_sam9xx5-ek.o

endif
