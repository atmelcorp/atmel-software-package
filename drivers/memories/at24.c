/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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
#include "crc.h"
#include "intmath.h"
#include "timer.h"
#include "trace.h"

#include "memories/at24.h"

#include "misc/cache.h"

#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "bus/twi-bus.h"
#include "peripherals/twid.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/*------------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

/** Temporary buffer used by at24_get_serial_number and at24_get_mac_address */
CACHE_ALIGNED static uint8_t at24_buffer[16];

/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static void at24_callback(void* arg)
{
	struct _at24 *at24 = (struct _at24 *)arg;
	
	if (at24)
		mutex_unlock(&at24->mutex);
}

//------------------------------------------------------------------------------
///        Exported functions
//------------------------------------------------------------------------------

/* Function to read the Serial Number from a AT24MAC402 EEPROM
 *
 * add: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
 * pSerNumbr: a pointer to 0x0F bytes of memory
 */
uint8_t at24_get_serial_number(struct _at24* at24)
{
	uint8_t status = TWID_SUCCESS;
	struct _buffer buf[2] = {
		{
			.data = &at24->sn_offset,
			.size = 1,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			.data = at24_buffer,
			.size = sizeof(at24->serial_number),
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_READ | TWID_BUF_ATTR_STOP,
		},
	};
	
	assert(sizeof(at24->serial_number) <= sizeof(at24_buffer));

	if (!mutex_try_lock(&at24->mutex))
		return TWID_ERROR_LOCK;

	while (twi_bus_transaction_pending(at24->bus));
	twi_bus_start_transaction(at24->bus);

	// Tell the EEPROM where we would like to read from
	status = twi_bus_transfer(at24->bus, at24->sn_addr, buf, 2, at24_callback, (void *)at24);
	if (status) {
		mutex_unlock(&at24->mutex);
		twi_bus_stop_transaction(at24->bus);
		return status;
	}

	while (twi_bus_is_busy(at24->bus));
	twi_bus_stop_transaction(at24->bus);

	while (mutex_is_locked(&at24->mutex));

	memcpy(at24->serial_number, at24_buffer, sizeof(at24->serial_number));

	return status;
}


/* Function to read the MAC address from a AT24MAC402 EEPROM
 *
 * add: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
 * pMacAddr: a pointer to 6 bytes of memory
 */
uint8_t at24_get_mac_address(struct _at24* at24)
{
	uint8_t status = TWID_SUCCESS;
	struct _buffer buf[2] = {
		{
			.data = &at24->eui_offset,
			.size = 1,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			.data = at24_buffer,
			.size = sizeof(at24->mac_addr_48),
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_READ | TWID_BUF_ATTR_STOP,
		},
	};

	assert(sizeof(at24->mac_addr_48) <= sizeof(at24_buffer));

	if (!mutex_try_lock(&at24->mutex))
		return TWID_ERROR_LOCK;

	while (twi_bus_transaction_pending(at24->bus));
	twi_bus_start_transaction(at24->bus);

	// Tell the EEPROM where we would like to read from
	status = twi_bus_transfer(at24->bus, at24->sn_addr, buf, 2, at24_callback, (void *)at24); // Location of the serial number
	if (status) {
		mutex_unlock(&at24->mutex);
		twi_bus_stop_transaction(at24->bus);
		return status;
	}
	while (twi_bus_is_busy(at24->bus));
	twi_bus_stop_transaction(at24->bus);

	while (mutex_is_locked(&at24->mutex));

	memcpy(at24->mac_addr_48, at24_buffer, sizeof(at24->mac_addr_48));


	return status;
}

/* Function to read the AT24MAC402 EEPROM
 *
 * BitA0ToA2: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
 * add: add to the data
 * Len: data to be read
 * pDataBuf: a pointer to memory buffer
 */
uint8_t at24_read_eep(struct _at24* at24, uint8_t addr, uint8_t* data, uint16_t length)
{
	uint8_t status = TWID_SUCCESS;
	struct _buffer buf[2] = {
		{
			.data = &addr,
			.size = 1,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			.data = data,
			.size = length,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_READ | TWID_BUF_ATTR_STOP,
		},
	};

	// Tell the EEPROM where we would like to read from
	if (!mutex_try_lock(&at24->mutex))
		return TWID_ERROR_LOCK;

	while (twi_bus_transaction_pending(at24->bus));
	twi_bus_start_transaction(at24->bus);

	// Tell the EEPROM where we would like to read from
	status = twi_bus_transfer(at24->bus, at24->addr, buf, 2, at24_callback, (void *)at24);
	if (status) {
		mutex_unlock(&at24->mutex);
		twi_bus_stop_transaction(at24->bus);
		return status;
	}
	while (twi_bus_is_busy(at24->bus));
	twi_bus_stop_transaction(at24->bus);

	while (mutex_is_locked(&at24->mutex));

	return status;
}

/* Function to write to the AT24MAC402 EEPROM
 *
 * BitA0ToA2: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
 * addr: offset of data in the EEPROM
 * length: Length of data to be read
 * data: a pointer to data to write in EEP
 */
uint8_t at24_write_eep(struct _at24* at24, uint8_t addr, const uint8_t* data, uint16_t length)
{
	uint8_t status = TWID_SUCCESS;
	uint8_t page_size = at24->desc.page_size;
	struct _buffer buf[2] = {
		{
			/* .data = addr; */
			.size = 1,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			/* .data = data; */
			/* .size = write_size, */
			.attr = TWID_BUF_ATTR_WRITE | TWID_BUF_ATTR_STOP,
		},
	};
	
	if (!mutex_try_lock(&at24->mutex))
		return TWID_ERROR_LOCK;

	while (twi_bus_transaction_pending(at24->bus));
	twi_bus_start_transaction(at24->bus);

	while (length) {
		/* Compute number of bytes to program in page */
		uint8_t write_size;
		write_size = min_u32(length, page_size - (addr % page_size));
		buf[0].data = &addr;
		buf[1].data = (uint8_t *)data;
		buf[1].size = write_size;
		status = twi_bus_transfer(at24->bus, at24->addr, buf, 2, at24_callback, (void *)at24);
		if (status != TWID_SUCCESS) {
			twi_bus_stop_transaction(at24->bus);
			mutex_unlock(&at24->mutex);
			return status;
		}
		while (twi_bus_is_busy(at24->bus));
		length -= write_size;
		addr += write_size;
		data += write_size;
		timer_sleep(10); /* Wait at least 10 ms */
	};

	twi_bus_stop_transaction(at24->bus);

	while (mutex_is_locked(&at24->mutex));

	return status;
}

/* Function to configuer the twi AT24MAC402 EEPROM
 * Return status always SUCCES
 */
uint8_t at24_configure(struct _at24* at24)
{
	at24->mutex = 0;
	return TWID_SUCCESS;
}
