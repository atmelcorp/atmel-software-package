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

static inline void irq_enable(void)
{
#if defined(__ICCARM__) || defined(__GNUC__)
        asm volatile ("cpsie i");
#else
#error Unsupported compiler!
#endif
}

static inline void irq_disable(void)
{
#if defined(__ICCARM__) || defined(__GNUC__)
        asm volatile ("cpsid i");
#else
#error Unsupported compiler!
#endif
}

#if defined(CONFIG_CORE_ARM926)

static inline void irq_wait(void)
{
}

static inline void dmb(void)
{
}

static inline void dsb(void)
{
}

static inline void isb(void)
{
}

#elif defined(CONFIG_CORE_CORTEXA5)

static inline void irq_wait(void)
{
#if defined(__ICCARM__) || defined(__GNUC__)
        asm volatile ("wfi");
#else
#error Unsupported compiler!
#endif
}

static inline void dmb(void)
{
#if defined(__ICCARM__) || defined(__GNUC__)
	asm volatile ("dmb" ::: "memory");
#else
#error Unsupported compiler!
#endif
}

static inline void dsb(void)
{
#if defined(__ICCARM__) || defined(__GNUC__)
	asm volatile ("dsb" ::: "memory");
#else
#error Unsupported compiler!
#endif
}

static inline void isb(void)
{
#if defined(__ICCARM__) || defined(__GNUC__)
	asm volatile ("isb" ::: "memory");
#else
#error Unsupported compiler!
#endif
}

#else
#error Unknown CPU core!
#endif /* CONFIG_CORE_xxx */

#endif /* ARM_H */
