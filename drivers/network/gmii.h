/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2008, Atmel Corporation
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

#ifndef GMII_H_
#define GMII_H_

//-----------------------------------------------------------------------------
//         Definitions
//-----------------------------------------------------------------------------

// The IEEE 802.3 specification provides a 32 register address space for the PHY.

// Registers 0-15 are standard PHY registers, defined per the spec.
#define GMII_BMCR        0x00 // Basic Mode Control Register
#define GMII_BMSR        0x01 // Basic Mode Status Register
#define GMII_PHYID1R     0x02 // PHY Idendifier Register 1
#define GMII_PHYID2R     0x03 // PHY Idendifier Register 2
#define GMII_ANAR        0x04 // Auto_Negotiation Advertisement Register
#define GMII_ANLPAR      0x05 // Auto_negotiation Link Partner Ability Register
#define GMII_ANER        0x06 // Auto-negotiation Expansion Register
#define GMII_ANNPR       0x07 // Auto-negotiation Next Page Register
#define GMII_ANLPNPAR    0x08 // Auto_negotiation Link Partner Next Page Ability Register
#define GMII_1000BTCR    0x09 // 1000Base-T Control, used by KSZ9021 and KSZ9031
#define GMII_1000BTSR    0x0a // 1000Base-T Status, used by KSZ9021 and KSZ9031
#define GMII_ERCR        0x0b // Extend Register - Control Register
#define GMII_ERDWR       0x0c // Extend Register - Data Write Register
#define GMII_ERDRR       0x0d // Extend Register - Data Read Register
#define GMII_EMSR        0x0f // Extend MII Status Register

// Registers 16-31 are vendor specific registers.
#define GMII_DRCR        0x10 // Digital Reserved Control Register
#define GMII_AFEC1R      0x11 // AFE Control 1 Register
#define GMII_RXERCR      0x15 // RXER Couter Register
#define GMII_OMSOR       0x16 // Operation Mode Strap Override Register
#define GMII_OMSSR       0x17 // Operation Mode Strap Status Register
#define GMII_ECR         0x18 // Expanded Control Register
#define GMII_ICSR        0x1B // Interrupt Control/Status Register
#define GMII_LCSR        0x1D // LinkMD(r) Control/Status Register
#define GMII_PC1R        0x1E // PHY Control 1 Register
#define GMII_PC2R        0x1F // PHY Control 2 Register

// Extended Registers
#define GMII_CCR        0x100 // Common Control Register
#define GMII_SSR        0x101 // Strap Status Register
#define GMII_RCCPSR     0x104 // RGMII Clock and Control Pad Skew Register
#define GMII_RRDPSR     0x105 // RGMII RX Data Pad Skew Register

// Basic Mode Control Register (BMCR)
// Bit definitions: MII_BMCR
#define GMII_RESET            (1 << 15) // 1= Software Reset; 0=Normal Operation
#define GMII_LOOPBACK         (1 << 14) // 1=loopback Enabled; 0=Normal Operation
#define GMII_SPEED_SELECT_LSB (1 << 13) // 1,0=1000Mbps 0,1=100Mbps; 0,0=10Mbps
#define GMII_AUTONEG          (1 << 12) // Auto-negotiation Enable
#define GMII_POWER_DOWN       (1 << 11) // 1=Power down 0=Normal operation
#define GMII_ISOLATE          (1 << 10) // 1 = Isolates 0 = Normal operation
#define GMII_RESTART_AUTONEG  (1 << 9)  // 1 = Restart auto-negotiation 0 = Normal operation
#define GMII_DUPLEX_MODE      (1 << 8)  // 1 = Full duplex operation 0 = Normal operation
// Reserved (bit 7)
#define GMII_SPEED_SELECT_MSB (1 << 6)  //
// Reserved (bits 0-5)

// Basic Mode Status Register (BMSR)
// Bit definitions: MII_BMSR
#define GMII_100BASE_T4      (1 << 15) // 100BASE-T4 Capable
#define GMII_100BASE_TX_FD   (1 << 14) // 100BASE-TX Full Duplex Capable
#define GMII_100BASE_T4_HD   (1 << 13) // 100BASE-TX Half Duplex Capable
#define GMII_10BASE_T_FD     (1 << 12) // 10BASE-T Full Duplex Capable
#define GMII_10BASE_T_HD     (1 << 11) // 10BASE-T Half Duplex Capable
// Reserved (bits 9-10)
#define GMII_EXTEND_STATUS   (1 << 8)  // 1 = Extend Status Information In Reg 15
// Reserved (bit 8)
#define GMII_MF_PREAMB_SUPPR (1 << 6)  // MII Frame Preamble Suppression
#define GMII_AUTONEG_COMP    (1 << 5)  // Auto-negotiation Complete
#define GMII_REMOTE_FAULT    (1 << 4)  // Remote Fault
#define GMII_AUTONEG_ABILITY (1 << 3)  // Auto Configuration Ability
#define GMII_LINK_STATUS     (1 << 2)  // Link Status
#define GMII_JABBER_DETECT   (1 << 1)  // Jabber Detect
#define GMII_EXTEND_CAPAB    (1 << 0)  // Extended Capability

// Auto-negotiation Advertisement Register (ANAR)
// Auto-negotiation Link Partner Ability Register (ANLPAR)
// Bit definitions: MII_ANAR, MII_ANLPAR
#define GMII_NP            (1 << 15) // Next page Indication
// Reserved (bit 14)
#define GMII_RF            (1 << 13) // Remote Fault
// Reserved (bit 12)
#define GMII_PAUSE_MASK    (3 << 11) // 0,0 = No Pause
                                     // 1,0 = Asymmetric Pause (link partner)
                                     // 0,1 = Symmetric Pause
                                     // 1,1 = Symmetric & Asymmetric Pause (local device)
#define GMII_T4            (1 << 9)  // 100BASE-T4 Support
#define GMII_TX_FDX        (1 << 8)  // 100BASE-TX Full Duplex Support
#define GMII_TX_HDX        (1 << 7)  // 100BASE-TX Support
#define GMII_10_FDX        (1 << 6)  // 10BASE-T Full Duplex Support
#define GMII_10_HDX        (1 << 5)  // 10BASE-T Support
// Selector (bits 4 to 0)            // Protocol Selection Bits
#define GMII_AN_IEEE_802_3 (1 << 0)

// Operation Mode Starp Override Rgeister (OMSOR)
#define GMII_RMII_OVERRIDE (1 << 1)  // Override strap-in for RMII mode

// GMII_1000BTCR
#define GMII_1000BaseT_HALF_DUPLEX (1 << 8)
#define GMII_1000BaseT_FULL_DUPLEX (1 << 9)
#define GMII_MARSTER_SLAVE_ENABLE  (1 << 12)
#define GMII_MARSTER_SLAVE_CONFIG  (1 << 11)
#define GMII_PORT_TYPE             (1 << 10)

// GMII_1000BTSR
#define GMII_LINKP_1000BaseT_HALF_DUPLEX (1 << 10)
#define GMII_LINKP_1000BaseT_FULL_DUPLEX (1 << 11)

#endif /* GMII_H_ */
