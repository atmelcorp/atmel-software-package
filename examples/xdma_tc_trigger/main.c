/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2021, Atmel Corporation
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
 * \page xdma_tc_trigger DMA trigger with TC compare counter and external trigger Example
 *
 * \section Purpose
 *
 * This example indicates how to use DMA trigger with TC compare counter and external trigger.
 *
 * \section Requirements
 *
 * This package can be used with SAM9X60 targets.
 *
 * \section Descriptions
 *
 * This example shows how to configure DMA with TC conpare counter trigger.
 * In this trigger mode, it supports Memory-to-Peripheral and Memory-to-Memory transfer operations, 
 * and chunk size is programmable as well.
 *
 * \section Usage
 *
 * -# Compile the application and connect the DBGU port of the evaluation board
 *    to the computer.
 * -# Open and configure a terminal application on PC
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Download the program inside the evaluation board and run it. Please refer to
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# Upon startup, the application will output the following line on the DBGU:
 *    \code
 *     -- DMA trigger with TC compare example --
 *     -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * -# Choose the item in the following menu to test.
 *    \code
 *     Menu :
 *     ------
 *       Output waveform property:
 *       0: Set Frequency =  4 Hz, Duty Cycle = 30%
 *       1: Set Frequency =  8 Hz, Duty Cycle = 50%
 *       2: Set Frequency =  15 Hz, Duty Cycle = 75%
 *       3: Set Frequency =  30 Hz, Duty Cycle = 80%
 *       4: Set Frequency =  50 Hz, Duty Cycle = 55%
 *       4: Set Frequency =  80 Hz, Duty Cycle = 20%
 *       -------------------------------------------
 *       m: dma memory to memory example
 *       [+|-]: change chunk size (CHK_1,CHK_2,CHK_4,CHK_8,CHK_16 data transfer)
 *       p: dma memory to peripheral example
 *       t: Start dma transfer
 *       e: dma external trigger latency measurement
 *       h: Display menu
 *     ------
 *    \endcode
 *
 * \section References
 * - xdma_tc_trigger/main.c
 */

/**
 * \file
 *
 * This file contains all the specific code for the DMA with TC trigger example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "board.h"
#include "callback.h"
#include "chip.h"
#include "compiler.h"
#include "timer.h"
#include "dma/dma.h"
#include "gpio/pio.h"
#include "irq/irq.h"
#include "mm/cache.h"
#include "serial/dbgu.h"
#include "peripherals/pmc.h"
#include "peripherals/tc.h"
#include "peripherals/tcd.h"
#include "serial/console.h"
#include "trace.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
#define DMA_MEM2MEM 			 0
#define DMA_MEM2PERI			 1
#define DMA_GPIO				 2

#define TRANSFER_SIZE			 64

/** Describes a possible Timer configuration as waveform mode */
struct _waveform {
	uint32_t min_timer_freq;
	uint32_t frequency;       /** Waveform frequency (in Hz). */
	uint32_t duty_cycle;      /** Duty cycle in percent (positive). */
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/** define Timer Counter descriptor for waveform */
static struct _tcd_desc tc_waveform = {
	.addr = TC0,
	.channel = 1,
};

/** TC waveform configurations (base on 66MHz peripheral clock)*/
static const struct _waveform waveforms[] = {
	{ 100000, 4, 30 },
	{ 100000, 8, 50 },
	{ 100000, 15, 75 },
	{ 100000, 30, 80 },
	{ 100000, 50, 55 },
	{ 100000, 80, 20 },
};

static uint64_t start, end;
/** DMA channel */
static struct _dma_channel* dma_chan_m2m; 
static struct _dma_channel* dma_chan_m2p;
static struct _dma_channel* dma_chan_gpio;

static uint8_t dma_transfer = DMA_MEM2MEM;
static uint8_t chunk_size = 0;
static uint8_t cfg = 0;
static uint8_t dmadone = 1;
/** PIOs for TC capture, waveform */
static const struct _pin pins_tc[] = {PIN_TC0_TIOA1};
CACHE_ALIGNED static uint8_t src_buffer[TRANSFER_SIZE];
CACHE_ALIGNED static uint8_t dst_buffer[TRANSFER_SIZE];
CACHE_ALIGNED static uint32_t src_wbuffer;
static uint8_t wave_idx;
struct _pin pin_trig = { PIO_GROUP_A, PIO_PA24, PIO_OUTPUT_0, PIO_DEFAULT };
struct _pin pin_out = { PIO_GROUP_A, PIO_PA3, PIO_OUTPUT_0, PIO_DEFAULT };
struct _pin pin_in = { PIO_GROUP_A, PIO_PA2, PIO_INPUT, PIO_IT_FALL_EDGE };

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Displays the user menu.
 */
static void _display_menu(void)
{
	uint32_t i;
	
	printf("\r\nMenu :\r\n");
	printf("------\r\n");
	printf("  Output waveform property:\r\n");
	for (i = 0; i < ARRAY_SIZE(waveforms); i++) {
		printf("  %u: Set Frequency = %4u Hz, Duty Cycle = %2u%%\r\n",
			(unsigned)i,
			(unsigned)waveforms[i].frequency,
			(unsigned)waveforms[i].duty_cycle);
	}
	printf("  -------------------------------------------\r\n");
	printf("  m: dma memory to memory example \r\n");
	printf("  [+|-]: change chunk size (CHK_1,CHK_2,CHK_4,CHK_8,CHK_16 data transfer) \r\n");
	printf("  p: dma memory to DBGU example \r\n");
	printf("  t: Start dma transfer \r\n");
	printf("  e: dma external trigger latency measurement\r\n");
	printf("  h: Display menu \r\n");
	printf("  ------\r\n\r\n");
}

/**
 * \brief Configure a TC channel as waveform operating mode.
 */
static void _tc_waveform_initialize(uint8_t waveform_idx)
{
	uint32_t frequency;

	printf("* Configure TC: channel %d: waveform generator mode\r\n", tc_waveform.channel);
	frequency = tcd_configure_waveform(&tc_waveform,
					   waveforms[waveform_idx].min_timer_freq,
					   waveforms[waveform_idx].frequency,
					   waveforms[waveform_idx].duty_cycle * 10);

	printf("  - Duty Cycle = %2d%%\r\n",(int)waveforms[waveform_idx].duty_cycle);
	printf("  - Configured frequency = %dHz\r\n", (int)frequency);
	printf("  - Period = %dms\r\n", (1000 / (int)waveforms[waveform_idx].frequency));
	tcd_start(&tc_waveform, NULL);
}

/**
 * \brief DMA callback.
 */
static int _dma_mm_callback(void* arg, void* arg2)
{
	end = timer_get_tick();
	printf("dump destination memory \n\r");
	cache_invalidate_region(dst_buffer, TRANSFER_SIZE);
	for(int i = 0; i < TRANSFER_SIZE; i++)
		printf("%d ", dst_buffer[i]);
	printf("\n\r");
	printf("\n\r%d(ms) elapsed!\r\n", (unsigned)(end - start));
	cfg = 0;
	return 0;
}

/**
 * \brief DMA callback.
 */
static int _dma_mp_callback(void* arg, void* arg2)
{
	end = timer_get_tick();
	printf("\n\r%d(ms) elapsed!\r\n", (unsigned)(end - start));
	cfg = 0;
	dmadone = 1;
	pio_clear(&pin_trig);
	return 0;
}

/**
 * \brief DMA callback.
 */
static int _dma_gpio_callback(void* arg, void* arg2)
{
	dmadone = 1;
	pio_clear(&pin_trig);
	return 0;
}

/**
 * \brief DMA configuration for memory-to-peripheral with TC compare counter trigger or external trigger enabled.
 */
void _dma_configure(struct _dma_channel* dma, uint32_t trigger, void *srcAddr, void *destAddr, uint32_t size)
{
	struct _dma_cfg cfg_dma;
	struct _dma_transfer_cfg tranfer_cfg;
	struct _callback _cb;

	if(dma_transfer == DMA_MEM2PERI) {
		cfg_dma.incr_saddr = true;
		cfg_dma.incr_daddr = false;
		cfg_dma.loop = false;
		cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
		cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;
		callback_set(&_cb, _dma_mp_callback, 0);
	} 

	if(dma_transfer == DMA_MEM2MEM) {
		cfg_dma.incr_saddr = true;
		cfg_dma.incr_daddr = true;
		cfg_dma.loop = false;
		cfg_dma.data_width = DMA_DATA_WIDTH_BYTE;
		cfg_dma.chunk_size = DMA_CHUNK_SIZE_1 + chunk_size;
		callback_set(&_cb, _dma_mm_callback, 0);
	}

	if(dma_transfer == DMA_GPIO) {
		cfg_dma.incr_saddr = true;
		cfg_dma.incr_daddr = false;
		cfg_dma.loop = false;
		cfg_dma.data_width = DMA_DATA_WIDTH_WORD;
		cfg_dma.chunk_size = DMA_CHUNK_SIZE_1;
		callback_set(&_cb, _dma_gpio_callback, 0);
	}

	tranfer_cfg.saddr = srcAddr;
	tranfer_cfg.daddr = destAddr;
	tranfer_cfg.len = size;
	dma_reset_channel(dma);
	dma_configure_transfer(dma, &cfg_dma, &tranfer_cfg, 1);
	xdmacd_set_hw_request(dma, trigger);
	dma_set_callback(dma, &_cb);
	cache_clean_region(tranfer_cfg.saddr, tranfer_cfg.len);
}


static void pio_handler(uint32_t group, uint32_t status, void* user_arg)
{
	/* unused */
	(void)group;
	(void)user_arg;
	if (group == pin_in.group && (status & pin_in.mask)) {
		pio_clear(&pin_out);
	}
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief xdma_tc_trigger Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uint8_t key;
	uint32_t i;
	
	/* Output example information */
	console_example_info("DMA with TC trigger example");

	/* Configure PIO Pins for TC waveform */
	pio_configure(pins_tc, ARRAY_SIZE(pins_tc));
	pio_configure(&pin_trig, 1);
	pio_configure(&pin_in, 1);
	pio_configure(&pin_out, 1);
	pio_clear(&pin_out);

	pio_add_handler_to_group(pin_in.group, pin_in.mask, pio_handler, NULL);
	/* Enable interrupts */
	pio_enable_it(&pin_in);

	_tc_waveform_initialize(0);

	/* Allocate a DMA channel. */
	dma_chan_m2m = dma_allocate_channel(DMA_PERIPH_MEMORY, DMA_PERIPH_MEMORY);
	dma_chan_m2p = dma_allocate_channel(DMA_PERIPH_MEMORY, ID_DBGU);
	dma_chan_gpio = dma_allocate_channel(DMA_PERIPH_MEMORY, DMA_PERIPH_MEMORY);

	_display_menu();
	while (1) {
		
		key = console_get_char();
		switch (key) {
		case 'H':
		case 'h':
			_display_menu();
			break;
		case 'p':
		case 'P':
			if (dma_transfer == DMA_GPIO) {
				tcd_stop(&tc_waveform);
				_tc_waveform_initialize(0);
			}
			dma_transfer = DMA_MEM2PERI;
			chunk_size = 0;
			for(i = 0; i < TRANSFER_SIZE; i++)
				src_buffer[i] = '0' + (i % 10);
			printf("DMA reads data from memory and writes to destination peripheral\r\n");
			_dma_configure(dma_chan_m2p, ID_TC1_CPA, src_buffer, (void *)&DBGU->DBGU_THR, TRANSFER_SIZE);
			printf("Estimate: %dms(trigger period per tranfer) x %d(size) / CHK_%d = %d ms\n\r", 
					(1000 / (int)waveforms[wave_idx].frequency),
					TRANSFER_SIZE,
					1 << chunk_size,
					((1000 / (int)waveforms[wave_idx].frequency) * TRANSFER_SIZE)/ (1 << chunk_size));
			cfg = 1;
			break;
		case 'm':
		case 'M':
			if (dma_transfer == DMA_GPIO) {
				tcd_stop(&tc_waveform);
				_tc_waveform_initialize(0);
			}
			dma_transfer = DMA_MEM2MEM;
			for(i = 0; i < TRANSFER_SIZE; i++) {
				src_buffer[i] = i;
				dst_buffer[i] = 0;
			}
			_dma_configure(dma_chan_m2m, ID_TC1_CPA, src_buffer, dst_buffer, TRANSFER_SIZE);
			printf("DMA reads data from source memory and writes to destination memory\r\n");
			printf("Estimate: %dms(trigger period per tranfer) x %d(size) / CHK_%d = %d ms\n\r", 
					(1000 / (int)waveforms[wave_idx].frequency),
					TRANSFER_SIZE,
					1 << chunk_size,
					((1000 / (int)waveforms[wave_idx].frequency) * TRANSFER_SIZE)/ (1 << chunk_size));
			cfg = 1;
			break;

		case 't':
		case 'T':
			if (!cfg) {
				printf("Config DMA mode first\r\n");
				continue;
			}
			printf("Start DMA transfer...\r\n");
			start = timer_get_tick();
			if (dma_transfer == DMA_MEM2MEM) {
				dma_start_transfer(dma_chan_m2m);
			} else {
				dma_start_transfer(dma_chan_m2p);
			}
			break;
		case '+':
			if (dma_transfer == DMA_MEM2PERI)
				continue;
			chunk_size++;
			if (chunk_size > 4) 
				chunk_size = 0;
			printf("CHK_%d\n\r",1 << chunk_size);
			cfg = 0;
			break;
		case '-':
			if (dma_transfer == DMA_MEM2PERI)
				continue;
			if (chunk_size == 0)
				chunk_size = 4;
			else 
				chunk_size--;
			printf("CHK_%d\n\r",1 << chunk_size);
			cfg = 0;
			break;
		case 'e':
		case 'E':
			if (dma_transfer != DMA_GPIO) {
				tcd_stop(&tc_waveform);
				tcd_waveform_enable_exteral_trigger(&tc_waveform);
				tcd_start(&tc_waveform, NULL);
				dma_transfer = DMA_GPIO;
			}
			src_wbuffer = pin_out.mask;
			printf("Start DMA transfer with external trigger, please measure signal...\r\n");
			printf("Press any key to stop...\r\n");
			for(;;){
				if (dmadone){
					dmadone = 0;
					_dma_configure(dma_chan_gpio, ID_TC1_EXT, &src_wbuffer, (void *)&PIOA->PIO_SODR, 1);
					dma_start_transfer(dma_chan_gpio);
					pio_set(&pin_trig);
				}
				if (dbgu_is_rx_ready(DBGU)) {
					tcd_stop(&tc_waveform);
					break;
				}
			}
			dma_transfer = DMA_MEM2MEM;
			_display_menu();
			break;
		default:
			/* Set waveform configuration #n */
			if ((key >= '0') && (key <= ('0' + ARRAY_SIZE(waveforms) - 1))) {
				_tc_waveform_initialize(key - '0');
				wave_idx = key - '0';
				 cfg = 0;
			}
			break;
		}
	}
}
