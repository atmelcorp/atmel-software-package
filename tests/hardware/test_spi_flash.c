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

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/trng.h"
#include "peripherals/wdt.h"
#include "peripherals/spid.h"

#include "memories/at25.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static const struct _pin at25_pins[] = AT25_PINS;

static struct _spi_desc spi_at25_desc = {
	.addr           = AT25_ADDR,
	.bitrate        = AT25_FREQ,
	.attributes     = AT25_ATTRS,
	.dlybs          = AT25_DLYBS,
	.dlybct         = AT25_DLYCT,
	.chip_select    = AT25_CS,
	.spi_mode       = AT25_SPI_MODE,
	.transfert_mode = SPID_MODE_FIFO,
};

static struct _at25 at25drv;

/*------------------------------------------------------------------------------
 *
 *----------------------------------------------------------------------------*/

uint8_t test_spi_flash (void)
{
	uint8_t status;

	/* configure spi serial flash pins */
	pio_configure(at25_pins, ARRAY_SIZE(at25_pins));
	/* open serial flash device */
	if( AT25_SUCCESS == at25_configure(&at25drv, &spi_at25_desc)) {
		if(at25_unprotect(&at25drv)) {
			printf(" -E- Protection desactivation FAILED!\r\n");
			status = 1;
		}
		else {
			at25_read_status(&at25drv);
			at25_print_device_info(&at25drv);

			status = at25_read_status(&at25drv);
			printf("at25 chip status:\r\n"
			       "\t- Busy\t\t\t\t: %s\r\n"
			       "\t- Write Enabled\t\t\t: %s\r\n"
			       "\t- Software protection\t\t: %s\r\n"
			       "\t- Write protect pin\t\t: %s\r\n"
			       "\t- Erase/Program error\t\t: %s\r\n"
			       "\t- Sector Protection Register\t: %s\r\n"
			       "\t- Raw register value\t\t: 0x%X\r\n",
			       status & AT25_STATUS_RDYBSY_BUSY ? "yes":"no",
			       status & AT25_STATUS_WEL ? "yes":"no",
			       status & AT25_STATUS_SWP ? "Some/all":"none",
			       status & AT25_STATUS_WPP ? "inactive":"active",
			       status & AT25_STATUS_EPE ? "yes":"no",
			       status & AT25_STATUS_SPRL ? "locked":"unlocked",
			       (unsigned int)status);
			status = 0;
		}
	}
	else {
		printf(" -E- Device not supported FAILED!\r\n");
		status = 1;
	}
	return status;
}


