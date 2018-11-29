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

#ifndef _PIO_H
#define _PIO_H

#define IRQ_PIO_HANDLERS_SIZE 16

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include <stdint.h>

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/* PIO Groups */
#define PIO_GROUP_A      0 /*< The IO group is A (or 0) */
#define PIO_GROUP_B      1 /*< The IO group is B (or 1) */
#define PIO_GROUP_C      2 /*< The IO group is C (or 2) */
#define PIO_GROUP_D      3 /*< The IO group is D (or 3) */
#define PIO_GROUP_E      4 /*< The IO group is E (or 4) */
#define PIO_GROUP_LENGTH 5

/* Pin Types */
#define PIO_PERIPH_A 0 /* Peripheral A */
#define PIO_PERIPH_B 1 /* Peripheral B */
#define PIO_PERIPH_C 2 /* Peripheral C */
#define PIO_PERIPH_D 3 /* Peripheral D */
#define PIO_PERIPH_E 4 /* Peripheral E */
#define PIO_PERIPH_F 5 /* Peripheral F */
#define PIO_PERIPH_G 6 /* Peripheral G */
#define PIO_INPUT    7 /* Input */
#define PIO_OUTPUT   8 /* Output */
#define PIO_OUTPUT_0 8 /* Output (default level of 0) */
#define PIO_OUTPUT_1 9 /* Output (default level of 1) */

/* Pin Attributes */
#define PIO_DEFAULT         (0)       /* Default pin configuration */
#define PIO_PULLUP          (1u << 0) /* The internal pull-up is enabled. */
#define PIO_PULLDOWN        (1u << 1) /* The internal pull-down is enabled. */
#define PIO_OPENDRAIN       (1u << 2) /* The pin is Open-Drain. */
#define PIO_DEGLITCH        (1u << 3) /* The Glitch Filter is enabled. */
#define PIO_DEBOUNCE        (1u << 4) /* The Debouncing Filter is enabled. */
#define PIO_NO_SCHMITT_TRIG (1u << 5) /* The Schmitt Trigger is disabled. */
#define PIO_CRTL_SLEWR      (1u << 9) /* The slew rate is controlled. */

/* Pin Event Detection */
#define PIO_IT_FALL_EDGE    (0u << 6) /*< Event detection on input falling edge. */
#define PIO_IT_RISE_EDGE    (1u << 6) /*< Event detection on input rising edge. */
#define PIO_IT_BOTH_EDGE    (2u << 6) /*< Event detection on input both edge. */
#define PIO_IT_LOW_LEVEL    (3u << 6) /*< Event detection on low level input. */
#define PIO_IT_HIGH_LEVEL   (4u << 6) /*< Event detection on high level input. */
#define PIO_IT_MASK         (7u << 6)

/* Pin Drive Strength */
#define PIO_DRVSTR_LO       (0u << 10) /*< Low drive */
#define PIO_DRVSTR_ME       (1u << 10) /*< Medium drive */
#define PIO_DRVSTR_HI       (2u << 10) /*< High drive */
#define PIO_DRVSTR_MASK     (3u << 10)

/*------------------------------------------------------------------------------
 *         Global Types
 *------------------------------------------------------------------------------*/

struct _pin
{
	uint8_t  group;     /*< The IO group containing the pins you want to use. */
	uint32_t mask;      /*< Bitmask indicating which pin(s) to configure. */
	uint8_t  type;      /*< Pin type */
	uint32_t attribute; /*< Pin config attribute. */
};

typedef void (*pio_handler_t)(uint32_t group, uint32_t status, void *arg);

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Configures a list of Pin instances.
 *
 * \details Each of them can either hold a single pin or a group of
 * pins, depending on the mask value; all pins are configured by this
 * function. The size of the array must also be provided and can be
 * computed using ARRAY_SIZE whenever its length is not known in
 * advance.
 *
 * \param pins Pointer to a list of struct _pin instances.
 * \param size Size of the pins list
 */
extern void pio_configure(const struct _pin *pins, uint32_t size);

/**
 * \brief Sets a high output level on all the PIOs defined in the
 * given struct _pin instance.
 *
 * This has no immediate effects on PIOs that are not configured as outputs.
 *
 * \param pin Pointer to a struct _pin instance describing one or more pins.
 */
extern void pio_set(const struct _pin *pin);

/**
 * \brief Sets a low output level on all the PIOs defined in the given
 * struct _pin instance.
 *
 * This has no immediate effects on PIOs that are not configured as outputs.
 *
 * \param pin Pointer to a struct _pin instance describing one or more pins.
 */
extern void pio_clear(const struct _pin *pin);

/**
 * \brief Gets the levels of one or more PIOs.
 *
 * \param pin Pointer to a struct _pin instance describing one or more pins.
 *
 * \return Bitmask of the levels for the pin(s).
 */
extern uint32_t pio_get(const struct _pin *pin);

/**
 * \brief Gets the configured output levels of one or more PIOs.
 *
 * Will return the configured output levels even if the pin(s) are not
 * configured as output.  To get the actual level of the pin(s), use pio_get()
 * function.
 *
 * \param pin Pointer to a struct _pin instance describing one or more pins.
 *
 * \return Bitmask of the configured output levels for the pin(s).
 */
extern uint32_t pio_get_output_data_status(const struct _pin *pin);

/**
 * \brief Configures Glitch or Debouncing filter for input.
 *
 * \param cutoff  Cut off frequency for debounce filter.
 */
extern void pio_set_debounce_filter(uint32_t cutoff);

/**
 * \brief Enable write protect.
 */
extern void pio_enable_write_protect(void);

/**
 * \brief Disable write protect.
 */
extern void pio_disable_write_protect(void);

/**
 * \brief Get write protect violation information.
 */
extern uint32_t pio_get_write_protect_violation_info(void);

/**
 * \brief Configure all outputs for a group to low.
 *
 * \param group PIO group number
 * \param mask  Bitmask of one or more pin(s) to configure.
 */
extern void pio_output_low(uint32_t group, uint32_t mask);

/**
 * \brief Configure an interrupt handler for some masked pins of a given PIO group.
 *
 * \param group    PIO group number
 * \param mask     Bitmask of one or more pin(s)
 * \param handler  Interrupt handler
 * \param user_arg User-defined argument that is passed as-is to the handler
 */
extern void pio_add_handler_to_group(uint32_t group, uint32_t mask,
                                     pio_handler_t handler, void* user_arg);

/**
 * \brief Disable interrupts for all pins on all PIO groups.
 */
extern void pio_reset_all_it(void);

/**
 * \brief Enables the given interrupt source if it has been configured.
 *
 * \param pin Interrupt source to enable.
 */
extern void pio_enable_it(const struct _pin *pin);

/**
 * \brief Disables a given interrupt source.
 *
 * \param pin Interrupt source to disable.
 */
extern void pio_disable_it(const struct _pin *pin);

#ifdef __cplusplus
}
#endif

#endif /* _PIO_H */
