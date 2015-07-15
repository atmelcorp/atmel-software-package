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

#include <stdint.h>

#include "board.h"
#include "chip.h"

#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/pio.h"
#include "peripherals/flexcom.h"
#include "peripherals/twid2.h"
#include "peripherals/xdmad.h"

#include "memories/at24.h"

#include "misc/console.h"

#include "memories/at25.h"

#include "mutex.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Using TWI1 IOS2
#define AT24_ADDR       TWIHS1

static const struct _pin at24_pins[] = PINS_TWI1_IOS2;

typedef void (*_parser)(const uint8_t*, uint32_t);

struct _at24 at24_drv;
struct _twi_desc at24_twid = {
	.addr = (Twi*)AT24_ADDR,
	.freq = 400000,
	.transfert_mode = TWID_MODE_DMA
};


mutex_t lock = 0;

int main (void)
{
	/* Disable watchdog */
	wdt_disable();

	/* Disable all PIO interrupts */
	pio_reset_all_it();

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);

	flexcom_select(FLEXCOM0, FLEX_MR_OPMODE_TWI);

	/* Clear console */
	xdmad_initialize(false);
	printf("-- Twi XDMA Example " SOFTPACK_VERSION " --\n\r"
	       "-- " BOARD_NAME " --\n\r"
	       "-- Compiled: " __DATE__ " at " __TIME__ " --\n\r");

	/* configure spi serial flash pins */
	pio_configure(at24_pins, ARRAY_SIZE(at24_pins));

	at24_configure(&at24_drv, &at24_twid);

	int i = 0;
	printf("serial number: ");
	for (i = 0; i < sizeof(at24_drv.serial_number); ++i) {
		printf("%u",
		       (unsigned int)at24_drv.serial_number[i]);
	}
	printf("\r\nMAC addr: ");
	for (i = 0; i < sizeof(at24_drv.mac_addr_48); i+=2) {
		printf("%02X:%02X:",
		       (unsigned int)at24_drv.mac_addr_48[i],
		       (unsigned int)at24_drv.mac_addr_48[i+1]);
	}
	printf("\r\n");

	while (1) {
		timer_sleep(1000);
	}
}
