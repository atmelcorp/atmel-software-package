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

/**
 * \page xdma XDMA Example
 *
 * \section Purpose
 *
 * The XDMA example will help new users get familiar with Atmel's
 * SAMA5D4X family of microcontrollers. This basic application shows the
 * XDMA transfer with single/multiple Microblock and LLI transfer.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D4-EK and SAMA5D4-XULT.
 *
 * \section Description
 *
 * The demonstration program evaluates the XDMA data transfer. The available
 * types of XDMA multiple buffers transfer can be switched by the corresponding
 * buttons.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a>
 *    application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>,
 *    depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *     \code
 *      -- XDMA Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# Press one of the keys listed in the menu to perform the corresponding action.
 *
 * \section References
 * - xdma/main.c
 * - xdmac.h
 * - xdmad.h
 */

/** \file
 *
 *  This file contains all the specific code for the DMA example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"

#include "misc/cache.h"
#include "peripherals/aic.h"
#include "peripherals/wdt.h"
#include "peripherals/xdmad.h"
#include "misc/console.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "compiler.h"

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

#define XDMA_SINGLE 1
#define XDMA_MULTI  2
#define XDMA_LL     3

/** Maximum size of Linked List in this example */
#define MAX_LL_SIZE 2

/** Microblock length for single transfer */
#define MICROBLOCK_LEN 16

/** Buffer length */
#define BUFFER_LEN 128

/** Polling or interrupt mode */
#undef USE_POLLING

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** DMA Linked List */
ALIGNED(8) static struct _xdmad_desc_view1 xdmad_desc[MAX_LL_SIZE];

/** DMA channel */
static struct _xdmad_channel *xdmad_channel;

/** Source buffer */
ALIGNED(L1_CACHE_BYTES) static uint8_t src_buf[BUFFER_LEN];

/** Destination buffer */
ALIGNED(L1_CACHE_BYTES) static uint8_t dest_buf[BUFFER_LEN];

/* Current Programming DMA mode for Multiple Buffer Transfers */
static uint8_t dma_mode = 0;
static uint8_t dma_data_width = 0;
static uint8_t dma_src_addr_mode = 0;
static uint8_t dma_dest_addr_mode = 0;
static uint8_t dma_memset = 0;

/** DMA transfer completion notifier */
static volatile bool transfer_complete = false;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Dump buffer to console
 */
static void _dump_buffer(uint8_t *buf)
{
	uint32_t i = 0;
	while (i < BUFFER_LEN) {
		printf("%02x ", buf[i++]);
		if (i % 16 == 0)
			printf("\n\r");
	}
	printf("\n\r");
}

/**
 * \brief Display main menu.
 */
static void _display_menu(void)
{
	uint8_t c[4];

	printf("\n\rxDMA Menu :\n\r\n\r");
	printf("|====== Channel Configuration ================================|\n\r");
	printf("| Press [a|b|c|d] to set Date width                           |\n\r");
	c[0] = (dma_data_width == 0) ? 'X' : ' ';
	c[1] = (dma_data_width == 1) ? 'X' : ' ';
	c[2] = (dma_data_width == 2) ? 'X' : ' ';
	c[3] = (dma_data_width == 3) ? 'X' : ' ';
	printf("|   a: BYTE[%c] b: HALFWORD[%c] c: WORD[%c] d: DWORD[%c]          |\n\r",
	       c[0], c[1], c[2], c[3]);
	printf("| Press [0|1|2|3] to set Source Addressing Mode               |\n\r");
	c[0] = (dma_src_addr_mode == 0) ? 'X' : ' ';
	c[1] = (dma_src_addr_mode == 1) ? 'X' : ' ';
	c[2] = (dma_src_addr_mode == 2) ? 'X' : ' ';
	c[3] = (dma_src_addr_mode == 3) ? 'X' : ' ';
	printf("|   0: FIXED[%c] 1: INCR[%c] 2: AM[%c] 3: DS_AM[%c]               |\n\r",
	       c[0], c[1], c[2], c[3]);
	printf("| Press [4|5|6|7] to set Destination Addressing Mode          |\n\r");
	c[0] = (dma_dest_addr_mode == 0) ? 'X' : ' ';
	c[1] = (dma_dest_addr_mode == 1) ? 'X' : ' ';
	c[2] = (dma_dest_addr_mode == 2) ? 'X' : ' ';
	c[3] = (dma_dest_addr_mode == 3) ? 'X' : ' ';
	printf("|   4: FIXED[%c] 5: INCR[%c] 6: AM[%c] 7: DS_AM[%c]               |\n\r",
	       c[0], c[1], c[2], c[3]);
	printf("| Press [8|9| to set MEMSET Mode                              |\n\r");
	c[0] = (dma_memset == 0) ? 'X' : ' ';
	c[1] = (dma_memset == 1) ? 'X' : ' ';
	printf("|   8: NORMAL Mode[%c] 9: HW_MODE[%c]                           |\n\r",
	       c[0], c[1]);
	printf("|=============================================================|\n\r");
	printf("\n\r");
	printf("- xDMA transfer type\n\r");
	printf("    S: Single Block with Single Microblock transfer\n\r");
	printf("    M: Single Block with Multiple Microblock transfer\n\r");
	printf("    L: Linked List Master transfer\n\r");
	printf("- h: Display this menu\n\r");
	printf("\n\r");
}

/**
 * \brief Callback function called when DMA transfer is completed
 */
static void _dma_callback(struct _xdmad_channel *channel, void *arg)
{
	printf("-I- DMA transfer complete\n\r");
	transfer_complete = true;
}

/**
 * \brief Programming DMAC for Multiple Buffer Transfers.
 */
static void _configure_transfer(void)
{
	struct _xdmad_cfg xdmad_cfg;

	if (dma_mode != XDMA_LL) {
		xdmad_cfg.ublock_size = MICROBLOCK_LEN;
		xdmad_cfg.src_addr = src_buf;
		xdmad_cfg.dest_addr = dest_buf;
		xdmad_cfg.cfg.uint32_value = XDMAC_CC_TYPE_MEM_TRAN |
		                    XDMA_GET_CC_MEMSET(dma_memset) |
		                    XDMAC_CC_MEMSET_NORMAL_MODE |
		                    XDMAC_CC_CSIZE_CHK_1 |
		                    XDMA_GET_DATASIZE(dma_data_width) |
		                    XDMAC_CC_SIF_AHB_IF0 |
		                    XDMAC_CC_DIF_AHB_IF0 |
		                    XDMA_GET_CC_SAM(dma_src_addr_mode) |
		                    XDMA_GET_CC_DAM(dma_dest_addr_mode);
		xdmad_cfg.block_size = (dma_mode == XDMA_SINGLE) ? 0 : 1;
		xdmad_cfg.data_stride = 0;
		xdmad_cfg.src_ublock_stride = 0;
		xdmad_cfg.dest_ublock_stride = 0;

		xdmad_configure_transfer(xdmad_channel, &xdmad_cfg, 0, 0);

		printf("- Microblock length: %u\n\r",
				(unsigned int)xdmad_cfg.ublock_size);
		printf("- Block length: %u\n\r",
				(unsigned int)xdmad_cfg.block_size);
		printf("- Data Stride/Pattern: %u\n\r",
				(unsigned int)xdmad_cfg.data_stride);
		printf("- Source Microblock Stride: %u\n\r",
				(unsigned int)xdmad_cfg.src_ublock_stride);
		printf("- Destination  Microblock Stride: %u\n\r",
				(unsigned int)xdmad_cfg.dest_ublock_stride);
	} else {
		uint32_t i, desc_cntrl;

		xdmad_cfg.cfg.uint32_value = XDMAC_CC_TYPE_MEM_TRAN |
		                    XDMAC_CC_MBSIZE_SINGLE |
		                    XDMA_GET_CC_MEMSET(dma_memset) |
		                    XDMAC_CC_CSIZE_CHK_1 |
		                    XDMA_GET_DATASIZE(dma_data_width) |
		                    XDMAC_CC_SIF_AHB_IF0 |
		                    XDMAC_CC_DIF_AHB_IF0 |
		                    XDMA_GET_CC_SAM(dma_src_addr_mode) |
		                    XDMA_GET_CC_DAM(dma_dest_addr_mode);
		xdmad_cfg.block_size = 0;

		for (i = 0; i < MAX_LL_SIZE; i++) {
			xdmad_desc[i].ublock_size = XDMA_UBC_NVIEW_NDV1 |
			                        MICROBLOCK_LEN;
			xdmad_desc[i].src_addr = src_buf + i;
			xdmad_desc[i].dest_addr = dest_buf + i;
			xdmad_desc[i].next_desc = &xdmad_desc[i + 1];
			if (i == 0) {
				/* first list element */
				xdmad_desc[i].ublock_size |= XDMA_UBC_NSEN_UPDATED |
			                                 XDMA_UBC_NDEN_UPDATED;
			} else if (i == (MAX_LL_SIZE - 1)) {
				/* last list element */
				xdmad_desc[i].ublock_size |= XDMA_UBC_NDE_FETCH_EN;
				xdmad_desc[i].next_desc = 0;
			}
		}

		desc_cntrl = XDMAC_CNDC_NDVIEW_NDV1 |
		    XDMAC_CNDC_NDE_DSCR_FETCH_EN |
		    XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED |
		    XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED;
		cache_clean_region(xdmad_desc, sizeof(xdmad_desc));
		xdmad_configure_transfer(xdmad_channel, &xdmad_cfg, desc_cntrl,
				xdmad_desc);
	}

	xdmad_set_callback(xdmad_channel, _dma_callback, NULL);

	printf("- Press 't' to perform xDMA transfer...\n\r");
}

/**
 * \brief Start DMAC Multiple Buffer Transfer.
 */
static uint8_t _start_dma_transfer(void)
{
	uint32_t i;

	/* Prepare source data to be transfered. */
	cache_invalidate_region(src_buf, BUFFER_LEN);
	cache_invalidate_region(dest_buf, BUFFER_LEN);
	for (i = 0; i < BUFFER_LEN; i++) {
		src_buf[i] = i;
		dest_buf[i] = 0xFF;
	}

	printf("-I- The Source Buffer content before transfer\n\r");
	_dump_buffer(src_buf);

	/* Start transfer */
	transfer_complete = false;
	cache_clean_region(src_buf, BUFFER_LEN);
	cache_clean_region(dest_buf, BUFFER_LEN);
	xdmad_start_transfer(xdmad_channel);

	/* Wait for completion */
	while (!transfer_complete) {
		/* always call xdmad_poll, it will do nothing if polling mode
		 * is disabled */
		xdmad_poll();
	}

	printf("-I- The Destination Buffer content after transfer\n\r");
	cache_invalidate_region(dest_buf, BUFFER_LEN);
	_dump_buffer(dest_buf);

	return 0;
}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief dma Application entry point
 *  \return Unused (ANSI-C compatibility)
 */
extern int main(void)
{
	uint8_t key;
	bool configured = false;

	/* Disable watchdog */
	wdt_disable();

	/* Configure console */
	board_cfg_console(0);

	/* Output example information */
	printf("-- XDMA Example " SOFTPACK_VERSION " --\n\r");
	printf("-- " BOARD_NAME "\n\r");
	printf("-- Compiled: " __DATE__ " " __TIME__ " --\n\r");

#ifdef USE_POLLING
	/* Initialize XDMA driver instance in polling mode */
	xdmad_initialize(true);
	printf("\n\rDMA using polling mode\n\r");
#else
	/* Initialize XDMA driver instance in interrupt mode */
	xdmad_initialize(false);
	printf("\n\rDMA using interrupt mode\n\r");
#endif

	/* Allocate a XDMA channel. */
	xdmad_channel = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, XDMAD_PERIPH_MEMORY);
	if (!xdmad_channel) {
		printf("-E- Can't allocate XDMA channel\n\r");
		return 0;
	}
	xdmad_prepare_channel(xdmad_channel);

	/* Display menu */
	_display_menu();
	while (1) {
		key = console_get_char();
		if (key >= 'a' && key <= 'd') {
			dma_data_width = key - 'a';
			_display_menu();
		} else if (key >= '0' && key <= '3') {
			dma_src_addr_mode = key - '0';
			_display_menu();
		} else if (key >= '4' && key <= '7') {
			dma_dest_addr_mode = key - '4';
			_display_menu();
		} else if (key >= '8' && key <= '9') {
			dma_memset = key - '8';
			_display_menu();
		} else if (key == 'S' || key == 's') {
			dma_mode = 1;
			_configure_transfer();
			configured = true;
		} else if (key == 'M' || key == 'm') {
			dma_mode = 2;
			_configure_transfer();
			configured = true;
		} else if (key == 'L' || key == 'l') {
			dma_mode = 3;
			_configure_transfer();
			configured = true;
		} else if (key == 'H' || key == 'h') {
			_display_menu();
		} else if (configured && (key == 'T' || key == 't')) {
			printf("-I- Start XDMA transfer\n\r");
			_start_dma_transfer();
			configured = false;
		}
	}
}
