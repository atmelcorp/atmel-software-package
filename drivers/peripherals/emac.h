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

/** \addtogroup emac_module
 * @{
 * Provides the interface to configure and use the EMAC peripheral.
 *
 * \section emac_usage Usage
 * - Configure Emac::EMAC_NCFG with emac_configure(), some of related controls
 *   are also available, such as:
 *   - emac_set_link_speed(): Setup EMAC working clock.
 *   - emac_full_duplex_enable(): Working in full duplex or not.
 *   - emac_cpy_all_enable(): Copying all valid frames (\ref EMAC_NCFG_CAF).
 *   - ...
 * - Setup emac::EMAC_NCR with gmac_network_control(), more related controls
 *   can modify with:
 *   - emac_receive_enable(): Enable/Disable Rx.
 *   - emac_transmit_enable(): Enable/Disable Tx.
 *   - emac_broadcast_disable(): Enable/Disable broadcast receiving.
 *   - ...
 * - Manage EMAC interrupts with emac_enable_it(), gmac_disable_it(),
 *   emac_get_it_mask() and emac_get_it_status().
 * - Manage EMAC Tx/Rx status with emac_get_tx_status(), gmac_eet_rx_status()
 *   emac_clear_tx_status() and emac_clear_rx_status().
 * - Manage PHY through EMAC is performed by
 *   - emac_phy_read(): Read data from PHY.
 *   - emac_phy_read(): Read data from PHY.
 *   - emac_enable_mdio(): Enable management port.
 *   - emac_disable_mdio(): Disable management port.
 * - Setup EMAC parameters with following functions:
 *   - emac_set_mac_addr(), emac_set_mac_addr32(), emac_set_mac_addr64(): Set MAC address.
 * - Enable EMAC MII mode through emac_enable_rmii()
 *
 * For more accurate information, please look at the EMAC section of the
 * Datasheet.
 *
 * \sa \ref emacd_module
 *
 * Related files:\n
 * emac.c\n
 * emac.h.\n
 *
 *   \defgroup emac_defines EMAC Defines
 *   \defgroup emac_structs EMAC Data Structs
 *   \defgroup emac_functions EMAC Functions
 */
/**@}*/

#ifndef _EMAC_H_
#define _EMAC_H_

#ifdef CONFIG_HAVE_EMAC

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "peripherals/ethd.h"

/*----------------------------------------------------------------------------
 *        Defines
 *----------------------------------------------------------------------------*/
/** \addtogroup emac_defines
	@{*/

#define EMAC_NUM_QUEUES 1
#define EMAC_QUEUE_INDEX 0

/**@}*/

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \addtogroup emac_structs
	@{*/

/**     @}*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/** \addtogroup emac_functions
	@{*/

extern bool emac_configure(Emac *emac);

/**
 *  \brief Write NCR register value
 */
extern void emac_set_network_control_register(Emac * emac, uint32_t ncr);

/**
 *  \brief Get NCR register value
 *  \param emac Pointer to an Emac instance.
 */
extern uint32_t emac_get_network_control_register(Emac * emac);

/**
 *  \brief Set network configuration register
 *  \param emac Pointer to an Emac instance.
 */
extern void emac_set_network_config_register(Emac* emac, uint32_t ncfgr);

/**
 *  \brief Get network configuration register
 *  \param emac Pointer to an Emac instance.
 */
extern uint32_t emac_get_network_config_register(Emac* emac);

/**
 *  \brief Enable MDI with PHY
 *  \param emac Pointer to an Emac instance.
 */
extern void emac_enable_mdio(Emac* emac);

/**
 *  \brief Disable MDI with PHY
 *  \param emac Pointer to an Emac instance.
 */
extern void emac_disable_mdio(Emac* emac);

/**
 *  \brief Execute PHY read command
 */
extern bool emac_phy_read(Emac* emac, uint8_t phy_addr, uint8_t reg_addr,
		uint16_t* data, uint32_t retries);

/**
 *  \brief Execute PHY write command
 */
extern bool emac_phy_write(Emac* emac, uint8_t phy_addr, uint8_t reg_addr,
		uint16_t data, uint32_t retries);

/**
 *  \brief Enable RMII mode for EMAC, called once after autonegotiate
 *  \param emac Pointer to an Emac instance.
 *  \param duplex: 1 full duplex 0 half duplex
 *  \param speed: 0 10M 1 100M
 */
extern void emac_enable_rmii(Emac* emac, enum _eth_speed speed,
		enum _eth_duplex duplex);

/**
 *  \brief Setup the GMAC for the link : speed 100M/10M and Full/Half duplex
 *  \param emac Pointer to an Emac instance.
 *  \param speed Link speed, 0 for 10M, 1 for 100M
 *  \param fullduplex 1 for Full Duplex mode
 */
extern void emac_set_link_speed(Emac* emac, enum _eth_speed speed,
		enum _eth_duplex duplex);

/**
 *  \brief Enable local loop back
 *  \param emac Pointer to an Emac instance.
 */
extern void emac_enable_local_loopback(Emac* emac);

/**
 *  \brief Disable local loop back
 *  \param emac Pointer to an Emac instance.
 */
extern void emac_disable_local_loopback(Emac* emac);

/**
 *  \brief Return transmit status
 *  \param emac Pointer to an Emac instance.
 */
extern uint32_t emac_get_tx_status(Emac* emac);

/**
 *  \brief Clear transmit status
 *  \param emac Pointer to an Emac instance.
 */
extern void emac_clear_tx_status(Emac* emac, uint32_t mask);

/**
 *  \brief Return receive status
 *  \param emac Pointer to an Emac instance.
 */
extern uint32_t emac_get_rx_status(Emac* emac);

/**
 *  \brief Clear receive status
 *  \param emac Pointer to an Emac instance.
 */
extern void emac_clear_rx_status(Emac* emac, uint32_t mask);

/**
 *  \brief Enable/Disable GMAC receive.
 */
extern void emac_receive_enable(Emac* emac, bool enable);

/**
 *  \brief Enable/Disable GMAC transmit.
 */
extern void emac_transmit_enable(Emac* emac, bool enable);

/**
 *  \brief Set RX descriptor address
 */
void emac_set_rx_desc(Emac* emac, struct _eth_desc* desc);

/**
 *  \brief Get RX descriptor address
 */
struct _eth_desc* emac_get_rx_desc(Emac* emac);

/**
 *  \brief Set TX descriptor address
 */
void emac_set_tx_desc(Emac* emac, struct _eth_desc* desc);

/**
 *  \brief Get TX descriptor address
 */
struct _eth_desc* emac_get_tx_desc(Emac* emac);

/**
 *  \brief Return interrupt mask.
 */
extern uint32_t emac_get_it_mask(Emac* emac);

/**
 *  \brief Enable interrupt(s).
 */
extern void emac_enable_it(Emac* emac, uint32_t mask);

/**
 *  \brief Disable interrupt(s).
 */
extern void emac_disable_it(Emac * emac, uint32_t mask);

/**
 *  \brief Return interrupt status mask.
 */
extern uint32_t emac_get_it_status(Emac* emac);

/**
 *  \brief Set MAC Address
 */
extern void emac_set_mac_addr(Emac* emac, uint8_t sa_idx, uint8_t* mac);

/**
 *  \brief Set MAC Address using two 32-bit integers
 */
extern void emac_set_mac_addr32(Emac* emac, uint8_t sa_idx,
			 uint32_t mac_top, uint32_t mac_bottom);

/**
 *  \brief Set MAC Address using a 64-bit integer
 */
extern void emac_set_mac_addr64(Emac* emac, uint8_t sa_idx, uint64_t mac);

/**
 *  \brief Clear all statistics registers
 */
extern void emac_clear_statistics(Emac* emac);

/**
 *  \brief Increase all statistics registers
 */
extern void emac_increase_statistics(Emac* emac);

/**
 *  \brief Enable/Disable statistics registers writing.
 */
extern void emac_enable_statistics_write(Emac* emac, bool enable);

/**
 *  \brief Start transmission
 */
extern void emac_start_transmission(Emac* emac);

/**
 *  \brief Halt transmission
 */
extern void emac_halt_transmission(Emac* emac);

/** @}*/

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_HAVE_EMAC */

#endif /* _EMAC_H_ */

