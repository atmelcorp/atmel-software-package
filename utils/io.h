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

#ifndef UTILS_IO_HEADER
#define UTILS_IO_HEADER

#include <stdint.h>

struct _buffer
{
	uint8_t* data; /* Data addr*/
	uint32_t size; /* data length */
	uint32_t attr; /* Attribute on buffer (depending of the peripheral) */
};

static inline void writeb(volatile void* reg, uint8_t value)
{
	*(volatile uint8_t*)reg = value;
}

static inline void writehw(volatile void* reg, uint16_t value)
{
	*(volatile uint16_t*)reg = value;
}

static inline void writew(volatile void* reg, uint32_t value)
{
	*(volatile uint32_t*)reg = value;
}

static inline void readb(volatile const void* reg, uint8_t* value)
{
	*value = *(volatile const uint8_t*)reg;
}

static inline void readhw(volatile const void* reg, uint16_t* value)
{
	*value = *(volatile const uint16_t*)reg;
}

static inline void readw(volatile const void* reg, uint32_t* value)
{
	*value = *(volatile const uint32_t*)reg;
}

#endif
