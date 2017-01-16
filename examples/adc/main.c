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

/**
 *  \page adc_adc ADC Example
 *
 *  \section Purpose
 *
 *  The adc12 example demonstrates how to use ADC peripheral with several modes.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-XPLAINED, SAMA5D4-EK, SAMA5D4-XPLAINED,
 *  SAMA5D3-EK, SAMA5D3-XPLAINED, SAM9XX5-EK.
 *
 *  -# SAMA5D2-XPLAINED: Connect PB9 (pin 1 on J21) to PD31 (ADTRG) (pin 33 on J17)
 *  -# SAMA5D4-XPLAINED: Connect PE23 (pin 1 on J18) to PE31 (ADTRG) (pin 34 on J15)
 *  -# SAMA5D4-EK: Connect to PE23 to PE31 (ADTRG)
 *  -# SAMA5D3-XPLAINED: Connect PD15 (pin 8 on J21) to PD19 (ADTRG) (pin 6 on J21)
 *  -# SAMA5D3-EK: Connect to PD15 (pin 32 on J3) to PD19 (ADTRG) (pin 34 on J3)
 *  -# SAM9XX5-EK: Connect to PA8 (pin 21 on J1) to PB18 (ADTRG) (pin 10 on J3)
 *
 *  \section Description
 *
 *  This application shows how to use the ADC using the several modes:
 *  with/without DMA, several types of trigger (Software, ADTRG, Timer, etc.),
 *  gain and offset selection, using sequencer. User can select different mode
 *  by configuration menu in the terminal.
 *
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or to the
 *     <a href="http://www.iar.com/website1/1.0.1.0/78/1/">
 *     IAR EWARM User and reference guides</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# In the terminal window, the
 *     following text should appear (values depend on the board and chip used):
 *     \code
 *      -- ADC12 Example xxx --
 *      -- xxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      =========================================================
 *      Menu: press a key to change the configuration.
 *      ---------------------------------------------------------
 *      [X] 0: Set ADC trigger mode: Software.
 *      [ ] 1: Set ADC trigger mode: ADTRG.
 *      [ ] 2: Set ADC trigger mode: Timer TIOA.
 *      [E] S: Enable/Disable sequencer
 *      [E] D: Enable/Disable to tranfer with DMA.
 *      [D] P: Enable/Disable ADC power save mode.
 *          Q: Quit configuration and start ADC.
 *      =========================================================
 *     \endcode
 *  -# The application will output converted value to hyperterminal and display
 *     a menu for user to set different mode.
 *
 *  \section References
 *  - adc12/main.c
 *  - adc.h
 */

/** \file
 *
 *  This file contains all the specific code for the adc12 example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "analog/adc.h"
#include "analog/adcd.h"
#include "board.h"
#include "callback.h"
#include "chip.h"
#include "component/component_tc.h"
#include "dma/dma.h"
#include "gpio/pio.h"
#include "led/led.h"
#include "mm/cache.h"
#include "peripherals/pit.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"
#include "serial/console.h"
#include "timer.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* check availability of ADC trigger 1 (trigger on TIOA0) */
#ifdef ADC_MR_TRGSEL_ADC_TRIG1
#define ADC_TRIG_TIOA0
#endif

/** ADC clock */
#define ADC_FREQ (300000)

/** ADC VREF */
#define BOARD_ADC_VREF (3300)

/** MAXIMUM DIGITAL VALUE */
#define DIGITAL_MAX    ((1 << adc_get_resolution()) - 1)

/** ADC slected channels */
static uint8_t adc_channel_used[] =
{
	0,
	1,
	2,
	3,
};

/** Total number of ADC channels in use */
#define NUM_CHANNELS    ARRAY_SIZE(adc_channel_used)

/*----------------------------------------------------------------------------
 *        Local types
 *----------------------------------------------------------------------------*/

/** ADC sample data */
struct _adc_sample
{
	uint8_t channel[NUM_CHANNELS];
	int16_t value[NUM_CHANNELS];
};

CACHE_ALIGNED static uint16_t adc_buffer[NUM_CHANNELS];

bool adc_converted = false;
unsigned count = 0;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** ADC sample data */
static struct _adc_sample _data;

/** ADCD test instance */
static struct _adcd_desc adcd;

/* /\** Definition of ADTRG pin *\/ */
struct _pin pin_adtrg[] = {PIN_ADTRG};
#if   defined(CONFIG_BOARD_SAMA5D4_XPLAINED)
struct _pin pin_trig = { PIO_GROUP_E, PIO_PE23, PIO_OUTPUT_1, PIO_PULLUP };
struct _pin pin_tioa0 = { PIO_GROUP_E, PIO_PE15C_TIOA0, PIO_PERIPH_C , PIO_DEFAULT };

#elif defined(CONFIG_BOARD_SAMA5D4_EK)
struct _pin pin_trig = { PIO_GROUP_E, PIO_PE23, PIO_OUTPUT_1, PIO_PULLUP };
struct _pin pin_tioa0 = { PIO_GROUP_E, PIO_PE15C_TIOA0, PIO_PERIPH_C , PIO_DEFAULT };

#elif defined(CONFIG_BOARD_SAMA5D2_XPLAINED)
struct _pin pin_trig = { PIO_GROUP_B, PIO_PB9,  PIO_OUTPUT_0, PIO_DEFAULT };
struct _pin pin_tioa0 = { PIO_GROUP_A, PIO_PA19D_TIOA0, PIO_PERIPH_D , PIO_DEFAULT };

#elif defined(CONFIG_BOARD_SAMA5D3_XPLAINED)
struct _pin pin_trig = { PIO_GROUP_D, PIO_PD15,  PIO_OUTPUT_0, PIO_DEFAULT };
struct _pin pin_tioa0 = { PIO_GROUP_D, PIO_PD5B_TIOA0, PIO_PERIPH_B , PIO_DEFAULT };

#elif defined(CONFIG_BOARD_SAMA5D3_EK)
struct _pin pin_trig = { PIO_GROUP_D, PIO_PD15,  PIO_OUTPUT_0, PIO_DEFAULT };
struct _pin pin_tioa0 = { PIO_GROUP_D, PIO_PD5B_TIOA0, PIO_PERIPH_B , PIO_DEFAULT };

#elif defined(CONFIG_BOARD_SAM9G15_EK) || \
	  defined(CONFIG_BOARD_SAM9G25_EK) || \
	  defined(CONFIG_BOARD_SAM9G35_EK) || \
	  defined(CONFIG_BOARD_SAM9X25_EK) || \
	  defined(CONFIG_BOARD_SAM9X35_EK)
struct _pin pin_trig = { PIO_GROUP_A, PIO_PA8,  PIO_OUTPUT_0, PIO_DEFAULT };
struct _pin pin_tioa0 = { PIO_GROUP_A, PIO_PA21A_TIOA0, PIO_PERIPH_A , PIO_DEFAULT };

#else
#error Unsupported target...
#endif

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Display ADC configuration menu.
 */
static void _display_menu(void)
{
	uint8_t tmp;

	printf("\n\r");
	printf("=========================================================\n\r");
	printf("Menu: press a key to change the configuration.\n\r");
	printf("---------------------------------------------------------\n\r");
	tmp = (adcd.cfg.trigger_mode == TRIGGER_MODE_SOFTWARE) ? 'X' : ' ';
	printf("[%c] 0: Set ADC trigger mode: Software.\n\r", tmp);
	tmp = (adcd.cfg.trigger_mode == TRIGGER_MODE_ADTRG) ? 'X' : ' ';
	printf("[%c] 1: Set ADC trigger mode: ADTRG.\n\r", tmp);
#ifdef ADC_TRIG_TIOA0
	tmp = (adcd.cfg.trigger_mode == TRIGGER_MODE_TIOA0) ? 'X' : ' ';
	printf("[%c] 2: Set ADC trigger mode: Timer TIOA.\n\r", tmp);
#endif /* ADC_TRIG_TIOA0 */
	tmp = (adcd.cfg.trigger_mode == TRIGGER_MODE_ADC_TIMER) ? 'X' : ' ';
	printf("[%c] 3: Set ADC trigger mode: ADC Internal Timer.\n\r", tmp);
	tmp = (adcd.cfg.sequence_enabled ) ? 'E' : 'D';
	printf("[%c] S: Enable/Disable sequencer.\n\r", tmp);
	tmp = (adcd.cfg.dma_enabled) ? 'E' : 'D';
	printf("[%c] D: Enable/Disable to tranfer with DMA.\n\r", tmp);
	tmp = (adcd.cfg.power_save_enabled) ? 'E' : 'D';
	printf("[%c] P: Enable/Disable ADC power save mode.\n\r", tmp);
	printf("=========================================================\n\r");
}

static void console_handler(uint8_t key)
{
	uint32_t i;

	switch (key) {
	case '0' :
		adcd.cfg.trigger_mode = TRIGGER_MODE_SOFTWARE;
		break;
	case '1' :
		adcd.cfg.trigger_mode = TRIGGER_MODE_ADTRG;
		break;
#ifdef ADC_TRIG_TIOA0
	case '2' :
		adcd.cfg.trigger_mode = TRIGGER_MODE_TIOA0;
		break;
#endif /* ADC_TRIG_TIOA0 */
	case '3' :
		adcd.cfg.trigger_mode = TRIGGER_MODE_ADC_TIMER;
		break;

	case 's' :
	case 'S' :
		/* Enable/disable sequencer */
		if (adcd.cfg.sequence_enabled)
			adcd.cfg.sequence_enabled = 0;
		else
			adcd.cfg.sequence_enabled = 1;

		if (adcd.cfg.sequence_enabled) {
			/* channel 0 and channel 1 is repeated 2 times.*/
			adcd.cfg.chan_sequence[0] = 0;
			adcd.cfg.chan_sequence[1] = 0;
			adcd.cfg.chan_sequence[2] = 1;
			adcd.cfg.chan_sequence[3] = 1;
		} else {
			/* Set default sequence */
			adcd.cfg.chan_sequence[0] = 0;
			adcd.cfg.chan_sequence[1] = 1;
			adcd.cfg.chan_sequence[2] = 2;
			adcd.cfg.chan_sequence[3] = 3;
		}
		for (i = 0; i < NUM_CHANNELS; i++) {
			_data.channel[i] = i;
			_data.value[i] = 0;
		}
		break;
	case 'd' :
	case 'D' :
		if (adcd.cfg.dma_enabled)
			adcd.cfg.dma_enabled = 0;
		else
			adcd.cfg.dma_enabled = 1;
		break;
	case 'p' :
	case 'P' :
		if (adcd.cfg.power_save_enabled)
			adcd.cfg.power_save_enabled = 0;
		else
			adcd.cfg.power_save_enabled = 1;
		break;

	default :
		break;
	}
	_display_menu();
}

#ifdef ADC_TRIG_TIOA0
/**
 * \brief Configure to trigger ADC by TIOA output of timer.
 */
static void _configure_tc_trigger(void)
{
	uint32_t tcclks = 0;
	uint32_t ra, rc;

	pio_configure(&pin_tioa0, 1);
	/* Configure TC for a 10Hz frequency and trigger on RC compare. */
	pmc_configure_peripheral(ID_TC0, NULL, true);
	tcclks = tc_find_best_clock_source(TC0, 0, 10);
	tc_configure(TC0, 0, tcclks | TC_CMR_WAVE | TC_CMR_ACPA_SET 
				| TC_CMR_ACPC_CLEAR | TC_CMR_CPCTRG);
	rc = tc_get_available_freq(TC0, 0, tcclks) / 10;
	ra = 50 * rc / 100;
	tc_set_ra_rb_rc(TC0, 0, &ra, 0, &rc);
}

#endif /* ADC_TRIG_TIOA0 */

static int _adc_callback(void* args)
{
	int i, j, chan, value;

	for (i = 0; i < NUM_CHANNELS; ++i) {
		chan = ADC_CHANNEL_NUM_IN_LCDR(adc_buffer[i]);
		value = ADC_LAST_DATA_IN_LCDR(adc_buffer[i]);
		/* Store value to channel according to sequence table*/
		for (j = 0; j < NUM_CHANNELS; j++) {
			if ( _data.channel[j] == chan) {
				_data.value[j] = value;
				break;
			}
		}
	}
	adc_converted = true;

	return 0;
}

/**
 * \brief (Re)init config ADC.
 *
 */
static void _adc_start_transfer(void)
{
	struct _callback _cb;

	if (adcd.cfg.trigger_mode == TRIGGER_MODE_SOFTWARE)
		adcd.cfg.trigger_edge = TRIGGER_NO;
	else if (adcd.cfg.trigger_mode == TRIGGER_MODE_ADTRG)
		adcd.cfg.trigger_edge = TRIGGER_EXT_TRIG_ANY;
#ifdef ADC_TRIG_TIOA0
	else if (adcd.cfg.trigger_mode == TRIGGER_MODE_TIOA0)
		adcd.cfg.trigger_edge = TRIGGER_EXT_TRIG_RISE;
#endif
	else if (adcd.cfg.trigger_mode == TRIGGER_MODE_ADC_TIMER)
		adcd.cfg.trigger_edge = TRIGGER_PERIOD;

#ifdef ADC_TRIG_TIOA0
	tc_stop(TC0, 0);
	if (adcd.cfg.trigger_mode == TRIGGER_MODE_TIOA0)
		/* Start the Timer */
		tc_start(TC0, 0);
#endif
	struct _buffer buf = {
		.data = (uint8_t*)adc_buffer,
		.size = NUM_CHANNELS,
	};
	callback_set(&_cb, _adc_callback, &adcd);
	adcd_transfer(&adcd, &buf, &_cb);

	while (adcd_is_busy(&adcd));

}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief adc_adc12 Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t i;

	/* Configure console interrupts */
	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	/* Output example information */
	console_example_info("ADC Example");

	/* Configure trigger pins */
	pio_configure(&pin_trig, 1);

	pio_clear(&pin_trig);
	pio_configure(pin_adtrg, ARRAY_SIZE(pin_adtrg));

	/* Set defaut ADC test mode */
	adcd.cfg.trigger_mode = TRIGGER_MODE_SOFTWARE;
	adcd.cfg.trigger_edge = TRIGGER_NO;

	adcd.cfg.dma_enabled = 0;
	adcd.cfg.ferq = ADC_FREQ;

	/* Set default sequence */
	adcd.cfg.chan_sequence[0] = 0;
	adcd.cfg.chan_sequence[1] = 1;
	adcd.cfg.chan_sequence[2] = 2;
	adcd.cfg.chan_sequence[3] = 3;

	/* Initialize ADC clock */
	adcd_initialize(&adcd);

	/* Launch first timeout */
	struct _timeout timeout;
	timer_start_timeout(&timeout, 500);
#ifdef ADC_TRIG_TIOA0
	_configure_tc_trigger();
#endif

	/* Init channel number and reset value */
	for (i = 0; i < NUM_CHANNELS; i++) {
		adcd.cfg.channel_used[i] = adc_channel_used[i];
		_data.channel[i] = adcd.cfg.chan_sequence[i];
		_data.value[i] = 0;
	}

	_adc_start_transfer();

	_display_menu();

	while (1)
	{
		/* ADC software trigger per 100ms */
		if (adcd.cfg.trigger_mode == TRIGGER_MODE_SOFTWARE) {
			if (timer_timeout_reached(&timeout)) {
				adc_start_conversion();
				timer_start_timeout(&timeout, 500);
				led_toggle(LED_RED);
			}
		}
		if (adcd.cfg.trigger_mode == TRIGGER_MODE_ADTRG) {
			msleep(500);
			if (pio_get(&pin_trig)) {
				led_clear(LED_RED);
				pio_clear(&pin_trig);
			} else {
				pio_set(&pin_trig);
				led_set(LED_RED);
			}
		}
		/* Check if ADC sample is done */
		if (adc_converted) {
			printf("Count: %08d ", count++);
			for (i = 0; i < NUM_CHANNELS; ++i) {
				printf(" CH%02d: %04d mV ",
					(int)(_data.channel[adcd.cfg.chan_sequence[i]]),
					(int)(_data.value[adcd.cfg.chan_sequence[i]]
					* BOARD_ADC_VREF / DIGITAL_MAX));
			}
			printf("\r");
			adc_converted = false;
			_adc_start_transfer();
		}
	}
}
