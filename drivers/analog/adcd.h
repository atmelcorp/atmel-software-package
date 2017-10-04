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


#ifndef ADCD_H_
#define ADCD_H_

/*------------------------------------------------------------------------------
 *        Header
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "callback.h"
#include "dma/dma.h"
#include "io.h"
#include "mutex.h"

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

#define ADCD_SUCCESS         (0)
#define ADCD_ERROR_LOCK      (1)
#define ADCD_ERROR_TRANSFER  (2)

#define ADCD_MAX_CHANNELS    (12)

/** ADC trigger modes */
enum _trg_mode
{
	TRIGGER_MODE_SOFTWARE = 0,
	TRIGGER_MODE_ADTRG,
	TRIGGER_MODE_TIOA0,
	TRIGGER_MODE_TIOA1,
	TRIGGER_MODE_TIOA2,
	TRIGGER_MODE_PWM0,
	TRIGGER_MODE_PWM1,
	TRIGGER_MODE_ADC_TIMER,
};

/** ADC trigger modes */
enum _trg_edge
{
	TRIGGER_NO = 0,
	TRIGGER_EXT_TRIG_RISE,
	TRIGGER_EXT_TRIG_FALL,
	TRIGGER_EXT_TRIG_ANY,
	TRIGGER_PEN,
	TRIGGER_PERIOD,
	TRIGGER_CONTINUOUS
};

/* structure to define ADC config */
struct _adcd_cfg {
	enum _trg_mode trigger_mode;
	enum _trg_edge trigger_edge;
	bool dma_enabled;
	bool power_save_enabled;
	uint32_t freq;
	uint32_t channel_mask;
};

/* structure to define ADC state */
struct _adcd_desc {
	struct _adcd_cfg cfg;

	/* following fields are used internally */
	mutex_t mutex;

	/* structure to hold data about current transfer */
	struct {
		struct _buffer *buf;        /*< buffer output */
		struct _callback callback;

		struct {
			struct _dma_channel *channel;
			struct _dma_cfg cfg_dma;
		} dma;
	} xfer;
};

/*------------------------------------------------------------------------------
 *        Functions
 *----------------------------------------------------------------------------*/

extern void adcd_initialize(struct _adcd_desc* desc);

extern uint32_t adcd_transfer(struct _adcd_desc* desc, struct _buffer* buffer, struct _callback* cb);

extern bool adcd_is_busy(struct _adcd_desc* desc);

extern void adcd_wait_transfer(struct _adcd_desc* desc);

#endif /* ADCD_H_ */
