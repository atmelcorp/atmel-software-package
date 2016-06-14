/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

/** \addtogroup emac_functions
 *@{
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"
#include "trace.h"
#include "peripherals/emac.h"
#include "peripherals/pmc.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static bool _emac_configure_mdc_clock(Emac *emac)
{
	uint32_t mck, clk;

	mck = pmc_get_peripheral_clock(get_emac_id_from_addr(emac));

	/* Disable RX/TX */
	emac->EMAC_NCR &= ~(EMAC_NCR_RE | EMAC_NCR_TE);

	/* Find divider */
	if (mck <= 20000000) {
		clk = EMAC_NCFGR_CLK_MCK_8; // MCK/8
	} else if (mck <= 40000000) {
		clk = EMAC_NCFGR_CLK_MCK_16; // MCK/16
	} else if (mck <= 80000000) {
		clk = EMAC_NCFGR_CLK_MCK_32; // MCK/32
	} else if (mck <= 160000000) {
		clk = EMAC_NCFGR_CLK_MCK_64; // MCK/64
	} else {
		trace_error("MCK too high, cannot configure MDC clock.\r\n");
		return false;
	}

	/* configure MDC clock divider and enable RX/TX */
	emac->EMAC_NCFGR = (emac->EMAC_NCFGR & ~EMAC_NCFGR_CLK_Msk) | clk;
	emac->EMAC_NCR |= (EMAC_NCR_RE | EMAC_NCR_TE);

	return true;
}

static bool _emac_phy_wait_idle(Emac* emac, uint32_t retries)
{
	uint32_t count = 0;
	while ((emac->EMAC_NSR & EMAC_NSR_IDLE) == 0) {
		if (retries > 0 && count > retries) {
			trace_debug("Timeout reached while waiting for PHY management logic to become idle");
			return false;
		}
		count++;
	}
	return true;
}

static void _emac_set_link_speed(Emac* emac, enum _eth_speed speed, enum _eth_duplex duplex)
{
	/* Configure duplex */
	switch (duplex) {
	case ETH_DUPLEX_HALF:
		emac->EMAC_NCFGR &= ~EMAC_NCFGR_FD;
		break;
	case ETH_DUPLEX_FULL:
		emac->EMAC_NCFGR |= EMAC_NCFGR_FD;
		break;
	default:
		trace_error("Invalid duplex value %d\r\n", duplex);
		return;
	}

	/* Configure speed */
	switch (speed) {
	case ETH_SPEED_10M:
		emac->EMAC_NCFGR &= ~EMAC_NCFGR_SPD;
		break;
	case ETH_SPEED_100M:
		emac->EMAC_NCFGR |= EMAC_NCFGR_SPD;
		break;
	default:
		trace_error("Invalid speed value %d\r\n", speed);
		return;
	}
}

/*----------------------------------------------------------------------------
 *       Exported functions
 *----------------------------------------------------------------------------*/

bool emac_configure(Emac* emac)
{
	pmc_enable_peripheral(get_emac_id_from_addr(emac));

	/* Disable TX & RX and more */
	emac_set_network_control_register(emac, 0);
	emac_set_network_config_register(emac, 0);

	/* Disable interrupts */
	emac_disable_it(emac, ~0u);

	/* Clear statistics */
	emac_clear_statistics(emac);

	/* Clear all status bits in the receive status register. */
	emac_clear_rx_status(emac, EMAC_RSR_OVR | EMAC_RSR_REC | EMAC_RSR_BNA);

	/* Clear all status bits in the transmit status register */
	emac_clear_tx_status(emac, EMAC_TSR_UBR | EMAC_TSR_COL | EMAC_TSR_RLES | EMAC_TSR_TGO | EMAC_TSR_COMP | EMAC_TSR_UND);

	/* Clear interrupts */
	emac_get_it_status(emac);

	return _emac_configure_mdc_clock(emac);
}

void emac_set_network_control_register(Emac* emac, uint32_t ncr)
{
	emac->EMAC_NCR = ncr;
}

uint32_t emac_get_network_control_register(Emac* emac)
{
	return emac->EMAC_NCR;
}

void emac_set_network_config_register(Emac* emac, uint32_t ncfgr)
{
	emac->EMAC_NCFGR = ncfgr;
}

uint32_t emac_get_network_config_register(Emac* emac)
{
	return emac->EMAC_NCFGR;
}

void emac_enable_mdio(Emac* emac)
{
	/* Disable RX/TX */
	emac->EMAC_NCR &= ~(EMAC_NCR_RE | EMAC_NCR_TE);

	/* Enable MDIO */
	emac->EMAC_NCR |= EMAC_NCR_MPE;

	/* Enable RX/TX */
	emac->EMAC_NCR |= (EMAC_NCR_RE | EMAC_NCR_TE);
}

void emac_disable_mdio(Emac* emac)
{
	/* Disable RX/TX */
	emac->EMAC_NCR &= ~(EMAC_NCR_RE | EMAC_NCR_TE);

	/* Disable MDIO */
	emac->EMAC_NCR &= ~EMAC_NCR_MPE;

	/* Enable RX/TX */
	emac->EMAC_NCR |= (EMAC_NCR_RE | EMAC_NCR_TE);
}

bool emac_phy_read(Emac* emac, uint8_t phy_addr, uint8_t reg_addr, uint16_t* data, uint32_t retries)
{
	/* Wait until idle */
	if (!_emac_phy_wait_idle(emac, retries))
		return false;

	/* Write maintenance register */
	emac->EMAC_MAN = EMAC_MAN_SOF(0x1) |
		EMAC_MAN_RW(2) |
		EMAC_MAN_CODE(2) |
		EMAC_MAN_PHYA(phy_addr) |
		EMAC_MAN_REGA(reg_addr);

	/* Wait until idle */
	if (!_emac_phy_wait_idle(emac, retries))
		return false;

	*data = (emac->EMAC_MAN & EMAC_MAN_DATA_Msk) >> EMAC_MAN_DATA_Pos;
	return true;
}

bool emac_phy_write(Emac* emac, uint8_t phy_addr, uint8_t reg_addr, uint16_t data,
		uint32_t retries)
{
	/* Wait until idle */
	if (!_emac_phy_wait_idle(emac, retries))
		return false;

	/* Write maintenance register */
	emac->EMAC_MAN = EMAC_MAN_SOF(0x1) |
		EMAC_MAN_RW(1) |
		EMAC_MAN_CODE(2) |
		EMAC_MAN_PHYA(phy_addr) |
		EMAC_MAN_REGA(reg_addr) |
		EMAC_MAN_DATA(data);

	/* Wait until idle */
	return _emac_phy_wait_idle(emac, retries);
}

void emac_enable_rmii(Emac* emac, enum _eth_speed speed, enum _eth_duplex duplex)
{
	/* Disable RX/TX */
	emac->EMAC_NCR &= ~(EMAC_NCR_RE | EMAC_NCR_TE);

	/* Configure speed/duplex */
	_emac_set_link_speed(emac, speed, duplex);

	/* Enable RMII */
	emac->EMAC_USRIO |= (EMAC_USRIO_RMII | EMAC_USRIO_CLKEN);

	/* Enable RX/TX */
	emac->EMAC_NCR |= (EMAC_NCR_RE | EMAC_NCR_TE);
}

void emac_set_link_speed(Emac* emac, enum _eth_speed speed, enum _eth_duplex duplex)
{
	/* Disable RX/TX */
	emac->EMAC_NCR &= ~(EMAC_NCR_RE | EMAC_NCR_TE);

	/* Configure speed/duplex */
	_emac_set_link_speed(emac, speed, duplex);

	/* Enable RX/TX */
	emac->EMAC_NCR |= (EMAC_NCR_RE | EMAC_NCR_TE);
}

void emac_enable_local_loopback(Emac* emac)
{
	emac->EMAC_NCR |= EMAC_NCR_LLB;
}

void emac_disable_local_loopback(Emac* emac)
{
	emac->EMAC_NCR &= ~EMAC_NCR_LLB;
}

uint32_t emac_get_tx_status(Emac* emac)
{
	return emac->EMAC_TSR;
}

void emac_clear_tx_status(Emac* emac, uint32_t mask)
{
	emac->EMAC_TSR = mask;
}

uint32_t emac_get_rx_status(Emac* emac)
{
	return emac->EMAC_RSR;
}

void emac_clear_rx_status(Emac* emac, uint32_t mask)
{
	emac->EMAC_RSR = mask;
}

void emac_receive_enable(Emac* emac, bool enable)
{
	if (enable)
		emac->EMAC_NCR |= EMAC_NCR_RE;
	else
		emac->EMAC_NCR &= ~EMAC_NCR_RE;
}

void emac_transmit_enable(Emac* emac, bool enable)
{
	if (enable)
		emac->EMAC_NCR |= EMAC_NCR_TE;
	else
		emac->EMAC_NCR &= ~EMAC_NCR_TE;
}

void emac_set_rx_desc(Emac* emac, struct _eth_desc* desc)
{
	emac->EMAC_RBQP = ((uint32_t)desc) & EMAC_RBQP_ADDR_Msk;
}

struct _eth_desc* emac_get_rx_desc(Emac* emac)
{
	return (struct _eth_desc*)(emac->EMAC_RBQP & EMAC_RBQP_ADDR_Msk);
}

void emac_set_tx_desc(Emac* emac, struct _eth_desc* desc)
{
	emac->EMAC_TBQP = ((uint32_t)desc) & EMAC_TBQP_ADDR_Msk;
}

struct _eth_desc* emac_get_tx_desc(Emac* emac)
{
	return (struct _eth_desc*)(emac->EMAC_TBQP & EMAC_TBQP_ADDR_Msk);
}

uint32_t emac_get_it_mask(Emac* emac)
{
	return emac->EMAC_IMR;
}

void emac_enable_it(Emac* emac, uint32_t mask)
{
	emac->EMAC_IER = mask;
}

void emac_disable_it(Emac * emac, uint32_t mask)
{
	emac->EMAC_IDR = mask;
}

uint32_t emac_get_it_status(Emac* emac)
{
	return emac->EMAC_ISR;
}

void emac_set_mac_addr(Emac* emac, uint8_t sa_idx, uint8_t* mac)
{
	emac->EMAC_SA[sa_idx].EMAC_SAxB = (mac[3] << 24) |
		(mac[2] << 16) | (mac[1] << 8) | mac[0];
	emac->EMAC_SA[sa_idx].EMAC_SAxT = (mac[5] << 8) |
		mac[4];
}

void emac_set_mac_addr32(Emac* emac, uint8_t sa_idx,
			 uint32_t mac_top, uint32_t mac_bottom)
{
	emac->EMAC_SA[sa_idx].EMAC_SAxB = mac_bottom;
	emac->EMAC_SA[sa_idx].EMAC_SAxT = mac_top;
}

void emac_set_mac_addr64(Emac* emac, uint8_t sa_idx, uint64_t mac)
{
	emac->EMAC_SA[sa_idx].EMAC_SAxB = (uint32_t)(mac & 0xffffffff);
	emac->EMAC_SA[sa_idx].EMAC_SAxT = (uint32_t)(mac >> 32);
}

void emac_clear_statistics(Emac* emac)
{
	emac->EMAC_NCR |= EMAC_NCR_CLRSTAT;
}

void emac_increase_statistics(Emac* emac)
{
	emac->EMAC_NCR |= EMAC_NCR_INCSTAT;
}

void emac_enable_statistics_write(Emac* emac, bool enable)
{
	if (enable)
		emac->EMAC_NCR |= EMAC_NCR_WESTAT;
	else
		emac->EMAC_NCR &= ~EMAC_NCR_WESTAT;
}

void emac_start_transmission(Emac * emac)
{
	emac->EMAC_NCR |= EMAC_NCR_TSTART;
}

void emac_halt_transmission(Emac * emac)
{
	emac->EMAC_NCR |= EMAC_NCR_THALT;
}

/**@}*/

