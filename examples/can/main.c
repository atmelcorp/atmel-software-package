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

/**
 * \page can Controller Area Network with Flexible Data-rate.
 * An example using the MCAN peripheral of SAMA5D2x Microcontrollers.
 *
 * \section Purpose
 *
 * The Controller Area Network example will help new users get familiar
 * with the MCAN peripheral used in Atmel's SAMA5D2x microcontrollers.
 *
 * \section Requirements
 *
 * This package is compatible with the evaluation boards listed below:
 * - SAMA5D2-VB
 * - SAMA5D2-XULT
 *
 * \section Description
 *
 * The demonstration program transmits several different CAN messages. Since it
 * also enables the CAN loopback mode, the transmitted messages are reflected
 * back as received messages too.
 * Both standard CAN and CAN FD operation can be tested.
 *
 * \section Usage
 *
 * -# Build the program and download it inside the evaluation board. Please
 *    refer to the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *    SAM-BA User Guide</a>, the
 *    <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *    GNU-Based Software Development</a>
 *    application note or to the
 *    <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *    IAR EWARM User Guide</a>,
 *    depending on your chosen solution.
 * -# On the computer, open and configure a terminal application
 *    (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *   - 57600 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and chip used):
 *    \code
 *     -- Controller Area Network (CAN) Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     CAN menu:
 *     Press [c|f|s] to set CAN or CAN FD mode
 *     Press [l] to toggle the integrated MCAN loop-back on/off
 *        p: Send sample messages
 *        h: Display this menu
 *     \endcode
 * -# Input command according to the menu.
 *
 * \section References
 * - mcan/main.c
 * - mcan.h
 * - mcan.h
 */

/** \file
 *
 *  This file contains all the specific code for the CAN example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>

#include "board.h"
#include "chip.h"
#include "peripherals/mcan.h"
#include "peripherals/wdt.h"
#include "peripherals/pmc.h"
#include "peripherals/pio.h"
#include "peripherals/aic.h"

#include "misc/console.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/* size of our custom Rx and Tx Buffer Elements, in words */
#define RAM_BUF_SIZE                  (MCAN_RAM_BUF_HDR_SIZE + 64u / 4)

#define RAM_ARRAY_SIZE_FILT_STD       (8u)
#define RAM_ARRAY_SIZE_FILT_EXT       (8u)
#define RAM_FIFO_SIZE_RX0             (12u)
/* no Rx FIFO 1 in our Message RAM */
#define RAM_ARRAY_SIZE_RX             (4u)
/* no Tx Event FIFO in our Message RAM */
#define RAM_ARRAY_SIZE_TX             (4u)
#define RAM_FIFO_SIZE_TX              (4u)

/* size of our custom Message RAM, in words */
#define MSG_RAM_SIZE      ( \
      RAM_ARRAY_SIZE_FILT_STD * MCAN_RAM_FILT_STD_SIZE \
    + RAM_ARRAY_SIZE_FILT_EXT * MCAN_RAM_FILT_EXT_SIZE \
    + RAM_FIFO_SIZE_RX0 * RAM_BUF_SIZE \
    + RAM_ARRAY_SIZE_RX * RAM_BUF_SIZE \
    + RAM_ARRAY_SIZE_TX * RAM_BUF_SIZE \
    + RAM_FIFO_SIZE_TX * RAM_BUF_SIZE )

#define MSG_LEN_1_CAN     8
#define MSG_LEN_1_CAN_FD  64
#define MSG_LEN_2_CAN     7
#define MSG_LEN_2_CAN_FD  48
#define MSG_ID_2          (CAN_STD_MSG_ID | 0x444)
#define MSG_ID_2_MASK     0x7FCul     /* bits 0 & 1 are don't care */
#define RX_BUFFER_0       0
#define RX_BUFFER_1       1
#define FILTER_0          0
#define FILTER_1          1

struct frame_desc
{
	uint32_t id;
	uint8_t data[64];
	uint8_t len;
	uint8_t buf_idx;
};

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* Allocate the Message RAM from non-cached memory.
 * The Buffer Elements in the Message RAM are contiguous and not aligned on
 * cache lines. If caching was turned on, it would be necessary to explicitly
 * clean the data cache lines matching transmit buffers, and then invalidate the
 * data cache lines matching receive buffers. Since these sections overlap in
 * the cache, strong constraints would apply as soon as several transmit and
 * receive buffers were used concurrently.
 * An alternative solution: if spare Buffers Elements are available, they may be
 * used to separate otherwise conflicting, active Buffer Elements, and then
 * benefit from memory caching.
 */
SECTION(".region_ddr_nocache")
static uint32_t mcan_msg_ram[MSG_RAM_SIZE];

struct frame_desc samples[3] = {
	{
		.id = CAN_STD_MSG_ID | 0x555,
		.buf_idx = 0,
		.len = 1,
		.data = { 0x81 },
	},
	{
		.id = CAN_EXT_MSG_ID | 0x11111111,
		.buf_idx = 1,
		.len = MSG_LEN_1_CAN_FD,
		.data = { 0x55, 0x55, 0x55, 0x55, 0xff, 0x00, 0xff, 0x00,
		          0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
		          0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
		          0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
		          0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
		          0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8,
		          0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8,
		          0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
		},
	},
	{
		.id = MSG_ID_2,
		.len = MSG_LEN_2_CAN_FD,
		.data = { 0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
		          0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
		          0x17, 0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24,
		          0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31, 0x32,
		          0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x40,
		          0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
		},
	},
};

static struct mcan_set mcan;
static enum mcan_can_mode can_mode;
static bool loop_back, bus_off;
static volatile bool rx_ded_buffer_data = false;

uint8_t      * txMailbox0;
uint8_t      * txMailbox1;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Trace buffer contents in hex.
 */
static void print_buffer(uint32_t len, const uint8_t *data)
{
	const uint8_t * const data_nxt = data + len;

	for ( ; data < data_nxt; data++)
		printf(" %02x", *data);
	printf("\n\r");
}

/**
 * \brief Handler for interrupt line 1 of MCANx.
 */
static void handle_mcan_irq1(void)
{
	if (mcan_rx_array_data(&mcan)) {
		mcan_clear_rx_array_flag(&mcan);
		rx_ded_buffer_data = true;
	}
}

/**
 * \brief Transmit sample messages.
 */
static void send_message(void)
{
	/* Send standard ID from a dedicated buffer */
	/* Write data into CAN mailbox */
	memcpy(txMailbox0, samples[0].data, samples[0].len);
	/* Send data */
	mcan_send_tx_buffer(&mcan, samples[0].buf_idx);

	/* Send extended ID from a dedicated buffer */
	if (can_mode > MCAN_MODE_CAN)
		samples[1].len = MSG_LEN_1_CAN_FD;
	else
		samples[1].len = MSG_LEN_1_CAN;
	txMailbox1 = mcan_prepare_tx_buffer(&mcan, samples[1].buf_idx,
	    samples[1].id, samples[1].len);
	/* Write data into CAN mailbox */
	memcpy(txMailbox1, samples[1].data, samples[1].len);
	/* Send data */
	mcan_send_tx_buffer(&mcan, samples[1].buf_idx);

	/* Send from TX FIFO */
	if (can_mode > MCAN_MODE_CAN)
		samples[2].len = MSG_LEN_2_CAN_FD;
	else
		samples[2].len = MSG_LEN_2_CAN;
	samples[2].buf_idx = mcan_enqueue_outgoing_msg(&mcan, samples[2].id,
	    samples[2].len, samples[2].data);

	printf("-I- Sending messages from transmit buffers %u, %u and %u.\n\r",
	    samples[0].buf_idx, samples[1].buf_idx, samples[2].buf_idx);
}

/**
 * \brief Print potential MCAN events out.
 */
static void watch_mcan(void)
{
	uint8_t msg_data[64];
	struct mcan_msg_info msg = { .data = msg_data };
	struct frame_desc *sample = NULL;
	uint8_t fifo_entries;

	/* Expect TX'd message complete */
	if (mcan_is_tx_complete(&mcan)) {
		mcan_clear_tx_flag(&mcan);
		for (sample = samples; sample < samples + ARRAY_SIZE(samples);
		    sample++) {
			if (!mcan_is_buffer_sent(&mcan, sample->buf_idx))
				continue;
			printf("-I- Transmit buffer %u sent: ID %lx, data",
			    sample->buf_idx, mcan_get_id(sample->id));
			print_buffer(sample->len, sample->data);
		}
	}

	if (rx_ded_buffer_data) {
		/* FIXME race condition here */
		rx_ded_buffer_data = false;
		if (mcan_rx_buffer_data(&mcan, RX_BUFFER_0)) {
			msg.data_len = sizeof(msg_data);
			mcan_read_rx_buffer(&mcan, RX_BUFFER_0, &msg);
			printf("-I- Message in receive buffer 0: ID %lx"
			    ", data", mcan_get_id(msg.id));
			print_buffer(msg.data_len, msg.data);
		}
		if (mcan_rx_buffer_data(&mcan, RX_BUFFER_1)) {
			msg.data_len = sizeof(msg_data);
			mcan_read_rx_buffer(&mcan, RX_BUFFER_1, &msg);
			printf("-I- Message in receive buffer 1: ID %lx"
			    ", data", mcan_get_id(msg.id));
			print_buffer(msg.data_len, msg.data);
		}
	}

	/* Poll for new CAN messages in RX FIFO */
	do {
		msg.data_len = sizeof(msg_data);
		fifo_entries = mcan_dequeue_received_msg(&mcan, 0, &msg);
		if (fifo_entries > 0) {
			printf("-I- Message from receive FIFO 0: ID %lx"
			    ", data", mcan_get_id(msg.id));
			print_buffer(msg.data_len, msg.data);
		}
	} while (fifo_entries > 1);

	/* Warn if the MCAN is not in its Normal Operation state anymore */
	if (!bus_off && !mcan_is_enabled(&mcan)) {
		printf("-W- MCAN has gone Bus_Off.\n\r");
		/* Warn only once */
		bus_off = true;
	}
}

/**
 * \brief Display main menu.
 */
static void display_menu(void)
{
	uint8_t chk_box[3];

	printf("\n\rCAN menu:\n\r");
	printf("Press [c|f|s] to set CAN or CAN FD mode\n\r");
	chk_box[0] = (can_mode == MCAN_MODE_CAN) ? 'X' : ' ';
	chk_box[1] = (can_mode == MCAN_MODE_EXT_LEN_CONST_RATE) ? 'X' : ' ';
	chk_box[2] = (can_mode == MCAN_MODE_EXT_LEN_DUAL_RATE) ? 'X' : ' ';
	printf("   c: [%c] ISO 11898-1 CAN\n\r", chk_box[0]);
	printf("   f: [%c] ISO 11898-7 CAN FD, 64-byte data\n\r", chk_box[1]);
	printf("   s: [%c] ISO 11898-7 CAN FD, 64-byte data, 2 Mbps data bit"
	    " rate\n\r", chk_box[2]);
	printf("Press [l] to toggle the integrated MCAN loop-back on/off\n\r");
	chk_box[0] = loop_back ? 'X' : ' ';
	printf("   l: [%c] Integrated CANTX->CANRX loop-back\n\r", chk_box[0]);
	printf("   p: Send sample messages\n\r");
	printf("   h: Display this menu\n\r");
	printf("\n\r");
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief CAN Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	const struct _pin can_pins[] = CAN0_PINS;
	const struct mcan_config mcan_cfg = {
		.id = ID_CAN0_INT0,
		.regs = MCAN0,
		.msg_ram = mcan_msg_ram,

		.array_size_filt_std = RAM_ARRAY_SIZE_FILT_STD,
		.array_size_filt_ext = RAM_ARRAY_SIZE_FILT_EXT,
		.fifo_size_rx0 = RAM_FIFO_SIZE_RX0,
		.fifo_size_rx1 = 0,
		.array_size_rx = RAM_ARRAY_SIZE_RX,
		.fifo_size_tx_evt = 0,
		.array_size_tx = RAM_ARRAY_SIZE_TX,
		.fifo_size_tx = RAM_FIFO_SIZE_TX,

		.buf_size_rx_fifo0 = 64,
		.buf_size_rx_fifo1 = 0,
		.buf_size_rx = 64,
		.buf_size_tx = 64,

		.bit_rate = 500000,
		.quanta_before_sp = 1 + 2 + 12,
		.quanta_after_sp = 12,

		.bit_rate_fd = 2000000,
		.quanta_before_sp_fd = 1 + 2 + 5,
		.quanta_after_sp_fd = 5,

		.quanta_sync_jump = 4,
		.quanta_sync_jump_fd = 2,
	};
	uint32_t int_source, mcan_msg_ram_size = ARRAY_SIZE(mcan_msg_ram);
	uint8_t user_key;

	wdt_disable();

#ifndef VARIANT_DDRAM
	/* In this variant the program runs from SRAM, but still the MCAN Driver
	 * requires access to DDR SDRAM, since it allocates the MCAN Message RAM
	 * from it. */
	board_cfg_ddram();
#endif

	board_cfg_console();

	/* Output example information */
	printf("\r\n\r\n\r\n");
	printf("-- CAN Example " SOFTPACK_VERSION " --\n\r") ;
	printf("-- " BOARD_NAME "\n\r");
	printf("-- Compiled: " __DATE__ " " __TIME__ " --\n\r");

	/* The MCAN peripheral is clocked by both its Peripheral Clock
	 * and Generated Clock 3 (at least on SAMA5D2x). */
	/* Configure GCLK3 = <Master clock> divided by 1
	 * FIXME follow datasheet recommendation: configure GCLK3 = <UPLL clock>
	 * divided by 24, 12 or 6 */
	pmc_configure_gck(mcan_cfg.id, PMC_PCR_GCKCSS_MCK_CLK, 1 - 1);
	pmc_enable_gck(mcan_cfg.id);
	pmc_enable_peripheral(mcan_cfg.id);
	/* Configure peripheral PIO's (CANTX and CANRX) */
	pio_configure(can_pins, ARRAY_SIZE(can_pins));
	/* Enable peripheral interrupt */
	int_source = mcan_cfg.id == ID_CAN0_INT0 ? ID_CAN0_INT1 : ID_CAN1_INT1;
	aic_set_source_vector(int_source, handle_mcan_irq1);
	aic_enable(int_source);

	if (!mcan_configure_msg_ram(&mcan_cfg, &mcan_msg_ram_size))
		goto Error;
	if (mcan_msg_ram_size > ARRAY_SIZE(mcan_msg_ram)) {
		printf("-E- Message RAM too small. Please verify its configuration.\n\r");
		goto Error;
	}
	else if (mcan_msg_ram_size != ARRAY_SIZE(mcan_msg_ram))
		printf("-I- The Message RAM is larger than required.\n\r");

	/* Display menu */
	can_mode = MCAN_MODE_CAN;
	loop_back = true;
	display_menu();

	if (!mcan_initialize(&mcan, &mcan_cfg))
		goto Error;
	mcan_set_mode(&mcan, can_mode);
	mcan_init_loopback(&mcan);
	mcan_enable(&mcan);
	bus_off = false;
	mcan_enable_rx_array_flag(&mcan, 1);

	txMailbox0 = mcan_prepare_tx_buffer(&mcan, samples[0].buf_idx,
	    samples[0].id, samples[0].len);
	mcan_filter_single_id(&mcan, RX_BUFFER_0, FILTER_0, samples[0].id);
	mcan_filter_single_id(&mcan, RX_BUFFER_1, FILTER_0, samples[1].id);
	mcan_filter_id_mask(&mcan, 0, FILTER_1, samples[2].id, MSG_ID_2_MASK);

	while (true) {
		watch_mcan();
		if (!console_is_rx_ready())
			continue;
		user_key = tolower(console_get_char());
		switch (user_key) {
		case 'c':
		case 'f':
		case 's':
			can_mode = user_key == 'f' ? MCAN_MODE_EXT_LEN_CONST_RATE :
			          (user_key == 's' ? MCAN_MODE_EXT_LEN_DUAL_RATE :
			                             MCAN_MODE_CAN);
			mcan_disable(&mcan);
			mcan_reconfigure(&mcan);
			mcan_set_mode(&mcan, can_mode);
			mcan_enable(&mcan);
			bus_off = false;
			display_menu();
			break;
		case 'l':
			loop_back = loop_back ? false : true;
			mcan_disable(&mcan);
			if (loop_back)
				mcan_loopback_on(&mcan);
			else
				mcan_loopback_off(&mcan);
			mcan_enable(&mcan);
			bus_off = false;
			display_menu();
			break;
		case 'h':
			display_menu();
			break;
		case 'p':
			if (!mcan_is_enabled(&mcan)) {
				mcan_enable(&mcan);
				bus_off = false;
				if (!mcan_is_enabled(&mcan))
					printf("-E- Failed to re-enable MCAN.\n\r");
			}
			/* Demonstrate ID filtering */
			samples[2].id = MSG_ID_2
			    + ((samples[2].id - MSG_ID_2 + 1) & 0x007);
			/* Also, transmit each time different data. */
			samples[2].data[0]++;
			send_message();
			break;
		}
	}

Error:
	printf("-E- Fatal error encountered. Program halted.\n\r");
	while (true) ;

	/* This code is never reached */
}
