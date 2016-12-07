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
 *  \page eth_uip_helloworld ETH uIP Hello World Example
 *
 *  \section Purpose
 *
 *  This project implements a telnet hello-world example of the uIP stack.
 *  It makes the device to respond to telnet connections on port 1000.
 *
 *  \section Requirements
 *  - On-board ethernet interface.
 *
 *  \section Description
 *
 * Please refer to the uIP documentation for more information
 * about the TCP/IP stack, the hello-world example.
 *
 * By default, the example does not use DHCP.
 * If you want to use DHCP, please:
 * - Open file uip-conf.h and don't comment the line "#define UIP_DHCP_on".
 * - Include uip/apps/dhcps to compile.
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
 *      with SAMA5D2-XPLAINED / SAMA5D3-EK / SAMA5D3-XULT / SAMA5D4-EK / SAMA5D4-XULT.
 *  -# Start the application. It will display the following message on the terminal:
 *    \code
 *    -- ETH uIP Hello World Example xxx --
 *    -- xxxxxx-xx
 *    -- Compiled: xxx xx xxxx xx:xx:xx --
 *    - MAC 3a:1f:34:08:54:05
 *    - Host IP 192.168.1.3
 *    - Router IP 192.168.1.1
 *    - Net Mask 255.255.255.0
 *    \endcode
 * -# Connect to the device IP address using telnet on port 1000:
 *    \code
 *    telnet 192.168.1.3 1000
 *    \endcode
 *    A greeting message will appear:
 *    \code
 *    Hello. What is your name?
 *    \endcode
 *
 * \note
 * Make sure the IP adress of the device( the  board) and the computer are in the same network.
 */

/** \file
 *
 *  This file contains all the specific code for the eth_uip_helloworld example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "board_eth.h"
#include "trace.h"
#include "timer.h"

#include "serial/console.h"
#include "network/ethd.h"

#include "uip/uip.h"
#include "uip/uip_arp.h"
#include "uip/clock.h"
#include "eth_tapdev.h"
#include "hello-world.h"

#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------
 *         Variables
 *---------------------------------------------------------------------------*/

/* uIP buffer : The ETH header */
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

/* The MAC address used for demo */
static struct uip_eth_addr _mac_addr;

/* The IP address used for demo (ping ...) */
static const uint8_t _host_ip_addr[4] = {192,168,1,3};

/* Set the default router's IP address. */
static const uint8_t _route_ip_addr[4] = {192,168,1,1};

/* The NetMask address */
static const uint8_t _netmask[4] = {255, 255, 255, 0};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * Input the eth number to use
 */
static uint8_t select_eth_port(void)
{
	uint8_t key, send_port = 0;

	if (ETH_IFACE_COUNT < 2)
		return send_port;

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
 * Initialize demo application
 */
static void _app_init(void)
{
	printf("P: hello-world application init\n\r");
	hello_world_init();

#ifdef __DHCPC_H__
	printf("P: DHCPC Init\n\r");
	dhcpc_init(_mac_addr.addr, 6);
#endif
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * uip_log: Global function for uIP to use.
 * \param m Pointer to string that logged
 */
void uip_log(char *m)
{
	trace_info("-uIP log- %s\n\r", m);
}

#ifdef __DHCPC_H__
/**
 * dhcpc_configured: Global function for uIP DHCPC to use,
 * notification of DHCP configuration.
 * \param s Pointer to DHCP state instance
 */
void dhcpc_configured(const struct dhcpc_state *s)
{
	u8_t * pAddr;

	printf("\n\r");
	printf("=== DHCP Configurations ===\n\r");
	pAddr = (u8_t *)s->ipaddr;
	printf("- IP   : %d.%d.%d.%d\n\r",
			pAddr[0], pAddr[1], pAddr[2], pAddr[3]);
	pAddr = (u8_t *)s->netmask;
	printf("- Mask : %d.%d.%d.%d\n\r",
			pAddr[0], pAddr[1], pAddr[2], pAddr[3]);
	pAddr = (u8_t *)s->default_router;
	printf("- GW   : %d.%d.%d.%d\n\r",
			pAddr[0], pAddr[1], pAddr[2], pAddr[3]);
	pAddr = (u8_t *)s->dnsaddr;
	printf("- DNS  : %d.%d.%d.%d\n\r",
			pAddr[0], pAddr[1], pAddr[2], pAddr[3]);
	printf("===========================\n\r\n");
	uip_sethostaddr(s->ipaddr);
	uip_setnetmask(s->netmask);
	uip_setdraddr(s->default_router);

#ifdef __RESOLV_H__
	resolv_conf(s->dnsaddr);
#else
	printf("DNS NOT enabled in the demo\n\r");
#endif
}
#endif

/**
 *  \brief gmac_uip_helloworld example entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
int main(void)
{
	uip_ipaddr_t ipaddr;
	struct _timeout periodic_timer, arp_timer;
	uint32_t i;
	uint8_t eth_port = 0;

	/* Output example information */
	console_example_info("ETH uIP Hello World Example");

	/* User select the port number for multiple eth */
	eth_port = select_eth_port();
	ethd_get_mac_addr(board_get_eth(eth_port), 0, _mac_addr.addr);

	/* Display MAC & IP settings */
	printf(" - MAC %02x:%02x:%02x:%02x:%02x:%02x\n\r",
	       _mac_addr.addr[0], _mac_addr.addr[1], _mac_addr.addr[2],
	       _mac_addr.addr[3], _mac_addr.addr[4], _mac_addr.addr[5]);
#ifndef __DHCPC_H__
	printf(" - Host IP  %d.%d.%d.%d\n\r",
	       _host_ip_addr[0], _host_ip_addr[1], _host_ip_addr[2], _host_ip_addr[3]);
	printf(" - Router IP  %d.%d.%d.%d\n\r",
	       _route_ip_addr[0], _route_ip_addr[1], _route_ip_addr[2], _route_ip_addr[3]);
	printf(" - Net Mask  %d.%d.%d.%d\n\r",
	       _netmask[0], _netmask[1], _netmask[2], _netmask[3]);
#endif

	timer_start_timeout(&periodic_timer, 500);
	timer_start_timeout(&arp_timer, 10000);
	/* Init uIP */
	uip_init();

#ifdef __DHCPC_H__
	printf("P: DHCP Supported\n\r");
	uip_ipaddr(ipaddr, 0, 0, 0, 0);
	uip_sethostaddr(ipaddr);
	uip_ipaddr(ipaddr, 0, 0, 0, 0);
	uip_setdraddr(ipaddr);
	uip_ipaddr(ipaddr, 0, 0, 0, 0);
	uip_setnetmask(ipaddr);
#else
	/* Set the IP address of this host */
	uip_ipaddr(ipaddr, _host_ip_addr[0], _host_ip_addr[1], _host_ip_addr[2], _host_ip_addr[3]);
	uip_sethostaddr(ipaddr);

	uip_ipaddr(ipaddr, _route_ip_addr[0], _route_ip_addr[1], _route_ip_addr[2], _route_ip_addr[3]);
	uip_setdraddr(ipaddr);

	uip_ipaddr(ipaddr, _netmask[0], _netmask[1], _netmask[2], _netmask[3]);
	uip_setnetmask(ipaddr);
#endif

	uip_setethaddr(_mac_addr);

	_app_init();

	while(1) {
		uip_len = eth_tapdev_read(eth_port);
		if(uip_len > 0) {
			if(BUF->type == htons(UIP_ETHTYPE_IP)) {
				uip_arp_ipin();
				uip_input();
				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if(uip_len > 0) {
					uip_arp_out();
					eth_tapdev_send(eth_port);
				}
			} else if(BUF->type == htons(UIP_ETHTYPE_ARP)) {
				uip_arp_arpin();
				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if(uip_len > 0) {
					eth_tapdev_send(eth_port);
				}
			}
		} else if(timer_timeout_reached(&periodic_timer)) {
			timer_reset_timeout(&periodic_timer);
			for(i = 0; i < UIP_CONNS; i++) {
				uip_periodic(i);
				/* If the above function invocation resulted in data that
				   should be sent out on the network, the global variable
				   uip_len is set to a value > 0. */
				if(uip_len > 0) {
					uip_arp_out();
					eth_tapdev_send(eth_port);
				}
			}
#if UIP_UDP
			for(i = 0; i < UIP_UDP_CONNS; i++) {
				uip_udp_periodic(i);
				/* If the above function invocation resulted in data that
				   should be sent out on the network, the global variable
				   uip_len is set to a value > 0. */
				if(uip_len > 0) {
					uip_arp_out();
					eth_tapdev_send();
				}
			}
#endif /* UIP_UDP */

			/* Call the ARP timer function every 10 seconds. */
			if(timer_timeout_reached(&arp_timer)) {
				timer_reset_timeout(&arp_timer);
				uip_arp_timer();
			}
		}
	}
}
