/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
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

#include "applet.h"
#include "chip.h"
#include "trace.h"

#include "peripherals/sfc.h"

#include <assert.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#if !defined(CONFIG_SOC_SAMA5D2)
#error Unsupported SOC!
#endif

#define FUSE_BOOTCONFIG_WORD_POS   16

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static void print_bscr(void)
{
	uint32_t bsc_cr = BSC->BSC_CR;

	printf("0x%08x -> ", (unsigned)bsc_cr);

	if (bsc_cr & BSC_CR_BUREG_VALID)
		printf("BUREG_VALID");
	else
		printf("BUREG_INVALID");

	switch (bsc_cr & BSC_CR_BUREG_INDEX_Msk) {
	case BSC_CR_BUREG_0:
		printf(" BUREG0");
		break;
	case BSC_CR_BUREG_1:
		printf(" BUREG1");
		break;
	case BSC_CR_BUREG_2:
		printf(" BUREG2");
		break;
	case BSC_CR_BUREG_3:
		printf(" BUREG3");
		break;
	}

}

static void print_boot_config(uint32_t value)
{
	printf("0x%08x ->", (unsigned)value);

	switch (value & BCW_QSPI_0_Msk) {
	case BCW_QSPI_0_IOSET_1:
		printf(" QSPI_0_IOSET_1");
		break;
	case BCW_QSPI_0_IOSET_2:
		printf(" QSPI_0_IOSET_2*");
		break;
	case BCW_QSPI_0_IOSET_3:
		printf(" QSPI_0_IOSET_3*");
		break;
	}

	switch (value & BCW_QSPI_1_Msk) {
	case BCW_QSPI_1_IOSET_1:
		printf(" QSPI_1_IOSET_1");
		break;
	case BCW_QSPI_1_IOSET_2:
		printf(" QSPI_1_IOSET_2*");
		break;
	case BCW_QSPI_1_IOSET_3:
		printf(" QSPI_1_IOSET_3*");
		break;
	}

	switch (value & BCW_SPI_0_Msk) {
	case BCW_SPI_0_IOSET_1:
		printf(" SPI_0_IOSET_1");
		break;
	case BCW_SPI_0_IOSET_2:
		printf(" SPI_0_IOSET_2*");
		break;
	}

	switch (value & BCW_SPI_1_Msk) {
	case BCW_SPI_1_IOSET_1:
		printf(" SPI_1_IOSET_1");
		break;
	case BCW_SPI_1_IOSET_2:
		printf(" SPI_1_IOSET_2*");
		break;
	case BCW_SPI_1_IOSET_3:
		printf(" SPI_1_IOSET_3*");
		break;
	}

	switch (value & BCW_NFC_Msk) {
	case BCW_NFC_IOSET_1:
		printf(" NFC_IOSET_1");
		break;
	case BCW_NFC_IOSET_2:
		printf(" NFC_IOSET_2*");
		break;
	}

	if ((value & BCW_SDMMC_0_DISABLED) == 0)
		printf(" SDMMC_0");

	if ((value & BCW_SDMMC_1_DISABLED) == 0)
		printf(" SDMMC_1");

	switch (value & BCW_UART_CONSOLE_Msk) {
	case BCW_UART_CONSOLE_UART1_IOSET_1:
		printf(" CONSOLE_UART1_IOSET_1");
		break;
	case BCW_UART_CONSOLE_UART0_IOSET_1:
		printf(" CONSOLE_UART0_IOSET_1*");
		break;
	case BCW_UART_CONSOLE_UART1_IOSET_2:
		printf(" CONSOLE_UART1_IOSET_2*");
		break;
	case BCW_UART_CONSOLE_UART2_IOSET_1:
		printf(" CONSOLE_UART2_IOSET_1*");
		break;
	case BCW_UART_CONSOLE_UART2_IOSET_2:
		printf(" CONSOLE_UART2_IOSET_2*");
		break;
	case BCW_UART_CONSOLE_UART2_IOSET_3:
		printf(" CONSOLE_UART2_IOSET_3*");
		break;
	case BCW_UART_CONSOLE_UART3_IOSET_1:
		printf(" CONSOLE_UART3_IOSET_1*");
		break;
	case BCW_UART_CONSOLE_UART3_IOSET_2:
		printf(" CONSOLE_UART3_IOSET_2*");
		break;
	case BCW_UART_CONSOLE_UART3_IOSET_3:
		printf(" CONSOLE_UART3_IOSET_3*");
		break;
	case BCW_UART_CONSOLE_UART4_IOSET_1:
		printf(" CONSOLE_UART4_IOSET_1*");
		break;
	}

	switch (value & BCW_JTAG_IO_SET_Msk) {
	case BCW_JTAG_IOSET_1:
		printf(" JTAG_IOSET_1");
		break;
	case BCW_JTAG_IOSET_2:
		printf(" JTAG_IOSET_2*");
		break;
	case BCW_JTAG_IOSET_3:
		printf(" JTAG_IOSET_3*");
		break;
	case BCW_JTAG_IOSET_4:
		printf(" JTAG_IOSET_4*");
		break;
	}

	if (value & BCW_EXT_MEM_BOOT_ENABLE)
		printf(" EXT_MEM_BOOT*");

	if (value & BCW_QSPI_XIP_MODE)
		printf(" QSPI_XIP_MODE*");

	if (value & BCW_DISABLE_BSCR)
		printf(" DISABLE_BSCR*");

	if (value & BCW_DISABLE_MONITOR)
		printf(" DISABLE_MONITOR*");

	if (value & BCW_SECURE_MODE)
		printf(" SECURE_MODE*");
}

static void print_all_boot_config(void)
{
	printf("BSCR:          ");
	print_bscr();
	printf("\r\n");

	printf("BUREG[0]:      ");
	print_boot_config(SECURAM->BUREG_256b[0]);
	printf("\r\n");

	printf("BUREG[1]:      ");
	print_boot_config(SECURAM->BUREG_256b[0]);
	printf("\r\n");

	printf("BUREG[2]:      ");
	print_boot_config(SECURAM->BUREG_256b[0]);
	printf("\r\n");

	printf("BUREG[3]:      ");
	print_boot_config(SECURAM->BUREG_256b[0]);
	printf("\r\n");

	printf("Boot Cfg Fuse: ");
	print_boot_config(sfc_read(FUSE_BOOTCONFIG_WORD_POS));
	printf("\r\n");
}

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_INITIALIZE);

	applet_set_init_params(mbx->in.comm_type, mbx->in.trace_level);

	trace_info_wp("\r\nApplet 'Boot Debug' from softpack "
			SOFTPACK_VERSION ".\r\n");

	printf("--- Boot Config ---\r\n");
	print_all_boot_config();

	return APPLET_SUCCESS;
}

/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ 0, NULL }
};
