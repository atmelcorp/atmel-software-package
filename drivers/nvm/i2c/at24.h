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

#ifndef AT24_H_
#define AT24_H_

#ifdef CONFIG_DRV_AT24

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------
 *         Global definitions
 *----------------------------------------------------------------------------*/

#define AT24_SERIAL_LENGTH 16
#define EUI48_LENGTH  6
#define EUI64_LENGTH  8

enum _at24_model {
	AT24C01,
	AT24C02,
	AT24C04,
	AT24C08,
	AT24C16,
	AT24C32,
	AT24C64,
	AT24C128,
	AT24C256,
	AT24C512,
	AT24C1024,
	AT24CM01,
	AT24CM02,
	AT24CS01,
	AT24CS02,
	AT24CS04,
	AT24CS08,
	AT24MAC402,
	AT24MAC602,
	FM24V10,
	MCP24AA02E48,
	MCP24AA02E64,
	MCP24AA025E48,
	MCP24AA025E64,
};

enum _at24_family {
	AT24C,
	AT24CS,
	AT24MAC4,
	AT24MAC6,
	FM24V,
	MCP24AAE4,
	MCP24AAE6,
};

struct _at24_desc {
	uint8_t model;      /* from enum _at24_model */
	const char *name;   /* device name */
	uint8_t family;     /* from enum _at24_family */
	uint8_t size;       /* total size, in power-of-2 bytes (8 => 2**8 = 256 bytes) */
	uint16_t page_size; /* write page size, in bytes */
	struct {
		uint8_t addr_offset;
		uint8_t offset;
		uint8_t len;
	} eui;
};

struct _at24_config {
	uint8_t bus;
	uint8_t addr;
	enum _at24_model model;
};

struct _at24 {
	uint8_t bus;
	uint8_t addr;
	const struct _at24_desc *desc;
};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

extern int at24_configure(struct _at24* at24, const struct _at24_config* cfg);
extern int at24_read(const struct _at24* at24, uint32_t offset, uint8_t* data, uint16_t length);
extern int at24_write(const struct _at24* at24, uint32_t offset, const uint8_t* data, uint16_t length);
extern bool at24_has_serial(const struct _at24* at24);
extern bool at24_read_serial(const struct _at24* at24, uint8_t* serial);
extern bool at24_has_eui48(const struct _at24* at24);
extern bool at24_read_eui48(const struct _at24* at24, uint8_t* eui48);
extern bool at24_has_eui64(const struct _at24* at24);
extern bool at24_read_eui64(const struct _at24* at24, uint8_t* eui64);

#endif /* CONFIG_DRV_AT24 */

#endif /* AT24_H_ */
