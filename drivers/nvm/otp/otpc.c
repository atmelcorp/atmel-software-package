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

#define OTPC_KEY_FOR_WRITING      ((uint32_t)0x7167)
#define OTPC_KEY_FOR_UPDATING     ((uint32_t)0x7167)
#define OTPC_KEY_FOR_LOCKING      OTPC_KEY_FOR_UPDATING
#define OTPC_KEY_FOR_INVALIDATING OTPC_KEY_FOR_UPDATING
#define OTPC_KEY_FOR_EMUL         OTPC_KEY_FOR_UPDATING

#define OTPC_ADDR_MAX_VALUE       0x1FFF
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

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

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
  \brief The method will wait until a refresh operation is done
  \param none
  \return error code: - OTPC_CANNOT_REFRESH  - No refresh operation has occured
                      - OTPC_NO_ERROR        - The refresh operation is done
*/
static uint8_t wait_for_refreshing(void)
{
	if (0 == otp_wait_isr(OTPC_ISR_EORF)) {
#ifdef CONFIG_HAVE_OTP_DEBUG
		trace_debug("OTP wait for End of refresh failed\r\n");
#endif
		return OTPC_CANNOT_REFRESH;
	}
	return OTPC_NO_ERROR;
}

/*!
  \brief The generic part used for both Atmel and User spaces
  \param hdr_addr Represents the address of the header given by value
  \return error code
 */
static uint8_t otp_trigger_packet_read(const uint16_t hdr_addr)
{
	/* let OTPC_MR writable */
	if (OTPC->OTPC_MR & OTPC_MR_LOCK)
		return OTPC_ERROR_MR_LOCKED;
	OTPC->OTPC_WPMR = (OTPC->OTPC_WPMR & ~OTPC_WPMR_WPCFEN) | OTPC_WPMR_WPKEY_PASSWD;

	/* Write address of the header in OTPC_MR register (AADDR field)*/
	OTPC->OTPC_MR &= ~(OTPC_MR_NPCKT | OTPC_MR_KBDST_Msk);
	OTPC->OTPC_MR = (OTPC->OTPC_MR & ~OTPC_MR_ADDR_Msk) | OTPC_MR_ADDR(hdr_addr);

	/* Set READ bit in OTPC_CR register*/
	OTPC->OTPC_CR = OTPC_CR_READ;

	while ((OTPC->OTPC_SR & OTPC_SR_READ) == OTPC_SR_READ)
		;

	if (0 == otp_wait_isr(OTPC_ISR_EOR))
		return OTPC_READING_DID_NOT_STOP;
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
	if ((isr_reg == 0) || (isr_reg & OTPC_ISR_KBERR))
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
 */
uint8_t otp_read_packet(const uint16_t hdr_addr,
                        uint32_t *dest,
                        uint16_t buffer_size,
                        uint16_t *actually_read)
{
	union otp_packet_header hdr;
	uint8_t error;
	uint16_t read = 0;

	while(1) {
		if (0 != (error = otp_trigger_packet_read(hdr_addr)))
			break;

		hdr.word = OTPC->OTPC_HR;
		if (hdr.header.packet == OTPC_HR_PACKET_KEY) {
			error = otp_trans_key(*dest);
		} else {
			OTPC->OTPC_MR &= ~OTPC_MR_RDDIS;
			if ((hdr.header.size + 1) * sizeof(uint32_t) <= buffer_size) {
				OTPC->OTPC_AR = OTPC_AR_DADDR(0) | OTPC_AR_INCRT_AFTER_READ;
				do {
					*dest++ =  OTPC->OTPC_DR;
				} while(read++ < hdr.header.size);
				read *= sizeof(uint32_t);
			} else
				error = OTPC_ERROR_BUFFER_OVERFLOW;
		}
		break;
	}

	if (actually_read)
		*actually_read = read;
#ifdef CONFIG_HAVE_OTP_DEBUG
	if (error)
		trace_debug("OTP read packet failed, header at 0x%04x, error code: 0x%02x\r\n",
		    hdr_addr, error);
	else
		trace_debug("OTP read packet succeed, header 0x%08x at 0x%04x, size: %u\r\n",
		    (unsigned int)hdr.word, hdr_addr, read);
#endif
	return error;
}

/*!
  \brief
  \param header_data Represents the value of the header to be written
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
uint8_t otp_write_packet(const union otp_packet_header *packet_header,
                         const uint32_t *src,
                         uint16_t *const pckt_hdr_addr,
                         uint16_t *actually_written)
{
	uint32_t backup_data_reg;
	union otp_packet_header hdr_backup;
	const uint32_t *backup_src = src;
	uint8_t error = OTPC_NO_ERROR;
	uint32_t isr_reg;
	uint16_t payload_size = (uint16_t)((packet_header->header.size * 4) + 4);
	uint16_t backup_size = payload_size;
	uint16_t size_field;
	uint16_t written = 0;
	uint8_t payload_offset = 0;
	bool must_invalidate = false;
	bool is_key = false;

	hdr_backup.word = packet_header->word;
	if (payload_size <= OTPC_MAX_PAYLOAD_ALLOWED)
	{
		/* let OTPC_MR writable */
		if (OTPC->OTPC_MR & OTPC_MR_LOCK) {
			error = OTPC_ERROR_MR_LOCKED;
			goto __exit__;
		}
		OTPC->OTPC_WPMR = (OTPC->OTPC_WPMR & ~OTPC_WPMR_WPCFEN) | OTPC_WPMR_WPKEY_PASSWD;

		OTPC->OTPC_MR &= ~OTPC_MR_WRDIS;

		if (packet_header->header.packet == OTPC_HR_PACKET_KEY) {
			is_key = true;
			hdr_backup.header.packet = OTPC_HR_PACKET_REGULAR;
		}

		/* Set MR_REG to its maximum value */
		OTPC->OTPC_MR &= ~(OTPC_MR_NPCKT | OTPC_MR_KBDST_Msk);
		OTPC->OTPC_MR = (OTPC->OTPC_MR & ~OTPC_MR_ADDR_Msk) | OTPC_MR_ADDR(OTPC_ADDR_MAX_VALUE);

		/* Set the READ field */
		OTPC->OTPC_CR = OTPC_CR_READ;

		if (0 == otp_wait_isr(OTPC_ISR_EOR)) {
			error = OTPC_READING_DID_NOT_STOP;
			goto __exit__;
		}
		if (OTPC->OTPC_SR & OTPC_SR_READ) {
			error = OTPC_READING_DID_NOT_START;
			goto __exit__;
		}

		/* There is "1" */
		if (OTPC->OTPC_SR & OTPC_SR_ONEF) {
			size_field = (((OTPC->OTPC_HR & OTPC_HR_SIZE_Msk) >> OTPC_HR_SIZE_Pos) + 1) * 4;
		trace_debug("OTP packet: header 0x%08x\r\n", (unsigned int)OTPC->OTPC_HR);

			if ((OTPC->OTPC_HR | packet_header->word) != packet_header->word) {
				/* Try to minimize the waste of memory, allocate 4 bytes and invalidate the packet */
				must_invalidate = true;
				goto start_programming;
			}

			/* Header is safe to be written, but what about payload ? */
			while (backup_size != 0) {
				backup_data_reg = OTPC->OTPC_DR;
				backup_data_reg |= *backup_src;

				/* Can be payload safely written ? */
				if (backup_data_reg != (*backup_src)) {
					must_invalidate = true;
					backup_size = size_field;
					hdr_backup.word &= OTPC_4B_AND_REGULAR;
					backup_src = src;
					goto further;
				}

				backup_size -= 4;
				backup_src++;
			}

			backup_size = payload_size;
		}

	further:
		OTPC->OTPC_MR = (OTPC->OTPC_MR & ~OTPC_MR_ADDR_Msk) | OTPC_MR_NPCKT;

		/* Check for flushing process */
		if (OTPC->OTPC_SR & OTPC_SR_FLUSH) {
			if (0 == (error = otp_wait_isr(OTPC_ISR_EOF))) {
				error = OTPC_FLUSHING_DID_NOT_END;
				goto __exit__;
			}
		}

		OTPC->OTPC_HR = hdr_backup.word;
		OTPC->OTPC_AR = OTPC_AR_DADDR(0) | OTPC_AR_INCRT_AFTER_WRITE;

		/* Start downloading data */
		while (backup_size) {
			OTPC->OTPC_DR = *src++;
			backup_size -= (uint16_t)4;
			payload_offset++;
		}

		if (is_key == true) {
			hdr_backup.header.packet = OTPC_HR_PACKET_KEY;
			OTPC->OTPC_HR = hdr_backup.word;
		}

	start_programming:
		/* Set the KEY field * Set PGM field */
		OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_WRITING) | OTPC_CR_PGM;

		isr_reg = otp_wait_isr(OTPC_ISR_EOP);
		if ((isr_reg == 0) || (isr_reg & OTPC_ISR_WERR)) {
			error = OTPC_CANNOT_START_PROGRAMMING;
			goto __exit__;
		}

		/* Retrieve the address of the packet header */
		*pckt_hdr_addr = (OTPC->OTPC_MR & OTPC_MR_ADDR_Msk) >> OTPC_MR_ADDR_Pos;

		if (must_invalidate == true) {
			/* Invalidate packet */
			otp_invalidate_packet(*pckt_hdr_addr);

			error = OTPC_ERROR_PACKET_INVALIDATED;
			written = size_field;
		}
		else
		{
			written = payload_size;
		}
	}
	else
	{
		error = OTPC_PACKET_TOO_BIG;
	}

__exit__:
	OTPC->OTPC_MR &= ~OTPC_MR_NPCKT;
	if (actually_written)
		*actually_written = written;
#ifdef CONFIG_HAVE_OTP_DEBUG
	if (error)
		trace_debug("OTP write packet failed, header 0x%08x, error code: 0x%02x\r\n",
		    (unsigned int)packet_header->word, error);
	else
		trace_debug("OTP write packet: header 0x%08x at 0x%08x, %u bytes wrote\r\n",
		    (unsigned int)packet_header->word, *pckt_hdr_addr, written);
#endif
	return error;
}

/*!
  \brief Updating an existing packet
  \param hdr_addr Represents the address of the header
  \param src Represents the input buffer
  \return error code: - OTPC_NO_ERROR                  - Packet was updated successfully
                      - OTPC_CANNOT_START_PROGRAMMING  - The packet cannot be updated
 */
uint8_t otp_update_payload(const uint16_t hdr_addr, const uint32_t *src)
{
	union otp_packet_header hdr;
	uint32_t timeout = TIMEOUT;
	uint32_t reg;
	uint16_t payload_offset = 0;
	uint8_t error;

	while(1) {
		if (0 != (error = otp_trigger_packet_read(hdr_addr)))
			break;

		hdr.word = OTPC->OTPC_HR;

		while(1) {
			OTPC->OTPC_AR = (payload_offset & OTPC_AR_DADDR_Msk) | OTPC_AR_INCRT;
			OTPC->OTPC_DR = *src++;
			if (hdr.header.size == 0) break;
			hdr.header.size--;
			payload_offset++;
		}

		/* Set the KEY field && PGM */
		OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_UPDATING) | OTPC_CR_PGM;

		while ((OTPC->OTPC_SR & OTPC_SR_PGM) != OTPC_SR_PGM) {
			if (timeout-- == 0) {
				error = OTPC_CANNOT_START_PROGRAMMING;
				break;
			}
		}
		if (error)
			break;

		reg = otp_wait_isr(OTPC_ISR_EOP);
		if ((0 == reg) || (reg & OTPC_ISR_WERR))
			error = OTPC_CANNOT_START_PROGRAMMING;

		break;
	}

#ifdef CONFIG_HAVE_OTP_DEBUG
	trace_debug("OTP update packet at 0x%04x, error code: 0x%02x\r\n",
	    hdr_addr, error);
#endif
	return error;
}

/*!
  \brief Locking a packet
  \param hdr_addr Represents the address of the packet header to be locked
  \return error code: - OTPC_CANNOT_LOCK - The packet cannot be locked
                      - OTPC_NO_ERROR    - The packet was locked susscessfully
 */
uint8_t otp_lock_packet(const uint16_t hdr_addr)
{
	uint8_t error;

	if (0 == (error = otp_trigger_packet_read(hdr_addr))) {
		/* Set the KEY field */
		OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_LOCKING) | OTPC_CR_CKSGEN;
		if (0 == otp_wait_isr(OTPC_ISR_EOL))
			error =  OTPC_CANNOT_LOCK;
	}
#ifdef CONFIG_HAVE_OTP_DEBUG
	trace_debug("OTP lock packet at 0x%04x, error code: 0x%02x\r\n",
	    hdr_addr, error);
#endif
	return error;
}

/*!
  \brief Invalidating a packet
  \param hdr_addr Represents the address of the packet header to be invalidated
  \return error code: - OTPC_CANNOT_INVALIDATE - The packet cannot be invalidated
                      - OTPC_NO_ERROR          - The packet was invalidated successfully
 */
uint8_t otp_invalidate_packet(const uint16_t hdr_addr)
{
	uint8_t error = OTPC_NO_ERROR;

	while (1) {
		/* let OTPC_MR writable */
		if (OTPC->OTPC_MR & OTPC_MR_LOCK) {
			error = OTPC_ERROR_MR_LOCKED;
			break;
		}
		OTPC->OTPC_WPMR = (OTPC->OTPC_WPMR & ~OTPC_WPMR_WPCFEN) | OTPC_WPMR_WPKEY_PASSWD;

		OTPC->OTPC_MR = (OTPC->OTPC_MR & (~OTPC_MR_ADDR_Msk)) | OTPC_MR_ADDR(hdr_addr);
		OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_INVALIDATING) | OTPC_CR_INVLD;

		if (0 == otp_wait_isr(OTPC_ISR_EOI))
			error = OTPC_CANNOT_INVALIDATE;
		break;
	}

#ifdef CONFIG_HAVE_OTP_DEBUG
	trace_debug("OTP invalidate packet at 0x%04x, error code: 0x%02x\r\n",
	    hdr_addr, error);
#endif
	return error;
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
uint8_t otp_emulation_mode(bool enable)
{
	uint8_t error = OTPC_NO_ERROR;

	while (1) {
		/* let OTPC_MR writable */
		if (OTPC->OTPC_MR & OTPC_MR_LOCK) {
			error = OTPC_ERROR_MR_LOCKED;
			break;
		}
		OTPC->OTPC_WPMR = (OTPC->OTPC_WPMR & ~OTPC_WPMR_WPCFEN) | OTPC_WPMR_WPKEY_PASSWD;

		if (enable)
			OTPC->OTPC_MR |= OTPC_MR_EMUL;
		else
			OTPC->OTPC_MR &= ~OTPC_MR_EMUL;
		OTPC->OTPC_CR = OTPC_CR_REFRESH | OTPC_CR_KEY(OTPC_KEY_FOR_EMUL);

		error = wait_for_refreshing();
		break;
	}

	if (error == OTPC_NO_ERROR) {
		if (otp_is_emulation_enabled() != enable)
			error = OTPC_ERROR_EMULATION;
	}

#ifdef CONFIG_HAVE_OTP_DEBUG
	trace_debug("%s OTP emulation mode, error code: 0x%02x\r\n",
	    enable ? "Enable" : "Disable", error);
#endif
	return error;
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
	uint8_t error = OTPC_NO_ERROR;

	while(1) {
		/* let OTPC_MR writable */
		if (OTPC->OTPC_MR & OTPC_MR_LOCK) {
			error = OTPC_ERROR_MR_LOCKED;
			break;
		}
		OTPC->OTPC_WPMR = (OTPC->OTPC_WPMR & ~OTPC_WPMR_WPCFEN) | OTPC_WPMR_WPKEY_PASSWD;

		OTPC->OTPC_MR &= ~(OTPC_MR_NPCKT | OTPC_MR_KBDST_Msk);
		OTPC->OTPC_MR = (OTPC->OTPC_MR & ~OTPC_MR_ADDR_Msk) | OTPC_MR_ADDR(hdr_addr);
		OTPC->OTPC_CR = OTPC_CR_KEY(OTPC_KEY_FOR_WRITING) | OTPC_CR_HIDE;

		while ((OTPC->OTPC_SR & OTPC_SR_HIDE) != OTPC_SR_HIDE) {
			if (timeout-- == 0) {
				error = OTPC_CANNOT_START_HIDING;
				break;
			}
		}
		if (error)
			break;

		if (0 == otp_wait_isr(OTPC_ISR_EOH))
			error = OTPC_CANNOT_PERFORM_HIDING;
		break;
	}
#ifdef CONFIG_HAVE_OTP_DEBUG
	if (error)
		trace_debug("OTP hide packet 0x%08x failed, error code: 0x%02x\r\n",
		    hdr_addr, error);
#endif
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
