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

#include "chip.h"
#include "board.h"

#include "compiler.h"

#if defined(CONFIG_HAVE_EMAC)
#include "peripherals/emacd.h"
#elif defined(CONFIG_HAVE_GMAC)
#include "peripherals/gmacd.h"
#endif
#include "peripherals/pio.h"
#include "network/phy.h"

#include "lwip/opt.h"
#include "ethif.h"
#include "lwip/def.h"
#include "lwip/mem.h"
#include "lwip/pbuf.h"
#include "lwip/sys.h"
#include "lwip/stats.h"
#include "netif/etharp.h"

#include <string.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/* Define those to better describe your network interface. */
#define IFNAME0 'e'
#define IFNAME1 'n'

/* Number of buffer for RX */
#define RX_BUFFERS  16

/* Number of buffer for TX */
#define TX_BUFFERS  8

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

static struct ethif Ethif_config;

/* The ETH driver instance */
static struct _ethd _ethd;

const struct _pin eth_pins[] = ETH_PINS;

/* The PHY driver config */
static const struct _phy_desc _phy_desc = {
	.addr = ETH_ADDR,
	.phy_if = ETH_PHY_IF,
	.retries = PHY_DEFAULT_RETRIES,
	.phy_addr = ETH_PHY_ADDR
};

/* The PHY driver instance */
static struct _phy _phy = {
	.desc = &_phy_desc
};

/** TX descriptors list */
ALIGNED(8) SECTION(".region_ddr_nocache")
static struct _eth_desc gGTxDs[TX_BUFFERS];

/** RX descriptors list */
ALIGNED(8) SECTION(".region_ddr_nocache")
static struct _eth_desc gGRxDs[RX_BUFFERS];

/** TX Buffers */
ALIGNED(32) SECTION(".region_ddr")
static uint8_t pGTxBuffer[TX_BUFFERS * ETH_TX_UNITSIZE];

/** RX Buffers */
ALIGNED(32) SECTION(".region_ddr")
static uint8_t pGRxBuffer[RX_BUFFERS * ETH_RX_UNITSIZE];

/** TX callbacks list */
static ethd_callback_t gGTxCbs[TX_BUFFERS];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/* Forward declarations. */
static void  ethif_input(struct netif *netif);
static err_t ethif_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr);

static void glow_level_init(struct netif *netif)
{
    struct ethif *ethif = netif->state;

    /* set MAC hardware address length */
    netif->hwaddr_len = ETHARP_HWADDR_LEN;
    /* set MAC hardware address */
    netif->hwaddr[0] = ethif->ethaddr.addr[0];
    netif->hwaddr[1] = ethif->ethaddr.addr[1];
    netif->hwaddr[2] = ethif->ethaddr.addr[2];
    netif->hwaddr[3] = ethif->ethaddr.addr[3];
    netif->hwaddr[4] = ethif->ethaddr.addr[4];
    netif->hwaddr[5] = ethif->ethaddr.addr[5];
    /* maximum transfer unit */
    netif->mtu = 1500;

    /* device capabilities */
    netif->flags = NETIF_FLAG_BROADCAST;

	/* Init GMAC */
	pio_configure(eth_pins, ARRAY_SIZE(eth_pins));
	ethd_configure(&_ethd, ETH_TYPE, ETH_ADDR, 1, 0);
	ethd_setup_queue(&_ethd, 0, RX_BUFFERS, pGRxBuffer, gGRxDs, TX_BUFFERS, pGTxBuffer, gGTxDs, gGTxCbs);
	ethd_set_mac_addr(&_ethd, 0, Ethif_config.ethaddr.addr);
	ethd_start(&_ethd);

	/* Init PHY */
	phy_configure(&_phy);
	if (phy_auto_negotiate(&_phy, 5000)) {
		printf( "P: Link detected \n\r");
	} else {
		printf( "P: Auto Negotiate ERROR!\n\r");
	}
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
    rc = ethd_send(&_ethd, 0, buf, p->tot_len, NULL);
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
    rc = ethd_poll(&_ethd, 0, buf, (uint32_t)sizeof(buf), (uint32_t*)&frmlen);
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
static err_t ethif_output(struct netif *netif, struct pbuf *p, struct ip_addr *ipaddr)
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
    struct ethif *ethif;
    struct eth_hdr *ethhdr;
    struct pbuf *p;
    ethif = netif->state;

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
            etharp_arp_input(netif, &ethif->ethaddr, p);
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
 * Set the MAC address of the system.
 * Should only be called before ethif_init is called.
 * The stack calls ethif_init after the user calls netif_add
 *
 */

void ethif_setmac(u8_t *addr)
{
    Ethif_config.ethaddr.addr[0] = addr[0];
    Ethif_config.ethaddr.addr[1] = addr[1];
    Ethif_config.ethaddr.addr[2] = addr[2];
    Ethif_config.ethaddr.addr[3] = addr[3];
    Ethif_config.ethaddr.addr[4] = addr[4];
    Ethif_config.ethaddr.addr[5] = addr[5];
}

/**
 * Should be called at the beginning of the program to set up the
 * network interface. It calls the function glow_level_init() to do the
 * actual setup of the hardware.
 *
 */
err_t ethif_init(struct netif *netif)
{
    struct ethif *ethif;
    ethif = &Ethif_config;
    if (ethif == NULL)
    {
        LWIP_DEBUGF(NETIF_DEBUG, ("ethif_init: out of memory\n"));
        return ERR_MEM;
    }
    netif->state = ethif;
    netif->name[0] = IFNAME0;
    netif->name[1] = IFNAME1;
    netif->output = ethif_output;
    netif->linkoutput = glow_level_output;
    glow_level_init(netif);
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
    ethif_input(netif);
}

