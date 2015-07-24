/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _SAMA5D23_
#define _SAMA5D23_

/** \addtogroup SAMA5D23_definitions SAMA5D23 definitions
  This file defines all structures and symbols for SAMA5D23:
    - registers and bitfields
    - peripheral base address
    - peripheral ID
    - PIO definitions
*/
/*@{*/

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

typedef enum IRQn
{
  PIT_IRQn             =  3, /**<  3 Periodic Interval Timer Interrupt (PIT) */
  WDT_IRQn             =  4, /**<  4 Watchdog timer Interrupt (WDT) */
  GMAC0_IRQn           =  5, /**<  5 Ethernet MAC (GMAC0) */
  XDMAC0_IRQn          =  6, /**<  6 DMA Controller 0 (XDMAC0) */
  XDMAC1_IRQn          =  7, /**<  7 DMA Controller 1 (XDMAC1) */
  ICM_IRQn             =  8, /**<  8 Integritry Check Monitor (ICM) */
  AES_IRQn             =  9, /**<  9 Advanced Enion Standard (AES) */
  AESB_IRQn            = 10, /**< 10 AES bridge (AESB) */
  TDES_IRQn            = 11, /**< 11 Triple Data Enion Standard (TDES) */
  SHA_IRQn             = 12, /**< 12 SHA Signature (SHA) */
  MPDDRC_IRQn          = 13, /**< 13 MPDDR controller (MPDDRC) */
  MATRIX1_IRQn         = 14, /**< 14 H32MX, 32-bit AHB Matrix (MATRIX1) */
  MATRIX0_IRQn         = 15, /**< 15 H64MX, 64-bit AHB Matrix (MATRIX0) */
  HSMC_IRQn            = 17, /**< 17 Multi-bit ECC Interrupt (HSMC) */
  PIOA_IRQn            = 18, /**< 18 Parallel I/O Controller (PIOA) */
  FLEXCOM0_IRQn        = 19, /**< 19 FLEXCOM 0 (FLEXCOM0) */
  FLEXCOM1_IRQn        = 20, /**< 20 FLEXCOM 1 (FLEXCOM1) */
  FLEXCOM3_IRQn        = 22, /**< 22 FLEXCOM 3 (FLEXCOM3) */
  FLEXCOM4_IRQn        = 23, /**< 23 FLEXCOM 4 (FLEXCOM4) */
  UART0_IRQn           = 24, /**< 24 UART 0 (UART0) */
  UART1_IRQn           = 25, /**< 25 UART 1 (UART1) */
  UART2_IRQn           = 26, /**< 26 UART 2 (UART2) */
  UART3_IRQn           = 27, /**< 27 UART 3 (UART3) */
  UART4_IRQn           = 28, /**< 28 UART 4 (UART4) */
  TWIHS0_IRQn          = 29, /**< 29 Two-Wire Interface 0 (TWIHS0) */
  TWIHS1_IRQn          = 30, /**< 30 Two-Wire Interface 1 (TWIHS1) */
  SPI0_IRQn            = 33, /**< 33 Serial Peripheral Interface 0 (SPI0) */
  SPI1_IRQn            = 34, /**< 34 Serial Peripheral Interface 1 (SPI1) */
  TC0_IRQn             = 35, /**< 35 Timer Counter 0 (ch. 0, 1, 2) (TC0) */
  TC1_IRQn             = 36, /**< 36 Timer Counter 1 (ch. 3, 4, 5) (TC1) */
  PWM_IRQn             = 38, /**< 38 Pulse Width Modulation Controller0 (ch. 0, 1, 2, 3) (PWM) */
  ADC_IRQn             = 40, /**< 40 Touch Screen ADC Controller (ADC) */
  UHPHS_IRQn           = 41, /**< 41 USB Host High Speed (UHPHS) */
  UDPHS_IRQn           = 42, /**< 42 USB Device High Speed (UDPHS) */
  SSC0_IRQn            = 43, /**< 43 Synchronous Serial Controller 0 (SSC0) */
  SSC1_IRQn            = 44, /**< 44 Synchronous Serial Controller 1 (SSC1) */
  LCDC_IRQn            = 45, /**< 45 LCD Controller (LCDC) */
  ISC_IRQn             = 46, /**< 46 Camera Interface (ISC) */
  TRNG_IRQn            = 47, /**< 47 True Random Number Generator (TRNG) */
  PDMIC_IRQn           = 48, /**< 48 Pulse Density Modulation Interface Controller (PDMIC) */
  SFC_IRQn             = 50, /**< 50 Fuse Controller (SFC) */
  QSPI0_IRQn           = 52, /**< 52 QSPI 0 (QSPI0) */
  QSPI1_IRQn           = 53, /**< 53 QSPI 1 (QSPI1) */
  I2SC0_IRQn           = 54, /**< 54 Inter-IC Sound Controller 0 (I2SC0) */
  I2SC1_IRQn           = 55, /**< 55 Inter-IC Sound Controller 1 (I2SC1) */
  CLASSD_IRQn          = 59, /**< 59 Audio Class D amplifier (CLASSD) */
  SFR_IRQn             = 60, /**< 60 Special Function Register  (SFR) */
  SAIC_IRQn            = 61, /**< 61 Secured Advanced Interrupt Controller  (SAIC) */
  AIC_IRQn             = 62, /**< 62 Advanced Interrupt Controller  (AIC) */
  L2CC_IRQn            = 63, /**< 63 L2 Cache Controller (L2CC) */
  PIOB_IRQn            = 68, /**< 68  (PIOB) */
  PIOC_IRQn            = 69, /**< 69  (PIOC) */
  PIOD_IRQn            = 70, /**< 70  (PIOD) */
  ACC_IRQn             = 75, /**< 75 Analog Comparator (ACC) */
  RXLP_IRQn            = 76, /**< 76 Uart Low Power (RXLP) */
  CHIPID_IRQn          = 78, /**< 78 Chip ID (CHIPID) */

  PERIPH_COUNT_IRQn    = 79  /**< Number of peripheral IDs */
} IRQn_Type;

/* ************************************************************************** */
/**  SOFTWARE PERIPHERAL API DEFINITION FOR SAMA5D23 */
/* ************************************************************************** */
/** \addtogroup SAMA5D23_api Peripheral Software API */
/*@{*/

#include "component/component_acc.h"
#include "component/component_adc.h"
#include "component/component_aesb.h"
#include "component/component_aes.h"
#include "component/component_aic.h"
#include "component/component_aximx.h"
#include "component/component_chipid.h"
#include "component/component_classd.h"
#include "component/component_flexcom.h"
#include "component/component_gmac.h"
#include "component/component_i2sc.h"
#include "component/component_icm.h"
#include "component/component_isc.h"
#include "component/component_l2cc.h"
#include "component/component_lcdc.h"
#include "component/component_matrix.h"
#include "component/component_mpddrc.h"
#include "component/component_pdmic.h"
#include "component/component_pio.h"
#include "component/component_pit.h"
#include "component/component_pmc.h"
#include "component/component_pwm.h"
#include "component/component_qspi.h"
#include "component/component_rstc.h"
#include "component/component_rtc.h"
#include "component/component_rxlp.h"
#include "component/component_sckc.h"
#include "component/component_sfc.h"
#include "component/component_sfr.h"
#include "component/component_sha.h"
#include "component/component_shdwc.h"
#include "component/component_smc.h"
#include "component/component_ssc.h"
#include "component/component_tc.h"
#include "component/component_tdes.h"
#include "component/component_trng.h"
#include "component/component_twihs.h"
#include "component/component_uart.h"
#include "component/component_udphs.h"
#include "component/component_wdt.h"
#include "component/component_xdmac.h"
/*@}*/

/* ************************************************************************** */
/*   BASE ADDRESS DEFINITIONS FOR SAMA5D23 */
/* ************************************************************************** */
/** \addtogroup SAMA5D23_base Peripheral Base Address Definitions */
/*@{*/

#define AXIMX    ((Aximx    *)0x00600000U) /**< \brief (AXIMX   ) Base Address */
#define L2CC     ((L2cc     *)0x00A00000U) /**< \brief (L2CC    ) Base Address */
#define LCDC     ((Lcdc     *)0xF0000000U) /**< \brief (LCDC    ) Base Address */
#define XDMAC1   ((Xdmac    *)0xF0004000U) /**< \brief (XDMAC1  ) Base Address */
#define ISC      ((Isc      *)0xF0008000U) /**< \brief (ISC     ) Base Address */
#define MPDDRC   ((Mpddrc   *)0xF000C000U) /**< \brief (MPDDRC  ) Base Address */
#define XDMAC0   ((Xdmac    *)0xF0010000U) /**< \brief (XDMAC0  ) Base Address */
#define PMC      ((Pmc      *)0xF0014000U) /**< \brief (PMC     ) Base Address */
#define MATRIX0  ((Matrix   *)0xF0018000U) /**< \brief (MATRIX0 ) Base Address */
#define AESB     ((Aesb     *)0xF001C000U) /**< \brief (AESB    ) Base Address */
#define QSPI0    ((Qspi     *)0xF0020000U) /**< \brief (QSPI0   ) Base Address */
#define QSPI1    ((Qspi     *)0xF0024000U) /**< \brief (QSPI1   ) Base Address */
#define SHA      ((Sha      *)0xF0028000U) /**< \brief (SHA     ) Base Address */
#define AES      ((Aes      *)0xF002C000U) /**< \brief (AES     ) Base Address */
#define SPI0     ((Spi      *)0xF8000000U) /**< \brief (SPI0    ) Base Address */
#define SSC0     ((Ssc      *)0xF8004000U) /**< \brief (SSC0    ) Base Address */
#define GMAC     ((Gmac     *)0xF8008000U) /**< \brief (GMAC    ) Base Address */
#define TC0      ((Tc       *)0xF800C000U) /**< \brief (TC0     ) Base Address */
#define TC1      ((Tc       *)0xF8010000U) /**< \brief (TC1     ) Base Address */
#define HSMC     ((Smc      *)0xF8014000U) /**< \brief (HSMC    ) Base Address */
#define PDMIC    ((Pdmic    *)0xF8018000U) /**< \brief (PDMIC   ) Base Address */
#define UART0    ((Uart     *)0xF801C000U) /**< \brief (UART0   ) Base Address */
#define UART1    ((Uart     *)0xF8020000U) /**< \brief (UART1   ) Base Address */
#define UART2    ((Uart     *)0xF8024000U) /**< \brief (UART2   ) Base Address */
#define TWIHS0   ((Twihs    *)0xF8028000U) /**< \brief (TWIHS0  ) Base Address */
#define PWM      ((Pwm      *)0xF802C000U) /**< \brief (PWM     ) Base Address */
#define SFR      ((Sfr      *)0xF8030000U) /**< \brief (SFR     ) Base Address */
#define FLEXCOM0 ((Flexcom  *)0xF8034000U) /**< \brief (FLEXCOM0) Base Address */
#define FLEXCOM1 ((Flexcom  *)0xF8038000U) /**< \brief (FLEXCOM1) Base Address */
#define SAIC     ((Aic      *)0xF803C000U) /**< \brief (SAIC    ) Base Address */
#define ICM      ((Icm      *)0xF8040000U) /**< \brief (ICM     ) Base Address */
#define RSTC     ((Rstc     *)0xF8048000U) /**< \brief (RSTC    ) Base Address */
#define SHDWC    ((Shdwc    *)0xF8048010U) /**< \brief (SHDWC   ) Base Address */
#define PIT      ((Pit      *)0xF8048030U) /**< \brief (PIT     ) Base Address */
#define WDT      ((Wdt      *)0xF8048040U) /**< \brief (WDT     ) Base Address */
#define SCKC     ((Sckc     *)0xF8048050U) /**< \brief (SCKC    ) Base Address */
#define RTC      ((Rtc      *)0xF80480B0U) /**< \brief (RTC     ) Base Address */
#define RXLP     ((Rxlp     *)0xF8049000U) /**< \brief (RXLP    ) Base Address */
#define ACC      ((Acc      *)0xF804A000U) /**< \brief (ACC     ) Base Address */
#define SFC      ((Sfc      *)0xF804C000U) /**< \brief (SFC     ) Base Address */
#define I2SC0    ((I2sc     *)0xF8050000U) /**< \brief (I2SC0   ) Base Address */
#define SPI1     ((Spi      *)0xFC000000U) /**< \brief (SPI1    ) Base Address */
#define SSC1     ((Ssc      *)0xFC004000U) /**< \brief (SSC1    ) Base Address */
#define UART3    ((Uart     *)0xFC008000U) /**< \brief (UART3   ) Base Address */
#define UART4    ((Uart     *)0xFC00C000U) /**< \brief (UART4   ) Base Address */
#define FLEXCOM3 ((Flexcom  *)0xFC014000U) /**< \brief (FLEXCOM3) Base Address */
#define FLEXCOM4 ((Flexcom  *)0xFC018000U) /**< \brief (FLEXCOM4) Base Address */
#define TRNG     ((Trng     *)0xFC01C000U) /**< \brief (TRNG    ) Base Address */
#define AIC      ((Aic      *)0xFC020000U) /**< \brief (AIC     ) Base Address */
#define TWIHS1   ((Twihs    *)0xFC028000U) /**< \brief (TWIHS1  ) Base Address */
#define UDPHS    ((Udphs    *)0xFC02C000U) /**< \brief (UDPHS   ) Base Address */
#define ADC      ((Adc      *)0xFC030000U) /**< \brief (ADC     ) Base Address */
#define PIOA     ((Pio      *)0xFC038000U) /**< \brief (PIOA    ) Base Address */
#define MATRIX1  ((Matrix   *)0xFC03C000U) /**< \brief (MATRIX1 ) Base Address */
#define TDES     ((Tdes     *)0xFC044000U) /**< \brief (TDES    ) Base Address */
#define CLASSD   ((Classd   *)0xFC048000U) /**< \brief (CLASSD  ) Base Address */
#define I2SC1    ((I2sc     *)0xFC04C000U) /**< \brief (I2SC1   ) Base Address */
#define CHIPID   ((Chipid   *)0xFC069000U) /**< \brief (CHIPID  ) Base Address */

/*@}*/

/* ************************************************************************** */
/*   PIO DEFINITIONS FOR SAMA5D23 */
/* ************************************************************************** */
/** \addtogroup SAMA5D23_pio Peripheral Pio Definitions */
/*@{*/

#include "pio/pio_sama5d23.h"
/*@}*/

/* ************************************************************************** */
/*   MEMORY MAPPING DEFINITIONS FOR SAMA5D23 */
/* ************************************************************************** */


#define EBI_CS0_ADDR    (0x10000000u) /**< EBI Chip Select 0 base address */
#define DDR_CS_ADDR     (0x20000000u) /**< DDR Chip Select base address */
#define DDR_AES_CS_ADDR (0x40000000u) /**< DDR with AES Chip Select base address */
#define EBI_CS1_ADDR    (0x60000000u) /**< EBI Chip Select 1 base address */
#define EBI_CS2_ADDR    (0x70000000u) /**< EBI Chip Select 2 base address */
#define EBI_CS3_ADDR    (0x80000000u) /**< EBI Chip Select 3 base address */
#define QSPI_AES0_ADDR  (0x90000000u) /**< QPSI Memory crypted with AES 0 base address */
#define QSPI_AES1_ADDR  (0x98000000u) /**< QPSI Memory crypted with AES 1 base address */
#define SDMMC0_ADDR     (0xA0000000u) /**< SDMMC 0 base address */
#define SDMMC1_ADDR     (0xB0000000u) /**< SDMMC 1 base address */
#define NFC_ADDR        (0xC0000000u) /**< NAND Flash Controller Command base address */
#define QSPIMEM0_ADDR   (0xD0000000u) /**< QSPI Memory 0 base address */
#define QSPIMEM1_ADDR   (0xD8000000u) /**< QSPI Memory 1 base address */
#define IROM_ADDR       (0x00000000u) /**< Internal ROM base address */
#define ECC_ROM_ADDR    (0x00040000u) /**< ECC ROM base address */
#define NFC_RAM_ADDR    (0x00100000u) /**< NAND Flash Controller RAM base address */
#define IRAM0_ADDR      (0x00200000u) /**< Internal RAM 0 base address */
#define IRAM1_ADDR      (0x00220000u) /**< Internal RAM 1 base address */
#define UDPHS_RAM_ADDR  (0x00300000u) /**< USB High Speed Device Port RAM base address */
#define UHPHS_OHCI_ADDR (0x00400000u) /**< USB High Speed Device Port RAM base address */
#define UHPHS_EHCI_ADDR (0x00500000u) /**< USB High Speed Device Port RAM base address */
#define AXIMX_ADDR      (0x00600000u) /**< AXI Bus Matrix base address */
#define DAP_ADDR        (0x00700000u) /**< Debug Access Port base address */
#define PTCMEM_ADDR     (0x00800000u) /**< PTC Memory base address */

/* ************************************************************************** */
/*   MISCELLANEOUS DEFINITIONS FOR SAMA5D23 */
/* ************************************************************************** */

#define CHIP_JTAGID (0x05B3F03FUL)
#define CHIP_CIDR   (0x8A5C08C0UL)
#define CHIP_EXID   (0x00000002UL)

/* ************************************************************************** */
/*   ELECTRICAL DEFINITIONS FOR SAMA5D23 */
/* ************************************************************************** */

/* %ATMEL_ELECTRICAL% */

/* Device characteristics */
#define CHIP_FREQ_SLCK_RC_MIN           (20000UL)
#define CHIP_FREQ_SLCK_RC               (32000UL)
#define CHIP_FREQ_SLCK_RC_MAX           (44000UL)
#define CHIP_FREQ_MAINCK_RC_4MHZ        (4000000UL)
#define CHIP_FREQ_MAINCK_RC_8MHZ        (8000000UL)
#define CHIP_FREQ_MAINCK_RC_12MHZ       (12000000UL)
#define CHIP_FREQ_CPU_MAX               (120000000UL)
#define CHIP_FREQ_XTAL_32K              (32768UL)
#define CHIP_FREQ_XTAL_12M              (12000000UL)

/* Embedded Flash Read Wait State (VDDCORE set at 1.20V) */
#define CHIP_FREQ_FWS_0                 (20000000UL)  /**< \brief Maximum operating frequency when FWS is 0 */
#define CHIP_FREQ_FWS_1                 (40000000UL)  /**< \brief Maximum operating frequency when FWS is 1 */
#define CHIP_FREQ_FWS_2                 (60000000UL)  /**< \brief Maximum operating frequency when FWS is 2 */
#define CHIP_FREQ_FWS_3                 (80000000UL)  /**< \brief Maximum operating frequency when FWS is 3 */
#define CHIP_FREQ_FWS_4                 (100000000UL) /**< \brief Maximum operating frequency when FWS is 4 */
#define CHIP_FREQ_FWS_5                 (123000000UL) /**< \brief Maximum operating frequency when FWS is 5 */

#ifdef __cplusplus
}
#endif

/*@}*/

#endif /* _SAMA5D23_ */
