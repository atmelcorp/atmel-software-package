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
#include "errno.h"
#include "gpio/pio.h"
#include "nvm/spi-nor/at25.h"
#ifdef CONFIG_HAVE_QSPI
#include "nvm/spi-nor/qspiflash.h"
#include "spi/qspi.h"
#endif
#include "peripherals/bus.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_SPI_AT25
static struct _at25 at25 = {
	.cfg = {
		.bus = BOARD_AT25_BUS,
		.spi_dev = {
			.chip_select = BOARD_AT25_CHIP_SELECT,
			.bitrate = BOARD_AT25_BITRATE,
			.delay = {
				.bs = BOARD_AT25_DLYBS,
				.bct = BOARD_AT25_DLYBCT,
			},
			.spi_mode = BOARD_AT25_SPI_MODE,
		},
	},
};
#endif

#ifdef CONFIG_HAVE_QSPI
static struct _qspiflash qspiflash;
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void board_cfg_spi_bus(void)
{

#ifdef BOARD_SPI_BUS0
	const struct _pin pins_spi_bus0[] = BOARD_SPI_BUS0_PINS;
	const struct _bus_iface iface_bus0 = {
		.type = BUS_TYPE_SPI,
		.spi = {
			.hw = BOARD_SPI_BUS0,
		},
		.transfer_mode = BOARD_SPI_BUS0_MODE,
	};
	pio_configure(pins_spi_bus0, ARRAY_SIZE(pins_spi_bus0));
	bus_configure(BUS(BUS_TYPE_SPI, 0), &iface_bus0);
#endif
#ifdef BOARD_SPI_BUS1
	const struct _pin pins_spi_bus1[] = BOARD_SPI_BUS1_PINS;
	const struct _bus_iface iface_bus1 = {
		.type = BUS_TYPE_SPI,
		.spi = {
			.hw = BOARD_SPI_BUS1,
		},
		.transfer_mode = BOARD_SPI_BUS1_MODE,
	};
	pio_configure(pins_spi_bus1, ARRAY_SIZE(pins_spi_bus1));
	bus_configure(BUS(BUS_TYPE_SPI, 1), &iface_bus1);
#endif
#ifdef BOARD_SPI_BUS2
	const struct _pin pins_spi_bus2[] = BOARD_SPI_BUS2_PINS;
	const struct _bus_iface iface_bus2 = {
		.type = BUS_TYPE_SPI,
		.spi = {
			.hw = BOARD_SPI_BUS2,
		},
		.transfer_mode = BOARD_SPI_BUS2_MODE,
	};
	pio_configure(pins_spi_bus2, ARRAY_SIZE(pins_spi_bus2));
	bus_configure(BUS(BUS_TYPE_SPI, 2), &iface_bus2);
#endif
#ifdef BOARD_SPI_BUS3
	const struct _pin pins_spi_bus3[] = BOARD_SPI_BUS3_PINS;
	const struct _bus_iface iface_bus3 = {
		.type = BUS_TYPE_SPI,
		.spi = {
			.hw = BOARD_SPI_BUS3,
		},
		.transfer_mode = BOARD_SPI_BUS3_MODE,
	};
	pio_configure(pins_spi_bus3, ARRAY_SIZE(pins_spi_bus3));
	bus_configure(BUS(BUS_TYPE_SPI, 3), &iface_bus3);
#endif
#ifdef BOARD_SPI_BUS4
	const struct _pin pins_spi_bus4[] = BOARD_SPI_BUS4_PINS;
	const struct _bus_iface iface_bus4 = {
		.type = BUS_TYPE_SPI,
		.spi = {
			.hw = BOARD_SPI_BUS4,
		},
		.transfer_mode = BOARD_SPI_BUS4_MODE,
	};
	pio_configure(pins_spi_bus4, ARRAY_SIZE(pins_spi_bus4));
	bus_configure(BUS(BUS_TYPE_SPI, 4), &iface_bus4);
#endif
#ifdef BOARD_SPI_BUS5
	const struct _pin pins_spi_bus5[] = BOARD_SPI_BUS5_PINS;
	const struct _bus_iface iface_bus5 = {
		.type = BUS_TYPE_SPI,
		.spi = {
			.hw = BOARD_SPI_BUS5,
		},
		.transfer_mode = BOARD_SPI_BUS5_MODE,
	};
	pio_configure(pins_spi_bus5, ARRAY_SIZE(pins_spi_bus5));
	bus_configure(BUS(BUS_TYPE_SPI, 5), &iface_bus5);
#endif
}

#ifdef CONFIG_HAVE_SPI_AT25
void board_cfg_at25(void)
{
	/* Open serial flash device */
	int rc = at25_configure(&at25);
	if (rc == -ENODEV)
		trace_error("AT25: Device not supported!\r\n");
	else if (rc < 0)
		trace_error("AT25: Initialization error!\r\n");

	if (at25_set_protection(&at25, false) < 0)
		trace_error("AT25: Protection desactivation failed!\r\n");
}

struct _at25* board_get_at25(void)
{
	return &at25;
}
#endif /* CONFIG_HAVE_SPI_AT25 */

#ifdef CONFIG_HAVE_QSPI
void board_cfg_qspiflash(void)
{
#ifdef BOARD_QSPIFLASH_PINS
	struct _pin pins_qspi[] = BOARD_QSPIFLASH_PINS;

	pio_configure(pins_qspi, ARRAY_SIZE(pins_qspi));

	qspi_initialize(BOARD_QSPIFLASH_ADDR);
	qspi_set_baudrate(BOARD_QSPIFLASH_ADDR, BOARD_QSPIFLASH_BAUDRATE);

	if (qspiflash_configure(&qspiflash, BOARD_QSPIFLASH_ADDR) < 0)
		trace_fatal("qspi: not configured\r\n");
#endif
}

struct _qspiflash* board_get_qspiflash(void)
{
	return &qspiflash;
}
#endif /* CONFIG_HAVE_QSPI */
