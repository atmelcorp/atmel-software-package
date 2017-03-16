/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

#include "chip.h"
#include "compiler.h"

#include "console_pin_defs.h"

/*----------------------------------------------------------------------------
 *        Public constants
 *----------------------------------------------------------------------------*/

const struct console_pin_definition console_pin_defs[] = {
	{
		.instance = 0,
		.ioset = 1,
		.addr = UART0,
		.tx_pin = PIN_UART0_TXD_IOS1,
	},
	{
		.instance = 1,
		.ioset = 1,
		.addr = UART1,
		.tx_pin = PIN_UART1_TXD_IOS1,
	},
	{
		.instance = 1,
		.ioset = 2,
		.addr = UART1,
		.tx_pin = PIN_UART1_TXD_IOS2,
	},
	{
		.instance = 2,
		.ioset = 1,
		.addr = UART2,
		.tx_pin = PIN_UART2_TXD_IOS1,
	},
	{
		.instance = 2,
		.ioset = 2,
		.addr = UART2,
		.tx_pin = PIN_UART2_TXD_IOS2,
	},
	{
		.instance = 2,
		.ioset = 3,
		.addr = UART2,
		.tx_pin = PIN_UART2_TXD_IOS3,
	},
	{
		.instance = 3,
		.ioset = 1,
		.addr = UART3,
		.tx_pin = PIN_UART3_TXD_IOS1,
	},
	{
		.instance = 3,
		.ioset = 2,
		.addr = UART3,
		.tx_pin = PIN_UART3_TXD_IOS2,
	},
	{
		.instance = 3,
		.ioset = 3,
		.addr = UART3,
		.tx_pin = PIN_UART3_TXD_IOS3,
	},
	{
		.instance = 4,
		.ioset = 1,
		.addr = UART4,
		.tx_pin = PIN_UART4_TXD_IOS1,
	},
	{
		.instance = 5,
		.ioset = 1,
		.addr = FLEXUSART0,
		.tx_pin = PIN_FLEXCOM0_USART_TXD_IOS1,
	},
	{
		.instance = 6,
		.ioset = 1,
		.addr = FLEXUSART1,
		.tx_pin = PIN_FLEXCOM1_USART_TXD_IOS1,
	},
	{
		.instance = 7,
		.ioset = 1,
		.addr = FLEXUSART2,
		.tx_pin = PIN_FLEXCOM2_USART_TXD_IOS1,
	},
	{
		.instance = 7,
		.ioset = 2,
		.addr = FLEXUSART2,
		.tx_pin = PIN_FLEXCOM2_USART_TXD_IOS2,
	},
	{
		.instance = 8,
		.ioset = 1,
		.addr = FLEXUSART3,
		.tx_pin = PIN_FLEXCOM3_USART_TXD_IOS1,
	},
	{
		.instance = 8,
		.ioset = 2,
		.addr = FLEXUSART3,
		.tx_pin = PIN_FLEXCOM3_USART_TXD_IOS2,
	},
	{
		.instance = 8,
		.ioset = 3,
		.addr = FLEXUSART3,
		.tx_pin = PIN_FLEXCOM3_USART_TXD_IOS3,
	},
	{
		.instance = 9,
		.ioset = 1,
		.addr = FLEXUSART4,
		.tx_pin = PIN_FLEXCOM4_USART_TXD_IOS1,
	},
	{
		.instance = 9,
		.ioset = 2,
		.addr = FLEXUSART4,
		.tx_pin = PIN_FLEXCOM4_USART_TXD_IOS2,
	},
	{
		.instance = 9,
		.ioset = 3,
		.addr = FLEXUSART4,
		.tx_pin = PIN_FLEXCOM4_USART_TXD_IOS3,
	},
};

const int num_console_pin_defs = ARRAY_SIZE(console_pin_defs);
