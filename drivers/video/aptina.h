/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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

//------------------------------------------------------------------------------
/// \unit
///
/// !!!Purpose
///
/// Interface for configuration the Omnivision captor.
///
/// !!!Usage
///
/// -# Initialize captor
/// -# Write Omnivision configuration
//------------------------------------------------------------------------------

#ifndef APTINA_H
#define APTINA_H

#include <stdint.h>

#include "peripherals/twid.h"

/** define a structure for ovxxxx register initialization values */
struct mt_reg {
	/* Register to be written */
	uint8_t reg;
	uint8_t va_h;
	uint8_t va_l;
};
//*************************************************************************
#define MT9v022_REG_CHIP_VERSION        0x00
#define MT9v022_TOTAL_SHUTTER           0x0B
#define MT9v022_RESET                   0x0C
#define MT9v022_LED_OUT                 0x1B
#define MT9v022_ANALOG_GAIN             0x35
#define MT9v022_DGAIN_X0Y0              0x80
#define MT9v022_DGAIN_X1Y0              0x81
#define MT9v022_DGAIN_X2Y0              0x82
#define MT9v022_DGAIN_X3Y0              0x83
#define MT9v022_DGAIN_X4Y0              0x84
#define MT9v022_DGAIN_X0Y1              0x85
#define MT9v022_DGAIN_X1Y1              0x86
#define MT9v022_DGAIN_X2Y1              0x87
#define MT9v022_DGAIN_X3Y1              0x88
#define MT9v022_DGAIN_X4Y1              0x89
#define MT9v022_DGAIN_X0Y2              0x8A
#define MT9v022_DGAIN_X1Y2              0x8B
#define MT9v022_DGAIN_X2Y2              0x8C
#define MT9v022_DGAIN_X3Y2              0x8D
#define MT9v022_DGAIN_X4Y2              0x8E
#define MT9v022_DGAIN_X0Y3              0x8F
#define MT9v022_DGAIN_X1Y3              0x90
#define MT9v022_DGAIN_X2Y3              0x91
#define MT9v022_DGAIN_X3Y3              0x92
#define MT9v022_DGAIN_X4Y3              0x93
#define MT9v022_DGAIN_X0Y4              0x94
#define MT9v022_DGAIN_X1Y4              0x95
#define MT9v022_DGAIN_X2Y4              0x96
#define MT9v022_DGAIN_X3Y4              0x97
#define MT9v022_DGAIN_X4Y4              0x98

#define MT9v022_AEC_AGC_ENABLE          0xAF
#define MT9v022_AEC_EXPOSURE_OUTPUT     0xBB
#define MT9v022_MAXIMUM_SHUTTER_WIDTH   0xBD

//*************************************************************************

/*----------------------------------------------------------------------------
 *       Exported functions
 *----------------------------------------------------------------------------*/
extern uint8_t mt_init(struct _twid * pTwid);
extern void mt_DumpRegisters(struct _twid * pTwid);
extern uint32_t mt_write_regs(struct _twid * pTwid, const struct mt_reg *pReglist);
extern uint8_t mt_read_reg(struct _twid * pTwid, uint8_t reg, uint8_t * pData);
//extern uint8_t mt_write_reg(struct _twid *pTwid, uint8_t reg, uint8_t val);
extern uint8_t mt_write_reg(struct _twid * pTwid, uint8_t reg, uint8_t * val);
//extern void write_command (struct _twid *pTwid,uint8_t reg,uint8_t data1,uint8_t data2);

#endif
