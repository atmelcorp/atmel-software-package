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
#include "core/pio.h"
#include "core/pmc.h"
#include "core/aic.h"

#include "utils/trace.h"

#include "resources/compiler_defines.h"

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

static void (*_handlers[PIO_GROUP_LENGTH])(uint32_t);

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

#ifdef PIOA
static void _pioa_handler(void)
{
	uint32_t status = PIOA->PIO_ISR;
	_handlers[0](status);
}
#endif
#ifdef PIOB
static void _piob_handler(void)
{
	uint32_t status = PIOB->PIO_ISR;
	_handlers[1](status);
}
#endif
#ifdef PIOC
static void _pioc_handler(void)
{
	uint32_t status = PIOC->PIO_ISR;
	_handlers[2](status);
}
#endif
#ifdef PIOD
static void _piod_handler(void)
{
	uint32_t status = PIOD->PIO_ISR;
	_handlers[3](status);
}
#endif
#ifdef PIOE
static void _pioe_handler(void)
{
	uint32_t status = PIOE->PIO_ISR;
	_handlers[4](status);
}
#endif

static inline uint32_t _pio_get_index(int group)
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
		return -1;
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

/**
 * \brief Configures a list of Pin instances.
 *
 * \details Each of them can either hold a single pin or a group of
 * pins, depending on the mask value; all pins are configured by this
 * function. The size of the array must also be provided and is easily
 * computed using PIO_LISTSIZE whenever its length is not known in
 * advance.
 *
 * \param list  Pointer to a list of Pin instances.
 * \param size  Size of the Pin list (calculated using PIO_LISTSIZE).
 *
 * \return 1 if the pins have been configured properly; otherwise 0.
 */
uint8_t pio_configure(const struct _pin *list, uint32_t size)
{
	/* Configure pins */
	while (size > 0) {
		switch (list->type) {

		case PIO_PERIPH_A:
			pio_set_peripheralA(list->pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		case PIO_PERIPH_B:
			pio_set_peripheralB(list->pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		case PIO_PERIPH_C:
			pio_set_peripheralC(list->pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;

		case PIO_PERIPH_D:
			pio_set_peripheralD(list->pio, list->mask,
					   (list->attribute & PIO_PULLUP) ? 1 : 0);
			break;
		case PIO_INPUT:
			pmc_enable_peripheral(list->id);
			pio_set_input(list->pio, list->mask, list->attribute);
			break;

		case PIO_OUTPUT_0:
		case PIO_OUTPUT_1:
			pio_set_output(list->pio, list->mask,
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

/**
 * \brief Sets a high output level on all the PIOs defined in the
 * given Pin instance.
 *
 * \details This has no immediate effects on PIOs that are not output,
 * but the PIO controller will memorize the value they are changed to
 * outputs.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_set(const struct _pin *pin)
{
	pin->pio->PIO_SODR = pin->mask;
}

/**
 * \brief Sets a low output level on all the PIOs defined in the given
 * Pin instance.
 *
 * \details This has no immediate effects on PIOs that are not output,
 * but the PIO controller will memorize the value they are changed to
 * outputs.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_clear(const struct _pin *pin)
{
	pin->pio->PIO_CODR = pin->mask;
}

/**
 * \brief Returns 1 if one or more PIO of the given Pin instance currently have
 * a high level; otherwise returns 0. This method returns the actual value that
 * is being read on the pin. To return the supposed output value of a pin, use
 * \ref pio_get_output_date_status() instead.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 *
 * \return 1 if the Pin instance contains at least one PIO that currently has
 * a high level; otherwise 0.
 */
uint8_t pio_get(const struct _pin *pin)
{
	uint32_t reg;

	if ((pin->type == PIO_OUTPUT_0) || (pin->type == PIO_OUTPUT_1)) {
		reg = pin->pio->PIO_ODSR;
	} else {
		reg = pin->pio->PIO_PDSR;
	}
	if ((reg & pin->mask) == 0) {
		return 0;
	} else {
		return 1;
	}
}

/**
 * \brief Returns 1 if one or more PIO of the given Pin are configured to output a
 * high level (even if they are not output).
 * To get the actual value of the pin, use pio_get() instead.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 *
 * \return 1 if the Pin instance contains at least one PIO that is configured
 * to output a high level; otherwise 0.
 */
uint8_t pio_get_output_data_status(const struct _pin *pin)
{
	if ((pin->pio->PIO_ODSR & pin->mask) == 0) {
		return 0;
	} else {
		return 1;
	}
}

/**
 * \brief Configures Glitch or Debouncing filter for input.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 * \param cuttoff  Cutt off frequency for debounce filter.
 */
void pio_set_debounce_filter(const struct _pin *pin, uint32_t cuttoff)
{
	Pio *pio = pin->pio;

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

/**
 * \brief Enable write protect.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_enable_write_protect(const struct _pin *pin)
{
	Pio *pio = pin->pio;
	pio->PIO_WPMR = (PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_EN);
}

/**
 * \brief Disable write protect.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
void pio_disable_write_protect(const struct _pin *pin)
{
	Pio *pio = pin->pio;
	pio->PIO_WPMR = (PIO_WPMR_WPKEY_VALID | PIO_WPMR_WPEN_DIS);
}

/**
 * \brief Get write protect violation information.
 *
 * \param pin  Pointer to a Pin instance describing one or more pins.
 */
uint32_t pio_get_write_protect_violation_info(const struct _pin * pin)
{
	Pio *pio = pin->pio;
	return (pio->PIO_WPSR);
}

/**
 * \brief Configure all pio output low
 *
 * \param pio  Pointer to a Pio instance describing one or more pins.
 * \param pioId PIO ID
 * \param mask  Bitmask of one or more pin(s) to configure.
 */
void pio_output_low (Pio *pio, uint32_t pioId ,uint32_t mask)
{
	PMC->PMC_PCER0 = 1 << pioId;
	pio->PIO_PUDR = mask;	// all Pull-up Disable
	pio->PIO_PPDDR = mask;	// all Pull-down Disable
	pio->PIO_PER = mask;	// all PIO enable
	pio->PIO_OER = mask;	// all PIO output mode
	pio->PIO_CODR = mask;	// all PIO clear output
}

void pio_set_group_handler(uint32_t group, void (*handler)(uint32_t))
{
	assert(group < ID_PERIPH_COUNT);
	uint32_t index = _pio_get_index(group);
	assert(index <
	       (sizeof(_generic_handlers)/sizeof(_generic_handlers[0])));
	_handlers[index] = handler;
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
	PIOB->PIO_ISR;
	PIOB->PIO_IDR = ~0;
#endif
#ifdef PIOD
	PIOB->PIO_ISR;
	PIOB->PIO_IDR = ~0;
#endif
#ifdef PIOE
	PIOB->PIO_ISR;
	PIOB->PIO_IDR = ~0;
#endif
}

/**
 * \brief Generate an interrupt on status change for a PIO or a group
 * of PIO.

 * \details The provided interrupt handler will be called with the
 * triggering pin as its parameter (enabling different pin instances
 * to share the same handler).
 *
 * \param pin  Pointer to a _pin instance.
 */
void pio_configure_it(const struct _pin * pin)
{
	trace_debug("Enter in pio_configure_it()\n\r");
	assert(pin);
	Pio *pio = pin->pio;

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

/**
 * Enables the given interrupt source if it has been configured. The status
 * register of the corresponding PIO controller is cleared prior to enabling
 * the interrupt.
 * \param pin  Interrupt source to enable.
 */
void pio_enable_it(const struct _pin * pin)
{
trace_debug("Enter in pio_enable_it()\n\r");

	assert(pin != NULL);

	pin->pio->PIO_ISR;
	pin->pio->PIO_IER = pin->mask;
}

/**
 * Disables a given interrupt source, with no added side effects.
 *
 * \param pin  Interrupt source to disable.
 */
void pio_disable_it(const struct _pin * pin)
{
	assert(pin != NULL);

	trace_debug("Enter in pio_disable_it()\n\r");

	pin->pio->PIO_IDR = pin->mask;
}
