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

/** \addtogroup twi_module Working with TWI
 * \section Purpose
 * The TWI driver provides the interface to configure and use the TWI
 * peripheral.
 *
 * \section Usage
 * <ul>
 * <li> Configures a TWI peripheral to operate in master mode, at the given
 * frequency (in Hz) using twi_configure(). </li>
 * <li> Sends a STOP condition on the TWI using twi_stop().</li>
 * <li> twi_send_start_condition generate a START condition on the TWI bus with
 * the specified slave. Should be called explicitely.
 * <li> Starts a read operation on the TWI bus with the specified slave using
 * twi_start_read(). Data must then be read using twi_read_byte() whenever
 * a byte is available (poll using twi_is_byte_received()).</li>
 * <li> Starts a write operation on the TWI to access the selected slave using
 * twi_start_write(). A byte of data must be provided to start the write;
 * other bytes are written next.</li>
 * <li> Sends a byte of data to one of the TWI slaves on the bus using twi_write_byte().
 * This function must be called once before twi_start_write() with the first byte of data
 * to send, then it shall be called repeatedly after that to send the remaining bytes.</li>
 * <li> Check if a byte has been received and can be read on the given TWI
 * peripheral using twi_is_byte_received().<
 * Check if a byte has been sent using twi_byte_sent().</li>
 * <li> Check if the current transmission is complete (the STOP has been sent)
 * using twi_is_transfer_complete().</li>
 * <li> Enables & disable the selected interrupts sources on a TWI peripheral
 * using twi_enable_it() and twi_enable_it().</li>
 * <li> Get current status register of the given TWI peripheral using
 * twi_get_status(). Get current status register of the given TWI peripheral, but
 * masking interrupt sources which are not currently enabled using
 * twi_get_masked_status().</li>
 * </ul>
 * For more accurate information, please look at the TWI section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref twi.c\n
 * \ref twi.h.\n
*/
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of Two Wire Interface (TWI).
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "i2c/twi.h"
#include "peripherals/pmc.h"
#include "trace.h"
#include "intmath.h"

#include "timer.h"
#include "io.h"

#include <stddef.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

#if defined(CONFIG_SOC_SAM9XX5) || defined(CONFIG_SOC_SAM9X60)
#define TWI_CLK_OFFSET (4)
#elif defined(CONFIG_SOC_SAMA5D2)
#define TWI_CLK_OFFSET (3) /* TODO: handle GCK case (offset=0) */
#elif defined(CONFIG_SOC_SAMA5D3)
#define TWI_CLK_OFFSET (4)
#elif defined(CONFIG_SOC_SAMA5D4)
#define TWI_CLK_OFFSET (4)
#elif defined(CONFIG_SOC_SAMV71)
#define TWI_CLK_OFFSET (3)
#else
#error Unsupported SoC!
#endif


/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

uint32_t twi_configure_master(Twi *twi, uint32_t twi_clock)
{
	uint32_t ck_div, clh_div, clock;
	uint32_t hold = 0;
	uint32_t id = get_twi_id_from_addr(twi);

	assert(twi);
	assert(id < ID_PERIPH_COUNT);

	/* TWI software reset */
	twi->TWI_CR = TWI_CR_SWRST;

	/* Configure dummy slave address */
	twi->TWI_MMR = 0;

	/* Compute clock */
	clock = pmc_get_peripheral_clock(id);
	for (ck_div = 0; ck_div < 7; ck_div++) {
		clh_div = ((clock / twi_clock) - 2 * TWI_CLK_OFFSET) >> ck_div;
		if (clh_div <= 511)
			break;
	}

#ifdef TWI_CWGR_HOLD
	/* Compute holding time (I2C spec requires 300ns) */
	hold = TWI_CWGR_HOLD(CEIL_INT_DIV((uint32_t)(0.3 * clock), 1000000) - 3);
#endif

	/* Configure clock */
	twi->TWI_CWGR = TWI_CWGR_CKDIV(ck_div)
	              | TWI_CWGR_CHDIV(clh_div >> 1)
	              | TWI_CWGR_CLDIV(clh_div >> 1)
	              | hold;

	/* Set master mode */
	twi->TWI_CR = TWI_CR_SVDIS;
	twi->TWI_CR = TWI_CR_MSEN;

	return clock / ((clh_div << ck_div) + 2 * TWI_CLK_OFFSET);
}

void twi_configure_slave(Twi *twi, uint8_t slave_address)
{
	assert(twi);

	/* TWI software reset */
	twi->TWI_CR = TWI_CR_SWRST;

	/* Configure slave address. */
	twi->TWI_SMR = TWI_SMR_SADR(slave_address);

	/* Set Slave Mode */
	twi->TWI_CR = TWI_CR_MSDIS;
	twi->TWI_CR = TWI_CR_SVEN;
}

void twi_stop(Twi *twi)
{
	assert(twi != NULL);
	twi->TWI_CR = TWI_CR_STOP;
}

void twi_init_read(Twi *twi, uint8_t address, uint32_t iaddress, uint8_t isize)
{
	assert(twi != NULL);
	assert((address & 0x80) == 0);
	assert((iaddress & 0xFF000000) == 0);
	assert(isize < 4);

	/* Set slave address and number of internal address bytes. */
	twi->TWI_MMR = TWI_MMR_DADR(address) | TWI_MMR_MREAD | TWI_MMR_IADRSZ(isize);
	/* Set internal address bytes */
	twi->TWI_IADR = TWI_IADR_IADR(iaddress);
}

uint8_t twi_read_byte(Twi *twi)
{
	assert(twi != NULL);
	uint8_t value;
	readb(&twi->TWI_RHR, &value);
	return value;
}

void twi_write_byte(Twi *twi, uint8_t byte)
{
	assert(twi != NULL);
	writeb(&twi->TWI_THR, byte);
}

void twi_init_write(Twi *twi, uint8_t address, uint32_t iaddress, uint8_t isize)
{
	assert(twi != NULL);
	assert((address & 0x80) == 0);
	assert((iaddress & 0xFF000000) == 0);
	assert(isize < 4);

	/* Set slave address and number of internal address bytes. */
	twi->TWI_MMR = TWI_MMR_DADR(address) | TWI_MMR_IADRSZ(isize);
	/* Set internal address bytes. */
	twi->TWI_IADR = TWI_IADR_IADR(iaddress);
}

uint8_t twi_is_byte_received(Twi *twi)
{
	assert(twi != NULL);
	return (twi->TWI_SR & TWI_SR_RXRDY) == TWI_SR_RXRDY;
}

uint8_t twi_is_byte_sent(Twi *twi)
{
	assert(twi != NULL);
	return (twi->TWI_SR & TWI_SR_TXRDY) == TWI_SR_TXRDY;
}

uint8_t twi_is_transfer_complete(Twi *twi)
{
	assert(twi != NULL);
	return (twi->TWI_SR & TWI_SR_TXCOMP) == TWI_SR_TXCOMP;
}

void twi_enable_it(Twi *twi, uint32_t sources)
{
	assert(twi != NULL);
	twi->TWI_IER = sources;
}

void twi_disable_it(Twi *twi, uint32_t sources)
{
	assert(twi != NULL);
	twi->TWI_IDR = sources;
}

uint32_t twi_get_status(Twi *twi)
{
	assert(twi != NULL);
	return twi->TWI_SR;
}

uint32_t twi_get_masked_status(Twi *twi)
{
	uint32_t status;
	assert(twi != NULL);
	status = twi->TWI_SR;
	status &= twi->TWI_IMR;
	return status;
}

void twi_send_stop_condition(Twi *twi)
{
	assert(twi != NULL);
	twi->TWI_CR = TWI_CR_STOP;
}

void twi_send_start_condition(Twi *twi)
{
	assert(twi != NULL);
	twi->TWI_CR = TWI_CR_START;
}

#ifdef CONFIG_HAVE_TWI_ALTERNATE_CMD

void twi_alt_cmd_configure_write(Twi *twi, uint8_t len)
{
	assert(twi != NULL);
	twi->TWI_ACR = TWI_ACR_DATAL(len);
}

void twi_alt_cmd_configure_read(Twi *twi, uint8_t len)
{
	assert(twi != NULL);
	twi->TWI_ACR = TWI_ACR_DATAL(len) | TWI_ACR_DIR;
}

void twi_alt_cmd_enable(Twi *twi)
{
	twi->TWI_CR = TWI_CR_ACMEN;
}

void twi_alt_cmd_disable(Twi *twi)
{
	twi->TWI_CR = TWI_CR_ACMDIS;
}

#endif /* CONFIG_HAVE_TWI_ALTERNATE_CMD */

#ifdef CONFIG_HAVE_TWI_FIFO

void twi_fifo_configure(Twi *twi, uint8_t tx_thres, uint8_t rx_thres, uint32_t rdym)
{
	assert(twi != NULL);

	/* Configure FIFO */
	twi->TWI_FMR = TWI_FMR_TXFTHRES(tx_thres) | TWI_FMR_RXFTHRES(rx_thres) | rdym;
}

void twi_fifo_enable(Twi *twi, bool master)
{
	assert(twi != NULL);

	/* Enable TWI master and slave mode and activate FIFO */
	twi->TWI_CR = TWI_CR_MSDIS | TWI_CR_SVDIS;
	twi->TWI_CR = TWI_CR_FIFOEN;
	twi->TWI_CR = TWI_CR_TXFCLR | TWI_CR_RXFCLR;

	if (master)
		twi->TWI_CR = TWI_CR_MSEN;
	else
		twi->TWI_CR = TWI_CR_SVEN;
}

void twi_fifo_disable(Twi *twi, bool master)
{
	assert(twi != NULL);

	/* Disable TWI master and slave mode and activate FIFO */
	twi->TWI_CR = TWI_CR_MSDIS | TWI_CR_SVDIS;
	twi->TWI_CR = TWI_CR_TXFCLR | TWI_CR_RXFCLR;
	twi->TWI_CR = TWI_CR_FIFODIS;

	if (master)
		twi->TWI_CR = TWI_CR_MSEN;
	else
		twi->TWI_CR = TWI_CR_SVEN;
}

uint32_t twi_fifo_get_rx_size(Twi *twi)
{
	assert(twi != NULL);

	return (twi->TWI_FLR & TWI_FLR_RXFL_Msk) >> TWI_FLR_RXFL_Pos;
}

uint32_t twi_fifo_get_tx_size(Twi *twi)
{
	assert(twi != NULL);

	return (twi->TWI_FLR & TWI_FLR_TXFL_Msk) >> TWI_FLR_TXFL_Pos;
}

uint8_t twi_fifo_write(Twi *twi, uint8_t *data, uint8_t size)
{
	uint8_t i;

	assert(twi != NULL);

	for (i = 0 ; i < size ; ) {
		if ((size - i) >= 4) {
			writew(&twi->TWI_THR,  *(uint32_t*)&data[i]);
			i += 4;
		} else if ((size - i) >= 2) {
			writehw(&twi->TWI_THR, *(uint16_t*)&data[i]);
			i += 2;
		} else {
			writeb(&twi->TWI_THR,  *(uint8_t*)&data[i]);
			i += 1;
		}
	}

	return i;
}

uint8_t twi_fifo_read(Twi *twi, uint8_t *data, uint8_t size)
{
	uint8_t i;

	assert(twi != NULL);

	for (i = 0 ; i < size ; ) {
		if ((size - i) >= 4) {
			readw(&twi->TWI_RHR, (uint32_t*)&data[i]);
			i += 4;
		} else if ((size - i) >= 2) {
			readhw(&twi->TWI_RHR, (uint16_t*)&data[i]);
			i += 2;
		} else {
			readb(&twi->TWI_RHR,  (uint8_t*)&data[i]);
			i += 1;
		}
	}

	return i;
}

void twi_fifo_flush_rx(Twi *twi)
{
	assert(twi != NULL);
	twi->TWI_CR = TWI_CR_RXFCLR;
}

void twi_fifo_flush_tx(Twi *twi)
{
	assert(twi != NULL);
	twi->TWI_CR = TWI_CR_TXFCLR;
}

bool twi_fifo_is_locked(Twi *twi)
{
	assert(twi != NULL);
	return twi->TWI_SR & TWI_SR_LOCK;
}

void twi_fifo_unlock(Twi *twi)
{
	assert(twi != NULL);
	twi->TWI_CR = TWI_CR_LOCKCLR;
}

#endif /* CONFIG_HAVE_TWI_FIFO */
