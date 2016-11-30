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
 * \page dmac DMAC Example
 *
 * \section Purpose
 *
 * The DMAC example will help new users get familiar with Atmel's
 * SAMA5D3X/SAM9XX5 family of microcontrollers. This basic application shows the
 * DMAC transfer with single/multiple Microblock and LLI transfer.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D3-XPLAINED, SAMA534-EK and SAM9XX5-EK.
 *
 * \section Description
 *
 * The demonstration program evaluates the DMAC data transfer. The available
 * types of DMAC multiple buffers transfer can be switched by the corresponding
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
 *      -- DMAC Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# Press one of the keys listed in the menu to perform the corresponding action.
 *
 * \section References
 * - dma_dmac/main.c
 * - dmac.h
 * - dmacd.h
 */

/** \file
 *
 *  This file contains all the specific code for the DMAC example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"

#include "misc/cache.h"
#include "dma/dmacd.h"
#include "misc/console.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "compiler.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

#define DMA_SINGLE 1
#define DMA_MULTI  2
#define DMA_LL     3

/** Maximum size of Linked List in this example */
#define MAX_LL_SIZE 2

/** Microblock length for single transfer */
#define MICROBLOCK_LEN 8

/** Buffer length */
#define BUFFER_LEN 128

/** Polling or interrupt mode */
#undef USE_POLLING

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** DMA Linked List */
CACHE_ALIGNED static struct _dma_desc dma_descs[MAX_LL_SIZE];

/** DMA channel */
static struct _dmacd_channel *dmacd_channel;

/** Source buffer */
CACHE_ALIGNED static uint8_t src_buf[BUFFER_LEN];

/** Destination buffer */
CACHE_ALIGNED static uint8_t dest_buf[BUFFER_LEN];

/* Current Programming DMA mode for Multiple Buffer Transfers */
static uint8_t dma_mode = 0;
static uint8_t dma_data_width = 0;
static uint8_t dma_src_addr_mode = 0;
static uint8_t dma_dest_addr_mode = 0;

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
			printf("\r\n");
	}
	printf("\r\n");
}

/**
 * \brief Display main menu.
 */
static void _display_menu(void)
{
	uint8_t c[4];

	printf("\r\nDMAC Menu :\r\n\r\n");
	printf("|====== Channel Configuration ================================|\r\n");
	printf("| Press [a|b|c|d] to set Date width                           |\r\n");
	c[0] = (dma_data_width == 0) ? 'X' : ' ';
	c[1] = (dma_data_width == 1) ? 'X' : ' ';
	c[2] = (dma_data_width == 2) ? 'X' : ' ';
#ifdef DMAC_CTRLA_DST_WIDTH_DWORD
	c[3] = (dma_data_width == 3) ? 'X' : ' ';
	printf("|   a: BYTE[%c] b: HALFWORD[%c] c: WORD[%c] d: DWORD[%c]          |\r\n",
	       c[0], c[1], c[2], c[3]);
#else
	printf("|   a: BYTE[%c] b: HALFWORD[%c] c: WORD[%c]                       |\r\n",
	       c[0], c[1], c[2]);
#endif
	printf("| Press [0|1] to set Source Addressing Mode                   |\r\n");
	c[0] = (dma_src_addr_mode == 0) ? 'X' : ' ';
	c[1] = (dma_src_addr_mode == 1) ? 'X' : ' ';
	printf("|   0: FIXED[%c] 1: INCR[%c]                                    |\r\n",
	       c[0], c[1]);
	printf("| Press [2|3] to set Destination Addressing Mode              |\r\n");
	c[0] = (dma_dest_addr_mode == 0) ? 'X' : ' ';
	c[1] = (dma_dest_addr_mode == 1) ? 'X' : ' ';
	printf("|   2: FIXED[%c] 3: INCR[%c]                                    |\r\n",
	       c[0], c[1]);
	printf("|=============================================================|\r\n");
	printf("\r\n");
	printf("- DMAC transfer type\r\n");
	printf("    S: Single Block with Single Microblock transfer\r\n");
	printf("    M: Single Block with Multiple Microblock transfer\r\n");
	printf("    L: Linked List Master transfer\r\n");
	printf("- H: Display this menu\r\n");
	printf("\r\n");
}

/**
 * \brief Callback function called when DMA transfer is completed
 */
static void _dma_callback(struct _dmacd_channel *channel, void *arg)
{
	trace_info("DMAC transfer complete\r\n");
	transfer_complete = true;
}

/**
 * \brief Programming DMAC for Multiple Buffer Transfers.
 */
static void _configure_transfer(void)
{
	uint8_t i;
	struct _dmacd_cfg dma_cfg;
	
	if (dma_mode != DMA_LL) {
		dma_cfg.s_decr_fetch = 1;
		dma_cfg.d_decr_fetch = 1;

		dma_cfg.trans_auto = (dma_mode == DMA_MULTI ? 1 : 0);
		dma_cfg.blocks = (dma_mode == DMA_MULTI ? 1 : 0);
		
		dma_descs[0].sa = src_buf;
		dma_descs[0].da = dest_buf;
		dma_descs[0].ctrla = dma_data_width << DMAC_CTRLA_SRC_WIDTH_Pos
						   | dma_data_width << DMAC_CTRLA_DST_WIDTH_Pos
						   | MICROBLOCK_LEN;
		dma_descs[0].ctrlb = DMAC_CTRLB_FC_MEM2MEM_DMA_FC
						   | (dma_src_addr_mode ? DMAC_CTRLB_SRC_INCR_INCREMENTING\
						     : DMAC_CTRLB_SRC_INCR_FIXED)
						   | (dma_dest_addr_mode ? DMAC_CTRLB_DST_INCR_INCREMENTING\
						     : DMAC_CTRLB_DST_INCR_FIXED)
						   | DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE 
						   | DMAC_CTRLB_DST_DSCR_FETCH_DISABLE
						   | DMAC_CTRLB_SIF_AHB_IF0
						   | DMAC_CTRLB_DIF_AHB_IF0;
		dmacd_configure_transfer(dmacd_channel, &dma_cfg, &dma_descs[0]);
	} else {
		dma_cfg.s_decr_fetch = 0;
		dma_cfg.d_decr_fetch = 0;
		for (i = 0; i < MAX_LL_SIZE; i++) {
			dma_descs[i].sa = src_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i;
			dma_descs[i].da = dest_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i;
			dma_descs[i].ctrla = dma_data_width << DMAC_CTRLA_SRC_WIDTH_Pos
							   | dma_data_width << DMAC_CTRLA_DST_WIDTH_Pos
							   | MICROBLOCK_LEN;
			dma_descs[i].ctrlb = DMAC_CTRLB_FC_MEM2MEM_DMA_FC
							   | (dma_src_addr_mode ? DMAC_CTRLB_SRC_INCR_INCREMENTING\
								: DMAC_CTRLB_SRC_INCR_FIXED)
							   | (dma_dest_addr_mode ? DMAC_CTRLB_DST_INCR_INCREMENTING\
								: DMAC_CTRLB_DST_INCR_FIXED)
							   | DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM
							   | DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM
							   | DMAC_CTRLB_SIF_AHB_IF0
							   | DMAC_CTRLB_DIF_AHB_IF0;
			dma_descs[i].desc = &dma_descs[i + 1];
		}
		dma_descs[MAX_LL_SIZE - 1].ctrlb |= DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE |
										DMAC_CTRLB_DST_DSCR_FETCH_DISABLE;
		dma_descs[MAX_LL_SIZE - 1].desc = 0;
		cache_clean_region(dma_descs, sizeof(dma_descs));
		dmacd_configure_transfer(dmacd_channel, &dma_cfg, &dma_descs[0]);
	}
	dmacd_set_callback(dmacd_channel, _dma_callback, NULL);

	printf("- Press 't' to perform DMAC transfer...\r\n");
}

/**
 * \brief Start DMAC Multiple Buffer Transfer.
 */
static uint8_t _start_dma_transfer(void)
{
	uint32_t i;

	/* Prepare source data to be transfered. */
	for (i = 0 ; i < BUFFER_LEN ; i++) {
		src_buf[i] = i;
		dest_buf[i] = 0xFF;
	}

	trace_info("The Source Buffer content before transfer\r\n");
	_dump_buffer(src_buf);

	/* Start transfer */
	transfer_complete = false;
	cache_clean_region(src_buf, BUFFER_LEN);
	cache_clean_region(dest_buf, BUFFER_LEN);
	dmacd_start_transfer(dmacd_channel);

	/* Wait for completion */
	while (!transfer_complete) {
		/* always call dmacd_poll, it will do nothing if polling mode
		 * is disabled */
		dmacd_poll();
	}

	trace_info("The Destination Buffer content after transfer\r\n");
	cache_invalidate_region(dest_buf, BUFFER_LEN);
	_dump_buffer(dest_buf);

	return 0;
}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief dmac Application entry point
 *  \return Unused (ANSI-C compatibility)
 */
extern int main(void)
{
	uint8_t key;
	bool configured = false;

	/* Output example information */
	console_example_info("DMAC Example");

	/* Allocate a DMAC channel. */
	dmacd_channel = dmacd_allocate_channel(DMACD_PERIPH_MEMORY, DMACD_PERIPH_MEMORY);
	if (!dmacd_channel) {
		trace_error("Can't allocate DMAC channel\r\n");
		return 0;
	}

	/* Display menu */
	_display_menu();
	while (1) {
		key = console_get_char();
		if (key >= 'a' && key <= 'd') {
			dma_data_width = key - 'a';
			_display_menu();
		} else if (key >= '0' && key <= '1') {
			dma_src_addr_mode = key - '0';
			_display_menu();
		} else if (key >= '2' && key <= '3') {
			dma_dest_addr_mode = key - '2';
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
		} else if (key == 'H') {
			_display_menu();
		} else if (configured && (key == 'T' || key == 't')) {
			trace_info("Start DMAC transfer\r\n");
			_start_dma_transfer();
			configured = false;
		}
	}
}
