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

#ifndef ARM_IRQFLAGS_H_
#define ARM_IRQFLAGS_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_ARCH_ARMV5TE)

static inline void arch_irq_enable(void)
{
	uint32_t cpsr;
	asm("mrs %0, cpsr" : "=r"(cpsr));
	asm("msr cpsr_c, %0" :: "r"(cpsr & ~0x80));
}

static inline void arch_irq_disable(void)
{
	uint32_t cpsr;
	asm("mrs %0, cpsr" : "=r"(cpsr));
	asm("msr cpsr_c, %0" :: "r"(cpsr | 0x80));
}

#elif defined(CONFIG_ARCH_ARMV7A)

static inline void arch_irq_enable(void)
{
	asm("cpsie if");
}

static inline void arch_irq_disable(void)
{
	asm("cpsid if");
}

#elif defined(CONFIG_ARCH_ARMV7M)

static inline void arch_irq_enable(void)
{
	asm("cpsie i");
}

static inline void arch_irq_disable(void)
{
	asm("cpsid i");
}

#endif

#endif /* ARM_IRQFLAGS_H_ */
