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

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct chipid _exid_names[] = {
	{ CHIPID_EXID_SAM9G15, "SAM9G15" },
	{ CHIPID_EXID_SAM9G25, "SAM9G25" },
	{ CHIPID_EXID_SAM9G35, "SAM9G35" },
	{ CHIPID_EXID_SAM9X35, "SAM9X35" },
	{ CHIPID_EXID_SAM9X25, "SAM9X25" },
};

static const struct peripheral_dma _dmac0_peripherals[] = {
	{ ID_HSMCI0,      0,    0 },
	{ ID_SPI0,        1,    2 },
	{ ID_USART0,      3,    4 },
	{ ID_USART1,      5,    6 },
	{ ID_TWI0,        7,    8 },
	{ ID_TWI2,        9,   10 },
	{ ID_UART0,      11,   12 },
	{ ID_SSC0,       13,   14 },
};

static const struct peripheral_dma _dmac1_peripherals[] = {
	{ ID_HSMCI1,      0,    0 },
	{ ID_SPI1,        1,    2 },
	{ ID_SMD,         3,    4 },
	{ ID_TWI1,        5,    6 },
	{ ID_ADC,      0xff,    7 },
	{ ID_DBGU,        8,    9 },
	{ ID_UART1,      10,   11 },
	{ ID_USART2,     12,   13 },
};

/* must be sorted by peripheral ID */
static const uint32_t _div_peripherals[] = {
	ID_PIOA, ID_PIOC, ID_USART0, ID_USART1, ID_USART2, ID_TWI0, ID_TWI1,
	ID_TWI2, ID_SPI0, ID_SPI1, ID_UART0, ID_UART1, ID_TC0, ID_TC1, ID_PWM0,
	ID_ADC, ID_SSC0,
#ifdef CONFIG_HAVE_CAN
	ID_CAN0, ID_CAN1
#endif
};

/*----------------------------------------------------------------------------
 *        Private functions
 *----------------------------------------------------------------------------*/

static const struct peripheral_dma *get_peripheral_dma(uint32_t id, Dmac *dmac)
{
	const struct peripheral_dma *dmac_peripherals;
	int dmac_peripherals_count;
	int i;

	if (dmac == DMAC0) {
		dmac_peripherals = _dmac0_peripherals;
		dmac_peripherals_count = ARRAY_SIZE(_dmac0_peripherals);
	} else if (dmac == DMAC1) {
		dmac_peripherals = _dmac1_peripherals;
		dmac_peripherals_count = ARRAY_SIZE(_dmac1_peripherals);
	} else {
		return NULL;
	}

	for (i = 0; i < dmac_peripherals_count; i++) {
		if (dmac_peripherals[i].id == id) {
			return &dmac_peripherals[i];
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
			CHIPID_CIDR_SAM9XX5) {
		uint32_t exid = DBGU->DBGU_EXID;
		for (i = 0; i < ARRAY_SIZE(_exid_names); i++) {
			if (_exid_names[i].exid == exid)
				return _exid_names[i].name;
		}
	}

	return "Unknown";
}

#ifdef CONFIG_HAVE_CAN
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
#endif /* CONFIG_HAVE_CAN */

uint32_t get_twi_id_from_addr(const Twi* addr)
{
	if (addr == TWI0)
		return ID_TWI0;
	else if (addr == TWI1)
		return ID_TWI1;
	else if (addr == TWI2)
		return ID_TWI2;
	else
		return ID_PERIPH_COUNT;
}

Twi* get_twi_addr_from_id(uint32_t id)
{
	if (id == ID_TWI0)
		return TWI0;
	else if (id == ID_TWI1)
		return TWI1;
	else if (id == ID_TWI2)
		return TWI2;
	else
		return (void*)0;
}

uint32_t get_spi_id_from_addr(const Spi* addr)
{
	if (addr == SPI0)
		return ID_SPI0;
	else if (addr == SPI1)
		return ID_SPI1;
	else
		return ID_PERIPH_COUNT;
}

Spi* get_spi_addr_from_id(uint32_t id)
{
	if (id == ID_SPI0)
		return SPI0;
	else if (id == ID_SPI1)
		return SPI1;
	else
		return (void*)0;
}

uint32_t get_pwm_id_from_addr(const Pwm* addr)
{
	if (addr == PWM0)
		return ID_PWM0;
	else
		return ID_PERIPH_COUNT;
}

Pwm* get_pwm_addr_from_id(uint32_t id)
{
	if (id == ID_PWM0)
		return PWM0;
	else
		return (void*)0;
}

uint32_t get_uart_id_from_addr(const Uart* addr)
{
	if (addr == UART0)
		return ID_UART0;
	else if (addr == UART1)
		return ID_UART1;
	else
		return ID_PERIPH_COUNT;
}

Uart* get_uart_addr_from_id(uint32_t id)
{
	if (id == ID_UART0)
		return UART0;
	else if (id == ID_UART1)
		return UART1;
	else
		return (void*)0;
}

uint32_t get_usart_id_from_addr(const Usart* addr)
{
	if (addr == USART0)
		return ID_USART0;
	else if (addr == USART1)
		return ID_USART1;
	else if (addr == USART2)
		return ID_USART2;
#ifdef USART3
	else if (addr == USART3)
		return ID_USART3;
#endif
	else
		return ID_PERIPH_COUNT;
}

Usart* get_usart_addr_from_id(uint32_t id)
{
	if (id == ID_USART0)
		return USART0;
	else if (id == ID_USART1)
		return USART1;
	else if (id == ID_USART2)
		return USART2;
#ifdef USART3
	else if (id == ID_USART3)
		return USART3;
#endif
	else
		return (void*)0;
}

uint32_t get_tc_id_from_addr(const Tc* addr)
{
	if (addr == TC0)
		return ID_TC0;
	else if (addr == TC1)
		return ID_TC1;
	else
		return ID_PERIPH_COUNT;
}

Tc* get_tc_addr_from_id(uint32_t id)
{
	if (id == ID_TC0)
		return TC0;
	else if (id == ID_TC1)
		return TC1;
	else
		return (void*)0;
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
	case 4:
		return EBI_CS4_ADDR;
	case 5:
		return EBI_CS5_ADDR;
	default:
		return 0;
	}
}

#ifdef CONFIG_HAVE_EMAC

uint32_t get_emac_id_from_addr(const Emac* addr)
{
#ifdef EMAC0
	if (addr == EMAC0)
		return ID_EMAC0;
#endif
#ifdef EMAC1
	if (addr == EMAC1)
		return ID_EMAC1;
#endif
	return ID_PERIPH_COUNT;
}

#endif /* CONFIG_HAVE_EMAC */

Matrix* get_peripheral_matrix(uint32_t id)
{
	return MATRIX; // AHB matrix
}

uint32_t get_peripheral_clock_matrix_div(uint32_t id)
{
	return 1;
}

uint32_t get_peripheral_clock_max_freq(uint32_t id)
{
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
