/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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

#include "applet.h"
#include "board.h"
#include "chip.h"
#include "trace.h"
#include "intmath.h"

#include "gpio/pio.h"
#include "nvm/nand/pmecc.h"
#include "nvm/nand/pmecc_gf_1024.h"
#include "nvm/nand/pmecc_gf_512.h"
#include "extram/smc.h"

#include "nvm/nand/nand_flash.h"
#include "nvm/nand/nand_flash_skip_block.h"
#include "nvm/nand/nand_flash_spare_scheme.h"
#include "nvm/nand/nand_flash_model_list.h"
#include "nvm/nand/nand_flash_model.h"
#include "nvm/nand/nand_flash_ecc.h"
#include "nvm/nand/nand_flash_onfi.h"
#include "nvm/nand/nand_flash_dma.h"
#include "nvm/nand/nand_flash_raw.h"

#include "misc/console.h"

#include "pin_defs.h"

#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#if !defined(CONFIG_SOC_SAMA5D2) && \
    !defined(CONFIG_SOC_SAMA5D3) && \
    !defined(CONFIG_SOC_SAMA5D4) && \
    !defined(CONFIG_SOC_SAM9XX5)
#error Unsupported SOC!
#endif

#define NAND_HEADER_KEY  (0x0cu)

/* Header inserted at beginning of NAND flash.
 * Used by ROM-code to know how to configure NAND & PMECC */
union _nand_header
{
	uint32_t uint32_value;
	struct {
		uint32_t use_pmecc            : 1;
		uint32_t nb_sector_per_page   : 3; /* Number of Sectors per Page (0..3) */
		uint32_t spare_size           : 9; /* size of spare zone in bytes */
		uint32_t ecc_bit_req          : 3; /* Number of ECC Bits Required (0..5) */
		uint32_t sector_size          : 2; /* 0 for 512 bytes, 1 for 1024 bytes per sector, other val for future use */
		uint32_t ecc_offset           : 9; /* offset of the first ecc byte in spare zone */
		uint32_t reserved             : 1;
		uint32_t key                  : 4;
	} bitfield;
};

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static uint8_t *buffer;
static uint32_t buffer_size;

static uint32_t nand_header;
static struct _nand_flash nand;
static uint32_t page_size;
static uint32_t block_size;

static uint8_t ecc_bit_req_2_tt[] = {
	2, 4, 8, 12, 24, 32
};

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static bool configure_instance_pio(uint32_t ioset)
{
	int i;
	for (i = 0; i < num_nandflash_pin_defs; i++) {
		const struct nandflash_pin_definition* def = &nandflash_pin_defs[i];
		if (def->ioset == ioset) {
			pio_configure(def->pins, def->num_pins);
			return true;
		}
	}
	return false;
}

static int pmecc_get_ecc_bit_req(uint8_t ecc_correctability) {
	int i;
	for (i = 0; i < ARRAY_SIZE(ecc_bit_req_2_tt); i++) {
		if (ecc_bit_req_2_tt[i] >= ecc_correctability)
			return i;
	}
	return ARRAY_SIZE(ecc_bit_req_2_tt) - 1;
}

static uint32_t pmecc_get_default_header(uint32_t data_size, uint32_t spare_size,
                                         uint32_t min_correctability)
{
	union _nand_header hdr;
	hdr.bitfield.use_pmecc = 1;
	hdr.bitfield.nb_sector_per_page = 31 - CLZ(data_size >> 9); /* 512-byte sectors */
	hdr.bitfield.spare_size = spare_size;
	hdr.bitfield.ecc_bit_req = pmecc_get_ecc_bit_req(min_correctability);
	hdr.bitfield.sector_size = 0; // 512 bytes
	hdr.bitfield.ecc_offset = PMECC_ECC_DEFAULT_START_ADDR;
	hdr.bitfield.reserved = 0;
	hdr.bitfield.key = NAND_HEADER_KEY;
	return *(uint32_t*)&hdr;
}

static bool pmecc_set_header(uint32_t header)
{
	uint16_t sector_size_in_byte, ecc_size_in_byte;
	uint8_t mm;
	uint8_t ecc_correction;
	union _nand_header *hdr;

	trace_info_wp("PMECC configuration: 0x%08x\r\n", (unsigned)header);

	hdr = (union _nand_header *)&header;

	if (hdr->bitfield.key != NAND_HEADER_KEY) {
		trace_error_wp("Invalid key field in PMECC configuration\r\n");
		return false;
	}

	if (!hdr->bitfield.use_pmecc) {
		trace_info_wp("ECC disabled\r\n");
		nand_set_ecc_type(ECC_NO);
		return true;
	}

	if (hdr->bitfield.ecc_bit_req >= ARRAY_SIZE(ecc_bit_req_2_tt)) {
		trace_error_wp("Unsupported ECC parameter (%u)\r\n",
				(unsigned)hdr->bitfield.ecc_bit_req);
		return false;
	}
	ecc_correction = ecc_bit_req_2_tt[hdr->bitfield.ecc_bit_req];
	if (ecc_correction > ARRAY_SIZE(PMERRLOC->PMERRLOC_EL)) {
		trace_error_wp("Invalid ECC parameter (%u: %u bits): correction level not supported by chip (max %u bits)\r\n",
				(unsigned)hdr->bitfield.ecc_bit_req,
				(unsigned)ecc_correction,
				ARRAY_SIZE(PMERRLOC->PMERRLOC_EL));
		return false;
	}
	if (ecc_correction < nand_onfi_get_ecc_correctability() &&
		nand_onfi_get_ecc_correctability() != 0xFF) {
		trace_error_wp("Invalid ECC parameter (%u: %u bits): requested value incompatible with ONFI %u bits\r\n",
				(unsigned)hdr->bitfield.ecc_bit_req,
				(unsigned)ecc_correction,
				nand_onfi_get_ecc_correctability());
		return false;
	}

	if (hdr->bitfield.spare_size > nand_onfi_get_spare_size()) {
		trace_error_wp("Invalid spare_size parameter (%u): ONFI spare size (%u) exceeded\r\n",
				(unsigned)hdr->bitfield.spare_size,
				(unsigned)nand_onfi_get_spare_size());
		return false;
	}

	if (hdr->bitfield.sector_size > 1) {
		trace_error_wp("Invalid sector size parameter (%u): use 0 for 512 bytes, 1 for 1024 bytes per sector\r\n",
				(unsigned)hdr->bitfield.sector_size);
		return false;
	}
	sector_size_in_byte = hdr->bitfield.sector_size == 1 ? 1024 : 512;
	if ((page_size / sector_size_in_byte) > 8) {
		trace_error_wp("Invalid sector size parameter (%u): unsupportted page or sector size\r\n",
				(unsigned)hdr->bitfield.sector_size);
		return false;
	}

	if (hdr->bitfield.ecc_offset > hdr->bitfield.spare_size) {
		trace_error_wp("Invalid ECC offset parameter: offset exceeds spare size\r\n");
		return false;
	}

	mm = hdr->bitfield.sector_size == 0 ? 13 : 14;
	if (((mm * ecc_correction) % 8 ) == 0) {
		ecc_size_in_byte = ((mm * ecc_correction) / 8) *
			(page_size / sector_size_in_byte);
	} else {
		ecc_size_in_byte = (((mm * ecc_correction) / 8 ) + 1) *
			(page_size / sector_size_in_byte);
	}

	if ((hdr->bitfield.ecc_offset + ecc_size_in_byte) > hdr->bitfield.spare_size) {
		trace_error_wp("Invalid ECC offset parameter: ECC overflows spare zone\r\n");
		return false;
	}

	nand_set_ecc_type(ECC_PMECC);
	pmecc_initialize(hdr->bitfield.sector_size, ecc_correction,
					 page_size, hdr->bitfield.spare_size,
					 hdr->bitfield.ecc_offset, 0);

	trace_info_wp("PMECC enabled\r\n");
	trace_info_wp("Sector size: %d\r\n", sector_size_in_byte);
	trace_info_wp("Sectors per page: %d\r\n", 1 << hdr->bitfield.nb_sector_per_page);
	trace_info_wp("Spare size: %d\r\n", hdr->bitfield.spare_size);
	trace_info_wp("ECC bits: %d\r\n", ecc_correction);
	trace_info_wp("ECC offset: %d\r\n", hdr->bitfield.ecc_offset);

	return true;
}


static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;
	uint32_t ioset = mbx->in.parameters[0];
	uint32_t bus_width = mbx->in.parameters[1];
	uint32_t header = mbx->in.parameters[2];
	struct _nand_flash_model model_from_onfi;
	uint8_t correctability = 0;

	assert(cmd == APPLET_CMD_INITIALIZE);

	applet_set_init_params(mbx->in.comm_type, mbx->in.trace_level);

	trace_info_wp("\r\nApplet 'NAND Flash' from softpack "
			SOFTPACK_VERSION ".\r\n");

	trace_info_wp("Initializing NAND ioSet%u Bus Width %d\r\n",
			(unsigned)ioset, (unsigned)bus_width);

	if (bus_width != 8 && bus_width != 16) {
		trace_error_wp("Invalid NAND Bus Width %u, must be 8 or 16.\r\n",
			(unsigned)bus_width);
		return APPLET_FAIL;
	}

	board_cfg_matrix_for_nand();
	smc_nand_configure(bus_width);

	if (!configure_instance_pio(ioset)) {
		trace_error_wp("Invalid configuration: NFC ioSet%u\r\n",
			(unsigned)ioset);
		return APPLET_FAIL;
	}

	nand_initialize(&nand);

	if (!nand_onfi_device_detect(&nand)) {
		trace_error_wp("Can't detect device\r\n");
		return APPLET_FAIL;
	}

	if (nand_onfi_check_compatibility(&nand)) {
		model_from_onfi.device_id =
			nand_onfi_get_manufacturer_id();
		model_from_onfi.options =
			nand_onfi_get_bus_width() ? NANDFLASHMODEL_DATABUS16 : NANDFLASHMODEL_DATABUS8;
		model_from_onfi.page_size_in_bytes =
			nand_onfi_get_page_size();
		model_from_onfi.spare_size_in_bytes =
			nand_onfi_get_spare_size();
		model_from_onfi.device_size_in_mega_bytes =
			((nand_onfi_get_pages_per_block() * nand_onfi_get_blocks_per_lun()) / 1024) *
			nand_onfi_get_page_size() / 1024;
		model_from_onfi.block_size_in_kbytes =
			(nand_onfi_get_pages_per_block() * nand_onfi_get_page_size()) / 1024;

		correctability = nand_onfi_get_ecc_correctability();
		if (correctability != 0xFF) {
			/* ONFI correctability is number of ECC bits per 512 bytes of data */
			correctability = correctability * nand_onfi_get_page_size() / 512;
		} else {
			/* force maximum correctability */
			correctability = 32;
		}

		switch (nand_onfi_get_page_size()) {
		case 256:
			model_from_onfi.scheme = &nand_spare_scheme256;
			break;
		case 512:
			model_from_onfi.scheme = &nand_spare_scheme512;
			break;
		case 2048:
			model_from_onfi.scheme = &nand_spare_scheme2048;
			break;
		case 4096:
			model_from_onfi.scheme = &nand_spare_scheme4096;
			break;
		case 8192:
			model_from_onfi.scheme = &nand_spare_scheme8192;
			break;
		}
	}

	nand_onfi_disable_internal_ecc(&nand);

	if (nand_raw_initialize(&nand, &model_from_onfi)) {
		trace_error_wp("Can't initialize device\r\n");
		return APPLET_FAIL;
	}

	/* Get device parameters */
	page_size = nand_model_get_page_data_size(&nand.model);
	block_size = nand_model_get_block_size_in_pages(&nand.model);
	nand_set_dma_enabled(false);
#ifdef CONFIG_HAVE_NFC
	nand_set_nfc_enabled(false);
	nand_set_nfc_sram_enabled(false);
#endif

	/* Initialize PMECC */
	if (header == 0) {
		header = pmecc_get_default_header(nand_onfi_get_page_size(),
		                                  nand_onfi_get_spare_size(),
		                                  correctability);
		trace_info_wp("Using default PMECC configuration\r\n");
	}
	if (pmecc_set_header(header)) {
		nand_header = header;
	} else {
		trace_error_wp("PMECC initialization failed\r\n");
		return APPLET_FAIL;
	}

	/* round buffer to a multiple of page size and check if it's big enough
	 * for at least one page */
	buffer = applet_buffer;
	buffer_size = applet_buffer_size & ~(page_size - 1);
	if (buffer_size == 0) {
		trace_info_wp("Not enough memory for buffer\r\n");
		return APPLET_FAIL;
	}
	trace_info_wp("Buffer Address: 0x%08x\r\n", (unsigned)buffer);
	trace_info_wp("Buffer Size: %u bytes\r\n", (unsigned)buffer_size);

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = page_size;
	mbx->out.mem_size = nand_model_get_device_size_in_pages(&nand.model);
	mbx->out.erase_support = block_size;
	mbx->out.nand_header = nand_header;

	trace_info_wp("NAND applet initialized successfully.\r\n");
	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_info(uint32_t cmd, uint32_t *mailbox)
{
	/* 'read info' uses the same mailbox output as 'initialize' */
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_READ_INFO);

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = page_size;
	mbx->out.mem_size = nand_model_get_device_size_in_pages(&nand.model);
	mbx->out.erase_support = block_size;
	mbx->out.nand_header = nand_header;

	return APPLET_SUCCESS;
}

/*
	Write data to NAND flash.
*/
static uint32_t handle_cmd_write_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t i;
	uint8_t *buf;
	uint16_t block, page;

	assert(cmd == APPLET_CMD_WRITE_PAGES);

	/* check that requested size does not overflow buffer */
	if (mbx->in.length > buffer_size) {
		trace_error_wp("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	block = mbx->in.offset / block_size;
	page = mbx->in.offset - block * block_size;

	for (i = 0, buf = buffer; i < mbx->in.length; i++, buf += page_size) {
		trace_debug_wp("Writing %u bytes at block %u page %u (offset 0x%08x)\r\n",
				(unsigned)page_size, block, page,
				(unsigned)((block * block_size + page) * page_size));
		uint8_t status = nand_skipblock_write_page(&nand, block, page, buf, NULL);
		if (status == NAND_ERROR_BADBLOCK) {
			trace_error_wp("Cannot write bad block %u (page %u)\r\n",
					block, page);
			mbx->out.pages = i;
			return APPLET_BAD_BLOCK;
		} else if (status != 0) {
			trace_error_wp("Write error at block %u, page %u\r\n",
					block, page);
			mbx->out.pages = 0;
			return APPLET_WRITE_FAIL;
		}

		page++;
		if (page == block_size) {
			page = 0;
			block++;
		}
	}


	trace_info_wp("Wrote %u bytes at offset 0x%08x\r\n",
			(unsigned)(mbx->in.length * page_size),
			(unsigned)(mbx->in.offset * page_size));

	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}

/*
	Read data from NAND flash.
*/
static uint32_t handle_cmd_read_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t i;
	uint8_t *buf;
	uint16_t block, page;

	assert(cmd == APPLET_CMD_READ_PAGES);

	/* check that requested size does not overflow buffer */
	if (mbx->in.length > buffer_size) {
		trace_error_wp("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	block = mbx->in.offset / block_size;
	page = mbx->in.offset - block * block_size;

	for (i = 0, buf = buffer; i < mbx->in.length; i++, buf += page_size) {
		uint8_t status = nand_skipblock_read_page(&nand, block, page, buf, NULL);
		if (status == NAND_ERROR_BADBLOCK) {
			trace_error_wp("Cannot read bad block %u\r\n", block);
			mbx->out.pages = i;
			return APPLET_BAD_BLOCK;
		} else if (status != 0) {
			trace_error_wp("Read error at block %u, page %u\r\n",
					block, page);
			mbx->out.pages = 0;
			return APPLET_READ_FAIL;
		}

		page++;
		if (page == block_size) {
			page = 0;
			block++;
		}
	}

	trace_info_wp("Read %u bytes at offset 0x%08x\r\n",
			(unsigned)(mbx->in.length * page_size),
			(unsigned)(mbx->in.offset * page_size));

	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}

/*
	Erase blocks from NAND flash.
*/
static uint32_t handle_cmd_erase_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint16_t block;
	uint8_t status;

	assert(cmd == APPLET_CMD_ERASE_PAGES);

	if (mbx->in.length != block_size) {
		trace_error("Memory does not support requested erase size %u bytes\r\n",
				(unsigned)(mbx->in.length * page_size));
		return APPLET_FAIL;
	}

	if (mbx->in.offset & (block_size - 1)) {
		trace_error("Unaligned erase offset: 0x%x (erase size %u bytes)\r\n",
				(unsigned)(mbx->in.offset * page_size),
				(unsigned)(mbx->in.length * page_size));
		return APPLET_FAIL;
	}
	block = mbx->in.offset / block_size;

	status = nand_skipblock_erase_block(&nand, block, NORMAL_ERASE);
	if (status == NAND_ERROR_BADBLOCK) {
		trace_error_wp("Cannot erase bad block %u\r\n", block);
		mbx->out.pages = 0;
		return APPLET_BAD_BLOCK;
	} else if (status != 0) {
		trace_error_wp("Erase error at block %u\r\n", block);
		mbx->out.pages = 0;
		return APPLET_ERASE_FAIL;
	}

	trace_info_wp("Erased %u bytes at 0x%08x\r\n",
			(unsigned)(mbx->in.length * page_size),
			(unsigned)(mbx->in.offset * page_size));
	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}

/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ APPLET_CMD_READ_INFO, handle_cmd_read_info },
	{ APPLET_CMD_ERASE_PAGES, handle_cmd_erase_pages },
	{ APPLET_CMD_READ_PAGES, handle_cmd_read_pages },
	{ APPLET_CMD_WRITE_PAGES, handle_cmd_write_pages },
	{ 0, NULL }
};
