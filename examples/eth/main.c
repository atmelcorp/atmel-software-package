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
#include "timer.h"
#include "trace.h"

#include "memories/at24.h"
#include "misc/cache.h"
#include "misc/console.h"
#include "peripherals/aic.h"
#if defined(CONFIG_HAVE_EMAC)
#include "peripherals/emacd.h"
#elif defined(CONFIG_HAVE_GMAC)
#include "peripherals/gmacd.h"
#endif
#include "peripherals/pio.h"
#include "peripherals/pmc.h"

#include "network/phy.h"

#include "mini_ip.h"

#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------
 *         Local Define
 *---------------------------------------------------------------------------*/

/** Number of buffers for RX */
#define RX_BUFFERS  16

/** Number of buffers for TX */
#define TX_BUFFERS  32

/** Timeout for PHY auto-negotiation */
#define PHY_AUTONEG_TIMEOUT 5000

/** Number of ARP requests sent by the example */
#define MAX_ARP_REQUESTS 20

/** Interval between ARP requests (in milliseconds) */
#define ARP_INTERVAL     250

#if defined(CONFIG_HAVE_EMAC)
#   define ETH_PINS EMAC0_PINS
#   define ETH_TYPE ETH_TYPE_EMAC
#   define ETH_ADDR EMAC0_ADDR
#   define ETH_PHY_ADDR EMAC0_PHY_ADDR
#   define ETH_PHY_IF PHY_IF_EMAC
#elif defined(CONFIG_HAVE_GMAC)
#   define ETH_PINS GMAC0_PINS
#   define ETH_TYPE ETH_TYPE_GMAC
#   define ETH_ADDR GMAC0_ADDR
#   define ETH_PHY_ADDR GMAC0_PHY_ADDR
#   define ETH_PHY_IF PHY_IF_GMAC
#endif

/*---------------------------------------------------------------------------
 *         Local variables
 *---------------------------------------------------------------------------*/

const struct _pin eth_pins[] = ETH_PINS;
const struct _phy_desc phy_desc = {
		.addr = ETH_ADDR,
		.phy_if = ETH_PHY_IF,
		.retries = PHY_DEFAULT_RETRIES,
		.phy_addr = ETH_PHY_ADDR
	};

/** The MAC address used for demo */
static uint8_t _mac_addr[6] = { 0x3a, 0x1f, 0x34, 0x08, 0x54, 0x54 };

/** The IP address used for demo (ping ...) */
static uint8_t _src_ip_initialized = 1;
static uint8_t _src_ip[4] = { 192, 168, 1, 3 };
static uint8_t _dest_ip[4] = { 192, 168, 1, 2 };

/** The ETH driver instance */
static struct _ethd _ethd;

/** TX descriptors list */
ALIGNED(8) NOT_CACHED_DDR static struct _eth_desc _tx_desc[TX_BUFFERS];

/** RX descriptors list */
ALIGNED(8) NOT_CACHED_DDR static struct _eth_desc _rx_desc[RX_BUFFERS];

/** TX Buffers (must be aligned on a cache line) */
CACHE_ALIGNED_DDR static uint8_t _tx_buffer[TX_BUFFERS * ETH_TX_UNITSIZE];

/** RX Buffers (must be aligned on a cache line) */
CACHE_ALIGNED_DDR static uint8_t _rx_buffer[RX_BUFFERS * ETH_RX_UNITSIZE];

/** Buffer for Ethernet packets */
static uint8_t _eth_buffer[ETH_MAX_FRAME_LENGTH];

static uint8_t _arp_request_count;
static uint8_t _arp_reply_count;

/*---------------------------------------------------------------------------
 *         Local functions
 *---------------------------------------------------------------------------*/

static void configure_mac_address(void)
{
	bool default_addr = true;

#ifdef BOARD_AT24_MODEL
	struct _at24 at24;
	struct _at24_config config = {
		.bus = BOARD_AT24_TWI_BUS,
		.addr = BOARD_AT24_ADDR,
		.model = BOARD_AT24_MODEL,
	};
	if (at24_configure(&at24, &config)) {
		if (at24_has_eui48(&at24)) {
			if (at24_read_eui48(&at24, _mac_addr)) {
				printf("MAC address initialized using AT24 EEPROM\r\n");
				default_addr = false;
			} else {
				printf("Failed reading MAC address from AT24 EEPROM\r\n");
			}
		} else {
			printf("AT24 EEPROM does not support EUI48 feature\r\n");
		}
	} else {
		printf("Could not configure AT24 EEPROM\r\n");
	}
#endif
	if (default_addr)
		printf("Using default MAC address\r\n");
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

static void _arp_create_and_send_request(uint8_t* src_mac, uint8_t* src_ip, uint8_t* dest_ip)
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

	rc = ethd_send(&_ethd, 0, &pkt, 42, NULL);
	if (rc == ETH_OK) {
		_arp_request_count++;
	} else {
		trace_error("ARP_REQUEST Send - 0x%x\n\r", rc);
	}
}

/**
 * Process a received ARP packet
 */
static void _arp_process_packet(struct _eth_packet *pkt,
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

		rc = ethd_send(&_ethd, 0, pkt, 42, NULL);
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
static void _ip_process_packet(struct _eth_packet* pkt)
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
			rc = ethd_send(&_ethd, 0, pkt, SWAP16(pkt->ip.ip_len) + 14, NULL);
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
static void _eth_process_packet(struct _eth_packet* pkt, uint32_t size)
{
	uint16_t prot;

	//display_packet_headers(pkt, size);

	prot = SWAP16(pkt->eth.et_protlen);
	switch (prot) {
	case ETH_PROT_ARP:
		/* initialize the ip address if not yet initialized */
		_arp_init_ip_addr(pkt);

		/* Process the ARP packet */
		if (_src_ip_initialized == 0)
			return;

		_arp_process_packet(pkt, _mac_addr, _src_ip, _dest_ip);
		break;

	case ETH_PROT_IP:
		if (_src_ip_initialized == 0)
			return;

		/* Process the IP packet */
		_ip_process_packet(pkt);
		break;

	default:
		break;
	}
}

static void _eth_rx_callback(uint8_t queue, uint32_t status)
{
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

	/* Output example information */
	console_example_info("ETH (GMAC/EMAC) Example");

	/* Retrieve MAC address from EEPROM if possible */
	configure_mac_address();

	/* Display MAC & IP settings */
	printf("-- MAC %02x:%02x:%02x:%02x:%02x:%02x\n\r",
	       _mac_addr[0], _mac_addr[1], _mac_addr[2],
	       _mac_addr[3], _mac_addr[4], _mac_addr[5]);
	printf("-- %s IP  %d.%d.%d.%d\n\r", BOARD_NAME,
	       _src_ip[0], _src_ip[1], _src_ip[2], _src_ip[3]);
	printf("-- PC IP  %d.%d.%d.%d\n\r",
		_dest_ip[0], _dest_ip[1], _dest_ip[2], _dest_ip[3]);

	/* Init GMAC */
	pio_configure(eth_pins, ARRAY_SIZE(eth_pins));
	ethd_configure(&_ethd, ETH_TYPE, ETH_ADDR, 1, 0);
	ethd_setup_queue(&_ethd, 0, RX_BUFFERS, _rx_buffer, _rx_desc, TX_BUFFERS, _tx_buffer, _tx_desc, NULL);
	ethd_set_rx_callback(&_ethd, 0, _eth_rx_callback);
	ethd_set_mac_addr(&_ethd, 0, _mac_addr);
	ethd_start(&_ethd);

	/* Init PHY */
	struct _phy phy = {
		.desc = &phy_desc
	};
	phy_configure(&phy);
	phy_auto_negotiate(&phy, PHY_AUTONEG_TIMEOUT);

	tick_start = timer_get_tick();
	_arp_request_count = 0;
	_arp_reply_count = 0;
	while (1) {
		if (_arp_request_count < MAX_ARP_REQUESTS) {
			if ((timer_get_tick() - tick_start) >= ARP_INTERVAL) {
				tick_start = timer_get_tick();
				printf("arp...\r\n");
				_arp_create_and_send_request(_mac_addr, _src_ip, _dest_ip);
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
		while (ethd_poll(&_ethd, 0, (uint8_t*)pkt, pkt_max_size, &length) == ETH_OK) {
			if (length > 0) {
				_eth_process_packet(pkt, length);
			}
		}
	}

	printf("%s sends out %d ARP request and gets %d reply\n\r", BOARD_NAME, _arp_request_count, _arp_reply_count);
	return 1;
}
