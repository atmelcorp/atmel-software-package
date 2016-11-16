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
 * ARM core utility functions
 *
 */

#ifndef ARM_H
#define ARM_H

#include "compiler.h"
#include "arm_cp15.h"
#include "arm_cpsr.h"
#include "arm_mmu.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_CORE_ARM926)

static inline void irq_enable_all(void)
{
	cpsr_clear_bits(CPSR_MASK_IRQ);
}

static inline void irq_disable_all(void)
{
	cpsr_set_bits(CPSR_MASK_IRQ);
}

static inline void irq_wait(void)
{
	/* drain write buffer */
	asm("mcr p15, 0, %0, c7, c10, 4" :: "r"(0) : "memory");
	/* wait for interrupt */
	asm("mcr p15, 0, %0, c7, c0, 4" :: "r"(0) : "memory");
}

static inline void dmb(void)
{
	asm("" ::: "memory");
}

static inline void dsb(void)
{
	/* drain write buffer */
	asm("mcr p15, 0, %0, c7, c10, 4" :: "r"(0) : "memory");
}

static inline void isb(void)
{
	asm("" ::: "memory");
}

#elif defined(CONFIG_CORE_CORTEXA5)

static inline void irq_enable_all(void)
{
	asm("cpsie if");
}

static inline void irq_disable_all(void)
{
	asm("cpsid if");
}

static inline void irq_wait(void)
{
	asm("wfi");
}

static inline void dmb(void)
{
	asm("dmb" ::: "memory");
}

static inline void dsb(void)
{
	asm("dsb" ::: "memory");
}

static inline void isb(void)
{
	asm("isb" ::: "memory");
}

#else
#error Unknown CPU core!
#endif /* CONFIG_CORE_xxx */

#endif /* ARM_H */
