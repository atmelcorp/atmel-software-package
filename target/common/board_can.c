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
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board_can.h"
#include "trace.h"

#include "can/can-bus.h"

#include "gpio/pio.h"


/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#ifndef BOARD_CAN_BUS0_FREQ_FD
#define BOARD_CAN_BUS0_FREQ_FD 0
#endif

#ifndef BOARD_CAN_BUS1_FREQ_FD
#define BOARD_CAN_BUS1_FREQ_FD 0
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void board_cfg_can_bus(void)
{
#ifdef BOARD_CAN_BUS0
	const struct _pin pins_can_bus0[] = BOARD_CAN_BUS0_PINS;
	pio_configure(pins_can_bus0, ARRAY_SIZE(pins_can_bus0));
	can_bus_configure(0, BOARD_CAN_BUS0, BOARD_CAN_BUS0_FREQ, BOARD_CAN_BUS0_FREQ_FD);
#endif
#ifdef BOARD_CAN_BUS1
	const struct _pin pins_can_bus1[] = BOARD_CAN_BUS1_PINS;
	pio_configure(pins_can_bus1, ARRAY_SIZE(pins_can_bus1));
	can_bus_configure(1, BOARD_CAN_BUS1, BOARD_CAN_BUS1_FREQ, BOARD_CAN_BUS1_FREQ_FD);
#endif
#ifdef BOARD_CAN_BUS2
	const struct _pin pins_can_bus2[] = BOARD_CAN_BUS2_PINS;
	pio_configure(pins_can_bus2, ARRAY_SIZE(pins_can_bus2));
	can_bus_configure(2, BOARD_CAN_BUS2, BOARD_CAN_BUS2_FREQ, BOARD_CAN_BUS2_FREQ_FD);
#endif
#ifdef BOARD_CAN_BUS3
	const struct _pin pins_can_bus3[] = BOARD_CAN_BUS3_PINS;
	pio_configure(pins_can_bus3, ARRAY_SIZE(pins_can_bus3));
	can_bus_configure(3, BOARD_CAN_BUS3, BOARD_CAN_BUS3_FREQ, BOARD_CAN_BUS3_FREQ_FD);
#endif
}
