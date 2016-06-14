/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
 * \file
 *
 * Implements DBGU console.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "compiler.h"

#include "peripherals/dbgu.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"

#include <assert.h>
#include <stdio.h>
#include <stdint.h>

/*------------------------------------------------------------------------------
*         Exported functions
*------------------------------------------------------------------------------*/

/**
 * \brief Configures an DBGU peripheral with the specified parameters.
 *
 * \param dgbu  Pointer to the DBGU peripheral to configure
 * \param baudrate  Baudrate at which the DBGU should operate (in Hz).
 * \param clock  Frequency of the system master clock (in Hz).
 */
void dbgu_configure(Dbgu* dbgu, uint32_t mode, uint32_t baudrate)
{
	assert(dbgu == DBGU);

	/* Reset and disable receiver & transmitter */
	dbgu->DBGU_CR = DBGU_CR_RSTRX | DBGU_CR_RSTTX;
	dbgu->DBGU_IDR = 0xFFFFFFFF;
	dbgu->DBGU_SR;

	/* Configure mode */
	dbgu->DBGU_MR = mode;

	/* Configure baudrate */
	dbgu->DBGU_BRGR = ROUND_INT_DIV(pmc_get_peripheral_clock(ID_DBGU) / 16, baudrate);

	/* Enable receiver and transmitter */
	dbgu->DBGU_CR = DBGU_CR_RXEN | DBGU_CR_TXEN;
}

/**
 * \brief Outputs a character on the DBGU line.
 *
 * \param Pointer to the DBGU peripheral
 * \note This function is synchronous (i.e. uses polling).
 * \param c  Character to send.
 */
void dbgu_put_char(Dbgu* dbgu, uint8_t c)
{
	/* Wait for the transmitter to be ready */
	while ((dbgu->DBGU_SR & DBGU_SR_TXRDY) == 0);

	/* Send character */
	dbgu->DBGU_THR = c;
}

/**
 * \brief Input a character from the DBGU line.
 *
 * \param Pointer to the DBGU peripheral
 * \note This function is synchronous
 * \return character received.
 */
extern uint32_t dbgu_get_char(Dbgu* dbgu)
{
	while ((dbgu->DBGU_SR & DBGU_SR_RXRDY) == 0);
	return dbgu->DBGU_RHR;
}

/**
 * \brief Check if there is Input from DBGU line.
 *
 * \param  Pointer to the DBGU peripheral
 * \return true if there is Input.
 */
extern uint32_t dbgu_is_rx_ready(Dbgu* dbgu)
{
	return (dbgu->DBGU_SR & DBGU_SR_RXRDY) > 0;
}

/**
 * \brief Enable interrupt bits
 * \param dbgu  Pointer to the DBGU peripheral.
 * \param mode  Interrupt bits to enable
 */
void dbgu_enable_it(Dbgu* dbgu, uint32_t mode)
{
	dbgu->DBGU_IER = mode;
}

/**
 * \brief Disable interrupt bits
 * \param dbgu  Pointer to the DBGU peripheral.
 * \param mode  Interrupt bits to disable
 */
void dbgu_disable_it(Dbgu* dbgu, uint32_t mode)
{
	dbgu->DBGU_IDR = mode;
}
