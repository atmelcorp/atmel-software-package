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
drivers-$(CONFIG_HAVE_AESB) += drivers/peripherals/aesb.o
drivers-$(CONFIG_HAVE_AES) += drivers/peripherals/aes.o
drivers-$(CONFIG_HAVE_AES) += drivers/peripherals/aesd.o
drivers-$(CONFIG_HAVE_AIC2) += drivers/peripherals/aic2.o
drivers-$(CONFIG_HAVE_AIC5) += drivers/peripherals/aic5.o
drivers-$(CONFIG_HAVE_SFC) += drivers/peripherals/sfc.o
drivers-$(CONFIG_HAVE_ETH) += drivers/peripherals/ethd.o
drivers-$(CONFIG_HAVE_EMAC) += drivers/peripherals/emacd.o
drivers-$(CONFIG_HAVE_EMAC) += drivers/peripherals/emac.o
drivers-$(CONFIG_HAVE_GMAC) += drivers/peripherals/gmacd.o
drivers-$(CONFIG_HAVE_GMAC) += drivers/peripherals/gmac.o
drivers-$(CONFIG_HAVE_ICM) += drivers/peripherals/icm.o
drivers-$(CONFIG_HAVE_L2CC) += drivers/peripherals/l2cc.o
drivers-$(CONFIG_HAVE_LCDC) += drivers/peripherals/lcdc.o
drivers-y += drivers/peripherals/matrix.o
drivers-$(CONFIG_HAVE_MPDDRC) += drivers/peripherals/mpddrc.o
drivers-$(CONFIG_HAVE_NFC) += drivers/peripherals/nfc.o
drivers-$(CONFIG_HAVE_PIT) += drivers/peripherals/pit.o
drivers-y += drivers/peripherals/pmc.o
drivers-$(CONFIG_HAVE_PMECC) += drivers/peripherals/pmecc.o
drivers-$(CONFIG_HAVE_PMECC) += drivers/peripherals/pmecc_gf_512.o
drivers-$(CONFIG_HAVE_PMECC) += drivers/peripherals/pmecc_gf_1024.o
drivers-$(CONFIG_HAVE_PWMC) += drivers/peripherals/pwmc.o
drivers-y += drivers/peripherals/rstc.o
drivers-y += drivers/peripherals/rtc.o
drivers-$(CONFIG_HAVE_SHA) += drivers/peripherals/sha.o
drivers-$(CONFIG_HAVE_SHA) += drivers/peripherals/shad.o
drivers-$(CONFIG_HAVE_SECUMOD) += drivers/peripherals/secumod.o
drivers-y += drivers/peripherals/shdwc.o
drivers-$(CONFIG_HAVE_SMC) += drivers/peripherals/smc.o
drivers-y += drivers/peripherals/spid.o
drivers-y += drivers/peripherals/spi.o
drivers-y += drivers/peripherals/tc.o
drivers-$(CONFIG_HAVE_TDES) += drivers/peripherals/tdes.o
drivers-$(CONFIG_HAVE_TDES) += drivers/peripherals/tdesd.o
drivers-$(CONFIG_HAVE_TRNG) += drivers/peripherals/trng.o
drivers-y += drivers/peripherals/twi.o
drivers-y += drivers/peripherals/twid.o
drivers-y += drivers/peripherals/uart.o
drivers-y += drivers/peripherals/usartd.o
drivers-y += drivers/peripherals/usart_iso7816_4.o
drivers-y += drivers/peripherals/usart.o
drivers-y += drivers/peripherals/wdt.o
drivers-y += drivers/peripherals/dma.o
drivers-$(CONFIG_HAVE_XDMAC) += drivers/peripherals/xdmac.o
drivers-$(CONFIG_HAVE_XDMAC) += drivers/peripherals/xdmacd.o
drivers-$(CONFIG_HAVE_DMAC) += drivers/peripherals/dmac.o
drivers-$(CONFIG_HAVE_DMAC) += drivers/peripherals/dmacd.o

drivers-$(CONFIG_HAVE_DBGU) += drivers/peripherals/dbgu.o
drivers-$(CONFIG_HAVE_FLEXCOM) += drivers/peripherals/flexcom.o
drivers-$(CONFIG_HAVE_USART_LIN) += drivers/peripherals/usart_lin.o
drivers-$(CONFIG_HAVE_PIO3) += drivers/peripherals/pio3.o
drivers-$(CONFIG_HAVE_PIO4) += drivers/peripherals/pio4.o
drivers-$(CONFIG_HAVE_QSPI) += drivers/peripherals/qspi.o
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
