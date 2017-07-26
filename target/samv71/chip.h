/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
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

#include "samv71.h"
#include "chip_common.h"

/* forward declaration */
struct _console_cfg;

/* ************************************************************************** */
/*   CHIPID DEFINITIONS FOR SAMV71x */
/* ************************************************************************** */
/** \addtogroup SAMV71x_chipid CHIPID Definitions */
/*@{*/

#define CHIPID_CIDR_SAME70Q21 (0xa1020e00ul)
#define CHIPID_CIDR_SAME70Q20 (0xa1020c00ul)
#define CHIPID_CIDR_SAME70Q19 (0xa10d0a00ul)
#define CHIPID_CIDR_SAME70N21 (0xa1020e00ul)
#define CHIPID_CIDR_SAME70N20 (0xa1020c00ul)
#define CHIPID_CIDR_SAME70N19 (0xa10d0a00ul)
#define CHIPID_CIDR_SAME70J21 (0xa1020e00ul)
#define CHIPID_CIDR_SAME70J20 (0xa1020c00ul)
#define CHIPID_CIDR_SAME70J19 (0xa10d0a00ul)
#define CHIPID_CIDR_SAMS70Q21 (0xa1120e00ul)
#define CHIPID_CIDR_SAMS70Q20 (0xa1120c00ul)
#define CHIPID_CIDR_SAMS70Q19 (0xa11d0a00ul)
#define CHIPID_CIDR_SAMS70N21 (0xa1120e00ul)
#define CHIPID_CIDR_SAMS70N20 (0xa1120c00ul)
#define CHIPID_CIDR_SAMS70N19 (0xa11d0a00ul)
#define CHIPID_CIDR_SAMS70J21 (0xa1120e00ul)
#define CHIPID_CIDR_SAMS70J20 (0xa1120c00ul)
#define CHIPID_CIDR_SAMS70J19 (0xa11d0a00ul)
#define CHIPID_CIDR_SAMV70Q20 (0xa1320c00ul)
#define CHIPID_CIDR_SAMV70Q19 (0xa13d0a00ul)
#define CHIPID_CIDR_SAMV70N20 (0xa1320c00ul)
#define CHIPID_CIDR_SAMV70N19 (0xa13d0a00ul)
#define CHIPID_CIDR_SAMV70J20 (0xa1320c00ul)
#define CHIPID_CIDR_SAMV70J19 (0xa13d0a00ul)
#define CHIPID_CIDR_SAMV71Q21 (0xa1220e00ul)
#define CHIPID_CIDR_SAMV71Q20 (0xa1220c00ul)
#define CHIPID_CIDR_SAMV71Q19 (0xa12d0a00ul)
#define CHIPID_CIDR_SAMV71N21 (0xa1220e00ul)
#define CHIPID_CIDR_SAMV71N20 (0xa1220c00ul)
#define CHIPID_CIDR_SAMV71N19 (0xa12d0a00ul)
#define CHIPID_CIDR_SAMV71J21 (0xa1220e00ul)
#define CHIPID_CIDR_SAMV71J20 (0xa1220c00ul)
#define CHIPID_CIDR_SAMV71J19 (0xa12d0a00ul)

#define CHIPID_EXID_SAME70Q21 (0x00000002ul)
#define CHIPID_EXID_SAME70Q20 (0x00000002ul)
#define CHIPID_EXID_SAME70Q19 (0x00000002ul)
#define CHIPID_EXID_SAME70N21 (0x00000001ul)
#define CHIPID_EXID_SAME70N20 (0x00000001ul)
#define CHIPID_EXID_SAME70N19 (0x00000001ul)
#define CHIPID_EXID_SAME70J21 (0x00000000ul)
#define CHIPID_EXID_SAME70J20 (0x00000000ul)
#define CHIPID_EXID_SAME70J19 (0x00000000ul)
#define CHIPID_EXID_SAMS70Q21 (0x00000002ul)
#define CHIPID_EXID_SAMS70Q20 (0x00000002ul)
#define CHIPID_EXID_SAMS70Q19 (0x00000002ul)
#define CHIPID_EXID_SAMS70N21 (0x00000001ul)
#define CHIPID_EXID_SAMS70N20 (0x00000001ul)
#define CHIPID_EXID_SAMS70N19 (0x00000001ul)
#define CHIPID_EXID_SAMS70J21 (0x00000000ul)
#define CHIPID_EXID_SAMS70J20 (0x00000000ul)
#define CHIPID_EXID_SAMS70J19 (0x00000000ul)
#define CHIPID_EXID_SAMV70Q20 (0x00000002ul)
#define CHIPID_EXID_SAMV70Q19 (0x00000002ul)
#define CHIPID_EXID_SAMV70N20 (0x00000001ul)
#define CHIPID_EXID_SAMV70N19 (0x00000001ul)
#define CHIPID_EXID_SAMV70J20 (0x00000000ul)
#define CHIPID_EXID_SAMV70J19 (0x00000000ul)
#define CHIPID_EXID_SAMV71Q21 (0x00000002ul)
#define CHIPID_EXID_SAMV71Q20 (0x00000002ul)
#define CHIPID_EXID_SAMV71Q19 (0x00000002ul)
#define CHIPID_EXID_SAMV71N21 (0x00000001ul)
#define CHIPID_EXID_SAMV71N20 (0x00000001ul)
#define CHIPID_EXID_SAMV71N19 (0x00000001ul)
#define CHIPID_EXID_SAMV71J21 (0x00000000ul)
#define CHIPID_EXID_SAMV71J20 (0x00000000ul)
#define CHIPID_EXID_SAMV71J19 (0x00000000ul)

/*@}*/

/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAMV71x */
/* ************************************************************************** */
/** \addtogroup SAMV71x_id Peripheral Ids Definitions */
/*@{*/

#define ID_SUPC         ( 0) /**< \brief Supply Controller (SUPC) */
#define ID_RSTC         ( 1) /**< \brief Reset Controller (RSTC) */
#define ID_RTC          ( 2) /**< \brief Real Time Clock (RTC) */
#define ID_RTT          ( 3) /**< \brief Real Time Timer (RTT) */
#define ID_WDT          ( 4) /**< \brief Watchdog Timer (WDT) */
#define ID_PMC          ( 5) /**< \brief Power Management Controller (PMC) */
#define ID_EFC          ( 6) /**< \brief Enhanced Embedded Flash Controller (EFC) */
#define ID_UART0        ( 7) /**< \brief UART 0 (UART0) */
#define ID_UART1        ( 8) /**< \brief UART 1 (UART1) */
#define ID_SMC          ( 9) /**< \brief Static Memory Controller (SMC) */
#define ID_PIOA         (10) /**< \brief Parallel I/O Controller A (PIOA) */
#define ID_PIOB         (11) /**< \brief Parallel I/O Controller B (PIOB) */
#define ID_PIOC         (12) /**< \brief Parallel I/O Controller C (PIOC) */
#define ID_USART0       (13) /**< \brief USART 0 (USART0) */
#define ID_USART1       (14) /**< \brief USART 1 (USART1) */
#define ID_USART2       (15) /**< \brief USART 2 (USART2) */
#define ID_PIOD         (16) /**< \brief Parallel I/O Controller D (PIOD) */
#define ID_PIOE         (17) /**< \brief Parallel I/O Controller E (PIOE) */
#define ID_HSMCI0       (18) /**< \brief Multimedia Card Interface (HSMCI0) */
#define ID_TWI0         (19) /**< \brief Two Wire Interface 0 (TWI0) */
#define ID_TWI1         (20) /**< \brief Two Wire Interface 1 (TWI1) */
#define ID_SPI0         (21) /**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SSC0         (22) /**< \brief Synchronous Serial Controller (SSC0) */
#define ID_TC0          (23) /**< \brief Timer/Counter 0 (TC0) */
#define ID_TC0_CH0      (23) /**< \brief Timer/Counter 0 Channel 0 (TC0) */
#define ID_TC0_CH1      (24) /**< \brief Timer/Counter 0 Channel 1 (TC0) */
#define ID_TC0_CH2      (25) /**< \brief Timer/Counter 0 Channel 2 (TC0) */
#define ID_TC1          (26) /**< \brief Timer/Counter 1 (TC1) */
#define ID_TC1_CH0      (26) /**< \brief Timer/Counter 1 Channel 0 (TC1) */
#define ID_TC1_CH1      (27) /**< \brief Timer/Counter 1 Channel 1 (TC1) */
#define ID_TC1_CH2      (28) /**< \brief Timer/Counter 1 Channel 2 (TC1) */
#define ID_AFEC0        (29) /**< \brief Analog Front End 0 (AFEC0) */
#define ID_DACC         (30) /**< \brief Digital To Analog Converter (DACC) */
#define ID_PWM0         (31) /**< \brief Pulse Width Modulation 0 (PWM0) */
#define ID_ICM          (32) /**< \brief Integrity Check Monitor (ICM) */
#define ID_ACC          (33) /**< \brief Analog Comparator (ACC) */
#define ID_USBHS        (34) /**< \brief USB Host / Device Controller (USBHS) */
#define ID_MCAN0_INT0   (35) /**< \brief MCAN Controller 0 Interrupt 0 (MCAN0) */
#define ID_MCAN1_INT0   (37) /**< \brief MCAN Controller 1 Interrupt 0 (MCAN1) */
#define ID_GMAC0        (39) /**< \brief Ethernet MAC (GMAC0) */
#define ID_AFEC1        (40) /**< \brief Analog Front End 1 (AFEC1) */
#define ID_TWI2         (41) /**< \brief Two Wire Interface 2 (TWI2) */
#define ID_SPI1         (42) /**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_QSPI0        (43) /**< \brief Quad I/O Serial Peripheral Interface (QSPI0) */
#define ID_UART2        (44) /**< \brief UART 2 (UART2) */
#define ID_UART3        (45) /**< \brief UART 3 (UART3) */
#define ID_UART4        (46) /**< \brief UART 4 (UART4) */
#define ID_TC2          (47) /**< \brief Timer/Counter 2 (TC2) */
#define ID_TC2_CH0      (47) /**< \brief Timer/Counter 2 Channel 0 (TC2) */
#define ID_TC2_CH1      (48) /**< \brief Timer/Counter 2 Channel 1 (TC2) */
#define ID_TC2_CH2      (49) /**< \brief Timer/Counter 2 Channel 2 (TC2) */
#define ID_TC3          (50) /**< \brief Timer/Counter 3 (TC3) */
#define ID_TC3_CH0      (50) /**< \brief Timer/Counter 3 Channel 0 (TC3) */
#define ID_TC3_CH1      (51) /**< \brief Timer/Counter 3 Channel 1 (TC3) */
#define ID_TC3_CH2      (52) /**< \brief Timer/Counter 3 Channel 2 (TC3) */
#define ID_MLB          (53) /**< \brief MediaLB (MLB) */
#define ID_AES          (56) /**< \brief AES (AES) */
#define ID_TRNG         (57) /**< \brief True Random Generator (TRNG) */
#define ID_XDMAC0       (58) /**< \brief DMA (XDMAC0) */
#define ID_ISI          (59) /**< \brief Camera Interface (ISI) */
#define ID_PWM1         (60) /**< \brief Pulse Width Modulation 1 (PWM1) */
#define ID_MPDDRC       (62) /**< \brief SDRAM Controller (MPDDRC) */
#define ID_RSWDT        (63) /**< \brief Reinforced Secure Watchdog Timer (RSWDT) */
#define ID_MCAN0_INT1   (35) /**< \brief MCAN Controller 0 Interrupt 1 (MCAN0) */
#define ID_MCAN1_INT1   (37) /**< \brief MCAN Controller 1 Interrupt 1 (MCAN1) */
#define ID_GMAC0_Q1     (66) /**< \brief GMAC0 Queue 1 Interrupt (GMAC0_Q1) */
#define ID_GMAC0_Q2     (67) /**< \brief GMAC0 Queue 2 Interrupt (GMAC0_Q2) */
#define ID_I2SC0        (69) /**< \brief Inter-IC Sound Controller (I2SC0) */
#define ID_I2SC1        (70) /**< \brief Inter-IC Sound Controller (I2SC1) */
#define ID_GMAC0_Q3     (71) /**< \brief GMAC0 Queue 3 Interrupt (GMAC0_Q3) */
#define ID_GMAC0_Q4     (72) /**< \brief GMAC0 Queue 4 Interrupt (GMAC0_Q4) */
#define ID_GMAC0_Q5     (73) /**< \brief GMAC0 Queue 5 Interrupt (GMAC0_Q5) */


#define ID_PERIPH_COUNT (74) /**< \brief Number of peripheral IDs */

/*@}*/

/* ************************************************************************** */
/*   SLAVE MATRIX ID DEFINITIONS FOR SAMV71x */
/* ************************************************************************** */
/** \addtogroup SAMV71x_matrix Matrix Ids Definitions */
/*@{*/

#define MX_SLAVE_SRAM0           0    /**< Internal SRAM */
#define MX_SLAVE_SRAM1           1    /**< Internal SRAM */
#define MX_SLAVE_ROM             2    /**< Internal ROM */
#define MX_SLAVE_FLASH           3    /**< Internal Flash */
#define MX_SLAVE_USB             4    /**< USB */
#define MX_SLAVE_EBI             5    /**< External Bus Interface */
#define MX_SLAVE_QSPI            6    /**< QSPI */
#define MX_SLAVE_APB             7    /**< Peripheral Bridge */
#define MX_SLAVE_AHB             8    /**< AHB Slave */

/*@}*/

/* ************************************************************************** */
/* INCLUDE FOR SAMV71x */
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
#define TC_CHANNEL_SIZE 16

/** CAN Interface max */
#ifndef CAN_IFACE_COUNT
#define CAN_IFACE_COUNT (2)
#endif

/** TWI Interface max */
#ifndef TWI_IFACE_COUNT
#define TWI_IFACE_COUNT (3)
#endif

/** SPI Interface max */
#ifndef SPI_IFACE_COUNT
#define SPI_IFACE_COUNT (2)
#endif

/** USART Interface max */
#ifndef USART_IFACE_COUNT
#define USART_IFACE_COUNT (3)
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
#define ETH_IFACE_COUNT (GMAC_IFACE_COUNT)
#endif

/** Ethernet Queue max */
#ifndef ETH_QUEUE_COUNT
#define ETH_QUEUE_COUNT (GMAC_QUEUE_COUNT)
#endif

/** Frequency of the on-chip slow clock oscillator */
#define SLOW_CLOCK_INT_OSC 32000

/** Frequency of the on-chip main clock oscillator */
#define MAIN_CLOCK_INT_OSC 12000000

/** Clock Assignment: PCK5 - CAN */
#define PMC_PCK_CAN 5

/** Endpoints max paxcket size */
#define CHIP_USB_ENDPOINT_MAXPACKETSIZE(ep) \
   ((ep) == 0 ? 64 : 1024)

/** Endpoints Number of Bank */
#define CHIP_USB_ENDPOINT_BANKS(ep) \
   ((ep) == 0 ? 1 : ((ep) < 3 ? 3 : 2))

/** Endpoints DMA support */
#define CHIP_USB_ENDPOINT_HAS_DMA(ep) \
    ((ep) > 0 && ((ep) <= 7))

/** Endpoints High Band Width support */
#define CHIP_USB_ENDPOINT_IS_HBW(ep) \
    ((ep) > 0 && ((ep) <= 9))

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

/**
 * \brief Get the minimum number of flash wait states required for a given
 * Master Clock.
 * \param frequency the Master Clock frequency
 * \return the number of flash wait states to be programmed in EEFC
 */
extern uint8_t get_flash_wait_states(uint32_t frequency);

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

#ifdef __cplusplus
}
#endif

#endif /* _CHIP_H_ */
