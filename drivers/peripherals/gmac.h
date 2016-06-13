/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
 *   - ...
 * - Setup Gmac::GMAC_NCR with gmac_network_control(), more related controls
 *   can modify with:
 *   - gmac_receive_enable(): Enable/Disable Rx.
 *   - gmac_transmit_enable(): Enable/Disable Tx.
 *   - ...
 * - Manage GMAC interrupts with gmac_enable_it(), gmac_disable_it(),
 *   gmac_get_it_mask() and gmac_get_it_status().
 * - Manage GMAC Tx/Rx status with gmac_get_tx_status(), gmac_get_rx_status()
 *   gmac_clear_tx_status() and gmac_clear_rx_status().
 * - Manage PHY through GMAC is performed by
 *   - gmac_phy_read(): Read data from PHY.
 *   - gmac_phy_read(): Read data from PHY.
 *   - gmac_enable_mdio(): Enable management port.
 *   - gmac_disable_mdio(): Disable management port.
 * - Setup GMAC parameters with following functions:
 *   - gmac_set_mac_addr(), gmac_set_mac_addr32(), gmac_set_mac_addr64(): Set MAC address.
 * - Switch GMAC MII/RMII mode through gmac_enable_rmii()
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

#ifndef _GMAC_H_
#define _GMAC_H_

#ifdef CONFIG_HAVE_GMAC

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "peripherals/ethd.h"

/*----------------------------------------------------------------------------
 *        Defines
 *----------------------------------------------------------------------------*/

/** \addtogroup gmac_defines
	@{*/

#ifdef CONFIG_HAVE_GMAC_QUEUES
#define GMAC_NUM_QUEUES 3
#else
#define GMAC_NUM_QUEUES 1
#endif

#define GMAC_MAX_JUMBO_FRAME_LENGTH 10240

/**@}*/

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** \addtogroup gmac_structs
	@{*/

/**     @}*/

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * TODO
 */
extern bool gmac_configure(Gmac *gmac);

/**
 *  \brief Write NCR register value
 */
extern void gmac_set_network_control_register(Gmac * gmac, uint32_t ncr);

/**
 *  \brief Get NCR register value
 */
extern uint32_t gmac_get_network_control_register(Gmac * gmac);

/**
 *  \brief Set network configuration register
 */
extern void gmac_set_network_config_register(Gmac* gmac, uint32_t ncfgr);

/**
 *  \brief Get network configuration register
 */

extern uint32_t gmac_get_network_config_register(Gmac* gmac);

/**
 *  \brief Enable MDI with PHY
 *  \param gmac Pointer to an Gmac instance.
 */
extern void gmac_enable_mdio(Gmac* gmac);

/**
 *  \brief Disable MDI with PHY
 *  \param gmac Pointer to an Gmac instance.
 */
extern void gmac_disable_mdio(Gmac* gmac);

/**
 *  \brief Execute PHY read command
 */
extern bool gmac_phy_read(Gmac* gmac, uint8_t phy_addr, uint8_t reg_addr,
		uint16_t* data, uint32_t retries);

/**
 *  \brief Execute PHY write command
 */
extern bool gmac_phy_write(Gmac* gmac, uint8_t phy_addr, uint8_t reg_addr,
		uint16_t data, uint32_t retries);

/**
 *  \brief Enable MII mode for GMAC, called once after autonegotiate
 *  \param gmac Pointer to an Gmac instance.
 */
extern void gmac_enable_mii(Gmac* gmac);

/**
 *  \brief Enable RMII mode for GMAC, called once after autonegotiate
 *  \param gmac Pointer to an Gmac instance.
 *  \param duplex: 1 full duplex 0 half duplex
 *  \param speed: 0 10M 1 100M
 */
extern void gmac_enable_rmii(Gmac* gmac, enum _eth_speed speed,
		enum _eth_duplex duplex);

/**
 *  \brief Setup the GMAC for the link : speed 100M/10M and Full/Half duplex
 *  \param gmac Pointer to an Gmac instance.
 *  \param speed Link speed, 0 for 10M, 1 for 100M
 *  \param fullduplex 1 for Full Duplex mode
 */
extern void gmac_set_link_speed(Gmac* gmac, enum _eth_speed speed,
		enum _eth_duplex duplex);

/**
 *  \brief Enable local loop back
 *  \param gmac Pointer to an Gmac instance.
 */
extern void gmac_enable_local_loopback(Gmac* gmac);

/**
 *  \brief Disable local loop back
 *  \param gmac Pointer to an Gmac instance.
 */
extern void gmac_disable_local_loopback(Gmac* gmac);

/**
 *  \brief Return transmit status
 */
extern uint32_t gmac_get_tx_status(Gmac* gmac);

/**
 *  \brief Clear transmit status
 */
extern void gmac_clear_tx_status(Gmac* gmac, uint32_t mask);

/**
 *  \brief Return receive status
 */
extern uint32_t gmac_get_rx_status(Gmac* gmac);

/**
 *  \brief Clear receive status
 */
extern void gmac_clear_rx_status(Gmac* gmac, uint32_t mask);

/**
 *  \brief Enable/Disable GMAC receive.
 */
extern void gmac_receive_enable(Gmac* gmac, bool enable);

/**
 *  \brief Enable/Disable GMAC transmit.
 */
extern void gmac_transmit_enable(Gmac* gmac, bool enable);

/**
 *  \brief Set RX descriptor address
 */
void gmac_set_rx_desc(Gmac* gmac, uint8_t queue, struct _eth_desc* desc);

/**
 *  \brief Get RX descriptor address
 */
struct _eth_desc* gmac_get_rx_desc(Gmac* gmac, uint8_t queue);

/**
 *  \brief Set TX descriptor address
 */
void gmac_set_tx_desc(Gmac* gmac, uint8_t queue, struct _eth_desc* desc);

/**
 *  \brief Get TX descriptor address
 */
struct _eth_desc* gmac_get_tx_desc(Gmac* gmac, uint8_t queue);

/**
 *  \brief Return interrupt mask.
 */
extern uint32_t gmac_get_it_mask(Gmac* gmac, uint8_t queue);

/**
 *  \brief Enable interrupt(s).
 */
extern void gmac_enable_it(Gmac* gmac, uint8_t queue, uint32_t mask);

/**
 *  \brief Disable interrupt(s).
 */
extern void gmac_disable_it(Gmac * gmac, uint8_t queue, uint32_t mask);

/**
 *  \brief Return interrupt status mask.
 */
extern uint32_t gmac_get_it_status(Gmac* gmac, uint8_t queue);

/**
 *  \brief Set MAC Address
 */
extern void gmac_set_mac_addr(Gmac* gmac, uint8_t sa_idx, uint8_t* mac);

/**
 *  \brief Set MAC Address using two 32-bit integers
 */
extern void gmac_set_mac_addr32(Gmac* gmac, uint8_t sa_idx,
			 uint32_t mac_top, uint32_t mac_bottom);

/**
 *  \brief Set MAC Address using a 64-bit integer
 */
extern void gmac_set_mac_addr64(Gmac* gmac, uint8_t sa_idx, uint64_t mac);

/**
 *  \brief Clear all statistics registers
 */
extern void gmac_clear_statistics(Gmac* gmac);

/**
 *  \brief Increase all statistics registers
 */
extern void gmac_increase_statistics(Gmac* gmac);

/**
 *  \brief Enable/Disable statistics registers writing.
 */
extern void gmac_enable_statistics_write(Gmac* gmac, bool enable);

/**
 *  \brief Start transmission
 */
extern void gmac_start_transmission(Gmac* gmac);

/**
 *  \brief Halt transmission
 */
extern void gmac_halt_transmission(Gmac* gmac);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_HAVE_GMAC */

#endif /* _GMAC_H_ */
