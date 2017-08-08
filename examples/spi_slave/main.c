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
 * \page spi_slave SPI Slave Example
 *
 * \section Purpose
 *
 * This example uses Serial Peripheral Interface (SPI) in slave mode to
 * communicate to another interface (SPI) in master mode.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2-XULT and SAMA5D4-XULT.
 *
 * Requirements when running on SAMA5D2-XULT:
 * We need to connect the SPI pins on the board before running the example.
 * - <b>  SPI0 IOSET1 (MASTER)             - SPI1 IOSET3 (SLAVE)</b>
 * - SPI0_NPCS2 (EXP_PA19 on J9 pin 1)  - SPI1_NPCS0 (EXP/XPRO_PD28 on J20 pin 3)
 * - SPI0_MOSI  (EXP_PA15 on J17 pin 5) - SPI1_MOSI  (EXP/XPRO_PD26 on J20 pin 4)
 * - SPI0_MISO  (EXP_PA16 on J8 pin 1)  - SPI1_MISO  (EXP/XPRO_PD27 on J20 pin 5)
 * - SPI0_SPCK  (EXP_PA14 on J17 pin 4) - SPI1_SPCK  (EXP/XPRO_PD25 on J20 pin 6)
 *
 * Requirements when running on SAMA5D3-EK (REV. E):
 * We need to connect the SPI pins on the board before running the example.
 * - <b>  SPI0 (MASTER)                        - SPI1 (SLAVE)</b>
 * - SPI0_MISO (PD10 on J3 pin 22) - SPI1_MISO  (PC22 on J2 pin 18)
 * - SPI0_MOSI (PD11 on J3 pin 24) - SPI1_MOSI  (PC23 on J2 pin 20)
 * - SPI0_SPCK (PD12 on J3 pin 26) - SPI1_SPCK  (PC24 on J2 pin 22)
 * - SPI0_NPCS2(PD15 on J3 pin 32) - SPI1_NPCS0 (PC25 on J2 pin 24)
 * Also remember to mount the following resisters: R6, R50, and R51.
 *
 * Requirements when running on SAMA5D4-XULT:
 * We need to connect the SPI pins on the board before running the example.
 * - <b>  SPI1 (MASTER)                          - SPI2 (SLAVE)</b>
 * - SPI1_NPCS3 (EXP/XPRO_PB27 on J15 pin 4)  - SPI2_NPCS0 (EXP/XPRO_PD17 on J19 pin 3)
 * - SPI1_MOSI  (EXP/XPRO_PB19 on J17 pin 4)  - SPI2_MOSI  (EXP/XPRO_PD13 on J19 pin 5)
 * - SPI1_MISO  (EXP/XPRO_PB18 on J17 pin 5)  - SPI2_MISO  (EXP/XPRO_PD11 on J15 pin 30)
 * - SPI1_SPCK  (EXP/XPRO_PB20 on J17 pin 6)  - SPI2_SPCK  (EXP/XPRO_PD15 on J15 pin 8)
 *
 * Requirements when running on SAMA5D4-EK:
 * We need to connect the SPI pins on the board before running the example.
 * - <b>  SPI1 (MASTER)                        - SPI2 (SLAVE)</b>
 * - SPI1_NPCS2(LCD_SPI1_CS2 on J10 pin 34) - SPI2_NPCS0 (XPRO_PD17 on J11 XPRO pin 14)
 * - SPI1_MOSI (LCD_SPI1_SI  on J10 pin 32) - SPI2_MOSI  (XPRO_PD13 on J11 XPRO pin 16)
 * - SPI1_MISO (LCD_SPI1_SO  on J10 pin 31) - SPI2_MISO  (XPRO_PD11 on J11 XPRO pin 17)
 * - SPI1_SPCK (LCD_SPI1_CLK on J10 pin 33) - SPI2_SPCK  (XPRO_PD15 on J11 XPRO pin 18)
 *
 * Requirements when running on SAM9XX5-EK:
 * We need to connect the SPI pins on the board before running the example.
 * - <b>  SPI0 (MASTER)                        - SPI1 (SLAVE)</b>
 * - SPI0_MISO (PA11 on J1 pin 27) - SPI1_MISO (PA21 on J1 pin 16)
 * - SPI0_MOSI (PA12 on J1 pin 29) - SPI1_MOSI (PA22 on J1 pin 18)
 * - SPI0_SPCK (PA13 on J1 pin 31) - SPI1_SPCK (PA23 on J1 pin 20)
 * - SPI0_NPCS1 (PA7 on J1 pin 19) - SPI1_NPCS0 (PA8 on J1 pin 21)
 *
 * \section Descriptions
 *
 * This example shows control of the SPI slave, how to configure and
 * transfer data with SPI slave. By default, example runs in SPI slave mode,
 * waiting for SPI slave & DBGU input.
 *
 * The code can be roughly broken down as follows:
 * <ul>
 * <li> 's' will start SPI transfer test
 * <ol>
 * <li>Configure SPI as master, setup SPI clock.
 * </ol>
 * <li>Setup SPI clock for slave.
 * </ul>
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
 *     -- SPI Slave Example  xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * -# The following traces detail operations on the SPI slave example, displaying success
 *    or error messages depending on the results of the commands.
 *
 * \section References
 * - spi_slave/main.c
 * - spi.c
 */

/**
 * \file
 *
 * This file contains all the specific code for the spi slave example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "gpio/pio.h"
#include "spi/spid.h"

#include "peripherals/bus.h"

#include "serial/console.h"
#include "mm/cache.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define DMA_TRANS_SIZE 256

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
	#include "config_sama5d2-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D27_SOM1_EK)
	#include "config_sama5d27-som1-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D3_EK)
	#include "config_sama5d3-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
	#include "config_sama5d4-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
	#include "config_sama5d4-xplained.h"
#elif defined(CONFIG_BOARD_SAM9G15_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9G25_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9G35_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9X25_EK)
	#include "config_sam9xx5-ek.h"
#elif defined(CONFIG_BOARD_SAM9X35_EK)
	#include "config_sam9xx5-ek.h"

#else
	#error Unsupported board!
#endif

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** data buffer for SPI master's receive */
CACHE_ALIGNED static uint8_t spi_buffer_master_tx[DMA_TRANS_SIZE];

/** data buffer for SPI slave's transfer */
CACHE_ALIGNED static uint8_t spi_buffer_slave_rx[DMA_TRANS_SIZE];

/** Pio pins for SPI slave */
static const struct _pin pins_spi_slave[] = SPI_SLAVE_PINS;

/** descriptor for SPI master */
static const struct _bus_dev_cfg spi_master_dev = {
	.bus = SPI_MASTER_BUS,
	.spi_dev = {
		.chip_select = SPI_MASTER_CS,
		.bitrate = SPI_MASTER_BITRATE,
		.delay = {
			.bs = 0,
			.bct = 0,
		},
		.spi_mode = SPID_MODE_0,
	},
};

static struct _spi_desc spi_slave_dev = {
	.addr = SPI_SLAVE_ADDR,
	.chip_select = 0,
	.transfer_mode = BUS_TRANSFER_MODE_DMA,
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Displays the user menu.
 */
static void _display_menu(void)
{
	printf("\r\nMenu :\r\n");
	printf("------\r\n");
	printf("  s: Perform SPI transfer start\r\n");
	printf("  h: Display menu \r\n\r\n");
}

static int _spi_slave_transfer_callback(void* arg, void* arg2)
{
	printf("Slave transfer complete\r\n");
	return 0;
}

/**
 * \brief Start SPI slave transfer and SPI master receive.
 */
static void _spi_transfer(void)
{
	int err;
	int i;
	struct _buffer master_buf = {
		.data = spi_buffer_master_tx,
		.size = DMA_TRANS_SIZE,
		.attr = BUS_BUF_ATTR_TX | BUS_SPI_BUF_ATTR_RELEASE_CS,
	};
	struct _buffer slave_buf = {
		.data = spi_buffer_slave_rx,
		.size = DMA_TRANS_SIZE,
		.attr = BUS_BUF_ATTR_RX,
	};
	struct _callback _cb = {
		.method = _spi_slave_transfer_callback,
		.arg = 0,
	};

	for (i = 0; i < DMA_TRANS_SIZE; i++)
		spi_buffer_master_tx[i] = i;
	memset(spi_buffer_slave_rx, 0, DMA_TRANS_SIZE);

	bus_start_transaction(spi_master_dev.bus);

	printf("Slave receiving...\r\n");
	err = spid_transfer(&spi_slave_dev, &slave_buf, 1, &_cb);
	if (err < 0) {
		trace_error("SPI: SLAVE: transfer failed.\r\n");
		return;
	}

	printf("Master sending...\r\n");
	bus_transfer(spi_master_dev.bus, spi_master_dev.spi_dev.chip_select, &master_buf, 1, NULL);
	bus_stop_transaction(spi_master_dev.bus);
	spid_wait_transfer(&spi_slave_dev);

	if (memcmp(spi_buffer_master_tx, spi_buffer_slave_rx, DMA_TRANS_SIZE)) {
		trace_error("SPI: received data does not match!\r\n");
		return;
	}

	printf("Received data matched.\r\n");
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief SPI slave Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t key;

	/* Output example information */
	console_example_info("SPI Slave Example");

	/* Configure SPI slave */
	pio_configure(pins_spi_slave, ARRAY_SIZE(pins_spi_slave));
	spid_configure(&spi_slave_dev);
	spid_configure_master(&spi_slave_dev, false);
	spid_configure_cs(&spi_slave_dev, 0, 0, 0, 0, SPID_MODE_0);

	bus_configure_slave(spi_master_dev.bus, &spi_master_dev);

	_display_menu();

	while (1) {
		key = console_get_char();
		switch (key) {
		case 'H':
		case 'h':
			_display_menu();
			break;
		case 'S':
		case 's':
			_spi_transfer();
			break;
		default:
			break;
		}
	}
}
