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

/** \addtogroup tdes_module Working with TDES
 * \ingroup peripherals_module
 * The ADC driver provides the interface to configure and use the TDES peripheral.
 * \n
 *
 * The Data Encryption Standard (DES) and the Triple Data Encryption Algorithm (TDES) specify
 * FIPS-approved cryptographic algorithms that can be used to protect electronic data. The TDES
 * bit in the TDES Mode Register (TDES_MR) is used to select either the single DES or the Triple
 * DES mode by function tdes_configure().
 * A DES is capable of using cryptographic keys of 64 bits to encrypt and decrypt data in blocks of
 * 64 bits, Date input can be set with tdes_set_input(). This 64-bit key is defined in the Key 1 Word
 * Registers (TDES_KEY1WRx) and set by tdes_write_key1. A TDES key consists of three DES keys,
 * which is also referred to as a key bundle. These three 64-bit keys are defined, respectively,
 * in the Key 1, 2 and 3 Word Registers (TDES_KEY1WRx, TDES_KEY2WRx and TDES_KEY3WRx).
 * In Triple DES mode (TDESMOD set to 1), the KEYMOD bit in the TDES Mode Register is used to choose between a two- and a three-key
 * algorithm:
 *
 * To Enable a TDES encryption and decrypt,the user has to follow these few steps:
 * <ul>
 * <li> A software triggered hardware reset of the TDES interface is performed by tdes_soft_reset().</li>
 * <li> Configure TDES algorithm mode, key mode, start mode and operation mode by tdes_configure(). </li>
 * <li> Set DES key with fucntion tdes_write_key1(), tdes_write_key2(), or tdes_write_key3(). </li>
 * <li> To start the encryption or the decryption process with tdes_start()</li>
 * <li> To get the encryption or decryption reslut by tdes_get_output() </li>
 * </ul>
 *
 * For more accurate information, please look at the TDES section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref tdes.c\n
 * \ref tdes.h\n
 */
/*@{*/
/*@}*/
/**
 * \file
 *
 * Implementation of Triple Data Encryption Standard (TDES).
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/tdes.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void tdes_start(void)
{
	TDES->TDES_CR = TDES_CR_START;
}

void tdes_soft_reset(void)
{
	TDES->TDES_CR = TDES_CR_SWRST;
}

void tdes_configure(uint32_t mode)
{
	TDES->TDES_MR = mode;
}

void tdes_enable_it(uint32_t sources)
{
	TDES->TDES_IER = sources;
}

void tdes_disable_it(uint32_t sources)
{
	TDES->TDES_IDR = sources;
}

uint32_t tdes_get_status(void)
{
	return TDES->TDES_ISR;
}

void tdes_write_key1(uint32_t key_word0, uint32_t key_word1)
{
	TDES->TDES_KEY1WR[0] = key_word0;
	TDES->TDES_KEY1WR[1] = key_word1;
}

void tdes_write_key2(uint32_t key_word0, uint32_t key_word1)
{
	TDES->TDES_KEY2WR[0] = key_word0;
	TDES->TDES_KEY2WR[1] = key_word1;
}

void tdes_write_key3(uint32_t key_word0, uint32_t key_word1)
{
	TDES->TDES_KEY3WR[0] = key_word0;
	TDES->TDES_KEY3WR[1] = key_word1;
}

void tdes_set_input(uint32_t data0, uint32_t data1)
{
	TDES->TDES_IDATAR[0] = data0;
	TDES->TDES_IDATAR[1] = data1;
}

void tdes_get_output(uint32_t *data0, uint32_t *data1)
{
	*data0 = TDES->TDES_ODATAR[0];
	*data1 = TDES->TDES_ODATAR[1];
}

void tdes_set_vector(uint32_t v0, uint32_t v1)
{
	TDES->TDES_IVR[0] = v0;
	TDES->TDES_IVR[1] = v1;
}

void tdes_set_xtea_rounds(uint32_t rounds)
{
	TDES->TDES_XTEA_RNDR = TDES_XTEA_RNDR_XTEA_RNDS(rounds);
}
