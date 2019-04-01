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
 * GCM/XTS modes. Programmable key mode with processing using with or without DMA
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

#define DATA_LEN_INBYTE	640
#define DATA_LEN_INWORD	(DATA_LEN_INBYTE / 4)

#define AES_VECTOR_SIZE   16

#define AES_GCM_IV_SIZE1   IV_LENGTH_96
#define AES_GCM_IV_SIZE2   16

#define AES_VECTOR_0		0x63a3d1db
#define AES_VECTOR_1		0xb4b72460
#define AES_VECTOR_2		0x6f7dda02
#define AES_VECTOR_3		0x11223344

/* Effective AAD Size */
#define AES_AAD_SIZE		20

#define AES_TWEAKIN_0		0x12345678
#define AES_TWEAKIN_1		0x11223344
#define AES_TWEAKIN_2		0x11122233
#define AES_TWEAKIN_3		0x11112222

#define AES_KEY_0		0xcf76d4f8
#define AES_KEY_1		0x6cea46d6
#define AES_KEY_2		0x1ccb8423
#define AES_KEY_3		0x5d19d627
#define AES_KEY_4		0xf3a9f1fe
#define AES_KEY_5		0x218d9c7b
#define AES_KEY_6		0xf8219ca7
#define AES_KEY_7		0x89d290cb

#ifdef CONFIG_HAVE_AES_GCM
#define AES_KEY2_0	0xa393d4ff
#define AES_KEY2_1	0x4cdf46de
#define AES_KEY2_2	0x1ccb8423
#define AES_KEY2_3	0x419d6250
#define AES_KEY2_4	0xfea9f1f3
#define AES_KEY2_5	0x318d2c71
#define AES_KEY2_6	0xf8ee0ca2
#define AES_KEY2_7	0xa9f290c3
#endif
static struct _aesd_desc aesd;

ALIGNED(16) const char aes_aad[20] = {
	0xa2,0x59,0xd8,0x7b,0x21,0x1a,0x96,0x47,0x0e,0x38,0x3b,0x82,
	0x50,0xb6,0xe8,0x9f,0xd3,0x61,0xba,0x82 };

/* This is the plain data for encrypt, it is necessary, that the length of the encrypted data is at least as large as the AES cipher block size, but it does not have to be a multiple of the cipher block size.*/

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

CACHE_ALIGNED static uint32_t msg_in_clear[DATA_LEN_INWORD];
CACHE_ALIGNED static uint32_t msg_encrypted[DATA_LEN_INWORD];
CACHE_ALIGNED static uint32_t msg_decrypted[DATA_LEN_INWORD];
CACHE_ALIGNED static uint32_t msg_aad[DATA_LEN_INWORD];

#ifdef CONFIG_HAVE_AES_GCM
CACHE_ALIGNED static uint32_t buffer[8];
#endif

static volatile bool dma_rd_complete = false;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
static int _aes_callback(void* args, void* arg2)
{
	/* TODO for user application */
	return 0;
}

/**
 * \brief Encrypt or decrypt the specified data buffer.
 * In this sample code, the size of data buffers is hardcoded.
 * \param encrypt  True to encrypt, false to decrypt
 * \param in  Input buffer
 * \param out  Target buffer receiving processed data
 * \param aad  Buffer for GCM additional authenticated data
 */
static void process_buffer(bool encrypt,
						   uint32_t *in,
						   uint32_t *out,
						   uint32_t *aad)
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
	struct _buffer buf_aad = {
		.data = (uint8_t*)aad,
		.size = 0,
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
	if (aesd.cfg.mode != AESD_MODE_GCM)
		aesd.cfg.vsize = AES_VECTOR_SIZE;

	aesd.cfg.vector[0] = AES_VECTOR_0;
	aesd.cfg.vector[1] = AES_VECTOR_1;
	aesd.cfg.vector[2] = AES_VECTOR_2;
	aesd.cfg.vector[3] = AES_VECTOR_3;

#ifdef CONFIG_HAVE_AES_GCM
	aesd.cfg.key2[0] = AES_KEY2_0;
	aesd.cfg.key2[1] = AES_KEY2_1;
	aesd.cfg.key2[2] = AES_KEY2_2;
	aesd.cfg.key2[3] = AES_KEY2_3;
	aesd.cfg.key2[4] = AES_KEY2_4;
	aesd.cfg.key2[5] = AES_KEY2_5;
	aesd.cfg.key2[6] = AES_KEY2_6;
	aesd.cfg.key2[7] = AES_KEY2_7;
#endif

#ifdef CONFIG_HAVE_AES_XTS
	aesd.cfg.tweakin[0] = AES_TWEAKIN_0;
	aesd.cfg.tweakin[1] = AES_TWEAKIN_1;
	aesd.cfg.tweakin[2] = AES_TWEAKIN_2;
	aesd.cfg.tweakin[3] = AES_TWEAKIN_3;
#endif
	callback_set(&_cb, _aes_callback, NULL);
	aesd_transfer(&aesd, &buf_in, &buf_out, &buf_aad, &_cb);
}

/**
 * \brief Start AES process.
 */
static bool start_aes(bool full_test)
{
	uint32_t i;
	uint8_t c;

	memcpy((char*)msg_in_clear, example_text, sizeof(example_text));
	memset(msg_encrypted, 0xff, DATA_LEN_INBYTE);
	memset(msg_decrypted, 0xff, DATA_LEN_INBYTE);
#ifdef CONFIG_HAVE_AES_GCM
	if (aesd.cfg.mode == AESD_MODE_GCM) {
		memset(msg_aad, 0, DATA_LEN_INBYTE);
		memcpy((char*)msg_aad, aes_aad, sizeof(aes_aad));
		aesd.buffer = (uint8_t*)buffer;
	}
#endif
	if (full_test) {
		switch(aesd.cfg.mode) {
		case AESD_MODE_ECB:
			printf("ECB ");
			break;
		case AESD_MODE_CBC:
			printf("CBC ");
			break;
		case AESD_MODE_OFB:
			printf("OFB ");
			break;
		case AESD_MODE_CFB:
			switch (aesd.cfg.cfbs){
			case AESD_CFBS_128:
				printf("CFBS_128 ");
				break;
			case AESD_CFBS_64:
				printf("CFBS_64 ");
				break;
			case AESD_CFBS_32:
				printf("CFBS_32 ");
				break;
			case AESD_CFBS_16:
				printf("CFBS_16 ");
				break;
			case AESD_CFBS_8:
				printf("CFBS_8 ");
				break;
			}
			break;
		case AESD_MODE_CTR:
			printf("CTR ");
			break;
		case AESD_MODE_GCM:
			printf("GCM ");
			printf("iv_size =%d ",aesd.cfg.vsize);
			break;
		case AESD_MODE_XTS:
			printf("XTS ");
			break;
		}
		switch (aesd.cfg.key_size) {
		case AESD_AES128:
			printf("key_size =128 ");
			break;
		case AESD_AES192:
			printf("key_size =192 ");
			break;
		case AESD_AES256:
			printf("key_size =256 ");
			break;
		}
		switch (aesd.cfg.transfer_mode) {
		case AESD_TRANS_POLLING_MANUAL:
			printf("manually ");
			break;
		case AESD_TRANS_POLLING_AUTO:
			printf("auto start ");
			break;
		case AESD_TRANS_DMA:
			printf("dma ");
			break;
		}
	}

	process_buffer(true, msg_in_clear, msg_encrypted, msg_aad);
	if (!full_test) {
		printf("-I- Dumping the encrypted message...");
		for (i = 0; i < DATA_LEN_INWORD; i++) {
			if (i % 8 == 0)
				printf("\n\r%03lx:    ", i * 4);
			printf(" %08lx", msg_encrypted[i]);
		}
		printf("\n\r");
	}

	process_buffer(false, msg_encrypted, msg_decrypted, msg_aad);

	if (!full_test) {
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
	if (memcmp(msg_in_clear, msg_decrypted, DATA_LEN_INWORD) != 0) {
		printf("failed\r\n");
		return false;
	}
	printf("passed\r\n");
	return true;
}

/**
 * \brief Start AES process.
 */
static void full_aes_test(void)
{
	for (aesd.cfg.transfer_mode = AESD_TRANS_POLLING_MANUAL;
			aesd.cfg.transfer_mode <= AESD_TRANS_DMA;
			aesd.cfg.transfer_mode++) {

		for (aesd.cfg.key_size = AESD_AES128;
			 aesd.cfg.key_size <= AESD_AES256;
			 aesd.cfg.key_size++) {
			for (aesd.cfg.mode = AESD_MODE_ECB;; aesd.cfg.mode++) {
				if (aesd.cfg.mode > AESD_MODE_XTS)
					break;
#if !defined CONFIG_HAVE_AES_GCM
				if (aesd.cfg.mode == AESD_MODE_GCM)
					continue;
#endif
#if !defined CONFIG_HAVE_AES_XTS
				if (aesd.cfg.mode == AESD_MODE_XTS)
					continue;
#endif

				aesd.cfg.cfbs = AESD_CFBS_128;
#ifdef CONFIG_HAVE_AES_GCM
				if (aesd.cfg.mode == AESD_MODE_GCM) {
					for (uint8_t i = 0; i < 2; i++) {
						if (i == 0)
							aesd.cfg.vsize = AES_GCM_IV_SIZE1;
						else
							aesd.cfg.vsize = AES_GCM_IV_SIZE2;
						start_aes(true);
					}
				}
#endif

				if (aesd.cfg.mode == AESD_MODE_CFB) {
					for (aesd.cfg.cfbs = AESD_CFBS_128;
						 aesd.cfg.cfbs <= AESD_CFBS_8;
						 aesd.cfg.cfbs++) {
						if (!start_aes(true)) {
							printf("TEST FAILED !\r\n");
							return;
						};
					}
				} else {
					if (aesd.cfg.mode != AESD_MODE_GCM) {
						start_aes(true);
					}
				}
			}
		}
	}
	printf("TEST SUCCESS !\r\n");
}

/**
 * \brief Display main menu.
 */
static void display_menu(void)
{
	uint8_t chk_box[7];
	printf("\n\rAES Menu:\n\r");
	printf("Press [0|1|2|3|4");
#ifdef CONFIG_HAVE_AES_GCM
	printf("|5");
#endif
#ifdef CONFIG_HAVE_AES_XTS
	printf("|6");
#endif
	printf("] to set the Mode of Operation\n\r");
	chk_box[0] = (aesd.cfg.mode == AESD_MODE_ECB) ? 'X' : ' ';
	chk_box[1] = (aesd.cfg.mode == AESD_MODE_CBC) ? 'X' : ' ';
	chk_box[2] = (aesd.cfg.mode == AESD_MODE_OFB) ? 'X' : ' ';
	chk_box[3] = (aesd.cfg.mode == AESD_MODE_CFB) ? 'X' : ' ';
	chk_box[4] = (aesd.cfg.mode == AESD_MODE_CTR) ? 'X' : ' ';
#ifdef CONFIG_HAVE_AES_GCM
	chk_box[5] = (aesd.cfg.mode == AESD_MODE_GCM) ? 'X' : ' ';
#endif
#ifdef CONFIG_HAVE_AES_XTS
	chk_box[6] = (aesd.cfg.mode == AESD_MODE_XTS) ? 'X' : ' ';
#endif

	printf("   0: Electronic Code Book    [%c]\n\r", chk_box[0]);
	printf("   1: Cipher Block Chaining   [%c]\n\r", chk_box[1]);
	printf("   2: Output Feedback         [%c]\n\r", chk_box[2]);
	printf("   3: Cipher Feedback         [%c]\n\r", chk_box[3]);
	printf("   4: 16-bit internal Counter [%c]\n\r", chk_box[4]);
#ifdef CONFIG_HAVE_AES_GCM
	printf("   5: Galois/Counter Mode     [%c]\n\r", chk_box[5]);
#endif
#ifdef CONFIG_HAVE_AES_XTS
	printf("   6: XEX-Based Tweaked-Code  [%c]\n\r", chk_box[6]);
#endif
	printf("Press [7|8|9] to select key size\n\r");
	chk_box[0] = (aesd.cfg.key_size == AESD_AES128) ? 'X' : ' ';
	chk_box[1] = (aesd.cfg.key_size == AESD_AES192) ? 'X' : ' ';
	chk_box[2] = (aesd.cfg.key_size == AESD_AES256) ? 'X' : ' ';
	printf("   7: 128 bits[%c]  8: 192 bits[%c]  9: 256 bits[%c]\n\r",
		chk_box[0], chk_box[1], chk_box[2]);
	printf("Press [m|a|d] to set Start Mode \n\r");
	chk_box[0] = (aesd.cfg.transfer_mode == AESD_TRANS_POLLING_MANUAL) ? 'X' : ' ';
	chk_box[1] = (aesd.cfg.transfer_mode == AESD_TRANS_POLLING_AUTO) ? 'X' : ' ';
	chk_box[2] = (aesd.cfg.transfer_mode == AESD_TRANS_DMA) ? 'X' : ' ';
	printf("   m: MANUAL_START[%c]  a: AUTO_START[%c]  d: DMA[%c]\n\r",
		chk_box[0], chk_box[1], chk_box[2]);
	printf("   p: Begin the encryption/decryption process\n\r");
	printf("   f: Full test for all AES mode\n\r");
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

#ifdef CONFIG_HAVE_AES_GCM
static void set_iv_size(void)
{
	uint8_t user_key;
	uint8_t chk_box[2];

	printf("Press [0|1] to select iv size\n\r");
	chk_box[0] = (aesd.cfg.vsize == AES_GCM_IV_SIZE1) ? 'X' : ' ';
	chk_box[1] = (aesd.cfg.vsize == AES_GCM_IV_SIZE2) ? 'X' : ' ';
	printf("   0: iv size == 96 bits [%c]\n\r", chk_box[0]);
	printf("   1: iv size != 96 bits [%c]\n\r", chk_box[1]);
	printf("\n\r");
	while (true) {
		user_key = tolower(console_get_char());
		if (user_key == '0') {
			aesd.cfg.vsize = AES_GCM_IV_SIZE1;
			break;
		} else {
			aesd.cfg.vsize = AES_GCM_IV_SIZE2;
			break;
		}
	}
}
#endif

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
			aesd.cfg.aadsize = 0;
			display_menu();
			if (aesd.cfg.mode == AESD_MODE_CFB) {
				display_cipher_menu();
				set_cipher_size();
				display_menu();
			}
			break;
#ifdef CONFIG_HAVE_AES_GCM
		case '5':
			set_iv_size();
			aesd.cfg.mode = AESD_MODE_GCM;
			aesd.cfg.aadsize = AES_AAD_SIZE;
			aesd.cfg.entag = true;
			display_menu();
			break;
#endif
#ifdef CONFIG_HAVE_AES_XTS
		case '6':
			aesd.cfg.mode = AESD_MODE_XTS;
			aesd.cfg.entag = false;
			display_menu();
			break;
#endif
		case '7': case '8': case '9':
			aesd.cfg.key_size = (enum _aesd_key_size)(user_key - '7');
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
			start_aes(false);
			break;
		case 'f':
			full_aes_test();
			aesd.cfg.transfer_mode = AESD_TRANS_POLLING_MANUAL;
			aesd.cfg.key_size = AESD_AES128;
			aesd.cfg.mode = AESD_MODE_ECB;
			aesd.cfg.cfbs = AESD_CFBS_128;
			break;
		}
	}

	/* This code is never reached */
}
