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
#ifdef CONFIG_HAVE_HSMCI
#include "sdmmc/hsmci.h"
#include "sdmmc/hsmcid.h"
#endif
#ifdef CONFIG_HAVE_SDMMC
#include "sdmmc/sdmmc.h"
#endif
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

/*----------------------------------------------------------------------------
 *        Local type definitions
 *----------------------------------------------------------------------------*/

struct _sdmmc_applet_config {
	uint32_t instance;
	uint32_t ioset;
	uint32_t boot_partition;
	uint32_t bus_width;
#ifdef CONFIG_HAVE_SDMMC
	uint32_t supported_voltages;
#endif
};

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* mask for board capabilities defines: voltage, slot type and 8-bit support */
#define CAPS0_MASK (SDMMC_CA0R_V33VSUP | SDMMC_CA0R_V30VSUP | \
                    SDMMC_CA0R_V18VSUP | SDMMC_CA0R_SLTYPE_Msk | \
                    SDMMC_CA0R_ED8SUP)

/* Allocate a Timer/Counter that is not used already by the libraries and
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

#if defined(CONFIG_HAVE_SDMMC)

/* Driver instance data (a.k.a. MCI driver instance) */
static struct sdmmc_set drv;

/* Reserved memory for SDMMC DMA descriptors */
static uint32_t dma_table[32 * SDMMC_DMADL_SIZE];

#elif defined(CONFIG_HAVE_HSMCI)

/* Driver configuration data (a.k.a. MCI driver configuration) */
static struct _hsmci_cfg drv_config;

/* Driver instance data (a.k.a. MCI driver instance) */
static struct _hsmci_set drv;

#endif

/* Library instance data (a.k.a. SDCard driver instance) */
CACHE_ALIGNED static sSdCard lib;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/
 
static void get_data_pins(const struct sdmmc_pin_definition* def,
		uint32_t bus_width, const struct _pin **pins_data,
		uint32_t *num_pins)
{
	switch (bus_width) {
	case 1:
		*pins_data = def->pins_data1b;
		*num_pins = def->num_pins_data1b;
		break;
	case 4:
		*pins_data = def->pins_data4b;
		*num_pins = def->num_pins_data4b;
		break;
	case 8:
		*pins_data = def->pins_data8b;
		*num_pins = def->num_pins_data8b;
		break;
	default:
		*pins_data = NULL;
		*num_pins = 0;
		break;
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

static const struct sdmmc_pin_definition* find_instance(
		struct _sdmmc_applet_config* config)
{
	int i;
	for (i = 0; i < num_sdmmc_pin_defs; i++) {
		if (sdmmc_pin_defs[i].instance == config->instance &&
		    sdmmc_pin_defs[i].ioset == config->ioset)
			return &sdmmc_pin_defs[i];
	}
	return 0;
}

static void configure_instance_pio(const struct sdmmc_pin_definition* def,
		struct _sdmmc_applet_config* config)
{
	const struct _pin *pins_data;
	uint32_t num_pins_data;

	get_data_pins(def, config->bus_width, &pins_data, &num_pins_data);
	if (!pins_data || !num_pins_data)
		return;

	// configure pins
	pio_configure(def->pin_ck, 1);
	pio_configure(def->pin_cmd, 1);
	unconfigure_all_data_pins(def);
	pio_configure(pins_data, num_pins_data);
#ifdef CONFIG_HAVE_SDMMC
	if (def->pin_vdd_sel) {
		if (config->supported_voltages ==
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
#endif /* CONFIG_HAVE_SDMMC */
}

#ifdef CONFIG_HAVE_SDMMC
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

#ifdef CONFIG_SOC_SAMA5D2
static int sdmmc_pre_init(uint32_t id)
{
	/* The SDMMC peripherals are clocked by their Peripheral Clock, the
	 * Master Clock, and a Generated Clock (at least on SAMA5D2x).
	 * Configure GCLKx = <PLLA clock> divided by 1
	 * As of writing, the PLLA clock runs at 498 MHz */
	struct _pmc_periph_cfg cfg = {
		.gck = {
			.css = PMC_PCR_GCKCSS_PLLA_CLK,
			.div = 1,
		},
	};
	pmc_configure_peripheral(id, &cfg, true);

	return 0;
}
#endif /* CONFIG_SOC_SAMA5D2 */

#ifdef CONFIG_SOC_SAM9X60
#define MULTCLK_100MHZ  100000000U

static int sdmmc_pre_init(uint32_t id)
{
	struct _pmc_periph_cfg cfg;
	uint32_t caps0, caps0_mask;
	uint32_t plla_clk, baseclkf;

	plla_clk = pmc_get_plla_clock();

	/*
	 * The MULTCLK is the connected to the SDMMC generated clock:
	 * we target a 100MHz MULTCLK.
	 */
	memset(&cfg, 0, sizeof(cfg));
	cfg.gck.css = PMC_PCR_GCKCSS_PLLA_CLK;
	cfg.gck.div = ROUND_INT_DIV(plla_clk, MULTCLK_100MHZ);
	pmc_configure_peripheral(id, &cfg, true);

	/* There is a hardware divider of 2 between MULTCLK and BASECLK. */
	baseclkf = (pmc_get_gck_clock(id) >> 1) / 1000000U;

	caps0_mask = SDMMC_CA0R_TEOCLKF_Msk |
		     SDMMC_CA0R_TEOCLKU |
		     SDMMC_CA0R_BASECLKF_Msk;
	caps0 = SDMMC_CA0R_TEOCLKF(baseclkf) |
		SDMMC_CA0R_TEOCLKU |
		SDMMC_CA0R_BASECLKF(baseclkf);

	sdmmc_set_capabilities(get_sdmmc_addr_from_id(id),
			       caps0, caps0_mask, 0, 0);

	return 0;
}
#endif /* CONFIG_SOC_SAM9X60 */
#endif /* CONFIG_HAVE_SDMMC */

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;
	struct _sdmmc_applet_config config;
	const struct sdmmc_pin_definition* instance_def;
	uint32_t max_bus_width, id;
	uint8_t rc, card_type;

	assert(cmd == APPLET_CMD_INITIALIZE);

	if (!applet_set_init_params(mbx))
		return APPLET_FAIL;

	trace_warning_wp("\r\nApplet 'SD/MMC' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	config.instance = mbx->in.parameters[0];
	config.ioset = mbx->in.parameters[1];
	instance_def = find_instance(&config);
	if (!instance_def) {
		trace_error("Invalid configuration: Instance %u I/O Set %u\r\n",
			(unsigned)config.instance,
			(unsigned)config.ioset);
		return APPLET_FAIL;
	}

	config.boot_partition = mbx->in.parameters[2];
	if (config.boot_partition > 2) {
		trace_error("Invalid configuration: Unknown partition %u\r\n",
			(unsigned)config.boot_partition);
		return APPLET_FAIL;
	}

	config.bus_width = mbx->in.parameters[3];
	if (config.bus_width != 0 && config.bus_width != 1 &&
	    config.bus_width != 4 && config.bus_width != 8) {
		trace_error("Invalid configuration: Unsupported bus width %u\r\n",
			(unsigned)config.bus_width);
		return APPLET_FAIL;
	}

	max_bus_width = get_max_bus_width(instance_def);
	if (!config.bus_width) {
		config.bus_width = max_bus_width;
	} else if (config.bus_width > max_bus_width) {
		trace_error("Invalid configuration: %s Bus Width %u\r\n",
			instance_def->name, (unsigned)config.bus_width);
		return APPLET_FAIL;
	}

#ifdef CONFIG_HAVE_SDMMC
	config.supported_voltages = mbx->in.parameters[4];
	if (!config.supported_voltages || (config.supported_voltages & ~SUPPORTED_VOLTAGE_MASK)) {
		trace_error("Invalid supported voltages value: 0x%x\r\n",
			(unsigned)config.supported_voltages);
		return APPLET_FAIL;
	}
#endif

	trace_warning_wp("Initializing %s", instance_def->name);
	if (config.boot_partition)
		trace_warning_wp(", boot partition %u", (unsigned)config.boot_partition);
	else
		trace_warning_wp(", user partition");
	trace_warning_wp(", %d-bit", (unsigned)config.bus_width);
#if defined(CONFIG_HAVE_SDMMC)
	trace_warning_wp(", %s", get_supported_voltage_string(config.supported_voltages));
#endif
	trace_warning_wp("\r\n");

	/* Configure PIO */
	configure_instance_pio(instance_def, &config);

	pmc_configure_peripheral(TIMER0_MODULE, NULL, true);

#if defined(CONFIG_HAVE_SDMMC)
	id = get_sdmmc_id_from_addr(instance_def->addr);
	if (sdmmc_pre_init(id))
		return APPLET_FAIL;

	// set SDMMC controller capabilities
	uint32_t caps0 = SDMMC_CA0R_SLTYPE_EMBEDDED;
	if (config.bus_width == 8)
		caps0 |= SDMMC_CA0R_ED8SUP;
	if (config.supported_voltages & SUPPORTED_VOLTAGE_18V)
		caps0 |= SDMMC_CA0R_V18VSUP;
	if (config.supported_voltages & SUPPORTED_VOLTAGE_30V)
		caps0 |= SDMMC_CA0R_V30VSUP;
	if (config.supported_voltages & SUPPORTED_VOLTAGE_33V)
		caps0 |= SDMMC_CA0R_V33VSUP;
	sdmmc_set_capabilities(instance_def->addr,
			caps0, CAPS0_MASK, 0, 0);

	sdmmc_initialize(&drv, id, TIMER0_MODULE, TIMER0_CHANNEL,
			dma_table, ARRAY_SIZE(dma_table), true, NULL);
#elif defined(CONFIG_HAVE_HSMCI)
	id = get_hsmci_id_from_addr(instance_def->addr);
	pmc_configure_peripheral(id, NULL, true);
	memset(&drv_config, 0, sizeof(drv_config));
	drv_config.periph_id = id;
	drv_config.slot = instance_def->slot;
	drv_config.use_polling = true;
	hsmci_initialize(&drv, &drv_config);
#endif

	SDD_InitializeSdmmcMode(&lib, &drv, 0);
	if (SD_GetStatus(&lib) == SDMMC_NOT_SUPPORTED) {
		trace_error("Device not detected.\n\r");
		return APPLET_FAIL;
	}

	rc = SD_Init(&lib);
	if (rc != SDMMC_OK) {
		trace_error("SD/MMC device initialization failed: %s\n\r",
				SD_StringifyRetCode(rc));
		return APPLET_FAIL;
	}

	card_type = SD_GetCardType(&lib);
	if (!(card_type & CARD_TYPE_bmSDMMC)) {
		trace_error("Invalid card type: only SD/MMC is supported\n\r");
		return APPLET_FAIL;
	}

	if (trace_level >= TRACE_LEVEL_WARNING)
		SD_DumpStatus(&lib);

	if (config.boot_partition) {
		/* check that card is MMC */
		if (!(card_type & CARD_TYPE_bmMMC)) {
			trace_error("Invalid card type: boot partition in only supported on MMC\n\r");
			return APPLET_FAIL;
		}

		/* get and check boot partition size */
		mem_size = MMC_EXT_BOOT_SIZE_MULTI(lib.EXT) * (128 * 1024 / BLOCK_SIZE);
		if (mem_size == 0) {
			trace_error("No boot partition available\n\r");
			return APPLET_FAIL;
		}

		/* configure boot partition */
		mmc_configure_partition(&lib, EMMC_BOOT_PARTITION_ACCESS(config.boot_partition) |
		                              EMMC_BOOT_PARTITION_ENABLE(config.boot_partition) |
		                              EMMC_BOOT_ACK);
		mmc_configure_boot_bus(&lib, 0);
	} else {
		mem_size = (uint32_t)(((uint64_t)SD_GetTotalSizeKB(&lib) * 1024ull) / BLOCK_SIZE);
	}

	buffer = applet_buffer;
	buffer_size = applet_buffer_size & ~(BLOCK_SIZE - 1);
	if (buffer_size == 0) {
		trace_error("Not enough memory for buffer\r\n");
		return APPLET_FAIL;
	}

	mbx->out.buf_addr = (uint32_t)buffer;
	mbx->out.buf_size = buffer_size;
	mbx->out.page_size = BLOCK_SIZE;
	mbx->out.mem_size = mem_size;
	mbx->out.erase_support = 0;
	mbx->out.nand_header = 0;

	trace_warning_wp("SD/MMC device initialization successful\n\r");
	trace_warning_wp("Buffer Address: 0x%lx\r\n", mbx->out.buf_addr);
	trace_warning_wp("Buffer Size: %ld bytes\r\n", mbx->out.buf_size);
	trace_warning_wp("Page Size: %ld bytes\r\n", mbx->out.page_size);
	trace_warning_wp("Memory Size: %ld pages\r\n", mbx->out.mem_size);

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
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* check that requested offset/size does not overflow memory */
	if (offset + length > mem_size) {
		trace_error("Memory overflow\r\n");
		return APPLET_FAIL;
	}

	if (SD_Write(&lib, offset, buffer, length, NULL, NULL) != SDMMC_OK) {
		trace_error("Error while writing %u bytes at offset 0x%08x\r\n",
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
		trace_error("Buffer overflow\r\n");
		return APPLET_FAIL;
	}

	/* check that requested offset/size does not overflow memory */
	if (offset + length > mem_size) {
		trace_error("Memory overflow\r\n");
		return APPLET_FAIL;
	}

	if (SD_Read(&lib, offset, buffer, length, NULL, NULL) != SDMMC_OK) {
		trace_error("Error while reading %u bytes at offset 0x%08x\r\n",
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

static uint32_t handle_cmd_enable_boot_part(uint32_t cmd, uint32_t *mailbox)
{
	union boot_partition_mailbox *mbx =
		(union boot_partition_mailbox*)mailbox;
	uint32_t boot_partition = mbx->in.boot_partition;
	uint32_t boot_size;
	uint8_t card_type;

	assert(cmd == APPLET_CMD_ENABLE_BOOT_PART);

	/* check the boot partition number is valid */
	if (boot_partition > 2) {
		trace_error("Invalid boot partition number\r\n");
		return APPLET_FAIL;
	}

	/* check that card is MMC */
	card_type = SD_GetCardType(&lib);
	if (!(card_type & CARD_TYPE_bmMMC)) {
		trace_error("Invalid card type: boot partition is only supported on MMC\r\n");
		return APPLET_SUCCESS;
	}

	/* get and check boot partition size */
	boot_size = MMC_EXT_BOOT_SIZE_MULTI(lib.EXT) * (128 * 1024 / BLOCK_SIZE);
	if (boot_size == 0) {
		trace_error("No boot partition available\r\n");
		return APPLET_FAIL;
	}

	/* configure boot partition */
	if (mmc_configure_partition(&lib, EMMC_BOOT_PARTITION_ACCESS(boot_partition) |
				    EMMC_BOOT_PARTITION_ENABLE(boot_partition) |
				    (boot_partition > 0 ? EMMC_BOOT_ACK : 0)))
		return APPLET_FAIL;

	/* update partition size */
	if (boot_partition)
		mem_size = boot_size;
	else
		mem_size = (uint32_t)(((uint64_t)SD_GetTotalSizeKB(&lib) * 1024ull) / BLOCK_SIZE);

	mbx->out.mem_size = mem_size;

	trace_warning_wp("Memory Size: %ld pages\r\n", mbx->out.mem_size);

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
	{ APPLET_CMD_ENABLE_BOOT_PART, handle_cmd_enable_boot_part },
	{ 0, NULL }
};
