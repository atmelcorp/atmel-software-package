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
 * This package can be used with SAMA5DX-XULT, SAMA5DX-EK.
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
 * - aes.h
 * - aesd.c
 * - aesd.h */

/** \file
 *
 * This file contains all the specific code for the AES
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"
#include "callback.h"
#include "chip.h"
#include "crypto/aes.h"
#include "crypto/aesd.h"
#include "dma/dma.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define DATA_LEN_INBYTE		640
#define DATA_LEN_INWORD		(DATA_LEN_INBYTE / 4)

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

static struct _aesd_desc aesd;

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

/* Buffers hereafter will receive data transferred by the DMA to/from the
 * peripheral. The data cache won't notice this memory update, hence we'll have
 * to clean/invalidate the related cache lines.
 * May the buffers fail to be aligned on cache lines, cache clean operations
 * would then occur on the shared lines. Which would be prone to data conflicts
 * between these buffers and the variables placed on a same cache line.
 * Alternatively, we might consider allocating these buffers from a
 * non-cacheable memory region. */
CACHE_ALIGNED static uint32_t msg_in_clear[DATA_LEN_INWORD];
CACHE_ALIGNED static uint32_t msg_encrypted[DATA_LEN_INWORD];
CACHE_ALIGNED static uint32_t msg_decrypted[DATA_LEN_INWORD];

static volatile bool dma_rd_complete = false;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
static int _aes_callback(void* args, void* arg2)
{
	printf("-I- transfer completed\r\n");
	return 0;
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
	struct _callback _cb;
	struct _buffer buf_in = {
		.data = (uint8_t*)in,
		.size = DATA_LEN_INBYTE,
	};
	struct _buffer buf_out = {
		.data = (uint8_t*)out,
		.size = DATA_LEN_INBYTE,
	};

	/* Perform a software-triggered hardware reset of the AES interface */
	aesd.cfg.encrypt = encrypt;
	aesd.cfg.key[0] = AES_KEY_0;
	aesd.cfg.key[1] = AES_KEY_1;
	aesd.cfg.key[2] = AES_KEY_2;
	aesd.cfg.key[3] = AES_KEY_3;
	aesd.cfg.key[4] = AES_KEY_4;
	aesd.cfg.key[5] = AES_KEY_5;
	aesd.cfg.key[6] = AES_KEY_6;
	aesd.cfg.key[7] = AES_KEY_7;

	aesd.cfg.vector[0] = AES_VECTOR_0;
	aesd.cfg.vector[1] = AES_VECTOR_1;
	aesd.cfg.vector[2] = AES_VECTOR_2;
	aesd.cfg.vector[3] = AES_VECTOR_3;

	aesd_configure_mode(&aesd);
	callback_set(&_cb, _aes_callback, NULL);
	aesd_transfer(&aesd, &buf_in, &buf_out, &_cb);
}

/**
 * \brief Start AES process.
 */
static void start_aes(void)
{
	uint32_t i;
	uint8_t c;

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
	chk_box[0] = (aesd.cfg.mode == AESD_MODE_ECB) ? 'X' : ' ';
	chk_box[1] = (aesd.cfg.mode == AESD_MODE_CBC) ? 'X' : ' ';
	chk_box[2] = (aesd.cfg.mode == AESD_MODE_OFB) ? 'X' : ' ';
	chk_box[3] = (aesd.cfg.mode == AESD_MODE_CFB) ? 'X' : ' ';
	chk_box[4] = (aesd.cfg.mode == AESD_MODE_CTR) ? 'X' : ' ';

	printf("   0: Electronic Code Book    [%c]\n\r", chk_box[0]);
	printf("   1: Cipher Block Chaining   [%c]\n\r", chk_box[1]);
	printf("   2: Output Feedback         [%c]\n\r", chk_box[2]);
	printf("   3: Cipher Feedback         [%c]\n\r", chk_box[3]);
	printf("   4: 16-bit internal Counter [%c]\n\r", chk_box[4]);
	printf("Press [5|6|7] to select key size\n\r");
	chk_box[0] = (aesd.cfg.key_size == AESD_AES128) ? 'X' : ' ';
	chk_box[1] = (aesd.cfg.key_size == AESD_AES192) ? 'X' : ' ';
	chk_box[2] = (aesd.cfg.key_size == AESD_AES256) ? 'X' : ' ';

	printf("   5: 128 bits[%c]  6: 192 bits[%c]  7: 256 bits[%c]\n\r",
		chk_box[0], chk_box[1], chk_box[2]);
	printf("Press [m|a|d] to set Start Mode \n\r");
	chk_box[0] = (aesd.cfg.transfer_mode == AESD_TRANS_POLLING_MANUAL) ? 'X' : ' ';
	chk_box[1] = (aesd.cfg.transfer_mode == AESD_TRANS_POLLING_AUTO) ? 'X' : ' ';
	chk_box[2] = (aesd.cfg.transfer_mode == AESD_TRANS_DMA) ? 'X' : ' ';
	printf("   m: MANUAL_START[%c]  a: AUTO_START[%c]  d: DMA[%c]\n\r",
		chk_box[0], chk_box[1], chk_box[2]);
	printf("   p: Begin the encryption/decryption process\n\r");
	printf("   h: Display this menu\n\r");
	printf("\n\r");
}

/**
 * \brief Display sub menu for CFB mode.
 */
static void display_cipher_menu(void)
{
	uint8_t chk_box[5];
	printf("\n\rAES Cipher Feedback Menu:\n\r");
	printf("Press [0|1|2|3|4] to set the cipher data size\n\r");
	chk_box[0] = (aesd.cfg.cfbs == AESD_CFBS_128) ? 'X' : ' ';
	chk_box[1] = (aesd.cfg.cfbs == AESD_CFBS_64) ? 'X' : ' ';
	chk_box[2] = (aesd.cfg.cfbs == AESD_CFBS_32) ? 'X' : ' ';
	chk_box[3] = (aesd.cfg.cfbs == AESD_CFBS_16) ? 'X' : ' ';
	chk_box[4] = (aesd.cfg.cfbs == AESD_CFBS_8) ? 'X' : ' ';
	printf("   0: 128 bits [%c]\n\r", chk_box[0]);
	printf("   1: 64 bits [%c]\n\r", chk_box[1]);
	printf("   2: 32 bits [%c]\n\r", chk_box[2]);
	printf("   3: 16 bits [%c]\n\r", chk_box[3]);
	printf("   4: 8 bits [%c]\n\r", chk_box[4]);
	printf("\n\r");
}

/**
 * \brief Set cipher data size.
 */
static void set_cipher_size(void)
{
	uint8_t user_key;
	while (true) {
		user_key = tolower(console_get_char());
		if (user_key >= '0' && user_key <= '4') {
			aesd.cfg.cfbs = (enum _aesd_cipher_size)(user_key - '0');
			break;
		}
	}
	display_cipher_menu();
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

	/* Output example information */
	console_example_info("AES Example");

	aesd_init(&aesd);

	/* Display menu */
	aesd.cfg.mode = AESD_MODE_ECB;
	aesd.cfg.key_size = AESD_AES128;
	aesd.cfg.transfer_mode = AESD_TRANS_POLLING_MANUAL;
	display_menu();

	while (true) {
		user_key = tolower(console_get_char());
		switch (user_key) {
		case '0': case '1': case '2': case '3': case '4':
			aesd.cfg.mode = (enum _aesd_mode)(user_key - '0');
			display_menu();
			if (aesd.cfg.mode == AESD_MODE_CFB) {
				display_cipher_menu();
				set_cipher_size();
				display_menu();
			}
			break;
		case '5': case '6': case '7':
			aesd.cfg.key_size = (enum _aesd_key_size)(user_key - '5');
			display_menu();
			break;
		case 'm':
		case 'a':
		case 'd':
			aesd.cfg.transfer_mode = user_key == 'a' ? AESD_TRANS_POLLING_AUTO :
						(user_key == 'd' ? AESD_TRANS_DMA :
						AESD_TRANS_POLLING_MANUAL);
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
