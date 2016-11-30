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
 *  This file contains all the common code for the USB examples.
 */

/*----------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "gpio/pio.h"

#include "usb/device/usbd.h"

#include "main_usb_common.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *         Constants
 *----------------------------------------------------------------------------*/

/**  VBus pin instance */
static const struct _pin pin_vbus = PIN_USB_VBUS;

#ifdef PIN_USB_POWER_ENA
/** Power Enable A (MicroAB Socket) pin instance. */
static const struct _pin pin_pon_a = PIN_USB_POWER_ENA;
#endif
#ifdef PIN_USB_POWER_ENB
/** Power Enable B (A Socket) pin instance. */
static const struct _pin pin_pon_b = PIN_USB_POWER_ENB;
#endif
#ifdef PIN_USB_OVCUR
/** Power Enable C (A Socket) pin instance. */
static const struct _pin pin_pon_c = PIN_USB_OVCUR;
#endif

/*----------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

static void handle_vbus_change(void)
{
	if (pio_get(&pin_vbus)) {
		trace_info("VBus detected\n\r");
		usbd_connect();
	} else {
		trace_info("No VBus detected\n\r");
		usbd_disconnect();
	}
}

/**
 * Handles interrupts coming from PIO controllers.
 */
static void vbus_pio_handler(uint32_t mask, uint32_t status, void* user_arg)
{
	if (status & pin_vbus.mask)
		handle_vbus_change();
}

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * Configures the VBus pin to trigger an interrupt when the level on that pin
 * changes.
 */
void usb_vbus_configure(void)
{
	trace_info("VBus configuration\n\r");

	/* Configure PIO */
	pio_configure(&pin_vbus, 1);

	/* Initialize pios interrupt with its handlers */
	pio_add_handler_to_group(pin_vbus.group,
			pin_vbus.mask, vbus_pio_handler, NULL);

	/* Enable PIO line interrupts. */
	pio_enable_it(&pin_vbus);

	/* Check current level on VBus */
	handle_vbus_change();
}

/**
 * Configures the Power Enable pin to disable self power.
 */
void usb_power_configure(void)
{
#ifdef PIN_USB_POWER_ENA
	pio_configure(&pin_pon_a, 1);
#endif
#ifdef PIN_USB_POWER_ENB
	pio_configure(&pin_pon_b, 1);
#endif
#ifdef PIN_USB_OVCUR
	pio_configure(&pin_pon_c, 1);
#endif
}
