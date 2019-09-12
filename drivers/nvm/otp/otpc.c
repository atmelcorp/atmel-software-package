/* ---------------------------------------------------------------------------- */
/*                Microchip Microcontroller Software Support                    */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2019, Microchip Technology Inc.                                */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Microchip's name may not be used to endorse or promote products derived from */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS  */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT    */
/* ARE DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT,        */
/* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF     */
/* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */
/* ---------------------------------------------------------------------------- */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>

#include "chip.h"
#include "otpc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Marcos
 *----------------------------------------------------------------------------*/

// #define CONFIG_HAVE_OTP_DEBUG

#define OTPC_UID_DISABLED 0XCAFECAFE

#define OTPC_KEY_FOR_WRITING      (0x7167U)
#define OTPC_KEY_FOR_UPDATING     (0x7167U)
#define OTPC_KEY_FOR_LOCKING      OTPC_KEY_FOR_UPDATING
#define OTPC_KEY_FOR_INVALIDATING OTPC_KEY_FOR_UPDATING
#define OTPC_KEY_FOR_EMUL         OTPC_KEY_FOR_UPDATING

#define OTPC_MAX_PAYLOAD_ALLOWED  1024

#define OTPC_4B_AND_REGULAR       (OTPC_HR_PACKET_REGULAR | OTPC_HR_ONE)

/*
 * writing one word lasts 350us
 * the timeout was chosen to be enough for writing 10 words
 **/
#define TIMEOUT 500000

#ifdef OTPC_MR_KBDST_Msk
  #define OTPC_MR_KBDST_SET(value) ((OTPC->OTPC_MR & ~OTPC_MR_KBDST_Msk) | OTPC_MR_KBDST(value))
#else
  #define OTPC_MR_KBDST_SET(value) ((OTPC->OTPC_MR & ~OTPC_MR_KBDST) | (((value) * (OTPC_MR_KBDST & ~(OTPC_MR_KBDST << 1))) & OTPC_MR_KBDST))
  #define OTPC_MR_KBDST_Msk OTPC_MR_KBDST
#endif

#define OTPC_MR_ALWAYS_RESET_Msk (OTPC_MR_KBDST_Msk | OTPC_MR_NPCKT)

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static uint16_t otp_get_payload_size(uint32_t pckt_hdr)
{
	uint16_t pckt_size;

	pckt_size = (pckt_hdr & OTPC_HR_SIZE_Msk) >> OTPC_HR_SIZE_Pos;
	return (pckt_size + 1) * sizeof(uint32_t);
}

static uint32_t otp_wait_isr(uint32_t mask)
{
	uint32_t timeout = TIMEOUT;
	uint32_t reg;
	do {
		reg = OTPC->OTPC_ISR;
		if (reg & mask)
			break;
		timeout--;
	} while (timeout != 0);
	return reg;
}

/*!
  \brief The generic part used for both Atmel and User spaces
  \param hdr_addr Represents the address of the header given by value
  \param pckt_hdr Pointer to the output word where OTPC_HR is written into
  \return OTPC_NO_ERROR is successfull, OTPC_READING_DID_NOT_STOP otherwise.
 */
static uint8_t otp_trigger_packet_read(uint16_t hdr_addr, uint32_t *pckt_hdr)
{
	uint32_t isr_reg, mr_reg;

	/* Write address of the header in OTPC_MR register (AADDR field)*/
	mr_reg = OTPC->OTPC_MR;
	mr_reg &= ~OTPC_MR_ALWAYS_RESET_Msk;
	mr_reg = (mr_reg & ~OTPC_MR_ADDR_Msk) | OTPC_MR_ADDR(hdr_addr);
	OTPC->OTPC_MR = mr_reg;

	/* Set READ bit in OTPC_CR register*/
	OTPC->OTPC_CR = OTPC_CR_READ;

	/* Wait for EOR bit in OTPC_ISR to be 1 (packet was transfered )*/
	isr_reg = otp_wait_isr(OTPC_ISR_EOR);
	if (!(isr_reg & OTPC_ISR_EOR))
		return OTPC_READING_DID_NOT_STOP;

	/* Read the header value from OTPC_HR */
	if (pckt_hdr)
		*pckt_hdr = OTPC->OTPC_HR;

	return OTPC_NO_ERROR;
}

static uint8_t otp_trans_key(uint32_t key_bus_dest)
{
	uint32_t isr_reg;
	uint32_t value;

	switch (key_bus_dest) {
#ifdef OTPC_MR_KBDST_AES
	case OTPC_AES_MODULE:
		value = OTPC_MR_KBDST_AES;
		break;
#endif
#ifdef OTPC_MR_KBDST_TDES
	case OTPC_TDES_MODULE:
		value = OTPC_MR_KBDST_TDES;
		break;
#endif
	default:
		return OTPC_CANNOT_TRANSFER_KEY;
	}
	OTPC->OTPC_MR = (OTPC->OTPC_MR & ~OTPC_MR_KBDST_Msk) | value;
	OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_WRITING) | OTPC_CR_KBSTART;
	isr_reg = otp_wait_isr(OTPC_ISR_EOKT);
	if (!(isr_reg & OTPC_ISR_EOKT) || (isr_reg & OTPC_ISR_KBERR))
		return OTPC_CANNOT_TRANSFER_KEY;
	return 0;
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/*!
  \brief Perform a read of a packet
  \param hdr_addr Represents the address of the packet header to be read
  \param dest Represents the output buffer in which the payload will be put
                   In case of a key transfer the value of the dest must be :
                   - OTPC_AES_MODULE
                   - OTPC_TZAESB_MODULE
                   - OTPC_TDES_MODULE
  \param buffer_size Represents the buffer size where data will be put
  \return error code: - OTPC_ERROR_BUFFER_OVERFLOW - The payload is too big
                      - OTPC_NO_ERROR              - Payload read successfully
                      - OTPC_CANNOT_TRANSFER_KEY   - The key cannot be transfered safely
                      - OTPC_ERROR_PACKET_IS_INVALID - The packet is invalid
 */
uint8_t otp_read_packet(const uint16_t hdr_addr,
                        uint32_t *dest,
                        uint16_t buffer_size,
                        uint16_t *actually_read)
{
	packet_header_t *hdr = NULL;
	uint32_t hdr_value = 0;
	uint16_t payload_size = 0;
	uint8_t error = OTPC_NO_ERROR;
	uint32_t ar_reg;

	if (OTPC->OTPC_MR & OTPC_MR_RDDIS)
		return  OTPC_CANNOT_START_READING;

	error = otp_trigger_packet_read(hdr_addr, &hdr_value);
	if (error != OTPC_NO_ERROR)
		return error;

	hdr = (packet_header_t *)&hdr_value;

	if ((hdr->word & OTPC_HR_INVLD_Msk) == OTPC_HR_INVLD_Msk)
		return OTPC_ERROR_PACKET_IS_INVALID;

	if ((hdr->word & OTPC_HR_PACKET_Msk) == OTPC_HR_PACKET_KEY)
		return otp_trans_key(*dest);

	/*
	 * Read packet payload from offset 0:
	 * clear DADDR field and set INCRT to AFTER_READ
	 */
	ar_reg = OTPC->OTPC_AR;
	ar_reg &= ~(OTPC_AR_DADDR_Msk | OTPC_AR_INCRT);
	ar_reg |= OTPC_AR_INCRT_AFTER_READ;
	OTPC->OTPC_AR = ar_reg;

	/* The value read from header shall be interpreted as follows: */
	/* 0   ==> 4 bytes */
	/* 255 ==> 1024 bytes */
	payload_size = otp_get_payload_size(hdr->word);

	if (payload_size > buffer_size)
		return OTPC_ERROR_BUFFER_OVERFLOW;

	*actually_read = payload_size;

	while (payload_size != 0) {
		/* Start reading the payload (one word at a time) */
		/* otpc_struct->OTPC_DR will be incremented automatically (default value) */
		*dest++ =  OTPC->OTPC_DR;

		/* Update the size of the payload to be read */
		payload_size -= sizeof(uint32_t);
	}

	return OTPC_NO_ERROR;
}

/*!
  \brief
  \param packet_header Represents the value of the header to be written
  \param src Represents the payload to be written
  \param pckt_hdr_addr Represents the address of the header. It is an output
  \param actually_written Represents the actual size which was written
  \return error code: - OTPC_NO_ERROR                 - Packet was written successfully
                      - OTPC_ERROR_PACKET_OVERLAPPED  - Packet overlaps another one
                      - OTPC_ERROR_HW_WRITE_DISABLED  - No write access is allowed
                      - OTPC_ERROR_PACKET_INVALIDATED - Packet was invalidated
                      - OTPC_CANNOT_START_PROGRAMMING - Cannot perform writing operation
                      - OTPC_READING_DID_NOT_START    - Cannot perform reading operation
                      - OTPC_READING_DID_NOT_STOP     - A read operation is not ended
                      - OTPC_FLUSHING_DID_NOT_END     - Flushing operation did not end
 */
uint8_t otp_write_packet(const packet_header_t *packet_header,
                         const uint32_t *src,
                         uint16_t *const pckt_hdr_addr,
                         uint16_t *actually_written)
{
	uint32_t backup_header_reg;
	uint32_t backup_data_reg;
	uint32_t backup_header_value = packet_header->word;
	const uint32_t *backup_src = src;
	uint32_t error = OTPC_NO_ERROR;
	uint32_t isr_reg, mr_reg, ar_reg;
	uint16_t payload_size = otp_get_payload_size(packet_header->word);
	uint16_t backup_size = payload_size;
	uint16_t size_field;
	bool must_invalidate = false;
	bool is_key = false;

	if (payload_size > OTPC_MAX_PAYLOAD_ALLOWED)
		return OTPC_PACKET_TOO_BIG;

	/* Check against the hardware write disable */
	if (OTPC->OTPC_MR & OTPC_MR_WRDIS)
		return OTPC_ERROR_HW_WRITE_DISABLED;

	if ((packet_header->word & OTPC_HR_PACKET_Msk) == OTPC_HR_PACKET_KEY) {
		is_key = true;
		backup_header_value &= ~OTPC_HR_PACKET_Msk;
		backup_header_value |= OTPC_HR_PACKET_REGULAR;
	}

	/* Set MR_ADDR to its maximum value */
	mr_reg = OTPC->OTPC_MR;
	mr_reg &= ~OTPC_MR_ALWAYS_RESET_Msk;
	mr_reg |= OTPC_MR_ADDR_Msk;
	OTPC->OTPC_MR = mr_reg;

	/* Set the READ field */
	OTPC->OTPC_CR = OTPC_CR_READ;

	/* Wait for EOR bit in OTPC_ISR to be 1 (packet was transfered )*/
	isr_reg = otp_wait_isr(OTPC_ISR_EOR);
	if (!(isr_reg & OTPC_ISR_EOR)) {
		if (OTPC->OTPC_SR & OTPC_SR_READ) {
			return OTPC_READING_DID_NOT_STOP;
		} else {
			return OTPC_READING_DID_NOT_START;
		}
	}

	/* There is "1" */
	if (OTPC->OTPC_SR & OTPC_SR_ONEF) {
		backup_header_reg = OTPC->OTPC_HR;
		size_field = otp_get_payload_size(backup_header_reg);
		backup_header_reg |= packet_header->word;

		if (backup_header_reg != packet_header->word) {
			/* Try to minimize the waste of memory, allocate 4 bytes and invalidate the packet */
			backup_size = size_field;
			backup_header_value &= OTPC_4B_AND_REGULAR;
			must_invalidate = true;
			goto start_programming;
		}

		/* Header is safe to be written, but what about payload ? */
		if (!must_invalidate) {
			while (backup_size != 0) {
				backup_data_reg = OTPC->OTPC_DR;
				backup_data_reg |= *backup_src;

				/* Can be payload safely written ? */
				if (backup_data_reg != (*backup_src)) {
					must_invalidate = true;
					backup_size = size_field;
					backup_header_value &= OTPC_4B_AND_REGULAR;
					backup_src = src;
					goto further;
				}

				backup_size -= sizeof(uint32_t);
				backup_src++;
			}
		}

		backup_size = payload_size;
	}

further:
	/* Write OTPC_MR.ADDR to '0' and set NPCKT */
	mr_reg = OTPC->OTPC_MR;
	mr_reg &= ~(OTPC_MR_ALWAYS_RESET_Msk | OTPC_MR_ADDR_Msk);
	mr_reg |= OTPC_MR_NPCKT;
	OTPC->OTPC_MR = mr_reg;

	/* Check for flushing process */
	if (OTPC->OTPC_SR & OTPC_SR_FLUSH) {
		/* Wait until flush operation is done or timeout occured */
		isr_reg = otp_wait_isr(OTPC_ISR_EOF);
		if (!(isr_reg & OTPC_ISR_EOF)) {
			error = OTPC_FLUSHING_DID_NOT_END;
			goto __exit__;
		}
	}

	OTPC->OTPC_HR = backup_header_value;

	/*
	 * Write packet payload from offset 0:
	 * clear DADDR field and set INCRT to AFTER_WRITE
	 */
	ar_reg = OTPC->OTPC_AR;
	ar_reg &= ~(OTPC_AR_DADDR_Msk | OTPC_AR_INCRT);
	ar_reg |= OTPC_AR_INCRT_AFTER_WRITE;
	OTPC->OTPC_AR = ar_reg;

	/* Start downloading data */
	while (backup_size) {
		OTPC->OTPC_DR = *src++;

		backup_size -= sizeof(uint32_t);
	}

	if (is_key) {
		backup_header_value &= ~OTPC_HR_PACKET_Msk;
		backup_header_value |= OTPC_HR_PACKET_KEY;
		OTPC->OTPC_HR = backup_header_value;
	}

start_programming:

	/* Set the KEY field * Set PGM field */
	OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_WRITING) | OTPC_CR_PGM;

	/* Check whether the data was written correctly */
	isr_reg = otp_wait_isr(OTPC_ISR_EOP);
	if (!(isr_reg & OTPC_ISR_EOP) || (isr_reg & OTPC_ISR_WERR)) {
		error = OTPC_CANNOT_START_PROGRAMMING;
		goto __exit__;
	}

	/* Retrieve the address of the packet header */
	*pckt_hdr_addr = (OTPC->OTPC_MR & OTPC_MR_ADDR_Msk) >> OTPC_MR_ADDR_Pos;

	if (must_invalidate) {
		/* Invalidate packet */
		otp_invalidate_packet(*pckt_hdr_addr);

		error = OTPC_ERROR_PACKET_INVALIDATED;
		*actually_written = size_field;
	} else {
		*actually_written = payload_size;
	}

__exit__:
	OTPC->OTPC_MR &= ~OTPC_MR_NPCKT;

	return error;
}

/*!
  \brief Updating an existing packet
  \param hdr_addr Represents the address of the header
  \param src Represents the input buffer
  \return error code: - OTPC_NO_ERROR                  - Packet was updated successfully
                      - OTPC_CANNOT_START_PROGRAMMING  - The packet cannot be updated
                      - OTPC_ERROR_PACKET_IS_INVALID   - The packet is invalid
 */
uint8_t otp_update_payload(const uint16_t hdr_addr, const uint32_t *src)
{
	packet_header_t *hdr = (packet_header_t *)NULL;
	uint32_t hdr_value = 0;
	uint32_t timeout = TIMEOUT;
	uint32_t reg;
	uint16_t payload_size = 0;
	uint8_t error = OTPC_NO_ERROR;

	error = otp_trigger_packet_read(hdr_addr, &hdr_value);
	if (error != OTPC_NO_ERROR)
		return error;

	hdr = (packet_header_t *)&hdr_value;

	if ((hdr->word & OTPC_HR_INVLD_Msk) == OTPC_HR_INVLD_Msk)
		return OTPC_ERROR_PACKET_IS_INVALID;

	/*
	 * Write packet payload from offset 0:
	 * clear DADDR field and set INCRT to AFTER_WRITE
	 */
	reg = OTPC->OTPC_AR;
	reg &= ~(OTPC_AR_DADDR_Msk | OTPC_AR_INCRT);
	reg |= OTPC_AR_INCRT_AFTER_WRITE;
	OTPC->OTPC_AR = reg;

	/* The value read from header shall be interpreted as follows: */
	/* 0   ==> 4 bytes */
	/* 255 ==> 1024 bytes */
	payload_size = otp_get_payload_size(hdr->word);

	while (payload_size) {
		OTPC->OTPC_DR = *src++;

		payload_size -= sizeof(uint32_t);
	}

	/* Set the KEY field && PGM */
	OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_UPDATING) | OTPC_CR_PGM;

	do {
		reg = OTPC->OTPC_SR;
		timeout--;

	} while (!(reg & OTPC_SR_PGM) && (timeout != 0));
	/* Is the programming sequence started ? */

	if (!(reg & OTPC_CR_PGM) && (timeout == 0))
		return OTPC_CANNOT_START_PROGRAMMING;

	/* Programming without errors */
	reg = otp_wait_isr(OTPC_ISR_EOP);
	if (!(reg & OTPC_ISR_EOP) || (reg & OTPC_ISR_WERR))
		return OTPC_CANNOT_START_PROGRAMMING;

	return OTPC_NO_ERROR;
}

/*!
  \brief Locking a packet
  \param hdr_addr Represents the address of the packet header to be locked
  \return error code: - OTPC_CANNOT_LOCK - The packet cannot be locked
                      - OTPC_NO_ERROR    - The packet was locked susscessfully
                      - OTPC_ERROR_PACKET_IS_INVALID - The packet is invalid
 */
uint8_t otp_lock_packet(const uint16_t hdr_addr)
{
	packet_header_t hdr;
	uint32_t reg;
	uint8_t error = OTPC_NO_ERROR;

	error = otp_trigger_packet_read(hdr_addr, &hdr.word);
	if (error != OTPC_NO_ERROR)
		return error;

	if ((hdr.word & OTPC_HR_INVLD_Msk) == OTPC_HR_INVLD_Msk)
		return OTPC_ERROR_PACKET_IS_INVALID;

	/* Set the KEY field */
	OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_LOCKING) | OTPC_CR_CKSGEN;

	/* Wait for locking the packet */
	reg = otp_wait_isr(OTPC_ISR_EOL);
	if (!(reg & OTPC_ISR_EOL))
		return OTPC_CANNOT_LOCK;

	return OTPC_NO_ERROR;
}

/*!
  \brief Invalidating a packet
  \param hdr_addr Represents the address of the packet header to be invalidated
  \return error code: - OTPC_CANNOT_INVALIDATE - The packet cannot be invalidated
                      - OTPC_NO_ERROR          - The packet was invalidated successfully
 */
uint8_t otp_invalidate_packet(const uint16_t hdr_addr)
{
	uint32_t reg;

	/* Set the header address and using reg as temp value */
	reg = OTPC->OTPC_MR;
	reg &= ~OTPC_MR_ALWAYS_RESET_Msk;
	reg = (reg & ~OTPC_MR_ADDR_Msk) | OTPC_MR_ADDR(hdr_addr);
	OTPC->OTPC_MR = reg;

	OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_INVALIDATING) | OTPC_CR_INVLD;

	/* Wait for invalidating the packet */
	reg = otp_wait_isr(OTPC_ISR_EOI);
	if (!(reg & OTPC_ISR_EOI))
		return OTPC_CANNOT_INVALIDATE;

	return OTPC_NO_ERROR;
}

/*!
  \brief Enable/Disable the emulation mode
  \param enable Represents the memory area in which the emulation will be enabled
  \return error code:
                    - OTPC_ERROR_EMULATION   - Update emulation mode failed
                    - OTPC_NO_ERROR          - Update emulation mode succeed
                    - OTPC_CANNOT_REFRESH    - The memory cannot be refreshed
                    - OTPC_ERROR_MR_LOCKED   - Register OTPC_MR is locked
 */
uint8_t otp_emulation_mode(bool on_off)
{
	uint32_t reg;
	uint32_t mr_emul_value;

	mr_emul_value = (((uint32_t)!!on_off) * (OTPC_MR_EMUL & ((~OTPC_MR_EMUL) << 1)));
	OTPC->OTPC_MR = (OTPC->OTPC_MR & (~OTPC_MR_EMUL)) | mr_emul_value;

	OTPC->OTPC_CR = OTPC_CR_REFRESH | OTPC_CR_KEY(OTPC_KEY_FOR_EMUL);

	/* Wait for refreshing data */
	reg = otp_wait_isr(OTPC_ISR_EORF);
	if (!(reg & OTPC_ISR_EORF))
		return OTPC_CANNOT_REFRESH;

	/* Check if the Emulation mode state */
	if ((!!(OTPC->OTPC_SR & OTPC_SR_EMUL)) ^ (!!on_off))
		return OTPC_ERROR_CANNOT_ACTIVATE_EMULATION;

	return OTPC_NO_ERROR;
}

/*!
  \brief The routine checks whether or not the OTP emulation mode is enabled
  \param none
  \return true  - OTP enumation mode is enabled
         false - OTP enumation mode is disabled
*/
bool otp_is_emulation_enabled(void)
{
	return (OTPC->OTPC_SR & OTPC_SR_EMUL) == OTPC_SR_EMUL;
}

/*!
  \brief The routine hides a packet
  \param hdr_addr Represents the header address to be hidden
  \return error code: - OTPC_NO_ERROR              - Packet was hidden successfully
                      - OTPC_CANNOT_START_HIDING   - Hiding operation cannot be started
                      - OTPC_CANNOT_PERFORM_HIDING - The hiding operation cannot be completed
*/
uint8_t otp_hide_packet(const uint16_t hdr_addr)
{
	uint32_t timeout = TIMEOUT;
	uint32_t reg;
	uint8_t error = OTPC_NO_ERROR;

	reg = OTPC->OTPC_MR;
	reg &= ~OTPC_MR_ALWAYS_RESET_Msk;
	reg = (reg & ~OTPC_MR_ADDR_Msk) | OTPC_MR_ADDR(hdr_addr);
	OTPC->OTPC_MR = reg;

	OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_WRITING) | OTPC_CR_HIDE;

	do {
		reg = OTPC->OTPC_SR;
		timeout--;

	} while (!(reg & OTPC_SR_HIDE) && (timeout != 0));

	if((timeout == 0) || (!(reg & OTPC_SR_HIDE))) {
		error = OTPC_CANNOT_START_HIDING;
		goto _exit_;
	}

	reg = otp_wait_isr(OTPC_ISR_EOH);
	if (!(reg & OTPC_ISR_EOH)) {
		error = OTPC_CANNOT_PERFORM_HIDING;
	}

_exit_:
	return error;
}

/*!
 \brief The routine checks whether or not the OTP is disabled
 \param none
 \return true  - OTP is disabled
         false - OTP is not disabled
*/
bool otp_is_disabled(void)
{
	return (
	    (OTPC->OTPC_UIDxR[0] == OTPC_UID_DISABLED) &&
	    (OTPC->OTPC_UIDxR[1] == OTPC_UID_DISABLED) &&
	    (OTPC->OTPC_UIDxR[2] == OTPC_UID_DISABLED) &&
	    (OTPC->OTPC_UIDxR[3] == OTPC_UID_DISABLED));
}
