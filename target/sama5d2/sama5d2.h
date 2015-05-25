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

#ifndef _SAMA5D2_
#define _SAMA5D2_

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
#include <stdint.h>
#ifdef __cplusplus
#define __I  volatile	    /**< Defines 'read-only'  permissions */
#else
#define __I  volatile const /**< Defines 'read-only'  permissions */
#endif
#define   __O  volatile	      /**< Defines 'write-only' permissions */
#define   __IO volatile	      /**< Defines 'read/write' permissions */
#endif


/* ************************************************************************** */
/*   PERIPHERAL ID DEFINITIONS FOR SAMA5D2x */
/* ************************************************************************** */
/** \addtogroup SAMA5D2x_id Peripheral Ids Definitions */
/*@{*/

#define ID_SAIC_FIQ       ( 0) /**< \brief FIQ Interrupt ID (SAIC_FIQ) */
#define ID_PMC            ( 1) /**< \brief System Controller Interrupt (PMC) */
#define ID_ARM_PMU        ( 2) /**< \brief Performance Monitor Unit (PMU) (ARM_PMU) */
#define ID_PIT            ( 3) /**< \brief Periodic Interval Timer Interrupt (PIT) */
#define ID_WDT            ( 4) /**< \brief Watchdog timer Interrupt (WDT) */
#define ID_GMAC           ( 5) /**< \brief Ethernet MAC (GMAC) */
#define ID_XDMAC0         ( 6) /**< \brief DMA Controller 0 (XDMAC0) */
#define ID_XDMAC1         ( 7) /**< \brief DMA Controller 1 (XDMAC1) */
#define ID_ICM            ( 8) /**< \brief Integritry Check Monitor (ICM) */
#define ID_AES            ( 9) /**< \brief Advanced Enion Standard (AES) */
#define ID_AESB           (10) /**< \brief AES bridge (AESB) */
#define ID_TDES           (11) /**< \brief Triple Data Enion Standard (TDES) */
#define ID_SHA            (12) /**< \brief SHA Signature (SHA) */
#define ID_MPDDRC         (13) /**< \brief MPDDR controller (MPDDRC) */
#define ID_MATRIX1        (14) /**< \brief H32MX, 32-bit AHB Matrix (MATRIX1) */
#define ID_MATRIX0        (15) /**< \brief H64MX, 64-bit AHB Matrix (MATRIX0) */
#define ID_HSMC           (17) /**< \brief Multi-bit ECC Interrupt (HSMC) */
#define ID_PIOA           (18) /**< \brief Parallel I/O Controller (PIOA) */
#define ID_FLEXCOM0       (19) /**< \brief FLEXCOM 0 (FLEXCOM0) */
#define ID_USART0         (19) /**< \brief USART (USART0) from FLEXCOM0 */
#define ID_FCOMSPI0       (19) /**< \brief Serial Peripheral Interface (SPI0) from FLEXCOM0 */
#define ID_TWI0           (19) /**< \brief Two-Wire Interface (TWI0) from FLEXCOM0 */
#define ID_FLEXCOM1       (20) /**< \brief FLEXCOM 1 (FLEXCOM1) */
#define ID_USART1         (20) /**< \brief USART (USART1) from FLEXCOM1 */
#define ID_FCOMSPI1       (20) /**< \brief Serial Peripheral Interface (SPI1) from FLEXCOM1 */
#define ID_TWI1           (20) /**< \brief Two-Wire Interface (TWI1) from FLEXCOM1 */
#define ID_FLEXCOM2       (21) /**< \brief FLEXCOM 1 (FLEXCOM1) */
#define ID_USART2         (21) /**< \brief USART (USART1) from FLEXCOM1 */
#define ID_FCOMSPI2       (21) /**< \brief Serial Peripheral Interface (SPI1) from FLEXCOM1 */
#define ID_TWI2           (21) /**< \brief Two-Wire Interface (TWI1) from FLEXCOM1 */
#define ID_FLEXCOM3       (22) /**< \brief FLEXCOM 3 (FLEXCOM3) */
#define ID_USART3         (22) /**< \brief USART (USART3) from FLEXCOM3 */
#define ID_FCOMSPI3       (22) /**< \brief Serial Peripheral Interface (SPI3) from FLEXCOM3 */
#define ID_TWI3           (22) /**< \brief Two-Wire Interface (TWI3) from FLEXCOM3 */
#define ID_FLEXCOM4       (23) /**< \brief FLEXCOM 4 (FLEXCOM4) */
#define ID_USART4         (23) /**< \brief USART (USART4) from FLEXCOM4 */
#define ID_FCOMSPI4       (23) /**< \brief Serial Peripheral Interface (SPI4) from FLEXCOM4 */
#define ID_TWI4           (23) /**< \brief Two-Wire Interface (TWI4) from FLEXCOM4 */
#define ID_UART0          (24) /**< \brief UART 0 (UART0) */
#define ID_UART1          (25) /**< \brief UART 1 (UART1) */
#define ID_UART2          (26) /**< \brief UART 2 (UART2) */
#define ID_UART3          (27) /**< \brief UART 3 (UART3) */
#define ID_UART4          (28) /**< \brief UART 4 (UART4) */
#define ID_TWIHS0         (29) /**< \brief Two-Wire Interface 0 (TWIHS0) */
#define ID_TWIHS1         (30) /**< \brief Two-Wire Interface 1 (TWIHS1) */
#define ID_SDHC0          (31) /**< \brief Ultra High Speed SD Host Controller 0 (SDHC0) */
#define ID_SDHC1          (32) /**< \brief Ultra High Speed SD Host Controller 1 (SDHC1) */
#define ID_SPI0           (33) /**< \brief Serial Peripheral Interface 0 (SPI0) */
#define ID_SPI1           (34) /**< \brief Serial Peripheral Interface 1 (SPI1) */
#define ID_TC0            (35) /**< \brief Timer Counter 0 (ch. 0, 1, 2) (TC0) */
#define ID_TC1            (36) /**< \brief Timer Counter 1 (ch. 3, 4, 5) (TC1) */
#define ID_PWM            (38) /**< \brief Pulse Width Modulation Controller0 (ch. 0, 1, 2, 3) (PWM) */
#define ID_ADC            (40) /**< \brief Touch Screen ADC Controller (ADC) */
#define ID_UHPHS          (41) /**< \brief USB Host High Speed (UHPHS) */
#define ID_UDPHS          (42) /**< \brief USB Device High Speed (UDPHS) */
#define ID_SSC0           (43) /**< \brief Synchronous Serial Controller 0 (SSC0) */
#define ID_SSC1           (44) /**< \brief Synchronous Serial Controller 1 (SSC1) */
#define ID_LCDC           (45) /**< \brief LCD Controller (LCDC) */
#define ID_ISC            (46) /**< \brief Camera Interface (ISC) */
#define ID_TRNG           (47) /**< \brief True Random Number Generator (TRNG) */
#define ID_PDMIC          (48) /**< \brief Pulse Density Modulation Interface Controller (PDMIC) */
#define ID_AIC_IRQ        (49) /**< \brief IRQ Interrupt ID (AIC_IRQ) */
#define ID_SFC            (50) /**< \brief Fuse Controller (SFC) */
#define ID_SECURAM        (51) /**< \brief Secured RAM (SECURAM) */
#define ID_QSPI0          (52) /**< \brief QSPI 0 (QSPI0) */
#define ID_QSPI1          (53) /**< \brief QSPI 1 (QSPI1) */
#define ID_I2SC0          (54) /**< \brief Inter-IC Sound Controller 0 (I2SC0) */
#define ID_I2SC1          (55) /**< \brief Inter-IC Sound Controller 1 (I2SC1) */
#define ID_CAN0_INT0      (56) /**< \brief MCAN 0 Interrupt0 (CAN0_INT0) */
#define ID_CAN1_INT0      (57) /**< \brief MCAN 1 Interrupt0 (CAN1_INT0) */
#define ID_CLASSD         (59) /**< \brief Audio Class D amplifier (CLASSD) */
#define ID_SFR            (60) /**< \brief Special Function Register  (SFR) */
#define ID_SAIC           (61) /**< \brief Secured Advanced Interrupt Controller  (SAIC) */
#define ID_AIC            (62) /**< \brief Advanced Interrupt Controller  (AIC) */
#define ID_L2CC           (63) /**< \brief L2 Cache Controller (L2CC) */
#define ID_CAN0_INT1      (64) /**< \brief MCAN 0 Interrupt1 (CAN0_INT1) */
#define ID_CAN1_INT1      (65) /**< \brief MCAN 1 Interrupt1 (CAN1_INT1) */
#define ID_GMAC_Q1        (66) /**< \brief GMAC Queue 1 Interrupt (GMAC_Q1) */
#define ID_GMAC_Q2        (67) /**< \brief GMAC Queue 2 Interrupt (GMAC_Q2) */
#define ID_PIOB           (68) /**< \brief  (PIOB) */
#define ID_PIOC           (69) /**< \brief  (PIOC) */
#define ID_PIOD           (70) /**< \brief  (PIOD) */
#define ID_SDHC0_TIMER    (71) /**< \brief  (SDHC0_TIMER) */
#define ID_RSTC           (73) /**< \brief System Controller Interrupt (RSTC) */
#define ID_RTC            (74) /**< \brief System Controller Interrupt (RTC) */
#define ID_ACC            (75) /**< \brief Analog Comparator (ACC) */
#define ID_RXLP           (76) /**< \brief Uart Low Power (RXLP) */
#define ID_CHIPID         (78) /**< \brief Chip ID (CHIPID) */

#define ID_PERIPH_COUNT   (79) /**< \brief Number of peripheral IDs */
/*@}*/

/* ************************************************************************** */
/* INCLUDE FOR SAMA5D2x */
/* ************************************************************************** */

#if defined CHIP_SAMA5D21
  #include "sama5d21.h"
#elif defined CHIP_SAMA5D22
  #include "sama5d22.h"
#elif defined CHIP_SAMA5D23
  #include "sama5d23.h"
#elif defined CHIP_SAMA5D24
  #include "sama5d24.h"
#elif defined CHIP_SAMA5D26
  #include "sama5d26.h"
#elif defined CHIP_SAMA5D27
  #include "sama5d27.h"
#elif defined CHIP_SAMA5D28
  #include "sama5d28.h"
#else
  #error Library does not support the specified device.
#endif

/**
 * \brief retrieve Flexcom base address from its ID
 * \return Flexcom base address on success, 0 otherwise
 */
static inline Flexcom* get_flexcom_addr_from_id(const uint32_t id)
{
	if (id == ID_FLEXCOM0) return FLEXCOM0; /**< \brief FLEXCOM 0 (FLEXCOM0) */
#ifdef FLEXCOM1
	else if (id == ID_FLEXCOM1) return FLEXCOM1; /**< \brief FLEXCOM 1 (FLEXCOM1) */
#endif
#ifdef FLEXCOM2
	else if (id == ID_FLEXCOM2) return FLEXCOM2; /**< \brief FLEXCOM 2 (FLEXCOM2) */
#endif
#ifdef FLEXCOM3
	else if (id == ID_FLEXCOM3) return FLEXCOM3; /**< \brief FLEXCOM 3 (FLEXCOM3) */
#endif
#ifdef FLEXCOM4
	else if (id == ID_FLEXCOM4) return FLEXCOM4; /**< \brief FLEXCOM 4 (FLEXCOM4) */
#endif
	else return (void*)0;
}


/**
 * \brief retrieve TWI ID from its base address
 * \return TWI ID on success, ID_PERIPH_COUNT otherwise
 */
static inline uint32_t get_twi_id_from_addr(const Twi* addr)
{
	if (addr == (void*)TWI0) return ID_FLEXCOM0; /**< \brief FLEXCOM 0 (FLEXCOM0) */
#ifdef TWI1
	else if (addr == (void*)TWI1) return ID_FLEXCOM1; /**< \brief FLEXCOM 1 (FLEXCOM1) */
#endif
#ifdef TWI2
	else if (addr == (void*)TWI2) return ID_FLEXCOM2; /**< \brief FLEXCOM 2 (FLEXCOM2) */
#endif
#ifdef TWI3
	else if (addr == (void*)TWI3) return ID_FLEXCOM3; /**< \brief FLEXCOM 3 (FLEXCOM3) */
#endif
#ifdef TWI4
	else if (addr == (void*)TWI4) return ID_FLEXCOM4; /**< \brief FLEXCOM 4 (FLEXCOM4) */
#endif
#ifdef TWIHS0
	else if (addr == (void*)TWIHS0) return ID_TWIHS0; /**< \brief TWIHS0 */
#endif
#ifdef TWIHS0
	else if (addr == (void*)TWIHS1) return ID_TWIHS1; /**< \brief TWIHS1 */
#endif
	else return ID_PERIPH_COUNT;
}

/**
 * \brief retrieve TWI base address from its ID
 * \return TWI base address on success, 0 otherwise
 */
static inline Twi* get_twi_addr_from_id(const uint32_t id)
{
	if (id == ID_FLEXCOM0) return TWI0; /**< \brief FLEXCOM 0 (FLEXCOM0) */
#ifdef TWI1
	else if (id == ID_FLEXCOM1) return TWI1; /**< \brief FLEXCOM 1 (FLEXCOM1) */
#endif
#ifdef TWI2
	else if (id == ID_FLEXCOM2) return TWI2; /**< \brief FLEXCOM 2 (FLEXCOM2) */
#endif
#ifdef TWI3
	else if (id == ID_FLEXCOM3) return TWI3; /**< \brief FLEXCOM 3 (FLEXCOM3) */
#endif
#ifdef TWI4
	else if (id == ID_FLEXCOM4) return TWI4; /**< \brief FLEXCOM 4 (FLEXCOM4) */
#endif
#ifdef TWIHS0
	else if (id == ID_TWIHS0) return (Twi*)TWIHS0; /**< \brief TWIHS0 */
#endif
#ifdef TWIHS1
	else if (id == ID_TWIHS1) return (Twi*)TWIHS1; /**< \brief TWIHS1 */
#endif
	else return (void*)0;
}

/**
 *
 */
static inline uint32_t get_spi_id_from_addr(const Spi* addr)
{
	if (addr == (void*)SPI0) return ID_SPI0;
#ifdef SPI1
	else if (addr == (void*)SPI1) return ID_SPI1;
#endif
#ifdef FCOMSPI0
	else if (addr == (void*)FCOMSPI0) return ID_FCOMSPI0;
#endif
#ifdef FCOMSPI1
	else if (addr == (void*)FCOMSPI1) return ID_FCOMSPI1;
#endif
#ifdef FCOMSPI2
	else if (addr == (void*)FCOMSPI2) return ID_FCOMSPI2;
#endif
#ifdef FCOMSPI3
	else if (addr == (void*)FCOMSPI3) return ID_FCOMSPI3;
#endif
#ifdef FCOMSPI4
	else if (addr == (void*)FCOMSPI4) return ID_FCOMSPI4;
#endif
	else return ID_PERIPH_COUNT;
}

static inline void* get_spi_addr_from_id(const uint32_t id)
{
	if (id == ID_SPI0) return SPI0; /**< \brief SPI 0 (SPI0) */
#ifdef SPI1
	else if (id == ID_SPI1) return SPI1; /**< \brief SPI 1 (SPI1) */
#endif
#ifdef  FCOMSPI0
	else if (id == ID_FCOMSPI0) return FCOMSPI0; /**< \brief FLEXCOM SPI 0 (FCOMSPI0) */
#endif
#ifdef  FCOMSPI1
	else if (id == ID_FCOMSPI1) return FCOMSPI1; /**< \brief FLEXCOM SPI 1 (FCOMSPI1) */
#endif
#ifdef  FCOMSPI2
	else if (id == ID_FCOMSPI2) return FCOMSPI2; /**< \brief FLEXCOM SPI 1 (FCOMSPI1) */
#endif
#ifdef  FCOMSPI3
	else if (id == ID_FCOMSPI3) return FCOMSPI3; /**< \brief FLEXCOM SPI 3 (FCOMSPI3) */
#endif
#ifdef  FCOMSPI4
	else if (id == ID_FCOMSPI4) return FCOMSPI4; /**< \brief FLEXCOM SPI 4 (FCOMSPI4) */
#endif
	else return (void*)0;
}

static inline uint32_t get_uart_id_from_addr(const Uart* addr)
{
	if (addr == (void*)UART0) return ID_UART0;
#ifdef UART1
	else if (addr == (void*)UART1) return ID_UART1;
#endif
#ifdef UART2
	else if (addr == (void*)UART2) return ID_UART2;
#endif
#ifdef UART3
	else if (addr == (void*)UART3) return ID_UART3;
#endif
#ifdef UART4
	else if (addr == (void*)UART4) return ID_UART4;
#endif
	else return ID_PERIPH_COUNT;
}

static inline uint32_t get_usart_id_from_addr(const Usart* addr)
{
	if (addr == (void*)USART0) return ID_USART0;
#ifdef USART1
	else if (addr == (void*)USART1) return ID_USART1;
#endif
#ifdef USART2
	else if (addr == (void*)USART2) return ID_USART2;
#endif
#ifdef USART3
	else if (addr == (void*)USART3) return ID_USART3;
#endif
#ifdef USART4
	else if (addr == (void*)USART4) return ID_USART4;
#endif
	else return ID_PERIPH_COUNT;
}

static inline uint32_t get_tc_id_from_addr(const Tc* addr)
{
	if (addr == TC0) return ID_TC0;
#ifdef TC1
	else if (addr == TC1) return ID_TC1;
#endif
	else return ID_PERIPH_COUNT;
}

static inline uint32_t get_peripheral_clock_divider(uint32_t id)
{
	switch (id) {
		case ID_PMC:
		case ID_PIT:
		case ID_WDT:
		case ID_GMAC:
		case ID_ICM:
		case ID_MATRIX1:
		case ID_TDES:
		case ID_HSMC:
		case ID_PIOA:
		case ID_FLEXCOM0:
		case ID_FLEXCOM1:
		case ID_FLEXCOM2:
		case ID_FLEXCOM3:
		case ID_FLEXCOM4:
		case ID_UART0:
		case ID_UART1:
		case ID_UART2:
		case ID_UART3:
		case ID_UART4:
		case ID_TWIHS0:
		case ID_TWIHS1:
		case ID_SPI0:
		case ID_SPI1:
		case ID_TC0:
		case ID_TC1:
		case ID_PWM:
		case ID_ADC:
		case ID_UHPHS:
		case ID_UDPHS:
		case ID_SSC0:
		case ID_SSC1:
		case ID_TRNG:
		case ID_PDMIC:
		case ID_AIC_IRQ:
		case ID_SFC:
		case ID_SECURAM:
		case ID_I2SC0:
		case ID_I2SC1:
		case ID_CAN0_INT0:
		case ID_CAN1_INT0:
		case ID_SAIC:
		case ID_AIC:
		case ID_CAN0_INT1:
		case ID_CAN1_INT1:
		case ID_RSTC:
		case ID_RTC:
		case ID_ACC:
		case ID_RXLP:
			return 2; // MCK/2

		case ID_XDMAC0:
		case ID_XDMAC1:
		case ID_AES:
		case ID_AESB:
		case ID_SHA:
		case ID_MPDDRC:
		case ID_MATRIX0:
		case ID_SDHC0:
		case ID_SDHC1:
		case ID_LCDC:
		case ID_ISC:
		case ID_QSPI0:
		case ID_QSPI1:
			return 1; // MCK

		default:
			return 0; // N/A
	}
}

#endif /* _SAMA5D2_ */
