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

/** \file */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <board.h>

#include "trace.h"

#include "nand_flash_common.h"
#include "nand_flash_raw.h"
#include "nand_flash_model.h"
#include "nand_flash_model_list.h"
#include "nand_flash_onfi.h"
#include "nand_flash_api.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
#define MAX_READ_STATUS_COUNT 1000

/** Not all 256 bytes are useful */
#define ONFI_PARAM_TABLE_SIZE 116

#define EBI_NF_ADDR BOARD_NANDFLASH_ADDR

/*---------------------------------------------------------------------- */
/*                   Variables                                           */
/*---------------------------------------------------------------------- */

/** ONFI Parameter page instance */
static struct _onfi_page_param onfi_parameter;

/*--------------------------------------------------------------------------
 *        Internal functions
 *------------------------------------------------------------------------*/

static void write_nand(uint8_t data)
{
	*(volatile uint8_t*)((uint32_t)EBI_NF_ADDR) = data;
}

static void write_nand_command(uint8_t cmd)
{
	*(volatile uint8_t*)((uint32_t)EBI_NF_ADDR | BOARD_NF_COMMAND_ADDR) = cmd;
}

static void write_nand_address(uint8_t addr)
{
	*(volatile uint8_t*)((uint32_t)EBI_NF_ADDR | BOARD_NF_ADDRESS_ADDR) = addr;
}

static uint8_t read_nand(void)
{
	return *(volatile uint8_t*)((uint32_t)EBI_NF_ADDR);
}

/**
 * \brief This function Reads the status register of the NAND device by
 * issuing a 0x70 command.
 * \return  NAND_IO_RC_PASS     =0 : The function completes operation successfully.
 *          NAND_IO_RC_FAIL     =1 : The function does not complete operation successfully.
 *          NAND_IO_RC_TIMEOUT  =2 : The function times out before operation completes.
*/
static uint32_t onfi_read_status(void)
{
	uint32_t retry;
	uint8_t ucStatus;

	/* Issue command */
	write_nand_command(NAND_CMD_STATUS);
	retry = 0;

	while (retry < MAX_READ_STATUS_COUNT) {
		/* Read status byte */
		ucStatus = read_nand();
		/* Check status */
		/* If status bit 6 = 1 device is ready */
		if ((ucStatus & STATUS_BIT_6) == STATUS_BIT_6) {

			if ((ucStatus & STATUS_BIT_0) == 0)
			/* If status bit 0 = 0 the last operation was successful */
				return NAND_IO_RC_PASS;
			else
				return NAND_IO_RC_FAIL;
		}
		retry++;
	}
	return NAND_IO_RC_TIMEOUT;
}


/**
 * \brief This function retrieves the data structure that describes the target's
 * organization, features, timings and other behavioural parameters.
 * \return  0: ONFI not compliant or not supported.
			1: ONFI compliant
*/
static uint8_t nand_onfi_retrieve_param (void)
{
	uint8_t i;
	uint8_t onfi_param_table[ONFI_PARAM_TABLE_SIZE];

	if (nand_onfi_is_compatible()) {
		onfi_parameter.onfi_compatible = 1;
		for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++) {
			onfi_param_table[i] = 0xFF;
		}
		/* Perform Read Parameter Page command */
		write_nand_command(NAND_CMD_READ_PARAM_PAGE);
		write_nand_address(0x0);

		/* Wait NF ready */
		onfi_read_status();
		/* Re-enable data output mode required after Read Status command */
		write_nand_command(NAND_CMD_READ0);

		/* Read the parameter table */
		for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++) {
			onfi_param_table[i] = read_nand();
		}
		for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++) {
			if (onfi_param_table[i] != 0xFF)
				break;
		}
		if (i == ONFI_PARAM_TABLE_SIZE) {
			onfi_parameter.onfi_compatible = 0;
			return 0;
		}

		/* JEDEC manufacturer ID */
		onfi_parameter.manufacturer_id = *(uint8_t *)(onfi_param_table + 64);
		trace_info("ONFI manufacturerId %x \n\r",onfi_parameter.manufacturer_id);
		/* Bus width */
		onfi_parameter.onfi_bus_width = (*(uint8_t *)(onfi_param_table + 6)) & 0x01;
		/* Get number of data bytes per page (bytes 80-83 in the param table) */
		onfi_parameter.onfi_page_size =  *(uint32_t *)(void*)(onfi_param_table + 80);
		trace_info("ONFI onfiPageSize %x \n\r", (unsigned int)onfi_parameter.onfi_page_size);
		/* Get number of spare bytes per page (bytes 84-85 in the param table) */
		onfi_parameter.onfi_spare_size =  *(uint16_t *)(void*)(onfi_param_table + 84);
		 trace_info("ONFI onfiSpareSize %x \n\r",(unsigned int)onfi_parameter.onfi_spare_size);
		/* Number of pages per block. */
		onfi_parameter.onfi_pages_per_block = *(uint32_t *)(void*)(onfi_param_table + 92);
		/* Number of blocks per logical unit (LUN). */
		onfi_parameter.onfi_blocks_per_lun = *(uint32_t *)(void*)(onfi_param_table + 96);
		/* Number of logical units. */
		onfi_parameter.onfi_logical_units = *(uint8_t *)(onfi_param_table + 100);
		/* Number of bits of ECC correction */
		onfi_parameter.onfi_ecc_correctability = *(uint8_t *)(onfi_param_table + 112);
		trace_info("ONFI onfiEccCorrectability %x \n\r",onfi_parameter.onfi_ecc_correctability);
		/* Device model */
		onfi_parameter.onfi_device_model= *(uint8_t *)(onfi_param_table + 49);
		return 1;
	}
	return 0;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 * \brief This function read an the ONFI signature at address of 20h to detect
 * if the device is ONFI compatible.
 * \return  0: ONFI not compliant or not supported.
			1: ONFI compliant
*/
uint8_t nand_onfi_is_compatible (void)
{
	uint8_t onfi_param_table[ONFI_PARAM_TABLE_SIZE];

	// Check if the Nandflash is ONFI compliant

	write_nand_command(NAND_CMD_READID);
	write_nand_address(0x20);

	onfi_param_table[0] = read_nand();
	onfi_param_table[1] = read_nand();
	onfi_param_table[2] = read_nand();
	onfi_param_table[3] = read_nand();

	if ((onfi_param_table[0] == 'O') &&
		(onfi_param_table[1] == 'N') &&
		(onfi_param_table[2] == 'F') &&
		(onfi_param_table[3] == 'I')) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t nand_onfi_compatible(void)
{
	return onfi_parameter.onfi_compatible;
}

uint8_t nand_onfi_get_manufacturer_id(void)
{
	return onfi_parameter.manufacturer_id;
}

uint8_t nand_onfi_get_bus_width(void)
{
	return onfi_parameter.onfi_bus_width;
}

uint32_t nand_onfi_get_page_size(void)
{
	return onfi_parameter.onfi_page_size;
}

uint16_t nand_onfi_get_spare_size(void)
{
	return onfi_parameter.onfi_spare_size;
}

uint16_t nand_onfi_get_pages_per_block(void)
{
	return onfi_parameter.onfi_pages_per_block ;
}

uint16_t nand_onfi_get_blocks_per_lun(void)
{
	return onfi_parameter.onfi_blocks_per_lun;
}

uint8_t nand_onfi_get_ecc_correctability(void)
{
	return onfi_parameter.onfi_ecc_correctability;
}

/**
 * \brief This function check if the NANDFLASH has an embedded ECC controller.
 * \return  0: ONFI not compliant or internal ECC not supported.
			1: Internal ECC enabled.
*/
uint8_t nand_onfi_enable_internal_ecc (void)
{
	if (onfi_parameter.onfi_compatible == 1) {
		/* Check if the NANDFLASH has an embedded ECC controller
		   Known memories with this feature :
		   - Manufacturer ID = 2Ch (Micron)
		   - Number of bits ECC = 04h (4-bit ECC means process 34nm)
		   - device size = 1Gb or 2Gb or 4Gb (Number of data bytes per page * Number of pages per block * Number of blocks per unit)  */
		if ( ((onfi_parameter.manufacturer_id & NAND_MFR_MICRON) == NAND_MFR_MICRON) &&
			  (onfi_parameter.onfi_ecc_correctability == 0x4) &&
			  ((onfi_parameter.onfi_device_model == '1')     //  1G,
			   || (onfi_parameter.onfi_device_model == '2')     //  2G
			   || (onfi_parameter.onfi_device_model == '4'))) { //  or 4G bits

			/* then activate the internal ECC controller */
			write_nand_command(NAND_CMD_SET_FEATURE);
			write_nand_address(0x90);
			write_nand(0x08);
			write_nand(0x00);
			write_nand(0x00);
			write_nand(0x00);
			nand_api_configure_ecc(ECC_NO);
			return 1;
		}
	}
	return 0;
}


/**
 * \brief This function check if the NANDFLASH has an embedded ECC controller, and disable it.
 * \return  0: ONFI not compliant or internal ECC not supported.
			1: Internal ECC disabled.
*/
uint8_t nand_onfi_disable_internal_ecc (void)
{
	if (onfi_parameter.onfi_compatible == 1) {
		/* Check if the NANDFLASH has an embedded ECC controller
		   Known memories with this feature :
		   - Manufacturer ID = 2Ch (Micron)
		   - Number of bits ECC = 04h (4-bit ECC means process 34nm)
		   - device size = 1Gb or 2Gb or 4Gb (Number of data bytes per page * Number of pages per block * Number of blocks per unit)  */
		if ( ((onfi_parameter.manufacturer_id & NAND_MFR_MICRON) == NAND_MFR_MICRON) &&
			  (onfi_parameter.onfi_ecc_correctability == 0x4) &&
			  ((onfi_parameter.onfi_device_model == '1')     //  1G,
			   || (onfi_parameter.onfi_device_model == '2')     //  2G
			   || (onfi_parameter.onfi_device_model == '4'))) { //  or 4G bits

			/* then activate the internal ECC controller */
			write_nand_command(NAND_CMD_SET_FEATURE);
			write_nand_address(0x90);
			write_nand(0x00);
			write_nand(0x00);
			write_nand(0x00);
			write_nand(0x00);
			return 1;
		}
	}
	return 0;
}
/**
 * \brief Detect NANDFLASH connection on EBI.
 * \return return TRUE if the chip is detected.  FALSE otherwise.
 */

uint8_t nand_onfi_device_detect(void)
{
	uint8_t rc;
	uint8_t chip_found = 0;
	uint8_t ids[4];
	uint8_t i;

	/* Send Reset command */
	write_nand_command(NAND_CMD_RESET);
	/* If a NANDFLASH is connected, it should answer to a read status command */
	for (;;) {
		rc = onfi_read_status();
		if (rc == NAND_IO_RC_PASS) {
			write_nand_command(NAND_CMD_READID);
			write_nand_address(0);
			ids[0] = read_nand();
			ids[1] = read_nand();
			ids[2] = read_nand();
			ids[3] = read_nand();
			printf("<%x,%x,%x,%x>",ids[0],ids[1],ids[2],ids[3]);
			for(i = 0; i< NANDFLASH_MODEL_LIST_SIZE ; i++) {
				if(nand_flash_model_list[i].device_id == ids[1]) {
					chip_found = 1;
					break;
				}
			}
			break;
		}
	}
	if (chip_found == 0) {
		if (nand_onfi_is_compatible()) {
			chip_found = 1;
			/* even if it is not in device list (it is maybe a new device, but it is ONFI compatible */
		}
	}
	if (chip_found) nand_onfi_retrieve_param();
	return chip_found;
}

