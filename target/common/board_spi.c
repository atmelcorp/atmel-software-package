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
#include "nvm/spi-nor/spi-nor.h"
#include "peripherals/bus.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_HAVE_SPI_AT25) && defined(CONFIG_HAVE_QSPI)
static struct spi_flash _spi_flash[2];
#else
static struct spi_flash _spi_flash[1];
#endif

static const struct spi_flash_cfg _spi_flash_cfg[] = {
#if defined(CONFIG_HAVE_QSPI) && defined(BOARD_QSPIFLASH_ADDR)
	{
		.type = SPI_FLASH_TYPE_QSPI,
		.baudrate = BOARD_QSPIFLASH_BAUDRATE,
		.mode = SPI_FLASH_MODE0,
		.qspi = {
			.addr = BOARD_QSPIFLASH_ADDR,
		},
	},
#endif
#ifdef BOARD_AT25_BUS
	{
		.type = SPI_FLASH_TYPE_SPI,
		.baudrate = BOARD_AT25_BITRATE,
		.mode = BOARD_AT25_SPI_MODE,
		.spi = {
			.bus_cfg = {
				.bus = BOARD_AT25_BUS,
				.spi_dev = {
					.chip_select = BOARD_AT25_CHIP_SELECT,
					.delay = {
						.bs = BOARD_AT25_DLYBS,
						.bct = BOARD_AT25_DLYBCT,
					},
				},
			},
		},
	},
#endif
	{ 0 },
};

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

void board_cfg_spi_flash(void)
{
	int i;

#ifdef BOARD_QSPIFLASH_PINS
	struct _pin pins_qspi[] = BOARD_QSPIFLASH_PINS;

	pio_configure(pins_qspi, ARRAY_SIZE(pins_qspi));
#endif

	for (i = 0; i < ARRAY_SIZE(_spi_flash) && _spi_flash_cfg[i].type != 0; i++) {
		if (spi_nor_configure(&_spi_flash[i], &_spi_flash_cfg[i]) < 0)
			trace_fatal("spi-nor: device%d: not configured\r\n", i);
	}
}

struct spi_flash * board_get_spi_flash(uint8_t idx)
{
	if (idx < ARRAY_SIZE(_spi_flash))
		return &_spi_flash[idx];

	return NULL;
}
