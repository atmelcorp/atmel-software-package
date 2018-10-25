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

#ifndef _SAM9X_SFR_COMPONENT_
#define _SAM9X_SFR_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Special Function Registers */
/* ============================================================================= */
/** \addtogroup SAM9X_SFR Special Function Registers */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief Sfr hardware registers */
typedef struct {
  __I  uint32_t Reserved1[1];
  __IO uint32_t SFR_CCFG_EBICSA;     /**< \brief (Sfr Offset: 0x04) EBI Chip Select Register */
  __I  uint32_t Reserved2[2];
  __IO uint32_t SFR_OHCIICR;         /**< \brief (Sfr Offset: 0x10) OHCI Interrupt Configuration Register */
  __I  uint32_t SFR_OHCIISR;         /**< \brief (Sfr Offset: 0x14) OHCI Interrupt Status Register */
  __IO uint32_t SFR_BU_OTPC_CONF_R0; /**< \brief (Sfr Offset: 0x18) OTPC Configuration 0 Register (BackUp) */
  __IO uint32_t SFR_BU_OTPC_CONF_R1; /**< \brief (Sfr Offset: 0x1C) OTPC Configuration 1 Register (BackUp) */
  __IO uint32_t SFR_BU_RC_XTAL_TRIM; /**< \brief (Sfr Offset: 0x20) RC and XTAL Oscillator Trimming Register (BackUp) */
  __I  uint32_t Reserved3[3];
  __IO uint32_t SFR_UTMICKTRIM;      /**< \brief (Sfr Offset: 0x30) UTMI Clock Trimming Register */
  __IO uint32_t SFR_UTMIHSTRIM;      /**< \brief (Sfr Offset: 0x34) UTMI High-Speed Trimming Register */
  __IO uint32_t SFR_UTMIFSTRIM;      /**< \brief (Sfr Offset: 0x38) UTMI Full-Speed Trimming Register */
  __IO uint32_t SFR_UTMISWAP;        /**< \brief (Sfr Offset: 0x3C) UTMI DP/DM Pin Swapping Register */
  __I  uint32_t Reserved4[7];
  __IO uint32_t SFR_RM0;             /**< \brief (Sfr Offset: 0x5C) Read Margin0 Register */
  __IO uint32_t SFR_RM1;             /**< \brief (Sfr Offset: 0x60) Read Margin1 Register */
  __IO uint32_t SFR_RM2;             /**< \brief (Sfr Offset: 0x64) Read Margin2 Register */
  __IO uint32_t SFR_RM3;             /**< \brief (Sfr Offset: 0x68) Read Margin3 Register */
  __IO uint32_t SFR_RM4;             /**< \brief (Sfr Offset: 0x6C) Read Margin4 Register */
  __IO uint32_t SFR_RM5;             /**< \brief (Sfr Offset: 0x70) Read Margin5 Register */
  __I  uint32_t Reserved5[2];
  __IO uint32_t SFR_LS;              /**< \brief (Sfr Offset: 0x7C) Light Sleep Register */
  __I  uint32_t Reserved6[12];
  __IO uint32_t SFR_CAL0;            /**< \brief (Sfr Offset: 0xB0) I/O Calibration 0 Register */
  __IO uint32_t SFR_CAL1;            /**< \brief (Sfr Offset: 0xB4) I/O Calibration 1 Register */
  __I  uint32_t Reserved7[11];
  __IO uint32_t SFR_WPMR;            /**< \brief (Sfr Offset: 0xE4) Write Protection Mode Register */
  __I  uint32_t Reserved8[6];
  __IO uint32_t SFR_SPARE;           /**< \brief (Sfr Offset: 0x100) Spare Register */
  __IO uint32_t SFR_BU_SPARE;        /**< \brief (Sfr Offset: 0x104) Spare Register (BackUp) */
} Sfr;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SFR_CCFG_EBICSA : (SFR Offset: 0x04) EBI Chip Select Register -------- */
#define SFR_CCFG_EBICSA_EBI_CS1A (0x1u << 1) /**< \brief (SFR_CCFG_EBICSA) EBI Chip Select 1 Assignment */
#define SFR_CCFG_EBICSA_EBI_CS3A (0x1u << 3) /**< \brief (SFR_CCFG_EBICSA) EBI Chip Select 3 Assignment */
#define SFR_CCFG_EBICSA_EBI_CS4A (0x1u << 4) /**< \brief (SFR_CCFG_EBICSA) EBI Chip Select 4 Assignment */
#define SFR_CCFG_EBICSA_EBI_CS5A (0x1u << 5) /**< \brief (SFR_CCFG_EBICSA) EBI Chip Select 5 Assignment */
#define SFR_CCFG_EBICSA_EBI_DBPUC (0x1u << 8) /**< \brief (SFR_CCFG_EBICSA) EBI Data Bus Pullup Configuration */
#define SFR_CCFG_EBICSA_EBI_DBPDC (0x1u << 9) /**< \brief (SFR_CCFG_EBICSA) EBI Data Bus Pulldown Configuration */
#define SFR_CCFG_EBICSA_EBI_DRIVE (0x1u << 16) /**< \brief (SFR_CCFG_EBICSA) EBI I/O Drive Configuration */
#define SFR_CCFG_EBICSA_DQIEN_F (0x1u << 20) /**< \brief (SFR_CCFG_EBICSA) Force Analog Input Comparator Configuration */
#define SFR_CCFG_EBICSA_NFD0_ON_D16 (0x1u << 24) /**< \brief (SFR_CCFG_EBICSA) NAND Flash Databus Selection */
#define SFR_CCFG_EBICSA_DDR_MP_EN (0x1u << 25) /**< \brief (SFR_CCFG_EBICSA) DDR Multi-port Enable */
/* -------- SFR_OHCIICR : (SFR Offset: 0x10) OHCI Interrupt Configuration Register -------- */
#define SFR_OHCIICR_RES0 (0x1u << 0) /**< \brief (SFR_OHCIICR) USB PORTx Reset */
#define SFR_OHCIICR_RES1 (0x1u << 1) /**< \brief (SFR_OHCIICR) USB PORTx Reset */
#define SFR_OHCIICR_RES2 (0x1u << 2) /**< \brief (SFR_OHCIICR) USB PORTx Reset */
#define SFR_OHCIICR_ARIE (0x1u << 4) /**< \brief (SFR_OHCIICR) OHCI Asynchronous Resume Interrupt Enable */
#define SFR_OHCIICR_APPSTART (0x1u << 5) /**< \brief (SFR_OHCIICR) OHCI Clock Start */
#define SFR_OHCIICR_SUSP0 (0x1u << 8) /**< \brief (SFR_OHCIICR) USB PORTx */
#define SFR_OHCIICR_SUSP1 (0x1u << 9) /**< \brief (SFR_OHCIICR) USB PORTx */
#define SFR_OHCIICR_SUSP2 (0x1u << 10) /**< \brief (SFR_OHCIICR) USB PORTx */
#define SFR_OHCIICR_UDPPUDIS (0x1u << 23) /**< \brief (SFR_OHCIICR) USB Device Pullup Disable */
/* -------- SFR_OHCIISR : (SFR Offset: 0x14) OHCI Interrupt Status Register -------- */
#define SFR_OHCIISR_RIS0 (0x1u << 0) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 0 */
#define SFR_OHCIISR_RIS1 (0x1u << 1) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 1 */
#define SFR_OHCIISR_RIS2 (0x1u << 2) /**< \brief (SFR_OHCIISR) OHCI Resume Interrupt Status Port 2 */
/* -------- SFR_BU_OTPC_CONF_R0 : (SFR Offset: 0x18) OTPC Configuration 0 Register (BackUp) -------- */
#define SFR_BU_OTPC_CONF_R0_ROM_READ (0x1u << 0) /**< \brief (SFR_BU_OTPC_CONF_R0) Reading of ROM (OTP part only) */
#define   SFR_BU_OTPC_CONF_R0_ROM_READ_ENABLE (0x0u << 0) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables reading of the ROM (OTP part only). */
#define   SFR_BU_OTPC_CONF_R0_ROM_READ_DISABLE (0x1u << 0) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables reading of the ROM (OTP part only). */
#define SFR_BU_OTPC_CONF_R0_ROM_PROGRAM (0x1u << 1) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of ROM (OTP part only) */
#define   SFR_BU_OTPC_CONF_R0_ROM_PROGRAM_ENABLE (0x0u << 1) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the ROM (OTP part only). */
#define   SFR_BU_OTPC_CONF_R0_ROM_PROGRAM_DISABLE (0x1u << 1) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the ROM (OTP part only). */
#define SFR_BU_OTPC_CONF_R0_PU_READ (0x1u << 2) /**< \brief (SFR_BU_OTPC_CONF_R0) Reading of Patch Unit */
#define   SFR_BU_OTPC_CONF_R0_PU_READ_ENABLE (0x0u << 2) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables reading of the patch unit. */
#define   SFR_BU_OTPC_CONF_R0_PU_READ_DISABLE (0x1u << 2) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables reading of the patch unit. */
#define SFR_BU_OTPC_CONF_R0_PU_PROGRAM (0x1u << 3) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of Patch Unit */
#define   SFR_BU_OTPC_CONF_R0_PU_PROGRAM_ENABLE (0x0u << 3) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the patch unit. */
#define   SFR_BU_OTPC_CONF_R0_PU_PROGRAM_DISABLE (0x1u << 3) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the patch unit. */
#define SFR_BU_OTPC_CONF_R0_ENGI_READ (0x1u << 4) /**< \brief (SFR_BU_OTPC_CONF_R0) Reading of Engineering Area */
#define   SFR_BU_OTPC_CONF_R0_ENGI_READ_ENABLE (0x0u << 4) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables reading of the engineering area. */
#define   SFR_BU_OTPC_CONF_R0_ENGI_READ_DISABLE (0x1u << 4) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables reading of the engineering area. */
#define SFR_BU_OTPC_CONF_R0_ENGI_PROGRAM (0x1u << 5) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of Engineering Area */
#define   SFR_BU_OTPC_CONF_R0_ENGI_PROGRAM_ENABLE (0x0u << 5) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the engineering area. */
#define   SFR_BU_OTPC_CONF_R0_ENGI_PROGRAM_DISABLE (0x1u << 5) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the engineering area. */
#define SFR_BU_OTPC_CONF_R0_USER_READ (0x1u << 6) /**< \brief (SFR_BU_OTPC_CONF_R0) Reading of User Area */
#define   SFR_BU_OTPC_CONF_R0_USER_READ_ENABLE (0x0u << 6) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables reading of the user area. */
#define   SFR_BU_OTPC_CONF_R0_USER_READ_DISABLE (0x1u << 6) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables reading of the user area. */
#define SFR_BU_OTPC_CONF_R0_USER_PROGRAM (0x1u << 7) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of User Area */
#define   SFR_BU_OTPC_CONF_R0_USER_PROGRAM_ENABLE (0x0u << 7) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the user area. */
#define   SFR_BU_OTPC_CONF_R0_USER_PROGRAM_DISABLE (0x1u << 7) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the user area. */
#define SFR_BU_OTPC_CONF_R0_PUID_INVALIDATE (0x1u << 8) /**< \brief (SFR_BU_OTPC_CONF_R0) Invalidation of Product UID Special Packet */
#define   SFR_BU_OTPC_CONF_R0_PUID_INVALIDATE_ENABLE (0x0u << 8) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables invalidation of the Product UID special packet. */
#define   SFR_BU_OTPC_CONF_R0_PUID_INVALIDATE_DISABLE (0x1u << 8) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables invalidation of the Product UID special packet. */
#define SFR_BU_OTPC_CONF_R0_PUID_LOCK (0x1u << 9) /**< \brief (SFR_BU_OTPC_CONF_R0) Lock of Product UID Special Packet */
#define   SFR_BU_OTPC_CONF_R0_PUID_LOCK_ENABLE (0x0u << 9) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables lock of the Product UID special packet. */
#define   SFR_BU_OTPC_CONF_R0_PUID_LOCK_DISABLE (0x1u << 9) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables lock of the Product UID special packet. */
#define SFR_BU_OTPC_CONF_R0_PUID_PARSE (0x1u << 10) /**< \brief (SFR_BU_OTPC_CONF_R0) Parsing of Product UID Special Packet */
#define   SFR_BU_OTPC_CONF_R0_PUID_PARSE_ENABLE (0x0u << 10) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables parsing of the Product UID special packet. */
#define   SFR_BU_OTPC_CONF_R0_PUID_PARSE_DISABLE (0x1u << 10) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables parsing of the Product UID special packet. */
#define SFR_BU_OTPC_CONF_R0_PUID_PROGRAM (0x1u << 11) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of Product UID Special Packet */
#define   SFR_BU_OTPC_CONF_R0_PUID_PROGRAM_ENABLE (0x0u << 11) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the Product UID special packet. */
#define   SFR_BU_OTPC_CONF_R0_PUID_PROGRAM_DISABLE (0x1u << 11) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the Product UID special packet. */
#define SFR_BU_OTPC_CONF_R0_EHC_INVALIDATE (0x1u << 12) /**< \brief (SFR_BU_OTPC_CONF_R0) Invalidation of Engineering Hardware Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_EHC_INVALIDATE_ENABLE (0x0u << 12) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables invalidation of the Engineering Hardware Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_EHC_INVALIDATE_DISABLE (0x1u << 12) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables invalidation of the Engineering Hardware Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_EHC_LOCK (0x1u << 13) /**< \brief (SFR_BU_OTPC_CONF_R0) Lock of Engineering Hardware Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_EHC_LOCK_ENABLE (0x0u << 13) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables lock of the Engineering Hardware Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_EHC_LOCK_DISABLE (0x1u << 13) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables lock of the Engineering Hardware Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_EHC_PARSE (0x1u << 14) /**< \brief (SFR_BU_OTPC_CONF_R0) Parsing of Engineering Hardware Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_EHC_PARSE_ENABLE (0x0u << 14) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables parsing of the Engineering Hardware Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_EHC_PARSE_DISABLE (0x1u << 14) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables parsing of the Engineering Hardware Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_EHC_PROGRAM (0x1u << 15) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of Engineering Hardware Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_EHC_PROGRAM_ENABLE (0x0u << 15) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the Engineering Hardware Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_EHC_PROGRAM_DISABLE (0x1u << 15) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the Engineering Hardware Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_ESC_INVALIDATE (0x1u << 16) /**< \brief (SFR_BU_OTPC_CONF_R0) Invalidation of Engineering Security Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_ESC_INVALIDATE_ENABLE (0x0u << 16) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables invalidation of the Engineering Security Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_ESC_INVALIDATE_DISABLE (0x1u << 16) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables invalidation of the Engineering Security Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_ESC_LOCK (0x1u << 17) /**< \brief (SFR_BU_OTPC_CONF_R0) Lock of Engineering Security Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_ESC_LOCK_ENABLE (0x0u << 17) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables lock of the Engineering Security Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_ESC_LOCK_DISABLE (0x1u << 17) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables lock of the Engineering Security Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_ESC_PARSE (0x1u << 18) /**< \brief (SFR_BU_OTPC_CONF_R0) Parsing of Engineering Security Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_ESC_PARSE_ENABLE (0x0u << 18) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables parsing of the Engineering Security Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_ESC_PARSE_DISABLE (0x1u << 18) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables parsing of the Engineering Security Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_ESC_PROGRAM (0x1u << 19) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of Engineering Security Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_ESC_PROGRAM_ENABLE (0x0u << 19) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the Engineering Security Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_ESC_PROGRAM_DISABLE (0x1u << 19) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the Engineering Security Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_UHC_INVALIDATE (0x1u << 20) /**< \brief (SFR_BU_OTPC_CONF_R0) Invalidation of User Hardware Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_UHC_INVALIDATE_ENABLE (0x0u << 20) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables invalidation of the User Hardware Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_UHC_INVALIDATE_DISABLE (0x1u << 20) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables invalidation of the User Hardware Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_UHC_LOCK (0x1u << 21) /**< \brief (SFR_BU_OTPC_CONF_R0) Lock of User Hardware Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_UHC_LOCK_ENABLE (0x0u << 21) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables lock of the User Hardware Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_UHC_LOCK_DISABLE (0x1u << 21) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables lock of the User Hardware Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_UHC_PARSE (0x1u << 22) /**< \brief (SFR_BU_OTPC_CONF_R0) Parsing of User Hardware Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_UHC_PARSE_ENABLE (0x0u << 22) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables parsing of the User Hardware Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_UHC_PARSE_DISABLE (0x1u << 22) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables parsing of the User Hardware Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_UHC_PROGRAM (0x1u << 23) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of User Hardware Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_UHC_PROGRAM_ENABLE (0x0u << 23) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the User Hardware Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_UHC_PROGRAM_DISABLE (0x1u << 23) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the User Hardware Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_BC_INVALIDATE (0x1u << 24) /**< \brief (SFR_BU_OTPC_CONF_R0) Invalidation of User Boot Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_BC_INVALIDATE_ENABLE (0x0u << 24) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables invalidation of the User Boot Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_BC_INVALIDATE_DISABLE (0x1u << 24) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables invalidation of the User Boot Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_BC_LOCK (0x1u << 25) /**< \brief (SFR_BU_OTPC_CONF_R0) Lock of User Boot Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_BC_LOCK_ENABLE (0x0u << 25) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables lock of the User Boot Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_BC_LOCK_DISABLE (0x1u << 25) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables lock of the User Boot Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_BC_PARSE (0x1u << 26) /**< \brief (SFR_BU_OTPC_CONF_R0) Parsing of User Boot Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_BC_PARSE_ENABLE (0x0u << 26) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables parsing of the User Boot Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_BC_PARSE_DISABLE (0x1u << 26) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables parsing of the User Boot Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_BC_PROGRAM (0x1u << 27) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of User Boot Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_BC_PROGRAM_ENABLE (0x0u << 27) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the User Boot Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_BC_PROGRAM_DISABLE (0x1u << 27) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the User Boot Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_SBD_INVALIDATE (0x1u << 28) /**< \brief (SFR_BU_OTPC_CONF_R0) Invalidation of User Secure Boot Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_SBD_INVALIDATE_ENABLE (0x0u << 28) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables invalidation of the User Secure Boot Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_SBD_INVALIDATE_DISABLE (0x1u << 28) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables invalidation of the User Secure Boot Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_SBD_LOCK (0x1u << 29) /**< \brief (SFR_BU_OTPC_CONF_R0) Lock of User Secure Boot Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_SBD_LOCK_ENABLE (0x0u << 29) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables lock of the User Secure Boot Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_SBD_LOCK_DISABLE (0x1u << 29) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables lock of the User Secure Boot Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_SBD_PARSE (0x1u << 30) /**< \brief (SFR_BU_OTPC_CONF_R0) Parsing of User Secure Boot Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_SBD_PARSE_ENABLE (0x0u << 30) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables parsing of the User Secure Boot Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_SBD_PARSE_DISABLE (0x1u << 30) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables parsing of the User Secure Boot Configuration special packet. */
#define SFR_BU_OTPC_CONF_R0_SBD_PROGRAM (0x1u << 31) /**< \brief (SFR_BU_OTPC_CONF_R0) Programming of User Secure Boot Configuration Special Packet */
#define   SFR_BU_OTPC_CONF_R0_SBD_PROGRAM_ENABLE (0x0u << 31) /**< \brief (SFR_BU_OTPC_CONF_R0) Enables programming of the User Secure Boot Configuration special packet. */
#define   SFR_BU_OTPC_CONF_R0_SBD_PROGRAM_DISABLE (0x1u << 31) /**< \brief (SFR_BU_OTPC_CONF_R0) Disables programming of the User Secure Boot Configuration special packet. */
/* -------- SFR_BU_OTPC_CONF_R1 : (SFR Offset: 0x1C) OTPC Configuration 1 Register (BackUp) -------- */
#define SFR_BU_OTPC_CONF_R1_SC_INVALIDATE (0x1u << 0) /**< \brief (SFR_BU_OTPC_CONF_R1) Invalidation of User Custom Special Packet (Secure World) */
#define   SFR_BU_OTPC_CONF_R1_SC_INVALIDATE_ENABLE (0x0u << 0) /**< \brief (SFR_BU_OTPC_CONF_R1) Enables invalidation of the User Custom special packet (for Secure World). */
#define   SFR_BU_OTPC_CONF_R1_SC_INVALIDATE_DISABLE (0x1u << 0) /**< \brief (SFR_BU_OTPC_CONF_R1) Disables invalidation of the User Custom special packet (for Secure World). */
#define SFR_BU_OTPC_CONF_R1_SC_LOCK (0x1u << 1) /**< \brief (SFR_BU_OTPC_CONF_R1) Lock of User Custom Special Packet (Secure World) */
#define   SFR_BU_OTPC_CONF_R1_SC_LOCK_ENABLE (0x0u << 1) /**< \brief (SFR_BU_OTPC_CONF_R1) Enables lock of the User Custom special packet (for Secure World). */
#define   SFR_BU_OTPC_CONF_R1_SC_LOCK_DISABLE (0x1u << 1) /**< \brief (SFR_BU_OTPC_CONF_R1) Disables lock of the User Custom special packet (for Secure World). */
#define SFR_BU_OTPC_CONF_R1_SC_PARSE (0x1u << 2) /**< \brief (SFR_BU_OTPC_CONF_R1) Parsing of the User Custom Special Packet (Secure World) */
#define   SFR_BU_OTPC_CONF_R1_SC_PARSE_ENABLE (0x0u << 2) /**< \brief (SFR_BU_OTPC_CONF_R1) Enables parsing of the User Custom special packet (for Secure World). */
#define   SFR_BU_OTPC_CONF_R1_SC_PARSE_DISABLE (0x1u << 2) /**< \brief (SFR_BU_OTPC_CONF_R1) Disables parsing of the User Custom special packet (for Secure World). */
#define SFR_BU_OTPC_CONF_R1_SC_PROGRAM (0x1u << 3) /**< \brief (SFR_BU_OTPC_CONF_R1) Programming of User Custom Special Packet (Secure World) */
#define   SFR_BU_OTPC_CONF_R1_SC_PROGRAM_ENABLE (0x0u << 3) /**< \brief (SFR_BU_OTPC_CONF_R1) Enables programming of the User Custom special packet (for Secure World). */
#define   SFR_BU_OTPC_CONF_R1_SC_PROGRAM_DISABLE (0x1u << 3) /**< \brief (SFR_BU_OTPC_CONF_R1) Disables programming of the User Custom special packet (for Secure World). */
#define SFR_BU_OTPC_CONF_R1_C_INVALIDATE (0x1u << 4) /**< \brief (SFR_BU_OTPC_CONF_R1) Invalidation of User Custom Special Packet (Non-Secure World) */
#define   SFR_BU_OTPC_CONF_R1_C_INVALIDATE_ENABLE (0x0u << 4) /**< \brief (SFR_BU_OTPC_CONF_R1) Enables invalidation of the User Custom special packet (for Non-Secure World). */
#define   SFR_BU_OTPC_CONF_R1_C_INVALIDATE_DISABLE (0x1u << 4) /**< \brief (SFR_BU_OTPC_CONF_R1) Disables invalidation of the User Custom special packet (for Non-Secure World). */
#define SFR_BU_OTPC_CONF_R1_C_LOCK (0x1u << 5) /**< \brief (SFR_BU_OTPC_CONF_R1) Lock of User Custom Special Packet (Non-Secure World) */
#define   SFR_BU_OTPC_CONF_R1_C_LOCK_ENABLE (0x0u << 5) /**< \brief (SFR_BU_OTPC_CONF_R1) Enables lock of the User Custom special packet (for Non-Secure World). */
#define   SFR_BU_OTPC_CONF_R1_C_LOCK_DISABLE (0x1u << 5) /**< \brief (SFR_BU_OTPC_CONF_R1) Disables lock of the User Custom special packet (for Non-Secure World). */
#define SFR_BU_OTPC_CONF_R1_C_PARSE (0x1u << 6) /**< \brief (SFR_BU_OTPC_CONF_R1) Parsing of User Custom Special Packet (Non-Secure World) */
#define   SFR_BU_OTPC_CONF_R1_C_PARSE_ENABLE (0x0u << 6) /**< \brief (SFR_BU_OTPC_CONF_R1) Enables parsing of the User Custom special packet (for Non-Secure World). */
#define   SFR_BU_OTPC_CONF_R1_C_PARSE_DISABLE (0x1u << 6) /**< \brief (SFR_BU_OTPC_CONF_R1) Disables parsing of the User Custom special packet (for Non-Secure World). */
#define SFR_BU_OTPC_CONF_R1_C_PROGRAM (0x1u << 7) /**< \brief (SFR_BU_OTPC_CONF_R1) Programming of User Custom Special Packet (Non-Secure World) */
#define   SFR_BU_OTPC_CONF_R1_C_PROGRAM_ENABLE (0x0u << 7) /**< \brief (SFR_BU_OTPC_CONF_R1) Enables programming of the User Custom special packet (for Non-Secure World). */
#define   SFR_BU_OTPC_CONF_R1_C_PROGRAM_DISABLE (0x1u << 7) /**< \brief (SFR_BU_OTPC_CONF_R1) Disables programming of the User Custom special packet (for Non-Secure World). */
#define SFR_BU_OTPC_CONF_R1_ENGI_REFRESH (0x1u << 8) /**< \brief (SFR_BU_OTPC_CONF_R1) Engineering Area Refresh */
#define   SFR_BU_OTPC_CONF_R1_ENGI_REFRESH_ALLOWED (0x0u << 8) /**< \brief (SFR_BU_OTPC_CONF_R1) Allows refresh of the Engineering Area. */
#define   SFR_BU_OTPC_CONF_R1_ENGI_REFRESH_FORBIDDEN (0x1u << 8) /**< \brief (SFR_BU_OTPC_CONF_R1) Forbids refresh of the Engineering Area. */
#define SFR_BU_OTPC_CONF_R1_USER_REFRESH (0x1u << 9) /**< \brief (SFR_BU_OTPC_CONF_R1) User Area Refresh */
#define   SFR_BU_OTPC_CONF_R1_USER_REFRESH_ALLOWED (0x0u << 9) /**< \brief (SFR_BU_OTPC_CONF_R1) Allows refresh of the User Area. */
#define   SFR_BU_OTPC_CONF_R1_USER_REFRESH_FORBIDDEN (0x1u << 9) /**< \brief (SFR_BU_OTPC_CONF_R1) Forbids refresh of the User Area. */
#define SFR_BU_OTPC_CONF_R1_FROM_SFRBU_ONLY (0x1u << 24) /**< \brief (SFR_BU_OTPC_CONF_R1) OTPC Configuration Signal */
/* -------- SFR_BU_RC_XTAL_TRIM : (SFR Offset: 0x20) RC and XTAL Oscillator Trimming Register (BackUp) -------- */
#define SFR_BU_RC_XTAL_TRIM_XTAL_TRIM_Pos 0
#define SFR_BU_RC_XTAL_TRIM_XTAL_TRIM_Msk (0x3u << SFR_BU_RC_XTAL_TRIM_XTAL_TRIM_Pos) /**< \brief (SFR_BU_RC_XTAL_TRIM) 32.768 kHz Crystal Oscillator Trimming Value */
#define SFR_BU_RC_XTAL_TRIM_XTAL_TRIM(value) ((SFR_BU_RC_XTAL_TRIM_XTAL_TRIM_Msk & ((value) << SFR_BU_RC_XTAL_TRIM_XTAL_TRIM_Pos)))
#define SFR_BU_RC_XTAL_TRIM_XTAL_SEL (0x1u << 4) /**< \brief (SFR_BU_RC_XTAL_TRIM) 32.768 kHz Crystal Oscillator Trimming Select */
#define SFR_BU_RC_XTAL_TRIM_RC_TRIM_Pos 8
#define SFR_BU_RC_XTAL_TRIM_RC_TRIM_Msk (0x7fu << SFR_BU_RC_XTAL_TRIM_RC_TRIM_Pos) /**< \brief (SFR_BU_RC_XTAL_TRIM) 32 kHz RC Oscillator Trimming Value */
#define SFR_BU_RC_XTAL_TRIM_RC_TRIM(value) ((SFR_BU_RC_XTAL_TRIM_RC_TRIM_Msk & ((value) << SFR_BU_RC_XTAL_TRIM_RC_TRIM_Pos)))
#define SFR_BU_RC_XTAL_TRIM_RC_SEL (0x1u << 15) /**< \brief (SFR_BU_RC_XTAL_TRIM) 32 kHz RC Oscillator Trimming Select */
/* -------- SFR_UTMICKTRIM : (SFR Offset: 0x30) UTMI Clock Trimming Register -------- */
#define SFR_UTMICKTRIM_VBG_Pos 16
#define SFR_UTMICKTRIM_VBG_Msk (0x3u << SFR_UTMICKTRIM_VBG_Pos) /**< \brief (SFR_UTMICKTRIM) UTMI Band Gap Voltage Trimming */
#define SFR_UTMICKTRIM_VBG(value) ((SFR_UTMICKTRIM_VBG_Msk & ((value) << SFR_UTMICKTRIM_VBG_Pos)))
/* -------- SFR_UTMIHSTRIM : (SFR Offset: 0x34) UTMI High-Speed Trimming Register -------- */
#define SFR_UTMIHSTRIM_SQUELCH_Pos 0
#define SFR_UTMIHSTRIM_SQUELCH_Msk (0x7u << SFR_UTMIHSTRIM_SQUELCH_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS Squelch Voltage Trimming */
#define SFR_UTMIHSTRIM_SQUELCH(value) ((SFR_UTMIHSTRIM_SQUELCH_Msk & ((value) << SFR_UTMIHSTRIM_SQUELCH_Pos)))
#define SFR_UTMIHSTRIM_DISC_Pos 4
#define SFR_UTMIHSTRIM_DISC_Msk (0x7u << SFR_UTMIHSTRIM_DISC_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI Disconnect Voltage Trimming */
#define SFR_UTMIHSTRIM_DISC(value) ((SFR_UTMIHSTRIM_DISC_Msk & ((value) << SFR_UTMIHSTRIM_DISC_Pos)))
#define SFR_UTMIHSTRIM_SLOPE0_Pos 8
#define SFR_UTMIHSTRIM_SLOPE0_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE0_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE0(value) ((SFR_UTMIHSTRIM_SLOPE0_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE0_Pos)))
#define SFR_UTMIHSTRIM_SLOPE1_Pos 12
#define SFR_UTMIHSTRIM_SLOPE1_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE1_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE1(value) ((SFR_UTMIHSTRIM_SLOPE1_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE1_Pos)))
#define SFR_UTMIHSTRIM_SLOPE2_Pos 16
#define SFR_UTMIHSTRIM_SLOPE2_Msk (0x7u << SFR_UTMIHSTRIM_SLOPE2_Pos) /**< \brief (SFR_UTMIHSTRIM) UTMI HS PORTx Transceiver Slope Trimming */
#define SFR_UTMIHSTRIM_SLOPE2(value) ((SFR_UTMIHSTRIM_SLOPE2_Msk & ((value) << SFR_UTMIHSTRIM_SLOPE2_Pos)))
/* -------- SFR_UTMIFSTRIM : (SFR Offset: 0x38) UTMI Full-Speed Trimming Register -------- */
#define SFR_UTMIFSTRIM_RISE_Pos 0
#define SFR_UTMIFSTRIM_RISE_Msk (0x7u << SFR_UTMIFSTRIM_RISE_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver Output Rising Slope Trimming */
#define SFR_UTMIFSTRIM_RISE(value) ((SFR_UTMIFSTRIM_RISE_Msk & ((value) << SFR_UTMIFSTRIM_RISE_Pos)))
#define SFR_UTMIFSTRIM_FALL_Pos 4
#define SFR_UTMIFSTRIM_FALL_Msk (0x7u << SFR_UTMIFSTRIM_FALL_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver Output Falling Slope Trimming */
#define SFR_UTMIFSTRIM_FALL(value) ((SFR_UTMIFSTRIM_FALL_Msk & ((value) << SFR_UTMIFSTRIM_FALL_Pos)))
#define SFR_UTMIFSTRIM_XCVR_Pos 8
#define SFR_UTMIFSTRIM_XCVR_Msk (0x3u << SFR_UTMIFSTRIM_XCVR_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver Crossover Voltage Trimming */
#define SFR_UTMIFSTRIM_XCVR(value) ((SFR_UTMIFSTRIM_XCVR_Msk & ((value) << SFR_UTMIFSTRIM_XCVR_Pos)))
#define SFR_UTMIFSTRIM_ZN_Pos 16
#define SFR_UTMIFSTRIM_ZN_Msk (0x7u << SFR_UTMIFSTRIM_ZN_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver NMOS Impedance Trimming */
#define SFR_UTMIFSTRIM_ZN(value) ((SFR_UTMIFSTRIM_ZN_Msk & ((value) << SFR_UTMIFSTRIM_ZN_Pos)))
#define SFR_UTMIFSTRIM_ZP_Pos 20
#define SFR_UTMIFSTRIM_ZP_Msk (0x7u << SFR_UTMIFSTRIM_ZP_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver PMOS Impedance Trimming */
#define SFR_UTMIFSTRIM_ZP(value) ((SFR_UTMIFSTRIM_ZP_Msk & ((value) << SFR_UTMIFSTRIM_ZP_Pos)))
#define SFR_UTMIFSTRIM_ZN_CAL_Pos 24
#define SFR_UTMIFSTRIM_ZN_CAL_Msk (0x7u << SFR_UTMIFSTRIM_ZN_CAL_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver NMOS Impedance Calibration */
#define SFR_UTMIFSTRIM_ZN_CAL(value) ((SFR_UTMIFSTRIM_ZN_CAL_Msk & ((value) << SFR_UTMIFSTRIM_ZN_CAL_Pos)))
#define SFR_UTMIFSTRIM_ZP_CAL_Pos 28
#define SFR_UTMIFSTRIM_ZP_CAL_Msk (0x7u << SFR_UTMIFSTRIM_ZP_CAL_Pos) /**< \brief (SFR_UTMIFSTRIM) FS Transceiver PMOS Impedance Calibration */
#define SFR_UTMIFSTRIM_ZP_CAL(value) ((SFR_UTMIFSTRIM_ZP_CAL_Msk & ((value) << SFR_UTMIFSTRIM_ZP_CAL_Pos)))
/* -------- SFR_UTMISWAP : (SFR Offset: 0x3C) UTMI DP/DM Pin Swapping Register -------- */
#define SFR_UTMISWAP_PORT0 (0x1u << 0) /**< \brief (SFR_UTMISWAP) PORT 0 DP/DM Pin Swapping */
#define   SFR_UTMISWAP_PORT0_NORMAL (0x0u << 0) /**< \brief (SFR_UTMISWAP) DP/DM normal pinout. */
#define   SFR_UTMISWAP_PORT0_SWAPPED (0x1u << 0) /**< \brief (SFR_UTMISWAP) DP/DM swapped pinout. */
#define SFR_UTMISWAP_PORT1 (0x1u << 1) /**< \brief (SFR_UTMISWAP) PORT 1 DP/DM Pin Swapping */
#define   SFR_UTMISWAP_PORT1_NORMAL (0x0u << 1) /**< \brief (SFR_UTMISWAP) DP/DM normal pinout. */
#define   SFR_UTMISWAP_PORT1_SWAPPED (0x1u << 1) /**< \brief (SFR_UTMISWAP) DP/DM swapped pinout. */
#define SFR_UTMISWAP_PORT2 (0x1u << 2) /**< \brief (SFR_UTMISWAP) PORT 2 DP/DM Pin Swapping */
#define   SFR_UTMISWAP_PORT2_NORMAL (0x0u << 2) /**< \brief (SFR_UTMISWAP) DP/DM normal pinout. */
#define   SFR_UTMISWAP_PORT2_SWAPPED (0x1u << 2) /**< \brief (SFR_UTMISWAP) DP/DM swapped pinout. */
/* -------- SFR_RM0 : (SFR Offset: 0x5C) Read Margin0 Register -------- */
#define SFR_RM0_RM00_Pos 0
#define SFR_RM0_RM00_Msk (0xfu << SFR_RM0_RM00_Pos) /**< \brief (SFR_RM0) READ_MARGIN Value: i_bank0_msb_rf2p, i_bank0_lsb_rf2p, i_bank1_msb_rf2p, i_bank1_lsb_rf2p - 512 bytes (rf2p) - gfx2d_bank_rf2p_dc_32x32sw1 (GFX2D) */
#define SFR_RM0_RM00(value) ((SFR_RM0_RM00_Msk & ((value) << SFR_RM0_RM00_Pos)))
#define SFR_RM0_RM01_Pos 4
#define SFR_RM0_RM01_Msk (0xfu << SFR_RM0_RM01_Pos) /**< \brief (SFR_RM0) WRITE_MARGIN Value: i_bank0_msb_rf2p, i_bank0_lsb_rf2p, i_bank1_msb_rf2p, i_bank1_lsb_rf2p - 512 bytes (rf2p) - gfx2d_bank_rf2p_dc_32x32sw1 (GFX2D) */
#define SFR_RM0_RM01(value) ((SFR_RM0_RM01_Msk & ((value) << SFR_RM0_RM01_Pos)))
#define SFR_RM0_RM02_Pos 8
#define SFR_RM0_RM02_Msk (0xfu << SFR_RM0_RM02_Pos) /**< \brief (SFR_RM0) READ_MARGIN Value: i_clut_rf1p - 2 Kbytes (rf1p) - gfx2d_clut_rf_sc_512x32 (GFX2D) */
#define SFR_RM0_RM02(value) ((SFR_RM0_RM02_Msk & ((value) << SFR_RM0_RM02_Pos)))
#define SFR_RM0_RM03_Pos 12
#define SFR_RM0_RM03_Msk (0xfu << SFR_RM0_RM03_Pos) /**< \brief (SFR_RM0) READ_MARGIN Value: i_queue_rf2p - 68 bytes (rf2p) - gfx2d_queue_rf2p_dc_8x68 (GFX2D) */
#define SFR_RM0_RM03(value) ((SFR_RM0_RM03_Msk & ((value) << SFR_RM0_RM03_Pos)))
#define SFR_RM0_RM04_Pos 16
#define SFR_RM0_RM04_Msk (0xfu << SFR_RM0_RM04_Pos) /**< \brief (SFR_RM0) WRITE_MARGIN Value: i_queue_rf2p - 68 bytes (rf2p) - gfx2d_queue_rf2p_dc_8x68 (GFX2D) */
#define SFR_RM0_RM04(value) ((SFR_RM0_RM04_Msk & ((value) << SFR_RM0_RM04_Pos)))
/* -------- SFR_RM1 : (SFR Offset: 0x60) Read Margin1 Register -------- */
#define SFR_RM1_RM10_Pos 0
#define SFR_RM1_RM10_Msk (0xfu << SFR_RM1_RM10_Pos) /**< \brief (SFR_RM1) READ_MARGIN Value: i_lcd_base_clut, i_lcd_heo_clut - 2 Kbytes (rf1p) - hlcdc_clut_rf_sc_256x32sw1 (HLCDC5) */
#define SFR_RM1_RM10(value) ((SFR_RM1_RM10_Msk & ((value) << SFR_RM1_RM10_Pos)))
#define SFR_RM1_RM11_Pos 4
#define SFR_RM1_RM11_Msk (0xfu << SFR_RM1_RM11_Pos) /**< \brief (SFR_RM1) READ_MARGIN Value: i_lcd_base_fifo, i_lcd_ovr1_rf2p, i_lcd_ovr2_rf2p, i_lcd_heo_fifo, i_lcd_heop1_fifo, i_lcd_heop2_fifo - 816 bytes (rf2p) - hlcdc_fifo_rf2p_dc_32x34 (HLCDC5) */
#define SFR_RM1_RM11(value) ((SFR_RM1_RM11_Msk & ((value) << SFR_RM1_RM11_Pos)))
#define SFR_RM1_RM12_Pos 8
#define SFR_RM1_RM12_Msk (0xfu << SFR_RM1_RM12_Pos) /**< \brief (SFR_RM1) WRITE_MARGIN Value: i_lcd_base_fifo, i_lcd_ovr1_rf2p, i_lcd_ovr2_rf2p, i_lcd_heo_fifo, i_lcd_heop1_fifo, i_lcd_heop2_fifo - 816 bytes (rf2p) - hlcdc_fifo_rf2p_dc_32x34 (HLCDC5) */
#define SFR_RM1_RM12(value) ((SFR_RM1_RM12_Msk & ((value) << SFR_RM1_RM12_Pos)))
#define SFR_RM1_RM13_Pos 12
#define SFR_RM1_RM13_Msk (0xfu << SFR_RM1_RM13_Pos) /**< \brief (SFR_RM1) READ_MARGIN Value: i_lcd_output_fifo - 1.5 Kbytes (rf2p) - hlcdc_fifo_rf2p_dc_512x24 (HLCDC5) */
#define SFR_RM1_RM13(value) ((SFR_RM1_RM13_Msk & ((value) << SFR_RM1_RM13_Pos)))
#define SFR_RM1_RM14_Pos 16
#define SFR_RM1_RM14_Msk (0xfu << SFR_RM1_RM14_Pos) /**< \brief (SFR_RM1) WRITE_MARGIN Value: i_lcd_output_fifo - 1.5 Kbytes (rf2p) - hlcdc_fifo_rf2p_dc_512x24 (HLCDC5) */
#define SFR_RM1_RM14(value) ((SFR_RM1_RM14_Msk & ((value) << SFR_RM1_RM14_Pos)))
#define SFR_RM1_RM15_Pos 20
#define SFR_RM1_RM15_Msk (0xfu << SFR_RM1_RM15_Pos) /**< \brief (SFR_RM1) READ_MARGIN Value: i_lcd_heo_scaler0, i_lcd_heo_scaler1, i_lcd_heo_scaler2 - 3 Kbytes (sram) hlcdc_heoscaler_sram_1024x24sw1 (HLCDC5) */
#define SFR_RM1_RM15(value) ((SFR_RM1_RM15_Msk & ((value) << SFR_RM1_RM15_Pos)))
#define SFR_RM1_RM16_Pos 24
#define SFR_RM1_RM16_Msk (0xfu << SFR_RM1_RM16_Pos) /**< \brief (SFR_RM1) READ_MARGIN Value: i_lcd_ovr1_sram, i_lcd_ovr2_sram - 2 Kbytes (sram) hlcdc_ovr_sram_256x32sw1 (HLCDC5) */
#define SFR_RM1_RM16(value) ((SFR_RM1_RM16_Msk & ((value) << SFR_RM1_RM16_Pos)))
#define SFR_RM1_RM17_Pos 28
#define SFR_RM1_RM17_Msk (0xfu << SFR_RM1_RM17_Pos) /**< \brief (SFR_RM1) READ_MARGIN Value: i_lcd_heo_cue0, i_lcd_heo_cue1 - 2 Kbytes (rf1p) - hlcdc_heocue_rf_sc_512x16sw1 (HLCDC5) */
#define SFR_RM1_RM17(value) ((SFR_RM1_RM17_Msk & ((value) << SFR_RM1_RM17_Pos)))
/* -------- SFR_RM2 : (SFR Offset: 0x64) Read Margin2 Register -------- */
#define SFR_RM2_RM20_Pos 0
#define SFR_RM2_RM20_Msk (0xfu << SFR_RM2_RM20_Pos) /**< \brief (SFR_RM2) READ-WRITE_MARGIN Value Port A: SDMMC0.i_dpram, SDMMC1.i_dpram - 2 Kbytes (dpsram) sdmmc_dpram_256x32sw1 (SDMMC) */
#define SFR_RM2_RM20(value) ((SFR_RM2_RM20_Msk & ((value) << SFR_RM2_RM20_Pos)))
#define SFR_RM2_RM21_Pos 4
#define SFR_RM2_RM21_Msk (0xfu << SFR_RM2_RM21_Pos) /**< \brief (SFR_RM2) READ-WRITE_MARGIN Value Port B SDMMC0.i_dpram, SDMMC1.i_dpram - 2 Kbytes (dpsram) sdmmc_dpram_256x32sw1 (SDMMC) */
#define SFR_RM2_RM21(value) ((SFR_RM2_RM21_Msk & ((value) << SFR_RM2_RM21_Pos)))
#define SFR_RM2_RM22_Pos 8
#define SFR_RM2_RM22_Msk (0xfu << SFR_RM2_RM22_Pos) /**< \brief (SFR_RM2) READ-WRITE_MARGIN Value Port A: i_husb2dev_dpram_4112x32 - 16.5 Kbytes (dpsram) husb2dev_dpram_4224x32sw1 (HUSB) */
#define SFR_RM2_RM22(value) ((SFR_RM2_RM22_Msk & ((value) << SFR_RM2_RM22_Pos)))
#define SFR_RM2_RM23_Pos 12
#define SFR_RM2_RM23_Msk (0xfu << SFR_RM2_RM23_Pos) /**< \brief (SFR_RM2) READ-WRITE_MARGIN Value Port B: i_husb2dev_dpram_4112x32 - 16.5 Kbytes (dpsram) husb2dev_dpram_4224x32sw1 (HUSB) */
#define SFR_RM2_RM23(value) ((SFR_RM2_RM23_Msk & ((value) << SFR_RM2_RM23_Pos)))
/* -------- SFR_RM3 : (SFR Offset: 0x68) Read Margin3 Register -------- */
#define SFR_RM3_RM30_Pos 0
#define SFR_RM3_RM30_Msk (0xfu << SFR_RM3_RM30_Pos) /**< \brief (SFR_RM3) READ-WRITE_MARGIN Value Port A: i_dpram_1056x32 - 4.125 Kbytes (dpsram) hxdma_dpram_1056x32sw1 (HXDMA) */
#define SFR_RM3_RM30(value) ((SFR_RM3_RM30_Msk & ((value) << SFR_RM3_RM30_Pos)))
#define SFR_RM3_RM31_Pos 4
#define SFR_RM3_RM31_Msk (0xfu << SFR_RM3_RM31_Pos) /**< \brief (SFR_RM3) READ-WRITE_MARGIN Value Port B: i_dpram_1056x32 - 4.125 Kbytes (dpsram) hxdma_dpram_1056x32sw1 (HXDMA) */
#define SFR_RM3_RM31(value) ((SFR_RM3_RM31_Msk & ((value) << SFR_RM3_RM31_Pos)))
#define SFR_RM3_RM32_Pos 8
#define SFR_RM3_RM32_Msk (0xfu << SFR_RM3_RM32_Pos) /**< \brief (SFR_RM3) READ-WRITE_MARGIN Value: i_daram - 4 Kbytes (rf1p) - uhp_rf_sc_512x64 (EHCI/OHCI) */
#define SFR_RM3_RM32(value) ((SFR_RM3_RM32_Msk & ((value) << SFR_RM3_RM32_Pos)))
#define SFR_RM3_RM33_Pos 12
#define SFR_RM3_RM33_Msk (0xfu << SFR_RM3_RM33_Pos) /**< \brief (SFR_RM3) READ-WRITE_MARGIN Value: i_descram- 320 bytes (rf1p) - uhp_rf_sc_80x32 (EHCI/OHCI) */
#define SFR_RM3_RM33(value) ((SFR_RM3_RM33_Msk & ((value) << SFR_RM3_RM33_Pos)))
/* -------- SFR_RM4 : (SFR Offset: 0x6C) Read Margin4 Register -------- */
#define SFR_RM4_RM40_Pos 0
#define SFR_RM4_RM40_Msk (0xfu << SFR_RM4_RM40_Pos) /**< \brief (SFR_RM4) READ-WRITE_MARGIN Value: i_ahb_sram - 64 Kbytes (sram) - system_sram_16384x32sw1 (SRAM0) */
#define SFR_RM4_RM40(value) ((SFR_RM4_RM40_Msk & ((value) << SFR_RM4_RM40_Pos)))
#define SFR_RM4_RM41_Pos 4
#define SFR_RM4_RM41_Msk (0xfu << SFR_RM4_RM41_Pos) /**< \brief (SFR_RM4) READ-WRITE_MARGIN Value: i_ahb_sram_otpc - 4 Kbytes (sram) - otpc_sram_1024x32sw1 (SRAM1 (OTPC)) */
#define SFR_RM4_RM41(value) ((SFR_RM4_RM41_Msk & ((value) << SFR_RM4_RM41_Pos)))
#define SFR_RM4_RM42_Pos 8
#define SFR_RM4_RM42_Msk (0xfu << SFR_RM4_RM42_Pos) /**< \brief (SFR_RM4) READ_MARGIN Value: i_rom_16384x32_sys - 64 Kbytes - (rom) - rom_system_rom_16384x32 (ROM) */
#define SFR_RM4_RM42(value) ((SFR_RM4_RM42_Msk & ((value) << SFR_RM4_RM42_Pos)))
#define SFR_RM4_RM43_Pos 12
#define SFR_RM4_RM43_Msk (0xfu << SFR_RM4_RM43_Pos) /**< \brief (SFR_RM4) READ_MARGIN Value: i_rom_24576x32_ecc - 96 Kbytes - (rom) - rom_system_rom_24576x32 (ROM) */
#define SFR_RM4_RM43(value) ((SFR_RM4_RM43_Msk & ((value) << SFR_RM4_RM43_Pos)))
#define SFR_RM4_RM44_Pos 16
#define SFR_RM4_RM44_Msk (0xfu << SFR_RM4_RM44_Pos) /**< \brief (SFR_RM4) READ-WRITE_MARGIN Value: i_otpc_rf_sc_264x32sw1 - 1 Kbyte (rf1p) - otpc_rf_sc_264x32sw1 (OTPC) */
#define SFR_RM4_RM44(value) ((SFR_RM4_RM44_Msk & ((value) << SFR_RM4_RM44_Pos)))
/* -------- SFR_RM5 : (SFR Offset: 0x70) Read Margin5 Register -------- */
#define SFR_RM5_RM50_Pos 0
#define SFR_RM5_RM50_Msk (0xfu << SFR_RM5_RM50_Pos) /**< \brief (SFR_RM5) READ-WRITE_MARGIN Value: uICTagRam0, uICTagRam1, uICTagRam2, uICTagRam3 - 2.75 Kbytes (rf1p) - rf_256x22 (ARM926) */
#define SFR_RM5_RM50(value) ((SFR_RM5_RM50_Msk & ((value) << SFR_RM5_RM50_Pos)))
#define SFR_RM5_RM51_Pos 4
#define SFR_RM5_RM51_Msk (0xfu << SFR_RM5_RM51_Pos) /**< \brief (SFR_RM5) READ-WRITE_MARGIN Value: uICValidRam, uDCValidRam - 384 bytes (rf1p) - rf_64x24 (ARM926) */
#define SFR_RM5_RM51(value) ((SFR_RM5_RM51_Msk & ((value) << SFR_RM5_RM51_Pos)))
#define SFR_RM5_RM52_Pos 8
#define SFR_RM5_RM52_Msk (0xfu << SFR_RM5_RM52_Pos) /**< \brief (SFR_RM5) READ_MARGIN Value: uDCTagRam0, uDCTagRam1, uDCTagRam2, uDCTagRam3 - 5.5 Kbytes (rf1p) - rf_512x22 (ARM926) */
#define SFR_RM5_RM52(value) ((SFR_RM5_RM52_Msk & ((value) << SFR_RM5_RM52_Pos)))
#define SFR_RM5_RM53_Pos 12
#define SFR_RM5_RM53_Msk (0xfu << SFR_RM5_RM53_Pos) /**< \brief (SFR_RM5) READ_MARGIN Value: uDCDirtyRam - 256 bytes (rf1p) - rf_256x8 (ARM926) */
#define SFR_RM5_RM53(value) ((SFR_RM5_RM53_Msk & ((value) << SFR_RM5_RM53_Pos)))
#define SFR_RM5_RM54_Pos 16
#define SFR_RM5_RM54_Msk (0xfu << SFR_RM5_RM54_Pos) /**< \brief (SFR_RM5) READ-WRITE_MARGIN Value: uMMU1, uMMU3 - 240 bytes (rf1p) - rf_32x30 (ARM926) */
#define SFR_RM5_RM54(value) ((SFR_RM5_RM54_Msk & ((value) << SFR_RM5_RM54_Pos)))
#define SFR_RM5_RM55_Pos 20
#define SFR_RM5_RM55_Msk (0xfu << SFR_RM5_RM55_Pos) /**< \brief (SFR_RM5) READ-WRITE_MARGIN Value: uMMU0, uMMU2 - 208 bytes (rf1p) - rf_32x26 (ARM926) */
#define SFR_RM5_RM55(value) ((SFR_RM5_RM55_Msk & ((value) << SFR_RM5_RM55_Pos)))
#define SFR_RM5_RM56_Pos 24
#define SFR_RM5_RM56_Msk (0xfu << SFR_RM5_RM56_Pos) /**< \brief (SFR_RM5) READ-WRITE_MARGIN Value: uICDataRam0, uICDataRam1, uICDataRam2, uICDataRam3,- 32 Kbytes (sram) - sram_2048x32 (ARM926). uDCDataRam0, uDCDataRam1, uDCDataRam2, uDCDataRam3 - 32 Kbytes (sram) - sram_2048x32sw1 (ARM926) */
#define SFR_RM5_RM56(value) ((SFR_RM5_RM56_Msk & ((value) << SFR_RM5_RM56_Pos)))
/* -------- SFR_LS : (SFR Offset: 0x7C) Light Sleep Register -------- */
#define SFR_LS_LS0 (0x1u << 0) /**< \brief (SFR_LS) Light Sleep Value (GFX2D) */
#define SFR_LS_LS1 (0x1u << 1) /**< \brief (SFR_LS) Light Sleep Value (HLCDC5) */
#define SFR_LS_LS2 (0x1u << 2) /**< \brief (SFR_LS) Light Sleep Value (SDMMC) */
#define SFR_LS_LS3 (0x1u << 3) /**< \brief (SFR_LS) Light Sleep Value (HUSB) */
#define SFR_LS_LS4 (0x1u << 4) /**< \brief (SFR_LS) Light Sleep Value (HXDMA) */
#define SFR_LS_LS5 (0x1u << 5) /**< \brief (SFR_LS) Light Sleep Value (EHCI/OHCI) */
#define SFR_LS_LS6 (0x1u << 6) /**< \brief (SFR_LS) Light Sleep Value (SRAM0) */
#define SFR_LS_LS7 (0x1u << 7) /**< \brief (SFR_LS) Light Sleep Value (SRAM1 (OTPC)) (This bit is used by i_ahb_sram_otpc) */
#define SFR_LS_LS8 (0x1u << 8) /**< \brief (SFR_LS) Light Sleep Value (ROM + OTPC) (This bit is used by rom_16384x32_sys, rom_24576x32_ecc and otpc_rf_sc_264x32sw1) */
#define SFR_LS_LS9 (0x1u << 9) /**< \brief (SFR_LS) Light Sleep Value (ARM926) */
#define SFR_LS_MEM_POWER_GATING_ULP1_EN (0x1u << 16) /**< \brief (SFR_LS) Light Sleep Value for ULP1 Power-Gated Memories */
/* -------- SFR_CAL0 : (SFR Offset: 0xB0) I/O Calibration 0 Register -------- */
#define SFR_CAL0_CALN_P0_Pos 0
#define SFR_CAL0_CALN_P0_Msk (0xfu << SFR_CAL0_CALN_P0_Pos) /**< \brief (SFR_CAL0) Calibration of Low Level Output Impedance of Pads with VDDIOP0 Supply */
#define SFR_CAL0_CALN_P0(value) ((SFR_CAL0_CALN_P0_Msk & ((value) << SFR_CAL0_CALN_P0_Pos)))
#define SFR_CAL0_CALP_P0_Pos 4
#define SFR_CAL0_CALP_P0_Msk (0xfu << SFR_CAL0_CALP_P0_Pos) /**< \brief (SFR_CAL0) Calibration of High Level Output Impedance of Pads with VDDIOP0 Supply */
#define SFR_CAL0_CALP_P0(value) ((SFR_CAL0_CALP_P0_Msk & ((value) << SFR_CAL0_CALP_P0_Pos)))
#define SFR_CAL0_CALN_P1_Pos 8
#define SFR_CAL0_CALN_P1_Msk (0xfu << SFR_CAL0_CALN_P1_Pos) /**< \brief (SFR_CAL0) Calibration of Low Level Output Impedance of Pads with VDDIOP1 Supply */
#define SFR_CAL0_CALN_P1(value) ((SFR_CAL0_CALN_P1_Msk & ((value) << SFR_CAL0_CALN_P1_Pos)))
#define SFR_CAL0_CALP_P1_Pos 12
#define SFR_CAL0_CALP_P1_Msk (0xfu << SFR_CAL0_CALP_P1_Pos) /**< \brief (SFR_CAL0) Calibration of High Level Output Impedance of Pads with VDDIOP1 Supply */
#define SFR_CAL0_CALP_P1(value) ((SFR_CAL0_CALP_P1_Msk & ((value) << SFR_CAL0_CALP_P1_Pos)))
#define SFR_CAL0_CALN_ANA_Pos 16
#define SFR_CAL0_CALN_ANA_Msk (0xfu << SFR_CAL0_CALN_ANA_Pos) /**< \brief (SFR_CAL0) Calibration of Low Level Output Impedance of Pads with VDDANA Supply */
#define SFR_CAL0_CALN_ANA(value) ((SFR_CAL0_CALN_ANA_Msk & ((value) << SFR_CAL0_CALN_ANA_Pos)))
#define SFR_CAL0_CALP_ANA_Pos 20
#define SFR_CAL0_CALP_ANA_Msk (0xfu << SFR_CAL0_CALP_ANA_Pos) /**< \brief (SFR_CAL0) Calibration of High Level Output Impedance of Pads with VDDANA Supply */
#define SFR_CAL0_CALP_ANA(value) ((SFR_CAL0_CALP_ANA_Msk & ((value) << SFR_CAL0_CALP_ANA_Pos)))
#define SFR_CAL0_CALN_QSPI_Pos 24
#define SFR_CAL0_CALN_QSPI_Msk (0xfu << SFR_CAL0_CALN_QSPI_Pos) /**< \brief (SFR_CAL0) Calibration of Low Level Output Impedance of Pads with VDDQSPI Supply */
#define SFR_CAL0_CALN_QSPI(value) ((SFR_CAL0_CALN_QSPI_Msk & ((value) << SFR_CAL0_CALN_QSPI_Pos)))
#define SFR_CAL0_CALP_QSPI_Pos 28
#define SFR_CAL0_CALP_QSPI_Msk (0xfu << SFR_CAL0_CALP_QSPI_Pos) /**< \brief (SFR_CAL0) Calibration of High Level Output Impedance of Pads with VDDQSPI Supply */
#define SFR_CAL0_CALP_QSPI(value) ((SFR_CAL0_CALP_QSPI_Msk & ((value) << SFR_CAL0_CALP_QSPI_Pos)))
/* -------- SFR_CAL1 : (SFR Offset: 0xB4) I/O Calibration 1 Register -------- */
#define SFR_CAL1_CALN_M_Pos 0
#define SFR_CAL1_CALN_M_Msk (0xfu << SFR_CAL1_CALN_M_Pos) /**< \brief (SFR_CAL1) Calibration of Low Level Output Impedance of Pads with VDDIOM Supply */
#define SFR_CAL1_CALN_M(value) ((SFR_CAL1_CALN_M_Msk & ((value) << SFR_CAL1_CALN_M_Pos)))
#define SFR_CAL1_CALP_M_Pos 4
#define SFR_CAL1_CALP_M_Msk (0xfu << SFR_CAL1_CALP_M_Pos) /**< \brief (SFR_CAL1) Calibration of High Level Output Impedance of Pads with VDDIOM Supply */
#define SFR_CAL1_CALP_M(value) ((SFR_CAL1_CALP_M_Msk & ((value) << SFR_CAL1_CALP_M_Pos)))
#define SFR_CAL1_TEST_M (0x1u << 8) /**< \brief (SFR_CAL1) Enable Calibration of Low/High Level Output Impedance of Pads with VDDIOM Supply */
/* -------- SFR_WPMR : (SFR Offset: 0xE4) Write Protection Mode Register -------- */
#define SFR_WPMR_WPEN (0x1u << 0) /**< \brief (SFR_WPMR) Write Protection Enable */
#define SFR_WPMR_WPKEY_Pos 8
#define SFR_WPMR_WPKEY_Msk (0xffffffu << SFR_WPMR_WPKEY_Pos) /**< \brief (SFR_WPMR) Write Protection Key */
#define SFR_WPMR_WPKEY(value) ((SFR_WPMR_WPKEY_Msk & ((value) << SFR_WPMR_WPKEY_Pos)))
#define   SFR_WPMR_WPKEY_PASSWD (0x534652u << 8) /**< \brief (SFR_WPMR) Writing any other value in this field aborts the write operation of the WPEN bit.Always reads as 0. */
/* -------- SFR_SPARE : (SFR Offset: 0x100) Spare Register -------- */
#define SFR_SPARE_VALUE_Pos 0
#define SFR_SPARE_VALUE_Msk (0xffffffffu << SFR_SPARE_VALUE_Pos) /**< \brief (SFR_SPARE) Spare */
#define SFR_SPARE_VALUE(value) ((SFR_SPARE_VALUE_Msk & ((value) << SFR_SPARE_VALUE_Pos)))
/* -------- SFR_BU_SPARE : (SFR Offset: 0x104) Spare Register (BackUp) -------- */
#define SFR_BU_SPARE_VALUE_Pos 0
#define SFR_BU_SPARE_VALUE_Msk (0xffffu << SFR_BU_SPARE_VALUE_Pos) /**< \brief (SFR_BU_SPARE) Spare */
#define SFR_BU_SPARE_VALUE(value) ((SFR_BU_SPARE_VALUE_Msk & ((value) << SFR_BU_SPARE_VALUE_Pos)))

/*@}*/


#endif /* _SAM9X_SFR_COMPONENT_ */
