/* ----------------------------------------------------------------------------
 *         SAM Software Package License
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

#include <stdbool.h>
#include <stdio.h>

#include "board.h"
#include "board_console.h"
#include "board_spi.h"
#include "chip.h"
#ifdef CONFIG_HAVE_QSPI_DMA
#include "dma/dma.h"
#endif
#include "gpio/pio.h"
#include "irqflags.h"
#include "mm/cache.h"
#include "mm/mmu.h"
#include "nvm/spi-nor/spi-nor.h"
#include "serial/console.h"
#include "spi/qspi.h"
#include "trace.h"

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
#include "getting-started_sama5d2-xplained_qspi0.h"
#elif defined(CONFIG_BOARD_SAMA5D27_SOM1_EK)
#include "getting-started_sama5d27-som1-ek_qspi1.h"
#endif

/*----------------------------------------------------------------------------
 *        Constants
 *----------------------------------------------------------------------------*/

#define BOARD_SPI_FLASH_QSPI0 0

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void run_xip_program(void* qspi_mem_addr)
{
	void (*xip_startup_fn)(void);

	printf("\n\r");
	printf("Running code from QSPI flash\n\r");
	printf("============================\n\r");

	/* Disable MMU, cache and interrupts */
	arch_irq_disable();
	mmu_disable();

	xip_startup_fn = (void(*)(void))qspi_mem_addr;
	xip_startup_fn();
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/* override default board init */
void board_init()
{
#ifdef VARIANT_SRAM
	bool clocks = true;
#else
	bool clocks = false;
#endif
	board_cfg_lowlevel(clocks, false, false);
	board_cfg_console(0);
#ifdef CONFIG_HAVE_QSPI_DMA
	dma_initialize(false);
#endif

	/* Configure SPI NOR flash memory */
	board_cfg_spi_flash();
}

/**
 *  \brief QSPI_XIP Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint32_t idx;
	uint32_t buffer[4];
	uint8_t *ptr, cmd;
	struct spi_flash* flash = board_get_spi_flash(BOARD_SPI_FLASH_QSPI0);
	void* qspi_mem_addr = get_qspi_mem_from_addr(flash->priv.qspi.addr);

	/* Output example information */
	console_example_info("QSPI XIP Example");

	/* get the code at the beginning of QSPI, run the code directly if it's valid */
	if (spi_nor_read(flash, 0, (uint8_t*)buffer, sizeof(buffer)) < 0)
		trace_fatal("Read the code from QSPI Flash failed!\n\r");

	printf("Data at the beginning of QSPI: %08x %08x %08x %08x\n\r",
		(unsigned int)buffer[0], (unsigned int)buffer[1],
		(unsigned int)buffer[2], (unsigned int)buffer[3]);

	/* check whether or not there's a valid application in QSPI */
	if ((((buffer[0] & 0xFF000000) == 0xE5000000) ||
	     ((buffer[0] & 0xFF000000) == 0xEA000000)) &&
	    ((buffer[0] & 0xFF000000) == (buffer[1] & 0xFF000000)) &&
	    ((buffer[0] & 0xFF000000) == (buffer[2] & 0xFF000000)) &&
	    ((buffer[0] & 0xFF000000) == (buffer[3] & 0xFF000000)) ) {
		printf("Valid application already in QSPI, will run it using QSPI XIP\n\r");

		printf("\r\nDo you want to Run it or Flash a new one (R/F): ");
		do {
			cmd = console_get_char();
		} while (cmd != 'R' && cmd != 'r' && cmd != 'F' && cmd != 'f');
		printf("%c\r\n", cmd);

		if (cmd == 'R' || cmd == 'r') {
			printf("Starting continuous read mode to enter in XIP mode\n\r");
			if (qspi_xip(flash, qspi_mem_addr) < 0)
				trace_fatal("Read the code from QSPI Flash failed!\n\r");
			run_xip_program(qspi_mem_addr);
		}
	} else {
		printf("No valid application found in QSPI, will one program first\n\r");
	}

	printf("Erasing beginning of memory...\n\r");
	for (idx = 0; idx * 4096 < sizeof(xip_program); idx++)
		if (spi_nor_erase(flash, idx * 4096, 4096) < 0)
			trace_fatal("QSPI Flash block erase failed!\n\r");
	printf("Erase done (%u bytes).\n\r", (unsigned)(idx * 4096));

	/* Flash the code to QSPI flash */
	printf("Writing to QSPI...\n\r");
	if (spi_nor_write(flash, 0, xip_program, sizeof(xip_program)) < 0)
		trace_fatal("QSPI Flash writing failed!\n\r");
	printf("Example code written to memory (%d bytes).\n\r", sizeof(xip_program));
	printf("Verifying...\n\r");

	printf("Starting continuous read mode to enter in XIP mode\n\r");
	if (qspi_xip(flash, qspi_mem_addr) < 0)
		trace_fatal("QSPI Flash read failed!\n\r");

	/* Start continuous read mode to enter in XIP mode*/
	ptr = (uint8_t*)qspi_mem_addr;
	for (idx = 0; idx < sizeof(xip_program); idx++, ptr++)
		if (*ptr != xip_program[idx])
			trace_fatal("Data does not match at 0x%x (0x%02x != 0x%02x)\n\r",
					(unsigned)ptr, *ptr, xip_program[idx]);

	printf("Verification OK\n\r");
	run_xip_program(qspi_mem_addr);

	while (1);
}
