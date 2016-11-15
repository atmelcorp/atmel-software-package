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

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

struct chipid {
	uint32_t    cidr; /**< CIDR */
	uint32_t    exid; /**< EXID */
	const char* name; /**< Chip Name */
};

struct peripheral_xdma {
	uint32_t id;   /**< Peripheral ID */
	uint8_t  iftx; /**< DMA Interface for TX */
	uint8_t  ifrx; /**< DMA Interface for RX */
};

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

static const struct chipid _chipid_names[] = {
	{ CHIPID_CIDR_SAME70Q21, CHIPID_EXID_SAME70Q21, "SAME70Q21" },
	{ CHIPID_CIDR_SAME70Q20, CHIPID_EXID_SAME70Q20, "SAME70Q20" },
	{ CHIPID_CIDR_SAME70Q19, CHIPID_EXID_SAME70Q19, "SAME70Q19" },
	{ CHIPID_CIDR_SAME70N21, CHIPID_EXID_SAME70N21, "SAME70N21" },
	{ CHIPID_CIDR_SAME70N20, CHIPID_EXID_SAME70N20, "SAME70N20" },
	{ CHIPID_CIDR_SAME70N19, CHIPID_EXID_SAME70N19, "SAME70N19" },
	{ CHIPID_CIDR_SAME70J21, CHIPID_EXID_SAME70J21, "SAME70J21" },
	{ CHIPID_CIDR_SAME70J20, CHIPID_EXID_SAME70J20, "SAME70J20" },
	{ CHIPID_CIDR_SAME70J19, CHIPID_EXID_SAME70J19, "SAME70J19" },
	{ CHIPID_CIDR_SAMS70Q21, CHIPID_EXID_SAMS70Q21, "SAMS70Q21" },
	{ CHIPID_CIDR_SAMS70Q20, CHIPID_EXID_SAMS70Q20, "SAMS70Q20" },
	{ CHIPID_CIDR_SAMS70Q19, CHIPID_EXID_SAMS70Q19, "SAMS70Q19" },
	{ CHIPID_CIDR_SAMS70N21, CHIPID_EXID_SAMS70N21, "SAMS70N21" },
	{ CHIPID_CIDR_SAMS70N20, CHIPID_EXID_SAMS70N20, "SAMS70N20" },
	{ CHIPID_CIDR_SAMS70N19, CHIPID_EXID_SAMS70N19, "SAMS70N19" },
	{ CHIPID_CIDR_SAMS70J21, CHIPID_EXID_SAMS70J21, "SAMS70J21" },
	{ CHIPID_CIDR_SAMS70J20, CHIPID_EXID_SAMS70J20, "SAMS70J20" },
	{ CHIPID_CIDR_SAMS70J19, CHIPID_EXID_SAMS70J19, "SAMS70J19" },
	{ CHIPID_CIDR_SAMV70Q20, CHIPID_EXID_SAMV70Q20, "SAMV70Q20" },
	{ CHIPID_CIDR_SAMV70Q19, CHIPID_EXID_SAMV70Q19, "SAMV70Q19" },
	{ CHIPID_CIDR_SAMV70N20, CHIPID_EXID_SAMV70N20, "SAMV70N20" },
	{ CHIPID_CIDR_SAMV70N19, CHIPID_EXID_SAMV70N19, "SAMV70N19" },
	{ CHIPID_CIDR_SAMV70J20, CHIPID_EXID_SAMV70J20, "SAMV70J20" },
	{ CHIPID_CIDR_SAMV70J19, CHIPID_EXID_SAMV70J19, "SAMV70J19" },
	{ CHIPID_CIDR_SAMV71Q21, CHIPID_EXID_SAMV71Q21, "SAMV71Q21" },
	{ CHIPID_CIDR_SAMV71Q20, CHIPID_EXID_SAMV71Q20, "SAMV71Q20" },
	{ CHIPID_CIDR_SAMV71Q19, CHIPID_EXID_SAMV71Q19, "SAMV71Q19" },
	{ CHIPID_CIDR_SAMV71N21, CHIPID_EXID_SAMV71N21, "SAMV71N21" },
	{ CHIPID_CIDR_SAMV71N20, CHIPID_EXID_SAMV71N20, "SAMV71N20" },
	{ CHIPID_CIDR_SAMV71N19, CHIPID_EXID_SAMV71N19, "SAMV71N19" },
	{ CHIPID_CIDR_SAMV71J21, CHIPID_EXID_SAMV71J21, "SAMV71J21" },
	{ CHIPID_CIDR_SAMV71J20, CHIPID_EXID_SAMV71J20, "SAMV71J20" },
	{ CHIPID_CIDR_SAMV71J19, CHIPID_EXID_SAMV71J19, "SAMV71J19" },
};

static const struct peripheral_xdma _xdmac_peripherals[] = {
	{ ID_HSMCI0,      0,    0 },
	{ ID_SPI0,        1,    2 },
	{ ID_SPI1,        3,    4 },
	{ ID_QSPI0,       5,    6 },
	{ ID_USART0,      7,    8 },
	{ ID_USART1,      9,   10 },
	{ ID_USART2,     11,   12 },
	{ ID_PWM0,       13, 0xff },
	{ ID_TWI0,       14,   15 },
	{ ID_TWI1,       16,   17 },
	{ ID_TWI2,       18,   19 },
	{ ID_UART0,      20,   21 },
	{ ID_UART1,      22,   23 },
	{ ID_UART2,      24,   25 },
	{ ID_UART3,      26,   27 },
	{ ID_UART4,      28,   29 },
	{ ID_DACC,       30, 0xff },
	{ ID_SSC0,       32,   33 },
	{ ID_PIOA,     0xff,   34 },
	{ ID_AFEC0,    0xff,   35 },
	{ ID_AFEC1,    0xff,   36 },
	{ ID_AES,        37,   38 },
	{ ID_PWM1,       39, 0xff },
	{ ID_TC0_CH0,  0xff,   40 },
	{ ID_TC1_CH0,  0xff,   41 },
	{ ID_TC2_CH0,  0xff,   42 },
	{ ID_TC3_CH0,  0xff,   43 },
	{ ID_I2SC0,      44,   45 }, /* Left or Left+Right */
	{ ID_I2SC1,      46,   47 }, /* Left or Left+Right */
	//{ ID_I2SC0,      48,   49 }, /* Right */
	//{ ID_I2SC1,      50,   51 }, /* Right */
};

/*----------------------------------------------------------------------------
 *        Private functions
 *----------------------------------------------------------------------------*/

static const struct peripheral_xdma *get_peripheral_xdma(uint32_t id, Xdmac *xdmac)
{
	int i;

	if (xdmac != XDMAC0) {
		return NULL;
	}

	for (i = 0; i < ARRAY_SIZE(_xdmac_peripherals); i++) {
		if (_xdmac_peripherals[i].id == id) {
			return &_xdmac_peripherals[i];
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
	uint32_t cidr = CHIPID->CHIPID_CIDR & ~CHIPID_CIDR_VERSION_Msk;
	uint32_t exid = CHIPID->CHIPID_EXID;

	for (i = 0; i < ARRAY_SIZE(_chipid_names); i++) {
		if (_chipid_names[i].cidr == cidr &&
		    _chipid_names[i].exid == exid)
			return _chipid_names[i].name;
	}

	return "Unknown";
}

uint8_t get_flash_wait_states(uint32_t frequency)
{
	/* Embedded Flash Wait States for Worst-Case Conditions */
	/* VDDIO 3.0V */
	const uint32_t max_freq[] = {
		23000000, 46000000, 69000000, 92000000, 115000000, 138000000 };
	int i;
	for (i = 0; i < ARRAY_SIZE(max_freq); i++)
		if (max_freq[i] <= frequency)
			break;
	return i;
}

uint32_t get_mcan_id_from_addr(const Mcan* addr, uint8_t int_idx)
{
	if (int_idx > 1)
		return ID_PERIPH_COUNT;
#ifdef MCAN0
	if (addr == (void*)MCAN0)
		return int_idx == 0 ? ID_MCAN0_INT0 : ID_MCAN0_INT1;
#endif
#ifdef MCAN1
	if (addr == (void*)MCAN1)
		return  int_idx == 0 ? ID_MCAN1_INT0 : ID_MCAN1_INT1;
#endif
	return ID_PERIPH_COUNT;
}

Mcan* get_mcan_addr_from_id(const uint32_t id)
{
#ifdef MCAN0
	if (id == ID_MCAN0_INT0 || id == ID_MCAN0_INT1)
		return MCAN0;
#endif
#ifdef MCAN1
	if (id == ID_MCAN1_INT0 || id == ID_MCAN1_INT1)
		return MCAN0;
#endif
	return (void*)0;
}

uint32_t get_twi_id_from_addr(const Twi* addr)
{
	if (addr == TWI0)
		return ID_TWI0;
#ifdef TWI1
	else if (addr == TWI1)
		return ID_TWI1;
#endif
#ifdef TWI2
	else if (addr == TWI2)
		return ID_TWI2;
#endif
	else
		return ID_PERIPH_COUNT;
}

Twi* get_twi_addr_from_id(uint32_t id)
{
	if (id == ID_TWI0)
		return TWI0;
#ifdef TWI1
	else if (id == ID_TWI1)
		return TWI1;
#endif
#ifdef TWI2
	else if (id == ID_TWI2)
		return TWI2;
#endif
	else
		return (void*)0;
}

uint32_t get_spi_id_from_addr(const Spi* addr)
{
	if (addr == SPI0)
		return ID_SPI0;
#ifdef SPI1
	else if (addr == SPI1)
		return ID_SPI1;
#endif
	else
		return ID_PERIPH_COUNT;
}

Spi* get_spi_addr_from_id(uint32_t id)
{
	if (id == ID_SPI0)
		return SPI0;
#ifdef SPI1
	else if (id == ID_SPI1)
		return SPI1;
#endif
	else
		return (void*)0;
}

uint32_t get_pwm_id_from_addr(const Pwm* addr)
{
	if (addr == PWM0)
		return ID_PWM0;
#ifdef PWM1
	else if (addr == PWM1)
		return ID_PWM1;
#endif
	else
		return ID_PERIPH_COUNT;
}

Pwm* get_pwm_addr_from_id(uint32_t id)
{
	if (id == ID_PWM0)
		return PWM0;
#ifdef PWM1
	else if (id == ID_PWM1)
		return PWM1;
#endif
	else
		return (void*)0;
}

uint32_t get_uart_id_from_addr(const Uart* addr)
{
	if (addr == UART0)
		return ID_UART0;
#ifdef UART1
	else if (addr == UART1)
		return ID_UART1;
#endif
#ifdef UART2
	else if (addr == UART2)
		return ID_UART2;
#endif
#ifdef UART3
	else if (addr == UART3)
		return ID_UART3;
#endif
#ifdef UART4
	else if (addr == UART4)
		return ID_UART4;
#endif
	else
		return ID_PERIPH_COUNT;
}

Uart* get_uart_addr_from_id(uint32_t id)
{
	if (id == ID_UART0)
		return UART0;
#ifdef UART1
	else if (id == ID_UART1)
		return UART1;
#endif
#ifdef UART2
	else if (id == ID_UART2)
		return UART2;
#endif
#ifdef UART3
	else if (id == ID_UART3)
		return UART3;
#endif
#ifdef UART4
	else if (id == ID_UART4)
		return UART4;
#endif
	else
		return (void*)0;
}

uint32_t get_usart_id_from_addr(const Usart* addr)
{
	if (addr == USART0)
		return ID_USART0;
#ifdef USART1
	else if (addr == USART1)
		return ID_USART1;
#endif
#ifdef USART2
	else if (addr == USART2)
		return ID_USART2;
#endif
	else
		return ID_PERIPH_COUNT;
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
	else
		return (void*)0;
}

uint32_t get_tc_id_from_addr(const Tc* addr)
{
	if (addr == TC0)
		return ID_TC0;
#ifdef TC1
	else if (addr == TC1)
		return ID_TC1;
#endif
#ifdef TC2
	else if (addr == TC2)
		return ID_TC2;
#endif
#ifdef TC3
	else if (addr == TC3)
		return ID_TC3;
#endif
	else
		return ID_PERIPH_COUNT;
}

Tc* get_tc_addr_from_id(uint32_t id)
{
	if (id == ID_TC0)
		return TC0;
#ifdef TC1
	else if (id == ID_TC1)
		return TC1;
#endif
#ifdef TC2
	else if (id == ID_TC2)
		return TC2;
#endif
#ifdef TC3
	else if (id == ID_TC3)
		return TC3;
#endif
	else
		return (void*)0;
}

uint32_t get_tc_interrupt(uint32_t tc_id, uint8_t channel)
{
	return tc_id + channel;
}

uint32_t get_qspi_id_from_addr(const Qspi* addr)
{
	if (addr == QSPI0)
		return ID_QSPI0;
	else
		return ID_PERIPH_COUNT;
}

void *get_qspi_mem_from_addr(const Qspi* addr)
{
	if (addr == QSPI0)
		return (void*)QSPIMEM0_ADDR;
	else
		return NULL;
}

uint32_t get_gmac_id_from_addr(const Gmac* addr)
{
	if (addr == GMAC0)
		return ID_GMAC0;
	else
		return ID_PERIPH_COUNT;
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
	default:
		return 0;
	}
}

Matrix* get_peripheral_matrix(uint32_t id)
{
	return MATRIX;
}

uint32_t get_peripheral_clock_matrix_div(uint32_t id)
{
	return 1;
}

uint32_t get_xdmac_id_from_addr(const Xdmac* addr)
{
#ifdef XDMAC0
	if (addr == XDMAC0)
		return ID_XDMAC0;
#endif
	return ID_PERIPH_COUNT;
}

Xdmac* get_xdmac_addr_from_id(uint32_t id)
{
#ifdef XDMAC0
	if (id == ID_XDMAC0)
		return XDMAC0;
#endif
	return (void*)0;
}

uint8_t get_peripheral_xdma_channel(uint32_t id, Xdmac *xdmac, bool transmit)
{
	const struct peripheral_xdma *periph_xdma = get_peripheral_xdma(id, xdmac);
	if (periph_xdma) {
		return transmit ? periph_xdma->iftx : periph_xdma->ifrx;
	} else {
		return 0xff;
	}
}

bool is_peripheral_on_xdma_controller(uint32_t id, Xdmac *xdmac)
{
	return get_peripheral_xdma(id, xdmac) != NULL;
}
