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

#ifndef IMAGE_SENSOR_INF_H
#define IMAGE_SENSOR_INF_H

#ifdef CONFIG_HAVE_IMAGE_SENSOR

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include "board.h"

/*---------------------------------------------------------------------------
 *         Definitions
 *---------------------------------------------------------------------------*/
#define SENSOR_OMNIVISION_2640  0
#define SENSOR_OMNIVISION_2643  1
#define SENSOR_OMNIVISION_5640  2
#define SENSOR_OMNIVISION_7670  3
#define SENSOR_OMNIVISION_7740  4
#define SENSOR_OMNIVISION_9740  5

#define SENSOR_SUPPORTED_NUMBER  6

#define SENSOR_SUPPORTED_OUTPUTS 7

/** terminating list entry for register in configuration file */
#define SENSOR_REG_TERM         0xFF
/** terminating list entry for value in configuration file */
#define SENSOR_VAL_TERM         0xFF

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
/** Sensor status or return code */
enum {
	SENSOR_OK = 0,        /**< Operation is successful */
	SENSOR_TWI_ERROR,
	SENSOR_ID_ERROR,
	SENSOR_RESOLUTION_NOT_SUPPORTED
};

/** Sensor type */
enum {
	SENSOR_COMS = 0,
	SENSOR_CCD
};

/** Sensor TWI mode */
enum {
	SENSOR_TWI_REG_BYTE_DATA_BYTE = 0,
	SENSOR_TWI_REG_2BYTE_DATA_BYTE,
	SENSOR_TWI_REG_BYTE_DATA_2BYTE
};

/** Sensor resolution */
enum {
	QVGA = 0,
	VGA,
	SVGA,
	XGA,
	WXGA,
	UVGA
};

/** Sensor output format */
enum {
	RAW_BAYER = 0,
	YUV_422,
	RGB,
	CCIR656,
	MONO
};

/** Sensor output bit width */
enum {
	BIT_8 = 0,
	BIT_9,
	BIT_10,
	BIT_11,
	BIT_12
};

/** define a structure for sensor register initialization values */
struct sensor_reg {
	uint16_t reg; /* Register to be written */
	uint16_t val; /* value to be written */
};

struct sensor_output {
	uint8_t type;                               /** Index 0: normal, 1: AF setting*/
	uint8_t output_resolution;                  /** sensor output resolution */
	uint8_t output_format;                      /** sensor output format */
	uint8_t output_bit;                         /** sensor output bit width */
	uint8_t supported;                          /** supported for current output_resolution*/
	uint32_t output_width;                      /** output width */
	uint32_t output_height;                     /** output height */
	const struct sensor_reg* output_setting;    /** sensor registers setting */
};

/** define a structure for sensor profile */
struct sensor_profile {
	const char* name;             /** Sensor name */
	uint8_t cmos_ccd;             /** Sensor type for CMOS sensor or CCD */
	uint8_t twi_inf_mode;         /** TWI interface mode  */
	uint8_t addr;                 /** TWI slave address */
	uint16_t pid_high_reg;        /** Register address for product ID high byte */
	uint16_t pid_low_reg;         /** Register address for product ID low byte*/
	uint16_t pid_high;            /** product ID high byte */
	uint16_t pid_low;             /** product ID low byte */
	uint16_t version_mask;        /** version mask */
	const struct sensor_output* output_conf[SENSOR_SUPPORTED_OUTPUTS]; /** sensor settings */
};

/*----------------------------------------------------------------------------
 *        Exported sensor profiles
 *----------------------------------------------------------------------------*/

extern const struct sensor_profile mt9v022_profile;
extern const struct sensor_profile ov2640_profile;
extern const struct sensor_profile ov2643_profile;
extern const struct sensor_profile ov5640_profile;
extern const struct sensor_profile ov7670_profile;
extern const struct sensor_profile ov7740_profile;
extern const struct sensor_profile ov9740_profile;

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Detect with given supported sensor index,
 *  or automatically detect the connected sensor.
 * \param twi_bus TWI bus
 * \param detect_auto true for auto detect.
 * \param id  Supported sensor index
 * \return pointer to a profile if no error; otherwise return NULL.
 */
extern struct sensor_profile* sensor_detect(uint8_t twi_bus, bool detect_auto, uint8_t id);

 /**
 * \brief Load and configure sensor setting with giving profile.
 * \param twi_bus TWI bus
 * \param sensor pointer to a sensor profile instance.
 * \param resolution resolution request
 * \return SENSOR_OK if no error; otherwise return SENSOR_XXX_ERROR
 */
extern uint32_t sensor_setup(uint8_t twi_bus,
							 struct sensor_profile* sensor,
							 uint8_t resolution,
							 uint8_t format);

/**
 * \brief Retrieves sensor output bit width and size for giving resolution and format.
 * \param sensor pointer to a sensor profile instance.
 * \param resolution Output resolution request.
 * \param format Output Format request.
 * \param bits   Output Format request.
 * \param width  pointer to image width to be read.
 * \param height  pointer to image height to be read.
 * \return SENSOR_OK if no error; otherwise return SENSOR_XXX_ERROR
 */
extern uint32_t sensor_get_output(struct sensor_profile* sensor,
								  uint8_t resolution,
								  uint8_t format,
								  uint8_t *bits,
								  uint32_t *width,
								  uint32_t *height);

#endif /* CONFIG_HAVE_IMAGE_SENSOR */

#endif /* ! IMAGE_SENSOR_INF_H */
