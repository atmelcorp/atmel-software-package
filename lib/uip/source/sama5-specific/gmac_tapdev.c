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

#include "peripherals/gmacd.h"
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

/*----------------------------------------------------------------------------
 *        Variables
 *----------------------------------------------------------------------------*/

/* The GMAC driver instance */
static struct _gmacd _gmacd;

/* The PHY driver config */
static const struct _phy_desc _phy_desc = {
	.addr = GMAC0_ADDR,
	.retries = GMAC0_PHY_RETRIES,
	.phy_addr = GMAC0_PHY_ADDR
};

/* The PHY driver instance */
static struct _phy _phy = {
	.desc = &_phy_desc
};

/** TX descriptors list */
ALIGNED(8) SECTION(".region_ddr_nocache")
static struct _gmac_desc gGTxDs[TX_BUFFERS];

/** RX descriptors list */
ALIGNED(8) SECTION(".region_ddr_nocache")
static struct _gmac_desc gGRxDs[RX_BUFFERS];

/** TX Buffers */
ALIGNED(32) SECTION(".region_ddr")
static uint8_t pGTxBuffer[TX_BUFFERS * GMAC_TX_UNITSIZE];

/** RX Buffers */
ALIGNED(32) SECTION(".region_ddr")
static uint8_t pGRxBuffer[RX_BUFFERS * GMAC_RX_UNITSIZE];

/* MAC address used for demo */
static uint8_t gGMacAddress[6] = {0x00, 0x45, 0x56, 0x78, 0x9a, 0xbc};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * Set the MAC address of the system.
 * Should only be called before tapdev_init is called.
 */
void gmac_tapdev_setmac(u8_t *addr)
{
	gGMacAddress[0] = addr[0];
	gGMacAddress[1] = addr[1];
	gGMacAddress[2] = addr[2];
	gGMacAddress[3] = addr[3];
	gGMacAddress[4] = addr[4];
	gGMacAddress[5] = addr[5];
}

/**
 * Initialization for GMAC device.
 * Should be called at the beginning of the program to set up the
 * network interface.
 */
void gmac_tapdev_init(void)
{
	/* Init GMAC */
	const struct _pin gmac_pins[] = GMAC0_PINS;
	pio_configure(gmac_pins, ARRAY_SIZE(gmac_pins));
	gmacd_configure(&_gmacd, GMAC0_ADDR, 1, 0);
	gmacd_setup_queue(&_gmacd, 0, RX_BUFFERS, pGRxBuffer, gGRxDs,
			TX_BUFFERS, pGTxBuffer, gGTxDs, NULL);
	gmac_set_mac_addr(_gmacd.gmac, 0, gGMacAddress);
	gmacd_start(&_gmacd);

	/* Init PHY */
	phy_configure(&_phy);
	if (phy_auto_negotiate(&_phy, 5000)) {
		printf( "P: Link detected \n\r");
	} else {
		printf( "P: Auto Negotiate ERROR!\n\r");
	}
}

/**
 * Read for GMAC device.
 */
uint32_t gmac_tapdev_read(void)
{
	uint32_t pkt_len = 0;
	uint8_t rc = gmacd_poll(&_gmacd, 0, (uint8_t*)uip_buf,
			UIP_CONF_BUFFER_SIZE, &pkt_len);
	if (rc != GMACD_OK)
		return 0;
	return pkt_len;
}

/**
 * Send to GMAC device
 */
void gmac_tapdev_send(void)
{
	uint8_t rc = gmacd_send(&_gmacd, 0, (void*)uip_buf, uip_len, NULL);
	if (rc != GMACD_OK)
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


