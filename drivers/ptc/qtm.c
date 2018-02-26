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

#include <stdio.h>
#include <string.h>

#include "board.h"
#include "board_ppp.h"
#include "callback.h"
#include "compiler.h"
#include "errno.h"
#include "ptc/ppp.h"
#include "ptc/qtm.h"
#include "ptc/qtm_firmware.h"
#include "ptc/qtm_configuration.h"
#include "timer.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Private variable
 *----------------------------------------------------------------------------*/

static struct _qtm* _qtm_instance;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static int _on_cmd_ack(void* arg, void* arg2)
{
	struct _qtm* qtm = (struct _qtm*)arg;

	mutex_unlock(&qtm->mutex);

	return 0;
}

static int _on_event(void* arg, void* arg2)
{
	struct _qtm* qtm = (struct _qtm*)arg;

	printf("events: key: id:         0x%08x%08x\r\n",
	       (unsigned int)qtm->mailbox->touch_events.key_event_id1,
	       (unsigned int)qtm->mailbox->touch_events.key_event_id0);
	printf("events: key: state:      0x%08x%08x\r\n",
	       (unsigned int)qtm->mailbox->touch_events.key_enable_state1,
	       (unsigned int)qtm->mailbox->touch_events.key_enable_state0);

	printf("events: scroller: id:            0x%08x\r\n",
	       (unsigned int)qtm->mailbox->touch_events.scroller_event_id);

	if (qtm->mailbox->touch_events.key_event_id0)
		callback_call(&qtm->event[QTM_EVENT_KEY], (void*)&qtm->mailbox->touch_events);

	if (qtm->mailbox->touch_events.scroller_event_id)
		callback_call(&qtm->event[QTM_EVENT_SCROLLER], (void*)&qtm->mailbox->touch_events);

	return 0;
}

static int _on_debug(void* arg, void* arg2)
{
	return 0;
}

static int _on_irq3(void* arg, void* arg2)
{
	trace_debug("IRQ3\r\n");

	return 0;
}

/**
 * \brief Send a command to the pPP
 * \param qtm        QTM instance
 * \param qcmd       QTM Command
 * \param qdata      QTM Data
 * \return Command status
 */
static uint32_t qtm_exec(struct _qtm* qtm, uint8_t qcmd, uint32_t qdata)
{
	uint32_t data;
	struct atmel_qtm_cmd cmd = {
			.id = qcmd,
			.data = qdata,
	};

	mutex_lock(&qtm->mutex);

	switch (qcmd) {
	case QTM_CMD_INIT:
		qtm_load(qtm, qdata);
		break;

	default:
		break;
	}
	memcpy((void *)&qtm->mailbox->cmd, &cmd.id, sizeof(struct atmel_qtm_cmd));
	ppp_exec(qtm->ppp);

	while (mutex_is_locked(&qtm->mutex));

	data = qtm->mailbox->cmd.data;

	return data;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

struct _qtm* qtm_get_instance(void)
{
	return _qtm_instance;
}

void qtm_configure(struct _qtm* qtm)
{
	_qtm_instance = qtm;
	qtm->mutex = 0;

	qtm->ppp = board_get_ppp();

	memset((void *)PPP_ADDR, 0, PPP_SRAM_LEN + PPP_MAILBOX_LEN);
	ppp_reset(qtm->ppp);
	ppp_load(qtm->ppp, qtm_get_firmware_addr(), qtm_get_firmware_size());
	ppp_start(qtm->ppp);

	/* Register IRQ callbacks */
	ppp_register_irq_handler(qtm->ppp, PPP_IER_IRQ0, _on_cmd_ack, qtm);
	ppp_register_irq_handler(qtm->ppp, PPP_IER_IRQ1, _on_event, qtm);
	ppp_register_irq_handler(qtm->ppp, PPP_IER_IRQ2, _on_debug, qtm);
	/* ppp_register_irq_handler(qtm->ppp, PPP_HF_HOST_IRQ_3, _on_irq3, NULL); */

	ppp_enable_it(qtm->ppp,  PPP_IER_IRQ0 | PPP_IER_IRQ1);
	ppp_disable_it(qtm->ppp, PPP_IDR_IRQ2 | PPP_IDR_IRQ3);

	qtm->mailbox = (struct atmel_qtm_mailbox*)(ppp_get_mailbox_addr(qtm->ppp));
	qtm_exec(qtm, QTM_CMD_FIRM_VERSION, 0);
	trace_info("qtm: firmware v%d.%d\r\n", qtm->mailbox->cmd.data >> 16, qtm->mailbox->cmd.data & 0xffff);
}

void qtm_start(struct _qtm* qtm)
{
	ppp_start(qtm->ppp);
        
	/* Initialise QTM for 10 sensors */
	qtm_exec(qtm, QTM_CMD_INIT, NULL);

	/* Configure QTM operation mode 	- uncomment only 1 of the lines below
	 * QTM_CMD_SET_ACQ_MODE_ON_DEMAND 	= 1 acquire per QTM_CMD_RUN
	 * QTM_CMD_SET_ACQ_MODE_TIMER 		= after 200 mS perform an acquire,
	 * only starts after 1 CMD_RUN_QTM command is issued
	 */
	qtm_exec(qtm, QTM_CMD_SET_ACQ_MODE_TIMER, QTM_ACQ_REFRESH);

	qtm_exec(qtm, QTM_CMD_RUN, NULL);

	/*enable PTC SleepWalking*/
	/*PMC->PMC_SLPWKCR = PMC_SLPWKCR_PID(ID_PPP)|(0x1<<12)|PMC_SLPWKCR_SLPWKSR;*/
}

int qtm_event_request(struct _qtm* qtm, enum _qtm_event event, callback_method_t on_event)
{
	switch (event) {
	case QTM_EVENT_KEY:
	case QTM_EVENT_SCROLLER:
		callback_set(&qtm->event[event], on_event, qtm);
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

void qtm_stop(struct _qtm* qtm)
{
	qtm_exec(qtm, QTM_CMD_STOP, 0);
	ppp_stop(qtm->ppp);

}

/**
 * \brief Load all touch related configuration into shared memory space.
 *	Initialise Acquire data structures.
 */
void qtm_load(struct _qtm* qtm, uint16_t channels)
{
	volatile struct atmel_qtm_mailbox* mb = qtm->mailbox;
        /** load qtm_configuration */
        ppp_memcpy((uint8_t *)&(mb->node_group_config), qtm_get_configuration_addr(), qtm_get_configuration_size());
}

/**
 *  \brief Helper function to display acquired data from PPP-PTC to Terminal window.
 */
void qtm_display_data(struct _qtm* qtm)
{
	struct atmel_qtm_mailbox _mb;

	qtm_get_mailbox(qtm, &_mb);

	//printf("\033c");
	printf("\033[J");

	printf("\033[2K");
	if(_mb.touch_events.scroller_event_id & 0x01) {
		printf("-D- Scroller%02d: \tPos: %04d\tRaw: %04d\tStat: %03d\tLHyst: %04d\tRHyst: %04d\tCtSz: %04d \r\n",
		       0,
		       _mb.scroller_data[0].position,
		       _mb.scroller_data[0].raw_position,
		       _mb.scroller_data[0].status,
		       _mb.scroller_data[0].left_hyst,
		       _mb.scroller_data[0].right_hyst,
		       _mb.scroller_data[0].contact_size);

	} else if(_mb.touch_events.scroller_event_id & 0x02) {
		trace_debug("Scrollerevents [0] :0x %08x\r\n", (unsigned int)_mb.touch_events.scroller_event_id);
		printf("-D- Scroller%02d: \tPos: %04d\tRaw: %04d\tStat: %03d\tLHyst: %04d\tRHyst: %04d\tCtSz: %04d \r\n",
		       1,
		       _mb.scroller_data[1].position,
		       _mb.scroller_data[1].raw_position,
		       _mb.scroller_data[1].status,
		       _mb.scroller_data[1].left_hyst,
		       _mb.scroller_data[1].right_hyst,
		       _mb.scroller_data[1].contact_size);

	}
}

void qtm_get_mailbox(struct _qtm* qtm, struct atmel_qtm_mailbox* mb)
{
	memcpy(mb, (void*)qtm->mailbox, sizeof(struct atmel_qtm_mailbox));
}
