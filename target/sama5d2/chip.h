/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
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
/*                                                                              */

#ifndef _CHIP_H_
#define _CHIP_H_

#include <stdint.h>
#include <stdbool.h>

#include "sama5d2.h"
#include "chip_common.h"

/* forward declaration */
struct _console_cfg;

/* ************************************************************************** */
/*   CHIPID DEFINITIONS FOR SAMA5D2x */
/* ************************************************************************** */
/** \addtogroup SAMA5D2x_chipid CHIPID Definitions */
/*@{*/

#define CHIPID_CIDR_SAMA5D2     (0x8a5c08c0ul)

#define CHIPID_EXID_SAMA5D21_CU (0x0000005aul)
#define CHIPID_EXID_SAMA5D22_CU (0x00000059ul)
#define CHIPID_EXID_SAMA5D22_CN (0x00000069ul)
#define CHIPID_EXID_SAMA5D23_CU (0x00000058ul)
#define CHIPID_EXID_SAMA5D24_CX (0x00000004ul)
#define CHIPID_EXID_SAMA5D24_CU (0x00000014ul)
#define CHIPID_EXID_SAMA5D26_CU (0x00000012ul)
#define CHIPID_EXID_SAMA5D27_CU (0x00000011ul)
#define CHIPID_EXID_SAMA5D27_CN (0x00000021ul)
#define CHIPID_EXID_SAMA5D28_CU (0x00000010ul)
#define CHIPID_EXID_SAMA5D28_CN (0x00000020ul)
#define CHIPID_EXID_SAMA5D225_D1M (0x00000053ul)
#define CHIPID_EXID_SAMA5D27_D5M (0x00000032ul)
#define CHIPID_EXID_SAMA5D27_D1G (0x00000033ul)
#define CHIPID_EXID_SAMA5D28_D1G (0x00000013ul)

/*@}*/

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAMA5D2x */
/* ************************************************************************** */
/** \addtogroup SAMA5D2x_id Peripheral Ids Definitions */
/*@{*/

#define ID_SAIC_FIQ     ( 0) /**< \brief FIQ Interrupt ID (SAIC_FIQ) */
#define ID_ARM_PMU      ( 2) /**< \brief Performance Monitor Unit (PMU) (ARM_PMU) */
#define ID_PIT          ( 3) /**< \brief Periodic Interval Timer Interrupt (PIT) */
#define ID_WDT          ( 4) /**< \brief Watchdog timer Interrupt (WDT) */
#define ID_GMAC0        ( 5) /**< \brief Ethernet MAC (GMAC0) */
#define ID_XDMAC0       ( 6) /**< \brief DMA Controller 0 (XDMAC0) */
#define ID_XDMAC1       ( 7) /**< \brief DMA Controller 1 (XDMAC1) */
#define ID_ICM          ( 8) /**< \brief Integritry Check Monitor (ICM) */
#define ID_AES          ( 9) /**< \brief Advanced Enion Standard (AES) */
#define ID_AESB         (10) /**< \brief AES bridge (AESB) */
#define ID_TDES         (11) /**< \brief Triple Data Enion Standard (TDES) */
#define ID_SHA          (12) /**< \brief SHA Signature (SHA) */
#define ID_MPDDRC       (13) /**< \brief MPDDR controller (MPDDRC) */
#define ID_MATRIX1      (14) /**< \brief H32MX, 32-bit AHB Matrix (MATRIX1) */
#define ID_MATRIX0      (15) /**< \brief H64MX, 64-bit AHB Matrix (MATRIX0) */
#define ID_SECUMOD      (16) /**< \brief Secure Module (SECUMOD) */
#define ID_SMC          (17) /**< \brief Static Memory Controller (SMC) */
#define ID_PIOA         (18) /**< \brief Parallel I/O Controller (PIOA) */
#define ID_FLEXCOM0     (19) /**< \brief FLEXCOM 0 (FLEXCOM0) */
#define ID_FLEXCOM1     (20) /**< \brief FLEXCOM 1 (FLEXCOM1) */
#define ID_FLEXCOM2     (21) /**< \brief FLEXCOM 1 (FLEXCOM1) */
#define ID_FLEXCOM3     (22) /**< \brief FLEXCOM 3 (FLEXCOM3) */
#define ID_FLEXCOM4     (23) /**< \brief FLEXCOM 4 (FLEXCOM4) */
#define ID_UART0        (24) /**< \brief UART 0 (UART0) */
#define ID_UART1        (25) /**< \brief UART 1 (UART1) */
#define ID_UART2        (26) /**< \brief UART 2 (UART2) */
#define ID_UART3        (27) /**< \brief UART 3 (UART3) */
#define ID_UART4        (28) /**< \brief UART 4 (UART4) */
#define ID_TWI0         (29) /**< \brief Two-Wire Interface 0 (TWI0) */
#define ID_TWI1         (30) /**< \brief Two-Wire Interface 1 (TWI1) */
#define ID_SDMMC0       (31) /**< \brief Secure Digital Multimedia Card Controller 0 (SDMMC0) */
#define ID_SDMMC1       (32) /**< \brief Secure Digital Multimedia Card Controller 1 (SDMMC1) */
#define ID_SPI0         (33) /**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SPI1         (34) /**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_TC0          (35) /**< \brief Timer Counter 0 (ch. 0, 1, 2) (TC0) */
#define ID_TC1          (36) /**< \brief Timer Counter 1 (ch. 3, 4, 5) (TC1) */
#define ID_PWM0         (38) /**< \brief Pulse Width Modulation Controller0 (ch. 0, 1, 2, 3) (PWM0) */
#define ID_ADC          (40) /**< \brief Touch Screen ADC Controller (ADC) */
#define ID_UHPHS        (41) /**< \brief USB Host High Speed (UHPHS) */
#define ID_UDPHS        (42) /**< \brief USB Device High Speed (UDPHS) */
#define ID_SSC0         (43) /**< \brief Synchronous Serial Controller 0 (SSC0) */
#define ID_SSC1         (44) /**< \brief Synchronous Serial Controller 1 (SSC1) */
#define ID_LCDC         (45) /**< \brief LCD Controller (LCDC) */
#define ID_ISC          (46) /**< \brief Camera Interface (ISC) */
#define ID_TRNG         (47) /**< \brief True Random Number Generator (TRNG) */
#define ID_PDMIC0       (48) /**< \brief Pulse Density Modulation Interface Controller (PDMIC0) */
#define ID_AIC_IRQ      (49) /**< \brief IRQ Interrupt ID (AIC_IRQ) */
#define ID_SFC          (50) /**< \brief Fuse Controller (SFC) */
#define ID_SECURAM      (51) /**< \brief Secured RAM (SECURAM) */
#define ID_QSPI0        (52) /**< \brief QSPI 0 (QSPI0) */
#define ID_QSPI1        (53) /**< \brief QSPI 1 (QSPI1) */
#define ID_I2SC0        (54) /**< \brief Inter-IC Sound Controller 0 (I2SC0) */
#define ID_I2SC1        (55) /**< \brief Inter-IC Sound Controller 1 (I2SC1) */
#define ID_MCAN0_INT0   (56) /**< \brief MCAN 0 Interrupt0 (MCAN0_INT0) */
#define ID_MCAN1_INT0   (57) /**< \brief MCAN 1 Interrupt0 (MCAN1_INT0) */
#define ID_CLASSD0      (59) /**< \brief Audio Class D amplifier (CLASSD0) */
#define ID_SFR          (60) /**< \brief Special Function Register  (SFR) */
#define ID_SAIC         (61) /**< \brief Secured Advanced Interrupt Controller  (SAIC) */
#define ID_AIC          (62) /**< \brief Advanced Interrupt Controller  (AIC) */
#define ID_L2CC         (63) /**< \brief L2 Cache Controller (L2CC) */
#define ID_MCAN0_INT1   (64) /**< \brief MCAN 0 Interrupt1 (MCAN0_INT1) */
#define ID_MCAN1_INT1   (65) /**< \brief MCAN 1 Interrupt1 (MCAN1_INT1) */
#define ID_GMAC0_Q1     (66) /**< \brief GMAC Queue 1 Interrupt (GMAC0_Q1) */
#define ID_GMAC0_Q2     (67) /**< \brief GMAC Queue 2 Interrupt (GMAC0_Q2) */
#define ID_PIOB         (68) /**< \brief  (PIOB) */
#define ID_PIOC         (69) /**< \brief  (PIOC) */
#define ID_PIOD         (70) /**< \brief  (PIOD) */
#define ID_SDMMC0_TIMER (71) /**< \brief  (SDMMC0_TIMER) */
#define ID_SDMMC1_TIMER (72) /**< \brief  (SDMMC1_TIMER) */
#define ID_SYSC         (74) /**< \brief System Controller Interrupt, RTC, RSTC, PMC (SYSC) */
#define ID_RTC          (74) /**< \brief Real Time Clock (RTC) */
#define ID_RSTC         (74) /**< \brief Reset Controller (RSTC) */
#define ID_ACC          (75) /**< \brief Analog Comparator (ACC) */
#define ID_RXLP         (76) /**< \brief Uart Low Power (RXLP) */
#define ID_CHIPID       (78) /**< \brief Chip ID (CHIPID) */

#define ID_PERIPH_COUNT (79) /**< \brief Number of peripheral IDs */

/*@}*/

/* ************************************************************************** */
/*   MASTER MATRIX ID DEFINITIONS FOR SAMA5D2x */
/* ************************************************************************** */
/** \addtogroup SAMA5D2x_matrix Matrix Ids Definitions */
/*@{*/

#define H64MX_MASTER_BRIDGE_AXI     0    /**< Bridge from AXI matrix (Core) */
#define H64MX_MASTER_1_DMAC0        1    /**< DMA Controller 0 */
#define H64MX_MASTER_2_DMAC0        2    /**< DMA Controller 0 */
#define H64MX_MASTER_3_DMAC1        3    /**< DMA Controller 1 */
#define H64MX_MASTER_4_DMAC1        4    /**< DMA Controller 1 */
#define H64MX_MASTER_5_LCDC_DMA     5    /**< LCDC DMA */
#define H64MX_MASTER_6_LCDC_DMA     6    /**< LCDC DMA */
#define H64MX_MASTER_SDMMC0         7    /**< SDMMC0 */
#define H64MX_MASTER_SDMMC1         8    /**< SDMMC1 */
#define H64MX_MASTER_ISC_DMA        9    /**< ISC DMA */
#define H64MX_MASTER_AESB          10    /**< AESB */
#define H64MX_MASTER_BRIDGE_H32MX  11    /**< Bridge from H32MX to H64MX */
#define H64MX_MASTER_COUNT         12

#define H32MX_MASTER_BRIDGE_H64MX   0    /**< Bridge from H64MX to H32MX */
#define H32MX_MASTER_ICM            1    /**< Integrity Check Monitor (ICM) */
#define H32MX_MASTER_UHPHS_EHCI_DMA 2    /**< UHPHS EHCI DMA */
#define H32MX_MASTER_UHPHS_OHCI_DMA 3    /**< UHPHS OHCI DMA */
#define H32MX_MASTER_UDPHS_DMA      4    /**< UDPHS DMA */
#define H32MX_MASTER_GMAC_DMA       5    /**< GMAC DMA */
#define H32MX_MASTER_CAN0_DMA       6    /**< CAN0 DMA */
#define H32MX_MASTER_CAN1_DMA       7    /**< CAN1 DMA */
#define H32MX_MASTER_COUNT          8

/*@}*/

/* ************************************************************************** */
/*   SLAVE MATRIX ID DEFINITIONS FOR SAMA5D2x */
/* ************************************************************************** */
/** \addtogroup SAMA5D2x_matrix Matrix Ids Definitions */
/*@{*/

#define H64MX_SLAVE_BRIDGE_H32MX    0    /**< Bridge from H64MX to H32MX */
#define H64MX_SLAVE_APB             1    /**< H64MX APB - User interfaces */
#define H64MX_SLAVE_SDMMC           1    /**< SDMMC0 - SDMMC1 */
#define H64MX_SLAVE_DDR_PORT0       2    /**< DDR Port 0 */
#define H64MX_SLAVE_DDR_PORT1       3    /**< DDR Port 1 */
#define H64MX_SLAVE_DDR_PORT2       4    /**< DDR Port 2 */
#define H64MX_SLAVE_DDR_PORT3       5    /**< DDR Port 3 */
#define H64MX_SLAVE_DDR_PORT4       6    /**< DDR Port 4 */
#define H64MX_SLAVE_DDR_PORT5       7    /**< DDR Port 5 */
#define H64MX_SLAVE_DDR_PORT6       8    /**< DDR Port 6 */
#define H64MX_SLAVE_DDR_PORT7       9    /**< DDR Port 7 */
#define H64MX_SLAVE_SRAM           10    /**< Internal SRAM 128K */
#define H64MX_SLAVE_L2C_SRAM       11    /**< Internal SRAM 128K (L2) */
#define H64MX_SLAVE_QSPI0          12    /**< QSPI0 */
#define H64MX_SLAVE_QSPI1          13    /**< QSPI1 */
#define H64MX_SLAVE_AESB           14    /**< AESB */
#define H64MX_SLAVE_COUNT          15

#define H32MX_SLAVE_BRIDGE_H64MX    0    /**< Bridge from H32MX to H64MX */
#define H32MX_SLAVE_APB0            1    /**< H32MX APB0 - User interfaces */
#define H32MX_SLAVE_APB1            2    /**< H32MX APB1 - User interfaces */
#define H32MX_SLAVE_EBI             3    /**< External Bus Interface CS0..CS3 */
#define H32MX_SLAVE_NFC_CMD         3    /**< NFC Command Register */
#define H32MX_SLAVE_NFC_SRAM        4    /**< NFC SRAM */
#define H32MX_SLAVE_USB             5    /**< USB */
#define H32MX_SLAVE_COUNT           6

/*@}*/

/* ************************************************************************** */
/*   PMECC DEFINITIONS FOR SAMA5D2x */
/* ************************************************************************** */
/** \addtogroup SAMA5D2x_pmecc PMECC Definitions */
/*@{*/

/** Address of Galois Field Table 512 mapping in ROM. */
#define GALOIS_TABLE_512_ROM_MAPPING (0x40000)

/** Address of Galois Field Table 1024 mapping in ROM. */
#define GALOIS_TABLE_1024_ROM_MAPPING (0x48000)

/*@}*/

/* ************************************************************************** */
/* INCLUDE FOR SAMA5D2x */
/* ************************************************************************** */

#include "chip_pins.h"

/** L1 data cache line size in bytes */
#define L1_CACHE_BYTES (32u)

/** L1 data cache line size in words */
#define L1_CACHE_WORDS (L1_CACHE_BYTES / sizeof(uint32_t))

/** Number of ways of L1 data cache */
#define L1_CACHE_WAYS (4)

/** Number of sets of L1 data cache */
#define L1_CACHE_SETS (256)

/** Build a set/way parameter for cache operations */
#define L1_CACHE_SETWAY(set, way) (((set) << 5) | ((way) << 30))

/** TC channel size (in bits) */
#define TC_CHANNEL_SIZE 32

/** FLEXCOM USART FIFO depth */
#define FLEXCOM_USART_FIFO_DEPTH (32u)

/** FLEXCOM SPI FIFO depth */
#define FLEXCOM_SPI_FIFO_DEPTH (32u)

/** CAN Interface max */
#define CAN_IFACE_COUNT (2)

/** SPI FIFO depth */
#define SPI_FIFO_DEPTH (16u)

/** TWI FIFO depth */
#define TWI_FIFO_DEPTH (16u)

/** TWI Interface max */
#ifndef TWI_IFACE_COUNT
#define TWI_IFACE_COUNT (7)
#endif

/** SPI Interface max */
#ifndef SPI_IFACE_COUNT
#define SPI_IFACE_COUNT (6)
#endif

/** USART Interface max */
#ifndef USART_IFACE_COUNT
#define USART_IFACE_COUNT (5)
#endif

/** GMAC Interface max */
#ifndef GMAC_IFACE_COUNT
#define GMAC_IFACE_COUNT (1)
#endif

/** GMAC Queue max */
#ifndef GMAC_QUEUE_COUNT
#define GMAC_QUEUE_COUNT (3)
#endif

/** Ethernet Interface max */
#ifndef ETH_IFACE_COUNT
#define ETH_IFACE_COUNT GMAC_IFACE_COUNT
#endif

/** Ethernet Queue max */
#ifndef ETH_QUEUE_COUNT
#define ETH_QUEUE_COUNT (3)
#endif

/** Frequency of the on-chip slow clock oscillator */
#define SLOW_CLOCK_INT_OSC 32000

/** Frequency of the on-chip main clock oscillator */
#define MAIN_CLOCK_INT_OSC 12000000

/** AIC redirection unlock key */
#define AICREDIR_KEY 0x5B6C0E26u

/** MPDDRC I/O Calibration Delay (in nanoseconds) */
#define MPDDRC_TZQIO_DELAY (600)

/** Endpoints max paxcket size */
#define CHIP_USB_ENDPOINT_MAXPACKETSIZE(ep) \
   ((ep) == 0 ? 64 : 1024)

/** Endpoints Number of Bank */
#define CHIP_USB_ENDPOINT_BANKS(ep) \
   ((ep) == 0 ? 1 : ((ep) < 3 ? 3 : 2))

/** Endpoints DMA support */
#define CHIP_USB_ENDPOINT_HAS_DMA(ep) \
    ((ep) > 0 && ((ep) < 7))

/** Endpoints High Band Width support */
#define CHIP_USB_ENDPOINT_IS_HBW(ep) \
    ((ep) == 1 || (ep) == 2)

/** NAND EBI Chip Select */
#define NAND_EBI_CS 3

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief Identify the chip model and return it as a string
 * \return a constant string containing the chip name
 */
extern const char* get_chip_name(void);

/**
 * \brief Return the default parameters used by the ROM-code for its console.
 * \param config a structure into which the function will write the serial
 * peripheral, the baudrate and the TX/RX pins. It will be all zeros if the
 * ROM-code console is disabled.
 */
extern void get_romcode_console(struct _console_cfg* config);

/** \brief Returns the matrix on which the given peripheral is connected
 *
 * \param id the Peripheral ID
 * \return a pointer to the Matrix instance
 */
extern Matrix* get_peripheral_matrix(uint32_t id);

/** \brief Returns the matrix clock divider for the given peripheral
 *
 * \param id the Peripheral ID
 * \return the clock divider for the peripheral
 */
extern uint32_t get_peripheral_clock_matrix_div(uint32_t id);

/** \brief Returns the XDMAC interface number for a given peripheral
 *
 * \param id the Peripheral ID
 * \param xdmac the XDMAC controller instance
 * \param transmit a boolean, true for transmit, false for receive
 * \return the XDMAC interface number or 0xff if none
 */
extern uint8_t get_peripheral_dma_channel(uint32_t id, Xdmac *xdmac, bool transmit);

/** \brief Checks if a peripheral is usable with a XDMAC controller
 *
 * \param id the Peripheral ID
 * \param xdmac the XDMAC controller instance
 * \return true if the peripheral is usable on the given XDMAC controller,
 * false otherwise
 */
extern bool is_peripheral_on_dma_controller(uint32_t id, Xdmac *xdmac);

/** \brief Retrive peripheral FIFO size from its base address
 *
 * \param addr the Peripheral base addr
 * \return Size in number of data of the peripherals FIFO if
 * available, negative value otherwise.
 */
extern int32_t get_peripheral_fifo_depth(void* addr);

#ifdef __cplusplus
}
#endif

#endif /* _CHIP_H_ */
