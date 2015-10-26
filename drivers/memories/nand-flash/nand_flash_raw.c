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
#include "board.h"

#include "peripherals/hsmc.h"
#include "peripherals/pio.h"
#include "peripherals/pmecc.h"

#include "memories/nand-flash/nand_flash_api.h"
#include "memories/nand-flash/nand_flash_common.h"
#include "memories/nand-flash/nand_flash_raw.h"
#include "memories/nand-flash/nand_flash_dma.h"
#include "memories/nand-flash/nand_flash_model_list.h"

#include "trace.h"

#include <assert.h>
#include <string.h>

/*------------------------------------------------------------------------*/
/*        Local Definitions                                               */
/*------------------------------------------------------------------------*/

#define WRITE_COMMAND(raw, command) \
	{ *((volatile uint8_t*)raw->command_addr) = (uint8_t)command; }
#define WRITE_COMMAND16(raw, command) \
	{ *((volatile uint16_t*)raw->command_addr) = (uint16_t)command; }
#define WRITE_ADDRESS(raw, address) \
	{ *((volatile uint8_t*)raw->address_addr) = (uint8_t)address; }
#define WRITE_ADDRESS16(raw, address) \
	{ *((volatile uint16_t*)raw->address_addr) = (uint16_t)address; }
#define WRITE_DATA8(raw, data) \
	{ *((volatile uint8_t*)raw->data_addr) = (uint8_t)data; }
#define WRITE_DATA16(raw, data) \
	{ *((volatile uint16_t*)raw->data_addr) = (uint16_t)data; }
#define READ_DATA8(raw) \
	(*((volatile uint8_t*)raw->data_addr))
#define READ_DATA16(raw) \
	(*((volatile uint16_t*)raw->data_addr))

/*------------------------------------------------------------------------*/
/*        Local Functions                                                 */
/*------------------------------------------------------------------------*/

/**
 * \brief Sends the column address to the NandFlash chip.
 *
 * \param raw  Pointer to a RawNandFlash instance.
 * \param column_address  Column address to send.
 */
static void _write_column_address(
	const struct _raw_nand_flash *raw,
	uint16_t column_address)
{
	uint16_t page_data_size = nand_model_get_page_data_size(MODEL(raw));

	/* Check the data bus width of the NandFlash */
	if (nand_model_get_data_bus(MODEL(raw)) == 16) {
		/* Div 2 is because we address in word and not in byte */
		column_address >>= 1;
	}
	/* Send single column address byte for small block devices, or two column address bytes for large block devices*/
	while (page_data_size > 2) {
		if (nand_model_get_data_bus(MODEL(raw)) == 16) {
			WRITE_ADDRESS16(raw, column_address & 0xFF);
		} else {
			WRITE_ADDRESS(raw, column_address & 0xFF);
		}
		page_data_size >>= 8;
		column_address >>= 8;
	}
}

/**
 * \brief Sends the row address to the NandFlash chip.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param row_address  Row address to send.
 */
static void _write_row_address(
	const struct _raw_nand_flash *raw,
	uint32_t row_address)
{
	uint32_t num_pages = nand_model_get_device_size_in_pages(MODEL(raw));

	while (num_pages > 0) {
		if (nand_model_get_data_bus(MODEL(raw)) == 16) {
			WRITE_ADDRESS16(raw, row_address & 0xFF);
		} else {
			WRITE_ADDRESS(raw, row_address & 0xFF);
		}
		num_pages >>= 8;
		row_address >>= 8;
	}
}

/**
 * \brief Translates the given column and row address into first and other (1-4) address
 *  cycles. The resulting values are stored in the provided variables if they are not null.
 * \param column_address  Column address to translate.
 * \param row_address  Row address to translate.
 * \param p_address_cycle0    First address cycle.
 * \param p_address_cycle_1234 Four address cycles.
 * \param row_only           Only ROW address is used.
 * \return Number of address cycles converted.
 */
static uint32_t _nfc_translate_address(
	const struct _raw_nand_flash *raw,
	uint16_t column_address,
	uint32_t row_address,
	uint32_t *p_address_cycle0,
	uint32_t *p_address_cycle_1234,
	uint8_t row_only,
	uint8_t col_only
	)
{
	uint16_t max_data_size =
		nand_model_get_page_data_size(MODEL(raw)) +
		nand_model_get_page_spare_size(MODEL(raw)) - 1;
	uint32_t max_page_num  =
		nand_model_get_device_size_in_pages(MODEL(raw)) - 1;
	uint8_t num_cycles = 0;
	uint32_t address_cycle0 = 0;
	uint32_t address_cycle1234 = 0;
	uint8_t cycle_bytes[8], cycle_idx, byte_position;

	/* Check the data bus width of the NandFlash */
	if (nand_model_get_data_bus(MODEL(raw)) == 16) {
		/* Div 2 is because we address in word and not in byte */
		column_address >>= 1;
	}
	/* Convert column address */
	if (!row_only) {
		/* Send single column address byte for small block devices,
		   or two column address bytes for large block devices */
		while (max_data_size > 2) {
			cycle_bytes[num_cycles++] = column_address & 0xFF;
			max_data_size >>= 8;
			column_address >>= 8;
		}
	}
	if (!col_only) {
		/* Convert row address */
		while (max_page_num > 0) {
			cycle_bytes[num_cycles++] = row_address & 0xFF;
			max_page_num >>= 8;
			row_address >>= 8;
		}
	}
	/* build address_cycle0 & address_cycle1234 */
	cycle_idx = 0;
	/* If more than 4 cycles, address_cycle0 is used */
	if (num_cycles > 4) {
		for (byte_position = 0; cycle_idx < num_cycles - 4; cycle_idx++) {
			address_cycle0 += cycle_bytes[cycle_idx] << byte_position;
			byte_position += 8;
		}
	}
	/* address_cycle1234 */
	for (byte_position = 0; cycle_idx < num_cycles; cycle_idx++) {
		address_cycle1234 += cycle_bytes[cycle_idx] << byte_position;
		byte_position += 8;
	}

	/* Store values*/
	if (p_address_cycle0)
		*p_address_cycle0 = address_cycle0;
	if (p_address_cycle_1234)
		*p_address_cycle_1234 = address_cycle1234;
	return num_cycles;
}

/**
 * \brief NAND flash send ALE CLE.
 * \param raw  Pointer to a RawNandFlash instance.
 * \param mode SMC ALE CLE mode parameter.
 * \param cmd1 First command to be sent.
 * \param cmd2 Second command to be sent.
 * \param colAddress Column address.
 * \param row_address Row address.
 */

static void _send_cle_ale(
	 const struct _raw_nand_flash *raw,
	 uint8_t mode,
	 uint32_t cmd1,
	 uint32_t cmd2,
	 uint32_t colAddress,
	 uint32_t row_address)
{
	uint32_t nfc_command;
	uint32_t nfc_data;
	uint32_t nfc_rw;
	uint32_t cycles;
	uint32_t address_cycle0 = 0;
	uint32_t address_cycle1234 = 0;

	/* Issue CLE and ALE through EBI */
	if (!nand_api_nfc_enabed()) {
		WRITE_COMMAND(raw, cmd1);
		if ((mode & ALE_COL_EN) == ALE_COL_EN)
			_write_column_address(raw, colAddress);
		if ((mode & ALE_ROW_EN) == ALE_ROW_EN)
			_write_row_address(raw, row_address);
		/* When set to true, the CMD2 field is issued after the address cycle.*/
		if ((mode & CLE_VCMD2_EN) == CLE_VCMD2_EN)
			WRITE_COMMAND(raw, cmd2);
	} else { /* Issue CLE and ALE using NFC */
		if ((mode & CLE_WRITE_EN) == CLE_WRITE_EN)
			nfc_rw = NFCADDR_CMD_NFCWR;
		else
			nfc_rw = NFCADDR_CMD_NFCRD;
		if (((mode & CLE_DATA_EN) == CLE_DATA_EN)
				&& nand_api_nfc_sram_enabed())
			nfc_data = NFCADDR_CMD_DATAEN;
		else
			nfc_data = NFCADDR_CMD_DATADIS;
		if (((mode & ALE_COL_EN) == ALE_COL_EN) ||
			((mode & ALE_ROW_EN) == ALE_ROW_EN)) {
			cycles = _nfc_translate_address(raw,
									   colAddress,
									   row_address,
									   &address_cycle0,
									   &address_cycle1234,
									   (((mode & ALE_COL_EN) == 0) &&
									   ((mode & ALE_ROW_EN) == ALE_ROW_EN)) ? 1 : 0,
									   (((mode & ALE_COL_EN) == ALE_COL_EN) &&
									   ((mode & ALE_ROW_EN) == 0)) ? 1 : 0);
		} else
			cycles = 0;
		nfc_command = (nfc_rw |
				 nfc_data |
				 NFCADDR_CMD_CSID_3 |
				 cycles << 19 |
				 (((mode & CLE_VCMD2_EN) == CLE_VCMD2_EN) ? NFCADDR_CMD_VCMD2 : 0) |
				 (cmd1 << 2) |
				 (cmd2 << 10));
		hsmc_nfc_send_cmd( nfc_command, address_cycle1234, address_cycle0);
	}
}

/**
 * \brief Transfer data from NAND to the provided buffer.
 * \param bus_width  NAND flash data bus width
 * \param host_sram  Set 1 to enable NFC Host SRAM
 * \param buffer  Buffer where the data will be stored or sent.
 * \param size  Number of bytes that will be read
 */
static void _data_array_in(
	uint8_t bus_width,
	uint8_t host_sram,
	uint8_t *buffer,
	uint32_t size )
{
	uint32_t address;
	uint32_t i;
	if (host_sram) {
		address = NFC_RAM_ADDR;
		hsmc_nfc_wait_xfr_done();
	} else
		address = BOARD_NF_DATA_ADDR;

	/* Check the data bus width of the NandFlash */
	if (nand_api_dma_enabed())
		nand_dma_read(address, (uint32_t)buffer, size);
	/* Transfer without DMA */
	else {
		/* Check the data bus width of the NandFlash */
		if (bus_width == 16 && !host_sram) {
			uint16_t *p_buff16 = (uint16_t *)((void *)buffer);
			volatile uint16_t * pDataAddress16 = (volatile uint16_t *)address;
			size = (size + 1) >> 1;
			if (host_sram){
				for(i = size; i != 0; i--) {
					*(p_buff16++) = *pDataAddress16++;
				}
			} else {
				for(i = size; i != 0; i--) {
					*(p_buff16++) = *pDataAddress16;
				}
			}
		} else {
			uint8_t *pbuff8 = buffer;
			volatile uint8_t * pDataAddress8 = (volatile uint8_t *)address;
			if (host_sram) {
				for (i = size; i != 0; i--)
					*(pbuff8++) = *pDataAddress8++;
			} else {
				for (i = size; i != 0; i--)
					*(pbuff8++) = *pDataAddress8;
			}
		}
	}
}

/**
 * \brief Transfer data to NANDFLASH from the provided buffer.
 * \param bus_width  NANDFLASH data bus width
 * \param host_sram  Set 1 to enable NFC Host SRAM
 * \param buffer  Buffer where the data will be stored or sent.
 * \param size  Number of bytes that will be read
 * \param offset Offset in bytes.
 */

static void _data_array_out(
	uint8_t bus_width,
	uint8_t host_sram,
	uint8_t *buffer,
	uint32_t size,
	uint32_t offset)
{
	uint32_t address;
	uint32_t i;

	if (host_sram) {
		address = NFC_RAM_ADDR;
	} else {
		address = BOARD_NF_DATA_ADDR;
	}
	address += offset;
	/* Check the data bus width of the NandFlash */
	if (nand_api_dma_enabed())
		nand_dma_write((uint32_t)buffer, address, size);
	/* Transfer without DMA */
	else {
		/* Check the data bus width of the NandFlash */
		if (bus_width == 16 && !host_sram) {
			uint16_t *p_buff16 = (uint16_t *)(void*) buffer;
			volatile uint16_t * pDataAddress16 = (volatile uint16_t *)address;
			size = (size + 1) >> 1;
			if (host_sram){
				for (i = size; i != 0; i--)
					*pDataAddress16++ = *(p_buff16++);
			} else {
				for (i = size; i != 0; i--)
					*pDataAddress16 = *(p_buff16++);
			}
		} else {
			uint8_t *pbuff8 = buffer;
			volatile uint8_t * pDataAddress8 = (volatile uint8_t *)address;
			if (host_sram){
				for (i = size; i != 0; i--)
					*pDataAddress8++ = *(pbuff8++);
			} else {
				for (i = size; i != 0; i--)
					*pDataAddress8 = *(pbuff8++);
			}
		}
	}
}

/**
 * \brief NAND Flash devices have an 8-bit status register that the software can read during
    device operation..
 * \param raw  Pointer to a RawNandFlash instance.
 * \param status status to be checked.
 */
static uint8_t _status_ready_pass(const struct _raw_nand_flash *raw)
{
	uint8_t ucStatus;
	uint16_t nReadStatusCount = 0;
	_send_cle_ale(raw, 0, COMMAND_STATUS, 0, 0, 0);
	while (nReadStatusCount < READ_STATUS_TIMEOUT) {
		/* Read status byte */
		ucStatus = READ_DATA8(raw);
		/* Check status */
		/* If status bit 6 = 1 device is ready */
		if ((ucStatus & STATUS_BIT_6) == STATUS_BIT_6) {
			/* If status bit 0 = 0 the last operation was successful */
			if ((ucStatus & STATUS_BIT_0) == 0)
				return 0;
			else
				return NAND_ERROR_STATUS;
		}
		nReadStatusCount++;
	}
	return NAND_ERROR_STATUS;
}

/**
 * \brief Waiting for the completion of a page program, erase and random read completion.
 * \param raw  Pointer to a RawNandFlash instance.
 */
static uint8_t _nand_wait_ready(const struct _raw_nand_flash *raw)
{
	if (raw->pin_ready_busy.mask)
		while (!pio_get(&(raw->pin_ready_busy)));
	else
		return _status_ready_pass(raw);
	return 0;
}

/**
 * \brief Erases the specified block of the device. Returns 0 if the operation was
 * successful; otherwise returns an error code.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \param block  Number of the physical block to erase.
 */
static uint8_t _erase_block(
	const struct _raw_nand_flash *raw,
	uint16_t block)
{
	uint32_t row_address;
	trace_debug("_erase_block(%d)\r\n", block);
	/* Calculate address used for erase */
	row_address = block * nand_model_get_block_size_in_pages(MODEL(raw));
	_send_cle_ale(raw, CLE_VCMD2_EN | ALE_ROW_EN,
					COMMAND_ERASE_1, COMMAND_ERASE_2, 0, row_address);

	if (_nand_wait_ready(raw)) {
		trace_error( "_erase_block: Could not erase block %d.\n\r", block);
		return NAND_ERROR_CANNOTERASE;
	}
	return 0;
}

/**
 * \brief Reads the data and/or the spare areas of a page of a NandFlash into the
 * provided buffers. If a buffer pointer is 0, the corresponding area is not
 * read.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \param block  Number of the block where the page to read resides.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
static uint8_t _read_page(
	const struct _raw_nand_flash *raw,
	uint16_t block,
	uint16_t page,
	void *data,
	void *spare)
{
	uint32_t page_data_size = nand_model_get_page_data_size(MODEL(raw));
	uint32_t page_spare_size = nand_model_get_page_spare_size(MODEL(raw));
	uint32_t bus_width = nand_model_get_data_bus(MODEL(raw));
	uint32_t col_address, row_address, smc_ecc_page_size;
	uint32_t smc_mode;
	uint32_t smc_trans_type = 0;

	if (nand_api_nfc_enabed()) {
		switch (page_data_size) {
		case 512:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS512;
			break;
		case 1024:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS1024;
			break;
		case 2048:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS2048;
			break;
		case 4096:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS4096;
			break;
		default:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS2048;
			break;
		}
		hsmc_nfc_configure(HSMC_CFG_NFCSPARESIZE((page_spare_size-1) >> 2) |
								HSMC_CFG_DTOCYC(0xF) |
								HSMC_CFG_DTOMUL_X1048576 |
								HSMC_CFG_RBEDGE |
								0 << 8 |
								smc_ecc_page_size);
	}
	/* nand_raw_read_page: At least one area must be read */
	assert(data || spare);
	trace_debug("RdPg(B#%d:P#%d)\r\n", block, page);

	/* Calculate actual address of the page */
	row_address = block * nand_model_get_block_size_in_pages(MODEL(raw)) + page;
	if (data)
		col_address = 0;
	else
		col_address = page_data_size;
	if (nand_api_nfc_sram_enabed()) {
		smc_trans_type |= SMC_TRANS_HOST_EN;
		smc_mode = ALE_COL_EN | ALE_ROW_EN | CLE_VCMD2_EN | CLE_DATA_EN;
		_send_cle_ale(raw, smc_mode, COMMAND_READ_1,
					COMMAND_READ_2, col_address, row_address);
	} else {
		smc_mode = ALE_COL_EN | ALE_ROW_EN | CLE_VCMD2_EN;
		_send_cle_ale(raw, smc_mode, COMMAND_READ_1,
					COMMAND_READ_2, col_address, row_address);
	}

	if (!nand_api_nfc_enabed()) {
		/* Wait for the nand to be ready */
		_status_ready_pass(raw);
		_send_cle_ale(raw, CLE_DATA_EN, COMMAND_READ_1, 0, 0, 0);
	} else {
		if (!nand_api_nfc_sram_enabed())
			hsmc_nfc_wait_rb_busy();
	}
	if (nand_api_nfc_sram_enabed())
		hsmc_nfc_wait_xfr_done();

	/* Read data area if needed */
	if (data) {
		_data_array_in(bus_width, smc_trans_type,
					(uint8_t *)data, page_data_size);
		if (spare)
			_data_array_in(bus_width, smc_trans_type,
					(uint8_t *)spare, page_spare_size);
	} else {
		/* Read spare area only */
		_data_array_in(bus_width, smc_trans_type,
					(uint8_t *)spare, page_spare_size);
	}
	return 0;
}

/**
 * \brief Reads the data and/or the spare areas of a page of a NandFlash into the
 * provided buffers. If a buffer pointer is 0, the corresponding area is not
 * read.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \param block  Number of the block where the page to read resides.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
static uint8_t _read_page_with_pmecc(
	const struct _raw_nand_flash *raw,
	uint16_t block,
	uint16_t page,
	void *data,
	void *spare)
{
	uint32_t page_data_size = nand_model_get_page_data_size(MODEL(raw));
	uint32_t page_spare_size = nand_model_get_page_spare_size(MODEL(raw));
	uint32_t row_address, smc_ecc_page_size;
	uint32_t smc_mode;
	uint32_t smc_trans_type = 0;
	if (nand_api_nfc_enabed()) {
		switch (page_data_size) {
		case 512:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS512;
			break;
		case 1024:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS1024;
			break;
		case 2048:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS2048;
			break;
		case 4096:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS4096;
			break;
		default:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS2048;
			break;
		}
		hsmc_nfc_configure(HSMC_CFG_NFCSPARESIZE((page_spare_size - 1) >> 2) |
							HSMC_CFG_DTOCYC(0xF) |
							HSMC_CFG_DTOMUL_X1048576 |
							HSMC_CFG_RBEDGE |
							0 << 8 |
							1 << 9 |
							smc_ecc_page_size);
	}
	assert ( data || spare); /* nand_raw_read_page: At least one area must be read */
	trace_debug("RdPg(B#%d:P#%d)\r\n", block, page);

	/* Calculate actual address of the page */
	row_address = block * nand_model_get_block_size_in_pages(MODEL(raw)) + page;
	if (nand_api_nfc_enabed() && nand_api_nfc_sram_enabed())
		smc_trans_type |= SMC_TRANS_HOST_EN;
	hsmc_pmecc_reset();
	hsmc_pmecc_enable();
	if (!hsmc_pmecc_auto_apare_en())
		hsmc_pmecc_auto_enable();
	if(nand_api_nfc_sram_enabed()){
		smc_trans_type |= SMC_TRANS_HOST_EN;
		smc_mode = ALE_COL_EN | ALE_ROW_EN | CLE_VCMD2_EN | CLE_DATA_EN;
		hsmc_pmecc_data_phase();
		_send_cle_ale(raw, smc_mode, COMMAND_READ_1, COMMAND_READ_2, 0, row_address);
	} else {
		smc_mode = ALE_COL_EN | ALE_ROW_EN | CLE_VCMD2_EN;
		_send_cle_ale(raw, smc_mode, COMMAND_READ_1, COMMAND_READ_2, 0, row_address);
	}
	if (!nand_api_nfc_enabed()){
		/* Wait for the nand to be ready */
		_nand_wait_ready(raw );
		_send_cle_ale(raw, 0, COMMAND_READ_1, 0, 0, 0);
	} else {
		if (!nand_api_nfc_sram_enabed())
			hsmc_nfc_wait_rb_busy();
	}
	/* Reset the ECC module*/
	hsmc_pmecc_or_reset();
	/* Start a Data Phase */
	hsmc_pmecc_data_phase();
	_data_array_in(nand_model_get_data_bus(MODEL(raw)),
					smc_trans_type,
					(uint8_t *)data,
					page_data_size + (pmecc_get_ecc_end_address()));
	/* Wait until the kernel of the PMECC is not busy */
	hsmc_pmecc_wait_ready();
	hsmc_pmecc_auto_disable();
	return 0;
}

/**
 * \brief Writes the data and/or the spare area of a page on a NandFlash chip. If one
 * of the buffer pointer is 0, the corresponding area is not written.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \param block  Number of the block where the page to write resides.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \return 0 if the write operation is successful; otherwise returns 1.
*/

static uint8_t _write_page_no_ecc(
	const struct _raw_nand_flash *raw,
	uint16_t block,
	uint16_t page,
	void *data,
	void *spare)
{

	uint8_t error = 0;
	uint32_t page_data_size = nand_model_get_page_data_size(MODEL(raw));
	uint32_t page_spare_size = nand_model_get_page_spare_size(MODEL(raw));
	uint32_t row_address,smc_ecc_page_size;
	uint32_t bus_width = nand_model_get_data_bus(MODEL(raw));

	if (nand_api_nfc_enabed()) {
		switch (page_data_size) {
		case 512:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS512;
			break;
		case 1024:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS1024;
			break;
		case 2048:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS2048;
			break;
		case 4096:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS4096;
			break;
		default:
			smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS2048;
			break;
		}
		hsmc_nfc_configure(HSMC_CFG_NFCSPARESIZE((page_spare_size - 1) >> 2) |
							HSMC_CFG_DTOCYC(0xF) |
							HSMC_CFG_DTOMUL_X1048576 |
							HSMC_CFG_RBEDGE |
							(spare ? (1 << 8) : 0) |
							smc_ecc_page_size);
	}
	trace_debug("write_page_no_ecc(B#%d:P#%d)\r\n", block, page);
	/* Calculate physical address of the page */
	row_address = block * nand_model_get_block_size_in_pages(MODEL(raw)) + page;

	if (nand_api_nfc_enabed() && nand_api_nfc_sram_enabed() && data) {
		_data_array_out(bus_width, SMC_TRANS_HOST_EN,
		(uint8_t *)data, page_data_size, 0);
	}
	if (nand_api_nfc_enabed() && nand_api_nfc_sram_enabed() && spare && data) {
		_data_array_out(bus_width, SMC_TRANS_HOST_EN,
		(uint8_t *)spare, page_spare_size, page_data_size);
	}
	if (nand_api_nfc_enabed() && nand_api_nfc_sram_enabed() && spare && !data) {
		_data_array_out(bus_width, SMC_TRANS_HOST_EN,
					(uint8_t *)spare, page_spare_size, 0);
	}
	/* Write data area if needed */
	if (data) {
		/* Start a Data Phase */
		if (nand_api_nfc_enabed() && nand_api_nfc_sram_enabed()) {
			_send_cle_ale(raw, CLE_WRITE_EN | ALE_COL_EN | ALE_ROW_EN |
			CLE_DATA_EN, COMMAND_WRITE_1, 0, 0, row_address);
			hsmc_nfc_wait_xfr_done();
		} else
			_send_cle_ale(raw, CLE_WRITE_EN | ALE_COL_EN | ALE_ROW_EN,
						COMMAND_WRITE_1, 0, 0, row_address);
		if (!nand_api_nfc_sram_enabed())
			_data_array_out(bus_width, 0, (uint8_t *)data, page_data_size, 0);
		if (!nand_api_nfc_sram_enabed() && spare && data)
			_data_array_out(bus_width, 0, (uint8_t *)spare,
					page_spare_size, page_data_size);
		if (!nand_api_nfc_sram_enabed() && spare && !data)
			_data_array_out(bus_width, 0, (uint8_t *)spare, page_spare_size, 0);
		_send_cle_ale(raw, CLE_WRITE_EN, COMMAND_WRITE_2, 0, 0, 0);

		hsmc_nfc_wait_rb_busy();
		if (_status_ready_pass(raw)) {
			trace_error("write_page_no_ecc: Failed writing data area.\n\r");
			error = NAND_ERROR_CANNOTWRITE;
		}
		/* Write spare area alone if needed */
		if (spare && !data) {
			_send_cle_ale(raw, CLE_WRITE_EN | ALE_COL_EN | ALE_ROW_EN,
				COMMAND_WRITE_1, 0, page_data_size, row_address);
			_data_array_out(bus_width, 0, (uint8_t *)spare, page_spare_size, 0);
			_send_cle_ale(raw, CLE_WRITE_EN, COMMAND_WRITE_2,0, 0, 0);

			if (_nand_wait_ready(raw)) {
				trace_error("write_page_no_ecc: Failed writing data area.\n\r");
				error = NAND_ERROR_CANNOTWRITE;
			}
		}
	}
	return error;
}

/**
 * \brief Writes the data and/or the spare area of a page on a NandFlash chip. If one
 * of the buffer pointer is 0, the corresponding area is not written.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \param block  Number of the block where the page to write resides.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \return 0 if the write operation is successful; otherwise returns 1.
*/
static uint8_t _write_page_with_pmecc(
	const struct _raw_nand_flash *raw,
	uint16_t block,
	uint16_t page,
	void *data,
	void *spare)
{
	uint8_t ecc_table[NAND_MAX_PMECC_BYTE_SIZE];
	uint8_t error = 0;
	uint32_t page_data_size = nand_model_get_page_data_size(MODEL(raw));
	uint32_t page_spare_size = nand_model_get_page_spare_size(MODEL(raw));
	uint32_t row_address;
	uint32_t smc_ecc_page_size;
	uint32_t ecc_start_addr;
	uint32_t bytes_per_sector;
	uint32_t pmecc_sector_number;
	uint32_t pmecc_sector_index;
	uint32_t byte_index;
	uint8_t *pmecc[8];
	uint8_t i;
	uint8_t nb_sectors_per_page;
	uint32_t bus_width = nand_model_get_data_bus(MODEL(raw));

	if (nand_api_nfc_enabed()) {
		switch (page_data_size) {
		case 512:  smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS512;  break;
		case 1024: smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS1024; break;
		case 2048: smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS2048; break;
		case 4096: smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS4096; break;
		default : smc_ecc_page_size = HSMC_CFG_PAGESIZE_PS2048; break;
		}
		hsmc_nfc_configure(HSMC_CFG_NFCSPARESIZE((page_spare_size - 1) >> 2) |
							HSMC_CFG_DTOCYC(0xF) |
							HSMC_CFG_DTOMUL_X1048576 |
							HSMC_CFG_RBEDGE |
							(spare ? (1 << 8) : 0) |
							smc_ecc_page_size);
	}
	ecc_start_addr = page_data_size + pmecc_get_ecc_start_address();

	trace_debug("write_page_pmecc(B#%d:P#%d)\r\n", block, page);
	/* Calculate physical address of the page */
	row_address = block * nand_model_get_block_size_in_pages(MODEL(raw)) + page;

	if(nand_api_nfc_enabed() && nand_api_nfc_sram_enabed() && data)
		_data_array_out(bus_width, SMC_TRANS_HOST_EN, (uint8_t *)data, page_data_size, 0);
	/* Write data area if needed */
	switch (pmecc_get_page_size()) {
		case HSMC_PMECCFG_PAGESIZE_PAGESIZE_1SEC: nb_sectors_per_page = 1; break;
		case HSMC_PMECCFG_PAGESIZE_PAGESIZE_2SEC: nb_sectors_per_page = 2; break;
		case HSMC_PMECCFG_PAGESIZE_PAGESIZE_4SEC: nb_sectors_per_page = 4; break;
		case HSMC_PMECCFG_PAGESIZE_PAGESIZE_8SEC: nb_sectors_per_page = 8; break;
		default: nb_sectors_per_page = 1; break;
	}
	hsmc_pmecc_reset();
	hsmc_pmecc_enable();
	for (i = 0; i < 8; i++)
		pmecc[i] = (uint8_t *)(&hsmc_pmecc(i));
	/* Start a Data Phase */
	hsmc_pmecc_data_phase();
	hsmc_pmecc_enable_write();
	if (nand_api_nfc_enabed() && nand_api_nfc_sram_enabed()) {
		_send_cle_ale(raw, CLE_WRITE_EN | ALE_COL_EN | ALE_ROW_EN | CLE_DATA_EN, COMMAND_WRITE_1, 0, 0, row_address);
		hsmc_nfc_wait_xfr_done();
	} else {
		_send_cle_ale(raw, CLE_WRITE_EN | ALE_COL_EN |ALE_ROW_EN, COMMAND_WRITE_1, 0, 0, row_address);
	}
	if (!nand_api_nfc_sram_enabed())
		_data_array_out(bus_width, 0, (uint8_t *)data, page_data_size, 0);
	_send_cle_ale(raw, CLE_WRITE_EN | ALE_COL_EN, COMMAND_RANDOM_IN, 0, ecc_start_addr, 0);
	/* Wait until the kernel of the PMECC is not busy */
	hsmc_pmecc_wait_ready();
	bytes_per_sector = (pmecc_get_ecc_bytes()) / nb_sectors_per_page;
	pmecc_sector_number = 1 << ((pmecc_get_page_size() >> 8) & 0x3);
	/* Read all ECC registers */
	for (pmecc_sector_index = 0;
			pmecc_sector_index < pmecc_sector_number;
			pmecc_sector_index++) {
		for (byte_index = 0; byte_index < bytes_per_sector; byte_index++)
			ecc_table[pmecc_sector_index * bytes_per_sector + byte_index] = pmecc[pmecc_sector_index][byte_index];
	}

	_data_array_out(bus_width, 0, (uint8_t *)(uint8_t *) ecc_table,
					pmecc_sector_number * bytes_per_sector, 0);
	_send_cle_ale(raw, CLE_WRITE_EN, COMMAND_WRITE_2, 0, 0, 0);

	if (nand_api_nfc_enabed()) {
		if (!nand_api_nfc_sram_enabed())
			hsmc_nfc_wait_rb_busy();
	}
	if (_nand_wait_ready(raw)) {
		trace_error("write_page_pmecc: Failed writing data area.\n\r");
		error = NAND_ERROR_CANNOTWRITE;
	}
	return error;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

 /**
 * \brief Initializes a _raw_nand_flash instance based on the given model and physical
 * interface. If no model is provided, then the function tries to auto detect it.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \param model  Pointer to the underlying NANDFLASH chip model. Can be 0.
 * \param command_addr  Address at which commands are sent.
 * \param address_addr  Address at which addresses are sent.
 * \param data_addr  Address at which data is sent.
 * \param pin_chip_enable  Pin controlling the CE signal of the NandFlash.
 * \param pin_ready_busy  Pin used to monitor the ready/busy signal of the NANDFLASH.
 * \returns 0 if initialization is successful; otherwise returns
 * NAND_ERROR_UNKNOWNMODEL.
*/
uint8_t nand_raw_initialize(
	struct _raw_nand_flash *raw,
	const struct _nand_flash_model *model,
	uint32_t command_addr,
	uint32_t address_addr,
	uint32_t data_addr,
	const struct _pin *pin_chip_enable,
	const struct _pin *pin_ready_busy)
{
	trace_debug("nand_raw_initialize()\n\r");
	/* Initialize fields */
	raw->command_addr = command_addr;
	raw->address_addr = address_addr;
	raw->data_addr = data_addr;
	if (pin_chip_enable)
		raw->pin_chip_enable = *pin_chip_enable;
	else
		memset(&raw->pin_chip_enable, 0, sizeof(raw->pin_chip_enable));
	if (pin_ready_busy)
		raw->pin_ready_busy = *pin_ready_busy;
	else
		memset(&raw->pin_ready_busy, 0, sizeof(raw->pin_ready_busy));

	/* Reset */
	nand_raw_reset(raw);

	/* If model is not provided, autodetect it */
	if (!model) {
		trace_debug("No model provided, trying autodetection ...\n\r");
		if (nand_model_find(nand_flash_model_list,
							NANDFLASH_MODEL_LIST_SIZE,
							nand_raw_read_id(raw),
							&(raw->model))) {
			trace_error(
					  "nand_raw_initialize: Could not autodetect chip.\n\r");
			return NAND_ERROR_UNKNOWNMODEL;
		}
	} else
		/* Copy provided model */
		raw->model = *model;
	return 0;
}

/**
 * \brief Resets a NandFlash device.
 * \param raw  Pointer to a _raw_nand_flash instance.
 */
void nand_raw_reset(const struct _raw_nand_flash *raw)
{
	trace_debug("nand_raw_reset()\n\r");
	_send_cle_ale(raw, 0, COMMAND_RESET, 0, 0, 0);
	_nand_wait_ready(raw);
}

/**
 * \brief Reads and returns the identifiers of a NandFlash chip.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \return id1|(id2<<8)|(id3<<16)|(id4<<24)
*/
uint32_t nand_raw_read_id(const struct _raw_nand_flash *raw)
{
	uint32_t chip_id, chip_id2;
	trace_debug("nand_raw_read_id()\n\r");
	//_send_cle_ale(raw, ALE_ROW_EN, COMMAND_READID, 0, 0, 0);
	WRITE_COMMAND(raw, COMMAND_READID);
	WRITE_ADDRESS(raw, 0);
	chip_id  = READ_DATA8(raw);
	chip_id |= READ_DATA8(raw) << 8;
	chip_id |= READ_DATA8(raw) << 16;
	chip_id |= READ_DATA8(raw) << 24;
	chip_id2  = READ_DATA8(raw);
	trace_info("CHIP ID %x %x %x %x %x\n\r",
	(unsigned int)(chip_id & 0xFF),
	(unsigned int)((chip_id & 0xFF00)>>8),
	(unsigned int)((chip_id & 0xFF0000) >> 16),
	(unsigned int)((chip_id & 0xFF000000) >> 24),
	(unsigned int) chip_id2);
	chip_id2 = chip_id2;
	return chip_id;
}

/**
 * \brief Erases the specified block of the device, retrying several time if it fails.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \param block  Number of the physical block to erase.
 * \return 0 if successful; otherwise returns NAND_ERROR_BADBLOCK.
 */
uint8_t nand_raw_erase_block(
	const struct _raw_nand_flash *raw,
	uint16_t block)
{
	uint8_t retry = NUMERASETRIES;
	trace_debug("nand_raw_erase_block(B#%d)\n\r", block);
	while (retry > 0) {
		if (!_erase_block(raw, block)) {
			return 0;
		}
		retry--;
	}
	trace_error("nand_raw_erase_block: Failed to erase %d after %d tries\n\r", block, NUMERASETRIES);
	return NAND_ERROR_BADBLOCK;
}

/**
 * \brief Reads the data and/or the spare areas of a page of a NandFlash into the
 * provided buffers. If a buffer pointer is 0, the corresponding area is not
 * read.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \param block  Number of the block where the page to read resides.
 * \param page  Number of the page to read inside the given block.
 * \param data  Buffer where the data area will be stored.
 * \param spare  Buffer where the spare area will be stored.
 * \return 0 if the operation has been successful; otherwise returns 1.
 */
uint8_t nand_raw_read_page(
	const struct _raw_nand_flash *raw,
	uint16_t block,
	uint16_t page,
	void *data,
	void *spare)
{
	if (!nand_api_use_pmecc() || spare)
		return _read_page( raw, block, page, data, spare);
	if (nand_api_use_pmecc())
		return _read_page_with_pmecc( raw, block, page, data,0);
	return NAND_ERROR_ECC_NOT_COMPATIBLE;
}

/**
 * \brief Writes the data and/or the spare area of a page on a NandFlash chip. If one
 * of the buffer pointer is 0, the corresponding area is not written. Retries
 * several time if there is an error.
 * \param raw  Pointer to a _raw_nand_flash instance.
 * \param block  Number of the block where the page to write resides.
 * \param page  Number of the page to write inside the given block.
 * \param data  Buffer containing the data area.
 * \param spare  Buffer containing the spare area.
 * \return 0 if the write operation is successful; otherwise returns
 * NAND_ERROR_BADBLOCK.
 */
uint8_t nand_raw_write_page (
	const struct _raw_nand_flash *raw,
	uint16_t block,
	uint16_t page,
	void *data,
	void *spare)
{
	trace_debug("nand_raw_write_page(B#%d:P#%d)\r\n", block, page);
	if (!nand_api_use_pmecc())
		return _write_page_no_ecc(raw, block, page, data, spare );
	if (nand_api_use_pmecc())
		return _write_page_with_pmecc(raw, block, page, data, spare );
	return NAND_ERROR_ECC_NOT_COMPATIBLE;
}
