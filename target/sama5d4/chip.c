/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
#include "serial/console.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

struct chipid {
	uint32_t    exid; /**< EXID */
	const char* name; /**< Chip Name */
};

struct peripheral_xdma {
	uint32_t id;   /**< Peripheral ID */
	uint8_t  iftx; /**< DMA Interface for TX */
	uint8_t  ifrx; /**< DMA Interface for RX */
};

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct chipid _exid_names[] = {
	{ CHIPID_EXID_SAMA5D41, "SAMA5D41" },
	{ CHIPID_EXID_SAMA5D42, "SAMA5D42" },
	{ CHIPID_EXID_SAMA5D43, "SAMA5D43" },
	{ CHIPID_EXID_SAMA5D44, "SAMA5D44" },
};

/* default console used by ROM-code */
static const struct _console_cfg _console_cfg =
	{ USART3, 115200, PIN_USART3_TXD, PIN_USART3_RXD };

static const uint8_t _h64_peripherals[] = {
	ID_ARM,     /* 2: Performance Monitor Unit (ARM) */
	ID_XDMAC0,  /* 8: DMA Controller 0 (XDMAC0) */
	ID_CPKCC,   /* 10: Classic Public Key Crypto Controller (CPKCC) */
	ID_AESB,    /* 13: AES bridge (AESB) */
	ID_MPDDRC,  /* 16: MPDDR controller (MPDDRC) */
	ID_MATRIX0, /* 18: H64MX, 64-bit AHB Matrix (MATRIX0) */
	ID_VDEC,    /* 19: Video Decoder (VDEC) */
	ID_XDMAC1,  /* 50: DMA Controller 1 (XDMAC1) */
	ID_LCDC,    /* 51: LCD Controller (LCDC) */
	ID_ISI,     /* 52: Camera Interface (ISI) */
	ID_L2CC,    /* 67: L2 Cache Controller  (L2CC) */
};

static const struct peripheral_xdma _xdmac0_peripherals[] = {
	{ ID_HSMCI0,    0,  0 },
	{ ID_HSMCI1,    1,  1 },
	{ ID_TWI0,      2,  3 },
	{ ID_TWI1,      4,  5 },
	{ ID_TWI2,      6,  7 },
	{ ID_TWI3,      8,  9 },
	{ ID_SPI0,     10, 11 },
	{ ID_SPI1,     12, 13 },
	{ ID_SPI2,     14, 15 },
	{ ID_USART2,   16, 17 },
	{ ID_USART3,   18, 19 },
	{ ID_USART4,   20, 21 },
	{ ID_UART0,    22, 23 },
	{ ID_UART1,    24, 25 },
	{ ID_SSC0,     26, 27 },
	{ ID_SSC1,     28, 29 },
	{ ID_DBGU,     30, 31 },
	{ ID_ADC,    0xff, 32 },
	{ ID_SMD,      33, 34 },
	{ ID_USART0,   36, 37 },
	{ ID_USART1,   38, 39 },
	{ ID_AES,      41, 40 },
	{ ID_TDES,     42, 43 },
	{ ID_SHA,      44, 0xff },
};

static const struct peripheral_xdma _xdmac1_peripherals[] = {
	{ ID_HSMCI0,    0,  0 },
	{ ID_HSMCI1,    1,  1 },
	{ ID_TWI0,      2,  3 },
	{ ID_TWI1,      4,  5 },
	{ ID_TWI2,      6,  7 },
	{ ID_TWI3,      8,  9 },
	{ ID_SPI0,     10, 11 },
	{ ID_SPI1,     12, 13 },
	{ ID_SPI2,     14, 15 },
	{ ID_USART2,   16, 17 },
	{ ID_USART3,   18, 19 },
	{ ID_USART4,   20, 21 },
	{ ID_UART0,    22, 23 },
	{ ID_UART1,    24, 25 },
	{ ID_SSC0,     26, 27 },
	{ ID_SSC1,     28, 29 },
	{ ID_DBGU,     30, 31 },
	{ ID_ADC,    0xff, 32 },
	{ ID_SMD,      33, 34 },
};

/*----------------------------------------------------------------------------
 *        Private functions
 *----------------------------------------------------------------------------*/

static const struct peripheral_xdma *get_peripheral_xdma(uint32_t id, Xdmac *xdmac)
{
	const struct peripheral_xdma *_xdmac_peripherals;
	int count, i;

	if (xdmac == XDMAC0) {
		_xdmac_peripherals = _xdmac0_peripherals;
		count = ARRAY_SIZE(_xdmac0_peripherals);
	} else if (xdmac == XDMAC1) {
		_xdmac_peripherals = _xdmac1_peripherals;
		count = ARRAY_SIZE(_xdmac1_peripherals);
	} else {
		return NULL;
	}

	for (i = 0; i < count; i++) {
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
	int i;

	if ((DBGU->DBGU_CIDR & ~DBGU_CIDR_VERSION_Msk) ==
			CHIPID_CIDR_SAMA5D4) {
		uint32_t exid = DBGU->DBGU_EXID;
		for (i = 0; i < ARRAY_SIZE(_exid_names); i++) {
			if (_exid_names[i].exid == exid)
				return _exid_names[i].name;
		}
	}

	return "Unknown";
}

void get_romcode_console(struct _console_cfg* config)
{
	memcpy(config, &_console_cfg, sizeof(*config));
}

Matrix* get_peripheral_matrix(uint32_t id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(_h64_peripherals); i++)
		if (_h64_peripherals[i] == id)
			return MATRIX0; // AHB 64-bit matrix
	return MATRIX1; // AHB 32-bit matrix
}

uint32_t get_peripheral_clock_matrix_div(uint32_t id)
{
	Matrix* matrix = get_peripheral_matrix(id);

	if (matrix == MATRIX1) {
		if (PMC->PMC_MCKR & PMC_MCKR_H32MXDIV_H32MXDIV2)
			return 2;
		else
			return 1;
	}

	return 1;
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
