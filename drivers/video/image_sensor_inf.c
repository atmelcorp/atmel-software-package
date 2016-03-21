/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
#include "chip.h"

#include "video/image_sensor_inf.h"
#include "peripherals/twi.h"
#include "peripherals/twid_legacy.h"

#include <stdbool.h>
#include <stdio.h>
 
#include "timer.h"
#include "trace.h"
/*----------------------------------------------------------------------------
 *        Local variable
 *----------------------------------------------------------------------------*/
static const sensor_profile_t *p_sensor;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Read value from a register in an dedicated sensor device.
 * \param p_twid TWI interface
 * \param reg Register to be read
 * \param p_data Data read
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static sensor_status_t sensor_twi_read_reg(struct _twid* p_twid,
						uint16_t reg,
						uint8_t *p_data)
{
	uint8_t status;
	uint8_t reg8[2];
	reg8[0] = reg >> 8;
	reg8[1] = reg & 0xff;
	switch (p_sensor->twi_inf_mode){
	case SENSOR_TWI_REG_BYTE_DATA_BYTE:
		status = twid_write(p_twid, p_sensor->twi_slave_addr, 0, 0, &reg8[1], 1, 0);
        timer_wait(10);
		status |= twid_read(p_twid, p_sensor->twi_slave_addr, 0, 0, p_data, 1, 0);
		break;

	case SENSOR_TWI_REG_2BYTE_DATA_BYTE:
		status = twid_write(p_twid, p_sensor->twi_slave_addr, 0, 0, reg8, 2, 0);
		status |= twid_read(p_twid, p_sensor->twi_slave_addr, 0, 0, p_data, 1, 0);
		break;

	case SENSOR_TWI_REG_BYTE_DATA_2BYTE:
		status = twid_write(p_twid, p_sensor->twi_slave_addr, 0, 0, &reg8[1], 1, 0);
		status |= twid_read(p_twid, p_sensor->twi_slave_addr, 0, 0, p_data, 2, 0);

		break;
	default:
		return SENSOR_TWI_ERROR;
	}
	if (status) return SENSOR_TWI_ERROR;
	return SENSOR_OK;
}

/**
 * \brief  Write a value to a register in an dedicated sensor device.
 * \param p_twid TWI interface
 * \param reg Register to be written
 * \param p_data Data written
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static sensor_status_t sensor_twi_write_reg(struct _twid* p_twid,
						uint16_t reg,
						uint8_t *p_data)
{
	uint8_t status;
	switch (p_sensor->twi_inf_mode){
	case SENSOR_TWI_REG_BYTE_DATA_BYTE:
		status = twid_write(p_twid, p_sensor->twi_slave_addr, reg, 1, p_data, 1, 0);
		break;

	case SENSOR_TWI_REG_2BYTE_DATA_BYTE:
		status = twid_write(p_twid, p_sensor->twi_slave_addr, reg, 2, p_data, 1, 0);
		break;

	case SENSOR_TWI_REG_BYTE_DATA_2BYTE:
		status = twid_write(p_twid, p_sensor->twi_slave_addr, reg, 1, p_data, 2, 0);
		break;

	default:
		return SENSOR_TWI_ERROR;
	}
	if (status) return SENSOR_TWI_ERROR;
	return SENSOR_OK;
}

/**
 * \brief Read and check sensor product ID.
 * \param p_twid TWI interface
 * \param reg_h Register address for product ID high byte.
 * \param reg_l Register address for product ID low byte.
 * \param pid Product ID to be compared.
 * \param ver_mask version mask.
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static sensor_status_t sensor_check_pid(struct _twid *p_twid,
						uint16_t reg_h,
						uint16_t reg_l,
						uint16_t pid,
						uint16_t ver_mask)
{
	uint16_t pid_high, pid_low;
	if (sensor_twi_read_reg(p_twid, reg_h, (uint8_t*)&pid_high) != SENSOR_OK)
		return SENSOR_TWI_ERROR;
	if (sensor_twi_read_reg(p_twid, reg_l,(uint8_t*)&pid_low) != SENSOR_OK)
		return SENSOR_TWI_ERROR;
	printf("PID = <%x, %x> \n\r", pid_high ,pid_low );
	if ((pid & ver_mask) == (((pid_high << 8 )| (pid_low)) & ver_mask))
		return SENSOR_OK;
	else
		return SENSOR_ID_ERROR;
}


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief  Initialize a list of registers.
 * The list of registers is terminated by the pair of values
 * \param p_twid TWI interface
 * \param p_reglist Register list to be written
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
sensor_status_t sensor_twi_write_regs(struct _twid *p_twid, const sensor_reg_t *p_reglist)
{
	uint8_t status;
	const sensor_reg_t *p_next = p_reglist;
	volatile uint32_t delay;

	while (!((p_next->reg == SENSOR_REG_TERM) && (p_next->val == SENSOR_VAL_TERM))) {
		status = sensor_twi_write_reg( p_twid, p_next->reg, (uint8_t *)(&p_next->val));
		for (delay = 0; delay <= 10000; delay++) ;
		if (status) return SENSOR_TWI_ERROR;
		p_next++;
	}
	return SENSOR_OK;
}

/**
 * \brief  read list of registers.
 * The list of registers is terminated by the pair of values
 * \param p_twid TWI interface
 * \param p_reglist Register list to be read
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
sensor_status_t sensor_twi_read_regs(struct _twid *p_twid, const sensor_reg_t *p_reglist)
{
	uint8_t status;
	const sensor_reg_t *p_next = p_reglist;
	volatile uint32_t delay;
	uint8_t val;
	while (!((p_next->reg == SENSOR_REG_TERM) && (p_next->val == SENSOR_VAL_TERM))) {
		status = sensor_twi_read_reg( p_twid, p_next->reg, (uint8_t *)&val);
		for (delay = 0; delay <= 10000; delay++) ;
		if (status) return SENSOR_TWI_ERROR;
		p_next++;
	}
	return SENSOR_OK;
}

/**
 * \brief Load and configure sensor setting with giving profile.
 * \param sensor_profile pointer to a profile instance.
 * \param resolution resolution request
 * \return SENSOR_OK if no error; otherwise return SENSOR_XXX_ERROR
 */
sensor_status_t sensor_setup(struct _twid* p_twid,
				const sensor_profile_t *sensor_profile,
				sensor_output_resolution_t resolution,
				sensor_output_format_t format )
{
	uint8_t i;
	uint8_t found = 0;
	sensor_status_t status = SENSOR_OK;
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
	p_sensor = sensor_profile;

	status = sensor_check_pid(p_twid,
					p_sensor->pid_high_reg,
					p_sensor->pid_low_reg,
					(p_sensor->pid_high) << 8 | p_sensor->pid_low,
					p_sensor->version_mask);
	if (status != SENSOR_OK)
		return SENSOR_ID_ERROR;
	else 
		return sensor_twi_write_regs(p_twid, p_sensor->output_conf[i]->output_setting);
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
sensor_status_t sensor_get_output(sensor_output_resolution_t resolution,
					sensor_output_format_t format,
					sensor_output_bit_t *bits,
					uint32_t *width,
					uint32_t* height)
{
	uint8_t i;
	for (i = 0; i < SENSOR_SUPPORTED_OUTPUTS; i++) {
		if (p_sensor->output_conf[i]->supported){
			if (p_sensor->output_conf[i]->output_resolution == resolution) {
				if (p_sensor->output_conf[i]->output_format == format) {
					*bits = p_sensor->output_conf[i]->output_bit;
					*width = p_sensor->output_conf[i]->output_width;
					*height = p_sensor->output_conf[i]->output_height;
					return SENSOR_OK;
				}
			}
		}
	}
	return SENSOR_RESOLUTION_NOT_SUPPORTED;
}
