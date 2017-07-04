/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015-2016, Atmel Corporation
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
 * \file
 *
 * Implementation of memories configuration on board.
 *
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "board_eth.h"
#include "board_twi.h"
#include "trace.h"

#include "gpio/pio.h"
#include "mm/cache.h"
#include "network/ethd.h"
#include "network/phy.h"
#include "nvm/i2c/at24.h"

#include <string.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/* Number of buffer for RX */
#define ETH_RX_BUFFERS  16

/* Number of buffer for TX */
#define ETH_TX_BUFFERS  8

#ifndef BOARD_ETH0_PHY_IDLE_TIMEOUT
#define BOARD_ETH0_PHY_IDLE_TIMEOUT PHY_DEFAULT_TIMEOUT_IDLE
#endif

#ifndef BOARD_ETH0_PHY_AUTONEG_TIMEOUT
#define BOARD_ETH0_PHY_AUTONEG_TIMEOUT PHY_DEFAULT_TIMEOUT_AUTONEG
#endif

#ifndef BOARD_ETH1_PHY_IDLE_TIMEOUT
#define BOARD_ETH1_PHY_IDLE_TIMEOUT PHY_DEFAULT_TIMEOUT_IDLE
#endif

#ifndef BOARD_ETH1_PHY_AUTONEG_TIMEOUT
#define BOARD_ETH1_PHY_AUTONEG_TIMEOUT PHY_DEFAULT_TIMEOUT_AUTONEG
#endif

/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/

/* The ETH driver instance */
static struct _ethd _ethd[ETH_IFACE_COUNT];

/* The PHY driver config */
static const struct _phy_desc _phy_desc[] = {
	{
		.addr = BOARD_ETH0_ADDR,
		.phy_if = BOARD_ETH0_PHY_IF,
		.phy_addr = BOARD_ETH0_PHY_ADDR,
		.timeout = {
			.idle = BOARD_ETH0_PHY_IDLE_TIMEOUT,
			.autoneg = BOARD_ETH0_PHY_AUTONEG_TIMEOUT,
		},
	},
#if defined(BOARD_ETH1_ADDR) && (ETH_IFACE_COUNT > 1)
	{
		.addr = BOARD_ETH1_ADDR,
		.phy_if = BOARD_ETH1_PHY_IF,
		.phy_addr = BOARD_ETH1_PHY_ADDR,
		.timeout = {
			.idle = BOARD_ETH1_PHY_IDLE_TIMEOUT,
			.autoneg = BOARD_ETH1_PHY_AUTONEG_TIMEOUT,
		},
	},
#endif
};

/* The PHY driver instance */
static struct _phy _phy[] = {
	{
		.desc = &_phy_desc[0]
	},
#if defined(BOARD_ETH1_ADDR) && (ETH_IFACE_COUNT > 1)
	{
		.desc = &_phy_desc[1]
	},
#endif
};

/** TX descriptors list */
ALIGNED(8) NOT_CACHED
static struct _eth_desc eth_txd[ETH_IFACE_COUNT][ETH_TX_BUFFERS];

/** RX descriptors list */
ALIGNED(8) NOT_CACHED
static struct _eth_desc eth_rxd[ETH_IFACE_COUNT][ETH_RX_BUFFERS];

/** TX Buffers */
CACHE_ALIGNED_DDR
static uint8_t eth_tx_buffer[ETH_IFACE_COUNT][ETH_TX_BUFFERS * ETH_TX_UNITSIZE];

/** RX Buffers */
CACHE_ALIGNED_DDR
static uint8_t eth_rx_buffer[ETH_IFACE_COUNT][ETH_RX_BUFFERS * ETH_RX_UNITSIZE];

/** TX callbacks list */
static ethd_callback_t eth_tx_callback[ETH_IFACE_COUNT][ETH_TX_BUFFERS];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _eth_rx_callback(uint8_t queue, uint32_t status)
{
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

void board_cfg_net(uint8_t iface, uint8_t* mac_addr, bool block)
{
#ifdef CONFIG_HAVE_ETH
	uint8_t _eth_mac_addr[6];

	/* Init ethernet interface */
	switch (iface) {
	case 0:
	{
		struct _pin eth_pins[] = BOARD_ETH0_PINS;

		pio_configure(eth_pins, ARRAY_SIZE(eth_pins));
		ethd_configure(&_ethd[iface], BOARD_ETH0_TYPE, BOARD_ETH0_ADDR, 1, 0);
		if (mac_addr) {
			memcpy(_eth_mac_addr, mac_addr, sizeof(_eth_mac_addr));
		} else {
#if defined(BOARD_ETH0_MAC_ADDR)
			uint8_t _mac_addr[] = BOARD_ETH0_MAC_ADDR;
			memcpy(_eth_mac_addr, _mac_addr, sizeof(_eth_mac_addr));
#elif defined(BOARD_AT24_TWI_BUS)
			if (at24_has_eui48(board_get_at24()))
				at24_read_eui48(board_get_at24(), _eth_mac_addr);
			else
				trace_error("eth0: no MAC address found");
#else
			trace_error("eth0: no MAC address");
#endif
		}
	}
	break;

#if defined(BOARD_ETH1_ADDR) && (ETH_IFACE_COUNT > 1)
	case 1:
	{
		struct _pin eth_pins[] = BOARD_ETH1_PINS;

		pio_configure(eth_pins, ARRAY_SIZE(eth_pins));
		ethd_configure(&_ethd[iface], BOARD_ETH1_TYPE, BOARD_ETH1_ADDR, 1, 0);
		if (mac_addr) {
			memcpy(_eth_mac_addr, mac_addr, sizeof(_eth_mac_addr));
		} else {
#if defined(BOARD_ETH1_MAC_ADDR)
			uint8_t _mac_addr[] = BOARD_ETH1_MAC_ADDR;
			memcpy(_eth_mac_addr, _mac_addr, sizeof(_eth_mac_addr));
#elif defined(BOARD_AT24_TWI_BUS)
			if (at24_has_eui48(board_get_at24()))
				at24_read_eui48(board_get_at24(), _eth_mac_addr);
			else
				trace_error("eth1: no MAC address found");
#else
			trace_error("eth1: no MAC address");
#endif
		}
	}
	break;
#endif /* BOARD_ETH1_ADDR */
	}

	ethd_setup_queue(&_ethd[iface], 0, ETH_RX_BUFFERS, eth_rx_buffer[iface], eth_rxd[iface],
			 ETH_TX_BUFFERS, eth_tx_buffer[iface], eth_txd[iface], eth_tx_callback[iface]);
	ethd_set_rx_callback(&_ethd[iface], 0, _eth_rx_callback);
	ethd_set_mac_addr(&_ethd[iface], 0, _eth_mac_addr);
	ethd_start(&_ethd[iface]);

	/* Init PHY */
	phy_configure(&_phy[iface]);
	phy_auto_negotiate(&_phy[iface], block);
#endif /* CONFIG_HAVE_ETH */
}

struct _ethd * board_get_eth(uint8_t iface)
{
#ifdef CONFIG_HAVE_ETH
	if (iface < ETH_IFACE_COUNT)
		return &_ethd[iface];
#endif /* CONFIG_HAVE_ETH */

	return NULL;
}

struct _phy * board_get_phy(uint8_t iface)
{
#ifdef CONFIG_HAVE_ETH
	if (iface < ETH_IFACE_COUNT)
		return &_phy[iface];
#endif /* CONFIG_HAVE_ETH */

	return NULL;
}
