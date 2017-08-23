# ----------------------------------------------------------------------------
#         SAM Software Package License
# ----------------------------------------------------------------------------
# Copyright (c) 2017, Atmel Corporation
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

ifeq ($(CONFIG_FLASH_LOADER),y)

CFLAGS_INC += -I$(TOP)/flash_loaders/applets/common
CFLAGS_INC += -I$(TOP)/flash_loaders/applets/common/framework2

CFLAGS += -mno-unaligned-access -DDMA_SG_ITEM_POOL_SIZE=2

obj-y += flash_loaders/applets/common/framework2/flash_loader_asm.o
obj-y += flash_loaders/applets/common/framework2/flash_loader.o
obj-y += flash_loaders/applets/common/interface.o

iar-linker-script-$(CONFIG_SOC_SAM9XX5) = $(TOP)/flash_loaders/applets/common/sam9xx5/sram.icf
iar-linker-script-$(CONFIG_SOC_SAMA5D2) = $(TOP)/flash_loaders/applets/common/sama5d2/sram.icf
iar-linker-script-$(CONFIG_SOC_SAMA5D3) = $(TOP)/flash_loaders/applets/common/sama5d3/sram.icf
iar-linker-script-$(CONFIG_SOC_SAMA5D4) = $(TOP)/flash_loaders/applets/common/sama5d4/sram.icf
iar-linker-script-$(CONFIG_SOC_SAMV71) = $(TOP)/flash_loaders/applets/common/samv71/sram.icf

iar-program-entry-y = FlashInitEntry
iar-debug-script-y =
iar-flash_loader-script-y =
iar-cstartup-y =
iar-project-template-y = $(TOP)/scripts/iar_flash_loader_project.template
CONFIG_BOOTSTRAP=n

endif
