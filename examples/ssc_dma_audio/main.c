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
 * \page ssc_dma_audio SSC with DMA Audio Example
 *
 * \section Purpose
 *
 * This example uses the Synchronous Serial Controller (SSC) of an SAMA5D4x
 * microcontroller to output an audio stream through the on-board WM8904 CODEC.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5d4-EK with external
 * codec WM8904 components.
 *
 * \section Description
 * This program plays a WAV file from PC via Line-In. The audio stream is
 * sent through the SSC interface connected to the on-board WM8904, enabling
 * the sound to be audible using a pair of headphones.
 *
 * \section Usage
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a> application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>, depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the following text should appear:
 *    \code
 *     -- SSC DMA Audio Example xxx --
 *      -- SAMxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *    \endcode
 * The user can then choose any of the available options to perform the described action.
 *
 * \section References
 * - ssc_dma_audio/main.c
 * - ssc.c
 * - twi.c
 * - twid.c
 * - dma.c
 */

/**
 * \file
 *
 * This file contains all the specific code for the ssc audio example.
 */


/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"
#include "timer.h"

#include "misc/console.h"
#include "misc/led.h"

#include "misc/cache.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/dma.h"
#include "peripherals/ssc.h"
#include "peripherals/twi.h"
#include "peripherals/twid.h"
#include "peripherals/pmc.h"

#include "audio/wm8904.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>


/*----------------------------------------------------------------------------
 *        Local macros
 *----------------------------------------------------------------------------*/

#define min( a, b ) (((a) < (b)) ? (a) : (b))

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** TWI clock */
#define TWI_CLOCK               (400000)

/** Wav feature. */
#define SAMPLE_RATE             (48000)
#define SLOT_BY_FRAME           (1)
#define BITS_BY_SLOT            (16)

/** DMA Descriptor */
#define TOTAL_BUFFERS            10

#define DMA_TRANSFER_LEN    (0xFFFE)

#define AUDIO_BUFFER_LEN    TOTAL_BUFFERS * DMA_TRANSFER_LEN * (BITS_BY_SLOT / 8)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* Audio buffer */
CACHE_ALIGNED_DDR uint16_t audio_buffer[AUDIO_BUFFER_LEN];

/** List of pins to configure. */
static const struct _pin pins_twi[] = PINS_TWI0;
static const struct _pin pins_clk[] = PIN_PCK2_ALT1; /* DAC Master Clock */

/* Global DMA driver for all transfer */

/** DMA channel for RX */
static struct dma_channel *ssc_dma_rx_channel;
/** DMA channel for TX */
static struct dma_channel *ssc_dma_tx_channel;

CACHE_ALIGNED struct dma_xfer_item dma_write_link_list[TOTAL_BUFFERS];
CACHE_ALIGNED struct dma_xfer_item dma_read_link_list[TOTAL_BUFFERS];

/** Twi instance*/
static struct _twi_desc wm8904_twid = {
	.addr = TWI0,
	.freq = TWI_CLOCK,
	.transfert_mode = TWID_MODE_POLLING
};

/** SSC instance*/
static struct _ssc_desc ssc_dev_desc = {
	.addr = SSC0,
	.bit_rate = 0,
	.sample_rate = SAMPLE_RATE,
	.slot_num = SLOT_BY_FRAME,
	.slot_length = BITS_BY_SLOT,
	.rx_auto_cfg = true,
	.tx_auto_cfg = true,
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Display main menu.
 */
static void _display_menu(void)
{
	printf("\n\r");
	printf("Insert Line-in cable with PC Headphone output\n\r");
	printf("m -> Mute the play sound\n\r");
	printf("u -> Unmute the play sound\n\r");
	printf("+ -> Increase the volume (volume increased by 3dB)\n\r");
	printf("- -> Decrease the volume (volume reduced by 3dB)\n\r");
	printf("=>");
}

/**
 * \brief DMA driver configuration
 */
static void dma_configure(void)
{
	/* Driver initialize */
	/* Allocate DMA channels for SSC */
	ssc_dma_tx_channel = dma_allocate_channel(DMA_PERIPH_MEMORY, ID_SSC0);
	ssc_dma_rx_channel = dma_allocate_channel(ID_SSC0, DMA_PERIPH_MEMORY);

	if (!ssc_dma_tx_channel || !ssc_dma_rx_channel) {
		printf("DMA channel allocation error\n\r");

		while(1);
	}
}

/**
 * \brief Play recording.
 */
static void play_recording(void)
{
	uint16_t* src;
	uint8_t i;
	struct dma_xfer_item_tmpl dma_cfg;

	src = audio_buffer;
	memset(audio_buffer, 0x00, sizeof(audio_buffer));

	for (i = 0; i < TOTAL_BUFFERS; i++) {
		dma_cfg.sa = (uint32_t *)&(ssc_dev_desc.addr->SSC_RHR);
		dma_cfg.da = (uint32_t *)(src);
		dma_cfg.upd_sa_per_data = 0;
		dma_cfg.upd_da_per_data = 1;
		dma_cfg.upd_sa_per_blk  = 0;
		dma_cfg.upd_da_per_blk  = 1;
		dma_cfg.data_width = DMA_DATA_WIDTH_HALF_WORD;
		dma_cfg.chunk_size = DMA_CHUNK_SIZE_1;
		dma_cfg.blk_size = DMA_TRANSFER_LEN;
		dma_prepare_item(ssc_dma_rx_channel, &dma_cfg, &dma_read_link_list[i]);
		if (i == (TOTAL_BUFFERS - 1))
			dma_link_item(ssc_dma_rx_channel, &dma_read_link_list[i], &dma_read_link_list[0]);
		else
			dma_link_item(ssc_dma_rx_channel, &dma_read_link_list[i], &dma_read_link_list[i + 1]);
		src += DMA_TRANSFER_LEN;
	}
	cache_clean_region(dma_read_link_list, sizeof(dma_read_link_list));
	dma_configure_sg_transfer(ssc_dma_rx_channel, &dma_cfg, dma_read_link_list);

	src = audio_buffer;
	for (i = 0; i < TOTAL_BUFFERS; i++) {
		dma_cfg.sa = (uint32_t *)(src);
		dma_cfg.da = (uint32_t *)&(ssc_dev_desc.addr->SSC_THR);
		dma_cfg.upd_sa_per_data = 1;
		dma_cfg.upd_da_per_data = 0;
		dma_cfg.upd_sa_per_blk  = 1;
		dma_cfg.upd_da_per_blk  = 0;
		dma_cfg.data_width = DMA_DATA_WIDTH_HALF_WORD;
		dma_cfg.chunk_size = DMA_CHUNK_SIZE_1;
		dma_cfg.blk_size = DMA_TRANSFER_LEN;
		dma_prepare_item(ssc_dma_tx_channel, &dma_cfg, &dma_write_link_list[i]);
		if (i == (TOTAL_BUFFERS - 1))
			dma_link_item(ssc_dma_tx_channel, &dma_write_link_list[i], &dma_write_link_list[0]);
		else
			dma_link_item(ssc_dma_tx_channel, &dma_write_link_list[i], &dma_write_link_list[i + 1]);
		src += DMA_TRANSFER_LEN;
	}

	cache_clean_region(dma_write_link_list, sizeof(dma_write_link_list));
	dma_configure_sg_transfer(ssc_dma_tx_channel, &dma_cfg, dma_write_link_list);

	dma_start_transfer(ssc_dma_rx_channel);
	ssc_enable_receiver(&ssc_dev_desc);

	timer_wait(300);

	/* Enable playback(SSC TX) */
	dma_start_transfer(ssc_dma_tx_channel);
	ssc_enable_transmitter(&ssc_dev_desc);

}

static void _set_volume(uint8_t vol)
{
	printf("Setting volume to %ddB\r\n", (signed)(vol-57));
	wm8904_set_left_volume(&wm8904_twid, WM8904_SLAVE_ADDRESS, vol);
	wm8904_set_right_volume(&wm8904_twid, WM8904_SLAVE_ADDRESS, vol);
}

/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Application entry point for tc_capture_waveform example.
 *
 * \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
	uint16_t data = 0;
	uint8_t vol = 30;
	uint8_t key;

	/* Output example information */
	console_example_info("SSC DMA Audio Example");

	/* Configure all pins */
	pio_configure(pins_twi, ARRAY_SIZE(pins_twi));
	pio_configure(pins_clk, ARRAY_SIZE(pins_clk));

	/* Configure SSC */
	ssc_configure(&ssc_dev_desc);
	ssc_disable_receiver(&ssc_dev_desc);
	ssc_disable_transmitter(&ssc_dev_desc);

	/* Configure DMA */
	dma_configure();

	/* Configure and enable the TWI (required for accessing the DAC) */
	twid_configure(&wm8904_twid);
	/* check that WM8904 is present */
	wm8904_write(&wm8904_twid, WM8904_SLAVE_ADDRESS, 22, 0);
	data = wm8904_read(&wm8904_twid, WM8904_SLAVE_ADDRESS, 0);

	if ( data != 0x8904) {
		printf("WM8904 not found!\n\r");
		while(1);
	}

	/* Initialize the audio DAC */
	wm8904_init(&wm8904_twid, WM8904_SLAVE_ADDRESS, PMC_MCKR_CSS_SLOW_CLK);

	/* Enable the DAC master clock */
	pmc_select_external_crystal();
	pmc_disable_pck(2);
	pmc_configure_pck(2, PMC_PCK_CSS_SLOW_CLK, 0);
	pmc_enable_pck(2);

	_set_volume(vol);
	play_recording();

	while(1) {
		_display_menu();
		key = console_get_char();
		printf("%c\r\n", key);
		if (key == '+') {
			if (vol < 63) {
				vol += 3;
				_set_volume(vol);
			} else {
				printf("Volume is already at max (+6dB)\r\n");
			}
		} else if (key == '-') {
			if (vol > 1) {
				vol -= 3;
				_set_volume(vol);
			} else {
				printf("Volume is already at min (-57dB)\r\n");
			}
		} else if (key == 'm') {
			wm8904_volume_mute(&wm8904_twid, WM8904_SLAVE_ADDRESS, true, true);
		} else if(key == 'u') {
			wm8904_volume_mute(&wm8904_twid, WM8904_SLAVE_ADDRESS, false, false);
		}
	};
}
