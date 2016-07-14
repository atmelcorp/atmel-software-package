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

#ifndef LIN_H
#define LIN_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

/** LIN error type */
#define US_CSR_LIN_ERROR (US_CSR_LINBE | US_CSR_LINISFE | US_CSR_LINIPE | US_CSR_LINCE)

/** Enhanced checksum used in the LIN 2.x */
#define USART_LIN_ENHANCED_CHECKSUM 0

/** Classic checksum used in the LIN 1.x */
#define USART_LIN_CLASSIC_CHECKSUM 1

/** The response data length is defined by the field DLC of DLM */
#define USART_LIN_DLM_DLC 0

/** The response data length is defined by the bits 5 and 6 of the identifier */
#define USART_LIN_DLM_IDCHR 1


enum enum_lin_cmd {
	PUBLISH,   /* The node sends the response */
	SUBSCRIBE, /* The node receives the response */
	IGNORE     /* The node is not concerned by the response, it doesn't send or receive */
} ;

struct _transfer_packet {
	uint32_t addr; /* Start address of the transfer packet data */
	uint32_t size; /* Transfer packet size (in units of the peripheral data width) */
};

/*! @brief This structure allows to handle a LIN message and, at the end of the
 *        received/transmitted message, allows to call a function associated
 *        to this message, the update or the capture of "signals".
 */
struct _lin_message {
	uint8_t             id;      /* LIN message ID (in case of LIN 1.3 - without length) */
	uint8_t             dlc;     /* Length of the LIN message, it is the number of data bytes of the LIN response */
	enum enum_lin_cmd   lin_cmd; /* Select an action for a specific message */
	uint8_t             status;  /* Status of the last communication:== 0x00: RXOK or TXOK != 0x00: LINERR, content of LIN Error Register 'LINERR' */
	uint8_t*            pdata;   /* Pointer on the data buffer, the data buffer where the bytes of the LIN response are stored */
	void  (*pfnct)(uint8_t*);    /* Pointer on the function which handles the data */
} ;

/*! @brief Error report definitions
 */
#define  LIN_OVERLOAD_INT    ((uint16_t)0x00FF) /* More than ONE interrupt in the same time */
#define  LIN_LAST_ERR_LENGTH 0x04               /* Default length of the 'lin_last_error[]' array */

struct _lin_desc {
	const struct _pin pin_enable; /* pin connected to LIN driver enable */
	Usart* addr;               /* USART address */
	uint32_t mode;             /* USART mode */
	uint32_t baudrate;         /* USART baudrate */
};

/*------------------------------------------------------------------------------*/
/*         Exported functions                                                   */
/*------------------------------------------------------------------------------*/

extern uint8_t lin_init(struct _lin_desc* lin_desc, uint8_t node);

extern uint8_t lin_register_descriptor(uint8_t node, uint8_t frame_id, struct _lin_message *msg);

extern uint8_t lin_send_cmd(uint8_t node, uint8_t id, uint8_t len);

extern void lin_slave_usart_handler(uint8_t node);

extern void lin_master_usart_handler(uint8_t node);

#endif  /* LIN_H */
