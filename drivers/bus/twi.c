/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
 * frequency (in Hz) using TWI_Configure(). </li>
 * <li> Sends a STOP condition on the TWI using TWI_Stop().</li>
 * <li> Starts a read operation on the TWI bus with the specified slave using
 * TWI_StartRead(). Data must then be read using TWI_ReadByte() whenever
 * a byte is available (poll using TWI_ByteReceived()).</li>
 * <li> Starts a write operation on the TWI to access the selected slave using
 * TWI_StartWrite(). A byte of data must be provided to start the write;
 * other bytes are written next.</li>
 * <li> Sends a byte of data to one of the TWI slaves on the bus using TWI_WriteByte().
 * This function must be called once before TWI_StartWrite() with the first byte of data
 * to send, then it shall be called repeatedly after that to send the remaining bytes.</li>
 * <li> Check if a byte has been received and can be read on the given TWI
 * peripheral using TWI_ByteReceived().<
 * Check if a byte has been sent using TWI_ByteSent().</li>
 * <li> Check if the current transmission is complete (the STOP has been sent)
 * using TWI_TransferComplete().</li>
 * <li> Enables & disable the selected interrupts sources on a TWI peripheral
 * using TWI_EnableIt() and TWI_DisableIt().</li>
 * <li> Get current status register of the given TWI peripheral using
 * TWI_GetStatus(). Get current status register of the given TWI peripheral, but
 * masking interrupt sources which are not currently enabled using
 * TWI_GetMaskedStatus().</li>
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
#include "bus/twi.h"
#include "core/pmc.h"
#include "utils/trace.h"

#include <stddef.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures a TWI peripheral to operate in master mode, at the given
 * frequency (in Hz). The duty cycle of the TWI clock is set to 50%.
 * \param twi  Pointer to an Twi instance.
 * \param dwTwCk  Desired TWI clock frequency.
 * \param dwMCk  Master clock frequency.
 */
void
TWI_ConfigureMaster(Twi * twi, uint32_t dwTwCk, uint32_t dwMCk)
{
	uint32_t dwCkDiv = 0;
	uint32_t dwClDiv;
	uint32_t dwOk = 0;
	uint32_t id = GET_TWI_ID_FROM_ADDR(twi);
	uint32_t maxClock;

	TRACE_DEBUG("TWI_ConfigureMaster()\n\r");
	assert(twi);
	assert(id != ID_PERIPH_COUNT);

	/* SVEN: TWI Slave Mode Enabled */
	twi->TWI_CR = TWI_CR_SVEN;
	/* Reset the TWI */
	twi->TWI_CR = TWI_CR_SWRST;
	twi->TWI_RHR;

	/* TWI Slave Mode Disabled, TWI Master Mode Disabled. */
	twi->TWI_CR = TWI_CR_SVDIS;
	twi->TWI_CR = TWI_CR_MSDIS;

	/* Set master mode */
	twi->TWI_CR = TWI_CR_MSEN;

	maxClock = pmc_set_peri_max_clock(id, dwMCk);

	/* Configure clock */
	while (!dwOk) {
		dwClDiv = ((maxClock / (2 * dwTwCk)) - 8) / (1 << dwCkDiv);
		if (dwClDiv <= 255) {
			dwOk = 1;
		} else {
			dwCkDiv++;
		}
	}

	assert(dwCkDiv < 8);
	TRACE_DEBUG("Using CKDIV = %u and CLDIV/CHDIV = %u\n\r", dwCkDiv,
		    dwClDiv);

	twi->TWI_CWGR = 0;
	twi->TWI_CWGR = (dwCkDiv << 16) | (dwClDiv << 8) | dwClDiv;
}

/**
 * \brief Configures a TWI peripheral to operate in slave mode.
 * \param twi  Pointer to an Twi instance.
 * \param slaveAddress Slave address.
 */
void
TWI_ConfigureSlave(Twi * twi, uint8_t slaveAddress)
{
	uint32_t i;

	/* TWI software reset */
	twi->TWI_CR = TWI_CR_SWRST;
	twi->TWI_RHR;

	/* Wait at least 10 ms */
	for (i = 0; i < 1000000; i++) ;

	/* TWI Slave Mode Disabled, TWI Master Mode Disabled */
	twi->TWI_CR = TWI_CR_SVDIS | TWI_CR_MSDIS;

	/* Configure slave address. */
	twi->TWI_SMR = 0;
	twi->TWI_SMR = TWI_SMR_SADR(slaveAddress);

	/* SVEN: TWI Slave Mode Enabled */
	twi->TWI_CR = TWI_CR_SVEN;

	/* Wait at least 10 ms */
	for (i = 0; i < 1000000; i++) ;
	assert((twi->TWI_CR & TWI_CR_SVDIS) != TWI_CR_SVDIS);
}

/**
 * \brief Sends a STOP condition on the TWI.
 * \param twi  Pointer to an Twi instance.
 */
void
TWI_Stop(Twi * twi)
{
	assert(twi != NULL);

	twi->TWI_CR = TWI_CR_STOP;
}

/**
 * \brief Starts a read operation on the TWI bus with the specified slave, it returns
 * immediately. Data must then be read using TWI_ReadByte() whenever a byte is
 * available (poll using TWI_ByteReceived()).
 * \param twi  Pointer to an Twi instance.
 * \param address  Slave address on the bus.
 * \param iaddress  Optional internal address bytes.
 * \param isize  Number of internal address bytes.
 */
void
TWI_StartRead(Twi * twi, uint8_t address, uint32_t iaddress, uint8_t isize)
{
	assert(twi != NULL);
	assert((address & 0x80) == 0);
	assert((iaddress & 0xFF000000) == 0);
	assert(isize < 4);

	/* Set slave address and number of internal address bytes. */
	twi->TWI_MMR = 0;
	twi->TWI_MMR = (isize << 8) | TWI_MMR_MREAD | (address << 16);

	/* Set internal address bytes */
	twi->TWI_IADR = 0;
	twi->TWI_IADR = iaddress;

	/* Send START condition */
	twi->TWI_CR = TWI_CR_START;
}

/**
 * \brief Reads a byte from the TWI bus. The read operation must have been started
 * using TWI_StartRead() and a byte must be available (check with TWI_ByteReceived()).
 * \param twi  Pointer to an Twi instance.
 * \return byte read.
 */
uint8_t
TWI_ReadByte(Twi * twi)
{
	assert(twi != NULL);

	return twi->TWI_RHR;
}

/**
 * \brief Sends a byte of data to one of the TWI slaves on the bus.
 * \note This function must be called once before TWI_StartWrite() with
 * the first byte of data  to send, then it shall be called repeatedly
 * after that to send the remaining bytes.
 * \param twi  Pointer to an Twi instance.
 * \param byte  Byte to send.
 */
void
TWI_WriteByte(Twi * twi, uint8_t byte)
{
	assert(twi != NULL);

	twi->TWI_THR = byte;
}

/**
 * \brief Starts a write operation on the TWI to access the selected slave, then
 *  returns immediately. A byte of data must be provided to start the write;
 * other bytes are written next.
 * after that to send the remaining bytes.
 * \param twi  Pointer to an Twi instance.
 * \param address  Address of slave to acccess on the bus.
 * \param iaddress  Optional slave internal address.
 * \param isize  Number of internal address bytes.
 * \param byte  First byte to send.
 */
void
TWI_StartWrite(Twi * twi,
	       uint8_t address, uint32_t iaddress, uint8_t isize, uint8_t byte)
{
	assert(twi != NULL);
	assert((address & 0x80) == 0);
	assert((iaddress & 0xFF000000) == 0);
	assert(isize < 4);

	/* Set slave address and number of internal address bytes. */
	twi->TWI_MMR = 0;
	twi->TWI_MMR = (isize << 8) | (address << 16);

	/* Set internal address bytes. */
	twi->TWI_IADR = 0;
	twi->TWI_IADR = iaddress;

	/* Write first byte to send. */
	TWI_WriteByte(twi, byte);
}

/**
 * \brief Check if a byte have been receiced from TWI.
 * \param twi  Pointer to an Twi instance.
 * \return 1 if a byte has been received and can be read on the given TWI
 * peripheral; otherwise, returns 0. This function resets the status register.
 */
uint8_t
TWI_ByteReceived(Twi * twi)
{
	return ((twi->TWI_SR & TWI_SR_RXRDY) == TWI_SR_RXRDY);
}

/**
 * \brief Check if a byte have been sent to TWI.
 * \param twi  Pointer to an Twi instance.
 * \return 1 if a byte has been sent  so another one can be stored for
 * transmission; otherwise returns 0. This function clears the status register.
 */
uint8_t
TWI_ByteSent(Twi * twi)
{
	return ((twi->TWI_SR & TWI_SR_TXRDY) == TWI_SR_TXRDY);
}

/**
 * \brief Check if current transmission is complet.
 * \param twi  Pointer to an Twi instance.
 * \return  1 if the current transmission is complete (the STOP has been sent);
 * otherwise returns 0.
 */
uint8_t
TWI_TransferComplete(Twi * twi)
{
	return ((twi->TWI_SR & TWI_SR_TXCOMP) == TWI_SR_TXCOMP);
}

/**
 * \brief Enables the selected interrupts sources on a TWI peripheral.
 * \param twi  Pointer to an Twi instance.
 * \param sources  Bitwise OR of selected interrupt sources.
 */
void
TWI_EnableIt(Twi * twi, uint32_t sources)
{
	assert(twi != NULL);
	assert((sources & 0xFFFFF088) == 0);

	twi->TWI_IER = sources;
}

/**
 * \brief Disables the selected interrupts sources on a TWI peripheral.
 * \param twi  Pointer to an Twi instance.
 * \param sources  Bitwise OR of selected interrupt sources.
 */
void
TWI_DisableIt(Twi * twi, uint32_t sources)
{
	assert(twi != NULL);
	assert((sources & 0xFFFFF088) == 0);

	twi->TWI_IDR = sources;
}

/**
 * \brief Get the current status register of the given TWI peripheral.
 * \note This resets the internal value of the status register, so further
 * read may yield different values.
 * \param twi  Pointer to an Twi instance.
 * \return  TWI status register.
 */
uint32_t
TWI_GetStatus(Twi * twi)
{
	assert(twi != NULL);

	return twi->TWI_SR;
}

/**
 * \brief Returns the current status register of the given TWI peripheral, but
 * masking interrupt sources which are not currently enabled.
 * \note This resets the internal value of the status register, so further
 * read may yield different values.
 * \param twi  Pointer to an Twi instance.
 */
uint32_t
TWI_GetMaskedStatus(Twi * twi)
{
	uint32_t status;

	assert(twi != NULL);

	status = twi->TWI_SR;
	status &= twi->TWI_IMR;

	return status;
}

/**
 * \brief  Sends a STOP condition. STOP Condition is sent just after completing
 *  the current byte transmission in master read mode.
 * \param twi  Pointer to an Twi instance.
 */
void
TWI_SendSTOPCondition(Twi * twi)
{
	assert(twi != NULL);

	twi->TWI_CR |= TWI_CR_STOP;
}
