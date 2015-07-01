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

/** \addtogroup gmac_module
 * @{
 * Provides the interface to configure and use the GMAC peripheral.
 *
 * \section gmac_usage Usage
 * - Configure Gmac::GMAC_NCFG with gmac_configure(), some of related controls
 *   are also available, such as:
 *   - gmac_set_link_speed(): Setup GMAC working clock.
 *   - gmac_full_duplex_enable(): Working in full duplex or not.
 *   - gmac_cpy_all_enable(): Copying all valid frames (\ref GMAC_NCFG_CAF).
 *   - ...
 * - Setup Gmac::GMAC_NCR with gmac_network_control(), more related controls
 *   can modify with:
 *   - gmac_receive_enable(): Enable/Disable Rx.
 *   - gmac_transmit_enable(): Enable/Disable Tx.
 *   - gmac_broadcast_disable(): Enable/Disable broadcast receiving.
 *   - ...
 * - Manage GMAC interrupts with GMAC_EnableIt(), gmac_disable_it(),
 *   gmac_get_it_mask() and gmac_get_it_status().
 * - Manage GMAC Tx/Rx status with gmac_get_tx_status(), gmac_get_rx_status()
 *   gmac_clear_tx_status() and gmac_clear_rx_status().
 * - Manage GMAC Queue with gmac_set_tx_queue(), GMAC_GetTxQueue(),
 *   gmac_set_rx_queue() and GMAC_GetRxQueue(), the queue descriptor can define
 *   by \ref _gmac_rx_descriptor and \ref _gmac_tx_descriptor.
 * - Manage PHY through GMAC is performed by
 *   - gmac_management_enable(): Enable/Disable PHY management.
 *   - gmac_phy_maintain(): Execute PHY management commands.
 *   - gmac_phy_data(): Return PHY management data.
 *   - gmac_is_idle(): Check if PHY is idle.
 * - Setup GMAC parameters with following functions:
 *   - gmac_set_hash(): Set Hash value.
 *   - gmac_set_address(): Set MAC address.
 * - Enable/Disable GMAC transceiver clock via GMAC_TransceiverClockEnable()
 * - Switch GMAC MII/RMII mode through gmac_enable_rgmii()
 *
 * For more accurate information, please look at the GMAC section of the
 * Datasheet.
 *
 * \sa \ref gmacd_module
 *
 * Related files:\n
 * gmac.c\n
 * gmac.h.\n
 *
 *   \defgroup gmac_defines GMAC Defines
 *   \defgroup gmac_structs GMAC Data Structs
 *   \defgroup gmac_functions GMAC Functions
 */
/**@}*/

#ifndef _GMAC_H
#define _GMAC_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "chip.h"

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*----------------------------------------------------------------------------
 *        Defines
 *----------------------------------------------------------------------------*/
/** \addtogroup gmac_defines
	@{*/

/// Board GMAC base address

/// Number of buffer for RX, be careful: MUST be 2^n
#define GRX_BUFFERS  16
/// Number of buffer for TX, be careful: MUST be 2^n
#define GTX_BUFFERS   8

/// Buffer Size
#define GMAC_RX_UNITSIZE            128	/// Fixed size for RX buffer
#define GMAC_TX_UNITSIZE            1518	/// Size for ETH frame length

// The MAC can support frame lengths up to 1536 bytes.
#define GMAC_FRAME_LENTGH_MAX       1536

//
#define GMAC_DUPLEX_HALF	0
#define GMAC_DUPLEX_FULL	1

//
#define GMAC_SPEED_10M      0
#define GMAC_SPEED_100M     1
#define GMAC_SPEED_1000M    2
/**@}*/

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/
/** \addtogroup gmac_structs
	@{*/
/** Receive buffer descriptor struct */
struct _gmac_rx_descriptor {
	union gmac_rx_addr {
		uint32_t val;
		struct gmac_rx_addr_bm {
			/** User clear, GMAC set this to one once it
			has successfully written a frame to memory */
			uint32_t bOwnership:1,
			/** Marks last descriptor in rx buffer */
			bWrap:1,
			/** Address in number of DW */
			addrDW:30;
		} bm;
	} addr;         /**< Address, Wrap & Ownership */
	union gmac_rx_status {
		uint32_t val;
		struct gmac_rx_status_bm {
			/** Length of frame including FCS */
			uint32_t len:12,
			/** Receive buffer offset, bits 13:12 of frame
			 * length for jumbo frame */
				offset:2,
			/** Start of frame */
				bSof:1,
			/** End of frame */
				bEof:1,
			/** Concatenation Format Indicator */
				bCFI:1,
			/** VLAN priority (if VLAN detected) */
				vlanPriority:3,
			/** Priority tag detected */
				bPriorityDetected:1,
			/** VLAN tag detected */
				bVlanDetected:1,
			/** Type ID match */
				bTypeIDMatch:1,
			/** Address register 4 match */
				bAddr4Match:1,
			/** Address register 3 match */
				bAddr3Match:1,
			/** Address register 2 match */
				bAddr2Match:1,
			/** Address register 1 match */
				bAddr1Match:1,
				reserved:1,
			/** External address match */
				bExtAddrMatch:1,
			/** Unicast hash match */
				bUniHashMatch:1,
			/** Multicast hash match */
				bMultiHashMatch:1,
			/** Global all ones broadcast address detected */
				bBroadcastDetected:1;
		} bm;
	} status;
} ;

/** Transmit buffer descriptor struct */
struct _gmac_tx_descriptor {
	uint32_t addr;
	union gmac_tx_status {
		uint32_t val;
		struct gmac_tx_status_bm {
			/** Length of buffer */
			uint32_t len:11,
				reserved:4,
			/** Last buffer (in the current frame) */
				bLastBuffer:1,
			/** No CRC */
				bNoCRC:1,
				reserved1:10,
			/** Buffer exhausted in mid frame */
				bExhausted:1,
			/** Transmit underrun */
				bUnderrun:1,
			/** Retry limit exceeded, error detected */
				bError:1,
			/** Marks last descriptor in TD list */
				bWrap:1,
			/** User clear, GMAC sets this once a frame
			 * has been successfully transmitted */
				bUsed:1;
		} bm;
	} status;
};

/**     @}*/

/*----------------------------------------------------------------------------
 *        PHY Exported functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Return 1 if PHY is idle
 */
extern uint8_t gmac_is_idle(Gmac * gmac);

/**
 *  \brief Execute PHY maintenance command
 */
extern void gmac_phy_maintain(Gmac * gmac, uint8_t phy_addr,
			      uint8_t bRegAddr, uint8_t rw, uint16_t data);

/**
 *  \brief Return PHY maintenance data returned
 */
extern uint16_t gmac_phy_data(Gmac * gmac);

/**
 *  \brief Set MDC clock according to current board clock. Per 802.3,
 *  MDC should be less then 2.5MHz.
 *
 *  \param gmac Pointer to an Gmac instance.
 *  \param mck Mdc clock
 *  \return 1 if successfully, 0 if MDC clock not found.
 */
extern uint8_t gmac_set_mdc_clock(Gmac * gmac, uint32_t mck);

/**
 *  \brief Enable MDI with PHY
 *  \param gmac Pointer to an Gmac instance.
 */
extern void gmac_enable_mdio(Gmac * gmac);

/**
 *  \brief Disable MDI with PHY
 *  \param gmac Pointer to an Gmac instance.
 */
extern void gmac_disable_mdio(Gmac * gmac);

/**
 *  \brief Enable MII mode for GMAC, called once after autonegotiate
 *  \param gmac Pointer to an Gmac instance.
 */
extern void gmac_enable_mii(Gmac * gmac);

/**
 *  \brief Enable GMII mode for GMAC, called once after autonegotiate
 *  \param gmac Pointer to an Gmac instance.
 */
extern void gmac_enable_gmii(Gmac * gmac);

/**
 *  \brief Enable RGMII mode for GMAC, called once after autonegotiate
 *  \param gmac Pointer to an Gmac instance.
 *  \param duplex: 1 full duplex 0 half duplex
 *  \param speed: 0 10M 1 100M
 */
extern void gmac_enable_rgmii(Gmac * gmac, uint32_t duplex, uint32_t speed);

/**
 *  \brief Setup the GMAC for the link : speed 100M/10M and Full/Half duplex
 *  \param gmac Pointer to an Gmac instance.
 *  \param speed Link speed, 0 for 10M, 1 for 100M
 *  \param fullduplex 1 for Full Duplex mode
 */
extern void gmac_set_link_speed(Gmac * gmac, uint8_t speed,
				uint8_t fullduplex);

/**
 *  \brief set local loop back
 *  \param gmac Pointer to an Gmac instance.
 */
extern uint32_t gmac_set_local_loopback(Gmac * gmac);

/**
 *  \brief Return interrupt mask.
 */
extern uint32_t gmac_get_it_mask(Gmac * gmac);

/**
 *  \brief Return transmit status
 */
extern uint32_t gmac_get_tx_status(Gmac * gmac);

/**
 *  \brief Clear transmit status
 */
extern void gmac_clear_tx_status(Gmac * gmac, uint32_t status);

/**
 *  \brief Return receive status
 */
extern uint32_t gmac_get_rx_status(Gmac * gmac);

/**
 *  \brief Clear receive status
 */
extern void gmac_clear_rx_status(Gmac * gmac, uint32_t status);

/**
 *  \brief Enable/Disable GMAC receive.
 */
extern void gmac_receive_enable(Gmac * gmac, uint8_t on_off);

/**
 *  \brief Enable/Disable GMAC transmit.
 */
extern void gmac_transmit_enable(Gmac * gmac, uint8_t on_off);

/**
 *  \brief Set Rx Queue
 */
extern void gmac_set_rx_queue(Gmac * gmac, uint32_t addr);

/**
 *  \brief Get Rx Queue Address
 */
extern uint32_t gmac_get_rx_queue(Gmac * gmac);

/**
 *  \brief Set Tx Queue
 */
extern void gmac_set_tx_queue(Gmac * gmac, uint32_t addr);

/**
 *  \brief Get Tx Queue
 */
extern uint32_t gmac_get_tx_queue(Gmac * gmac);

/**
 *  \brief Write control value
 */
extern void gmac_network_control(Gmac * gmac, uint32_t ncr);

/**
 *  \brief Get control value
 */
extern uint32_t gmac_get_network_control(Gmac * gmac);

/**
 *  \brief Enable interrupt(s).
 */
extern void gmac_enable_it(Gmac * gmac, uint32_t sources);

/**
 *  \brief Disable interrupt(s).
 */
extern void gmac_disable_it(Gmac * gmac, uint32_t sources);

/**
 *  \brief Return interrupt status mask.
 */
extern uint32_t gmac_get_it_status(Gmac * gmac);

/**
 *  \brief Set MAC Address
 */
extern void gmac_set_address(Gmac * gmac, uint8_t index, uint8_t * mac_addr);

/**
 *  \brief Set MAC Address via 2 int32
 */
extern void gmac_set_address_32(Gmac * gmac, uint8_t index,
				uint32_t mac_t, uint32_t mac_b);

/**
 *  \brief Set MAC Address via int64
 */
extern void gmac_set_address_64(Gmac * gmac, uint8_t index, uint64_t mac);

/**
 *  \brief Clear all statistics registers
 */
extern void gmac_clear_statistics(Gmac * gmac);

/**
 *  \brief Increase all statistics registers
 */
extern void gmac_increase_statistics(Gmac * gmac);

/**
 *  \brief Enable/Disable statistics registers writing.
 */
extern void gmac_statistics_write_enable(Gmac * gmac, uint8_t on_off);

/**
 *  \brief Setup network configuration register
 */
extern void gmac_configure(Gmac * gmac, uint32_t cfg);

/**
 *  \brief Return network configuration.
 */
extern uint32_t gmac_get_configure(Gmac * gmac);

/**
 *  \brief Start transmission
 */
extern void gmac_transmission_start(Gmac * gmac);

/**
 *  \brief Halt transmission
 */
extern void gmac_transmission_halt(Gmac * gmac);

#ifdef __cplusplus
}
#endif

#endif				// #ifndef GMAC_H
