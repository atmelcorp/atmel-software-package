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

#ifndef PAC1720_H_
#define PAC1720_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "peripherals/bus.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

struct _pac1720_desc {
	struct _bus_dev_cfg cfg;
	uint8_t addr;
	struct {
		uint32_t fsr; /* Current Sensing Range: Table 4-6  */
		uint32_t denominator; /* Current Denominator: Table 4-5 */
	} private;
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern int pac1720_configure(struct _pac1720_desc* desc);

extern int pac1720_wait_for_conversion(struct _pac1720_desc* desc, uint16_t wait);

extern int pac1720_read_vsense(struct _pac1720_desc* desc, uint8_t channel, uint16_t* vsense);

extern int pac1720_read_vsource(struct _pac1720_desc* desc, uint8_t channel, uint16_t* vsource);

extern int pac1720_read_power(struct _pac1720_desc* desc, uint8_t channel, uint16_t* power);

extern int pac1720_convert(struct _pac1720_desc* desc, float rsense,
		uint16_t vsense, uint16_t vsource, uint16_t pratio,
		float* i, float* v, float* w);

#endif /* ! PAC1720_H_ */
