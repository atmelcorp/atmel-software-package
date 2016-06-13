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

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "chip.h"
#include "trace.h"
#include "ring.h"

#include "peripherals/aic.h"
#include "peripherals/gmacd.h"
#include "misc/cache.h"
#include "peripherals/pmc.h"

#include <string.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *         Definitions
 *----------------------------------------------------------------------------*/

// Interrupt bits
#define GMAC_INT_RX_BITS     (GMAC_IER_RCOMP | GMAC_IER_RXUBR | GMAC_IER_ROVR)
#define GMAC_INT_TX_ERR_BITS (GMAC_IER_TUR | GMAC_IER_RLEX | GMAC_IER_TFC)
#define GMAC_INT_TX_BITS     (GMAC_INT_TX_ERR_BITS | GMAC_IER_TCOMP)

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/

struct _gmacd_irq_handler {
	Gmac*           addr;
	struct _ethd** gmacd;
	uint32_t        irq;
	aic_handler_t   handler;
};

/*---------------------------------------------------------------------------
 *         IRQ Handlers
 *---------------------------------------------------------------------------*/

#if ETH_NUM_QUEUES < GMAC_NUM_QUEUES
#error The number of queues for ETH is too small for GMAC!
#endif

#ifdef CONFIG_HAVE_GMAC_QUEUES
#if GMAC_NUM_QUEUES != 3
#error This driver assumes that GMAC_NUM_QUEUES is 3
#endif
#endif

static struct _ethd* _gmacd0;
#ifdef GMAC1
static struct _ethd* _gmacd1;
#endif

static void _gmacd_handler(struct _ethd* gmacd, uint8_t queue);

static void _gmacd_gmac0_irq_handler(void)
{
	_gmacd_handler(_gmacd0, 0);
}

#ifdef CONFIG_HAVE_GMAC_QUEUES
static void _gmacd_gmac0q1_irq_handler(void)
{
	_gmacd_handler(_gmacd0, 1);
}

static void _gmacd_gmac0q2_irq_handler(void)
{
	_gmacd_handler(_gmacd0, 2);
}
#endif

#ifdef GMAC1
static void _gmacd_gmac1_irq_handler(void)
{
	_gmacd_handler(_gmacd1, 0);
}

#ifdef CONFIG_HAVE_GMAC_QUEUES
static void _gmacd_gmac1q1_irq_handler(void)
{
	_gmacd_handler(_gmacd1, 1);
}

static void _gmacd_gmac1q2_irq_handler(void)
{
	_gmacd_handler(_gmacd1, 2);
}
#endif
#endif

static const struct _gmacd_irq_handler _gmacd_irq_handlers[] = {
	{ GMAC0, &_gmacd0, ID_GMAC0,    _gmacd_gmac0_irq_handler },
#ifdef CONFIG_HAVE_GMAC_QUEUES
	{ GMAC0, &_gmacd0, ID_GMAC0_Q1, _gmacd_gmac0q1_irq_handler },
	{ GMAC0, &_gmacd0, ID_GMAC0_Q2, _gmacd_gmac0q2_irq_handler },
#endif
#ifdef GMAC1
	{ GMAC1, &_gmacd1, ID_GMAC1,    _gmacd_gmac1_irq_handler },
#ifdef CONFIG_HAVE_GMAC_QUEUES
	{ GMAC1, &_gmacd1, ID_GMAC1_Q1, _gmacd_gmac1q1_irq_handler },
	{ GMAC1, &_gmacd1, ID_GMAC1_Q2, _gmacd_gmac1q2_irq_handler },
#endif
#endif
};

/*---------------------------------------------------------------------------
 *         Dummy Buffers for unconfigured queues
 *---------------------------------------------------------------------------*/

#define DUMMY_BUFFERS 2
#define DUMMY_UNITSIZE 128

/** TX descriptors list */
ALIGNED(8) SECTION(".region_ddr_nocache")
static struct _eth_desc dummy_tx_desc[DUMMY_BUFFERS];

/** RX descriptors list */
ALIGNED(8) SECTION(".region_ddr_nocache")
static struct _eth_desc dummy_rx_desc[DUMMY_BUFFERS];

/** Send Buffer */
ALIGNED(32)
static uint8_t dummy_buffer[DUMMY_BUFFERS * DUMMY_UNITSIZE];

/*---------------------------------------------------------------------------
 *         Local functions
 *---------------------------------------------------------------------------*/

/**
 *  \brief Disable TX & reset registers and descriptor list
 *  \param gmacd Pointer to GMAC Driver instance.
 */
static void _gmacd_reset_tx(struct _ethd* gmacd, uint8_t queue)
{
	struct _ethd_queue* q = &gmacd->queues[queue];
	uint32_t addr = (uint32_t)q->tx_buffer;
	uint32_t i;

	/* Disable TX */
	gmac_transmit_enable(gmacd->gmac, false);

	/* Setup the TX descriptors */
	RING_CLEAR(q->tx_head, q->tx_tail);
	for (i = 0; i < q->tx_size; i++) {
		q->tx_desc[i].addr = addr;
		dsb();
		q->tx_desc[i].status = ETH_TX_STATUS_USED;
		addr += ETH_TX_UNITSIZE;
	}
	q->tx_desc[q->tx_size - 1].status |= ETH_TX_STATUS_WRAP;

	/* Transmit Buffer Queue Pointer Register */
	gmac_set_tx_desc(gmacd->gmac, queue, q->tx_desc);
}

/**
 *  \brief Disable RX & reset registers and descriptor list
 *  \param gmacd Pointer to GMAC Driver instance.
 */
static void _gmacd_reset_rx(struct _ethd* gmacd, uint8_t queue)
{
	struct _ethd_queue* q = &gmacd->queues[queue];
	uint32_t addr = (uint32_t)q->rx_buffer;
	uint32_t i;

	/* Disable RX */
	gmac_receive_enable(gmacd->gmac, false);

	/* Setup the RX descriptors */
	q->rx_head = 0;
	for (i = 0; i < q->rx_size; i++) {
		q->rx_desc[i].addr = addr & ETH_RX_ADDR_MASK;
		dsb();
		q->rx_desc[i].status = 0;
		addr += ETH_RX_UNITSIZE;
	}
	q->rx_desc[q->rx_size - 1].addr |= ETH_RX_ADDR_WRAP;

	/* Receive Buffer Queue Pointer Register */
	gmac_set_rx_desc(gmacd->gmac, queue, q->rx_desc);
}

/**
 *  \brief Process successfully sent packets
 *  \param gmacd Pointer to GMAC Driver instance.
 */
static void _gmacd_tx_complete_handler(struct _ethd* gmacd, uint8_t queue)
{
	Gmac* gmac = gmacd->gmac;
	struct _ethd_queue* q = &gmacd->queues[queue];
	struct _eth_desc *desc;
	ethd_callback_t callback;
	uint32_t tsr;

	//printf("<TX>\r\n");

	/* Clear status */
	tsr = gmac_get_tx_status(gmac);
	gmac_clear_tx_status(gmac, tsr);

	while (!RING_EMPTY(q->tx_head, q->tx_tail)) {
		desc = &q->tx_desc[q->tx_tail];

		/* Exit if frame has not been sent yet:
		 * On TX completion, the GMAC set the USED bit only into the
		 * very first buffer descriptor of the sent frame.
		 * Otherwise it updates this descriptor with status error bits.
		 * This is the descriptor writeback.
		 */
		if ((desc->status & ETH_TX_STATUS_USED) == 0)
			break;

		/* Process all buffers of the current transmitted frame */
		while ((desc->status & ETH_TX_STATUS_LASTBUF) == 0) {
			RING_INC(q->tx_tail, q->tx_size);
			desc = &q->tx_desc[q->tx_tail];
		}

		/* Notify upper layer that a frame has been sent */
		if (q->tx_callbacks) {
			callback = q->tx_callbacks[q->tx_tail];
			if (callback)
				callback(queue, tsr);
		}

		/* Go to next frame */
		RING_INC(q->tx_tail, q->tx_size);
	}

	/* If a wakeup callback has been set, notify upper layer that it can
	   send more packets now */
	if (q->tx_wakeup_callback) {
		if (RING_SPACE(q->tx_head, q->tx_tail, q->tx_size) >=
				q->tx_wakeup_threshold) {
			q->tx_wakeup_callback(queue);
		}
	}
}

/**
 *  \brief Reset TX queue when errors are detected
 *  \param gmacd Pointer to GMAC Driver instance.
 */
static void _gmacd_tx_error_handler(struct _ethd* gmacd, uint8_t queue)
{
	Gmac *gmac = gmacd->gmac;
	struct _ethd_queue* q = &gmacd->queues[queue];
	struct _eth_desc* desc;
	ethd_callback_t callback;
	uint32_t tsr;

	printf("<TXERR>\r\n");

	/* Clear TXEN bit into the Network Configuration Register:
	 * this is a workaround to recover from TX lockups that
	 * occur on sama5d4 gmac (r1p24f2) when using  scatter-gather.
	 * This issue has never been seen on sama5d4 gmac (r1p31).
	 */
	gmac_transmit_enable(gmac, false);

	/* The following step should be optional since this function is called
	 * directly by the IRQ handler. Indeed, according to Cadence
	 * documentation, the transmission is halted on errors such as
	 * too many retries or transmit under run.
	 * However it would become mandatory if the call of this function
	 * were scheduled as a task by the IRQ handler (this is how Linux
	 * driver works). Then this function might compete with ethd_send().
	 *
	 * Setting bit 10, tx_halt, of the Network Control Register is not enough:
	 * We should wait for bit 3, tx_go, of the Transmit Status Register to
	 * be cleared at transmit completion if a frame is being transmitted.
	 */
	gmac_halt_transmission(gmac);
	while (gmac_get_tx_status(gmac) & GMAC_TSR_TXGO);

	/* Treat frames in TX queue including the ones that caused the error. */
	while (!RING_EMPTY(q->tx_head, q->tx_tail)) {
		int tx_completed = 0;
		desc = &q->tx_desc[q->tx_tail];

		/* Check USED bit on the very first buffer descriptor to validate
		 * TX completion.
		 */
		if (desc->status & ETH_TX_STATUS_USED)
			tx_completed = 1;

		/* Go to the last buffer descriptor of the frame */
		while ((desc->status & ETH_TX_STATUS_LASTBUF) == 0) {
			RING_INC(q->tx_tail, q->tx_size);
			desc = &q->tx_desc[q->tx_tail];
		}

		/* Notify upper layer that a frame status */
		// TODO: which error to notify?
		if (q->tx_callbacks) {
			callback = q->tx_callbacks[q->tx_tail];
			if (callback)
				callback(queue, tx_completed ? GMAC_TSR_TXCOMP : 0);
		}

		/* Go to next frame */
		RING_INC(q->tx_tail, q->tx_size);
	}

	/* Reset TX queue */
	_gmacd_reset_tx(gmacd, queue);

	/* Clear status */
	tsr = gmac_get_tx_status(gmac);
	gmac_clear_tx_status(gmac, tsr);

	/* Now we are ready to start transmission again */
	gmac_transmit_enable(gmac, true);
	if (q->tx_wakeup_callback)
		q->tx_wakeup_callback(queue);
}

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

/**
 *  \brief GMAC Interrupt handler
 *  \param gmacd Pointer to GMAC Driver instance.
 */
static void _gmacd_handler(struct _ethd * gmacd, uint8_t queue)
{
	Gmac *gmac = gmacd->gmac;
	struct _ethd_queue* q = &gmacd->queues[queue];
	uint32_t isr;
	uint32_t rsr;

	/* Interrupt Status Register is cleared on read */
	while ((isr = gmac_get_it_status(gmac, queue)) != 0) {
		/* RX packet */
		if (isr & GMAC_INT_RX_BITS) {
			/* Clear status */
			rsr = gmac_get_rx_status(gmac);
			gmac_clear_rx_status(gmac, rsr);

			/* Invoke callback */
			if (q->rx_callback)
				q->rx_callback(queue, rsr);
		}

		/* TX error */
		if (isr & GMAC_INT_TX_ERR_BITS) {
			_gmacd_tx_error_handler(gmacd, queue);
			break;
		}

		/* TX packet */
		if (isr & GMAC_IER_TCOMP) {
			_gmacd_tx_complete_handler(gmacd, queue);
		}

		/* HRESP not OK */
		if (isr & GMAC_IER_HRESP) {
			trace_error("HRESP not OK\n\r");
		}
	}
}

/**
 * \brief Initialize the GMAC with the Gmac controller address
 *  \param gmacd Pointer to GMAC Driver instance.
 *  \param gmac    Pointer to HW address for registers.
 *  \param enableCAF    Enable/Disable CopyAllFrame.
 *  \param enableNBC    Enable/Disable NoBroadCast.
 */
void gmacd_configure(struct _ethd * gmacd,
	   Gmac * gmac, uint8_t enableCAF, uint8_t enableNBC)
{
	uint32_t ncfgr;
	int i;

	/* Initialize struct */
	gmacd->gmac = gmac;

	gmac_configure(gmac);

	uint32_t id = get_gmac_id_from_addr(gmac);
	for (i = 0; i < ARRAY_SIZE(_gmacd_irq_handlers); i++) {
		if (_gmacd_irq_handlers[i].addr == gmac) {
			*_gmacd_irq_handlers[i].gmacd = gmacd;
			aic_set_source_vector(_gmacd_irq_handlers[i].irq,
					_gmacd_irq_handlers[i].handler);
		}
	}
	aic_enable(id);

	/* Enable the copy of data into the buffers
	   ignore broadcasts, and don't copy FCS. */
	ncfgr = gmac_get_network_config_register(gmac);
	ncfgr |= GMAC_NCFGR_FD;
	if (enableCAF) {
		ncfgr |= GMAC_NCFGR_CAF;
	}
	if (enableNBC) {
		ncfgr |= GMAC_NCFGR_NBC;
	}
	gmac_set_network_config_register(gmac, ncfgr);

	for (i = 0; i < GMAC_NUM_QUEUES; i++) {
		gmacd_setup_queue(gmacd, i,
				DUMMY_BUFFERS, dummy_buffer, dummy_rx_desc,
				DUMMY_BUFFERS, dummy_buffer, dummy_tx_desc,
				NULL);
	}
}

/**
 * Initialize necessary allocated buffer lists for GMAC Driver to transfer data.
 * Must be invoked after gmacd_configure() but before RX/TX start.
 * \param gmacd Pointer to GMAC Driver instance.
 * \param rx_buffer Pointer to allocated buffer for RX. The address should
 *                  be 8-byte aligned and the size should be
 *                  ETH_RX_UNITSIZE * wRxSize.
 * \param rx_desc      Pointer to allocated RX descriptor list.
 * \param wRxSize   RX size, in number of registered units (RX descriptors).
 * \param tx_buffer Pointer to allocated buffer for TX. The address should
 *                  be 8-byte aligned and the size should be
 *                  ETH_TX_UNITSIZE * wTxSize.
 * \param tx_desc      Pointer to allocated TX descriptor list.
 * \param pTxCb     Pointer to allocated TX callback list.
 * \param wTxSize   TX size, in number of registered units (TX descriptors).
 * \return ETH_OK or ETH_PARAM.
 * \note If input address is not 8-byte aligned the address is automatically
 *       adjusted and the list size is reduced by one.
 */
uint8_t gmacd_setup_queue(struct _ethd* gmacd, uint8_t queue,
		uint16_t rx_size, uint8_t* rx_buffer, struct _eth_desc* rx_desc,
		uint16_t tx_size, uint8_t* tx_buffer, struct _eth_desc* tx_desc,
		ethd_callback_t *tx_callbacks)
{
	Gmac *gmac = gmacd->gmac;
	struct _ethd_queue* q = &gmacd->queues[queue];

	if (rx_size <= 1 || tx_size <= 1)
		return ETH_PARAM;

	/* Assign RX buffers */
	if (((uint32_t)rx_buffer & 0x7)
	    || ((uint32_t)rx_desc & 0x7)) {
		rx_size--;
		trace_debug("RX list address adjusted\n\r");
	}
	q->rx_buffer = (uint8_t*)((uint32_t)rx_buffer & 0xFFFFFFF8);
	q->rx_desc = (struct _eth_desc *)((uint32_t)rx_desc & 0xFFFFFFF8);
	q->rx_size = rx_size;
	q->rx_callback = NULL;

	/* Assign TX buffers */
	if (((uint32_t)tx_buffer & 0x7)
	    || ((uint32_t)tx_desc & 0x7)) {
		tx_size--;
		trace_debug("TX list address adjusted\n\r");
	}
	q->tx_buffer = (uint8_t*)((uint32_t)tx_buffer & 0xFFFFFFF8);
	q->tx_desc = (struct _eth_desc*)((uint32_t)tx_desc & 0xFFFFFFF8);
	q->tx_size = tx_size;
	q->tx_callbacks = tx_callbacks;
	q->tx_wakeup_callback = NULL;

	/* Reset TX & RX */
	_gmacd_reset_rx(gmacd, queue);
	_gmacd_reset_tx(gmacd, queue);

	/* Setup the interrupts for RX/TX completion (and errors) */
	gmac_enable_it(gmac, queue, GMAC_INT_RX_BITS | GMAC_INT_TX_BITS | GMAC_IER_HRESP);

	return ETH_OK;
}

void gmacd_start(struct _ethd * gmacd)
{
	/* Enable Rx and Tx, plus the stats register. */
	gmac_transmit_enable(gmacd->gmac, true);
	gmac_receive_enable(gmacd->gmac, true);
	gmac_enable_statistics_write(gmacd->gmac, true);
}

/**
 * Reset TX & RX queue & statistics
 * \param gmacd Pointer to GMAC Driver instance.
 */
void gmacd_reset(struct _ethd* gmacd)
{
	int i;
	for (i = 0; i < GMAC_NUM_QUEUES; i++) {
		_gmacd_reset_rx(gmacd, i);
		_gmacd_reset_tx(gmacd, i);
	}

	gmac_set_network_control_register(gmacd->gmac, GMAC_NCR_TXEN | GMAC_NCR_RXEN |
			GMAC_NCR_WESTAT | GMAC_NCR_CLRSTAT);
}

/**
 * \brief Registers pRxCb callback. Callback will be invoked after the next received
 * frame. When ethd_poll() returns GMAC_RX_NO_DATA the application task call
 * ethd_set_rx_callback() to register pRxCb() callback and enters suspend state.
 * The callback is in charge to resume the task once a new frame has been received.
 * The next time ethd_poll() is called, it will be successful.
 *  \param gmacd Pointer to GMAC Driver instance.
 *  \param fRxCb   Pointer to callback function
 *  \return        OK, no data, or frame too small
 */
void gmacd_set_rx_callback(struct _ethd* gmacd, uint8_t queue, ethd_callback_t callback)
{
	struct _ethd_queue* q = &gmacd->queues[queue];
	if (!callback) {
		gmac_disable_it(gmacd->gmac, queue, GMAC_IDR_RCOMP);
		q->rx_callback = NULL;
	} else {
		q->rx_callback = callback;
		gmac_enable_it(gmacd->gmac, queue, GMAC_IER_RCOMP);
	}
}

const struct _ethd_op _gmac_op = {
	.configure = (_ethd_configure)gmacd_configure,
	.setup_queue = (_ethd_setup_queue)gmacd_setup_queue,
	.start = (_ethd_start)gmacd_start,
	.reset = (_ethd_reset)gmacd_reset,
	.set_mac_addr = (_eth_set_mac_addr)gmac_set_mac_addr,
	.set_mac_addr32 = (_eth_set_mac_addr32)gmac_set_mac_addr32,
	.set_mac_addr64 = (_eth_set_mac_addr64)gmac_set_mac_addr64,
	.start_transmission =(_eth_start_transmission)gmac_start_transmission,
	.send_sg = (_ethd_send_sg)ethd_send_sg,
	.send = (_ethd_send)ethd_send,
	.poll = (_ethd_poll)ethd_poll,
	.set_rx_callback = (_ethd_set_rx_callback)gmacd_set_rx_callback,
	.set_tx_wakeup_callback = (_ethd_set_tx_wakeup_callback)ethd_set_tx_wakeup_callback,
};
