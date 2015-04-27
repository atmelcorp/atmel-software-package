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

/** \addtogroup usart_module Working with USART
 * \section Purpose
 * The USART driver provides the interface to configure and use the USART peripheral.\n
 *
 * The USART supports several kinds of communication modes such as full-duplex asynchronous/
 * synchronous serial communication,RS485 with driver control signal,ISO7816,SPI and Test modes.
 *
 * To start a USART transfer with \ref dmad_module "DMA" support, the user could follow these steps:
 * <ul>
 * <li> Configure USART with expected mode and baudrate(see \ref usart_configure), which could be done by:
 * -# Resetting and disabling transmitter and receiver by setting US_CR(Control Register). </li>
 * -# Configuring the USART in a specific mode by setting USART_MODE bits in US_MR(Mode Register) </li>
 * -# Setting baudrate which is different from mode to mode.
   </li>
 * <li> Enable transmitter or receiver respectively by set US_CR_TXEN or US_CR_RXEN in US_CR.</li>
 * <li> Read from or write to the peripheral with  \ref dmad_module </li>
 * </ul>
 *
 * \section Usage
 * <ul>
 * <li>  Enable or disable USART transmitter or receiver using
 * usart_set_transmitter_enabled() and usart_set_receiver_enabled().
 * <li>  Enable or disable USART interrupt using usart_enable_it() or usart_disable_it().
 * </li>
 * </ul>
 *
 * For more accurate information, please look at the USART section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref usart.c\n
 * \ref usart.h\n
*/

/**
 * \file
 *
 * Implementation of USART (Universal Synchronous Asynchronous Receiver Transmitter)
 * controller.
 *
 */
/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"
#include "serial/flexcom.h"

#include "serial/usart.h"
#include "bus/spi.h"
#include "bus/twi.h"

#include <assert.h>

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

/**
 * \brief Select a protocol for a FLEXCOM device
 *
 *
 *  \param flexcom  Pointer to FLEXCOM peripheral to configure.
 *  \param protocol  Protocol to use.
 */
void flexcom_select(Flexcom * flexcom, uint32_t protocol)
{
	assert(flexcom);
	uint32_t current_protocol = flexcom->FLEX_MR;

	usart_set_receiver_enabled(&flexcom->usart, 0u);
	
	/* Shutdown previous protocol */
	switch (current_protocol) {
	case FLEX_MR_OPMODE_USART:
		usart_set_receiver_enabled(&flexcom->usart, 0u);
		usart_set_transmitter_enabled(&flexcom->usart, 0u);
		break;
	case FLEX_MR_OPMODE_SPI:
		SPI_Disable(&flexcom->spi);
		break;
	case FLEX_MR_OPMODE_TWI:
		TWI_Stop(&flexcom->twi);
	default:
		break;
	}

	assert(protocol & FLEX_MR_OPMODE_NO_COM ||
	       protocol & FLEX_MR_OPMODE_USART ||
	       FLEX_MR_OPMODE_SPI || FLEX_MR_OPMODE_TWI);
	
	/* Activate the new mode () */
	flexcom->FLEX_MR = protocol;
}
