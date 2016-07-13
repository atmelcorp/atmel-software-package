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

/*-----------------------------------------------------------------------*/
/*            Headers                                                    */
/*-----------------------------------------------------------------------*/

#include "chip.h"
#include "trace.h"

#include "peripherals/hsmc.h"
#include "peripherals/pio.h"
#include "peripherals/pmecc.h"
#include "misc/cache.h"

#include "nand_flash.h"
#include "nand_flash_raw.h"
#include "nand_flash_dma.h"
#include "nand_flash_model_list.h"

#include <assert.h>
#include <string.h>

/*---------------------------------------------------------------------- */
/*         Local variables                                               */
/*---------------------------------------------------------------------- */

CACHE_ALIGNED static uint8_t ecc_table[NAND_MAX_PMECC_BYTE_SIZE];

/*------------------------------------------------------------------------*/
/*        Local Functions                                                 */
/*------------------------------------------------------------------------*/

/**
 * \brief Sends the column address to the NandFlash chip.
 *
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param column_address  Column address to send.
 */
static void _write_column_address(const struct _nand_flash *nand,
		uint16_t column_address)
{
	uint16_t data_size = nand_model_get_page_data_size(&nand->model);

	/* Check the data bus width of the NandFlash */
	if (nand_model_get_data_bus(&nand->model) == 16)
		column_address >>= 1; /* addr div 2 is because of 16-bit addressing */

	while (data_size > 2) {
		if (nand_model_get_data_bus(&nand->model) == 16)
			nand_write_address16(nand, column_address & 0xFF);
		else
			nand_write_address(nand, column_address & 0xFF);
		data_size >>= 8;
		column_address >>= 8;
	}
}

/**
 * \brief Sends the row address to the NandFlash chip.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param row_address  Row address to send.
 */
static void _write_row_address(const struct _nand_flash *nand,
		uint32_t row_address)
{
	uint32_t num_pages = nand_model_get_device_size_in_pages(&nand->model);

	while (num_pages > 0) {
		if (nand_model_get_data_bus(&nand->model) == 16)
			nand_write_address16(nand, row_address & 0xFF);
		else
			nand_write_address(nand, row_address & 0xFF);
		num_pages >>= 8;
		row_address >>= 8;
	}
}

/**
 * \brief Translates the given column and row address into address cycles.
 * \param nand         Pointer to a struct _nand_flash instance.
 * \param col_address  Column address to translate
 * \param row_address  Row address to translate
 * \param cycle_bytes  Array of at least 5 bytes to hold the address cycle bytes
 * \param row_only     Only ROW address is output
 * \param col_only     Only COL address is output
 * \return Number of address cycles converted
 */
static uint32_t _nfc_translate_address(const struct _nand_flash *nand,
		uint16_t col_address, uint32_t row_address,
		uint8_t *cycle_bytes, uint8_t row_only, uint8_t col_only)
{
	uint16_t max_data_size =
		nand_model_get_page_data_size(&nand->model) +
		nand_model_get_page_spare_size(&nand->model) - 1;
	uint32_t max_page_num  =
		nand_model_get_device_size_in_pages(&nand->model) - 1;
	uint8_t num_cycles = 0;

	/* Check the data bus width of the NandFlash */
	if (nand_model_get_data_bus(&nand->model) == 16) {
		/* Div 2 is because we address in word and not in byte */
		col_address >>= 1;
	}

	/* Convert column address */
	if (!row_only) {
		/* Send single column address byte for small block devices,
		   or two column address bytes for large block devices */
		while (max_data_size > 2) {
			cycle_bytes[num_cycles++] = col_address & 0xFF;
			max_data_size >>= 8;
			col_address >>= 8;
		}
	}

	/* Convert row address */
	if (!col_only) {
		while (max_page_num > 0) {
			cycle_bytes[num_cycles++] = row_address & 0xFF;
			max_page_num >>= 8;
			row_address >>= 8;
		}
	}

	return num_cycles;
}

/**
 * \brief NAND flash send ALE CLE.
 * \param nand Pointer to a struct _nand_flash instance.
 * \param mode SMC ALE CLE mode parameter
 * \param cmd1 First command to be sent
 * \param cmd2 Second command to be sent
 * \param col_address Column address
 * \param row_address Row address
 */
static void _send_cle_ale(const struct _nand_flash *nand,
		uint8_t mode, uint32_t cmd1, uint32_t cmd2,
		uint32_t col_address, uint32_t row_address)
{
	/* Issue CLE and ALE through EBI */
	if (!nand_is_nfc_enabled()) {
		nand_write_command(nand, cmd1);

		if ((mode & ALE_COL_EN) == ALE_COL_EN)
			_write_column_address(nand, col_address);

		if ((mode & ALE_ROW_EN) == ALE_ROW_EN)
			_write_row_address(nand, row_address);

		/* When set to true, the CMD2 field is issued after the address cycle.*/
		if ((mode & CLE_VCMD2_EN) == CLE_VCMD2_EN)
			nand_write_command(nand, cmd2);
	} else { /* Issue CLE and ALE using NFC */
		uint32_t nfc_command;
		uint8_t cycle_bytes[5];

		nfc_command = NFCADDR_CMD_CMD1(cmd1) |
		              NFCADDR_CMD_CSID_3;

		if ((mode & CLE_VCMD2_EN) == CLE_VCMD2_EN) {
			nfc_command |= NFCADDR_CMD_VCMD2 |
			               NFCADDR_CMD_CMD2(cmd2);
		}

		if (mode & (ALE_COL_EN | ALE_ROW_EN)) {
			bool col_en = (mode & ALE_COL_EN) == ALE_COL_EN;
			bool row_en = (mode & ALE_ROW_EN) == ALE_ROW_EN;
			uint32_t cycles = _nfc_translate_address(nand,
					col_address, row_address, cycle_bytes,
					row_en && !col_en, col_en && !row_en);
			nfc_command |= NFCADDR_CMD_ACYCLE(cycles);
		}

		if ((mode & CLE_WRITE_EN) == CLE_WRITE_EN)
			nfc_command |= NFCADDR_CMD_NFCWR;

		if ((mode & CLE_DATA_EN) == CLE_DATA_EN && nand_is_nfc_sram_enabled())
			nfc_command |= NFCADDR_CMD_DATAEN;

		hsmc_nfc_send_cmd(nfc_command, cycle_bytes);
	}
}

/**
 * \brief Transfer data from NAND to the provided buffer.
 * \param nfc_sram True if the NFC SRAM is to be used, false otherwise
 * \param buffer   Buffer from which the data will be read
 * \param size     Number of bytes that will be read
 */
static void _data_array_in(const struct _nand_flash *nand, bool nfc_sram,
		uint8_t *buffer, uint32_t size)
{
	uint32_t address;
	uint32_t i;

	if (nfc_sram) {
		address = NFC_RAM_ADDR;
		hsmc_nfc_wait_xfr_done();
	} else {
		address = nand->data_addr;
	}

	if (nand_is_dma_enabled()) {
		nand_dma_read(address, (uint32_t)buffer, size);
	} else {
		uint32_t bus_width = nand_model_get_data_bus(&nand->model);

		/* Check the data bus width of the NandFlash */
		if (bus_width == 16 && !nfc_sram) {
			uint16_t *buff16 = (uint16_t*)buffer;
			volatile uint16_t *data16 = (volatile uint16_t*)address;
			size = (size + 1) >> 1;
			for (i = size; i != 0; i--) {
				*buff16 = *data16;
				buff16++;
			}
		} else {
			uint8_t *buff8 = buffer;
			volatile uint8_t *data8 = (volatile uint8_t*)address;
			for(i = size; i != 0; i--) {
				*buff8 = *data8;
				if (nfc_sram)
					data8++;
				buff8++;
			}
		}
	}
}

/**
 * \brief Transfer data to NANDFLASH from the provided buffer.
 * \param nfc_sram True if the NFC SRAM is to be used, false otherwise
 * \param buffer   Buffer where the data will be written
 * \param size     Number of bytes that will be written
 * \param offset   Offset in bytes
 */
static void _data_array_out(const struct _nand_flash *nand, bool nfc_sram,
		uint8_t *buffer, uint32_t size, uint32_t offset)
{
	uint32_t address;
	uint32_t i;

	if (nfc_sram) {
		address = NFC_RAM_ADDR;
	} else {
		address = nand->data_addr;
	}
	address += offset;

	if (nand_is_dma_enabled()) {
		nand_dma_write((uint32_t)buffer, address, size);
	} else {
		uint32_t bus_width = nand_model_get_data_bus(&nand->model);

		/* Check the data bus width of the NandFlash */
		if (bus_width == 16 && !nfc_sram) {
			uint16_t *buff16 = (uint16_t*)buffer;
			volatile uint16_t *data16 = (volatile uint16_t*)address;
			size = (size + 1) >> 1;
			for (i = size; i != 0; i--) {
				*data16 = *buff16;
				buff16++;
			}
		} else {
			uint8_t *buff8 = buffer;
			volatile uint8_t *data8 = (volatile uint8_t*)address;
			for (i = size; i != 0; i--) {
				*data8 = *buff8;
				if (nfc_sram)
					data8++;
				buff8++;
			}
		}
	}
}

/**
 * \brief NAND Flash devices have an 8-bit status register that the software can read during
    device operation..
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param status status to be checked.
 */
static uint8_t _status_ready_pass(const struct _nand_flash *nand)
{
	uint8_t status;
	uint16_t count;

	_send_cle_ale(nand, 0, COMMAND_STATUS, 0, 0, 0);

	for (count = 0; count < READ_STATUS_TIMEOUT; count++) {
		/* Read status byte */
		status = nand_read_data(nand);

		/* Check status */
		/* If status bit 6 = 1 device is ready */
		if ((status & STATUS_BIT_6) == STATUS_BIT_6) {
			/* If status bit 0 = 0 the last operation was successful */
			if ((status & STATUS_BIT_0) == 0)
				return 0;
			else
				return NAND_ERROR_STATUS;
		}
	}

	return NAND_ERROR_STATUS;
}

/**
 * \brief Waiting for the completion of a page program, erase and random read completion.
 * \param nand  Pointer to a struct _nand_flash instance.
 */
static uint8_t _nand_wait_ready(const struct _nand_flash *nand)
{
	return _status_ready_pass(nand);
}

/**
 * \brief Erases the specified block of the device. Returns 0 if the operation was
 * successful; otherwise returns an error code.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param block  Number of the physical block to erase.
 */
static uint8_t _erase_block(const struct _nand_flash *nand, uint16_t block)
{
	uint32_t row_address;

	NAND_TRACE("_erase_block(%d)\r\n", block);

	/* Calculate address used for erase */
	row_address = block * nand_model_get_block_size_in_pages(&nand->model);

	_send_cle_ale(nand, CLE_VCMD2_EN | ALE_ROW_EN,
	              COMMAND_ERASE_1, COMMAND_ERASE_2, 0, row_address);

	if (_nand_wait_ready(nand)) {
		trace_error("_erase_block: Could not erase block %d.\r\n", block);
		return NAND_ERROR_CANNOTERASE;
	}

	return 0;
}

/**
 * \brief Reads the data and/or the spare areas of a page of a NandFlash into the
 * provided buffers. If a buffer pointer is 0, the corresponding area is not
 * read.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param block  Number of the block where the page to read resides.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
static uint8_t _read_page(const struct _nand_flash *nand,
	uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare)
{
	uint32_t data_size = nand_model_get_page_data_size(&nand->model);
	uint32_t spare_size = nand_model_get_page_spare_size(&nand->model);
	uint32_t col_address, row_address;

	NAND_TRACE("_read_page(B#%d:P#%d)\r\n", block, page);

	/* at least one area must be read */
	assert(data || spare);

	if (nand_is_nfc_enabled())
		hsmc_nfc_configure(data_size, spare_size, spare != NULL, false);

	/* Calculate actual address of the page */
	row_address = block * nand_model_get_block_size_in_pages(&nand->model) + page;
	col_address = data ? 0 : data_size;

	if (nand_is_nfc_sram_enabled()) {
		_send_cle_ale(nand, ALE_COL_EN | ALE_ROW_EN | CLE_VCMD2_EN | CLE_DATA_EN,
		              COMMAND_READ_1, COMMAND_READ_2, col_address, row_address);
	} else {
		_send_cle_ale(nand, ALE_COL_EN | ALE_ROW_EN | CLE_VCMD2_EN,
		              COMMAND_READ_1, COMMAND_READ_2, col_address, row_address);
	}

	if (!nand_is_nfc_enabled()) {
		/* Wait for the nand to be ready */
		_status_ready_pass(nand);
		_send_cle_ale(nand, CLE_DATA_EN, COMMAND_READ_1, 0, 0, 0);
	} else {
		hsmc_nfc_wait_rb_busy();
	}

	/* Read data area */
	if (data)
		_data_array_in(nand, nand_is_nfc_sram_enabled(), data, data_size);

	/* Read spare area */
	if (spare)
		_data_array_in(nand, nand_is_nfc_sram_enabled(), spare, spare_size);

	return 0;
}

/**
 * \brief Reads the data and/or the spare areas of a page of a NandFlash into the
 * provided buffers. If a buffer pointer is 0, the corresponding area is not
 * read.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param block  Number of the block where the page to read resides.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
static uint8_t _read_page_with_pmecc(const struct _nand_flash *nand,
	uint16_t block, uint16_t page, uint8_t *data)
{
	uint32_t data_size = nand_model_get_page_data_size(&nand->model);
	uint32_t spare_size = nand_model_get_page_spare_size(&nand->model);
	uint32_t row_address;

	NAND_TRACE("_read_page_with_pmecc(B#%d:P#%d)\r\n", block, page);

	/* at least one area must be read */
	assert(data);

	if (nand_is_nfc_enabled())
		hsmc_nfc_configure(data_size, spare_size, true, false);

	/* Calculate actual address of the page */
	row_address = block * nand_model_get_block_size_in_pages(&nand->model) + page;

	hsmc_pmecc_reset();
	hsmc_pmecc_enable();

	if (!hsmc_pmecc_auto_apare_en())
		hsmc_pmecc_auto_enable();

	if (nand_is_nfc_sram_enabled()){
		hsmc_pmecc_data_phase();
		_send_cle_ale(nand, ALE_COL_EN | ALE_ROW_EN | CLE_VCMD2_EN | CLE_DATA_EN,
		              COMMAND_READ_1, COMMAND_READ_2, 0, row_address);
	} else {
		_send_cle_ale(nand, ALE_COL_EN | ALE_ROW_EN | CLE_VCMD2_EN,
		              COMMAND_READ_1, COMMAND_READ_2, 0, row_address);
	}

	if (!nand_is_nfc_enabled()){
		/* Wait for the nand to be ready */
		_nand_wait_ready(nand);
		_send_cle_ale(nand, 0, COMMAND_READ_1, 0, 0, 0);
	} else {
		if (!nand_is_nfc_sram_enabled())
			hsmc_nfc_wait_rb_busy();
	}

	/* Reset the ECC module*/
	hsmc_pmecc_or_reset();

	/* Start a Data Phase */
	hsmc_pmecc_data_phase();
	_data_array_in(nand, nand_is_nfc_sram_enabled(),
	               data, data_size + pmecc_get_ecc_end_address());

	/* Wait until the kernel of the PMECC is not busy */
	hsmc_pmecc_wait_ready();
	hsmc_pmecc_auto_disable();
	return 0;
}

/**
 * \brief Writes the data and/or the spare area of a page on a NandFlash chip. If one
 * of the buffer pointer is 0, the corresponding area is not written.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param block  Number of the block where the page to write resides.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \return 0 if the write operation is successful; otherwise returns 1.
*/
static uint8_t _write_page(const struct _nand_flash *nand,
	uint16_t block, uint16_t page, uint8_t *data, uint8_t *spare)
{
	uint8_t error = 0;
	uint32_t data_size = nand_model_get_page_data_size(&nand->model);
	uint32_t spare_size = nand_model_get_page_spare_size(&nand->model);
	uint32_t row_address;

	NAND_TRACE("_write_page(B#%d:P#%d)\r\n", block, page);

	if (nand_is_nfc_enabled())
		hsmc_nfc_configure(data_size, spare_size, false, spare != NULL);

	/* Calculate physical address of the page */
	row_address = block * nand_model_get_block_size_in_pages(&nand->model) + page;

	/* Write data area if needed */
	if (data) {
		/* Start a Data Phase */
		if (nand_is_nfc_sram_enabled()) {
			_data_array_out(nand, true, data, data_size, 0);
			if (spare)
				_data_array_out(nand, true, spare, spare_size, data_size);

			_send_cle_ale(nand, CLE_WRITE_EN | ALE_COL_EN | ALE_ROW_EN | CLE_DATA_EN,
			              COMMAND_WRITE_1, 0, 0, row_address);

			hsmc_nfc_wait_xfr_done();
		} else {
			_send_cle_ale(nand, CLE_WRITE_EN | ALE_COL_EN | ALE_ROW_EN,
			              COMMAND_WRITE_1, 0, 0, row_address);

			_data_array_out(nand, false, data, data_size, 0);
			if (spare)
				_data_array_out(nand, false, spare, spare_size, data_size);
		}
	} else {
		/* Write spare area alone if needed */
		if (spare) {
			_send_cle_ale(nand, CLE_WRITE_EN | ALE_COL_EN | ALE_ROW_EN,
			              COMMAND_WRITE_1, 0, data_size, row_address);

			_data_array_out(nand, false, spare, spare_size, 0);
		}
	}

	_send_cle_ale(nand, CLE_WRITE_EN, COMMAND_WRITE_2, 0, 0, 0);

	if (nand_is_nfc_enabled() && !nand_is_nfc_sram_enabled())
		hsmc_nfc_wait_rb_busy();

	if (_status_ready_pass(nand)) {
			trace_error("write_page_no_ecc: Failed writing data area.\r\n");
			error = NAND_ERROR_CANNOTWRITE;
	}

	return error;
}

/**
 * \brief Writes the data and/or the spare area of a page on a NandFlash chip. If one
 * of the buffer pointer is 0, the corresponding area is not written.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param block  Number of the block where the page to write resides.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \return 0 if the write operation is successful; otherwise returns 1.
*/
static uint8_t _write_page_with_pmecc(const struct _nand_flash *nand,
	uint16_t block, uint16_t page, uint8_t *data)
{
	uint8_t error = 0;
	uint32_t data_size = nand_model_get_page_data_size(&nand->model);
	uint32_t spare_size = nand_model_get_page_spare_size(&nand->model);
	uint32_t row_address;
	uint32_t ecc_start_addr;
	uint32_t bytes_per_sector;
	uint32_t pmecc_sector_number;
	uint32_t pmecc_sector_index;
	uint32_t byte_index;
	volatile uint8_t *pmecc[8];
	uint8_t i;
	uint8_t nb_sectors_per_page;

	NAND_TRACE("_write_page_with_pmecc(B#%d:P#%d)\r\n", block, page);

	assert(data);

	if (nand_is_nfc_enabled())
		hsmc_nfc_configure(data_size, spare_size, false, false);

	ecc_start_addr = data_size + pmecc_get_ecc_start_address();

	/* Calculate physical address of the page */
	row_address = block * nand_model_get_block_size_in_pages(&nand->model) + page;

	/* Write data area if needed */
	switch (pmecc_get_page_size()) {
		case HSMC_PMECCFG_PAGESIZE_PAGESIZE_1SEC:
			nb_sectors_per_page = 1;
			break;
		case HSMC_PMECCFG_PAGESIZE_PAGESIZE_2SEC:
			nb_sectors_per_page = 2;
			break;
		case HSMC_PMECCFG_PAGESIZE_PAGESIZE_4SEC:
			nb_sectors_per_page = 4;
			break;
		case HSMC_PMECCFG_PAGESIZE_PAGESIZE_8SEC:
			nb_sectors_per_page = 8;
			break;
		default:
			nb_sectors_per_page = 1;
			break;
	}
	hsmc_pmecc_reset();
	hsmc_pmecc_enable();
	for (i = 0; i < 8; i++)
		pmecc[i] = (volatile uint8_t *)&hsmc_pmecc(i);

	/* Start a Data Phase */
	hsmc_pmecc_data_phase();
	hsmc_pmecc_enable_write();
	if (nand_is_nfc_sram_enabled()) {
		_data_array_out(nand, true, (uint8_t*)data, data_size, 0);

		_send_cle_ale(nand, CLE_WRITE_EN | ALE_COL_EN | ALE_ROW_EN | CLE_DATA_EN,
		              COMMAND_WRITE_1, 0, 0, row_address);

		hsmc_nfc_wait_xfr_done();
	} else {
		_send_cle_ale(nand, CLE_WRITE_EN | ALE_COL_EN | ALE_ROW_EN,
		              COMMAND_WRITE_1, 0, 0, row_address);

		_data_array_out(nand, false, (uint8_t *)data, data_size, 0);
	}

	_send_cle_ale(nand, CLE_WRITE_EN | ALE_COL_EN,
	              COMMAND_RANDOM_IN, 0, ecc_start_addr, 0);

	/* Wait until the kernel of the PMECC is not busy */
	hsmc_pmecc_wait_ready();
	bytes_per_sector = pmecc_get_ecc_bytes() / nb_sectors_per_page;
	pmecc_sector_number = 1 << ((pmecc_get_page_size() >> 8) & 0x3);

	/* Read all ECC registers */
	for (pmecc_sector_index = 0; pmecc_sector_index < pmecc_sector_number; pmecc_sector_index++) {
		for (byte_index = 0; byte_index < bytes_per_sector; byte_index++)
			ecc_table[pmecc_sector_index * bytes_per_sector + byte_index] =
				pmecc[pmecc_sector_index][byte_index];
	}

	_data_array_out(nand, false, ecc_table,
			pmecc_sector_number * bytes_per_sector, 0);

	_send_cle_ale(nand, CLE_WRITE_EN, COMMAND_WRITE_2, 0, 0, 0);

	if (nand_is_nfc_enabled()) {
		if (!nand_is_nfc_sram_enabled())
			hsmc_nfc_wait_rb_busy();
	}

	if (_nand_wait_ready(nand)) {
		trace_error("write_page_pmecc: Failed writing.\r\n");
		error = NAND_ERROR_CANNOTWRITE;
	}

	return error;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Initializes a struct _nand_flash instance based on the given model.
 * If no model is provided, then the function tries to auto detect it.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param model  Pointer to the underlying NANDFLASH chip model. Can be 0.
 * \returns 0 if initialization is successful; otherwise returns
 * NAND_ERROR_UNKNOWNMODEL.
*/
uint8_t nand_raw_initialize(struct _nand_flash *nand,
		const struct _nand_flash_model *model)
{
	NAND_TRACE("nand_raw_initialize()\r\n");

	/* Reset */
	nand_raw_reset(nand);

	/* If model is not provided, autodetect it */
	if (!model) {
		NAND_TRACE("No model provided, trying autodetection ...\r\n");
		if (nand_model_find(nand_flash_model_list,
					nand_flash_model_list_size,
					nand_raw_read_id(nand), &nand->model)) {
			trace_error("nand_raw_initialize: Could not autodetect chip.\r\n");
			return NAND_ERROR_UNKNOWNMODEL;
		}
	} else
		/* Copy provided model */
		nand->model = *model;

	return 0;
}

/**
 * \brief Resets a NandFlash device.
 * \param nand  Pointer to a struct _nand_flash instance.
 */
void nand_raw_reset(const struct _nand_flash *nand)
{
	NAND_TRACE("nand_raw_reset()\r\n");

	_send_cle_ale(nand, 0, COMMAND_RESET, 0, 0, 0);
	_nand_wait_ready(nand);
}

/**
 * \brief Reads and returns the identifiers of a NandFlash chip.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \return id1|(id2<<8)|(id3<<16)|(id4<<24)
*/
uint32_t nand_raw_read_id(const struct _nand_flash *nand)
{
	uint32_t chip_id, chip_id2;

	NAND_TRACE("nand_raw_read_id()\r\n");

	//_send_cle_ale(nand, ALE_ROW_EN, COMMAND_READID, 0, 0, 0);
	nand_write_command(nand, COMMAND_READID);
	nand_write_address(nand, 0);
	chip_id  = nand_read_data(nand);
	chip_id |= nand_read_data(nand) << 8;
	chip_id |= nand_read_data(nand) << 16;
	chip_id |= nand_read_data(nand) << 24;
	chip_id2 = nand_read_data(nand);

	trace_info("CHIP ID %x %x %x %x %x\r\n",
			(unsigned)(chip_id & 0xFF),
			(unsigned)((chip_id & 0xFF00) >> 8),
			(unsigned)((chip_id & 0xFF0000) >> 16),
			(unsigned)((chip_id & 0xFF000000) >> 24),
			(unsigned)chip_id2);

	chip_id2 = chip_id2;

	return chip_id;
}

/**
 * \brief Erases the specified block of the device, retrying several time if it fails.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param block  Number of the physical block to erase.
 * \return 0 if successful; otherwise returns NAND_ERROR_BADBLOCK.
 */
uint8_t nand_raw_erase_block(const struct _nand_flash *nand, uint16_t block)
{
	uint8_t retry = NUMERASETRIES;

	NAND_TRACE("nand_raw_erase_block(B#%d)\r\n", block);

	while (retry > 0) {
		if (!_erase_block(nand, block)) {
			return 0;
		}
		retry--;
	}

	trace_error("nand_raw_erase_block: Failed to erase %d after %d tries\r\n",
			block, NUMERASETRIES);
	return NAND_ERROR_BADBLOCK;
}

/**
 * \brief Reads the data and/or the spare areas of a page of a NandFlash into the
 * provided buffers. If a buffer pointer is 0, the corresponding area is not
 * read.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param block  Number of the block where the page to read resides.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
uint8_t nand_raw_read_page(const struct _nand_flash *nand,
		uint16_t block, uint16_t page, void *data, void *spare)
{
	NAND_TRACE("nand_raw_read_page(B#%d:P#%d)\r\n", block, page);

	if (!nand_is_using_pmecc() || spare)
		return _read_page(nand, block, page, data, spare);

	if (nand_is_using_pmecc())
		return _read_page_with_pmecc(nand, block, page, data);

	return NAND_ERROR_ECC_NOT_COMPATIBLE;
}

/**
 * \brief Writes the data and/or the spare area of a page on a NandFlash chip. If one
 * of the buffer pointer is 0, the corresponding area is not written. Retries
 * several time if there is an error.
 * \param nand  Pointer to a struct _nand_flash instance.
 * \param block  Number of the block where the page to write resides.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \param spare  Buffer containing the spare area.
 * \return 0 if the write operation is successful; otherwise returns
 * NAND_ERROR_BADBLOCK.
 */
uint8_t nand_raw_write_page(const struct _nand_flash *nand,
		uint16_t block, uint16_t page, void *data, void *spare)
{
	NAND_TRACE("nand_raw_write_page(B#%d:P#%d)\r\n", block, page);

	if (!nand_is_using_pmecc() || spare)
		return _write_page(nand, block, page, data, spare);

	if (nand_is_using_pmecc())
		return _write_page_with_pmecc(nand, block, page, data);

	return NAND_ERROR_ECC_NOT_COMPATIBLE;
}
