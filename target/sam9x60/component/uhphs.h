/* ---------------------------------------------------------------------------- */
/*                Microchip Microcontroller Software Support                    */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) %copyright_year%, Microchip Technology Inc.                    */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Microchip's name may not be used to endorse or promote products derived from */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS  */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT    */
/* ARE DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT,        */
/* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF     */
/* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */
/* ---------------------------------------------------------------------------- */

#ifndef _SAM9X_UHPHS_COMPONENT_
#define _SAM9X_UHPHS_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR USB Host High Speed Port */
/* ============================================================================= */
/** \addtogroup SAM9X_UHPHS USB Host High Speed Port */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Uhphs hardware registers */
typedef struct {
  __I  uint32_t UHPHS_HCCAPBASE;        /**< \brief (Uhphs Offset: 0x0) UHPHS Host Controller Capability Register */
  __I  uint32_t UHPHS_HCSPARAMS;        /**< \brief (Uhphs Offset: 0x4) UHPHS Host Controller Structural Parameters Register */
  __I  uint32_t UHPHS_HCCPARAMS;        /**< \brief (Uhphs Offset: 0x8) UHPHS Host Controller Capability Parameters Register */
  __I  uint32_t Reserved1[1];
  __IO uint32_t UHPHS_USBCMD;           /**< \brief (Uhphs Offset: 0x10) UHPHS USB Command Register */
  __IO uint32_t UHPHS_USBSTS;           /**< \brief (Uhphs Offset: 0x14) UHPHS USB Status Register */
  __IO uint32_t UHPHS_USBINTR;          /**< \brief (Uhphs Offset: 0x18) UHPHS USB Interrupt Enable Register */
  __IO uint32_t UHPHS_FRINDEX;          /**< \brief (Uhphs Offset: 0x1C) UHPHS USB Frame Index Register */
  __IO uint32_t UHPHS_CTRLDSSEGMENT;    /**< \brief (Uhphs Offset: 0x20) UHPHS Control Data Structure Segment Register */
  __IO uint32_t UHPHS_PERIODICLISTBASE; /**< \brief (Uhphs Offset: 0x24) UHPHS Periodic Frame List Base Address Register */
  __IO uint32_t UHPHS_ASYNCLISTADDR;    /**< \brief (Uhphs Offset: 0x28) UHPHS Asynchronous List Address Register */
  __I  uint32_t Reserved2[9];
  __IO uint32_t UHPHS_CONFIGFLAG;       /**< \brief (Uhphs Offset: 0x50) UHPHS Configured Flag Register */
  __IO uint32_t UHPHS_PORTSC[3];        /**< \brief (Uhphs Offset: 0x54) UHPHS Port Status and Control Register (port = 0) */
  __I  uint32_t Reserved3[18];
  __IO uint32_t UHPHS_INSNREG06;        /**< \brief (Uhphs Offset: 0xA8) EHCI Specific Registers 06 */
  __IO uint32_t UHPHS_INSNREG07;        /**< \brief (Uhphs Offset: 0xAC) EHCI Specific Registers 07 */
} Uhphs;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- UHPHS_HCCAPBASE : (UHPHS Offset: 0x0) UHPHS Host Controller Capability Register -------- */
#define UHPHS_HCCAPBASE_CAPLENGTH_Pos 0
#define UHPHS_HCCAPBASE_CAPLENGTH_Msk (0xffu << UHPHS_HCCAPBASE_CAPLENGTH_Pos) /**< \brief (UHPHS_HCCAPBASE) Capability Registers Length */
#define UHPHS_HCCAPBASE_HCIVERSION_Pos 16
#define UHPHS_HCCAPBASE_HCIVERSION_Msk (0xffffu << UHPHS_HCCAPBASE_HCIVERSION_Pos) /**< \brief (UHPHS_HCCAPBASE) Host Controller Interface Version Number */
/* -------- UHPHS_HCSPARAMS : (UHPHS Offset: 0x4) UHPHS Host Controller Structural Parameters Register -------- */
#define UHPHS_HCSPARAMS_N_PORTS_Pos 0
#define UHPHS_HCSPARAMS_N_PORTS_Msk (0xfu << UHPHS_HCSPARAMS_N_PORTS_Pos) /**< \brief (UHPHS_HCSPARAMS) Number of Ports */
#define UHPHS_HCSPARAMS_PPC (0x1u << 4) /**< \brief (UHPHS_HCSPARAMS) Port Power Control */
#define UHPHS_HCSPARAMS_N_PCC_Pos 8
#define UHPHS_HCSPARAMS_N_PCC_Msk (0xfu << UHPHS_HCSPARAMS_N_PCC_Pos) /**< \brief (UHPHS_HCSPARAMS) Number of Ports per Companion Controller */
#define UHPHS_HCSPARAMS_N_CC_Pos 12
#define UHPHS_HCSPARAMS_N_CC_Msk (0xfu << UHPHS_HCSPARAMS_N_CC_Pos) /**< \brief (UHPHS_HCSPARAMS) Number of Companion Controllers */
#define UHPHS_HCSPARAMS_P_INDICATOR (0x1u << 16) /**< \brief (UHPHS_HCSPARAMS) Port Indicators */
#define UHPHS_HCSPARAMS_N_DP_Pos 20
#define UHPHS_HCSPARAMS_N_DP_Msk (0xfu << UHPHS_HCSPARAMS_N_DP_Pos) /**< \brief (UHPHS_HCSPARAMS) Debug Port Number */
/* -------- UHPHS_HCCPARAMS : (UHPHS Offset: 0x8) UHPHS Host Controller Capability Parameters Register -------- */
#define UHPHS_HCCPARAMS_AC (0x1u << 0) /**< \brief (UHPHS_HCCPARAMS) 64-bit Addressing Capability */
#define UHPHS_HCCPARAMS_PFLF (0x1u << 1) /**< \brief (UHPHS_HCCPARAMS) Programmable Frame List Flag */
#define UHPHS_HCCPARAMS_ASPC (0x1u << 2) /**< \brief (UHPHS_HCCPARAMS) Asynchronous Schedule Park Capability */
#define UHPHS_HCCPARAMS_IST_Pos 4
#define UHPHS_HCCPARAMS_IST_Msk (0xfu << UHPHS_HCCPARAMS_IST_Pos) /**< \brief (UHPHS_HCCPARAMS) Isochronous Scheduling Threshold */
#define UHPHS_HCCPARAMS_EECP_Pos 8
#define UHPHS_HCCPARAMS_EECP_Msk (0xffu << UHPHS_HCCPARAMS_EECP_Pos) /**< \brief (UHPHS_HCCPARAMS) EHCI Extended Capabilities Pointer */
/* -------- UHPHS_USBCMD : (UHPHS Offset: 0x10) UHPHS USB Command Register -------- */
#define UHPHS_USBCMD_RS (0x1u << 0) /**< \brief (UHPHS_USBCMD) Run/Stop (read/write) */
#define UHPHS_USBCMD_HCRESET (0x1u << 1) /**< \brief (UHPHS_USBCMD) Host Controller Reset (read/write) */
#define UHPHS_USBCMD_FLS_Pos 2
#define UHPHS_USBCMD_FLS_Msk (0x3u << UHPHS_USBCMD_FLS_Pos) /**< \brief (UHPHS_USBCMD) Frame List Size (read/write or read-only) */
#define UHPHS_USBCMD_FLS(value) ((UHPHS_USBCMD_FLS_Msk & ((value) << UHPHS_USBCMD_FLS_Pos)))
#define UHPHS_USBCMD_PSE (0x1u << 4) /**< \brief (UHPHS_USBCMD) Periodic Schedule Enable (read/write) */
#define UHPHS_USBCMD_ASE (0x1u << 5) /**< \brief (UHPHS_USBCMD) Asynchronous Schedule Enable (read/write) */
#define UHPHS_USBCMD_IAAD (0x1u << 6) /**< \brief (UHPHS_USBCMD) Interrupt on Async Advance Doorbell (read/write) */
#define UHPHS_USBCMD_LHCR (0x1u << 7) /**< \brief (UHPHS_USBCMD) Light Host Controller Reset (optional) (read/write) */
#define UHPHS_USBCMD_ASPMC_Pos 8
#define UHPHS_USBCMD_ASPMC_Msk (0x3u << UHPHS_USBCMD_ASPMC_Pos) /**< \brief (UHPHS_USBCMD) Asynchronous Schedule Park Mode Count (optional) (read/write or read-only) */
#define UHPHS_USBCMD_ASPMC(value) ((UHPHS_USBCMD_ASPMC_Msk & ((value) << UHPHS_USBCMD_ASPMC_Pos)))
#define UHPHS_USBCMD_ASPME (0x1u << 11) /**< \brief (UHPHS_USBCMD) Asynchronous Schedule Park Mode Enable (optional) (read/write or read-only) */
#define UHPHS_USBCMD_ITC_Pos 16
#define UHPHS_USBCMD_ITC_Msk (0xffu << UHPHS_USBCMD_ITC_Pos) /**< \brief (UHPHS_USBCMD) Interrupt Threshold Control (read/write) */
#define UHPHS_USBCMD_ITC(value) ((UHPHS_USBCMD_ITC_Msk & ((value) << UHPHS_USBCMD_ITC_Pos)))
/* -------- UHPHS_USBSTS : (UHPHS Offset: 0x14) UHPHS USB Status Register -------- */
#define UHPHS_USBSTS_USBINT (0x1u << 0) /**< \brief (UHPHS_USBSTS) USB Interrupt (cleared on write) */
#define UHPHS_USBSTS_USBERRINT (0x1u << 1) /**< \brief (UHPHS_USBSTS) USB Error Interrupt (cleared on write) */
#define UHPHS_USBSTS_PCD (0x1u << 2) /**< \brief (UHPHS_USBSTS) Port Change Detect (cleared on write) */
#define UHPHS_USBSTS_FLR (0x1u << 3) /**< \brief (UHPHS_USBSTS) Frame List Rollover (cleared on write) */
#define UHPHS_USBSTS_HSE (0x1u << 4) /**< \brief (UHPHS_USBSTS) Host System Error (cleared on write) */
#define UHPHS_USBSTS_IAA (0x1u << 5) /**< \brief (UHPHS_USBSTS) Interrupt on Async Advance (cleared on write) */
#define UHPHS_USBSTS_HCHLT (0x1u << 12) /**< \brief (UHPHS_USBSTS) HCHalted (read-only) */
#define UHPHS_USBSTS_RCM (0x1u << 13) /**< \brief (UHPHS_USBSTS) Reclamation (read-only) */
#define UHPHS_USBSTS_PSS (0x1u << 14) /**< \brief (UHPHS_USBSTS) Periodic Schedule Status (read-only) */
#define UHPHS_USBSTS_ASS (0x1u << 15) /**< \brief (UHPHS_USBSTS) Asynchronous Schedule Status (read-only) */
/* -------- UHPHS_USBINTR : (UHPHS Offset: 0x18) UHPHS USB Interrupt Enable Register -------- */
#define UHPHS_USBINTR_USBIE (0x1u << 0) /**< \brief (UHPHS_USBINTR) USBINT Interrupt Enable */
#define UHPHS_USBINTR_USBEIE (0x1u << 1) /**< \brief (UHPHS_USBINTR) USBERRINT Interrupt Enable */
#define UHPHS_USBINTR_PCIE (0x1u << 2) /**< \brief (UHPHS_USBINTR) Port Change Detect Interrupt Enable */
#define UHPHS_USBINTR_FLRE (0x1u << 3) /**< \brief (UHPHS_USBINTR) Frame List Rollover Interrupt Enable */
#define UHPHS_USBINTR_HSEE (0x1u << 4) /**< \brief (UHPHS_USBINTR) Host System Error Interrupt Enable */
#define UHPHS_USBINTR_IAAE (0x1u << 5) /**< \brief (UHPHS_USBINTR) Interrupt on Async Advance Enable */
/* -------- UHPHS_FRINDEX : (UHPHS Offset: 0x1C) UHPHS USB Frame Index Register -------- */
#define UHPHS_FRINDEX_FI_Pos 0
#define UHPHS_FRINDEX_FI_Msk (0x3fffu << UHPHS_FRINDEX_FI_Pos) /**< \brief (UHPHS_FRINDEX) Frame Index */
#define UHPHS_FRINDEX_FI(value) ((UHPHS_FRINDEX_FI_Msk & ((value) << UHPHS_FRINDEX_FI_Pos)))
/* -------- UHPHS_PERIODICLISTBASE : (UHPHS Offset: 0x24) UHPHS Periodic Frame List Base Address Register -------- */
#define UHPHS_PERIODICLISTBASE_BA_Pos 12
#define UHPHS_PERIODICLISTBASE_BA_Msk (0xfffffu << UHPHS_PERIODICLISTBASE_BA_Pos) /**< \brief (UHPHS_PERIODICLISTBASE) Base Address (Low) */
#define UHPHS_PERIODICLISTBASE_BA(value) ((UHPHS_PERIODICLISTBASE_BA_Msk & ((value) << UHPHS_PERIODICLISTBASE_BA_Pos)))
/* -------- UHPHS_ASYNCLISTADDR : (UHPHS Offset: 0x28) UHPHS Asynchronous List Address Register -------- */
#define UHPHS_ASYNCLISTADDR_LPL_Pos 5
#define UHPHS_ASYNCLISTADDR_LPL_Msk (0x7ffffffu << UHPHS_ASYNCLISTADDR_LPL_Pos) /**< \brief (UHPHS_ASYNCLISTADDR) Link Pointer Low */
#define UHPHS_ASYNCLISTADDR_LPL(value) ((UHPHS_ASYNCLISTADDR_LPL_Msk & ((value) << UHPHS_ASYNCLISTADDR_LPL_Pos)))
/* -------- UHPHS_CONFIGFLAG : (UHPHS Offset: 0x50) UHPHS Configured Flag Register -------- */
#define UHPHS_CONFIGFLAG_CF (0x1u << 0) /**< \brief (UHPHS_CONFIGFLAG) Configure Flag (Read/Write) */
/* -------- UHPHS_PORTSC[3] : (UHPHS Offset: 0x54) UHPHS Port Status and Control Register (port = 0) -------- */
#define UHPHS_PORTSC_CCS (0x1u << 0) /**< \brief (UHPHS_PORTSC[3]) Current Connect Status (read-only) */
#define UHPHS_PORTSC_CSC (0x1u << 1) /**< \brief (UHPHS_PORTSC[3]) Connect Status Change (read/write clear) */
#define UHPHS_PORTSC_PED (0x1u << 2) /**< \brief (UHPHS_PORTSC[3]) Port Enabled/Disabled (read/write) */
#define UHPHS_PORTSC_PEDC (0x1u << 3) /**< \brief (UHPHS_PORTSC[3]) Port Enable/Disable Change (read/write clear) */
#define UHPHS_PORTSC_OCA (0x1u << 4) /**< \brief (UHPHS_PORTSC[3]) Over-current Active (read-only) */
#define UHPHS_PORTSC_OCC (0x1u << 5) /**< \brief (UHPHS_PORTSC[3]) Over-current Change (read/write clear) */
#define UHPHS_PORTSC_FPR (0x1u << 6) /**< \brief (UHPHS_PORTSC[3]) Force Port Resume (read/write) */
#define UHPHS_PORTSC_SUS (0x1u << 7) /**< \brief (UHPHS_PORTSC[3]) Suspend (read/write) */
#define UHPHS_PORTSC_PR (0x1u << 8) /**< \brief (UHPHS_PORTSC[3]) Port Reset (read/write) */
#define UHPHS_PORTSC_LS_Pos 10
#define UHPHS_PORTSC_LS_Msk (0x3u << UHPHS_PORTSC_LS_Pos) /**< \brief (UHPHS_PORTSC[3]) Line Status (read-only) */
#define UHPHS_PORTSC_LS(value) ((UHPHS_PORTSC_LS_Msk & ((value) << UHPHS_PORTSC_LS_Pos)))
#define   UHPHS_PORTSC_LS_SE0 (0x0u << 10) /**< \brief (UHPHS_PORTSC[3]) Not a low-speed device, perform EHCI reset */
#define   UHPHS_PORTSC_LS_K_STATE (0x1u << 10) /**< \brief (UHPHS_PORTSC[3]) Low-speed device, release ownership of port */
#define   UHPHS_PORTSC_LS_J_STATE (0x2u << 10) /**< \brief (UHPHS_PORTSC[3]) Not a low-speed device, perform EHCI reset */
#define   UHPHS_PORTSC_LS_UNDEFINED (0x3u << 10) /**< \brief (UHPHS_PORTSC[3]) Not a low-speed device, perform EHCI reset */
#define UHPHS_PORTSC_PP (0x1u << 12) /**< \brief (UHPHS_PORTSC[3]) Port Power (read/write or read-only) */
#define UHPHS_PORTSC_PO (0x1u << 13) /**< \brief (UHPHS_PORTSC[3]) Port Owner (read/write) */
#define UHPHS_PORTSC_PIC_Pos 14
#define UHPHS_PORTSC_PIC_Msk (0x3u << UHPHS_PORTSC_PIC_Pos) /**< \brief (UHPHS_PORTSC[3]) Port Indicator Control (read/write) */
#define UHPHS_PORTSC_PIC(value) ((UHPHS_PORTSC_PIC_Msk & ((value) << UHPHS_PORTSC_PIC_Pos)))
#define UHPHS_PORTSC_PTC_Pos 16
#define UHPHS_PORTSC_PTC_Msk (0xfu << UHPHS_PORTSC_PTC_Pos) /**< \brief (UHPHS_PORTSC[3]) Port Test Control (read/write) */
#define UHPHS_PORTSC_PTC(value) ((UHPHS_PORTSC_PTC_Msk & ((value) << UHPHS_PORTSC_PTC_Pos)))
#define UHPHS_PORTSC_WKCNNT_E (0x1u << 20) /**< \brief (UHPHS_PORTSC[3]) Wake on Connect Enable (read/write) */
#define UHPHS_PORTSC_WKDSCNNT_E (0x1u << 21) /**< \brief (UHPHS_PORTSC[3]) Wake on Disconnect Enable (read/write) */
#define UHPHS_PORTSC_WKOC_E (0x1u << 22) /**< \brief (UHPHS_PORTSC[3]) Wake on Over-current Enable (read/write) */
/* -------- UHPHS_INSNREG06 : (UHPHS Offset: 0xA8) EHCI Specific Registers 06 -------- */
#define UHPHS_INSNREG06_Nb_Success_Burst_Pos 0
#define UHPHS_INSNREG06_Nb_Success_Burst_Msk (0xfu << UHPHS_INSNREG06_Nb_Success_Burst_Pos) /**< \brief (UHPHS_INSNREG06) Number of Successful Bursts (Read-only) */
#define UHPHS_INSNREG06_Nb_Success_Burst(value) ((UHPHS_INSNREG06_Nb_Success_Burst_Msk & ((value) << UHPHS_INSNREG06_Nb_Success_Burst_Pos)))
#define UHPHS_INSNREG06_Nb_Burst_Pos 4
#define UHPHS_INSNREG06_Nb_Burst_Msk (0x1fu << UHPHS_INSNREG06_Nb_Burst_Pos) /**< \brief (UHPHS_INSNREG06) Number of Bursts (Read-only) */
#define UHPHS_INSNREG06_Nb_Burst(value) ((UHPHS_INSNREG06_Nb_Burst_Msk & ((value) << UHPHS_INSNREG06_Nb_Burst_Pos)))
#define UHPHS_INSNREG06_HBURST_Pos 9
#define UHPHS_INSNREG06_HBURST_Msk (0x7u << UHPHS_INSNREG06_HBURST_Pos) /**< \brief (UHPHS_INSNREG06) Burst Value (Read-only) */
#define UHPHS_INSNREG06_HBURST(value) ((UHPHS_INSNREG06_HBURST_Msk & ((value) << UHPHS_INSNREG06_HBURST_Pos)))
#define UHPHS_INSNREG06_AHB_ERR (0x1u << 31) /**< \brief (UHPHS_INSNREG06) AHB Error */
/* -------- UHPHS_INSNREG07 : (UHPHS Offset: 0xAC) EHCI Specific Registers 07 -------- */
#define UHPHS_INSNREG07_AHB_ADDR_Pos 0
#define UHPHS_INSNREG07_AHB_ADDR_Msk (0xffffffffu << UHPHS_INSNREG07_AHB_ADDR_Pos) /**< \brief (UHPHS_INSNREG07) AHB Address (Read Only) */
#define UHPHS_INSNREG07_AHB_ADDR(value) ((UHPHS_INSNREG07_AHB_ADDR_Msk & ((value) << UHPHS_INSNREG07_AHB_ADDR_Pos)))

/*@}*/


#endif /* _SAM9X_UHPHS_COMPONENT_ */
