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

 \file

	Implementation of USB device functions on a UDP controller.

	See \ref usbd_api_method USBD API Methods.
*/

/** \addtogroup usbd_hal
 *@{*/

/*---------------------------------------------------------------------------
 *      Headers
 *---------------------------------------------------------------------------*/

#include "barriers.h"
#include "chip.h"
#include "trace.h"

#include "mm/cache.h"
#include "irq/irq.h"
#include "peripherals/pmc.h"

#include "usb/device/usbd_hal.h"

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------
 *      Definitions
 *---------------------------------------------------------------------------*/

#undef USB_HAL_DEBUG

#ifdef USB_HAL_DEBUG
#define USB_HAL_TRACE(...) trace_debug_wp(__VA_ARGS__)
#else
#define USB_HAL_TRACE(...)
#endif

/** Max size of the DMA FIFO */
#define DMA_MAX_FIFO_SIZE     (65536)

/** FIFO space size in bytes */
#define EPT_VIRTUAL_SIZE      (65536)

/** Number of endpoints */
#define USB_ENDPOINTS         FIELD_ARRAY_SIZE(Udphs, UDPHS_EPT)

/** Get Number of buffer in Multi-Buffer-List
 *  \param i    input index
 *  \param o    output index
 *  \param size list size
 */
#define MBL_NbBuffer(i, o, size) (((i)>(o))?((i)-(o)):((i)+(size)-(o)))

/** Buffer list is full */
#define MBL_FULL        1

/** Buffer list is null */
#define MBL_NULL        2

/*---------------------------------------------------------------------------
 *      Types
 *---------------------------------------------------------------------------*/

/**
 * \section endpoint_states_sec "UDP Endpoint states"
 *
 *  This page lists the endpoint states.
 *
 *  \subsection States
 *  - UDPHS_ENDPOINT_DISABLED
 *  - UDPHS_ENDPOINT_HALTED
 *  - UDPHS_ENDPOINT_IDLE
 *  - UDPHS_ENDPOINT_SENDING
 *  - UDPHS_ENDPOINT_RECEIVING
 *  - UDPHS_ENDPOINT_SENDINGM
 *  - UDPHS_ENDPOINT_RECEIVINGM
 */
enum _endpoint_state {
	/**  Endpoint is disabled */
	UDPHS_ENDPOINT_DISABLED,

	/**  Endpoint is halted (i.e. STALLs every request) */
	UDPHS_ENDPOINT_HALTED,

	/**  Endpoint is idle (i.e. ready for transmission) */
	UDPHS_ENDPOINT_IDLE,

	/**  Endpoint is sending data */
	UDPHS_ENDPOINT_SENDING,

	/**  Endpoint is receiving data */
	UDPHS_ENDPOINT_RECEIVING,

	/**  Endpoint is sending MBL */
	UDPHS_ENDPOINT_SENDINGM,

	/**  Endpoint is receiving MBL */
	UDPHS_ENDPOINT_RECEIVINGM,
};

/** Describes a single buffer transfer */
struct _single_xfer {
	/**  Number of bytes which have been written into the UDP internal FIFO
	 *   buffers. */
	uint32_t buffered;

	/**  Pointer to a data buffer used for emission/reception. */
	uint8_t *data;

	/**  Number of bytes which have been sent/received. */
	uint32_t transferred;

	/**  Number of bytes which have not been buffered/transferred yet. */
	uint32_t remaining;
};

/** Describes a multi buffer transfer */
struct _multi_xfer {
	/** List state (OK, FULL, NULL) (run time) */
	uint8_t list_state;

	/**  Multi-Buffer List size */
	uint16_t list_size;

	/**  Pointer to multi-buffer list */
	struct _usbd_transfer_buffer *buffers;

	/**  Offset number of buffers to start transfer */
	uint16_t offset;

	/**  Current processing buffer index (run time) */
	uint16_t out;

	/**  Current buffer for input (run time) */
	uint16_t in;
};

/**
 *  Describes the state of an endpoint of the UDP controller.
 */
struct _endpoint {
	/* CSR */
	/**  Current endpoint state. */
	volatile enum _endpoint_state state;

	/**  Current reception bank (0 or 1). */
	volatile uint8_t bank;

	/**  Maximum packet size for the endpoint. */
	volatile uint16_t size;

	/**  Describes an ongoing transfer (if current state is either
	 *   UDPHS_ENDPOINT_SENDING[M] or UDPHS_ENDPOINT_RECEIVING[M]) */
	struct {
		/**  Optional callback to invoke when the transfer completes. */
		usbd_xfer_cb_t callback;

		/**  Optional argument to the callback function. */
		void *callback_arg;

		/**  Transfer type */
		bool use_multi;

		union {
			struct _single_xfer single;
			struct _multi_xfer  multi;
		};
	} transfer;

	/** Special case for send a ZLP */
	uint32_t send_zlp;
};

/**
 * DMA Descriptor.
 */
struct _udphs_dma_desc {
	void     *next;
	void     *addr;
	uint32_t  ctrl;
	uint32_t  reserved; /** reverved (padding) */
};

/*---------------------------------------------------------------------------
 *      Internal constants
 *---------------------------------------------------------------------------*/

/** 7.1.20 Test Mode Support
 * Test codes for the USB HS test mode. */
static const char test_packet_buffer[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // JKJKJKJK * 9
	0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,       // JJKKJJKK * 8
	0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE, 0xEE,       // JJJJKKKK * 8
	0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, // JJJJJJJKKKKKKK * 8
	0x7F, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD,             // JJJJJJJK * 8
	0xFC, 0x7E, 0xBF, 0xDF, 0xEF, 0xF7, 0xFB, 0xFD, 0x7E  // {JKKKKKKK * 10}, JK
};

/*---------------------------------------------------------------------------
 *      Internal variables
 *---------------------------------------------------------------------------*/

/** Holds the internal state for each endpoint of the UDP. */
static struct _endpoint endpoints[USB_ENDPOINTS];

/** Force Full-Speed mode */
static bool force_full_speed = false;

/** DMA link list */
CACHE_ALIGNED static struct _udphs_dma_desc dma_desc[4];

/*---------------------------------------------------------------------------
 *      Internal Functions
 *---------------------------------------------------------------------------*/

/**
 * Enables the clock of the UDP peripheral.
 * \return 1 if peripheral status changed.
 */
static uint8_t udphs_enable_peripheral_clock(void)
{
	if (!pmc_is_peripheral_enabled(ID_UDPHS)) {
		pmc_enable_peripheral(ID_UDPHS);
		return 1;
	}
	return 0;
}

/**
 * Disables the UDP peripheral clock.
 */
static void udphs_disable_peripheral_clock(void)
{
	pmc_disable_peripheral(ID_UDPHS);
}

/**
 * Enables the 480MHz USB clock.
 */
static void udphs_enable_usb_clock(void)
{
	pmc_enable_upll_clock();
}

/**
 *  Disables the 480MHz USB clock.
 */
static void udphs_disable_usb_clock(void)
{
	pmc_disable_upll_clock();
}

/**
 * Enables the BIAS.
 */
static void udphs_enable_bias(void)
{
	pmc_enable_upll_bias();
}

/**
 * Disables the BIAS.
 */
static void udphs_disable_bias(void)
{
	pmc_disable_upll_bias();
}

/**
 * Handles a completed transfer on the given endpoint, invoking the
 * configured callback if any.
 * \param ep Number of the endpoint for which the transfer has completed.
 * \param status   Status code returned by the transfer operation
 */
static void udphs_end_of_transfer(uint8_t ep, uint8_t status)
{
	struct _endpoint *endpoint = &(endpoints[ep]);

	/* Check that endpoint was sending or receiving data */
	switch (endpoint->state) {
	case UDPHS_ENDPOINT_RECEIVING:
	case UDPHS_ENDPOINT_SENDING:
		{
			struct _single_xfer *xfer =
				(struct _single_xfer*)&endpoint->transfer.single;
			uint32_t transferred = xfer->transferred;
			uint32_t remaining = xfer->remaining + xfer->buffered;

			USB_HAL_TRACE("EoT[%s%d:T%d:R%d] ",
					endpoint->state == UDPHS_ENDPOINT_RECEIVING ? "R" : "S",
					(unsigned)ep, (unsigned)transferred,
					(unsigned)remaining);

			if (endpoint->state == UDPHS_ENDPOINT_SENDING)
				endpoint->send_zlp = 0;

			endpoint->state = UDPHS_ENDPOINT_IDLE;
			xfer->data = NULL;
			xfer->transferred = -1;
			xfer->buffered = -1;
			xfer->remaining = -1;

			/* Invoke callback */
			if (endpoint->transfer.callback) {
				endpoint->transfer.callback(
						endpoint->transfer.callback_arg,
						status, transferred, remaining);
			} else {
				USB_HAL_TRACE("NoCB ");
			}
		}
		break;
	case UDPHS_ENDPOINT_RECEIVINGM:
	case UDPHS_ENDPOINT_SENDINGM:
		{
			struct _multi_xfer *xfer =
				(struct _multi_xfer*)&endpoint->transfer.multi;

			USB_HAL_TRACE("EoMT[%s%d] ",
					endpoint->state == UDPHS_ENDPOINT_RECEIVINGM ? "R" : "S",
					(unsigned)ep);

			endpoint->state = UDPHS_ENDPOINT_IDLE;
			xfer->list_state = 0;
			xfer->out = 0;
			xfer->in = 0;

			/* Invoke callback */
			if (endpoint->transfer.callback) {
				endpoint->transfer.callback(
						endpoint->transfer.callback_arg,
						status, 0, 0);
			} else {
				USB_HAL_TRACE("NoCB ");
			}
		}
		break;
	default:
		break;
	}
}

/**
 * Update multi-buffer-transfer descriptors.
 * \param pTransfer Pointer to instance MblTransfer.
 * \param size      Size of bytes that processed.
 * \param forceEnd  Force the buffer END.
 * \return 1 if current buffer ended.
 */
static uint8_t udphs_multi_update(struct _multi_xfer *xfer,
		struct _usbd_transfer_buffer *buffer, uint16_t size, uint8_t force_end)
{
	/* Update transfer descriptor */
	buffer->remaining -= size;

	/* Check if list NULL */
	if (xfer->list_state == MBL_NULL)
		return 1;

	/* Check if current buffer ended */
	if (buffer->remaining == 0 || force_end || size == 0) {
		/* Process to next buffer */
		xfer->out++;
		if (xfer->out == xfer->list_size)
			xfer->out = 0;

		/* Check buffer NULL case */
		if (xfer->out == xfer->in) {
			xfer->list_state = MBL_NULL;
		} else {
			/* Continue transfer, prepare for next operation */
			xfer->list_state = 0;
			buffer = &xfer->buffers[xfer->out];
			buffer->buffered = 0;
			buffer->transferred = 0;
			buffer->remaining = buffer->size;
		}
		return 1;
	}

	return 0;
}

/**
 * Transfers a data payload from the current tranfer buffer to the endpoint
 * FIFO
 * \param ep Number of the endpoint which is sending data.
 */
static void udphs_write_fifo_multi(uint8_t ep)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _multi_xfer *xfer = &endpoint->transfer.multi;
	volatile uint8_t *fifo;
	uint32_t size;
	struct _usbd_transfer_buffer *buffer = &xfer->buffers[xfer->out];

	volatile uint8_t *pBytes;

	/* Get the number of bytes to send */
	size = endpoint->size;
	if (size > buffer->remaining)
		size = buffer->remaining;

	USB_HAL_TRACE("w%d.%d ", xfer->out, (unsigned)size);

	pBytes = &buffer->buffer[buffer->transferred + buffer->buffered];
	buffer->buffered += size;
	udphs_multi_update(xfer, buffer, size, 0);

	/* Write packet in the FIFO buffer */
	fifo = ((uint8_t*)UDPHS_RAM_ADDR) + EPT_VIRTUAL_SIZE * ep;
	for (; size; size--)
		*(fifo++) = *(pBytes++);
	dmb();
}

/**
 * Transfers a data payload from the current tranfer buffer to the endpoint
 * FIFO
 * \param ep Number of the endpoint which is sending data.
 */
static void udphs_write_fifo_single(uint8_t ep)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;
	volatile uint8_t *fifo;
	uint32_t size;

	/* Get the number of bytes to send */
	size = endpoint->size;
	if (size > xfer->remaining)
		size = xfer->remaining;

	/* Update transfer descriptor information */
	xfer->buffered += size;
	xfer->remaining -= size;

	/* Write packet in the FIFO buffer */
	fifo = ((uint8_t*)UDPHS_RAM_ADDR) + EPT_VIRTUAL_SIZE * ep;
	for (; size; size--)
		*(fifo++) = *(xfer->data++);
	dmb();
}

/**
 * Transfers a data payload from an endpoint FIFO to the current transfer buffer
 * \param ep Endpoint number.
 * \param wPacketSize Size of received data packet
 */
static void udphs_read_fifo_single(uint8_t ep, uint32_t size)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;
	volatile uint8_t *fifo;

	/* Check that the requested size is not bigger than the remaining transfer */
	if (size > xfer->remaining) {
		xfer->buffered += size - xfer->remaining;
		size = xfer->remaining;
	}

	/* Update transfer descriptor information */
	xfer->remaining -= size;
	xfer->transferred += size;

	/* Retrieve packet */
	fifo = ((uint8_t*)UDPHS_RAM_ADDR) + EPT_VIRTUAL_SIZE * ep;
	dmb();
	for (; size; size--)
		*(xfer->data++) = *(fifo++);
}

/**
 * Received SETUP packet from endpoint 0 FIFO
 * \param request Generic USB SETUP request sent over Control endpoints
 */
static void udphs_read_request(USBGenericRequest *request)
{
	uint32_t *data = (uint32_t*)request;
	volatile uint32_t *fifo = (volatile uint32_t*)UDPHS_RAM_ADDR;
	dmb();
	*data++ = *fifo++;
	*data = *fifo;
}

/**
 * Endpoint interrupt handler.
 * Handle IN/OUT transfers, received SETUP packets and STALLing
 * \param ep Index of endpoint
 */
static void udphs_endpoint_handler(uint8_t ep)
{
	UdphsEpt *ept = &UDPHS->UDPHS_EPT[ep];
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;
	uint32_t status = ept->UDPHS_EPTSTA;
	uint32_t type = ept->UDPHS_EPTCFG & UDPHS_EPTCFG_EPT_TYPE_Msk;
	uint32_t req_buf[2];
	USBGenericRequest *req = (USBGenericRequest*)req_buf;
	uint16_t pkt_size;

	USB_HAL_TRACE("Ep%d ", ep);

	/* IN packet sent */
	if ((ept->UDPHS_EPTCTL & UDPHS_EPTCTL_TXRDY) &&
			!(status & UDPHS_EPTSTA_TXRDY)) {
		USB_HAL_TRACE("Wr ");

		/* Multi-buffer-list transfer state */
		if (endpoint->state == UDPHS_ENDPOINT_SENDINGM) {
		}
		/* Sending state */
		else if (endpoint->state == UDPHS_ENDPOINT_SENDING) {
			if (xfer->buffered) {
				xfer->transferred += xfer->buffered;
				xfer->buffered = 0;
			}
			if ((xfer->transferred % endpoint->size == 0)
				&& (xfer->remaining == 0)
				&& (xfer->transferred > 0)
				&& (endpoint->send_zlp == 0)) {
				endpoint->send_zlp = 1;	// Force ZLP transmission in total length is  a multiple of endpoint size

			}
			if (xfer->buffered == 0
				&& xfer->transferred == 0
				&& xfer->remaining == 0
				&& endpoint->send_zlp == 0) {
				endpoint->send_zlp = 1;
			}

			/* End of transfer ? */
			if (xfer->remaining || endpoint->send_zlp == 1) {
				if (endpoint->send_zlp == 1) {
					// A null packet will be send, keep trace of it : Change this value only if ZLP will be send!!!
					endpoint->send_zlp = 2;
				}

				/* Transfer remaining */
				USB_HAL_TRACE("%d ", endpoint->size);

				/* Send next packet */
				udphs_write_fifo_single(ep);
				ept->UDPHS_EPTSETSTA = UDPHS_EPTSETSTA_TXRDY;
			} else {
				USB_HAL_TRACE("l%d ", (int)xfer->transferred);

				/* Disable interrupt on not-control EP */
				if (type != UDPHS_EPTCFG_EPT_TYPE_CTRL8) {
					UDPHS->UDPHS_IEN &= ~(UDPHS_IEN_EPT_0 << ep);
				}
				ept->UDPHS_EPTCTLDIS = UDPHS_EPTCTLDIS_TXRDY;
				udphs_end_of_transfer(ep, USBD_STATUS_SUCCESS);
				endpoint->send_zlp = 0;
			}
		} else {
			trace_warning("Err Wr %d\n\r", (unsigned)endpoint->send_zlp);
		}
	}
	/* OUT packet received */
	if (status & UDPHS_EPTSTA_RXRDY_TXKL) {
		USB_HAL_TRACE("Rd ");

		/* NOT in receiving state */
		if (endpoint->state != UDPHS_ENDPOINT_RECEIVING) {
			/* Check if ACK received on a Control EP */
			if (type == UDPHS_EPTCFG_EPT_TYPE_CTRL8 &&
					!(status & UDPHS_EPTSTA_BYTE_COUNT_Msk))
			{
				USB_HAL_TRACE("Ack ");
				ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_RXRDY_TXKL;
				udphs_end_of_transfer(ep, USBD_STATUS_SUCCESS);
			}
			/* data has been STALLed */
			else if (UDPHS_EPTSTA_FRCESTALL & status) {
				USB_HAL_TRACE("Discard ");
				ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_RXRDY_TXKL;
			}
			/* NAK the data */
			else {
				USB_HAL_TRACE("Nak ");
				ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_RXRDY_TXKL;
			}
		}
		/* In read state */
		else {
			pkt_size = (uint16_t)((status & UDPHS_EPTSTA_BYTE_COUNT_Msk)
					>> UDPHS_EPTSTA_BYTE_COUNT_Pos);
			udphs_read_fifo_single(ep, pkt_size);
			ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_RXRDY_TXKL;

			/* Check if transfer is finished */
			if (xfer->remaining == 0 ||
					pkt_size < endpoint->size) {
				ept->UDPHS_EPTCTLDIS = UDPHS_EPTCTLDIS_RXRDY_TXKL;

				/* Disable interrupt if not control EP */
				if (UDPHS_EPTCFG_EPT_TYPE_CTRL8 != type)
					UDPHS->UDPHS_IEN &= ~(UDPHS_IEN_EPT_0 << ep);

				udphs_end_of_transfer(ep, USBD_STATUS_SUCCESS);
			}
		}
	}

	/* STALL sent */
	if (status & UDPHS_EPTSTA_STALL_SNT) {
		/* Acknowledge */
		ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_STALL_SNT;

		/* ISO error */
		if (type == UDPHS_EPTCFG_EPT_TYPE_ISO) {
			USB_HAL_TRACE("IsoE[%d]\n\r", ep);

			udphs_end_of_transfer(ep, USBD_STATUS_ABORTED);
		}
		/* If EP is not halted, clear STALL */
		else {
			USB_HAL_TRACE("Stall[%d]\n\r", ep);

			if (endpoint->state != UDPHS_ENDPOINT_HALTED)
				ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_FRCESTALL;
		}
	}

	/* SETUP packet received */
	if (status & UDPHS_EPTSTA_RX_SETUP) {
		/* If a transfer was pending, complete it
		   Handles the case where during the status phase of a control write
		   transfer, the host receives the device ZLP and ack it, but the ack
		   is not received by the device */
		if (endpoint->state == UDPHS_ENDPOINT_RECEIVING
			|| endpoint->state == UDPHS_ENDPOINT_RECEIVINGM
			|| endpoint->state == UDPHS_ENDPOINT_SENDING
			|| endpoint->state == UDPHS_ENDPOINT_SENDINGM) {
			udphs_end_of_transfer(ep, USBD_STATUS_SUCCESS);
		}

		/* ISO Err Flow */
		if (type == UDPHS_EPTCFG_EPT_TYPE_ISO) {
			USB_HAL_TRACE("IsoFE[%d]\n\r", ep);

			/* Acknowledge setup packet */
			ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_RX_SETUP;
		} else {
			USB_HAL_TRACE("Setup ");

			/* Copy setup */
			udphs_read_request(req);

			/* Acknowledge setup packet */
			ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_RX_SETUP;

			/* Handler */
			usbd_request_handler(ep, req);
		}
	}
}

/**
 * DMA Single transfer
 * \param ep EP number
 * \param xfer Pointer to transfer instance
 * \param cfg DMA Control configuration (excluding length)
 */
static void udphs_dma_single(uint8_t ep, struct _single_xfer *xfer, uint32_t cfg)
{
	uint32_t start_addr = (uint32_t)&xfer->data[xfer->transferred];

	/* Single transfer */
	UDPHS->UDPHS_DMA[ep].UDPHS_DMAADDRESS = start_addr;
	UDPHS->UDPHS_DMA[ep].UDPHS_DMASTATUS = UDPHS->UDPHS_DMA[ep].UDPHS_DMASTATUS;

	/* Interrupt enable */
	UDPHS->UDPHS_IEN |= UDPHS_IEN_DMA_1 << (ep - 1);

	/* DMA Configure */
	UDPHS->UDPHS_DMA[ep].UDPHS_DMACONTROL = 0;
	UDPHS->UDPHS_DMA[ep].UDPHS_DMACONTROL = cfg |
		UDPHS_DMACONTROL_BUFF_LENGTH(xfer->buffered);
}

/**
 * Endpoint DMA interrupt handler.
 * This function handles DMA interrupts.
 * \param ep Index of endpoint
 */
static void udphs_dma_handler(uint8_t ep)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;
	uint32_t dma_status, remaining, transferred;
	uint8_t rc = USBD_STATUS_SUCCESS;

	dma_status = UDPHS->UDPHS_DMA[ep].UDPHS_DMASTATUS;
	USB_HAL_TRACE("iDma%d,%x ", ep, (unsigned)dma_status);

	/* Multi transfer */
	if (endpoint->state == UDPHS_ENDPOINT_SENDINGM ||
		endpoint->state == UDPHS_ENDPOINT_RECEIVINGM) {
		/* Not implemented */
		return;
	}

	/* Disable DMA interrupt to avoid receiving 2 (B_EN and TR_EN) */
	UDPHS->UDPHS_DMA[ep].UDPHS_DMACONTROL &=
		~(UDPHS_DMACONTROL_END_TR_EN | UDPHS_DMACONTROL_END_B_EN);

	if (dma_status & UDPHS_DMASTATUS_END_BF_ST) {
		USB_HAL_TRACE("EoDmaB ");

		/* BUFF_COUNT holds the number of untransmitted bytes.
		   BUFF_COUNT is equal to zero in case of good transfer */
		remaining = (dma_status & UDPHS_DMASTATUS_BUFF_COUNT_Msk)
			>> UDPHS_DMASTATUS_BUFF_COUNT_Pos;

		USB_HAL_TRACE("C%d ", (unsigned)remaining);
		transferred = xfer->buffered - remaining;

		xfer->transferred += transferred;
		xfer->buffered = remaining;
		xfer->remaining -= transferred;

		USB_HAL_TRACE("[B%d:T%d:R%d] ", (int)xfer->buffered,
				   (int)xfer->transferred, (int)xfer->remaining);

		/* There is still data */
		if (xfer->remaining + xfer->buffered > 0) {
			if (xfer->remaining > DMA_MAX_FIFO_SIZE) {
				xfer->buffered = DMA_MAX_FIFO_SIZE;
			} else {
				xfer->buffered = xfer->remaining;
			}

			/* Single transfer again */
			udphs_dma_single(ep, xfer,
					UDPHS_DMACONTROL_END_TR_EN |
					UDPHS_DMACONTROL_END_TR_IT |
					UDPHS_DMACONTROL_END_B_EN |
					UDPHS_DMACONTROL_END_BUFFIT |
					UDPHS_DMACONTROL_CHANN_ENB);
		}
	} else if (dma_status & UDPHS_DMASTATUS_END_TR_ST) {
		USB_HAL_TRACE("EoDmaT ");

		xfer->transferred = xfer->buffered -
			((dma_status & UDPHS_DMASTATUS_BUFF_COUNT_Msk) >> UDPHS_DMASTATUS_BUFF_COUNT_Pos);
		xfer->remaining = 0;

		USB_HAL_TRACE("[B%d:T%d] ", (int)xfer->buffered,
				   (int)xfer->transferred);
	} else {
		trace_error("udphs_dma_handler: ST 0x%x\n\r",
				(unsigned)dma_status);

		rc = USBD_STATUS_ABORTED;
	}

	/* Callback */
	if (xfer->remaining == 0) {
		/* invalidate cache if receiving */
		if (endpoint->state == UDPHS_ENDPOINT_RECEIVING && xfer->transferred)
			cache_invalidate_region(xfer->data, xfer->transferred);
		udphs_end_of_transfer(ep, rc);
	}
}

/**
 * Sends data through a USB endpoint. Sets up the transfer descriptor,
 * writes one or two data payloads (depending on the number of FIFO bank
 * for the endpoint) and then starts the actual transfer. The operation is
 * complete when all the data has been sent.
 *
 * *If the size of the buffer is greater than the size of the endpoint
 *  (or twice the size if the endpoint has two FIFO banks), then the buffer
 *  must be kept allocated until the transfer is finished*. This means that
 *  it is not possible to declare it on the stack (i.e. as a local variable
 *  of a function which returns after starting a transfer).
 *
 * \param endpoint Pointer to Endpoint struct.
 * \param data Pointer to a buffer with the data to send.
 * \param data_len Size of the data buffer.
 * \return USBD_STATUS_SUCCESS if the transfer has been started;
 *         otherwise, the corresponding error status code.
 */
static uint8_t udphs_write(uint8_t ep,
		const void *data, uint32_t data_len)
{
	UdphsEpt *ept = &UDPHS->UDPHS_EPT[ep];
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;

	/* Return if busy */
	while (endpoint->state > UDPHS_ENDPOINT_IDLE);

	/* Sending state */
	endpoint->state = UDPHS_ENDPOINT_SENDING;
	endpoint->send_zlp = 0;

	USB_HAL_TRACE("Wr%d(%d) ", ep, (unsigned)data_len);

	/* Setup transfer descriptor */
	endpoint->transfer.use_multi = false;
	xfer->data = (void*)data;
	xfer->remaining = data_len;
	xfer->buffered = 0;
	xfer->transferred = 0;

	/* 1. DMA supported, 2. Not ZLP */
	if (CHIP_USB_ENDPOINT_HAS_DMA(ep) && xfer->remaining > 0) {
		if (xfer->remaining > DMA_MAX_FIFO_SIZE) {
			xfer->buffered = DMA_MAX_FIFO_SIZE;
		} else {
			xfer->buffered = xfer->remaining;
		}

		/* Single transfer */
		udphs_dma_single(ep, xfer,
				UDPHS_DMACONTROL_END_B_EN |
				UDPHS_DMACONTROL_END_BUFFIT |
				UDPHS_DMACONTROL_CHANN_ENB);
	} else {
		/* Enable IT */
		UDPHS->UDPHS_IEN |= UDPHS_IEN_EPT_0 << ep;

		/* Enable TX */
		ept->UDPHS_EPTCTLENB = UDPHS_EPTCTLENB_TXRDY;
	}

	return USBD_STATUS_SUCCESS;
}

/**
 * Sends data through a USB endpoint. Sets up the transfer descriptor list,
 * writes one or two data payloads (depending on the number of FIFO bank
 * for the endpoint) and then starts the actual transfer. The operation is
 * complete when all the transfer buffer in the list has been sent.
 *
 * *If the size of the buffer is greater than the size of the endpoint
 *  (or twice the size if the endpoint has two FIFO banks), then the buffer
 *  must be kept allocated until the transfer is finished*. This means that
 *  it is not possible to declare it on the stack (i.e. as a local variable
 *  of a function which returns after starting a transfer).
 *
 * \param endpoint Pointer to Endpoint struct.
 * \param data Pointer to a buffer with the data to send.
 * \param data_len Size of the data buffer.
 * \return USBD_STATUS_SUCCESS if the transfer has been started;
 *         otherwise, the corresponding error status code.
 */
static uint8_t udphs_add_buffer(uint8_t ep,
		const void *data, uint32_t data_len)
{
	UdphsEpt *ept = &UDPHS->UDPHS_EPT[ep];
	struct _endpoint *endpoint = &endpoints[ep];
	struct _multi_xfer *xfer = &endpoint->transfer.multi;
	struct _usbd_transfer_buffer *tx;

	/* Check parameter */
	if (data_len >= 0x10000)
		return USBD_STATUS_INVALID_PARAMETER;

	/* Data in process */
	if (endpoint->state > UDPHS_ENDPOINT_IDLE) {
		/* MBL transfer */
		if (!endpoint->transfer.use_multi ||
				xfer->list_state == MBL_FULL) {
			trace_warning("udphs_add_buffer: EP%d not idle\n\r", ep);
			return USBD_STATUS_LOCKED;
		}
	}

	USB_HAL_TRACE("AddW%d(%d) ", ep, (unsigned)data_len);

	/* Add buffer to buffer list and update index */
	tx = &xfer->buffers[xfer->in];
	tx->buffer = (uint8_t*)data;
	tx->size = tx->remaining = data_len;
	tx->transferred = 0;
	tx->buffered = 0;

	/* Update input index */
	if (xfer->in >= (xfer->list_size - 1))
		xfer->in = 0;
	else
		xfer->in++;
	if (xfer->in == xfer->out)
		xfer->list_state = MBL_FULL;
	else
		xfer->list_state = 0;

	/* Start sending when offset achieved */
	if (MBL_NbBuffer(xfer->in, xfer->out, xfer->list_size) >= xfer->offset &&
			endpoint->state == UDPHS_ENDPOINT_IDLE) {
		uint8_t nb_banks = CHIP_USB_ENDPOINT_BANKS(ep);

		/* Change state */
		endpoint->state = UDPHS_ENDPOINT_SENDINGM;

		USB_HAL_TRACE("StartM ");

		/* Fill data into FIFO */
		for (; nb_banks && xfer->buffers[xfer->in].remaining; nb_banks--) {
			udphs_write_fifo_multi(ep);
			ept->UDPHS_EPTSETSTA = UDPHS_EPTSETSTA_TXRDY;
		}

		/* Enable interrupt */
		UDPHS->UDPHS_IEN |= UDPHS_IEN_EPT_0 << ep;
		ept->UDPHS_EPTCTLENB = UDPHS_EPTCTLENB_TXRDY;

	}

	return USBD_STATUS_SUCCESS;
}

/**
 * Reads incoming data on an USB endpoint This methods sets the transfer
 * descriptor and activate the endpoint interrupt. The actual transfer is
 * then carried out by the endpoint interrupt handler. The Read operation
 * finishes either when the buffer is full, or a short packet (inferior to
 * endpoint maximum  size) is received.
 *
 * *The buffer must be kept allocated until the transfer is finished*.
 * \param ep Endpoint number.
 * \param data Pointer to a data buffer.
 * \param data_len Size of the data buffer in bytes.
 * \return USBD_STATUS_SUCCESS if the read operation has been started;
 *         otherwise, the corresponding error code.
 */
static uint8_t udphs_read(uint8_t ep, void *data, uint32_t data_len)
{
	UdphsEpt *ept = &UDPHS->UDPHS_EPT[ep];
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;

	/* Return if busy */
	if (endpoint->state != UDPHS_ENDPOINT_IDLE) {
		trace_warning("udphs_read: EP%d not idle\n\r", ep);
		return USBD_STATUS_LOCKED;
	}

	/* Receiving state */
	endpoint->state = UDPHS_ENDPOINT_RECEIVING;

	USB_HAL_TRACE("Rd%d(%d) ", ep, (unsigned)data_len);

	/* Setup transfer descriptor */
	endpoint->transfer.use_multi = false;
	xfer->data = (void*)data;
	xfer->remaining = data_len;
	xfer->buffered = 0;
	xfer->transferred = 0;

	/* If: 1. DMA supported, 2. Has data */
	if (CHIP_USB_ENDPOINT_HAS_DMA(ep) && xfer->remaining > 0) {
		/* DMA XFR size adjust */
		if (xfer->remaining > DMA_MAX_FIFO_SIZE)
			xfer->buffered = DMA_MAX_FIFO_SIZE;
		else
			xfer->buffered = xfer->remaining;

		/* Single transfer */
		udphs_dma_single(ep, xfer,
				UDPHS_DMACONTROL_END_TR_EN |
				UDPHS_DMACONTROL_END_TR_IT |
				UDPHS_DMACONTROL_END_B_EN |
				UDPHS_DMACONTROL_END_BUFFIT |
				UDPHS_DMACONTROL_CHANN_ENB);
	} else {
		/* Enable IT */
		UDPHS->UDPHS_IEN |= UDPHS_IEN_EPT_0 << ep;

		/* Enable RX */
		ept->UDPHS_EPTCTLENB = UDPHS_EPTCTLENB_RXRDY_TXKL;
	}

	return USBD_STATUS_SUCCESS;
}

/**
 * USBD (UDP) interrupt handler
 * Manages device resume, suspend, end of bus reset.
 * Forwards ep events to the appropriate handler.
 */
static void udphs_irq_handler(uint32_t source, void* user_arg)
{
	uint32_t status;

	assert(source == ID_UDPHS);

	status = UDPHS->UDPHS_INTSTA;
	status &= UDPHS->UDPHS_IEN;

	/* Handle all UDPHS interrupts */
	while (status) {
		/* SOF */
		if (status & UDPHS_INTSTA_INT_SOF) {
			USB_HAL_TRACE("SOF ");

			/* Acknowledge interrupt */
			UDPHS->UDPHS_CLRINT = UDPHS_CLRINT_INT_SOF;
		}
		/* Suspend, treated last */
		else if (status == UDPHS_INTSTA_DET_SUSPD) {
			USB_HAL_TRACE("Susp ");
			/* Enable wakeup */
			UDPHS->UDPHS_IEN |= UDPHS_IEN_WAKE_UP |
				UDPHS_IEN_ENDOFRSM;
			UDPHS->UDPHS_IEN &= ~(uint32_t)UDPHS_IEN_DET_SUSPD;

			/* Acknowledge interrupt */
			UDPHS->UDPHS_CLRINT = UDPHS_CLRINT_DET_SUSPD |
				UDPHS_CLRINT_WAKE_UP;

			usbd_suspend_handler();
		}
		/* Resume */
		else if ((status & UDPHS_INTSTA_WAKE_UP)
			 || (status & UDPHS_INTSTA_ENDOFRSM)) {
			usbd_resume_handler();

			USB_HAL_TRACE("Rsm ");

			/* Acknowledge interrupt */
			UDPHS->UDPHS_CLRINT = UDPHS_CLRINT_WAKE_UP |
				UDPHS_CLRINT_ENDOFRSM |
				UDPHS_CLRINT_DET_SUSPD;

			UDPHS->UDPHS_IEN |= UDPHS_IEN_ENDOFRSM |
				UDPHS_IEN_DET_SUSPD;
			UDPHS->UDPHS_CLRINT = UDPHS_CLRINT_WAKE_UP |
				UDPHS_CLRINT_ENDOFRSM;
			UDPHS->UDPHS_IEN &= ~(uint32_t)UDPHS_IEN_WAKE_UP;
		}
		/* Bus reset */
		else if (status & UDPHS_INTSTA_ENDRESET) {
			USB_HAL_TRACE("EoB ");

			/* Flush and enable the suspend interrupt */
			UDPHS->UDPHS_CLRINT = UDPHS_CLRINT_WAKE_UP |
				UDPHS_CLRINT_DET_SUSPD;
			UDPHS->UDPHS_IEN |= UDPHS_IEN_DET_SUSPD;

			/* Reset handler */
			usbd_reset_handler();

			/* Acknowledge interrupt */
			UDPHS->UDPHS_CLRINT = UDPHS_CLRINT_ENDRESET;
		}
		/* Upstream resume */
		else if (status & UDPHS_INTSTA_UPSTR_RES) {
			USB_HAL_TRACE("ExtRes ");

			/* Acknowledge interrupt */
			UDPHS->UDPHS_CLRINT = UDPHS_CLRINT_UPSTR_RES;
		}
		/* Endpoints */
		else {
			uint32_t ep;
			for (ep = 0; ep < USB_ENDPOINTS; ep++) {
				if (CHIP_USB_ENDPOINT_HAS_DMA(ep) &&
						(status & (UDPHS_INTSTA_DMA_1 << (ep - 1)))) {
					udphs_dma_handler(ep);
				} else if (status & (UDPHS_INTSTA_EPT_0 << ep)) {
					udphs_endpoint_handler(ep);
				}
			}
		}

		/* Update interrupt status */
		status = UDPHS->UDPHS_INTSTA;
		status &= UDPHS->UDPHS_IEN;

		USB_HAL_TRACE("\n\r");
		if (status) {
			USB_HAL_TRACE(" - ");
		}
	}
}

/*---------------------------------------------------------------------------
 *      Exported functions
 *---------------------------------------------------------------------------*/

/**
 * \brief Reset endpoints and disable them.
 * -# Terminate transfer if there is any, with given status;
 * -# Reset the endpoint & disable it.
 * \param endpoint_bits    Bitmap for endpoints to reset.
 * \param status  Status passed to terminate transfer on endpoint.
 * \param keep_config 1 to keep old endpoint configuration.
 * \note Use usbd_hal_configure() to configure and enable endpoint
		 if not keeping old configuration.
 * \sa usbd_hal_configure().
 */
void usbd_hal_reset_endpoints(uint32_t endpoint_bits, uint8_t status, bool keep_cfg)
{
	UdphsEpt *ept;
	struct _endpoint *endpoint;
	uint32_t tmp = endpoint_bits & ((1 << USB_ENDPOINTS) - 1);
	uint8_t ep;
	uint32_t ep_cfg;

	for (ep = 0; ep < USB_ENDPOINTS; ep++) {
		if (tmp & (1 << ep)) {
			ept = &UDPHS->UDPHS_EPT[ep];

			/* Disable ISR */
			UDPHS->UDPHS_IEN &= ~(UDPHS_IEN_EPT_0 << ep);

			/* Reset transfer information */
			endpoint = &(endpoints[ep]);

			/* Reset endpoint state */
			endpoint->bank = 0;

			/* save endpoint config */
			ep_cfg = ept->UDPHS_EPTCFG;

			/* Reset endpoint */
			UDPHS->UDPHS_EPTRST = 1 << ep;

			/* Restore endpoint config */
			if (keep_cfg) {
				ept->UDPHS_EPTCFG = ep_cfg;
			} else {
				endpoint->state = UDPHS_ENDPOINT_DISABLED;
			}

			/* Terminate transfer on this EP */
			udphs_end_of_transfer(ep, status);
		}
	}
}

/**
 * Configures an endpoint according to its endpoint Descriptor.
 * \param descriptor Pointer to an endpoint descriptor.
 * \return The endpoint address.
 */
uint8_t usbd_hal_configure(const USBEndpointDescriptor *descriptor)
{
	UdphsEpt *ept;
	struct _endpoint *endpoint;
	uint8_t ep;
	uint8_t ept_size;
	uint8_t direction;
	uint8_t type;
	uint8_t nb_trans = 1;

	/* NULL or DEVICE descriptor -> Control endpoint 0 */
	if (!descriptor || descriptor->bDescriptorType == USBGenericDescriptor_DEVICE) {
		USBDeviceDescriptor *dev_desc = (USBDeviceDescriptor*)descriptor;

		ep = 0;
		endpoint = &endpoints[0];
		type = USBEndpointDescriptor_CONTROL;
		direction = 0;
		endpoint->size = dev_desc ?
			dev_desc->bMaxPacketSize0 : CHIP_USB_ENDPOINT_MAXPACKETSIZE(0);
	}
	/* Endpoint descriptor */
	else if (descriptor->bDescriptorType == USBGenericDescriptor_ENDPOINT) {
		/* The endpoint number */
		ep = usb_endpoint_descriptor_get_number(descriptor);
		endpoint = &endpoints[ep];

		/* Transfer type: Control, Isochronous, Bulk, Interrupt */
		type = usb_endpoint_descriptor_get_type(descriptor);

		/* Direction, ignored for control endpoints */
		direction = usb_endpoint_descriptor_get_direction(descriptor);
		endpoint->size = usb_endpoint_descriptor_get_max_packet_size(descriptor);

		/* Convert descriptor value to EP configuration */
		if (usbd_hal_is_high_speed()) {
			/* HS Interval, *125us */
			/* MPS: Bit12,11 specify NB_TRANS, as USB 2.0 Spec. */
			nb_trans = (endpoint->size >> 11) & 0x3;
			if (nb_trans == 3)
				nb_trans = 1;
			else
				nb_trans++;

			/* Mask, bit 10..0 is the size */
			endpoint->size &= 0x7ff;
		}
	} else {
		trace_error("usbd_hal_configure: invalid descriptor\r\n");
		return 0xff;
	}

	ept = &UDPHS->UDPHS_EPT[ep];
	endpoint->bank = CHIP_USB_ENDPOINT_BANKS(ep);

	USB_HAL_TRACE("CfgE%d ", ep);

	/* Abort the current transfer is the endpoint was configured and in
	   Write or Read state */
	if ((endpoint->state == UDPHS_ENDPOINT_RECEIVING)
		|| (endpoint->state == UDPHS_ENDPOINT_SENDING)
		|| (endpoint->state == UDPHS_ENDPOINT_RECEIVINGM)
		|| (endpoint->state == UDPHS_ENDPOINT_SENDINGM)) {
		udphs_end_of_transfer(ep, USBD_STATUS_RESET);
	}
	endpoint->state = UDPHS_ENDPOINT_IDLE;

	/* Disable endpoint */
	ept->UDPHS_EPTCTLDIS = UDPHS_EPTCTLDIS_SHRT_PCKT
		| UDPHS_EPTCTLDIS_BUSY_BANK
		| UDPHS_EPTCTLDIS_NAK_OUT
		| UDPHS_EPTCTLDIS_NAK_IN
		| UDPHS_EPTCTLDIS_STALL_SNT
		| UDPHS_EPTCTLDIS_RX_SETUP
		| UDPHS_EPTCTLDIS_TXRDY
		| UDPHS_EPTCTLDIS_RXRDY_TXKL
		| UDPHS_EPTCTLDIS_ERR_OVFLW
		| UDPHS_EPTCTLDIS_MDATA_RX
		| UDPHS_EPTCTLDIS_DATAX_RX
		| UDPHS_EPTCTLDIS_NYET_DIS
		| UDPHS_EPTCTLDIS_INTDIS_DMA
		| UDPHS_EPTCTLDIS_AUTO_VALID
		| UDPHS_EPTCTLDIS_EPT_DISABL;

	/* Reset Endpoint Fifos */
	ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_TOGGLESQ | UDPHS_EPTCLRSTA_FRCESTALL;
	UDPHS->UDPHS_EPTRST = 1 << ep;

	/* Configure endpoint size */
	ept_size = 0;
	if (endpoint->size <= 16)
		ept_size = 1;
	else if (endpoint->size <= 32)
		ept_size = 2;
	else if (endpoint->size <= 64)
		ept_size = 3;
	else if (endpoint->size <= 128)
		ept_size = 4;
	else if (endpoint->size <= 256)
		ept_size = 5;
	else if (endpoint->size <= 512)
		ept_size = 6;
	else if (endpoint->size <= 1024)
		ept_size = 7;

	/* Configure endpoint */
	if (type == USBEndpointDescriptor_CONTROL)
		UDPHS->UDPHS_IEN |= UDPHS_IEN_EPT_0 << ep;

	ept->UDPHS_EPTCFG = ept_size |
		(direction << 3) |
		(type << 4) |
		(endpoint->bank << 6) |
		(nb_trans << 8);

	if ((ept->UDPHS_EPTCFG & UDPHS_EPTCFG_EPT_MAPD) == 0) {
		trace_error("EP%d configuration: ", ep);
		trace_error_wp("ept_size=0x%X ", ept_size);
		trace_error_wp("direction=%d ", direction);
		trace_error_wp("type=0x%X ", type);
		trace_error_wp("bank=%d ", endpoint->bank);
		trace_error_wp("UDPHS_EPTCFG=0x%X\n\r",
				(unsigned)ept->UDPHS_EPTCFG);
		trace_fatal("EP%d configuration failed\n\r", ep);
	}

	if (type == USBEndpointDescriptor_CONTROL) {
		ept->UDPHS_EPTCTLENB = UDPHS_EPTCTLENB_RXRDY_TXKL |
			UDPHS_EPTCTLENB_RX_SETUP |
			UDPHS_EPTCTLENB_EPT_ENABL;
	} else {
		ept->UDPHS_EPTCTLENB = UDPHS_EPTCTLENB_AUTO_VALID |
			UDPHS_EPTCTLENB_EPT_ENABL;
	}

	USB_HAL_TRACE("<%x,%x,%x> ", (unsigned)ept->UDPHS_EPTCFG,
			(unsigned)ept->UDPHS_EPTCTL, (unsigned)ept->UDPHS_EPTSTA);

	return ep;
}

/**
 * Set callback for a USB endpoint for transfer (read/write).
 *
 * \param ep       Endpoint number.
 * \param callback Optional callback function to invoke when the transfer is
 *                  complete.
 * \param callback_arg Optional pointer to data to the callback function.
 * \return USBD_STATUS_SUCCESS or USBD_STATUS_LOCKED if endpoint is busy.
 */
uint8_t usbd_hal_set_transfer_callback(uint8_t ep,
		usbd_xfer_cb_t callback, void *callback_arg)
{
	struct _endpoint *endpoint = &endpoints[ep];

	/* Check that the endpoint is not transferring */
	while (endpoint->state > UDPHS_ENDPOINT_IDLE);

	USB_HAL_TRACE("sXfrCb%d ", (unsigned)ep);

	/* Setup the transfer callback and extension data */
	endpoint->transfer.callback = callback;
	endpoint->transfer.callback_arg = callback_arg;

	return USBD_STATUS_SUCCESS;
}

/**
 * Configure an endpoint to use multi-buffer-list transfer mode.
 * The buffers can be added by _Read/_Write function.
 * \param ep Endpoint number.
 * \param list  Pointer to a multi-buffer list used, NULL to disable MBL.
 * \param list_size  Multi-buffer list size (number of buffers can be queued)
 * \param start_offset When number of buffer achieve this offset transfer start
 */
uint8_t usbd_hal_setup_multi_transfer(uint8_t ep,
		struct _usbd_transfer_buffer *list,
		uint16_t list_size,
		uint16_t start_offset)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _multi_xfer *xfer = &endpoint->transfer.multi;
	int i;

	/* Check that the endpoint is not transferring */
	while (endpoint->state > UDPHS_ENDPOINT_IDLE);

	USB_HAL_TRACE("sMblXfr ");

	/* Enable Multi-Buffer Transfer List */
	if (list) {
		/* Reset list items */
		for (i = 0; i < list_size; i--) {
			list[i].buffer = NULL;
			list[i].size = 0;
			list[i].transferred = 0;
			list[i].buffered = 0;
			list[i].remaining = 0;
		}

		/* Setup transfer */
		endpoint->transfer.use_multi = true;
		xfer->list_state = 0; /* OK */
		xfer->list_size = list_size;
		xfer->buffers = list;
		xfer->out = 0;
		xfer->in = 0;
		xfer->offset = start_offset;
	}
	/* Disable Multi-Buffer Transfer */
	else {
		endpoint->transfer.use_multi = false;
	}

	return USBD_STATUS_SUCCESS;
}

/**
 * Sends data through a USB endpoint. Sets up the transfer descriptor,
 * writes one or two data payloads (depending on the number of FIFO bank
 * for the endpoint) and then starts the actual transfer. The operation is
 * complete when all the data has been sent.
 *
 * *If the size of the buffer is greater than the size of the endpoint
 *  (or twice the size if the endpoint has two FIFO banks), then the buffer
 *  must be kept allocated until the transfer is finished*. This means that
 *  it is not possible to declare it on the stack (i.e. as a local variable
 *  of a function which returns after starting a transfer).
 *
 * \param ep Endpoint number.
 * \param data Pointer to a buffer with the data to send.
 * \param data_len Size of the data buffer.
 * \return USBD_STATUS_SUCCESS if the transfer has been started;
 *         otherwise, the corresponding error status code.
 */
uint8_t usbd_hal_write(uint8_t ep, const void *data, uint32_t data_len)
{
	if (CHIP_USB_ENDPOINT_HAS_DMA(ep) && data_len)
		cache_clean_region(data, data_len);

	if (endpoints[ep].transfer.use_multi)
		return udphs_add_buffer(ep, data, data_len);
	else
		return udphs_write(ep, data, data_len);
}

/**
 * Special write function.
 * Sends data through a USB endpoint. Sets up the transfer descriptor,
 * writes header and one or two data payloads (depending on the number of
 * FIFO bank for the endpoint) and then starts the actual transfer. The
 * operation is complete when all the data has been sent.
 *
 * *If the size of the buffer is greater than the size of the endpoint
 *  (or twice the size if the endpoint has two FIFO banks), then the buffer
 *  must be kept allocated until the transfer is finished*. This means that
 *  it is not possible to declare it on the stack (i.e. as a local variable
 *  of a function which returns after starting a transfer).
 *
 * \param ep Endpoint number.
 * \param header Pointer to header.
 * \param header_len Size of header.
 * \param data Pointer to a buffer with the data to send.
 * \param data_len Size of the data buffer.
 * \return USBD_STATUS_SUCCESS if the transfer has been started;
 *         otherwise, the corresponding error status code.
 */
uint8_t usbd_hal_write_with_header(uint8_t ep,
			   const void *header, uint32_t header_len,
			   const void *data, uint32_t data_len)
{
	UdphsEpt *ept = &UDPHS->UDPHS_EPT[ep];
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;

	if (header_len)
		cache_clean_region(header, header_len);
	if (data_len)
		cache_clean_region(data, data_len);

	/* Return if DMA is not supported */
	if (!CHIP_USB_ENDPOINT_HAS_DMA(ep))
		return USBD_STATUS_HW_NOT_SUPPORTED;

	/* Return if busy */
	while (endpoint->state > UDPHS_ENDPOINT_IDLE);

	/* Sending state */
	endpoint->state = UDPHS_ENDPOINT_SENDING;
	endpoint->send_zlp = 0;

	USB_HAL_TRACE("Wr%d(%d+%d) ", ep, (unsigned)header_len, (unsigned)data_len);

	/* Setup transfer descriptor */
	endpoint->transfer.use_multi = false;
	xfer->data = (void*)data;
	xfer->remaining = header_len + data_len;
	xfer->buffered = 0;
	xfer->transferred = 0;

	/* use DMA except for ZLP */
	if (header_len + data_len > 0) {
		uint8_t nb_trans = (ept->UDPHS_EPTCFG & UDPHS_EPTCFG_NB_TRANS_Msk) >> UDPHS_EPTCFG_NB_TRANS_Pos;

		if (xfer->remaining > DMA_MAX_FIFO_SIZE) {
			/* Transfer the max */
			xfer->buffered = DMA_MAX_FIFO_SIZE;
		} else {
			/* Good size, total size */
			xfer->buffered = xfer->remaining;
		}

		/* LD1: header - load to fifo without interrupt */
		/* Header discarded if exceed the DMA FIFO length */
		//if (header_len > DMA_MAX_FIFO_SIZE) header_len = DMA_MAX_FIFO_SIZE;
		dma_desc[0].next = &dma_desc[1];
		dma_desc[0].addr = (void*)header;
		dma_desc[0].ctrl = UDPHS_DMACONTROL_CHANN_ENB
			| UDPHS_DMACONTROL_BUFF_LENGTH(header_len)
			| UDPHS_DMACONTROL_LDNXT_DSC;
		dma_desc[0].reserved = 0;

		/* High bandwidth ISO EP, max size n*ep_size */
		if (nb_trans > 1) {
			uint8_t *data_ptr = (uint8_t*)data;
			uint32_t max_size = nb_trans * endpoint->size;

			data_len = xfer->buffered - header_len;
			if (data_len > max_size)
				data_len = max_size;

			uint32_t pkt_len;

			/* LD2: data   -  bank 0 */
			pkt_len = endpoint->size - header_len;
			if (pkt_len >= data_len) {
				dma_desc[1].next = NULL;
				dma_desc[1].addr = data_ptr;
				dma_desc[1].ctrl =
					UDPHS_DMACONTROL_CHANN_ENB |
					UDPHS_DMACONTROL_BUFF_LENGTH(data_len) |
					UDPHS_DMACONTROL_END_B_EN |
					UDPHS_DMACONTROL_END_BUFFIT;
				dma_desc[1].reserved = 0;
			} else {
				dma_desc[1].next = &dma_desc[2];
				dma_desc[1].addr = data_ptr;
				dma_desc[1].ctrl =
					UDPHS_DMACONTROL_CHANN_ENB |
					UDPHS_DMACONTROL_BUFF_LENGTH(pkt_len) |
					UDPHS_DMACONTROL_END_B_EN |
					UDPHS_DMACONTROL_LDNXT_DSC;
				dma_desc[1].reserved = 0;
				data_len -= pkt_len;
				data_ptr += pkt_len;

				/* LD3: data  - bank 1 */
				pkt_len = endpoint->size;
				if (pkt_len >= data_len) {
					dma_desc[2].next = NULL;
					dma_desc[2].addr = data_ptr;
					dma_desc[2].ctrl =
						UDPHS_DMACONTROL_CHANN_ENB |
						UDPHS_DMACONTROL_BUFF_LENGTH(data_len) |
						UDPHS_DMACONTROL_END_B_EN |
						UDPHS_DMACONTROL_END_BUFFIT;
					dma_desc[2].reserved = 0;
				} else {
					dma_desc[2].next = &dma_desc[3];
					dma_desc[2].addr = data_ptr;
					dma_desc[2].ctrl =
						UDPHS_DMACONTROL_CHANN_ENB |
						UDPHS_DMACONTROL_BUFF_LENGTH(pkt_len) |
						UDPHS_DMACONTROL_END_B_EN |
						UDPHS_DMACONTROL_LDNXT_DSC;
					dma_desc[2].reserved = 0;
					data_len -= pkt_len;
					data_ptr += pkt_len;

					/* LD4: data  - bank 2 */
					dma_desc[3].next = NULL;
					dma_desc[3].addr = data_ptr;
					dma_desc[3].ctrl =
						UDPHS_DMACONTROL_CHANN_ENB |
						UDPHS_DMACONTROL_BUFF_LENGTH(data_len) |
						UDPHS_DMACONTROL_END_B_EN |
						UDPHS_DMACONTROL_END_BUFFIT;
					dma_desc[3].reserved = 0;
				}
			}
		} else {
			/* Normal, fill all data */
			/* LD2: data   -  load to fifo with interrupt */
			data_len = xfer->buffered - header_len;
			dma_desc[1].next = NULL;
			dma_desc[1].addr = (void*)data;
			dma_desc[1].ctrl = UDPHS_DMACONTROL_CHANN_ENB
				| UDPHS_DMACONTROL_BUFF_LENGTH(data_len)
				| UDPHS_DMACONTROL_END_B_EN
				| UDPHS_DMACONTROL_END_BUFFIT;
			dma_desc[1].reserved = 0;
		}

		/* Flush DMA descriptors */
		cache_clean_region(dma_desc, sizeof(dma_desc));

		/* Interrupt enable */
		UDPHS->UDPHS_IEN |= UDPHS_IEN_DMA_1 << (ep - 1);

		/* Start transfer with LLI */
		UDPHS->UDPHS_DMA[ep].UDPHS_DMANXTDSC = (uint32_t)dma_desc;
		UDPHS->UDPHS_DMA[ep].UDPHS_DMACONTROL = 0;
		UDPHS->UDPHS_DMA[ep].UDPHS_DMACONTROL = UDPHS_DMACONTROL_LDNXT_DSC;
	} else {
		/* Enable IT */
		UDPHS->UDPHS_IEN |= UDPHS_IEN_EPT_0 << ep;

		/* Enable TX */
		ept->UDPHS_EPTCTLENB = UDPHS_EPTCTLENB_TXRDY;
	}

	return USBD_STATUS_SUCCESS;
}

/**
 * Get the size of data is available for read or write
 * \param ep Endpoint number
 * \return size of data available
 */
uint16_t usbd_hal_get_data_size(uint8_t ep)
{
	UdphsEpt *ept = &UDPHS->UDPHS_EPT[ep];
	uint32_t status;
	uint16_t size;

	status = ept->UDPHS_EPTSTA;
	size = (uint16_t)((status & UDPHS_EPTSTA_BYTE_COUNT_Msk)
				>> UDPHS_EPTSTA_BYTE_COUNT_Pos);
	return size;
}

/**
 * Reads incoming data on an USB endpoint This methods sets the transfer
 * descriptor and activate the endpoint interrupt. The actual transfer is
 * then carried out by the endpoint interrupt handler. The Read operation
 * finishes either when the buffer is full, or a short packet (inferior to
 * endpoint maximum  size) is received.
 *
 * *The buffer must be kept allocated until the transfer is finished*.
 * \param ep Endpoint number.
 * \param data Pointer to a data buffer.
 * \param data_len Size of the data buffer in bytes.
 * \return USBD_STATUS_SUCCESS if the read operation has been started;
 *         otherwise, the corresponding error code.
 */
uint8_t usbd_hal_read(uint8_t ep, void *data, uint32_t data_len)
{
	if (endpoints[ep].transfer.use_multi) {
		trace_warning("usbd_hal_read does not support 'multi' transfers\r\n");
		return USBD_STATUS_SW_NOT_SUPPORTED;
	} else {
		return udphs_read(ep, data, data_len);
	}
}

/**
 *  \brief Enable Pull-up, connect.
 *
 *  -# Enable HW access if needed
 *  -# Enable Pull-Up
 *  -# Disable HW access if needed
 */
void usbd_hal_connect(void)
{
	uint8_t dis = udphs_enable_peripheral_clock();
	UDPHS->UDPHS_CTRL |= UDPHS_CTRL_PULLD_DIS;
	UDPHS->UDPHS_CTRL &= ~(uint32_t) UDPHS_CTRL_DETACH;
	if (dis)
		udphs_disable_peripheral_clock();
}

/**
 *  \brief Disable Pull-up, disconnect.
 *
 *  -# Enable HW access if needed
 *  -# Disable PULL-Up
 *  -# Disable HW access if needed
 */
void usbd_hal_disconnect(void)
{
	uint8_t dis = udphs_enable_peripheral_clock();
	UDPHS->UDPHS_CTRL |= UDPHS_CTRL_DETACH;
	UDPHS->UDPHS_CTRL &= ~(uint32_t) UDPHS_CTRL_PULLD_DIS;
	if (dis)
		udphs_disable_peripheral_clock();
}

/**
 * Starts a remote wake-up procedure.
 */
void usbd_hal_remote_wakeup(void)
{
	udphs_enable_peripheral_clock();
	udphs_enable_usb_clock();

	USB_HAL_TRACE("RWUp ");

	/* Activates a remote wakeup (edge on ESR), then clear ESR */
	UDPHS->UDPHS_CTRL |= UDPHS_CTRL_REWAKEUP;
	while (UDPHS->UDPHS_CTRL & UDPHS_CTRL_REWAKEUP) {
		USB_HAL_TRACE("w");
	}

	udphs_enable_bias();
}

/**
 * Sets the device address to the given value.
 * \param address New device address.
 */
void usbd_hal_set_address(uint8_t address)
{
	if (address) {
		UDPHS->UDPHS_CTRL &= ~(uint32_t)UDPHS_CTRL_DEV_ADDR_Msk;
		UDPHS->UDPHS_CTRL |= address | UDPHS_CTRL_FADDR_EN;
	} else {
		UDPHS->UDPHS_CTRL &= ~(uint32_t)UDPHS_CTRL_FADDR_EN;
	}
}

/**
 * Sets the current device configuration.
 * \param cfgnum - Configuration number to set.
 */
void usbd_hal_set_configuration(uint8_t cfgnum)
{
	/* Nothing to do now */
	(void)cfgnum;
}

/**
 * Initializes the USB HW Access driver.
 */
void usbd_hal_init(void)
{
	UdphsEpt *ept;
	UdphsDma *dma;
	int i;

	/* Setup IRQ handler */
	irq_add_handler(ID_UDPHS, udphs_irq_handler, NULL);
	irq_enable(ID_UDPHS);

	/* Must before USB & TXVC access! */
	udphs_enable_peripheral_clock();

	/* Reset & disable endpoints */
	usbd_hal_reset_endpoints(0xFFFFFFFF, USBD_STATUS_RESET, 0);

	/* Configure the pull-up on D+ and disconnect it */
	UDPHS->UDPHS_CTRL |= UDPHS_CTRL_DETACH;
	UDPHS->UDPHS_CTRL |= UDPHS_CTRL_PULLD_DIS;

	/* Reset IP */
	UDPHS->UDPHS_CTRL &= ~(uint32_t)UDPHS_CTRL_EN_UDPHS;
	UDPHS->UDPHS_CTRL |= UDPHS_CTRL_EN_UDPHS;

	/* (XCHQ[2010.1.21], IP recomendation, setup clock after reset IP) */
	udphs_enable_usb_clock();

	/* Initialize DMA */
	for (i = 1; i < 7; i++) {
		ept = &UDPHS->UDPHS_EPT[i];
		dma = &UDPHS->UDPHS_DMA[i];

		/* DMA stop */
		dma->UDPHS_DMACONTROL = 0;

		/* Disable endpoint */
		ept->UDPHS_EPTCTLDIS = UDPHS_EPTCTLDIS_SHRT_PCKT |
			UDPHS_EPTCTLDIS_BUSY_BANK |
			UDPHS_EPTCTLDIS_NAK_OUT |
			UDPHS_EPTCTLDIS_NAK_IN |
			UDPHS_EPTCTLDIS_STALL_SNT |
			UDPHS_EPTCTLDIS_RX_SETUP |
			UDPHS_EPTCTLDIS_TXRDY |
			UDPHS_EPTCTLDIS_TX_COMPLT |
			UDPHS_EPTCTLDIS_RXRDY_TXKL |
			UDPHS_EPTCTLDIS_ERR_OVFLW |
			UDPHS_EPTCTLDIS_MDATA_RX |
			UDPHS_EPTCTLDIS_DATAX_RX |
			UDPHS_EPTCTLDIS_NYET_DIS |
			UDPHS_EPTCTLDIS_INTDIS_DMA |
			UDPHS_EPTCTLDIS_AUTO_VALID |
			UDPHS_EPTCTLDIS_EPT_DISABL;

		/* Clear status endpoint */
		ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_TOGGLESQ |
			UDPHS_EPTCLRSTA_FRCESTALL |
			UDPHS_EPTCLRSTA_RXRDY_TXKL |
			UDPHS_EPTCLRSTA_TX_COMPLT |
			UDPHS_EPTCLRSTA_RX_SETUP |
			UDPHS_EPTCLRSTA_STALL_SNT |
			UDPHS_EPTCLRSTA_NAK_IN |
			UDPHS_EPTCLRSTA_NAK_OUT;

		/* Reset endpoint config */
		ept->UDPHS_EPTCTLENB = 0;

		/* Reset DMA channel (Buffer count and Control field) */
		dma->UDPHS_DMACONTROL = UDPHS_DMACONTROL_LDNXT_DSC;

		/* Reset DMA channel */
		dma->UDPHS_DMACONTROL = 0;

		/* Clear DMA channel status (read to clear) */
		dma->UDPHS_DMASTATUS = dma->UDPHS_DMASTATUS;
	}

	/* Force Full-Speed */
	UDPHS->UDPHS_TST = force_full_speed ?
		UDPHS_TST_SPEED_CFG_FULL_SPEED : 0;

	/* Clear interrupts */
	UDPHS->UDPHS_IEN = 0;
	UDPHS->UDPHS_CLRINT = UDPHS_CLRINT_UPSTR_RES |
		UDPHS_CLRINT_ENDOFRSM |
		UDPHS_CLRINT_WAKE_UP |
		UDPHS_CLRINT_ENDRESET |
		UDPHS_CLRINT_INT_SOF |
		UDPHS_CLRINT_MICRO_SOF |
		UDPHS_CLRINT_DET_SUSPD;

	/* Enable interrupts */
	UDPHS->UDPHS_IEN = UDPHS_IEN_ENDOFRSM |
		UDPHS_IEN_WAKE_UP |
		UDPHS_IEN_DET_SUSPD;

	/* Disable USB clocks */
	udphs_disable_usb_clock();
}

/**
 * Causes the given endpoint to acknowledge the next packet it receives
 * with a STALL handshake except setup request.
 * \param ep Endpoint number.
 * \return USBD_STATUS_SUCCESS or USBD_STATUS_LOCKED.
 */
uint8_t usbd_hal_stall(uint8_t ep)
{
	UdphsEpt *ept = &UDPHS->UDPHS_EPT[ep];
	struct _endpoint *endpoint = &endpoints[ep];

	/* Check that endpoint is in Idle state */
	if (endpoint->state != UDPHS_ENDPOINT_IDLE) {
		trace_warning("usbd_hal_stall: EP%d not idle\n\r", ep);
		return USBD_STATUS_LOCKED;
	}

	/* STALL endpoint */
	ept->UDPHS_EPTSETSTA = UDPHS_EPTSETSTA_FRCESTALL;

	USB_HAL_TRACE("Stall%d ", ep);
	return USBD_STATUS_SUCCESS;
}

/**
 * Sets the HALT state on the endpoint.
 * In HALT state, the endpoint should keep stalling any packet.
 * \param ep Endpoint number.
 * \return endpoint halt status.
 */
bool usbd_hal_halt(uint8_t ep)
{
	UdphsEpt *ept = &UDPHS->UDPHS_EPT[ep];

	/* Check that endpoint is enabled and not already in Halt state */
	if ((endpoints[ep].state != UDPHS_ENDPOINT_DISABLED)
		&& (endpoints[ep].state != UDPHS_ENDPOINT_HALTED)) {
		USB_HAL_TRACE("Halt%d ", ep);

		/* Abort the current transfer if necessary */
		udphs_end_of_transfer(ep, USBD_STATUS_ABORTED);

		/* Put endpoint into Halt state */
		endpoints[ep].state = UDPHS_ENDPOINT_HALTED;
		ept->UDPHS_EPTSETSTA = UDPHS_EPTSETSTA_FRCESTALL;

		if (CHIP_USB_ENDPOINT_HAS_DMA(ep)) {
			/* Enable the endpoint DMA interrupt */
			UDPHS->UDPHS_IEN |= UDPHS_IEN_DMA_1 << (ep - 1);
		} else {
			/* Enable the endpoint interrupt */
			UDPHS->UDPHS_IEN |= UDPHS_IEN_EPT_0 << ep;
		}
	}

	return endpoints[ep].state == UDPHS_ENDPOINT_HALTED;
}

/**
 * Clear the HALT state on the endpoint.
 * Clearing the Halt feature results in the endpoint no longer returning
 * a STALL. 
 * For endpoints using data toggle, regardless of whether an
 * endpoint has the Halt feature set, a ClearFeature(ENDPOINT_HALT) request 
 * always results in the data toggle being reinitialized to DATA0.
 *
 * \param ep Endpoint number.
 */
void usbd_hal_unhalt(uint8_t ep)
{
	UdphsEpt *ept = &UDPHS->UDPHS_EPT[ep];

	/* Check if the endpoint is halted */
	if (endpoints[ep].state == UDPHS_ENDPOINT_HALTED) {
		USB_HAL_TRACE("Unhalt%d ", ep);

		/* Return endpoint to Idle state */
		endpoints[ep].state = UDPHS_ENDPOINT_IDLE;

		/* Clear FORCESTALL flag */
		ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_FRCESTALL;
	}
	
	if (CHIP_USB_ENDPOINT_BANKS(ep) > 1) {
		/* Clear data toggle sequence */
		ept->UDPHS_EPTCLRSTA = UDPHS_EPTCLRSTA_TOGGLESQ;
	}
}

/**
 * Get the HALT state on the endpoint.
 * In HALT state, the endpoint should keep stalling any packet.
 * \param ep Endpoint number.
 * \return endpoint halt status.
 */
bool usbd_hal_is_halted(uint8_t ep)
{
	return endpoints[ep].state == UDPHS_ENDPOINT_HALTED;
}

void usbd_hal_force_full_speed(void)
{
	force_full_speed = true;
}

/**
 * Indicates if the device is running in high or full-speed.
 */
bool usbd_hal_is_high_speed(void)
{
	return (UDPHS->UDPHS_INTSTA & UDPHS_INTSTA_SPEED) != 0;
}

/**
 * Suspend USB Device HW Interface
 * -# Disable transceiver
 * -# Disable USB Clock
 * -# Disable USB Peripheral
 */
void usbd_hal_suspend(void)
{
	udphs_disable_bias();
	udphs_disable_usb_clock();
	udphs_disable_peripheral_clock();
}

/**
 * Activate USB Device HW Interface
 * -# Enable USB Peripheral
 * -# Enable USB Clock
 * -# Enable transceiver
 */
void usbd_hal_activate(void)
{
	udphs_enable_peripheral_clock();
	udphs_enable_usb_clock();
	udphs_enable_bias();
}

/**
 * Certification test for High Speed device.
 * \param index Test to be done
 */
void usbd_hal_test(uint8_t index)
{
	uint8_t *fifo;
	int i;

	/* remove suspend for TEST */
	UDPHS->UDPHS_IEN &= ~UDPHS_IEN_DET_SUSPD;

	/* force High Speed (remove suspend) */
	UDPHS->UDPHS_TST |= UDPHS_TST_SPEED_CFG_HIGH_SPEED;

	switch (index) {
	case USBFeatureRequest_TESTPACKET:
		USB_HAL_TRACE("TEST_PACKET ");

		UDPHS->UDPHS_DMA[1].UDPHS_DMACONTROL = 0;
		UDPHS->UDPHS_DMA[2].UDPHS_DMACONTROL = 0;

		/* Configure endpoint 2, 64 bytes, direction IN, type BULK, 1 bank */
		UDPHS->UDPHS_EPT[2].UDPHS_EPTCFG = UDPHS_EPTCFG_EPT_SIZE_64 |
			UDPHS_EPTCFG_EPT_DIR |
			UDPHS_EPTCFG_EPT_TYPE_BULK |
			UDPHS_EPTCFG_BK_NUMBER_1;
		while ((UDPHS->UDPHS_EPT[2].UDPHS_EPTCFG &
					UDPHS_EPTCFG_EPT_MAPD) !=
				UDPHS_EPTCFG_EPT_MAPD);
		UDPHS->UDPHS_EPT[2].UDPHS_EPTCTLENB = UDPHS_EPTCTLENB_EPT_ENABL;

		/* Write FIFO */
		fifo = ((uint8_t*)UDPHS_RAM_ADDR) + EPT_VIRTUAL_SIZE * 2;
		for (i = 0; i < sizeof(test_packet_buffer); i++)
			fifo[i] = test_packet_buffer[i];

		/* Tst PACKET */
		UDPHS->UDPHS_TST |= UDPHS_TST_TST_PKT;

		/* Send packet */
		UDPHS->UDPHS_EPT[2].UDPHS_EPTSETSTA = UDPHS_EPTSETSTA_TXRDY;
		break;

	case USBFeatureRequest_TESTJ:
		USB_HAL_TRACE("TEST_J ");
		UDPHS->UDPHS_TST = UDPHS_TST_TST_J;
		break;

	case USBFeatureRequest_TESTK:
		USB_HAL_TRACE("TEST_K ");
		UDPHS->UDPHS_TST = UDPHS_TST_TST_K;
		break;

	case USBFeatureRequest_TESTSE0NAK:
		USB_HAL_TRACE("TEST_SEO_NAK ");
		UDPHS->UDPHS_IEN = 0;
		break;

	case USBFeatureRequest_TESTSENDZLP:
		UDPHS->UDPHS_EPT[0].UDPHS_EPTSETSTA = UDPHS_EPTSETSTA_TXRDY;
		USB_HAL_TRACE("SEND_ZLP ");
		break;
	}
	USB_HAL_TRACE("\r\n");
}

/**@}*/
