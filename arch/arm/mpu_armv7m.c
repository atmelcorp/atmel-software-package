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

/*------------------------------------------------------------------------------ */
/*         Headers                                                               */
/*------------------------------------------------------------------------------ */

#include "chip.h"
#include "barriers.h"

#include "arm/mpu_armv7m.h"

#include <assert.h>

/*------------------------------------------------------------------------------ */
/*         Exported functions                                                    */
/*------------------------------------------------------------------------------ */

void mpu_configure(const void* config)
{
	uint32_t* values = (uint32_t*)config;

	while (*values != 0) {
		MPU->MPU_REGION[0].MPU_RBAR = *values++;
		MPU->MPU_REGION[0].MPU_RASR = *values++;
	}
}

bool mpu_is_enabled(void)
{
	return (MPU->MPU_CTRL & MPU_CTRL_ENABLE) != 0;
}

void mpu_enable(void)
{
	/* Activate MemFault, BusFault & UsageFault exceptions */
	SCB->SCB_SHCSR |= (SCB_SHCSR_MEMFAULTENA |
	                   SCB_SHCSR_BUSFAULTENA |
	                   SCB_SHCSR_USGFAULTENA);

	/* Enable the MPU without the background region */
	MPU->MPU_CTRL = MPU_CTRL_ENABLE;

	dsb();
	isb();
}

void mpu_disable(void)
{
	MPU->MPU_CTRL = 0;
}
