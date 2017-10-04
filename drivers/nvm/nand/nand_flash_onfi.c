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

#include <string.h>

#include "chip.h"
#include "trace.h"

#include "nand_flash.h"
#include "nand_flash_raw.h"
#include "nand_flash_model.h"
#include "nand_flash_onfi.h"
#include "nand_flash_commands.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#define MAX_READ_STATUS_COUNT 1000

/** Not all 256 bytes are useful */
#define ONFI_PARAM_TABLE_SIZE 116

#define NAND_MFR_MICRON    0x2c

/*---------------------------------------------------------------------- */
/*                   Variables                                           */
/*---------------------------------------------------------------------- */

/** ONFI Parameter page instance */
static struct _onfi_page_param onfi_parameter;

/*--------------------------------------------------------------------------
 *        Internal functions
 *------------------------------------------------------------------------*/

/**
 * \brief This function reads the status register of the NAND device.
 * \return  NAND_IO_RC_PASS     = 0 : The function completes operation successfully.
 *          NAND_IO_RC_FAIL     = 1 : The function does not complete operation successfully.
 *          NAND_IO_RC_TIMEOUT  = 2 : The function times out before operation completes.
 */
static uint32_t onfi_read_status(const struct _nand_flash *nand)
{
	int i;

	/* Issue command */
	nand_write_command(nand, NAND_CMD_STATUS);

	for (i = 0; i < MAX_READ_STATUS_COUNT; i++) {
		uint8_t status = nand_read_data(nand);

		/* Check that device is ready */
		if (!(status & NAND_STATUS_RDY))
			continue;

		/* Check that last command was successful */
		if ((status & NAND_STATUS_FAIL) == 0)
			return NAND_IO_RC_PASS;
		else
			return NAND_IO_RC_FAIL;
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

	onfi_parameter.onfi_compatible = false;

	if (nand_onfi_check_compatibility(nand)) {
		/* Perform Read Parameter Page command */
		nand_write_command(nand, NAND_CMD_READ_PARAM_PAGE);
		nand_write_address(nand, 0x0);

		/* Wait NF ready */
		onfi_read_status(nand);

		/* Re-enable data output mode required after Read Status command */
		nand_write_command(nand, NAND_CMD_READ_1);

		/* Read the parameter table */
		for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++)
			onfi_param_table[i] = nand_read_data(nand);

		/* Check table (full 0xFF -> failure) */
		for (i = 0; i < ONFI_PARAM_TABLE_SIZE; i++)
			if (onfi_param_table[i] != 0xFF)
				break;
		if (i == ONFI_PARAM_TABLE_SIZE)
			return false;

		onfi_parameter.onfi_compatible = true;
		/* Bus width */
		onfi_parameter.bus_width = (onfi_param_table[6] & 0x01) ? 16 : 8;
		/* Manufacturer */
		memcpy(onfi_parameter.manufacturer, &onfi_param_table[32], 12);
		onfi_parameter.manufacturer[12] = 0;
		/* Device model */
		memcpy(onfi_parameter.device_model, &onfi_param_table[44], 20);
		onfi_parameter.device_model[20] = 0;
		/* JEDEC manufacturer ID */
		onfi_parameter.manuf_id = onfi_param_table[64];
		/* Get number of data bytes per page (bytes 80-83 in the param table) */
		memcpy(&onfi_parameter.page_size, &onfi_param_table[80], 4);
		/* Get number of spare bytes per page (bytes 84-85 in the param table) */
		memcpy(&onfi_parameter.spare_size, &onfi_param_table[84], 2);
		/* Number of pages per block. */
		memcpy(&onfi_parameter.pages_per_block, &onfi_param_table[92], 4);
		/* Number of blocks per logical unit (LUN). */
		memcpy(&onfi_parameter.blocks_per_lun, &onfi_param_table[96], 4);
		/* Number of logical units. */
		onfi_parameter.logical_units = onfi_param_table[100];
		/* Number of bits of ECC correction */
		onfi_parameter.ecc_correctability = onfi_param_table[112];

		trace_info_wp("ONFI manuf_id 0x%02x\r\n",
				onfi_parameter.manuf_id);
		trace_info_wp("ONFI manufacturer %s\r\n",
				onfi_parameter.manufacturer);
		trace_info_wp("ONFI device_model %s\r\n",
				onfi_parameter.device_model);
		trace_info_wp("ONFI page_size %d\r\n",
				(unsigned)onfi_parameter.page_size);
		trace_info_wp("ONFI spare_size %d\r\n",
				(unsigned)onfi_parameter.spare_size);
		trace_info_wp("ONFI pages_per_block %d\r\n",
				(unsigned)onfi_parameter.pages_per_block);
		trace_info_wp("ONFI blocks_per_lun %d\r\n",
				(unsigned)onfi_parameter.blocks_per_lun);
		trace_info_wp("ONFI logical_units %d\r\n",
				(unsigned)onfi_parameter.logical_units);
		trace_info_wp("ONFI ecc_correctability %d\r\n",
				onfi_parameter.ecc_correctability);
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
	return onfi_parameter.manuf_id;
}

uint8_t nand_onfi_get_bus_width(void)
{
	return onfi_parameter.bus_width;
}

uint32_t nand_onfi_get_page_size(void)
{
	return onfi_parameter.page_size;
}

uint16_t nand_onfi_get_spare_size(void)
{
	return onfi_parameter.spare_size;
}

uint16_t nand_onfi_get_pages_per_block(void)
{
	return onfi_parameter.pages_per_block;
}

uint16_t nand_onfi_get_blocks_per_lun(void)
{
	return onfi_parameter.blocks_per_lun;
}

uint8_t nand_onfi_get_ecc_correctability(void)
{
	return onfi_parameter.ecc_correctability;
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
		if (onfi_parameter.manuf_id == NAND_MFR_MICRON &&
		    onfi_parameter.ecc_correctability == 0x4 &&
		    (onfi_parameter.device_model[5] == '1' ||
		     onfi_parameter.device_model[5] == '2' ||
		     onfi_parameter.device_model[5] == '4')) {
			/* enable the internal ECC controller */
			nand_write_command(nand, NAND_CMD_SET_FEATURES);
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
		if (onfi_parameter.manuf_id == NAND_MFR_MICRON &&
		    onfi_parameter.ecc_correctability == 0x4 &&
		    (onfi_parameter.device_model[5] == '1' ||
		     onfi_parameter.device_model[5] == '2' ||
		     onfi_parameter.device_model[5] == '4')) {
			/* disable the internal ECC controller */
			nand_write_command(nand, NAND_CMD_SET_FEATURES);
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
	/* Send Reset command */
	nand_write_command(nand, NAND_CMD_RESET);

	/* If a NANDFLASH is connected, it should answer to a read status command */
	for (;;) {
		uint8_t rc = onfi_read_status(nand);
		if (rc == NAND_IO_RC_PASS)
			break;
	}

	return nand_onfi_retrieve_param(nand);
}

bool nand_onfi_get_model(struct _nand_flash_model *model)
{
	if (onfi_parameter.onfi_compatible) {
		model->device_id = nand_onfi_get_manufacturer_id();
		model->data_bus_width = nand_onfi_get_bus_width();
		model->page_size = nand_onfi_get_page_size();
		model->spare_size = nand_onfi_get_spare_size();
		model->block_size = nand_onfi_get_pages_per_block() * nand_onfi_get_page_size();
		model->device_size = ((model->block_size / 1024) * nand_onfi_get_blocks_per_lun()) / 1024;
		return true;
	}
	return false;
}
