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
 * - xdmac.c
 * - xdmad.c
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

#include "cortex-a/mmu.h"
#include "cortex-a/cp15.h"

#include "misc/console.h"
#include "misc/led.h"

#include "peripherals/l2cc.h"
#include "peripherals/pio.h"
#include "peripherals/pit.h"
#include "peripherals/wdt.h"
#include "peripherals/xdmad.h"
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
#define TOTAL_BUFFERS            (10)

#define DMA_TRANSFER_LEN    (0xFFFF)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/* Audio buffer */
SECTION(".region_ddr")
ALIGNED(L1_CACHE_BYTES) uint16_t audio_buffer[TOTAL_BUFFERS * DMA_TRANSFER_LEN * (BITS_BY_SLOT / 8)];

/** List of pins to configure. */
static const struct _pin  pins_ssc[] = PINS_SSC_CODEC;
static const struct _pin  pins_twi[] = PINS_TWI0;
static const struct _pin  pins_pck2[] = PIN_PCK2_ALT1;

/** Global DMA driver for all transfer */
/** DMA channel for RX */
static struct _xdmad_channel *ssc_dma_rx_channel;
/** DMA channel for TX */
static struct _xdmad_channel *ssc_dma_tx_channel;

struct _xdmad_cfg xdmad_cfg;


ALIGNED(L1_CACHE_BYTES) 
static struct _xdmad_desc_view1 dma_write_link_list[TOTAL_BUFFERS];

ALIGNED(L1_CACHE_BYTES) 
static struct _xdmad_desc_view1 dma_read_link_list[TOTAL_BUFFERS];


/** Twi instance*/
struct _twi_desc wm8904_twid = {
	.addr = TWI0,
	.freq = TWI_CLOCK,
	.transfert_mode = TWID_MODE_POLLING
};

/** SSC instance*/
struct _ssc_desc ssc_dev = {
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
 * \brief DMA driver configuration
 */
static void dma_configure(void)
{
	/* Driver initialize */
	xdmad_initialize(false);
	/* Allocate DMA channels for SSC */
	ssc_dma_tx_channel = xdmad_allocate_channel(XDMAD_PERIPH_MEMORY, ID_SSC0);
	ssc_dma_rx_channel = xdmad_allocate_channel(ID_SSC0, XDMAD_PERIPH_MEMORY);

	if (!ssc_dma_tx_channel || !ssc_dma_rx_channel) {
		printf("xDMA channel allocation error\n\r");

		while(1);
	}

	xdmad_prepare_channel(ssc_dma_tx_channel);
	xdmad_prepare_channel(ssc_dma_rx_channel);
}


/**
 * \brief Play recording.
 */
static void play_recording(void)
{
	uint16_t* src;
	uint8_t i;
	uint32_t xdma_cndc;

	src = audio_buffer;
	memset(audio_buffer, 0x00, sizeof(audio_buffer));

	for (i = 0; i < TOTAL_BUFFERS; i++) {
		dma_read_link_list[i].ublock_size = XDMA_UBC_NVIEW_NDV1
											| XDMA_UBC_NDE_FETCH_EN
											| XDMA_UBC_NSEN_UPDATED
											| XDMAC_CUBC_UBLEN(DMA_TRANSFER_LEN);
		dma_read_link_list[i].src_addr  = (uint32_t *)&(ssc_dev.addr->SSC_RHR);
		dma_read_link_list[i].dest_addr = (uint32_t *)(src);

		if (i == (TOTAL_BUFFERS - 1))
			dma_read_link_list[i].next_desc = &dma_read_link_list[0];
		else
			dma_read_link_list[i].next_desc = &dma_read_link_list[i + 1];

		src += DMA_TRANSFER_LEN;
	}

	xdmad_cfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
								| XDMAC_CC_MBSIZE_SINGLE
								| XDMAC_CC_DSYNC_PER2MEM
								| XDMAC_CC_CSIZE_CHK_1
								| XDMAC_CC_DWIDTH_HALFWORD
								| XDMAC_CC_SIF_AHB_IF1
								| XDMAC_CC_DIF_AHB_IF0
								| XDMAC_CC_SAM_FIXED_AM
								| XDMAC_CC_DAM_INCREMENTED_AM;

	xdma_cndc = XDMAC_CNDC_NDVIEW_NDV1
				| XDMAC_CNDC_NDE_DSCR_FETCH_EN
				| XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED
				| XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED;

	l2cc_clean_region((uint32_t)dma_read_link_list, (uint32_t )dma_read_link_list 
							+ sizeof(dma_read_link_list));

	xdmad_configure_transfer(ssc_dma_rx_channel, &xdmad_cfg, xdma_cndc,
							&dma_read_link_list[0]);
	src = audio_buffer;

	for (i = 0; i < TOTAL_BUFFERS; i++) {
		dma_write_link_list[i].ublock_size = XDMA_UBC_NVIEW_NDV1
											| XDMA_UBC_NDE_FETCH_EN
											| XDMA_UBC_NSEN_UPDATED
											| XDMAC_CUBC_UBLEN(DMA_TRANSFER_LEN);

		dma_write_link_list[i].src_addr = (uint32_t *)(src);
		dma_write_link_list[i].dest_addr = (uint32_t *)&(ssc_dev.addr->SSC_THR);

		if (i == (TOTAL_BUFFERS - 1 ))
			dma_write_link_list[i].next_desc = &dma_write_link_list[0];
		else
			dma_write_link_list[i].next_desc = &dma_write_link_list[i + 1];

		src += DMA_TRANSFER_LEN;
	}

	xdmad_cfg.cfg.uint32_value = XDMAC_CC_TYPE_PER_TRAN
								| XDMAC_CC_MBSIZE_SINGLE
								| XDMAC_CC_DSYNC_MEM2PER
								| XDMAC_CC_CSIZE_CHK_1
								| XDMAC_CC_DWIDTH_HALFWORD
								| XDMAC_CC_SIF_AHB_IF0
								| XDMAC_CC_DIF_AHB_IF1
								| XDMAC_CC_SAM_INCREMENTED_AM
								| XDMAC_CC_DAM_FIXED_AM;

	xdma_cndc = XDMAC_CNDC_NDVIEW_NDV1
				| XDMAC_CNDC_NDE_DSCR_FETCH_EN
				| XDMAC_CNDC_NDSUP_SRC_PARAMS_UPDATED
				| XDMAC_CNDC_NDDUP_DST_PARAMS_UPDATED ;
	xdmad_configure_transfer(ssc_dma_tx_channel, &xdmad_cfg, xdma_cndc,
							&dma_write_link_list[0]);

	l2cc_clean_region((uint32_t)dma_write_link_list, (uint32_t)dma_write_link_list + sizeof(dma_write_link_list));
	xdmad_start_transfer(ssc_dma_rx_channel);
	ssc_enable_receiver(&ssc_dev);

	timer_wait(300);

	/* Enable playback(SSC TX) */
	xdmad_start_transfer(ssc_dma_tx_channel);
	ssc_enable_transmitter(&ssc_dev);

}


/*----------------------------------------------------------------------------
 *         Global functions
 *----------------------------------------------------------------------------*/
/**
 * \brief Application entry point for tc_capture_waveform example.
 *
 * \return Unused (ANSI-C compatibility).
 */
int main( void )
{
	uint16_t data = 0;
	/* Disable watchdog */
	wdt_disable();

	/* Configure console */
	board_cfg_console(0);

	/* Output example information */
	printf("-- SSC DMA Audio Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

	/* Configure all pins */
	pio_configure(pins_ssc, ARRAY_SIZE(pins_ssc));
	pio_configure(pins_twi, ARRAY_SIZE(pins_twi));
	pio_configure(pins_pck2, ARRAY_SIZE(pins_pck2));

	/* Configure SSC */
	ssc_configure(&ssc_dev);
	ssc_disable_receiver(&ssc_dev);
	ssc_disable_transmitter(&ssc_dev);

	/* Configure DMA */
	dma_configure();

	board_cfg_pmic();

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
	pmc_select_internal_crystal();
	pmc_disable_pck2();
	pmc_configure_pck2(PMC_MCKR_CSS_SLOW_CLK, 0);
	pmc_enable_pck2();

	printf("Insert Line-in cable with PC Headphone output\n\r");

	play_recording();

	while(1);
}
