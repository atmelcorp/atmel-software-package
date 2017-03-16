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

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "applet.h"
#include "board.h"
#include "chip.h"
#include "gpio/pio.h"
#include "intmath.h"
#include "nvm/spi-nor/at25.h"
#include "peripherals/bus.h"
#include "peripherals/pmc.h"
#include "pin_defs.h"
#include "spi/spid.h"
#include "trace.h"

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

static struct _at25 at25drv = {
	.cfg = {
		.bus = 0,
		.spi_dev = {
			/* .chip_select */
			/* .bitrate */
			.delay = {
				.bs = 0,
				.bct = 0,
			},
			.spi_mode = SPID_MODE_0,
		},
	},
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
	struct _bus_iface iface;

	assert(cmd == APPLET_CMD_INITIALIZE);

	if (!applet_set_init_params(mbx))
		return APPLET_FAIL;

	trace_warning_wp("\r\nApplet 'AT25/AT26 Serial Flash' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	uint32_t max_freq = pmc_get_peripheral_clock(ID_SPI0);
	if (freq == 0 || freq > max_freq) {
		trace_error("Invalid configuration: frequency must be " \
				"between 1 and %uHz (requested %uHz)\r\n",
				(unsigned)max_freq, (unsigned)freq);
		return APPLET_FAIL;
	}

	if (!configure_instance_pio(instance, ioset, chip_select, &iface.spi.hw)) {
		trace_error("Invalid configuration: SPI%u IOSet%u NPCS%u\r\n",
			(unsigned)instance, (unsigned)ioset,
			(unsigned)chip_select);
		return APPLET_FAIL;
	}

	iface.type = BUS_TYPE_SPI;
	iface.transfer_mode = BUS_TRANSFER_MODE_DMA;
	bus_configure(BUS(BUS_TYPE_SPI, 0), &iface);
#ifdef CONFIG_HAVE_SPI_FIFO
	bus_ioctl(0, BUS_IOCTL_ENABLE_FIFO, NULL);
#endif

	at25drv.cfg.spi_dev.bitrate = ROUND_INT_DIV(freq, 1000);
	at25drv.cfg.spi_dev.chip_select = chip_select;

	trace_warning_wp("Initializing SPI%u ioSet%u NPCS%u at %uHz\r\n",
			(unsigned)instance, (unsigned)ioset,
			(unsigned)chip_select, (unsigned)freq);

	/* initialize the SPI and serial flash */
	if (at25_configure(&at25drv) < 0) {
		trace_error("Error while detecting AT25 chip\r\n");
		return APPLET_DEV_UNKNOWN;
	}

	trace_warning_wp("SPI and AT25/AT26 drivers initialized\r\n");

	if (!at25drv.desc) {
		trace_error("Device Unknown\r\n");
		return APPLET_DEV_UNKNOWN;
	}
	else {
		/* Get device parameters */
		uint32_t size = at25drv.desc->size;
		uint32_t page_size = at25drv.desc->page_size;

		trace_warning_wp("Found Device %s\r\n", at25drv.desc->name);
		trace_warning_wp("Size: %u bytes\r\n", (unsigned)size);
		trace_warning_wp("Page Size: %u bytes\r\n", (unsigned)page_size);

		erase_support = 0;
		if (at25drv.desc->flags & SPINOR_FLAG_ERASE_4K) {
			trace_warning_wp("Supports 4K block erase\r\n");
			erase_support |= (4 * 1024) / page_size;
		}
		if (at25drv.desc->flags & SPINOR_FLAG_ERASE_32K) {
			trace_warning_wp("Supports 32K block erase\r\n");
			erase_support |= (32 * 1024) / page_size;
		}
		if (at25drv.desc->flags & SPINOR_FLAG_ERASE_64K) {
			trace_warning_wp("Supports 64K block erase\r\n");
			erase_support |= (64 * 1024) / page_size;
		}
		if (at25drv.desc->flags & SPINOR_FLAG_ERASE_256K) {
			trace_warning_wp("Supports 256K block erase\r\n");
			erase_support |= (256 * 1024) / page_size;
		}

		if (at25_set_protection(&at25drv, false) < 0) {
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
			trace_error("Not enough memory for buffer\r\n");
			return APPLET_FAIL;
		}
		trace_warning_wp("Buffer Address: 0x%08x\r\n", (unsigned)buffer);
		trace_warning_wp("Buffer Size: %u bytes\r\n",
				(unsigned)buffer_size);

		mbx->out.buf_addr = (uint32_t)buffer;
		mbx->out.buf_size = buffer_size;
		mbx->out.page_size = page_size;
		mbx->out.mem_size = size / page_size;
		mbx->out.erase_support = erase_support;
		mbx->out.nand_header = 0;

		trace_warning_wp("SPI serialflash applet initialized successfully.\r\n");
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
	if (at25_write(&at25drv, offset, buffer, length) < 0) {
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
	if (at25_read(&at25drv, offset, buffer, length) < 0) {
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

	if (at25_erase_block(&at25drv, offset, length) < 0) {
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
