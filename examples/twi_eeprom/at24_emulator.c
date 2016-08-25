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

#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/twid.h"
#include "bus/twi-bus.h"

#include "misc/cache.h"
#include "misc/console.h"

#include "at24_emulator.h"

#include <assert.h>
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
struct _slave_device_driver
{
	/** TWI slave address */
	uint8_t addr;
	/** TWI device */
	Twi* twi;
	/** Memory buffer */
	uint8_t data[TWI_SLAVE_SIZE];
	/** Offset of the memory access */
	uint16_t offset;
	/** Read address of the request */
	uint8_t state;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** instance of TWI slave device */
static struct _slave_device_driver at24_emulator;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Handler for TWI slave interrupt.
 *
 *  Handle process TWI master's requests.
 */
static void twi_slave_handler(void)
{
	uint32_t status;
	Twi *twi = at24_emulator.twi;

	status = twi_get_status(twi);

	if (TWI_STATUS_SVACC(status)) {
		/* Write to slave */
		if (TWI_STATUS_RXRDY(status)) {
			uint8_t data = twi_read_byte(twi);

			switch (at24_emulator.state) {
			case TWI_EEPROM_OFFSET:
				/* Acquire address */
				at24_emulator.offset = data;
				at24_emulator.state = TWI_EEPROM_DATA;
				break;
			case TWI_EEPROM_DATA:
				/* Read one byte of data from master to slave device */
				at24_emulator.data[at24_emulator.offset] = data;
				at24_emulator.offset = (at24_emulator.offset + 1) % TWI_SLAVE_SIZE;
				break;
			}
		} else if (TWI_STATUS_SVREAD(status)) {
			/* Read from slave */
			if (TWI_STATUS_TXRDY(status)) {
				/* Write one byte of data from slave to master device */
				twi_write_byte(twi, at24_emulator.data[at24_emulator.offset]);
				at24_emulator.offset = (at24_emulator.offset + 1) % TWI_SLAVE_SIZE;
				twi_enable_it(twi, TWI_IER_TXCOMP);
			}
		}
		twi_enable_it(twi, TWI_IER_EOSACC);
	} else {
		if (TWI_STATUS_EOSACC(status) && TWI_STATUS_TXCOMP(status)) {
			at24_emulator.state = TWI_EEPROM_OFFSET;
			twi_disable_it(twi, TWI_IDR_EOSACC | TWI_IDR_TXCOMP);

			/* At the end of a read from the slave, we need to
			 * clear an additionnal byte that may be pending in
			 * TWI_THR register. */
#ifdef TWI_CR_THRCLR
			/* On SAMA5D2, writing TWI_CR_THRCLR to TWI_CR will
			 * clear TWI_THR. */
			twi->TWI_CR = TWI_CR_THRCLR;
#else
			/* On older versions of the TWI peripheral, we have to
			 * trigger a software reset... */
			twi_configure_slave(twi, at24_emulator.addr);
			twi_enable_it(twi, TWI_IER_SVACC | TWI_IER_RXRDY);
#endif
		}
	}
}

/*------------------------------------------------------------------------------
k *         Public functions
 *------------------------------------------------------------------------------*/

void at24_emulator_initialize(Twi* twi, uint8_t addr)
{
	uint32_t twi_id;

	/* Setup slave driver structure */
	memset(at24_emulator.data, 0xff, ARRAY_SIZE(at24_emulator.data));
	at24_emulator.addr = addr;
	at24_emulator.twi = twi;
	at24_emulator.offset = 0;
	at24_emulator.state = TWI_EEPROM_OFFSET;

	/* Configure TWI slave */
	twi_id = get_twi_id_from_addr(twi);
	pmc_enable_peripheral(twi_id);
	twi_configure_slave(twi, addr);
	aic_set_source_vector(twi_id, twi_slave_handler);
	twi_enable_it(twi, TWI_IER_SVACC | TWI_IER_RXRDY);
	aic_enable(twi_id);
}
