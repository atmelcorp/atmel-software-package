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
#include "video/omnivision.h"
#include "peripherals/pio.h"
#include "peripherals/twid.h"

#include "trace.h"

/** Slave address of OMNIVISION chips. */
#define OV_CAPTOR_ADDRESS_1   0x30
#define OV_CAPTOR_ADDRESS_2   0x21
#define OV_CAPTOR_ADDRESS_3   0x3c
#define OV_CAPTOR_ADDRESS_4   0x10

/** terminating list entry for register in configuration file */
#define OV_REG_TERM 0xFF
#define OV_REG_DELAY 0xFFFF
/** terminating list entry for value in configuration file */
#define OV_VAL_TERM 0xFF

static const struct _pin pin_ISI_RST = PIN_ISI_RST;
static uint8_t twiSlaveAddr = OV_CAPTOR_ADDRESS_1;
/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/
static void
ov_reset(void)
{
	volatile uint32_t i;
	pio_configure(&pin_ISI_RST, 1);
	pio_clear(&pin_ISI_RST);
	for (i = 0; i < 6000; i++) ;
	pio_set(&pin_ISI_RST);
	for (i = 0; i < 6000; i++) ;
}

/**
 * \brief  Read PID and VER
 * \param pTwid TWI interface
 * \return  VER | (PID<<8)
 */
static uint16_t
ov_id8(struct _twid * pTwid)
{
	uint8_t id, ver;
	uint8_t status;
	// OV_PID
	status = ov_read_reg8(pTwid, 0x0A, &id);
	if (status != 0)
		return 0;
	trace_info("PID  = 0x%X\n\r", id);

	// OV_VER
	status = ov_read_reg8(pTwid, 0x0B, &ver);
	if (status != 0)
		return 0;
	trace_info("VER  = 0x%X\n\r", ver);

	return ((uint16_t) (id << 8) | ver);
}

/**
 * \brief  Read PID and VER
 * \param pTwid TWI interface
 * \return  VER | (PID<<8)
 */
static uint16_t
ov_id16(struct _twid * pTwid)
{
	uint8_t id, ver;
	// OV_PID
	ov_read_reg16(pTwid, 0x300A, &id);
	trace_info("PID  = 0x%X\n\r", id);

	// OV_VER
	ov_read_reg16(pTwid, 0x300B, &ver);
	trace_info("VER  = 0x%X\n\r", ver);

	return ((uint16_t) (id << 8) | ver);
}

/**
 * \brief  Read PID and VER
 * \param pTwid TWI interface
 * \return  VER | (PID<<8)
 */
static uint16_t
ov_id(struct _twid * pTwid)
{
	uint16_t id;
	printf("-I- Try TWI address 0x%x \n\r", twiSlaveAddr);
	twiSlaveAddr = OV_CAPTOR_ADDRESS_1;
	id = ov_id8(pTwid);
	if (id == 0) {
		twiSlaveAddr = OV_CAPTOR_ADDRESS_2;
		printf("-I- Try TWI address 0x%x \n\r", twiSlaveAddr);
		id = ov_id8(pTwid);
		if (id == 0) {
			twiSlaveAddr = OV_CAPTOR_ADDRESS_3;
			printf("-I- Try TWI address 0x%x \n\r", twiSlaveAddr);
			id = ov_id16(pTwid);
			if (id == 0) {
				twiSlaveAddr = OV_CAPTOR_ADDRESS_4;
				printf("-I- Try TWI address 0x%x \n\r",
				       twiSlaveAddr);
				id = ov_id16(pTwid);
			}
		}
	}
	return id;
}

/*----------------------------------------------------------------------------
 *        Global Functions
 *----------------------------------------------------------------------------*/
/**
 * \brief  Read a value from a register in an OV sensor device.
 * \param pTwid TWI interface
 * \param reg Register to be read
 * \param isize Internal address size in bytes.
 * \param pData Data read
 * \return 0 if no error; otherwize TWID_ERROR_BUSY
 */
uint8_t
ov_read_reg8(struct _twid * pTwid, uint8_t reg, uint8_t * pData)
{
	uint8_t status;

	status = twid_write(pTwid, twiSlaveAddr, 0, 0, &reg, 1, 0);
	status |= twid_read(pTwid, twiSlaveAddr, 0, 0, pData, 1, 0);
	if (status != 0) {
		trace_error("ov_read_reg pb\n\r");
	}
	return status;
}

/**
 * \brief  Read a value from a register in an OV sensor device.
 * \param pTwid TWI interface
 * \param reg Register to be read
 * \param pData Data read
 * \return 0 if no error; otherwize TWID_ERROR_BUSY
 */
uint8_t
ov_read_reg16(struct _twid * pTwid, uint16_t reg, uint8_t * pData)
{
	uint8_t status;
	uint8_t reg8[2];
	reg8[0] = reg >> 8;
	reg8[1] = reg & 0xff;

	status = twid_write(pTwid, twiSlaveAddr, 0, 0, reg8, 2, 0);
	status |= twid_read(pTwid, twiSlaveAddr, 0, 0, pData, 1, 0);
	if (status != 0) {

		trace_error("ov_read_reg pb\n\r");
	}
	return status;
}

/**
 * \brief  Write a value to a register in an OV sensor device.
 * \param pTwid TWI interface
 * \param reg Register to be writen
 * \param pData Data written
 * \return 0 if no error; otherwize TWID_ERROR_BUSY
 */
uint8_t
ov_write_reg8(struct _twid * pTwid, uint8_t reg, uint8_t val)
{
	uint8_t status;

	status = twid_write(pTwid, twiSlaveAddr, reg, 1, &val, 1, 0);
	if (status != 0) {
		trace_error("ov_write_reg pb\n\r");
	}

	return status;
}

/**
 * \brief  Write a value to a register in an OV sensor device.
 * \param pTwid TWI interface
 * \param reg Register to be writen
 * \param pData Data written
 * \return 0 if no error; otherwize TWID_ERROR_BUSY
 */
uint8_t
ov_write_reg16(struct _twid * pTwid, uint16_t reg, uint8_t val)
{
	uint8_t status;
	status = twid_write(pTwid, twiSlaveAddr, reg, 2, &val, 1, 0);
	if (status != 0) {
		trace_error("ov_write_reg pb\n\r");
	}

	return status;
}

/**
 * \brief  Initialize a list of OV registers.
 * The list of registers is terminated by the pair of values
 * \param pTwid TWI interface
 * \param pReglist Register list to be written
 * \return 0 if no error; otherwize TWID_ERROR_BUSY
 */
uint32_t
ov_write_regs8(struct _twid * pTwid, const struct ov_reg * pReglist)
{
	uint32_t err;
	uint32_t size = 0;
	const struct ov_reg *pNext = pReglist;
	volatile uint32_t delay;

	trace_debug("ov_write_regs:");
	while (!((pNext->reg == OV_REG_TERM) && (pNext->val == OV_VAL_TERM))) {
		err = ov_write_reg8(pTwid, pNext->reg, pNext->val);

		size++;
		for (delay = 0; delay <= 10000; delay++) ;
		if (err == TWID_ERROR_BUSY) {
			trace_error("ov_write_regs: TWI ERROR\n\r");
			return err;
		}
		//printf("(0x%02x,0x%02x) \n\r",  pNext->reg,pNext->val);
		pNext++;
	}
	trace_debug_wp("\n\r");
	return 0;
}

/**
 * \brief  Initialize a list of OV registers.
 * The list of registers is terminated by the pair of values
 * \param pTwid TWI interface
 * \param pReglist Register list to be written
 * \return 0 if no error; otherwize TWID_ERROR_BUSY
 */
uint32_t
ov_write_regs16(struct _twid * pTwid, const struct ov_reg * pReglist)
{
	uint32_t err = 0;
	uint32_t size = 0;
	const struct ov_reg *pNext = pReglist;
	volatile uint32_t delay;

	trace_debug("ov_write_regs:");
	while (!((pNext->reg == OV_REG_TERM) && (pNext->val == OV_VAL_TERM))) {
		err = ov_write_reg16(pTwid, pNext->reg, pNext->val);
		size++;
		for (delay = 0; delay <= 10000; delay++) ;
		if (err == TWID_ERROR_BUSY) {
			trace_error("ov_write_regs: TWI ERROR\n\r");
			return err;
		}
		//printf("(0x%02x,0x%02x) \n\r",  pNext->reg,pNext->val);
		pNext++;
	}
	trace_debug_wp("\n\r");
	return 0;
}

void
isOV5640_AF_InitDone(struct _twid * pTwid)
{
	uint8_t value = 0;
	while (1) {
		ov_read_reg16(pTwid, 0x3029, &value);
		if (value == 0x70)
			break;
	}
}

/**
 * \brief  AF for OV 5640
 * \param pTwid TWI interface
 * \return 0 if no error; otherwize TWID_ERROR_BUSY
 */
uint32_t
ov_5640_AF_single(struct _twid * pTwid)
{
	uint8_t value;
	ov_write_reg16(pTwid, 0x3023, 1);
	ov_write_reg16(pTwid, 0x3022, 3);
	value = 1;
	while (1) {
		ov_read_reg16(pTwid, 0x3023, &value);
		if (value == 0)
			break;
	}
	return 0;
}

uint32_t
ov_5640_AF_continue(struct _twid * pTwid)
{
	uint8_t value;
	ov_write_reg16(pTwid, 0x3024, 1);
	ov_write_reg16(pTwid, 0x3022, 4);
	value = 1;
	while (1) {
		ov_read_reg16(pTwid, 0x3023, &value);
		if (value == 0)
			break;
	}
	return 0;
}

uint32_t
ov_5640_AFPause(struct _twid * pTwid)
{
	uint8_t value;
	ov_write_reg16(pTwid, 0x3023, 1);
	ov_write_reg16(pTwid, 0x3022, 6);
	value = 1;
	while (1) {
		ov_read_reg16(pTwid, 0x3023, &value);
		if (value == 0)
			break;
	}
	return 0;
}

uint32_t
ov_5640_AFrelease(struct _twid * pTwid)
{
	uint8_t value;
	ov_write_reg16(pTwid, 0x3023, 1);
	ov_write_reg16(pTwid, 0x3022, 8);
	value = 1;
	while (1) {
		ov_read_reg16(pTwid, 0x3023, &value);
		if (value == 0)
			break;
	}
	return 0;
}

/**
 * \brief  Dump all register
 * \param pTwid TWI interface
 */
void
ov_DumpRegisters8(struct _twid * pTwid)
{
	uint32_t i;
	uint8_t value;

	trace_info_wp("Dump all camera register\n\r");
	for (i = 0; i <= 0x5C; i++) {
		value = 0;
		ov_read_reg8(pTwid, i, &value);
		trace_info_wp("[0x%02x]=0x%02x ", i, value);
		if (((i + 1) % 5) == 0) {
			trace_info_wp("\n\r");
		}
	}
	trace_info_wp("\n\r");
}

/**
 * \brief  Dump all register
 * \param pTwid TWI interface
 */
void
ov_DumpRegisters16(struct _twid * pTwid)
{
	uint32_t i;
	uint8_t value;

	trace_info_wp("Dump all camera register\n\r");
	for (i = 3000; i <= 0x305C; i++) {
		value = 0;
		ov_read_reg16(pTwid, i, &value);
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
 * \return OV type
 */
uint8_t
ov_init(struct _twid * pTwid)
{
	uint16_t id = 0;
	uint8_t ovType;
	ov_reset();
	id = ov_id(pTwid);
	switch (id) {
	case 0x7740:
	case 0x7742:
		ovType = OV_7740;
		break;
	case 0x9740:
	case 0x9742:
		ovType = OV_9740;
		break;
	case 0x2642:
	case 0x2640:
		ovType = OV_2640;
		break;
	case 0x2643:
		ovType = OV_2643;
		break;
	case 0x5640:
		ovType = OV_5640;
		break;
	default:
		ovType = OV_UNKNOWN;
		trace_error("Can not support product ID %x \n\r", id);
		break;
	}
	return ovType;
}
