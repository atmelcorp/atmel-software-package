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
/*-----------------------------------------------------------------------------
*         Headers
 *---------------------------------------------------------------------------*/

#include "chip.h"
#include "compiler.h"
#include "serial/usart.h"
#include "peripherals/pmc.h"

#include "trace.h"
#include "io.h"

#include <assert.h>
#include <string.h>

/*-----------------------------------------------------------------------------
*
 *---------------------------------------------------------------------------*/

/* The CD value scope programmed in MR register. */
#define MIN_CD_VALUE                  0x01
#define MIN_CD_VALUE_SPI              0x04
#define MAX_CD_VALUE                  US_BRGR_CD_Msk

/* The receiver sampling divide of baudrate clock. */
#define HIGH_FRQ_SAMPLE_DIV           16
#define LOW_FRQ_SAMPLE_DIV            8

/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

void usart_reset_status(Usart *usart)
{
	usart->US_CR = US_CR_RSTSTA;
}

void usart_configure(Usart *usart, uint32_t mode, uint32_t baudrate)
{
	uint32_t clock = pmc_get_peripheral_clock(get_usart_id_from_addr(usart));
	/* Reset and disable receiver & transmitter */
	uint32_t control = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS;
	/* apply */
	usart->US_CR = control;
	/* Configure mode */
	usart->US_MR = mode;

	/* Configure baudrate */
	/* Asynchronous, no oversampling */
	if (((mode & US_MR_SYNC) == 0) && ((mode & US_MR_OVER) == 0))
		usart->US_BRGR = (clock / baudrate) / 16;

	/* Disable all interrupts */
	usart->US_IDR = 0xFFFFFFFF;
	/* Enable receiver and transmitter */
	usart->US_CR = US_CR_RXEN | US_CR_TXEN;
}

uint32_t usart_get_status(Usart *usart)
{
	return usart->US_CSR;
}

uint32_t usart_get_masked_status(Usart *usart)
{
	uint32_t status;
	assert(usart != NULL);
	status = usart->US_CSR;
	status &= usart->US_IMR;
	return status;
}

void usart_enable_it(Usart *usart, uint32_t mode)
{
	usart->US_IER = mode;
}

void usart_disable_it(Usart *usart, uint32_t mode)
{
	usart->US_IDR = mode;
}

uint32_t usart_get_it_mask(Usart *usart)
{
	return usart->US_IMR;
}

void usart_set_transmitter_enabled(Usart *usart, uint8_t enabled)
{
	if (enabled) {
		usart->US_CR = US_CR_TXEN;
	} else {
		usart->US_CR = US_CR_TXDIS;
	}
}

void usart_set_receiver_enabled(Usart *usart, uint8_t enabled)
{
	if (enabled) {
		usart->US_CR = US_CR_RXEN;
	} else {
		usart->US_CR = US_CR_RXDIS;
	}
}

void usart_set_rts_enabled(Usart *usart, uint8_t enabled)
{
	if (enabled) {
		usart->US_CR = US_CR_RTSEN;
	} else {
		usart->US_CR = US_CR_RTSDIS;
	}
}

void usart_reset_tx(Usart *usart)
{
	/* Reset transmitter */
	usart->US_CR = US_CR_RSTTX | US_CR_TXDIS;
}

void usart_set_tx_timeguard(Usart *usart, uint32_t timeguard)
{
	usart->US_TTGR = timeguard;
}

void usart_reset_rx(Usart *usart)
{
	/* Reset Receiver */
	usart->US_CR = US_CR_RSTRX | US_CR_RXDIS;
}

void usart_set_rx_timeout(Usart *usart, uint32_t baudrate, uint32_t timeout)
{
	uint32_t to = ((timeout * 1000000) / ((1000000000 / baudrate) + 1));
	if (to > US_RTOR_TO_Msk)
		to = US_RTOR_TO_Msk;
	usart->US_RTOR = US_RTOR_TO(to);
}

void usart_start_tx_break(Usart *usart)
{
	usart->US_CR = US_CR_STTBRK;
}

void usart_stop_tx_break(Usart *usart)
{
	usart->US_CR = US_CR_STPBRK;
}

void usart_start_rx_timeout(Usart *usart)
{
	usart->US_CR = US_CR_STTTO;
}

void usart_reset_iterations(Usart *usart)
{
	usart->US_CR = US_CR_RSTIT;
}

void usart_reset_nack(Usart *usart)
{
	usart->US_CR = US_CR_RSTNACK;
}

void usart_restart_rx_timeout(Usart *usart)
{
	usart->US_CR = US_CR_RETTO;
}

void usart_write(Usart *usart, uint16_t data, volatile uint32_t timeout)
{
	if (timeout == 0) {
		while ((usart->US_CSR & US_CSR_TXRDY) == 0) ;
	} else {
		while ((usart->US_CSR & US_CSR_TXRDY) == 0) {
			if (timeout == 0) {
				trace_error("usart_write: Timed out.\n\r");
				return;
			}
			timeout--;
		}
	}
	usart->US_THR = data;
}

uint16_t usart_read(Usart *usart, volatile uint32_t timeout)
{
	if (timeout == 0) {
		while ((usart->US_CSR & US_CSR_RXRDY) == 0) ;
	} else {
		while ((usart->US_CSR & US_CSR_RXRDY) == 0) {
			if (timeout == 0) {
				trace_error("usart_read: Timed out.\n\r");
				return 0;
			}
			timeout--;
		}
	}
	return usart->US_RHR;
}

bool usart_is_rx_ready(Usart *usart)
{
	return (usart->US_CSR & US_CSR_RXRDY) != 0;
}

bool usart_is_tx_ready(Usart *usart)
{
	return (usart->US_CSR & US_CSR_TXRDY) != 0;
}

bool usart_is_tx_empty(Usart *usart)
{
	return (usart->US_CSR & US_CSR_TXEMPTY) != 0;
}

void usart_put_char(Usart *usart, uint8_t c)
{
	/* Wait for the transmitter to be ready */
	while ((usart->US_CSR & US_CSR_TXEMPTY) == 0);
	/* Send character */
	/* Force an octet write to avoid race conditions with FIFO mode */
	writeb(&usart->US_THR, c);
}

uint8_t usart_get_char(Usart *usart)
{
	while ((usart->US_CSR & US_CSR_RXRDY) == 0);
	/* Force an octet read to avoid race conditions with FIFO mode */
	uint8_t v;
	readb(&usart->US_RHR, &v);
	return v;
}

void usart_set_irda_filter(Usart *usart, uint8_t filter)
{
	assert(usart != NULL);

	usart->US_IF = filter;
	/* Set IrDA mode. */
	usart->US_MR = (usart->US_MR & ~US_MR_USART_MODE_Msk) | US_MR_USART_MODE_IRDA;
}

void usart_set_sync_slave_baudrate(Usart *usart)
{
	usart->US_MR = (usart->US_MR & ~US_MR_USCLKS_Msk) | US_MR_USCLKS_SCK | US_MR_SYNC;
}

uint32_t usart_init_hw_handshaking(Usart *usart)
{
	/* The USART should be initialized first as standard RS232. */
	/* Set hardware handshaking mode. */
	usart->US_MR = (usart->US_MR & ~US_MR_USART_MODE_Msk) | US_MR_USART_MODE_HW_HANDSHAKING;
	return 0;
}

uint32_t usart_set_async_baudrate(Usart *usart, uint32_t baudrate)
{
	uint32_t over, cd_fp, cd, fp;
	uint32_t mck;

	/* get peripheral clock */
	mck = pmc_get_peripheral_clock(get_usart_id_from_addr(usart));

	/* Calculate the receiver sampling divide of baudrate clock. */
	if (mck >= HIGH_FRQ_SAMPLE_DIV * baudrate) {
		over = HIGH_FRQ_SAMPLE_DIV;
	} else {
		over = LOW_FRQ_SAMPLE_DIV;
	}

	/* Calculate clock divider according to the fraction calculated formula. */
	cd_fp = (8 * mck + (over * baudrate) / 2) / (over * baudrate);
	cd = cd_fp >> 0x03;
	fp = cd_fp & 0x07;
	if (cd < MIN_CD_VALUE || cd > MAX_CD_VALUE) {
		return 1;
	}

	/* Configure the OVER bit in MR register. */
	if (over == 8) {
		usart->US_MR |= US_MR_OVER;
	}

	/* Configure the baudrate generate register. */
	usart->US_BRGR = (cd << US_BRGR_CD_Pos) | (fp << US_BRGR_FP_Pos);

	return 0;
}

/*-----------------------------------------------------------------------------
*        Functions if FIFO are used
 *---------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_USART_FIFO
void usart_fifo_configure(Usart *usart, uint8_t tx_thres, uint8_t rx_down_thres, uint8_t rx_up_thres)
{
	/* Configure FIFO */
	usart->US_FMR = US_FMR_TXFTHRES(tx_thres) | US_FMR_RXFTHRES(rx_down_thres)
		| US_FMR_RXFTHRES2(rx_up_thres) | US_FMR_RXRDYM_ONE_DATA | US_FMR_TXRDYM_FOUR_DATA;

	/* Disable all fifo related interrupts */
	usart->US_FIDR = 0xFFFFFFFF;
}

void usart_fifo_enable(Usart *usart)
{
	/* Reset and disable receiver & transmitter */
	usart->US_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS | US_CR_FIFOEN;

	/* Reenable receiver & transmitter */
	usart->US_CR = US_CR_RXEN | US_CR_TXEN;
}

void usart_fifo_disable(Usart *usart)
{
	/* Reset and disable receiver & transmitter */
	usart->US_CR = US_CR_RSTRX | US_CR_RSTTX | US_CR_RXDIS | US_CR_TXDIS;

	/* Reenable receiver & transmitter */
	usart->US_CR = US_CR_RXEN | US_CR_TXEN;
}

void usart_fifo_enable_it(Usart *usart, uint32_t interrupt_mask)
{
	usart->US_FIER = interrupt_mask;
}

void usart_fifo_disable_it(Usart *usart, uint32_t interrupt_mask)
{
	usart->US_FIDR = interrupt_mask;
}

uint32_t usart_fifo_get_rx_size(Usart *usart)
{
	return (usart->US_FLR & US_FLR_RXFL_Msk) >> US_FLR_RXFL_Pos;
}

uint32_t usart_fifo_get_tx_size(Usart *usart)
{
	return (usart->US_FLR & US_FLR_TXFL_Msk) >> US_FLR_TXFL_Pos;
}

#endif /* CONFIG_HAVE_USART_FIFO */
