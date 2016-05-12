/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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
 *  \page adc_adc12 ADC12 Example
 *
 *  \section Purpose
 *
 *  The adc12 example demonstrates how to use ADC peripheral with several modes.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-XPLAINED, SAMA5D4-EK and
 *  SAMA5D4-XULT. Refer to \ref adc_adc12_requirement for detail.
 *  
 *  -# SAMA5D2-XPLAINED: Connect PB9 to PD31 (ADTRG)
 *  -# SAMA5D4-XPLAINED: Connect PE23 to PE31 (ADTRG)
 *  -# SAMA5D4-EK: Connect to PE23 to PE31 (ADTRG)
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

#include "board.h"
#include "chip.h"
#include "timer.h"
#include "mutex.h"

#include "peripherals/aic.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"

#include "peripherals/adc.h"
#include "peripherals/l2cc.h"
#include "peripherals/tc.h"
#include "component/component_tc.h"
#include "peripherals/xdmad.h"

#include "misc/led.h"
#include "misc/console.h"


#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** ADC clock */
#define BOARD_ADC_FREQ (300000)

/** ADC slected channels */
static uint8_t adc_channel_used[] =
{
	ADC_CHANNEL_3,
	ADC_CHANNEL_4,
	ADC_CHANNEL_0,
	ADC_CHANNEL_1,
	ADC_CHANNEL_2,
};

/** Total number of ADC channels in use */
#define NUM_CHANNELS    ARRAY_SIZE(adc_channel_used)

/** ADC convention done mask */
#define ADC_DONE_MASK   ((1<<NUM_CHANNELS) - 1 )

/** ADC VREF */
#define BOARD_ADC_VREF (3300)

/** MAXIMUM DIGITAL VALUE */
#define DIGITAL_MAX    (1 << 12)

/*----------------------------------------------------------------------------
 *        Local types
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
	TRIGGER_MODE_ADC_TIMER,
};

/** ADC sample data */
struct _adc_sample
{
	uint8_t channel[NUM_CHANNELS];
	int16_t value[NUM_CHANNELS];
	uint16_t done;
};

#define _DMA_BUFFER_NUM ROUND_UP_MULT(NUM_CHANNELS * sizeof(uint16_t), L1_CACHE_BYTES) / sizeof(uint16_t)
ALIGNED(L1_CACHE_BYTES)
static uint16_t _dma_buffer[_DMA_BUFFER_NUM];

bool modif_config = false;
unsigned count = 0;

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** ADC sample data */
static struct _adc_sample _data;

/** ADC test mode */
static struct _adc_test_mode _test_mode;

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

#else
#error Unsupported target...
#endif

mutex_t lock = 0;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _start_dma(void);

static void _adc_dma_callback(struct _xdmad_channel *channel, void *arg)
{
	l2cc_invalidate_region((uint32_t)_dma_buffer,
			       (uint32_t)_dma_buffer + sizeof(_dma_buffer));

	/* Only keep sample value, discard channel number */
	int i, j, chan, value;
	for (i = 0; i < ARRAY_SIZE(_dma_buffer); ++i) {
		chan = _dma_buffer[i] >> ADC_LCDR_CHNB_Pos;
		value = _dma_buffer[i] & ADC_LCDR_LDATA_Msk;

			/* Store value to channel according to sequence table*/
			for (j = 0; j < NUM_CHANNELS; j++) {
				if ( _data.channel[j] == chan) {
					_data.value[j] = value;
					_data.done |= 1 << i;
					break;
				}
			}
	}
	xdmad_free_channel(channel);
	if (_test_mode.dma_enabled)
		_start_dma();
}

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
		for (i=0; i < adc_num_channels(); i++) {
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

/**
 *  \brief Configure xDMA and start to transfer.
 */
static void _start_dma(void)
{
	/* Allocate a XDMA channel, Write accesses into SHA_IDATARx */
	struct _xdmad_channel* dma_channel =
	xdmad_allocate_channel(ID_ADC, XDMAD_PERIPH_MEMORY);
	xdmad_prepare_channel(dma_channel);
	struct _xdmad_cfg dma_cfg;
	memset(&dma_cfg, 0, sizeof(dma_cfg));
	dma_cfg.ublock_size = NUM_CHANNELS;
	dma_cfg.src_addr = (void*)&ADC->ADC_LCDR;
	dma_cfg.dest_addr = (void*)_dma_buffer;
	dma_cfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
		| XDMAC_CC_MEMSET_NORMAL_MODE
		| XDMAC_CC_CSIZE_CHK_1
		| XDMAC_CC_DWIDTH_HALFWORD
		| XDMAC_CC_SIF_AHB_IF1
		| XDMAC_CC_DIF_AHB_IF0
		| XDMAC_CC_SAM_FIXED_AM
		| XDMAC_CC_DAM_INCREMENTED_AM;
	dma_cfg.block_size = 0;
	xdmad_configure_transfer(dma_channel, &dma_cfg, 0, 0);
	xdmad_set_callback(dma_channel, _adc_dma_callback, NULL);
	xdmad_start_transfer(dma_channel);
}

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
	tmp = (_test_mode.trigger_mode == TRIGGER_MODE_SOFTWARE) ? 'X' : ' ';
	printf("[%c] 0: Set ADC trigger mode: Software.\n\r", tmp);
	tmp = (_test_mode.trigger_mode == TRIGGER_MODE_ADTRG) ? 'X' : ' ';
	printf("[%c] 1: Set ADC trigger mode: ADTRG.\n\r", tmp);
	tmp = (_test_mode.trigger_mode == TRIGGER_MODE_TIMER) ? 'X' : ' ';
	printf("[%c] 2: Set ADC trigger mode: Timer TIOA.\n\r", tmp);
	tmp = (_test_mode.trigger_mode == TRIGGER_MODE_ADC_TIMER) ? 'X' : ' ';
	printf("[%c] 3: Set ADC trigger mode: ADC Internal Timer.\n\r", tmp);
	tmp = (_test_mode.sequence_enabled ) ? 'E' : 'D';
	printf("[%c] S: Enable/Disable sequencer.\n\r", tmp);
	tmp = (_test_mode.dma_enabled) ? 'E' : 'D';
	printf("[%c] D: Enable/Disable to tranfer with DMA.\n\r", tmp);
	tmp = (_test_mode.power_save_enabled) ? 'E' : 'D';
	printf("[%c] P: Enable/Disable ADC power save mode.\n\r", tmp);
	printf("=========================================================\n\r");
}

static void console_handler(uint8_t key)
{
	if (mutex_try_lock(&lock))
		return;

	switch (key) {
	case '0' :
		_test_mode.trigger_mode = TRIGGER_MODE_SOFTWARE;
		break;
	case '1' :
		_test_mode.trigger_mode = TRIGGER_MODE_ADTRG;
		break;
	case '2' :
		_test_mode.trigger_mode = TRIGGER_MODE_TIMER;
		break;
	case '3' :
		_test_mode.trigger_mode = TRIGGER_MODE_ADC_TIMER;
		break;

	case 's' :
	case 'S' :
		/* Enable/disable sequencer */
		if (_test_mode.sequence_enabled) _test_mode.sequence_enabled = 0;
		else _test_mode.sequence_enabled = 1;
		break;

	case 'd' :
	case 'D' :
		if (_test_mode.dma_enabled) _test_mode.dma_enabled = 0;
		else _test_mode.dma_enabled = 1;
		break;
	case 'p' :
	case 'P' :
		if (_test_mode.power_save_enabled) _test_mode.power_save_enabled = 0;
		else _test_mode.power_save_enabled = 1;
		break;

	default :
		break;
	}
	modif_config = true; /* indicate config ADC change */
	_display_menu();
	mutex_free(&lock);
}

/**
 * \brief Configure to trigger ADC by TIOA output of timer.
 */
static void _configure_tc_trigger(void)
{
	uint32_t div = 0;
	uint32_t tcclks = 0;
	uint32_t ra, rc;
	
	pio_configure(&pin_tioa0, 1);
	/* Enable peripheral clock. */
	pmc_enable_peripheral(ID_TC0);
	/* Configure TC for a 10Hz frequency and trigger on RC compare. */
	tc_find_mck_divisor(10, &div, &tcclks);
	tc_configure(TC0, 0, tcclks | TC_CMR_WAVE | TC_CMR_ACPA_SET | TC_CMR_ACPC_CLEAR | TC_CMR_CPCTRG);
	rc = tc_get_available_freq(TC0, tcclks) / 10;
	ra = 50 * rc / 100;
	tc_set_ra_rb_rc(TC0, 0, &ra, 0, &rc);
	/* Start the Timer */
	tc_start(TC0, 0);
}


static void _initialize_adc(void)
{
	/* Initialize ADC */
	adc_initialize();
	adc_set_ts_mode(0);
	/*
	 * Formula: ADCClock = MCK / ((PRESCAL+1) * 2)
	 * For example, MCK = 64MHZ, PRESCAL = 4, then:
	 *     ADCClock = 64 / ((4+1) * 2) = 6.4MHz;
	 */
	/* Set ADC clock */
	adc_set_clock(BOARD_ADC_FREQ);

	/* Formula:
	 *     Startup  Time = startup value / ADCClock
	 *     Transfer Time = (TRANSFER * 2 + 3) / ADCClock
	 *     Tracking Time = (TRACKTIM + 1) / ADCClock
	 *     Settling Time = settling value / ADCClock
	 * For example, ADC clock = 6MHz (166.7 ns)
	 *     Startup time = 512 / 6MHz = 85.3 us
	 *     Transfer Time = (1 * 2 + 3) / 6MHz = 833.3 ns
	 *     Tracking Time = (0 + 1) / 6MHz = 166.7 ns
	 *     Settling Time = 3 / 6MHz = 500 ns
	 */
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

	led_clear(LED_RED);
	led_clear(LED_BLUE);

	/* Init channel number and reset value */
	for (i = 0; i < NUM_CHANNELS; i++) {
		_data.channel[i] = adc_channel_used[i];
		_data.value[i] = 0;
	}

	/* Enable/disable sequencer */
	if (_test_mode.sequence_enabled) {
		/* Set user defined channel sequence */
		adc_set_sequence_by_list(adc_channel_used, NUM_CHANNELS);
		/* Enable sequencer */
		adc_set_sequence_mode(true);

	} else {
		adc_set_sequence(0, 0);
		/* Disable sequencer */
		adc_set_sequence_mode(false);
	}

	/* Enable channels, gain, single mode */
	for (i = 0; i < NUM_CHANNELS; i++) {
		adc_enable_channel(_data.channel[i]);
#ifdef CONFIG_HAVE_ADC_INPUT_OFFSET
		adc_disable_channel_differential_input(_data.channel[i]);
#endif
	}

	/* Set power save */
	if (_test_mode.power_save_enabled) {
		adc_set_sleep_mode(true);
	} else {
		adc_set_sleep_mode(false);
	}

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
			break;

	    case TRIGGER_MODE_ADTRG:
			pio_configure(pin_adtrg, ARRAY_SIZE(pin_adtrg));
			pio_configure(&pin_trig, 1);
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG0);
			adc_set_trigger_mode(ADC_TRGR_TRGMOD_EXT_TRIG_ANY);
			break;
			
		case TRIGGER_MODE_TIMER :
			/* Trigger timer*/
			/* Configure Timer TC0 */
			_configure_tc_trigger();
			adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG1);
			adc_set_trigger_mode(ADC_TRGR_TRGMOD_EXT_TRIG_RISE);
			break;

		case TRIGGER_MODE_ADC_TIMER :
			/* Trigger timer*/
			adc_set_trigger_mode(ADC_TRGR_TRGMOD_PERIOD_TRIG);
			adc_set_trigger_period(250);
			break;

	    default :
			break;
	}

	if (_test_mode.dma_enabled) {
		_start_dma();
	} else {
		aic_enable(ID_ADC);
	}
}

/**
 * \brief (Re)init config ADC.
 *
 */
static void _set_adc_configuration(void)
{
	aic_disable(ID_ADC);
	tc_stop(TC0, 0);
	led_set(LED_BLUE);
	_configure_adc();
	adc_start_conversion();
	modif_config = false;
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

	/* Disable watchdog */
	wdt_disable();

	/* Initialize console */
	board_cfg_console(0);
	console_clear_screen();
	console_reset_cursor();

	/* Configure console interrupts */
	console_set_rx_handler(console_handler);
	console_enable_rx_interrupt();

	/* Output example information */
	printf("-- ADC12 Example " SOFTPACK_VERSION " --\n\r"
	       "-- " BOARD_NAME "\n\r"
	       "-- Compiled: "__DATE__ " at " __TIME__" --\n\r");

	board_cfg_pmic();

	/* PIO configuration for LEDs */
	printf("Configure LED PIOs.\n\r");
	led_configure(LED_RED);
	led_configure(LED_BLUE);

	pio_configure(pin_adtrg, ARRAY_SIZE(pin_adtrg));
	xdmad_initialize(false);

	/* Set defaut ADC test mode */
	memset((void *)&_test_mode, 0, sizeof(_test_mode));
	_test_mode.trigger_mode = TRIGGER_MODE_SOFTWARE;
	_test_mode.dma_enabled = 0;
	_test_mode.sequence_enabled = 0;

	/* Initialize ADC clock */
	_initialize_adc();
	/* Init ADC config */
	_set_adc_configuration();

	/* Launch first timeout */
	struct _timeout timeout;
	timer_start_timeout(&timeout, 250);

	_display_menu();

	while (1)
	{
		/* ADC software trigger per 100ms */
		if (_test_mode.trigger_mode == TRIGGER_MODE_SOFTWARE) {
			if (timer_timeout_reached(&timeout) && !_data.done) {
				adc_start_conversion();
				timer_start_timeout(&timeout, 250);
				led_toggle(LED_RED);
			}
		}
		if (_test_mode.trigger_mode == TRIGGER_MODE_ADTRG) {
			timer_wait(250);
			if (pio_get(&pin_trig))
				pio_clear(&pin_trig);
			else
				pio_set(&pin_trig);
		}
		/* Check if ADC sample is done */
		if (_data.done) {
			printf("Count: %08d ", count++);
			for (i = 0; i < NUM_CHANNELS; ++i) {
				printf(" CH%02d: %04d mV ",
					(int)(_data.channel[i]),
					(int)(_data.value[i] * BOARD_ADC_VREF / DIGITAL_MAX));
			}
			printf("\r");
			_data.done = 0;
		}

		/* After console_handler, set configuration adc */
		if (modif_config) {
			_set_adc_configuration();
		}

	}
}
