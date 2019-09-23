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

#ifndef _OTPC_H_
#define _OTPC_H_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

/* definitions of error code */
#define OTPC_NO_ERROR                        ((uint8_t)0x00)
#define OTPC_ERROR_HW_WRITE_DISABLED         ((uint8_t)0x01)
#define OTPC_ERROR_PACKET_OVERLAPPED         ((uint8_t)0x02)
#define OTPC_ERROR_CANNOT_ACTIVATE_EMULATION ((uint8_t)0x03)
#define OTPC_ERROR_PACKET_NOT_FOUND          ((uint8_t)0x04)
#define OTPC_ERROR_BUFFER_OVERFLOW           ((uint8_t)0x05)
#define OTPC_ERROR_PACKET_INVALIDATED        ((uint8_t)0x06)
#define OTPC_CANNOT_START_PROGRAMMING        ((uint8_t)0x09)
#define OTPC_CANNOT_START_READING            ((uint8_t)0x0A)
#define OTPC_PACKET_TOO_BIG                  ((uint8_t)0x0B)
#define OTPC_FLUSHING_DID_NOT_END            ((uint8_t)0x0C)
#define OTPC_READING_DID_NOT_START           ((uint8_t)0x0D)
#define OTPC_READING_DID_NOT_STOP            ((uint8_t)0x0E)
#define OTPC_CANNOT_LOCK                     ((uint8_t)0x0F)
#define OTPC_CANNOT_INVALIDATE               ((uint8_t)0x10)
#define OTPC_CANNOT_REFRESH                  ((uint8_t)0x11)
#define OTPC_CANNOT_TRANSFER_KEY             ((uint8_t)0x12)
#define OTPC_CANNOT_START_HIDING             ((uint8_t)0x13)
#define OTPC_CANNOT_PERFORM_HIDING           ((uint8_t)0x14)
#define OTPC_ERROR_PACKET_IS_INVALID         ((uint8_t)0x15)
#define OTPC_ERROR_BAD_HEADER                ((uint8_t)0x16)

#define OTPC_PAYLOAD_SIZE(x) (((x) / 4) - 1) /*!< x must be multiple of 4 bytes */

#define OTPC_AES_MODULE    1
#define OTPC_TZAESB_MODULE 2
#define OTPC_TDES_MODULE   3

/* the CHECKSUM field of packet header */
/* - When CHECKSUM is read as 0, the checksum has not been generated. It is possible to
     modify the packet content. */
#define OTPC_CS_NOT_GENERATED    0x0000
/* - When CHECKSUM is read as 0x33CC, the checksum has not been generated but some bits
     are already at 1. Locking the packet may fail. */
#define OTPC_CS_BITS_ALREADY_1   0x33CC
/* – When CHECKSUM is read as 0xA5A5, the checksum has been generated and the last check
     was successful. It is impossible to modify the packet content. */
#define OTPC_CS_CHECK_OK         0xA5A5
/* – When CHECKSUM is read as 0xCC33, the header of the packet is corrupted. */
#define OTPC_CS_CORRUPTED        0xCC33
/* – When CHECKSUM is read as 0xFFFF, the entire packet is no longer valid. It is possible to
     modify the packet content and it is up to the software to program the payload to a different
     value if needed. */
#define OTPC_CS_NOT_VALID        0xFFFF
/* – For all other values of CHECKSUM, the checksum has been generated and the last check
     failed to match the checksum written in the OTP memory. It is impossible to modify the packet
     content */

enum otp_packet_type {
	OTP_PCKT_REGULAR,
	OTP_PCKT_KEY,
	OTP_PCKT_BOOT_CONFIGURATION,
	OTP_PCKT_SECURE_BOOT_CONFIGURATION,
	OTP_PCKT_HARDWARE_CONFIGURATION,
	OTP_PCKT_CUSTOM,

	OTP_PCKT_MAX_TYPE
};

struct otp_new_packet {
	enum otp_packet_type    type;
	uint32_t                size; /* size of the packet payload in bytes */
	bool                    is_secure;
};

struct otp_packet_header {
	enum otp_packet_type    type;
	uint32_t                size; /* size of the packet payload in bytes */
	bool                    is_locked;
	bool                    is_invalid;
	bool                    is_secure;
	uint16_t                checksum;
};

#define OTP_FILTER_TYPE         (1U << 0)
#define OTP_FILTER_SIZE         (1U << 1)
#define OTP_FILTER_LOCKED       (1U << 2)
#define OTP_FILTER_INVALID      (1U << 3)
#define OTP_FILTER_CHECKSUM     (1U << 4)
#define OTP_FILTER_SECURE       (1U << 5)

/*!
 \brief Initialize the OTPC driver
 \param none
 \return 0 if successful, a negative error code otherwise
*/
int otp_init(void);

/*!
 \brief Cleanup the OTPC driver and release all internal allocated resources
 \param none
 \return none
*/
void otp_cleanup(void);

/*!
  \brief
  \param header_data Represents the value of the header to be written
  \param src Represents the payload to be written
  \param pckt_hdr_addr Represents the address of the header. It is an output
  \return error code: - OTPC_NO_ERROR                 - Packet was written successfully
                      - OTPC_ERROR_PACKET_OVERLAPPED  - Packet overlaps another one
                      - OTPC_ERROR_HW_WRITE_DISABLED  - No write access is allowed
                      - OTPC_ERROR_PACKET_INVALIDATED - Packet was invalidated
                      - OTPC_CANNOT_START_PROGRAMMING - Cannot perform writing operation
                      - OTPC_READING_DID_NOT_START    - Cannot perform reading operation
                      - OTPC_READING_DID_NOT_STOP     - A read operation is not ended
                      - OTPC_FLUSHING_DID_NOT_END     - Flushing operation did not end
 */
uint8_t otp_write_packet(const struct otp_new_packet *pckt,
                         const uint32_t *src,
                         uint16_t *pckt_hdr_addr,
                         uint16_t *actually_written);

/*!
  \brief Updating an existing packet
  \param hdr_addr Represents the address of the header
  \param src Represents the input buffer
  \return error code: - OTPC_NO_ERROR                  - Packet was updated successfully
                      - OTPC_CANNOT_START_PROGRAMMING  - The packet cannot be updated
 */
uint8_t otp_update_payload(uint16_t hdr_addr, const uint32_t *src);

/*!
  \brief Locking a packet
  \param hdr_addr Represents the address of the packet header to be locked
  \return error code: - OTPC_CANNOT_LOCK - The packet cannot be locked
                      - OTPC_NO_ERROR    - The packet was locked susscessfully
 */
uint8_t otp_lock_packet(uint16_t hdr_addr);

/*!
  \brief Invalidating a packet
  \param hdr_addr Represents the address of the packet header to be invalidated
  \return error code:  - OTPC_CANNOT_INVALIDATE - The packet cannot be invalidated
                       - OTPC_NO_ERROR          - The packet was invalidated successfully
 */
uint8_t otp_invalidate_packet(uint16_t hdr_addr);

/*!
  \brief Perform a read of a packet
  \param hdr_addr Represents the address of the packet header to be read
  \param dest Represents the output buffer in which the payload will be put
                   In case of a key transfer the value of the pu32_dest must be:
                   - OTPC_AES_MODULE
                   - OTPC_TZAESB_MODULE
                   - OTPC_TDES_MODULE
  \param buffer_size Represents the buffer size where data will be put
   \return error code: - OTPC_ERROR_BUFFER_OVERFLOW - The payload is too big
                       - OTPC_NO_ERROR              - Payload read successfully
                       - OTPC_CANNOT_TRANSFER_KEY   - The key cannot be transfered safely
 */
uint8_t otp_read_packet(uint16_t hdr_addr, uint32_t *dest,
                        uint16_t buffer_size, uint16_t *actually_read);

/*!
  \brief Enable the emulation mode
  \return error code: - OTPC_ERROR_CANNOT_ACTIVATE_EMULATION - The emulation  mode was not activated
                      - OTPC_NO_ERROR                        - The emulation  mode is activated
                      - OTPC_CANNOT_REFRESH                  - The memory cannot be refreshed
 */
uint8_t otp_emulation_mode(bool enable);

/*!
 \brief The routine checks whether or not the OTP emulation mode is enabled
 \param none
 \return true  - OTP enumation mode is enabled
         false - OTP enumation mode is disabled
*/
bool otp_is_emulation_enabled(void);

/*!
 \brief The routine hides a packet
 \param hdr_addr Represents the header address to be hidden
 \return error code: -OTPC_NO_ERROR - Packet was hidden successfully
                     -OTPC_CANNOT_START_HIDING - Hiding operation cannot be started
                     -OTPC_CANNOT_PERFORM_HIDING - The hiding operation cannot be completed
*/
uint8_t otp_hide_packet(uint16_t hdr_addr);

/*!
 \brief The routine checks whether or not the OTP is disabled
 \param none
 \return true  - OTP is disabled
         false - OTP is not disabled
*/
bool otp_is_disabled(void);

/*!
 \brief Look up the OTP for the next packet matching the given packet header value
 \param filters [IN] bitmask of packet header filters
 \param match [IN] packet header value associated to filters
 \result [OUT] if not NULL, the header value of the matching packet
 \result [INOUT] if not NULL, the address to start the scan from and the address
                 of the matching packet, if any
 \return : - OTPC_NO_ERROR               - A matching packet was found
           - OTPC_ERROR_PACKET_NOT_FOUND - No matching packet was found
 */
uint8_t otp_get_next_matching_packet(uint32_t filters,
				     const struct otp_packet_header *match,
				     struct otp_packet_header *result,
				     uint16_t *hdr_addr);

/*!
 \brief Look up the OTP for the latest packet matching the given packet header value
 \param filters [IN] bitmask of packet header filters
 \param match [IN] packet header value associated to filters
 \result [OUT] if not NULL, the header value of the matching packet
 \result [INOUT] if not NULL, the address to start the scan from and the address
                 of the matching packet, if any
 \return : - OTPC_NO_ERROR               - A matching packet was found
           - OTPC_ERROR_PACKET_NOT_FOUND - No matching packet was found
 */
uint8_t otp_get_latest_matching_packet(uint32_t filters,
				       const struct otp_packet_header *match,
				       struct otp_packet_header *result,
				       uint16_t *hdr_addr);

bool otp_can_update_payload(const void *old_payload, const void *new_payload,
			    uint16_t payload_size);

/*!
 \brief The routine gets the header information
 \param none
 \return the header
*/
static inline uint32_t otp_get_header(void)
{
	return OTPC->OTPC_HR;
}

#endif /* _OTPC_H_ */
