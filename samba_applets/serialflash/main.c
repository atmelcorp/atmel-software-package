/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
#include "misc/console.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/spid.h"
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

/* Instance/IOSet PIO configuration */
struct pio_definition
{
	uint32_t           instance;
	uint32_t           ioset;
	uint32_t           cs;
	Spi*               addr;
	uint32_t           num_pins;
	const struct _pin *pins;
};

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_SOC_SAMA5D2)
static const struct _pin spi0_npcs0_ioset1[] = PINS_SPI0_NPCS0_IOS1;
static const struct _pin spi0_npcs1_ioset1[] = PINS_SPI0_NPCS1_IOS1;
static const struct _pin spi0_npcs2_ioset1[] = PINS_SPI0_NPCS2_IOS1;
static const struct _pin spi0_npcs3_ioset1[] = PINS_SPI0_NPCS3_IOS1;
static const struct _pin spi0_npcs0_ioset2[] = PINS_SPI0_NPCS0_IOS2;
static const struct _pin spi0_npcs1_ioset2[] = PINS_SPI0_NPCS1_IOS2;
static const struct _pin spi0_npcs2_ioset2[] = PINS_SPI0_NPCS2_IOS2;
static const struct _pin spi0_npcs3_ioset2[] = PINS_SPI0_NPCS3_IOS2;
static const struct _pin spi1_npcs0_ioset1[] = PINS_SPI1_NPCS0_IOS1;
static const struct _pin spi1_npcs1_ioset1[] = PINS_SPI1_NPCS1_IOS1;
static const struct _pin spi1_npcs2_ioset1[] = PINS_SPI1_NPCS2_IOS1;
static const struct _pin spi1_npcs3_ioset1[] = PINS_SPI1_NPCS3_IOS1;
static const struct _pin spi1_npcs0_ioset2[] = PINS_SPI1_NPCS0_IOS2;
static const struct _pin spi1_npcs1_ioset2[] = PINS_SPI1_NPCS1_IOS2;
static const struct _pin spi1_npcs2_ioset2[] = PINS_SPI1_NPCS2_IOS2;
static const struct _pin spi1_npcs3_ioset2[] = PINS_SPI1_NPCS3_IOS2;
static const struct _pin spi1_npcs0_ioset3[] = PINS_SPI1_NPCS0_IOS3;
static const struct _pin spi1_npcs1_ioset3[] = PINS_SPI1_NPCS1_IOS3;
static const struct _pin spi1_npcs2_ioset3[] = PINS_SPI1_NPCS2_IOS3;

static const struct pio_definition pio_definitions[] = {
	{ 0, 1, 0, SPI0, ARRAY_SIZE(spi0_npcs0_ioset1), spi0_npcs0_ioset1 },
	{ 0, 1, 1, SPI0, ARRAY_SIZE(spi0_npcs1_ioset1), spi0_npcs1_ioset1 },
	{ 0, 1, 2, SPI0, ARRAY_SIZE(spi0_npcs2_ioset1), spi0_npcs2_ioset1 },
	{ 0, 1, 3, SPI0, ARRAY_SIZE(spi0_npcs3_ioset1), spi0_npcs3_ioset1 },
	{ 0, 2, 0, SPI0, ARRAY_SIZE(spi0_npcs0_ioset2), spi0_npcs0_ioset2 },
	{ 0, 2, 1, SPI0, ARRAY_SIZE(spi0_npcs1_ioset2), spi0_npcs1_ioset2 },
	{ 0, 2, 2, SPI0, ARRAY_SIZE(spi0_npcs2_ioset2), spi0_npcs2_ioset2 },
	{ 0, 2, 3, SPI0, ARRAY_SIZE(spi0_npcs3_ioset2), spi0_npcs3_ioset2 },
	{ 1, 1, 0, SPI1, ARRAY_SIZE(spi1_npcs0_ioset1), spi1_npcs0_ioset1 },
	{ 1, 1, 1, SPI1, ARRAY_SIZE(spi1_npcs1_ioset1), spi1_npcs1_ioset1 },
	{ 1, 1, 2, SPI1, ARRAY_SIZE(spi1_npcs2_ioset1), spi1_npcs2_ioset1 },
	{ 1, 1, 3, SPI1, ARRAY_SIZE(spi1_npcs3_ioset1), spi1_npcs3_ioset1 },
	{ 1, 2, 0, SPI1, ARRAY_SIZE(spi1_npcs0_ioset2), spi1_npcs0_ioset2 },
	{ 1, 2, 1, SPI1, ARRAY_SIZE(spi1_npcs1_ioset2), spi1_npcs1_ioset2 },
	{ 1, 2, 2, SPI1, ARRAY_SIZE(spi1_npcs2_ioset2), spi1_npcs2_ioset2 },
	{ 1, 2, 3, SPI1, ARRAY_SIZE(spi1_npcs3_ioset2), spi1_npcs3_ioset2 },
	{ 1, 3, 0, SPI1, ARRAY_SIZE(spi1_npcs0_ioset3), spi1_npcs0_ioset3 },
	{ 1, 3, 1, SPI1, ARRAY_SIZE(spi1_npcs1_ioset3), spi1_npcs1_ioset3 },
	{ 1, 3, 2, SPI1, ARRAY_SIZE(spi1_npcs2_ioset3), spi1_npcs2_ioset3 },
};
#elif defined(CONFIG_SOC_SAMA5D4)
static const struct _pin spi0_npcs0[] = PINS_SPI0_NPCS0;
static const struct _pin spi0_npcs1[] = PINS_SPI0_NPCS1;
static const struct _pin spi0_npcs1_alt[] = PINS_SPI0_NPCS1_ALT;
static const struct _pin spi0_npcs2[] = PINS_SPI0_NPCS2;
static const struct _pin spi0_npcs2_alt[] = PINS_SPI0_NPCS2_ALT;
static const struct _pin spi0_npcs3[] = PINS_SPI0_NPCS3;
static const struct _pin spi1_npcs0[] = PINS_SPI1_NPCS0;
static const struct _pin spi1_npcs1[] = PINS_SPI1_NPCS1;
static const struct _pin spi1_npcs1_alt[] = PINS_SPI1_NPCS1_ALT;
static const struct _pin spi1_npcs2[] = PINS_SPI1_NPCS2;
static const struct _pin spi1_npcs2_alt[] = PINS_SPI1_NPCS2_ALT;
static const struct _pin spi1_npcs3[] = PINS_SPI1_NPCS3;
static const struct _pin spi1_npcs3_alt[] = PINS_SPI1_NPCS3_ALT;
static const struct _pin spi2_npcs0[] = PINS_SPI2_NPCS0;
static const struct _pin spi2_npcs1[] = PINS_SPI2_NPCS1;
static const struct _pin spi2_npcs2[] = PINS_SPI2_NPCS2;
static const struct _pin spi2_npcs3[] = PINS_SPI2_NPCS3;

static const struct pio_definition pio_definitions[] = {
	{ 0, 1, 0, SPI0, ARRAY_SIZE(spi0_npcs0),     spi0_npcs0 },
	{ 0, 1, 1, SPI0, ARRAY_SIZE(spi0_npcs1),     spi0_npcs1 },
	{ 0, 1, 2, SPI0, ARRAY_SIZE(spi0_npcs2),     spi0_npcs2 },
	{ 0, 1, 3, SPI0, ARRAY_SIZE(spi0_npcs3),     spi0_npcs3 },
	{ 0, 2, 1, SPI0, ARRAY_SIZE(spi0_npcs1_alt), spi0_npcs1_alt },
	{ 0, 2, 2, SPI0, ARRAY_SIZE(spi0_npcs2_alt), spi0_npcs2_alt },
	{ 1, 1, 0, SPI1, ARRAY_SIZE(spi1_npcs0),     spi1_npcs0 },
	{ 1, 1, 1, SPI1, ARRAY_SIZE(spi1_npcs1),     spi1_npcs1 },
	{ 1, 1, 2, SPI1, ARRAY_SIZE(spi1_npcs2),     spi1_npcs2 },
	{ 1, 1, 3, SPI1, ARRAY_SIZE(spi1_npcs3),     spi1_npcs3 },
	{ 1, 2, 1, SPI1, ARRAY_SIZE(spi1_npcs1_alt), spi1_npcs1_alt },
	{ 1, 2, 2, SPI1, ARRAY_SIZE(spi1_npcs2_alt), spi1_npcs2_alt },
	{ 1, 2, 3, SPI1, ARRAY_SIZE(spi1_npcs3_alt), spi1_npcs3_alt },
	{ 2, 1, 0, SPI2, ARRAY_SIZE(spi2_npcs0),     spi2_npcs0 },
	{ 2, 1, 1, SPI2, ARRAY_SIZE(spi2_npcs1),     spi2_npcs1 },
	{ 2, 1, 2, SPI2, ARRAY_SIZE(spi2_npcs2),     spi2_npcs2 },
	{ 2, 1, 3, SPI2, ARRAY_SIZE(spi2_npcs3),     spi2_npcs3 },
};
#endif

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
	int i;
	for (i = 0; i < ARRAY_SIZE(pio_definitions); i++) {
		const struct pio_definition* def = &pio_definitions[i];
		if (def->instance == instance && def->ioset == ioset &&
				def->cs == cs) {
			*addr = def->addr;
			pio_configure(def->pins, def->num_pins);
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
	uint32_t written = 0;
	uint32_t offset = in->mem_offset;
	uint8_t *tmp_buf;

	assert(cmd == APPLET_CMD_WRITE);

	/* provision space for head and/or tail handling if we are not
	 * 4K-aligned */
	tmp_buf = buf + size;

	/* check that mailbox buffer is contained in our buffer zone */
	if (buf < buffer || buf >= buffer_end) {
		trace_error("Invalid buffer address\r\n");
		return APPLET_FAIL;
	}

	/* check that requested size does not overflow buffer */
	if ((tmp_buf + 4096) > buffer_end) {
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	while (size > 0) {
		uint8_t *data = buf;
		uint32_t head = offset & 4095;
		uint32_t count = MIN(size, 4096 - head);
		uint32_t tail = (offset + count) & 4095;

		/* handle read/update if partial block update */
		if (head || tail) {
			data = tmp_buf;
			offset &= ~4095;

			/* read data to be updated */
			at25_read(&at25drv, offset, data, 4096);

			/* copy data to be overwritten */
			memcpy(data + head, buf, count);
		}

		/* erase block */
		at25_erase_block(&at25drv, offset, AT25_ERASE_4K);
		at25_wait(&at25drv);

		/* write block */
		at25_write(&at25drv, offset, data, 4096);
		at25_wait(&at25drv);

		/* update position */
		offset += 4096;
		written += count;
		buf += count;
		size -= count;
	}

	trace_info_wp("Wrote %u bytes at 0x%x\r\n", (unsigned)written,
			(unsigned)in->mem_offset);
	out->bytes_written = written;
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

	/* check that mailbox buffer is contained in our buffer zone */
	if (buf < buffer || buf >= buffer_end) {
		trace_error("Invalid buffer address\r\n");
		return APPLET_FAIL;
	}

	/* check that requested size does not overflow buffer */
	if ((buf + size) > buffer_end) {
		size = buffer_end - buf;
		trace_warning("Buffer overflow: size %u is too much, "
				"will use %u instead\r\n",
				(unsigned)in->buf_size, (unsigned)size);
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
	uint32_t count = 0, incr = 0, i;

	assert(cmd == APPLET_CMD_BUFFER_ERASE);

	if (offset & (64 * 1024 - 1)) {
		trace_error("Unaligned Block Erase offset: 0x%x\r\n",
				(unsigned)offset);
		return APPLET_FAIL;
	}

	if (at25drv.desc->erase_support & AT25_ERASE_64K) {
		erase_type = AT25_ERASE_64K;
		count = 1;
		incr = 64 * 1024;
	} else if (at25drv.desc->erase_support & AT25_ERASE_32K) {
		erase_type = AT25_ERASE_32K;
		count = 2;
		incr = 32 * 1024;
	} else if (at25drv.desc->erase_support & AT25_ERASE_4K) {
		erase_type = AT25_ERASE_4K;
		count = 16;
		incr = 4 * 1024;
	} else {
		trace_error("Memory supports neither 4K, 32K nor 64K erase\r\n");
		return APPLET_FAIL;
	}

	for (i = 0; i < count; i++, offset += incr) {
		if (at25_erase_block(&at25drv, offset,
					erase_type) != AT25_SUCCESS) {
			trace_error("Block Erase failed at offset 0x%x\r\n",
					(unsigned)offset);
			return APPLET_ERASE_FAIL;
		}
		at25_wait(&at25drv);
	}

	trace_info_wp("Erased %u bytes at 0x%x\r\n", (unsigned)(count * incr),
			(unsigned)in->mem_offset);
	out->bytes_erased = count * incr;
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
