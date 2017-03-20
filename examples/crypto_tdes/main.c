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
 * - SAMA5D3-EK
 * - SAMA5D3-XULT

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
 *     Press [s|t|x] to set tdesd.cfg.algorithm for encryption/decryption
 *     Press [k] set key tdesd.cfg.algorithm (three key or two key mode, no need for DES)
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
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "board.h"
#include "callback.h"
#include "chip.h"
#include "compiler.h"
#include "crypto/tdes.h"
#include "crypto/tdesd.h"
#include "mm/cache.h"
#include "serial/console.h"

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

CACHE_ALIGNED static uint32_t msg_in_clear[DATA_LEN_INWORD];
CACHE_ALIGNED static uint32_t msg_encrypted[DATA_LEN_INWORD];
CACHE_ALIGNED static uint32_t msg_decrypted[DATA_LEN_INWORD];

static uint32_t  key_mode;

/* TDES driver instance */
static struct _tdesd_desc tdesd;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static int _tdes_callback(void* arg, void* arg2)
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

	tdesd.cfg.encrypt = encrypt;
	tdesd.cfg.key_mode = (enum _tdesd_key_mode)key_mode;
	tdesd.cfg.key[0] = TDES_KEY1_0;
	tdesd.cfg.key[1] = TDES_KEY1_1;
	tdesd.cfg.key[2] = TDES_KEY2_0;
	tdesd.cfg.key[3] = TDES_KEY2_1;
	tdesd.cfg.key[4] = TDES_KEY3_0;
	tdesd.cfg.key[5] = TDES_KEY3_1;
	tdesd.cfg.vector[0] = TDES_VECTOR_0;
	tdesd.cfg.vector[1] = TDES_VECTOR_1;

	tdesd_configure_mode(&tdesd);

	callback_set(&_cb, _tdes_callback, NULL);
	tdesd_transfer(&tdesd, &buf_in, &buf_out, &_cb);
}

/**
 * \brief Start TDES process.
 */
static void start_tdes(void)
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
	printf("Press [s|t|x] to set tdesd.cfg.algorithm for encryption/decryption\n\r");
	chk_box[0] = (tdesd.cfg.algo == TDESD_ALGO_SINGLE) ? 'X' : ' ';
	chk_box[1] = (tdesd.cfg.algo == TDESD_ALGO_TRIPLE) ? 'X' : ' ';
	chk_box[2] = (tdesd.cfg.algo == TDESD_ALGO_XTEA) ? 'X' : ' ';
	printf("   s: SINGLE[%c] t: TRIPLE[%c] x: XTEA[%c]\n\r", chk_box[0],
	       chk_box[1], chk_box[2]);
	printf("Press [k] set key algorithm (three key or two key mode, no need"
	       " for DES)\n\r");
	chk_box[0] = (key_mode == TDESD_KEY_THREE) ? 'X' : ' ';
	chk_box[1] = (key_mode == TDESD_KEY_TWO) ? 'X' : ' ';
	printf("   Three key[%c] Two key[%c] \n\r", chk_box[0], chk_box[1]);
	printf("Press [0|1|2|3] to set the Mode of Operation\n\r");
	chk_box[0] = (tdesd.cfg.mode == TDESD_MODE_ECB) ? 'X' : ' ';
	chk_box[1] = (tdesd.cfg.mode == TDESD_MODE_CBC) ? 'X' : ' ';
	chk_box[2] = (tdesd.cfg.mode == TDESD_MODE_OFB) ? 'X' : ' ';
	chk_box[3] = (tdesd.cfg.mode == TDESD_MODE_CFB) ? 'X' : ' ';
	printf("   0: Electronic Code Book    [%c]\n\r", chk_box[0]);
	printf("   1: Cipher Block Chaining   [%c]\n\r", chk_box[1]);
	printf("   2: Output Feedback         [%c]\n\r", chk_box[2]);
	printf("   3: Cipher Feedback         [%c]\n\r", chk_box[3]);
	printf("Press [m|a|d] to set Start Mode\n\r");
	chk_box[0] = (tdesd.cfg.transfer_mode == TDESD_TRANS_POLLING_MANUAL) ? 'X' : ' ';
	chk_box[1] = (tdesd.cfg.transfer_mode == TDESD_TRANS_POLLING_AUTO) ? 'X' : ' ';
	chk_box[2] = (tdesd.cfg.transfer_mode == TDESD_TRANS_DMA) ? 'X' : ' ';
	printf("   m: MANUAL_START[%c] a: AUTO_START[%c] d: DMA[%c]\n\r",
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
	uint8_t chk_box[4];

	printf("\n\rAES Cipher Feedback Menu:\n\r");
	printf("Press [0|1|2|3] to set the cipher data size\n\r");
	chk_box[0] = (tdesd.cfg.cfbs == TDESD_CFBS_64) ? 'X' : ' ';
	chk_box[1] = (tdesd.cfg.cfbs == TDESD_CFBS_32) ? 'X' : ' ';
	chk_box[2] = (tdesd.cfg.cfbs == TDESD_CFBS_16) ? 'X' : ' ';
	chk_box[3] = (tdesd.cfg.cfbs == TDESD_CFBS_8) ? 'X' : ' ';
	printf("   0: 64 bits [%c]\n\r", chk_box[0]);
	printf("   1: 32 bits [%c]\n\r", chk_box[1]);
	printf("   2: 16 bits [%c]\n\r", chk_box[2]);
	printf("   3: 8 bits [%c]\n\r", chk_box[3]);
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
		if (user_key >= '0' && user_key <= '3') {
			tdesd.cfg.cfbs = (enum _tdesd_cipher_size)(user_key - '0');
			break;
		}
	}
	display_cipher_menu();
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

	tdesd_init(&tdesd);

	/* Display menu */
	tdesd.cfg.algo = TDESD_ALGO_SINGLE;
	tdesd.cfg.mode = TDESD_MODE_ECB;
	tdesd.cfg.transfer_mode = TDESD_TRANS_POLLING_MANUAL;
	tdesd.cfg.cfbs = TDESD_CFBS_64;
	key_mode = 0;

	display_menu();

	while (true) {
		user_key = tolower(console_get_char());
		switch (user_key) {
		case 's':
		case 't':
		case 'x':
			tdesd.cfg.algo = (enum _tdesd_algo)(user_key == 'x' ? 2 : user_key - 's');
			key_mode = (user_key == 'x' ? TDESD_KEY_TWO : key_mode);
			display_menu();
			break;
		case 'k':
			key_mode = (key_mode == TDESD_KEY_THREE ? TDESD_KEY_TWO : TDESD_KEY_THREE);
			if (tdesd.cfg.mode == TDESD_MODE_CFB
			    || tdesd.cfg.algo == TDESD_ALGO_XTEA)
				key_mode = TDESD_KEY_TWO;
			display_menu();
			break;
		case '0':
		case '1':
		case '2':
		case '3':
			tdesd.cfg.mode = (enum _tdesd_mode)(user_key - '0');
			key_mode = (user_key == '2') || (user_key == '3')
						? TDESD_KEY_TWO : key_mode;
			display_menu();
			if (tdesd.cfg.mode == TDESD_MODE_CFB) {
				display_cipher_menu();
				set_cipher_size();
				display_menu();
			}
			break;
		case 'm':
		case 'a':
		case 'd':
			tdesd.cfg.transfer_mode = user_key == 'a' ? TDESD_TRANS_POLLING_AUTO :
						(user_key == 'd' ? TDESD_TRANS_DMA :
						 TDESD_TRANS_POLLING_MANUAL);
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
