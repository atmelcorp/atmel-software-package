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

CFLAGS_INC += -I$(TOP)/target/common

target-y += target/common/board_console.o
target-y += target/common/board_timer.o
target-y += target/common/chip_common.o

target-$(CONFIG_HAVE_AUDIO) += target/common/board_audio.o
target-$(CONFIG_HAVE_CAN_BUS) += target/common/board_can.o
target-$(CONFIG_HAVE_ETH) += target/common/board_eth.o
target-$(CONFIG_HAVE_ISC) += target/common/board_isc.o
target-$(CONFIG_HAVE_ISI) += target/common/board_isi.o
target-$(CONFIG_HAVE_LCD) += target/common/board_lcd.o
target-$(CONFIG_HAVE_LED) += target/common/board_led.o
target-$(CONFIG_HAVE_SPI_BUS) += target/common/board_spi.o
target-$(CONFIG_HAVE_I2C_BUS) += target/common/board_twi.o

bootstrap-y ?= target/common/bootstrap.o
