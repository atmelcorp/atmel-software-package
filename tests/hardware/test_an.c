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

//------------------------------------------------------------------------------
//         Headers
//------------------------------------------------------------------------------

#include "board.h"
#include "chip.h"

#include "misc/console.h"
#include "peripherals/aic.h"
#include "peripherals/adc.h"
#include "peripherals/l2cc.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"
#include "peripherals/xdmad.h"
#include "peripherals/wdt.h"

#include "timer.h"
#include "mutex.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* warning to PIOs used for TWI PMIC
 * #define ADC_CHANNEL_2  2	 PD21
 * #define ADC_CHANNEL_3  3	 PD22
 */

/** ADC clock */
#define BOARD_ADC_FREQ (300000)

#define NUMBER_OF_ADC_CHANNELS	12

static uint8_t adc_channel_used[] =
{
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_4,
	ADC_CHANNEL_5,
};

/** Total number of ADC channels in use */
#define NUM_CHANNELS    ARRAY_SIZE(adc_channel_used)

/** ADC convention done mask */
#define ADC_DONE_MASK   ((1<<NUM_CHANNELS) - 1 )

#define VREF		3300
#define MAX_DIGITAL	4096

/*------------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** ADC test mode structure */
struct _adc_test_mode
{
	uint8_t trigger_mode;
	uint8_t dma_enabled;
	uint8_t sequence_enabled;
	uint8_t power_save_enabled;
};

/** ADC trigger modes */
enum _trg_mode
{
	TRIGGER_MODE_SOFTWARE = 0,
	TRIGGER_MODE_ADTRG,
	TRIGGER_MODE_TIMER,
};

/** ADC sample data */
struct _adc_sample
{
	int16_t value[NUM_CHANNELS];
	uint16_t done;
	uint8_t  channel[NUM_CHANNELS];
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** ADC sample data */
static struct _adc_sample _data;

/** ADC test mode */
static struct _adc_test_mode _test_mode;

/* /\** Definition of ADTRG pin *\/ */
struct _pin pin_adtrg[] = {PIN_ADTRG};

struct _timeout timeout;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Interrupt handler for the ADC.
 */
static void adc_irq_handler(void)
{
	uint32_t status;
 	uint8_t i, j;
	uint32_t value;

	/* Get Interrupt Status (ISR) */
	status = adc_get_status();

	/* check at least one EOCn flag set */
	if( status & 0x00000FFF ) {
		for (i=0; i < NUMBER_OF_ADC_CHANNELS; i++) {
			value = adc_get_converted_data(i);
			/* Check ISR "End of Conversion" corresponding bit */
			if ((status & (1u<<i))) {
				for (j = 0; j < NUM_CHANNELS; j++) {
					if ( _data.channel[j] == i) {
						_data.value[j] = value;
						_data.done |= 1 << i;
						break;
					}
				}
			}
		}
	}
}

static void _initialize_adc(void)
{
	/* Initialize ADC */
	adc_initialize();
	adc_set_ts_mode(0);
	/* Set ADC clock */
	adc_set_clock(BOARD_ADC_FREQ);
	/* Set ADC timing */
	adc_set_timing(ADC_MR_STARTUP_SUT512, 0, 0);
	/* Enable channel number tag */
	adc_set_tag_enable(true);
}

/**
 * \brief (Re)Sart ADC sample.
 * Initialize ADC, set clock and timing, set ADC to given mode.
 */
static void _configure_adc(void)
{
	uint8_t i = 0;

	/* Check if sequence mode is necessary */
	_test_mode.sequence_enabled = 0;
	for(i = 0; i < NUM_CHANNELS; i++) {
		if(i != adc_channel_used[i]) {
			_test_mode.sequence_enabled = 1;
			break;
		}
	}

	/* Update channel number */
	for (i = 0; i < NUM_CHANNELS; i++) {
		_data.channel[i] = adc_channel_used[i];
	}

	/* Enable/disable sequencer */
	if (_test_mode.sequence_enabled) {

		/* Set user defined channel sequence */
		adc_set_sequence_by_list(adc_channel_used, NUM_CHANNELS);
		/* Enable sequencer */
		adc_set_sequence_mode(true);

	} else {
		/* Disable sequencer */
		adc_set_sequence_mode(false);
	}

	/* Enable channels, gain, single mode */
	for (i = 0; i < NUM_CHANNELS; i++) {
		adc_enable_channel(_data.channel[i]);
	}

	/* Set power save */
	if (_test_mode.power_save_enabled) {
		adc_set_sleep_mode(true);
	} else {
		adc_set_sleep_mode(false);
	}

	/* Transfer with/without DMA */
	/* Initialize XDMA driver instance with polling mode */

	/* Enable Data ready interrupt */
	uint32_t ier_mask = 0;
	for (i = 0; i < NUM_CHANNELS; i++) {
		ier_mask |= 0x1u << _data.channel[i];
	}
	adc_enable_it(ier_mask) ;

	/* Set ADC irq handler */
	aic_set_source_vector(ID_ADC, adc_irq_handler);

	/* Configure trigger mode and start convention */
	switch (_test_mode.trigger_mode) {
		case TRIGGER_MODE_SOFTWARE:
			/* Disable hardware trigger */
			adc_set_trigger(0);
			/* No trigger, only software trigger can start conversions */
			adc_set_trigger_mode(ADC_TRGR_TRGMOD_NO_TRIGGER);
			aic_enable(ID_ADC);
			break;
		case TRIGGER_MODE_ADTRG:
			pio_configure(pin_adtrg, ARRAY_SIZE(pin_adtrg));
			break;
		case TRIGGER_MODE_TIMER :
			/* Enable hardware trigger */
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG1);
			/* Trigger timer*/
			adc_set_trigger_mode(ADC_TRGR_TRGMOD_PERIOD_TRIG);
			adc_set_trigger_period(250);
			aic_enable(ID_TC0);
			break;
		default :
			break;
	}
}

void launch_adc (void)
{
	/* Set defaut ADC test mode */
	memset((void *)&_test_mode, 0, sizeof(_test_mode));

	_test_mode.trigger_mode = TRIGGER_MODE_SOFTWARE;
	_test_mode.dma_enabled = 0;
	_test_mode.sequence_enabled = 0;

	aic_enable(ID_ADC);
	_initialize_adc();
	_configure_adc();

	_data.done = 0;
	adc_start_conversion();
	timer_start_timeout(&timeout, 250);

}

int16_t get_adc_conv (uint8_t channel)
{
	int16_t x = 0x0000 ;

	switch (channel) {
		case ADC_CHANNEL_0:
		case ADC_CHANNEL_1:
		case ADC_CHANNEL_4:
		case ADC_CHANNEL_5:
			if (_data.done & ADC_DONE_MASK) {
				x = _data.value[channel];
			}
			break;
		default:
			if (timer_timeout_reached(&timeout)) {
				_data.done = 0;
				adc_start_conversion();
				timer_start_timeout(&timeout, 250);
			}
			break;
	}
	return x;
}

void test_adc (void)
{
	uint8_t i = 0;

	while (1)
	{
		/* ADC software trigger per 100ms */
		if (_test_mode.trigger_mode == TRIGGER_MODE_SOFTWARE) {
			if (timer_timeout_reached(&timeout) && !_data.done) {
				adc_start_conversion();
				timer_start_timeout(&timeout, 250);
			}
		}
		if (_test_mode.trigger_mode == TRIGGER_MODE_ADTRG) {
			if (pio_get_output_data_status(&pin_adtrg[0]))
				pio_clear(&pin_adtrg[0]);
			else
				pio_set(&pin_adtrg[0]);
		}
		/* Check if ADC sample is done */
		if (_data.done & ADC_DONE_MASK) {
			for (i = 0; i < NUM_CHANNELS; ++i) {
				printf(" CH%02d: %04d ", _data.channel[i],
					   (_data.value[i]* VREF/MAX_DIGITAL) );
			}
			printf("\r");
			_data.done = 0;
		}
	}
}


