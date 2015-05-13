/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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

/** \file */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "core/pio_it.h"
#include "core/aic.h"
#include "core/pmc.h"
#include "utils/trace.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* Maximum number of interrupt sources that can be defined. This
 * constant can be increased, but the current value is the smallest possible
 * that will be compatible with all existing projects. */
#define MAX_INTERRUPT_SOURCES       7

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

/**
 * Describes a PIO interrupt source, including the PIO instance triggering the
 * interrupt and the associated interrupt handler.
 */
struct _interrupt_source {
	const struct _pin *pin;					/* Pointer to the source pin instance. */
	void (*handler) (const struct _pin *); 	/* Interrupt handler. */
} ;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* List of interrupt sources. */
static struct _interrupt_source int_sources[MAX_INTERRUPT_SOURCES];

/* Number of currently defined interrupt sources. */
static uint32_t num_sources = 0;

const uint8_t idt[PIOIO_GROUP_NUMBER] = {ID_PIOA, ID_PIOB, ID_PIOC, ID_PIOD};

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Handles all interrupts on the given PIO controller.
 * \param id  PIO controller ID.
 * \param pPio  PIO controller base address.
 */
void _pio_it_handler(uint8_t id)
{
	uint32_t status;
	uint32_t i;
	PioIo_group* pioiog = &PIO_ADD->PIO_IO_GROUP[id];

	/* Read PIO controller status */
	status = pioiog->PIO_ISR;
	status &= pioiog->PIO_IMR;

	/* Check pending events */
	if (status != 0) {
		TRACE_DEBUG("PIO interrupt on PIO controller #%d\n\r", id);
		/* Find triggering source */
		i = 0;
		while (status != 0) {
			/* There cannot be an unconfigured source enabled. */
			assert(i < num_sources);
			/* Source is configured on the same controller */
			if ( int_sources[i].pin->id == id) {
				/* Source has PIOs whose statuses have changed */
				if ((status & int_sources[i].pin->mask) != 0) {
					TRACE_DEBUG ("Interrupt source #%d triggered\n\r", i);
					int_sources[i].handler(int_sources[i].pin);
					status &= ~(int_sources[i].pin->mask);
				}
			}
			i++;
		}
	}
}


/*----------------------------------------------------------------------------
 *        Global Functions
 *----------------------------------------------------------------------------*/

/**
 * Generic PIO interrupt handler. Single entry point for interrupts coming
 * from any PIO controller (PIO A, B, C ...). Dispatches the interrupt to
 * the user-configured handlers.
 */
void pio_it_handler(void)
{
	uint8_t i;
	for(i=0; i<PIOIO_GROUP_NUMBER; i++) {
		_pio_it_handler(idt[i]);
	}
}

/**
 * \brief Initializes the PIO interrupt management logic
 *
 * The desired priority of PIO interrupts must be provided.
 * Calling this function multiple times result in the reset of currently
 * configured interrupts.
 *
 * \param priority  PIO controller interrupts priority.
 */
void pio_initialize_it(uint32_t priority)
{
	uint8_t i;
	uint32_t status, id ;

	TRACE_DEBUG("pio_initialize_it()\n\r");
	/* Reset sources */
	num_sources = 0;

	for(i=0; i<PIOIO_GROUP_NUMBER; i++) {
		/* Configure PIO interrupt sources */
		id = idt[i];
		TRACE_DEBUG("PIO_Initialize: Configuring PIO%c \n\r", 0x40+id);
		pmc_enable_peripheral(id);
		PioIo_group* pioiog = &PIO_ADD->PIO_IO_GROUP[id];
		/* Read PIO Interrupt Status Register */
		status = pioiog->PIO_ISR;
		/* Disable all interrupt */
		pioiog->PIO_IDR = 0xFFFFFFFF;
		aic_enable(id);
	}
}

/**
 * Configures a PIO or a group of PIO to generate an interrupt on status
 * change. The provided interrupt handler will be called with the triggering
 * pin as its parameter (enabling different pin instances to share the same
 * handler).
 * \param pPin  Pointer to a Pin instance.
 */
void pio_configure_it(const struct _pin *pin)
{
	TRACE_DEBUG("pio_configure_it()\n\r");
	assert(pin != NULL);
	assert(num_sources < MAX_INTERRUPT_SOURCES);
	struct _interrupt_source *p_int_source;
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];

	// Add pio interrupt to int_sources
	p_int_source = &(int_sources[num_sources]);
	p_int_source->pin = pin;
	num_sources++;
	/* disable additional interrupt mode */
	pioiog->PIO_IDR = pin->mask;
}

/**
 * Enables the given interrupt source if it has been configured. The status
 * register of the corresponding PIO controller is cleared prior to enabling
 * the interrupt.
 * \param pin  Interrupt source to enable.
 */
void pio_enable_it(const struct _pin *pin)
{
	TRACE_DEBUG("pio_enable_it() \n\r");
	assert(pin != NULL);
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];

#ifndef NOASSERT
	uint32_t i = 0;
	uint32_t dwFound = 0;

	while ((i < num_sources) && !dwFound) {
		if (int_sources[i].pin == pin) {
			dwFound = 1;
		}
		i++;
	}
	assert(dwFound != 0);
#endif

	i = pioiog->PIO_ISR;
 	/* Configure interrupt enable register */
	pioiog->PIO_IER = pin->mask;	/* enable interrupt register */
}

/**
 * Disables a given interrupt source, with no added side effects.
 *
 * \param pin  Interrupt source to disable.
 */
void pio_disable_it(const struct _pin *pin)
{
	assert(pin != NULL);
	TRACE_DEBUG("pio_enable_it()\n\r");
	PioIo_group* pioiog = &pin->pio->PIO_IO_GROUP[pin->id];
	pioiog->PIO_IDR = pin->mask;
}
