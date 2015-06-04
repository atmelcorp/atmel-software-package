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

#ifndef _SAMA5D4_
#define _SAMA5D4_

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

#if defined(CONFIG_SOC_SAMA5D41)
  #include "sama5d41.h"
#elif defined(CONFIG_SOC_SAMA5D42)
  #include "sama5d42.h"
#elif defined(CONFIG_SOC_SAMA5D43)
  #include "sama5d43.h"
#elif defined(CONFIG_SOC_SAMA5D44)
  #include "sama5d44.h"
#else
  #error Library does not support the specified device.
#endif

/**
 * \brief retrieve TWI ID from its base address
 * \return TWI ID on success, ID_PERIPH_COUNT otherwise
 */
static inline uint32_t get_twi_id_from_addr(const Twi* addr)
{
	if (addr == (void*)TWI0) return ID_TWI0; /**< \brief TWI 0 (TWI0) */
#ifdef TWI1
	else if (addr == (void*)TWI1) return ID_TWI1; /**< \brief TWI 1 (TWI1) */
#endif
#ifdef TWI2
	else if (addr == (void*)TWI2) return ID_TWI2; /**< \brief TWI 2 (TWI2) */
#endif
#ifdef TWI3
	else if (addr == (void*)TWI3) return ID_TWI3; /**< \brief TWI 3 (TWI3) */
#endif
#ifdef TWI4
	else if (addr == (void*)TWI4) return ID_TWI4; /**< \brief TWI 4 (TWI4) */
#endif
	else return ID_PERIPH_COUNT;
}

/**
 * \brief retrieve TWI base address from its ID
 * \return TWI base address on success, 0 otherwise
 */
static inline Twi* get_twi_addr_from_id(const uint32_t id)
{
	if (id == ID_TWI0) return TWI0; /**< \brief TWI 0 */
#ifdef TWI1
	else if (id == ID_TWI1) return TWI1; /**< \brief TWI 1 (TWI1) */
#endif
#ifdef TWI2
	else if (id == ID_TWI2) return TWI2; /**< \brief TWI 2 (TWI2) */
#endif
#ifdef TWI3
	else if (id == ID_TWI3) return TWI3; /**< \brief TWI 3 (TWI3) */
#endif
#ifdef TWI4
	else if (id == ID_TWI4) return TWI4; /**< \brief TWI 4 (TWI4) */
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
#ifdef SPI2
	else if (addr == (void*)SPI2) return ID_SPI2;
#endif
	else return ID_PERIPH_COUNT;
}

static inline Spi* get_spi_addr_from_id(const uint32_t id)
{
	if (id == ID_SPI0) return SPI0; /**< \brief SPI 0 (SPI0) */
#ifdef SPI1
	else if (id == ID_SPI1) return SPI1; /**< \brief SPI 1 (SPI1) */
#endif
#ifdef SPI2
	else if (id == ID_SPI2) return SPI2; /**< \brief SPI 0 (SPI2) */
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
#ifdef TC2
	else if (addr == TC2) return ID_TC2;
#endif
	else return ID_PERIPH_COUNT;
}

static inline uint32_t get_peripheral_clock_divider(uint32_t id)
{
	switch (id) {
		case ID_PIT:
		case ID_WDT:
		case ID_PIOD:
		case ID_USART0:
		case ID_USART1:
		case ID_ICM:
		case ID_AES:
		case ID_TDES:
		case ID_SHA:
		case ID_HSMC:
		case ID_PIOA:
		case ID_PIOB:
		case ID_PIOC:
		case ID_PIOE:
		case ID_UART0:
		case ID_UART1:
		case ID_USART2:
		case ID_USART3:
		case ID_USART4:
		case ID_TWI0:
		case ID_TWI1:
		case ID_TWI2:
		case ID_HSMCI0:
		case ID_HSMCI1:
		case ID_SPI0:
		case ID_SPI1:
		case ID_SPI2:
		case ID_TC0:
		case ID_TC1:
		case ID_TC2:
		case ID_PWM:
		case ID_ADC:
		case ID_DBGU:
		case ID_UHPHS:
		case ID_UDPHS:
		case ID_SSC0:
		case ID_SSC1:
		case ID_TRNG:
		case ID_GMAC0:
		case ID_GMAC1:
		case ID_IRQ:
		case ID_SFC:
		case ID_TWI3:
			return 2; // MCK/2

		case ID_XDMAC0:
		case ID_AESB:
		case ID_MPDDRC:
		case ID_XDMAC1:
		case ID_LCDC:
		case ID_ISI:
			return 1; // MCK

		default:
			return 0; // N/A
	}
}

/** Frequency of the on-chip slow clock oscillator */
#define SLOW_CLOCK_INT_OSC 32000

/** Frequency of the on-chip main clock oscillator */
#define MAIN_CLOCK_INT_OSC 12000000

#endif /* _SAMA5D4_ */
