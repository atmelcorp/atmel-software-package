/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
#include "compiler.h"

#include "peripherals/pmc.h"

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

struct chipid {
	uint32_t    exid; /**< EXID */
	const char* name; /**< Chip Name */
};

struct peripheral_dma {
	uint32_t id;   /**< Peripheral ID */
	uint8_t  iftx; /**< DMA Interface for TX */
	uint8_t  ifrx; /**< DMA Interface for RX */
};

struct peripheral_max_freq {
	uint32_t id;   /**< Peripheral ID */
	uint32_t freq; /**< Frequency max */
};

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct chipid _exid_names[] = {
	{ CHIPID_EXID_SAMA5D31, "SAMA5D31" },
	{ CHIPID_EXID_SAMA5D33, "SAMA5D33" },
	{ CHIPID_EXID_SAMA5D34, "SAMA5D34" },
	{ CHIPID_EXID_SAMA5D35, "SAMA5D35" },
	{ CHIPID_EXID_SAMA5D36, "SAMA5D36" },
};

static const struct peripheral_dma _dmac0_peripherals[] = {
	{ ID_HSMCI0,    0,  0 },
	{ ID_SPI0,      1,  2 },
	{ ID_USART0,    3,  4 },
	{ ID_USART1,    5,  6 },
	{ ID_TWI0,      7,  8 },
	{ ID_TWI1,      9, 10 },
	{ ID_UART0,    11, 12 },
	{ ID_SSC0,     13, 14 },
	{ ID_SMD,      15, 16 },
};

static const struct peripheral_dma _dmac1_peripherals[] = {
	{ ID_HSMCI1,    0,  0 },
	{ ID_HSMCI2,    1,  1 },
	{ ID_ADC,    0xff,  2 },
	{ ID_SSC1,      3,  4 },
	{ ID_UART1,     5,  6 },
	{ ID_USART2,    7,  8 },
	{ ID_USART3,    9, 10 },
	{ ID_TWI2,     11, 12 },
	{ ID_DBGU,     13, 14 },
	{ ID_SPI1,     15, 16 },
	{ ID_SHA,      17, 0xff },
	{ ID_AES,      18, 19 },
	{ ID_TDES,     20, 21 },
};

/** max peripheral frequency */
static const struct peripheral_max_freq _peripheral_clock_max_freq[] = {
	{ ID_SMD,     24000000 },
	{ ID_USART0,  66000000 },
	{ ID_USART1,  66000000 },
	{ ID_USART2,  66000000 },
	{ ID_USART3,  66000000 },
	{ ID_UART0,   66000000 },
	{ ID_UART1,   66000000 },
	{ ID_TWI0,    33000000 },
	{ ID_TWI1,    33000000 },
	{ ID_TWI2,    33000000 },
	{ ID_SPI0,   133000000 },
	{ ID_SPI1,   133000000 },
	{ ID_TC0,     66000000 },
	{ ID_TC1,     66000000 },
	{ ID_ADC,     66000000 },
	{ ID_SSC0,    66000000 },
	{ ID_SSC1,    66000000 },
	{ ID_CAN0,    66000000 },
	{ ID_CAN1,    66000000 },
};

/* must be sorted by peripheral ID */
static const uint32_t _div_peripherals[] = {
	ID_USART0, ID_USART1, ID_USART2, ID_USART3, ID_UART0, ID_UART1,
	ID_TWI0, ID_TWI1, ID_TWI2, ID_SPI0, ID_SPI1, ID_TC0, ID_TC1, ID_ADC,
	ID_SSC0, ID_SSC1, ID_CAN0, ID_CAN1
};

/*----------------------------------------------------------------------------
 *        Private functions
 *----------------------------------------------------------------------------*/

static const struct peripheral_dma *get_peripheral_dma(uint32_t id, Dmac *dmac)
{
	const struct peripheral_dma *_dmac_peripherals;
	int count, i;

	if (dmac == DMAC0) {
		_dmac_peripherals = _dmac0_peripherals;
		count = ARRAY_SIZE(_dmac0_peripherals);
	} else if (dmac == DMAC1) {
		_dmac_peripherals = _dmac1_peripherals;
		count = ARRAY_SIZE(_dmac1_peripherals);
	} else {
		return NULL;
	}

	for (i = 0; i < count; i++) {
		if (_dmac_peripherals[i].id == id) {
			return &_dmac_peripherals[i];
		}
	}

	return NULL;
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

const char* get_chip_name(void)
{
	int i;

	if ((DBGU->DBGU_CIDR & ~DBGU_CIDR_VERSION_Msk) ==
			CHIPID_CIDR_SAMA5D3) {
		uint32_t exid = DBGU->DBGU_EXID;
		for (i = 0; i < ARRAY_SIZE(_exid_names); i++) {
			if (_exid_names[i].exid == exid)
				return _exid_names[i].name;
		}
	}

	return "Unknown";
}

uint32_t get_can_id_from_addr(const Can* addr)
{
	if (addr == (void*)CAN0) return ID_CAN0; /**< \brief CAN 0 (CAN0) */
#ifdef CAN1
	else if (addr == (void*)CAN1) return ID_CAN1; /**< \brief CAN 1 (CAN1) */
#endif
	else return ID_PERIPH_COUNT;
}

Can* get_can_addr_from_id(const uint32_t id)
{
	if (id == ID_CAN0) return CAN0; /**< \brief CAN 0 */
#ifdef CAN1
	else if (id == ID_CAN1) return CAN1; /**< \brief CAN 1 (CAN1) */
#endif
	else return (void*)0;
}

uint32_t get_twi_id_from_addr(const Twi* addr)
{
	if (addr == (void*)TWI0) return ID_TWI0; /**< \brief TWI 0 (TWI0) */
#ifdef TWI1
	else if (addr == (void*)TWI1) return ID_TWI1; /**< \brief TWI 1 (TWI1) */
#endif
#ifdef TWI2
	else if (addr == (void*)TWI2) return ID_TWI2; /**< \brief TWI 2 (TWI2) */
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
	else return (void*)0;
}

uint32_t get_spi_id_from_addr(const Spi* addr)
{
	if (addr == (void*)SPI0) return ID_SPI0;
#ifdef SPI1
	else if (addr == (void*)SPI1) return ID_SPI1;
#endif
	else return ID_PERIPH_COUNT;
}

Spi* get_spi_addr_from_id(const uint32_t id)
{
	if (id == ID_SPI0) return SPI0; /**< \brief SPI 0 (SPI0) */
#ifdef SPI1
	else if (id == ID_SPI1) return SPI1; /**< \brief SPI 1 (SPI1) */
#endif
	else return (void*)0;
}

uint32_t get_pwm_id_from_addr(const Pwm* addr)
{
	if (addr == (void*)PWM0) return ID_PWM0;
	else return ID_PERIPH_COUNT;
}

Pwm* get_pwm_addr_from_id(const uint32_t id)
{
	if (id == ID_PWM0) return PWM0;
	else return (void*)0;
}

uint32_t get_uart_id_from_addr(const Uart* addr)
{
	if (addr == (void*)UART0) return ID_UART0;
#ifdef UART1
	else if (addr == (void*)UART1) return ID_UART1;
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
	else return ID_PERIPH_COUNT;
}

Usart* get_usart_addr_from_id(uint32_t id)
{
	if (id == ID_USART0)
		return USART0;
#ifdef USART1
	else if (id == ID_USART1)
		return USART1;
#endif
#ifdef USART2
	else if (id == ID_USART2)
		return USART2;
#endif
#ifdef USART3
	else if (id == ID_USART3)
		return USART3;
#endif
	else
		return (void*)0;
}

uint32_t get_tc_id_from_addr(const Tc* addr)
{
	if (addr == TC0) return ID_TC0;
#ifdef TC1
	else if (addr == TC1) return ID_TC1;
#endif
	else return ID_PERIPH_COUNT;
}

Tc* get_tc_addr_from_id(const uint32_t id)
{
	if (id == ID_TC0) return TC0; /**< \brief Timer/Counter 0 (TC0) */
#ifdef TC1
	else if (id == ID_TC1) return TC1; /**< \brief Timer/Counter 1 (TC1) */
#endif
	else return (void*)0;
}

uint32_t get_tc_interrupt(uint32_t tc_id, uint8_t channel)
{
	return tc_id;
}

uint32_t get_hsmci_id_from_addr(const Hsmci* addr)
{
#ifdef HSMCI0
	if (addr == HSMCI0)
		return ID_HSMCI0;
#endif
#ifdef HSMCI1
	if (addr == HSMCI1)
		return ID_HSMCI1;
#endif
	return ID_PERIPH_COUNT;
}

Hsmci* get_hsmci_addr_from_id(uint32_t id)
{
#ifdef HSMCI0
	if (id == ID_HSMCI0)
		return HSMCI0;
#endif
#ifdef HSMCI1
	if (id == ID_HSMCI1)
		return HSMCI1;
#endif
	return (void*)0;
}

uint32_t get_ssc_id_from_addr(const Ssc* addr)
{
	if (addr == SSC0)
		return ID_SSC0;
#ifdef ID_SSC1
	else if (addr == SSC1)
		return ID_SSC1;
#endif
	else
		return ID_PERIPH_COUNT;
}

uint32_t get_ebi_addr_from_cs(uint32_t cs)
{
	switch (cs) {
	case 0:
		return EBI_CS0_ADDR;
	case 1:
		return EBI_CS1_ADDR;
	case 2:
		return EBI_CS2_ADDR;
	case 3:
		return EBI_CS3_ADDR;
	default:
		return 0;
	}
}

uint32_t get_gmac_id_from_addr(const Gmac* addr)
{
	if (addr == GMAC0) return ID_GMAC0;
	else return ID_PERIPH_COUNT;
}

uint32_t get_emac_id_from_addr(const Emac* addr)
{
	if (addr == EMAC0) return ID_EMAC0;
	else return ID_PERIPH_COUNT;
}

Matrix* get_peripheral_matrix(uint32_t id)
{
	return MATRIX; // AHB 32-bit matrix
}

uint32_t get_peripheral_clock_matrix_div(uint32_t id)
{
	return 1;
}

uint32_t get_peripheral_clock_max_freq(uint32_t id)
{
	uint8_t i;
	
	for (i = 0 ; i < ARRAY_SIZE(_peripheral_clock_max_freq) ; i++)
		if (_peripheral_clock_max_freq[i].id == id)
			return _peripheral_clock_max_freq[i].freq;
	return pmc_get_master_clock();
}

bool peripheral_has_clock_div(uint32_t id)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(_div_peripherals) && _div_peripherals[i] <= id; i++)
		if (_div_peripherals[i] == id)
			return true;
	return false;
}

uint32_t get_dmac_id_from_addr(const Dmac* addr)
{
#ifdef DMAC0
	if (addr == DMAC0)
		return ID_DMAC0;
#endif
#ifdef DMAC1
	if (addr == DMAC1)
		return ID_DMAC1;
#endif
	return ID_PERIPH_COUNT;
}

Dmac* get_dmac_addr_from_id(uint32_t id)
{
#ifdef DMAC0
	if (id == ID_DMAC0)
		return DMAC0;
#endif
#ifdef DMAC1
	if (id == ID_DMAC1)
		return DMAC1;
#endif
	return (void*)0;
}

uint8_t get_peripheral_dma_channel(uint32_t id, Dmac *dmac, bool transmit)
{
	const struct peripheral_dma *periph_dma = get_peripheral_dma(id, dmac);
	if (periph_dma) {
		return transmit ? periph_dma->iftx : periph_dma->ifrx;
	} else {
		return 0xff;
	}
}

bool is_peripheral_on_dma_controller(uint32_t id, Dmac *dmac)
{
	return get_peripheral_dma(id, dmac) != NULL;
}
