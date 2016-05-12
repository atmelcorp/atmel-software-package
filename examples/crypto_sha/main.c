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
 *
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

#include <stdint.h>

#include "board.h"
#include "chip.h"
#include "peripherals/sha.h"
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

#define DDR_RESERVED_LEN    0x01000000
#define MSG_MAX_LEN         0x00100000
#define DMA_DESC_MAX_COUNT  (LEN_MSG_LONG / 4 / 16 + 1)

#define SHA_1    0
#define SHA_256  1
#define SHA_384  2
#define SHA_512  3
#define SHA_224  4

#define SHA_ONE_BLOCK    0
#define SHA_MULTI_BLOCK  1
#define SHA_LONG_MESSAGE 2

#define MAX_MESSAGE_SIZE_INWORD   (64)
#define MAX_DIGEST_SIZE_INWORD    (16)

#define LEN_MSG_0      3
#define LEN_MSG_1      56
#define LEN_MSG_2      112
#define LEN_MSG_LONG   (1000000)

struct _sha_algo
{
    uint8_t block_len_words;
    uint8_t digest_len_words;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/*
 * Algorithm | Block Size | Word Size | Message Digest Size (all in bits)
 * SHA-1     | 512        | 32        | 160
 * SHA-256   | 512        | 32        | 256
 * SHA-384   | 1024       | 64        | 384
 * SHA-512   | 1024       | 64        | 512
 * SHA-224   | 512        | 32        | 224
 */
static const struct _sha_algo algo_desc[5] = {
	{ 512 / 32,	160 / 32 },
	{ 512 / 32,	256 / 32 },
	{ 1024 / 32,	384 / 32 },
	{ 1024 / 32,	512 / 32 },
	{ 512 / 32,	224 / 32 }
};

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

#ifndef VARIANT_DDRAM
static uint32_t * const message = (uint32_t*)(DDR_CS_ADDR + DDR_RESERVED_LEN);
#else
static uint32_t message[MSG_MAX_LEN];
#endif
static uint32_t digest[MAX_DIGEST_SIZE_INWORD];
static uint32_t op_mode, start_mode, block_mode;
static volatile bool digest_ready = false;

/* Global DMA driver instance for all DMA transfers in application. */
static struct _xdmad_cfg dma_cfg = { 0 };
static struct _xdmad_channel *dma_chan = NULL;
/* DMA linked list */
#ifndef VARIANT_DDRAM
static struct _xdmad_desc_view1 * const dma_dlist = (struct _xdmad_desc_view1*)
	(DDR_CS_ADDR + DDR_RESERVED_LEN + MSG_MAX_LEN);
#else
static struct _xdmad_desc_view1 dma_dlist[DMA_DESC_MAX_COUNT];
#endif

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Prepare XDMA channel.
 */
static void init_dma(void)
{
	/* Initialize XDMA driver instance with polling mode */
	xdmad_initialize(true);
	/* Allocate a XDMA channel, Write accesses into SHA_IDATARx */
	dma_chan = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, ID_SHA);
	if (!dma_chan)
		printf("-E- Can't allocate XDMA channel\n\r");
	else
		xdmad_prepare_channel(dma_chan);
}

/**
 * \brief Configure XDMA channel for SHA transfer.
 * \param buf  Pointer to data buffer.
 * \param len  Count of data blocks.
 */
static void configure_dma_write(uint32_t *buf, uint32_t len)
{
	const uint32_t words = algo_desc[op_mode].block_len_words;
	uint32_t i;

	dma_cfg.cfg.uint32_value =
		XDMAC_CC_TYPE_PER_TRAN |
		XDMAC_CC_MBSIZE_SINGLE |
		XDMAC_CC_DSYNC_MEM2PER |
		XDMAC_CC_CSIZE_CHK_16 |
		XDMAC_CC_DWIDTH_WORD |
		XDMAC_CC_SIF_AHB_IF0 |
		XDMAC_CC_DIF_AHB_IF1 |
		XDMAC_CC_SAM_INCREMENTED_AM |
		XDMAC_CC_DAM_FIXED_AM;
	for (i = 0; i < len; i++) {
		cache_clean_region(&buf[i * words], words * 4);
		dma_dlist[i].ublock_size = XDMA_UBC_NVIEW_NDV1 |
			(i == len - 1 ? 0 : XDMA_UBC_NDE_FETCH_EN) |
			XDMA_UBC_NSEN_UPDATED | words;
		dma_dlist[i].src_addr = &buf[i * words];
		dma_dlist[i].dest_addr = (void*)&SHA->SHA_IDATAR[0];
		dma_dlist[i].next_desc = i == len - 1 ? NULL : &dma_dlist[i + 1];
	}
	cache_clean_region(dma_dlist, sizeof(*dma_dlist) * len);
	xdmad_configure_transfer(dma_chan, &dma_cfg,
		XDMAC_CNDC_NDVIEW_NDV1 |
		XDMAC_CNDC_NDE_DSCR_FETCH_EN |
		XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED |
		XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED,
		dma_dlist);
}

/**
 * \brief SHA interrupt handler.
 */
static void handle_sha_irq(void)
{
	if ((sha_get_status() & SHA_ISR_DATRDY) == SHA_ISR_DATRDY) {
		sha_disable_it(SHA_IER_DATRDY);
		digest_ready = true;
	}
}

/**
 * \brief Generate message for given ASCII string.
 * \param M pointer to string
 * \param length message length in byte.
 * \param longMsg true in case of long message.
 * \note Maximun length is 32bits only.
 */
static void build_message(const uint8_t *M, uint32_t length, bool longMsg)
{
	uint32_t k, l = length * 8;
	uint8_t *p = (uint8_t *)message;

	if (algo_desc[op_mode].block_len_words == 1024 / 32)
		k = (1024 + 896 - ((l % 1024) + 1)) % 1024;
	else
		k = (512 + 448 - ((l % 512) + 1)) % 512;
	if (longMsg)
		memset (p, *M, length);
	else
		memcpy (p, M, length);
	p += length;
	/* Append a bit "1" to the message */
	*p++ = 0x80;
	/* Followed by k zero bits */
	memset(p, 0, (k - 7) / 8);
	p += (k - 7) / 8;
	if (algo_desc[op_mode].block_len_words == 1024 / 32) {
		memset(p, 0, 8);
		p += 8;
	}
	/* Then append the 64-bit block length */
	memset(p, 0, 4);
	p += 4;
	*p++ = l >> 24 & 0xff;
	*p++ = l >> 16 & 0xff;
	*p++ = l >> 8 & 0xff;
	*p++ = l & 0xff;
}

/**
 * \brief Byte swap unsigned int
 */
static uint32_t swap_uint32(uint32_t val)
{
	val = ((val << 8) & 0xFF00FF00 ) | ((val >> 8) & 0xFF00FF );
	return (val << 16) | (val >> 16);
}

/**
 * \brief Start SHA process.
 */
static void start_sha(void)
{
	uint32_t *p = NULL;
	uint32_t rc = 0, i, blk_cnt = 0, val, ref = 0;

	sha_get_status();
	if (start_mode == SHA_MR_SMOD_IDATAR0_START)
		init_dma();
	switch (op_mode) {
		case SHA_1:
			if (block_mode == SHA_ONE_BLOCK) {
				printf("-I- Testing FIPS APPENDIX A.1 SHA-1 Example (One-Block Message)\n\r-I- Get the final 160-bit message digest...\n\r");
				blk_cnt = 1;
				build_message(msg0, LEN_MSG_0, false);
			}
			if (block_mode == SHA_MULTI_BLOCK) {
				printf("-I- Testing FIPS APPENDIX A.2 SHA-1 Example (Multi-Block Message)\n\r-I- Get the final 160-bit message digest...\n\r");
				blk_cnt = 2;
				build_message(msg1, LEN_MSG_1, false);
			}
			if (block_mode == SHA_LONG_MESSAGE) {
				printf("-I- Testing FIPS APPENDIX A.3 SHA-1 Example (Long Message)\n\r-I- Get the final 160-bit message digest...\n\r");
				blk_cnt = DMA_DESC_MAX_COUNT;
				build_message(&msg_long_pattern, LEN_MSG_LONG, true);
			}
			break;
		case SHA_256:
			if (block_mode == SHA_ONE_BLOCK) {
				printf("-I- Testing FIPS APPENDIX B.1 SHA-256 Example (One-Block Message)\n\r-I- Get the final 256-bit message digest...\n\r");
				blk_cnt = 1;
				build_message(msg0, LEN_MSG_0, false);
			}
			if (block_mode == SHA_MULTI_BLOCK) {
				printf("-I- Testing FIPS APPENDIX B.2 SHA-256 Example (Multi-Block Message)\n\r-I- Get the final 256-bit message digest...\n\r");
				blk_cnt = 2;
				build_message(msg1, LEN_MSG_1, false);
			}
			if (block_mode == SHA_LONG_MESSAGE) {
				printf("-I- Testing FIPS APPENDIX B.3 SHA-256 Example (Long Message)\n\r-I- Get the final 256-bit message digest...\n\r");
				blk_cnt = DMA_DESC_MAX_COUNT;
				build_message(&msg_long_pattern, LEN_MSG_LONG, true);
			}
			break;
		case SHA_384:
			if (block_mode == SHA_ONE_BLOCK) {
				printf("-I- Testing FIPS APPENDIX D.1 SHA-384 Example (One-Block Message)\n\r-I- Get the final 384-bit message digest...\n\r");
				blk_cnt = 1;
				build_message(msg0, LEN_MSG_0, false);
			}
			if (block_mode == SHA_MULTI_BLOCK) {
				printf("-I- Testing FIPS APPENDIX D.2 SHA-384 Example (Multi-Block Message)\n\r-I- Get the final 384-bit message digest...\n\r");
				blk_cnt = 2;
				build_message(msg2, LEN_MSG_2, false);
			}
			if (block_mode == SHA_LONG_MESSAGE) {
				printf("-I- Testing FIPS APPENDIX D.3 SHA-384 Example (Long Message)\n\r-I- Get the final 384-bit message digest...\n\r");
				blk_cnt = LEN_MSG_LONG / 4 / 32 + 1;
				build_message(&msg_long_pattern, LEN_MSG_LONG, true);
			}
			break;
		case SHA_512:
			if (block_mode == SHA_ONE_BLOCK) {
				printf("-I- Testing FIPS APPENDIX C.1 SHA-512 Example (One-Block Message)\n\r-I- Get the final 512-bit message digest...\n\r");
				blk_cnt = 1;
				build_message(msg0, LEN_MSG_0 , false);
			}
			if (block_mode == SHA_MULTI_BLOCK) {
				printf("-I- Testing FIPS APPENDIX C.2 SHA-512 Example (Multi-Block Message)\n\r-I- Get the final 512-bit message digest...\n\r");
				blk_cnt = 2;
				build_message(msg2, LEN_MSG_2, false);
			}
			if (block_mode == SHA_LONG_MESSAGE) {
				printf("-I- Testing FIPS APPENDIX C.3 SHA-512 Example (Long Message)\n\r-I- Get the final 512-bit message digest...\n\r");
				blk_cnt = LEN_MSG_LONG / 4 / 32 + 1;
				build_message(&msg_long_pattern, LEN_MSG_LONG, true);
			}
			break;
		case SHA_224:
			if (block_mode == SHA_ONE_BLOCK) {
				printf("-I- Testing FIPS APPENDIX 1 SHA-224 Example (One-Block Message)\n\r-I- Get the final 224-bit message digest...\n\r");
				blk_cnt = 1;
				build_message(msg0, LEN_MSG_0, false);
			}
			if (block_mode == SHA_MULTI_BLOCK) {
				printf("-I- Testing FIPS APPENDIX 2 SHA-224 Example (Multi-Block Message)\n\r-I- Get the final 224-bit message digest...\n\r");
				blk_cnt = 2;
				build_message(msg1, LEN_MSG_1, false);
			}
			if (block_mode == SHA_LONG_MESSAGE) {
				printf("-I- Testing FIPS APPENDIX 2 SHA-224 Example (Long Message)\n\r-I- Get the final 224-bit message digest...\n\r");
				blk_cnt = DMA_DESC_MAX_COUNT;
				build_message(&msg_long_pattern, LEN_MSG_LONG, true);
			}
			break;
	}

	sha_configure(start_mode | (op_mode << SHA_MR_ALGO_Pos) |
		      SHA_MR_PROCDLY_LONGEST);
	/* For the first block of a message, the FIRST command must be set by
	 * setting the corresponding bit of the Control Register (SHA_CR). For
	 * the other blocks, there is nothing to write in this Control Register. */
	sha_first_block();
	if (start_mode == SHA_MR_SMOD_IDATAR0_START) {
		configure_dma_write(message, blk_cnt);
		rc = xdmad_start_transfer(dma_chan);
		if (rc == XDMAD_OK) {
			while (!xdmad_is_transfer_done(dma_chan))
				xdmad_poll();
			xdmad_stop_transfer(dma_chan);
		}
	} else {
		for (p = message, i = 0; i < blk_cnt;
		     i++, p+= algo_desc[op_mode].block_len_words) {
			digest_ready = false;
			/* Write the block to be processed in the Input Data Registers */
			sha_set_input(p, algo_desc[op_mode].block_len_words);
			if (start_mode == SHA_MR_SMOD_MANUAL_START) {
				/* Set the START bit in the SHA Control Register SHA_CR to begin the processing. */
				sha_start();
			}
			/* Set the bit DATRDY (Data Ready) in the SHA Interrupt Enable Register (SHA_IER) */
			sha_enable_it(SHA_IER_DATRDY);
			/* When the processing completes, the bit DATRDY in the
			 * SHA Interrupt Status Register (SHA_ISR) raises. If an
			 * interrupt has been enabled by setting the bit DATRDY
			 * in SHA_IER, the interrupt line of the SHA is activated. */
			while (!digest_ready) ;
			/* Repeat the write procedure for each block, start
			 * procedure and wait for the interrupt procedure up to
			 * the last block of the entire message. Each time the
			 * start procedure is complete, the DATRDY flag is cleared. */
		}
	}

	sha_get_output(digest);
	printf("-I- Dump and compare digest result...\n\r");
	for (rc = 0, i = 0; i < algo_desc[op_mode].digest_len_words; i++) {
		val = swap_uint32(digest[i]);
		switch (op_mode) {
		case SHA_1:   ref = ref_digests_one[block_mode][i]; break;
		case SHA_256: ref = ref_digests_256[block_mode][i]; break;
		case SHA_384: ref = ref_digests_384[block_mode][i]; break;
		case SHA_512: ref = ref_digests_512[block_mode][i]; break;
		case SHA_224: ref = ref_digests_224[block_mode][i]; break;
		}
		if (val != ref) {
			printf(" [X]");
			rc++;
		}
		printf("   0x%08x  \n\r", (unsigned int)val);
	}
	if (rc)
		printf("-I- Failed to verify message digest (%du errors)\n\r",
		       (unsigned int)rc);
	else
		printf("-I- Message digest result matched exactly with the result in FIPS example\n\r");
}

/**
 * \brief Display main menu.
 */
static void display_menu(void)
{
	uint8_t chk_box[5];

	printf("\n\rSHA Menu :\n\r");
	printf("Press [0|1|2|3|4] to set SHA Algorithm \n\r");
	memset(chk_box, ' ', sizeof(chk_box));
	chk_box[op_mode] = 'X';
	printf("   0: SHA1[%c] 1: SHA256[%c] 2: SHA384[%c] 3: SHA512[%c] 4: SHA224[%c]\n\r",
	       chk_box[0], chk_box[1], chk_box[2], chk_box[3], chk_box[4]);

	printf("Press [o|t|l] to set one/multi-block or long message \n\r");
	memset(chk_box, ' ', sizeof(chk_box));
	chk_box[block_mode] = 'X';
	printf("   o: one-block[%c] t: multi-block[%c] l: long-message[%c] \n\r",
	       chk_box[0], chk_box[1], chk_box[2]);

	printf("Press [m|a|d] to set Start Mode \n\r");
	chk_box[0] = (start_mode == SHA_MR_SMOD_MANUAL_START) ? 'X' : ' ';
	chk_box[1] = (start_mode == SHA_MR_SMOD_AUTO_START) ? 'X' : ' ';
	chk_box[2] = (start_mode == SHA_MR_SMOD_IDATAR0_START) ? 'X' : ' ';
	printf("   m: MANUAL_START[%c] a: AUTO_START[%c] d: DMA[%c]\n\r",
	       chk_box[0], chk_box[1], chk_box[2]);

	printf("   p: Start hash algorithm process \n\r");
	printf("   h: Display this menu\n\r");
	printf("\n\r");
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

	wdt_disable();
	board_cfg_console(0);

	/* Output example information */
	printf("\r\n\r\n\r\n");
	printf("-- SHA Example " SOFTPACK_VERSION " --\r\n");
	printf("-- " BOARD_NAME "\r\n");
	printf("-- Compiled: " __DATE__ " " __TIME__ " --\n\r");

#ifndef VARIANT_DDRAM
	board_cfg_ddram();
#endif

	/* Enable peripheral clock */
	pmc_enable_peripheral(ID_SHA);
	/* Perform a software-triggered hardware reset of the SHA interface */
	sha_soft_reset();
	aic_set_source_vector(ID_SHA, handle_sha_irq);
	aic_enable(ID_SHA);

	/* Display menu */
	op_mode = SHA_1;
	start_mode = SHA_MR_SMOD_MANUAL_START;
	block_mode = SHA_ONE_BLOCK;
	display_menu();

	/* Handle keypresses */
	while (true) {
		user_key = tolower(console_get_char());
		switch (user_key) {
			case '0': case '1': case '2': case '3': case '4':
				op_mode = user_key - '0';
				display_menu();
				break;
			case 'o':
			case 't':
			case 'l':
				block_mode = user_key == 't' ? SHA_MULTI_BLOCK :
				            (user_key == 'l' ? SHA_LONG_MESSAGE :
				                               SHA_ONE_BLOCK);
				display_menu();
				break;
			case 'm':
			case 'a':
			case 'd':
				start_mode = user_key == 'a' ? SHA_MR_SMOD_AUTO_START :
				            (user_key == 'd' ? SHA_MR_SMOD_IDATAR0_START :
				                               SHA_MR_SMOD_MANUAL_START);
				display_menu();
				break;
			case 'h':
				display_menu();
				break;
			case 'p':
				start_sha();
				break;
		}
	}

	/* This code is never reached */
}
