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
 * \page xdmac DMA_XDMAC Example
 *
 * \section Purpose
 *
 * The XDMAC example will help new users get familiar with Atmel's
 * SAMA5D4X family of microcontrollers. This basic application shows the
 * XDMAC transfer with single/multiple Microblock and LLI transfer.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D2-XPLAINED, SAMA5D4-EK and SAMA5D4-XULT.
 *
 * \section Description
 *
 * The demonstration program evaluates the XDMAC data transfer. The available
 * types of XDMAC multiple buffers transfer can be switched by the corresponding
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
 *      -- XDMAC Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
 * -# Press one of the keys listed in the menu to perform the corresponding action.
 *
 * \section References
 * - dma_xdmac/main.c
 * - xdmac.h
 * - xdmacd.h
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
#include "peripherals/xdmacd.h"
#include "misc/console.h"

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "compiler.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/

#define XDMA_SINGLE 1
#define XDMA_MULTI  2
#define XDMA_LL     3

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
CACHE_ALIGNED static struct _xdmacd_desc_view0 xdmacd_desc_view0[MAX_LL_SIZE];
CACHE_ALIGNED static struct _xdmacd_desc_view1 xdmacd_desc_view1[MAX_LL_SIZE];
CACHE_ALIGNED static struct _xdmacd_desc_view2 xdmacd_desc_view2[MAX_LL_SIZE];
CACHE_ALIGNED static struct _xdmacd_desc_view3 xdmacd_desc_view3[MAX_LL_SIZE];

/** DMA channel */
static struct _xdmacd_channel *xdmacd_channel;

/** Source buffer */
CACHE_ALIGNED static uint8_t src_buf[BUFFER_LEN];

/** Destination buffer */
CACHE_ALIGNED static uint8_t dest_buf[BUFFER_LEN];

/* Current Programming DMA mode for Multiple Buffer Transfers */
static uint8_t dma_mode = 0;
static uint8_t dma_data_width = 0;
static uint8_t dma_src_addr_mode = 0;
static uint8_t dma_dest_addr_mode = 0;
static uint8_t dma_memset = 0;
static uint8_t dma_view = 1;

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

	printf("\r\nxDMA Menu :\r\n\r\n");
	printf("|====== Channel Configuration ================================|\r\n");
	printf("| Press [a|b|c|d] to set Date width                           |\r\n");
	c[0] = (dma_data_width == 0) ? 'X' : ' ';
	c[1] = (dma_data_width == 1) ? 'X' : ' ';
	c[2] = (dma_data_width == 2) ? 'X' : ' ';
	c[3] = (dma_data_width == 3) ? 'X' : ' ';
	printf("|   a: BYTE[%c] b: HALFWORD[%c] c: WORD[%c] d: DWORD[%c]          |\r\n",
	       c[0], c[1], c[2], c[3]);
	printf("| Press [0|1|2|3] to set Source Addressing Mode               |\r\n");
	c[0] = (dma_src_addr_mode == 0) ? 'X' : ' ';
	c[1] = (dma_src_addr_mode == 1) ? 'X' : ' ';
	c[2] = (dma_src_addr_mode == 2) ? 'X' : ' ';
	c[3] = (dma_src_addr_mode == 3) ? 'X' : ' ';
	printf("|   0: FIXED[%c] 1: INCR[%c] 2: AM[%c] 3: DS_AM[%c]               |\r\n",
	       c[0], c[1], c[2], c[3]);
	printf("| Press [4|5|6|7] to set Destination Addressing Mode          |\r\n");
	c[0] = (dma_dest_addr_mode == 0) ? 'X' : ' ';
	c[1] = (dma_dest_addr_mode == 1) ? 'X' : ' ';
	c[2] = (dma_dest_addr_mode == 2) ? 'X' : ' ';
	c[3] = (dma_dest_addr_mode == 3) ? 'X' : ' ';
	printf("|   4: FIXED[%c] 5: INCR[%c] 6: AM[%c] 7: DS_AM[%c]               |\r\n",
	       c[0], c[1], c[2], c[3]);
	printf("| Press [8|9| to set MEMSET Mode                              |\r\n");
	c[0] = (dma_memset == 0) ? 'X' : ' ';
	c[1] = (dma_memset == 1) ? 'X' : ' ';
	printf("|   8: NORMAL Mode[%c] 9: HW_MODE[%c]                           |\r\n",
	       c[0], c[1]);
	printf("| Press [e|f|g|i] to set list view                            |\r\n");
	c[0] = (dma_view == 0) ? 'X' : ' ';
	c[1] = (dma_view == 1) ? 'X' : ' ';
	c[2] = (dma_view == 2) ? 'X' : ' ';
	c[3] = (dma_view == 3) ? 'X' : ' ';
	printf("|   e: view0[%c] f: view1[%c] g: view2[%c] h: view3[%c]           |\r\n",
	       c[0], c[1], c[2], c[3]);
	printf("|=============================================================|\r\n");
	printf("\r\n");
	printf("- xDMA transfer type\r\n");
	printf("    S: Single Block with Single Microblock transfer\r\n");
	printf("    M: Single Block with Multiple Microblock transfer\r\n");
	printf("    L: Linked List Master transfer\r\n");
	printf("- H: Display this menu\r\n");
	printf("\r\n");
}

/**
 * \brief Callback function called when DMA transfer is completed
 */
static void _dma_callback(struct _xdmacd_channel *channel, void *arg)
{
	trace_info("DMA transfer complete\r\n");
	transfer_complete = true;
}

/**
 * \brief Configure View0-View4 for linked list
 */
static uint32_t _configure_view(void **xdmacd_view, uint32_t *desc_cntrl,
		struct _xdmacd_cfg *xdmacd_cfg)
{
	uint32_t desc_size = 0;
	uint32_t i = 0;

	*desc_cntrl = XDMAC_CNDC_NDE_DSCR_FETCH_EN
	            | XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED
	            | XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED;

	switch(dma_view) {
	case 0:
		for (i = 0 ; i < MAX_LL_SIZE; i++) {
			xdmacd_desc_view0[i].mbr_ubc = XDMA_UBC_NVIEW_NDV0
			                            | XDMA_UBC_NSEN_UPDATED
			                            | XDMA_UBC_NDEN_UPDATED
			                            | XDMA_UBC_NDE_FETCH_EN
			                            | MICROBLOCK_LEN;
			xdmacd_desc_view0[i].mbr_nda = &xdmacd_desc_view0[i + 1];
			xdmacd_desc_view0[i].mbr_ta = dest_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i;
		}

		/* last list element */
		xdmacd_desc_view0[MAX_LL_SIZE - 1].mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
		xdmacd_desc_view0[MAX_LL_SIZE - 1].mbr_nda = 0;

		xdmacd_cfg->sa = src_buf;
		xdmacd_cfg->da = dest_buf;

		desc_size = sizeof(xdmacd_desc_view0);
		*desc_cntrl |= XDMAC_CNDC_NDVIEW_NDV0;
		*xdmacd_view = &xdmacd_desc_view0;
		break;

	case 1:
		for (i = 0; i < MAX_LL_SIZE; i++) {
			xdmacd_desc_view1[i].mbr_ubc = XDMA_UBC_NVIEW_NDV1
			                            | XDMA_UBC_NSEN_UPDATED
			                            | XDMA_UBC_NDEN_UPDATED
			                            | XDMA_UBC_NDE_FETCH_EN
			                            | MICROBLOCK_LEN;
			xdmacd_desc_view1[i].mbr_sa = src_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i;
			xdmacd_desc_view1[i].mbr_da = dest_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i;
			xdmacd_desc_view1[i].mbr_nda = &xdmacd_desc_view1[i + 1];
		}

		/* last list element */
		xdmacd_desc_view1[MAX_LL_SIZE - 1].mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
		xdmacd_desc_view1[MAX_LL_SIZE - 1].mbr_nda = 0;

		desc_size = sizeof(xdmacd_desc_view1);
		*desc_cntrl |= XDMAC_CNDC_NDVIEW_NDV1;
		*xdmacd_view = &xdmacd_desc_view1;
		break;

	case 2:
		for (i = 0 ; i < MAX_LL_SIZE ; i++) {
			xdmacd_desc_view2[i].mbr_ubc = XDMA_UBC_NVIEW_NDV2
			                            | XDMA_UBC_NSEN_UPDATED
			                            | XDMA_UBC_NDEN_UPDATED
			                            | XDMA_UBC_NDE_FETCH_EN
			                            | MICROBLOCK_LEN;
			xdmacd_desc_view2[i].mbr_sa = src_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i;
			xdmacd_desc_view2[i].mbr_da = dest_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i;
			xdmacd_desc_view2[i].mbr_cfg = xdmacd_cfg->cfg;
			xdmacd_desc_view2[i].mbr_nda = &xdmacd_desc_view2[i + 1];
		}

		/* last list element */
		xdmacd_desc_view2[MAX_LL_SIZE - 1].mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
		xdmacd_desc_view2[MAX_LL_SIZE - 1].mbr_nda = 0;

		desc_size = sizeof(xdmacd_desc_view2);
		*desc_cntrl |= XDMAC_CNDC_NDVIEW_NDV2;
		*xdmacd_view = &xdmacd_desc_view2;
		break;

	case 3:
		for (i = 0 ; i < MAX_LL_SIZE ; i++) {
			xdmacd_desc_view3[i].mbr_ubc = XDMA_UBC_NVIEW_NDV3
			                            | XDMA_UBC_NSEN_UPDATED
			                            | XDMA_UBC_NDEN_UPDATED
			                            | XDMA_UBC_NDE_FETCH_EN
			                            | MICROBLOCK_LEN;
			xdmacd_desc_view3[i].mbr_sa = src_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i;
			xdmacd_desc_view3[i].mbr_da = dest_buf + MICROBLOCK_LEN * (1 << dma_data_width) * i;
			xdmacd_desc_view3[i].mbr_cfg = xdmacd_cfg->cfg;
			xdmacd_desc_view3[i].mbr_nda = &xdmacd_desc_view3[i + 1];
			xdmacd_desc_view3[i].mbr_bc = 0;
			xdmacd_desc_view3[i].mbr_ds = 0;
			xdmacd_desc_view3[i].mbr_sus = 0;
			xdmacd_desc_view3[i].mbr_dus = 0;
		}

		/* last list element */
		xdmacd_desc_view3[MAX_LL_SIZE - 1].mbr_ubc &= ~XDMA_UBC_NDE_FETCH_EN;
		xdmacd_desc_view3[MAX_LL_SIZE - 1].mbr_nda = 0;

		desc_size = sizeof(xdmacd_desc_view3);
		*desc_cntrl |= XDMAC_CNDC_NDVIEW_NDV3;
		*xdmacd_view = &xdmacd_desc_view3;
		break;
	}

	return desc_size;
	
}
/**
 * \brief Programming DMAC for Multiple Buffer Transfers.
 */
static void _configure_transfer(void)
{
	struct _xdmacd_cfg xdmacd_cfg;
	void* xdmacd_desc = NULL;
	uint32_t desc_size;

	if (dma_mode != XDMA_LL) {
		xdmacd_cfg.ubc = MICROBLOCK_LEN;
		xdmacd_cfg.sa = src_buf;
		xdmacd_cfg.da = dest_buf;
		xdmacd_cfg.cfg = XDMAC_CC_TYPE_MEM_TRAN |
			XDMA_GET_CC_MEMSET(dma_memset) |
			XDMAC_CC_MBSIZE_SINGLE |
			XDMAC_CC_CSIZE_CHK_1 |
			XDMA_GET_DATASIZE(dma_data_width) |
			XDMAC_CC_SIF_AHB_IF0 |
			XDMAC_CC_DIF_AHB_IF0 |
			XDMA_GET_CC_SAM(dma_src_addr_mode) |
			XDMA_GET_CC_DAM(dma_dest_addr_mode);
		xdmacd_cfg.bc = (dma_mode == XDMA_SINGLE) ? 0 : 1;
		xdmacd_cfg.ds = 0;
		xdmacd_cfg.sus = 0;
		xdmacd_cfg.dus = 0;

		xdmacd_configure_transfer(xdmacd_channel, &xdmacd_cfg, 0, 0);

		printf("- Microblock length: %u\r\n",
				(unsigned int)xdmacd_cfg.ubc);
		printf("- Block length: %u\r\n",
				(unsigned int)xdmacd_cfg.bc);
		printf("- Data Stride/Pattern: %u\r\n",
				(unsigned int)xdmacd_cfg.ds);
		printf("- Source Microblock Stride: %u\r\n",
				(unsigned int)xdmacd_cfg.sus);
		printf("- Destination  Microblock Stride: %u\r\n",
				(unsigned int)xdmacd_cfg.dus);
	} else {
		uint32_t desc_cntrl;

		xdmacd_cfg.bc = 0;
		xdmacd_cfg.ds = 0;
		xdmacd_cfg.sus = 0;
		xdmacd_cfg.dus = 0;
		switch (dma_view) {
		case 0:
			xdmacd_cfg.cfg = XDMAC_CC_TYPE_MEM_TRAN |
				XDMA_GET_CC_MEMSET(dma_memset) |
				XDMAC_CC_MBSIZE_SINGLE |
				XDMAC_CC_CSIZE_CHK_1 |
				XDMA_GET_DATASIZE(dma_data_width) |
				XDMAC_CC_SIF_AHB_IF0 |
				XDMAC_CC_DIF_AHB_IF0 |
				XDMA_GET_CC_SAM(dma_src_addr_mode) |
				XDMA_GET_CC_DAM(dma_dest_addr_mode);
			break;
		case 1:
			xdmacd_cfg.cfg = XDMAC_CC_TYPE_MEM_TRAN |
				XDMA_GET_CC_MEMSET(dma_memset) |
				XDMAC_CC_MBSIZE_SINGLE |
				XDMAC_CC_CSIZE_CHK_1 |
				XDMA_GET_DATASIZE(dma_data_width) |
				XDMAC_CC_SIF_AHB_IF0 |
				XDMAC_CC_DIF_AHB_IF0 |
				XDMA_GET_CC_SAM(dma_src_addr_mode) |
				XDMA_GET_CC_DAM(dma_dest_addr_mode);
			break;
		case 2:
		case 3:
			xdmacd_cfg.cfg = XDMAC_CC_TYPE_MEM_TRAN |
				XDMA_GET_CC_MEMSET(dma_memset) |
				XDMAC_CC_MBSIZE_SINGLE |
				XDMAC_CC_CSIZE_CHK_1 |
				XDMA_GET_DATASIZE(dma_data_width) |
				XDMAC_CC_SIF_AHB_IF0 |
				XDMAC_CC_DIF_AHB_IF0 |
				XDMA_GET_CC_SAM(dma_src_addr_mode) |
				XDMA_GET_CC_DAM(dma_dest_addr_mode);
			break;
		}
		desc_size = _configure_view(&xdmacd_desc, &desc_cntrl, &xdmacd_cfg);

		cache_clean_region(xdmacd_desc, desc_size);
		xdmacd_configure_transfer(xdmacd_channel, &xdmacd_cfg, desc_cntrl,
				xdmacd_desc);
	}

	xdmacd_set_callback(xdmacd_channel, _dma_callback, NULL);

	printf("- Press 't' to perform xDMA transfer...\r\n");
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
	xdmacd_start_transfer(xdmacd_channel);

	/* Wait for completion */
	while (!transfer_complete) {
		/* always call xdmacd_poll, it will do nothing if polling mode
		 * is disabled */
		xdmacd_poll();
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
 *  \brief dma Application entry point
 *  \return Unused (ANSI-C compatibility)
 */
extern int main(void)
{
	uint8_t key;
	bool configured = false;

	/* Output example information */
	console_example_info("XDMAC Example");

	/* Allocate a XDMAC channel. */
	xdmacd_channel = xdmacd_allocate_channel(XDMACD_PERIPH_MEMORY, XDMACD_PERIPH_MEMORY);
	if (!xdmacd_channel) {
		trace_error("Can't allocate XDMAC channel\r\n");
		return 0;
	}

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
			if (dma_memset == 0 && dma_view == 0) {
				trace_info("XDMAC View 0 cannot be used when MEMSET is in NORMAL mode, selecting DMA View 1 instead.\r\n");
				dma_view = 1;
			}
			_display_menu();
		}
		else if (key >= 'e' && key <= 'h') {
			dma_view = key - 'e';
			if (dma_view == 0 && dma_memset == 0) {
				trace_info("XDMAC View 0 can only be used when MEMSET is in HW mode, enabling HW mode.\r\n");
				dma_memset = 1;
			}
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
			trace_info("Start XDMAC transfer\r\n");
			_start_dma_transfer();
			configured = false;
		}
	}
}
