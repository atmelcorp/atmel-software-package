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

/** \addtogroup ssc_module Working with SSC
 * \section Purpose
 * The SSC driver provides the interface to configure and use the SSC
 * peripheral.
 *
 * \section Usage
 * -# Enable the SSC interface pins.
 * -# Configure the SSC to operate at a specific frequency by calling
 *    SSC_Configure(). This function enables the peripheral clock of the SSC,
 *    but not its PIOs.
 * -# Configure the transmitter and/or the receiver using the
 *    SSC_ConfigureTransmitter() and SSC_ConfigureEmitter() functions.
 * -# Enable the PIOs or the transmitter and/or the received.
 * -# Enable the transmitter and/or the receiver using SSC_EnableTransmitter()
 *    and SSC_EnableReceiver()
 * -# Send data through the transmitter using SSC_Write()
 * -# Receive data from the receiver using SSC_Read()
 * -# Disable the transmitter and/or the receiver using SSC_DisableTransmitter()
 *    and SSC_DisableReceiver()
 *
 * For more accurate information, please look at the SSC section of the
 * Datasheet.
 *
 * Related files :\n
 * \ref ssc.c\n
 * \ref ssc.h.\n
*/
/*@{*/
/*@}*/

/**
 * \file
 *
 * Implementation of Synchronous Serial (SSC) controller.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "peripherals/ssc.h"
#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *       Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures a SSC peripheral.If the divided clock is not used, the master
 * clock frequency can be set to 0.
 * \note The emitter and transmitter are disabled by this function.
 * \param desc  Pointer to an SSC instance.
 */
void ssc_configure(struct _ssc_desc* desc)
{
	uint32_t id;
	uint32_t clock;
	id = (desc->addr == SSC0) ? ID_SSC0 : ID_SSC1;
	clock = pmc_get_peripheral_clock(id);

	/* Reset, disable receiver & transmitter */
	desc->addr->SSC_CR = SSC_CR_RXDIS | SSC_CR_TXDIS | SSC_CR_SWRST;

	/* Configure clock frequency */
	if (desc->bit_rate != 0) {
		desc->addr->SSC_CMR = clock / (2 * desc->bit_rate);
	} else {
		desc->addr->SSC_CMR = 0;
	}

	if (desc->rx_auto_cfg) {
		uint32_t rcmr = SSC_RCMR_CKS_RK |
		                SSC_RCMR_CKO_NONE |
		                SSC_RCMR_CKI |
		                SSC_RCMR_START_RF_EDGE |
		                SSC_RCMR_STTDLY(1) |
		                SSC_RCMR_PERIOD(0);

		uint32_t rfmr = SSC_RFMR_DATLEN(desc->slot_length - 1) |
		                SSC_RFMR_MSBF |
		                SSC_RFMR_DATNB(desc->slot_num - 1) |
		                SSC_RFMR_FSOS_NONE;

		ssc_configure_receiver(desc, rcmr, rfmr);
	} else {
		ssc_disable_receiver(desc);
	}

	if (desc->tx_auto_cfg) {
		uint32_t tcmr = SSC_TCMR_CKS_TK |
		                SSC_TCMR_CKO_NONE |
		                SSC_TCMR_START_TF_EDGE |
		                SSC_TCMR_STTDLY(1) |
		                SSC_TCMR_PERIOD(0);

		uint32_t tfmr = SSC_TFMR_DATLEN(desc->slot_length - 1) |
		                SSC_TFMR_MSBF |
		                SSC_TFMR_DATNB(desc->slot_num - 1) |
		                SSC_TFMR_FSOS_NONE;

		ssc_configure_transmitter(desc, tcmr, tfmr);
	} else {
		ssc_disable_transmitter(desc);
	}

	/* Enable SSC peripheral clock */
	pmc_enable_peripheral(id);
}

/**
 * \brief Configures the transmitter of a SSC peripheral.
 * \param desc  Pointer to an SSC instance.
 * \param tcmr Transmit Clock Mode Register value.
 * \param tfmr Transmit Frame Mode Register value.
 */
void ssc_configure_transmitter(struct _ssc_desc* desc, uint32_t tcmr, uint32_t tfmr)
{
	desc->addr->SSC_TCMR = tcmr;
	desc->addr->SSC_TFMR = tfmr;
}

/**
 * \brief Configures the receiver of a SSC peripheral.
 * \param desc  Pointer to an SSC instance.
 * \param rcmr Receive Clock Mode Register value.
 * \param rfmr Receive Frame Mode Register value.
 */
void ssc_configure_receiver(struct _ssc_desc* desc, uint32_t rcmr, uint32_t rfmr)
{
	desc->addr->SSC_RCMR = rcmr;
	desc->addr->SSC_RFMR = rfmr;
}

/**
 * \brief Enables the transmitter of a SSC peripheral.
 * \param desc  Pointer to an SSC instance.
 */
void ssc_enable_transmitter(struct _ssc_desc* desc)
{
	desc->addr->SSC_CR = SSC_CR_TXEN;
}

/**
 * \brief Disables the transmitter of a SSC peripheral.
 * \param desc  Pointer to an SSC instance.
 */
void ssc_disable_transmitter(struct _ssc_desc* desc)
{
	desc->addr->SSC_CR = SSC_CR_TXDIS;
}

/**
 * \brief Enables the receiver of a SSC peripheral.
 * \param desc  Pointer to an SSC instance.
 */
void ssc_enable_receiver(struct _ssc_desc* desc)
{
	desc->addr->SSC_CR = SSC_CR_RXEN;
}

/**
 * \brief Disables the receiver of a SSC peripheral.
 * \param desc  Pointer to an SSC instance.
 */
void ssc_disable_receiver(struct _ssc_desc* desc)
{
	desc->addr->SSC_CR = SSC_CR_RXDIS;
}

/**
 * \brief Enables one or more interrupt sources of a SSC peripheral.
 * \param desc  Pointer to an SSC instance.
 * \param sources Bitwise OR of selected interrupt sources.
 */
void ssc_enable_interrupts(struct _ssc_desc* desc, uint32_t sources)
{
	desc->addr->SSC_IER = sources;
}

/**
 * \brief Disables one or more interrupt sources of a SSC peripheral.
 * \param desc  Pointer to an SSC instance.
 * \param sources Bitwise OR of selected interrupt sources.
 */
void ssc_disable_interrupts(struct _ssc_desc* desc, uint32_t sources)
{
	desc->addr->SSC_IDR = sources;
}

/**
 * \brief Sends one data frame through a SSC peripheral. If another frame is currently
 * being sent, this function waits for the previous transfer to complete.
 * \param desc  Pointer to an SSC instance.
 * \param frame Data frame to send.
 */
void ssc_write(struct _ssc_desc* desc, uint32_t frame)
{
	while ((desc->addr->SSC_SR & SSC_SR_TXRDY) == 0) ;
	desc->addr->SSC_THR = frame;
}

/**
 * \brief Waits until one frame is received on a SSC peripheral, and returns it.
 * \param desc  Pointer to an SSC instance.
 */
uint32_t ssc_read(struct _ssc_desc* desc)
{
	while ((desc->addr->SSC_SR & SSC_SR_RXRDY) == 0) ;
	return desc->addr->SSC_RHR;
}

/**
 * \brief Return 1 if one frame is received, 0 otherwise.
 * \param desc  Pointer to an SSC instance.
 */
uint8_t ssc_is_rx_ready(struct _ssc_desc* desc)
{
	return ((desc->addr->SSC_SR & SSC_SR_RXRDY) > 0);
}
