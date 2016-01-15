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
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/qspi.h"
#include "memories/qspiflash.h"
#include "pin_defs.h"
#include "trace.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#if !defined(CONFIG_SOC_SAMA5D2)
#error Unsupported SOC!
#endif

#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define MAX_BUFFER_SIZE (64 * 1024)

/* Input arguments for the Init command. */
struct input_init
{
	uint32_t comm_type;   /* Type of communication link used */
	uint32_t trace_level; /* Trace level */
	uint32_t instance;    /* QSPI instance (0, 1) */
	uint32_t ioset;       /* QSPI IOSet (1, 2, 3) */
	uint32_t freq;        /* QSPI Frequency */
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

static struct _qspiflash flash;

static bool initialized = false;
static uint8_t buffer[MAX_BUFFER_SIZE];
static uint32_t buffer_size;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static bool configure_instance_pio(uint32_t instance, uint32_t ioset, Qspi** addr)
{
	int i;
	for (i = 0; i < num_qspiflash_pin_defs; i++) {
		const struct qspiflash_pin_definition* def =
			&qspiflash_pin_defs[i];
		if (def->instance == instance && def->ioset == ioset) {
			*addr = def->addr;
			pio_configure(def->pins, def->num_pins);
			return true;
		}
	}

	trace_error_wp("Invalid configuration: QSPI%u IOSet%u\r\n",
		(unsigned)instance, (unsigned)ioset);
	return false;
}

static uint32_t handle_cmd_init(uint32_t cmd, uint32_t *args)
{
	struct input_init *in = (struct input_init *)args;
	struct output_init *out = (struct output_init *)args;

	assert(cmd == APPLET_CMD_INIT);

	applet_set_init_params(in->comm_type, in->trace_level);

	initialized = false;

	trace_info_wp("\r\nApplet 'QSPI Flash' from softpack " SOFTPACK_VERSION ".\r\n");

	uint32_t max_freq = pmc_get_peripheral_clock(ID_QSPI0);
	if (in->freq == 0 || in->freq > max_freq) {
		trace_error_wp("Invalid configuration: frequency must be " \
				"between 1 and %uHz (requested %uHz)\r\n",
				(unsigned)max_freq, (unsigned)in->freq);
		return APPLET_FAIL;
	}

	Qspi* addr;
	if (!configure_instance_pio(in->instance, in->ioset, &addr))
		return APPLET_FAIL;

	trace_info_wp("Initializing QSPI%u IOSet%u at %uHz\r\n",
			(unsigned)in->instance, (unsigned)in->ioset,
			(unsigned)in->freq);

	/* initialize the QSPI */
	qspi_initialize(addr);
	qspi_set_baudrate(addr, in->freq);

	/* initialize the QSPI flash */
	if (!qspiflash_configure(&flash, addr)) {
		trace_error_wp("Error while detecting QSPI flash chip\r\n");
		return APPLET_DEV_UNKNOWN;
	}

	trace_info_wp("QSPI flash drivers initialized\r\n");

	if (!flash.desc.jedec_id) {
		trace_error_wp("Device Unknown\r\n");
		return APPLET_DEV_UNKNOWN;
	}
	else {
		uint32_t page_size = flash.desc.page_size;
		uint32_t mem_size = flash.desc.num_blocks * flash.desc.block_size;

		trace_info_wp("Found Device %s\r\n", flash.desc.name);
		trace_info_wp("Size: %d bytes\r\n", (int)mem_size);
		trace_info_wp("Page Size: %d bytes\r\n", (int)page_size);
		trace_info_wp("Block Size: %d bytes\r\n", (int)flash.desc.block_size);

		buffer_size = flash.desc.block_size;

		/* round buffer size to a multiple of page_size */
		buffer_size = buffer_size & ~(page_size - 1);
		if (buffer_size < page_size || buffer_size > MAX_BUFFER_SIZE) {
			trace_error_wp("Not enough memory for transfer buffer\r\n");
			return APPLET_FAIL;
		}

		out->buf_addr = (uint32_t)buffer;
		out->buf_size = buffer_size;
		out->mem_size = mem_size;

		trace_info_wp("Buffer Address: 0x%lx\r\n", out->buf_addr);
		trace_info_wp("Buffer Size: 0x%lx\r\n", out->buf_size);

		initialized = true;
		return APPLET_SUCCESS;
	}
}

static uint32_t handle_cmd_write(uint32_t cmd, uint32_t *args)
{
	struct input_write *in = (struct input_write *)args;
	struct output_write *out = (struct output_write *)args;

	uint8_t *buffer_end = buffer + sizeof(buffer);
	uint8_t *buf = (uint8_t*)in->buf_addr;
	uint32_t size = in->buf_size;
	uint32_t offset = in->mem_offset;

	assert(cmd == APPLET_CMD_WRITE);

	/* check that mailbox buffer is contained in our buffer zone */
	if (buf < buffer || buf >= buffer_end) {
		trace_error("Invalid buffer address\r\n");
		return APPLET_FAIL;
	}

	/* check that requested size does not overflow buffer */
	if ((buf + size) > buffer_end) {
		size = buffer_end - buf;
		trace_warning("Buffer overflow: %d bytes is too much, will use %d instead\r\n",
				(int)in->buf_size, (int)size);
	}

	/* perform the write operation */
	if (!qspiflash_write(&flash, offset, buf, size)) {
		trace_error("Write error\r\n");
		out->bytes_written = 0;
		return APPLET_WRITE_FAIL;
	}

	trace_info_wp("Wrote %lu bytes at 0x%lx\r\n", size, in->mem_offset);
	out->bytes_written = size;
	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read(uint32_t cmd, uint32_t *args)
{
	struct input_read *in = (struct input_read *)args;
	struct output_read *out = (struct output_read *)args;

	uint8_t *buffer_end = buffer + sizeof(buffer);

	uint8_t *buf = (uint8_t*)in->buf_addr;
	uint32_t size = in->buf_size;
	uint32_t offset = in->mem_offset;

	assert(cmd == APPLET_CMD_READ);

	/* check that mailbox buffer is contained in our buffer zone */
	if (buf < buffer || buf >= buffer_end) {
		trace_error("Invalid buffer address\r\n");
		return APPLET_FAIL;
	}

	/* check that requested size does not overflow buffer */
	if ((buf + size) > buffer_end) {
		size = buffer_end - buf;
		trace_warning("Buffer overflow: %d bytes is too much, will use %d instead\r\n",
				(int)in->buf_size, (int)size);
	}

	/* perform the read operation */
	if (!qspiflash_read(&flash, offset, buf, size)) {
		trace_error("Read error\r\n");
		out->bytes_read = 0;
		return APPLET_READ_FAIL;
	}

	trace_info_wp("Read %lu bytes at 0x%lx\r\n", size, in->mem_offset);
	out->bytes_read = size;
	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_full_erase(uint32_t cmd, uint32_t *args)
{
	assert(cmd == APPLET_CMD_FULL_ERASE);

	/* unused argument */
	(void)args;

	if (!qspiflash_erase_chip(&flash)) {
		return APPLET_ERASE_FAIL;
	}

	trace_info_wp("Full erase completed.\r\n");
	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_buffer_erase(uint32_t cmd, uint32_t *args)
{
	struct input_buffer_erase *in = (struct input_buffer_erase *)args;
	struct output_buffer_erase *out = (struct output_buffer_erase *)args;
	uint32_t offset = in->mem_offset;

	assert(cmd == APPLET_CMD_BUFFER_ERASE);

	if (offset & (flash.desc.block_size - 1)) {
		trace_warning("Unaligned Block Erase offset: 0x%lx\r\n", offset);
		return APPLET_FAIL;
	}

	if (!qspiflash_erase_block(&flash, offset, false)) {
		trace_error("Block Erase failed at offset 0x%lx\r\n", offset);
		return APPLET_ERASE_FAIL;
	}

	trace_info_wp("Erased %d bytes at 0x%lx\r\n", (int)flash.desc.block_size,
			in->mem_offset & ~(flash.desc.block_size - 1));
	out->bytes_erased = flash.desc.block_size;
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
