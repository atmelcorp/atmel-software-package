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
 * Requirements when running on SAMA5D4-EK:
 * We need to connect the SPI pins on the board before running the example.
 * - <b>  SPI1 (MASTER)                        - SPI2 (SLAVE)</b>
 * - SPI1_NPCS2(LCD_SPI1_CS2 on J10 pin 34) - SPI2_NPCS0 (XPRO_PD17 on J11 XPRO pin 14)
 * - SPI1_MOSI (LCD_SPI1_SI  on J10 pin 32) - SPI2_MOSI  (XPRO_PD13 on J11 XPRO pin 16)
 * - SPI1_MISO (LCD_SPI1_SO  on J10 pin 31) - SPI2_MISO  (XPRO_PD11 on J11 XPRO pin 17)
 * - SPI1_SPCK (LCD_SPI1_CLK on J10 pin 33) - SPI2_SPCK  (XPRO_PD15 on J11 XPRO pin 18)
 *
 * Requirements when running on SAMA5D4-XULT:
 * We need to connect the SPI pins on the board before running the example.
 * - <b>  SPI2 (MASTER)                          - SPI1 (SLAVE)</b>
 * - SPI2_NPCS0 (EXP/XPRO_PD17 on J19 pin 3)  - SPI1_NPCS0 (EXP/XPRO_PB21 on J17 pin 3)
 * - SPI2_MOSI  (EXP/XPRO_PD13 on J19 pin 5)  - SPI1_MOSI  (EXP/XPRO_PB19 on J17 pin 4)
 * - SPI2_MISO  (EXP/XPRO_PD11 on J15 pin 30) - SPI1_MISO  (EXP/XPRO_PB18 on J17 pin 5)
 * - SPI2_SPCK  (EXP/XPRO_PD15 on J15 pin 8)  - SPI1_SPCK  (EXP/XPRO_PB20 on J17 pin 6)
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

#include "peripherals/pio.h"
#include "peripherals/twid.h"
#include "peripherals/spid.h"
#include "peripherals/xdmad.h"
#include "peripherals/wdt.h"

#include "misc/console.h"


#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define DMA_TRANS_SIZE 256

#if defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
	#include "config_sama5d2-xplained.h"
#elif defined(CONFIG_BOARD_SAMA5D4_EK)
	#include "config_sama5d4-ek.h"
#elif defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
	#include "config_sama5d4-xplained.h"
#else
	#error Unsupported board!
#endif

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/


/** data buffer for SPI master's receive */
static uint8_t spi_buffer_master_rx[DMA_TRANS_SIZE];

/** data buffer for SPI slave's transfer */
static uint8_t spi_buffer_slave_tx[DMA_TRANS_SIZE];

/** Pio pins for SPI master */
static const struct _pin pins_spi_master[] = SPI_MASTER_PINS;

/** Pio pins for SPI slave */
static const struct _pin pins_spi_slave[] = SPI_SLAVE_PINS;

/** descriptor for SPI master */
static struct _spi_desc spi_master_desc = {
	.addr           = SPI_MASTER_ADDR,
	.bitrate        = 0,
	.attributes     = (SPI_MR_MODFDIS | SPI_MR_WDRBT | SPI_MR_MSTR),
	.dlybs          = 0,
	.dlybct         = 0,
	.chip_select    = SPI_MASTER_CS,
	.spi_mode       = (SPI_CSR_NCPHA | SPI_CSR_BITS_8_BIT),
	.transfert_mode = SPID_MODE_DMA,
};

/** descriptor for SPI slave */
static struct _spi_desc spi_slave_desc = {
	.addr           = SPI_SLAVE_ADDR,
	.bitrate        = 0,
	.attributes     = (SPI_MR_MODFDIS | SPI_MR_WDRBT),
	.dlybs          = 0,
	.dlybct         = 0,
	.chip_select    = SPI_SLAVE_CS,
	.spi_mode       = (SPI_CSR_NCPHA | SPI_CSR_BITS_8_BIT),
	.transfert_mode = SPID_MODE_DMA,
};

/** SPI clock configuration (KHz) */
static const uint32_t clock_configurations[3] = { 500, 1000, 5000 };

/** SPI Clock setting (KHz) */
static uint32_t spi_clock = 500;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Callback function for SPI.
 * Will set the boolean pointer to by user_args to true.
 */
static void _spi_callback(struct _spi_desc* desc, void* user_args)
{
	volatile bool *done = (volatile bool*)user_args;
	(void)desc;
	*done = true;
}

/**
 * \brief Displays the user menu.
 */
static void _display_menu(void)
{
	uint32_t i;

	printf("\r\nMenu :\r\n");
	printf("------\r\n");
	for (i = 0 ; i < ARRAY_SIZE(clock_configurations) ; i++) {
		printf("  %u: Set SPCK = %7u kHz\r\n",
			(unsigned int)i, (unsigned int)clock_configurations[i]);
	}
	printf("  s: Perform SPI transfer start\r\n");
	printf("  h: Display menu \r\n\r\n");
}

/**
 * \brief Sets the specified SPI clock configuration.
 * \param configuration  Index of the configuration to set.
 */
static void _set_clock_configuration(uint8_t configuration)
{
	printf("Next SPI master transfer will use %ukHz clock.\r\n",
		(unsigned int)clock_configurations[configuration]);
	spi_clock = clock_configurations[configuration];
}

/**
 * \brief Start SPI slave transfer and SPI master receive.
 */
static void _spi_transfer(void)
{
	int i;
	uint32_t status;
	volatile bool master_rx_done;
	volatile bool slave_tx_done;

	struct _buffer master_in = {
		.data = spi_buffer_master_rx,
		.size = DMA_TRANS_SIZE
	};
	struct _buffer slave_out = {
		.data = spi_buffer_slave_tx,
		.size = DMA_TRANS_SIZE
	};

	slave_tx_done = false;
	master_rx_done = false;

	spi_master_desc.bitrate = spi_clock;
	spi_slave_desc.bitrate = spi_clock;

	spid_configure(&spi_master_desc);
	spid_configure(&spi_slave_desc);

	printf("Slave sending, Master receiving... \r\n");
	for (i = 0; i < DMA_TRANS_SIZE; i++) {
		spi_buffer_slave_tx[i] = 0xFF - i;
	}
	memset(spi_buffer_master_rx, 0x0, DMA_TRANS_SIZE);

	spid_begin_transfert(&spi_slave_desc);
	status = spid_transfert(&spi_slave_desc, 0, &slave_out,
				_spi_callback, (void*)&slave_tx_done);
	if (SPID_SUCCESS != status) {
		printf("Error: SPI slave transfer failed.\r\n");
		return;
	}

	spid_begin_transfert(&spi_master_desc);
	status = spid_transfert(&spi_master_desc, &master_in, 0,
				_spi_callback, (void*)&master_rx_done);
	if (SPID_SUCCESS != status) {
		printf("Error: SPI master transfer failed.\r\n");
		return;
	}

	while (!slave_tx_done || !master_rx_done);

	spid_finish_transfert(&spi_master_desc);
	spid_finish_transfert(&spi_slave_desc);

	spid_close(&spi_master_desc);
	spid_close(&spi_slave_desc);

	for (i = 0; i < DMA_TRANS_SIZE; i ++) {
		if (spi_buffer_slave_tx[i] != spi_buffer_master_rx[i]) {
			printf("Error: received data does not match!\r\n");
			return;
		}
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

	/* Disable watchdog */
	wdt_disable();

	/* Configure console */
	board_cfg_console(0);

	/* Initialize XDMA */
	xdmad_initialize(false);

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Output example information */
	printf("-- SPI Slave Example " SOFTPACK_VERSION " --\r\n");
	printf("-- " BOARD_NAME "\r\n");
	printf("-- Compiled: " __DATE__ " " __TIME__ " --\r\n");

	board_cfg_pmic();

	/* Configure SPI pins */
	pio_configure(pins_spi_master, ARRAY_SIZE(pins_spi_master));
	pio_configure(pins_spi_slave, ARRAY_SIZE(pins_spi_slave));

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
			/* Set SPI clock configuration #n */
			if (key >= '0' && key <= '2')
				_set_clock_configuration(key - '0');
			break;
		}
	}
}

