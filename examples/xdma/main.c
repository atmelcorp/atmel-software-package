/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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

#include <board.h>
#include <string.h>

#include "peripherals/wdt.h"
#include "peripherals/aic.h"

#include "misc/console.h"
#include "peripherals/xdmad.h"
#include "peripherals/xdmac.h"

/*----------------------------------------------------------------------------
 *         Local constants
 *----------------------------------------------------------------------------*/
#define XDMA_SINGLE          1
#define XDMA_MULTI           2
#define XDMA_LLI             3

/** Maximum size of Linked List Item  in this example*/
#define MAX_LLI_SIZE         2
/** Microblock length for single transfer  */
#define MICROBLOCK_LEN       16
/** Buffer length */
#define BUFFER_LEN         128
/** Polling or interrupt mode */
#define POLLING_MODE   0

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/** Global DMA driver instance for all DMA transfers in application. */
static sXdmad xdmad;
static sXdmadCfg xdmadCfg;

#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma data_alignment=8
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((aligned(8)))
#endif
static LinkedListDescriporView1 LLIview1[MAX_LLI_SIZE];

/* DMA driver instance */
static uint32_t dmaChannel;

/* Linked lists for multi transfer buffer chaining structure instance. */
//static sDmaTransferDescriptor dmaLinkList[MAX_LLI_SIZE];

#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma data_alignment=8
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((aligned(8)))
#endif
static uint8_t sourceBuffer[512];

#if defined ( __ICCARM__ )	/* IAR Ewarm */
#pragma data_alignment=8
#elif defined (  __GNUC__  )	/* GCC CS3 */
__attribute__ ((aligned(8)))
#endif
static uint8_t destinationBuffer[512];

/* Current Programming DMAC mode for Multiple Buffer Transfers */
static uint8_t dmaProgrammingMode = 0;
static uint8_t ConfigFlag = 0;
static uint8_t dmaDataWidth = 0;
static uint8_t dmaSourceAddrMode = 0;
static uint8_t dmaDestAddrMode = 0;
static uint8_t dmaMemSet = 0;

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Dump buffer to DBGU
 *
 */
static void _DumpBufferInfo(uint8_t * pcBuffer)
{
	uint32_t i = 0;
	while (i < BUFFER_LEN) {
		printf("%02x ", pcBuffer[i++]);
		if ((i % 16 == 0))
			printf("\n\r");
	}
	printf("\n\r");
}

/**
 * \brief Display main menu.
 */
static void _displayMenu(void)
{
	uint8_t ucChar[4];
	printf("\n\rxDMA Menu :\n\r");
	printf
	    ("\n\r|====== Channel Configuration ================================|\n\r");
	printf
	    ("| Press [a|b|c|d] to set Date width                           |\n\r");
	ucChar[0] = (dmaDataWidth == 0) ? 'X' : ' ';
	ucChar[1] = (dmaDataWidth == 1) ? 'X' : ' ';
	ucChar[2] = (dmaDataWidth == 2) ? 'X' : ' ';
	ucChar[3] = (dmaDataWidth == 3) ? 'X' : ' ';
	printf
	    ("|   a: BYTE[%c] b: HALFWORD[%c] c: WORD[%c] d: DWORD[%c]          |\n\r",
	     ucChar[0], ucChar[1], ucChar[2], ucChar[3]);
	printf
	    ("| Press [0|1|2|3] to set Source Addressing Mode               |\n\r");
	ucChar[0] = (dmaSourceAddrMode == 0) ? 'X' : ' ';
	ucChar[1] = (dmaSourceAddrMode == 1) ? 'X' : ' ';
	ucChar[2] = (dmaSourceAddrMode == 2) ? 'X' : ' ';
	ucChar[3] = (dmaSourceAddrMode == 3) ? 'X' : ' ';
	printf
	    ("|   0: FIXED[%c] 1: INCR[%c] 2: AM[%c] 3: DS_AM[%c]               |\n\r",
	     ucChar[0], ucChar[1], ucChar[2], ucChar[3]);
	printf
	    ("| Press [4|5|6|7] to set Destination Addressing Mode          |\n\r");
	ucChar[0] = (dmaDestAddrMode == 0) ? 'X' : ' ';
	ucChar[1] = (dmaDestAddrMode == 1) ? 'X' : ' ';
	ucChar[2] = (dmaDestAddrMode == 2) ? 'X' : ' ';
	ucChar[3] = (dmaDestAddrMode == 3) ? 'X' : ' ';
	printf
	    ("|   4: FIXED[%c] 5: INCR[%c] 6: AM[%c] 7: DS_AM[%c]               |\n\r",
	     ucChar[0], ucChar[1], ucChar[2], ucChar[3]);
	printf
	    ("| Press [8|9| to set MEMSET Mode                              |\n\r");
	ucChar[0] = (dmaMemSet == 0) ? 'X' : ' ';
	ucChar[1] = (dmaMemSet == 1) ? 'X' : ' ';
	printf
	    ("|   8: NORMAL Mode[%c] 9: HW_MODE[%c]                           |\n\r",
	     ucChar[0], ucChar[1]);
	printf
	    ("|=============================================================|\n\r");
	printf("\n\r- xDMA transfer type \n\r");
	printf("    S: Single Block with Single Microblock transfer\n\r");
	printf("    M: Single Block with Multiple Microblock transfer  \n\r");
	printf("    L: Linked List Master transfer\n\r");
	printf("- t: Start DMA transfer\n\r");
	printf("- h: Display this menu\n\r");
	printf("\n\r");
}

/**
 * \brief Programming DMAC for Multiple Buffer Transfers.
 */
static uint8_t _configureTransferMode(void)
{
	uint32_t xdmaCndc;
	uint8_t i;
	if (dmaProgrammingMode < XDMA_LLI) {
		xdmadCfg.mbr_ubc = MICROBLOCK_LEN;
		xdmadCfg.mbr_sa = (uint32_t) sourceBuffer;
		xdmadCfg.mbr_da = (uint32_t) destinationBuffer;
		xdmadCfg.mbr_cfg = XDMAC_CC_TYPE_MEM_TRAN |
		    XDMA_GET_CC_MEMSET(dmaMemSet) |
		    XDMAC_CC_MEMSET_NORMAL_MODE |
		    XDMAC_CC_CSIZE_CHK_1 |
		    XDMA_GET_DATASIZE(dmaDataWidth) |
		    XDMAC_CC_SIF_AHB_IF0 |
		    XDMAC_CC_DIF_AHB_IF0 |
		    XDMA_GET_CC_SAM(dmaSourceAddrMode) |
		    XDMA_GET_CC_DAM(dmaDestAddrMode);

		xdmadCfg.mbr_bc = (dmaProgrammingMode == XDMA_SINGLE) ? 0 : 1;
		xdmadCfg.mbr_ds = 0;
		xdmadCfg.mbr_sus = 0;
		xdmadCfg.mbr_dus = 0;
		XDMAD_ConfigureTransfer(&xdmad, dmaChannel, &xdmadCfg, 0, 0);
		printf("- Set Microblock length to [ %u ] \n\r",
		       (unsigned int)xdmadCfg.mbr_ubc);
		printf("- Set Block length [ %u ] \n\r",
		       (unsigned int)xdmadCfg.mbr_bc);
		printf("- Set Data Stride/Pattern [ %u ] \n\r",
		       (unsigned int)xdmadCfg.mbr_ds);
		printf("- Set Source Microblock Stride  [ %u ] \n\r",
		       (unsigned int)xdmadCfg.mbr_sus);
		printf("- Set Destination  Microblock Stride [ %u ]\n\r",
		       (unsigned int)xdmadCfg.mbr_dus);
		printf("- Press 't' to perform xDMA transfer...\n\r");

	}
	if (dmaProgrammingMode == XDMA_LLI) {
		xdmadCfg.mbr_cfg = XDMAC_CC_TYPE_MEM_TRAN |
		    XDMAC_CC_MBSIZE_SINGLE |
		    XDMA_GET_CC_MEMSET(dmaMemSet) |
		    XDMAC_CC_CSIZE_CHK_1 |
		    XDMA_GET_DATASIZE(dmaDataWidth) |
		    XDMAC_CC_SIF_AHB_IF0 |
		    XDMAC_CC_DIF_AHB_IF0 |
		    XDMA_GET_CC_SAM(dmaSourceAddrMode) |
		    XDMA_GET_CC_DAM(dmaDestAddrMode);
		xdmadCfg.mbr_bc = 0;
		for (i = 0; i < MAX_LLI_SIZE; i++) {
			LLIview1[i].mbr_ubc = XDMA_UBC_NVIEW_NDV1 |
			    ((i == 0) ? XDMA_UBC_NSEN_UPDATED : 0) |
			    ((i == 0) ? XDMA_UBC_NDEN_UPDATED : 0) |
			    ((i ==
			      MAX_LLI_SIZE -
			      1) ? 0 : XDMA_UBC_NDE_FETCH_EN) | MICROBLOCK_LEN;
			LLIview1[i].mbr_sa = (uint32_t) sourceBuffer + i;
			LLIview1[i].mbr_da = (uint32_t) destinationBuffer + i;
			LLIview1[i].mbr_nda =
			    (i ==
			     (MAX_LLI_SIZE - 1)) ? 0 : (uint32_t) & LLIview1[i +
									     1];
		}
		xdmaCndc = XDMAC_CNDC_NDVIEW_NDV1 |
		    XDMAC_CNDC_NDE_DSCR_FETCH_EN |
		    XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED |
		    XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED;
		XDMAD_ConfigureTransfer(&xdmad, dmaChannel, &xdmadCfg, xdmaCndc,
					(uint32_t) & LLIview1[0]);
		printf("- Press 't' to perform xDMA Master transfer...\n\r");
	}
	return 0;
}

/**
 * \brief Start DMAC Multiple Buffer Transfer.
 */
static uint8_t _startDmaTransfer(void)
{
	uint32_t i;
	/* Prepare source data to be transfered. */
	for (i = 0; i < BUFFER_LEN; i++) {
		sourceBuffer[i] = i;
		destinationBuffer[i] = 0xFF;
	}

	printf("-I- The Source Buffer 0 content before transfer\n\r");
	_DumpBufferInfo((uint8_t *) sourceBuffer);
	/* Start transfer */
	XDMAD_StartTransfer(&xdmad, dmaChannel);
	while (XDMAD_IsTransferDone(&xdmad, dmaChannel)) ;
	printf("-I- The Destination Buffer content after transfer\n\r");
	_DumpBufferInfo((uint8_t *) destinationBuffer);
	return 0;
}

void XDMAC0_IrqHandler(void)
{
	XDMAD_Handler(&xdmad);
}

void XDMAC1_IrqHandler(void)
{
	XDMAD_Handler(&xdmad);
}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief dma Application entry point
 *
 *  \return Unused (ANSI-C compatibility)
 */
extern int main(void)
{
	uint8_t key;

	/* Disable watchdog */
	WDT_Disable(WDT);

	/* Output example information */
	printf("-- XDMA Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);
	/* Initialize XDMA driver instance with polling mode */
	XDMAD_Initialize(&xdmad, POLLING_MODE);

	/* Allocate a XDMA channel. */
	dmaChannel =
	    XDMAD_AllocateChannel(&xdmad, XDMAD_TRANSFER_MEMORY,
				  XDMAD_TRANSFER_MEMORY);
	if (dmaChannel == XDMAD_ALLOC_FAILED) {
		printf("-E- Can't allocate XDMA channel\n\r");
		return 0;
	}
	XDMAD_PrepareChannel(&xdmad, dmaChannel);

	/*Enable xDMA interrupt */
	aic_enable(ID_XDMAC0);
	aic_enable(ID_XDMAC1);
	/* Display menu */
	_displayMenu();
	for (;;) {
		key = console_get_char();
		if ((key == 'a') || (key == 'b') || (key == 'c')
		    || (key == 'd')) {
			dmaDataWidth = key - 'a';
			_displayMenu();
		}
		if ((key >= '0') && (key <= '3')) {
			dmaSourceAddrMode = key - '0';
			_displayMenu();
		}
		if ((key >= '4') && (key <= '7')) {
			dmaDestAddrMode = key - '4';
			_displayMenu();
		}
		if ((key >= '8') && (key <= '9')) {
			dmaMemSet = key - '8';
			_displayMenu();
		}
		if ((key == 'S') || (key == 's')) {
			dmaProgrammingMode = 1;
			_configureTransferMode();
			ConfigFlag = 1;
		}
		if ((key == 'M') || (key == 'm')) {
			dmaProgrammingMode = 2;
			_configureTransferMode();
			ConfigFlag = 1;
		}
		if ((key == 'L') || (key == 'l')) {
			dmaProgrammingMode = 3;
			_configureTransferMode();
			ConfigFlag = 1;
		}
		if ((key == 'H') || (key == 'h'))
			_displayMenu();
		if ((key == 'T') || (key == 't')) {
			if (ConfigFlag) {
				printf("-I- Start XDMA transfer\n\r");
				_startDmaTransfer();
				ConfigFlag = 0;
			}
		}
	}
}
