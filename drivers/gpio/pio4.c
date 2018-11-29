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
 * <li>  Set a high or low output level on the given PIO using pio_set() or pio_clear().
 * <li>  Get the level of the given PIOs using pio_get() or pio_get_output_date_status().
 * <li>  Configures Glitch or Debouncing filter for given input PIO using pio_set_debounce_filter().
 * <li>  Enable & disable write protect of the given PIOs using pio_enable_write_protect() or pio_disable_write_protect().
 * <li>  Get write protect violation information of given PIO using pio_get_write_protect_violation_info().
 * </ul>
 *
 * For more accurate information, please look at the PIO section of the Datasheet.
 *
 * Related files:\n
 * \ref pio.h\n
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
#include "irq/irq.h"
#include "gpio/pio.h"
#include "peripherals/pmc.h"

#include "trace.h"
#include "compiler.h"

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

struct _handler {
	uint32_t      group;
	uint32_t      mask;
	pio_handler_t handler;
	void         *user_arg;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _handler _handlers[IRQ_PIO_HANDLERS_SIZE];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static uint32_t _pio_get_group_mask(uint32_t id)
{
	uint32_t group = 0;

#ifdef ID_PIOA
	if (id == ID_PIOA)
		group |= (1 << PIO_GROUP_A);
#endif
#ifdef ID_PIOB
	if (id == ID_PIOB)
		group |= (1 << PIO_GROUP_B);
#endif
#ifdef ID_PIOC
	if (id == ID_PIOC)
		group |= (1 << PIO_GROUP_C);
#endif
#ifdef ID_PIOD
	if (id == ID_PIOD)
		group |= (1 << PIO_GROUP_D);
#endif
#ifdef ID_PIOE
	if (id == ID_PIOE)
		group |= (1 << PIO_GROUP_E);
#endif

	return group;
}

static PioIo* _pio_get_instance(uint32_t group)
{
	assert(group < PIO_GROUP_LENGTH);
	return &PIOA->PIO_IO[group];
}

static uint32_t _pio_get_periph_id(uint32_t group)
{
	switch (group) {
#ifdef ID_PIOA
	case PIO_GROUP_A:
		return ID_PIOA;
#endif
#ifdef ID_PIOB
	case PIO_GROUP_B:
		return ID_PIOB;
#endif
#ifdef ID_PIOC
	case PIO_GROUP_C:
		return ID_PIOC;
#endif
#ifdef ID_PIOD
	case PIO_GROUP_D:
		return ID_PIOD;
#endif
#ifdef ID_PIOE
	case PIO_GROUP_E:
		return ID_PIOE;
#endif
	default:
		trace_fatal("Invalid PIO group!");
	}
}

static void _handler_push(uint32_t group, uint32_t mask, pio_handler_t handler, void* user_arg)
{
	static int i = 0;
	assert(i < (ARRAY_SIZE(_handlers) - 1));
	_handlers[i].group = group;
	_handlers[i].mask = mask;
	_handlers[i].handler = handler;
	_handlers[i].user_arg = user_arg;
	i++;
}

static void _pio_handle_interrupt(uint32_t group)
{
	int i;
	uint32_t status = PIOA->PIO_IO[group].PIO_ISR;
	for (i = 0; i < ARRAY_SIZE(_handlers); i++) {
		if (_handlers[i].group == group && (_handlers[i].mask & status))
			_handlers[i].handler(group, status, _handlers[i].user_arg);
	}
}

static void _pio_handler(uint32_t source, void* user_arg)
{
	uint32_t group_mask = _pio_get_group_mask(source);

#ifdef ID_PIOA
	if (group_mask & (1 << PIO_GROUP_A))
		_pio_handle_interrupt(PIO_GROUP_A);
#endif
#ifdef ID_PIOB
	if (group_mask & (1 << PIO_GROUP_B))
		_pio_handle_interrupt(PIO_GROUP_B);
#endif
#ifdef ID_PIOC
	if (group_mask & (1 << PIO_GROUP_C))
		_pio_handle_interrupt(PIO_GROUP_C);
#endif
#ifdef ID_PIOD
	if (group_mask & (1 << PIO_GROUP_D))
		_pio_handle_interrupt(PIO_GROUP_D);
#endif
#ifdef ID_PIOE
	if (group_mask & (1 << PIO_GROUP_E))
		_pio_handle_interrupt(PIO_GROUP_E);
#endif
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

void pio_configure(const struct _pin *pin_list, uint32_t size)
{
	int i;

	for (i = 0; i < size; i++) {
		const struct _pin *pin = &pin_list[i];
		PioIo* pio = _pio_get_instance(pin->group);
		uint32_t cfgr = 0;

		/* Disable interrupts */
		pio->PIO_IDR = pin->mask;

		/* The PIO input logic requires the peripheral clock */
		if (pin->type == PIO_INPUT)
			pmc_configure_peripheral(ID_PIOA, NULL, true);

#ifdef CONFIG_HAVE_PIO4_SECURE
		/* Configure pins as non-secure */
		PIOA->S_PIO_IO[pin->group].S_PIO_SIONR = pin->mask;
#endif

		/* Enable pull-up resistors as requested */
		if (pin->attribute & PIO_PULLUP)
			cfgr |= PIO_CFGR_PUEN_ENABLED;

		/* Enable pull-down resistors as requested */
		if (pin->attribute & PIO_PULLDOWN)
			cfgr |= PIO_CFGR_PDEN_ENABLED;

		/* Select open-drain output stage as requested */
		if (pin->attribute & PIO_OPENDRAIN)
			cfgr |= PIO_CFGR_OPD_ENABLED;

		if (pin->attribute & (PIO_DEGLITCH | PIO_DEBOUNCE))
			cfgr |= PIO_CFGR_IFEN_ENABLED;

		if (pin->attribute & PIO_DEBOUNCE)
			cfgr |= PIO_CFGR_IFSCEN_ENABLED;

		if (pin->attribute & PIO_NO_SCHMITT_TRIG)
			cfgr |= PIO_CFGR_SCHMITT_DISABLED;

		if (pin->attribute & PIO_CRTL_SLEWR)
			trace_fatal("Invalid slew rate setting\r\n");

		switch (pin->attribute & PIO_DRVSTR_MASK) {
		case PIO_DRVSTR_LO:
			cfgr |= PIO_CFGR_DRVSTR_LO;
			break;
#ifdef PIO_CFGR_DRVSTR_ME
		case PIO_DRVSTR_ME:
			cfgr |= PIO_CFGR_DRVSTR_ME;
			break;
#endif
		case PIO_DRVSTR_HI:
			cfgr |= PIO_CFGR_DRVSTR_HI;
			break;
		default:
			trace_fatal("Invalid pin drive strength\r\n");
			break;
		}

		switch (pin->attribute & PIO_IT_MASK) {
		case PIO_IT_FALL_EDGE:
			cfgr |= PIO_CFGR_EVTSEL_FALLING;
			break;
		case PIO_IT_RISE_EDGE:
			cfgr |= PIO_CFGR_EVTSEL_RISING;
			break;
		case PIO_IT_BOTH_EDGE:
			cfgr |= PIO_CFGR_EVTSEL_BOTH;
			break;
		case PIO_IT_LOW_LEVEL:
			cfgr |= PIO_CFGR_EVTSEL_LOW;
			break;
		case PIO_IT_HIGH_LEVEL:
			cfgr |= PIO_CFGR_EVTSEL_HIGH;
			break;
		default:
			trace_fatal("Invalid pin interrupt type\r\n");
			break;
		}

		switch (pin->type) {
		case PIO_PERIPH_A:
			cfgr |= PIO_CFGR_FUNC_PERIPH_A;
			break;
		case PIO_PERIPH_B:
			cfgr |= PIO_CFGR_FUNC_PERIPH_B;
			break;
		case PIO_PERIPH_C:
			cfgr |= PIO_CFGR_FUNC_PERIPH_C;
			break;
		case PIO_PERIPH_D:
			cfgr |= PIO_CFGR_FUNC_PERIPH_D;
			break;
		case PIO_PERIPH_E:
			cfgr |= PIO_CFGR_FUNC_PERIPH_E;
			break;
		case PIO_PERIPH_F:
			cfgr |= PIO_CFGR_FUNC_PERIPH_F;
			break;
		case PIO_PERIPH_G:
			cfgr |= PIO_CFGR_FUNC_PERIPH_G;
			break;
		case PIO_INPUT:
			break;
		case PIO_OUTPUT_0:
		case PIO_OUTPUT_1:
			if (pin->type == PIO_OUTPUT_1)
				pio->PIO_SODR = pin->mask;
			else
				pio->PIO_CODR = pin->mask;
			cfgr |= PIO_CFGR_DIR_OUTPUT;
			break;
		default:
			trace_fatal("Invalid pin type\r\n");
		}

		pio->PIO_MSKR = pin->mask;
		pio->PIO_CFGR = cfgr;
	}
}

void pio_set(const struct _pin *pin)
{
	PioIo* pio = _pio_get_instance(pin->group);
	pio->PIO_SODR = pin->mask;
}

void pio_clear(const struct _pin *pin)
{
	PioIo* pio = _pio_get_instance(pin->group);
	pio->PIO_CODR = pin->mask;
}

uint32_t pio_get(const struct _pin *pin)
{
	PioIo* pio = _pio_get_instance(pin->group);
	if ((pin->type == PIO_OUTPUT_0) || (pin->type == PIO_OUTPUT_1))
		return pio->PIO_ODSR & pin->mask;
	else
		return pio->PIO_PDSR & pin->mask;
}

uint32_t pio_get_output_data_status(const struct _pin *pin)
{
	PioIo* pio = _pio_get_instance(pin->group);
	return pio->PIO_ODSR & pin->mask;
}

void pio_set_debounce_filter(uint32_t cutoff)
{
	cutoff = ((pmc_get_slow_clock() / (2 * cutoff)) - 1) & 0x3FFF;
#ifdef CONFIG_HAVE_PIO4_SECURE
	PIOA->S_PIO_SCDR = cutoff;
#else
	PIOA->PIO_SCDR = cutoff;
#endif
}

void pio_enable_write_protect(void)
{
	PIOA->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD | PIO_WPMR_WPEN;
}

void pio_disable_write_protect(void)
{
	PIOA->PIO_WPMR = PIO_WPMR_WPKEY_PASSWD;
}

uint32_t pio_get_write_protect_violation_info(void)
{
	return PIOA->PIO_WPSR;
}

void pio_add_handler_to_group(uint32_t group, uint32_t mask,
			      pio_handler_t handler, void* user_arg)
{
	uint32_t periph_id = _pio_get_periph_id(group);

	_handler_push(group, mask, handler, user_arg);

	irq_add_handler(periph_id, _pio_handler, NULL);
	irq_enable(periph_id);
}

void pio_reset_all_it(void)
{
	int i;
	for (i = 0; i < PIO_GROUP_LENGTH; i++) {
		PioIo* pio = _pio_get_instance(i);
		pio->PIO_ISR;
		pio->PIO_IDR = ~0u;
	}
}

void pio_enable_it(const struct _pin *pin)
{
	assert(pin);
	PioIo* pio = _pio_get_instance(pin->group);
	pio->PIO_IER = pin->mask;
}

void pio_disable_it(const struct _pin *pin)
{
	assert(pin);
	PioIo* pio = _pio_get_instance(pin->group);
	pio->PIO_IDR = pin->mask;
}
