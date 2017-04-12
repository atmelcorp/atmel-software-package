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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <assert.h>
#include <string.h>

#include "board.h"
#include "can/cand.h"
#include "irq/irq.h"
#include "peripherals/pmc.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** \addtogroup cand_states CAN Driver states
 *      @{*/
#define CAND_STATE_DISABLED     0 /**< Power-up reset, controller is disabled */
#define CAND_STATE_INIT         1 /**< Initializing */
#define CAND_STATE_SLEEP        2 /**< Low-power mode */
#define CAND_STATE_SYNC         3 /**< Synchronizating */
#define CAND_STATE_ERROR        4 /**< Error halt */
#define CAND_STATE_ACTIVATED    5 /**< Bus synchronization is done */
#define CAND_STATE_XFR          6 /**< Transfer in progress */
/**     @}*/

/** \addtogroup cand_xfr_states CAN Transfer states
 *      @{*/
#define CAND_XFR_DISABLED       0 /**< Transfer not used */
#define CAND_XFR_HALTED         1 /**< Error halt */
#define CAND_XFR_IDLE           2 /**< No transfer */
#define CAND_XFR_TX             3 /**< Transferring data */
/**     @}*/

/** \addtogroup cand_reg_bits CAN Register Bitfields
 *      @{*/
/** CAN mailbox event statuses bits */
#define CAN_MB_EVENTS       0xFF
/** CAN errors statuses bits */
#define CAN_ERRS    (0 \
                     /*| CAN_SR_ERRA*/ \
                     /*| CAN_SR_WARN*/ \
                     /*| CAN_SR_ERRP*/ \
                     /*| CAN_SR_BOFF*/ \
                     /*| CAN_SR_SLEEP*/ \
                     /*| CAN_SR_WAKEUP*/ \
                     /*| CAN_SR_TOVF*/ \
                     /*| CAN_SR_TSTP*/ \
                     | CAN_SR_CERR \
                     | CAN_SR_SERR \
                     | CAN_SR_AERR \
                     | CAN_SR_FERR \
                     | CAN_SR_BERR \
                     /*| CAN_SR_RBSY*/ \
                     /*| CAN_SR_TBSY*/ \
                     /*| CAN_SR_OVLSY*/ \
                     )
/**     @}*/

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static struct _can_desc can_desc[CAN_IFACE_COUNT];

/*----------------------------------------------------------------------------
 *        Local Functions
 *----------------------------------------------------------------------------*/

static void cand_reset_mailbox(struct _can_desc* desc, uint8_t mailbox,
		uint32_t mask, uint8_t type, uint8_t priority)
{
	Can *can = desc->addr;
	can_disable_it(can, (1 << mailbox) & CAN_MB_EVENTS);
	can_message_control(can, mailbox, 0);
	can_configure_msg_mask(can, mailbox, mask);
	can_configure_message_mode(can, mailbox,
		CAN_MMR_MOT(type) | CAN_MMR_PRIOR(priority));
}

static uint8_t cand_allocate_mailbox(struct _can_desc* desc)
{
	uint8_t mailbox;

	for (mailbox = 0; mailbox < CAN_NUM_MAILBOX; mailbox++) {
		if (desc->mailboxes[mailbox].state == CAND_XFR_DISABLED
			|| desc->mailboxes[mailbox].state == CAND_XFR_IDLE)
		break;
	}
	return mailbox;
}

/**
 * Handler for CAN errors
 */
static void cand_error_handler(struct _can_desc* desc, uint32_t errors)
{
	uint32_t ecr;

	trace_debug("CAN[%p]: 0x%08x\n\r", desc->addr, (unsigned)errors);

	ecr = (desc->addr)->CAN_ECR;

	if (errors & CAN_SR_ERRA)
		trace_error("Active Mode: TEC %u, REC %u\n\r",
			(unsigned)((ecr & CAN_ECR_TEC_Msk) >> CAN_ECR_TEC_Pos),
			(unsigned)((ecr & CAN_ECR_REC_Msk) >> CAN_ECR_REC_Pos));

	if (errors & CAN_SR_WARN)
		trace_error("Warning Limit: TEC %u, REC %u\n\r",
			(unsigned)((ecr & CAN_ECR_TEC_Msk) >> CAN_ECR_TEC_Pos),
			(unsigned)((ecr & CAN_ECR_REC_Msk) >> CAN_ECR_REC_Pos));

	if (errors & CAN_SR_ERRP)
		trace_error("Passive Mode: TEC %u, REC %u\n\r",
			(unsigned)((ecr & CAN_ECR_TEC_Msk) >> CAN_ECR_TEC_Pos),
			(unsigned)((ecr & CAN_ECR_REC_Msk) >> CAN_ECR_REC_Pos));

	if (errors & CAN_SR_BOFF)
		trace_error("Bus Off Mode, TEC %u\n\r",
			(unsigned)((ecr & CAN_ECR_TEC_Msk) >> CAN_ECR_TEC_Pos));

	if (errors & CAN_SR_CERR)
		trace_error("MB CRC\n\r");

	if (errors & CAN_SR_SERR)
		trace_error("MB Stuffing\n\r");

	if (errors & CAN_SR_AERR)
		trace_error("Ack\n\r");

	if (errors & CAN_SR_FERR)
		trace_error("Form\n\r");

	if (errors & CAN_SR_BERR)
		trace_error("Bit\n\r");
}

/**
 * Handler for messages
 * \param pCand Pointer to CAN Driver instance.
 */
static void cand_message_handler(struct _can_desc* desc)
{
	uint8_t mailbox;
	uint32_t sr;
	struct _buffer **buf;
	Can *can = desc->addr;

	for (mailbox = 0; mailbox < CAN_NUM_MAILBOX; mailbox++) {
		buf = &desc->mailboxes[mailbox].buf;
		if (*buf == NULL)
			continue;

		/* Mailbox ready ? */
		sr = can_get_message_status(can, mailbox);
		if ((sr & CAN_MSR_MRDY) != CAN_MSR_MRDY)
			continue;

		/* Handle data */
		switch (can_get_message_mode(can, mailbox) & CAN_MMR_MOT_Msk) {
		case CAN_MMR_MOT_MB_RX_OVERWRITE: /** Next data overwrite current */
		case CAN_MMR_MOT_MB_RX:
		case CAN_MMR_MOT_MB_CONSUMER: /** TX then RX message */
			can_get_message(can, mailbox, (uint32_t *)(*buf)->data);
			(*buf)->size = (sr & CAN_MSR_MDLC_Msk) >> CAN_MSR_MDLC_Pos;
			(*buf)->attr |= CAND_BUF_ATTR_TRANSFER_DONE;
			break;

		case CAN_MMR_MOT_MB_TX:
		case CAN_MMR_MOT_MB_PRODUCER: /** RX then TX message */
			(*buf)->attr |= CAND_BUF_ATTR_TRANSFER_DONE;
			break;

		default:
			trace_error("MB[%d] disabled\n\r", mailbox);
			(*buf)->attr |= CAND_BUF_ATTR_TRANSFER_ERR;
			break;
		}

		/* Disable mailbox interrupt */
		can_disable_it(can, 1 << mailbox);

		*buf = NULL;
		desc->mailboxes[mailbox].state = CAND_XFR_IDLE;
		callback_call(&desc->mailboxes[mailbox].cb, NULL);
	}

	/* All transfer finished ? */
	if ((can_get_it_mask(can) & CAN_MB_EVENTS) == 0)
		desc->state = CAND_STATE_ACTIVATED;
}

/**
 * Interrupt handler for CAN Driver.
 */
static void _can_handler(uint32_t source, void* user_arg)
{
	uint32_t status;
	struct _can_desc *desc = (struct _can_desc*)user_arg;
	Can *can;

	can = desc->addr;
	status = can_get_status(can);

	/* Errors */
	if (status & CAN_ERRS) {
		desc->state = CAND_STATE_ERROR;
		cand_error_handler(desc, status & CAN_ERRS);
		can_disable_it(can, status & CAN_ERRS);
	} else {
		/* Wakeup and bus synchronization done */
		if (desc->state > CAND_STATE_ACTIVATED) {
			/* Mailbox events */
			if (status & CAN_MB_EVENTS)
				cand_message_handler(desc);
		} else if (status & CAN_SR_WAKEUP) {
			can_disable_it(can, CAN_IDR_WAKEUP);
			desc->state = CAND_STATE_ACTIVATED;
		}
	}

	/* Low-power Mode enabled */
	if (status & CAN_SR_SLEEP) {
		can_disable_it(can, CAN_IDR_SLEEP);
		desc->state = CAND_STATE_SLEEP;
	}
}

/**
 * \brief Calculate and configure the baudrate
 * \param can      Pointer to Can instance.
 * \param baudrate Baudrate value (b/s)
 *                 allowed: 100000, 800000, 500000, 250000, 125000, 50000, 25000, 10000
 * \return 0 on success, otherwise return errno.
 */
static int cand_set_baudrate(Can* can, uint32_t baudrate)
{
	uint32_t brp, propag, phase1, phase2, sjw;
	uint8_t  tq;
	uint32_t t1t2;
	uint32_t clock;
	uint32_t id;

	id = get_can_id_from_addr(can);
	assert(id < ID_PERIPH_COUNT);

	clock = pmc_get_peripheral_clock(id);
	baudrate /= 1000;
	if (baudrate >= 1000)
		tq = 8;
	else
		tq = 16;
	brp = (clock / (baudrate * 1000 * tq)) - 1;
	if (brp == 0)
		return -EINVAL;

	/* Timing delay:
	   Delay Bus Driver     - 50ns
	   Delay Receiver       - 30ns
	   Delay Bus Line (20m) - 110ns */
	if ( (tq * baudrate * 2 * (50 + 30 + 110) / 1000000) >= 1 )
		propag = (tq * baudrate * 2 * (50 + 30 + 110) / 1000000) - 1;
	else
		propag = 0;
	t1t2 = tq - 1 - (propag + 1);

	if ( (t1t2 & 0x01) == 0x01 ) {
		phase1 = ((t1t2 - 1) / 2) - 1;
		phase2 = phase1 + 1;
	} else {
		phase1 = ((t1t2) / 2) - 1;
		phase2 = phase1;
	}

	if ( 1 > (4 / (phase1 + 1)) )
		sjw = 3;
	else
		sjw = phase1;

	if ((propag + phase1 + phase2) != (uint32_t)(tq - 4))
		return -EINVAL;

	can->CAN_BR = CAN_BR_PHASE2(phase2)
		| CAN_BR_PHASE1(phase1)
		| CAN_BR_PROPAG(propag)
		| CAN_BR_SJW(sjw)
		| CAN_BR_BRP(brp)
		| CAN_BR_SMP_ONCE;

	return 0;
}

/*----------------------------------------------------------------------------
 *        Exported Functions
 *----------------------------------------------------------------------------*/

struct _can_desc* cand_get_desc(uint8_t can_if)
{
	if (can_if >= CAN_IFACE_COUNT)
		return NULL;
	return &can_desc[can_if];
}

int cand_configure(struct _can_desc* desc)
{
	uint32_t mailbox;
	Can *can = desc->addr;
	uint32_t id = get_can_id_from_addr(can);
	int err;

	pmc_enable_peripheral(id);

	err = cand_set_baudrate(can, desc->freq);
	if (err < 0) {
		trace_error("Set baudrate for can bus failed!");
		return err;
	}

	/* Reset CAN mode */
	can_configure_mode(can, 0);

	memset(desc->mailboxes, 0, sizeof(desc->mailboxes));

	/* Reset all mailboxes */
	for (mailbox = 0; mailbox < CAN_NUM_MAILBOX; mailbox ++)
		cand_reset_mailbox(desc, mailbox, 0,
			CAN_MMR_MOT_MB_DISABLED >> CAN_MMR_MOT_Pos, 0);

	desc->state = CAND_STATE_INIT;

	/* Enable the interrupts for error cases */
	can_enable_it(can, CAN_ERRS);

	irq_add_handler(id, _can_handler, desc);
	irq_enable(id);

	return 0;
}

void cand_enable(struct _can_desc* desc)
{
	Can *can = desc->addr;
	if (desc->state > CAND_STATE_SYNC)
		return;

	/* Disable low-power mode */
	can_enable_low_power(can, 0);

	/* Start sync state */
	desc->state = CAND_STATE_SYNC;

	/* Enable CAN and wait interrupt */
	can_enable_it(can, CAN_IER_WAKEUP);
	can_enable(can, 1);
}

bool cand_is_enabled(struct _can_desc* desc)
{
	return (desc->state >= CAND_STATE_ACTIVATED);
}

int cand_transfer(struct _can_desc* desc, struct _buffer* buf,
		struct _callback* cb)
{
	uint32_t type;
	uint32_t mask;
	uint32_t identifier;

	Can *can = desc->addr;
	struct _cand_mailbox *mb;
	uint8_t mailbox;

	mailbox = cand_allocate_mailbox(desc);
	if (mailbox >= CAN_NUM_MAILBOX)
		return -ENOMEM;

	mb = &desc->mailboxes[mailbox];
	callback_copy(&mb->cb, cb);

	if (buf->attr & CAND_BUF_ATTR_RX)
		type = CAN_MMR_MOT_MB_RX;
	else if (buf->attr & CAND_BUF_ATTR_RX_OVERWRITE)
		type = CAN_MMR_MOT_MB_RX_OVERWRITE;
	else if (buf->attr & CAND_BUF_ATTR_TX)
		type = CAN_MMR_MOT_MB_TX;
	else if (buf->attr & CAND_BUF_ATTR_CONSUMER)
		type = CAN_MMR_MOT_MB_CONSUMER;
	else if (buf->attr & CAND_BUF_ATTR_PRODUCER)
		type = CAN_MMR_MOT_MB_PRODUCER;
	else
		return -EINVAL;

	if (buf->attr & CAND_BUF_ATTR_EXTENDED) {
		mask = CAN_MID_MIDvB(desc->mask);
		identifier = CAN_MID_MIDvB(desc->identifier);
	} else {
		mask = CAN_MID_MIDvA(desc->mask);
		identifier = CAN_MID_MIDvA(desc->identifier);
	}

	cand_reset_mailbox(desc, mailbox, mask, type >> CAN_MMR_MOT_Pos, 0);

	buf->attr &= ~CAND_BUF_ATTR_TRANSFER_MSK;
	desc->mailboxes[mailbox].buf = buf;

	/* Reset transfer state */
	desc->mailboxes[mailbox].state = CAND_XFR_IDLE;

	/* Fill ID */
	can_configure_message_id(can, mailbox, identifier);

	/* Start TX if not RX */
	if (buf->attr & CAND_BUF_ATTR_TX_MSK) {
		/* Fill data registers */
		can_set_message(can, mailbox, (uint32_t*)buf->data);
		can_message_control(can, mailbox, CAN_MCR_MDLC(buf->size));
	}

	/* Change transfer state */
	desc->mailboxes[mailbox].state = CAND_XFR_TX;

	/* Change CAN state */
	desc->state = CAND_STATE_XFR;

	/* Start transfers */
	can_command(can, 1 << mailbox);

	/* Enable interrupts */
	can_enable_it(can, 1 << mailbox | CAN_ERRS);

	return 0;
}
