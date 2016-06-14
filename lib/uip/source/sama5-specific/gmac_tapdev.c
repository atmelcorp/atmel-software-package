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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "board.h"
#include "trace.h"
#if defined(CONFIG_HAVE_EMAC)
#include "peripherals/emacd.h"
#elif defined(CONFIG_HAVE_GMAC)
#include "peripherals/gmacd.h"
#endif
#include "peripherals/pio.h"
#include "network/phy.h"

#include "uip.h"
#include "uip_arp.h"

#include "gmac_tapdev.h"

#include <string.h>
#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

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

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

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

/* MAC address used for demo */
static uint8_t gEthMacAddress[6] = {0x00, 0x45, 0x56, 0x78, 0x9a, 0xbc};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * Set the MAC address of the system.
 * Should only be called before tapdev_init is called.
 */
void eth_tapdev_setmac(u8_t *addr)
{
	gEthMacAddress[0] = addr[0];
	gEthMacAddress[1] = addr[1];
	gEthMacAddress[2] = addr[2];
	gEthMacAddress[3] = addr[3];
	gEthMacAddress[4] = addr[4];
	gEthMacAddress[5] = addr[5];
}

/**
 * Initialization for GMAC device.
 * Should be called at the beginning of the program to set up the
 * network interface.
 */
void eth_tapdev_init(void)
{
	/* Init GMAC */
	pio_configure(eth_pins, ARRAY_SIZE(eth_pins));
	ethd_configure(&_ethd, ETH_TYPE, ETH_ADDR, 1, 0);
	ethd_setup_queue(&_ethd, 0, RX_BUFFERS, pGRxBuffer, gGRxDs,
			TX_BUFFERS, pGTxBuffer, gGTxDs, NULL);
	ethd_set_mac_addr(&_ethd, 0, gEthMacAddress);
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
 * Read for ETH device.
 */
uint32_t eth_tapdev_read(void)
{
	uint32_t pkt_len = 0;
	uint8_t rc = ethd_poll(&_ethd, 0, (uint8_t*)uip_buf,
			UIP_CONF_BUFFER_SIZE, &pkt_len);
	if (rc != ETH_OK)
		return 0;
	return pkt_len;
}

/**
 * Send to ETH device
 */
void eth_tapdev_send(void)
{
	uint8_t rc = ethd_send(&_ethd, 0, (void*)uip_buf, uip_len, NULL);
	if (rc != ETH_OK)
	{
		trace_error("E: Send, rc 0x%x\n\r", rc);
	}
}








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
 * search-and-replace for the word "gmacif" to replace it with
 * something that better describes your network interface.
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/


