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

/** \addtogroup pio_module Working with PIO
 * \section Purpose
 * The PIO driver provides the Interface for configuration the Parallel Input/Output
 *  Controller (PIO).
 *
 * \section Usage
 * <ul>
 * <li>  Initialize the PIO with the desired period using pio_configure().
 * <li>  Set a high or low output level on the given PIO using
 * pio_set() or pio_clear().
 * <li>  Get the level of the given PIOs using pio_get() or
 * pio_get_output_date_status().
 * <li>  Configures Glitch or Debouncing filter for given input PIO
 * using pio_set_debounce_filter().
 * <li>  Enable & disable write protect of the given PIOs using
 * pio_enable_write_protect() or pio_disable_write_protect().
 * <li>  Get write protect violation information of given PIO using
 * pio_get_write_protect_violation_info().
 * </ul>
 *
 * For more accurate information, please look at the PIT section of
 * the Datasheet.
 *
 * Related files :\n
 * \ref pio.c\n
 * \ref pio3.h\n
*/
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of PIO V3 (Parallel Input/Output) controller.
 *
 */
/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/aic.h"

#include "trace.h"
#include "compiler.h"

#include <stdio.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local functions declarations
 *----------------------------------------------------------------------------*/

#ifdef PIOA
static void _pioa_handler(void);
#endif
#ifdef PIOB
static void _piob_handler(void);
#endif
#ifdef PIOC
static void _pioc_handler(void);
#endif
#ifdef PIOD
static void _piod_handler(void);
#endif
#ifdef PIOE
static void _pioe_handler(void);
#endif

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
struct _handler {
	uint32_t mask;
	pio_handler_t handler;
	void *user_arg;
};
static struct _handler _handlers[IRQ_PIO_HANDLERS_SIZE];

static const aic_handler_t _generic_handlers[PIO_GROUP_LENGTH] = {
#ifdef PIOA
	_pioa_handler,
#endif
#ifdef PIOB
	_piob_handler,
#endif
#ifdef PIOC
	_pioc_handler,
#endif
#ifdef PIOD
	_piod_handler,
#endif
#ifdef PIOE
	_pioe_handler,
#endif
};

/*----------------------------------------------------------------------------
 *        Local functions definitions
 *----------------------------------------------------------------------------*/

static void _handler_push(void (*handler)(uint32_t, uint32_t, void*), uint32_t mask, void* user_arg)
{
	static int i = 0;
	_handlers[i].mask = mask;
	_handlers[i].handler = handler;
	_handlers[i].user_arg = user_arg;
	++i;
	assert(i < ARRAY_SIZE(_handlers));
}

#ifdef PIOA
static void _pioa_handler(void)
{
	uint32_t status = PIOA->PIO_ISR;
	int i = 0;
	for (i = 0; i < ARRAY_SIZE(_handlers); ++i) {
		if (_handlers[i].mask & status) {
			_handlers[i].handler(PIO_GROUP_A, status,
					_handlers[i].user_arg);
		}
	}
}
#endif
#ifdef PIOB
static void _piob_handler(void)
{
	uint32_t status = PIOB->PIO_ISR;
	int i = 0;
	for (i = 0; i < ARRAY_SIZE(_handlers); ++i) {
		if (_handlers[i].mask & status) {
			_handlers[i].handler(PIO_GROUP_B, status,
					_handlers[i].user_arg);
		}
	}
}
#endif
#ifdef PIOC
static void _pioc_handler(void)
{
	uint32_t status = PIOC->PIO_ISR;
	int i = 0;
	for (i = 0; i < ARRAY_SIZE(_handlers); ++i) {
		if (_handlers[i].mask & status) {
			_handlers[i].handler(PIO_GROUP_C, status,
					_handlers[i].user_arg);
		}
	}
}
#endif
#ifdef PIOD
static void _piod_handler(void)
{
	uint32_t status = PIOD->PIO_ISR;
	int i = 0;
	for (i = 0; i < ARRAY_SIZE(_handlers); ++i) {
		if (_handlers[i].mask & status) {
			_handlers[i].handler(PIO_GROUP_D, status,
					_handlers[i].user_arg);
		}
	}
}
#endif
#ifdef PIOE
static void _pioe_handler(void)
{
	uint32_t status = PIOE->PIO_ISR;
	int i = 0;
	for (i = 0; i < ARRAY_SIZE(_handlers); ++i) {
		if (_handlers[i].mask & status) {
			_handlers[i].handler(PIO_GROUP_E, status,
					_handlers[i].user_arg);
		}
	}
}
#endif

static uint32_t _pio_get_index(int group)
{
	uint32_t ix = PIO_GROUP_LENGTH;

	if (group == PIO_GROUP_A)
		ix = 0;
	else if (group == PIO_GROUP_B)
		ix = 1;
	else if (group == PIO_GROUP_C)
		ix = 2;
	else if (group == PIO_GROUP_D)
		ix = 3;
	else if (group == PIO_GROUP_E)
		ix = 4;
	else
		trace_fatal("Invalid PIO group!");
	return ix;
}

static Pio *_pio_get_instance(int group)
{
	Pio *pio = NULL;

	if (group == PIO_GROUP_A)
		pio = PIOA;
	else if (group == PIO_GROUP_B)
		pio = PIOB;
	else if (group == PIO_GROUP_C)
		pio = PIOC;
	else if (group == PIO_GROUP_D)
		pio = PIOD;
	else if (group == PIO_GROUP_E)
		pio = PIOE;
	else
		trace_fatal("Invalid PIO group!");
	return pio;
}

static uint32_t _pio_get_periph_id(int group)
{
	uint32_t id = ID_PERIPH_COUNT;

	if (group == PIO_GROUP_A)
		id = ID_PIOA;
	else if (group == PIO_GROUP_B)
		id = ID_PIOB;
	else if (group == PIO_GROUP_C)
		id = ID_PIOC;
	else if (group == PIO_GROUP_D)
		id = ID_PIOD;
	else if (group == PIO_GROUP_E)
		id = ID_PIOE;
	else
		trace_fatal("Invalid PIO group!");
	return id;
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

uint8_t pio_configure(const struct _pin *pin, uint32_t size)
{
	Pio* pio = NULL;

	for ( ; size != 0; size--, pin++) {
		pio = _pio_get_instance(pin->group);
		assert(pio);

		/* Disable interrupts */
		pio->PIO_IDR = pin->mask;
		/* The PIO input logic requires the peripheral clock */
		if (pin->type == PIO_INPUT)
			pmc_enable_peripheral(pin->group);
		/* Enable pull-up or pull-down resistors as requested */
		if (pin->attribute & PIO_PULLDOWN) {
			pio->PIO_PUDR = pin->mask;
			pio->PIO_PPDER = pin->mask;
		} else if (pin->attribute & PIO_PULLUP) {
			pio->PIO_PPDDR = pin->mask;
			pio->PIO_PUER = pin->mask;
		} else {
			pio->PIO_PUDR = pin->mask;
			pio->PIO_PPDDR = pin->mask;
		}
		/* Select push-pull or multi-driver (open-drain) output stage */
		if (pin->attribute & PIO_OPENDRAIN)
			pio->PIO_MDER = pin->mask;
		else
			pio->PIO_MDDR = pin->mask;
		/* Enable the input filter if requested */
		if (pin->attribute & (PIO_DEGLITCH | PIO_DEBOUNCE))
			pio->PIO_IFER = pin->mask;
		else
			pio->PIO_IFDR = pin->mask;
		/* The de-bounce input filter depends on the slow clock */
		if (pin->attribute & PIO_DEBOUNCE)
			pio->PIO_IFSCER = pin->mask;
		else
			pio->PIO_IFSCDR = pin->mask;

		switch (pin->type) {

		case PIO_PERIPH_A:
			/* Give control of the pin(s) to the specified
			 * peripheral */
			pio->PIO_ABCDSR[0] &= ~pin->mask;
			pio->PIO_ABCDSR[1] &= ~pin->mask;
			pio->PIO_PDR = pin->mask;
			break;

		case PIO_PERIPH_B:
			pio->PIO_ABCDSR[0] |= pin->mask;
			pio->PIO_ABCDSR[1] &= ~pin->mask;
			pio->PIO_PDR = pin->mask;
			break;

		case PIO_PERIPH_C:
			pio->PIO_ABCDSR[0] &= ~pin->mask;
			pio->PIO_ABCDSR[1] |= pin->mask;
			pio->PIO_PDR = pin->mask;
			break;

		case PIO_PERIPH_D:
			pio->PIO_ABCDSR[0] |= pin->mask;
			pio->PIO_ABCDSR[1] |= pin->mask;
			pio->PIO_PDR = pin->mask;
			break;

		case PIO_INPUT:
			/* Give control of the pin(s) to the PIO (vs to the
			 * peripheral), and disable the output stage */
			pio->PIO_ODR = pin->mask;
			pio->PIO_PER = pin->mask;
			break;

		case PIO_OUTPUT_0:
		case PIO_OUTPUT_1:
			/* Select the logic level to be driven */
			if (pin->type == PIO_OUTPUT_1)
				pio->PIO_SODR = pin->mask;
			else
				pio->PIO_CODR = pin->mask;
			/* Give control of the pin(s) to the PIO (vs to the
			 * peripheral), and enable the output stage */
			pio->PIO_OER = pin->mask;
			pio->PIO_PER = pin->mask;
			break;

		default:
			return 0;
		}
	}
	return 1;
}

void pio_set(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_SODR = pin->mask;
}

void pio_clear(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_CODR = pin->mask;
}

uint8_t pio_get(const struct _pin *pin)
{
	uint32_t reg;

	Pio* pio = _pio_get_instance(pin->group);
	if ((pin->type == PIO_OUTPUT_0) || (pin->type == PIO_OUTPUT_1)) {
		reg = pio->PIO_ODSR;
	} else {
		reg = pio->PIO_PDSR;
	}
	if ((reg & pin->mask) == 0) {
		return 0;
	} else {
		return 1;
	}
}

uint8_t pio_get_output_data_status(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	if ((pio->PIO_ODSR & pin->mask) == 0) {
		return 0;
	} else {
		return 1;
	}
}

void pio_set_debounce_filter(const struct _pin *pin, uint32_t cuttoff)
{
	Pio* pio = _pio_get_instance(pin->group);
	if (cuttoff == 0) {
		pio->PIO_IFSCDR = pin->mask;
		pio->PIO_SCDR = 0;
	} else {
		/* set Debouncing, 0 bit field no effect */
		pio->PIO_IFSCER = pin->mask;
		/* the lowest 14 bits work */
		pio->PIO_SCDR = ((32678 / (2 * (cuttoff))) - 1) & 0x3FFF;
	}
}

void pio_enable_write_protect(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_WPMR = (PIO_WPMR_WPKEY_PASSWD | PIO_WPMR_WPEN);
}

void pio_disable_write_protect(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD;
}

uint32_t pio_get_write_protect_violation_info(const struct _pin * pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	return (pio->PIO_WPSR);
}

void pio_output_low(uint32_t group, uint32_t mask)
{
	Pio* pio = _pio_get_instance(group);
	pmc_enable_peripheral(_pio_get_periph_id(group));
	pio->PIO_PUDR = mask;	// all Pull-up Disable
	pio->PIO_PPDDR = mask;	// all Pull-down Disable
	pio->PIO_PER = mask;	// all PIO enable
	pio->PIO_OER = mask;	// all PIO output mode
	pio->PIO_CODR = mask;	// all PIO clear output
}

void pio_add_handler_to_group(uint32_t group, uint32_t mask,
			      pio_handler_t handler, void* user_arg)
{
	assert(group < ID_PERIPH_COUNT);
	uint32_t index = _pio_get_index(group);
	assert(index <
	       (sizeof(_generic_handlers)/sizeof(_generic_handlers[0])));
	_handler_push(handler, mask, user_arg);
	aic_set_source_vector(group,
			      (aic_handler_t)_generic_handlers[index]);
	aic_enable(group);
}

void pio_reset_all_it(void)
{
#ifdef PIOA
	PIOA->PIO_ISR;
	PIOA->PIO_IDR = ~0;
#endif
#ifdef PIOB
	PIOB->PIO_ISR;
	PIOB->PIO_IDR = ~0;
#endif
#ifdef PIOC
	PIOC->PIO_ISR;
	PIOC->PIO_IDR = ~0;
#endif
#ifdef PIOD
	PIOD->PIO_ISR;
	PIOD->PIO_IDR = ~0;
#endif
#ifdef PIOE
	PIOE->PIO_ISR;
	PIOE->PIO_IDR = ~0;
#endif
}

void pio_configure_it(const struct _pin * pin)
{
	assert(pin);

	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_IDR = pin->mask;

	/* PIO with additional interrupt support
	 * Configure additional interrupt mode registers */
	if (pin->attribute & PIO_IT_AIME) {
		/* enable additional interrupt mode */
		pio->PIO_AIMER = pin->mask;

		/* if bit field of selected pin is 1, set as Rising
		 * Edge/High level detection event */
		if (pin->attribute & PIO_IT_RE_OR_HL) {
			pio->PIO_REHLSR = pin->mask;
		} else {
			pio->PIO_FELLSR = pin->mask;
		}

		/* if bit field of selected pin is 1, set as edge
		 * detection source */
		if (pin->attribute & PIO_IT_EDGE)
			pio->PIO_ESR = pin->mask;
		else
			pio->PIO_LSR = pin->mask;
	} else {
		/* disable additional interrupt mode */
		pio->PIO_AIMDR = pin->mask;
	}
}

void pio_enable_it(const struct _pin * pin)
{
	assert(pin != NULL);

	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_ISR;
	pio->PIO_IER = pin->mask;
}

void pio_disable_it(const struct _pin * pin)
{
	assert(pin != NULL);

	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_IDR = pin->mask;
}
