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

#include "board_spi.h"
#include "trace.h"

#include "bus/spi-bus.h"

#include "peripherals/pio.h"

#include "memories/at25.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_SPI_AT25
static struct _at25 at25 = {
	.dev = {
		.bus = BOARD_AT25_BUS,
		.chip_select = BOARD_AT25_CHIP_SELECT,
		.bitrate = BOARD_AT25_BITRATE,
		.delay = {
			.bs = BOARD_AT25_DLYBS,
			.bct = BOARD_AT25_DLYBCT,
		},
		.spi_mode = BOARD_AT25_SPI_MODE,
	},
};
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void board_cfg_spi_bus(void)
{
#ifdef BOARD_SPI_BUS0
	const struct _pin pins_spi_bus0[] = BOARD_SPI_BUS0_PINS;
	pio_configure(pins_spi_bus0, ARRAY_SIZE(pins_spi_bus0));
	spi_bus_configure(0, BOARD_SPI_BUS0, BOARD_SPI_BUS0_MODE);
#endif
#ifdef BOARD_SPI_BUS1
	const struct _pin pins_spi_bus1[] = BOARD_SPI_BUS1_PINS;
	pio_configure(pins_spi_bus1, ARRAY_SIZE(pins_spi_bus1));
	spi_bus_configure(1, BOARD_SPI_BUS1, BOARD_SPI_BUS1_MODE);
#endif
#ifdef BOARD_SPI_BUS2
	const struct _pin pins_spi_bus2[] = BOARD_SPI_BUS2_PINS;
	pio_configure(pins_spi_bus2, ARRAY_SIZE(pins_spi_bus2));
	spi_bus_configure(2, BOARD_SPI_BUS2, BOARD_SPI_BUS2_MODE);
#endif
#ifdef BOARD_SPI_BUS3
	const struct _pin pins_spi_bus3[] = BOARD_SPI_BUS3_PINS;
	pio_configure(pins_spi_bus3, ARRAY_SIZE(pins_spi_bus3));
	spi_bus_configure(3, BOARD_SPI_BUS3, BOARD_SPI_BUS3_MODE);
#endif
#ifdef BOARD_SPI_BUS4
	const struct _pin pins_spi_bus4[] = BOARD_SPI_BUS4_PINS;
	pio_configure(pins_spi_bus4, ARRAY_SIZE(pins_spi_bus4));
	spi_bus_configure(4, BOARD_SPI_BUS4, BOARD_SPI_BUS4_MODE);
#endif
#ifdef BOARD_SPI_BUS5
	const struct _pin pins_spi_bus5[] = BOARD_SPI_BUS5_PINS;
	pio_configure(pins_spi_bus5, ARRAY_SIZE(pins_spi_bus5));
	spi_bus_configure(5, BOARD_SPI_BUS5, BOARD_SPI_BUS5_MODE);
#endif
}

#ifdef CONFIG_HAVE_SPI_AT25
void board_cfg_at25(void)
{
	/* Open serial flash device */
	int rc = at25_configure(&at25);
	if (rc == AT25_DEVICE_NOT_SUPPORTED)
		trace_error("AT25: Device not supported!\r\n");
	else if (rc != AT25_SUCCESS)
		trace_error("AT25: Initialization error!\r\n");

	if (at25_unprotect(&at25))
		trace_error("AT25: Protection desactivation failed!\r\n");
}

struct _at25 * board_get_at25(void)
{
	return &at25;
}
#endif /* CONFIG_HAVE_SPI_AT25 */
