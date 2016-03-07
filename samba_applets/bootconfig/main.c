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
#include "peripherals/sfc.h"
#include "trace.h"
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#if !defined(CONFIG_SOC_SAMA5D2)
#error Unsupported SOC!
#endif

/** Mailbox content for the 'read boot config' command. */
union read_bootcfg_mailbox
{
	struct {
	} in;

	struct {
		/** Boot Fuse */
		uint32_t boot_fuse;
		/** BSC CR register */
		uint32_t bsc_cr;
		/** BUREG registers */
		uint32_t bureg[4];
	} out;
};

#define WRITE_BOOTCFG_FLAG_KEY     (0xA5D2 << 16)
#define WRITE_BOOTCFG_FLAG_KEYMASK (0xFFFF << 16)
#define WRITE_BOOTCFG_FLAG_FUSE    (1 << 0)
#define WRITE_BOOTCFG_FLAG_BSCR    (1 << 1)
#define WRITE_BOOTCFG_FLAG_BUREG0  (1 << 2)
#define WRITE_BOOTCFG_FLAG_BUREG1  (1 << 3)
#define WRITE_BOOTCFG_FLAG_BUREG2  (1 << 4)
#define WRITE_BOOTCFG_FLAG_BUREG3  (1 << 5)

/** Mailbox content for the 'write boot config' command. */
union write_bootcfg_mailbox
{
	struct {
		/** Write flags */
		uint32_t flags;
		/** Boot Fuse */
		uint32_t boot_fuse;
		/** BSC CR register */
		uint32_t bsc_cr;
		/** BUREG registers */
		uint32_t bureg[4];
	} in;

	struct {
	} out;
};

#define FUSE_BOOTCONFIG_WORD_POS   16

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static void print_bscr(void)
{
	uint32_t bsc_cr = BSC->BSC_CR;

	trace_info_wp("0x%08x -> ", (unsigned)bsc_cr);

	if (bsc_cr & BSC_CR_BUREG_VALID)
		trace_info_wp("BUREG_VALID");
	else
		trace_info_wp("BUREG_INVALID");

	switch (bsc_cr & BSC_CR_BUREG_INDEX_Msk) {
	case BSC_CR_BUREG_0:
		trace_info_wp(" BUREG0");
		break;
	case BSC_CR_BUREG_1:
		trace_info_wp(" BUREG1");
		break;
	case BSC_CR_BUREG_2:
		trace_info_wp(" BUREG2");
		break;
	case BSC_CR_BUREG_3:
		trace_info_wp(" BUREG3");
		break;
	}

}

static void print_boot_config(uint32_t value)
{
	trace_info_wp("0x%08x ->", (unsigned)value);

	switch (value & BCW_QSPI_0_Msk) {
	case BCW_QSPI_0_IOSET_1:
		trace_info_wp(" QSPI_0_IOSET_1");
		break;
	case BCW_QSPI_0_IOSET_2:
		trace_info_wp(" QSPI_0_IOSET_2*");
		break;
	case BCW_QSPI_0_IOSET_3:
		trace_info_wp(" QSPI_0_IOSET_3*");
		break;
	}

	switch (value & BCW_QSPI_1_Msk) {
	case BCW_QSPI_1_IOSET_1:
		trace_info_wp(" QSPI_1_IOSET_1");
		break;
	case BCW_QSPI_1_IOSET_2:
		trace_info_wp(" QSPI_1_IOSET_2*");
		break;
	case BCW_QSPI_1_IOSET_3:
		trace_info_wp(" QSPI_1_IOSET_3*");
		break;
	}

	switch (value & BCW_SPI_0_Msk) {
	case BCW_SPI_0_IOSET_1:
		trace_info_wp(" SPI_0_IOSET_1");
		break;
	case BCW_SPI_0_IOSET_2:
		trace_info_wp(" SPI_0_IOSET_2*");
		break;
	}

	switch (value & BCW_SPI_1_Msk) {
	case BCW_SPI_1_IOSET_1:
		trace_info_wp(" SPI_1_IOSET_1");
		break;
	case BCW_SPI_1_IOSET_2:
		trace_info_wp(" SPI_1_IOSET_2*");
		break;
	case BCW_SPI_1_IOSET_3:
		trace_info_wp(" SPI_1_IOSET_3*");
		break;
	}

	switch (value & BCW_NFC_Msk) {
	case BCW_NFC_IOSET_1:
		trace_info_wp(" NFC_IOSET_1");
		break;
	case BCW_NFC_IOSET_2:
		trace_info_wp(" NFC_IOSET_2*");
		break;
	}

	if ((value & BCW_SDMMC_0_DISABLED) == 0)
		trace_info_wp(" SDMMC_0");

	if ((value & BCW_SDMMC_1_DISABLED) == 0)
		trace_info_wp(" SDMMC_1");

	switch (value & BCW_UART_CONSOLE_Msk) {
	case BCW_UART_CONSOLE_UART1_IOSET_1:
		trace_info_wp(" CONSOLE_UART1_IOSET_1");
		break;
	case BCW_UART_CONSOLE_UART0_IOSET_1:
		trace_info_wp(" CONSOLE_UART0_IOSET_1*");
		break;
	case BCW_UART_CONSOLE_UART1_IOSET_2:
		trace_info_wp(" CONSOLE_UART1_IOSET_2*");
		break;
	case BCW_UART_CONSOLE_UART2_IOSET_1:
		trace_info_wp(" CONSOLE_UART2_IOSET_1*");
		break;
	case BCW_UART_CONSOLE_UART2_IOSET_2:
		trace_info_wp(" CONSOLE_UART2_IOSET_2*");
		break;
	case BCW_UART_CONSOLE_UART2_IOSET_3:
		trace_info_wp(" CONSOLE_UART2_IOSET_3*");
		break;
	case BCW_UART_CONSOLE_UART3_IOSET_1:
		trace_info_wp(" CONSOLE_UART3_IOSET_1*");
		break;
	case BCW_UART_CONSOLE_UART3_IOSET_2:
		trace_info_wp(" CONSOLE_UART3_IOSET_2*");
		break;
	case BCW_UART_CONSOLE_UART3_IOSET_3:
		trace_info_wp(" CONSOLE_UART3_IOSET_3*");
		break;
	case BCW_UART_CONSOLE_UART4_IOSET_1:
		trace_info_wp(" CONSOLE_UART4_IOSET_1*");
		break;
	}

	switch (value & BCW_JTAG_IO_SET_Msk) {
	case BCW_JTAG_IOSET_1:
		trace_info_wp(" JTAG_IOSET_1");
		break;
	case BCW_JTAG_IOSET_2:
		trace_info_wp(" JTAG_IOSET_2*");
		break;
	case BCW_JTAG_IOSET_3:
		trace_info_wp(" JTAG_IOSET_3*");
		break;
	case BCW_JTAG_IOSET_4:
		trace_info_wp(" JTAG_IOSET_4*");
		break;
	}

	if (value & BCW_EXT_MEM_BOOT_ENABLE)
		trace_info_wp(" EXT_MEM_BOOT*");

	if (value & BCW_QSPI_XIP_MODE)
		trace_info_wp(" QSPI_XIP_MODE*");

	if (value & BCW_DISABLE_BSCR)
		trace_info_wp(" DISABLE_BSCR*");

	if (value & BCW_DISABLE_MONITOR)
		trace_info_wp(" DISABLE_MONITOR*");

	if (value & BCW_SECURE_MODE)
		trace_info_wp(" SECURE_MODE*");
}

static void print_all_boot_config(void)
{
	trace_info_wp("BSCR:          ");
	print_bscr();
	trace_info_wp("\r\n");

	trace_info_wp("BUREG[0]:      ");
	print_boot_config(SECURAM->BUREG_256b[0]);
	trace_info_wp("\r\n");

	trace_info_wp("BUREG[1]:      ");
	print_boot_config(SECURAM->BUREG_256b[1]);
	trace_info_wp("\r\n");

	trace_info_wp("BUREG[2]:      ");
	print_boot_config(SECURAM->BUREG_256b[2]);
	trace_info_wp("\r\n");

	trace_info_wp("BUREG[3]:      ");
	print_boot_config(SECURAM->BUREG_256b[3]);
	trace_info_wp("\r\n");

	trace_info_wp("Boot Cfg Fuse: ");
	print_boot_config(sfc_read(FUSE_BOOTCONFIG_WORD_POS));
	trace_info_wp("\r\n");
}

static uint32_t handle_cmd_initialize(uint32_t cmd, uint32_t *mailbox)
{
	union initialize_mailbox *mbx = (union initialize_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_INITIALIZE);

	applet_set_init_params(mbx->in.comm_type, mbx->in.trace_level);

	trace_info_wp("\r\nApplet 'BootConfig' from "
			"softpack " SOFTPACK_VERSION ".\r\n");

	mbx->out.buf_addr = 0;
	mbx->out.buf_size = 0;
	mbx->out.page_size = 0;
	mbx->out.mem_size = 0;
	mbx->out.erase_support = 0;

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_read_bootcfg(uint32_t cmd, uint32_t *mailbox)
{
	union read_bootcfg_mailbox *mbx = (union read_bootcfg_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_READ_BOOTCFG);

	mbx->out.boot_fuse = sfc_read(FUSE_BOOTCONFIG_WORD_POS);
	mbx->out.bsc_cr = BSC->BSC_CR;
	mbx->out.bureg[0] = SECURAM->BUREG_256b[0];
	mbx->out.bureg[1] = SECURAM->BUREG_256b[1];
	mbx->out.bureg[2] = SECURAM->BUREG_256b[2];
	mbx->out.bureg[3] = SECURAM->BUREG_256b[3];

	trace_info_wp("----- Reading Boot Configuration -----\r\n");
	print_all_boot_config();

	return APPLET_SUCCESS;
}

static uint32_t handle_cmd_write_bootcfg(uint32_t cmd, uint32_t *mailbox)
{
	union write_bootcfg_mailbox *mbx = (union write_bootcfg_mailbox*)mailbox;

	assert(cmd == APPLET_CMD_WRITE_BOOTCFG);

	if ((mbx->in.flags & WRITE_BOOTCFG_FLAG_KEYMASK) !=
	    WRITE_BOOTCFG_FLAG_KEY) {
		trace_error_wp("Invalid key in write boot config flags!\r\n");
		return APPLET_FAIL;
	}

	if (mbx->in.flags & WRITE_BOOTCFG_FLAG_FUSE) {
		trace_info_wp("Writing 0x%08x to bootcfg fuse (fuse #%d)\r\n",
		              (unsigned)mbx->in.boot_fuse,
			      FUSE_BOOTCONFIG_WORD_POS);
		sfc_enable();
		sfc_write(FUSE_BOOTCONFIG_WORD_POS, mbx->in.boot_fuse);
		sfc_disable();
	}

	if (mbx->in.flags & WRITE_BOOTCFG_FLAG_BSCR) {
		trace_info_wp("Writing 0x%08x to BSC CR\r\n",
		              (unsigned)mbx->in.bsc_cr);
		BSC->BSC_CR = mbx->in.bsc_cr;
	}

	if (mbx->in.flags & WRITE_BOOTCFG_FLAG_BUREG0) {
		trace_info_wp("Writing 0x%08x to BUREG[0]\r\n",
		              (unsigned)mbx->in.bureg[0]);
		SECURAM->BUREG_256b[0] = mbx->in.bureg[0];
	}

	if (mbx->in.flags & WRITE_BOOTCFG_FLAG_BUREG1) {
		trace_info_wp("Writing 0x%08x to BUREG[1]\r\n",
		              (unsigned)mbx->in.bureg[1]);
		SECURAM->BUREG_256b[1] = mbx->in.bureg[1];
	}

	if (mbx->in.flags & WRITE_BOOTCFG_FLAG_BUREG2) {
		trace_info_wp("Writing 0x%08x to BUREG[2]\r\n",
		              (unsigned)mbx->in.bureg[2]);
		SECURAM->BUREG_256b[2] = mbx->in.bureg[2];
	}

	if (mbx->in.flags & WRITE_BOOTCFG_FLAG_BUREG3) {
		trace_info_wp("Writing 0x%08x to BUREG[3]\r\n",
		              (unsigned)mbx->in.bureg[3]);
		SECURAM->BUREG_256b[3] = mbx->in.bureg[3];
	}

	trace_info_wp("----- Boot Configuration after modification -----\r\n");
	print_all_boot_config();

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
