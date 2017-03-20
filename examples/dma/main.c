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
 * \page dma DMA Example
 *
 * \section Purpose
 *
 * The DMA example will help new users get familiar with Atmel's
 * SAM9XX5/SAMA5 family of microcontrollers. This basic application shows the
 * DMA transfer with single/multiple Microblock and LLI transfer.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2-XPLAINED, SAMA5D4-EK and SAMA5D4-XULT.
 *
 * \section Description
 *
 * The demonstration program evaluates the DMA data transfer. The available
 * types of DMA multiple buffers transfer can be switched by the corresponding
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
 *      -- DMA Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# Press one of the keys listed in the menu to perform the corresponding action.
 *
 * \section References
 * - dma/main.c
  * - dma.h
 */

/** \file
 *
 *  This file contains all the specific code for the DMA example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "board.h"
#include "callback.h"
#include "chip.h"
#include "compiler.h"
#include "dma/dma.h"
#include "mm/cache.h"
#include "mutex.h"
#include "serial/console.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

#define DMA_SINGLE 1
#define DMA_SG     2

/** Maximum size of Linked List in this example */
#define MAX_SG_SIZE 2

/** Microblock length for single transfer */
#define MICROBLOCK_LEN  8

/** Buffer length */
#define BUFFER_LEN 128

/** Polling or interrupt mode */
#undef USE_POLLING

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** DMA channel */
static struct _dma_channel* dma_chan;

/** Source buffer */
CACHE_ALIGNED static uint8_t src_buf[BUFFER_LEN];
CACHE_ALIGNED static uint8_t test_buf[BUFFER_LEN];

/** Destination buffer */
CACHE_ALIGNED static uint8_t dest_buf[BUFFER_LEN];

/* Current Programming DMA mode for Multiple Buffer Transfers */
static uint8_t dma_mode = DMA_SINGLE;
static uint8_t dma_data_width = 0;
static uint8_t dma_src_addr_mode = 0;
static uint8_t dma_dest_addr_mode = 0;

/** DMA transfer completion notifier */
static mutex_t tx_done;

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

	printf("\n\rDMA Menu :\n\r\n\r");
	printf("|====== Channel Configuration ================================|\n\r");
	printf("| Press [a|b|c|d] to set Date width                           |\n\r");
	c[0] = (dma_data_width == 0) ? 'X' : ' ';
	c[1] = (dma_data_width == 1) ? 'X' : ' ';
	c[2] = (dma_data_width == 2) ? 'X' : ' ';
#ifdef DMA_DATA_WIDTH_DWORD
	c[3] = (dma_data_width == 3) ? 'X' : ' ';
	printf("|   a: BYTE[%c] b: HALFWORD[%c] c: WORD[%c] d: DWORD[%c]          |\n\r",
	       c[0], c[1], c[2], c[3]);
#else
	printf("|   a: BYTE[%c] b: HALFWORD[%c] c: WORD[%c]                      |\n\r",
	       c[0], c[1], c[2]);
#endif
	printf("| Press [0|1] to set Source Addressing Mode                   |\n\r");
	c[0] = (dma_src_addr_mode == 0) ? 'X' : ' ';
	c[1] = (dma_src_addr_mode == 1) ? 'X' : ' ';
	printf("|   0: FIXED[%c] 1: INCR[%c]                                    |\n\r",
	       c[0], c[1]);
	printf("| Press [2|3] to set Destination Addressing Mode              |\n\r");
	c[0] = (dma_dest_addr_mode == 0) ? 'X' : ' ';
	c[1] = (dma_dest_addr_mode == 1) ? 'X' : ' ';
	printf("|   2: FIXED[%c] 3: INCR[%c]                                    |\n\r",
	       c[0], c[1]);
	printf("|=============================================================|\n\r");
	printf("\n\r");
	printf("- DMA transfer type\n\r");
	printf("    S: Single Block transfer\n\r");
	printf("    L: Linked List transfer\n\r");
	printf("- H: Display this menu\n\r");
	printf("\n\r");
}

/**
 * \brief Callback function called when DMA transfer is completed
 */
static int _dma_callback(void* arg, void* arg2)
{
	struct _dma_channel* channel = (struct _dma_channel*)arg;
	dma_reset_channel(channel);
	mutex_unlock(&tx_done);
	trace_info("DMA transfer complete\n\r");

	return 0;
}

/**
 * \brief Programming DMA for Multiple Buffer Transfers.
 */
static void _configure_transfer(void)
{
	uint32_t i;
	struct _dma_cfg dma_cfg;
	struct _callback _cb;

	dma_cfg.incr_saddr = dma_src_addr_mode ? true : false;
	dma_cfg.incr_daddr = dma_dest_addr_mode ? true : false;
	dma_cfg.data_width = dma_data_width;
	dma_cfg.chunk_size = DMA_CHUNK_SIZE_1;
	dma_cfg.loop = false;

	if (dma_mode == DMA_SINGLE) {
		struct _dma_transfer_cfg cfg;

		cfg.saddr = (uint32_t *)src_buf;
		cfg.daddr = (uint32_t *)dest_buf;
		cfg.len = MICROBLOCK_LEN;

		dma_configure_transfer(dma_chan, &dma_cfg, &cfg, 1);

	} else {
		struct _dma_transfer_cfg _sg_list[MAX_SG_SIZE];

		for (i = 0; i < ARRAY_SIZE(_sg_list); i++) {
			_sg_list[i].saddr = (uint32_t *)(src_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i);
			_sg_list[i].daddr = (uint32_t *)(dest_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i);
			_sg_list[i].len = MICROBLOCK_LEN;
		}

		dma_configure_transfer(dma_chan, &dma_cfg, _sg_list, ARRAY_SIZE(_sg_list));
	}
	callback_set(&_cb, _dma_callback, dma_chan);
	dma_set_callback(dma_chan, &_cb);

	printf("- Press 't' to perform DMA transfer...\n\r");
}

/**
 * \brief Start DMA Multiple Buffer Transfer.
 */
static uint8_t _start_dma_transfer(void)
{
	uint32_t i;

	/* Prepare source data to be transfered. */
	for (i = 0 ; i < BUFFER_LEN ; i++) {
		src_buf[i] = i;
		test_buf[i] = 0xAA;
		dest_buf[i] = 0xFF;
	}

	trace_info("The Source Buffer content before transfer\n\r");
	_dump_buffer(src_buf);

	/* Start transfer */
	mutex_lock(&tx_done);

	cache_clean_region(src_buf, BUFFER_LEN);
	cache_clean_region(dest_buf, BUFFER_LEN);
	cache_clean_region(test_buf, BUFFER_LEN);

	dma_start_transfer(dma_chan);
	/* Wait for completion */
	while (mutex_is_locked(&tx_done)) {
		/* always call dma_poll, it will do nothing if polling mode
		 * is disabled */
		dma_poll();
	}

	trace_info("The Destination Buffer content after transfer\n\r");
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

	tx_done = 0;

	/* Output example information */
	console_example_info("DMA Example");

	/* Allocate a DMA channel. */
	dma_chan = dma_allocate_channel(DMA_PERIPH_MEMORY, DMA_PERIPH_MEMORY);
	if (!dma_chan) {
		trace_error("Can't allocate DMA channel\n\r");
		return 0;
	}

	/* Display menu */
	_display_menu();
	while (1) {
		key = console_get_char();
#ifdef DMA_DATA_WIDTH_DWORD
		if (key >= 'a' && key <= 'd') {
			dma_data_width = key - 'a';
			_display_menu();
#else
		if (key >= 'a' && key <= 'c') {
			dma_data_width = key - 'a';
			_display_menu();
#endif
		} else if (key >= '0' && key <= '1') {
			dma_src_addr_mode = key - '0';
			_display_menu();
		} else if (key >= '2' && key <= '3') {
			dma_dest_addr_mode = key - '2';
			_display_menu();
		} else if (key == 'S' || key == 's') {
			dma_mode = DMA_SINGLE;
			_configure_transfer();
			configured = true;
		} else if (key == 'L' || key == 'l') {
			dma_mode = DMA_SG;
			_configure_transfer();
			configured = true;
		} else if (key == 'H') {
			_display_menu();
		} else if (configured && (key == 'T' || key == 't')) {
			trace_info("Start DMA transfer\n\r");
			_start_dma_transfer();
			configured = false;
		}
	}
}
