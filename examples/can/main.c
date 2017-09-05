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
 * \page can Controller Area Network.
 * An example using the CAN/MCAN peripheral of SAMA5Dx Microcontrollers.
 *
 * \section Purpose
 *
 * The Controller Area Network example will help new users get familiar
 * with the CAN/MCAN peripheral used in Atmel's microcontrollers.
 *
 * \section Requirements
 *
 * This package is compatible with the evaluation boards listed below:
 * - SAM9X25-EK
 * - SAM9X35-EK
 * - SAMA5D2-VB
 * - SAMA5D3-EK
 * - SAMA5D2-XPLAINED
 * - SAMA5D27-SOM1-EK
 * - SAMA5D3-EK
 * - SAMA5D3-XPLAINED
 *
 * A FIELDBUS-SHIELD-XULT board is needed when there are no CAN transceivers on
 * the board.
 *
 * \section Description
 *
 * The demonstration program transmits several different CAN messages. The
 * transmitted messages can be received from the other CAN port with correct
 * CAN bus connected. In case of the loop back mode the transmitted messages
 * are reflected back as received messages too.
 *
 * Only standard CAN operation is supported with the CAN peripheral.
 * Both standard CAN and CAN FD operation can be tested with the MCAN peripheral.
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
 *   - 115200 bauds
 *   - 8 bits of data
 *   - No parity
 *   - 1 stop bit
 *   - No flow control
 * -# Start the application.
 * -# In the terminal window, the
 *    following text should appear (values depend on the board and chip used):
 *    \code
 *     -- Controller Area Network (CAN/MCAN) Example xxx --
 *     -- xxxxxx-xx
 *     -- Compiled: xxx xx xxxx xx:xx:xx --
 *
 *     CAN menu:
 *     Press [c|f|s] to set CAN or CAN FD mode
 *        c: [X] ISO 11898-1 CAN
 *        f: [ ] ISO 11898-7 CAN FD, 64-byte data
 *        s: [ ] ISO 11898-7 CAN FD, 64-byte data, 2 Mbps data bit rate
 *     Press [l] to toggle the integrated MCAN loop-back on/off
 *        l: [x] Integrated CANTX->CANRX loop-back
 *        p: Send sample messages
 *        r: Receive a specified message
 *        t: Send out a specified message
 *        h: Display this menu
 *     \endcode
 * -# Input command according to the menu.
 *
 * \section References
 * - can/main.c
 * - can-bus.h
 * - can.h
 * - mcan.h
 */

/** \file
 *
 *  This file contains all the specific code for the CAN example.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "trace.h"

#include "can/can-bus.h"
#include "serial/console.h"

#include <ctype.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

/** CAN operation timeout (ms) */
#define CAN_TO 500

#define MSG_LEN_1_CAN     8
#define MSG_LEN_1_CAN_FD  64
#define MSG_LEN_2_CAN     7
#define MSG_LEN_2_CAN_FD  48

enum _RX_BUFF_IDX {
	_RX_BUFF_SIMPLE,
	_RX_BUFF_DISCARD,
	_RX_BUFF_OVERWR,
	_RX_BUFF_CONSUMER,
	_RX_BUFF_CNT,
	_RX_BUFF_SIMPLE_EXT = _RX_BUFF_DISCARD,
	_RX_BUFF_SIMPLE_FIFO = _RX_BUFF_OVERWR,
};

#define PRINT_SPLIT do {printf("\r\n===========================\r\n");} while(0)
#define PRINT_PASS do {printf("-------- test PASSED\r\n");} while(0)
#define PRINT_FAIL do {printf("-------- test FAILED\r\n");} while(0)

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static uint8_t rx_buffers[_RX_BUFF_CNT][64];

static uint32_t id[] = {0x555, 0x11111111, 0x444};

static const uint8_t msg_0[] = {0x81};
static const uint8_t msg_1[] = {
				0x55, 0x55, 0x55, 0x55, 0xff, 0x00, 0xff, 0x00,
				0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
				0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38,
				0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58,
				0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88,
				0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8,
				0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8,
				0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7, 0xf8,
		};
static uint8_t msg_2[] = {
				0x00, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
				0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
				0x17, 0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24,
				0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31, 0x32,
				0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x40,
				0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48,
		};

static enum can_mode mode = CAN_MODE_CAN;
static bool loop_back;

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
	printf("\r\n");
}

static void test_message(uint8_t bus)
{
	uint8_t bus_rx = loop_back ? bus : ((0 == bus) ? 1 : 0);

	static const uint8_t msg1[] = {0x00, 0xFF, 0x11, 0x22};
	static const uint8_t msg2[] = {0x01, 0xFF, 0x11, 0x11};
	static const uint8_t msg3[] = {0x01, 0xFF, 0x22, 0x22, 0x01, 0xFF, 0x23, 0x45};
	static const uint8_t msg4[] = {0x02, 0xFF, 0x11, 0x11};
	static const uint8_t msg5[] = {0x02, 0xFF, 0x22, 0x22, 0x02, 0xFF, 0x23, 0x45};
	static const uint8_t msg6[] = {0xEF, 0x03};

	struct _buffer buf_rx_standard = {
			.data = rx_buffers[_RX_BUFF_SIMPLE],
			.size = sizeof(rx_buffers[_RX_BUFF_SIMPLE]),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_RX,
		};
	struct _buffer buf_rx_discard = {
			.data = rx_buffers[_RX_BUFF_DISCARD],
			.size = sizeof(rx_buffers[_RX_BUFF_DISCARD]),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_RX,
		};
	struct _buffer buf_rx_overwr = {
			.data = rx_buffers[_RX_BUFF_OVERWR],
			.size = sizeof(rx_buffers[_RX_BUFF_OVERWR]),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_RX_OVERWRITE,
		};
	struct _buffer buf_producer = {
			.data = (uint8_t*)msg6,
			.size = sizeof(msg6),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_PRODUCER,
		};


	PRINT_SPLIT;
	struct _buffer buf1 = {
			.data = (uint8_t*)msg1,
			.size = sizeof(msg1),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_TX,
		};
	can_bus_transfer(bus_rx, 0x31, 0x7FF, &buf_rx_standard, NULL);
	can_bus_transfer(bus, 0x31, 0, &buf1, NULL);
	if (can_bus_wait_transfer_done(&buf1, CAN_TO) == 0) {
		trace_error("CAN%d: Simple test TX error\r\n", bus);
	}

	struct _buffer buf20 = {
			.data = (uint8_t*)msg2,
			.size = sizeof(msg2),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_TX,
		};
	struct _buffer buf21 = {
			.data = (uint8_t*)msg3,
			.size = sizeof(msg3),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_TX,
		};
	can_bus_transfer(bus, 0x32, 0x7FF, &buf_rx_discard, NULL);
	can_bus_transfer(bus, 0x32, 0, &buf21, NULL);
	can_bus_transfer(bus, 0x32, 0, &buf20, NULL);
	if (!can_bus_wait_transfer_done(&buf21, CAN_TO)
		|| !can_bus_wait_transfer_done(&buf20, CAN_TO)) {
		trace_error("CAN%d: Discard test TX error\r\n", bus);
	}

	/* test buffer overwrite mode, currently not supported by MCAN */
	struct _buffer buf30 = {
			.data = (uint8_t*)msg4,
			.size = sizeof(msg4),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_TX,
		};
	struct _buffer buf31 = {
			.data = (uint8_t*)msg5,
			.size = sizeof(msg5),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_TX,
		};
	if (0 == can_bus_transfer(bus_rx, 0x40, 0x7FE, &buf_rx_overwr,  NULL)) {
		can_bus_transfer(bus, 0x40, 0, &buf30, NULL);
		can_bus_transfer(bus, 0x41, 0, &buf31, NULL);
		if (!can_bus_wait_transfer_done(&buf30, CAN_TO)
			|| !can_bus_wait_transfer_done(&buf31, CAN_TO)) {
			trace_error("CAN%d: Overwrite test TX error\r\n", bus);
		}
	}


	PRINT_SPLIT;
	if (buf_rx_standard.attr & CAND_BUF_ATTR_TRANSFER_DONE) {
		trace_info("CAN%d.1: Simple test data received\r\n", bus_rx);
		if (buf_rx_standard.size == sizeof(msg1)
			&& (0 == memcmp(buf_rx_standard.data, msg1, sizeof(msg1))))
			PRINT_PASS;
		else
			PRINT_FAIL;
	}

	if (buf_rx_discard.attr & CAND_BUF_ATTR_TRANSFER_DONE) {
		trace_info("CAN%d.2: discard test data received\r\n", bus_rx);
		if (buf_rx_discard.size == sizeof(msg3)
			&& (0 == memcmp(buf_rx_discard.data, msg3, sizeof(msg3))))
			PRINT_PASS;
		else
			PRINT_FAIL;
	}

	if (can_bus_wait_transfer_done(&buf_rx_overwr, CAN_TO)) {
		trace_info("CAN%d.3: overwrite test data received\r\n", bus_rx);
		if (buf_rx_overwr.size == sizeof(msg4)
			&& (0 == memcmp(buf_rx_overwr.data, msg4, sizeof(msg4))))
			PRINT_PASS;
		else
			PRINT_FAIL;
	}


	PRINT_SPLIT;
	/* test producer-consumer mode, currently not supported by MCAN */
	struct _buffer buf_consumer = {
			.data = rx_buffers[_RX_BUFF_CONSUMER],
			.size = sizeof(rx_buffers[_RX_BUFF_CONSUMER]),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_CONSUMER,
		};
	if (0 == can_bus_transfer(bus_rx, 0x34, 0, &buf_producer, NULL)) {
		can_bus_transfer(bus, 0x34, 0x7FF, &buf_consumer, NULL);
		if (!can_bus_wait_transfer_done(&buf_consumer, CAN_TO)) {
			trace_error("CAN%d: Ask for data fail\r\n", bus);
			return;
		}
		trace_info("- CAN%d.5: Remote requested data received\r\n", bus);
		if (buf_consumer.size == 2
			&& (0 == memcmp(buf_consumer.data, msg6, sizeof(msg6))))
			PRINT_PASS;
		else
			PRINT_FAIL;
	}
}

/**
 * \brief Transmit sample messages.
 */
static void send_message(uint8_t bus)
{
	struct _buffer *tx_buf;
	uint8_t bus_rx = loop_back ? bus : ((0 == bus) ? 1 : 0);

	struct _buffer buf_rx_simple_std = {
			.data = rx_buffers[_RX_BUFF_SIMPLE],
			.size = sizeof(rx_buffers[_RX_BUFF_SIMPLE]),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_RX,
		};
	struct _buffer buf_rx_simple_ext = {
			.data = rx_buffers[_RX_BUFF_SIMPLE_EXT],
			.size = sizeof(rx_buffers[_RX_BUFF_SIMPLE_EXT]),
			.attr = CAND_BUF_ATTR_EXTENDED | CAND_BUF_ATTR_RX,
		};
	struct _buffer buf_rx_simple_fifo = {
			.data = rx_buffers[_RX_BUFF_SIMPLE_FIFO],
			.size = sizeof(rx_buffers[_RX_BUFF_SIMPLE_FIFO]),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_RX | CAND_BUF_ATTR_USING_FIFO,
		};

	can_bus_transfer(bus_rx, id[0], 0x7FF, &buf_rx_simple_std, NULL);
	can_bus_transfer(bus_rx, id[1], 0x1FFFFFFF, &buf_rx_simple_ext, NULL);
	can_bus_transfer(bus_rx, id[2], 0x7FF, &buf_rx_simple_fifo, NULL);

	PRINT_SPLIT;
	static struct _buffer buf_tx_msg0 = {
			.data = (uint8_t*)msg_0,
			.size = sizeof(msg_0),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_TX,
		};
	tx_buf = &buf_tx_msg0;
	trace_info("CAN%u -> %u, ID 0x%lx, len %d:", (unsigned)bus, (unsigned)bus_rx, id[0], (unsigned)tx_buf->size);
	print_buffer(tx_buf->size, tx_buf->data);
	buf_rx_simple_std.attr &= ~CAND_BUF_ATTR_TRANSFER_DONE;
	buf_rx_simple_std.size = sizeof(rx_buffers[0]);

	can_bus_transfer(bus, id[0], 0, tx_buf, NULL);
	if (!can_bus_wait_transfer_done(tx_buf, CAN_TO)) {
		trace_error("TX failed!\r\n");
		return;
	} else
		trace_info("TX OK!\r\n");

	if (!can_bus_wait_transfer_done(&buf_rx_simple_std, CAN_TO)) {
		trace_warning("RX failed!\r\n");
	} else {
		if (buf_rx_simple_std.size == tx_buf->size
			&& (0 == memcmp(buf_rx_simple_std.data, tx_buf->data, tx_buf->size)))
			PRINT_PASS;
		else
			PRINT_FAIL;
	}


	PRINT_SPLIT;
	static struct _buffer buf_tx_msg1 = {
			.data = (uint8_t*)msg_1,
			.size = sizeof(msg_1),
			.attr = CAND_BUF_ATTR_EXTENDED | CAND_BUF_ATTR_TX,
		};
	tx_buf = &buf_tx_msg1;
	tx_buf->size = (mode > CAN_MODE_CAN) ? MSG_LEN_1_CAN_FD : MSG_LEN_1_CAN;
	trace_info("CAN%u -> %u, ID 0x%lx, len %u:", (unsigned)bus, (unsigned)bus_rx, id[0], (unsigned)tx_buf->size);
	print_buffer(tx_buf->size, tx_buf->data);
	buf_rx_simple_ext.attr &= ~CAND_BUF_ATTR_TRANSFER_DONE;
	buf_rx_simple_ext.size = sizeof(rx_buffers[0]);

	can_bus_transfer(bus, id[1], 0, tx_buf, NULL);
	if (!can_bus_wait_transfer_done(tx_buf, CAN_TO)) {
		trace_error("TX failed!\r\n");
		return;
	} else
		trace_info("TX OK!\r\n");

	if (!can_bus_wait_transfer_done(&buf_rx_simple_ext, CAN_TO)) {
		trace_warning("RX failed!\r\n");
	} else {
		if (buf_rx_simple_ext.size == tx_buf->size
			&& (0 == memcmp(buf_rx_simple_ext.data, tx_buf->data, tx_buf->size)))
			PRINT_PASS;
		else
			PRINT_FAIL;
	}

	PRINT_SPLIT;
	static struct _buffer buf_tx_msg2 = {
			.data = (uint8_t*)msg_2,
			.size = sizeof(msg_2),
			.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_TX | CAND_BUF_ATTR_USING_FIFO,
		};
	tx_buf = &buf_tx_msg2;
	tx_buf->size = (mode > CAN_MODE_CAN) ? MSG_LEN_2_CAN_FD : MSG_LEN_2_CAN;
	trace_info("CAN%u -> %u, ID 0x%lx, len %u", (unsigned)bus, (unsigned)bus_rx, id[2], (unsigned)tx_buf->size);
	print_buffer(tx_buf->size, tx_buf->data);

	buf_rx_simple_fifo.attr &= ~CAND_BUF_ATTR_TRANSFER_DONE;
	buf_rx_simple_fifo.size = sizeof(rx_buffers[0]);
	can_bus_transfer(bus, id[2], 0, tx_buf, NULL);
	if (!can_bus_wait_transfer_done(tx_buf, CAN_TO)) {
		trace_error("TX failed!\r\n");
		return;
	} else
		trace_info("TX OK!\r\n");

	if (!can_bus_wait_transfer_done(&buf_rx_simple_fifo, CAN_TO)) {
		trace_warning("RX failed!\r\n");
	} else {
		if (buf_rx_simple_fifo.size == tx_buf->size
			&& (0 == memcmp(buf_rx_simple_fifo.data, tx_buf->data, tx_buf->size)))
			PRINT_PASS;
		else
			PRINT_FAIL;
	}

	test_message(bus);
}

/**
 * \brief Display main menu.
 */
static void display_menu(void)
{
	uint8_t chk_box[3];

	printf("\r\nCAN menu:\r\n");
	printf("Press [c|f|s] to set CAN or CAN FD mode\r\n");
	chk_box[0] = (mode == CAN_MODE_CAN) ? 'X' : ' ';
	chk_box[1] = (mode == CAN_MODE_CAN_FD_CONST_RATE) ? 'X' : ' ';
	chk_box[2] = (mode == CAN_MODE_CAN_FD_DUAL_RATE) ? 'X' : ' ';
	printf("   c: [%c] ISO 11898-1 CAN\r\n", chk_box[0]);
	printf("   f: [%c] ISO 11898-7 CAN FD, 64-byte data\r\n", chk_box[1]);
	printf("   s: [%c] ISO 11898-7 CAN FD, 64-byte data, 2 Mbps data bit"
	    " rate\r\n", chk_box[2]);
	printf("Press [l] to toggle the integrated MCAN loop-back on/off\r\n");
	chk_box[0] = loop_back ? 'X' : ' ';
	printf("   l: [%c] Integrated CANTX->CANRX loop-back\r\n", chk_box[0]);
	printf("   p: Send sample messages\r\n");
	printf("   r: Receive a specified message\r\n");
	printf("   t: Send out a specified message\r\n");
	printf("   h: Display this menu\r\n");
	printf("\r\n");
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
	uint8_t user_key;

	/* Output example information */
	console_example_info("Controller Area Network (CAN/MCAN) Example");

	if ((0 == can_bus_loopback(0, true)) && (0 == can_bus_loopback(1, true)))
		loop_back = true;
	else
		loop_back = false;
	can_bus_mode(0, mode);
	can_bus_mode(1, mode);

	/* Display menu */
	display_menu();

	while (true) {
		if (!console_is_rx_ready())
			continue;
		user_key = tolower(console_get_char());
		switch (user_key) {
		case 'c':
		case 'f':
		case 's':
			mode = user_key == 'f' ? CAN_MODE_CAN_FD_CONST_RATE :
					(user_key == 's' ? CAN_MODE_CAN_FD_DUAL_RATE :
						CAN_MODE_CAN);
			if (0 == can_bus_mode(0, mode))
				can_bus_mode(1, mode);
			else {
				mode = CAN_MODE_CAN;
				trace_warning("Only support standard CAN operation!\r\n");
			}
			display_menu();
			break;
		case 'l':
			loop_back = loop_back ? false : true;
			if (0 == can_bus_loopback(0, loop_back))
				can_bus_loopback(1, loop_back);
			else {
				loop_back = false;
				trace_warning("Loop-back mode not supported!\r\n");
			}
			display_menu();
			break;
		case 'h':
			display_menu();
			break;
		case 'p':
			if (can_bus_activate(0, CAN_TO) < 0) {
				trace_error("Failed to enable CAN/MCAN.\r\n");
				break;
			}
			if (can_bus_activate(1, CAN_TO) < 0) {
				trace_error("Failed to enable CAN/MCAN.\r\n");
				break;
			}
			/* Demonstrate ID filtering */
			id[2] = 0x444 + ((id[2] - 0x444 + 1) & 0x007);
			/* Also, transmit each time different data. */
			msg_2[0]++;
			send_message(0);
			send_message(1);
			break;
		case 'r': {
			struct _buffer buf_rx = {
					.data = rx_buffers[_RX_BUFF_SIMPLE],
					.size = sizeof(rx_buffers[_RX_BUFF_SIMPLE]),
					.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_RX,
				};
			if (can_bus_activate(1, CAN_TO) < 0) {
				trace_error("Failed to enable CAN/MCAN.\r\n");
				break;
			}
			can_bus_transfer(1, 0x222, 0x7FF, &buf_rx, NULL);
			if (!can_bus_wait_transfer_done(&buf_rx, 10 * CAN_TO)) {
				trace_warning("RX failed!\r\n");
			} else {
				trace_info("CAN1 RX, len %u:", (unsigned)buf_rx.size);
				print_buffer(buf_rx.size, buf_rx.data);
			}
			break;
		}
		case 't': {
			struct _buffer buf_tx = {
					.data = (uint8_t*)msg_2,
					.size = 8,
					.attr = CAND_BUF_ATTR_STANDARD | CAND_BUF_ATTR_TX,
				};
			if (can_bus_activate(1, CAN_TO) < 0) {
				trace_error("Failed to enable CAN/MCAN.\n\r");
				break;
			}
			trace_info("CAN1 TX, ID 0x222, len %u:", (unsigned)buf_tx.size);
			print_buffer(buf_tx.size, buf_tx.data);

			can_bus_transfer(1, 0x222, 0, &buf_tx, NULL);
			if (!can_bus_wait_transfer_done(&buf_tx, CAN_TO))
				trace_error("TX failed!\r\n");
			else
				trace_info("TX OK!\r\n");
			break;
		}
		}
	}
}
