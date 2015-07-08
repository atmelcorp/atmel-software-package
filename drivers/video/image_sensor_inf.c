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
#include "peripherals/twihs.h"
#include "peripherals/twihsd.h"
#include <stdbool.h>
#include <stdio.h>

#include "trace.h"
/*----------------------------------------------------------------------------
 *        Local variable
 *----------------------------------------------------------------------------*/
static const sensorProfile_t* pSensor;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Read value from a register in an dedicated sensor device.
 * \param pTwid TWI interface
 * \param reg Register to be read
 * \param pData Data read
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static sensorStatus_t sensor_twi_read_reg(Twihsd* pTwid,
					  uint16_t reg,
					  uint8_t * pData)
{
	uint8_t status;
	uint8_t reg8[2];
	reg8[0] = reg >> 8;
	reg8[1] = reg & 0xff;
	switch (pSensor->twi_inf_mode){
	case SENSOR_TWI_REG_BYTE_DATA_BYTE:
		status = twihsd_write(pTwid, pSensor->twi_slave_addr, 0, 0, &reg8[1], 1, 0);
		status |= twihsd_read(pTwid, pSensor->twi_slave_addr, 0, 0, pData, 1, 0);
		break;

	case SENSOR_TWI_REG_2BYTE_DATA_BYTE:
		status = twihsd_write(pTwid, pSensor->twi_slave_addr, 0, 0, reg8, 2, 0);
		status |= twihsd_read(pTwid, pSensor->twi_slave_addr, 0, 0, pData, 1, 0);
		break;

	case SENSOR_TWI_REG_BYTE_DATA_2BYTE:
		status = twihsd_write(pTwid, pSensor->twi_slave_addr, 0, 0, &reg8[1], 1, 0);
		status |= twihsd_read(pTwid, pSensor->twi_slave_addr, 0, 0, pData, 2, 0);

		break;
	default:
		return SENSOR_TWI_ERROR;
	}
	if (status) return SENSOR_TWI_ERROR;
	return SENSOR_OK;
}

/**
 * \brief  Write a value to a register in an dedicated sensor device.
 * \param pTwid TWI interface
 * \param reg Register to be written
 * \param pData Data written
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static sensorStatus_t sensor_twi_write_reg(Twihsd* pTwid,
					   uint16_t reg,
					   uint8_t *pData)
{
	uint8_t status;
	switch (pSensor->twi_inf_mode){
	case SENSOR_TWI_REG_BYTE_DATA_BYTE:
		status = twihsd_write(pTwid, pSensor->twi_slave_addr, reg, 1, pData, 1, 0);
		break;

	case SENSOR_TWI_REG_2BYTE_DATA_BYTE:
		status = twihsd_write(pTwid, pSensor->twi_slave_addr, reg, 2, pData, 1, 0);
		break;

	case SENSOR_TWI_REG_BYTE_DATA_2BYTE:
		status = twihsd_write(pTwid, pSensor->twi_slave_addr, reg, 1, pData, 2, 0);
		break;

	default:
		return SENSOR_TWI_ERROR;
	}
	if (status) return SENSOR_TWI_ERROR;
	return SENSOR_OK;
}

/**
 * \brief Read and check sensor product ID.
 * \param pTwid TWI interface
 * \param reg_h Register address for product ID high byte.
 * \param reg_l Register address for product ID low byte.
 * \param pid Product ID to be compared.
 * \param ver_mask version mask.
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
static sensorStatus_t sensor_check_pid(Twihsd* pTwid,
				       uint16_t reg_h,
				       uint16_t reg_l,
				       uint16_t pid,
				       uint16_t ver_mask)
{
	uint8_t status;
	uint16_t pid_high, pid_low;
	status = sensor_twi_read_reg(pTwid, reg_h, (uint8_t*)&pid_high);
	status |= sensor_twi_read_reg(pTwid, reg_l,(uint8_t*)&pid_low);
	printf("PID = <%x, %x> \n\r", pid_high ,pid_low );
	if (status) return SENSOR_TWI_ERROR;
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
 * \param pTwid TWI interface
 * \param pReglist Register list to be written
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
sensorStatus_t sensor_twi_write_regs(Twihsd* pTwid, const sensorReg_t * pReglist)
{
	uint8_t status;
	const sensorReg_t *pNext = pReglist;
	volatile uint32_t delay;

	while (!((pNext->reg == SENSOR_REG_TERM) && (pNext->val == SENSOR_VAL_TERM))) {
		status = sensor_twi_write_reg( pTwid, pNext->reg, (uint8_t *)(&pNext->val));
		for (delay = 0; delay <= 10000; delay++) ;
		if (status) return SENSOR_TWI_ERROR;
		pNext++;
	}
	return SENSOR_OK;
}

/**
 * \brief  read list of registers.
 * The list of registers is terminated by the pair of values
 * \param pTwid TWI interface
 * \param pReglist Register list to be read
 * \return SENSOR_OK if no error; otherwise SENSOR_TWI_ERROR
 */
sensorStatus_t sensor_twi_read_regs(Twihsd* pTwid, const sensorReg_t * pReglist)
{
	uint8_t status;
	const sensorReg_t *pNext = pReglist;
	volatile uint32_t delay;
	uint8_t val;
	while (!((pNext->reg == SENSOR_REG_TERM) && (pNext->val == SENSOR_VAL_TERM))) {
		status = sensor_twi_read_reg( pTwid, pNext->reg, (uint8_t *)&val);
		//printf("< %x, %x>\n\r", pNext->reg, val);
		for (delay = 0; delay <= 10000; delay++) ;
		if (status) return SENSOR_TWI_ERROR;
		pNext++;
	}
	return SENSOR_OK;
}

/**
 * \brief Load and configure sensor setting with giving profile.
 * \param sensor_profile pointer to a profile instance.
 * \param resolution resolution request
 * \return SENSOR_OK if no error; otherwise return SENSOR_XXX_ERROR
 */
sensorStatus_t sensor_setup(Twihsd* pTwid,
			    const sensorProfile_t *sensor_profile,
			    sensorOutputResolution_t resolution,
			    sensorOutputFormat_t format )
{
	uint8_t i;
	uint8_t found = 0;
	sensorStatus_t status = SENSOR_OK;
	for (i = 0; i< SENDOR_SUPPORTED_OUTPUTS; i++) {
		if (sensor_profile->outputConf[i]->supported){
			if (sensor_profile->outputConf[i]->output_resolution == resolution) {
				if (sensor_profile->outputConf[i]->output_format == format) {
					found = 1;
					break;
				}
			}
		}
	}
	if (found == 0)
		return SENSOR_RESOLUTION_NOT_SUPPORTED;
	pSensor = sensor_profile;

	status = sensor_check_pid(pTwid,
				  pSensor->pid_high_reg,
				  pSensor->pid_low_reg,
				  (pSensor->pid_high) << 8 | pSensor->pid_low,
				  pSensor->version_mask);

	if (status) return SENSOR_ID_ERROR;
	return sensor_twi_write_regs(pTwid, pSensor->outputConf[i]->output_setting);
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
sensorStatus_t sensor_get_output(sensorOutputResolution_t resolution,
				 sensorOutputFormat_t format,
				 sensorOutputBit_t *bits,
				 uint32_t *width,
				 uint32_t* height)
{
	uint8_t i;
	for (i = 0; i< SENDOR_SUPPORTED_OUTPUTS; i++) {
		if (pSensor->outputConf[i]->supported){
			if (pSensor->outputConf[i]->output_resolution == resolution) {
				if (pSensor->outputConf[i]->output_format == format) {
					*bits = pSensor->outputConf[i]->output_bit;
					*width = pSensor->outputConf[i]->output_width;
					*height = pSensor->outputConf[i]->output_height;
					return SENSOR_OK;
				}
			}
		}
	}
	return SENSOR_RESOLUTION_NOT_SUPPORTED;
}
