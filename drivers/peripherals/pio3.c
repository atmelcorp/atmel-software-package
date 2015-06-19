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

#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

typedef const void(*const_handler_t)(void);
typedef void(*handler_t)(void);

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
	void (*handler)(uint32_t, uint32_t);
};
static struct _handler _handlers[IRQ_PIO_HANDLERS_SIZE];

static const void (*_generic_handlers[PIO_GROUP_LENGTH])(void) = {
#ifdef PIOA
	(const_handler_t)_pioa_handler,
#endif
#ifdef PIOB
	(const_handler_t)_piob_handler,
#endif
#ifdef PIOC
	(const_handler_t)_pioc_handler,
#endif
#ifdef PIOD
	(const_handler_t)_piod_handler,
#endif
#ifdef PIOE
	(const_handler_t)_pioe_handler,
#endif
};

/*----------------------------------------------------------------------------
 *        Local functions definitions
 *----------------------------------------------------------------------------*/

static void _handler_push(void (*handler)(uint32_t, uint32_t), uint32_t mask)
{
	static int i = 0;
	_handlers[i].mask = mask;
	_handlers[i].handler = handler;
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
			_handlers[i].handler(PIO_GROUP_A, status);
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
			_handlers[i].handler(PIO_GROUP_B, status);
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
			_handlers[i].handler(PIO_GROUP_C, status);
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
			_handlers[i].handler(PIO_GROUP_D, status);
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
			_handlers[i].handler(PIO_GROUP_E, status);
		}
	}
}
#endif

static uint32_t _pio_get_index(int group)
{
	switch(group) {
	case PIO_GROUP_A:
		return 0;
	case PIO_GROUP_B:
		return 1;
	case PIO_GROUP_C:
		return 2;
	case PIO_GROUP_D:
		return 3;
	case PIO_GROUP_E:
		return 4;
	default:
		trace_fatal("Invalid PIO group!");
		return -1;
	};
}

static Pio *_pio_get_instance(int group)
{
	switch(group) {
	case PIO_GROUP_A:
		return PIOA;
	case PIO_GROUP_B:
		return PIOB;
	case PIO_GROUP_C:
		return PIOC;
	case PIO_GROUP_D:
		return PIOD;
	case PIO_GROUP_E:
		return PIOE;
	default:
		trace_fatal("Invalid PIO group!");
		return NULL;
	};
}

/**
 * \brief Configures one or more pin(s) of a PIO controller as being
 * controlled by peripheral A. Optionally, the corresponding internal
 * pull-up(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
static void pio_set_peripheralA(Pio * pio, uint32_t mask, uint8_t enablePullUp)
{
	uint32_t abcdsr;
	/* Disable interrupts on the pin(s) */
	pio->PIO_IDR = mask;
	/* Enable the pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		//pio->PIO_PUDR = mask;
		pio->PIO_PPDDR = mask;
	}
	abcdsr = pio->PIO_ABCDSR[0];
	pio->PIO_ABCDSR[0] &= (~mask & abcdsr);
	abcdsr = pio->PIO_ABCDSR[1];
	pio->PIO_ABCDSR[1] &= (~mask & abcdsr);
	pio->PIO_PDR = mask;

}

/**
 * \brief Configures one or more pin(s) of a PIO controller as being controlled
 * by peripheral B. Optionally, the corresponding internal pull-up(s) can be
 * enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
static void pio_set_peripheralB(Pio * pio, uint32_t mask, uint8_t enablePullUp)
{
	uint32_t abcdsr;
	/* Disable interrupts on the pin(s) */
	pio->PIO_IDR = mask;
	/* Enable the pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
		pio->PIO_PPDDR = mask;
	}
	abcdsr = pio->PIO_ABCDSR[0];
	pio->PIO_ABCDSR[0] = (mask | abcdsr);
	abcdsr = pio->PIO_ABCDSR[1];
	pio->PIO_ABCDSR[1] &= (~mask & abcdsr);
	pio->PIO_PDR = mask;
}

/**
 * \brief Configures one or more pin(s) of a PIO controller as being
 * controlled by peripheral C. Optionally, the corresponding internal
 * pull-up(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
static void pio_set_peripheralC(Pio * pio, uint32_t mask, uint8_t enablePullUp)
{
	uint32_t abcdsr;
	/* Disable interrupts on the pin(s) */
	pio->PIO_IDR = mask;
	/* Enable the pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
		//  pio->PIO_PPDDR = mask;
	}
	abcdsr = pio->PIO_ABCDSR[0];
	pio->PIO_ABCDSR[0] &= (~mask & abcdsr);
	abcdsr = pio->PIO_ABCDSR[1];
	pio->PIO_ABCDSR[1] = (mask | abcdsr);
	pio->PIO_PDR = mask;
}

/**
 * \brief Configures one or more pin(s) of a PIO controller as being
 * controlled by peripheral D. Optionally, the corresponding internal
 * pull-up(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask of one or more pin(s) to configure.
 * \param enablePullUp  Indicates if the pin(s) internal pull-up shall be
 *                      configured.
 */
static void pio_set_peripheralD(Pio * pio, uint32_t mask, uint8_t enablePullUp)
{
	uint32_t abcdsr;
	/* Disable interrupts on the pin(s) */
	pio->PIO_IDR = mask;
	/* Enable the pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
	}
	abcdsr = pio->PIO_ABCDSR[0];
	pio->PIO_ABCDSR[0] = (mask | abcdsr);
	abcdsr = pio->PIO_ABCDSR[1];
	pio->PIO_ABCDSR[1] = (mask | abcdsr);
	pio->PIO_PDR = mask;
}

/**
 * \brief Configures one or more pin(s) or a PIO controller as
 * inputs. Optionally, the corresponding internal pull-up(s) and
 * glitch filter(s) can be enabled.
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask indicating which pin(s) to configure as input(s).
 * \param enablePullUp  Indicates if the internal pull-up(s) must be enabled.
 * \param enableFilter  Indicates if the glitch filter(s) must be enabled.
 */
static void pio_set_input(Pio * pio, uint32_t mask, uint8_t attribute)
{
	/* Disable interrupts */
	pio->PIO_IDR = mask;
	/* Enable pull-up(s) if necessary */
	if (attribute & PIO_PULLUP) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
	}
	/* Enable Input Filter if necessary */
	if (attribute & (PIO_DEGLITCH | PIO_DEBOUNCE))
		pio->PIO_IFER = mask;
	else
		pio->PIO_IFDR = mask;
	/* Enable de-glitch or de-bounce if necessary */
	if (attribute & PIO_DEGLITCH) {
		pio->PIO_IFSCDR = mask;
	} else if (attribute & PIO_DEBOUNCE) {
		pio->PIO_IFSCER = mask;
	}
	/* Configure pin as input */
	pio->PIO_ODR = mask;
	pio->PIO_PER = mask;
}

/**
 * \brief Configures one or more pin(s) of a PIO controller as outputs, with the
 * given default value. Optionally, the multi-drive feature can be enabled
 * on the pin(s).
 *
 * \param pio  Pointer to a PIO controller.
 * \param mask  Bitmask indicating which pin(s) to configure.
 * \param defaultValue  Default level on the pin(s).
 * \param enableMultiDrive  Indicates if the pin(s) shall be configured as
 *                          open-drain.
 * \param enablePullUp  Indicates if the pin shall have its pull-up activated.
 */
static void pio_set_output(Pio * pio, uint32_t mask, uint8_t defaultValue,
			   uint8_t enableMultiDrive, uint8_t enablePullUp)
{
	/* Disable interrupts */
	pio->PIO_IDR = mask;

	/* Enable pull-up(s) if necessary */
	if (enablePullUp) {
		pio->PIO_PPDDR = mask;
		pio->PIO_PUER = mask;
	} else {
		pio->PIO_PUDR = mask;
	}
	/* Enable multi-drive if necessary */
	if (enableMultiDrive) {
		pio->PIO_MDER = mask;
	} else {

		pio->PIO_MDDR = mask;
	}
	/* Set default value */
	if (defaultValue) {

		pio->PIO_SODR = mask;
	} else {

		pio->PIO_CODR = mask;
	}
	/* Configure pin(s) as output(s) */
	pio->PIO_OER = mask;
	pio->PIO_PER = mask;
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

uint8_t pio_configure(const struct _pin *list, uint32_t size)
{
	/* Configure pins */
	while (size > 0) {
		Pio* pio = _pio_get_instance(list->group);
		switch (list->type) {

		case PIO_PERIPH_A:
			pio_set_peripheralA(pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		case PIO_PERIPH_B:
			pio_set_peripheralB(pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		case PIO_PERIPH_C:
			pio_set_peripheralC(pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		case PIO_PERIPH_D:
			pio_set_peripheralD(pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;
		case PIO_INPUT:
			pmc_enable_peripheral(list->group);
			pio_set_input(pio, list->mask, list->attribute);
			break;

		case PIO_OUTPUT_0:
		case PIO_OUTPUT_1:
			pio_set_output(pio, list->mask,
				      (list->type == PIO_OUTPUT_1),
				      (list->attribute & PIO_OPENDRAIN) ? 1 : 0,
				      (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		default:
			return 0;
		}
		list++;
		size--;
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
	pio->PIO_WPMR = (PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_EN);
}

void pio_disable_write_protect(const struct _pin *pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	pio->PIO_WPMR = (PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_DIS);
}

uint32_t pio_get_write_protect_violation_info(const struct _pin * pin)
{
	Pio* pio = _pio_get_instance(pin->group);
	return (pio->PIO_WPSR);
}

void pio_output_low(uint32_t group, uint32_t mask)
{
	Pio* pio = _pio_get_instance(group);
	PMC->PMC_PCER0 = 1 << group;
	pio->PIO_PUDR = mask;	// all Pull-up Disable
	pio->PIO_PPDDR = mask;	// all Pull-down Disable
	pio->PIO_PER = mask;	// all PIO enable
	pio->PIO_OER = mask;	// all PIO output mode
	pio->PIO_CODR = mask;	// all PIO clear output
}

void pio_add_handler_to_group(uint32_t group, uint32_t mask,
			   void (*handler)(uint32_t, uint32_t))
{
	assert(group < ID_PERIPH_COUNT);
	uint32_t index = _pio_get_index(group);
	assert(index <
	       (sizeof(_generic_handlers)/sizeof(_generic_handlers[0])));
	_handler_push(handler, mask);
	aic_set_source_vector(group,
			      (handler_t)_generic_handlers[index]);
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
