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

/** \file */

/*---------------------------------------------------------------------------
 *         Headers
 *---------------------------------------------------------------------------*/

#include "chip.h"
#include "trace.h"
#include "timer.h"

#ifdef CONFIG_HAVE_EMAC
#include "peripherals/emac.h"
#endif
#ifdef CONFIG_HAVE_GMAC
#include "peripherals/gmac.h"
#endif

#include "network/phy.h"
#include "network/gmii.h"

/*---------------------------------------------------------------------------
 *         Constants
 *---------------------------------------------------------------------------*/

#define GMII_ID2_MASK (~0xfu)

enum _phy_model {
	/* Micrel */
	PHY_KSZ8051,
	PHY_KSZ8081,
	PHY_KSZ8061,
	PHY_KSZ9021,
	PHY_KSZ9031,
	/* Davicom */
	PHY_DM9161AEP,
};

struct _phy_dev {
	enum _phy_model model;
	const char* name;
	uint16_t id1;
	uint16_t id2;
};

static const struct _phy_dev _phy_devices[] = {
	{ PHY_KSZ8051,   "Micrel KSZ8051",    0x0022, 0x1550 },
	{ PHY_KSZ8081,   "Micrel KSZ8081",    0x0022, 0x1560 },
	{ PHY_KSZ8061,   "Micrel KSZ8061",    0x0022, 0x1570 },
	{ PHY_KSZ9021,   "Micrel KSZ9021",    0x0022, 0x1610 },
	{ PHY_KSZ9031,   "Micrel KSZ9031",    0x0022, 0x1620 },
	{ PHY_DM9161AEP, "Davicom DM9161AEP", 0x0181, 0xB8A0 },
};

#ifdef CONFIG_HAVE_EMAC
static const struct _eth_phy_op _emac_op = {
	.phy_write = (eth_phy_write)emac_phy_write,
	.phy_read = (eth_phy_read)emac_phy_read,
	.enable_mido = (eth_enable_mdio)emac_enable_mdio,
	.disable_mido = (eth_disable_mdio)emac_disable_mdio,
	.enable_rmii = (eth_enable_rmii)emac_enable_rmii,
};
#endif

#ifdef CONFIG_HAVE_GMAC
static const struct _eth_phy_op _gmac_op = {
	.phy_read = (eth_phy_read)gmac_phy_read,
	.phy_write = (eth_phy_write)gmac_phy_write,
	.enable_mido = (eth_enable_mdio)gmac_enable_mdio,
	.disable_mido = (eth_disable_mdio)gmac_disable_mdio,
	.enable_rmii = (eth_enable_rmii)gmac_enable_rmii,
};
#endif

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

static bool _phy_get_id(const struct _phy* phy, void* eth, uint8_t phy_addr,
		uint32_t retries, uint16_t* id1, uint16_t* id2)
{
	return phy->op->phy_read(eth, phy_addr, GMII_PHYID1R, id1, retries) &&
		phy->op->phy_read(eth, phy_addr, GMII_PHYID2R, id2, retries);
}

static bool _phy_find_addr(struct _phy* phy)
{
	uint8_t phy_addr;
	uint16_t id1, id2;
	const struct _phy_dev *dev;
	int i;

	phy->op->enable_mido(phy->desc->addr);

	/* start searching at desc->phy_addr */
	phy_addr = phy->desc->phy_addr;
	dev = NULL;
	for (i = 0; i < 32; i++) {
		id1 = id2 = 0;
		if (_phy_get_id(phy, phy->desc->addr, phy_addr,
					phy->desc->retries, &id1, &id2)) {
			dev = _phy_find_dev(id1, id2);
			if (dev)
				break;
		}
		phy_addr = (phy_addr + 1) & 0x1F;
	}

	if (dev) {
		trace_info("Found PHY %s at 0x%02x\r\n",
				dev->name, phy_addr);
		phy->dev = dev;
		phy->phy_addr = phy_addr;
	} else {
		trace_error("No known PHY detected\r\n");
		phy->phy_addr = 0xff;
	}

	phy->op->disable_mido(phy->desc->addr);

	return dev != NULL;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

bool phy_configure(struct _phy* phy)
{
	phy->op = NULL;
#ifdef CONFIG_HAVE_EMAC
	if (PHY_IF_EMAC == phy->desc->phy_if)
		phy->op = &_emac_op;
#endif
#ifdef CONFIG_HAVE_GMAC
	if (PHY_IF_GMAC == phy->desc->phy_if)
		phy->op = &_gmac_op;
#endif

	if (phy->op == NULL)
		return false;

	if (!_phy_find_addr(phy))
		return false;

	if (!phy_reset(phy))
		return false;

	return phy_reset_omsor(phy);
}

bool phy_get_id(const struct _phy* phy, uint16_t* id1, uint16_t* id2)
{
	return _phy_get_id(phy, phy->desc->addr, phy->phy_addr, phy->desc->retries,
			id1, id2);
}

bool phy_reset(const struct _phy* phy)
{
	phy->op->enable_mido(phy->desc->addr);

	phy->op->phy_write(phy->desc->addr, phy->phy_addr, GMII_BMCR,
			GMII_RESET, phy->desc->retries);

	uint32_t timeout = 10;
	uint16_t bmcr = GMII_RESET;
	do {
		phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_BMCR,
				&bmcr, phy->desc->retries);
		timeout--;
	} while ((bmcr & GMII_RESET) && timeout);

	phy->op->disable_mido(phy->desc->addr);

	return timeout != 0;
}

bool phy_reset_omsor(const struct _phy* phy)
{
	uint16_t value, temp, timeout;

	phy->op->enable_mido(phy->desc->addr);

	/* Reconfig OMSOR */
	phy->op->phy_read(phy->desc->addr, phy->phy_addr,  GMII_OMSOR, &value,
	                  phy->desc->retries);

	/* Override strap-in for RMII mode */
	value = GMII_RMII_OVERRIDE;
	timeout = 10;
	do {
		phy->op->phy_write(phy->desc->addr, phy->phy_addr, GMII_OMSOR, value,
		                   phy->desc->retries);
		phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_OMSOR, &temp,
		                  phy->desc->retries);
		timeout--;
	} while ((temp != GMII_RMII_OVERRIDE) && timeout);

	phy->op->disable_mido(phy->desc->addr);

	return timeout != 0;
}

void phy_dump_registers(const struct _phy* phy)
{
	uint16_t value;

	trace_info_wp(" -- GMII Registers @0x%02x --\r\n", phy->phy_addr);

	phy->op->enable_mido(phy->desc->addr);

	phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_BMCR, &value,
			phy->desc->retries);
	trace_info_wp(" - BMCR     : 0x%x\r\n", (unsigned)value);

	phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_BMSR, &value,
			phy->desc->retries);
	trace_info_wp(" - BMSR     : 0x%x\r\n", (unsigned)value);

	phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_ANAR, &value,
			phy->desc->retries);
	trace_info_wp(" - ANAR     : 0x%x\r\n", (unsigned)value);

	phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_ANLPAR, &value,
			phy->desc->retries);
	trace_info_wp(" - ANLPAR   : 0x%x\r\n", (unsigned)value);

	phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_ANER, &value,
			phy->desc->retries);
	trace_info_wp(" - ANER     : 0x%x\r\n", (unsigned)value);

	phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_ANNPR, &value,
			phy->desc->retries);
	trace_info_wp(" - ANNPR    : 0x%x\r\n", (unsigned)value);

	phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_ANLPNPAR, &value,
			phy->desc->retries);
	trace_info_wp(" - ANLPNPAR : 0x%x\r\n", (unsigned)value);

	phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_RXERCR, &value,
			phy->desc->retries);
	trace_info_wp(" - RXERCR   : 0x%x\r\n", (unsigned)value);

	phy->op->phy_read(phy->desc->addr, phy->phy_addr, GMII_ICSR, &value,
			phy->desc->retries);
	trace_info_wp(" - ICSR     : 0x%x\r\n", (unsigned)value);

	phy->op->disable_mido(phy->desc->addr);
}

bool phy_auto_negotiate(const struct _phy* phy, uint32_t time_out)
{
	bool rc = false;
	uint16_t value;
	uint32_t tick_start;

	uint16_t base_tc, base_ts;

	phy->op->enable_mido(phy->desc->addr);

	if (phy->dev->model == PHY_KSZ9021 || phy->dev->model == PHY_KSZ9031) {
		value = GMII_RCCPSR | 0x8000;
		phy->op->phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_ERCR,
					value, phy->desc->retries);

		value = 0xF2F4;
		phy->op->phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_ERDWR,
					value, phy->desc->retries);

		value = GMII_RRDPSR | 0x8000;
		phy->op->phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_ERCR,
					value, phy->desc->retries);

		value = 0x2222;
		phy->op->phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_ERDWR,
					value, phy->desc->retries);

		value = 0xFF00;
		phy->op->phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_ICSR,
					value, phy->desc->retries);

		/* Read & modify 1000Base-T control register  */
		phy->op->phy_read(phy->desc->addr, phy->desc->phy_addr, GMII_1000BTCR,
					&base_tc, phy->desc->retries);
		base_tc |= GMII_1000BaseT_HALF_DUPLEX | GMII_1000BaseT_FULL_DUPLEX;
		phy->op->phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_1000BTCR,
				base_tc, phy->desc->retries);

	}
	/* Set the Auto_negotiation Advertisement Register, MII advertising for
	 * Next page, 100BaseTxFD and HD, 10BaseTFD and HD, IEEE 802.3 */
	value = 0;
	if (!phy->op->phy_read(phy->desc->addr, phy->desc->phy_addr, GMII_ANAR,
				&value, phy->desc->retries)) {
		trace_error("Error reading PHY ANAR\r\n");
		goto exit;
	}

	value = GMII_TX_FDX | GMII_TX_HDX |
		GMII_10_FDX | GMII_10_HDX | GMII_AN_IEEE_802_3;
	if (!phy->op->phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_ANAR,
				value, phy->desc->retries)) {
		trace_error("Error writing PHY ANAR\r\n");
		goto exit;
	}

	/* Read & modify control register */
	value = 0;
	if (!phy->op->phy_read(phy->desc->addr, phy->desc->phy_addr, GMII_BMCR,
				&value, phy->desc->retries)) {
		trace_error("Error reading PHY BMCR\r\n");
		goto exit;
	}

	/* Check AutoNegotiate complete */
	value |= GMII_AUTONEG | GMII_RESTART_AUTONEG;
	if (!phy->op->phy_write(phy->desc->addr, phy->desc->phy_addr, GMII_BMCR,
				value, phy->desc->retries)) {
		trace_error("Error writing PHY BMCR\r\n");
		goto exit;
	}


	/* Wait for auto-negotiation completion */
	tick_start = timer_get_tick();
	while (1) {
		if (!phy->op->phy_read(phy->desc->addr, phy->desc->phy_addr,
					GMII_BMSR, &value, phy->desc->retries)) {
			trace_error("Error reading PHY BMSR\r\n");
			goto exit;
		}

		/* auto-negotiation completed */
		if (value & GMII_AUTONEG_COMP)
			break;

		/* Time out check */
		if (time_out && (timer_get_tick() - tick_start) >= time_out) {
			trace_error("Time out auto-negotiation \r\n");
			goto exit;
		}
	}

	/* Set local link mode */
	while (1) {
		if (phy->dev->model == PHY_KSZ9021 || phy->dev->model == PHY_KSZ9031) {
			phy->op->phy_read(phy->desc->addr, phy->desc->phy_addr, GMII_1000BTSR,
				&base_ts, phy->desc->retries);
			/* Setup the MAC link speed */
			if ((base_ts & GMII_LINKP_1000BaseT_FULL_DUPLEX) &&
				(base_tc & GMII_1000BaseT_FULL_DUPLEX)) {

				/* set RGMII for 1000BaseTX and Full Duplex */
				trace_debug("PHY Auto-Negotiation complete -> 1000BaseT/Full\r\n");
				phy->op->enable_rmii(phy->desc->addr, ETH_SPEED_1000M, ETH_DUPLEX_FULL);
				rc = true;
				break;
			} else if ((base_ts & GMII_LINKP_1000BaseT_HALF_DUPLEX) &&
				(base_tc & GMII_1000BaseT_HALF_DUPLEX)) {

				/* set RGMII for 1000BaseT and Half Duplex*/
				trace_debug("PHY Auto-Negotiation complete -> 1000BaseT/Half\r\n");
				phy->op->enable_rmii(phy->desc->addr, ETH_SPEED_1000M, ETH_DUPLEX_HALF);
				rc = true;
				break;
			}
		}

		if (!phy->op->phy_read(phy->desc->addr, phy->desc->phy_addr,
					GMII_ANLPAR, &value, phy->desc->retries)) {
			trace_error("Error reading PHY ANLPAR\r\n");
			goto exit;
		}

		/* Setup the GMAC link speed */
		if (value & GMII_TX_FDX) {
			trace_debug("PHY Auto-Negotiation complete -> 100BaseT/Full\r\n");
			phy->op->enable_rmii(phy->desc->addr, ETH_SPEED_100M, ETH_DUPLEX_FULL);
			rc = true;
			break;
		} else if (value & GMII_10_FDX) {
			trace_debug("PHY Auto-Negotiation complete -> 10BaseT/Full\r\n");
			phy->op->enable_rmii(phy->desc->addr, ETH_SPEED_10M, ETH_DUPLEX_FULL);
			rc = true;
			break;
		} else if (value & GMII_TX_HDX) {
			trace_debug("PHY Auto-Negotiation complete -> 100BaseT/Half\r\n");
			phy->op->enable_rmii(phy->desc->addr, ETH_SPEED_100M, ETH_DUPLEX_HALF);
			rc = true;
			break;
		} else if (value & GMII_10_HDX) {
			trace_debug("PHY Auto-Negotiation complete -> 10BaseT/Half\r\n");
			phy->op->enable_rmii(phy->desc->addr, ETH_SPEED_10M, ETH_DUPLEX_HALF);
			rc = true;
			break;
		}

		/* Time out check */
		if (time_out && (timer_get_tick() - tick_start) >= time_out) {
			trace_error("Time out setup MAC link speed\r\n");
			goto exit;
		}
	}

exit:
	if (!rc)
		trace_debug("PHY Auto-Negotiation failed!\r\n");
	phy->op->disable_mido(phy->desc->addr);
	return rc;
}
