/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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
 *  \page eth ETH Example
 *
 *  \section Purpose
 *
 *  This example uses the Ethrenet MAC (EMAC) / Gigabit Ethernet MAC (GMAC) and
 *  the on-board Ethernet transceiver available on Atmel SAMA5D3-EK, SAMA5D3-XULT,
 *  SAMA5D4-EK, SAMA5D4-XULT or SAMA5D2-Xplained. It enables the device to
 *  respond to a ping command sent by a host computer.
 *
 *  \section Requirements
 *
 *  - On-board ethernet interface.
 *
 *  \section Description
 *
 *  Upon startup, the program will configure the EMAC/GMAC with a default IP and
 *  MAC address and then ask the transceiver to auto-negotiate the best mode
 *  of operation. Once this is done, it will start to monitor incoming packets
 *  and processing them whenever appropriate.
 *
 *  The basic will only answer to two kinds of packets:
 *
 *  - It will reply to ARP requests with its MAC address,
 *  - and to ICMP ECHO request so the device can be PING'ed.
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
 *  -# Connect an Ethernet cable between the evaluation board and the network.
 *      The board may be connected directly to a computer; in this case,
 *      make sure to use a cross/twisted wired cable such as the one provided
 *      with the board.
 *  -# Start the application. It will display the following message on the DBGU:
 *     \code
 *      -- ETH Example xxx --
 *      -- SAMxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      MAC 3a 1f 34 08 54 54
 *      IP  192, 168, 1, 3
 *     \endcode
 *  -# The program will then auto-negotiate the mode of operation and start
 *     receiving packets, displaying feedback on the DBGU. To display additional
 *     information, press any key in the terminal application.
 *  \note
 *  Make sure the IP adress of the device(the board) and the computer are in the same network.
 *
 *  \section References
 *  - eth/main.c
 *  - ethd.c
 *  - ethd.h
 */

/** \file
 *
 *  This file contains all the specific code for the ETH example.
 *
 */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "board.h"
#include "board_eth.h"
#include "timer.h"
#include "trace.h"

#include "mm/cache.h"
#include "serial/console.h"
#include "network/ethd.h"
#include "gpio/pio.h"
#include "peripherals/pmc.h"

#include "network/phy.h"

#include "mini_ip.h"

#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------
 *         Local Define
 *---------------------------------------------------------------------------*/

/** Number of ARP requests sent by the example */
#define MAX_ARP_REQUESTS 20

/** Interval between ARP requests (in milliseconds) */
#define ARP_INTERVAL     250

/*---------------------------------------------------------------------------
 *         Local variables
 *---------------------------------------------------------------------------*/

/** The IP address used for demo (ping ...) */
static uint8_t _src_ip_initialized = 1;
static uint8_t _src_ip[4] = { 192, 168, 1, 3 };
static uint8_t _dest_ip[4] = { 192, 168, 1, 2 };

/** Buffer for Ethernet packets */
static uint8_t _eth_buffer[ETH_MAX_FRAME_LENGTH];

static uint8_t _mac_addr[6];

static uint8_t _arp_request_count;
static uint8_t _arp_reply_count;

/*---------------------------------------------------------------------------
 *         Local functions
 *---------------------------------------------------------------------------*/

/**
 * Input the eth number to use
 */
static uint8_t select_eth_port(void)
{
	uint8_t key, send_port = 0;

	if (ETH_IFACE_COUNT < 2)
		return 0;

	while (1) {
		printf("\n\r");
		printf("Input an eth number '0' or '1' to initialize:\n\r");
		printf("=>");
		key = console_get_char();
		printf("%c\r\n", key);
		if (key == '0') {
			send_port = 0;
			break;
		} else if (key == '1') {
			send_port = 1;
			break;
		}
	}

	return send_port;
}

/**
 * initialize the Ip address of the board if not yet initialized
 */
static void _arp_init_ip_addr(struct _eth_packet *pkt)
{
	uint32_t i;

	if (SWAP16(pkt->arp.ar_op) == ARP_REQUEST) {
		if (_src_ip_initialized == 0) {
			printf("first arp request, Check @ip. src=%d.%d.%d.%d dst=%d.%d.%d.%d ",
			     pkt->arp.ar_spa[0], pkt->arp.ar_spa[1], pkt->arp.ar_spa[2],
			     pkt->arp.ar_spa[3], pkt->arp.ar_tpa[0], pkt->arp.ar_tpa[1],
			     pkt->arp.ar_tpa[2], pkt->arp.ar_tpa[3]);

			if (pkt->arp.ar_tpa[0] == pkt->arp.ar_spa[0] &&
					pkt->arp.ar_tpa[1] == pkt->arp.ar_spa[1] &&
					pkt->arp.ar_tpa[2] == pkt->arp.ar_spa[2] &&
					pkt->arp.ar_tpa[3] >= 250 &&
					pkt->arp.ar_tpa[3] <= 254) {
				for (i = 0; i < 4; i++) {
					_src_ip[i] = pkt->arp.ar_tpa[i];
				}
				printf("=> OK\n\r");
				_src_ip_initialized = 1;
			} else {
				printf("=> KO!\n\r");
			}
		}
	}
}

static void _arp_create_and_send_request(uint8_t eth_port, uint8_t* src_mac,
                                         uint8_t* src_ip, uint8_t* dest_ip)
{
	struct _eth_packet pkt;
	uint32_t i;
	uint8_t rc;

	pkt.eth.et_protlen = SWAP16(ETH_PROT_ARP);

	// ARP REPLY operation
	pkt.arp.ar_hrd = SWAP16(0x0001);
	pkt.arp.ar_pro = SWAP16(ETH_PROT_IP);
	pkt.arp.ar_hln = 6;
	pkt.arp.ar_pln = 4;
	pkt.arp.ar_op = SWAP16(ARP_REQUEST);

	/* Fill the dest and src MAC addresses */
	for (i = 0; i < 6; i++) {
		pkt.eth.et_dest[i] = 0xff;
		pkt.eth.et_src[i] = src_mac[i];
		pkt.arp.ar_tha[i] = 0x00;
		pkt.arp.ar_sha[i] = src_mac[i];
	}

	/* Fill the dest and src IP addresses */
	for (i = 0; i < 4; i++) {
		pkt.arp.ar_tpa[i] = dest_ip[i];
		pkt.arp.ar_spa[i] = src_ip[i];
	}

	rc = ethd_send(board_get_eth(eth_port), 0, &pkt, 42, NULL);
	if (rc == ETH_OK) {
		_arp_request_count++;
	} else {
		trace_error("ARP_REQUEST Send - 0x%x\n\r", rc);
	}
}

/**
 * Process a received ARP packet
 */
static void _arp_process_packet(uint8_t eth_port, struct _eth_packet *pkt,
		uint8_t* src_mac, uint8_t* src_ip, uint8_t* dest_ip)
{
	uint32_t i;
	uint8_t rc;
	bool match;

	switch (SWAP16(pkt->arp.ar_op)) {
	case ARP_REQUEST:
		/* ARP REPLY operation */
		pkt->arp.ar_op = SWAP16(ARP_REPLY);

		/* Fill the dest address and src address */
		for (i = 0; i < 6; i++) {
			/* swap ethernet dest address and ethernet src address */
			pkt->eth.et_dest[i] = pkt->eth.et_src[i];
			pkt->eth.et_src[i] = src_mac[i];
			pkt->arp.ar_tha[i] = pkt->arp.ar_sha[i];
			pkt->arp.ar_sha[i] = src_mac[i];
		}

		/* swap sender IP address and target IP address */
		for (i = 0; i < 4; i++) {
			pkt->arp.ar_tpa[i] = pkt->arp.ar_spa[i];
			pkt->arp.ar_spa[i] = src_ip[i];
		}

		rc = ethd_send(board_get_eth(eth_port), 0, pkt, 42, NULL);
		if (rc != ETH_OK) {
			trace_error("ARP_REPLY Send - 0x%x\n\r", rc);
		}

		break;

	case ARP_REPLY:
		/* check sender IP address and target IP address */
		match = true;
		for (i = 0; i < 4; i++) {
			if (pkt->arp.ar_tpa[i] != src_ip[i]) {
				match = false;
				break;
			}
			if (pkt->arp.ar_spa[i] != dest_ip[i]) {
				match = false;
				break;
			}
		}
		if (match) {
			_arp_reply_count++;
		}
	}
}

/**
 * Process the received IP packet
 */
static void _ip_process_packet(uint8_t eth_port, struct _eth_packet* pkt)
{
	uint32_t i;
	uint32_t icmp_len;
	uint32_t rc = ETH_OK;

	switch (pkt->ip.ip_p) {
	case IP_PROT_ICMP:
		if (pkt->icmp.type == ICMP_ECHO_REQUEST) {
			pkt->icmp.type = ICMP_ECHO_REPLY;
			pkt->icmp.code = 0;
			pkt->icmp.cksum = 0;

			/* Checksum of the ICMP Message */
			icmp_len = (SWAP16(pkt->ip.ip_len) - 20);
			if (icmp_len % 2) {
				*((uint8_t*)&pkt->icmp + icmp_len) = 0;
				icmp_len++;
			}
			icmp_len = icmp_len / sizeof (unsigned short);

			pkt->icmp.cksum = SWAP16(icmp_chksum((uint16_t*)&pkt->icmp, icmp_len));

			/* Swap IP Dest address and IP Source address */
			for (i = 0; i < 4; i++) {
				_src_ip[i] = pkt->ip.ip_dst[i];
				pkt->ip.ip_dst[i] = pkt->ip.ip_src[i];
				pkt->ip.ip_src[i] = _src_ip[i];
			}

			/* Swap Eth Dest address and Eth Source address */
			for (i = 0; i < 6; i++) {

				/* swap ethernet dest address and ethernet src addr */
				pkt->eth.et_dest[i] = pkt->eth.et_src[i];
				pkt->eth.et_src[i] = _mac_addr[i];
			}

			/* send the echo_reply */
			rc = ethd_send(board_get_eth(eth_port), 0, pkt, SWAP16(pkt->ip.ip_len) + 14, NULL);
			if (rc != ETH_OK) {
				printf("-E- ICMP Send - 0x%x\n\r", (unsigned int)rc);
			}
		}
		break;

	default:
		break;
	}
}

/**
 * Process the received ETH packet
 */
static void _eth_process_packet(uint8_t eth_port, struct _eth_packet* pkt, uint32_t size)
{
	uint16_t proto;

	//display_packet_headers(pkt, size);

	proto = SWAP16(pkt->eth.et_protlen);
	switch (proto) {
	case ETH_PROT_ARP:
		/* initialize the ip address if not yet initialized */
		_arp_init_ip_addr(pkt);

		/* Process the ARP packet */
		if (_src_ip_initialized == 0)
			return;

		_arp_process_packet(eth_port, pkt, _mac_addr, _src_ip, _dest_ip);
		break;

	case ETH_PROT_IP:
		if (_src_ip_initialized == 0)
			return;

		/* Process the IP packet */
		_ip_process_packet(eth_port, pkt);
		break;

	default:
		break;
	}
}

/*---------------------------------------------------------------------------
 *         Global functions
 *---------------------------------------------------------------------------*/

/**
 * Default main() function.
 */
int main(void)
{
	uint32_t tick_start;
	uint8_t eth_port = 0;

	/* Output example information */
	console_example_info("ETH (GMAC/EMAC) Example");

	/* User select the port number for multiple eth */
	eth_port = select_eth_port();
	ethd_get_mac_addr(board_get_eth(eth_port), 0, _mac_addr);

	/* Display MAC & IP settings */
	printf("-- MAC %02x:%02x:%02x:%02x:%02x:%02x\n\r",
	       _mac_addr[0], _mac_addr[1], _mac_addr[2],
	       _mac_addr[3], _mac_addr[4], _mac_addr[5]);
	printf("-- %s IP  %d.%d.%d.%d\n\r", BOARD_NAME,
	       _src_ip[0], _src_ip[1], _src_ip[2], _src_ip[3]);
	printf("-- PC IP  %d.%d.%d.%d\n\r",
		_dest_ip[0], _dest_ip[1], _dest_ip[2], _dest_ip[3]);

	tick_start = timer_get_tick();
	_arp_request_count = 0;
	_arp_reply_count = 0;
	while (1) {
		if (_arp_request_count < MAX_ARP_REQUESTS) {
			if ((timer_get_tick() - tick_start) >= ARP_INTERVAL) {
				tick_start = timer_get_tick();
				printf("arp...\r\n");
				_arp_create_and_send_request(eth_port, _mac_addr, _src_ip, _dest_ip);
			}
		} else {
			/* wait 1s to get remaining replies */
			if ((timer_get_tick() - tick_start) >= 500)
				break;
		}

		struct _eth_packet* pkt = (struct _eth_packet*)_eth_buffer;
		uint32_t pkt_max_size = sizeof(_eth_buffer);

		/* Process packets */
		uint32_t length = 0;
		while (ethd_poll(board_get_eth(eth_port), 0, (uint8_t*)pkt, pkt_max_size, &length) == ETH_OK) {
			if (length > 0) {
				_eth_process_packet(eth_port, pkt, length);
			}
		}
	}

	printf("%s eth%d sends out %d ARP request and gets %d reply\n\r", BOARD_NAME, eth_port, _arp_request_count, _arp_reply_count);
	return 1;
}
