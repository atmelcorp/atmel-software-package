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

/**
 *  \file
 *
 *  \section Purpose
 *
 *  This file provides a basic API for PIO configuration and usage of
 *  user-controlled pins. Please refer to the board.h file for a list of
 *  available pin definitions.
 *
 *  \section Usage
 *
 *  -# Define a constant pin description array such as the following one, using
 *     the existing definitions provided by the board.h file if possible:
 *     \code
 *        const struct _pin_t pins[] = {PIN_USART0_TXD, PIN_USART0_RXD};
 *     \endcode
 *     Alternatively, it is possible to add new pins by provided the full Pin
 *     structure:
 *     \code
 *     // Pin instance to configure PA10 & PA11 as inputs with the internal
 *     // pull-up enabled.
 *     const Pin pins = {
 *          (1 << 10) | (1 << 11),
 *          REG_PIOA,
 *          ID_PIOA,
 *          PIO_INPUT,
 *          PIO_PULLUP
 *     };
 *     \endcode
 *  -# Configure a pin array by calling pio_configure() with a pointer to the
 *     array and its size (which is computed using the ARRAY_SIZE macro).
 *  -# Change and get the value of a user-controlled pin using the pio_set,
 *     pio_clear and pio_get methods.
 *  -# Get the level being currently output by a user-controlled pin configured
 *     as an output using pio_get_output_date_status().
 */

#ifndef _PIO_H
#error "pio4.h cannot be included. pio.h should be used instead"
#endif

#ifndef _PIO3_H
#define _PIO3_H

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

#include <stdint.h>

/*------------------------------------------------------------------------------
 *         Definitions
 *------------------------------------------------------------------------------*/

/* The IO group is A (equivalent to PIOA peripheral ID) */
#define PIO_GROUP_A                 ID_PIOA
/* The IO group is B (equivalent to PIOB peripheral ID) */
#define PIO_GROUP_B                 ID_PIOB
/* The IO group is C (equivalent to PIOC peripheral ID) */
#define PIO_GROUP_C                 ID_PIOC
/* The IO group is D (equivalent to PIOD peripheral ID) */
#define PIO_GROUP_D                 ID_PIOD
/* The IO group is E (equivalent to PIOE peripheral ID) */
#define PIO_GROUP_E                 ID_PIOE

#define PIO_GROUP_LENGTH            5

/*  The pin is controlled by the associated signal of peripheral A. */
#define PIO_PERIPH_A                0
/*  The pin is controlled by the associated signal of peripheral B. */
#define PIO_PERIPH_B                1
/*  The pin is controlled by the associated signal of peripheral C. */
#define PIO_PERIPH_C                2
/*  The pin is controlled by the associated signal of peripheral D. */
#define PIO_PERIPH_D                3

/*  The pin is an input. */
#define PIO_INPUT                   4
/*  The pin is an output and has a default level of 0. */
#define PIO_OUTPUT_0                5
/*  The pin is an output and has a default level of 1. */
#define PIO_OUTPUT_1                6

/*  Default pin configuration (no attribute). */
#define PIO_DEFAULT                 (0 << 0)
/*  The internal pin pull-up is active. */
#define PIO_PULLUP                  (1 << 0)
/*  The internal glitch filter is active. */
#define PIO_DEGLITCH                (1 << 1)
/*  The pin is open-drain. */
#define PIO_OPENDRAIN               (1 << 2)
/* The internal pin pull-down is active. */
#define PIO_PULLDOWN                (1 << 3)
/*  The internal debouncing filter is active. */
#define PIO_DEBOUNCE                (1 << 4)

/*  Enable additional interrupt modes. */
#define PIO_IT_AIME                 (1 << 5)

/*  Interrupt High Level/Rising Edge detection is active. */
#define PIO_IT_RE_OR_HL             (1 << 6)
/*  Interrupt Edge detection is active. */
#define PIO_IT_EDGE                 (1 << 7)

/*  Low level interrupt is active */
#define PIO_IT_LOW_LEVEL            (0 | 0 | PIO_IT_AIME)
/*  High level interrupt is active */
#define PIO_IT_HIGH_LEVEL           (PIO_IT_RE_OR_HL | 0 | PIO_IT_AIME)
/*  Falling edge interrupt is active */
#define PIO_IT_FALL_EDGE            (0 | PIO_IT_EDGE | PIO_IT_AIME)
/*  Rising edge interrupt is active */
#define PIO_IT_RISE_EDGE            (PIO_IT_RE_OR_HL | PIO_IT_EDGE | PIO_IT_AIME)

#endif	/* #ifndef _PIO3_H */
