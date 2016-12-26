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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "trace.h"
#include "irqflags.h"

#include "irq/aic.h"
#include "irq/irq.h"
#include "peripherals/matrix.h"

#include <stdint.h>
#include <assert.h>
#include <errno.h>

/*------------------------------------------------------------------------------
 *         Local functions
 *------------------------------------------------------------------------------*/

static void spurious_handler(void)
{
	// nothing here
}

/**
 * \brief Interrupt Init.
 */
static void _aic_initialize(Aic* aic, aic_handler_t irq_handler)
{
	int i;

	/* Disable all interrupts and clear pending flags */
	for (i = 1; i < ID_PERIPH_COUNT; i++)
	{
		aic->AIC_SSR = i;
		aic->AIC_IDCR = AIC_IDCR_INTD;
		aic->AIC_ICCR = AIC_ICCR_INTCLR;
	}

	/* Perform 8 IT acknowledge (write any value in EOICR) */
	for (i = 0; i < 8; i++)
		aic->AIC_EOICR = 0;

	/* Assign default handlers */
	for (i = 0; i < ID_PERIPH_COUNT; i++)
	{
		aic->AIC_SSR = i;
		aic->AIC_SVR = (uint32_t)irq_handler;
	}
	aic->AIC_SPU = (uint32_t)spurious_handler;
}

static Aic* _get_aic_instance(uint32_t source)
{
#ifdef CONFIG_HAVE_SAIC
	if (SFR->SFR_AICREDIR == 0) {
		Matrix* matrix = get_peripheral_matrix(source);
		if (matrix_is_peripheral_secured(matrix, source))
			return SAIC;
	}
#endif /* CONFIG_HAVE_SAIC */
	return AIC;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void aic_initialize(aic_handler_t irq_handler)
{
	/* Disable interrupts at core level */
	arch_irq_disable();

	/* Set default vectors */
	_aic_initialize(AIC, irq_handler);
#ifdef CONFIG_HAVE_SAIC
	_aic_initialize(SAIC, irq_handler);

	/* Redirect all interrupts to Non-secure AIC */
	uint32_t aicredir = SFR_AICREDIR_AICREDIRKEY((uint32_t)(AICREDIR_KEY));
	SFR->SFR_AICREDIR = (aicredir ^ SFR->SFR_SN1) | SFR_AICREDIR_NSAIC;
#endif /* CONFIG_HAVE_SAIC */

	/* Enable interrupts at core level */
	arch_irq_enable();
}

void aic_set_source_vector(uint32_t source, aic_handler_t handler)
{
	Aic *aic = _get_aic_instance(source);
	aic->AIC_SSR = AIC_SSR_INTSEL(source);
	aic->AIC_SVR = (uint32_t)handler;
}

void aic_set_spurious_vector(aic_handler_t handler)
{
	AIC->AIC_SPU = (uint32_t)handler;
#ifdef CONFIG_HAVE_SAIC
	if (SFR->SFR_AICREDIR == 0)
		SAIC->AIC_SPU = (uint32_t)handler;
#endif
}

void aic_configure_mode(uint32_t source, enum _irq_mode mode)
{
	uint32_t srctype;

	switch (mode) {
	case IRQ_MODE_HIGH_LEVEL:
		srctype = AIC_SMR_SRCTYPE_EXT_HIGH_LEVEL;
		break;
	case IRQ_MODE_LOW_LEVEL:
		srctype = AIC_SMR_SRCTYPE_INT_LEVEL_SENSITIVE;
		break;
	case IRQ_MODE_POSITIVE_EDGE:
		srctype = AIC_SMR_SRCTYPE_EXT_POSITIVE_EDGE;
		break;
	case IRQ_MODE_NEGATIVE_EDGE:
		srctype = AIC_SMR_SRCTYPE_INT_EDGE_TRIGGERED;
		break;
	default:
		trace_fatal("Invalid interrupt mode: %d\r\n", (int)mode);
	}

	Aic* aic = _get_aic_instance(source);
	aic->AIC_SSR = source;
	aic->AIC_IDCR = AIC_IDCR_INTD;
	aic->AIC_SMR = (aic->AIC_SMR & ~AIC_SMR_SRCTYPE_Msk) | srctype;
	aic->AIC_ICCR = AIC_ICCR_INTCLR;
}

void aic_configure_priority(uint32_t source, uint8_t priority)
{
	Aic* aic = _get_aic_instance(source);
	aic->AIC_SSR = source;
	aic->AIC_IDCR = AIC_IDCR_INTD;
	aic->AIC_SMR = (aic->AIC_SMR & ~AIC_SMR_PRIOR_Msk) | AIC_SMR_PRIOR(priority);
	aic->AIC_ICCR = AIC_ICCR_INTCLR;
}

void aic_enable(uint32_t source)
{
	Aic* aic = _get_aic_instance(source);
	aic->AIC_SSR = AIC_SSR_INTSEL(source);
	aic->AIC_IECR = AIC_IECR_INTEN;
}

void aic_disable(uint32_t source)
{
	Aic* aic = _get_aic_instance(source);
	aic->AIC_SSR = AIC_SSR_INTSEL(source);
	aic->AIC_IDCR = AIC_IDCR_INTD;
}

uint32_t aic_get_current_interrupt_source(void)
{
	return AIC->AIC_ISR;
}

void aic_set_debug_config(Aic* aic, bool protect, bool mask)
{
	uint32_t dcr = 0;
	if (protect)
		dcr |= AIC_DCR_PROT;
	if (mask)
		dcr |= AIC_DCR_GMSK;
	aic->AIC_DCR = dcr;
}

void aic_set_write_protection(Aic* aic, bool enable)
{
	if (enable)
		aic->AIC_WPMR = AIC_WPMR_WPKEY_PASSWD | AIC_WPMR_WPEN;
	else
		aic->AIC_WPMR = AIC_WPMR_WPKEY_PASSWD;
}

bool aic_check_write_protection_violation(Aic* aic, uint32_t* wpvsrc)
{
	if (aic->AIC_WPSR & AIC_WPSR_WPVS) {
		*wpvsrc = (aic->AIC_WPSR & AIC_WPSR_WPVSRC_Msk) >> AIC_WPSR_WPVSRC_Pos;
		return true;
	}
	return false;
}
