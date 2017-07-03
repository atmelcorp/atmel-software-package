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
#include "nvm/sfc.h"
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
	{ CHIPID_EXID_SAMA5D21_CU, "SAMA5D21-CU" },
	{ CHIPID_EXID_SAMA5D22_CU, "SAMA5D22-CU" },
	{ CHIPID_EXID_SAMA5D22_CN, "SAMA5D22-CN" },
	{ CHIPID_EXID_SAMA5D23_CU, "SAMA5D23-CU" },
	{ CHIPID_EXID_SAMA5D24_CX, "SAMA5D24-CX" },
	{ CHIPID_EXID_SAMA5D24_CU, "SAMA5D24-CU" },
	{ CHIPID_EXID_SAMA5D26_CU, "SAMA5D26-CU" },
	{ CHIPID_EXID_SAMA5D27_CU, "SAMA5D27-CU" },
	{ CHIPID_EXID_SAMA5D27_CN, "SAMA5D27-CN" },
	{ CHIPID_EXID_SAMA5D28_CU, "SAMA5D28-CU" },
	{ CHIPID_EXID_SAMA5D28_CN, "SAMA5D28-CN" },
	{ CHIPID_EXID_SAMA5D225_D1M, "SAMA5D225-D1M" },
	{ CHIPID_EXID_SAMA5D27_D5M, "SAMA5D27-D5M" },
	{ CHIPID_EXID_SAMA5D27_D1G, "SAMA5D27-D1G" },
	{ CHIPID_EXID_SAMA5D28_D1G, "SAMA5D28-D1G" },
};

/* default console used by ROM-code */
static const struct _console_cfg _console_cfg[] = {
	{ UART1, 115200, PIN_UART1_TXD_IOS1, PIN_UART1_RXD_IOS1 },
	{ UART0, 115200, PIN_UART0_TXD_IOS1, PIN_UART0_RXD_IOS1 },
	{ UART1, 115200, PIN_UART1_TXD_IOS2, PIN_UART1_RXD_IOS2 },
	{ UART2, 115200, PIN_UART2_TXD_IOS1, PIN_UART2_RXD_IOS1 },
	{ UART2, 115200, PIN_UART2_TXD_IOS2, PIN_UART2_RXD_IOS2 },
	{ UART2, 115200, PIN_UART2_TXD_IOS3, PIN_UART2_RXD_IOS3 },
	{ UART3, 115200, PIN_UART3_TXD_IOS1, PIN_UART3_RXD_IOS1 },
	{ UART3, 115200, PIN_UART3_TXD_IOS2, PIN_UART3_RXD_IOS2 },
	{ UART3, 115200, PIN_UART3_TXD_IOS3, PIN_UART3_RXD_IOS3 },
	{ UART4, 115200, PIN_UART4_TXD_IOS1, PIN_UART4_RXD_IOS1 },
};

static const uint8_t _h64_peripherals[] = {
	ID_ARM_PMU, /*  2: Performance Monitor Unit (PMU) (ARM_PMU) */
	ID_XDMAC0,  /*  6: DMA Controller 0 (XDMAC0) */
	ID_XDMAC1,  /*  7: DMA Controller 1 (XDMAC1) */
	ID_AES,     /*  9: Advanced Enion Standard (AES) */
	ID_AESB,    /* 10: AES bridge (AESB) */
	ID_SHA,     /* 12: SHA Signature (SHA) */
	ID_MPDDRC,  /* 13: MPDDR controller (MPDDRC) */
	ID_MATRIX0, /* 15: H64MX, 64-bit AHB Matrix (MATRIX0) */
	ID_SDMMC0,  /* 31: Secure Digital Multimedia Card Controller 0 (SDMMC0) */
	ID_SDMMC1,  /* 32: Secure Digital Multimedia Card Controller 1 (SDMMC1) */
	ID_LCDC,    /* 45: LCD Controller (LCDC) */
	ID_ISC,     /* 46: Camera Interface (ISC) */
	ID_QSPI0,   /* 52: QSPI 0 (QSPI0) */
	ID_QSPI1,   /* 53: QSPI 1 (QSPI1) */
	ID_L2CC,    /* 63: L2 Cache Controller (L2CC) */
};

static const struct peripheral_xdma _xdmac_peripherals[] = {
	{ ID_TWI0,        0,    1 },
	{ ID_TWI1,        2,    3 },
	{ ID_QSPI0,       4,    5 },
	{ ID_SPI0,        6,    7 },
	{ ID_SPI1,        8,    9 },
	{ ID_PWM0,       10, 0xff },
	{ ID_FLEXCOM0,   11,   12 },
	{ ID_FLEXCOM1,   13,   14 },
	{ ID_FLEXCOM2,   15,   16 },
	{ ID_FLEXCOM3,   17,   18 },
	{ ID_FLEXCOM4,   19,   20 },
	{ ID_SSC0,       21,   22 },
	{ ID_SSC1,       23,   24 },
	{ ID_ADC,      0xff,   25 },
	{ ID_AES,        26,   27 },
	{ ID_TDES,       28,   29 },
	{ ID_SHA,        30, 0xff },
	{ ID_I2SC0,      31,   32 },
	{ ID_I2SC1,      33,   34 },
	{ ID_UART0,      35,   36 },
	{ ID_UART1,      37,   38 },
	{ ID_UART2,      39,   40 },
	{ ID_UART3,      41,   42 },
	{ ID_UART4,      43,   44 },
	{ ID_TC0,      0xff,   45 },
	{ ID_TC1,      0xff,   46 },
	{ ID_CLASSD0,    47, 0xff },
	{ ID_QSPI0,      48,   49 },
	{ ID_PDMIC0,   0xff,   50 },
};

/*----------------------------------------------------------------------------
 *        Private functions
 *----------------------------------------------------------------------------*/

static const struct peripheral_xdma *get_peripheral_xdma(uint32_t id, Xdmac *xdmac)
{
	int i;

	if (xdmac != XDMAC0 && xdmac != XDMAC1) {
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
	int i;

	if ((CHIPID->CHIPID_CIDR & ~CHIPID_CIDR_VERSION_Msk) ==
			CHIPID_CIDR_SAMA5D2) {
		uint32_t exid = CHIPID->CHIPID_EXID;
		for (i = 0; i < ARRAY_SIZE(_exid_names); i++) {
			if (_exid_names[i].exid == exid)
				return _exid_names[i].name;
		}
	}

	return "Unknown";
}

void get_romcode_console(struct _console_cfg* config)
{
	uint32_t bcw;
	uint32_t console;

	/* read boot config word from fuse */
	bcw = sfc_read(16);

	/* if BSCR is not disabled and BUREG index is valid, use BUREG */
	if ((bcw & BCW_DISABLE_BSCR) == 0) {
		uint32_t bsc_cr = BSC->BSC_CR;
		if (bsc_cr & BSC_CR_BUREG_VALID) {
			uint32_t index = (bsc_cr & BSC_CR_BUREG_INDEX_Msk) >> BSC_CR_BUREG_INDEX_Pos;
			bcw = SECURAM->BUREG[index];
		}
	}

	/* configure console */
	console = (bcw & BCW_UART_CONSOLE_Msk) >> BCW_UART_CONSOLE_Pos;
	if (console < ARRAY_SIZE(_console_cfg))
		memcpy(config, &_console_cfg[console], sizeof(*config));
	else
		memset(config, 0, sizeof(*config));
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

int32_t get_peripheral_fifo_depth(void* addr)
{
	uint32_t size = -1;
	uint32_t tmp = (uint32_t)addr;
	switch (tmp) {
	case (uint32_t)FLEXUSART0:
#ifdef FLEXUSART1
	case (uint32_t)FLEXUSART1:
#endif
#ifdef FLEXUSART2
	case (uint32_t)FLEXUSART2:
#endif
#ifdef FLEXUSART3
	case (uint32_t)FLEXUSART3:
#endif
#ifdef FLEXUSART4
	case (uint32_t)FLEXUSART4:
#endif
		size = FLEXCOM_USART_FIFO_DEPTH;
		break;

	case (uint32_t)FLEXSPI0:
#ifdef FLEXSPI1
	case (uint32_t)FLEXSPI1:
#endif
#ifdef FLEXSPI2
	case (uint32_t)FLEXSPI2:
#endif
#ifdef FLEXSPI3
	case (uint32_t)FLEXSPI3:
#endif
#ifdef FLEXSPI4
	case (uint32_t)FLEXSPI4:
#endif
		size = FLEXCOM_SPI_FIFO_DEPTH;
		break;
	case (uint32_t)SPI0:
#ifdef SPI1
	case (uint32_t)SPI1:
#endif
		size = SPI_FIFO_DEPTH;
		break;
	case (uint32_t)FLEXTWI0:
#ifdef FLEXTWI1
	case (uint32_t)FLEXTWI1:
#endif
#ifdef FLEXTWI2
	case (uint32_t)FLEXTWI2:
#endif
#ifdef FLEXTWI3
	case (uint32_t)FLEXTWI3:
#endif
#ifdef FLEXTWI4
	case (uint32_t)FLEXTWI4:
#endif
#ifdef TWI0
	case (uint32_t)TWI0:
#endif
#ifdef TWI1
	case (uint32_t)TWI1:
#endif
		size = TWI_FIFO_DEPTH;
		break;
	default:
		size = -1;
	}
	return size;
}
