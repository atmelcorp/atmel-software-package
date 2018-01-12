/* ----------------------------------------------------------------------------
 *         SAM Software Package License
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

/**
 * \page qspi_flash QSPI Example
 *
 * \section Purpose
 *
 * This example indicates how to use the spi_nor driver in order to
 * access data on a QSPI device.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2-PTC-EK, SAMA5D2-XPLAINED, SAMA5D27-SOM1-EK.
 *
 * \section Descriptions
 *
 * This example shows how to use current spi driver package which composed of 
 * low-level functions for spi-nor devices to access QSPI device. All external API 
 * functions that support the unified interface of functions and operations for 
 * all supported QSPI Devices. 
 *
 * \section Usage
 *
 * -# Compile the application and connect the DBGU port of the evaluation board
 *    to the computer.
 * -# Open and configure a terminal application on PC
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Download the program inside the evaluation board and run it. Please refer to
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# Upon startup, the application will output the following line on the DBGU:
 *    \code
 *     -- QSPI Example xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * -# Choose an item in the menu to test.
 *
 * \section References
 * - qspi_flash/main.c
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "board_spi.h"
#include "chip.h"
#include "compiler.h"
#include "crypto/trng.h"
#include "gpio/pio.h"
#include "mm/cache.h"
#include "nvm/spi-nor/spi-nor.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "spi/qspi.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

CACHE_ALIGNED static uint8_t buf[768];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _display_buf(uint8_t *buffer, uint32_t size)
{
	int i;
	for (i = 0; i < size; i++) {
		printf("%02x ", buffer[i]);
		if ((i & 31) == 31)
			printf("\r\n");
		else if ((i & 3) == 3)
			printf(" ");
	}
	printf("\r\n");
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

#define BOARD_SPI_FLASH_QSPI0 0

int main(void)
{
	uint32_t start = 0x280000;
	struct spi_flash* flash = board_get_spi_flash(BOARD_SPI_FLASH_QSPI0);
	int rc;

	/* Initialize TRNG */
	trng_enable();

	/* Output example information */
	console_example_info("QSPI Example");

	printf("erasing block at 0x%08x\r\n", (int)start);
	rc = spi_nor_erase(flash, start, 4 * 1024);
	printf("erase returns %d\r\n", rc);

	printf("reading %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	memset(buf, 0, sizeof(buf));
	rc = spi_nor_read(flash, start, buf, sizeof(buf));
	printf("read returns %d\r\n", rc);
	_display_buf(buf, sizeof(buf));

	printf("preparing write buffer\r\n");
	uint8_t r = trng_get_random_data() & 0xff;
	uint32_t i = 0;
	while (i * 32 < sizeof(buf)) {
		memset(buf + i * 32, r + i, 32);
		i++;
	}
	_display_buf(buf, sizeof(buf));

	printf("writing %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	rc = spi_nor_write(flash, start, buf, sizeof(buf));
	printf("write returns %d\r\n", rc);

	printf("reading %d bytes at 0x%08x\r\n", sizeof(buf), (int)start);
	memset(buf, 0, sizeof(buf));
	rc = spi_nor_read(flash, start, buf, sizeof(buf));
	printf("read returns %d\r\n", rc);
	_display_buf(buf, sizeof(buf));

	while (1) { }
}
