/* ---------------------------------------------------------------------------- */
/*                Microchip Microcontroller Software Support                    */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2019, Microchip Technology Inc.                                */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Microchip's name may not be used to endorse or promote products derived from */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS  */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT    */
/* ARE DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT,        */
/* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF     */
/* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */
/* ---------------------------------------------------------------------------- */

/**
 *  \page OTP Example
 *
 *  \section Purpose
 *
 *  This example indicates how to use the OTP driver in order to access data stored in OTP.
 *
 *  \section Requirements
 *
 *  This package can be used with SAM9X60-EK.
 *
 *  \section Description
 *
 *  The demonstration program shows some basic operations of OTP.
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
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# Start the application.
 *  -# In the terminal window, the following text should appear (values depend
 *     on the board and chip used):
 *     \code
 *      -- OTP Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *     \endcode
  * -# Choose an item in the menu to test.
*
 *  \section References
 *  - otp/main.c
 *  - otpc.h
 *  - otpc.c
 */

/** \file
 *
 *  This file contains all the specific code for the OTP example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "serial/console.h"
#include "nvm/otp/otpc.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

typedef uint8_t (* PACKET_PROC)(const uint16_t);

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

static const char *otp_packet_type[] = {
	"REGULAR",
	"KEY",
	"BOOT_CONFIGURATION",
	"SECURE_BOOT_DATA",
	"HARDWARE_CONFIGURATION",
	"CUSTOM"
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void clear_sram1_for_emulation(void)
{
	volatile uint8_t *sram1 = (volatile uint8_t *)IRAM1_ADDR;
	uint32_t sram1_size = 4 * 1024;
	while(sram1_size--)
		*sram1++ = 0;
}

static void show_packets(void)
{
	struct otp_packet_header match, result;
	uint32_t buf[256];
	uint32_t i;
	uint32_t filters;
	uint16_t packet_addr;
	uint16_t actually_read;

	printf("\r\npacket type:\r\n");
	for (i = 0; i < ARRAY_SIZE(otp_packet_type); i++) {
		printf("\t%c - %s\r\n", *otp_packet_type[i], otp_packet_type[i]);
	}

	/* No filter, match all packets */
	memset(&match, 0, sizeof(match));
	filters = 0;
	packet_addr = 0;
	i = 0;

	printf(" idx | header addr | check sum |  size | valid | locked | type | payload\r\n");
	while (!otp_get_next_matching_packet(filters, &match, &result, &packet_addr)) {
		if (!result.is_invalid &&
		    otp_read_packet(packet_addr, buf, sizeof(buf), &actually_read)) {
			trace_error("failed to read packet payload\r\n");
			break;
		}
		if (result.checksum == OTPC_CS_CORRUPTED) {
			trace_error("the header of the packet is corrupted!\r\n");
			break;
		}
		if (result.type >= OTP_PCKT_MAX_TYPE) {
			trace_error("invalid packet type!\r\n");
			break;
		}
		printf("%4u |  0x%08x |    0x%04x |%5luB |   %s |   %s  |   %c ",
		    (unsigned)i, (unsigned)packet_addr,
		    result.checksum,
		    result.size,
		    !result.is_invalid ? "yes" : " no",
		    result.is_locked ? "yes" : " no",
		    *otp_packet_type[result.type]);
		if (result.is_invalid)
			printf(" | <invalid> \r\n");
		else
			printf(" | %02x %02x %02x ...\r\n",
			    *((uint8_t*)buf + 0),
			    *((uint8_t*)buf + 1),
			    *((uint8_t*)buf + 2));

		packet_addr += 1 + (result.size >> 2);
		i++;
	}
	printf("\r\n");
}

static void _process_packet(PACKET_PROC func, const char * op)
{
	uint32_t addr;
	printf("\n\rEnter hexadecimal address of the packet to be operated: ");

	if (console_get_hexa_32(&addr) != 1)
		printf("-W- Invalid input, %s packet canceled.\r\n", op);
	else
		printf("%s packet at address 0x%lx, %s\r\n",
		    op, addr, 0 == func(addr) ? "succeed" : "failed");
}

/**
 * \brief Display main menu.
 */
static void _display_menu(void)
{
	printf("\n\r =================== OTP Example Menu =====================\n\r");
	printf("|  e: User area Emulation: Enabled[%c] Disabled [%c]          |\n\r",
	    otp_is_emulation_enabled() ? 'X' : ' ', otp_is_emulation_enabled() ? ' ' : 'X');
	printf("|  h: Hide packet                                           |\n\r");
	printf("|  i: Invalidate packet                                     |\n\r");
	printf("|  l: Lock packet                                           |\n\r");
	printf("|  s: Show packets                                          |\n\r");
	printf("|  w: write a packet                                        |\n\r");
	printf("|  m: Menu                                                  |\n\r");
	printf("|-----------------------------------------------------------|\n\r");
}

/**
 *  \brief Handler for DBGU input.
 */
static void console_handler(uint8_t key)
{
	printf("%c entered\r\n", key);
	switch (key) {
	case 'e':
		(void)otp_emulation_mode(!otp_is_emulation_enabled());
		break;
	case 'h':
		_process_packet(otp_hide_packet, "hide");
		break;
	case 'i':
		_process_packet(otp_invalidate_packet, "invalidate");
		break;
	case 'l':
		_process_packet(otp_lock_packet, "lock");
		break;
	case 's':
		show_packets();
		break;
	case 'w': {
		uint16_t packet_addr;
		uint32_t payload = 0xaabbccdd;
		struct otp_new_packet pckt;
		memset(&pckt, 0, sizeof(pckt));
		pckt.type = OTP_PCKT_CUSTOM;
		pckt.size = sizeof(payload);
		otp_write_packet(&pckt, &payload, &packet_addr, NULL);
		break;
	}
	case 'm':
	default:
		break;
	}
	_display_menu();
}

static void test_otp_in_emulation_mode(void)
{
	struct otp_new_packet pckt;
	uint16_t packet_addr;
	uint32_t buf[16];
	uint32_t i = 0;

	do {
		*((uint8_t *)buf + i) = i;
	} while (++i < sizeof(buf));

	memset(&pckt, 0, sizeof(pckt));
	pckt.type = OTP_PCKT_CUSTOM;

	// OTPC_HR_SIZE(0):   SIZE = 0 means payload is 32-bit size
	// OTPC_HR_SIZE(255): SIZE = 255 means payload is 8192-bit size.
	pckt.size = 1 * sizeof(uint32_t);
	otp_write_packet(&pckt, &buf[0], &packet_addr, NULL);

	pckt.size = 2 * sizeof(uint32_t);
	otp_write_packet(&pckt, &buf[1], &packet_addr, NULL);
	otp_update_payload(packet_addr, &buf[2]);

	pckt.size = 3 * sizeof(uint32_t);
	otp_write_packet(&pckt, &buf[5], &packet_addr, NULL);

	pckt.size = 4 * sizeof(uint32_t);
	otp_write_packet(&pckt, &buf[7], &packet_addr, NULL);

	pckt.size = 2 * sizeof(uint32_t);
	otp_write_packet(&pckt, &buf[9], &packet_addr, NULL);

	pckt.size = 4 * sizeof(uint32_t);
	otp_write_packet(&pckt, &buf[7], &packet_addr, NULL);

	otp_invalidate_packet(0x0);
	otp_lock_packet(0x9);
}

/*----------------------------------------------------------------------------
 *        Global functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief OTP Example entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	console_example_info("OTP Example");

	if (otp_is_disabled()) {
		printf("\n\r OTP is disabled, terminate this example.\n\r");
		while(1);
	}

	otp_init();

	clear_sram1_for_emulation();
	otp_emulation_mode(true);

	show_packets();

	if (otp_is_emulation_enabled()) {
		test_otp_in_emulation_mode();
		show_packets();
	}

	/* Display menu */
	_display_menu();

	while(1) {
		console_handler(console_get_char());
	}
}
