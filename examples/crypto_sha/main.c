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
 * \page sha Secure Hash Algorithm Example
 *
 * \section Purpose
 *
 * This example demonstrates the Secure Hash Algorithm (SHA) peripheral
 * available on the Atmel SAMA5D microcontrollers. It takes FIPS-compliant
 * tests (American Federal Information Processing Standard, Publication 180-2)
 * and checks them against the known answers.
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
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="http://www.iar.com/website1/1.0.1.0/78/1/">
 *    IAR EWARM User and reference guides</a>, depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
 *     -- SHA Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     SHA menu:
 *     Press [0|1|2|3|4] to set SHA Algorithm
 *     Press [o|t|l] to set one/multi-block or long message
 *     Press [m|a|d] to set Start Mode
 *        p: Start hash algorithm process
 *        h: Display this menu
 *    \endcode
 * -# Press one of the keys listed in the menu to perform the corresponding action.
 *
 * \section References
 * - sha/main.c
 * - sha.c
 * - sha.h
 */

/**
 * \file
 *
 * This file contains all the specific code for the SHA example.
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
#include "chip.h"
#include "crypto/shad.h"
#include "crypto/sha.h"
#include "intmath.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "serial/console.h"
#include "swab.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* Buffer size for each SHA transfer, size should be multiple of block size
   (block size: 64 for SHA_1/SHA_256/SHA_224, 128 for SHA_384/SHA_512) */
#define BUF_SIZE         LEN_MSG_LONG

#define SHA_ONE_BLOCK    0
#define SHA_MULTI_BLOCK  1
#define SHA_LONG_MESSAGE 2

#define MAX_DIGEST_SIZE_INWORD  (16)

#define LEN_MSG_0    3
#define LEN_MSG_1    56
#define LEN_MSG_2    112
#define LEN_MSG_LONG 1000000

#define SHA_UPDATE_LEN (128 * 1024) /* buffer length when spliting long message */

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/* A.1  SHA-1 Example (One-Block Message)
 * B.1  SHA-256 Example (One-Block Message)
 * C.1  SHA-512 Example (One-Block Message)
 * D.1  SHA-384 Example (One-Block Message)
 *      SHA-224 Example (One-Block Message)
 * Let the message, M, be the 24-bit ( l = 24) ASCII string  "abc ", which is
 * equivalent to the following binary string: 01100001 01100010 01100011.
 */
static const uint8_t msg0[LEN_MSG_0] = "abc";

/* A.2  SHA-1 Example (Multi-Block Message)
 * B.2  SHA-256 Example (Multi-Block Message)
 *      SHA-224 Example (Multi-Block Message)
 * Let the message, M, be the 448-bit ( l = 448) ASCII string
 * "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq".
 */
static const uint8_t msg1[LEN_MSG_1] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

/* C.2  SHA-512 Example (Multi-Block Message)
 * D.2  SHA-384 Example (Multi-Block Message)
 * Let the message, M, be the 896-bit ( l = 896) ASCII string
 * "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklm
 *  nopqklmnopqrlmnopqrsmnopqrstnopqrstu".
 */
static const uint8_t msg2[LEN_MSG_2] = "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu";

/* A.3  SHA-1 Example (Long Message)
 * B.3  SHA-256 Example (Long Message)
 * C.3  SHA-512 Example (Long Message)
 * D.3  SHA-384 Example (Long Message)
 *      SHA-224 Example (Long Message)
 * Let the message M be the binary-coded form of the ASCII string which consists
 * in 1,000,000 repetitions of the character "a".
 */
static const uint8_t msg_long_pattern = 'a';

/* In Federal Information Processing Standards Publication 180-2
 * (+ Change Notice to include SHA-224) SECURE HASH STANDARD
 * APPENDIX A: SHA-256 EXAMPLES
 * A.1 SHA-1 Example (One-Block Message) The resulting 160-bit message digest
 * A.2 SHA-1 Example (Multi-Block Message) The resulting 160-bit message digest
 * A.3 SHA-1 Example (Long Message) The resulting 160-bit message digest
 */
static const uint32_t ref_digests_one[3][5] = {
	{ 0xa9993e36, 0x4706816a, 0xba3e2571, 0x7850c26c, 0x9cd0d89d },
	{ 0x84983e44, 0x1c3bd26e, 0xbaae4aa1, 0xf95129e5, 0xe54670f1 },
	{ 0x34aa973c, 0xd4c4daa4, 0xf61eeb2b, 0xdbad2731, 0x6534016f }
};

/* In Federal Information Processing Standards Publication 180-2
 * (+ Change Notice to include SHA-224) SECURE HASH STANDARD
 * APPENDIX B: SHA-256 EXAMPLES
 * B.1  SHA-256 Example (One-Block Message) The resulting 256-bit message digest
 * B.2  SHA-256 Example (Multi-Block Message) The resulting 256-bit message digest
 * B.3  SHA-256 Example (Long Message) The resulting 256-bit message digest
 */
static const uint32_t ref_digests_256[3][8] = {
	{ 0xba7816bf, 0x8f01cfea, 0x414140de, 0x5dae2223,
	  0xb00361a3, 0x96177a9c, 0xb410ff61, 0xf20015ad },
	{ 0x248d6a61, 0xd20638b8, 0xe5c02693, 0x0c3e6039,
	  0xa33ce459, 0x64ff2167, 0xf6ecedd4, 0x19db06c1 },
	{ 0xcdc76e5c, 0x9914fb92, 0x81a1c7e2, 0x84d73e67,
	  0xf1809a48, 0xa497200e, 0x046d39cc, 0xc7112cd0 }
};

/* In Federal Information Processing Standards Publication 180-2
 * (+ Change Notice to include SHA-224) SECURE HASH STANDARD
 * APPENDIX D: SHA-384 EXAMPLES
 * D.1  SHA-384 Example (One-Block Message) The resulting 384-bit message digest
 * D.2  SHA-384 Example (Multi-Block Message) The resulting 384-bit message digest
 * D.3  SHA-384 Example (Long Message) The resulting 384-bit message digest
 */
static const uint32_t ref_digests_384[3][12] = {
	{ 0xcb00753f, 0x45a35e8b, 0xb5a03d69, 0x9ac65007,
	  0x272c32ab, 0x0eded163, 0x1a8b605a, 0x43ff5bed,
	  0x8086072b, 0xa1e7cc23, 0x58baeca1, 0x34c825a7 },
	{ 0x09330c33, 0xf71147e8, 0x3d192fc7, 0x82cd1b47,
	  0x53111b17, 0x3b3b05d2, 0x2fa08086, 0xe3b0f712,
	  0xfcc7c71a, 0x557e2db9, 0x66c3e9fa, 0x91746039 },
	{ 0x9d0e1809, 0x716474cb, 0x086e834e, 0x310a4a1c,
	  0xed149e9c, 0x00f24852, 0x7972cec5, 0x704c2a5b,
	  0x07b8b3dc, 0x38ecc4eb, 0xae97ddd8, 0x7f3d8985 }
};

/* In Federal Information Processing Standards Publication 180-2
 * (+ Change Notice to include SHA-224) SECURE HASH STANDARD
 * APPENDIX C: SHA-512 EXAMPLES
 * C.1  SHA-512 Example (One-Block Message)  The resulting 512-bit message digest
 * C.2  SHA-512 Example (Multi-Block Message) The resulting 512-bit message digest
 * C.3  SHA-512 Example (Long Message) The resulting 512-bit message digest
 */
static const uint32_t ref_digests_512[3][16] = {
	{ 0xddaf35a1, 0x93617aba, 0xcc417349, 0xae204131,
	  0x12e6fa4e, 0x89a97ea2, 0x0a9eeee6, 0x4b55d39a,
	  0x2192992a, 0x274fc1a8, 0x36ba3c23, 0xa3feebbd,
	  0x454d4423, 0x643ce80e, 0x2a9ac94f, 0xa54ca49f },
	{ 0x8e959b75, 0xdae313da, 0x8cf4f728, 0x14fc143f,
	  0x8f7779c6, 0xeb9f7fa1, 0x7299aead, 0xb6889018,
	  0x501d289e, 0x4900f7e4, 0x331b99de, 0xc4b5433a,
	  0xc7d329ee, 0xb6dd2654, 0x5e96e55b, 0x874be909 },
	{ 0xe718483d, 0x0ce76964, 0x4e2e42c7, 0xbc15b463,
	  0x8e1f98b1, 0x3b204428, 0x5632a803, 0xafa973eb,
	  0xde0ff244, 0x877ea60a, 0x4cb0432c, 0xe577c31b,
	  0xeb009c5c, 0x2c49aa2e, 0x4eadb217, 0xad8cc09b }
};

/* In Federal Information Processing Standards Publication 180-2
 * SHA-224 Specification
 * APPENDIX C: SHA-512 EXAMPLES
 * 1. SHA-224 Example (One-Block Message)  The resulting 224-bit message digest
 * 2.  SHA-224 Example (Multi-Block Message) The resulting 224-bit message digest
 * 3. SHA-224 Example (Long Message) The resulting 224-bit message digest
 */
static const uint32_t ref_digests_224[3][7] = {
	{ 0x23097d22, 0x3405d822, 0x8642a477, 0xbda255b3, 0x2aadbce4,
	  0xbda0b3f7, 0xe36c9da7 },
	{ 0x75388b16, 0x512776cc, 0x5dba5da1, 0xfd890150, 0xb0c6455c,
	  0xb4f58b19, 0x52522525 },
	{ 0x20794655, 0x980c91d8, 0xbbb4c1ea, 0x97618a4b, 0xf03f4258,
	  0x1948b2ee, 0x4ee7ad67 }
};

CACHE_ALIGNED_DDR static uint8_t message[BUF_SIZE];

static uint32_t digest[MAX_DIGEST_SIZE_INWORD];
static uint32_t block_mode;

/* shad instance */
static struct _shad_desc shad;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Start SHA process.
 */
static void start_sha(void)
{
	uint32_t rc = 0, i, val, ref = 0;
	uint32_t len;
	int output_size = shad_get_output_size(shad.cfg.algo);

	if (output_size < 0) {
		printf("-F- Unsupported SHA algorithm\r\n");
		return;
	}

	memset(digest, 0, ARRAY_SIZE(digest));

	if (block_mode == SHA_ONE_BLOCK) {
		len = LEN_MSG_0;
		memcpy ((uint8_t*)message, msg0, len);
	} else if (block_mode == SHA_MULTI_BLOCK) {
		if (shad.cfg.algo == ALGO_SHA_384 ||
		    shad.cfg.algo == ALGO_SHA_512) {
			len = LEN_MSG_2;
			memcpy ((uint8_t*)message, msg2, len);
		} else {
			len = LEN_MSG_1;
			memcpy ((uint8_t*)message, msg1, len);
		}
	} else {
		len = LEN_MSG_LONG;
		memset((uint8_t*)message, msg_long_pattern, len);
	}

	struct _buffer buf_in = {
		.data = (uint8_t*)message,
		.size = len,
	};
	struct _buffer buf_out = {
		.data = (uint8_t*)digest,
		.size = output_size,
	};
	shad_start(&shad);
	while (len) {
		buf_in.size = min_u32(len, SHA_UPDATE_LEN);

		shad_update(&shad, &buf_in, NULL);
		shad_wait_completion(&shad);

		buf_in.data += buf_in.size;
		len -= buf_in.size;
	}
	shad_finish(&shad, &buf_out, NULL);
	shad_wait_completion(&shad);

	printf("-I- Dump and compare digest result...\r\n");
	for (rc = 0, i = 0; i < output_size / 4; i++) {
		val = swab32(digest[i]);
		switch (shad.cfg.algo) {
		case ALGO_SHA_1:
			ref = ref_digests_one[block_mode][i];
			break;
		case ALGO_SHA_224:
			ref = ref_digests_224[block_mode][i];
			break;
		case ALGO_SHA_256:
			ref = ref_digests_256[block_mode][i];
			break;
		case ALGO_SHA_384:
			ref = ref_digests_384[block_mode][i];
			break;
		case ALGO_SHA_512:
			ref = ref_digests_512[block_mode][i];
			break;
		}
		if (val != ref) {
			printf(" [X]");
			rc++;
		}
		printf("   0x%08x\r\n", (unsigned)val);
	}

	if (rc)
		printf("-I- Failed to verify message digest (%u errors)\r\n",
			  (unsigned)rc);
	else
		printf("-I- Message digest result matched with the result in FIPS example\r\n");
}

/**
 * \brief Display main menu.
 */
static void display_menu(void)
{
	uint8_t chk_box[5];

	printf("\r\nSHA Menu :\r\n");
	printf("Press [0|1|2|3|4] to set SHA Algorithm \r\n");
	memset(chk_box, ' ', sizeof(chk_box));
	chk_box[shad.cfg.algo] = 'X';
	printf("   0: SHA1[%c] 1: SHA224[%c] 2: SHA256[%c] 3: SHA384[%c] 4: SHA512[%c]\r\n",
	       chk_box[0], chk_box[1], chk_box[2], chk_box[3], chk_box[4]);

	printf("Press [o|t|l] to set one/multi-block or long message \r\n");
	memset(chk_box, ' ', sizeof(chk_box));
	chk_box[block_mode] = 'X';
	printf("   o: one-block[%c] t: multi-block[%c] l: long-message[%c] \r\n",
	       chk_box[0], chk_box[1], chk_box[2]);

	printf("Press [m|a|d] to set Start Mode \r\n");
	chk_box[0] = (shad.cfg.transfer_mode == SHAD_TRANS_POLLING) ? 'X' : ' ';
	chk_box[1] = (shad.cfg.transfer_mode == SHAD_TRANS_DMA) ? 'X' : ' ';
	printf("   p: POLLING[%c] d: DMA[%c]\r\n", chk_box[0], chk_box[1]);
	printf("   s: Start hash algorithm process \r\n");
	printf("   h: Display this menu\r\n");
	printf("\r\n");
}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for SHA example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t user_key;

	/* Output example information */
	console_example_info("SHA Example");

	shad_init(&shad);

	/* Display menu */
	shad.cfg.algo = ALGO_SHA_1;
	shad.cfg.transfer_mode = SHAD_TRANS_POLLING;
	block_mode = SHA_ONE_BLOCK;

	display_menu();

	/* Handle keypresses */
	while (true) {
		user_key = tolower(console_get_char());
		switch (user_key) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
				shad.cfg.algo = (enum _shad_algo)(user_key - '0');
				display_menu();
				break;
			case 'o':
				block_mode = SHA_ONE_BLOCK;
				display_menu();
				break;
			case 't':
				block_mode = SHA_MULTI_BLOCK;
				display_menu();
				break;
			case 'l':
				block_mode = SHA_LONG_MESSAGE;
				display_menu();
				break;
			case 'p':
				shad.cfg.transfer_mode = SHAD_TRANS_POLLING;
				display_menu();
				break;
			case 'd':
				shad.cfg.transfer_mode = SHAD_TRANS_DMA;
				display_menu();
				break;
			case 'h':
				display_menu();
				break;
			case 's':
				start_sha();
				break;
		}
	}

	/* This code is never reached */
}
