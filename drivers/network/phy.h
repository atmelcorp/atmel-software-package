/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2012-2016, Atmel Corporation
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

/** \file */

/** \addtogroup phy_module Ethernet PHY Driver
 *@{
 *  Implement PHY driver, that initializes the PHY to prepare for
 *  ethernet transfer.
 *
 *  \section Usage
 *  -# GMAC related pins and Driver should be initialized at first.
 *  -# Configure PHY via phy_configure(), PHY address is
 *     automatically adjusted by attempt to read.
 *  -# Perform PHY auto negotiate through phy_auto_negotiate(), so
 *     connection established.
 *
 *
 *  Related files:\n
 *  \ref phy.h\n
 *  \ref phy.c\n
 *  \ref gmii.h.\n
 *
 */
/**@}*/

#ifndef _PHY_H
#define _PHY_H

#ifdef CONFIG_HAVE_ETH

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include <stdint.h>
#include "network/ethd.h"

/*---------------------------------------------------------------------------
 *         Definitions
 *---------------------------------------------------------------------------*/

/** Default timeouts */
#define PHY_DEFAULT_TIMEOUT_IDLE    500
#define PHY_DEFAULT_TIMEOUT_AUTONEG 5000

enum _phy_if_eth {
	PHY_IF_EMAC,
	PHY_IF_GMAC,
};

/*---------------------------------------------------------------------------
 *         Types
 *---------------------------------------------------------------------------*/

struct _phy_desc {
	void* addr;       /**< ETH instance (GMAC/EMAC) */
	enum _phy_if_eth phy_if;
	uint8_t phy_addr; /**< PHY address (configured) */
	struct {
		uint32_t idle;    /**< idle timeout */
		uint32_t autoneg; /**< auto-negociation timeout */
	} timeout;
};

typedef void (*eth_enable_mdio)(void* eth);
typedef void (*eth_disable_mdio)(void* eth);
typedef int (*eth_phy_read)(void* eth, uint8_t phy_addr, uint8_t reg_addr,
		uint16_t* data, uint32_t idle_timeout);
typedef int (*eth_phy_write)(void* eth, uint8_t phy_addr, uint8_t reg_addr,
		uint16_t data, uint32_t idle_timeout);
typedef void (*eth_enable_rmii)(void* eth, enum _eth_speed speed, enum _eth_duplex duplex);

struct _eth_phy_op {
	eth_phy_read phy_read;
	eth_phy_write phy_write;
	eth_enable_mdio enable_mido;
	eth_disable_mdio disable_mido;
	eth_enable_rmii enable_rmii;
};

struct _phy {
	const struct _phy_desc* desc;
	const struct _phy_dev* dev;
	uint8_t phy_addr; /**< PHY address (actual) */
	const struct _eth_phy_op* op;
};

/*---------------------------------------------------------------------------
 *         Exported functions
 *---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

extern int phy_configure(struct _phy* phy);

extern int phy_get_id(const struct _phy* phy, uint16_t* id1, uint16_t* id2);

extern int phy_reset(const struct _phy* phy);

extern int phy_powerdown(const struct _phy* phy);

extern int phy_auto_negotiate(const struct _phy* phy, bool block);

extern int phy_auto_negotiate_wait_for_completion(const struct _phy* phy);

extern int phy_set_speed_duplex(const struct _phy* phy, enum _eth_speed speed, enum _eth_duplex duplex);

extern void phy_dump_registers(const struct _phy* phy);


#ifdef __cplusplus
}
#endif

#endif /* CONFIG_HAVE_ETH */

#endif /* _PHY_H_ */
