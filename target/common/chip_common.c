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

#include <stdlib.h>

#include "chip.h"
#include "chip_common.h"

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

#ifdef CONFIG_HAVE_CAN

uint32_t get_can_id_from_addr(const Can* addr)
{
#ifdef CAN0
	if (addr == (void*)CAN0)
		return ID_CAN0;
#endif
#ifdef CAN1
	if (addr == (void*)CAN1)
		return ID_CAN1;
#endif
	return ID_PERIPH_COUNT;
}

Can* get_can_addr_from_id(const uint32_t id)
{
#ifdef CAN0
	if (id == ID_CAN0)
		return CAN0;
#endif
#ifdef CAN1
	if (id == ID_CAN1)
		return CAN1;
#endif
	return NULL;
}

#endif /* CONFIG_HAVE_CAN */

#ifdef CONFIG_HAVE_CLASSD

uint32_t get_classd_id_from_addr(const Classd* addr)
{
#ifdef CLASSD0
	if (addr == CLASSD0)
		return ID_CLASSD0;
#endif
	return ID_PERIPH_COUNT;
}

#endif /* CONFIG_HAVE_CLASSD */

#ifdef CONFIG_HAVE_DMAC

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
	return NULL;
}

#endif /* CONFIG_HAVE_DMAC */

uint32_t get_ebi_addr_from_cs(uint32_t cs)
{
	switch (cs) {
#ifdef EBI_CS0_ADDR
	case 0:
		return EBI_CS0_ADDR;
#endif
#ifdef EBI_CS1_ADDR
	case 1:
		return EBI_CS1_ADDR;
#endif
#ifdef EBI_CS2_ADDR
	case 2:
		return EBI_CS2_ADDR;
#endif
#ifdef EBI_CS3_ADDR
	case 3:
		return EBI_CS3_ADDR;
#endif
#ifdef EBI_CS4_ADDR
	case 4:
		return EBI_CS4_ADDR;
#endif
#ifdef EBI_CS5_ADDR
	case 5:
		return EBI_CS5_ADDR;
#endif
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

#ifdef CONFIG_HAVE_FLEXCOM

uint32_t get_flexcom_id_from_addr(const Flexcom* addr)
{
#ifdef FLEXCOM0
	if (addr == FLEXCOM0)
		return ID_FLEXCOM0;
#endif
#ifdef FLEXCOM1
	if (addr == FLEXCOM1)
		return ID_FLEXCOM1;
#endif
#ifdef FLEXCOM2
	if (addr == FLEXCOM2)
		return ID_FLEXCOM2;
#endif
#ifdef FLEXCOM3
	if (addr == FLEXCOM3)
		return ID_FLEXCOM3;
#endif
#ifdef FLEXCOM4
	if (addr == FLEXCOM4)
		return ID_FLEXCOM4;
#endif
#ifdef FLEXCOM5
	if (addr == FLEXCOM5)
		return ID_FLEXCOM5;
#endif
#ifdef FLEXCOM6
	if (addr == FLEXCOM6)
		return ID_FLEXCOM6;
#endif
#ifdef FLEXCOM7
	if (addr == FLEXCOM7)
		return ID_FLEXCOM7;
#endif
#ifdef FLEXCOM8
	if (addr == FLEXCOM8)
		return ID_FLEXCOM8;
#endif
#ifdef FLEXCOM9
	if (addr == FLEXCOM9)
		return ID_FLEXCOM9;
#endif
	return ID_PERIPH_COUNT;
}

Flexcom* get_flexcom_addr_from_id(uint32_t id)
{
#ifdef FLEXCOM0
	if (id == ID_FLEXCOM0)
		return FLEXCOM0;
#endif
#ifdef FLEXCOM1
	if (id == ID_FLEXCOM1)
		return FLEXCOM1;
#endif
#ifdef FLEXCOM2
	if (id == ID_FLEXCOM2)
		return FLEXCOM2;
#endif
#ifdef FLEXCOM3
	if (id == ID_FLEXCOM3)
		return FLEXCOM3;
#endif
#ifdef FLEXCOM4
	if (id == ID_FLEXCOM4)
		return FLEXCOM4;
#endif
#ifdef FLEXCOM5
	if (id == ID_FLEXCOM5)
		return FLEXCOM5;
#endif
#ifdef FLEXCOM6
	if (id == ID_FLEXCOM6)
		return FLEXCOM6;
#endif
#ifdef FLEXCOM7
	if (id == ID_FLEXCOM7)
		return FLEXCOM7;
#endif
#ifdef FLEXCOM8
	if (id == ID_FLEXCOM8)
		return FLEXCOM8;
#endif
#ifdef FLEXCOM9
	if (id == ID_FLEXCOM9)
		return FLEXCOM9;
#endif
	return NULL;
}

#endif /* CONFIG_HAVE_FLEXCOM */

#ifdef CONFIG_HAVE_GMAC

uint32_t get_gmac_id_from_addr(const Gmac* addr)
{
#ifdef GMAC0
	if (addr == GMAC0)
		return ID_GMAC0;
#endif
#ifdef GMAC1
	if (addr == GMAC1)
		return ID_GMAC1;
#endif
	return ID_PERIPH_COUNT;
}

#endif /* CONFIG_HAVE_GMAC */

#ifdef CONFIG_HAVE_HSMCI

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
	return NULL;
}

#endif /* CONFIG_HAVE_HSMCI */

#ifdef CONFIG_HAVE_MCAN

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
#ifdef MCAN2
	if (addr == (void*)MCAN2)
		return  int_idx == 0 ? ID_MCAN2_INT0 : ID_MCAN2_INT1;
#endif
#ifdef MCAN3
	if (addr == (void*)MCAN3)
		return  int_idx == 0 ? ID_MCAN3_INT0 : ID_MCAN3_INT1;
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
		return MCAN1;
#endif
#ifdef MCAN2
	if (id == ID_MCAN2_INT0 || id == ID_MCAN2_INT1)
		return MCAN2;
#endif
#ifdef MCAN3
	if (id == ID_MCAN3_INT0 || id == ID_MCAN3_INT1)
		return MCAN3;
#endif
	return NULL;
}

#endif /* CONFIG_HAVE_MCAN */

#ifdef CONFIG_HAVE_PDMIC

uint32_t get_pdmic_id_from_addr(const Pdmic* addr)
{
#ifdef PDMIC0
	if (addr == PDMIC0)
		return ID_PDMIC0;
#endif
#ifdef PDMIC1
	if (addr == PDMIC1)
		return ID_PDMIC1;
#endif
#ifdef PDMIC2
	if (addr == PDMIC2)
		return ID_PDMIC2;
#endif
#ifdef PDMIC3
	if (addr == PDMIC3)
		return ID_PDMIC3;
#endif
	return ID_PERIPH_COUNT;
}

#endif /* CONFIG_HAVE_PDMIC */

uint32_t get_pwm_id_from_addr(const Pwm* addr)
{
#ifdef PWM0
	if (addr == PWM0)
		return ID_PWM0;
#endif
#ifdef PWM1
	if (addr == PWM1)
		return ID_PWM1;
#endif
	return ID_PERIPH_COUNT;
}

Pwm* get_pwm_addr_from_id(uint32_t id)
{
#ifdef PWM0
	if (id == ID_PWM0)
		return PWM0;
#endif
#ifdef PWM1
	if (id == ID_PWM1)
		return PWM1;
#endif
	return NULL;
}

#ifdef CONFIG_HAVE_QSPI

uint32_t get_qspi_id_from_addr(const Qspi* addr)
{
#ifdef QSPI0
	if (addr == QSPI0)
		return ID_QSPI0;
#endif
#ifdef QSPI1
	if (addr == QSPI1)
		return ID_QSPI1;
#endif
	return ID_PERIPH_COUNT;
}

void *get_qspi_mem_from_addr(const Qspi* addr)
{
#ifdef QSPI0
	if (addr == QSPI0)
		return (void*)QSPIMEM0_ADDR;
#endif
#ifdef QSPI1
	if (addr == QSPI1)
		return (void*)QSPIMEM1_ADDR;
#endif
	return NULL;
}

#ifdef CONFIG_HAVE_AESB

void *get_qspi_aesb_mem_from_addr(const Qspi* addr)
{
#ifdef QSPI0
	if (addr == QSPI0)
		return (void*)QSPI_AES0_ADDR;
#endif
#ifdef QSPI1
	if (addr == QSPI1)
		return (void*)QSPI_AES1_ADDR;
#endif
	return NULL;
}

#endif /* CONFIG_HAVE_AESB */

#endif /* CONFIG_HAVE_QSPI */

#ifdef CONFIG_HAVE_SDMMC

uint32_t get_sdmmc_id_from_addr(const Sdmmc* addr)
{
#ifdef SDMMC0
	if (addr == SDMMC0)
		return ID_SDMMC0;
#endif
#ifdef SDMMC1
	if (addr == SDMMC1)
		return ID_SDMMC1;
#endif
	return ID_PERIPH_COUNT;
}

Sdmmc* get_sdmmc_addr_from_id(uint32_t id)
{
#ifdef SDMMC0
	if (id == ID_SDMMC0)
		return SDMMC0;
#endif
#ifdef SDMMC1
	if (id == ID_SDMMC1)
		return SDMMC1;
#endif
	return NULL;
}

#endif /* CONFIG_HAVE_SDMMC */

#ifdef CONFIG_HAVE_SSC

uint32_t get_ssc_id_from_addr(const Ssc* addr)
{
#ifdef SSC0
	if (addr == SSC0)
		return ID_SSC0;
#endif
#ifdef SSC1
	if (addr == SSC1)
		return ID_SSC1;
#endif
	return ID_PERIPH_COUNT;
}

#endif /* CONFIG_HAVE_SSC */

uint32_t get_spi_id_from_addr(const Spi* addr)
{
#ifdef SPI0
	if (addr == SPI0)
		return ID_SPI0;
#endif
#ifdef SPI1
	if (addr == SPI1)
		return ID_SPI1;
#endif
#ifdef SPI2
	if (addr == SPI2)
		return ID_SPI2;
#endif
#ifdef FLEXSPI0
	if (addr == FLEXSPI0)
		return ID_FLEXCOM0;
#endif
#ifdef FLEXSPI1
	if (addr == FLEXSPI1)
		return ID_FLEXCOM1;
#endif
#ifdef FLEXSPI2
	if (addr == FLEXSPI2)
		return ID_FLEXCOM2;
#endif
#ifdef FLEXSPI3
	if (addr == FLEXSPI3)
		return ID_FLEXCOM3;
#endif
#ifdef FLEXSPI4
	if (addr == FLEXSPI4)
		return ID_FLEXCOM4;
#endif
#ifdef FLEXSPI5
	if (addr == FLEXSPI5)
		return ID_FLEXCOM5;
#endif
#ifdef FLEXSPI6
	if (addr == FLEXSPI6)
		return ID_FLEXCOM6;
#endif
#ifdef FLEXSPI7
	if (addr == FLEXSPI7)
		return ID_FLEXCOM7;
#endif
#ifdef FLEXSPI8
	if (addr == FLEXSPI8)
		return ID_FLEXCOM8;
#endif
#ifdef FLEXSPI9
	if (addr == FLEXSPI9)
		return ID_FLEXCOM9;
#endif
	return ID_PERIPH_COUNT;
}

Spi* get_spi_addr_from_id(uint32_t id)
{
#ifdef SPI0
	if (id == ID_SPI0)
		return SPI0;
#endif
#ifdef SPI1
	if (id == ID_SPI1)
		return SPI1;
#endif
#ifdef SPI2
	if (id == ID_SPI2)
		return SPI2;
#endif
#ifdef  FLEXSPI0
	if (id == ID_FLEXCOM0)
		return FLEXSPI0;
#endif
#ifdef  FLEXSPI1
	if (id == ID_FLEXCOM1)
		return FLEXSPI1;
#endif
#ifdef  FLEXSPI2
	if (id == ID_FLEXCOM2)
		return FLEXSPI2;
#endif
#ifdef  FLEXSPI3
	if (id == ID_FLEXCOM3)
		return FLEXSPI3;
#endif
#ifdef  FLEXSPI4
	if (id == ID_FLEXCOM4)
		return FLEXSPI4;
#endif
#ifdef  FLEXSPI5
	if (id == ID_FLEXCOM5)
		return FLEXSPI5;
#endif
#ifdef  FLEXSPI6
	if (id == ID_FLEXCOM6)
		return FLEXSPI6;
#endif
#ifdef  FLEXSPI7
	if (id == ID_FLEXCOM7)
		return FLEXSPI7;
#endif
#ifdef  FLEXSPI8
	if (id == ID_FLEXCOM8)
		return FLEXSPI8;
#endif
#ifdef  FLEXSPI9
	if (id == ID_FLEXCOM9)
		return FLEXSPI9;
#endif
	return NULL;
}

uint32_t get_tc_id_from_addr(const Tc* addr, uint8_t channel)
{
#ifdef TC0
	if (addr == TC0)
#ifdef ID_TC0_CH0
		return ID_TC0 + channel;
#else
		return ID_TC0;
#endif
#endif

#ifdef TC1
	if (addr == TC1)
#ifdef ID_TC1_CH0
		return ID_TC1 + channel;
#else
		return ID_TC1;
#endif
#endif

#ifdef TC2
	if (addr == TC2)
#ifdef ID_TC2_CH0
		return ID_TC2 + channel;
#else
		return ID_TC2;
#endif
#endif

#ifdef TC3
	if (addr == TC3)
#ifdef ID_TC3_CH0
		return ID_TC3 + channel;
#else
		return ID_TC3;
#endif
#endif
	return ID_PERIPH_COUNT;
}

Tc* get_tc_addr_from_id(uint32_t id)
{
#ifdef TC0
	if (id == ID_TC0)
		return TC0;
#endif
#ifdef TC1
	if (id == ID_TC1)
		return TC1;
#endif
#ifdef TC2
	if (id == ID_TC2)
		return TC2;
#endif
#ifdef TC3
	if (id == ID_TC3)
		return TC3;
#endif
	return NULL;
}

uint32_t get_twi_id_from_addr(const Twi* addr)
{
#ifdef TWI0
	if (addr == TWI0)
		return ID_TWI0;
#endif
#ifdef TWI1
	if (addr == TWI1)
		return ID_TWI1;
#endif
#ifdef TWI2
	if (addr == TWI2)
		return ID_TWI2;
#endif
#ifdef TWI3
	if (addr == TWI3)
		return ID_TWI3;
#endif
#ifdef TWI4
	if (addr == TWI4)
		return ID_TWI4;
#endif
#ifdef FLEXTWI0
	if (addr == FLEXTWI0)
		return ID_FLEXCOM0;
#endif
#ifdef FLEXTWI1
	if (addr == FLEXTWI1)
		return ID_FLEXCOM1;
#endif
#ifdef FLEXTWI2
	if (addr == FLEXTWI2)
		return ID_FLEXCOM2;
#endif
#ifdef FLEXTWI3
	if (addr == FLEXTWI3)
		return ID_FLEXCOM3;
#endif
#ifdef FLEXTWI4
	if (addr == FLEXTWI4)
		return ID_FLEXCOM4;
#endif
#ifdef FLEXTWI5
	if (addr == FLEXTWI5)
		return ID_FLEXCOM5;
#endif
#ifdef FLEXTWI6
	if (addr == FLEXTWI6)
		return ID_FLEXCOM6;
#endif
#ifdef FLEXTWI7
	if (addr == FLEXTWI7)
		return ID_FLEXCOM7;
#endif
#ifdef FLEXTWI8
	if (addr == FLEXTWI8)
		return ID_FLEXCOM8;
#endif
#ifdef FLEXTWI9
	if (addr == FLEXTWI9)
		return ID_FLEXCOM9;
#endif
	return ID_PERIPH_COUNT;
}

Twi* get_twi_addr_from_id(uint32_t id)
{
#ifdef TWI0
	if (id == ID_TWI0)
		return TWI0;
#endif
#ifdef TWI1
	if (id == ID_TWI1)
		return TWI1;
#endif
#ifdef TWI2
	if (id == ID_TWI2)
		return TWI2;
#endif
#ifdef TWI3
	if (id == ID_TWI3)
		return TWI3;
#endif
#ifdef TWI4
	if (id == ID_TWI4)
		return TWI4;
#endif
#ifdef FLEXTWI0
	if (id == ID_FLEXCOM0)
		return FLEXTWI0;
#endif
#ifdef FLEXTWI1
	if (id == ID_FLEXCOM1)
		return FLEXTWI1;
#endif
#ifdef FLEXTWI2
	if (id == ID_FLEXCOM2)
		return FLEXTWI2;
#endif
#ifdef FLEXTWI3
	if (id == ID_FLEXCOM3)
		return FLEXTWI3;
#endif
#ifdef FLEXTWI4
	if (id == ID_FLEXCOM4)
		return FLEXTWI4;
#endif
#ifdef FLEXTWI5
	if (id == ID_FLEXCOM5)
		return FLEXTWI5;
#endif
#ifdef FLEXTWI6
	if (id == ID_FLEXCOM6)
		return FLEXTWI6;
#endif
#ifdef FLEXTWI7
	if (id == ID_FLEXCOM7)
		return FLEXTWI7;
#endif
#ifdef FLEXTWI8
	if (id == ID_FLEXCOM8)
		return FLEXTWI8;
#endif
#ifdef FLEXTWI9
	if (id == ID_FLEXCOM9)
		return FLEXTWI9;
#endif
	return NULL;
}

#ifdef CONFIG_HAVE_UART

uint32_t get_uart_id_from_addr(const Uart* addr)
{
#ifdef UART0
	if (addr == UART0)
		return ID_UART0;
#endif
#ifdef UART1
	if (addr == UART1)
		return ID_UART1;
#endif
#ifdef UART2
	if (addr == UART2)
		return ID_UART2;
#endif
#ifdef UART3
	if (addr == UART3)
		return ID_UART3;
#endif
#ifdef UART4
	if (addr == UART4)
		return ID_UART4;
#endif
	return ID_PERIPH_COUNT;
}

Uart* get_uart_addr_from_id(uint32_t id)
{
#ifdef UART0
	if (id == ID_UART0)
		return UART0;
#endif
#ifdef UART1
	if (id == ID_UART1)
		return UART1;
#endif
#ifdef UART2
	if (id == ID_UART2)
		return UART2;
#endif
#ifdef UART3
	if (id == ID_UART3)
		return UART3;
#endif
#ifdef UART4
	if (id == ID_UART4)
		return UART4;
#endif
	return NULL;
}

#endif /* CONFIG_HAVE_UART */

uint32_t get_usart_id_from_addr(const Usart* addr)
{
#ifdef USART0
	if (addr == USART0)
		return ID_USART0;
#endif
#ifdef USART1
	if (addr == USART1)
		return ID_USART1;
#endif
#ifdef USART2
	if (addr == USART2)
		return ID_USART2;
#endif
#ifdef USART3
	if (addr == USART3)
		return ID_USART3;
#endif
#ifdef USART4
	if (addr == USART4)
		return ID_USART4;
#endif
#ifdef FLEXUSART0
	if (addr == FLEXUSART0)
		return ID_FLEXCOM0;
#endif
#ifdef FLEXUSART1
	if (addr == FLEXUSART1)
		return ID_FLEXCOM1;
#endif
#ifdef FLEXUSART2
	if (addr == FLEXUSART2)
		return ID_FLEXCOM2;
#endif
#ifdef FLEXUSART3
	if (addr == FLEXUSART3)
		return ID_FLEXCOM3;
#endif
#ifdef FLEXUSART4
	if (addr == FLEXUSART4)
		return ID_FLEXCOM4;
#endif
#ifdef FLEXUSART5
	if (addr == FLEXUSART5)
		return ID_FLEXCOM5;
#endif
#ifdef FLEXUSART6
	if (addr == FLEXUSART6)
		return ID_FLEXCOM6;
#endif
#ifdef FLEXUSART7
	if (addr == FLEXUSART7)
		return ID_FLEXCOM7;
#endif
#ifdef FLEXUSART8
	if (addr == FLEXUSART8)
		return ID_FLEXCOM8;
#endif
#ifdef FLEXUSART9
	if (addr == FLEXUSART9)
		return ID_FLEXCOM9;
#endif
	return ID_PERIPH_COUNT;
}

Usart* get_usart_addr_from_id(uint32_t id)
{
#ifdef USART0
	if (id == ID_USART0)
		return USART0;
#endif
#ifdef USART1
	if (id == ID_USART1)
		return USART1;
#endif
#ifdef USART2
	if (id == ID_USART2)
		return USART2;
#endif
#ifdef USART3
	if (id == ID_USART3)
		return USART3;
#endif
#ifdef USART4
	if (id == ID_USART4)
		return USART4;
#endif
#ifdef FLEXUSART0
	if (id == ID_FLEXCOM0)
		return FLEXUSART0;
#endif
#ifdef FLEXUSART1
	if (id == ID_FLEXCOM1)
		return FLEXUSART1;
#endif
#ifdef FLEXUSART2
	if (id == ID_FLEXCOM2)
		return FLEXUSART2;
#endif
#ifdef FLEXUSART3
	if (id == ID_FLEXCOM3)
		return FLEXUSART3;
#endif
#ifdef FLEXUSART4
	if (id == ID_FLEXCOM4)
		return FLEXUSART4;
#endif
#ifdef FLEXUSART5
	if (id == ID_FLEXCOM5)
		return FLEXUSART5;
#endif
#ifdef FLEXUSART6
	if (id == ID_FLEXCOM6)
		return FLEXUSART6;
#endif
#ifdef FLEXUSART7
	if (id == ID_FLEXCOM7)
		return FLEXUSART7;
#endif
#ifdef FLEXUSART8
	if (id == ID_FLEXCOM8)
		return FLEXUSART8;
#endif
#ifdef FLEXUSART9
	if (id == ID_FLEXCOM9)
		return FLEXUSART9;
#endif
	return NULL;
}

#ifdef CONFIG_HAVE_XDMAC

uint32_t get_xdmac_id_from_addr(const Xdmac* addr)
{
#ifdef XDMAC0
	if (addr == XDMAC0)
		return ID_XDMAC0;
#endif
#ifdef XDMAC1
	if (addr == XDMAC1)
		return ID_XDMAC1;
#endif
	return ID_PERIPH_COUNT;
}

Xdmac* get_xdmac_addr_from_id(uint32_t id)
{
#ifdef XDMAC0
	if (id == ID_XDMAC0)
		return XDMAC0;
#endif
#ifdef XDMAC1
	if (id == ID_XDMAC1)
		return XDMAC1;
#endif
	return (void*)0;
}

#endif /* CONFIG_HAVE_XDMAC */
