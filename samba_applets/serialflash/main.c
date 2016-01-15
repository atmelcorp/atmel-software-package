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
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#if !defined(CONFIG_SOC_SAMA5D2) && !defined(CONFIG_SOC_SAMA5D4)
#error Unsupported SOC!
#endif

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#if defined(CONFIG_SOC_SAMA5D2)
#define MAX_BUFFER_SIZE (32 * 1024)
#elif defined(CONFIG_SOC_SAMA5D4)
#define MAX_BUFFER_SIZE (24 * 1024)
#endif

/* Input arguments for the Init command. */
struct input_init
{
	uint32_t comm_type;   /* Type of communication link used */
	uint32_t trace_level; /* Trace level */
	uint32_t instance;    /* SPI instance */
	uint32_t ioset;       /* SPI ioSet */
	uint32_t cs;          /* SPI Chip Select */
	uint32_t freq;        /* SPI Frequency */
};

/* Output arguments for the Init command. */
struct output_init
{
	uint32_t mem_size; /* Memory size */
	uint32_t buf_addr; /* Buffer address */
	uint32_t buf_size; /* Buffer size */
};

/* Input arguments for the Write command. */
struct input_write
{
	uint32_t buf_addr;   /* Buffer address */
	uint32_t buf_size;   /* Buffer size */
	uint32_t mem_offset; /* Memory offset */
};

/* Output arguments for the Write command. */
struct output_write
{
	uint32_t bytes_written; /* Bytes written */
};

/* Input arguments for the Read command. */
struct input_read
{
	uint32_t buf_addr;   /* Buffer address */
	uint32_t buf_size;   /* Buffer size */
	uint32_t mem_offset; /* Memory offset */
};

/* Output arguments for the Read command. */
struct output_read
{
	uint32_t bytes_read; /* Bytes read */
};

/* Input arguments for the Buffer Erase command. */
struct input_buffer_erase
{
	uint32_t mem_offset; /* Memory offset to be erase */
};

/* Output arguments for the Buffer Erase command. */
struct output_buffer_erase
{
	uint32_t bytes_erased; /* Bytes erased */
};

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static struct _at25 at25drv;

static struct _spi_desc spi_at25_desc = {
	.attributes     = SPI_MR_MODFDIS | SPI_MR_WDRBT | SPI_MR_MSTR,
	.dlybs          = 0,
	.dlybct         = 0,
	.mutex          = 1,
	.spi_mode       = SPI_CSR_NCPHA | SPI_CSR_BITS_8_BIT,
	.transfert_mode = SPID_MODE_FIFO,
};

static bool initialized = false;
static uint8_t buffer[MAX_BUFFER_SIZE];
static uint32_t buffer_size;

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

static uint32_t handle_cmd_init(uint32_t cmd, uint32_t *args)
{
	struct input_init *in = (struct input_init *)args;
	struct output_init *out = (struct output_init *)args;

	assert(cmd == APPLET_CMD_INIT);

	applet_set_init_params(in->comm_type, in->trace_level);

	initialized = false;

	trace_info_wp("\r\nApplet 'AT25/AT26 Serial Flash' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	uint32_t max_freq = pmc_get_peripheral_clock(ID_SPI0);
	if (in->freq == 0 || in->freq > max_freq) {
		trace_error_wp("Invalid configuration: frequency must be " \
				"between 1 and %uHz (requested %uHz)\r\n",
				(unsigned)max_freq, (unsigned)in->freq);
		return APPLET_FAIL;
	}

	if (!configure_instance_pio(in->instance, in->ioset, in->cs,
				&spi_at25_desc.addr)) {
		trace_error_wp("Invalid configuration: QSPI%u IOSet%u NPCS%u\r\n",
			(unsigned)in->instance, (unsigned)in->ioset,
			(unsigned)in->cs);
		return APPLET_FAIL;
	}

	spi_at25_desc.bitrate = ROUND_INT_DIV(in->freq, 1000);
	spi_at25_desc.chip_select = in->cs;

	trace_info_wp("Initializing SPI%u ioSet%u NPCS%u at %uHz\r\n",
			(unsigned)in->instance, (unsigned)in->ioset,
			(unsigned)in->cs, (unsigned)in->freq);

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
		uint32_t page_size = at25drv.desc->page_size;

		trace_info_wp("Found Device %s\r\n", at25drv.desc->name);
		trace_info_wp("Size: %u bytes\r\n",
				(unsigned)at25drv.desc->size);
		trace_info_wp("Page Size: %u bytes\r\n", (unsigned)page_size);
		if (at25drv.desc->erase_support & AT25_ERASE_4K)
			trace_info_wp("Supports 4K block erase\r\n");
		if (at25drv.desc->erase_support & AT25_ERASE_32K)
			trace_info_wp("Supports 32K block erase\r\n");
		if (at25drv.desc->erase_support & AT25_ERASE_64K)
			trace_info_wp("Supports 64K block erase\r\n");

		if (at25_unprotect(&at25drv) != AT25_SUCCESS) {
			return APPLET_UNPROTECT_FAIL;
		}

		if (AT25_JEDEC_MANUF(at25drv.desc->jedec_id) == AT25_MANUF_SST) {
			/* SST Flash write is slow, reduce buffer size to avoid
			 * application timeouts */
			buffer_size = 10 * page_size;
		} else {
			buffer_size = MAX_BUFFER_SIZE;
		}

		/* round buffer size to a multiple of page_size */
		buffer_size = buffer_size & ~(page_size - 1);
		if (buffer_size < page_size || buffer_size > MAX_BUFFER_SIZE) {
			trace_info_wp("Not enough memory for transfer "
					"buffer\r\n");
			return APPLET_FAIL;
		}

		out->buf_addr = (uint32_t)buffer;
		out->buf_size = buffer_size;
		out->mem_size = at25drv.desc->size;

		trace_info_wp("Buffer Address: 0x%x\r\n",
				(unsigned)out->buf_addr);
		trace_info_wp("Buffer Size: %u bytes\r\n",
				(unsigned)out->buf_size);

		initialized = true;
		return APPLET_SUCCESS;
	}
}

static uint32_t handle_cmd_write(uint32_t cmd, uint32_t *args)
{
	struct input_write *in = (struct input_write *)args;
	struct output_write *out = (struct output_write *)args;

	uint8_t *buffer_end = buffer + buffer_size;

	uint8_t *buf = (uint8_t*)in->buf_addr;
	uint32_t size = in->buf_size;
	uint32_t offset = in->mem_offset;

	assert(cmd == APPLET_CMD_WRITE);

	/* check that start of buffer is contained in our buffer zone */
	if (buf < buffer || buf >= buffer_end) {
		trace_error("Invalid buffer address\r\n");
		return APPLET_FAIL;
	}

	/* check that requested size does not overflow buffer */
	if ((buf + size) > buffer_end) {
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* perform the write operation */
	if (at25_write(&at25drv, offset, buf, size) != AT25_SUCCESS) {
		trace_error("Write error\r\n");
		out->bytes_written = 0;
		return APPLET_WRITE_FAIL;
	}
	at25_wait(&at25drv);

	trace_info_wp("Wrote %u bytes at 0x%x\r\n", (unsigned)size,
			(unsigned)offset);
	out->bytes_written = size;
	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read(uint32_t cmd, uint32_t *args)
{
	struct input_read *in = (struct input_read *)args;
	struct output_read *out = (struct output_read *)args;

	uint8_t *buffer_end = buffer + buffer_size;

	uint8_t *buf = (uint8_t*)in->buf_addr;
	uint32_t size = in->buf_size;
	uint32_t offset = in->mem_offset;

	assert(cmd == APPLET_CMD_READ);

	/* check that start of buffer is contained in our buffer zone */
	if (buf < buffer || buf >= buffer_end) {
		trace_error("Invalid buffer address\r\n");
		return APPLET_FAIL;
	}

	/* check that requested size does not overflow buffer */
	if ((buf + size) > buffer_end) {
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* perform the read operation */
	if (at25_read(&at25drv, offset, buf, size) != AT25_SUCCESS) {
		trace_error("Read error\r\n");
		out->bytes_read = 0;
		return APPLET_READ_FAIL;
	}

	trace_info_wp("Read %u bytes at 0x%x\r\n", (unsigned)size,
			(unsigned)in->mem_offset);
	out->bytes_read = size;
	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_full_erase(uint32_t cmd, uint32_t *args)
{
	assert(cmd == APPLET_CMD_FULL_ERASE);

	/* unused argument */
	(void)args;

	if (at25_erase_chip(&at25drv) != AT25_SUCCESS) {
		return APPLET_ERASE_FAIL;
	}

	at25_wait(&at25drv);
	trace_info_wp("Full erase completed.\r\n");
	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_buffer_erase(uint32_t cmd, uint32_t *args)
{
	struct input_buffer_erase *in = (struct input_buffer_erase *)args;
	struct output_buffer_erase *out = (struct output_buffer_erase *)args;

	uint32_t erase_type = 0;
	uint32_t offset = in->mem_offset;
	uint32_t size;

	assert(cmd == APPLET_CMD_BUFFER_ERASE);

	if (at25drv.desc->erase_support & AT25_ERASE_4K) {
		erase_type = AT25_ERASE_4K;
		size = 4;
	} else if (at25drv.desc->erase_support & AT25_ERASE_32K) {
		erase_type = AT25_ERASE_32K;
		size = 32;
	} else if (at25drv.desc->erase_support & AT25_ERASE_64K) {
		erase_type = AT25_ERASE_64K;
		size = 64;
	} else if (at25drv.desc->erase_support & AT25_ERASE_256K) {
		erase_type = AT25_ERASE_256K;
		size = 256;
	} else {
		trace_error("Memory supports neither 4KB, 32KB, 64KB nor 256KB erase\r\n");
		return APPLET_FAIL;
	}

	if (offset & ((size * 1024) - 1)) {
		trace_error("Unaligned Block Erase offset: 0x%x (erase size %uKB)\r\n",
				(unsigned)offset, (unsigned)size);
		return APPLET_FAIL;
	}

	if (at25_erase_block(&at25drv, offset, erase_type) != AT25_SUCCESS) {
		trace_error("Block Erase failed at offset 0x%x\r\n",
				(unsigned)offset);
		return APPLET_ERASE_FAIL;
	}
	at25_wait(&at25drv);

	trace_info_wp("Erased %uKB at 0x%x\r\n", (unsigned)size,
			(unsigned)offset);
	out->bytes_erased = size * 1024;
	return APPLET_SUCCESS;
}

/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INIT, handle_cmd_init },
	{ APPLET_CMD_WRITE, handle_cmd_write },
	{ APPLET_CMD_READ, handle_cmd_read },
	{ APPLET_CMD_FULL_ERASE, handle_cmd_full_erase },
	{ APPLET_CMD_BUFFER_ERASE, handle_cmd_buffer_erase },
	{ 0, NULL }
};
