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

#include <stdint.h>

/*---------------------------------------------------------------------------
 *         Definition
 *---------------------------------------------------------------------------*/
#define SENSOR_SUPPORTED_OUTPUTS 7

/** terminating list entry for register in configuration file */
#define SENSOR_REG_TERM         0xFF
/** terminating list entry for value in configuration file */
#define SENSOR_VAL_TERM         0xFF

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

struct _twi_desc;

/** Sensor type */
typedef enum _sensor_type {
	SENSOR_COMS = 0,
	SENSOR_CCD
}sensor_type_t;

/** Sensor status or return code */
typedef enum _sensor_status {
	SENSOR_OK = 0,        /**< Operation is successful */
	SENSOR_TWI_ERROR,
	SENSOR_ID_ERROR,
	SENSOR_RESOLUTION_NOT_SUPPORTED
} sensor_status_t;

/** Sensor TWI mode */
typedef enum _sensor_twi_mode {
	SENSOR_TWI_REG_BYTE_DATA_BYTE = 0,
	SENSOR_TWI_REG_2BYTE_DATA_BYTE,
	SENSOR_TWI_REG_BYTE_DATA_2BYTE
} sensor_twi_mode_t;

/** Sensor resolution */
typedef enum _sensor_resolution {
	QVGA = 0,
	VGA,
	SVGA,
	XGA,
	WXGA,
	UVGA
} sensor_output_resolution_t;

/** Sensor output format */
typedef enum _sensor_output_format {
	RAW_BAYER = 0,
	YUV_422,
	RGB,
	CCIR656,
	MONO
} sensor_output_format_t;

/** Sensor output bit width */
typedef enum _sensor_output_bit {
	BIT_8 = 0,
	BIT_9,
	BIT_10,
	BIT_11,
	BIT_12
} sensor_output_bit_t;


/** define a structure for sensor register initialization values */
typedef struct _sensor_reg {
	uint16_t reg; /* Register to be written */
	uint16_t val; /* value to be written */
}sensor_reg_t;

typedef struct _sensor_output {
	uint8_t type ;                              /** Index 0: normal, 1: AF setting*/
	sensor_output_resolution_t output_resolution; /** sensor output resolution */
	sensor_output_format_t output_format;         /** sensor output format */
	sensor_output_bit_t output_bit;               /** sensor output bit width */
	uint8_t supported;                          /** supported for current output_resolution*/
	uint32_t output_width;                      /** output width */
	uint32_t output_height;                     /** output height */
	const sensor_reg_t *output_setting;          /** sensor registers setting */
}sensor_output_t;

/** define a structure for sensor profile */
typedef struct _sensor_profile {
	sensor_type_t cmos_ccd;        /** Sensor type for CMOS sensor or CCD */
	sensor_twi_mode_t twi_inf_mode; /** TWI interface mode  */
	uint32_t twi_slave_addr;      /** TWI slave address */
	uint16_t pid_high_reg;        /** Register address for product ID high byte */
	uint16_t pid_low_reg;         /** Register address for product ID low byte*/
	uint16_t pid_high;            /** product ID high byte */
	uint16_t pid_low;             /** product ID low byte */
	uint16_t version_mask;        /** version mask */
	const sensor_output_t *output_conf[SENSOR_SUPPORTED_OUTPUTS]; /** sensor settings */
}sensor_profile_t;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
extern sensor_status_t sensor_twi_write_regs(struct _twi_desc *p_twid,
						const sensor_reg_t *p_reglist);

extern sensor_status_t sensor_twi_read_regs(struct _twi_desc *p_twid,
						const sensor_reg_t *p_reglist);

extern sensor_status_t sensor_setup(struct _twi_desc *p_twid,
						const sensor_profile_t *sensor_profile,
						sensor_output_resolution_t resolution,
						sensor_output_format_t format);

extern sensor_status_t sensor_get_output(sensor_output_resolution_t resolution,
						sensor_output_format_t format,
						sensor_output_bit_t *bits,
						uint32_t *width,
						uint32_t *height);
