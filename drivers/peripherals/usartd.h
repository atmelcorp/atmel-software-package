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

#ifndef USARTD_HEADER__
#define USARTD_HEADER__

#include "peripherals/usart.h"
#include "peripherals/dma.h"
#include "mutex.h"
#include "io.h"

#define USARTD_SUCCESS         (0)
#define USARTD_INVALID_ID      (1)
#define USARTD_INVALID_BITRATE (2)
#define USARTD_ERROR_LOCK      (3)
#define USARTD_ERROR_DUPLEX    (4)
#define USARTD_ERROR_TIMEOUT   (5)

enum _usartd_buf_attr {
	USARTD_BUF_ATTR_WRITE = 0x01,
	USARTD_BUF_ATTR_READ  = 0x02,
};

struct _usart_desc;

typedef void (*usartd_callback_t)(struct _usart_desc* usartd, void* args);

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
		bool has_timeout;

		usartd_callback_t callback;
		void*   cb_args;
	} rx, tx;

#ifdef CONFIG_HAVE_USART_FIFO
	bool use_fifo;
	struct {
		struct {
			uint16_t size;
			uint16_t threshold;
		} rx, tx;
	} fifo;
#endif

	struct {
		struct {
			struct dma_channel *channel;
			struct dma_xfer_cfg cfg;
		} rx;
		struct {
			struct dma_channel *channel;
			struct dma_xfer_cfg cfg;
		} tx;
	} dma;
};

enum _usartd_trans_mode
{
	USARTD_MODE_POLLING,
	USARTD_MODE_ASYNC,
	USARTD_MODE_DMA,
	USARTD_MODE_FIFO,
};

extern void usartd_configure(struct _usart_desc* desc);
extern uint32_t usartd_transfer(struct _usart_desc* desc, struct _buffer* buf,
			  usartd_callback_t cb, void* user_args);
extern void usartd_finish_rx_transfer_callback(struct _usart_desc* desc, void* user_args);
extern void usartd_finish_rx_transfer(struct _usart_desc* desc);
extern uint32_t usartd_rx_is_busy(const struct _usart_desc* desc);
extern void usartd_wait_rx_transfer(const struct _usart_desc* desc);
extern void usartd_finish_tx_transfer_callback(struct _usart_desc* desc, void* user_args);
extern void usartd_finish_tx_transfer(struct _usart_desc* desc);
extern uint32_t usartd_tx_is_busy(const struct _usart_desc* desc);
extern void usartd_wait_tx_transfer(const struct _usart_desc* desc);

#endif /* USARTD_HEADER__ */
