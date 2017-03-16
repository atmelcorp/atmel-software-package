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

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "applet.h"
#include "chip.h"
#include "nvm/sfc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#if !defined(CONFIG_SOC_SAMA5D2)
#error Unsupported SOC!
#endif

#define BOOTCFG_BSCR    0
#define BOOTCFG_BUREG0  1
#define BOOTCFG_BUREG1  2
#define BOOTCFG_BUREG2  3
#define BOOTCFG_BUREG3  4
#define BOOTCFG_FUSE    5

/** Mailbox content for the 'read boot config' command. */
union read_bootcfg_mailbox
{
	struct {
		/** Configuration index to read */
		uint32_t index;
	} in;

	struct {
		/** Configuration value */
		uint32_t value;
	} out;
};

/** Mailbox content for the 'write boot config' command. */
union write_bootcfg_mailbox
{
	struct {
		/** Configuration index to read */
		uint32_t index;

		/** Configuration value */
		uint32_t value;
	} in;
};

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

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_INITIALIZE);

	if (!applet_set_init_params(mbx))
		return APPLET_FAIL;

	trace_warning_wp("\r\nApplet 'BootConfig' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	mbx->out.buf_addr = 0;
	mbx->out.buf_size = 0;
	mbx->out.page_size = 0;
	mbx->out.mem_size = 0;
	mbx->out.erase_support = 0;
	mbx->out.nand_header = 0;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_bootcfg(uint32_t cmd, uint32_t *mailbox)
{
	union read_bootcfg_mailbox *mbx = (union read_bootcfg_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_READ_BOOTCFG);

	switch (mbx->in.index) {
	case BOOTCFG_BSCR:
		mbx->out.value = BSC->BSC_CR;
		print_bscr(mbx->out.value);
		break;
	case BOOTCFG_BUREG0:
		mbx->out.value = SECURAM->BUREG[0];
		print_bcw("BUREG0", mbx->out.value);
		break;
	case BOOTCFG_BUREG1:
		mbx->out.value = SECURAM->BUREG[1];
		print_bcw("BUREG1", mbx->out.value);
		break;
	case BOOTCFG_BUREG2:
		mbx->out.value = SECURAM->BUREG[2];
		print_bcw("BUREG2", mbx->out.value);
		break;
	case BOOTCFG_BUREG3:
		mbx->out.value = SECURAM->BUREG[3];
		print_bcw("BUREG3", mbx->out.value);
		break;
	case BOOTCFG_FUSE:
		mbx->out.value = sfc_read(FUSE_BOOTCONFIG_WORD_POS);
		print_bcw("FUSE", mbx->out.value);
		break;
	default:
		trace_error("Unknown configuration index %u\r\n",
				(unsigned)mbx->in.index);
		return APPLET_FAIL;
	}


	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_write_bootcfg(uint32_t cmd, uint32_t *mailbox)
{
	union write_bootcfg_mailbox *mbx = (union write_bootcfg_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_WRITE_BOOTCFG);

	uint32_t bureg0, bureg1, bureg2, bureg3;

	bureg0 = SECURAM->BUREG[0];
	bureg1 = SECURAM->BUREG[1];
	bureg2 = SECURAM->BUREG[2];
	bureg3 = SECURAM->BUREG[3];

	switch (mbx->in.index) {
	case BOOTCFG_BSCR:
		trace_warning_wp("Writing 0x%08x to BSC CR\r\n",
		              (unsigned)mbx->in.value);
		BSC->BSC_CR = (mbx->in.value & ~BSC_CR_WPKEY_Msk) | BSC_CR_WPKEY;
		break;
	case BOOTCFG_BUREG0:
		trace_warning_wp("Writing 0x%08x to BUREG[0]\r\n",
		              (unsigned)mbx->in.value);
		SECURAM->BUREG[0] = mbx->in.value;
		SECURAM->BUREG[1] = bureg1;
		SECURAM->BUREG[2] = bureg2;
		SECURAM->BUREG[3] = bureg3;
		break;
	case BOOTCFG_BUREG1:
		trace_warning_wp("Writing 0x%08x to BUREG[1]\r\n",
		              (unsigned)mbx->in.value);
		SECURAM->BUREG[0] = bureg0;
		SECURAM->BUREG[1] = mbx->in.value;
		SECURAM->BUREG[2] = bureg2;
		SECURAM->BUREG[3] = bureg3;
		break;
	case BOOTCFG_BUREG2:
		trace_warning_wp("Writing 0x%08x to BUREG[2]\r\n",
		              (unsigned)mbx->in.value);
		SECURAM->BUREG[0] = bureg0;
		SECURAM->BUREG[1] = bureg1;
		SECURAM->BUREG[2] = mbx->in.value;
		SECURAM->BUREG[3] = bureg3;
		break;
	case BOOTCFG_BUREG3:
		trace_warning_wp("Writing 0x%08x to BUREG[3]\r\n",
		              (unsigned)mbx->in.value);
		SECURAM->BUREG[0] = bureg0;
		SECURAM->BUREG[1] = bureg1;
		SECURAM->BUREG[2] = bureg2;
		SECURAM->BUREG[3] = mbx->in.value;
		break;
	case BOOTCFG_FUSE:
		trace_warning_wp("Writing 0x%08x to bootcfg fuse (fuse #%d)\r\n",
		              (unsigned)mbx->in.value,
			      FUSE_BOOTCONFIG_WORD_POS);
		sfc_enable();
		sfc_write(FUSE_BOOTCONFIG_WORD_POS, mbx->in.value);
		sfc_disable();
		break;
	default:
		trace_error("Unknown configuration index %u\r\n",
				(unsigned)mbx->in.index);
		return APPLET_FAIL;
	}

	return APPLET_SUCCESS;
}

/*----------------------------------------------------------------------------
 *         Commands list
 *----------------------------------------------------------------------------*/

const struct applet_command applet_commands[] = {
	{ APPLET_CMD_INITIALIZE, handle_cmd_initialize },
	{ APPLET_CMD_READ_BOOTCFG, handle_cmd_read_bootcfg },
	{ APPLET_CMD_WRITE_BOOTCFG, handle_cmd_write_bootcfg },
	{ 0, NULL }
};
