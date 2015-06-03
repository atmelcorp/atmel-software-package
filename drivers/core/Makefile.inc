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

drivers-y += drivers/core/aic.o
drivers-y += drivers/core/async.o
drivers-y += drivers/core/cortexa5_interrupts.o
drivers-y += drivers/core/cp15_asm_gcc.o
drivers-y += drivers/core/cp15.o
drivers-y += drivers/core/cp15_pmu.o
drivers-y += drivers/core/cpsr_gcc.o
drivers-y += drivers/core/cpsr.o
drivers-y += drivers/core/l2cc.o
drivers-y += drivers/core/mmu.o
drivers-y += drivers/core/pmc.o
drivers-y += drivers/core/pwmc.o
drivers-y += drivers/core/rstc.o
drivers-y += drivers/core/wdt.o

drivers-$(CONFIG_HAVE_PIO3) += drivers/core/pio3.o
drivers-$(CONFIG_HAVE_PIO4) += drivers/core/pio4.o

drivers-$(CONFIG_SOC_SAMA5D4) += drivers/core/adc.o
