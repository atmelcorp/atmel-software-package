/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016-2017, Atmel Corporation
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

#include <errno.h>

#include "applet.h"
#include "bootconfig.h"
#include "chip.h"
#include "nvm/sfc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define BOOTCFG_BSCR    0
#define BOOTCFG_BUREG0  1
#define BOOTCFG_BUREG1  2
#define BOOTCFG_BUREG2  3
#define BOOTCFG_BUREG3  4
#define BOOTCFG_FUSE    5

#define FUSE_BOOTCONFIG_WORD_POS   16

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static void print_bscr(uint32_t bsc_cr)
{
	trace_warning_wp("BSCR: 0x%08x -> ", (unsigned)bsc_cr);

	if (bsc_cr & BSC_CR_BUREG_VALID)
		trace_warning_wp("BUREG_VALID");

	switch (bsc_cr & BSC_CR_BUREG_INDEX_Msk) {
	case BSC_CR_BUREG_0:
		trace_warning_wp(" BUREG_0");
		break;
	case BSC_CR_BUREG_1:
		trace_warning_wp(" BUREG_1");
		break;
	case BSC_CR_BUREG_2:
		trace_warning_wp(" BUREG_2");
		break;
	case BSC_CR_BUREG_3:
		trace_warning_wp(" BUREG_3");
		break;
	}

	trace_warning_wp("\r\n");
}

static void print_bcw(const char* name, uint32_t value)
{
	trace_warning_wp("%s: 0x%08x ->", name, (unsigned)value);

	switch (value & BCW_QSPI_0_Msk) {
	case BCW_QSPI_0_IOSET_1:
		trace_warning_wp(" QSPI_0_IOSET_1");
		break;
	case BCW_QSPI_0_IOSET_2:
		trace_warning_wp(" QSPI_0_IOSET_2*");
		break;
	case BCW_QSPI_0_IOSET_3:
		trace_warning_wp(" QSPI_0_IOSET_3*");
		break;
	}

	switch (value & BCW_QSPI_1_Msk) {
	case BCW_QSPI_1_IOSET_1:
		trace_warning_wp(" QSPI_1_IOSET_1");
		break;
	case BCW_QSPI_1_IOSET_2:
		trace_warning_wp(" QSPI_1_IOSET_2*");
		break;
	case BCW_QSPI_1_IOSET_3:
		trace_warning_wp(" QSPI_1_IOSET_3*");
		break;
	}

	switch (value & BCW_SPI_0_Msk) {
	case BCW_SPI_0_IOSET_1:
		trace_warning_wp(" SPI_0_IOSET_1");
		break;
	case BCW_SPI_0_IOSET_2:
		trace_warning_wp(" SPI_0_IOSET_2*");
		break;
	}

	switch (value & BCW_SPI_1_Msk) {
	case BCW_SPI_1_IOSET_1:
		trace_warning_wp(" SPI_1_IOSET_1");
		break;
	case BCW_SPI_1_IOSET_2:
		trace_warning_wp(" SPI_1_IOSET_2*");
		break;
	case BCW_SPI_1_IOSET_3:
		trace_warning_wp(" SPI_1_IOSET_3*");
		break;
	}

	switch (value & BCW_NFC_Msk) {
	case BCW_NFC_IOSET_1:
		trace_warning_wp(" NFC_IOSET_1");
		break;
	case BCW_NFC_IOSET_2:
		trace_warning_wp(" NFC_IOSET_2*");
		break;
	}

	if ((value & BCW_SDMMC_0_DISABLED) == 0)
		trace_warning_wp(" SDMMC_0");

	if ((value & BCW_SDMMC_1_DISABLED) == 0)
		trace_warning_wp(" SDMMC_1");

	switch (value & BCW_UART_CONSOLE_Msk) {
	case BCW_UART_CONSOLE_UART1_IOSET_1:
		trace_warning_wp(" CONSOLE_UART1_IOSET_1");
		break;
	case BCW_UART_CONSOLE_UART0_IOSET_1:
		trace_warning_wp(" CONSOLE_UART0_IOSET_1*");
		break;
	case BCW_UART_CONSOLE_UART1_IOSET_2:
		trace_warning_wp(" CONSOLE_UART1_IOSET_2*");
		break;
	case BCW_UART_CONSOLE_UART2_IOSET_1:
		trace_warning_wp(" CONSOLE_UART2_IOSET_1*");
		break;
	case BCW_UART_CONSOLE_UART2_IOSET_2:
		trace_warning_wp(" CONSOLE_UART2_IOSET_2*");
		break;
	case BCW_UART_CONSOLE_UART2_IOSET_3:
		trace_warning_wp(" CONSOLE_UART2_IOSET_3*");
		break;
	case BCW_UART_CONSOLE_UART3_IOSET_1:
		trace_warning_wp(" CONSOLE_UART3_IOSET_1*");
		break;
	case BCW_UART_CONSOLE_UART3_IOSET_2:
		trace_warning_wp(" CONSOLE_UART3_IOSET_2*");
		break;
	case BCW_UART_CONSOLE_UART3_IOSET_3:
		trace_warning_wp(" CONSOLE_UART3_IOSET_3*");
		break;
	case BCW_UART_CONSOLE_UART4_IOSET_1:
		trace_warning_wp(" CONSOLE_UART4_IOSET_1*");
		break;
	}

	switch (value & BCW_JTAG_IO_SET_Msk) {
	case BCW_JTAG_IOSET_1:
		trace_warning_wp(" JTAG_IOSET_1");
		break;
	case BCW_JTAG_IOSET_2:
		trace_warning_wp(" JTAG_IOSET_2*");
		break;
	case BCW_JTAG_IOSET_3:
		trace_warning_wp(" JTAG_IOSET_3*");
		break;
	case BCW_JTAG_IOSET_4:
		trace_warning_wp(" JTAG_IOSET_4*");
		break;
	}

	if (value & BCW_EXT_MEM_BOOT_ENABLE)
		trace_warning_wp(" EXT_MEM_BOOT*");

	if (value & BCW_QSPI_XIP_MODE)
		trace_warning_wp(" QSPI_XIP_MODE*");

	if (value & BCW_DISABLE_BSCR)
		trace_warning_wp(" DISABLE_BSCR*");

	if (value & BCW_DISABLE_MONITOR)
		trace_warning_wp(" DISABLE_MONITOR*");

	if (value & BCW_SECURE_MODE)
		trace_warning_wp(" SECURE_MODE*");

	trace_warning_wp("\r\n");
}

/*----------------------------------------------------------------------------
 *         Public functions
 *----------------------------------------------------------------------------*/

int bootcfg_initialize(void)
{
	/* nothing here */
	return 0;
}

int bootcfg_print(uint32_t index, uint32_t value)
{
	switch (index) {
	case BOOTCFG_BSCR:
		print_bscr(value);
		break;
	case BOOTCFG_BUREG0:
		print_bcw("BUREG0", value);
		break;
	case BOOTCFG_BUREG1:
		print_bcw("BUREG1", value);
		break;
	case BOOTCFG_BUREG2:
		print_bcw("BUREG2", value);
		break;
	case BOOTCFG_BUREG3:
		print_bcw("BUREG3", value);
		break;
	case BOOTCFG_FUSE:
		print_bcw("FUSE", value);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

int bootcfg_read(uint32_t index, uint32_t* value)
{
	switch (index) {
	case BOOTCFG_BSCR:
		*value = BSC->BSC_CR;
		break;
	case BOOTCFG_BUREG0:
		*value = SECURAM->BUREG[0];
		break;
	case BOOTCFG_BUREG1:
		*value = SECURAM->BUREG[1];
		break;
	case BOOTCFG_BUREG2:
		*value = SECURAM->BUREG[2];
		break;
	case BOOTCFG_BUREG3:
		*value = SECURAM->BUREG[3];
		break;
	case BOOTCFG_FUSE:
		*value = sfc_read(FUSE_BOOTCONFIG_WORD_POS);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

int bootcfg_write(uint32_t index, uint32_t value)
{
	uint32_t bureg0, bureg1, bureg2, bureg3;

	bureg0 = SECURAM->BUREG[0];
	bureg1 = SECURAM->BUREG[1];
	bureg2 = SECURAM->BUREG[2];
	bureg3 = SECURAM->BUREG[3];

	switch (index) {
	case BOOTCFG_BSCR:
		BSC->BSC_CR = (value & ~BSC_CR_WPKEY_Msk) | BSC_CR_WPKEY;
		break;
	case BOOTCFG_BUREG0:
		SECURAM->BUREG[0] = value;
		SECURAM->BUREG[1] = bureg1;
		SECURAM->BUREG[2] = bureg2;
		SECURAM->BUREG[3] = bureg3;
		break;
	case BOOTCFG_BUREG1:
		SECURAM->BUREG[0] = bureg0;
		SECURAM->BUREG[1] = value;
		SECURAM->BUREG[2] = bureg2;
		SECURAM->BUREG[3] = bureg3;
		break;
	case BOOTCFG_BUREG2:
		SECURAM->BUREG[0] = bureg0;
		SECURAM->BUREG[1] = bureg1;
		SECURAM->BUREG[2] = value;
		SECURAM->BUREG[3] = bureg3;
		break;
	case BOOTCFG_BUREG3:
		SECURAM->BUREG[0] = bureg0;
		SECURAM->BUREG[1] = bureg1;
		SECURAM->BUREG[2] = bureg2;
		SECURAM->BUREG[3] = value;
		break;
	case BOOTCFG_FUSE:
		sfc_enable();
		sfc_write(FUSE_BOOTCONFIG_WORD_POS, value);
		sfc_disable();
		break;
	default:
		return -EINVAL;
	}

	return 0;
}
