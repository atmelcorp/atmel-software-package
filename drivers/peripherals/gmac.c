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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"


#include "peripherals/gmac.h"
#include "trace.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/
/** The buffer addresses written into the descriptors must be aligned so the
    last few bits are zero.  These bits have special meaning for the GMAC
     peripheral and cannot be used as part of the address.*/

#define GMAC_ADDRESS_MASK   ((uint32_t)0xFFFFFFFC)
#define GMAC_LENGTH_FRAME   ((uint32_t)0x3FFF)	    /** Length of frame mask */
/** receive buffer descriptor bits */
#define GMAC_RX_OWNERSHIP_BIT   (1 <<  0)
#define GMAC_RX_WRAP_BIT        (1 <<  1)
#define GMAC_RX_SOF_BIT         (1 << 14)
#define GMAC_RX_EOF_BIT         (1 << 15)

/** Transmit buffer descriptor bits */
#define GMAC_TX_LAST_BUFFER_BIT (1 << 15)
#define GMAC_TX_WRAP_BIT        (1 << 30)
#define GMAC_TX_USED_BIT        (1 << 31)
#define GMAC_TX_RLE_BIT         (1 << 29) /** Retry Limit Exceeded */
#define GMAC_TX_UND_BIT         (1 << 28) /** Tx Buffer Underrun */
#define GMAC_TX_ERR_BIT         (1 << 27) /** Exhausted in mid-frame */
#define GMAC_TX_ERR_BITS  \
    (GMAC_TX_RLE_BIT | GMAC_TX_UND_BIT | GMAC_TX_ERR_BIT)

#define GMAC_NCFGR_GBE (0x1u << 10)

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

uint8_t gmac_is_idle(Gmac * gmac)
{
	return ((gmac->GMAC_NSR & GMAC_NSR_IDLE) > 0);
}

void gmac_phy_maintain(Gmac * gmac, uint8_t bPhyAddr, uint8_t bRegAddr, uint8_t bRW, uint16_t wData)
{
	/* Wait until bus idle */
	while ((gmac->GMAC_NSR & GMAC_NSR_IDLE) == 0) ;
	/* Write maintain register */
	gmac->GMAC_MAN = (~GMAC_MAN_WZO & GMAC_MAN_CLTTO)
	    | (GMAC_MAN_OP(bRW ? 0x2 : 0x1))
	    | GMAC_MAN_WTN(0x02)
	    | GMAC_MAN_PHYA(bPhyAddr)
	    | GMAC_MAN_REGA(bRegAddr)
	    | GMAC_MAN_DATA(wData);
}

uint16_t gmac_phy_data(Gmac * gmac)
{
	/* Wait until bus idle */
	while ((gmac->GMAC_NSR & GMAC_NSR_IDLE) == 0) ;
	/* Return data */
	return (uint16_t) (gmac->GMAC_MAN & GMAC_MAN_DATA_Msk);
}

uint8_t gmac_set_mdc_clock(Gmac * gmac, uint32_t mck)
{
	uint32_t clock_dividor;

	gmac->GMAC_NCR &= ~(GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	if (mck <= 20000000) {
		clock_dividor = GMAC_NCFGR_CLK_MCK_8;	// MDC clock = MCK/8
	} else if (mck <= 40000000) {
		clock_dividor = GMAC_NCFGR_CLK_MCK_16;	// MDC clock = MCK/16
	} else if (mck <= 80000000) {
		clock_dividor = GMAC_NCFGR_CLK_MCK_32;	// MDC clock = MCK/32
	} else if (mck <= 160000000) {
		clock_dividor = GMAC_NCFGR_CLK_MCK_64;	// MDC clock = MCK/64
	} else if (mck <= 240000000) {
		clock_dividor = GMAC_NCFGR_CLK_MCK_96;	// MDC clock = MCK/96
	} else {
		trace_error("E: No valid MDC clock.\n\r");
		return 0;
	}
	gmac->GMAC_NCFGR =
	    (gmac->GMAC_NCFGR & (~GMAC_NCFGR_CLK_Msk)) | clock_dividor;
	gmac->GMAC_NCR |= (GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	return 1;
}

void gmac_enable_mdio(Gmac * gmac)
{
	gmac->GMAC_NCR &= ~(GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	gmac->GMAC_NCR |= GMAC_NCR_MPE;
	gmac->GMAC_NCR |= (GMAC_NCR_RXEN | GMAC_NCR_TXEN);
}

void gmac_disable_mdio(Gmac * gmac)
{
	gmac->GMAC_NCR &= ~(GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	gmac->GMAC_NCR &= ~GMAC_NCR_MPE;
	gmac->GMAC_NCR |= (GMAC_NCR_RXEN | GMAC_NCR_TXEN);
}

void gmac_enable_mii(Gmac * gmac)
{
	gmac->GMAC_NCR &= ~(GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	gmac->GMAC_UR &= ~GMAC_UR_RMII;
	gmac->GMAC_NCR |= (GMAC_NCR_RXEN | GMAC_NCR_TXEN);
}

void gmac_enable_gmii(Gmac * gmac)
{
	gmac->GMAC_NCR &= ~(GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	/* RGMII disable */
	gmac->GMAC_UR &= ~GMAC_UR_RMII;
	gmac->GMAC_NCR |= (GMAC_NCR_RXEN | GMAC_NCR_TXEN);
}

void gmac_enable_rgmii(Gmac * gmac, uint32_t duplex, uint32_t speed)
{
	gmac->GMAC_NCR &= ~(GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	if (duplex == GMAC_DUPLEX_HALF) {
		gmac->GMAC_NCFGR &= ~GMAC_NCFGR_FD;
	} else {
		gmac->GMAC_NCFGR |= GMAC_NCFGR_FD;
	}

	if (speed == GMAC_SPEED_10M) {
		gmac->GMAC_NCFGR &= ~GMAC_NCFGR_SPD;
	} else if (speed == GMAC_SPEED_100M) {
		gmac->GMAC_NCFGR |= GMAC_NCFGR_SPD;
	} else {
		gmac->GMAC_NCFGR |= GMAC_NCFGR_SPD;
	}

	/* RGMII enable */
	gmac->GMAC_UR |= GMAC_UR_RMII;
	gmac->GMAC_NCFGR &= ~GMAC_NCFGR_GBE;
	gmac->GMAC_NCR |= (GMAC_NCR_RXEN | GMAC_NCR_TXEN);
	return;
}

void gmac_set_link_speed(Gmac * gmac, uint8_t speed, uint8_t fullduplex)
{
	uint32_t ncfgr;

	ncfgr = gmac->GMAC_NCFGR;
	ncfgr &= ~(GMAC_NCFGR_SPD | GMAC_NCFGR_FD);
	if (speed) {
		ncfgr |= GMAC_NCFGR_SPD;
	}
	if (fullduplex) {
		ncfgr |= GMAC_NCFGR_FD;
	}
	gmac->GMAC_NCFGR = ncfgr;
	gmac->GMAC_NCR |= (GMAC_NCR_RXEN | GMAC_NCR_TXEN);
}

uint32_t gmac_set_local_loopback(Gmac * gmac)
{
	gmac->GMAC_NCR |= GMAC_NCR_LBL;
	return 0;
}

uint32_t gmac_get_it_mask(Gmac * gmac)
{
	return gmac->GMAC_IMR;
}

uint32_t gmac_get_tx_status(Gmac * gmac)
{
	return gmac->GMAC_TSR;
}

void gmac_clear_tx_status(Gmac * gmac, uint32_t status)
{
	gmac->GMAC_TSR = status;
}

uint32_t gmac_get_rx_status(Gmac * gmac)
{
	return gmac->GMAC_RSR;
}

void gmac_clear_rx_status(Gmac * gmac, uint32_t status)
{
	gmac->GMAC_RSR = status;
}

void gmac_receive_enable(Gmac * gmac, uint8_t on_off)
{
	if (on_off)
		gmac->GMAC_NCR |= GMAC_NCR_RXEN;
	else
		gmac->GMAC_NCR &= ~GMAC_NCR_RXEN;
}

void gmac_transmit_enable(Gmac * gmac, uint8_t on_off)
{
	if (on_off)
		gmac->GMAC_NCR |= GMAC_NCR_TXEN;
	else
		gmac->GMAC_NCR &= ~GMAC_NCR_TXEN;
}

void gmac_set_rx_queue(Gmac * gmac, uint32_t addr)
{
	gmac->GMAC_RBQB = GMAC_RBQB_ADDR_Msk & addr;
}

uint32_t gmac_get_rx_queue(Gmac * gmac)
{
	return gmac->GMAC_RBQB;
}

void gmac_set_tx_queue(Gmac * gmac, uint32_t addr)
{
	gmac->GMAC_TBQB = GMAC_TBQB_ADDR_Msk & addr;
}

uint32_t gmac_get_tx_queue(Gmac * gmac)
{
	return gmac->GMAC_TBQB;
}

void gmac_network_control(Gmac * gmac, uint32_t ncr)
{
	gmac->GMAC_NCR = ncr;
}

uint32_t gmac_get_network_control(Gmac * gmac)
{
	return gmac->GMAC_NCR;
}

void gmac_enable_it(Gmac * gmac, uint32_t sources)
{
	gmac->GMAC_IER = sources;
}

void gmac_disable_it(Gmac * gmac, uint32_t sources)
{
	gmac->GMAC_IDR = sources;
}

uint32_t gmac_get_it_status(Gmac * gmac)
{
	return gmac->GMAC_ISR;
}

void gmac_set_address(Gmac * gmac, uint8_t index, uint8_t * mac_addr)
{
	gmac->GMAC_SA[index].GMAC_SAB = (mac_addr[3] << 24)
	    | (mac_addr[2] << 16)
	    | (mac_addr[1] << 8)
	    | (mac_addr[0]);
	gmac->GMAC_SA[index].GMAC_SAT = (mac_addr[5] << 8)
	    | (mac_addr[4]);
}

void gmac_set_address_32(Gmac * gmac, uint8_t bIndex,
			 uint32_t mac_t, uint32_t mac_b)
{
	gmac->GMAC_SA[bIndex].GMAC_SAB = mac_b;
	gmac->GMAC_SA[bIndex].GMAC_SAT = mac_t;
}

void gmac_set_address_64(Gmac * gmac, uint8_t bIndex, uint64_t mac)
{
	gmac->GMAC_SA[bIndex].GMAC_SAB = (uint32_t) mac;
	gmac->GMAC_SA[bIndex].GMAC_SAT = (uint32_t) (mac >> 32);
}

void gmac_clear_statistics(Gmac * gmac)
{
	gmac->GMAC_NCR |= GMAC_NCR_CLRSTAT;
}

void gmac_increase_statistics(Gmac * gmac)
{
	gmac->GMAC_NCR |= GMAC_NCR_INCSTAT;
}

void gmac_statistics_write_enable(Gmac * gmac, uint8_t on_off)
{
	if (on_off)
		gmac->GMAC_NCR |= GMAC_NCR_WESTAT;
	else
		gmac->GMAC_NCR &= ~GMAC_NCR_WESTAT;
}

void gmac_configure(Gmac * gmac, uint32_t cfg)
{
	gmac->GMAC_NCFGR = cfg;
}

uint32_t gmac_get_configure(Gmac * gmac)
{
	return gmac->GMAC_NCFGR;
}

void gmac_transmission_start(Gmac * gmac)
{
	gmac->GMAC_NCR |= GMAC_NCR_TSTART;
}

void gmac_transmission_halt(Gmac * gmac)
{
	gmac->GMAC_NCR |= GMAC_NCR_THALT;
}
