/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "analog/i2c/pac1720.h"
#include "i2c/twid.h"
#include "peripherals/bus.h"
#include "timer.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define PAC1720_CONFIG                 (0x00)
#define   PAC1720_CONFIG_CDEN          (1 << 6)
#define   PAC1720_CONFIG_MSKAL         (1 << 5)
#define   PAC1720_CONFIG_C2IDS         (1 << 4)
#define   PAC1720_CONFIG_C2VDS         (1 << 3)
#define   PAC1720_CONFIG_TOUT          (1 << 2)
#define   PAC1720_CONFIG_C1IDS         (1 << 1)
#define   PAC1720_CONFIG_C1VDS         (1 << 0)

#define PAC1720_CONV_RATE              (0x01)
#define   PAC1720_CONV_RATE_1SPS       (0)
#define   PAC1720_CONV_RATE_2SPS       (1)
#define   PAC1720_CONV_RATE_4SPS       (2)
#define   PAC1720_CONV_RATE_CONTINUOUS (3)

#define PAC1720_ONESHOT                (0x02)

#define PAC1720_CHANNEL_MASK           (0x03)
#define   PAC1720_CHANNEL_MASK_C2VS    (1 << 3)
#define   PAC1720_CHANNEL_MASK_C2VSR   (1 << 2)
#define   PAC1720_CHANNEL_MASK_C1VS    (1 << 1)
#define   PAC1720_CHANNEL_MASK_C1VSR   (1 << 0)

#define PAC1720_HLIMIT_STATUS          (0x04)
#define   PAC1720_HLIMIT_STATUS_CVDN   (1 << 7)
#define   PAC1720_HLIMIT_STATUS_C2VSH  (1 << 3)
#define   PAC1720_HLIMIT_STATUS_C2VRH  (1 << 2)
#define   PAC1720_HLIMIT_STATUS_C1VSH  (1 << 1)
#define   PAC1720_HLIMIT_STATUS_C1VRH  (1 << 0)

#define PAC1720_LLIMIT_STATUS          (0x05)
#define   PAC1720_LLIMIT_STATUS_C2VSL  (1 << 3)
#define   PAC1720_LLIMIT_STATUS_C2VRL  (1 << 2)
#define   PAC1720_LLIMIT_STATUS_C1VSL  (1 << 1)
#define   PAC1720_LLIMIT_STATUS_C1VRL  (1 << 0)

#define PAC1720_VSOURCE_CONF           (0x0a)
#define   PAC1720_VSOURCE_CONF_C2RS(x) (((x) & 3) << 6)
#define   PAC1720_VSOURCE_CONF_C2RA(x) (((x) & 3) << 4)
#define   PAC1720_VSOURCE_CONF_C1RS(x) (((x) & 3) << 2)
#define   PAC1720_VSOURCE_CONF_C1RA(x) (((x) & 3) << 0)

#define PAC1720_CH1_VSENSE_CONF    0x0b
#define   PAC1720_CH1_VSENSE_CONF_C1CSS(x) (((x) & 7) << 4)
#define   PAC1720_CH1_VSENSE_CONF_C1SA(x)  (((x) & 3) << 2)
#define   PAC1720_CH1_VSENSE_CONF_C1SR(x)  (((x) & 3) << 0)

#define PAC1720_CH2_VSENSE_CONF    0x0c
#define   PAC1720_CH2_VSENSE_CONF_C2CSS(x) (((x) & 7) << 4)
#define   PAC1720_CH2_VSENSE_CONF_C2SA(x)  (((x) & 3) << 2)
#define   PAC1720_CH2_VSENSE_CONF_C2SR(x)  (((x) & 3) << 0)

#define PAC1720_CH1_VSENSE_V_H     0x0d
#define PAC1720_CH1_VSENSE_V_L     0x0e
#define PAC1720_CH2_VSENSE_V_H     0x0f
#define PAC1720_CH2_VSENSE_V_L     0x10
#define PAC1720_CH1_VSOURCE_V_H    0x11
#define PAC1720_CH1_VSOURCE_V_L    0x12
#define PAC1720_CH2_VSOURCE_V_H    0x13
#define PAC1720_CH2_VSOURCE_V_L    0x14
#define PAC1720_CH1_PRATIO_H       0x15
#define PAC1720_CH1_PRATIO_L       0x16
#define PAC1720_CH2_PRATIO_H       0x17
#define PAC1720_CH2_PRATIO_L       0x18
#define PAC1720_CH1_VSENSE_HLIMIT  0x19
#define PAC1720_CH1_VSENSE_LLIMIT  0x1a
#define PAC1720_CH2_VSENSE_HLIMIT  0x1b
#define PAC1720_CH2_VSENSE_LLIMIT  0x1c
#define PAC1720_CH1_VSOURCE_HLIMIT 0x1d
#define PAC1720_CH1_VSOURCE_LLIMIT 0x1e
#define PAC1720_CH2_VSOURCE_HLIMIT 0x1f
#define PAC1720_CH2_VSOURCE_LLIMIT 0x20

#define PAC1720_PRODUCT_ID         0xfd /* 0x57/0x58 */
#define PAC1720_MANUFACTURER_ID    0xfe /* 0x5d */
#define PAC1720_REVISION           0xff /* 0x81 */

#define PAC1720_VSOURCE_SAMPLE_TIME_2MS5 (0)
#define PAC1720_VSOURCE_SAMPLE_TIME_5MS  (1)
#define PAC1720_VSOURCE_SAMPLE_TIME_10MS (2)
#define PAC1720_VSOURCE_SAMPLE_TIME_20MS (3)

#define PAC1720_VSOURCE_AVERAGE_DISABLED (0)
#define PAC1720_VSOURCE_AVERAGE_2        (1)
#define PAC1720_VSOURCE_AVERAGE_4        (2)
#define PAC1720_VSOURCE_AVERAGE_8        (3)

#define PAC1720_CSENSE_SAMPLING_TIME_2MS5  (0)
#define PAC1720_CSENSE_SAMPLING_TIME_5MS   (1)
#define PAC1720_CSENSE_SAMPLING_TIME_10MS  (2)
#define PAC1720_CSENSE_SAMPLING_TIME_20MS  (3)
#define PAC1720_CSENSE_SAMPLING_TIME_40MS  (4)
#define PAC1720_CSENSE_SAMPLING_TIME_80MS  (5)
#define PAC1720_CSENSE_SAMPLING_TIME_160MS (6)
#define PAC1720_CSENSE_SAMPLING_TIME_320MS (7)

#define PAC1720_CSENSE_AVERAGE_DISABLED (0)
#define PAC1720_CSENSE_AVERAGE_2        (1)
#define PAC1720_CSENSE_AVERAGE_4        (2)
#define PAC1720_CSENSE_AVERAGE_8        (3)

#define PAC1720_CSENSE_RANGE_10MV (0)
#define PAC1720_CSENSE_RANGE_20MV (1)
#define PAC1720_CSENSE_RANGE_40MV (2)
#define PAC1720_CSENSE_RANGE_80MV (3)

/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static int _pac1720_i2c_read(const struct _pac1720_desc* pac1720, uint8_t reg, uint8_t* buf, uint8_t len)
{
	int err;
	struct _buffer i2c_buf[2] = {
		{
			.data = &reg,
			.size = 1,
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_TX,
		},
		{
			.data = buf,
			.size = len,
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_RX | BUS_I2C_BUF_ATTR_STOP,
		},
	};


	bus_start_transaction(pac1720->cfg.bus);
	err = bus_transfer(pac1720->cfg.bus, pac1720->addr, i2c_buf, 2, NULL);
	bus_stop_transaction(pac1720->cfg.bus);

	return err;
}

static int _pac1720_i2c_write(const struct _pac1720_desc* pac1720, uint8_t reg, uint8_t* buf, uint8_t len)
{
	int err;
	struct _buffer i2c_buf[2] = {
		{
			.data = &reg,
			.size = 1,
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_TX,
		},
		{
			.data = buf,
			.size = len,
			.attr = BUS_BUF_ATTR_TX | BUS_I2C_BUF_ATTR_STOP,
		},
	};

	bus_start_transaction(pac1720->cfg.bus);
	err = bus_transfer(pac1720->cfg.bus, pac1720->addr, i2c_buf, 2, NULL);
	bus_stop_transaction(pac1720->cfg.bus);

	return err;
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

int pac1720_configure(struct _pac1720_desc* desc)
{
	int err;
	uint8_t id[3];
	uint8_t val;
	uint8_t avg;

	memset(id, 0, sizeof(id));
	err = _pac1720_i2c_read(desc, PAC1720_PRODUCT_ID, id, 3);
	if (err < 0)
		return err;

	if (id[0] != 0x57 && id[0] != 0x58)
		return -ENODEV;

	val = PAC1720_CONFIG_MSKAL | PAC1720_CONFIG_C2IDS | PAC1720_CONFIG_C2VDS;
	err = _pac1720_i2c_write(desc, PAC1720_CONFIG, &val, 1);
	if (err < 0)
		return err;

	val = PAC1720_CONV_RATE_CONTINUOUS;
	err = _pac1720_i2c_write(desc, PAC1720_CONV_RATE, &val, 1);
	if (err < 0)
		return err;

	val = PAC1720_CHANNEL_MASK_C1VS | PAC1720_CHANNEL_MASK_C1VSR;
	err = _pac1720_i2c_write(desc, PAC1720_CHANNEL_MASK, &val, 1);
	if (err < 0)
		return err;

	val = PAC1720_VSOURCE_CONF_C1RS(PAC1720_VSOURCE_SAMPLE_TIME_20MS) |
		PAC1720_VSOURCE_CONF_C1RA(PAC1720_VSOURCE_AVERAGE_4);
	err = _pac1720_i2c_write(desc, PAC1720_VSOURCE_CONF, &val, 1);
	if (err < 0)
		return err;

	val = PAC1720_CH1_VSENSE_CONF_C1CSS(PAC1720_CSENSE_SAMPLING_TIME_80MS) |
		PAC1720_CH1_VSENSE_CONF_C1SA(PAC1720_CSENSE_AVERAGE_4) |
		PAC1720_CH1_VSENSE_CONF_C1SR(PAC1720_CSENSE_RANGE_20MV);
	err = _pac1720_i2c_write(desc, PAC1720_CH1_VSENSE_CONF, &val, 1);
	if (err < 0)
		return err;

	avg = 4;

	for (int i = 0; i < avg; i++) {
		uint16_t vsense;
		pac1720_wait_for_conversion(desc, 50);
		pac1720_read_vsense(desc, 1, &vsense);
	}

	desc->private.denominator = 2047;
	desc->private.fsr = 20;

	return 0;
}

int pac1720_wait_for_conversion(struct _pac1720_desc* desc, uint16_t wait)
{
	int err;
	uint8_t hlimit;

	/* Clear PAC1720_HLIMIT_STATUS_CVDN bit */
	err = _pac1720_i2c_read(desc, PAC1720_HLIMIT_STATUS, &hlimit, 1);
	if (err < 0)
		return err;
	do {
		msleep(wait);
		err = _pac1720_i2c_read(desc, PAC1720_HLIMIT_STATUS, &hlimit, 1);
		if (err < 0)
			return err;
	} while ((hlimit & PAC1720_HLIMIT_STATUS_CVDN) != PAC1720_HLIMIT_STATUS_CVDN);

	return 0;
}

int pac1720_read_vsense(struct _pac1720_desc* desc, uint8_t channel, uint16_t* vsense)
{
	int err;
	uint8_t reg[2];

	if (!vsense)
		return -EINVAL;

	switch (channel) {
	case 1:
		err = _pac1720_i2c_read(desc, PAC1720_CH1_VSENSE_V_H, reg, 2);
		break;
	case 2:
		err = _pac1720_i2c_read(desc, PAC1720_CH2_VSENSE_V_H, reg, 2);
		break;
	default:
		err = -EINVAL;
		break;
	}

	if (err < 0)
		*vsense = 0;
	else
		*vsense = (reg[1] >> 4) | ((uint16_t)reg[0] << 4);
	return err;
}

int pac1720_read_vsource(struct _pac1720_desc* desc, uint8_t channel, uint16_t* vsource)
{
	int err;
	uint8_t reg[2];

	if (!vsource)
		return -EINVAL;

	switch (channel) {
	case 1:
		err = _pac1720_i2c_read(desc, PAC1720_CH1_VSOURCE_V_H, reg, 2);
		break;
	case 2:
		err = _pac1720_i2c_read(desc, PAC1720_CH2_VSOURCE_V_H, reg, 2);
		break;
	default:
		err = -EINVAL;
		break;
	}

	if (err < 0)
		*vsource = 0;
	else
		*vsource = (reg[1] >> 5) | ((uint16_t)reg[0] << 3);
	return err;
}

int pac1720_read_power(struct _pac1720_desc* desc, uint8_t channel, uint16_t* power)
{
	int err;
	uint8_t reg[2];

	if (!power)
		return -EINVAL;

	switch (channel) {
	case 1:
		err = _pac1720_i2c_read(desc, PAC1720_CH1_PRATIO_H, reg, 2);
		break;
	case 2:
		err = _pac1720_i2c_read(desc, PAC1720_CH2_PRATIO_H, reg, 2);
		break;
	default:
		err = -EINVAL;
		break;
	}

	if (err < 0)
		*power = 0;
	else
		*power = reg[1] | ((uint16_t)reg[0] << 8);
	return err;
}

int pac1720_convert(struct _pac1720_desc* desc, float rsense,
		uint16_t vsense, uint16_t vsource, uint16_t pratio,
		float *i, float *v, float *p)
{
	float fsc, fsv, fsp;

	if (desc->private.denominator == 0)
		return -EINVAL;

	fsc = desc->private.fsr / rsense;
	*i = fsc * vsense / desc->private.denominator;

	fsv = 40 - (40 / desc->private.denominator);
	*v = fsv * vsource / desc->private.denominator;

	fsp = fsc * fsv;
	*p = fsp * pratio / 65535;

	return 0;
}
