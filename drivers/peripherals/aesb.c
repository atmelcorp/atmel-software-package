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
 * \file
 *
 * Implementation of Advanced Encryption Standard Bridge (AESB)
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/aesb.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Starts Manual encryption/decryption process.
 */
void aesb_start(void)
{
	AESB->AESB_CR = AESB_CR_START;
}

/**
 * \brief Resets the AESB. A software triggered hardware reset of the AESB interface is performed.
 */
void aesb_swrst(void)
{
	AESB->AESB_CR = AESB_CR_SWRST;
}

/**
 * \brief Configures an AESB peripheral with the specified parameters.
 *  \param mode  Desired value for the AESB mode register (see the datasheet).
 */
void aesb_configure(uint32_t mode)
{
	AESB->AESB_MR = mode;
}

/**
 * \brief Enables the selected interrupts sources on a AESB peripheral.
 * \param sources  Bitwise OR of selected interrupt sources.
 */
void aesb_enable_it(uint32_t sources)
{
	AESB->AESB_IER = sources;
}

/**
 * \brief Disables the selected interrupts sources on a AESB peripheral.
 * \param sources  Bitwise OR of selected interrupt sources.
 */
void aesb_disable_it(uint32_t sources)
{
	AESB->AESB_IDR = sources;
}

/**
 * \brief Get the current status register of the given AESB peripheral.
 * \return  AESB status register.
 */
uint32_t aesb_get_status(void)
{
	return AESB->AESB_ISR;
}

/**
 * \brief Set the 128-bit cryptographic key used for encryption/decryption.
 * \param pKey Pointer to a 16 bytes cipher key.
 */
void aesb_write_key(const uint32_t * pKey)
{
	AESB->AESB_KEYWR[0] = pKey[0];
	AESB->AESB_KEYWR[1] = pKey[1];
	AESB->AESB_KEYWR[2] = pKey[2];
	AESB->AESB_KEYWR[3] = pKey[3];
}

/**
 * \brief Set the for 32-bit input Data allow to set the 128-bit data block used for encryption/decryption.
 * \param data Pointer to the 16-bytes data to cipher/decipher.
 */
void aesb_set_input(uint32_t * data)
{
	uint8_t i;
	for (i = 0; i < 4; i++)
		AESB->AESB_IDATAR[i] = data[i];
}

/**
 * \brief Get the four 32-bit data contain the 128-bit data block which has been encrypted/decrypted.
 * \param data pointer to the word that has been encrypted/decrypted..
 */
void aesb_get_output(uint32_t * data)
{
	uint8_t i;
	for (i = 0; i < 4; i++)
		data[i] = AESB->AESB_ODATAR[i];
}

/**
 * \brief Set four 64-bit initialization vector data block, which is used by some
 * modes of operation as an additional initial input.
 * \param vector point to the word of the initialization vector.
 */
void aesb_set_vector(const uint32_t * vector)
{
	AESB->AESB_IVR[0] = vector[0];
	AESB->AESB_IVR[1] = vector[1];
	AESB->AESB_IVR[2] = vector[2];
	AESB->AESB_IVR[3] = vector[3];
}
