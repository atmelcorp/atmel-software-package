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
#include "peripherals/twi.h"
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

static void at24_free_mutex(struct _twi_desc* twi, void* arg)
{
	if (arg)
		mutex_unlock((mutex_t*)(arg));
}

static uint32_t _at24_read(struct _at24* at24, uint8_t* buffer, uint32_t len, mutex_t *mutex)
{
	struct _buffer in = {
		.data = buffer,
		.size = len
	};
	return twid_transfert(at24->twid, &in, NULL, at24_free_mutex, (void *)mutex);
}

static uint32_t _at24_write(struct _at24* at24, const uint8_t* buffer, uint32_t len, mutex_t *mutex)
{
	struct _buffer out = {
		.data = (uint8_t*)buffer,
		.size = len
	};
	return twid_transfert(at24->twid, NULL, &out, at24_free_mutex, (void *)mutex);
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
	uint8_t dummy = 0x0;

	assert(sizeof(at24->serial_number) <= sizeof(at24_buffer));

	at24->twid->slave_addr = at24->sn_addr;
	at24->twid->iaddr = at24->sn_offset;
	at24->twid->isize = 1;

	// Tell the EEPROM where we would like to read from
	if (!mutex_try_lock(&at24->mutex))
		return TWID_ERROR_LOCK;
	status = _at24_read(at24, &dummy, 1, NULL); // Location of the serial number
	if (status)
		return status;
	at24->twid->iaddr = 0;
	at24->twid->isize = 0;
	// Now read bytes from that memory address
	status = _at24_read(at24, at24_buffer, sizeof(at24->serial_number), &at24->mutex);
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
	uint8_t dummy = 0x0;

	assert(sizeof(at24->mac_addr_48) <= sizeof(at24_buffer));

	at24->twid->slave_addr = at24->sn_addr;
	at24->twid->iaddr = at24->eui_offset;
	at24->twid->isize = 1;

	if (!mutex_try_lock(&at24->mutex))
		return TWID_ERROR_LOCK;
	// Tell the EEPROM where we would like to read from
	status = _at24_read(at24, &dummy, 1, NULL); // Location of the EUI-48
	if (status)
		return status;
	at24->twid->iaddr = 0;
	at24->twid->isize = 0;
	status = _at24_read(at24, at24_buffer, sizeof(at24->mac_addr_48), &at24->mutex);
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
uint8_t at24_read_eep(struct _at24* at24, uint8_t addr,
		      uint8_t* data, uint8_t length)
{
	uint8_t status = TWID_SUCCESS;
	uint8_t dummy = 0xDE;

	at24->twid->slave_addr = at24->addr;
	at24->twid->iaddr = addr;
	at24->twid->isize = 1;

	// Tell the EEPROM where we would like to read from
	if (!mutex_try_lock(&at24->mutex))
		return TWID_ERROR_LOCK;
	status = _at24_read(at24, &dummy, 1, NULL);
	if (status)
		return status;
	status = _at24_read(at24, data, length, &at24->mutex);
	while (mutex_is_locked(&at24->mutex));
	return status;
}

/* Function to write to the AT24MAC402 EEPROM
 *
 * BitA0ToA2: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
 * add: add to the data
 * Len: data to be read
 * pDataBuf: a pointer to data to write in EEP
 */
uint8_t at24_write_eep(struct _at24* at24, uint8_t addr,
		       const uint8_t* data, uint8_t length)
{
	uint8_t status = TWID_SUCCESS;
	uint8_t dummy = 0xDE;
	uint8_t page_size = at24->desc.page_size;

	at24->twid->slave_addr = at24->addr;
	at24->twid->iaddr = addr;
	at24->twid->isize = 1;

	// Tell the EEPROM where we would like to read from
	if (!mutex_try_lock(&at24->mutex))
		return TWID_ERROR_LOCK;
	status = _at24_read(at24, &dummy, 1, NULL);
	if (status)
		return status;

	while (length) {
		/* Compute number of bytes to program in page */
		uint8_t write_size;
		write_size = min_u32(length, page_size - (addr % page_size));
		at24->twid->iaddr = addr;
		status |= _at24_write(at24, data, write_size, &at24->mutex);
		while (mutex_is_locked(&at24->mutex));
		length -= write_size;
		addr += write_size;
		data += write_size;
		timer_sleep(10); /* Wait at least 10 ms */
	};
	return status;
}

/* Function to configuer the twi AT24MAC402 EEPROM
 * Return status always SUCCES
 */
uint8_t at24_configure(struct _at24* at24, struct _twi_desc* twid)
{
	uint8_t status = TWID_SUCCESS;
	at24->twid = twid;
	twid_configure(twid);
	at24->mutex = 0;
	return status;
}
