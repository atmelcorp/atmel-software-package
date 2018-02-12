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

#ifndef _QTM_H
#define _QTM_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdio.h>

#include "compiler.h"
#include "mutex.h"
#include "ptc.h"
/*----------------------------------------------------------------------------
 *        Constants
 *----------------------------------------------------------------------------*/

/* X line bit position */
#define PTC_X_NONE 0u

#define PTC_X(n) ((uint16_t)(0x0001u << (n)))
#define PTC_GET_X(n) (32 - CLZ(n) - 1)

/* Y line bit position */
#define PTC_Y(n) ((uint32_t)(0x00000001u << (n)))
#define PTC_GET_Y(n) (32 - CLZ(n) - 1)

/** Node is disabled */
#define QTM_NODE_DISABLED 0u

/** Node is enabled */
#define QTM_NODE_ENABLED  1u

/**After mS perform an acquire */
#define QTM_ACQ_REFRESH  1u
  

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

enum _qtm_event {
	QTM_EVENT_KEY,
	QTM_EVENT_SCROLLER,

	QTM_EVENTS,
};

struct _qtm {
	struct _ppp* ppp; /* ppp instance */
        
	volatile struct atmel_qtm_mailbox* mailbox; /* mapping in the mailbox */

	struct _callback event[QTM_EVENTS];

	mutex_t mutex;
};

/*----------------------------------------------------------------------------
 *        Public functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Get a pointer to the qtm instance in use
 * \return pointer to the current QTM instance
 */
extern struct _qtm* qtm_get_instance(void);

/**
 * \brief configure a QTM isntance
 * \param qtm        QTM instance
 */
extern void qtm_configure(struct _qtm* qtm);

/**
 * \brief Register a handler for events
 * \param qtm       QTM instance
 * \param event     Event to handle
 * \param on_event  Callback to handle the event \event
 * \return 0 on succes, else negative error code
 */
extern int qtm_event_request(struct _qtm* qtm, enum _qtm_event event, callback_method_t on_event);

/**
 * \brief Start QTM
 * \param qtm        QTM instance
 */
extern void qtm_start(struct _qtm* qtm);

/**
 * \brief Stop QTM
 * \param qtm        QTM instance
 */
extern void qtm_stop(struct _qtm* qtm);

/**
 * \brief Get a copy of the current mailbox
 * \param qtm        QTM instance
 * \param mb         Pointer to a mailbox structure to copy the current mailbox into
 */
extern void qtm_get_mailbox(struct _qtm* qtm, struct atmel_qtm_mailbox* mb);

/**
 * \brief Print the given scroller
 * \param idx        Id of scroller
 */
extern void qtm_print_scroller(struct _qtm* qtm, uint8_t idx);

/**
 * \brief Load QTM configuration
 * \param qtm        QTM instance
 * \param channels   Number of channels
 */
extern void qtm_load(struct _qtm* qtm, uint16_t channels);

/**
 * \brief Display QTM acquired data
 * \param qtm     QTM instance
 */
extern void qtm_display_data(struct _qtm* qtm);


#endif /* ! _QTM_H */
