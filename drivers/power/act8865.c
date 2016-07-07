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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/twi.h"
#include "peripherals/twid.h"

#include "power/act8865.h"

#include "trace.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>


/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/
static bool _act8865_read_reg(struct _act8865* act8865, uint32_t iaddr,
		uint8_t* value)
{

	uint32_t status;
	struct _buffer in = {
		.data = value,
		.size = 1
	};

	act8865->twid->slave_addr = ACT8865_TWI_ADDRESS;
	act8865->twid->iaddr = iaddr;
	act8865->twid->isize = 1;

	status = twid_transfert(act8865->twid, &in, 0, NULL, 0);
	if (status != TWID_SUCCESS)
		return false;
	twid_wait_transfert(act8865->twid);
	return true;
}

static bool _act8865_write_reg(struct _act8865* act8865, uint32_t iaddr, uint8_t value)
{
	uint32_t status;
	struct _buffer out = {
		.data = (uint8_t*)&value,
		.size = 1
	};
	act8865->twid->slave_addr = ACT8865_TWI_ADDRESS;
	act8865->twid->iaddr = iaddr;
	act8865->twid->isize = 1;
	status = twid_transfert(act8865->twid, 0, &out, NULL, 0);
	if (status != TWID_SUCCESS)
		return false;
	twid_wait_transfert(act8865->twid);
	return true;
}

bool act8865_check_twi_status(struct _act8865* act8865)
{
	uint8_t data = 0;

	return _act8865_read_reg(act8865, SYS_0, &data);
}

bool act8865_set_reg_voltage(struct _act8865* act8865, uint8_t volt_reg, uint8_t value)
{
	uint8_t enable_reg;
	uint8_t data;
	bool ret;

	switch (volt_reg) {
	case REG1_0:
	case REG1_1:
		enable_reg = REG1_2;
		break;
	case REG2_0:
	case REG2_1:
		enable_reg = REG2_2;
		break;
	case REG3_0:
	case REG3_1:
		enable_reg = REG3_2;
		break;
	case REG4_0:
		enable_reg = REG4_1;
		break;
	case REG5_0:
		enable_reg = REG5_1;
		break;
	case REG6_0:
		enable_reg = REG6_1;
		break;
	case REG7_0:
		enable_reg = REG7_1;
		break;
	default:
		return false;
	}

	/* Set output voltage */
	ret = _act8865_write_reg(act8865, volt_reg, value);
	if (!ret)
		return false;

	/* Enable Regulator */
	data = 0;
	ret = _act8865_read_reg(act8865, enable_reg, &data);
	if (!ret)
		return false;

	data |= REG_ENABLE_BIT;
	ret = _act8865_write_reg(act8865, enable_reg, data);
	if (!ret)
		return false;

	return true;
}

