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

drivers-y += drivers/peripherals/aes.o
drivers-y += drivers/peripherals/aesb.o
drivers-y += drivers/peripherals/aic.o
#drivers-y += drivers/peripherals/ddram.o
drivers-y += drivers/peripherals/icm.o
drivers-y += drivers/peripherals/iso7816_4.o
drivers-y += drivers/peripherals/l2cc.o
drivers-y += drivers/peripherals/matrix.o
drivers-y += drivers/peripherals/mpddrc.o
drivers-y += drivers/peripherals/pit.o
drivers-y += drivers/peripherals/pmc.o
drivers-y += drivers/peripherals/pwmc.o
drivers-y += drivers/peripherals/rstc.o
drivers-y += drivers/peripherals/rtc.o
drivers-y += drivers/peripherals/rtc_calib.o
drivers-y += drivers/peripherals/sha.o
drivers-y += drivers/peripherals/smc_nfc.o
drivers-y += drivers/peripherals/spi.o
drivers-y += drivers/peripherals/spid.o
drivers-y += drivers/peripherals/tc.o
drivers-y += drivers/peripherals/tdes.o
drivers-y += drivers/peripherals/trng.o
drivers-y += drivers/peripherals/twi.o
drivers-y += drivers/peripherals/twid.o
drivers-y += drivers/peripherals/uart.o
drivers-y += drivers/peripherals/usart.o
drivers-y += drivers/peripherals/wdt.o
drivers-y += drivers/peripherals/xdmac.o
drivers-y += drivers/peripherals/xdmad.o

drivers-$(CONFIG_HAVE_DBGU) += drivers/peripherals/dbgu.o
drivers-$(CONFIG_HAVE_FLEXCOM) += drivers/peripherals/flexcom.o

drivers-$(CONFIG_HAVE_PIO3) += drivers/peripherals/pio3.o
drivers-$(CONFIG_HAVE_PIO4) += drivers/peripherals/pio4.o

#drivers-$(CONFIG_SOC_SAMA5D2) += drivers/peripherals/isc.o

drivers-$(CONFIG_SOC_SAMA5D4) += drivers/peripherals/adc.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/peripherals/can.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/peripherals/gmac.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/peripherals/gmacb.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/peripherals/gmacd.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/peripherals/hsmci.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/peripherals/ssc.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/peripherals/isi.o
