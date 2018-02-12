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
 *	  Includes
 *----------------------------------------------------------------------------*/

#include <string.h>

#include "callback.h"
#include "chip.h"
#include "compiler.h"
#include "ptc/ppp.h"
#include "irq/irq.h"
#include "mutex.h"
#include "peripherals/pmc.h"
#include "timer.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *	   Private variables
 *----------------------------------------------------------------------------*/

static void _ppp_handler(uint32_t source, void* user_arg)
{
	struct _ppp* ppp = (struct _ppp*)user_arg;
	uint32_t isr = ppp->addr->PPP_ISR & ppp->imr;

	if (isr) {
		if (isr & PPP_ISR_IRQ0) {
			callback_call(&ppp->irq_handler.on_irq0, NULL);

			/* Acknowledge IRQ */
			ppp_clear_pending_it(ppp, PPP_ICR_IRQ0);
			ppp_disable_it(ppp, PPP_IDR_IRQ0);

			mutex_unlock(&ppp->mutex);
		}
		if (isr & PPP_ISR_IRQ1) {

			callback_call(&ppp->irq_handler.on_irq1, NULL);

			/* Acknowledge IRQ */
			ppp_clear_pending_it(ppp, PPP_ICR_IRQ1);
		}
		if (isr & PPP_ISR_IRQ2) {
			callback_call(&ppp->irq_handler.on_irq2, NULL);

			/* Acknowledge IRQ */
			ppp_clear_pending_it(ppp, PPP_ICR_IRQ2);
		}
		if (isr & PPP_ISR_IRQ3) {
			callback_call(&ppp->irq_handler.on_irq3, NULL);

			/* Acknowledge IRQ */
			ppp_clear_pending_it(ppp, PPP_ICR_IRQ3);
		}
	}
}

/*----------------------------------------------------------------------------
 *	   Public methods
 *----------------------------------------------------------------------------*/

int ppp_configure(struct _ppp* ppp)
{
	irq_disable(ID_PPP);

	ppp->mutex = 0;

	/* Internal OSC should be enabled too */
	pmc_enable_internal_osc();
	/* Enable PTC peripheral clock */
	pmc_enable_peripheral(ID_PPP);

	ppp_stop(ppp);
	ppp_reset(ppp);

	memset(ppp->sram.code.addr, 0, ppp->sram.code.len);

	return 0;
}

void ppp_load(struct _ppp* ppp, uint8_t* firmware, uint16_t size)
{
	ppp->cfg.firmware.code = firmware;
	ppp->cfg.firmware.size = size;

	/* Upload PPP software */
	if (firmware != NULL)
		memcpy(ppp->sram.code.addr, ppp->cfg.firmware.code, ppp->cfg.firmware.size);
}

uint8_t* ppp_get_mailbox_addr(struct _ppp* ppp)
{
	return (uint8_t*)ppp->sram.mailbox.addr;
}


void ppp_register_irq_handler(struct _ppp* ppp, uint32_t irq, callback_method_t handler, void* user_arg)
{
	switch (irq & PPP_ISR_Msk) {
	case PPP_ISR_IRQ0:
		callback_set(&ppp->irq_handler.on_irq0, handler, user_arg);
		break;
	case PPP_ISR_IRQ1:
		callback_set(&ppp->irq_handler.on_irq1, handler, user_arg);
		break;
	case PPP_ISR_IRQ2:
		callback_set(&ppp->irq_handler.on_irq2, handler, user_arg);
		break;
	case PPP_ISR_IRQ3:
		callback_set(&ppp->irq_handler.on_irq3, handler, user_arg);
		break;
	default:
		trace_error("ppp: IRQ not supported\r\n");
	}
}

void ppp_enable_it(struct _ppp* ppp, uint32_t mask)
{
	ppp->imr |= mask;
	ppp->addr->PPP_IER = mask & PPP_IER_Msk;
}

void ppp_disable_it(struct _ppp* ppp, uint32_t mask)
{
	ppp->imr &= ~mask;
	ppp->addr->PPP_IDR = mask & PPP_IDR_Msk;
}

void ppp_clear_pending_it(struct _ppp* ppp, uint32_t mask)
{
	if (mask & PPP_ISR_Msk)
		ppp->addr->PPP_ICR &= ~mask;
}

void ppp_notify(struct _ppp* ppp, uint32_t mask)
{
	if (mask & PPP_ICR_NOTIFY_Msk)
		ppp->addr->PPP_ICR |= mask;
}

void ppp_start(struct _ppp* ppp)
{
	/* Enable PPP interrupt */
	irq_add_handler(ID_PPP, _ppp_handler, ppp);
	irq_enable(ID_PPP);

	ppp->addr->PPP_CMD = PPP_CMD_RUN;
}

void ppp_stop(struct _ppp* ppp)
{
	irq_disable(ID_PPP);

	ppp->addr->PPP_CMD = PPP_CMD_STOP;
}

void ppp_restart(struct _ppp* ppp)
{
	/* Enable PPP interrupt */
	irq_add_handler(ID_PPP, _ppp_handler, ppp);
	irq_enable(ID_PPP);

	ppp->addr->PPP_CMD = PPP_CMD_RESTART;
}

void ppp_abort(struct _ppp* ppp)
{
	irq_disable(ID_PPP);

	ppp->addr->PPP_CMD = PPP_CMD_ABORT;
}

void ppp_reset(struct _ppp* ppp)
{
	ppp_abort(ppp);
	ppp_clear_pending_it(ppp, PPP_IDR_Msk);

	ppp->addr->PPP_CMD = PPP_CMD_RESET;

	/* Reload */
	ppp_load(ppp, ppp->cfg.firmware.code, ppp->cfg.firmware.size);

}

void ppp_memcpy(uint8_t* dst, uint8_t* src, uint16_t len)
{
	while (len-- > 0)
		*dst++ = *src++;
}

void  ppp_exec(struct _ppp* ppp)
{
	mutex_lock(&ppp->mutex);

	ppp_enable_it(ppp, PPP_IER_IRQ0);

	/* Send a CMD_TO_AVR => PPP_ISR_AVR8_IRQ_0 = (1 << 24)*/
	ppp_notify(ppp, PPP_ICR_NOTIFY0);

	while (mutex_is_locked(&ppp->mutex));
}
