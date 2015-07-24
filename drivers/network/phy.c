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

/** \file */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "chip.h"
#include "trace.h"

#include "peripherals/gmac.h"
#include "network/phy.h"
#include "network/gmii.h"

/*---------------------------------------------------------------------------
 *         Constants
 *---------------------------------------------------------------------------*/

#define GMII_ID2_MASK (~0xf)

struct _phy_dev {
	const char* name;
	uint16_t id1;
	uint16_t id2;
};

static const struct _phy_dev _phy_devices[] = {
	{ "Micrel KSZ8081", 0x0022, 0x1560 },
	{ "Micrel KSZ8061", 0x0022, 0x1570 },
};

/*---------------------------------------------------------------------------
 *         Local functions
 *---------------------------------------------------------------------------*/

static const struct _phy_dev* _phy_find_dev(uint16_t id1, uint16_t id2)
{
	int i;
	id2 = id2 & GMII_ID2_MASK;
	for (i = 0; i < ARRAY_SIZE(_phy_devices); i++) {
		if (_phy_devices[i].id1 == id1 &&
				_phy_devices[i].id2 == id2) {
			return &_phy_devices[i];
		}
	}
	return NULL;
}

static bool _phy_get_id(Gmac* gmac, uint8_t phy_addr, uint32_t retries,
		uint16_t* id1, uint16_t* id2)
{
	return gmac_phy_read(gmac, phy_addr, GMII_PHYID1R, id1, retries) &&
		gmac_phy_read(gmac, phy_addr, GMII_PHYID2R, id2, retries);
}

static bool _phy_find_addr(struct _phy* phy)
{
	uint8_t phy_addr;
	uint16_t id1, id2;
	const struct _phy_dev *dev;
	int i;

	gmac_enable_mdio(phy->desc->addr);

	/* start searching at desc->phy_addr */
	phy_addr = phy->desc->phy_addr;
	dev = NULL;
	for (i = 0; i < 32; i++) {
		id1 = id2 = 0;
		if (_phy_get_id(phy->desc->addr, phy_addr,
					phy->desc->retries, &id1, &id2)) {
			dev = _phy_find_dev(id1, id2);
			if (dev)
				break;
		}
		printf("addr=0x%02x id1=0x%04x id2=0x%04x\r\n",
				phy_addr, id1, id2);
		phy_addr = (phy_addr + 1) & 0x1F;
	}

	if (dev) {
		trace_info("Found %s PHY at address 0x%02x\r\n",
				dev->name,phy_addr);
		phy->phy_addr = phy_addr;
	} else {
		trace_error("No known PHY detected\r\n");
		phy->phy_addr = 0xff;
	}

	gmac_disable_mdio(phy->desc->addr);

	return dev != NULL;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

bool phy_configure(struct _phy* phy)
{
	if (!_phy_find_addr(phy))
		return false;
	return phy_reset(phy);
}

bool phy_get_id(const struct _phy* phy, uint16_t* id1, uint16_t* id2)
{
	return _phy_get_id(phy->desc->addr, phy->phy_addr, phy->desc->retries,
			id1, id2);
}

bool phy_reset(const struct _phy* phy)
{
	gmac_enable_mdio(phy->desc->addr);

	gmac_phy_write(phy->desc->addr, phy->phy_addr, GMII_BMCR,
			GMII_RESET, phy->desc->retries);

	uint32_t timeout = 10;
	uint16_t bmcr = GMII_RESET;
	do {
		gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_BMCR,
				&bmcr, phy->desc->retries);
		timeout--;
	} while ((bmcr & GMII_RESET) && timeout);

	gmac_disable_mdio(phy->desc->addr);

	return timeout != 0;
}

void phy_dump_registers(const struct _phy* phy)
{
	uint16_t value;

	trace_info_wp(" -- GMII Registers @0x%02x --\r\n", phy->phy_addr);

	gmac_enable_mdio(phy->desc->addr);

	gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_BMCR, &value,
			phy->desc->retries);
	trace_info_wp(" - BMCR     : 0x%x\r\n", (unsigned)value);

	gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_BMSR, &value,
			phy->desc->retries);
	trace_info_wp(" - BMSR     : 0x%x\r\n", (unsigned)value);

	gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_ANAR, &value,
			phy->desc->retries);
	trace_info_wp(" - ANAR     : 0x%x\r\n", (unsigned)value);

	gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_ANLPAR, &value,
			phy->desc->retries);
	trace_info_wp(" - ANLPAR   : 0x%x\r\n", (unsigned)value);

	gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_ANER, &value,
			phy->desc->retries);
	trace_info_wp(" - ANER     : 0x%x\r\n", (unsigned)value);

	gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_ANNPR, &value,
			phy->desc->retries);
	trace_info_wp(" - ANNPR    : 0x%x\r\n", (unsigned)value);

	gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_ANLPNPAR, &value,
			phy->desc->retries);
	trace_info_wp(" - ANLPNPAR : 0x%x\r\n", (unsigned)value);

	gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_RXERCR, &value,
			phy->desc->retries);
	trace_info_wp(" - RXERCR   : 0x%x\r\n", (unsigned)value);

	gmac_phy_read(phy->desc->addr, phy->phy_addr, GMII_ICSR, &value,
			phy->desc->retries);
	trace_info_wp(" - ICSR     : 0x%x\r\n", (unsigned)value);

	gmac_disable_mdio(phy->desc->addr);
}

bool phy_auto_negotiate(const struct _phy* phy)
{
	bool rc = false;
	uint16_t value;

	gmac_enable_mdio(phy->desc->addr);

	/* Set the Auto_negotiation Advertisement Register, MII advertising for
	 * Next page, 100BaseTxFD and HD, 10BaseTFD and HD, IEEE 802.3 */
	value = 0;
	if (!gmac_phy_read(phy->desc->addr, phy->desc->phy_addr, GMII_ANAR,
				&value, phy->desc->retries)) {
		trace_error("Error reading PHY ANAR\r\n");
		goto exit;
	}

	value = GMII_TX_FDX | GMII_TX_HDX |
		GMII_10_FDX | GMII_10_HDX | GMII_AN_IEEE_802_3;
	if (!gmac_phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_ANAR,
				value, phy->desc->retries)) {
		trace_error("Error writing PHY ANAR\r\n");
		goto exit;
	}

	/* Read & modify control register */
	value = 0;
	if (!gmac_phy_read(phy->desc->addr, phy->desc->phy_addr, GMII_BMCR,
				&value, phy->desc->retries)) {
		trace_error("Error reading PHY BMCR\r\n");
		goto exit;
	}

	/* Check AutoNegotiate complete */
	value |= GMII_AUTONEG | GMII_RESTART_AUTONEG;
	if (!gmac_phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_BMCR,
				value, phy->desc->retries)) {
		trace_error("Error writing PHY BMCR\r\n");
		goto exit;
	}

	/* Wait for auto-negotiation completion */
	while (1) {
		if (!gmac_phy_read(phy->desc->addr, phy->desc->phy_addr,
					GMII_BMSR, &value, phy->desc->retries)) {
			trace_error("Error reading PHY BMSR\r\n");
			goto exit;
		}

		/* auto-negotiation completed */
		if (value & GMII_AUTONEG_COMP)
			break;

		// TODO timeout
	}

	/* Set local link mode */
	while (1) {
		if (!gmac_phy_read(phy->desc->addr, phy->desc->phy_addr,
					GMII_ANLPAR, &value, phy->desc->retries)) {
			trace_error("Error reading PHY ANLPAR\r\n");
			goto exit;
		}

		/* Setup the GMAC link speed */
		if (value & GMII_TX_FDX) {
			trace_debug("PHY Auto-Negotiation complete -> 100M/Full-Duplex\r\n");
			gmac_enable_rmii(phy->desc->addr, GMAC_SPEED_100M, GMAC_DUPLEX_FULL);
			rc = true;
			break;
		} else if (value & GMII_10_FDX) {
			trace_debug("PHY Auto-Negotiation complete -> 10M/Full-Duplex\r\n");
			gmac_enable_rmii(phy->desc->addr, GMAC_SPEED_10M, GMAC_DUPLEX_FULL);
			rc = true;
			break;
		} else if (value & GMII_TX_HDX) {
			trace_debug("PHY Auto-Negotiation complete -> 100M/Half-Duplex\r\n");
			gmac_enable_rmii(phy->desc->addr, GMAC_SPEED_100M, GMAC_DUPLEX_HALF);
			rc = true;
			break;
		} else if (value & GMII_10_HDX) {
			trace_debug("PHY Auto-Negotiation complete -> 10M/Half-Duplex\r\n");
			gmac_enable_rmii(phy->desc->addr, GMAC_SPEED_10M, GMAC_DUPLEX_HALF);
			rc = true;
			break;
		}

		// TODO timeout
	}

exit:
	if (!rc) {
		trace_debug("PHY Auto-Negotiation failed!\r\n");
	}
	gmac_disable_mdio(phy->desc->addr);
	return rc;
}
