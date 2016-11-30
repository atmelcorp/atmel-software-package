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

drivers-$(CONFIG_HAVE_ADC) += drivers/peripherals/adc.o
drivers-$(CONFIG_HAVE_ADC) += drivers/peripherals/adcd.o
drivers-$(CONFIG_HAVE_L2CC) += drivers/peripherals/l2cc.o
drivers-$(CONFIG_HAVE_LCDC) += drivers/peripherals/lcdc.o
drivers-y += drivers/peripherals/matrix.o
drivers-$(CONFIG_HAVE_PIT) += drivers/peripherals/pit.o
drivers-y += drivers/peripherals/pmc.o
drivers-$(CONFIG_HAVE_PWMC) += drivers/peripherals/pwmc.o
drivers-y += drivers/peripherals/rstc.o
drivers-y += drivers/peripherals/rtc.o
drivers-$(CONFIG_HAVE_SECUMOD) += drivers/peripherals/secumod.o
drivers-$(CONFIG_HAVE_SHDWC) += drivers/peripherals/shdwc.o
drivers-$(CONFIG_HAVE_SCKC) += drivers/peripherals/slowclock_sckc.o
drivers-y += drivers/peripherals/tc.o
drivers-y += drivers/peripherals/wdt.o

drivers-$(CONFIG_HAVE_FLEXCOM) += drivers/peripherals/flexcom.o
drivers-$(CONFIG_HAVE_MCAN) += drivers/peripherals/mcan.o
drivers-$(CONFIG_HAVE_SDMMC) += drivers/peripherals/sdmmc.o

drivers-$(CONFIG_HAVE_ACC) += drivers/peripherals/acc.o
drivers-$(CONFIG_HAVE_CLASSD) += drivers/peripherals/classd.o
drivers-$(CONFIG_HAVE_ISC) += drivers/peripherals/isc.o
drivers-$(CONFIG_HAVE_PDMIC) += drivers/peripherals/pdmic.o
drivers-$(CONFIG_HAVE_SFRBU) += drivers/peripherals/sfrbu.o

drivers-$(CONFIG_HAVE_HSMCI) += drivers/peripherals/hsmci.o
drivers-$(CONFIG_HAVE_HSMCI) += drivers/peripherals/hsmcid.o
drivers-$(CONFIG_HAVE_ISI) += drivers/peripherals/isi.o
drivers-$(CONFIG_HAVE_SSC) += drivers/peripherals/ssc.o
