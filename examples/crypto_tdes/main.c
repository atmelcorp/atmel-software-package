/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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
 * \page tdes Triple Data Encryption Algorithm Example with SAMA5Dxx
 * Microcontrollers
 *
 * \section Purpose
 *
 * This application demonstrates the Triple Data Encryption Algorithm (TDES)
 * peripheral integrated in some SAMA5Dxx microcontrollers. It encrypts and
 * decrypts a test buffer in Electronic Code Book (ECB), Cipher Block Chaining
 * (CBC), Output Feedback (OFB), and Cipher Feedback (CFB) modes, and checks the
 * decrypted data against the expected result.
 *
 * \section Requirements
 *
 * This package is compatible with the evaluation boards listed below:
 * - SAMA5D2-VB
 * - SAMA5D2-XULT
 * - SAMA5D4-EK
 * - SAMA5D4-XULT
 *
 * \section Description
 * This example shows how to configure TDES in encryption and decryption modes.
 * In encryption mode, it encrypts plain text in one of the ECB/CBC/OFB/CFB
 * modes.
 * Programmable key mode with Single DES, Triple DES or XTEA encryption, with or
 * without DMA support.
 * In decryption mode, it decrypts cipher data generated at encryption step,
 * and prints the result, which should match the initial plain value.
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
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and chip used):
 *    \code
 *     -- TDES Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     TDES menu:
 *     Press [s|t|x] to set algorithm for encryption/decryption
 *     Press [k] set key algorithm (three key or two key mode, no need for DES)
 *     Press [0|1|2|3] to set the Mode of Operation
 *     Press [m|a|d] to set Start Mode
 *        p: Begin the encryption/decryption process
 *        h: Display this menu
 *     \endcode
 * -# Input command according to the menu.
 *
 * \section References
 * - tdes/main.c
 * - tdes.h
 * - tdes.h
 */

/** \file
 *
 *  This file contains all the specific code for the TDES
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "board.h"
#include "compiler.h"
#include "chip.h"
#include "peripherals/tdes.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/xdmad.h"

#include "misc/cache.h"
#include "misc/console.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define DATA_LEN_INBYTE   640
#define DATA_LEN_INWORD   (DATA_LEN_INBYTE / 4)

#define TDES_VECTOR_0     0x11223344
#define TDES_VECTOR_1     0x55667788

#define TDES_KEY1_0       0x01234567
#define TDES_KEY1_1       0x89ABCDEF
#define TDES_KEY2_0       0x76543210
#define TDES_KEY2_1       0xFEDCBA98
#define TDES_KEY3_0       0x55AA55AA
#define TDES_KEY3_1       0xAA55AA55

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

char example_text[DATA_LEN_INBYTE] = "\
***************************************************************\n\r\
* The Triple Data Encryption Standard (TDES) is compliant with the American \n\r\
* FIPS Publication 46-3 specification. The TDES supports the four different \n\r\
* confidentiality modes of operation (ECB, CBC, OFB and CFB), specified in  \n\r\
* the FIPS and is compatible with the Peripheral Data Controller channels   \n\r\
* for all of these modes, minimizing processor intervention for large buffer\n\r\
* transfers.                                                                \n\r\
                                        \n\r\
***************************************************************\n\r";

/* Buffers hereafter will receive data transferred by the DMA to/from the
 * peripheral. The data cache won't notice this memory update, hence we'll have
 * to clean/invalidate the related cache lines.
 * May the buffers fail to be aligned on cache lines, cache clean operations
 * would then occur on the shared lines. Which would be prone to data conflicts
 * between these buffers and the variables placed on a same cache line.
 * Alternatively, we might consider allocating these buffers from a
 * non-cacheable memory region. */
ALIGNED(L1_CACHE_BYTES)
static uint32_t msg_in_clear[ROUND_UP_MULT(DATA_LEN_INWORD, L1_CACHE_WORDS)];
ALIGNED(L1_CACHE_BYTES)
static uint32_t msg_encrypted[ROUND_UP_MULT(DATA_LEN_INWORD, L1_CACHE_WORDS)];
ALIGNED(L1_CACHE_BYTES)
static uint32_t msg_decrypted[ROUND_UP_MULT(DATA_LEN_INWORD, L1_CACHE_WORDS)];

static uint32_t algo, op_mode, start_mode, key_mode;
static volatile bool data_ready = false;

static struct _xdmad_channel *dma_wr_chan = NULL, *dma_rd_chan = NULL;
/* DMA linked lists */
ALIGNED(L1_CACHE_BYTES)
static struct _xdmad_desc_view1 dma_wr_dlist[DATA_LEN_INWORD];
ALIGNED(L1_CACHE_BYTES)
static struct _xdmad_desc_view1 dma_rd_dlist[DATA_LEN_INWORD];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief xDMA init.
 */
static void init_dma(void)
{
	/* Initialize XDMA driver instance with polling mode */
	/* Allocate XDMA channels:
	 * 1. Write accesses into TDES_IDATARx
	 * 2. Read accesses into TDES_ODATARx */
	dma_wr_chan = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, ID_TDES);
	dma_rd_chan = xdmad_allocate_channel(ID_TDES, XDMAD_PERIPH_MEMORY);
	if (!dma_wr_chan || !dma_rd_chan)
		printf("-E- Can't allocate XDMA channel\n\r");
	else {
		xdmad_prepare_channel(dma_wr_chan);
		xdmad_prepare_channel(dma_rd_chan);
	}
}

/**
 * \brief Configure xDMA write linker list for TDES transfer.
 * \param buf  Pointer to data buffer.
 * \param len  Count of 32-bit data blocks.
 */
static void configure_dma_write(uint32_t *buf, uint32_t len)
{
	uint32_t i;
	struct _xdmad_cfg dma_cfg = {
		.cfg = XDMAC_CC_TYPE_PER_TRAN |
			XDMAC_CC_MBSIZE_SINGLE | XDMAC_CC_DSYNC_MEM2PER |
			XDMAC_CC_CSIZE_CHK_1 | XDMAC_CC_DWIDTH_WORD |
			XDMAC_CC_SIF_AHB_IF0 | XDMAC_CC_DIF_AHB_IF1 |
			XDMAC_CC_SAM_INCREMENTED_AM | XDMAC_CC_DAM_FIXED_AM,
	};

	for (i = 0; i < len; i++) {
		dma_wr_dlist[i].mbr_ubc = XDMA_UBC_NVIEW_NDV1 |
			(i == len - 1 ? 0 : XDMA_UBC_NDE_FETCH_EN) |
			XDMA_UBC_NSEN_UPDATED | 1;
		dma_wr_dlist[i].mbr_sa = &buf[i];
		dma_wr_dlist[i].mbr_da = (void*)&TDES->TDES_IDATAR[0];
		dma_wr_dlist[i].mbr_nda = i == len - 1 ? NULL :
			&dma_wr_dlist[i + 1];
	}
	cache_clean_region(dma_wr_dlist, sizeof(*dma_wr_dlist) * len);
	xdmad_configure_transfer(dma_wr_chan, &dma_cfg, XDMAC_CNDC_NDVIEW_NDV1 |
		XDMAC_CNDC_NDE_DSCR_FETCH_EN |
		XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED |
		XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED, dma_wr_dlist);
}

/**
 * \brief Configure xDMA read linker list for TDES transfer.
 * \param buf  Pointer to data buffer.
 * \param len  Count of 32-bit data blocks.
 */
static void configure_dma_read(uint32_t *buf, uint32_t len)
{
	uint32_t i;
	struct _xdmad_cfg dma_cfg = {
		.cfg = XDMAC_CC_TYPE_PER_TRAN |
			XDMAC_CC_MBSIZE_SINGLE | XDMAC_CC_DSYNC_PER2MEM |
			XDMAC_CC_CSIZE_CHK_1 | XDMAC_CC_DWIDTH_WORD |
			XDMAC_CC_SIF_AHB_IF1 | XDMAC_CC_DIF_AHB_IF0 |
			XDMAC_CC_SAM_FIXED_AM | XDMAC_CC_DAM_INCREMENTED_AM,
	};

	for (i = 0; i < len; i++) {
		dma_rd_dlist[i].mbr_ubc = XDMA_UBC_NVIEW_NDV1 |
			(i == len - 1 ? 0 : XDMA_UBC_NDE_FETCH_EN) |
			XDMA_UBC_NDEN_UPDATED | 1;
		dma_rd_dlist[i].mbr_sa = (void*)&TDES->TDES_ODATAR[0];
		dma_rd_dlist[i].mbr_da = &buf[i];
		dma_rd_dlist[i].mbr_nda = i == len - 1 ? NULL :
			&dma_rd_dlist[i + 1];
	}
	cache_clean_region(dma_rd_dlist, sizeof(*dma_rd_dlist) * len);
	xdmad_configure_transfer(dma_rd_chan, &dma_cfg, XDMAC_CNDC_NDVIEW_NDV1 |
		XDMAC_CNDC_NDE_DSCR_FETCH_EN |
		XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED |
		XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED, dma_rd_dlist);
}

/**
 * \brief TDES interrupt hander.
 */
static void handle_tdes_irq(void)
{
	if ((tdes_get_status() & TDES_ISR_DATRDY) == TDES_ISR_DATRDY) {
		tdes_disable_it(TDES_IER_DATRDY);
		data_ready = true;
	}
}

/**
 * \brief Encrypt or decrypt the specified data buffer.
 * In this sample code, the size of data buffers is hardcoded.
 * \param encrypt  True to encrypt, false to decrypt
 * \param in  Input buffer
 * \param out  Target buffer receiving processed data
 */
static void process_buffer(bool encrypt, uint32_t *in, uint32_t *out)
{
	const bool use_dma = start_mode == TDES_MR_SMOD_IDATAR0_START;
	uint32_t rc = 0, i;

	tdes_configure((encrypt ?
		TDES_MR_CIPHER_ENCRYPT : TDES_MR_CIPHER_DECRYPT)
		| algo | key_mode | start_mode | op_mode);
	/* Write the 64-bit key(s) in the different Key Word Registers,
	 * depending on whether one, two or three keys are required. */
	tdes_write_key1(TDES_KEY1_0, TDES_KEY1_1);
	tdes_write_key2(TDES_KEY2_0, TDES_KEY2_1);
	if (key_mode == 0)
		tdes_write_key3(TDES_KEY3_0, TDES_KEY3_1);
	else
		tdes_write_key3(0, 0);
	/* The Initialization Vector Registers apply to all modes except ECB. */
	if (op_mode != TDES_MR_OPMOD_ECB)
		tdes_set_vector(TDES_VECTOR_0, TDES_VECTOR_1);
	if (use_dma) {
		init_dma();
		if (encrypt)
			cache_clean_region(in, DATA_LEN_INBYTE);
		configure_dma_write(in, DATA_LEN_INWORD);
		configure_dma_read(out, DATA_LEN_INWORD);
		printf("-I- TDES %scryption, starting dual DMA transfer"
			   "\n\r", encrypt ? "en" : "de");
		rc = xdmad_start_transfer(dma_wr_chan);
		if (rc == XDMAD_OK)
			rc = xdmad_start_transfer(dma_rd_chan);
		if (rc == XDMAD_OK) {
			while (!xdmad_is_transfer_done(dma_rd_chan))
				xdmad_poll();
			xdmad_stop_transfer(dma_rd_chan);
			xdmad_stop_transfer(dma_wr_chan);
		}
		xdmad_free_channel(dma_rd_chan); dma_rd_chan = NULL;
		xdmad_free_channel(dma_wr_chan); dma_wr_chan = NULL;
		cache_invalidate_region(out, DATA_LEN_INBYTE);
	} else
		/* Iterate per 64-bit data block */
		for (i = 0; i < DATA_LEN_INWORD; i += 2) {
			data_ready = false;
			tdes_enable_it(TDES_IER_DATRDY);
			/* Write one 64-bit input data block to the authorized
			 * Input Data Registers */
			tdes_set_input(in[i], in[i + 1]);
			if (start_mode == TDES_MR_SMOD_MANUAL_START)
				/* Set the START bit in the TDES Control
				 * register to begin the encryption or
				 * decryption process. */
				tdes_start();
			while (!data_ready) ;
			tdes_get_output(&out[i], &out[i + 1]);
		}
}

/**
 * \brief Start TDES process.
 */
static void start_tdes(void)
{
	uint32_t i;
	uint8_t c;

	/* Perform a software-triggered hardware reset of the TDES interface */
	tdes_soft_reset();

	if (algo == TDES_MR_TDESMOD(2))
		tdes_set_xtea_rounds(32);

	memcpy((char*)msg_in_clear, example_text, sizeof(example_text));
	memset(msg_encrypted, 0xff, DATA_LEN_INBYTE);
	memset(msg_decrypted, 0xff, DATA_LEN_INBYTE);

	process_buffer(true, msg_in_clear, msg_encrypted);
	printf("-I- Dumping the encrypted message...");
	for (i = 0; i < DATA_LEN_INWORD; i++) {
		if (i % 8 == 0)
			printf("\n\r%03lx:    ", i * 4);
		printf(" %08lx", msg_encrypted[i]);
	}
	printf("\n\r");

	process_buffer(false, msg_encrypted, msg_decrypted);
	printf("-I- Dumping plain text after TDES decryption...\n\r");
	/* Print the entire buffer, even past the nul characters if any */
	for (i = 0; i < DATA_LEN_INBYTE; i++) {
		c = ((const uint8_t*)msg_decrypted)[i];
		if (isprint(c) || isspace(c))
			putchar(c);
		else
			printf("%%%x", c);
	}
	printf("\n\r");
}

/**
 * \brief Display main menu.
 */
static void display_menu(void)
{
	uint8_t chk_box[4];

	printf("\n\rTDES menu:\n\r");
	printf("Press [s|t|x] to set algorithm for encryption/decryption\n\r");
	chk_box[0] = (algo == TDES_MR_TDESMOD(0)) ? 'X' : ' ';
	chk_box[1] = (algo == TDES_MR_TDESMOD(1)) ? 'X' : ' ';
	chk_box[2] = (algo == TDES_MR_TDESMOD(2)) ? 'X' : ' ';
	printf("   s: SINGLE[%c] t: TRIPLE[%c] x: XTEA[%c]\n\r", chk_box[0],
	       chk_box[1], chk_box[2]);
	printf("Press [k] set key algorithm (three key or two key mode, no need"
	       " for DES)\n\r");
	chk_box[0] = (key_mode == 0) ? 'X' : ' ';
	chk_box[1] = (key_mode == TDES_MR_KEYMOD) ? 'X' : ' ';
	printf("   Three key[%c] Two key[%c] \n\r", chk_box[0], chk_box[1]);
	printf("Press [0|1|2|3] to set the Mode of Operation\n\r");
	chk_box[0] = (op_mode == TDES_MR_OPMOD_ECB) ? 'X' : ' ';
	chk_box[1] = (op_mode == TDES_MR_OPMOD_CBC) ? 'X' : ' ';
	chk_box[2] = (op_mode == TDES_MR_OPMOD_OFB) ? 'X' : ' ';
	chk_box[3] = (op_mode == TDES_MR_OPMOD_CFB) ? 'X' : ' ';
	printf("   0: Electronic Code Book    [%c]\n\r", chk_box[0]);
	printf("   1: Cipher Block Chaining   [%c]\n\r", chk_box[1]);
	printf("   2: Output Feedback         [%c]\n\r", chk_box[2]);
	printf("   3: Cipher Feedback         [%c]\n\r", chk_box[3]);
	printf("Press [m|a|d] to set Start Mode\n\r");
	chk_box[0] = (start_mode == TDES_MR_SMOD_MANUAL_START) ? 'X' : ' ';
	chk_box[1] = (start_mode == TDES_MR_SMOD_AUTO_START) ? 'X' : ' ';
	chk_box[2] = (start_mode == TDES_MR_SMOD_IDATAR0_START) ? 'X' : ' ';
	printf("   m: MANUAL_START[%c] a: AUTO_START[%c] d: DMA[%c]\n\r",
	       chk_box[0], chk_box[1], chk_box[2]);
	printf("   p: Begin the encryption/decryption process\n\r");
	printf("   h: Display this menu\n\r");
	printf("\n\r");
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief TDES Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t user_key;

	/* Output example information */
	console_example_info("TDES Example");

	/* Enable peripheral clock */
	pmc_enable_peripheral(ID_TDES);
	/* Enable peripheral interrupt */
	aic_set_source_vector(ID_TDES, handle_tdes_irq);
	aic_enable(ID_TDES);

	/* Display menu */
	algo = TDES_MR_TDESMOD(0);
	op_mode = TDES_MR_OPMOD_ECB;
	start_mode = TDES_MR_SMOD_MANUAL_START;
	key_mode = 0;
	display_menu();

	while (true) {
		user_key = tolower(console_get_char());
		switch (user_key) {
		case 's':
		case 't':
		case 'x':
			algo = TDES_MR_TDESMOD(user_key == 'x' ? 2 :
			                                user_key - 's');
			key_mode = user_key == 'x' ? TDES_MR_KEYMOD : key_mode;
			display_menu();
			break;
		case 'k':
			key_mode = key_mode == 0 ? TDES_MR_KEYMOD : 0;
			if (op_mode == TDES_MR_OPMOD_CFB
			    || algo == TDES_MR_TDESMOD(2))
				key_mode = TDES_MR_KEYMOD;
			display_menu();
			break;
		case '0':
		case '1':
		case '2':
		case '3':
			op_mode = ((user_key - '0') << TDES_MR_OPMOD_Pos);
			key_mode = user_key == '3' ? TDES_MR_KEYMOD : key_mode;
			display_menu();
			break;
		case 'm':
		case 'a':
		case 'd':
			start_mode = user_key == 'a' ? TDES_MR_SMOD_AUTO_START :
			            (user_key == 'd' ? TDES_MR_SMOD_IDATAR0_START :
			                               TDES_MR_SMOD_MANUAL_START);
		case 'h':
			display_menu();
			break;
		case 'p':
			start_tdes();
			break;
		}
	}

	/* This code is never reached */
}
