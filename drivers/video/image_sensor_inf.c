/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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

#include <stdbool.h>
#include <stdio.h>

#include "chip.h"
#include "errno.h"
#include "i2c/twid.h"
#include "peripherals/bus.h"
#include "timer.h"
#include "trace.h"
#include "video/image_sensor_inf.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/** Supported sensor profiles */
static const struct sensor_profile* sensor_profiles[SENSOR_SUPPORTED_NUMBER] = {
	&ov2640_profile,
	&ov2643_profile,
	&ov5640_profile,
	&ov7670_profile,
	&ov7740_profile,
	&ov9740_profile
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Read value from a register in an dedicated sensor device.
 * \param bus  TWI bus
 * \param addr Sensor TWI addr
 * \param reg Register to be read
 * \param data Data read
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static int sensor_twi_read_reg(uint8_t twi_mode, uint8_t bus, uint8_t addr,
			       uint16_t reg, uint8_t *data)
{
	int err;
	uint8_t reg8[2];
	struct _buffer buf[2] = {
		{
			/* .data */
			/* .size */
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_TX | BUS_I2C_BUF_ATTR_STOP,
		},
		{
			/* .data */
			/* .size */
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_RX | BUS_I2C_BUF_ATTR_STOP,
		},
	};

	reg8[0] = reg >> 8;
	reg8[1] = reg & 0xff;
	switch (twi_mode){
	case SENSOR_TWI_REG_BYTE_DATA_BYTE:
		buf[0].data = reg8 + 1;
		buf[0].size = 1;
		buf[1].data = data;
		buf[1].size = 1;
		break;

	case SENSOR_TWI_REG_2BYTE_DATA_BYTE:
		buf[0].data = reg8;
		buf[0].size = 2;
		buf[1].data = data;
		buf[1].size = 1;
		break;

	case SENSOR_TWI_REG_BYTE_DATA_2BYTE:
		buf[0].data = reg8 + 1;
		buf[0].size = 1;
		buf[1].data = data;
		buf[1].size = 2;
		break;

	default:
		return -EINVAL;
	}

	bus_start_transaction(bus);
	err = bus_transfer(bus, addr, buf, 2, NULL);
	bus_stop_transaction(bus);

	return err;
}

/**
 * \brief  Write a value to a register in an dedicated sensor device.
 * \param bus  TWI bus
 * \param addr Sensor TWI addr
 * \param reg Register to be written
 * \param data Data written
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static int sensor_twi_write_reg(uint8_t twi_mode, uint8_t bus, uint8_t addr,
				uint16_t reg, uint8_t *data)
{
	int err;
	uint8_t addr_buf[2];
	struct _buffer buf[2] = {
		{
			.data = addr_buf,
			/* .size */
			.attr = BUS_I2C_BUF_ATTR_START | BUS_BUF_ATTR_TX,
		},
		{
			.data = data,
			/* .size */
			.attr = BUS_BUF_ATTR_TX | BUS_I2C_BUF_ATTR_STOP,
		},
	};

	switch (twi_mode){
	case SENSOR_TWI_REG_BYTE_DATA_BYTE:
		buf[0].size = 1;
		buf[1].size = 1;
		addr_buf[0] = reg & 0xff;

		break;

	case SENSOR_TWI_REG_2BYTE_DATA_BYTE:
		buf[0].size = 2;
		buf[1].size = 1;
		addr_buf[0] = (reg >> 8) & 0xff;
		addr_buf[1] = reg & 0xff;
		break;

	case SENSOR_TWI_REG_BYTE_DATA_2BYTE:
		buf[0].size = 1;
		buf[1].size = 2;
		addr_buf[0] = reg & 0xff;
		break;

	default:
		return -EINVAL;
	}

	bus_start_transaction(bus);
	err = bus_transfer(bus, addr, buf, 2, NULL);
	bus_stop_transaction(bus);

	return err;
}

/**
 * \brief Read and check sensor product ID.
 * \param twi_bus  TWI bus
 * \param sensor_profile Sensor profile
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static uint32_t sensor_check_pid(uint8_t twi_bus, struct sensor_profile* sensor_profile)
{
	/* use uint32_t to force 4-byte alignment */
	uint32_t pid_high = 0;
	uint32_t pid_low = 0;
	uint16_t reg_h = sensor_profile->pid_high_reg;
	uint16_t reg_l = sensor_profile->pid_low_reg;
	uint16_t pid = (sensor_profile->pid_high) << 8 | sensor_profile->pid_low;
	uint16_t ver_mask = sensor_profile->version_mask;

	if (sensor_twi_read_reg(sensor_profile->twi_inf_mode,
							twi_bus,
							sensor_profile->addr,
							reg_h, (uint8_t*)&pid_high) < 0)
		return SENSOR_TWI_ERROR;
	pid_high &= 0xff;
	if (sensor_twi_read_reg(sensor_profile->twi_inf_mode,
							twi_bus,
							sensor_profile->addr,
							reg_l, (uint8_t*)&pid_low) < 0)
		return SENSOR_TWI_ERROR;
	pid_low &= 0xff;

	trace_debug_wp("SENSOR PID = <%x, %x>\n\r", (unsigned)pid_high, (unsigned)pid_low);

	if ((pid & ver_mask) == (((pid_high << 8) | pid_low) & ver_mask))
		return SENSOR_OK;
	else
		return SENSOR_ID_ERROR;
}

/**
 * \brief  Initialize a list of registers.
 * The list of registers is terminated by the pair of values
 * \param twi_bus  TWI bus
 * \param sensor_profile   Sensor private profile
 * \param reglist Register list to be written
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static uint32_t sensor_twi_write_regs(uint8_t twi_bus,
									  struct sensor_profile* sensor_profile,
									  const struct sensor_reg* reglist)
{
	int status;
	const struct sensor_reg *next = reglist;

	while (!((next->reg == SENSOR_REG_TERM) && (next->val == SENSOR_VAL_TERM))) {
		status = sensor_twi_write_reg(sensor_profile->twi_inf_mode,
									  twi_bus,
									  sensor_profile->addr,
									  next->reg,
									  (uint8_t *)(&next->val));
		msleep(2);
		if (status < 0)
			return SENSOR_TWI_ERROR;
		next++;
	}

	return SENSOR_OK;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

uint32_t sensor_setup(uint8_t twi_bus, struct sensor_profile* sensor_profile,
					  uint8_t resolution,
					  uint8_t format)
{
	uint8_t i;
	uint8_t found = 0;

	for (i = 0; i < SENSOR_SUPPORTED_OUTPUTS; i++) {
		if (sensor_profile->output_conf[i]->supported){
			if (sensor_profile->output_conf[i]->output_resolution == resolution) {
				if (sensor_profile->output_conf[i]->output_format == format) {
					found = 1;
					break;
				}
			}
		}
	}
	if (found == 0)
		return SENSOR_RESOLUTION_NOT_SUPPORTED;

	return sensor_twi_write_regs(twi_bus, sensor_profile,
								 sensor_profile->output_conf[i]->output_setting);
}

struct sensor_profile* sensor_detect(uint8_t twi_bus, bool detect_auto, uint8_t id)
{
	uint8_t i;
	struct sensor_profile *sensor;

	if (!detect_auto) {
		sensor = (struct sensor_profile*)sensor_profiles[id];
		if (sensor_check_pid(twi_bus, sensor) == SENSOR_OK)
			return sensor;
		else
			return NULL;
	} else {
		for (i = 0; i < SENSOR_SUPPORTED_NUMBER; i++) {
			sensor = (struct sensor_profile*) sensor_profiles[i];
			if (sensor_check_pid(twi_bus, sensor) == SENSOR_OK)
				break;
			else
				sensor = NULL;
		}
		return sensor;
	}
}

/**
 * \brief Retrieves sensor output bit width and size for giving resolution and format.
 * \param resolution Output resolution request.
 * \param format Output Format request.
 * \param bits   Output Format request.
 * \param width  pointer to image width to be read.
 * \param height  pointer to image height to be read.
 * \return SENSOR_OK if no error; otherwise return SENSOR_XXX_ERROR
 */
uint32_t sensor_get_output(struct sensor_profile *sensor,
						   uint8_t resolution,
						   uint8_t format,
						   uint8_t *bits,
						   uint32_t *width,
						   uint32_t *height)
{
	uint8_t i;
	for (i = 0; i < SENSOR_SUPPORTED_OUTPUTS; i++) {
		if (sensor->output_conf[i]->supported){
			if (sensor->output_conf[i]->output_resolution == resolution) {
				if (sensor->output_conf[i]->output_format == format) {
					*bits = sensor->output_conf[i]->output_bit;
					*width = sensor->output_conf[i]->output_width;
					*height = sensor->output_conf[i]->output_height;
					return SENSOR_OK;
				}
			}
		}
	}
	return SENSOR_RESOLUTION_NOT_SUPPORTED;
}
