# ----------------------------------------------------------------------------
#         SAM Software Package License
# ----------------------------------------------------------------------------
# Copyright (c) 2018, Atmel Corporation
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

ifeq ($(CONFIG_SOC_SAM9X60),y)

CFLAGS_INC += -I$(TOP)/target/sam9x60

gnu-debug-lib-y ?= $(TOP)/target/sam9x60/toolchain/gnu/common.gdb
gnu-cstartup-y ?= target/sam9x60/toolchain/gnu/cstartup.o
iar-cstartup-y ?= target/sam9x60/toolchain/iar/cstartup.o

xc32-cstartup-y ?= target/sam9x60/toolchain/xc32/cstartup.o
xc32-linker-script-y ?= $(TOP)/target/sam9x60/toolchain/xc32/

# SRAM variant
ifeq ($(VARIANT),sram)
gnu-linker-script-y ?= $(TOP)/target/sam9x60/toolchain/$(COMPILER)/sram.ld
gnu-debug-script-y ?= $(TOP)/target/sam9x60/toolchain/gnu/sram.gdb
iar-linker-script-y ?= $(TOP)/target/sam9x60/toolchain/iar/sram.icf
iar-debug-script-y ?= $(TOP)/target/sam9x60/toolchain/iar/sram.mac
endif

# DDRAM variant
ifeq ($(VARIANT),ddram)
gnu-linker-script-y ?= $(TOP)/target/sam9x60/toolchain/$(COMPILER)/ddram.ld
gnu-debug-script-y ?= $(TOP)/target/sam9x60/toolchain/gnu/ddram.gdb
bootstrap-linker-script-y ?= $(TOP)/target/sam9x60/toolchain/$(COMPILER)/sram.ld
iar-linker-script-y ?= $(TOP)/target/sam9x60/toolchain/iar/ddram.icf
iar-debug-script-y ?= $(TOP)/target/sam9x60/toolchain/iar/ddram.mac

ifeq ($(CONFIG_HAVE_CLASSD),y)
iar-flashloader-script-$(CONFIG_BOARD_SAM9X60_EK) ?= $(TOP)/flash_loaders/sam9x60-generic/sam9x60-ek-mck196.608.board
else
iar-flashloader-script-$(CONFIG_BOARD_SAM9X60_EK) ?= $(TOP)/flash_loaders/sam9x60-generic/sam9x60-ek.board
endif
iar-flashloader-script-$(CONFIG_BOARD_SAM9X60_CURIOSITY) ?= $(TOP)/flash_loaders/sam9x60-generic/sam9x60-curiosity.board

endif

# QSPI0 variant
ifeq ($(VARIANT),qspi0)
gnu-linker-script-y ?= $(TOP)/target/sam9x60/toolchain/gnu/qspi0.ld
iar-linker-script-y ?= $(TOP)/target/sam9x60/toolchain/iar/qspi0.icf
iar-debug-script-y ?= $(TOP)/target/sam9x60/toolchain/iar/qspi.mac
iar-flashloader-script-$(CONFIG_BOARD_SAM9X60_EK) ?= $(TOP)/flash_loaders/sam9x60-generic/sam9x60-ek.board
endif

chip-family = sam9x60

target-y += target/sam9x60/chip.o
target-y += target/sam9x60/board_support.o
ifeq ($(TARGET),sam9x60-generic)
target-y += target/sam9x60/board_sam9x60-generic.o
else
target-y += target/sam9x60/board_$(TARGET).o
endif

endif

