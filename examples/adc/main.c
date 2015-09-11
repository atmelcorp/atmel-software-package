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
 *  \page adc_adc10 ADC10 Example
 *
 *  \section Purpose
 *
 *  The adc10 example demonstrates how to use ADC peripheral with several modes.
 *
 *  \section Requirements
 *
 *  This package can be used with SAMA5D2-XPLAINED, SAMA5D4-EK and
 *  SAMA5D4-XULT. Refer to \ref adc_adc10_requirement for detail.
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
 *      -- ADC10 Example xxx --
 *      -- xxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      =========================================================
 *      Menu: press a key to change the configuration.
 *      ---------------------------------------------------------
 *      [X] 0: Set ADC trigger mode: Software.
 *      [ ] 1: Set ADC trigger mode: ADTRG.
 *      [ ] 2: Set ADC trigger mode: Timer TIOA.
 *      [E] D: Enable/Disable to tranfer with DMA.
 *      [D] S: Enable/Disable to use user sequence mode.
 *      [D] P: Enable/Disable ADC power save mode.
 *      [D] G: Enable/Disable to set gain=2 for potentiometer channel.
 *      [D] O: Enable/Disable offset for potentiometer channel.
 *          Q: Quit configuration and start ADC.
 *      =========================================================
 *     \endcode
 *  -# The application will output converted value to hyperterminal and display
 *     a menu for user to set different mode.
 *
 *  \section References
 *  - adc10/main.c
 *  - adc.h
 */

/** \file
 *
 *  This file contains all the specific code for the adc10 example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
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
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/*
 * We use one ADC channel for this example:
 *    ADC_CHANNEL_4  (potentiometer)
 *    ADC_CHANNEL_0 (no connection/or connection by user)
 *    ADC_CHANNEL_1 (no connection/or connection by user)
 *    ADC_CHANNEL_2 (no connection/or connection by user)
 *    ADC_CHANNEL_3 (no connection/or connection by user)
 */

/** Total number of ADC channels in use */
#define NUM_CHANNELS    (5)
/** ADC convention done mask */
#define ADC_DONE_MASK   ((1<<NUM_CHANNELS) - 1 )

/** ADC clock */
#define BOARD_ADC_FREQ (300000)

/** ADC VREF */
#define BOARD_ADC_VREF (3300)

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
};

/** ADC sample data */
struct _adc_sample
{
	int16_t value[NUM_CHANNELS];
	uint16_t done;
	uint8_t  channel[NUM_CHANNELS];
};

static uint16_t _dma_buffer[NUM_CHANNELS];
/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/** ADC sample data */
static struct _adc_sample _data;
/** ADC test mode */
static struct _adc_test_mode _test_mode;


struct _pin pins_adc[] = {PIN_AD0, PIN_AD1, PIN_AD2, PIN_AD3, PIN_AD4};

/* /\** Definition of ADTRG pin *\/ */
struct _pin pin_adtrg[] = {PIN_ADTRG};

mutex_t lock = 0;

/* /\** Trigger simulate pin: PD8 *\/ */
/* static Pin pinTrg = { PIO_PD8, PIOD, ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT }; */

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _start_dma(void);

static void _adc_dma_callback(struct _xdmad_channel *channel,
			      void *arg)
{
	l2cc_invalidate_region((uint32_t)_dma_buffer,
			       (uint32_t)_dma_buffer + sizeof(_dma_buffer));

	/* Only keep sample value, discard channel number */
	int i = 0, chan = 0;
	for (i = 0; i < ARRAY_SIZE(_dma_buffer); ++i) {
		chan = _dma_buffer[i] >> ADC_LCDR_CHNB_Pos;
		if (chan < NUM_CHANNELS) {
			_data.channel[chan] = (_dma_buffer[i] >> ADC_LCDR_CHNB_Pos);
			_data.value[chan] = _dma_buffer[i] & ADC_LCDR_LDATA_Msk;
		}
	}
	_data.done = ADC_DONE_MASK;

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
	status = adc_get_status();
	if ((status & ADC_ISR_EOC0) == ADC_ISR_EOC0) {
		_data.value[0] = adc_get_converted_data(0);
		_data.channel[0] = ADC_CHANNEL_0;
		_data.done |= 1;
	}
	if ((status & ADC_ISR_EOC1) == ADC_ISR_EOC1) {
		_data.value[1] = adc_get_converted_data(1);
		_data.channel[1] = ADC_CHANNEL_1;
		_data.done |= 2;
	}
	if ((status & ADC_ISR_EOC2) == ADC_ISR_EOC2) {
		_data.value[2] = adc_get_converted_data(2);
		_data.channel[2] = ADC_CHANNEL_2;
		_data.done |= 4;
	}
	if ((status & ADC_ISR_EOC3) == ADC_ISR_EOC3) {
		_data.value[3] = adc_get_converted_data(3);
		_data.channel[3] = ADC_CHANNEL_3;
		_data.done |= 8;
	}
	if ((status & ADC_ISR_EOC4) == ADC_ISR_EOC4) {
		_data.value[4] = adc_get_converted_data(4);
		_data.channel[4] = ADC_CHANNEL_4;
		_data.done |= 0x10;
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
	tmp = (_test_mode.dma_enabled) ? 'E' : 'D';
	printf("[%c] D: Enable/Disable to tranfer with DMA.\n\r", tmp);
	tmp = (_test_mode.sequence_enabled) ? 'E' : 'D';
	printf("[%c] S: Enable/Disable to use user sequence mode.\n\r", tmp);
	tmp = (_test_mode.power_save_enabled) ? 'E' : 'D';
	printf("[%c] P: Enable/Disable ADC power save mode.\n\r", tmp);
	printf("    Q: Quit configuration and start ADC.\n\r");
	printf("=========================================================\n\r");
}

static void console_handler(void)
{
	uint8_t key;
	if (!console_is_rx_ready())
		return;
	key = console_get_char();
	if (mutex_try_lock(&lock))
		return;
	aic_disable(ID_TC0);
	switch (key) {
	case '0' :
		/* Disable hardware trigger */
		adc_set_trigger(0);
		/* No trigger, only software trigger can start conversions */
		adc_set_trigger_mode(ADC_TRGR_TRGMOD_NO_TRIGGER);
		_test_mode.trigger_mode = TRIGGER_MODE_SOFTWARE;
		break;
	case '1' :
		adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG0);
		/* External Trigger Any Edge */
		adc_set_trigger_mode(ADC_TRGR_TRGMOD_EXT_TRIG_ANY);
		_test_mode.trigger_mode = TRIGGER_MODE_ADTRG;
		break;
	case '2' :
		adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG1);
		/* aic_enable(ID_TC0); */
		/* adc_set_trigger_mode(ADC_TRGR_TRGMOD_EXT_TRIG_ANY); */
		adc_set_trigger_mode(ADC_TRGR_TRGMOD_PERIOD_TRIG);
		adc_set_trigger_period(210);
		_test_mode.trigger_mode = TRIGGER_MODE_TIMER;
		break;
	case 'd' :
	case 'D' :
		if (_test_mode.dma_enabled) {
			aic_enable(ID_ADC);
			_test_mode.dma_enabled = 0;
		} else {
			aic_disable(ID_ADC);
			_start_dma();
			_test_mode.dma_enabled = 1;
		}
		break;
	case 's' :
	case 'S' :
		if (_test_mode.sequence_enabled)
		{
			_test_mode.sequence_enabled = 0;
		}
		else
		{
			_test_mode.sequence_enabled = 1;
		}
		break;
	case 'p' :
	case 'P' :
		if (_test_mode.power_save_enabled)
		{
			_test_mode.power_save_enabled = 0;
		}
		else
		{
			_test_mode.power_save_enabled = 1;
		}
		break;
	default :
		break;
	}
	_display_menu();
	mutex_free(&lock);
}

static void tc_handler(void)
{
	uint32_t i;

	/* Clear status bit to acknowledge interrupt */
	i = tc_get_status(TC0, 0);
	for (i = 0; i < NUM_CHANNELS; ++i) {
		_data.value[i] = adc_get_converted_data(i);
		_data.channel[i] = i;
		_data.done |= 1 << i;
	}
}

/**
 * \brief Configure to trigger ADC by TIOA output of timer.
 */
static void _configure_tc_trigger(void)
{
	/* Enable peripheral clock. */
	pmc_enable_peripheral(ID_TC0);

	/* Put the source vector */
	aic_set_source_vector(ID_TC0, tc_handler);
	aic_enable(ID_TC0);

	/* Configure TC for a 1Hz frequency and trigger on RC compare. */
	tc_trigger_on_freq(TC0, 0, 10);

	tc_enable_it(TC0, 0, TC_IER_CPCS);

	/* Set TIOA0 trigger */
	adc_set_trigger(ADC_MR_TRGSEL_ADC_TRIG1);
	/* External Trigger Any Edge */
	adc_set_trigger_mode(ADC_TRGR_TRGMOD_EXT_TRIG_ANY);

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
	int i = 0;

	/* Enable/disable sequencer */
	if (_test_mode.sequence_enabled) {
		/* Set user defined channel sequence */
		adc_set_sequence(ADC_SEQR1_USCH1(ADC_CHANNEL_4)
				 | ADC_SEQR1_USCH2(ADC_CHANNEL_3)
				 | ADC_SEQR1_USCH3(ADC_CHANNEL_2)
				 | ADC_SEQR1_USCH4(ADC_CHANNEL_1)
				 | ADC_SEQR1_USCH5(ADC_CHANNEL_0),
				 0);
		/* Enable sequencer */
		adc_set_sequence_mode(true);

		/* Enable channels */
		for (i = 0; i < NUM_CHANNELS; i++) {
			adc_enable_channel(i);
		}
		/* Update channel number */
		_data.channel[0] = ADC_CHANNEL_4;
		_data.channel[1] = ADC_CHANNEL_3;
		_data.channel[2] = ADC_CHANNEL_2;
		_data.channel[3] = ADC_CHANNEL_1;
		_data.channel[4] = ADC_CHANNEL_0;
	} else {
		/* Disable sequencer */
		adc_set_sequence_mode(false);

		/* Enable channels */
		for (i = 0; i < NUM_CHANNELS; ++i)
		{
			adc_enable_channel(i);
		}

		/* Update channel number */
		_data.channel[0] = ADC_CHANNEL_0;
		_data.channel[1] = ADC_CHANNEL_1;
		_data.channel[2] = ADC_CHANNEL_2;
		_data.channel[3] = ADC_CHANNEL_3;
		_data.channel[4] = ADC_CHANNEL_4;
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
	adc_enable_it(ADC_IER_EOC0 | ADC_IER_EOC1 | ADC_IER_EOC2
		      | ADC_IER_EOC3 | ADC_IER_EOC4);
	/* Set ADC irq handler */
	aic_set_source_vector(ID_ADC, adc_irq_handler);
	/* Enable ADC interrupt */

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
		break;

	case TRIGGER_MODE_TIMER :

		break;

	default :
		break;
	}
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief adc_adc10 Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	int i = 0;
	/* Disable watchdog */
	wdt_disable();

	//l2cc_configure(NULL);

#ifndef VARIANT_DDRAM
	board_cfg_ddram();
#endif

	/* Initialize console */
	console_configure(CONSOLE_BAUDRATE);

	/* Configure console interrupts */
	console_enable_interrupts(US_IER_RXRDY);
	aic_set_source_vector(CONSOLE_ID, console_handler);
	aic_enable(CONSOLE_ID);

	/* Output example information */
	printf("-- ADC10 Example " SOFTPACK_VERSION " --\n\r"
	       "-- " BOARD_NAME "\n\r"
	       "-- Compiled: "__DATE__ " at " __TIME__" --\n\r");

	pio_configure(pins_adc, ARRAY_SIZE(pins_adc));
	pio_configure(pin_adtrg, ARRAY_SIZE(pin_adtrg));

	xdmad_initialize(false);

	/* Set defaut ADC test mode */
	memset((void *)&_test_mode, 0, sizeof(_test_mode));
	_test_mode.trigger_mode = TRIGGER_MODE_SOFTWARE;
	_test_mode.dma_enabled = 1;
	_test_mode.sequence_enabled = 0;

	_display_menu();
	_initialize_adc();
	_configure_adc();
	_configure_tc_trigger();
	adc_start_conversion();
	printf("Press any key to display configuration menu.\n\r\n\r");
	struct _timeout timeout;
	timer_start_timeout(&timeout, 100);
	while (1)
	{
		/* ADC software trigger per 100ms */
		if (_test_mode.trigger_mode == TRIGGER_MODE_SOFTWARE) {
			if (timer_timeout_reached(&timeout) && !_data.done)
			{
				adc_start_conversion();
				timer_start_timeout(&timeout, 100);
			}
		}
		if (_test_mode.trigger_mode == TRIGGER_MODE_ADTRG) {
			if (pio_get_output_data_status(&pin_adtrg[0]))
				pio_clear(&pin_adtrg[0]);
			else
				pio_set(&pin_adtrg[0]);
		}
		/* Check if ADC sample is done */
		if (_data.done == ADC_DONE_MASK)
		{
			for (i = 0; i < NUM_CHANNELS; ++i)
			{
				printf(" CH%02d: %04d mV",
					(int)_data.channel[i],
					(int)(_data.value[i] * BOARD_ADC_VREF / 4096));
			}
			printf("\r");
			_data.done = 0;
		}
	}
}
