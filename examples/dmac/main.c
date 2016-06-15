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
 * SAMA5D3X family of microcontrollers. This basic application shows the
 * DMA transfer with single/multiple buffer transfer.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D3-EK, SAMA5D3-XULT.
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
 * - dmac.h
 * - dmacd.h
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
#include "peripherals/dmacd.h"
#include "misc/console.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "compiler.h"

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/
#define TEST_ROW                    11

#define NUM_REPEAT                  2

/** Maximum size of Linked List in this example */
#define MAX_LL_SIZE 2

/** Transfer size relates to the number of transfers to be performed.*/
#define BLOCK_TRANSFER_SIZE        2

/** Buffer length */
#define BUFFER_LEN 64

#define SINGLE_BUFFER_TRANSFER     0

/** Polling or interrupt mode */
#undef USE_POLLING

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** DMA channel */
static struct _dmacd_channel *dmacd_channel;

/** Source buffer */
CACHE_ALIGNED static uint8_t src_buf[BUFFER_LEN];

/** Destination buffer */
CACHE_ALIGNED static uint8_t dest_buf[BUFFER_LEN];

/** DMA transfer completion notifier */
static volatile bool transfer_complete = false;

CACHE_ALIGNED struct _dma_desc dma_descs[MAX_LL_SIZE];

static uint8_t dma_transfer_type;

static volatile uint8_t repeat_count;
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
	printf("Menu :\n\r");
	printf("------\n\r");
	printf( "- 1-9, A, B: Programming DMAC for Multiple Buffer Transfers\n\r");
	printf( "    1: Single Buffer or Last buffer of a multiple buffer transfer \n\r" );
	printf( "    2: Multi Buffer transfer with contiguous DADDR\n\r" );
	printf( "    3: Multi Buffer transfer with contiguous SADDR\n\r" );
	printf( "    4: Multi Buffer transfer with LLI support \n\r" );
	printf( "    5: Multi Buffer transfer with DADDR reloaded\n\r" );
	printf( "    6: Multi Buffer transfer with SADDR reloaded\n\r" );
	printf( "    7: Multi Buffer transfer with BTSIZE reloaded and contiguous DADDR \n\r" );
	printf( "    8: Multi Buffer transfer with BTSIZE reloaded and contiguous SADDR\n\r" );
	printf( "    9: Automatic mode channel is stalling BTsize is reloaded\n\r" );
	printf( "    A: Automatic mode BTSIZE, SADDR and DADDR reloaded\n\r" );
	printf( "    B: Automatic mode BTSIZE, SADDR reloaded and DADDR contiguous\n\r" );
	printf( "- h: Display this menu\n\r");
	printf("\n\r");
}

static void _dump_dam_info(struct _dmacd_cfg * dma_cfg)
{
	if (dma_transfer_type == SINGLE_BUFFER_TRANSFER)
		printf("-I- DMA single buffer transfer.\n\r");
	else
		printf("-I- DMA multiple buffer transfer.\n\r");
	if (dma_cfg->s_decr_fetch) {
		printf("-I- the starting source address is stored in DMAC_SADDRx register");
		if (dma_transfer_type != SINGLE_BUFFER_TRANSFER) {
			if (dma_cfg->sa_rep)
				printf(", the next source address are reloaded from DMAC_SADDRx register.\n\r");
			else
				printf(", the next source address are contiguous.\n\r");
		} else
			printf("\n\r");
	} else {
		printf("-I- the source address are stored in DMA Linker list\n\r");
	}
	if (dma_cfg->d_decr_fetch) {
		printf("-I- the starting destination address is stored in DMAC_DADDRx register");
		if (dma_transfer_type != SINGLE_BUFFER_TRANSFER) {
			if (dma_cfg->da_rep)
				printf(", the next destination address are reloaded from DMAC_DADDRx register.\n\r");
			else
				printf(", the next destination address are contiguous.\n\r");
		}else
			printf("\n\r");
	} else {
		printf("-I- the destination address are stored in DMA Linker list\n\r");
	}
	if (!(dma_cfg->s_decr_fetch) || !(dma_cfg->d_decr_fetch)) {
		printf("-I- the first buffer trannsfer size are stored in DMA Linker list");
	} else {
		printf("-I- the first buffer trannsfer size are stored in DMAC_CTRLAx register\n\r");
	}
	if (dma_cfg->trans_auto)
		printf(",the next buffer trannsfer size are reloaded from previous value.\n\r");
	else
		printf(",the next buffer trannsfer size are fetched from DMA Linker list.\n\r");
	if (dma_cfg->trans_auto) {
		if ((dma_cfg->s_decr_fetch) && (dma_cfg->d_decr_fetch)) {
			printf("-I- Automatic mode, channel will stalling for each transfer.\n\r");
		}
	}
}

/**
 * \brief Callback function called when DMA transfer is completed
 */
static void _dma_callback(struct _dmacd_channel *channel, void *arg)
{
	printf("-I- DMA transfer complete\n\r");
	transfer_complete = true;
}

/**
 * \brief Programming DMAC for Multiple Buffer Transfers.
 */
static void _configure_transfer(void)
{
	uint8_t i;
	struct _dmacd_cfg dma_cfg;

	repeat_count = 0;

	switch (dma_transfer_type) {
	case 0: case 2: case 5: case 7: case 8: case 9: case 10: 
		dma_cfg.s_decr_fetch = 1;
		break;
	default: 
		dma_cfg.s_decr_fetch = 0;
		break;
	}
	switch (dma_transfer_type) {
	case 0: case 1: case 4: case 6: case 8: case 9: case 10: 
		dma_cfg.d_decr_fetch = 1;
		break;
	default: 
		dma_cfg.d_decr_fetch = 0;
		break;
	}
	switch (dma_transfer_type) {
	case 5: case 9: case 10:
		dma_cfg.sa_rep = 1;
		break;
	default: 
		dma_cfg.sa_rep = 0;
		break;
	}
	switch (dma_transfer_type) {
	case 4: case 9:
		dma_cfg.da_rep = 1;
		break;
	default: 
		dma_cfg.da_rep = 0;
		break;
	}

	switch (dma_transfer_type) {
	case 6: case 7: case 8: case 9: case 10:
		dma_cfg.trans_auto = 1;
		dma_cfg.blocks = NUM_REPEAT;
		break;
	default: 
		dma_cfg.trans_auto = 0;
		dma_cfg.blocks = 0;
		break;
	}

	dma_cfg.cfg = ((dma_cfg.sa_rep) ? DMAC_CFG_SRC_REP_RELOAD_ADDR : 0 ) |
				  ((dma_cfg.da_rep) ? DMAC_CFG_DST_REP_RELOAD_ADDR : 0);

	/* Set up the chain of linked list items in memory. Write the control information in the
	LLI.DMAC_CTRLAx and DMAC_CTRLBx registers location of the buffer descriptor for each LLI
	in memory for channel x. If the buffer address is REP or CONT, although the linker list fetched,
	is not used. */
	for (i = 0; i < MAX_LL_SIZE; i++) {
		dma_descs[i].sa = src_buf + i * BLOCK_TRANSFER_SIZE * sizeof(uint32_t);
		dma_descs[i].da = dest_buf + i* BLOCK_TRANSFER_SIZE * sizeof(uint32_t);
		dma_descs[i].ctrla = DMAC_CTRLA_SRC_WIDTH_WORD |
							 DMAC_CTRLA_DST_WIDTH_WORD |
							 BLOCK_TRANSFER_SIZE;

		dma_descs[i].ctrlb = DMAC_CTRLB_FC_MEM2MEM_DMA_FC |
						 DMAC_CTRLB_SRC_INCR_INCREMENTING |
						 DMAC_CTRLB_DST_INCR_INCREMENTING |
						 (dma_cfg.s_decr_fetch ?
						     DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE : DMAC_CTRLB_SRC_DSCR_FETCH_FROM_MEM) |
						 (dma_cfg.d_decr_fetch ?
						     DMAC_CTRLB_DST_DSCR_FETCH_DISABLE : DMAC_CTRLB_DST_DSCR_FETCH_FROM_MEM) |
						 DMAC_CTRLB_SIF_AHB_IF0 |
						 DMAC_CTRLB_DIF_AHB_IF0 |
						 (dma_cfg.trans_auto ? DMAC_CTRLB_AUTO : 0);
		dma_descs[i].desc = &dma_descs[i + 1];
	}
	dma_descs[MAX_LL_SIZE - 1].ctrlb |= DMAC_CTRLB_SRC_DSCR_FETCH_DISABLE |
										DMAC_CTRLB_DST_DSCR_FETCH_DISABLE;
	dma_descs[MAX_LL_SIZE - 1].ctrlb &= ~DMAC_CTRLB_AUTO;
	dma_descs[MAX_LL_SIZE - 1].desc = 0;
	cache_clean_region(dma_descs, sizeof(dma_descs));
	dmacd_configure_transfer(dmacd_channel, &dma_cfg, &dma_descs[0]);
	_dump_dam_info(&dma_cfg);
	printf("- Press 't' to perform DMA transfer...\n\r");
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

	printf("-I- The Source Buffer content before transfer\n\r");
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

	/* Output example information */
	console_example_info("DMA Example");

	/* Allocate a DMA channel. */
	dmacd_channel = dmacd_allocate_channel(DMACD_PERIPH_MEMORY, DMACD_PERIPH_MEMORY);
	if (!dmacd_channel) {
		printf("-E- Can't allocate DMA channel\n\r");
		return 0;
	}

	dmacd_set_callback(dmacd_channel, _dma_callback, NULL);

	_display_menu();
	while (1) {
		key = console_get_char();
		if (key >= '1' && key <= '9') {
			dma_transfer_type = key -'1';
			_configure_transfer();
		}
		if (key == 'a' || key == 'A') {
			dma_transfer_type = 9;
			_configure_transfer();
		}
		if (key == 'b' || key == 'B') {
			dma_transfer_type = 10;
			_configure_transfer();
		}
		if (key == 'h' || key == 'H') {
			_display_menu();
		}
		if (key == 't' || key == 'T') {
			_start_dma_transfer();
		}
	}
}
