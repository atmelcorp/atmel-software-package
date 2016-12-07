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

#include "pin_defs.h"
#include "serial/console.h"
#include "mm/cache.h"
#include "peripherals/sdmmc.h"
#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "gpio/pio.h"
#include "libsdmmc/libsdmmc.h"

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#if !defined(CONFIG_SOC_SAMA5D2)
#error Unsupported SOC!
#endif

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* mask for board capabilities defines: voltage, slot type and 8-bit support */
#define CAPS0_MASK (SDMMC_CA0R_V33VSUP | SDMMC_CA0R_V30VSUP | \
                    SDMMC_CA0R_V18VSUP | SDMMC_CA0R_SLTYPE_Msk | \
                    SDMMC_CA0R_ED8SUP)

/* Allocate 2 Timers/Counters, that are not used already by the libraries and
 * drivers this applet depends on. */
#define TIMER0_MODULE                 ID_TC0
#define TIMER0_CHANNEL                0

#define BLOCK_SIZE                    512u

#define EMMC_BOOT_PARTITION_ACCESS(p) (p << 0)
#define EMMC_BOOT_PARTITION_ENABLE(p) (p << 3)
#define EMMC_BOOT_ACK                 (1 << 6)

#define SUPPORTED_VOLTAGE_18V         (1 << 0)
#define SUPPORTED_VOLTAGE_30V         (1 << 1)
#define SUPPORTED_VOLTAGE_33V         (1 << 2)
#define SUPPORTED_VOLTAGE_MASK        (SUPPORTED_VOLTAGE_18V |\
                                       SUPPORTED_VOLTAGE_30V |\
                                       SUPPORTED_VOLTAGE_33V)

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static uint8_t* buffer;

static uint32_t buffer_size;

static uint32_t mem_size;

/* Driver instance data (a.k.a. MCI driver instance) */
static struct sdmmc_set drv;

/* Library instance data (a.k.a. SDCard driver instance) */
CACHE_ALIGNED static sSdCard lib;

/* Reserved memory for SDMMC DMA descriptors */
static uint32_t dma_table[32 * SDMMC_DMADL_SIZE];

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/
 
static void get_data_pins(const struct sdmmc_pin_definition* def,
		uint32_t bus_width, const struct _pin **pins_data,
		uint32_t *num_pins)
{
	if (bus_width == 1) {
		*pins_data = def->pins_data1b;
		*num_pins = def->num_pins_data1b;
	} else if (bus_width == 4) {
		*pins_data = def->pins_data4b;
		*num_pins = def->num_pins_data4b;
	} else if (bus_width == 8) {
		*pins_data = def->pins_data8b;
		*num_pins = def->num_pins_data8b;
	} else {
		*pins_data = NULL;
		*num_pins = 0;
	}
}

static int get_max_bus_width(const struct sdmmc_pin_definition* def)
{
	if (def->num_pins_data8b)
		return 8;
	else if (def->num_pins_data4b)
		return 4;
	else if (def->num_pins_data1b)
		return 1;
	return 0;
}

static void unconfigure_all_data_pins(const struct sdmmc_pin_definition* def)
{
	const struct _pin *pins_data;
	uint32_t num_pins, i;

	get_data_pins(def, get_max_bus_width(def), &pins_data, &num_pins);

	for (i = 0; i < num_pins; i++) {
		struct _pin pin = pins_data[i];
		pin.type = PIO_INPUT;
		pin.attribute = PIO_PULLUP;
		pio_configure(&pin, 1);
	}
}

static const struct sdmmc_pin_definition* find_instance(uint32_t instance)
{
	int i;
	for (i = 0; i < num_sdmmc_pin_defs; i++) {
		if (sdmmc_pin_defs[i].instance == instance)
			return &sdmmc_pin_defs[i];
	}
	return 0;
}

static void configure_instance_pio(const struct sdmmc_pin_definition* def,
		uint32_t bus_width, uint32_t supported_voltages)
{
	const struct _pin *pins_data;
	uint32_t num_pins_data;

	get_data_pins(def, bus_width, &pins_data, &num_pins_data);
	if (!pins_data || !num_pins_data)
		return;

	// configure pins
	pio_configure(def->pin_ck, 1);
	pio_configure(def->pin_cmd, 1);
	unconfigure_all_data_pins(def);
	pio_configure(pins_data, num_pins_data);
	if (def->pin_vdd_sel) {
		if (supported_voltages ==
				SUPPORTED_VOLTAGE_18V) {
			// only 1.8V, force VDD_SEL to 1
			struct _pin pin = *def->pin_vdd_sel;
			pin.type = PIO_OUTPUT_1;
			pin.attribute = PIO_DEFAULT;
			pio_configure(&pin, 1);
		} else {
			// let SDMMC controller drive VDD_SEL
			pio_configure(def->pin_vdd_sel, 1);
		}
	}
}

static char* get_supported_voltage_string(uint32_t supported_voltages)
{
	static char str[5 * 3 + 1];
	str[0] = 0;
	if (supported_voltages & SUPPORTED_VOLTAGE_18V)
		strcat(str, "1.8V/");
	if (supported_voltages & SUPPORTED_VOLTAGE_30V)
		strcat(str, "3.0V/");
	if (supported_voltages & SUPPORTED_VOLTAGE_33V)
		strcat(str, "3.3V/");
	str[strlen(str) - 1] = 0;
	return str;
}

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;
	uint32_t instance = mbx->in.parameters[0];
	uint32_t boot_partition = mbx->in.parameters[1];
	uint32_t bus_width = mbx->in.parameters[2];
	uint32_t supported_voltages = mbx->in.parameters[3];
	const struct sdmmc_pin_definition* instance_def;
	uint32_t max_bus_width, sdmmc_id, caps0;
	uint8_t rc, card_type;

	assert(cmd == APPLET_CMD_INITIALIZE);

	applet_set_init_params(mbx->in.comm_type, mbx->in.trace_level);

	trace_info_wp("\r\nApplet 'SD/MMC' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	if (bus_width != 0 && bus_width != 1 &&
			bus_width != 4 && bus_width != 8) {
		trace_error_wp("Invalid configuration: Unsupported bus width %u\r\n",
			(unsigned)bus_width);
		return APPLET_FAIL;
	}

	if (!supported_voltages || (supported_voltages & ~SUPPORTED_VOLTAGE_MASK)) {
		trace_error_wp("Invalid supported voltages value: 0x%x\r\n",
			(unsigned)supported_voltages);
		return APPLET_FAIL;
	}

	instance_def = find_instance(instance);
	if (!instance_def) {
		trace_error_wp("Invalid configuration: SDMMC%u\r\n",
			(unsigned)instance);
		return APPLET_FAIL;
	}

	max_bus_width = get_max_bus_width(instance_def);
	if (!bus_width) {
		bus_width = max_bus_width;
	} else if (bus_width > max_bus_width) {
		trace_error_wp("Invalid configuration: SDMMC%u Bus Width %u\r\n",
			(unsigned)instance, (unsigned)bus_width);
		return APPLET_FAIL;
	}

	if (boot_partition > 2) {
		trace_error_wp("Invalid configuration: Unknown partition %u\r\n",
			(unsigned)boot_partition);
		return APPLET_FAIL;
	}

	trace_info_wp("Initializing SDMMC%u", (unsigned)instance);
	if (boot_partition)
		trace_info_wp(", boot partition %u",
				(unsigned)boot_partition);
	else
		trace_info_wp(", user partition");
	if (bus_width == 1)
		trace_info_wp(", 1-bit");
	else if (bus_width == 4)
		trace_info_wp(", 4-bit");
	else if (bus_width == 8)
		trace_info_wp(", 8-bit");
	trace_info_wp(", %s",
			get_supported_voltage_string(supported_voltages));
	trace_info_wp("\r\n");

	/* Configure PIO */
	configure_instance_pio(instance_def, bus_width, supported_voltages);

	/* The SDMMC peripherals are clocked by their Peripheral Clock, the
	 * Master Clock, and a Generated Clock (at least on SAMA5D2x).
	 * Configure GCLKx = <PLLA clock> divided by 1
	 * As of writing, the PLLA clock runs at 498 MHz */
	sdmmc_id = get_sdmmc_id_from_addr(instance_def->addr);
	struct _pmc_periph_cfg cfg = {
		.gck = {
			.css = PMC_PCR_GCKCSS_PLLA_CLK,
			.div = 1,
		},
	};
	pmc_configure_peripheral(sdmmc_id, &cfg, true);

	// set SDMMC controller capabilities
	caps0 = SDMMC_CA0R_SLTYPE_EMBEDDED;
	if (bus_width == 8)
		caps0 |= SDMMC_CA0R_ED8SUP;
	if (supported_voltages & SUPPORTED_VOLTAGE_18V)
		caps0 |= SDMMC_CA0R_V18VSUP;
	if (supported_voltages & SUPPORTED_VOLTAGE_30V)
		caps0 |= SDMMC_CA0R_V30VSUP;
	if (supported_voltages & SUPPORTED_VOLTAGE_33V)
		caps0 |= SDMMC_CA0R_V33VSUP;
	sdmmc_set_capabilities(instance_def->addr,
			caps0, CAPS0_MASK, 0, 0);

	sdmmc_initialize(&drv, sdmmc_id, TIMER0_MODULE, TIMER0_CHANNEL,
			dma_table, ARRAY_SIZE(dma_table), true);

	SDD_InitializeSdmmcMode(&lib, &drv, 0);
	if (SD_GetStatus(&lib) == SDMMC_NOT_SUPPORTED) {
		trace_error_wp("Device not detected.\n\r");
		return APPLET_FAIL;
	}

	rc = SD_Init(&lib);
	if (rc != SDMMC_OK) {
		trace_error_wp("SD/MMC device initialization failed: %d\n\r", rc);
		return APPLET_FAIL;
	}

	card_type = SD_GetCardType(&lib);
	if (!(card_type & CARD_TYPE_bmSDMMC)) {
		trace_error_wp("Invalid card type: only SD/MMC is supported\n\r");
		return APPLET_FAIL;
	}

	SD_DumpStatus(&lib);

	if (boot_partition) {
		/* check that card is MMC */
		if (!(card_type & CARD_TYPE_bmMMC)) {
			trace_error_wp("Invalid card type: boot partition in only supported on MMC\n\r");
			return APPLET_FAIL;
		}

		/* get and check boot partition size */
		mem_size = MMC_EXT_BOOT_SIZE_MULTI(lib.EXT) * (128 * 1024 / BLOCK_SIZE);
		if (mem_size == 0) {
			trace_error_wp("No boot partition available\n\r");
			return APPLET_FAIL;
		}

		/* configure boot partition */
		mmc_configure_partition(&lib, EMMC_BOOT_PARTITION_ACCESS(boot_partition) |
		                              EMMC_BOOT_PARTITION_ENABLE(boot_partition) |
		                              EMMC_BOOT_ACK);
		mmc_configure_boot_bus(&lib, 0);
	} else {
		mem_size = SD_GetTotalSizeKB(&lib) * 1024 / BLOCK_SIZE;
	}

	buffer = applet_buffer;
	buffer_size = applet_buffer_size & ~(BLOCK_SIZE - 1);
	if (buffer_size == 0) {
		trace_info_wp("Not enough memory for buffer\r\n");
		return APPLET_FAIL;
	}

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = BLOCK_SIZE;
	mbx->out.mem_size = mem_size;
	mbx->out.erase_support = 0;
	mbx->out.nand_header = 0;

	trace_info_wp("SD/MMC device initialization successful\n\r");
	trace_info_wp("Buffer Address: 0x%lx\r\n", mbx->out.buf_addr);
	trace_info_wp("Buffer Size: %ld bytes\r\n", mbx->out.buf_size);
	trace_info_wp("Page Size: %ld bytes\r\n", mbx->out.page_size);
	trace_info_wp("Memory Size: %ld pages\r\n", mbx->out.mem_size);

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_info(uint32_t cmd, uint32_t *mailbox)
{
	/* 'read info' uses the same mailbox output as 'initialize' */
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_READ_INFO);

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = BLOCK_SIZE;
	mbx->out.mem_size = mem_size;
	mbx->out.erase_support = 0;
	mbx->out.nand_header = 0;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_write_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset;
	uint32_t length = mbx->in.length;

	assert(cmd == APPLET_CMD_WRITE_PAGES);

	/* check that requested size does not overflow buffer */
	if ((length * BLOCK_SIZE) > buffer_size) {
		trace_error_wp("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* check that requested offset/size does not overflow memory */
	if (offset + length > mem_size) {
		trace_error_wp("Memory overflow\r\n");
		return APPLET_FAIL;
	}

	if (SD_Write(&lib, offset, buffer, length, NULL, NULL) != SDMMC_OK) {
		trace_info_wp("Error while writing %u bytes at offset 0x%08x\r\n",
				(unsigned)(mbx->in.length * BLOCK_SIZE),
				(unsigned)(mbx->in.offset * BLOCK_SIZE));
		mbx->out.pages = 0;
		return APPLET_READ_FAIL;
	}

	trace_info_wp("Wrote %u bytes at offset 0x%08x\r\n",
			(unsigned)(mbx->in.length * BLOCK_SIZE),
			(unsigned)(mbx->in.offset * BLOCK_SIZE));
	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_write_erase_pages_mailbox *mbx =
		(union read_write_erase_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset;
	uint32_t length = mbx->in.length;

	assert(cmd == APPLET_CMD_READ_PAGES);

	/* check that requested size does not overflow buffer */
	if ((length * BLOCK_SIZE) > buffer_size) {
		trace_error_wp("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* check that requested offset/size does not overflow memory */
	if (offset + length > mem_size) {
		trace_error_wp("Memory overflow\r\n");
		return APPLET_FAIL;
	}

	if (SD_Read(&lib, offset, buffer, length, NULL, NULL) != SDMMC_OK) {
		trace_info_wp("Error while reading %u bytes at offset 0x%08x\r\n",
				(unsigned)(mbx->in.length * BLOCK_SIZE),
				(unsigned)(mbx->in.offset * BLOCK_SIZE));
		mbx->out.pages = 0;
		return APPLET_READ_FAIL;
	}

	trace_info_wp("Read %u bytes at offset 0x%08x\r\n",
			(unsigned)(mbx->in.length * BLOCK_SIZE),
			(unsigned)(mbx->in.offset * BLOCK_SIZE));
	mbx->out.pages = mbx->in.length;

	return APPLET_SUCCESS;
}


/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ APPLET_CMD_READ_INFO, handle_cmd_read_info },
	{ APPLET_CMD_WRITE_PAGES, handle_cmd_write_pages },
	{ APPLET_CMD_READ_PAGES, handle_cmd_read_pages },
	{ 0, NULL }
};
