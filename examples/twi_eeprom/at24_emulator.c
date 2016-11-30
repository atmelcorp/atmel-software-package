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

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "board.h"
#include "trace.h"

#include "i2c/twid.h"

#include "at24_emulator.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Constants
 *----------------------------------------------------------------------------*/

#define TWI_SLAVE_SIZE 256

#define TWI_EEPROM_OFFSET 0
#define TWI_EEPROM_DATA   1


/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

/** The slave device instance*/
struct _at24_emulator_driver
{
	/** Memory buffer */
	uint8_t data[TWI_SLAVE_SIZE];
	/** Offset of the memory access */
	uint8_t offset;
	/** Read address of the request */
	uint8_t state;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** instance of TWI slave device */
static struct _at24_emulator_driver _at24_emulator;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _at24_emulator_on_start(void)
{
	_at24_emulator.state = TWI_EEPROM_OFFSET;
}

static int16_t _at24_emulator_on_read(uint8_t byte)
{
	int16_t ret = 1;

	switch (_at24_emulator.state) {
	case TWI_EEPROM_OFFSET:
		/* Acquire address */
		_at24_emulator.offset = byte;
		_at24_emulator.state = TWI_EEPROM_DATA;
		/* Send first data byte */
		ret = _at24_emulator.data[_at24_emulator.offset];
		break;
	case TWI_EEPROM_DATA:
		/* Read one byte of data from master to slave device */
		_at24_emulator.data[_at24_emulator.offset] = byte;
		_at24_emulator.offset = (_at24_emulator.offset + 1) % TWI_SLAVE_SIZE;
		break;
	default:
		ret = -1;
	}

	return ret;
}

static int16_t _at24_emulator_on_write(void)
{
	int16_t ret = -1;

	/* Send next data byte */
	_at24_emulator.offset = (_at24_emulator.offset + 1) % TWI_SLAVE_SIZE;
	ret = _at24_emulator.data[_at24_emulator.offset];

	return ret;
}

/*------------------------------------------------------------------------------
 *         Public functions
 *------------------------------------------------------------------------------*/

static struct _twi_slave_ops _at24_emulator_ops = {
	.on_start = _at24_emulator_on_start,
	.on_stop = NULL,
	.on_read = _at24_emulator_on_read,
	.on_write = _at24_emulator_on_write,
};

void at24_emulator_initialize(struct _twi_slave_desc* desc)
{
	/* Setup slave driver structure */
	memset(_at24_emulator.data, 0xff, ARRAY_SIZE(_at24_emulator.data));
	_at24_emulator.offset = 0;
	_at24_emulator.state = TWI_EEPROM_OFFSET;

	twid_slave_configure(desc, &_at24_emulator_ops);
}
