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

/*----------------------------------------------------------------------------
*        Headers
*----------------------------------------------------------------------------*/

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "chip.h"
#include "gpio/pio.h"
#include "irq/irq.h"
#ifdef CONFIG_HAVE_L1CACHE
#include "mm/l1cache.h"
#endif
#ifdef CONFIG_HAVE_L2CACHE
#include "mm/l2cache.h"
#endif
#ifdef CONFIG_HAVE_MMU
#include "mm/mmu.h"
#endif
#ifdef CONFIG_HAVE_FLEXCOM
#include "peripherals/flexcom.h"
#endif
#include "peripherals/pmc.h"
#ifdef CONFIG_HAVE_DBGU
#include "serial/dbgu.h"
#endif
#include "serial/uart.h"
#include "serial/usart.h"
#include "seriald.h"

/*----------------------------------------------------------------------------
 *        Local Types
 *----------------------------------------------------------------------------*/

typedef void (*init_handler_t)(void*, uint32_t, uint32_t);
typedef void (*put_char_handler_t)(void*, uint8_t);
typedef bool (*tx_empty_handler_t)(void*);
typedef uint8_t (*get_char_handler_t)(void*);
typedef bool (*rx_ready_handler_t)(void*);
typedef void (*enable_it_handler_t)(void*, uint32_t);
typedef void (*disable_it_handler_t)(void*, uint32_t);

struct _seriald_ops {
	uint32_t             mode;
	uint32_t             rx_int_mask;
	init_handler_t       init;
	put_char_handler_t   put_char;
	tx_empty_handler_t   tx_empty;
	get_char_handler_t   get_char;
	rx_ready_handler_t   rx_ready;
	enable_it_handler_t  enable_it;
	disable_it_handler_t disable_it;
};

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_SERIALD_USART
static const struct _seriald_ops seriald_ops_usart = {
	.mode = US_MR_CHMODE_NORMAL | US_MR_PAR_NO | US_MR_CHRL_8_BIT,
	.rx_int_mask = US_IER_RXRDY,
	.init = (init_handler_t)usart_configure,
	.put_char = (put_char_handler_t)usart_put_char,
	.tx_empty = (tx_empty_handler_t)usart_is_tx_empty,
	.get_char = (get_char_handler_t)usart_get_char,
	.rx_ready = (rx_ready_handler_t)usart_is_rx_ready,
	.enable_it = (enable_it_handler_t)usart_enable_it,
	.disable_it = (disable_it_handler_t)usart_disable_it,
};
#endif

#ifdef CONFIG_HAVE_SERIALD_UART
static const struct _seriald_ops seriald_ops_uart = {
	.mode = UART_MR_CHMODE_NORMAL | UART_MR_PAR_NO,
	.rx_int_mask = UART_IER_RXRDY,
	.init = (init_handler_t)uart_configure,
	.put_char = (put_char_handler_t)uart_put_char,
	.tx_empty = (tx_empty_handler_t)uart_is_tx_empty,
	.get_char = (get_char_handler_t)uart_get_char,
	.rx_ready = (rx_ready_handler_t)uart_is_rx_ready,
	.enable_it = (enable_it_handler_t)uart_enable_it,
	.disable_it = (disable_it_handler_t)uart_disable_it,
};
#endif

#ifdef CONFIG_HAVE_SERIALD_DBGU
static const struct _seriald_ops seriald_ops_dbgu = {
	.mode = DBGU_MR_CHMODE_NORM | DBGU_MR_PAR_NONE,
	.rx_int_mask = DBGU_IER_RXRDY,
	.init = (init_handler_t)dbgu_configure,
	.put_char = (put_char_handler_t)dbgu_put_char,
	.tx_empty = (tx_empty_handler_t)dbgu_is_tx_empty,
	.get_char = (get_char_handler_t)dbgu_get_char,
	.rx_ready = (rx_ready_handler_t)dbgu_is_rx_ready,
	.enable_it = (enable_it_handler_t)dbgu_enable_it,
	.disable_it = (disable_it_handler_t)dbgu_disable_it,
};
#endif

/*------------------------------------------------------------------------------
 *         Local functions
 *------------------------------------------------------------------------------*/

static void seriald_handler(uint32_t source, void* user_arg)
{
	const struct _seriald* serial = (struct _seriald*)user_arg;
	uint8_t c;

	if (!seriald_is_rx_ready(serial))
		return;

	c = seriald_get_char(serial);
	if (serial->rx_handler)
		serial->rx_handler(c);
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

int seriald_configure(struct _seriald* serial, void* addr, uint32_t baudrate)
{
	uint32_t id = ID_PERIPH_COUNT;
	const struct _seriald_ops* ops = NULL;

	if (!serial)
		return -EINVAL;

#ifdef CONFIG_HAVE_SERIALD_USART
	id = get_usart_id_from_addr((Usart*)addr);
	if (id != ID_PERIPH_COUNT) {
		ops = &seriald_ops_usart;
#ifdef CONFIG_HAVE_FLEXCOM
		Flexcom* flexcom = get_flexcom_addr_from_id(id);
		if (flexcom)
			flexcom_select(flexcom, FLEX_MR_OPMODE_USART);
#endif
	}
#endif
#ifdef CONFIG_HAVE_SERIALD_UART
	if (!ops) {
		id = get_uart_id_from_addr((Uart*)addr);
		if (id != ID_PERIPH_COUNT)
			ops = &seriald_ops_uart;
	}
#endif
#ifdef CONFIG_HAVE_SERIALD_DBGU
	if (!ops) {
		if (addr == DBGU) {
			id = ID_DBGU;
			ops = &seriald_ops_dbgu;
		}
	}
#endif
	if (!ops)
		return -ENODEV;

	/* Save serial peripheral address and ID */
	memset(serial, 0, sizeof(*serial));
	serial->id = id;
	serial->addr = addr;
	serial->ops = ops;

	/* Initialize driver to use */
	pmc_configure_peripheral(id, NULL, true);
	ops->init(addr, ops->mode, baudrate);

	return 0;
}

void seriald_put_char(const struct _seriald* serial, uint8_t c)
{
	if (!serial || !serial->id)
		return;

	serial->ops->put_char(serial->addr, c);
}

void seriald_put_string(const struct _seriald* serial, const uint8_t* str)
{
	if (!serial || !serial->id)
		return;

	while (*str)
		serial->ops->put_char(serial->addr, *str++);
}

bool seriald_is_tx_empty(const struct _seriald* serial)
{
	if (!serial || !serial->id)
		return true;

	return serial->ops->tx_empty(serial->addr);
}

uint8_t seriald_get_char(const struct _seriald* serial)
{
	if (!serial || !serial->id) {
		assert(0);
		while(1);
	}

	return serial->ops->get_char(serial->addr);
}

bool seriald_is_rx_ready(const struct _seriald* serial)
{
	if (!serial || !serial->id)
		return false;

	return serial->ops->rx_ready(serial->addr);
}

void seriald_set_rx_handler(struct _seriald* serial, seriald_rx_handler_t handler)
{
	if (!serial || !serial->id)
		return;

	serial->rx_handler = handler;
}

void seriald_enable_rx_interrupt(const struct _seriald* serial)
{
	if (!serial || !serial->id)
		return;

	irq_add_handler(serial->id, seriald_handler, (void*)serial);
	irq_enable(serial->id);
	serial->ops->enable_it(serial->addr, serial->ops->rx_int_mask);
}

void seriald_disable_rx_interrupt(const struct _seriald* serial)
{
	if (!serial || !serial->id)
		return;

	serial->ops->disable_it(serial->addr, serial->ops->rx_int_mask);
	irq_disable(serial->id);
	irq_remove_handler(serial->id, seriald_handler);
}
