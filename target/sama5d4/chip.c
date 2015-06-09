/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const uint8_t _h64_peripherals[] = {
	ID_ARM,     /* 2: Performance Monitor Unit (ARM) */
	ID_XDMAC0,  /* 8: DMA Controller 0 (XDMAC0) */
	ID_CPKCC,   /* 10: Classic Public Key Crypto Controller (CPKCC) */
	ID_AESB,    /* 13: AES bridge (AESB) */
	ID_MPDDRC,  /* 16: MPDDR controller (MPDDRC) */
	ID_MATRIX0, /* 18: H64MX, 64-bit AHB Matrix (MATRIX0) */
	ID_VDEC,    /* 19: Video Decoder (VDEC) */
	ID_XDMAC1,  /* 50: DMA Controller 1 (XDMAC1) */
	ID_LCDC,    /* 51: LCD Controller (LCDC) */
	ID_ISI,     /* 52: Camera Interface (ISI) */
	ID_L2CC,    /* 67: L2 Cache Controller  (L2CC) */
};

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

uint32_t get_twi_id_from_addr(const Twi* addr)
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

Twi* get_twi_addr_from_id(const uint32_t id)
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

uint32_t get_spi_id_from_addr(const Spi* addr)
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

Spi* get_spi_addr_from_id(const uint32_t id)
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

uint32_t get_uart_id_from_addr(const Uart* addr)
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

uint32_t get_usart_id_from_addr(const Usart* addr)
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

uint32_t get_tc_id_from_addr(const Tc* addr)
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

Matrix* get_peripheral_matrix(uint32_t id)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(_h64_peripherals); i++)
		if (_h64_peripherals[i] == id)
			return MATRIX0; // AHB 64-bit matrix
	return MATRIX1; // AHB 32-bit matrix
}

uint32_t get_peripheral_clock_divider(uint32_t id)
{
	Matrix* matrix = get_peripheral_matrix(id);

	if (matrix == MATRIX1) {
		if (PMC->PMC_MCKR & PMC_MCKR_H32MXDIV_H32MXDIV2)
			return 2;
		else
			return 1;
	}

	return 1;
}
