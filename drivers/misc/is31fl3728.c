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

/**
  * \file
  *
  * Implementation driver: IS31FL3728 AUDIO MODULATED MATRIX LED DRIVER.
  *
  */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "peripherals/pio.h"
#include "peripherals/twi.h"
#include "peripherals/twid.h"

#include "timer.h"

#include "is31fl3728.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>


/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief  Write one byte of data to QT1070 Register.
 *
 * \param IS31FL3728 Pointer to the driver structure.
 * \param reg_addr Register address to write.
 * \param data    Data to write.
 */
static void _is31fl3728_write_reg(struct _is31fl3728* is31fl3728, uint8_t iaddr, uint8_t data)
{
	struct _buffer out = {
		.data = &data,
		.size = 1,
		.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE | TWID_BUF_ATTR_STOP,
	};
	is31fl3728->twid->slave_addr = is31fl3728->addr;
	is31fl3728->twid->iaddr = iaddr;
	is31fl3728->twid->isize = 1;
	twid_transfer(is31fl3728->twid, &out, 1, NULL, NULL);
	twid_wait_transfer(is31fl3728->twid);
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void is31fl3728_fb_set(struct _is31fl3728 *is31fl3728, uint8_t x, uint8_t y)
{
	if (x < is31fl3728->desc.matrix.cols && y < is31fl3728->desc.matrix.rows)
		is31fl3728->fb[x] |= (1 << y);
}

void is31fl3728_fb_reset(struct _is31fl3728 *is31fl3728, uint8_t value)
{
	uint8_t i;

	for (i = 0 ; i < is31fl3728->desc.matrix.cols ; i++)
		if (!!value)
			is31fl3728->fb[i] = 0xff; // 0 = LED ON
		else
			is31fl3728->fb[i] = 0x00; // 0 = LED OFF
}

void is31fl3728_refresh(struct _is31fl3728 *is31fl3728)
{
	uint8_t i, reg;

	reg = IS31FL3728_REG_COLUMN_DATA1;
	for (i = 0 ; i < is31fl3728->desc.matrix.cols ; i++) {
		_is31fl3728_write_reg(is31fl3728, reg + i, is31fl3728->fb[i]);
	}
	/* Dumy write operation to the Update Column Register is required
	 * to update the Column Data Registers
	 */
	_is31fl3728_write_reg(is31fl3728, IS31FL3728_REG_UPDATE_COLUMN, 0xFF);
}


uint8_t is31fl3728_configure(struct _is31fl3728 *is31fl3728, struct _twi_desc *twid, uint8_t addr, uint8_t *fb)
{
	uint8_t status = TWID_SUCCESS;

	is31fl3728->twid = twid;
	is31fl3728->addr = addr;
	twid_configure(is31fl3728->twid);
	is31fl3728->fb = fb;

	_is31fl3728_write_reg(is31fl3728, IS31FL3728_REG_CONFIGURATION, is31fl3728->settings.config);
	is31fl3728_fb_reset(is31fl3728, 0);
	is31fl3728_refresh(is31fl3728);

	return status;
}
