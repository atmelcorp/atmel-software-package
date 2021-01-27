/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Atmel Corporation
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

#include <string.h>

#include "chip.h"
#include "compiler.h"
#include "peripherals/pmc.h"
#include "serial/console.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

struct peripheral_xdma {
	uint32_t id;   /**< Peripheral ID */
	uint8_t  iftx; /**< DMA Interface for TX */
	uint8_t  ifrx; /**< DMA Interface for RX */
};

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

/* default console used by ROM-code */
static const struct _console_cfg _console_cfg =
	{ DBGU, 115200, PIN_DBGU_TXD, PIN_DBGU_RXD };

static const struct peripheral_xdma _xdmac_peripherals[] = {
	{ ID_FLEXCOM0,    0,    1 },
	{ ID_FLEXCOM1,    2,    3 },
	{ ID_FLEXCOM2,    4,    5 },
	{ ID_FLEXCOM3,    6,    7 },
	{ ID_FLEXCOM4,    8,    9 },
	{ ID_FLEXCOM5,   10,   11 },
	{ ID_FLEXCOM6,   12,   13 },
	{ ID_FLEXCOM7,   14,   15 },
	{ ID_FLEXCOM8,   16,   17 },
	{ ID_FLEXCOM9,   18,   19 },
	{ ID_FLEXCOM10,  20,   21 },
	{ ID_FLEXCOM11,  22,   23 },
	{ ID_FLEXCOM12,  24,   25 },
	{ ID_QSPI0,      26,   27 },
	{ ID_DBGU,       28,   29 },
	{ ID_TDES,       31,   30 },
	{ ID_AES,        32,   33 },
	{ ID_SHA,        34,  0xff},
	{ ID_CLASSD0,    35, 0xff },
	{ ID_I2SMCC,     36,   37 },
	{ ID_SSC,        38,   39 },
	{ ID_ADC,      0xff,   40 },
	{ ID_TC0,      0xff,   41 },
	{ ID_TC1,      0xff,   42 },
/*	{ ID_TC0_TC1_CPA, 43,  0xff },
	{ ID_TC1_TC4_CPA, 44,  0xff },
	{ ID_TC0_TC1_CPB, 45,  0xff },
	{ ID_TC1_TC4_CPB, 46,  0xff },
	{ ID_TC0_TC1_CPC, 47,  0xff },
	{ ID_TC1_TC4_CPC, 48,  0xff },
	{ ID_TC0_TC1_EXT, 49,  0xff },
	{ ID_TC1_TC4_EXT, 50,  0xff },*/
};

/* must be sorted by peripheral ID */
static const uint32_t _div_peripherals[] = {
	ID_PIOA,
#ifdef CONFIG_HAVE_CAN
	ID_CAN0, ID_CAN1
#endif
};

/*----------------------------------------------------------------------------
 *        Private functions
 *----------------------------------------------------------------------------*/

static const struct peripheral_xdma *get_peripheral_xdma(uint32_t id, Xdmac *xdmac)
{
	int i;

	if (xdmac != XDMAC0) {
		return NULL;
	}

	for (i = 0; i < ARRAY_SIZE(_xdmac_peripherals); i++) {
		if (_xdmac_peripherals[i].id == id) {
			return &_xdmac_peripherals[i];
		}
	}

	return NULL;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

const char* get_chip_name(void)
{
	if ((DBGU->DBGU_CIDR & ~DBGU_CIDR_VERSION_Msk) ==
			CHIPID_CIDR_SAM9X60) {
		return "SAM9X60";
	}

	return "Unknown";
}

void get_romcode_console(struct _console_cfg* config)
{
	memcpy(config, &_console_cfg, sizeof(*config));
}

uint32_t get_peripheral_clock_matrix_div(uint32_t id)
{
	return 1;
}

uint32_t get_peripheral_clock_max_freq(uint32_t id)
{
	return pmc_get_master_clock();
}

bool peripheral_has_clock_div(uint32_t id)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(_div_peripherals) && _div_peripherals[i] <= id; i++)
		if (_div_peripherals[i] == id)
			return true;
	return false;
}

uint8_t get_peripheral_dma_channel(uint32_t id, Xdmac *xdmac, bool transmit)
{
	const struct peripheral_xdma *periph_xdma = get_peripheral_xdma(id, xdmac);
	if (periph_xdma) {
		return transmit ? periph_xdma->iftx : periph_xdma->ifrx;
	} else {
		return 0xff;
	}
}

bool is_peripheral_on_dma_controller(uint32_t id, Xdmac *xdmac)
{
	return get_peripheral_xdma(id, xdmac) != NULL;
}


int32_t get_peripheral_fifo_depth(void* addr)
{
	uint32_t size = -1;
	uint32_t tmp = (uint32_t)addr;
	switch (tmp) {
	case (uint32_t)FLEXUSART0:
	case (uint32_t)FLEXUSART1:
	case (uint32_t)FLEXUSART2:
	case (uint32_t)FLEXUSART3:
	case (uint32_t)FLEXUSART4:
	case (uint32_t)FLEXUSART5:
	case (uint32_t)FLEXUSART6:
	case (uint32_t)FLEXUSART7:
	case (uint32_t)FLEXUSART8:
	case (uint32_t)FLEXUSART9:
	case (uint32_t)FLEXUSART10:
	case (uint32_t)FLEXUSART11:
	case (uint32_t)FLEXUSART12:
		size = FLEXCOM_USART_FIFO_DEPTH;
		break;

	case (uint32_t)FLEXSPI0:
	case (uint32_t)FLEXSPI1:
	case (uint32_t)FLEXSPI2:
	case (uint32_t)FLEXSPI3:
	case (uint32_t)FLEXSPI4:
	case (uint32_t)FLEXSPI5:
		size = FLEXCOM_SPI_FIFO_DEPTH;
		break;
	case (uint32_t)FLEXTWI0:
	case (uint32_t)FLEXTWI1:
	case (uint32_t)FLEXTWI2:
	case (uint32_t)FLEXTWI3:
	case (uint32_t)FLEXTWI4:
	case (uint32_t)FLEXTWI5:
	case (uint32_t)FLEXTWI6:
	case (uint32_t)FLEXTWI7:
	case (uint32_t)FLEXTWI8:
	case (uint32_t)FLEXTWI9:
	case (uint32_t)FLEXTWI10:
	case (uint32_t)FLEXTWI11:
	case (uint32_t)FLEXTWI12:
		size = TWI_FIFO_DEPTH;
		break;
	default:
		size = -1;
	}
	return size;
}