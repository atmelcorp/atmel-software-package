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

#ifndef AT24MAC402_H
#define AT24MAC402_H

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include "peripherals/twid.h"
#include "mutex.h"

/*----------------------------------------------------------------------------
 *         Global definitions
 *----------------------------------------------------------------------------*/



/** Internal Register Address Allocation */
#define AT24_FIRST_MEM_ADDR     0x00
#define AT24_SECOND_MEM_ADDR    0x80
#define AT24_EUI64_VALUE_ADDR   0x98        // 0x98-0x9F
#define AT24_DUMMY_ADDR         0x00

#define AT24_NUM_PAGE           2
#define AT24_PAGE_SIZE          128
#define AT24_BLOCK_SIZE         16
#define AT24_NUM_BLOCK          (AT24_PAGE_SIZE / AT24_BLOCK_SIZE)
#define AT24_MEM_SIZE           (AT24_PAGE_SIZE * AT24_NUM_PAGE)

#define AT24_SN_SIZE            ((0x8F-0x80)+1)
#define AT24_EUI48_SIZE         ((0x9F-0x9A)+1)
#define AT24_EUI64_SIZE         ((0x9F-0x98)+1)

#define AT24_INFO_ADDR          (AT24_SECOND_MEM_ADDR + \
				 ((AT24_NUM_BLOCK-2)* AT24_BLOCK_SIZE))
#define AT24_INFO_SIZE          (AT24_BLOCK_SIZE*2)

struct _at24_desc {
	const char* name;
	uint8_t     size;
	uint8_t     page_size;
};

struct _at24 {
	struct _twi_desc* twid;
	struct _at24_desc desc;

	uint8_t addr;
	uint8_t sn_addr;
	uint8_t sn_offset;
	uint8_t eui_offset;

	uint8_t serial_number[AT24_SN_SIZE];
	uint8_t mac_addr_48[AT24_EUI48_SIZE];

	mutex_t mutex;
};

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

extern uint8_t at24_get_serial_number(struct _at24* at24);
extern uint8_t at24_get_mac_address(struct _at24* at24);
extern uint8_t at24_read_eep(struct _at24* at24, uint8_t addr,
			     uint8_t* data, uint8_t length);
extern uint8_t at24_write_eep(struct _at24* at24, uint8_t addr,
			      const uint8_t* data, uint8_t length);
extern uint8_t at24_configure(struct _at24* at24, struct _twi_desc* twid);

#endif //#ifndef AT24MAC402_H
