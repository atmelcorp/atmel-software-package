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
#include "nvm/nand/nand_flash_model_list.h"
#include "nvm/nand/nand_flash_model.h"
#include "nvm/nand/nand_flash_ecc.h"
#include "nvm/nand/nand_flash_onfi.h"
#include "nvm/nand/nand_flash_dma.h"
#include "nvm/nand/nand_flash_raw.h"

#include "serial/console.h"

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
static uint32_t spare_size;
static uint32_t block_size;

static uint8_t ecc_bit_req_2_tt[] = {
	2, 4, 8, 12, 24, 32
};

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static bool configure_instance_pio(uint32_t ioset, uint8_t bus_width)
{
	int i;
	for (i = 0; i < num_nandflash_pin_defs; i++) {
		const struct nandflash_pin_definition* def = &nandflash_pin_defs[i];
		if (def->ioset == ioset && def->bus_width == bus_width) {
			pio_configure(def->pins, def->num_pins);
			return true;
		}
	}
	return false;
}

static int pmecc_get_ecc_bit_req(uint8_t ecc_correctability) {
	int i;
	if (ecc_correctability > ARRAY_SIZE(PMERRLOC->PMERRLOC_EL))
		ecc_correctability = ARRAY_SIZE(PMERRLOC->PMERRLOC_EL);
	for (i = 0; i < ARRAY_SIZE(ecc_bit_req_2_tt); i++) {
		if (ecc_bit_req_2_tt[i] >= ecc_correctability)
			return i;
	}
	return ARRAY_SIZE(ecc_bit_req_2_tt) - 1;
}

static uint32_t pmecc_get_ecc_size(uint32_t ecc_bits, uint32_t sector_size_in_byte,
                                   uint32_t nb_sector_per_page)
{
	uint32_t mm = sector_size_in_byte == 512 ? 13 : 14;
	return ROUND_INT_DIV(mm * ecc_bits, 8) * nb_sector_per_page;
}

static uint32_t pmecc_get_default_header(uint32_t min_correctability)
{
	unsigned ecc_size;
	union _nand_header hdr;
	hdr.bitfield.use_pmecc = 1;
	hdr.bitfield.nb_sector_per_page = 31 - CLZ(page_size >> 9); /* 512-byte sectors */
	hdr.bitfield.spare_size = spare_size;
	hdr.bitfield.ecc_bit_req = pmecc_get_ecc_bit_req(min_correctability);
	hdr.bitfield.sector_size = 0; // 512 bytes
	ecc_size = pmecc_get_ecc_size(ecc_bit_req_2_tt[hdr.bitfield.ecc_bit_req],
	                              512, 1 << hdr.bitfield.nb_sector_per_page);
	hdr.bitfield.ecc_offset = spare_size - ecc_size;
	hdr.bitfield.reserved = 0;
	hdr.bitfield.key = NAND_HEADER_KEY;
	return hdr.uint32_value;
}

static bool pmecc_set_header(uint32_t header, uint8_t correctability)
{
	uint16_t sector_size_in_byte, nb_sector_per_page, ecc_size_in_byte;
	uint8_t ecc_correction;
	union _nand_header *hdr;

	trace_warning_wp("PMECC configuration: 0x%08x\r\n", (unsigned)header);

	hdr = (union _nand_header *)&header;

	if (hdr->bitfield.key != NAND_HEADER_KEY) {
		trace_error("Invalid key field in PMECC configuration\r\n");
		return false;
	}

	if (!hdr->bitfield.use_pmecc) {
		trace_warning_wp("ECC disabled\r\n");
		nand_set_ecc_type(ECC_NO);
		return true;
	}

	if (hdr->bitfield.ecc_bit_req >= ARRAY_SIZE(ecc_bit_req_2_tt)) {
		trace_error("Unsupported ECC parameter (%u)\r\n",
				(unsigned)hdr->bitfield.ecc_bit_req);
		return false;
	}

	ecc_correction = ecc_bit_req_2_tt[hdr->bitfield.ecc_bit_req];

	if (ecc_correction > ARRAY_SIZE(PMERRLOC->PMERRLOC_EL)) {
		trace_error("Invalid ECC parameter (%u: %u bits): correction level not supported by device (max %u bits)\r\n",
				(unsigned)hdr->bitfield.ecc_bit_req,
				(unsigned)ecc_correction,
				ARRAY_SIZE(PMERRLOC->PMERRLOC_EL));
		return false;
	}

	sector_size_in_byte = hdr->bitfield.sector_size == 1 ? 1024 : 512;
	nb_sector_per_page = 1 << hdr->bitfield.nb_sector_per_page;
	ecc_size_in_byte = pmecc_get_ecc_size(ecc_correction, sector_size_in_byte, nb_sector_per_page);
	trace_warning_wp("Sector size: %d\r\n", sector_size_in_byte);
	trace_warning_wp("Sectors per page: %d\r\n", nb_sector_per_page);
	trace_warning_wp("Spare size: %d\r\n", hdr->bitfield.spare_size);
	trace_warning_wp("ECC bits: %d\r\n", ecc_correction);
	trace_warning_wp("ECC offset: %d\r\n", hdr->bitfield.ecc_offset);
	trace_warning_wp("ECC size: %d\r\n", ecc_size_in_byte);

	if (ecc_correction < (correctability / nb_sector_per_page) && correctability != 0xFF) {
		trace_warning_wp("Warning: Invalid ECC parameter (%u: %u bits/sector): NAND requires at least %u bits\r\n",
				(unsigned)hdr->bitfield.ecc_bit_req,
				(unsigned)ecc_correction,
				correctability / nb_sector_per_page);
	}

	if (hdr->bitfield.spare_size > spare_size) {
		trace_warning_wp("Warning: Invalid spare_size parameter (%u): NAND spare size (%u) exceeded\r\n",
				(unsigned)hdr->bitfield.spare_size,
				(unsigned)spare_size);
	}

	if (hdr->bitfield.sector_size > 1) {
		trace_error("Invalid sector size parameter (%u): use 0 for 512 bytes, 1 for 1024 bytes per sector\r\n",
				(unsigned)hdr->bitfield.sector_size);
		return false;
	}

	if ((page_size / sector_size_in_byte) != nb_sector_per_page) {
		trace_warning_wp("Warning: Invalid sector size (%u) or number of sectors per page (%u): does not match page size (%u)\r\n",
				(unsigned)sector_size_in_byte,
				(unsigned)nb_sector_per_page,
				(unsigned)page_size);
	}

	if (hdr->bitfield.ecc_offset > hdr->bitfield.spare_size) {
		trace_warning_wp("Warning: Invalid ECC offset parameter: offset exceeds spare size\r\n");
	}

	if ((hdr->bitfield.ecc_offset + ecc_size_in_byte) > hdr->bitfield.spare_size) {
		trace_warning_wp("Warning: Invalid ECC offset parameter: ECC overflows spare zone\r\n");
	}

	nand_set_ecc_type(ECC_PMECC);
	pmecc_initialize(hdr->bitfield.sector_size, ecc_correction,
					 page_size, hdr->bitfield.spare_size,
					 hdr->bitfield.ecc_offset, 0);

	trace_warning_wp("PMECC enabled\r\n");

	return true;
}


static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;
	uint32_t ioset = mbx->in.parameters[0];
	uint32_t bus_width = mbx->in.parameters[1];
	uint32_t header = mbx->in.parameters[2];
	struct _nand_flash_model *model, model_from_onfi;
	uint8_t correctability;

	assert(cmd == APPLET_CMD_INITIALIZE);

	if (!applet_set_init_params(mbx))
		return APPLET_FAIL;

	trace_warning_wp("\r\nApplet 'NAND Flash' from softpack "
			SOFTPACK_VERSION ".\r\n");

	trace_warning_wp("Initializing NAND ioSet%u Bus Width %u\r\n",
			(unsigned)ioset, (unsigned)bus_width);

	if (bus_width != 8 && bus_width != 16) {
		trace_error("Invalid NAND Bus Width %u, must be 8 or 16.\r\n",
			(unsigned)bus_width);
		return APPLET_FAIL;
	}

	board_cfg_matrix_for_nand();
	smc_nand_configure(bus_width);

	if (!configure_instance_pio(ioset, bus_width)) {
		trace_error("Invalid configuration: NFC ioSet%u Bus Width %u\r\n",
			(unsigned)ioset, (unsigned)bus_width);
		return APPLET_FAIL;
	}

	nand_initialize(&nand);

	/* defaults: use hardcoded NAND model table, no minimum ECC */
	model = NULL;
	correctability = 0;

	/* try reading ONFI data */
	if (nand_onfi_device_detect(&nand) && nand_onfi_check_compatibility(&nand)) {
		nand_onfi_disable_internal_ecc(&nand);
		nand_onfi_get_model(&model_from_onfi);
		model = &model_from_onfi;
		correctability = nand_onfi_get_ecc_correctability();
		if (correctability != 0xff) {
			/* ONFI correctability is number of ECC bits per 512 bytes of data */
			correctability *= nand_onfi_get_page_size() / 512;
		}
	}

	if (nand_raw_initialize(&nand, model)) {
		trace_error("Can't initialize device\r\n");
		return APPLET_FAIL;
	}

	/* Get device parameters */
	page_size = nand_model_get_page_data_size(&nand.model);
	spare_size = nand_model_get_page_spare_size(&nand.model);
	block_size = nand_model_get_block_size_in_pages(&nand.model);
	nand_set_dma_enabled(false);
#ifdef CONFIG_HAVE_NFC
	nand_set_nfc_enabled(false);
	nand_set_nfc_sram_enabled(false);
#endif

	/* Initialize PMECC */
	if (header == 0) {
		header = pmecc_get_default_header(correctability);
		trace_warning_wp("Using default PMECC configuration\r\n");
	}
	if (pmecc_set_header(header, correctability)) {
		nand_header = header;
	} else {
		trace_error("PMECC initialization failed\r\n");
		return APPLET_FAIL;
	}

	/* round buffer to a multiple of page size and check if it's big enough
	 * for at least one page */
	buffer = applet_buffer;
	buffer_size = applet_buffer_size & ~(page_size - 1);
	if (buffer_size == 0) {
		trace_error("Not enough memory for buffer\r\n");
		return APPLET_FAIL;
	}
	trace_warning_wp("Buffer Address: 0x%08x\r\n", (unsigned)buffer);
	trace_warning_wp("Buffer Size: %u bytes\r\n", (unsigned)buffer_size);

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = page_size;
	mbx->out.mem_size = nand_model_get_device_size_in_pages(&nand.model);
	mbx->out.erase_support = block_size;
	mbx->out.nand_header = nand_header;

	trace_warning_wp("NAND applet initialized successfully.\r\n");
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
		trace_error("Buffer overflow\r\n");
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
			trace_error("Cannot write bad block %u (page %u)\r\n",
					block, page);
			mbx->out.pages = i;
			return APPLET_BAD_BLOCK;
		} else if (status != 0) {
			trace_error("Write error at block %u, page %u\r\n",
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
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	block = mbx->in.offset / block_size;
	page = mbx->in.offset - block * block_size;

	for (i = 0, buf = buffer; i < mbx->in.length; i++, buf += page_size) {
		uint8_t status = nand_skipblock_read_page(&nand, block, page, buf, NULL);
		if (status == NAND_ERROR_BADBLOCK) {
			trace_error("Cannot read bad block %u\r\n", block);
			mbx->out.pages = i;
			return APPLET_BAD_BLOCK;
		} else if (status != 0) {
			trace_error("Read error at block %u, page %u\r\n",
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
		trace_error("Cannot erase bad block %u\r\n", block);
		mbx->out.pages = 0;
		return APPLET_BAD_BLOCK;
	} else if (status != 0) {
		trace_error("Erase error at block %u\r\n", block);
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
