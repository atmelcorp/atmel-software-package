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

drivers-$(CONFIG_HAVE_IMAGE_SENSOR) += drivers/video/image_sensor_inf.o
drivers-$(CONFIG_HAVE_IMAGE_SENSOR) += drivers/video/mt9v022_config.o
drivers-$(CONFIG_HAVE_IMAGE_SENSOR) += drivers/video/ov2640_config.o
drivers-$(CONFIG_HAVE_IMAGE_SENSOR) += drivers/video/ov2643_config.o
drivers-$(CONFIG_HAVE_IMAGE_SENSOR) += drivers/video/ov5640_config.o
drivers-$(CONFIG_HAVE_IMAGE_SENSOR) += drivers/video/ov7740_config.o
drivers-$(CONFIG_HAVE_IMAGE_SENSOR) += drivers/video/ov7670_config.o
drivers-$(CONFIG_HAVE_IMAGE_SENSOR) += drivers/video/ov9740_config.o
drivers-$(CONFIG_HAVE_ISC) += drivers/video/isc.o
drivers-$(CONFIG_HAVE_QT1070) += drivers/video/qt1070.o
drivers-$(CONFIG_HAVE_ISC) += drivers/video/isc.o
drivers-$(CONFIG_HAVE_ISC) += drivers/video/iscd.o
drivers-$(CONFIG_HAVE_ISI) += drivers/video/isi.o
drivers-$(CONFIG_HAVE_ISI) += drivers/video/isid.o
