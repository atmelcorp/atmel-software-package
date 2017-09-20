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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "barriers.h"
#include "chip.h"
#include "trace.h"

#include "irq/nvic.h"
#include "irqflags.h"

#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

ALIGNED(128 * 4)
static nvic_handler_t nvic_vectors[16 + ID_PERIPH_COUNT];

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void nvic_initialize(nvic_handler_t irq_handler)
{
	int i;

	/* Disable interrupts at core level */
	arch_irq_disable();

	memcpy(nvic_vectors, (void*)SCB->SCB_VTOR, 16 * 4);
	for (i = 0; i < ID_PERIPH_COUNT; i++)
		nvic_vectors[16 + i] = irq_handler;
	SCB->SCB_VTOR = (uint32_t)nvic_vectors;
	dsb();

	/* Enable interrupts at core level */
	arch_irq_enable();
}

void nvic_set_source_vector(uint32_t source, nvic_handler_t handler)
{
	uint32_t* vtor = (uint32_t*)SCB->SCB_VTOR;
	vtor[source + 16] = (uint32_t)handler;
	dsb();
}

void nvic_configure_priority(uint32_t source, uint8_t priority)
{
	/* TODO */
}

void nvic_enable(uint32_t source)
{
	uint32_t index = source >> 5;
	uint32_t bit = 1 << (source & 0x1f);
	NVIC->NVIC_ISER[index] = bit;
}

void nvic_disable(uint32_t source)
{
	uint32_t index = source >> 5;
	uint32_t bit = 1 << (source & 0x1f);
	NVIC->NVIC_ICER[index] = bit;
}

uint32_t nvic_get_current_interrupt_source(void)
{
	uint32_t ipsr;
	asm("mrs %0, ipsr" : "=r"(ipsr));
	return ipsr - 16;
}
