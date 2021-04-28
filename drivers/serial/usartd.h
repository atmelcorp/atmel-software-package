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

#ifndef USARTD_H_
#define USARTD_H_

#ifdef CONFIG_HAVE_USART

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "callback.h"
#include "dma/dma.h"
#include "io.h"
#include "mutex.h"
#include "serial/usart.h"

/*----------------------------------------------------------------------------
 *        Constants
 *----------------------------------------------------------------------------*/

#define USARTD_SUCCESS         (0)
#define USARTD_INVALID_ID      (1)
#define USARTD_INVALID_BITRATE (2)
#define USARTD_ERROR_LOCK      (3)
#define USARTD_ERROR_DUPLEX    (4)
#define USARTD_ERROR_TIMEOUT   (5)
#define USARTD_ERROR           (6)

/*----------------------------------------------------------------------------
 *        Type definitions
 *----------------------------------------------------------------------------*/

enum _usartd_buf_attr {
	USARTD_BUF_ATTR_WRITE = 0x01,
	USARTD_BUF_ATTR_READ  = 0x02,
	USARTD_BUF_ATTR_PINGPONG = 0x04, /* the buffer is splited into 2 and used as the ping/pong buffer */
};

struct _usart_desc
{
	Usart*  addr;
	uint32_t mode;
	uint32_t baudrate;
	uint8_t transfer_mode;
	uint32_t timeout; // ms

	/* implicit internal padding is mandatory here */
	struct {
		mutex_t mutex;

		struct _buffer buffer;
		uint16_t transferred;

		struct _callback callback;
	} rx, tx;

#ifdef CONFIG_HAVE_USART_FIFO
	bool use_fifo;
	struct {
		struct {
			uint16_t size;
			uint16_t threshold;
			uint16_t threshold2;
		} rx, tx;
	} fifo;
#endif

	struct {
		struct {
			struct _dma_channel *channel;
			struct _dma_cfg cfg_dma;
			struct _dma_transfer_cfg cfg;
		} rx;
		struct {
			struct _dma_channel *channel;
			struct _dma_cfg cfg_dma;
		} tx;
	} dma;

#ifdef US_CSR_CMP
	/* variables needed for comparison function */
	struct {
		uint32_t enable;
		uint16_t val1;   /* First Comparison Value for Received Character*/
		uint16_t val2;   /* Second Comparison Value for Received Character */
		uint8_t mode;    /* Comparison Mode */
		uint8_t parity;  /* Compare Parity */
	} cmp;
#endif /* US_CSR_CMP */

	/* extra variables needed for receive with DMA ping/pong buffer */
	struct {
		uint32_t total;        /* total bytes received */
		uint32_t processed;    /* bytes processed in the ping/pong buffer */
		uint32_t buf_switch;
		struct _dma_transfer_cfg cfg[2];
	} dma_pingpong;
};

enum _usartd_trans_mode
{
	USARTD_MODE_POLLING,
	USARTD_MODE_ASYNC,
	USARTD_MODE_DMA,
	USARTD_MODE_FIFO,
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

extern void usartd_configure(uint8_t iface, struct _usart_desc* desc);
extern uint32_t usartd_transfer(uint8_t iface, struct _buffer* buf, struct _callback* cb);
extern uint32_t usartd_dma_pingpong_read(uint8_t iface, uint8_t* buf, uint32_t size, uint32_t* actural_read);
extern void usartd_finish_rx_transfer(uint8_t iface);
extern uint32_t usartd_rx_is_busy(const uint8_t iface);
extern void usartd_wait_rx_transfer(const uint8_t iface);
extern void usartd_finish_tx_transfer(uint8_t iface);
extern uint32_t usartd_tx_is_busy(const uint8_t iface);
extern void usartd_wait_tx_transfer(const uint8_t iface);

#endif /* CONFIG_HAVE_USART */

#endif /* USARTD_H_ */
