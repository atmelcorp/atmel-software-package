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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "io/aptina.h"
#include "io/omnivision.h"
#include "bus/twid.h"
#include "core/pio.h"

#include "utils/trace.h"

#define MT_CAPTOR_ADDRESS   (0x90>>1)
#define MT_REG_TERM 0xFF
#define MT_VAL_H_TERM 0xFF
#define MT_VAL_L_TERM 0xFF

#define MT_9V022         0x05

uint8_t BUF[3];
static const struct _pin pin_ISI_RST = PIN_ISI_RST;

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/
static void
write_command(struct _twid * pTwid, uint8_t reg, uint8_t data1, uint8_t data2)
{
	BUF[0] = reg;
	BUF[1] = data1;
	BUF[2] = data2;
	mt_write_reg(pTwid, BUF[0], &BUF[1]);
}

static void
mt_reset(struct _twid * pTwid)
{
	volatile uint32_t i;
	pio_configure(&pin_ISI_RST, 1);
	pio_clear(&pin_ISI_RST);
	for (i = 0; i < 6000; i++) ;
	pio_set(&pin_ISI_RST);
	for (i = 0; i < 6000; i++) ;

	write_command(pTwid, MT9v022_RESET, 0x00, 0x01);
	for (i = 0; i < 6000; i++) ;
	write_command(pTwid, MT9v022_RESET, 0x00, 0x00);

}

/**
 * \brief  Read PID and VER
 * \param pTwid TWI interface
 * \return  VER | (PID<<8)
 */
static unsigned short
mt_id(struct _twid * pTwid)
{
	uint8_t id = 0;
	uint8_t ver = 0;

	// MT_PID
	mt_read_reg(pTwid, MT9v022_REG_CHIP_VERSION, &id);
	printf("PID  = 0x%X\n\r", id);

	// MT_VER
	mt_read_reg(pTwid, MT9v022_REG_CHIP_VERSION, &ver);
	printf("VER  = 0x%X\n\r", ver);

	return ((unsigned short) (id << 8) | ver);
}

/*----------------------------------------------------------------------------
 *        Global Functions
 *----------------------------------------------------------------------------*/
/**
 * \brief  Read a value from a register in an MT sensor device.
 * \param pTwid TWI interface
 * \param reg Register to be read
 * \param pData Data read
 * \return 0 if no error; otherwise TWID_ERROR_BUSY
 */
uint8_t
mt_read_reg(struct _twid * pTwid, uint8_t reg, uint8_t * pData)
{
	uint8_t status;
	status = twid_write(pTwid, MT_CAPTOR_ADDRESS, 0, 0, &reg, 1, 0);
	status |= twid_read(pTwid, MT_CAPTOR_ADDRESS, 0, 0, pData, 2, 0);
	if (status != 0) {
		trace_error("mt_read_reg pb");
	}
	return status;
}

/**
 * \brief  Write a value to a register in an OV sensor device.
 * \param pTwid TWI interface
 * \param reg Register to be written
 * \param val Data written
 * \return 0 if no error; otherwise TWID_ERROR_BUSY
 */
uint8_t
mt_write_reg(struct _twid * pTwid, uint8_t reg, uint8_t * val)
{
	uint8_t status;
	status = twid_write(pTwid, MT_CAPTOR_ADDRESS, reg, 1, val, 2, 0);
	if (status != 0) {
		trace_error("mt_write_reg pb");
	}
	return status;
}

/**
 * \brief  Initialize a list of MT registers.
 * The list of registers is terminated by the pair of values
 * \param pTwid TWI interface
 * \param pReglist Register list to be written
 * \return 0 if no error; otherwise TWID_ERROR_BUSY
 */
uint32_t
mt_write_regs(struct _twid * pTwid, const struct mt_reg * pReglist)
{
	uint32_t err;
	uint32_t size = 0;
	const struct mt_reg *pNext = pReglist;
	volatile uint32_t delay;
	trace_debug("mt_write_regs:");
	BUF[0] = pNext->reg;
	BUF[1] = pNext->va_h;
	BUF[2] = pNext->va_l;
	while (!
	       ((pNext->reg == MT_REG_TERM) && (pNext->va_h == MT_VAL_H_TERM)
		&& (pNext->va_l == MT_VAL_L_TERM))) {
		err = mt_write_reg(pTwid, BUF[0], &BUF[1]);
		size++;
		for (delay = 0; delay <= 10000; delay++) ;
		if (err == TWID_ERROR_BUSY) {
			trace_error("mt_write_regs: TWI ERROR\n\r");
			return err;
		}
		pNext++;
		BUF[0] = pNext->reg;
		BUF[1] = pNext->va_h;
		BUF[2] = pNext->va_l;
	}
	trace_debug_wp("\n\r");
	mt_read_reg(pTwid, 0x00, &BUF[1]);
	return 0;
}

/**
 * \brief  Dump all register
 * \param pTwid TWI interface
 */
void
mt_DumpRegisters(struct _twid * pTwid)
{
	uint32_t i;
	uint8_t value;

	trace_info_wp("Dump all camera register\n\r");
	for (i = 0; i <= 0x5C; i++) {
		value = 0;
		mt_read_reg(pTwid, i, &value);
		trace_info_wp("[0x%02x]=0x%02x ", i, value);
		if (((i + 1) % 5) == 0) {
			trace_info_wp("\n\r");
		}
	}
	trace_info_wp("\n\r");
}

/**
 * \brief Sequence For correct operation of the sensor
 * \param pTwid TWI interface
 * \return MT type
 */
uint8_t
mt_init(struct _twid * pTwid)
{
	uint16_t id = 0;
	uint8_t mtType;
	mt_reset(pTwid);
	id = mt_id(pTwid);
	switch (id) {
	case 0x1313:
		mtType = MT_9V022;
		break;
	default:
		mtType = OV_UNKNOWN;
		trace_error("Can not support product ID %x \n\r", id);
		break;
	}
	return mtType;
}
