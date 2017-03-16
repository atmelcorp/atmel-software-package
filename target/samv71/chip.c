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

#include <string.h>

#include "chip.h"
#include "compiler.h"
#include "serial/console.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

struct chipid {
	uint32_t    cidr; /**< CIDR */
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

static const struct chipid _chipid_names[] = {
	{ CHIPID_CIDR_SAME70Q21, CHIPID_EXID_SAME70Q21, "SAME70Q21" },
	{ CHIPID_CIDR_SAME70Q20, CHIPID_EXID_SAME70Q20, "SAME70Q20" },
	{ CHIPID_CIDR_SAME70Q19, CHIPID_EXID_SAME70Q19, "SAME70Q19" },
	{ CHIPID_CIDR_SAME70N21, CHIPID_EXID_SAME70N21, "SAME70N21" },
	{ CHIPID_CIDR_SAME70N20, CHIPID_EXID_SAME70N20, "SAME70N20" },
	{ CHIPID_CIDR_SAME70N19, CHIPID_EXID_SAME70N19, "SAME70N19" },
	{ CHIPID_CIDR_SAME70J21, CHIPID_EXID_SAME70J21, "SAME70J21" },
	{ CHIPID_CIDR_SAME70J20, CHIPID_EXID_SAME70J20, "SAME70J20" },
	{ CHIPID_CIDR_SAME70J19, CHIPID_EXID_SAME70J19, "SAME70J19" },
	{ CHIPID_CIDR_SAMS70Q21, CHIPID_EXID_SAMS70Q21, "SAMS70Q21" },
	{ CHIPID_CIDR_SAMS70Q20, CHIPID_EXID_SAMS70Q20, "SAMS70Q20" },
	{ CHIPID_CIDR_SAMS70Q19, CHIPID_EXID_SAMS70Q19, "SAMS70Q19" },
	{ CHIPID_CIDR_SAMS70N21, CHIPID_EXID_SAMS70N21, "SAMS70N21" },
	{ CHIPID_CIDR_SAMS70N20, CHIPID_EXID_SAMS70N20, "SAMS70N20" },
	{ CHIPID_CIDR_SAMS70N19, CHIPID_EXID_SAMS70N19, "SAMS70N19" },
	{ CHIPID_CIDR_SAMS70J21, CHIPID_EXID_SAMS70J21, "SAMS70J21" },
	{ CHIPID_CIDR_SAMS70J20, CHIPID_EXID_SAMS70J20, "SAMS70J20" },
	{ CHIPID_CIDR_SAMS70J19, CHIPID_EXID_SAMS70J19, "SAMS70J19" },
	{ CHIPID_CIDR_SAMV70Q20, CHIPID_EXID_SAMV70Q20, "SAMV70Q20" },
	{ CHIPID_CIDR_SAMV70Q19, CHIPID_EXID_SAMV70Q19, "SAMV70Q19" },
	{ CHIPID_CIDR_SAMV70N20, CHIPID_EXID_SAMV70N20, "SAMV70N20" },
	{ CHIPID_CIDR_SAMV70N19, CHIPID_EXID_SAMV70N19, "SAMV70N19" },
	{ CHIPID_CIDR_SAMV70J20, CHIPID_EXID_SAMV70J20, "SAMV70J20" },
	{ CHIPID_CIDR_SAMV70J19, CHIPID_EXID_SAMV70J19, "SAMV70J19" },
	{ CHIPID_CIDR_SAMV71Q21, CHIPID_EXID_SAMV71Q21, "SAMV71Q21" },
	{ CHIPID_CIDR_SAMV71Q20, CHIPID_EXID_SAMV71Q20, "SAMV71Q20" },
	{ CHIPID_CIDR_SAMV71Q19, CHIPID_EXID_SAMV71Q19, "SAMV71Q19" },
	{ CHIPID_CIDR_SAMV71N21, CHIPID_EXID_SAMV71N21, "SAMV71N21" },
	{ CHIPID_CIDR_SAMV71N20, CHIPID_EXID_SAMV71N20, "SAMV71N20" },
	{ CHIPID_CIDR_SAMV71N19, CHIPID_EXID_SAMV71N19, "SAMV71N19" },
	{ CHIPID_CIDR_SAMV71J21, CHIPID_EXID_SAMV71J21, "SAMV71J21" },
	{ CHIPID_CIDR_SAMV71J20, CHIPID_EXID_SAMV71J20, "SAMV71J20" },
	{ CHIPID_CIDR_SAMV71J19, CHIPID_EXID_SAMV71J19, "SAMV71J19" },
};

/* default console used by ROM-code */
static const struct _console_cfg _console_cfg =
	{ UART0, 115200, PIN_UART0_TXD, PIN_UART0_RXD };

static const struct peripheral_xdma _xdmac_peripherals[] = {
	{ ID_HSMCI0,      0,    0 },
	{ ID_SPI0,        1,    2 },
	{ ID_SPI1,        3,    4 },
	{ ID_QSPI0,       5,    6 },
	{ ID_USART0,      7,    8 },
	{ ID_USART1,      9,   10 },
	{ ID_USART2,     11,   12 },
	{ ID_PWM0,       13, 0xff },
	{ ID_TWI0,       14,   15 },
	{ ID_TWI1,       16,   17 },
	{ ID_TWI2,       18,   19 },
	{ ID_UART0,      20,   21 },
	{ ID_UART1,      22,   23 },
	{ ID_UART2,      24,   25 },
	{ ID_UART3,      26,   27 },
	{ ID_UART4,      28,   29 },
	{ ID_DACC,       30, 0xff },
	{ ID_SSC0,       32,   33 },
	{ ID_PIOA,     0xff,   34 },
	{ ID_AFEC0,    0xff,   35 },
	{ ID_AFEC1,    0xff,   36 },
	{ ID_AES,        37,   38 },
	{ ID_PWM1,       39, 0xff },
	{ ID_TC0_CH0,  0xff,   40 },
	{ ID_TC1_CH0,  0xff,   41 },
	{ ID_TC2_CH0,  0xff,   42 },
	{ ID_TC3_CH0,  0xff,   43 },
	{ ID_I2SC0,      44,   45 }, /* Left or Left+Right */
	{ ID_I2SC1,      46,   47 }, /* Left or Left+Right */
	//{ ID_I2SC0,      48,   49 }, /* Right */
	//{ ID_I2SC1,      50,   51 }, /* Right */
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
	int i;
	uint32_t cidr = CHIPID->CHIPID_CIDR & ~CHIPID_CIDR_VERSION_Msk;
	uint32_t exid = CHIPID->CHIPID_EXID;

	for (i = 0; i < ARRAY_SIZE(_chipid_names); i++) {
		if (_chipid_names[i].cidr == cidr &&
		    _chipid_names[i].exid == exid)
			return _chipid_names[i].name;
	}

	return "Unknown";
}

void get_romcode_console(struct _console_cfg* config)
{
	memcpy(config, &_console_cfg, sizeof(*config));
}

uint8_t get_flash_wait_states(uint32_t frequency)
{
	/* Embedded Flash Wait States for Worst-Case Conditions */
	/* VDDIO 3.0V */
	const uint32_t max_freq[] = {
		23000000, 46000000, 69000000, 92000000, 115000000, 138000000 };
	int i;
	for (i = 0; i < ARRAY_SIZE(max_freq); i++)
		if (max_freq[i] >= frequency)
			break;
	return i;
}

uint32_t get_peripheral_clock_matrix_div(uint32_t id)
{
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
