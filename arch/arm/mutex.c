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

#include "barriers.h"
#include "chip.h"
#include "mutex.h"
#include "cpuidle.h"

#include <stdint.h>
#include <stdbool.h>

#define MUTEX_LOCKED   1
#define MUTEX_UNLOCKED 0

void mutex_lock(mutex_t* mutex)
{
	while (!mutex_try_lock(mutex)) {
		cpu_idle();
	}
}

#if defined(CONFIG_ARCH_ARMV7A) || defined(CONFIG_ARCH_ARMV7M)

bool mutex_try_lock(mutex_t* mutex)
{
	uint32_t value;
	asm("ldrex %0, [%1]" : "=r"(value) : "r"(mutex));
	if (value != MUTEX_UNLOCKED)
		return false;
	asm("strex %0, %1, [%2]" : "=&r"(value) : "r"(MUTEX_LOCKED), "r"(mutex));
	if (value == 1) /* strex failed */
		return false;
	dmb();
	return true;
}

#elif defined(CONFIG_ARCH_ARMV5TE)

bool mutex_try_lock(mutex_t* mutex)
{
	uint32_t value;
	asm("swp %0, %1, [%2]" : "=&r"(value) : "r"(MUTEX_LOCKED), "r"(mutex));
	return value == MUTEX_UNLOCKED;
}

#endif

void mutex_unlock(mutex_t* mutex)
{
	dmb();
	*mutex = MUTEX_UNLOCKED;
}

bool mutex_is_locked(const mutex_t* mutex)
{
	return *mutex != MUTEX_UNLOCKED;
}
