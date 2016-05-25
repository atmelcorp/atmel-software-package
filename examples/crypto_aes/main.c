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
 * \page aes Advanced Encryption Standard Example with SAMA5Dxx Microcontrollers
 *
 * \section Purpose
 *
 * This application demonstrates the Advanced Encryption Standard (AES)
 * peripheral integrated in some SAMA5D microcontrollers. It encrypts and
 * decrypts several test values in Electronic Code Book (ECB), Cipher Block
 * Chaining (CBC), OBC, OFB and TRC modes, and checks the processed data
 * against the known answers.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5D4-EK and SAMA5D4-XULT.
 *
 * \section Description
 *
 * This example shows how to configure AES in encryption and decryption mode.
 * In encryption mode, it encrypts plain text in one of the ECB/CBC/OFB/CFB/CTR
 * modes. Programmable key mode with processing using with or without DMA
 * support.
 * In decryption mode, it decrypts cipher data generated from encryption mode,
 * and compares the result against the initial plain value.
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
 *     -- AES Example xxx --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *     -- Menu Choices for this example--
 *     \endcode
 * -# Input command according to the menu.
 *
 * \section References
 * - aes/main.c
 * - aes.c
 * - aes.h */

/** \file
 *
 * This file contains all the specific code for the AES
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "board.h"
#include "chip.h"
#include "peripherals/aes.h"
#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"
#include "peripherals/xdmad.h"

#include "misc/cache.h"
#include "misc/console.h"
#include "trace.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define DATA_LEN_INBYTE		640
#define DATA_LEN_INWORD		(DATA_LEN_INBYTE / 4)
#define DATA_LEN_INDWORD	(DATA_LEN_INBYTE / 8)

#define AES_VECTOR_0		0x11223344
#define AES_VECTOR_1		0x55667788
#define AES_VECTOR_2		0x11112222
#define AES_VECTOR_3		0x33334444

#define AES_KEY_0		0x01234567
#define AES_KEY_1		0x89ABCDEF
#define AES_KEY_2		0x76543210
#define AES_KEY_3		0xFEDCBA98
#define AES_KEY_4		0x55AA55AA
#define AES_KEY_5		0xAA55AA55
#define AES_KEY_6		0x0000FFFF
#define AES_KEY_7		0xFFFF0000

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

const char example_text[DATA_LEN_INBYTE] = "\
  The Advanced Encryption Standard (AES) is compliant with the A\
merican FIPS (Federal Information Processing Standard) Publicati\
on 197 specification. AES supports all five confidentiality mode\
s of operation for symmetrical key block cipher algorithms (ECB,\
CBC,OFB, CFB and CTR), as specified in the NIST Special Publicat\
ion 80038A. It is compatible with all these modes via Peripheral\
 DMA Controller channels, minimizing processor intervention for \
large buffer transfers.The 128-bit/192-bit/256-bit key is stored\
in four/six/eight 32-bit registers (AES_KEYWRx) which are all wr\
ite-only .......................................................";

const uint32_t aes_vectors[4] = {
	AES_VECTOR_0, AES_VECTOR_1, AES_VECTOR_2, AES_VECTOR_3 };
const uint32_t aes_keys[8] = {
	AES_KEY_0, AES_KEY_1, AES_KEY_2, AES_KEY_3, AES_KEY_4, AES_KEY_5,
	AES_KEY_6, AES_KEY_7 };

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

static uint32_t op_mode, start_mode, key_id, key_byte_len;
static volatile uint32_t data_ready = 0;

/** Global DMA driver instance for all DMA transfers in application. */
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
	xdmad_initialize(true);
	/* Allocate XDMA channels:
	 * 1. Write accesses into AES_IDATARx
	 * 2. Read accesses into AES_ODATARx */
	dma_wr_chan = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, ID_AES);
	dma_rd_chan = xdmad_allocate_channel(ID_AES, XDMAD_PERIPH_MEMORY);
	if (!dma_wr_chan || !dma_rd_chan)
		printf("-E- Can't allocate XDMA channel\n\r");
	else {
		xdmad_prepare_channel(dma_wr_chan);
		xdmad_prepare_channel(dma_rd_chan);
	}
}

/**
 * \brief Configure xDMA write linker list for AES transfer.
 * \param buf  Pointer to data buffer.
 * \param len  Count of 128-bit data blocks.
 */
static void configure_dma_write(uint32_t *buf, uint32_t len)
{
	uint32_t i;
	struct _xdmad_cfg dma_cfg = {
		.cfg = XDMAC_CC_TYPE_PER_TRAN |
			XDMAC_CC_MBSIZE_SINGLE | XDMAC_CC_DSYNC_MEM2PER |
			XDMAC_CC_CSIZE_CHK_4 | XDMAC_CC_DWIDTH_WORD |
			XDMAC_CC_SIF_AHB_IF0 | XDMAC_CC_DIF_AHB_IF1 |
			XDMAC_CC_SAM_INCREMENTED_AM | XDMAC_CC_DAM_FIXED_AM,
	};

	for (i = 0; i < len; i++) {
		dma_wr_dlist[i].mbr_ubc = XDMA_UBC_NVIEW_NDV1 |
			(i == len - 1 ? 0 : XDMA_UBC_NDE_FETCH_EN) |
			XDMA_UBC_NSEN_UPDATED | 4;
		dma_wr_dlist[i].mbr_sa = &buf[i * 4];
		dma_wr_dlist[i].mbr_da = (void*)&AES->AES_IDATAR[0];
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
 * \brief Configure xDMA read linker list for AES transfer.
 * \param buf  Pointer to data buffer.
 * \param len  Count of 128-bit data blocks.
 */
static void configure_dma_read(uint32_t *buf, uint32_t len)
{
	uint32_t i;
	struct _xdmad_cfg dma_cfg = {
		.cfg = XDMAC_CC_TYPE_PER_TRAN |
			XDMAC_CC_MBSIZE_SINGLE | XDMAC_CC_DSYNC_PER2MEM |
			XDMAC_CC_CSIZE_CHK_4 | XDMAC_CC_DWIDTH_WORD |
			XDMAC_CC_SIF_AHB_IF1 | XDMAC_CC_DIF_AHB_IF0 |
			XDMAC_CC_SAM_FIXED_AM | XDMAC_CC_DAM_INCREMENTED_AM,
	};

	for (i = 0; i < len; i++) {
		dma_rd_dlist[i].mbr_ubc = XDMA_UBC_NVIEW_NDV1 |
			(i == len - 1 ? 0 : XDMA_UBC_NDE_FETCH_EN) |
			XDMA_UBC_NDEN_UPDATED | 4;
		dma_rd_dlist[i].mbr_sa = (void*)&AES->AES_ODATAR[0];
		dma_rd_dlist[i].mbr_da = &buf[i * 4];
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
 * \brief AES interrupt hander.
 */
static void handle_aes_irq(void)
{
	if ((aes_get_status() & AES_ISR_DATRDY) == AES_ISR_DATRDY) {
		aes_disable_it(AES_IER_DATRDY);
		data_ready = 1;
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
	const bool use_dma = start_mode == AES_MR_SMOD_IDATAR0_START;
	uint32_t rc = 0, i;

	aes_configure((encrypt ? AES_MR_CIPHER_ENCRYPT : AES_MR_CIPHER_DECRYPT)
		| start_mode | key_id | op_mode);
	/* Write the 128-bit/192-bit/256-bit key in the Key Word Registers */
	aes_write_key(aes_keys, key_byte_len);
	/* The Initialization Vector Registers apply to all modes except
	 * ECB. */
	if (op_mode != AES_MR_OPMOD_ECB)
		aes_set_vector(aes_vectors);
	if (use_dma) {
		init_dma();
		aes_set_data_len(DATA_LEN_INBYTE);
		if (encrypt)
			cache_clean_region(in, DATA_LEN_INBYTE);
		configure_dma_write(in, DATA_LEN_INWORD / 4);
		configure_dma_read(out, DATA_LEN_INWORD / 4);
		printf("-I- AES %scryption, starting dual DMA transfer"
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
		/* Iterate per 128-bit data block */
		for (i = 0; i < DATA_LEN_INWORD; i += 4) {
			data_ready = 0;
			aes_enable_it(AES_IER_DATRDY);
			/* Write one 128-bit input data block in the authorized
			 * Input Data Registers */
			aes_set_input(&in[i]);
			if (start_mode == AES_MR_SMOD_MANUAL_START)
				/* Set the START bit in the AES Control register
				 * to begin the encrypt. or decrypt. process. */
				aes_start();
			while (!data_ready) ;
			aes_get_output(&out[i]);
		}
}

/**
 * \brief Start AES process.
 */
static void start_aes(void)
{
	uint32_t i;
	uint8_t c;

	/* Perform a software-triggered hardware reset of the AES interface */
	aes_soft_reset();

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
	printf("-I- Dumping plain text after AES decryption...\n\r");
	/* Print the entire buffer, even past the nul characters if any */
	for (i = 0; i < DATA_LEN_INBYTE; i++) {
		c = ((const uint8_t*)msg_decrypted)[i];
		if (isprint(c))
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
	uint8_t chk_box[5];
	printf("\n\rAES Menu:\n\r");
	printf("Press [0|1|2|3|4] to set the Mode of Operation\n\r");
	chk_box[0] = (op_mode == AES_MR_OPMOD_ECB) ? 'X' : ' ';
	chk_box[1] = (op_mode == AES_MR_OPMOD_CBC) ? 'X' : ' ';
	chk_box[2] = (op_mode == AES_MR_OPMOD_OFB) ? 'X' : ' ';
	chk_box[3] = (op_mode == AES_MR_OPMOD_CFB) ? 'X' : ' ';
	chk_box[4] = (op_mode == AES_MR_OPMOD_CTR) ? 'X' : ' ';
	printf("   0: Electronic Code Book    [%c]\n\r", chk_box[0]);
	printf("   1: Cipher Block Chaining   [%c]\n\r", chk_box[1]);
	printf("   2: Output Feedback         [%c]\n\r", chk_box[2]);
	printf("   3: Cipher Feedback         [%c]\n\r", chk_box[3]);
	printf("   4: 16-bit internal Counter [%c]\n\r", chk_box[4]);
	printf("Press [5|6|7] to select key size\n\r");
	chk_box[0] = (key_id == AES_MR_KEYSIZE_AES128) ? 'X' : ' ';
	chk_box[1] = (key_id == AES_MR_KEYSIZE_AES192) ? 'X' : ' ';
	chk_box[2] = (key_id == AES_MR_KEYSIZE_AES256) ? 'X' : ' ';
	printf("   5: 128 bits[%c]  6: 192 bits[%c]  7: 256 bits[%c]\n\r",
		chk_box[0], chk_box[1], chk_box[2]);
	printf("Press [m|a|d] to set Start Mode \n\r");
	chk_box[0] = (start_mode == AES_MR_SMOD_MANUAL_START) ? 'X' : ' ';
	chk_box[1] = (start_mode == AES_MR_SMOD_AUTO_START) ? 'X' : ' ';
	chk_box[2] = (start_mode == AES_MR_SMOD_IDATAR0_START) ? 'X' : ' ';
	printf("   m: MANUAL_START[%c]  a: AUTO_START[%c]  d: DMA[%c]\n\r",
		chk_box[0], chk_box[1], chk_box[2]);
	printf("   p: Begin the encryption/decryption process\n\r");
	printf("   h: Display this menu\n\r");
	printf("\n\r");
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief AES Application entry point.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t user_key;

	wdt_disable();
	board_cfg_console(0);

	/* Output example information */
	printf("\r\n\r\n\r\n");
	printf("-- AES Example " SOFTPACK_VERSION " --\n\r") ;
	printf("-- " BOARD_NAME "\n\r");
	printf("-- Compiled: " __DATE__ " " __TIME__ " --\n\r");

	/* Enable peripheral clock */
	pmc_enable_peripheral(ID_AES);
	/* Enable peripheral interrupt */
	aic_set_source_vector(ID_AES, handle_aes_irq);
	aic_enable(ID_AES);

	/* Display menu */
	op_mode = AES_MR_OPMOD_ECB;
	key_id = AES_MR_KEYSIZE_AES128;
	key_byte_len = 128 / 8;
	start_mode = AES_MR_SMOD_MANUAL_START;
	display_menu();

	while (true) {
		user_key = tolower(console_get_char());
		switch (user_key) {
		case '0': case '1': case '2': case '3': case '4':
			op_mode = (user_key - '0') << AES_MR_OPMOD_Pos;
			display_menu();
			break;
		case '5': case '6': case '7':
			key_byte_len = (user_key - '5' + 2) * 8;
			key_id = (user_key - '5') << AES_MR_KEYSIZE_Pos;
			display_menu();
			break;
		case 'm':
		case 'a':
		case 'd':
			start_mode = user_key == 'a' ? AES_MR_SMOD_AUTO_START :
				   (user_key == 'd' ? AES_MR_SMOD_IDATAR0_START :
						      AES_MR_SMOD_MANUAL_START);
		case 'h':
			display_menu();
			break;
		case 'p':
			start_aes();
			break;
		}
	}

	/* This code is never reached */
}
