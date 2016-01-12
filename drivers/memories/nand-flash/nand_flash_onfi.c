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

#include "chip.h"
#include "trace.h"

#include "nand_flash.h"
#include "nand_flash_raw.h"
#include "nand_flash_model.h"
#include "nand_flash_onfi.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define MAX_READ_STATUS_COUNT 1000

/** Not all 256 bytes are useful */
#define ONFI_PARAM_TABLE_SIZE 116

/*---------------------------------------------------------------------- */
/*                   Variables                                           */
/*---------------------------------------------------------------------- */

/** ONFI Parameter page instance */
static struct _onfi_page_param onfi_parameter;

/*--------------------------------------------------------------------------
 *        Internal functions
 *------------------------------------------------------------------------*/

/**
 * \brief This function Reads the status register of the NAND device by
 * issuing a 0x70 command.
 * \return  NAND_IO_RC_PASS     =0 : The function completes operation successfully.
 *          NAND_IO_RC_FAIL     =1 : The function does not complete operation successfully.
 *          NAND_IO_RC_TIMEOUT  =2 : The function times out before operation completes.
*/
static uint32_t onfi_read_status(const struct _nand_flash *nand)
{
	uint8_t status;
	int retry;

	/* Issue command */
	nand_write_command(nand, NAND_CMD_STATUS);
	for (retry = 0; retry < MAX_READ_STATUS_COUNT; retry++) {
		/* Read status byte */
		status = nand_read_data(nand);

		/* Check status */
		/* If status bit 6 = 1 device is ready */
		if ((status & STATUS_BIT_6) == STATUS_BIT_6) {
			/* If status bit 0 = 0 the last operation was successful */
			if ((status & STATUS_BIT_0) == 0)
				return NAND_IO_RC_PASS;
			else
				return NAND_IO_RC_FAIL;
		}
	}

	return NAND_IO_RC_TIMEOUT;
}


/**
 * \brief This function retrieves the data structure that describes the target's
 * organization, features, timings and other behavioural parameters.
 * \return  0: ONFI not compliant or not supported.
			1: ONFI compliant
*/
static bool nand_onfi_retrieve_param(const struct _nand_flash *nand)
{
	uint8_t i;
	uint8_t onfi_param_table[ONFI_PARAM_TABLE_SIZE];

	if (nand_onfi_check_compatibility(nand)) {
		onfi_parameter.onfi_compatible = true;
		for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++) {
			onfi_param_table[i] = 0xFF;
		}
		/* Perform Read Parameter Page command */
		nand_write_command(nand, NAND_CMD_READ_PARAM_PAGE);
		nand_write_address(nand, 0x0);

		/* Wait NF ready */
		onfi_read_status(nand);

		/* Re-enable data output mode required after Read Status command */
		nand_write_command(nand, NAND_CMD_READ0);

		/* Read the parameter table */
		for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++) {
			onfi_param_table[i] = nand_read_data(nand);
		}
		for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++) {
			if (onfi_param_table[i] != 0xFF)
				break;
		}
		if (i == ONFI_PARAM_TABLE_SIZE) {
			onfi_parameter.onfi_compatible = false;
			return false;
		}

		/* Bus width */
		onfi_parameter.onfi_bus_width = (*(uint8_t*)(onfi_param_table + 6)) & 0x01;
		/* Device model */
		onfi_parameter.onfi_device_model= *(uint8_t*)(onfi_param_table + 49);
		/* JEDEC manufacturer ID */
		onfi_parameter.manufacturer_id = *(uint8_t*)(onfi_param_table + 64);
		/* Get number of data bytes per page (bytes 80-83 in the param table) */
		onfi_parameter.onfi_page_size =  *(uint32_t*)(onfi_param_table + 80);
		/* Get number of spare bytes per page (bytes 84-85 in the param table) */
		onfi_parameter.onfi_spare_size =  *(uint16_t*)(onfi_param_table + 84);
		/* Number of pages per block. */
		onfi_parameter.onfi_pages_per_block = *(uint32_t*)(onfi_param_table + 92);
		/* Number of blocks per logical unit (LUN). */
		onfi_parameter.onfi_blocks_per_lun = *(uint32_t*)(onfi_param_table + 96);
		/* Number of logical units. */
		onfi_parameter.onfi_logical_units = *(uint8_t*)(onfi_param_table + 100);
		/* Number of bits of ECC correction */
		onfi_parameter.onfi_ecc_correctability = *(uint8_t*)(onfi_param_table + 112);

		trace_info_wp("ONFI manufacturerId %x\r\n",
				onfi_parameter.manufacturer_id);
		trace_info_wp("ONFI onfiPageSize %x\r\n",
				(unsigned)onfi_parameter.onfi_page_size);
		trace_info_wp("ONFI onfiSpareSize %x\r\n",
				(unsigned)onfi_parameter.onfi_spare_size);
		trace_info_wp("ONFI onfiEccCorrectability %x\r\n",
				onfi_parameter.onfi_ecc_correctability);
		return true;
	}

	return false;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief This function reads an the ONFI signature at address of 0x20 to detect
 * if the device is ONFI compatible.
 * \return false if ONFI not compliant or not supported, true if ONFI compliant
*/
bool nand_onfi_check_compatibility(const struct _nand_flash *nand)
{
	uint8_t onfi_param_table[ONFI_PARAM_TABLE_SIZE];

	nand_write_command(nand, NAND_CMD_READID);
	nand_write_address(nand, 0x20);
	onfi_param_table[0] = nand_read_data(nand);
	onfi_param_table[1] = nand_read_data(nand);
	onfi_param_table[2] = nand_read_data(nand);
	onfi_param_table[3] = nand_read_data(nand);

	return onfi_param_table[0] == 'O' && onfi_param_table[1] == 'N' &&
		onfi_param_table[2] == 'F' && onfi_param_table[3] == 'I';
}

bool nand_onfi_is_compatible(void)
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
	return onfi_parameter.onfi_pages_per_block;
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
 * \return false if ONFI not compliant or internal ECC not supported, true if Internal ECC enabled.
*/
bool nand_onfi_enable_internal_ecc(const struct _nand_flash *nand)
{
	if (onfi_parameter.onfi_compatible) {
		/* Check if the NANDFLASH has an embedded ECC controller
		   Known memories with this feature :
		   - Manufacturer ID = 2Ch (Micron)
		   - Number of bits ECC = 04h (4-bit ECC means process 34nm)
		   - device size = 1Gb or 2Gb or 4Gb */
		if ((onfi_parameter.manufacturer_id & NAND_MFR_MICRON) == NAND_MFR_MICRON &&
				onfi_parameter.onfi_ecc_correctability == 0x4 &&
				(onfi_parameter.onfi_device_model == '1' ||
				 onfi_parameter.onfi_device_model == '2' ||
				 onfi_parameter.onfi_device_model == '4')) {
			/* then activate the internal ECC controller */
			nand_write_command(nand, NAND_CMD_SET_FEATURE);
			nand_write_address(nand, 0x90);
			nand_write_data(nand, 0x08);
			nand_write_data(nand, 0x00);
			nand_write_data(nand, 0x00);
			nand_write_data(nand, 0x00);
			nand_set_ecc_type(ECC_NO);
			return true;
		}
	}
	return false;
}

/**
 * \brief This function check if the NANDFLASH has an embedded ECC controller, and disable it.
 * \return false if ONFI not compliant or internal ECC not supported, true if Internal ECC disabled.
*/
bool nand_onfi_disable_internal_ecc(const struct _nand_flash *nand)
{
	if (onfi_parameter.onfi_compatible) {
		/* Check if the NANDFLASH has an embedded ECC controller
		   Known memories with this feature :
		   - Manufacturer ID = 2Ch (Micron)
		   - Number of bits ECC = 04h (4-bit ECC means process 34nm)
		   - device size = 1Gb or 2Gb or 4Gb */
		if ((onfi_parameter.manufacturer_id & NAND_MFR_MICRON) == NAND_MFR_MICRON &&
				onfi_parameter.onfi_ecc_correctability == 0x4 &&
				(onfi_parameter.onfi_device_model == '1' ||
				 onfi_parameter.onfi_device_model == '2' ||
				 onfi_parameter.onfi_device_model == '4')) {
			/* then activate the internal ECC controller */
			nand_write_command(nand, NAND_CMD_SET_FEATURE);
			nand_write_address(nand, 0x90);
			nand_write_data(nand, 0x00);
			nand_write_data(nand, 0x00);
			nand_write_data(nand, 0x00);
			nand_write_data(nand, 0x00);
			return true;
		}
	}
	return false;
}
/**
 * \brief Detect NANDFLASH connection on EBI.
 * \return return TRUE if the chip is detected.  FALSE otherwise.
 */

bool nand_onfi_device_detect(const struct _nand_flash *nand)
{
	uint8_t rc;
	uint8_t id[4];

	/* Send Reset command */
	nand_write_command(nand, NAND_CMD_RESET);

	/* If a NANDFLASH is connected, it should answer to a read status command */
	for (;;) {
		rc = onfi_read_status(nand);
		if (rc == NAND_IO_RC_PASS) {
			nand_write_command(nand, NAND_CMD_READID);
			nand_write_address(nand, 0);
			id[0] = nand_read_data(nand);
			id[1] = nand_read_data(nand);
			id[2] = nand_read_data(nand);
			id[3] = nand_read_data(nand);
#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
			trace_debug("NANDFLASH ID = <%x,%x,%x,%x>\r\n",
					id[0], id[1], id[2], id[3]);
#else
			(void)id;
#endif
			break;
		}
	}

	return nand_onfi_retrieve_param(nand);
}

