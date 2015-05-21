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

#include "chip.h"

#include "serial/flexcom.h"
#include "serial/usart.h"
#include "core/wdt.h"
#include "core/pmc.h"
#include "core/aic.h"
#include "core/pio.h"
#include "core/pio_it.h"

Flexcom* flexcom = FLEXCOM3;
static const struct _pin usart_pins[] = PINS_FLEXCOM3_USART_IOS3;

static const char data [] = "-- Write FIFO test PADDING PADDING PADDING PADDING PADDING PADDING PADDING PADDING PADDING PADDING PADDING PADDING -- \r\n";

static void usart_handler(void)
{
	char read_buffer[33];
	uint32_t read = 0;
	*read_buffer = '\0';

	if (usart_is_rx_ready(&flexcom->usart)) {
		uint32_t size = usart_fifo_rx_size(&flexcom->usart);
		read = usart_read_stream(&flexcom->usart, read_buffer, size);
		read_buffer[read] = '\0';
	}
	flexcom->usart.US_CR = US_CR_RSTSTA;

	usart_write_stream(&flexcom->usart, read_buffer, read);
}

static void _configure_usart(void)
{
	pio_configure(usart_pins, 1);
	pmc_enable_peripheral(ID_USART3);

	aic_set_source_vector(ID_USART3, usart_handler);

	uint32_t mode = US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT;

	flexcom_select(flexcom, FLEX_MR_OPMODE_USART);

	usart_configure(&flexcom->usart, mode, 115200);

	usart_fifo_configure(&flexcom->usart, 16u, 7u, 4u,
			     US_FMR_RXRDYM_ONE_DATA | US_FMR_TXRDYM_FOUR_DATA);

	usart_enable_it(&flexcom->usart, US_IER_RXRDY);
	aic_enable(ID_USART3);
}

int main (void)
{
	/* Disable watchdog */
	WDT_Disable(WDT);

#if defined (ddram)
	MMU_Initialize((uint32_t *) 0x20C000);
	cp15_enable_mmu();
	cp15_enable_dcache();
	cp15_enable_icache();
#endif
	_configure_usart();

	usart_write_stream(&flexcom->usart, data, sizeof(data));

	while (1);
}
