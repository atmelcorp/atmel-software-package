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
/**
 * \page qspi_aesb Advanced Encryption Standard Example with sama5 Microcontrollers
 *
 * \section Purpose
 * This application demonstrates the Advanced Encryption Standard Bridge (AESB) 
 * peripheral integrated in some SAMA5 microcontrollers. 
 * The AESB supports three confidentiality modes of operation for symmetrical key 
 * block cipher algorithms (ECB, CBC and CTR), as specified in the NIST Special 
 * Publication 800-38A Recommendation.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2 xPlained board.
 *
 * \section Description
 * This example shows how to configure AESB to protect electronic data. 
 * The Automatic Bridge mode, when the AESB block is connected between the system bus 
 * and a QSPI memory space , provides automatic encryption/decryption to/from a QSPI 
 * space without any action on the part of the user.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a>
 *    application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>,
 *    depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and chip used):
 *    \code
 *     -- AESB Example xxx --
 *     -- SAMxxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# Input command according to the menu.
 *
 * \section References
 * - aesb/main.c
 * - aesb.c
 * - aesb.h
 */

/** \file
 *
 *  This file contains all the specific code for the qspi_aesb example.
 *
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
#include "crypto/aesb.h"
#include "gpio/pio.h"
#include "nvm/spi-nor/spi-flash.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "spi/qspi.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Constants
 *----------------------------------------------------------------------------*/

#define BOARD_SPI_FLASH_QSPI0 0

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static uint8_t buffer[4096];
static uint8_t buffer_read[4096];

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief CRYPTO_QSPI_AESB Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	bool verify_failed = 0;
	uint32_t idx;
	struct spi_flash* flash = board_get_spi_flash(BOARD_SPI_FLASH_QSPI0);

	/* Output example information */
	console_example_info("QSPI AESB Example");

	/* Enable peripheral clock */
	pmc_configure_peripheral(ID_AESB, NULL, true);

	/* Perform a software-triggered hardware reset of the AES interface */
	aesb_swrst();

	/* Enable AESB automatic bridge mode */
	printf("-I- Configure AESB in automatic bridge mode: AES CTR selected\n\r");
	aesb_configure(AESB_MR_AAHB | AESB_MR_DUALBUFF_ACTIVE | AESB_MR_PROCDLY(0) |
	               AESB_MR_SMOD_AUTO_START | AESB_MR_OPMOD_CTR | AESB_MR_CKEY_PASSWD);

	printf("-I- Enable QSPI AESB IP scope (0x900000000-0x980000000)\n\r");
	spi_flash_use_aesb(flash, true);

	/* Write 64 word buffer with walking bit pattern (0x01, 0x02, ...) */
	for (idx = 0; idx < ARRAY_SIZE(buffer); idx++)
		buffer[idx] = 1 << (idx % 8);

	if (spi_flash_erase(flash, 0, 4096) < 0)
		trace_fatal("QSPI Flash block erase failed!\n\r");

	printf("-I- Writing to address of QSPI AESB IP scope, the data is encrypted automatically\n\r");
	if (spi_flash_write(flash, 0, buffer, ARRAY_SIZE(buffer)) < 0)
		trace_fatal("QSPI Flash writing failed!\n\r");

	printf("-I- Read from address of QSPI AESB IP scope\n\r");
	memset(buffer_read, 0, ARRAY_SIZE(buffer_read));
	if (spi_flash_read(flash, 0, buffer_read, ARRAY_SIZE(buffer_read)) < 0)
			trace_fatal("Read the code from QSPI Flash failed!\n\r");
	verify_failed = false;
	printf("-I- Read and verify data from address of AESB IP scope\r\n");
	for (idx = 0; idx < ARRAY_SIZE(buffer_read); idx++) {
		if (buffer_read[idx] != buffer[idx]) {
			verify_failed = true;
			printf("-E- Data does not match at 0x%x (0x%02x != 0x%02x)\n\r",
				   (unsigned)(buffer_read + idx), buffer_read[idx], buffer[idx]);
			break;
		}
	}
	if (!verify_failed)
		printf("\r\n-I- As expected, it automatically decrypts the data read from the target slave before putting it on the system bus\r\n");
	printf("\r\n-I- Read data from address outside of AESB IP scope. This test is expeted to fail.\r\n");

	spi_flash_use_aesb(flash, false);

	printf("-I- Read buffer without using AESB IP scope\n\r");
	memset(buffer_read, 0, ARRAY_SIZE(buffer_read));
	if (spi_flash_read(flash, 0, buffer_read, ARRAY_SIZE(buffer_read)) < 0)
			trace_fatal("Read the code from QSPI Flash failed!\n\r");

	verify_failed = false;
	printf("-I- Read and verify data from address 0xD00000000 \r\n");
	for (idx = 0; idx < ARRAY_SIZE(buffer_read); idx++) {
		if (buffer_read[idx] != buffer[idx]) {
			verify_failed = true;
			printf("-E- Data does not match at 0x%x (0x%02x != 0x%02x)\n\r",
				   (unsigned)(buffer_read + idx), buffer_read[idx], buffer[idx]);
			break;
		}
	}
	if (verify_failed)
		printf("\r\n-I- As expected, data cannot be decrypted from address outside of AESB IP scope\r\n");

	while (1);
}
