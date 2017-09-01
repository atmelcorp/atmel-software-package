/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2017, Atmel Corporation
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

	Implementation of USB device functions on a USB Device controller.

	See \ref usbd_api_method USBD API Methods.
*/

/** \addtogroup usbd_hal
 *@{*/

/*---------------------------------------------------------------------------
 *      Headers
 *---------------------------------------------------------------------------*/

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "barriers.h"
#include "chip.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "peripherals/pmc.h"
#include "trace.h"
#include "usb/device/usbd_hal.h"

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
#define DMA_MAX_FIFO_SIZE     (32768)

/** FIFO space size in bytes */
#define EPT_VIRTUAL_SIZE      (32768)

/** Number of endpoints */
#define USB_ENDPOINTS FIELD_ARRAY_SIZE(Usbhs, USBHS_DEVEPTCFG)

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
 * \section endpoint_states_sec "USB Device Endpoint states"
 *
 *  This page lists the endpoint states.
 *
 *  \subsection States
 *  - USB_HAL_ENDPOINT_DISABLED
 *  - USB_HAL_ENDPOINT_HALTED
 *  - USB_HAL_ENDPOINT_IDLE
 *  - USB_HAL_ENDPOINT_SENDING
 *  - USB_HAL_ENDPOINT_RECEIVING
 *  - USB_HAL_ENDPOINT_SENDINGM
 *  - USB_HAL_ENDPOINT_RECEIVINGM
 */
enum _endpoint_state {
	/**  Endpoint is disabled */
	USB_HAL_ENDPOINT_DISABLED,

	/**  Endpoint is halted (i.e. STALLs every request) */
	USB_HAL_ENDPOINT_HALTED,

	/**  Endpoint is idle (i.e. ready for transmission) */
	USB_HAL_ENDPOINT_IDLE,

	/**  Endpoint is sending data */
	USB_HAL_ENDPOINT_SENDING,

	/**  Endpoint is receiving data */
	USB_HAL_ENDPOINT_RECEIVING,

	/**  Endpoint is sending MBL */
	USB_HAL_ENDPOINT_SENDINGM,

	/**  Endpoint is receiving MBL */
	USB_HAL_ENDPOINT_RECEIVINGM,
};

/** Describes a single buffer transfer */
struct _single_xfer {
	/**  Number of bytes which have been written into the USB Device internal FIFO
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
 *  Describes the state of an endpoint of the USB Device controller.
 */
struct _endpoint {
	/* CSR */
	/**  Current endpoint state. */
	volatile enum _endpoint_state state;

	/**  Maximum packet size for the endpoint. */
	volatile uint16_t size;

	/**  Describes an ongoing transfer (if current state is either
	 *   USB_HAL_ENDPOINT_SENDING[M] or USB_HAL_ENDPOINT_RECEIVING[M]) */
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
struct _usb_dma_desc {
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
static const uint8_t test_packet_buffer[] = {
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

/** Holds the internal state for each endpoint */
static struct _endpoint endpoints[USB_ENDPOINTS];

/** Force Full-Speed mode */
static bool force_full_speed = false;

/** DMA link list */
CACHE_ALIGNED static struct _usb_dma_desc dma_desc[4];

/*---------------------------------------------------------------------------
 *      Internal Functions
 *---------------------------------------------------------------------------*/

/**
 * Enables the clock of the USB Device peripheral.
 * \return true if peripheral status changed.
 */
static bool _usbd_hal_enable_peripheral_clock(void)
{
	if (!pmc_is_peripheral_enabled(ID_USBHS)) {
		pmc_enable_peripheral(ID_USBHS);
		return true;
	}
	return false;
}

/**
 * Enables the 480MHz USB clock.
 */
static void _usbd_hal_enable_usb_clock(void)
{
	pmc_enable_upll_clock();
}

/**
 * Reset endpoint for a given endpoint
 */
static void _usbd_hal_endpoint_reset(uint8_t ep)
{
	USBHS->USBHS_DEVEPT |= USBHS_DEVEPT_EPRST0 << ep;
	USBHS->USBHS_DEVEPT &= ~(USBHS_DEVEPT_EPRST0 << ep);
}

/**
 * Get endpoint config
 */
static uint32_t _usbd_hal_endpoint_get_config(uint8_t ep)
{
	return USBHS->USBHS_DEVEPTCFG[ep];
}

/**
 * Configure given endpoint
 */
static void _usbd_hal_endpoint_set_config(uint8_t ep, uint32_t config)
{
	USBHS->USBHS_DEVEPTCFG[ep] = config;
}

/**
 * Enable or disable Auto switch of banks
 */
static void _usbd_auto_switch_bank_enable(uint8_t ep, bool enable)
{
	if(enable)
		USBHS->USBHS_DEVEPTCFG[ep] |= USBHS_DEVEPTCFG_AUTOSW;
	else
		USBHS->USBHS_DEVEPTCFG[ep] &= ~((uint32_t)USBHS_DEVEPTCFG_AUTOSW);
}

/**
 * Check if given endpoint's bank is free
 */
static bool _usbd_is_bank_free(uint8_t ep)
{
	return(!(USBHS->USBHS_DEVEPTISR[ep] & USBHS_DEVEPTISR_NBUSYBK_Msk));
}

/**
 * Configure given endpoint
 */
static int _usbd_hal_endpoint_configure(uint8_t ep, uint8_t direction,
		uint8_t type, uint16_t size, uint8_t banks, uint8_t nb_trans)
{
	uint32_t cfg = 0;

	if (size <= 8)
		cfg |= USBHS_DEVEPTCFG_EPSIZE_8_BYTE;
	else if (size <= 16)
		cfg |= USBHS_DEVEPTCFG_EPSIZE_16_BYTE;
	else if (size <= 32)
		cfg |= USBHS_DEVEPTCFG_EPSIZE_32_BYTE;
	else if (size <= 64)
		cfg |= USBHS_DEVEPTCFG_EPSIZE_64_BYTE;
	else if (size <= 128)
		cfg |= USBHS_DEVEPTCFG_EPSIZE_128_BYTE;
	else if (size <= 256)
		cfg |= USBHS_DEVEPTCFG_EPSIZE_256_BYTE;
	else if (size <= 512)
		cfg |= USBHS_DEVEPTCFG_EPSIZE_512_BYTE;
	else if (size <= 1024)
		cfg |= USBHS_DEVEPTCFG_EPSIZE_1024_BYTE;
	else
		return -EINVAL;

	if (direction == USBEndpointDescriptor_IN)
		cfg |= USBHS_DEVEPTCFG_EPDIR;

	switch (type) {
	case USBEndpointDescriptor_CONTROL:
		cfg |= USBHS_DEVEPTCFG_EPTYPE_CTRL;
		break;
	case USBEndpointDescriptor_ISOCHRONOUS:
		cfg |= USBHS_DEVEPTCFG_EPTYPE_ISO;
		break;
	case USBEndpointDescriptor_BULK:
		cfg |= USBHS_DEVEPTCFG_EPTYPE_BLK;
		break;
	case USBEndpointDescriptor_INTERRUPT:
		cfg |= USBHS_DEVEPTCFG_EPTYPE_INTRPT;
		break;
	default:
		return -EINVAL;
	}

	cfg |= USBHS_DEVEPTCFG_EPBK(banks);

	cfg |= USBHS_DEVEPTCFG_NBTRANS(nb_trans);

	_usbd_hal_endpoint_set_config(ep, cfg);
	return 0;
}

/**
 * Get endpoint type
 */
static uint8_t _usbd_hal_endpoint_get_type(uint8_t ep)
{
	switch (_usbd_hal_endpoint_get_config(ep) & USBHS_DEVEPTCFG_EPTYPE_Msk) {
		case USBHS_DEVEPTCFG_EPTYPE_CTRL:
			return USBEndpointDescriptor_CONTROL;
		case USBHS_DEVEPTCFG_EPTYPE_ISO:
			return USBEndpointDescriptor_ISOCHRONOUS;
		case USBHS_DEVEPTCFG_EPTYPE_BLK:
			return USBEndpointDescriptor_BULK;
		case USBHS_DEVEPTCFG_EPTYPE_INTRPT:
			return USBEndpointDescriptor_INTERRUPT;
	}
	return 0xff;
}

/**
 * Gets interrupt status for a given EP
 */
static uint32_t _usbd_hal_endpoint_get_status(uint8_t ep)
{
	return USBHS->USBHS_DEVEPTISR[ep];
}

/**
 * Clears register/acknowledge for a given endpoint
 */
static void _usbd_hal_endpoint_clear_status(uint8_t ep, uint32_t bits)
{
	USBHS->USBHS_DEVEPTICR[ep] = bits;
}

/**
 * Sets/Raise register for a given endpoint
 */
static void _usbd_hal_endpoint_set_status(uint8_t ep, uint32_t bits)
{
	USBHS->USBHS_DEVEPTIFR[ep] = bits;
}

/**
 * Read endpoint's byte count of the FIFO
 */
static uint16_t _usbd_hal_endpoint_get_received_data_size(uint8_t ep)
{
	return (uint16_t)((_usbd_hal_endpoint_get_status(ep) & USBHS_DEVEPTISR_BYCT_Msk) >> USBHS_DEVEPTISR_BYCT_Pos);
}

/**
 * Read endpoint's control status for a given endpoint
 */
static uint32_t _usbd_hal_endpoint_control_get_status(uint8_t ep)
{
	return USBHS->USBHS_DEVEPTIMR[ep];
}

/**
 * Enables an interrupt type for a given endpoint
 */
static void _usbd_hal_endpoint_control_enable(uint8_t ep, uint32_t flags)
{
	USBHS->USBHS_DEVEPTIER[ep] = flags;
}

/**
 * Disables an interrupt type for a given endpoint
 */
static void _usbd_hal_endpoint_control_disable(uint8_t ep, uint32_t flags)
{
	USBHS->USBHS_DEVEPTIDR[ep] = flags;
}

/**
 * Enables endpoint interrupt for a given endpoint
  */
static void _usbd_hal_endpoint_interrupt_enable(uint8_t ep)
{
	USBHS->USBHS_DEVIER = USBHS_DEVIER_PEP_0 << ep;
}

/**
 * Disable endpoint interrupt for a given endpoint
  */
static void _usbd_hal_endpoint_interrupt_disable(uint8_t ep)
{
	USBHS->USBHS_DEVIDR = USBHS_DEVIDR_PEP_0 << ep;
}

/**
 * Enables endpoint DMA interrupt for a given endpoint
 */
static void _usbd_hal_endpoint_dma_interrupt_enable(uint8_t ep)
{
	assert(ep > 0);
	USBHS->USBHS_DEVIER = USBHS_DEVIER_DMA_1 << (ep - 1);
}

/**
 * \brief Read status for a DMA Endpoint
 * \param pUsbhs   Pointer to an USBHS instance.
 * \param DmaNum  DMA Endpoint
 */
static uint32_t _usbd_hal_get_dma_interrupt_status(uint8_t num)
{
	return (USBHS->USBHS_DEVISR & (USBHS_DEVISR_DMA_1 << num) );
}

/**
 * Copy data from a memory buffer to the endpoint FIFO (Write to FIFO).
 */
static void _usbd_hal_write_fifo_buffer(uint8_t ep, const uint8_t* data, uint32_t size)
{
	volatile uint8_t *fifo = ((volatile uint8_t*)USBHS_RAM_ADDR) + EPT_VIRTUAL_SIZE * ep;
	for (; size; size--)
		*(fifo++) = *(data++);
	dmb();
}

/**
 * Copy data from endpoint FIFO into a memory buffer (Read from FIFO).
 */
static void _usbd_hal_read_fifo_buffer(uint8_t ep, uint8_t* data, uint32_t size)
{
	volatile uint8_t *fifo = ((volatile uint8_t*)USBHS_RAM_ADDR) + EPT_VIRTUAL_SIZE * ep;
	dmb();
	for (; size; size--)
		*(data++) = *(fifo++);
}

/**
 * Handles a completed transfer on the given endpoint, invoking the
 * configured callback if any.
 * \param ep Number of the endpoint for which the transfer has completed.
 * \param status   Status code returned by the transfer operation
 */
static void _usbd_hal_end_of_transfer(uint8_t ep, uint8_t status)
{
	struct _endpoint *endpoint = &(endpoints[ep]);

	/* Check that endpoint was sending or receiving data */
	switch (endpoint->state) {
	case USB_HAL_ENDPOINT_RECEIVING:
	case USB_HAL_ENDPOINT_SENDING:
		{
			struct _single_xfer *xfer =
				(struct _single_xfer*)&endpoint->transfer.single;
			uint32_t transferred = xfer->transferred;
			uint32_t remaining = xfer->remaining + xfer->buffered;

			USB_HAL_TRACE("EoT[%s%d:T%d:R%d] ",
					endpoint->state == USB_HAL_ENDPOINT_RECEIVING ? "R" : "S",
					(unsigned)ep, (unsigned)transferred,
					(unsigned)remaining);

			if (endpoint->state == USB_HAL_ENDPOINT_SENDING)
				endpoint->send_zlp = 0;

			endpoint->state = USB_HAL_ENDPOINT_IDLE;
			xfer->data = NULL;
			xfer->transferred = -1;
			xfer->buffered = -1;
			xfer->remaining = -1;

			/* Invoke callback */
			if (endpoint->transfer.callback) {
				endpoint->transfer.callback(
						endpoint->transfer.callback_arg,
						status, transferred, remaining);
			}
		}
		break;
	case USB_HAL_ENDPOINT_RECEIVINGM:
	case USB_HAL_ENDPOINT_SENDINGM:
		{
			struct _multi_xfer *xfer =
				(struct _multi_xfer*)&endpoint->transfer.multi;

			USB_HAL_TRACE("EoMT[%s%d] ",
					endpoint->state == USB_HAL_ENDPOINT_RECEIVINGM ? "R" : "S",
					(unsigned)ep);

			endpoint->state = USB_HAL_ENDPOINT_IDLE;
			xfer->list_state = 0;
			xfer->out = 0;
			xfer->in = 0;

			/* Invoke callback */
			if (endpoint->transfer.callback) {
				endpoint->transfer.callback(
						endpoint->transfer.callback_arg,
						status, 0, 0);
			}
		}
		break;
	default:
		break;
	}
}

/**
 * Update multi-buffer-transfer descriptors.
 * \param xfer Pointer to struct _multi_xfer instance.
 * \param buffer Buffer to be processed
 * \param size Size of buffer to be processed.
 * \param force_end  Force buffer end.
 */
static void _usbd_hal_multi_update(struct _multi_xfer *xfer,
		struct _usbd_transfer_buffer *buffer, uint16_t size, uint8_t force_end)
{
	/* Update transfer descriptor */
	buffer->remaining -= size;

	/* Check if list NULL */
	if (xfer->list_state == MBL_NULL)
		return;

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
	}
}

/**
 * Transfers a data payload from the current tranfer buffer to the endpoint
 * FIFO
 * \param ep Number of the endpoint which is sending data.
 */
static void _usbd_hal_write_fifo_multi(uint8_t ep)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _multi_xfer *xfer = &endpoint->transfer.multi;
	struct _usbd_transfer_buffer *buffer = &xfer->buffers[xfer->out];
	uint8_t* data;
	uint32_t size;

	/* Get the number of bytes to send */
	size = endpoint->size;
	if (size > buffer->remaining)
		size = buffer->remaining;

	USB_HAL_TRACE("w%d.%d ", xfer->out, (unsigned)size);

	data = &buffer->buffer[buffer->transferred + buffer->buffered];
	buffer->buffered += size;
	_usbd_hal_multi_update(xfer, buffer, size, 0);

	/* Write packet in the FIFO buffer */
	_usbd_hal_write_fifo_buffer(ep, data, size);
}

/**
 * Transfers a data payload from the current tranfer buffer to the endpoint
 * FIFO
 * \param ep Number of the endpoint which is sending data.
 */
static void _usbd_hal_write_fifo_single(uint8_t ep)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;
	uint8_t* data = xfer->data;
	uint32_t size;

	/* Get the number of bytes to send */
	size = endpoint->size;
	if (size > xfer->remaining)
		size = xfer->remaining;

	/* Update transfer descriptor information */
	xfer->data += size;
	xfer->buffered += size;
	xfer->remaining -= size;

	/* Write packet in the FIFO buffer */
	_usbd_hal_write_fifo_buffer(ep, data, size);
}

/**
 * Transfers a data payload from an endpoint FIFO to the current transfer buffer
 * \param ep Endpoint number.
 * \param wPacketSize Size of received data packet
 */
static void _usbd_hal_read_fifo_single(uint8_t ep, uint32_t size)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;
	uint8_t* data = xfer->data;

	/* Check that the requested size is not bigger than the remaining transfer */
	if (size > xfer->remaining) {
		xfer->buffered += size - xfer->remaining;
		size = xfer->remaining;
	}

	/* Update transfer descriptor information */
	xfer->data += size;
	xfer->remaining -= size;
	xfer->transferred += size;

	/* Retrieve packet */
	_usbd_hal_read_fifo_buffer(ep, data, size);
}

/**
 * Received SETUP packet from endpoint 0 FIFO
 * \param request Generic USB SETUP request sent over Control endpoints
 */
static void _usbd_hal_read_request(USBGenericRequest *request)
{
	_usbd_hal_read_fifo_buffer(0, (uint8_t*)request, sizeof(USBGenericRequest));
}

/**
 * Endpoint interrupt handler.
 * Handle IN/OUT transfers, received SETUP packets and STALLing
 * \param ep Index of endpoint
 */
static void _usbd_hal_endpoint_handler(uint8_t ep)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;
	uint32_t status = _usbd_hal_endpoint_get_status(ep);
	uint32_t type = _usbd_hal_endpoint_get_type(ep);
	uint32_t req_buf[2];
	USBGenericRequest *req = (USBGenericRequest*)req_buf;
	uint16_t pkt_size;

	USB_HAL_TRACE("Ep%d ", ep);

	/* IN packet sent */
	if ((_usbd_hal_endpoint_control_get_status(ep) & USBHS_DEVEPTIMR_TXINE) &&
			(status & USBHS_DEVEPTISR_TXINI)) {
		USB_HAL_TRACE("Wr ");

		/* Multi-buffer-list transfer state */
		if (endpoint->state == USB_HAL_ENDPOINT_SENDINGM) {
		}
		/* Sending state */
		else if (endpoint->state == USB_HAL_ENDPOINT_SENDING) {
			if (xfer->buffered) {
				xfer->transferred += xfer->buffered;
				xfer->buffered = 0;
			}

			if ((xfer->transferred % endpoint->size == 0)
				&& (xfer->remaining == 0)
				&& (xfer->transferred > 0)
				&& (endpoint->send_zlp == 0)) {
				/* Force ZLP transmission in total length is  a multiple of endpoint size */
				endpoint->send_zlp = 1;
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
					/* A null packet will be send, keep trace of it:
					Change this value only if ZLP will be send!!! */
					endpoint->send_zlp = 2;
				}

				/* Transfer remaining */
				USB_HAL_TRACE("%d ", endpoint->size);

				/* Send next packet */
				_usbd_hal_write_fifo_single(ep);

				/* Acknowledges the interrupt by clearing TXINIC.*/
				_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_TXINIC);

				if (type != USBEndpointDescriptor_CONTROL)
					/* Send the bank and switch to the next bank (if any) by clearing FIFOCON. */
					_usbd_hal_endpoint_control_disable(ep, USBHS_DEVEPTIDR_FIFOCONC);
			} else {
				USB_HAL_TRACE("l%d ", (int)xfer->transferred);

				/* Disable interrupt on non-control EP */
				if (type != USBEndpointDescriptor_CONTROL)
					_usbd_hal_endpoint_interrupt_disable(ep);
				_usbd_hal_endpoint_control_disable(ep, USBHS_DEVEPTIDR_TXINEC);
				_usbd_hal_end_of_transfer(ep, USBD_STATUS_SUCCESS);
				endpoint->send_zlp = 0;
			}
		} else {
			trace_warning("Err Wr %d\n\r", (unsigned)endpoint->send_zlp);
		}
	}

	/* OUT packet received */
	if (status & USBHS_DEVEPTISR_RXOUTI) {
		USB_HAL_TRACE("Rd ");

		/* NOT in receiving state */
		if (endpoint->state != USB_HAL_ENDPOINT_RECEIVING) {
			/* Check if ACK received on a Control EP */
			if (type == USBEndpointDescriptor_CONTROL &&
					_usbd_hal_endpoint_get_received_data_size(ep) == 0) {
				USB_HAL_TRACE("Ack ");
				_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_RXOUTIC);
				_usbd_hal_end_of_transfer(ep, USBD_STATUS_SUCCESS);
			}
			/* data has been STALLed */
			else if (status & USBHS_DEVEPTISR_STALLEDI) {
				USB_HAL_TRACE("Discard ");
				_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_RXOUTIC);
			}
			/* NAK the data */
			else {
				USB_HAL_TRACE("Nak ");
				_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_RXOUTIC);
			}
		}
		/* In read state */
		else {
			/* Acknowledge Received OUT Data Interrupt if not control EP */
			if (type != USBEndpointDescriptor_CONTROL)
				_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_RXOUTIC);

			pkt_size = _usbd_hal_endpoint_get_received_data_size(ep);
			_usbd_hal_read_fifo_single(ep, pkt_size);

			/*Acknowledge Received OUT Data Interrupt if it is a control EP*/
			if (type == USBEndpointDescriptor_CONTROL)
				_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_RXOUTIC);

			/*Free the current bank and to switch to the next bank (If any).*/
			if (type != USBEndpointDescriptor_CONTROL)
				_usbd_hal_endpoint_control_disable(ep, USBHS_DEVEPTIDR_FIFOCONC);

			/* Check if transfer is finished */
			if (xfer->remaining == 0 ||
					pkt_size < endpoint->size) {
				_usbd_hal_endpoint_control_disable(ep, USBHS_DEVEPTIDR_RXOUTEC);

				/* Disable interrupt if not control EP */
				if (type != USBEndpointDescriptor_CONTROL)
					_usbd_hal_endpoint_interrupt_disable(ep);

				_usbd_hal_end_of_transfer(ep, USBD_STATUS_SUCCESS);
				_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_NAKINIC);
				_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_TXINIC);
			}
		}
	}

	/* STALL sent */
	if (status & USBHS_DEVEPTISR_STALLEDI) {
		/* Acknowledge */
		_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_STALLEDIC);

		/* ISO error */
		if (type == USBEndpointDescriptor_ISOCHRONOUS) {
			USB_HAL_TRACE("IsoE[%d]\n\r", ep);

			_usbd_hal_end_of_transfer(ep, USBD_STATUS_ABORTED);
		}
		/* If EP is not halted, clear STALL */
		else {
			USB_HAL_TRACE("Stall[%d]\n\r", ep);

			if (endpoint->state != USB_HAL_ENDPOINT_HALTED)
				_usbd_hal_endpoint_control_disable(ep, USBHS_DEVEPTIDR_STALLRQC);
		}
	}

	/* SETUP packet received */
	if (status & USBHS_DEVEPTISR_RXSTPI) {
		/* If a transfer was pending, complete it
		   Handles the case where during the status phase of a control write
		   transfer, the host receives the device ZLP and ack it, but the ack
		   is not received by the device */
		if (endpoint->state == USB_HAL_ENDPOINT_RECEIVING
			|| endpoint->state == USB_HAL_ENDPOINT_RECEIVINGM
			|| endpoint->state == USB_HAL_ENDPOINT_SENDING
			|| endpoint->state == USB_HAL_ENDPOINT_SENDINGM) {
			_usbd_hal_end_of_transfer(ep, USBD_STATUS_SUCCESS);
		}

		/* ISO Err Flow */
		if (type == USBEndpointDescriptor_ISOCHRONOUS) {
			USB_HAL_TRACE("IsoFE[%d]\n\r", ep);

			/* Acknowledge setup packet */
			_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_RXSTPIC);
		} else {
			USB_HAL_TRACE("Setup ");

			/* Copy setup */
			_usbd_hal_read_request(req);

			/* Acknowledge setup packet */
			_usbd_hal_endpoint_clear_status(ep, USBHS_DEVEPTICR_RXSTPIC);

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
static void _usbd_hal_dma_single(uint8_t ep, struct _single_xfer *xfer, uint32_t cfg)
{
	uint32_t start_addr = (uint32_t)&xfer->data[xfer->transferred];

	/* Single transfer */
	USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMAADDRESS = start_addr;
	USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMASTATUS = USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMASTATUS;

	/* DMA Configure */
	USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMACONTROL = 0;
	USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMACONTROL = cfg | USBHS_DEVDMACONTROL_BUFF_LENGTH(xfer->buffered);;

	/* Interrupt enable */
	_usbd_hal_endpoint_dma_interrupt_enable(ep);
}

/**
 * Endpoint DMA interrupt handler.
 * This function handles DMA interrupts.
 * \param ep Index of endpoint
 */
static void _usbd_hal_dma_handler(uint8_t ep)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;
	uint32_t dma_status, remaining, transferred;
	uint8_t rc = USBD_STATUS_SUCCESS;

	dma_status = USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMASTATUS;
	USB_HAL_TRACE("iDma%d,%x ", ep, (unsigned)dma_status);

	/* Multi transfer */
	if (endpoint->state == USB_HAL_ENDPOINT_SENDINGM ||
		endpoint->state == USB_HAL_ENDPOINT_RECEIVINGM) {
		/* Not implemented */
		return;
	}

	/* Disable DMA interrupt to avoid receiving 2 (B_EN and TR_EN) */
	USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMACONTROL &=
		~(USBHS_DEVDMACONTROL_END_TR_EN | USBHS_DEVDMACONTROL_END_B_EN);

	if (dma_status & USBHS_DEVDMASTATUS_END_BF_ST) {
		USB_HAL_TRACE("EoDmaB ");

		/* BUFF_COUNT holds the number of untransmitted bytes.
		   BUFF_COUNT is equal to zero in case of good transfer */
		remaining = (dma_status & USBHS_DEVDMASTATUS_BUFF_COUNT_Msk)
			>> USBHS_DEVDMASTATUS_BUFF_COUNT_Pos;

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
			_usbd_hal_dma_single(ep, xfer,
					USBHS_DEVDMACONTROL_END_TR_EN |
					USBHS_DEVDMACONTROL_END_TR_IT |
					USBHS_DEVDMACONTROL_END_B_EN |
					USBHS_DEVDMACONTROL_END_BUFFIT |
					USBHS_DEVDMACONTROL_CHANN_ENB);
		}
	} else if (dma_status & USBHS_DEVDMASTATUS_END_TR_ST) {
		USB_HAL_TRACE("EoDmaT ");

		xfer->transferred = xfer->buffered -
			((dma_status & USBHS_DEVDMASTATUS_BUFF_COUNT_Msk) >> USBHS_DEVDMASTATUS_BUFF_COUNT_Pos);
		xfer->remaining = 0;

		USB_HAL_TRACE("[B%d:T%d] ", (int)xfer->buffered,
				   (int)xfer->transferred);
	} else {
		trace_error("_usbd_hal_dma_handler: ST 0x%x\n\r",
				(unsigned)dma_status);

		rc = USBD_STATUS_ABORTED;
	}

	/* Callback */
	if (xfer->remaining == 0) {
		/* invalidate cache if receiving */
		if (endpoint->state == USB_HAL_ENDPOINT_RECEIVING && xfer->transferred)
			cache_invalidate_region(xfer->data, xfer->transferred);
		_usbd_hal_end_of_transfer(ep, rc);
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
static uint8_t _usbd_hal_write(uint8_t ep,
		const void *data, uint32_t data_len)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;

	/* Return if busy */
	if (endpoint->state != USB_HAL_ENDPOINT_IDLE)
		return USBD_STATUS_LOCKED;

	/* Sending state */
	endpoint->state = USB_HAL_ENDPOINT_SENDING;
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
		/* Enable automatic bank switch for DMA */
		_usbd_auto_switch_bank_enable(ep, true);

		if (xfer->remaining > DMA_MAX_FIFO_SIZE) {
			xfer->buffered = DMA_MAX_FIFO_SIZE;
		} else {
			xfer->buffered = xfer->remaining;
		}

		/* Single transfer */
		_usbd_hal_dma_single(ep, xfer,
				USBHS_DEVDMACONTROL_END_B_EN |
				USBHS_DEVDMACONTROL_END_BUFFIT |
				USBHS_DEVDMACONTROL_CHANN_ENB);
	} else {
		/* Wait for the bank to be free before disabling the automatic bank switch in order
		 * to transfer data in FIFO mode correctly when the last is done with DMA.
		 * Add the timeout machine to avoid stucking here.
		 */
		if (ep) {
			volatile uint32_t timeout = 0;
			while (!_usbd_is_bank_free(ep) && timeout++ < 0xFFFFFF);
			if (timeout >= 0xFFFFFF)
			{
				while (!_usbd_is_bank_free(ep)) {
					USBHS->USBHS_DEVEPTIER[ep] = USBHS_DEVEPTIER_KILLBKS;
					while (USBHS->USBHS_DEVEPTIMR[ep] & USBHS_DEVEPTIMR_KILLBK);
				}
				_usbd_hal_end_of_transfer(ep, USBD_STATUS_CANCELED);
				return USBD_STATUS_CANCELED;
			}
		}

		/* Disable automatic bank switch*/
		_usbd_auto_switch_bank_enable(ep, false);

		/* Enable IT */
		_usbd_hal_endpoint_interrupt_enable(ep);

		/* Enable TX */
		_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_TXINES);
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
static uint8_t _usbd_hal_add_buffer(uint8_t ep,
		const void *data, uint32_t data_len)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _multi_xfer *xfer = &endpoint->transfer.multi;
	struct _usbd_transfer_buffer *tx;

	/* Check parameter */
	if (data_len >= 0x10000)
		return USBD_STATUS_INVALID_PARAMETER;

	/* Data in process */
	if (endpoint->state > USB_HAL_ENDPOINT_IDLE) {
		/* MBL transfer */
		if (!endpoint->transfer.use_multi ||
				xfer->list_state == MBL_FULL) {
			trace_warning("_usbd_hal_add_buffer: EP%d not idle\n\r", ep);
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
			endpoint->state == USB_HAL_ENDPOINT_IDLE) {
		uint8_t nb_banks = CHIP_USB_ENDPOINT_BANKS(ep);

		/* Change state */
		endpoint->state = USB_HAL_ENDPOINT_SENDINGM;

		USB_HAL_TRACE("StartM ");

		/* Fill data into FIFO */
		for (; nb_banks && xfer->buffers[xfer->in].remaining; nb_banks--) {
			_usbd_hal_write_fifo_multi(ep);
			_usbd_hal_endpoint_set_status(ep, USBHS_DEVEPTIFR_TXINIS);
		}

		/* Enable interrupt */
		_usbd_hal_endpoint_interrupt_enable(ep);
		_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_TXINES);
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
static uint8_t _usbd_hal_read(uint8_t ep, void *data, uint32_t data_len)
{
	struct _endpoint *endpoint = &endpoints[ep];
	struct _single_xfer *xfer = &endpoint->transfer.single;

	/* Return if busy */
	if (endpoint->state != USB_HAL_ENDPOINT_IDLE) {
		trace_warning("_usbd_hal_read: EP%d not idle\n\r", ep);
		return USBD_STATUS_LOCKED;
	}

	/* Receiving state */
	endpoint->state = USB_HAL_ENDPOINT_RECEIVING;

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
		_usbd_hal_dma_single(ep, xfer,
				USBHS_DEVDMACONTROL_END_TR_EN |
				USBHS_DEVDMACONTROL_END_TR_IT |
				USBHS_DEVDMACONTROL_END_B_EN |
				USBHS_DEVDMACONTROL_END_BUFFIT |
				USBHS_DEVDMACONTROL_CHANN_ENB);
	} else {
		/* Enable IT */
		_usbd_hal_endpoint_interrupt_enable(ep);

		/* Enable RX */
		_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_RXOUTES);
	}

	return USBD_STATUS_SUCCESS;
}

/**
 * USBD (USBHS) interrupt handler
 * Manages device resume, suspend, end of bus reset.
 * Forwards endpoint events to the appropriate handler.
 */
static void _usbd_hal_irq_handler(uint32_t source, void* user_arg)
{
	uint32_t status;

	status = USBHS->USBHS_DEVISR;
	status &= USBHS->USBHS_DEVIMR;

	/* Handle all USBHS interrupts */
	while (status) {
		/* SOF */
		if (status & USBHS_DEVISR_SOF) {
			USB_HAL_TRACE("SOF ");

			/* Acknowledge interrupt */
			USBHS->USBHS_DEVICR = USBHS_DEVICR_SOFC;
		}
		else if (status & USBHS_DEVISR_MSOF) {
			USB_HAL_TRACE("Mosf ");

			/* Acknowledge interrupt */
			USBHS->USBHS_DEVICR = USBHS_DEVICR_MSOFC;
		}
		/* Suspend, treated last */
		else if (status & USBHS_DEVISR_SUSP) {
			USB_HAL_TRACE("Susp ");

			USBHS->USBHS_CTRL &= ~((uint32_t)USBHS_CTRL_FRZCLK);
			/* Acknowledge interrupt */
			USBHS->USBHS_DEVICR = USBHS_DEVICR_SUSPC;
			USBHS->USBHS_DEVIDR = USBHS_DEVIDR_SUSPEC;

			/* Enable wakeup */
			USBHS->USBHS_DEVIER = USBHS_DEVIER_WAKEUPES;
			USBHS->USBHS_CTRL |= USBHS_CTRL_FRZCLK;
			usbd_suspend_handler();
			USBHS->USBHS_DEVIER = USBHS_DEVIER_UPRSMES;
		}
		/* Resume */
		else if ((status & USBHS_DEVISR_WAKEUP) ||
				(status & USBHS_DEVISR_EORSM)) {
			USB_HAL_TRACE("Rsm ");

			USBHS->USBHS_CTRL &= ~((uint32_t)USBHS_CTRL_FRZCLK);

			/* Acknowledge interrupt */
			USBHS->USBHS_DEVICR = USBHS_DEVICR_WAKEUPC;
			USBHS->USBHS_DEVIDR = USBHS_DEVIDR_WAKEUPEC;

			USBHS->USBHS_DEVIER |= USBHS_DEVIER_EORSMES | USBHS_DEVIER_SUSPES;
			usbd_resume_handler();
		}
		/* Bus reset */
		else if (status & USBHS_DEVISR_EORST) {
			USB_HAL_TRACE("EoB ");

			/* Acknowledge interrupt */
			USBHS->USBHS_DEVICR = USBHS_DEVICR_EORSTC;

			/* Flush and enable the suspend interrupt */
			USBHS->USBHS_DEVICR = USBHS_DEVICR_WAKEUPC | USBHS_DEVICR_SUSPC;
			USBHS->USBHS_DEVIER = USBHS_DEVIER_SUSPES;

			/* Reset handler */
			usbd_reset_handler();

			USBHS->USBHS_DEVIER = (USBHS_DEVIER_SUSPES | USBHS_DEVIER_SOFES |\
				   USBHS_DEVIER_MSOFES);
		}
		/* Upstream resume */
		else if (status & USBHS_DEVISR_UPRSM) {
			USB_HAL_TRACE("ExtRes ");

			/* Acknowledge interrupt */
			USBHS->USBHS_DEVICR = USBHS_DEVICR_UPRSMC;
			USBHS->USBHS_DEVIER = USBHS_DEVIER_EORSMES;
		}
		/* Endpoints */
		else {
			uint32_t ep;
			for (ep = 0; ep < USB_ENDPOINTS; ep++) {
				if (CHIP_USB_ENDPOINT_HAS_DMA(ep) &&
					_usbd_hal_get_dma_interrupt_status(ep - 1)) {
					_usbd_hal_dma_handler(ep);
				} else if (USBHS->USBHS_DEVISR & (USBHS_DEVISR_PEP_0 << ep)) {
					_usbd_hal_endpoint_handler(ep);
				}
			}
		}

		/* Update interrupt status */
		status = USBHS->USBHS_DEVISR;
		status &= USBHS->USBHS_DEVIMR;

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
 * \param keep_cfg true to keep old endpoint configuration.
 * \note Use usbd_hal_configure() to configure and enable endpoint
		 if not keeping old configuration.
 * \sa usbd_hal_configure().
 */
void usbd_hal_reset_endpoints(uint32_t endpoint_bits, uint8_t status, bool keep_cfg)
{
	struct _endpoint *endpoint;
	uint32_t tmp = endpoint_bits & ((1 << USB_ENDPOINTS) - 1);
	uint8_t ep;
	uint32_t ep_cfg;

	for (ep = 0; ep < USB_ENDPOINTS; ep++) {
		if (tmp & (1 << ep)) {
			/* Disable ISR */
			_usbd_hal_endpoint_interrupt_disable(ep);

			/* Reset transfer information */
			endpoint = &(endpoints[ep]);

			/* save endpoint config */
			ep_cfg = _usbd_hal_endpoint_get_config(ep);

			/* Reset endpoint */
			_usbd_hal_endpoint_reset(ep);

			/* Restore endpoint config */
			if (keep_cfg) {
				_usbd_hal_endpoint_set_config(ep, ep_cfg);
			} else {
				endpoint->state = USB_HAL_ENDPOINT_DISABLED;
			}

			/* Clear data toggle sequence */
			_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_RSTDTS);

			/* Terminate transfer on this EP */
			_usbd_hal_end_of_transfer(ep, status);
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
	struct _endpoint *endpoint;
	uint8_t ep;
	uint8_t direction;
	uint8_t type;
	uint8_t nb_trans = 0;
	uint8_t nb_banks;

	/* NULL or DEVICE descriptor -> Control endpoint 0 */
	if (!descriptor || descriptor->bDescriptorType == USBGenericDescriptor_DEVICE) {
		USBDeviceDescriptor *dev_desc = (USBDeviceDescriptor*)descriptor;

		ep = 0;
		endpoint = &endpoints[0];
		type = USBEndpointDescriptor_CONTROL;
		direction = USBEndpointDescriptor_OUT;
		endpoint->size = dev_desc ?
			dev_desc->bMaxPacketSize0 : CHIP_USB_ENDPOINT_MAXPACKETSIZE(0);
		nb_banks = 0;
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
		if (type == USBEndpointDescriptor_ISOCHRONOUS && usbd_hal_is_high_speed()) {
			/* HS Interval, *125us */
			/* MPS: Bit12,11 specify NB_TRANS, as USB 2.0 Spec. */
			nb_trans = ((endpoint->size >> 11) & 0x3) + 1;
			if (nb_trans > 1) {
				if (CHIP_USB_ENDPOINT_IS_HBW(ep)) {
					if (nb_trans == 4)
						nb_trans = 1;
				} else {
					trace_fatal("usbd_hal_configure: invalid descriptor (NBTRANS > 0 but endpoint is not High Bandwidth capable\r\n");
				}
			}
		}

		/* Mask, bit 10..0 is the size */
		endpoint->size &= 0x7ff;
		nb_banks = CHIP_USB_ENDPOINT_BANKS(ep) - 1;
	} else {
		trace_fatal("usbd_hal_configure: invalid descriptor\r\n");
	}
	USB_HAL_TRACE("CfgE%d ", ep);

	/* Abort the current transfer is the endpoint was configured and in
	   Write or Read state */
	if ((endpoint->state == USB_HAL_ENDPOINT_RECEIVING)
		|| (endpoint->state == USB_HAL_ENDPOINT_SENDING)
		|| (endpoint->state == USB_HAL_ENDPOINT_RECEIVINGM)
		|| (endpoint->state == USB_HAL_ENDPOINT_SENDINGM)) {
		_usbd_hal_end_of_transfer(ep, USBD_STATUS_RESET);
	}
	endpoint->state = USB_HAL_ENDPOINT_IDLE;

	/* Configure endpoint */
	if (type == USBEndpointDescriptor_CONTROL)
		_usbd_hal_endpoint_interrupt_enable(ep);

	_usbd_hal_endpoint_configure(ep, direction, type, endpoint->size, nb_banks, nb_trans);

	USBHS->USBHS_DEVEPTCFG[ep] |= USBHS_DEVEPTCFG_ALLOC;
	if ((_usbd_hal_endpoint_get_status(ep) & USBHS_DEVEPTISR_CFGOK) == 0) {
		trace_error_wp("EP%d configuration:", ep);
		trace_error_wp("direction=%d ", direction);
		trace_error_wp("type=0x%X ", type);
		trace_error_wp("size=0x%X ", endpoint->size);
		trace_error_wp("nb_banks=%d ", nb_banks);
		trace_error_wp("config=0x%X\n\r",
				(unsigned)_usbd_hal_endpoint_get_status(ep));
		trace_error_wp("EP%d configuration failed\n\r", ep);
	}
	/* enable Endpoint */
	USBHS->USBHS_DEVEPT |= (USBHS_DEVEPT_EPEN0 << ep);

	if (type == USBEndpointDescriptor_CONTROL) {
		/* Enable endpoinnt interrupt type */
		_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_RXOUTES | USBHS_DEVEPTIER_RXSTPES);
		/* enable endpoint interrupt */
		_usbd_hal_endpoint_interrupt_enable(ep);
	}
	_usbd_auto_switch_bank_enable(ep, true);
	USB_HAL_TRACE("<%x,%x,%x> ", (unsigned)_usbd_hal_endpoint_get_config(ep),
			(unsigned)_usbd_hal_endpoint_control_get_status(ep), (unsigned)_usbd_hal_endpoint_get_status(ep));
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
	if (endpoint->state > USB_HAL_ENDPOINT_IDLE)
		return USBD_STATUS_LOCKED;

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
	while (endpoint->state > USB_HAL_ENDPOINT_IDLE);

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
		return _usbd_hal_add_buffer(ep, data, data_len);
	else
		return _usbd_hal_write(ep, data, data_len);
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
	if (endpoint->state != USB_HAL_ENDPOINT_IDLE)
		return USBD_STATUS_LOCKED;

	/* Sending state */
	endpoint->state = USB_HAL_ENDPOINT_SENDING;
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
		uint8_t nb_trans = (_usbd_hal_endpoint_get_config(ep) & USBHS_DEVEPTCFG_NBTRANS_Msk) >> USBHS_DEVEPTCFG_NBTRANS_Pos;

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
		dma_desc[0].ctrl = USBHS_DEVDMACONTROL_CHANN_ENB
			| USBHS_DEVDMACONTROL_BUFF_LENGTH(header_len)
			| USBHS_DEVDMACONTROL_LDNXT_DSC;
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
				dma_desc[1].ctrl = USBHS_DEVDMACONTROL_CHANN_ENB |
					USBHS_DEVDMACONTROL_BUFF_LENGTH(data_len) |
					USBHS_DEVDMACONTROL_END_B_EN |
					USBHS_DEVDMACONTROL_END_BUFFIT;
				dma_desc[1].reserved = 0;
			} else {
				dma_desc[1].next = &dma_desc[2];
				dma_desc[1].addr = data_ptr;
				dma_desc[1].ctrl = USBHS_DEVDMACONTROL_CHANN_ENB |
					USBHS_DEVDMACONTROL_BUFF_LENGTH(pkt_len) |
					USBHS_DEVDMACONTROL_END_B_EN |
					USBHS_DEVDMACONTROL_LDNXT_DSC;
				dma_desc[1].reserved = 0;
				data_len -= pkt_len;
				data_ptr += pkt_len;

				/* LD3: data  - bank 1 */
				pkt_len = endpoint->size;
				if (pkt_len >= data_len) {
					dma_desc[2].next = NULL;
					dma_desc[2].addr = data_ptr;
					dma_desc[2].ctrl = USBHS_DEVDMACONTROL_CHANN_ENB |
						USBHS_DEVDMACONTROL_BUFF_LENGTH(data_len) |
						USBHS_DEVDMACONTROL_END_B_EN |
						USBHS_DEVDMACONTROL_END_BUFFIT;
					dma_desc[2].reserved = 0;
				} else {
					dma_desc[2].next = &dma_desc[3];
					dma_desc[2].addr = data_ptr;
					dma_desc[2].ctrl = USBHS_DEVDMACONTROL_CHANN_ENB |
						USBHS_DEVDMACONTROL_BUFF_LENGTH(pkt_len) |
						USBHS_DEVDMACONTROL_END_B_EN |
						USBHS_DEVDMACONTROL_LDNXT_DSC;
					dma_desc[2].reserved = 0;
					data_len -= pkt_len;
					data_ptr += pkt_len;

					/* LD4: data  - bank 2 */
					dma_desc[3].next = NULL;
					dma_desc[3].addr = data_ptr;
					dma_desc[3].ctrl = USBHS_DEVDMACONTROL_CHANN_ENB |
						USBHS_DEVDMACONTROL_BUFF_LENGTH(data_len) |
						USBHS_DEVDMACONTROL_END_B_EN |
						USBHS_DEVDMACONTROL_END_BUFFIT;
					dma_desc[3].reserved = 0;
				}
			}
		}
		/* Normal, fill all data */
		else {
			/* LD2: data   -  load to fifo with interrupt */
			data_len = xfer->buffered - header_len;
			dma_desc[1].next = NULL;
			dma_desc[1].addr = (void*)data;
			dma_desc[1].ctrl = USBHS_DEVDMACONTROL_CHANN_ENB
				| USBHS_DEVDMACONTROL_BUFF_LENGTH(data_len)
				| USBHS_DEVDMACONTROL_END_B_EN
				| USBHS_DEVDMACONTROL_END_BUFFIT;
			dma_desc[1].reserved = 0;
		}

		/* Flush DMA descriptors */
		cache_clean_region(dma_desc, sizeof(dma_desc));

		/* Interrupt enable */
		_usbd_hal_endpoint_dma_interrupt_enable(ep);

		/* Start transfer with LLI */
		USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMANXTDSC = (uint32_t)dma_desc;
		USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMACONTROL = 0;
		USBHS->USBHS_DEVDMA[ep - 1].USBHS_DEVDMACONTROL = USBHS_DEVDMACONTROL_LDNXT_DSC;
	} else {
		/* Enable IT */
		_usbd_hal_endpoint_interrupt_enable(ep);

		/* Enable TX */
		_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_TXINES);
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
	return _usbd_hal_endpoint_get_received_data_size(ep);
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
		return _usbd_hal_read(ep, data, data_len);
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
	/* At startup the USB bus state is unknown, therefore the state is considered
	IDLE to not miss any USB event*/

	USBHS->USBHS_CTRL &= ~((uint32_t)USBHS_CTRL_FRZCLK);

	/* Authorize attach */
	USBHS->USBHS_DEVCTRL &= ~((uint32_t)USBHS_DEVCTRL_DETACH);

	/*(RESET_AND_WAKEUP)
	 After the attach and the first USB suspend, the following USB Reset time can be
	 inferior to CPU restart clock time.
	 Thus, the USB Reset state is not detected and endpoint control is not allocated
	 In this case, a Reset is do automatically after attach. */
	usbd_hal_configure(0);

	USBHS->USBHS_DEVIER = (USBHS_DEVIER_EORSTES | USBHS_DEVIER_WAKEUPES |\
						   USBHS_DEVIER_SUSPES | USBHS_DEVIER_MSOFES);
	/* Reset following interrupts flag */
	USBHS->USBHS_DEVICR = (USBHS_DEVICR_EORSTC | USBHS_DEVICR_SOFC | USBHS_DEVICR_MSOFC |\
						   USBHS_DEVICR_SUSPC);

	/* The first suspend interrupt is not detected else raise it */
	USBHS->USBHS_DEVIFR = USBHS_DEVIFR_SUSPS;
	USBHS->USBHS_DEVICR = USBHS_DEVICR_WAKEUPC;
	USBHS->USBHS_CTRL |= USBHS_CTRL_FRZCLK;
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
	USBHS->USBHS_CTRL |= USBHS_CTRL_FRZCLK;
	/* Detach device from the bus */
	USBHS->USBHS_DEVCTRL |= USBHS_DEVCTRL_DETACH;
}

/**
 * Starts a remote wake-up procedure.
 */
void usbd_hal_remote_wakeup(void)
{
	USB_HAL_TRACE("RWUp ");

	/* Activates a remote wakeup (edge on ESR), then clear ESR */
	USBHS->USBHS_DEVCTRL |= USBHS_DEVCTRL_RMWKUP;
	while (USBHS->USBHS_DEVCTRL & USBHS_DEVCTRL_RMWKUP) {
		USB_HAL_TRACE("w");
	}
}

/**
 * Sets the device address to the given value.
 * \param address New device address.
 */
void usbd_hal_set_address(uint8_t address)
{
	if (address) {
		USBHS->USBHS_DEVCTRL |= USBHS_DEVCTRL_UADD(address);
		USBHS->USBHS_DEVCTRL |= USBHS_DEVCTRL_ADDEN;
	} else {
		USBHS->USBHS_DEVCTRL &= ~((uint32_t)USBHS_DEVCTRL_ADDEN);
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
	uint32_t cfg = USBHS->USBHS_DEVCTRL;

	if (force_full_speed){
		/* USB clock register: USB Clock Input is UTMI PLL */
		PMC->PMC_USB = (PMC_USB_USBS | PMC_USB_USBDIV(10 - 1));
	} else {
		/* USBCLK not used in this configuration (High Speed) */
		PMC->PMC_SCDR = PMC_SCDR_USBCLK;
	}

	/* Enable the USBHS peripheral clock.*/
	_usbd_hal_enable_peripheral_clock();

	/* Enable the 480MHz USB clock */
	_usbd_hal_enable_usb_clock();

	cfg &= ~((uint32_t)USBHS_DEVCTRL_SPDCONF_Msk);
	if (force_full_speed)
		USBHS->USBHS_DEVCTRL |= (cfg | USBHS_DEVCTRL_SPDCONF_FORCED_FS);
	else
		USBHS->USBHS_DEVCTRL |= cfg;

	/* Device mode is selected */
	USBHS->USBHS_CTRL |= USBHS_CTRL_UIMOD_DEVICE;
	USBHS->USBHS_CTRL &= ~((uint32_t)USBHS_CTRL_UIDE);

	/* Enable USB hardware*/
	USBHS->USBHS_CTRL |= USBHS_CTRL_USBE;

	/* Unfreeze the USB clock */
	USBHS->USBHS_CTRL &= ~((uint32_t)USBHS_CTRL_FRZCLK);

	if (force_full_speed){
		/* Enable the USBCLK bit */
		PMC->PMC_SCER = PMC_SCER_USBCLK;
	}

	/* Check USB clock */
	while (!((USBHS->USBHS_SR & USBHS_SR_CLKUSABLE) >> 14));

	/* Add and enable USB IRQ */
	irq_add_handler(ID_USBHS, _usbd_hal_irq_handler, USBHS);
	irq_enable(ID_USBHS);
}

/**
 * Causes the given endpoint to acknowledge the next packet it receives
 * with a STALL handshake except setup request.
 * \param ep Endpoint number.
 * \return USBD_STATUS_SUCCESS or USBD_STATUS_LOCKED.
 */
uint8_t usbd_hal_stall(uint8_t ep)
{
	struct _endpoint *endpoint = &endpoints[ep];

	/* Check that endpoint is in Idle state */
	if (endpoint->state != USB_HAL_ENDPOINT_IDLE) {
		trace_warning("usbd_hal_stall: EP%d not idle\n\r", ep);
		return USBD_STATUS_LOCKED;
	}

	/* STALL endpoint */
	_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_STALLRQS);

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
	struct _endpoint *endpoint = &endpoints[ep];

	/* Check that endpoint is enabled and not already in Halt state */
	if ((endpoint->state != USB_HAL_ENDPOINT_DISABLED)
		&& (endpoint->state != USB_HAL_ENDPOINT_HALTED)) {
		USB_HAL_TRACE("Halt%d ", ep);

		/* Abort the current transfer if necessary */
		_usbd_hal_end_of_transfer(ep, USBD_STATUS_ABORTED);

		/* Put endpoint into Halt state */
		endpoint->state = USB_HAL_ENDPOINT_HALTED;

		while (!_usbd_is_bank_free(ep)) {
			USBHS->USBHS_DEVEPTIER[ep] = USBHS_DEVEPTIER_KILLBKS;
			while (USBHS->USBHS_DEVEPTIMR[ep] & USBHS_DEVEPTIMR_KILLBK);
		}

		if (_usbd_is_bank_free(ep)) {
			_usbd_auto_switch_bank_enable(ep, false);
			_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_STALLRQS | USBHS_DEVEPTIER_RSTDTS);
		} else {
			_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_NBUSYBKES);
			if (CHIP_USB_ENDPOINT_HAS_DMA(ep)) {
				/* Enable the endpoint DMA interrupt */
				_usbd_hal_endpoint_dma_interrupt_enable(ep);
			} else {
				/* Enable the endpoint interrupt */
				_usbd_hal_endpoint_interrupt_enable(ep);
			}
		}
	}

	return endpoint->state == USB_HAL_ENDPOINT_HALTED;
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
	struct _endpoint *endpoint = &endpoints[ep];

	/* Check if the endpoint is halted */
	if (endpoint->state == USB_HAL_ENDPOINT_HALTED ||
			(_usbd_hal_endpoint_control_get_status(ep) & USBHS_DEVEPTIMR_STALLRQ)) {
		USB_HAL_TRACE("Unhalt%d ", ep);

		/* Return endpoint to Idle state */
		endpoint->state = USB_HAL_ENDPOINT_IDLE;

		/* Clear FORCESTALL flag */
		_usbd_hal_endpoint_control_disable(ep, USBHS_DEVEPTIDR_STALLRQC);
		_usbd_auto_switch_bank_enable(ep, true);
	} else {
		/* Reinitialize the data toggle to DATA0 regardless of whether
		the endponit has the Halt feature.*/
		/* Clear data toggle sequence */
		_usbd_hal_endpoint_control_enable(ep, USBHS_DEVEPTIER_RSTDTS);
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
	return endpoints[ep].state == USB_HAL_ENDPOINT_HALTED;
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
	return ((USBHS->USBHS_SR & USBHS_SR_SPEED_Msk) == USBHS_SR_SPEED_HIGH_SPEED) ? \
		   true : false;
}

/**
 * Suspend USB Device HW Interface
 * -# Disable transceiver
 * -# Disable USB Clock
 * -# Disable USB Peripheral
 */
void usbd_hal_suspend(void)
{
	USBHS->USBHS_CTRL |= USBHS_CTRL_FRZCLK;
}

/**
 * Activate USB Device HW Interface
 * -# Enable USB Peripheral
 * -# Enable USB Clock
 * -# Enable transceiver
 */
void usbd_hal_activate(void)
{
	USBHS->USBHS_CTRL &= ~((uint32_t)USBHS_CTRL_FRZCLK);
}

/**
 * Certification test for High Speed device.
 * \param index Test to be done
 */
void usbd_hal_test(uint8_t index)
{
	/* remove suspend for TEST */
	USBHS->USBHS_DEVIDR |= USBHS_DEVIDR_SUSPEC;

	/* force High Speed (remove suspend) */
	USBHS->USBHS_DEVCTRL |= USBHS_DEVCTRL_SPDCONF_HIGH_SPEED;

	switch (index) {
	case USBFeatureRequest_TESTPACKET:
		USB_HAL_TRACE("TEST_PACKET ");

		USBHS->USBHS_DEVDMA[1].USBHS_DEVDMACONTROL = 0;
		USBHS->USBHS_DEVDMA[2].USBHS_DEVDMACONTROL = 0;

		/* Configure endpoint 2, 64 bytes, direction IN, type BULK, 1 bank */
		_usbd_hal_endpoint_configure(2, USBEndpointDescriptor_IN, USBEndpointDescriptor_BULK, 64, 1, 0);
		USBHS->USBHS_DEVEPTCFG[2] |= USBHS_DEVEPTCFG_ALLOC;
		while ((USBHS->USBHS_DEVEPTISR[2] & USBHS_DEVEPTISR_CFGOK) !=
			   USBHS_DEVEPTISR_CFGOK);
		USBHS->USBHS_DEVEPT |= (USBHS_DEVEPT_EPEN0 << 2);

		/* Write FIFO */
		_usbd_hal_write_fifo_buffer(2, test_packet_buffer, sizeof(test_packet_buffer));

		/* Tst PACKET */
		USBHS->USBHS_DEVCTRL |= USBHS_DEVCTRL_TSTPCKT;

		/* Send packet */
		_usbd_hal_endpoint_control_disable(2, USBHS_DEVEPTIDR_FIFOCONC);
		break;

	case USBFeatureRequest_TESTJ:
		USB_HAL_TRACE("TEST_J ");
		USBHS->USBHS_DEVCTRL |= USBHS_DEVCTRL_TSTJ;
		break;

	case USBFeatureRequest_TESTK:
		USB_HAL_TRACE("TEST_K ");
		USBHS->USBHS_DEVCTRL |= USBHS_DEVCTRL_TSTK;
		break;

	case USBFeatureRequest_TESTSE0NAK:
		USB_HAL_TRACE("TEST_SEO_NAK ");
		USBHS->USBHS_DEVIDR |= 0xFFFFFFFF;
		break;

	case USBFeatureRequest_TESTSENDZLP:
		_usbd_hal_endpoint_clear_status(2, USBHS_DEVEPTICR_TXINIC);
		USB_HAL_TRACE("SEND_ZLP ");
		break;
	}
	USB_HAL_TRACE("\r\n");
}

/**@}*/
