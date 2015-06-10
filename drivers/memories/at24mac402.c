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
#include "peripherals/twid.h"

#include "at24mac402.h"

#include "trace.h"
#include "crc.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/*------------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

#define BitA0ToA2 0x04;

struct _handler_twi htwi_eep = {0};
uint8_t buf_twi[AT24MAC402_PAGE_SIZE] = {0};

// Using TWI1 IOS2
#define at24mac402_TWI_ID	ID_TWIHS1

static const struct _pin pins_twi_at24mac402[] = PINS_TWI1_IOS2;

uint8_t SerNumbr[AT24MAC402_SER_NUM_SIZE] = {0};
uint8_t MacAddr48[AT24MAC402_EUI48_SIZE] = {0};
uint8_t MacAddr64[AT24MAC402_EUI64_SIZE] = {0};


//------------------------------------------------------------------------------
///        Local functions
//------------------------------------------------------------------------------

static uint8_t _at24mac402_twi_handler_init (struct _handler_twi * phtwi);
static uint8_t _at24mac402_is_twi_handler_ready (struct _handler_twi * phtwi);
static uint8_t _at24mac402_twid_rd_wr (struct _handler_twi * phtwi, enum TWI_CMD Cmd);
static void _at24mac402_delay_ms (uint32_t delay);
static void _at24mac402_set_dummy_add (uint8_t PerAdd, uint8_t RegAdd);

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
uint8_t _at24mac402_twi_handler_init (struct _handler_twi * phtwi_eep)
{
	uint8_t Status = phtwi_eep->Status;
	static struct _twid twid;
	Twi* pTwi = NULL;

	assert( phtwi_eep->Twck != 0 );
	assert( phtwi_eep->IdTwi != 0 );

	memset((void*)&twid, 0x00, sizeof(twid));

	pio_configure(pins_twi_at24mac402, ARRAY_SIZE(pins_twi_at24mac402));
	pmc_enable_peripheral(at24mac402_TWI_ID);

	// Init twi
	pTwi = get_twi_addr_from_id (at24mac402_TWI_ID);
	twi_configure_master(pTwi, phtwi_eep->Twck);
	twid_initialize(&twid, pTwi);

	phtwi_eep->Status = Status | TWI_STATUS_HANDLE;
	memcpy ((void*)&phtwi_eep->twid, (void*)&twid, sizeof(twid));
	return phtwi_eep->Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

uint8_t _at24mac402_is_twi_handler_ready (struct _handler_twi* phtwi_eep)
{
	return phtwi_eep->Status & TWI_STATUS_READY;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

uint8_t _at24mac402_twid_rd_wr (struct _handler_twi* phtwi_eep, enum TWI_CMD Cmd)
{
	if (Cmd == TWI_RD)
		return (uint8_t)twid_read(&phtwi_eep->twid, phtwi_eep->PeriphAddr,
					  phtwi_eep->RegMemAddr, phtwi_eep->AddSize,
					  (uint8_t*)phtwi_eep->pData, phtwi_eep->LenData, 0);
	else
		return (uint8_t)twid_write(&phtwi_eep->twid, phtwi_eep->PeriphAddr,
					   phtwi_eep->RegMemAddr, phtwi_eep->AddSize,
					   (uint8_t*)phtwi_eep->pData, phtwi_eep->LenData, 0);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void _at24mac402_delay_ms (uint32_t delay)
{
	unsigned int count;
	for(;delay>0;delay--)
		for(count=0;count<(pmc_get_master_clock()/1000000);count++);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void _at24mac402_set_dummy_add (uint8_t PerAdd, uint8_t RegAdd)
{
	uint8_t Data = 0x00;
	htwi_eep.PeriphAddr = PerAdd;
	htwi_eep.RegMemAddr = RegAdd;
	htwi_eep.pData = &Data;
	htwi_eep.LenData = 1;
	_at24mac402_twid_rd_wr(&htwi_eep, TWI_RD);
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
uint8_t at24mac402_get_serial_number (uint8_t* pSerNumbr)
{
	uint8_t Status = TWI_SUCCES;
	uint8_t i2c_address = AT24MAC402_EXT_MEM_ADD | BitA0ToA2;

	// Tell the EEPROM where we would like to read from
	_at24mac402_set_dummy_add (i2c_address, AT24MAC402_SERIAL_NUMB_ADD) ; // Location of the serial number

	// Now read bytes from that memory address
	htwi_eep.PeriphAddr = i2c_address;
	htwi_eep.RegMemAddr = AT24MAC402_SERIAL_NUMB_ADD;
	htwi_eep.pData = pSerNumbr;
	htwi_eep.LenData = AT24MAC402_SER_NUM_SIZE;
	htwi_eep.AddSize = 1;
	Status = _at24mac402_twid_rd_wr(&htwi_eep, TWI_RD);
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Function to read the MAC address from a AT24MAC402 EEPROM
//
// add: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
// pMacAddr: a pointer to 6 bytes of memory
//
uint8_t at24mac402_get_mac_address(uint8_t* pMacAddr)
{
	uint8_t Status = TWI_SUCCES;
	uint8_t i2c_address = AT24MAC402_EXT_MEM_ADD | BitA0ToA2;

	_at24mac402_set_dummy_add (i2c_address, AT24MAC402_EUI48_VALUE_ADD) ; // Location of the EUI-48

	// Now read bytes from that memory address
	htwi_eep.RegMemAddr = AT24MAC402_EUI48_VALUE_ADD;
	htwi_eep.pData = pMacAddr;
	htwi_eep.LenData = AT24MAC402_EUI48_SIZE;
	Status = _at24mac402_twid_rd_wr(&htwi_eep, TWI_RD);
	return Status;
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
uint8_t at24mac402_read_eep (uint8_t add, uint8_t Len, uint8_t* pDataBuf)
{
	uint8_t Status = TWI_SUCCES;
	uint8_t i2c_address = AT24MAC402_EEP_ADD | BitA0ToA2;

	_at24mac402_set_dummy_add (i2c_address, add) ;

	htwi_eep.RegMemAddr = add;
	htwi_eep.pData = pDataBuf;
	htwi_eep.LenData = Len;
	Status = _at24mac402_twid_rd_wr(&htwi_eep, TWI_RD);
	return Status;
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
uint8_t at24mac402_write_eep (uint8_t add, uint8_t Len, uint8_t* pDataBuf)
{
	uint8_t Status = TWI_SUCCES;
	uint8_t i2c_address = AT24MAC402_EEP_ADD | BitA0ToA2;

	_at24mac402_set_dummy_add (i2c_address, add) ;
	htwi_eep.pData = pDataBuf;
	htwi_eep.LenData = 1;
	do {
		Status = _at24mac402_twid_rd_wr(&htwi_eep, TWI_WR);
		htwi_eep.RegMemAddr++;
		htwi_eep.pData++;
		// Wait at least 10 ms
		_at24mac402_delay_ms(10);
	} while (--Len);

	return Status;
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
uint8_t at24mac402_write_eep_async (uint8_t add, uint8_t Len, uint8_t* pDataBuf)
{
	uint8_t Status = TWI_SUCCES;
	uint8_t i2c_address = AT24MAC402_EEP_ADD | BitA0ToA2;

	_at24mac402_set_dummy_add (i2c_address, add) ;
	htwi_eep.PeriphAddr = i2c_address;
	htwi_eep.RegMemAddr = add ;
	htwi_eep.pData = pDataBuf;
	htwi_eep.LenData = Len;
	// ToDo Status = at24mac402_twid_rd_wr_async(&htwi_eep, TWI_WR);
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Function to write to the AT24MAC402 EEPROM
//
// BitA0ToA2: the 3-bit address assigned to the EEPROM (using the A0 A1 A2 pins)
// add: add to the data
// Len: data to be read
// pDataBuf: a pointer to write data read in EEP
//
uint8_t at24mac402_read_eep_async (uint8_t add, uint8_t Len, uint8_t* pDataBuf)
{
	uint8_t Status = TWI_SUCCES;
	uint8_t i2c_address = AT24MAC402_EEP_ADD | BitA0ToA2;

	_at24mac402_set_dummy_add (i2c_address, add) ;
	htwi_eep.PeriphAddr = i2c_address;
	htwi_eep.RegMemAddr = add ;
	htwi_eep.pData = pDataBuf;
	htwi_eep.LenData = Len;
	// ToDo Status = at24mac402_twid_rd_wr_async(&htwi_eep, TWI_RD);
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

uint8_t at24mac402_get_info_board (struct _at24mac402_board_info* pInfo_board)
{
	uint8_t Status = TWI_SUCCES;
	uint8_t crc = 0;

	Status = at24mac402_read_eep (AT24MAC402_INFO_ADD, AT24MAC402_INFO_SIZE, (uint8_t*)pInfo_board);
	if(Status != TWI_SUCCES) return Status;
	crc = compute_crc8 ((uint8_t*)pInfo_board, AT24MAC402_INFO_SIZE-1);
	return (crc==pInfo_board->crc) ? 0: 1;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
uint8_t at24mac402_set_info_board (struct _at24mac402_board_info* pInfo_board)
{
	uint8_t Status = TWI_SUCCES;

	pInfo_board->crc_sn = compute_crc8 ((uint8_t*)SerNumbr, AT24MAC402_SER_NUM_SIZE);
	pInfo_board->crc = compute_crc8 ((uint8_t*)pInfo_board, AT24MAC402_INFO_SIZE-1);
	Status = at24mac402_write_eep (AT24MAC402_INFO_ADD, AT24MAC402_INFO_SIZE, (uint8_t*)pInfo_board);
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

void _reset_buftwi (void)
{
	memset(buf_twi, 0x00, sizeof(buf_twi));
}

void at24mac402_display_info_board (struct _at24mac402_board_info* pInfo_board)
{
	printf("\tInfo Size   : %02d\n\r", pInfo_board->page_size);
	_reset_buftwi();
	memcpy(buf_twi, (char*)pInfo_board->manufacturer, SIZE_SUBC);
	printf("\tManufacturer: %s\n\r", buf_twi);
	_reset_buftwi();
	memcpy(buf_twi, (char*)pInfo_board->country, SIZE_MANUF_COUNTRY);
	printf("\tMade in     : %s\n\r", buf_twi);
	printf("\tManuf year  : %d\n\r", pInfo_board->manuf_year+2000);
	printf("\tWeek        : %02d\n\r", pInfo_board->manuf_week);
	_reset_buftwi();
	memcpy(buf_twi, (char*)pInfo_board->rev_code, SIZE_HW_REVISION);
	printf("\tRevision    : %s\n\r", buf_twi);
	printf("\tCrcSN       : Ox%02X\n\r", pInfo_board->crc_sn);
	printf("\tExtended add: 0x%04X\n\r", pInfo_board->addr_ext_config);
	_reset_buftwi();
	memcpy(buf_twi, (char*)pInfo_board->board_ident, SIZE_BOARD_IDENT);
	printf("\tBoard       : %s\n\r", buf_twi);
	printf("\tMapping     : %c\n\r", pInfo_board->rev_mapping);
	printf("\tCrc         : 0x%02X\n\r", pInfo_board->crc);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
void at24mac402_display_register (void)
{
	uint8_t Len, Status = TWI_SUCCES;
	struct _at24mac402_board_info sInfo = {0};

	// Display Serial Number
	printf(" -I- Serial Number: ");
	for (Len=0; Len<AT24MAC402_SER_NUM_SIZE; Len++) {
		printf("%02X", SerNumbr[Len]);
	}
	printf("\n\r");
	// Display Mac address
	printf(" -I- Mac add EUI48 ");
	for (Len=0; Len<AT24MAC402_EUI48_SIZE; Len++) {
		printf(":%02X", MacAddr48[Len]);
	}
	printf("\n\r");
	// Check Info board
	Status = at24mac402_get_info_board (&sInfo);
	if (Status) {
		memcpy (&buf_twi, &DEFAULT_BOARD_INFO, sizeof(struct _at24mac402_board_info));
		Status = at24mac402_set_info_board ((struct _at24mac402_board_info*)&buf_twi);
		Status = at24mac402_get_info_board (&sInfo);
	}
	printf(" -I- Manufacturing info\n\r");
	at24mac402_display_info_board(&sInfo);
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

uint8_t at24mac402_begin (void)
{
	uint8_t Status = TWI_SUCCES;

	if (!_at24mac402_is_twi_handler_ready(&htwi_eep))
	{
		// Set TWI interface
		memset ((uint8_t*)&htwi_eep, 0x00, sizeof(htwi_eep));
		htwi_eep.IdTwi = ID_TWI1;
		htwi_eep.Twck = TWCK_400K;
		trace_info("at24mac402 @0x%02X TWCK:%dKHz \n\r",
			   (unsigned int)AT24MAC402_EXT_MEM_ADD,
			   (unsigned int)htwi_eep.Twck/1000);
		Status = _at24mac402_twi_handler_init (&htwi_eep);
		htwi_eep.PeriphAddr = AT24MAC402_EXT_MEM_ADD;
		htwi_eep.AddSize = 1;
		htwi_eep.pData = &buf_twi[0];
		htwi_eep.LenData = 1;
	}
	if( !(Status&TWI_STATUS_HANDLE)) return TWI_FAIL;
	else Status = TWI_SUCCES;

	// Read serial number
	Status |=at24mac402_get_serial_number(&SerNumbr[0]);
	// Get EUI-48 mac address
	Status |= at24mac402_get_mac_address(&MacAddr48[0]);
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------

uint8_t at24mac402_test (void)
{
	uint8_t Len, Status = TWI_SUCCES;
	uint8_t Pattern[2] = {0xA5, 0x5A};

	Status = at24mac402_begin();
	if (Status) return Status = TWI_FAIL;

	//** start test
	// Erase
	memset (buf_twi, 0x00, AT24MAC402_PAGE_SIZE);
	Status = at24mac402_write_eep (AT24MAC402_FIRST_MEM_ADD, AT24MAC402_BLOCK_SIZE, buf_twi);
	// Write pattern
	for(Len=0; Len<(AT24MAC402_BLOCK_SIZE); Len+=2) {
		buf_twi[Len+0] = Pattern[0];
		buf_twi[Len+1] = Pattern[1];
	}
	Status = at24mac402_write_eep (AT24MAC402_FIRST_MEM_ADD, AT24MAC402_BLOCK_SIZE, buf_twi);
	// Read back
	memset (buf_twi, 0x00, AT24MAC402_BLOCK_SIZE);
	Status = at24mac402_read_eep (AT24MAC402_FIRST_MEM_ADD, AT24MAC402_BLOCK_SIZE, buf_twi);
	// Compare
	Status = TWI_SUCCES;
	printf("-T- ");
	for(Len=0; Len<AT24MAC402_BLOCK_SIZE; Len+=2) {
		printf("%s", buf_twi[Len]!=Pattern[0] ? "!": "." );
		printf("%s", buf_twi[Len+1]!=Pattern[1] ? "!": "." );
		if( buf_twi[Len]!=Pattern[0] || buf_twi[Len+1]!=Pattern[1] ) {Status++;}
	}
	printf("\n\r");
	return Status;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//End of file
