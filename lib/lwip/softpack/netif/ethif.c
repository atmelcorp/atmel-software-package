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

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethif" to replace it with
 * something that better describes your network interface.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>

#include "board.h"
#include "board_eth.h"
#include "chip.h"
#include "compiler.h"
#include "gpio/pio.h"
#include "lwip/opt.h"
#include "netif/etharp.h"
#include "netif/ethif.h"
#include "network/ethd.h"
#include "network/phy.h"
#include "lwip/def.h"
#if LWIP_DHCP
#include "lwip/dhcp.h"
#endif
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/priv/tcp_priv.h"
#include "lwip/stats.h"
#include "lwip/sys.h"
#include "timer.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/* Timer for calling lwIP tmr functions without system */
typedef struct _timers_info {
	uint32_t timer;
	uint32_t timer_interval;
	void (*timer_func)(void);
} timers_info;

/*---------------------------------------------------------------------------
 *         Variables
 *---------------------------------------------------------------------------*/

/* lwIP tmr functions list */
static timers_info timers_table[] = {
	/* LWIP_TCP */
#if LWIP_TCP
	{ 0, TCP_FAST_INTERVAL,     tcp_fasttmr},
	{ 0, TCP_SLOW_INTERVAL,     tcp_slowtmr},
#endif
	/* LWIP_ARP */
#if LWIP_ARP
	{ 0, ARP_TMR_INTERVAL,      etharp_tmr},
#endif
	/* LWIP_DHCP */
#if LWIP_DHCP
	{ 0, DHCP_COARSE_TIMER_SECS, dhcp_coarse_tmr},
	{ 0, DHCP_FINE_TIMER_MSECS,  dhcp_fine_tmr},
#endif
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 * Process timing functions
 */
static void timers_update(void)
{
	static uint32_t last_time;
	uint32_t cur_time, time_diff, idxtimer;
	timers_info * ptmr_inf;

	cur_time = timer_get_tick();
	if (cur_time >= last_time)
		time_diff = cur_time - last_time;
	else
		time_diff = 0xFFFFFFFF - last_time + cur_time;

	if (time_diff) {
		last_time = cur_time;
		for (idxtimer = 0;
			idxtimer < (sizeof(timers_table)/sizeof(timers_info));
			idxtimer++) {
			ptmr_inf = &timers_table[idxtimer];
			ptmr_inf->timer += time_diff;
			if (ptmr_inf->timer > ptmr_inf->timer_interval) {
				if (ptmr_inf->timer_func)
					ptmr_inf->timer_func();
				ptmr_inf->timer -= ptmr_inf->timer_interval;
			}
		}
	}
}

/* Forward declarations. */
static void  ethif_input(struct netif *netif);
static err_t ethif_output(struct netif *netif, struct pbuf *p, ip4_addr_t *ipaddr);

static void glow_level_init(struct netif *netif, struct _ethd* ethd)
{
	uint8_t _mac_addr[6];

	/* set MAC hardware address length */
	netif->hwaddr_len = sizeof(netif->hwaddr);
	/* set MAC hardware address */
	ethd_get_mac_addr(ethd, 0, _mac_addr);
	SMEMCPY(netif->hwaddr, _mac_addr, sizeof(netif->hwaddr));
	/* maximum transfer unit */
	netif->mtu = 1500;
	/* device capabilities */
	netif->flags = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET| NETIF_FLAG_LINK_UP;
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 */
static err_t glow_level_output(struct netif *netif, struct pbuf *p)
{

    struct pbuf *q;
    uint8_t buf[1514];
    uint8_t *bufptr = &buf[0];
    uint8_t rc;

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE);    /* drop the padding word */
#endif

    for(q = p; q != NULL; q = q->next) {
        /* Send the data from the pbuf to the interface, one pbuf at a
        time. The size of the data in each pbuf is kept in the ->len
        variable. */

        /* send data from(q->payload, q->len); */
        memcpy(bufptr, q->payload, q->len);
        bufptr += q->len;
    }

    /* signal that packet should be sent(); */
    rc = ethd_send(board_get_eth(netif->num), 0, buf, p->tot_len, NULL);
    if (rc != ETH_OK) {
        return ERR_BUF;
    }
#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE);     /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.xmit);
    return ERR_OK;

}

/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
static struct pbuf *glow_level_input(struct netif *netif)
{
    struct pbuf *p, *q;
    u16_t len;
    uint8_t buf[1514];
    uint8_t *bufptr = &buf[0];

    uint32_t frmlen;
    uint8_t rc;

    /* Obtain the size of the packet and put it into the "len"
       variable. */
    rc = ethd_poll(board_get_eth(netif->num), 0, buf, (uint32_t)sizeof(buf), (uint32_t*)&frmlen);
    if (rc != ETH_OK)
    {
      return NULL;
    }
    len = frmlen;

#if ETH_PAD_SIZE
    len += ETH_PAD_SIZE;      /* allow room for Ethernet padding */
#endif

    /* We allocate a pbuf chain of pbufs from the pool. */
    p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);

    if (p != NULL) {
#if ETH_PAD_SIZE
        pbuf_header(p, -ETH_PAD_SIZE);          /* drop the padding word */
#endif
        /* We iterate over the pbuf chain until we have read the entire
         * packet into the pbuf. */
        for(q = p; q != NULL; q = q->next) {
            /* Read enough bytes to fill this pbuf in the chain. The
             * available data in the pbuf is given by the q->len
             * variable. */
            /* read data into(q->payload, q->len); */
            memcpy(q->payload, bufptr, q->len);
            bufptr += q->len;
        }
        /* acknowledge that packet has been read(); */

#if ETH_PAD_SIZE
        pbuf_header(p, ETH_PAD_SIZE);           /* reclaim the padding word */
#endif
        LINK_STATS_INC(link.recv);
    } else {
        /* drop packet(); */
        LINK_STATS_INC(link.memerr);
        LINK_STATS_INC(link.drop);
    }
    return p;
}

/**
 * This function is called by the TCP/IP stack when an IP packet
 * should be sent. It calls the function called glow_level_output() to
 * do the actual transmission of the packet.
 *
 */
static err_t ethif_output(struct netif *netif, struct pbuf *p, ip4_addr_t *ipaddr)
{
    /* resolve hardware address, then send (or queue) packet */
    return etharp_output(netif, p, ipaddr);
}
/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethif
 */

static void ethif_input(struct netif *netif)
{
    struct eth_hdr *ethhdr;
    struct pbuf *p;

    /* move received packet into a new pbuf */
    p = glow_level_input(netif);
    /* no packet could be read, silently ignore this */
    if (p == NULL) return;
    /* points to packet payload, which starts with an Ethernet header */
    ethhdr = p->payload;

    switch (htons(ethhdr->type)) {
        /* IP packet? */
        case ETHTYPE_IP:
            /* skip Ethernet header */
            pbuf_header(p, -(s16_t)sizeof(struct eth_hdr));
            /* pass to network layer */
            netif->input(p, netif);
            break;

        case ETHTYPE_ARP:
            /* pass p to ARP module  */
		  	ethernet_input(p, netif);
            break;
        default:
            pbuf_free(p);
            p = NULL;
            break;
        }

}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function glow_level_init() to do the
 * actual setup of the hardware.
 *
 */
err_t ethif_init(struct netif *netif)
{
	netif->name[0] = IFNAME0;
	netif->name[1] = IFNAME1;
	netif->output = (netif_output_fn) ethif_output;
	netif->linkoutput = glow_level_output;
	glow_level_init(netif, board_get_eth(netif->num));
	etharp_init();
	return ERR_OK;
}

/**
 * Polling task
 * Should be called periodically
 *
 */
void ethif_poll(struct netif *netif)
{
	/* Run periodic tasks */
	timers_update();

	ethif_input(netif);
}
