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
 *  \page gmac_uip_helloworld GMAC uIP Hello World Example
 *
 *  \section Purpose
 *
 *  This project implements a telnet hello-world example of the uIP stack.
 *  It makes the device to respond to telnet connections on port 1000.
 *
 *  \section Requirements
 *  - SAMA5D4x microcontrollers with GMAC feature.
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
 *      with SAMA5D4-EK / SAMA5D4-XULT.
 *  -# Start the application. It will display the following message on the terminal:
 *    \code
 *    -- GMAC uIP Hello World Example xxx --
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
 *  This file contains all the specific code for the gmac_uip_helloworld example.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "trace.h"

#include "memories/at24.h"
#include "peripherals/pio.h"
#include "peripherals/wdt.h"

#include "uip/uip.h"
#include "uip/uip_arp.h"
#include "uip/clock.h"
#include "uip/timer.h"
#include "gmac_tapdev.h"
#include "hello-world.h"

#include <stdio.h>
#include <string.h>

/*---------------------------------------------------------------------------
 *         Variables
 *---------------------------------------------------------------------------*/

/* uIP buffer : The ETH header */
#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

/** if AT24 is available on the board, it will be used to setup the MAC addr */
#ifdef AT24_PINS
static const struct _pin at24_pins[] = AT24_PINS;

struct _at24 at24_drv = {
        .desc = AT24_DESC
};

struct _twi_desc at24_twid = {
        .addr = AT24_ADDR,
        .freq = AT24_FREQ,
        .transfert_mode = TWID_MODE_DMA
};
#endif

/* The MAC address used for demo */
static struct uip_eth_addr MacAddress = {{0x3a, 0x1f, 0x34, 0x08, 0x54, 0x54}};

/* The IP address used for demo (ping ...) */
static const uint8_t HostIpAddress[4] = {192,168,1,3};

/* Set the default router's IP address. */
static const uint8_t RoutIpAddress[4] = {192,168,1,1};

/* The NetMask address */
static const uint8_t NetMask[4] = {255, 255, 255, 0};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * Initialize demo application
 */
static void _app_init(void)
{
	printf("P: hello-world application init\n\r");
	hello_world_init();

#ifdef __DHCPC_H__
	printf("P: DHCPC Init\n\r");
	dhcpc_init(MacAddress.addr, 6);
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
	struct timer periodic_timer, arp_timer;
	uint32_t i;

	/* Disable watchdog */
	wdt_disable();

#ifndef VARIANT_DDRAM
	/* Configure DDRAM */
	board_cfg_ddram();
#endif

	printf("-- GMAC uIP Hello World Example %s --\n\r", SOFTPACK_VERSION);
	printf("-- %s\n\r", BOARD_NAME);
	printf("-- Compiled: %s %s --\n\r", __DATE__, __TIME__);

#ifdef AT24_PINS
	pio_configure(at24_pins, ARRAY_SIZE(at24_pins));
	at24_configure(&at24_drv, &at24_twid);
	if (at24_get_mac_address(&at24_drv)) {
		printf("Failed reading MAC address from AT24 EEPROM");
	} else {
		memcpy(MacAddress.addr, at24_drv.mac_addr_48, 6);
	}
#endif

	/* Display MAC & IP settings */
	printf(" - MAC %02x:%02x:%02x:%02x:%02x:%02x\n\r",
			MacAddress.addr[0], MacAddress.addr[1], MacAddress.addr[2],
			MacAddress.addr[3], MacAddress.addr[4], MacAddress.addr[5]);
#ifndef __DHCPC_H__
	printf(" - Host IP  %d.%d.%d.%d\n\r",
			HostIpAddress[0], HostIpAddress[1], HostIpAddress[2], HostIpAddress[3]);
	printf(" - Router IP  %d.%d.%d.%d\n\r",
			RoutIpAddress[0], RoutIpAddress[1], RoutIpAddress[2], RoutIpAddress[3]);
	printf(" - Net Mask  %d.%d.%d.%d\n\r",
			NetMask[0], NetMask[1], NetMask[2], NetMask[3]);
#endif

	/* System devices initialize */
	gmac_tapdev_setmac((uint8_t *)MacAddress.addr);
	gmac_tapdev_init();
	clock_init();
	timer_set(&periodic_timer, CLOCK_SECOND / 2);
	timer_set(&arp_timer, CLOCK_SECOND * 10);

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
	uip_ipaddr(ipaddr, HostIpAddress[0], HostIpAddress[1],
			HostIpAddress[2], HostIpAddress[3]);
	uip_sethostaddr(ipaddr);

	uip_ipaddr(ipaddr, RoutIpAddress[0], RoutIpAddress[1],
			RoutIpAddress[2], RoutIpAddress[3]);
	uip_setdraddr(ipaddr);

	uip_ipaddr(ipaddr, NetMask[0], NetMask[1], NetMask[2], NetMask[3]);
	uip_setnetmask(ipaddr);
#endif

	uip_setethaddr(MacAddress);

	_app_init();

	while(1) {
		uip_len = gmac_tapdev_read();
		if(uip_len > 0) {
			if(BUF->type == htons(UIP_ETHTYPE_IP)) {
				uip_arp_ipin();
				uip_input();
				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if(uip_len > 0) {
					uip_arp_out();
					gmac_tapdev_send();
				}
			} else if(BUF->type == htons(UIP_ETHTYPE_ARP)) {
				uip_arp_arpin();
				/* If the above function invocation resulted in data that
				should be sent out on the network, the global variable
				uip_len is set to a value > 0. */
				if(uip_len > 0) {
					gmac_tapdev_send();
				}
			}
		} else if(timer_expired(&periodic_timer)) {
			timer_reset(&periodic_timer);
			for(i = 0; i < UIP_CONNS; i++) {
				uip_periodic(i);
				/* If the above function invocation resulted in data that
				   should be sent out on the network, the global variable
				   uip_len is set to a value > 0. */
				if(uip_len > 0) {
					uip_arp_out();
					gmac_tapdev_send();
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
					gmac_tapdev_send();
				}
			}
#endif /* UIP_UDP */

			/* Call the ARP timer function every 10 seconds. */
			if(timer_expired(&arp_timer)) {
				timer_reset(&arp_timer);
				uip_arp_timer();
			}
		}
	}
}
