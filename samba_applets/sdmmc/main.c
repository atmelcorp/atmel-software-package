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
#include "misc/console.h"
#include "peripherals/sdmmc.h"
#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/pio.h"
#include "peripherals/aic.h"
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

/* Allocate 2 Timers/Counters, that are not used already by the libraries and
 * drivers this applet depends on. */
#define TIMER0_MODULE                 ID_TC0
#define TIMER0_CHANNEL                0

#define BLOCK_SIZE                    512u

#define EMMC_BOOT_PARTITION_ACCESS(p) (p << 0)
#define EMMC_BOOT_PARTITION_ENABLE(p) (p << 3)
#define EMMC_BOOT_ACK                 (1 << 6)

/*----------------------------------------------------------------------------
 *         Local variables
 *----------------------------------------------------------------------------*/

static bool initialized = false;

static uint8_t* buffer;

static uint32_t buffer_size;

static uint32_t mem_size;

static Sdmmc* sdmmc_instance;

static uint32_t sdmmc_id;

/* Driver instance data (a.k.a. MCI driver instance) */
static struct sdmmc_set drv = { 0 };

/* Library instance data (a.k.a. SDCard driver instance) */
ALIGNED(L1_CACHE_BYTES) static sSdCard lib = { .pDrv = 0 };

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/
 
static bool configure_instance_pio(uint32_t instance, Sdmmc** addr, uint32_t* id)
{
	uint8_t i;
	for (i = 0; i < num_sdmmc_pin_defs; i++) {
		const struct sdmmc_pin_definition* def =
			&sdmmc_pin_defs[i];
		if (def->instance == instance) {
			*addr = def->addr;
			*id = def->sdmmc_id;
			pio_configure(def->pins, def->num_pins);
			return true;
		}
	}
	return false;
}

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;
	uint32_t instance = mbx->in.parameters[0];
	uint32_t boot_partition = mbx->in.parameters[1];
	uint8_t rc, card_type;

	assert(cmd == APPLET_CMD_INITIALIZE);

	applet_set_init_params(mbx->in.comm_type, mbx->in.trace_level);
	initialized = false;

	trace_info_wp("\r\nApplet 'SD/MMC' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	if (!configure_instance_pio(instance, &sdmmc_instance, &sdmmc_id)) {
		trace_error_wp("Invalid configuration: SD/MMC Instance %u\r\n",
			(unsigned)instance);
		return APPLET_FAIL;
	}

	if (boot_partition > 2) {
		trace_error_wp("Invalid configuration: Unknown partition %u\r\n",
			(unsigned)boot_partition);
		return APPLET_FAIL;
	}

	if (boot_partition) {
		trace_info_wp("Initializing SD/MMC%u (boot partition %u)\r\n",
				(unsigned)instance,
				(unsigned)boot_partition);
	} else {
		trace_info_wp("Initializing SD/MMC%u (user partition)\r\n",
				(unsigned)instance);
	}

	/* The SDMMC peripherals are clocked by their Peripheral Clock, the
	 * Master Clock, and a Generated Clock (at least on SAMA5D2x).
	 * Configure GCLKx = <PLLA clock> divided by 1
	 * As of writing, the PLLA clock runs at 498 MHz */
	pmc_configure_gck(sdmmc_id, PMC_PCR_GCKCSS_PLLA_CLK, 1 - 1);
	pmc_enable_gck(sdmmc_id);
	pmc_enable_peripheral(sdmmc_id);

	sdmmc_initialize(&drv, sdmmc_instance, sdmmc_id, TIMER0_MODULE, TIMER0_CHANNEL, NULL, 0);
	sdmmc_instance->SDMMC_MC1R |= SDMMC_MC1R_FCD;

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
	mbx->out.erase_support = 0;
	mbx->out.mem_size = mem_size;

	trace_info_wp("SD/MMC device initialization successful\n\r");
	trace_info_wp("Buffer Address: 0x%lx\r\n", mbx->out.buf_addr);
	trace_info_wp("Buffer Size: %ld bytes\r\n", mbx->out.buf_size);
	trace_info_wp("Page Size: %ld bytes\r\n", mbx->out.page_size);
	trace_info_wp("Memory Size: %ld pages\r\n", mbx->out.mem_size);

	initialized = true;
	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_write_pages(uint32_t cmd, uint32_t *mailbox)
{
	union write_pages_mailbox *mbx = (union write_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset;
	uint32_t length = mbx->in.length;

	assert(cmd == APPLET_CMD_WRITE_PAGES);

	if (!initialized) {
		trace_error_wp("Applet not initialized\r\n");
		return APPLET_FAIL;
	}

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
		mbx->out.pages_written = 0;
		return APPLET_READ_FAIL;
	}

	trace_info_wp("Wrote %u bytes at offset 0x%08x\r\n",
			(unsigned)(mbx->in.length * BLOCK_SIZE),
			(unsigned)(mbx->in.offset * BLOCK_SIZE));
	mbx->out.pages_written = mbx->in.length;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_pages(uint32_t cmd, uint32_t *mailbox)
{
	union read_pages_mailbox *mbx = (union read_pages_mailbox*)mailbox;
	uint32_t offset = mbx->in.offset;
	uint32_t length = mbx->in.length;

	assert(cmd == APPLET_CMD_READ_PAGES);

	if (!initialized) {
		trace_error_wp("Applet not initialized\r\n");
		return APPLET_FAIL;
	}

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
		mbx->out.pages_read = 0;
		return APPLET_READ_FAIL;
	}

	trace_info_wp("Read %u bytes at offset 0x%08x\r\n",
			(unsigned)(mbx->in.length * BLOCK_SIZE),
			(unsigned)(mbx->in.offset * BLOCK_SIZE));
	mbx->out.pages_read = mbx->in.length;

	return APPLET_SUCCESS;
}


/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ APPLET_CMD_WRITE_PAGES, handle_cmd_write_pages },
	{ APPLET_CMD_READ_PAGES, handle_cmd_read_pages },
	{ 0, NULL }
};
