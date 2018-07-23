/* ----------------------------------------------------------------------------
 *         MICROCHIP Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2018, Microchip
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
		.addr = DBGU,
		.tx_pin = PIN_DBGU_TXD,
	},
	{
		.instance = 1,
		.ioset = 1,
		.addr = FLEXUSART0,
		.tx_pin = PIN_FLEXCOM0_USART_TXD_IOS1,
	},
	{
		.instance = 2,
		.ioset = 1,
		.addr = FLEXUSART1,
		.tx_pin = PIN_FLEXCOM1_USART_TXD_IOS1,
	},
	{
		.instance = 3,
		.ioset = 1,
		.addr = FLEXUSART2,
		.tx_pin = PIN_FLEXCOM2_USART_TXD_IOS1,
	},
	{
		.instance = 4,
		.ioset = 1,
		.addr = FLEXUSART3,
		.tx_pin = PIN_FLEXCOM3_USART_TXD_IOS1,
	},
	{
		.instance = 5,
		.ioset = 1,
		.addr = FLEXUSART4,
		.tx_pin = PIN_FLEXCOM4_USART_TXD_IOS1,
	},
	{
		.instance = 6,
		.ioset = 1,
		.addr = FLEXUSART5,
		.tx_pin = PIN_FLEXCOM5_USART_TXD_IOS1,
	},
	{
		.instance = 7,
		.ioset = 1,
		.addr = FLEXUSART6,
		.tx_pin = PIN_FLEXCOM6_USART_TXD_IOS1,
	},
	{
		.instance = 8,
		.ioset = 1,
		.addr = FLEXUSART7,
		.tx_pin = PIN_FLEXCOM7_USART_TXD_IOS1,
	},
	{
		.instance = 9,
		.ioset = 1,
		.addr = FLEXUSART8,
		.tx_pin = PIN_FLEXCOM8_USART_TXD_IOS1,
	},
	{
		.instance = 10,
		.ioset = 1,
		.addr = FLEXUSART9,
		.tx_pin = PIN_FLEXCOM9_USART_TXD_IOS1,
	},
	{
		.instance = 11,
		.ioset = 1,
		.addr = FLEXUSART10,
		.tx_pin = PIN_FLEXCOM10_USART_TXD_IOS1,
	},
	{
		.instance = 12,
		.ioset = 1,
		.addr = FLEXUSART11,
		.tx_pin = PIN_FLEXCOM11_USART_TXD_IOS1,
	},
	{
		.instance = 13,
		.ioset = 1,
		.addr = FLEXUSART12,
		.tx_pin = PIN_FLEXCOM12_USART_TXD_IOS1,
	},
};

const int num_console_pin_defs = ARRAY_SIZE(console_pin_defs);
