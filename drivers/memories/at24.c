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

#include "board.h"
#include "chip.h"

#include "peripherals/pio.h"
#include "peripherals/pmc.h"

#include "peripherals/twi.h"
#include "peripherals/twid2.h"

#include "memories/at24.h"

#include "trace.h"
#include "crc.h"
#include "timer.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static uint32_t _at24_read(struct _at24* at24, uint8_t* buffer, uint32_t len)
{
	struct _buffer in = {
		.data = buffer,
		.size = len
	};
	return twid_transfert(at24->twid, &in, 0,
			      twid_finish_transfert_callback, 0);
}

static uint32_t _at24_write(struct _at24* at24, const uint8_t* buffer,
			    uint32_t len)
{
	struct _buffer out = {
		.data = (uint8_t*)buffer,
		.size = len
	};
	return twid_transfert(at24->twid, 0, &out,
			      twid_finish_transfert_callback, 0);
}

//------------------------------------------------------------------------------
///        Exported functions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Function to read the Serial Number from a AT24MAC402 EEPROM
//
// add: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
// pSerNumbr: a pointer to 0x0F bytes of memory
//
uint8_t at24_get_serial_number(struct _at24* at24)
{
	uint8_t status = TWID_SUCCESS;
	uint8_t dummy = 0x0;

	at24->twid->slave_addr = AT24_SN_ADDR;
	at24->twid->iaddr = AT24_SN_INT_ADDR;
	at24->twid->isize = 1;

	// Tell the EEPROM where we would like to read from
	status = _at24_read(at24, &dummy, 1); // Location of the serial number
	if (status) {
		return status;
	}

	at24->twid->iaddr = 0;
	at24->twid->isize = 0;

	/* // Now read bytes from that memory address */
	return _at24_read(at24, at24->serial_number,
			  sizeof(at24->serial_number));
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Function to read the MAC address from a AT24MAC402 EEPROM
//
// add: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
// pMacAddr: a pointer to 6 bytes of memory
//
uint8_t at24_get_mac_address(struct _at24* at24)
{
	uint8_t status = TWID_SUCCESS;
	uint8_t dummy = 0x0;

	at24->twid->slave_addr = AT24_SN_ADDR;
	at24->twid->iaddr = AT24_EUI48_VALUE_ADDR;
	at24->twid->isize = 1;

	// Tell the EEPROM where we would like to read from
	status = _at24_read(at24, &dummy, 1); // Location of the EUI-48
	if (status) {
		return status;
	}

	at24->twid->iaddr = 0;
	at24->twid->isize = 0;

	return _at24_read(at24, at24->mac_addr_48,
			  sizeof(at24->mac_addr_48));
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Function to read the AT24MAC402 EEPROM
//
// BitA0ToA2: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
// add: add to the data
// Len: data to be read
// pDataBuf: a pointer to memory buffer
//
uint8_t at24_read_eep(struct _at24* at24, uint8_t addr,
		      uint8_t* data, uint8_t length)
{
	uint8_t status = TWID_SUCCESS;
	uint8_t dummy = 0xDE;

	at24->twid->slave_addr = AT24_EEP_ADDR;
	at24->twid->iaddr = addr;
	at24->twid->isize = 1;

	// Tell the EEPROM where we would like to read from
	status = _at24_read(at24, &dummy, 1);
	if (status) {
		return status;
	}

	return _at24_read(at24, data, length);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Function to write to the AT24MAC402 EEPROM
//
// BitA0ToA2: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
// add: add to the data
// Len: data to be read
// pDataBuf: a pointer to data to write in EEP
//
uint8_t at24_write_eep(struct _at24* at24, uint8_t addr,
		       const uint8_t* data, uint8_t length)
{
	uint8_t status = TWID_SUCCESS;
	uint8_t dummy = 0xDE;

	at24->twid->slave_addr = AT24_EEP_ADDR;
	at24->twid->iaddr = addr;
	at24->twid->isize = 1;

	// Tell the EEPROM where we would like to read from
	status = _at24_read(at24, &dummy, 1);
	if (status) {
		return status;
	}

	do {
		status |= _at24_write(at24, data++, 1);
		at24->twid->iaddr++;
		// Wait at least 10 ms
		timer_sleep(10);
	} while (--length);

	return status;
}

/* //------------------------------------------------------------------------------ */
/* //------------------------------------------------------------------------------ */

/* uint8_t at24mac402_get_info_board (struct _at24mac402_board_info* pInfo_board) */
/* { */
/* 	uint8_t Status = TWI_SUCCES; */
/* 	uint8_t crc = 0; */

/* 	Status = at24mac402_read_eep (AT24MAC402_INFO_ADD, AT24MAC402_INFO_SIZE, (uint8_t*)pInfo_board); */
/* 	if(Status != TWI_SUCCES) return Status; */
/* 	crc = compute_crc8 ((uint8_t*)pInfo_board, AT24MAC402_INFO_SIZE-1); */
/* 	return (crc==pInfo_board->crc) ? 0: 1; */
/* } */

/* //------------------------------------------------------------------------------ */
/* //------------------------------------------------------------------------------ */
/* uint8_t at24mac402_set_info_board (struct _at24mac402_board_info* pInfo_board) */
/* { */
/* 	uint8_t Status = TWI_SUCCES; */

/* 	pInfo_board->crc_sn = compute_crc8 ((uint8_t*)SerNumbr, AT24MAC402_SER_NUM_SIZE); */
/* 	pInfo_board->crc = compute_crc8 ((uint8_t*)pInfo_board, AT24MAC402_INFO_SIZE-1); */
/* 	Status = at24mac402_write_eep (AT24MAC402_INFO_ADD, AT24MAC402_INFO_SIZE, (uint8_t*)pInfo_board); */
/* 	return Status; */
/* } */

/* //------------------------------------------------------------------------------ */
/* //------------------------------------------------------------------------------ */

/* void _reset_buftwi (void) */
/* { */
/* 	memset(buf_twi, 0x00, sizeof(buf_twi)); */
/* } */

/* void at24mac402_display_info_board (struct _at24mac402_board_info* pInfo_board) */
/* { */
/* 	printf("\tInfo Size   : %02d\n\r", pInfo_board->page_size); */
/* 	_reset_buftwi(); */
/* 	memcpy(buf_twi, (char*)pInfo_board->manufacturer, SIZE_SUBC); */
/* 	printf("\tManufacturer: %s\n\r", buf_twi); */
/* 	_reset_buftwi(); */
/* 	memcpy(buf_twi, (char*)pInfo_board->country, SIZE_MANUF_COUNTRY); */
/* 	printf("\tMade in     : %s\n\r", buf_twi); */
/* 	printf("\tManuf year  : %d\n\r", pInfo_board->manuf_year+2000); */
/* 	printf("\tWeek        : %02d\n\r", pInfo_board->manuf_week); */
/* 	_reset_buftwi(); */
/* 	memcpy(buf_twi, (char*)pInfo_board->rev_code, SIZE_HW_REVISION); */
/* 	printf("\tRevision    : %s\n\r", buf_twi); */
/* 	printf("\tCrcSN       : Ox%02X\n\r", pInfo_board->crc_sn); */
/* 	printf("\tExtended add: 0x%04X\n\r", pInfo_board->addr_ext_config); */
/* 	_reset_buftwi(); */
/* 	memcpy(buf_twi, (char*)pInfo_board->board_ident, SIZE_BOARD_IDENT); */
/* 	printf("\tBoard       : %s\n\r", buf_twi); */
/* 	printf("\tMapping     : %c\n\r", pInfo_board->rev_mapping); */
/* 	printf("\tCrc         : 0x%02X\n\r", pInfo_board->crc); */
/* } */

/* //------------------------------------------------------------------------------ */
/* //------------------------------------------------------------------------------ */
/* void at24mac402_display_register (void) */
/* { */
/* 	uint8_t Len, Status = TWI_SUCCES; */
/* 	struct _at24mac402_board_info sInfo = {0}; */

/* 	// Display Serial Number */
/* 	printf(" -I- Serial Number: "); */
/* 	for (Len=0; Len<AT24MAC402_SER_NUM_SIZE; Len++) { */
/* 		printf("%02X", SerNumbr[Len]); */
/* 	} */
/* 	printf("\n\r"); */
/* 	// Display Mac address */
/* 	printf(" -I- Mac add EUI48 "); */
/* 	for (Len=0; Len<AT24MAC402_EUI48_SIZE; Len++) { */
/* 		printf(":%02X", MacAddr48[Len]); */
/* 	} */
/* 	printf("\n\r"); */
/* 	// Check Info board */
/* 	Status = at24mac402_get_info_board (&sInfo); */
/* 	if (Status) { */
/* 		memcpy (&buf_twi, &DEFAULT_BOARD_INFO, sizeof(struct _at24mac402_board_info)); */
/* 		Status = at24mac402_set_info_board ((struct _at24mac402_board_info*)&buf_twi); */
/* 		Status = at24mac402_get_info_board (&sInfo); */
/* 	} */
/* 	printf(" -I- Manufacturing info\n\r"); */
/* 	at24mac402_display_info_board(&sInfo); */
/* } */

/* //------------------------------------------------------------------------------ */
/* //------------------------------------------------------------------------------ */

uint8_t at24_configure(struct _at24* at24, struct _twi_desc* twid)
{
	uint8_t status = TWID_SUCCESS;

	at24->twid = twid;
	twid_configure(twid);

	// Read serial number
	status |= at24_get_serial_number(at24);

	twid_wait_transfert(at24->twid);
	// Get EUI-48 mac address
	status |= at24_get_mac_address(at24);
	return status;
}

/* //------------------------------------------------------------------------------ */
/* //------------------------------------------------------------------------------ */

/* uint8_t at24mac402_test (void) */
/* { */
/* 	uint8_t Len, Status = TWI_SUCCES; */
/* 	uint8_t Pattern[2] = {0xA5, 0x5A}; */

/* 	Status = at24mac402_begin(); */
/* 	if (Status) return Status = TWI_FAIL; */

/* 	//\** start test */
/* 	// Erase */
/* 	memset (buf_twi, 0x00, AT24MAC402_PAGE_SIZE); */
/* 	Status = at24mac402_write_eep (AT24MAC402_FIRST_MEM_ADD, AT24MAC402_BLOCK_SIZE, buf_twi); */
/* 	// Write pattern */
/* 	for(Len=0; Len<(AT24MAC402_BLOCK_SIZE); Len+=2) { */
/* 		buf_twi[Len+0] = Pattern[0]; */
/* 		buf_twi[Len+1] = Pattern[1]; */
/* 	} */
/* 	Status = at24mac402_write_eep (AT24MAC402_FIRST_MEM_ADD, AT24MAC402_BLOCK_SIZE, buf_twi); */
/* 	// Read back */
/* 	memset (buf_twi, 0x00, AT24MAC402_BLOCK_SIZE); */
/* 	Status = at24mac402_read_eep (AT24MAC402_FIRST_MEM_ADD, AT24MAC402_BLOCK_SIZE, buf_twi); */
/* 	// Compare */
/* 	Status = TWI_SUCCES; */
/* 	printf("-T- "); */
/* 	for(Len=0; Len<AT24MAC402_BLOCK_SIZE; Len+=2) { */
/* 		printf("%s", buf_twi[Len]!=Pattern[0] ? "!": "." ); */
/* 		printf("%s", buf_twi[Len+1]!=Pattern[1] ? "!": "." ); */
/* 		if( buf_twi[Len]!=Pattern[0] || buf_twi[Len+1]!=Pattern[1] ) {Status++;} */
/* 	} */
/* 	printf("\n\r"); */
/* 	return Status; */
/* } */

/* //------------------------------------------------------------------------------ */
/* //------------------------------------------------------------------------------ */
/* //------------------------------------------------------------------------------ */
/* //End of file */
