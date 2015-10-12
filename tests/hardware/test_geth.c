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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "timer.h"
#include "trace.h"

#include "peripherals/aic.h"
#include "peripherals/gmacd.h"
#include "peripherals/l2cc.h"
#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/wdt.h"

#include "network/phy.h"

#include "gmac/mini_ip.h"

#include "memories/at24.h"
#include "test_at24mac402.h"

#include <stdio.h>
#include <string.h>


/*---------------------------------------------------------------------------
 *         Local Define
 *---------------------------------------------------------------------------*/

/** Number of buffers for RX */
#define RX_BUFFERS  16

/** Number of buffers for TX */
#define TX_BUFFERS  32

#define GMAC_CAF_DISABLE  0
#define GMAC_CAF_ENABLE   1
#define GMAC_NBC_DISABLE  0
#define GMAC_NBC_ENABLE   1

#define MAX_ARP_REQUESTS  10
#define ARP_INTERVAL 50

/*---------------------------------------------------------------------------
 *         Local variables
 *---------------------------------------------------------------------------*/

/** The MAC address used for demo */
//static uint8_t _mac_addr[6] = { 0x3a, 0x1f, 0x34, 0x08, 0x54, 0x54 };
static uint8_t _mac_addr[6] = {0};

/** The IP address used for demo (ping ...) */
static uint8_t _src_ip_initialized = 1;
static uint8_t _src_ip[4] = { 192, 168, 1, 3 };
static uint8_t _dest_ip[4] = { 192, 168, 1, 2 };

/** The GMAC driver instance */
static struct _gmacd _gmacd;

/** TX descriptors list */
ALIGNED(8) SECTION(".region_ddr_nocache")
static struct _gmac_desc _tx_desc[TX_BUFFERS];

/** RX descriptors list */
ALIGNED(8) SECTION(".region_ddr_nocache")
static struct _gmac_desc _rx_desc[RX_BUFFERS];

/** TX Buffers (must be aligned on a cache line) */
ALIGNED(32) SECTION(".region_ddr")
static uint8_t _tx_buffer[TX_BUFFERS * GMAC_TX_UNITSIZE];

/** RX Buffers (must be aligned on a cache line) */
ALIGNED(32) SECTION(".region_ddr")
static uint8_t _rx_buffer[RX_BUFFERS * GMAC_RX_UNITSIZE];

/** Buffer for Ethernet packets */
static uint8_t _eth_buffer[GMAC_MAX_FRAME_LENGTH];

static uint8_t _arp_request_count;
static uint8_t _arp_reply_count;

/*---------------------------------------------------------------------------
 *         Local functions
 *---------------------------------------------------------------------------*/

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
				printf(" => OK\n\r");
				_src_ip_initialized = 1;
			} else {
				printf(" => KO!\n\r");
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

	rc = gmacd_send(&_gmacd, 0, &pkt, 42, NULL);
	if (rc == GMACD_OK) {
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

		rc = gmacd_send(&_gmacd, 0, pkt, 42, NULL);
		if (rc != GMACD_OK) {
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
	uint32_t gmac_rc = GMACD_OK;

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
			gmac_rc = gmacd_send(&_gmacd, 0, pkt, SWAP16(pkt->ip.ip_len) + 14, NULL);
			if (gmac_rc != GMACD_OK) {
				printf(" -E- ICMP Send - 0x%x\n\r", (unsigned int) gmac_rc);
			}
		}
		break;

	default:
		break;
	}
}

/**
 * Process the received GMAC packet
 */
static void _eth_process_packet(struct _eth_packet* pkt, uint32_t size)
{
	uint16_t prot;

	display_packet_headers(pkt, size);

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

static void _gmac_rx_callback(uint8_t queue, uint32_t status)
{
}

/*---------------------------------------------------------------------------
 *         Global functions
 *---------------------------------------------------------------------------*/

uint8_t test_geth (uint8_t bypass_exchange)
{
	uint8_t status = 0;
	uint32_t tick_start;
	struct _at24* p_at24;


	/* Display MAC settings */
	p_at24 = at24mac402_get_descriptor();
	memcpy (_mac_addr, p_at24->mac_addr_48, AT24_EUI48_SIZE);
	printf("-- MAC ADD : %02x:%02x:%02x:%02x:%02x:%02x\n\r",
	       _mac_addr[0], _mac_addr[1], _mac_addr[2],
	       _mac_addr[3], _mac_addr[4], _mac_addr[5]);
	/* Display IP settings */
	printf("-- BOARD IP: %d.%d.%d.%d\n\r",
	       _src_ip[0], _src_ip[1], _src_ip[2], _src_ip[3]);
	printf("-- PC IP   : %d.%d.%d.%d\n\r",
		_dest_ip[0], _dest_ip[1], _dest_ip[2], _dest_ip[3]);

	/* Init GMAC */
	const struct _pin gmac_pins[] = GMAC0_PINS;
	pio_configure(gmac_pins, ARRAY_SIZE(gmac_pins));
	gmacd_configure(&_gmacd, GMAC0_ADDR, GMAC_CAF_ENABLE, GMAC_NBC_DISABLE);
	gmacd_setup_queue(&_gmacd, 0, RX_BUFFERS, _rx_buffer, _rx_desc, TX_BUFFERS, _tx_buffer, _tx_desc, NULL);
	gmacd_set_rx_callback(&_gmacd, 0, _gmac_rx_callback);
	gmac_set_mac_addr(_gmacd.gmac, 0, p_at24->mac_addr_48);
	gmacd_start(&_gmacd);

	/* Init PHY */
	struct _phy_desc phy_desc = {
		.addr = GMAC0_ADDR,
		.retries = GMAC0_PHY_RETRIES,
		.phy_addr = GMAC0_PHY_ADDR
	};
	struct _phy phy = {
		.desc = &phy_desc
	};
	phy_configure(&phy);
	printf("-I- Start Auto-negotiation \n\r");
	status = phy_auto_negotiate(&phy, 5000);
	if ( status == false ) {
		printf("-E- Error Auto-negotiation \n\r");
		return 1;
	}

	if (bypass_exchange) return status = 0;

	/* Send-Receive packets */
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
		while (gmacd_poll(&_gmacd, 0, (uint8_t*)pkt, pkt_max_size, &length) == GMACD_OK) {
			if (length > 0) {
				_eth_process_packet(pkt, length);
			}
		}
	}
	printf("Sends out %d ARP request and gets %d reply\n\r", _arp_request_count, _arp_reply_count);
	return status = 0;
}



