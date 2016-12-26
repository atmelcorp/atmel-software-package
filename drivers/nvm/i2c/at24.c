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
#include "timer.h"
#include "intmath.h"
#include "trace.h"

#include "i2c/twi-bus.h"

#include "mm/cache.h"

#include "nvm/i2c/at24.h"

#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *         Local definitions
 *----------------------------------------------------------------------------*/

#define AT24_EEPROM_ADDR        0x50 /*< AT24 EEPROM I2C address */

#define AT24_SERIAL_ADDR_OFFSET 8    /*< Offset between EEPROM and serial I2C addresses */
#define AT24_SERIAL_OFFSET      0x80 /*< Read offset for serial number */
#define AT24_SERIAL_LENGTH      16   /*< Length of serial number data in bytes */

#define AT24_EUI48_ADDR_OFFSET  8    /*< Offset between EEPROM and EUI48 I2C addresses */
#define AT24_EUI48_OFFSET       0x9a /*< Read offset for EUI48 */
#define AT24_EUI48_LENGTH       6    /*< Length of EUI48 data in bytes */

#define AT24_EUI64_ADDR_OFFSET  8    /*< Offset between EEPROM and EUI64 I2C addresses */
#define AT24_EUI64_OFFSET       0x98 /*< Read offset for EUI64 */
#define AT24_EUI64_LENGTH       8    /*< Length of EUI64 data in bytes */

/*------------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

static const struct _at24_desc _at24_devices[] = {
	{ AT24C01,    "AT24C01",    AT24C,     7,   8, },
	{ AT24C02,    "AT24C02",    AT24C,     8,   8, },
	{ AT24C04,    "AT24C04",    AT24C,     9,   8, },
	{ AT24C08,    "AT24C08",    AT24C,    10,   8, },
	{ AT24C16,    "AT24C16",    AT24C,    11,  16, },
	{ AT24C32,    "AT24C32",    AT24C,    12,  32, },
	{ AT24C64,    "AT24C64",    AT24C,    13,  32, },
	{ AT24C128,   "AT24C128",   AT24C,    14,  64, },
	{ AT24C256,   "AT24C256",   AT24C,    15,  64, },
	{ AT24C512,   "AT24C512",   AT24C,    16, 128, },
	{ AT24C1024,  "AT24C1024",  AT24C,    17, 256, },
	{ AT24CM01,   "AT24CM01",   AT24C,    17, 256, },
	{ AT24CM02,   "AT24CM02",   AT24C,    18, 256, },
	{ AT24CS01,   "AT24CS01",   AT24CS,    7,   8, },
	{ AT24CS02,   "AT24CS02",   AT24CS,    8,   8, },
	{ AT24CS04,   "AT24CS04",   AT24CS,    9,  16, },
	{ AT24CS08,   "AT24CS08",   AT24CS,   10,  16, },
	{ AT24MAC402, "AT24MAC402", AT24MAC4,  8,  16, },
	{ AT24MAC602, "AT24MAC602", AT24MAC6,  8,  16, },
};

/*------------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

CACHE_ALIGNED static uint8_t _at24_buffer[16];

/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static int _at24_compute_address_field(const struct _at24* at24, uint8_t *addr_buf, uint32_t mem_offset, uint8_t *addr_offset)
{
	if (at24->desc->size == 18) {
		*addr_offset = (mem_offset >> 16) & 3;
	} else if (at24->desc->size == 17) {
		*addr_offset = (mem_offset >> 16) & 1;
	} else {
		*addr_offset = 0;
	}

	if (at24->desc->size <= 8) {
		addr_buf[0] = mem_offset & 0xff;
		return 1;
	} else {
		addr_buf[0] = mem_offset >> 8;
		addr_buf[1] = mem_offset & 0xff;
		return 2;
	}
}

static bool _at24_twi_read(const struct _at24* at24, uint8_t addr_offset, struct _buffer *buf)
{
	uint8_t status;

	/* start a TWI bus transaction */
	while (twi_bus_transaction_pending(at24->bus));
	twi_bus_start_transaction(at24->bus);

	/* start the TWI bus transfer */
	status = twi_bus_transfer(at24->bus, at24->addr + addr_offset, buf, 2, NULL);

	/* wait for completion and stop transaction */
	twi_bus_wait_transfer(at24->bus);
	twi_bus_stop_transaction(at24->bus);

	return !status;
}

//------------------------------------------------------------------------------
///        Exported functions
//------------------------------------------------------------------------------

bool at24_configure(struct _at24* at24, const struct _at24_config* cfg)
{
	int i;
	const struct _at24_desc *desc;
	uint8_t addr_mask;

	assert(at24);
	assert(cfg);

	for (i = 0, desc = NULL; i < ARRAY_SIZE(_at24_devices); i++) {
		if (_at24_devices[i].model == cfg->model) {
			desc = &_at24_devices[i];
			break;
		}
	}
	if (!desc) {
		trace_error("at24: unknown model %u\r\n", cfg->model);
		return false;
	}

	if (at24->desc->size == 18) {
		addr_mask = ~4; /* A2 */
	} else if (at24->desc->size == 17) {
		addr_mask = ~6; /* A2 A1 */
	} else {
		addr_mask = ~7; /* A2 A1 A0 */
	}
	if ((cfg->addr & addr_mask) != AT24_EEPROM_ADDR) {
		trace_error("at24: invalid TWI address %u\r\n", cfg->addr);
		return false;
	}

	at24->bus = cfg->bus;
	at24->addr = cfg->addr;
	at24->desc = desc;
	return true;
}

bool at24_read(const struct _at24* at24, uint32_t offset, uint8_t* data, uint16_t length)
{
	uint8_t addr_offset, addr_buf[2];
	struct _buffer buf[2] = {
		{
			.data = addr_buf,
			/* .size */
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			.data = data,
			.size = length,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_READ | TWID_BUF_ATTR_STOP,
		},
	};

	/* prepare TWI bus buffers */
	buf[0].size = _at24_compute_address_field(at24, addr_buf, offset, &addr_offset);

	/* read data */
	return _at24_twi_read(at24, addr_offset, buf);
}

bool at24_write(const struct _at24* at24, uint32_t offset, const uint8_t* data, uint16_t length)
{
	const uint8_t page_size = at24->desc->page_size;
	uint8_t addr_offset, addr_buf[2];
	struct _buffer buf[2] = {
		{
			.data = addr_buf,
			/* .size */
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			/* .data */
			/* .size */
			.attr = TWID_BUF_ATTR_WRITE | TWID_BUF_ATTR_STOP,
		},
	};
	uint8_t status, chunk_size;

	/* start a TWI bus transaction */
	while (twi_bus_transaction_pending(at24->bus));
	twi_bus_start_transaction(at24->bus);

	while (length) {
		/* compute chunk size (aligned to write page size) */
		chunk_size = min_u32(length, page_size - (offset % page_size));

		/* prepare TWI bus buffers */
		buf[0].size = _at24_compute_address_field(at24, addr_buf, offset, &addr_offset);
		buf[1].data = (uint8_t*)data;
		buf[1].size = chunk_size;

		/* start the TWI bus transfer */
		status = twi_bus_transfer(at24->bus, at24->addr + addr_offset, buf, 2, NULL);
		if (status)
			break;

		/* wait for completion */
		twi_bus_wait_transfer(at24->bus);

		/* update position & remaining data length */
		offset += chunk_size;
		data += chunk_size;
		length -= chunk_size;

		/* wait 10 ms for write cycle to complete */
		msleep(10);
	};

	/* stop transaction */
	twi_bus_stop_transaction(at24->bus);

	return !status;
}

bool at24_has_serial(const struct _at24* at24)
{
	return at24->desc->family == AT24CS ||
	       at24->desc->family == AT24MAC4 ||
	       at24->desc->family == AT24MAC6;
}

bool at24_read_serial(const struct _at24* at24, uint8_t* serial)
{
	uint8_t offset = AT24_SERIAL_OFFSET;
	struct _buffer buf[2] = {
		{
			.data = &offset,
			.size = 1,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			.data = _at24_buffer,
			.size = AT24_SERIAL_LENGTH,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_READ | TWID_BUF_ATTR_STOP,
		},
	};

	assert(sizeof(_at24_buffer) >= AT24_SERIAL_LENGTH);

	if (!at24_has_serial(at24)) {
		trace_warning("at24: device has no serial number\r\n");
		return false;
	}

	if (_at24_twi_read(at24, AT24_SERIAL_ADDR_OFFSET, buf)) {
		/* copy serial number to user buffer */
		memcpy(serial, _at24_buffer, AT24_SERIAL_LENGTH);
		return true;
	}

	return false;
}

bool at24_has_eui48(const struct _at24* at24)
{
	return at24->desc->family == AT24MAC4;
}

bool at24_read_eui48(const struct _at24* at24, uint8_t* eui48)
{
	uint8_t offset = AT24_EUI48_OFFSET;
	struct _buffer buf[2] = {
		{
			.data = &offset,
			.size = 1,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			.data = _at24_buffer,
			.size = AT24_EUI48_LENGTH,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_READ | TWID_BUF_ATTR_STOP,
		},
	};

	assert(sizeof(_at24_buffer) >= AT24_EUI48_LENGTH);

	if (!at24_has_eui48(at24)) {
		trace_warning("at24: device has no EUI48\r\n");
		return false;
	}

	if (_at24_twi_read(at24, AT24_EUI48_ADDR_OFFSET, buf)) {
		/* copy EUI48 to user buffer */
		memcpy(eui48, _at24_buffer, AT24_EUI48_LENGTH);
		return true;
	}

	return false;
}

bool at24_has_eui64(const struct _at24* at24)
{
	return at24->desc->family == AT24MAC6;
}

bool at24_read_eui64(const struct _at24* at24, uint8_t* eui64)
{
	uint8_t offset = AT24_EUI64_OFFSET;
	struct _buffer buf[2] = {
		{
			.data = &offset,
			.size = 1,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_WRITE,
		},
		{
			.data = _at24_buffer,
			.size = AT24_EUI64_LENGTH,
			.attr = TWID_BUF_ATTR_START | TWID_BUF_ATTR_READ | TWID_BUF_ATTR_STOP,
		},
	};

	assert(sizeof(_at24_buffer) >= AT24_EUI64_LENGTH);

	if (!at24_has_eui64(at24)) {
		trace_warning("at24: device has no EUI64\r\n");
		return false;
	}

	if (_at24_twi_read(at24, AT24_EUI64_ADDR_OFFSET, buf)) {
		/* copy EUI64 to user buffer */
		memcpy(eui64, _at24_buffer, AT24_EUI64_LENGTH);
		return true;
	}

	return false;
}
