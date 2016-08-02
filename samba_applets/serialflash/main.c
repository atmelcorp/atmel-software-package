/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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

#include "applet.h"
#include "board.h"
#include "chip.h"
#include "memories/at25.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/spid.h"
#include "pin_defs.h"
#include "trace.h"
#include "intmath.h"
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

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static struct _at25 at25drv;

static struct _spi_desc spi_at25_desc = {
	.attributes     = SPI_MR_MODFDIS | SPI_MR_WDRBT | SPI_MR_MSTR,
	.dlybs          = 0,
	.dlybct         = 0,
	.mutex          = 0,
	.spi_mode       = SPI_CSR_NCPHA | SPI_CSR_BITS_8_BIT,
#if defined(CONFIG_HAVE_SPI_FIFO)
	.transfer_mode = SPID_MODE_FIFO,
#else
	.transfer_mode = SPID_MODE_POLLING,
#endif
};

static uint8_t *buffer;
static uint32_t buffer_size;
static uint32_t erase_support;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static bool configure_instance_pio(uint32_t instance, uint32_t ioset,
		uint32_t cs, Spi** addr)
{
	if (cs >= 4)
		return false;

	int i;
	for (i = 0; i < num_serialflash_pin_defs; i++) {
		const struct serialflash_pin_definition* def =
			&serialflash_pin_defs[i];
		if (def->instance == instance && def->ioset == ioset &&
				def->npcs_pins[cs]) {
			*addr = def->addr;
			pio_configure(def->pins, def->num_pins);
			pio_configure(def->npcs_pins[cs], 1);
			return true;
		}
	}

	return false;
}

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;
	uint32_t instance = mbx->in.parameters[0];
	uint32_t ioset = mbx->in.parameters[1];
	uint32_t chip_select = mbx->in.parameters[2];
	uint32_t freq = mbx->in.parameters[3];

	assert(cmd == APPLET_CMD_INITIALIZE);

	applet_set_init_params(mbx->in.comm_type, mbx->in.trace_level);

	trace_info_wp("\r\nApplet 'AT25/AT26 Serial Flash' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	uint32_t max_freq = pmc_get_peripheral_clock(ID_SPI0);
	if (freq == 0 || freq > max_freq) {
		trace_error_wp("Invalid configuration: frequency must be " \
				"between 1 and %uHz (requested %uHz)\r\n",
				(unsigned)max_freq, (unsigned)freq);
		return APPLET_FAIL;
	}

	if (!configure_instance_pio(instance, ioset, chip_select,
				&spi_at25_desc.addr)) {
		trace_error_wp("Invalid configuration: SPI%u IOSet%u NPCS%u\r\n",
			(unsigned)instance, (unsigned)ioset,
			(unsigned)chip_select);
		return APPLET_FAIL;
	}

	spi_at25_desc.bitrate = ROUND_INT_DIV(freq, 1000);
	spi_at25_desc.chip_select = chip_select;

	trace_info_wp("Initializing SPI%u ioSet%u NPCS%u at %uHz\r\n",
			(unsigned)instance, (unsigned)ioset,
			(unsigned)chip_select, (unsigned)freq);

	/* initialize the SPI and serial flash */
	if (at25_configure(&at25drv, &spi_at25_desc) != AT25_SUCCESS) {
		trace_info_wp("Error while detecting AT25 chip\r\n");
		return APPLET_DEV_UNKNOWN;
	}

	trace_info_wp("SPI and AT25/AT26 drivers initialized\r\n");

	if (!at25drv.desc) {
		trace_info_wp("Device Unknown\r\n");
		return APPLET_DEV_UNKNOWN;
	}
	else {
		/* Get device parameters */
		uint32_t size = at25drv.desc->size;
		uint32_t page_size = at25drv.desc->page_size;

		trace_info_wp("Found Device %s\r\n", at25drv.desc->name);
		trace_info_wp("Size: %u bytes\r\n", (unsigned)size);
		trace_info_wp("Page Size: %u bytes\r\n", (unsigned)page_size);

		erase_support = 0;
		if (at25drv.desc->flags & SPINOR_FLAG_ERASE_4K) {
			trace_info_wp("Supports 4K block erase\r\n");
			erase_support |= (4 * 1024) / page_size;
		}
		if (at25drv.desc->flags & SPINOR_FLAG_ERASE_32K) {
			trace_info_wp("Supports 32K block erase\r\n");
			erase_support |= (32 * 1024) / page_size;
		}
		if (at25drv.desc->flags & SPINOR_FLAG_ERASE_64K) {
			trace_info_wp("Supports 64K block erase\r\n");
			erase_support |= (64 * 1024) / page_size;
		}
		if (at25drv.desc->flags & SPINOR_FLAG_ERASE_256K) {
			trace_info_wp("Supports 256K block erase\r\n");
			erase_support |= (256 * 1024) / page_size;
		}

		if (at25_unprotect(&at25drv) != AT25_SUCCESS) {
			return APPLET_UNPROTECT_FAIL;
		}

		/* round buffer size to a multiple of page size and check if
		 * it's big enough for at least one page */
		buffer = applet_buffer;
		buffer_size = applet_buffer_size & ~(page_size - 1);
		/* SST Flash write is slow, reduce buffer size to avoid
		 * timeouts */
		if (SPINOR_JEDEC_MANUF(at25drv.desc->jedec_id) == SPINOR_MANUF_SST) {
			buffer_size = min_u32(10 * page_size, buffer_size);
		}
		if (buffer_size == 0) {
			trace_info_wp("Not enough memory for buffer\r\n");
			return APPLET_FAIL;
		}
		trace_info_wp("Buffer Address: 0x%08x\r\n", (unsigned)buffer);
		trace_info_wp("Buffer Size: %u bytes\r\n",
				(unsigned)buffer_size);

		mbx->out.buf_addr = (uint32_t)buffer;
		mbx->out.buf_size = buffer_size;
		mbx->out.page_size = page_size;
		mbx->out.mem_size = size / page_size;
		mbx->out.erase_support = erase_support;
		mbx->out.nand_header = 0;

		trace_info_wp("SPI serialflash applet initialized successfully.\r\n");
		return APPLET_SUCCESS;
	}
}

static uint32_t handle_cmd_read_info(uint32_t cmd, uint32_t *mailbox)
{
	/* 'read info' uses the same mailbox output as 'initialize' */
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_READ_INFO);

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = at25drv.desc->page_size;
	mbx->out.mem_size = at25drv.desc->size / at25drv.desc->page_size;
	mbx->out.erase_support = erase_support;
	mbx->out.nand_header = 0;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_write_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset * at25drv.desc->page_size;
	uint32_t length = mbx->in.length * at25drv.desc->page_size;

	assert(cmd == APPLET_CMD_WRITE_PAGES);

	/* check that requested size does not overflow buffer */
	if (length > buffer_size) {
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* perform the write operation */
	if (at25_write(&at25drv, offset, buffer, length) != AT25_SUCCESS) {
		trace_error("Write error\r\n");
		mbx->out.pages = 0;
		return APPLET_WRITE_FAIL;
	}
	at25_wait(&at25drv);

	trace_info_wp("Wrote %u bytes at 0x%08x\r\n",
			(unsigned)length, (unsigned)offset);

	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset * at25drv.desc->page_size;
	uint32_t length = mbx->in.length * at25drv.desc->page_size;

	assert(cmd == APPLET_CMD_READ_PAGES);

	/* check that requested size does not overflow buffer */
	if (length > buffer_size) {
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* perform the read operation */
	if (at25_read(&at25drv, offset, buffer, length) != AT25_SUCCESS) {
		trace_error("Read error\r\n");
		mbx->out.pages = 0;
		return APPLET_READ_FAIL;
	}

	trace_info_wp("Read %u bytes at 0x%08x\r\n",
			(unsigned)length, (unsigned)offset);

	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_erase_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset * at25drv.desc->page_size;
	uint32_t length = mbx->in.length * at25drv.desc->page_size;

	assert(cmd == APPLET_CMD_ERASE_PAGES);

	if ((at25drv.desc->flags & SPINOR_FLAG_ERASE_4K)
			&& length == 4 * 1024) {
	} else if ((at25drv.desc->flags & SPINOR_FLAG_ERASE_32K)
			&& length == 32 * 1024) {
	} else if ((at25drv.desc->flags & SPINOR_FLAG_ERASE_64K)
			&& length == 64 * 1024) {
	} else if ((at25drv.desc->flags & SPINOR_FLAG_ERASE_256K)
			&& length == 256 * 1024) {
	} else {
		trace_error("Memory does not support requested erase size "
				"%u bytes\r\n", (unsigned)length);
		return APPLET_FAIL;
	}

	if (offset & (length - 1)) {
		trace_error("Unaligned erase offset: 0x%08x (erase size "
				"%u bytes)\r\n", (unsigned)offset,
				(unsigned)length);
		return APPLET_FAIL;
	}

	if (at25_erase_block(&at25drv, offset, length) != AT25_SUCCESS) {
		trace_error("Erase failed at offset 0x%08x\r\n",
				(unsigned)offset);
		return APPLET_ERASE_FAIL;
	}
	at25_wait(&at25drv);

	trace_info_wp("Erased %u bytes at 0x%08x\r\n",
			(unsigned)length, (unsigned)offset);

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
