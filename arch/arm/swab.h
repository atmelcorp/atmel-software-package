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

#ifndef ARM_SWAB_H_
#define ARM_SWAB_H_

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_ARCH_ARMV5TE)

static inline uint16_t swab16(uint16_t value)
{
	uint32_t result;

	result = ((value & 0xff00) >> 8) |
	         ((value & 0x00ff) << 8);

	return result;
}

static inline uint32_t swab32(uint32_t value)
{
	uint32_t result;

	// ARMv5TE does not support the "rev" instruction
	asm("eor %0, %1, %1, ror #16\n"
	    "bic %0, %0, #0xff0000\n"
	    "mov %0, %0, lsr #8\n"
	    "eor %0, %0, %1, ror #8" : "=r"(result) : "r"(value));

	return result;
}

#elif defined(CONFIG_ARCH_ARMV7A) ||\
      defined(CONFIG_ARCH_ARMV7M)

static inline uint16_t swab16(uint16_t value)
{
	uint32_t result;

	asm("rev16 %0, %1" : "=r"(result) : "r"(value));

	return result;
}

static inline uint32_t swab32(uint32_t value)
{
	uint32_t result;

	asm("rev %0, %1" : "=r"(result) : "r"(value));

	return result;
}

#endif

#endif /* ARM_SWAB_H_ */
