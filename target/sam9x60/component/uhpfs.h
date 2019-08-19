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

#ifndef _SAM9X_UHPFS_COMPONENT_
#define _SAM9X_UHPFS_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR USB Host Full-Speed Port */
/* ============================================================================= */
/** \addtogroup SAM9X_UHPFS USB Host Full-Speed Port */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Uhpfs hardware registers */
typedef struct {
  __I  uint32_t UHPFS_HcRevision;         /**< \brief (Uhpfs Offset: 0x0) OHCI Revision Number Register */
  __IO uint32_t UHPFS_HcControl;          /**< \brief (Uhpfs Offset: 0x4) HC Operating Mode Register */
  __IO uint32_t UHPFS_HcCommandStatus;    /**< \brief (Uhpfs Offset: 0x8) HC Command and Status Register */
  __IO uint32_t UHPFS_HcInterruptStatus;  /**< \brief (Uhpfs Offset: 0xC) HC Interrupt and Status Register */
  __IO uint32_t UHPFS_HcInterruptEnable;  /**< \brief (Uhpfs Offset: 0x10) HC Interrupt Enable Register */
  __IO uint32_t UHPFS_HcInterruptDisable; /**< \brief (Uhpfs Offset: 0x14) HC Interrupt Disable Register */
  __IO uint32_t UHPFS_HcHCCA;             /**< \brief (Uhpfs Offset: 0x18) HC HCCA Address Register */
  __IO uint32_t UHPFS_HcPeriodCurrentED;  /**< \brief (Uhpfs Offset: 0x1C) HC Current Periodic Register */
  __IO uint32_t UHPFS_HcControlHeadED;    /**< \brief (Uhpfs Offset: 0x20) HC Head Control Register */
  __IO uint32_t UHPFS_HcControlCurrentED; /**< \brief (Uhpfs Offset: 0x24) HC Current Control Register */
  __IO uint32_t UHPFS_HcBulkHeadED;       /**< \brief (Uhpfs Offset: 0x28) HC Head Bulk Register */
  __IO uint32_t UHPFS_HcBulkCurrentED;    /**< \brief (Uhpfs Offset: 0x2C) HC Current Bulk Register */
  __IO uint32_t UHPFS_HcDoneHead;         /**< \brief (Uhpfs Offset: 0x30) HC Head Done Register */
  __IO uint32_t UHPFS_HcFmInterval;       /**< \brief (Uhpfs Offset: 0x34) HC Frame Interval Register */
  __IO uint32_t UHPFS_HcFmRemaining;      /**< \brief (Uhpfs Offset: 0x38) HC Frame Remaining Register */
  __IO uint32_t UHPFS_HcFmNumber;         /**< \brief (Uhpfs Offset: 0x3C) HC Frame Number Register */
  __IO uint32_t UHPFS_HcPeriodicStart;    /**< \brief (Uhpfs Offset: 0x40) HC Periodic Start Register */
  __IO uint32_t UHPFS_HcLSThreshold;      /**< \brief (Uhpfs Offset: 0x44) HC Low-Speed Threshold Register */
  __IO uint32_t UHPFS_HcRhDescriptorA;    /**< \brief (Uhpfs Offset: 0x48) HC Root Hub A Register */
  __IO uint32_t UHPFS_HcRhDescriptorB;    /**< \brief (Uhpfs Offset: 0x4C) HC Root Hub B Register */
  __IO uint32_t UHPFS_HcRhStatus;         /**< \brief (Uhpfs Offset: 0x50) HC Root Hub Status Register */
  __IO uint32_t UHPFS_HcRhPortStatus[3];  /**< \brief (Uhpfs Offset: 0x54) HC Port Status and Control Register (ndp = 0) */
} Uhpfs;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- UHPFS_HcRevision : (UHPFS Offset: 0x0) OHCI Revision Number Register -------- */
#define UHPFS_HcRevision_REV_Pos 0
#define UHPFS_HcRevision_REV_Msk (0xffu << UHPFS_HcRevision_REV_Pos) /**< \brief (UHPFS_HcRevision) OHCI Revision Number */
/* -------- UHPFS_HcControl : (UHPFS Offset: 0x4) HC Operating Mode Register -------- */
#define UHPFS_HcControl_CBSR_Pos 0
#define UHPFS_HcControl_CBSR_Msk (0x3u << UHPFS_HcControl_CBSR_Pos) /**< \brief (UHPFS_HcControl) Control/Bulk Service Ratio */
#define UHPFS_HcControl_CBSR(value) ((UHPFS_HcControl_CBSR_Msk & ((value) << UHPFS_HcControl_CBSR_Pos)))
#define UHPFS_HcControl_PLE (0x1u << 2) /**< \brief (UHPFS_HcControl) Periodic List Enable */
#define UHPFS_HcControl_IE (0x1u << 3) /**< \brief (UHPFS_HcControl) Isochronous Enable */
#define UHPFS_HcControl_CLE (0x1u << 4) /**< \brief (UHPFS_HcControl) ControL List Enable */
#define UHPFS_HcControl_BLE (0x1u << 5) /**< \brief (UHPFS_HcControl) Bulk List Enable */
#define UHPFS_HcControl_HCFS_Pos 6
#define UHPFS_HcControl_HCFS_Msk (0x3u << UHPFS_HcControl_HCFS_Pos) /**< \brief (UHPFS_HcControl) Host Controller Functional State */
#define UHPFS_HcControl_HCFS(value) ((UHPFS_HcControl_HCFS_Msk & ((value) << UHPFS_HcControl_HCFS_Pos)))
#define UHPFS_HcControl_IR (0x1u << 8) /**< \brief (UHPFS_HcControl) Interrupt Routing */
#define UHPFS_HcControl_RWC (0x1u << 9) /**< \brief (UHPFS_HcControl) Remote Wakeup Connected */
#define UHPFS_HcControl_RWE (0x1u << 10) /**< \brief (UHPFS_HcControl) Remote Wakeup Enable */
/* -------- UHPFS_HcCommandStatus : (UHPFS Offset: 0x8) HC Command and Status Register -------- */
#define UHPFS_HcCommandStatus_HCR (0x1u << 0) /**< \brief (UHPFS_HcCommandStatus) Host Controller Reset (read/write) */
#define UHPFS_HcCommandStatus_CLF (0x1u << 1) /**< \brief (UHPFS_HcCommandStatus) Control List Filled (read/write) */
#define UHPFS_HcCommandStatus_BLF (0x1u << 2) /**< \brief (UHPFS_HcCommandStatus) Bulk List Filled (read/write) */
#define UHPFS_HcCommandStatus_OCR (0x1u << 3) /**< \brief (UHPFS_HcCommandStatus) Ownership Change Request (read/write) */
#define UHPFS_HcCommandStatus_SOC_Pos 16
#define UHPFS_HcCommandStatus_SOC_Msk (0x3u << UHPFS_HcCommandStatus_SOC_Pos) /**< \brief (UHPFS_HcCommandStatus) Scheduling Overrun Count (read-only) */
#define UHPFS_HcCommandStatus_SOC(value) ((UHPFS_HcCommandStatus_SOC_Msk & ((value) << UHPFS_HcCommandStatus_SOC_Pos)))
/* -------- UHPFS_HcInterruptStatus : (UHPFS Offset: 0xC) HC Interrupt and Status Register -------- */
#define UHPFS_HcInterruptStatus_SO (0x1u << 0) /**< \brief (UHPFS_HcInterruptStatus) Scheduling Overrun (read/write, write '1' to clear) */
#define UHPFS_HcInterruptStatus_WDH (0x1u << 1) /**< \brief (UHPFS_HcInterruptStatus) Write Done Head (read/write, write '1' to clear) */
#define UHPFS_HcInterruptStatus_SF (0x1u << 2) /**< \brief (UHPFS_HcInterruptStatus) Start of Frame (read/write, write '1' to clear) */
#define UHPFS_HcInterruptStatus_RD (0x1u << 3) /**< \brief (UHPFS_HcInterruptStatus) Resume Detected (read/write, write '1' to clear) */
#define UHPFS_HcInterruptStatus_UE (0x1u << 4) /**< \brief (UHPFS_HcInterruptStatus) Unrecoverable Error (read/write, write '1' to clear) */
#define UHPFS_HcInterruptStatus_FNO (0x1u << 5) /**< \brief (UHPFS_HcInterruptStatus) Frame Number Overflow (read/write, write '1' to clear) */
#define UHPFS_HcInterruptStatus_RHSC (0x1u << 6) /**< \brief (UHPFS_HcInterruptStatus) Root Hub Status Change (read/write, write '1' to clear) */
#define UHPFS_HcInterruptStatus_OC (0x1u << 30) /**< \brief (UHPFS_HcInterruptStatus) Ownership Change (read-only) */
/* -------- UHPFS_HcInterruptEnable : (UHPFS Offset: 0x10) HC Interrupt Enable Register -------- */
#define UHPFS_HcInterruptEnable_SO (0x1u << 0) /**< \brief (UHPFS_HcInterruptEnable) Scheduling Overrun (read/write, write '1' to set) */
#define UHPFS_HcInterruptEnable_WDH (0x1u << 1) /**< \brief (UHPFS_HcInterruptEnable) Write Done Head (read/write, write '1' to set) */
#define UHPFS_HcInterruptEnable_SF (0x1u << 2) /**< \brief (UHPFS_HcInterruptEnable) Start of Frame (read/write, write '1' to set) */
#define UHPFS_HcInterruptEnable_RD (0x1u << 3) /**< \brief (UHPFS_HcInterruptEnable) Resume Detected (read/write, write '1' to set) */
#define UHPFS_HcInterruptEnable_UE (0x1u << 4) /**< \brief (UHPFS_HcInterruptEnable) Unrecoverable Error (read/write, write '1' to set) */
#define UHPFS_HcInterruptEnable_FNO (0x1u << 5) /**< \brief (UHPFS_HcInterruptEnable) Frame Number Overflow (read/write, write '1' to set) */
#define UHPFS_HcInterruptEnable_RHSC (0x1u << 6) /**< \brief (UHPFS_HcInterruptEnable) Root Hub Status Change (read/write, write '1' to set) */
#define UHPFS_HcInterruptEnable_OC (0x1u << 30) /**< \brief (UHPFS_HcInterruptEnable) Ownership Change (read-only) */
#define UHPFS_HcInterruptEnable_MIE (0x1u << 31) /**< \brief (UHPFS_HcInterruptEnable) Master Interrupt Enable (read/write, write '1' to set) */
/* -------- UHPFS_HcInterruptDisable : (UHPFS Offset: 0x14) HC Interrupt Disable Register -------- */
#define UHPFS_HcInterruptDisable_SO (0x1u << 0) /**< \brief (UHPFS_HcInterruptDisable) Scheduling Overrun (read/write) */
#define UHPFS_HcInterruptDisable_WDH (0x1u << 1) /**< \brief (UHPFS_HcInterruptDisable) Write Done Head (read/write) */
#define UHPFS_HcInterruptDisable_SF (0x1u << 2) /**< \brief (UHPFS_HcInterruptDisable) Start of Frame (read/write) */
#define UHPFS_HcInterruptDisable_RD (0x1u << 3) /**< \brief (UHPFS_HcInterruptDisable) Resume Detected (read/write) */
#define UHPFS_HcInterruptDisable_UE (0x1u << 4) /**< \brief (UHPFS_HcInterruptDisable) Unrecoverable Error (read/write) */
#define UHPFS_HcInterruptDisable_FNO (0x1u << 5) /**< \brief (UHPFS_HcInterruptDisable) Frame Number Overflow (read/write) */
#define UHPFS_HcInterruptDisable_RHSC (0x1u << 6) /**< \brief (UHPFS_HcInterruptDisable) Root Hub Status Change (read/write) */
#define UHPFS_HcInterruptDisable_OC (0x1u << 30) /**< \brief (UHPFS_HcInterruptDisable) Ownership Change (read-only) */
#define UHPFS_HcInterruptDisable_MIE (0x1u << 31) /**< \brief (UHPFS_HcInterruptDisable) Master Interrupt Enable (read/write) */
/* -------- UHPFS_HcHCCA : (UHPFS Offset: 0x18) HC HCCA Address Register -------- */
#define UHPFS_HcHCCA_HCCA_Pos 8
#define UHPFS_HcHCCA_HCCA_Msk (0xffffffu << UHPFS_HcHCCA_HCCA_Pos) /**< \brief (UHPFS_HcHCCA) Physical Address of the Beginning of the HCCA */
#define UHPFS_HcHCCA_HCCA(value) ((UHPFS_HcHCCA_HCCA_Msk & ((value) << UHPFS_HcHCCA_HCCA_Pos)))
/* -------- UHPFS_HcPeriodCurrentED : (UHPFS Offset: 0x1C) HC Current Periodic Register -------- */
#define UHPFS_HcPeriodCurrentED_PCED_Pos 4
#define UHPFS_HcPeriodCurrentED_PCED_Msk (0xfffffffu << UHPFS_HcPeriodCurrentED_PCED_Pos) /**< \brief (UHPFS_HcPeriodCurrentED) Physical Address of the Current ED on the Periodic ED list */
#define UHPFS_HcPeriodCurrentED_PCED(value) ((UHPFS_HcPeriodCurrentED_PCED_Msk & ((value) << UHPFS_HcPeriodCurrentED_PCED_Pos)))
/* -------- UHPFS_HcControlHeadED : (UHPFS Offset: 0x20) HC Head Control Register -------- */
#define UHPFS_HcControlHeadED_CHED_Pos 4
#define UHPFS_HcControlHeadED_CHED_Msk (0xfffffffu << UHPFS_HcControlHeadED_CHED_Pos) /**< \brief (UHPFS_HcControlHeadED) Physical Address of the Head ED on the Control ED list */
#define UHPFS_HcControlHeadED_CHED(value) ((UHPFS_HcControlHeadED_CHED_Msk & ((value) << UHPFS_HcControlHeadED_CHED_Pos)))
/* -------- UHPFS_HcControlCurrentED : (UHPFS Offset: 0x24) HC Current Control Register -------- */
#define UHPFS_HcControlCurrentED_CCED_Pos 4
#define UHPFS_HcControlCurrentED_CCED_Msk (0xfffffffu << UHPFS_HcControlCurrentED_CCED_Pos) /**< \brief (UHPFS_HcControlCurrentED) Physical Address of the Current ED on the Control ED List */
#define UHPFS_HcControlCurrentED_CCED(value) ((UHPFS_HcControlCurrentED_CCED_Msk & ((value) << UHPFS_HcControlCurrentED_CCED_Pos)))
/* -------- UHPFS_HcBulkHeadED : (UHPFS Offset: 0x28) HC Head Bulk Register -------- */
#define UHPFS_HcBulkHeadED_BHED_Pos 4
#define UHPFS_HcBulkHeadED_BHED_Msk (0xfffffffu << UHPFS_HcBulkHeadED_BHED_Pos) /**< \brief (UHPFS_HcBulkHeadED) Physical Address of the Head ED on the Bulk ED List */
#define UHPFS_HcBulkHeadED_BHED(value) ((UHPFS_HcBulkHeadED_BHED_Msk & ((value) << UHPFS_HcBulkHeadED_BHED_Pos)))
/* -------- UHPFS_HcBulkCurrentED : (UHPFS Offset: 0x2C) HC Current Bulk Register -------- */
#define UHPFS_HcBulkCurrentED_BCED_Pos 4
#define UHPFS_HcBulkCurrentED_BCED_Msk (0xfffffffu << UHPFS_HcBulkCurrentED_BCED_Pos) /**< \brief (UHPFS_HcBulkCurrentED) Physical Address of the Current ED on the Bulk ED List */
#define UHPFS_HcBulkCurrentED_BCED(value) ((UHPFS_HcBulkCurrentED_BCED_Msk & ((value) << UHPFS_HcBulkCurrentED_BCED_Pos)))
/* -------- UHPFS_HcDoneHead : (UHPFS Offset: 0x30) HC Head Done Register -------- */
#define UHPFS_HcDoneHead_DH_Pos 4
#define UHPFS_HcDoneHead_DH_Msk (0xfffffffu << UHPFS_HcDoneHead_DH_Pos) /**< \brief (UHPFS_HcDoneHead) Physical Address of the Last TD that has added to the done queue */
#define UHPFS_HcDoneHead_DH(value) ((UHPFS_HcDoneHead_DH_Msk & ((value) << UHPFS_HcDoneHead_DH_Pos)))
/* -------- UHPFS_HcFmInterval : (UHPFS Offset: 0x34) HC Frame Interval Register -------- */
#define UHPFS_HcFmInterval_FRAMEINTERVAL_Pos 0
#define UHPFS_HcFmInterval_FRAMEINTERVAL_Msk (0x3fffu << UHPFS_HcFmInterval_FRAMEINTERVAL_Pos) /**< \brief (UHPFS_HcFmInterval) Frame Interval */
#define UHPFS_HcFmInterval_FRAMEINTERVAL(value) ((UHPFS_HcFmInterval_FRAMEINTERVAL_Msk & ((value) << UHPFS_HcFmInterval_FRAMEINTERVAL_Pos)))
#define UHPFS_HcFmInterval_FSMPS_Pos 16
#define UHPFS_HcFmInterval_FSMPS_Msk (0x7fffu << UHPFS_HcFmInterval_FSMPS_Pos) /**< \brief (UHPFS_HcFmInterval) Largest Data Packet */
#define UHPFS_HcFmInterval_FSMPS(value) ((UHPFS_HcFmInterval_FSMPS_Msk & ((value) << UHPFS_HcFmInterval_FSMPS_Pos)))
#define UHPFS_HcFmInterval_FIT (0x1u << 31) /**< \brief (UHPFS_HcFmInterval) Frame Interval Toggle */
/* -------- UHPFS_HcFmRemaining : (UHPFS Offset: 0x38) HC Frame Remaining Register -------- */
#define UHPFS_HcFmRemaining_FR_Pos 0
#define UHPFS_HcFmRemaining_FR_Msk (0x3fffu << UHPFS_HcFmRemaining_FR_Pos) /**< \brief (UHPFS_HcFmRemaining) Frame Remaining */
#define UHPFS_HcFmRemaining_FR(value) ((UHPFS_HcFmRemaining_FR_Msk & ((value) << UHPFS_HcFmRemaining_FR_Pos)))
#define UHPFS_HcFmRemaining_FRT (0x1u << 31) /**< \brief (UHPFS_HcFmRemaining) Frame Remaining Toggle */
/* -------- UHPFS_HcFmNumber : (UHPFS Offset: 0x3C) HC Frame Number Register -------- */
#define UHPFS_HcFmNumber_FN_Pos 0
#define UHPFS_HcFmNumber_FN_Msk (0xffffu << UHPFS_HcFmNumber_FN_Pos) /**< \brief (UHPFS_HcFmNumber) Frame Number */
#define UHPFS_HcFmNumber_FN(value) ((UHPFS_HcFmNumber_FN_Msk & ((value) << UHPFS_HcFmNumber_FN_Pos)))
/* -------- UHPFS_HcPeriodicStart : (UHPFS Offset: 0x40) HC Periodic Start Register -------- */
#define UHPFS_HcPeriodicStart_PS_Pos 0
#define UHPFS_HcPeriodicStart_PS_Msk (0x3fffu << UHPFS_HcPeriodicStart_PS_Pos) /**< \brief (UHPFS_HcPeriodicStart) Periodic Start */
#define UHPFS_HcPeriodicStart_PS(value) ((UHPFS_HcPeriodicStart_PS_Msk & ((value) << UHPFS_HcPeriodicStart_PS_Pos)))
/* -------- UHPFS_HcLSThreshold : (UHPFS Offset: 0x44) HC Low-Speed Threshold Register -------- */
#define UHPFS_HcLSThreshold_LST_Pos 0
#define UHPFS_HcLSThreshold_LST_Msk (0x3fffu << UHPFS_HcLSThreshold_LST_Pos) /**< \brief (UHPFS_HcLSThreshold) Low-Speed Threshold */
#define UHPFS_HcLSThreshold_LST(value) ((UHPFS_HcLSThreshold_LST_Msk & ((value) << UHPFS_HcLSThreshold_LST_Pos)))
/* -------- UHPFS_HcRhDescriptorA : (UHPFS Offset: 0x48) HC Root Hub A Register -------- */
#define UHPFS_HcRhDescriptorA_NDP_Pos 0
#define UHPFS_HcRhDescriptorA_NDP_Msk (0xffu << UHPFS_HcRhDescriptorA_NDP_Pos) /**< \brief (UHPFS_HcRhDescriptorA) Number of Downstream Ports (read-only) */
#define UHPFS_HcRhDescriptorA_NDP(value) ((UHPFS_HcRhDescriptorA_NDP_Msk & ((value) << UHPFS_HcRhDescriptorA_NDP_Pos)))
#define UHPFS_HcRhDescriptorA_PSM (0x1u << 8) /**< \brief (UHPFS_HcRhDescriptorA) Power Switching Mode (read/write) */
#define UHPFS_HcRhDescriptorA_NPS (0x1u << 9) /**< \brief (UHPFS_HcRhDescriptorA) No Power Switching (read/write) */
#define UHPFS_HcRhDescriptorA_DT (0x1u << 10) /**< \brief (UHPFS_HcRhDescriptorA) Device Type (read-only) */
#define UHPFS_HcRhDescriptorA_OCPM (0x1u << 11) /**< \brief (UHPFS_HcRhDescriptorA) Overcurrent Protection Mode (read/write) */
#define UHPFS_HcRhDescriptorA_NOCP (0x1u << 12) /**< \brief (UHPFS_HcRhDescriptorA) No Overcurrent Protection (read/write) */
#define UHPFS_HcRhDescriptorA_POTPG_Pos 24
#define UHPFS_HcRhDescriptorA_POTPG_Msk (0xffu << UHPFS_HcRhDescriptorA_POTPG_Pos) /**< \brief (UHPFS_HcRhDescriptorA) Power-On to Power-good Time (read/write) */
#define UHPFS_HcRhDescriptorA_POTPG(value) ((UHPFS_HcRhDescriptorA_POTPG_Msk & ((value) << UHPFS_HcRhDescriptorA_POTPG_Pos)))
/* -------- UHPFS_HcRhDescriptorB : (UHPFS Offset: 0x4C) HC Root Hub B Register -------- */
#define UHPFS_HcRhDescriptorB_DR0 (0x1u << 0) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR1 (0x1u << 1) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable Bit for Downstream Port 1 */
#define UHPFS_HcRhDescriptorB_DR2 (0x1u << 2) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable Bit for Downstream Port 2 */
#define UHPFS_HcRhDescriptorB_DR3 (0x1u << 3) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable Bit for Downstream Port 3 */
#define UHPFS_HcRhDescriptorB_DR4 (0x1u << 4) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR5 (0x1u << 5) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR6 (0x1u << 6) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR7 (0x1u << 7) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR8 (0x1u << 8) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR9 (0x1u << 9) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR10 (0x1u << 10) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR11 (0x1u << 11) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR12 (0x1u << 12) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR13 (0x1u << 13) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR14 (0x1u << 14) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_DR15 (0x1u << 15) /**< \brief (UHPFS_HcRhDescriptorB) Device Removable */
#define UHPFS_HcRhDescriptorB_PPCM0 (0x1u << 16) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM1 (0x1u << 17) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask for Downstream Port 1 */
#define UHPFS_HcRhDescriptorB_PPCM2 (0x1u << 18) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask for Downstream Port 2 */
#define UHPFS_HcRhDescriptorB_PPCM3 (0x1u << 19) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask for Downstream Port 3 */
#define UHPFS_HcRhDescriptorB_PPCM4 (0x1u << 20) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM5 (0x1u << 21) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM6 (0x1u << 22) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM7 (0x1u << 23) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM8 (0x1u << 24) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM9 (0x1u << 25) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM10 (0x1u << 26) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM11 (0x1u << 27) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM12 (0x1u << 28) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM13 (0x1u << 29) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM14 (0x1u << 30) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
#define UHPFS_HcRhDescriptorB_PPCM15 (0x1u << 31) /**< \brief (UHPFS_HcRhDescriptorB) Port Power Control Mask */
/* -------- UHPFS_HcRhStatus : (UHPFS Offset: 0x50) HC Root Hub Status Register -------- */
#define UHPFS_HcRhStatus_LPS (0x1u << 0) /**< \brief (UHPFS_HcRhStatus) Local Power Status (read/write) */
#define UHPFS_HcRhStatus_OCI (0x1u << 1) /**< \brief (UHPFS_HcRhStatus) Overcurrent Indicator (read-only) */
#define UHPFS_HcRhStatus_DRWE (0x1u << 15) /**< \brief (UHPFS_HcRhStatus) Device Remote Wakeup Enable (read/write) */
#define UHPFS_HcRhStatus_LPSC (0x1u << 16) /**< \brief (UHPFS_HcRhStatus) Local Power Status Change (read/write) */
#define UHPFS_HcRhStatus_OCIC (0x1u << 17) /**< \brief (UHPFS_HcRhStatus) Overcurrent Indication Change (read/write) */
#define UHPFS_HcRhStatus_CRWE (0x1u << 31) /**< \brief (UHPFS_HcRhStatus) Clear Remote Wakeup Enable (read/write) */
/* -------- UHPFS_HcRhPortStatus[3] : (UHPFS Offset: 0x54) HC Port Status and Control Register (ndp = 0) -------- */
#define UHPFS_HcRhPortStatus_CCS (0x1u << 0) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Current Connection Status/clear Port Enable (read/write) */
#define UHPFS_HcRhPortStatus_CPE (0x1u << 0) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Current Connection Status/clear Port Enable (read/write) */
#define UHPFS_HcRhPortStatus_PES (0x1u << 1) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Enable Status/set Port Enable (read/write) */
#define UHPFS_HcRhPortStatus_SPE (0x1u << 1) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Enable Status/set Port Enable (read/write) */
#define UHPFS_HcRhPortStatus_PSS (0x1u << 2) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Suspend Status/set Port Suspend (read/write) */
#define UHPFS_HcRhPortStatus_SPS (0x1u << 2) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Suspend Status/set Port Suspend (read/write) */
#define UHPFS_HcRhPortStatus_POCI (0x1u << 3) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Overcurrent Indicator/clear Suspend Status (read/write) */
#define UHPFS_HcRhPortStatus_CSS (0x1u << 3) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Overcurrent Indicator/clear Suspend Status (read/write) */
#define UHPFS_HcRhPortStatus_PRS (0x1u << 4) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Reset Status/set Port Reset (read/write) */
#define UHPFS_HcRhPortStatus_SPR (0x1u << 4) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Reset Status/set Port Reset (read/write) */
#define UHPFS_HcRhPortStatus_PPS (0x1u << 8) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Power Status/set Port Power (read/write) */
#define UHPFS_HcRhPortStatus_SPP (0x1u << 8) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Power Status/set Port Power (read/write) */
#define UHPFS_HcRhPortStatus_LSDA (0x1u << 9) /**< \brief (UHPFS_HcRhPortStatus[3]) Low-speed Device Attached/clear Port Power (read/write) */
#define UHPFS_HcRhPortStatus_CPP (0x1u << 9) /**< \brief (UHPFS_HcRhPortStatus[3]) Low-speed Device Attached/clear Port Power (read/write) */
#define UHPFS_HcRhPortStatus_CSC (0x1u << 16) /**< \brief (UHPFS_HcRhPortStatus[3]) Connect Status Change (read/write, write '1' to clear) */
#define UHPFS_HcRhPortStatus_PESC (0x1u << 17) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Enable Status Change (read/write, write '1' to clear) */
#define UHPFS_HcRhPortStatus_PSSC (0x1u << 18) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Suspend Status Change (read/write, write '1' to clear) */
#define UHPFS_HcRhPortStatus_OCIC (0x1u << 19) /**< \brief (UHPFS_HcRhPortStatus[3]) Overcurrent Indicator Change (read/write) */
#define UHPFS_HcRhPortStatus_PRSC (0x1u << 20) /**< \brief (UHPFS_HcRhPortStatus[3]) Port Reset Status Change (read/write, write '1' to clear) */

/*@}*/


#endif /* _SAM9X_UHPFS_COMPONENT_ */
