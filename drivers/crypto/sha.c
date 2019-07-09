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

/** \addtogroup sha_module Working with SHA
 * \ingroup peripherals_module
 * The SHA driver provides the interface to configure and use the SHA
 * peripheral.
 * \n
 *
 * The Secure Hash Algorithm (SHA) module requires a padded message
 * according to FIPS180-2 specification. The first block of the
 * message must be indicated to the module by a specific command. The
 * SHA module produces a N-bit message digest each time a block is
 * written and processing period ends. N is 160 for SHA1, 224 for
 * SHA224, 256 for SHA256, 384 for SHA384, 512 for SHA512.
 *
 * To Enable a SHA encryption and decrypt,the user has to follow these
 * few steps:
 * <ul>
 * <li> Configure SHA algorithm mode, key mode, start mode and
 * operation mode by sha_configure(). </li>
 * <li> Set sha_first_block() to indicates that the next block to
 * process is the first one of a message.</li>
 * <li> Input data for encryption by sha_set_input(). </li>
 * <li> To start the encryption process with sha_start()</li>
 * <li> To get the encryption reslut by sha_get_output() </li>
 * </ul>
 *
 * For more accurate information, please look at the SHA section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref sha.c\n
 * \ref sha.h\n
 */
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of Secure Hash Algorithm (SHA)
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>

#include "chip.h"
#include "crypto/sha.h"
#include "intmath.h"
/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void sha_start(void)
{
	SHA->SHA_CR = SHA_CR_START;
}

void sha_soft_reset(void)
{
	SHA->SHA_CR = SHA_CR_SWRST;
}

void sha_first_block(void)
{
	SHA->SHA_CR = SHA_CR_FIRST;
}


void sha_configure(uint32_t mode)
{
	SHA->SHA_MR = mode;
}

void sha_enable_it(uint32_t sources)
{
	SHA->SHA_IER = sources;
}

void sha_disable_it(uint32_t sources)
{
	SHA->SHA_IDR = sources;
}

uint32_t sha_get_status(void)
{
	return SHA->SHA_ISR;
}

void sha_set_input(const uint8_t* data, int len)
{
	int i;
	int32_t value;

	for (i = 0; i < CEIL_INT_DIV(len , 4) && i < 32; i++) {
		memcpy(&value, &data[i * 4], 4);
		if (i < 16)
			SHA->SHA_IDATAR[i] = value;
		else
			SHA->SHA_IODATAR[i - 16] = value;
	}
}

void sha_get_output(uint8_t* data, int len)
{
	int i;
	int32_t value;

	for (i = 0; i < (len / 4) && i < 16; i++) {
		value = SHA->SHA_IODATAR[i];
		memcpy(&data[i * 4], &value, 4);
	}
}

#ifdef CONFIG_HAVE_SHA_HMAC
void sha_enable_hmac(void)
{
	SHA->SHA_MR |= SHA_MR_ALGO_HMAC_SHA1;
}

void sha_set_ir0(uint8_t ir)
{
	if (ir)
		SHA->SHA_CR = SHA_CR_WUIHV;
	else
		SHA->SHA_CR = 0;
}

void sha_set_ir1(uint8_t ir)
{
	if (ir)
		SHA->SHA_CR = SHA_CR_WUIEHV;
	else
		SHA->SHA_CR = 0;
}

void sha_set_start_algo(uint8_t ir)
{
	SHA->SHA_MR |= ir << 5;
}

void sha_set_msr(uint32_t size)
{
	SHA->SHA_MSR = size;
}

void sha_set_bcr(uint32_t size)
{
	SHA->SHA_BCR = size;
}
#endif