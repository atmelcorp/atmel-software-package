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

drivers-y += drivers/io/ov7740_config.o
drivers-y += drivers/io/iso7816_4.o
drivers-y += drivers/io/mt.o
drivers-y += drivers/io/ov.o
drivers-y += drivers/io/ov2643_config.o
drivers-y += drivers/io/ov9740_config.o
drivers-y += drivers/io/ov5640_config.o
drivers-y += drivers/io/qt1070.o
drivers-y += drivers/io/ov2640_config.o
drivers-y += drivers/io/mt9v022_config.o
drivers-y += drivers/io/mtyuv.o
drivers-y += drivers/io/led.o

drivers-$(CONFIG_HAVE_PMIC_ACT8945A) += drivers/io/act8945A.o

drivers-$(CONFIG_SOC_SAMA5D4) += drivers/io/tsd_com.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/io/tsd_tsadc.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/io/mcid_dma.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/io/aptina.o
drivers-$(CONFIG_SOC_SAMA5D4) += drivers/io/omnivision.o
