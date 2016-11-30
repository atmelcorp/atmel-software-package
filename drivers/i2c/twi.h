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

/**
 * \file
 *
 * Interface for configuration the Two Wire Interface (TWI) peripheral.
 *
 */

#ifndef _TWI_H_
#define _TWI_H_

/*------------------------------------------------------------------------------
 *         Headers
 *------------------------------------------------------------------------------*/

#include "chip.h"

#include <stdint.h>

/*----------------------------------------------------------------------------
 *        Macros
 *----------------------------------------------------------------------------*/

/* Returns 1 if the TXRDY bit (ready to transmit data) is set in the given status register value.*/
#define TWI_STATUS_TXRDY(status) ((status & TWI_SR_TXRDY) == TWI_SR_TXRDY)

/* Returns 1 if the RXRDY bit (ready to receive data) is set in the given status register value.*/
#define TWI_STATUS_RXRDY(status) ((status & TWI_SR_RXRDY) == TWI_SR_RXRDY)

/* Returns 1 if the TXCOMP bit (transfer complete) is set in the given status register value.*/
#define TWI_STATUS_TXCOMP(status) ((status & TWI_SR_TXCOMP) == TWI_SR_TXCOMP)

/* Returns 1 if the GACC bit (General Call access) is set in the given status register value.*/
#define TWI_STATUS_GACC(status) ((status & TWI_SR_GACC) == TWI_SR_GACC)

/* Returns 1 if the SVREAD bit (slave read) is set in the given status register value.*/
#define TWI_STATUS_SVREAD(status) ((status & TWI_SR_SVREAD) == TWI_SR_SVREAD)

/* Returns 1 if the SVACC bit (slave access) is set in the given status register value.*/
#define TWI_STATUS_SVACC(status) ((status & TWI_SR_SVACC) == TWI_SR_SVACC)

/* Returns 1 if the EOSACC bit (end of slave access) is set in the given status register value.*/
#define TWI_STATUS_EOSACC(status) ((status & TWI_SR_EOSACC) == TWI_SR_EOSACC)

/* Returns 1 if the NACK bit (NACK) is set in the given status register value.*/
#define TWI_STATUS_NACK(status) ((status & TWI_SR_NACK) == TWI_SR_NACK)

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *        External function
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures a TWI peripheral to operate in master mode, at the given
 * frequency (in Hz). The duty cycle of the TWI clock is set to 50%.
 * \param twi  Pointer to an Twi instance.
 * \param twi_clock  Desired TWI clock frequency.
 * \return the TWI clock frequency configured
 */
extern uint32_t twi_configure_master(Twi *twi, uint32_t twck);

/**
 * \brief Configures a TWI peripheral to operate in slave mode.
 * \param twi  Pointer to an Twi instance.
 * \param slaveAddress Slave address.
 */
extern void twi_configure_slave(Twi *twi, uint8_t slaveAddress);

/**
 * \brief Sends a STOP condition on the TWI.
 * \param twi  Pointer to an Twi instance.
 */
extern void twi_stop(Twi *twi);

/**
 * \brief Init a read operation on the TWI bus with the specified slave, it returns
 * immediately. Data must then be read using twi_read_byte() whenever a byte is
 * available (poll using twi_is_byte_received()).
 * \param twi  Pointer to an Twi instance.
 * \param address  Slave address on the bus.
 * \param iaddress  Optional internal address bytes.
 * \param isize  Number of internal address bytes.
 */
extern void twi_init_read(Twi *twi, uint8_t address, uint32_t iaddress, uint8_t isize);

/**
 * \brief Reads a byte from the TWI bus. The read operation must have been started
 * using twi_start_read() and a byte must be available (check with twi_is_byte_received()).
 * \param twi  Pointer to an Twi instance.
 * \return byte read.
 */
extern uint8_t twi_read_byte(Twi *twi);

/**
 * \brief Sends a byte of data to one of the TWI slaves on the bus.
 * \note This function must be called once before twi_start_write() with
 * the first byte of data  to send, then it shall be called repeatedly
 * after that to send the remaining bytes.
 * \param twi  Pointer to an Twi instance.
 * \param byte  Byte to send.
 */
extern void twi_write_byte(Twi *twi, uint8_t byte);

/**
 * \brief Init a write operation on the TWI to access the selected slave, then
 *  returns immediately.
 * after that to send the remaining bytes.
 * \param twi  Pointer to an Twi instance.
 * \param address  Address of slave to acccess on the bus.
 * \param iaddress  Optional slave internal address.
 * \param isize  Number of internal address bytes.
 */
extern void twi_init_write(Twi *twi, uint8_t address, uint32_t iaddress, uint8_t isize);

/**
 * \brief Check if a byte have been receiced from TWI.
 * \param twi  Pointer to an Twi instance.
 * \return 1 if a byte has been received and can be read on the given TWI
 * peripheral; otherwise, returns 0. This function resets the status register.
 */
extern uint8_t twi_is_byte_received(Twi *twi);

/**
 * \brief Check if a byte have been sent to TWI.
 * \param twi  Pointer to an Twi instance.
 * \return 1 if a byte has been sent  so another one can be stored for
 * transmission; otherwise returns 0. This function clears the status register.
 */
extern uint8_t twi_is_byte_sent(Twi *twi);

/**
 * \brief Check if current transmission is complet.
 * \param twi  Pointer to an Twi instance.
 * \return  1 if the current transmission is complete (the STOP has been sent);
 * otherwise returns 0.
 */
extern uint8_t twi_is_transfer_complete(Twi *twi);

/**
 * \brief Enables the selected interrupts sources on a TWI peripheral.
 * \param twi  Pointer to an Twi instance.
 * \param sources  Bitwise OR of selected interrupt sources.
 */
extern void twi_enable_it(Twi *twi, uint32_t sources);

/**
 * \brief Disables the selected interrupts sources on a TWI peripheral.
 * \param twi  Pointer to an Twi instance.
 * \param sources  Bitwise OR of selected interrupt sources.
 */
extern void twi_disable_it(Twi *twi, uint32_t sources);

/**
 * \brief Get the current status register of the given TWI peripheral.
 * \note This resets the internal value of the status register, so further
 * read may yield different values.
 * \param twi  Pointer to an Twi instance.
 * \return  TWI status register.
 */
extern uint32_t twi_get_status(Twi *twi);

/**
 * \brief Returns the current status register of the given TWI peripheral, but
 * masking interrupt sources which are not currently enabled.
 * \note This resets the internal value of the status register, so further
 * read may yield different values.
 * \param twi  Pointer to an Twi instance.
 */
extern uint32_t twi_get_masked_status(Twi *twi);

/**
 * \brief  Sends a START condition. START Condition is sent just before the first
 * byte transmission in master mode
 * \param twi  Pointer to an Twi instance.
 */
extern void twi_send_start_condition(Twi *twi);

/**
 * \brief  Sends a STOP condition. STOP Condition is sent just after completing
 *  the current byte transmission in master read mode.
 * \param twi  Pointer to an Twi instance.
 */
extern void twi_send_stop_condition(Twi *twi);

#ifdef CONFIG_HAVE_TWI_ALTERNATE_CMD
/**
 * \brief  Configure the register to use alternative commands (write)
 * \param twi  Pointer to an Twi instance.
 * \param len  Length of data to transmit
 */
extern void twi_alt_cmd_configure_write(Twi *twi, uint8_t len);

/**
 * \brief  Configure the register to use alternative commands (read)
 * \param twi  Pointer to an Twi instance.
 * \param len  Length of data to transmit
 */
extern void twi_alt_cmd_configure_read(Twi *twi, uint8_t len);

/**
 * \brief  Enable Alternate commands
 * \param twi  Pointer to an Twi instance.
 */
extern void twi_alt_cmd_enable(Twi *twi);

/**
 * \brief  Disable Alternate commands
 * \param twi  Pointer to an Twi instance.
 */
extern void twi_alt_cmd_disable(Twi *twi);

#endif /* CONFIG_HAVE_TWI_ALTERNATE_CMD */

#ifdef CONFIG_HAVE_TWI_FIFO
/**
 * \brief  Configure FIFO
 * \param twi       Pointer to an Twi instance.
 * \param tx_thres  TX threshold
 * \param rx_thres  RX threshold
 * \param rdym      Ready modes
 */
extern void twi_fifo_configure(Twi *twi, uint8_t tx_thres, uint8_t rx_thres, uint32_t rdym);

/**
 * \brief  Enable FIFO
 * \param twi  Pointer to an Twi instance.
 */
extern void twi_fifo_enable(Twi *twi, bool master);

/**
 * \brief  Disable FIFO
 * \param twi  Pointer to an Twi instance.
 */
extern void twi_fifo_disable(Twi *twi, bool master);

/**
 * \brief  Get RX FIFO size
 * \param twi       Pointer to an Twi instance.
 * \return the number of bytes in the FIFO
 */
extern uint32_t twi_fifo_get_rx_size(Twi *twi);

/**
 * \brief  Get TX FIFO size
 * \param twi       Pointer to an Twi instance.
 * \return the number of bytes in the FIFO
 */
extern uint32_t twi_fifo_get_tx_size(Twi *twi);

/**
 * Write data to fifo up to FIFO bytes
 * \param twi
 * \param data
 * \param size
 * \return size bytes
 */
extern uint8_t twi_fifo_write(Twi *twi, uint8_t *data, uint8_t size);

/**
 * Read data from FIFO up to FIFO bytes
 * \param twi
 * \param data
 * \param size
 * \return size bytes
 */
extern uint8_t twi_fifo_read(Twi *twi, uint8_t *data, uint8_t size);

extern void twi_fifo_flush_rx(Twi *twi);

extern void twi_fifo_flush_tx(Twi *twi);

extern bool twi_fifo_is_locked(Twi *twi);

extern void twi_fifo_unlock(Twi *twi);
#endif /* CONFIG_HAVE_TWI_FIFO */

#ifdef __cplusplus
}
#endif
#endif /* #ifndef _TWI_H_ */
