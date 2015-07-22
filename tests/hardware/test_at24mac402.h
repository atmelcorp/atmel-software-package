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

#ifndef TEST_AT24MAC402_H
#define TEST_AT24MAC402_H

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include <stdint.h>

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

#define SIZE_SUBC 6
#define SIZE_MANUF_COUNTRY 3
#define SIZE_BOARD_IDENT 12
#define SIZE_HW_REVISION 3

struct _board_info {
    uint8_t page_size;
    uint8_t manufacturer[SIZE_SUBC];
    uint8_t country[SIZE_MANUF_COUNTRY];
    uint8_t manuf_year;
    uint8_t manuf_week;
	uint8_t rev_code[SIZE_HW_REVISION];
	uint8_t crc_sn;
	uint16_t addr_ext_config;
    uint8_t board_ident[SIZE_BOARD_IDENT];
    uint8_t rev_mapping;
    uint8_t crc;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

extern uint8_t at24mac402_display_serial_number (struct _at24* pAt24);
extern uint8_t at24mac402_display_mac_adress (struct _at24* pAt24);
extern uint8_t at24mac402_get_info_board (struct _at24* pAt24, struct _board_info* pInfo);
extern uint8_t at24mac402_set_info_board (struct _at24* pAt24, struct _board_info* pInfo);
extern uint8_t at24mac402_display_info_board (struct _at24* pAt24);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif //#ifndef TEST_AT24MAC402_H