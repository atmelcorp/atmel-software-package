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

#ifndef _CHIP_COMMON_H_
#define _CHIP_COMMON_H_

#include <stdint.h>

#ifdef CONFIG_HAVE_CAN

/**
 * \brief retrieve CAN ID from its base address
 * \return CAN ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_can_id_from_addr(const Can* addr);

/**
 * \brief retrieve CAN base address from its ID
 * \return CAN base address on success, 0 otherwise
 */
extern Can* get_can_addr_from_id(const uint32_t id);

#endif /* CONFIG_HAVE_CAN */

#ifdef CONFIG_HAVE_CLASSD

/**
 * \brief retrieve CLASSD ID from its base address
 * \return CLASSD ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_classd_id_from_addr(const Classd* addr);

#endif /* CONFIG_HAVE_CLASSD */

#ifdef CONFIG_HAVE_DMAC

/**
 * \brief retrieve DMAC ID from its base address
 * \return DMAC ID upon success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_dmac_id_from_addr(const Dmac* addr);

/**
 * \brief retrieve DMAC base address from its ID
 * \return DMAC base address on success, 0 otherwise
 */
extern Dmac* get_dmac_addr_from_id(uint32_t id);

#endif /* CONFIG_HAVE_DMAC */

/**
 * \brief retrieve EBI memory start from its Chip Select (CS)
 * \return EBI memory start on success, 0 otherwise
 */
extern uint32_t get_ebi_addr_from_cs(uint32_t cs);

#ifdef CONFIG_HAVE_EMAC

/**
 * \brief retrieve EMAC ID from its base address
 * \return EMAC ID on success, ID_PERIPH_COUNT otherwise
 */
uint32_t get_emac_id_from_addr(const Emac* addr);

#endif /* CONFIG_HAVE_EMAC */

#ifdef CONFIG_HAVE_FLEXCOM

/**
 * \brief retrieve FLEXCOM ID from its base address
 * \return FLEXCOM ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_flexcom_id_from_addr(const Flexcom* addr);

/**
 * \brief retrieve Flexcom base address from its ID
 * \return Flexcom base address on success, 0 otherwise
 */
extern Flexcom* get_flexcom_addr_from_id(uint32_t id);

#endif /* CONFIG_HAVE_FLEXCOM */

#ifdef CONFIG_HAVE_GMAC

/**
 * \brief retrieve GMAC ID from its base address
 * \return GMAC ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_gmac_id_from_addr(const Gmac* addr);

#endif /* CONFIG_HAVE_GMAC */

#ifdef CONFIG_HAVE_HSMCI

/**
 * \brief retrieve HSMCI ID from its base address
 * \return HSMCI ID upon success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_hsmci_id_from_addr(const Hsmci* addr);

/**
 * \brief retrieve HSMCI base address from its ID
 * \return HSMCI base address on success, 0 otherwise
 */
extern Hsmci* get_hsmci_addr_from_id(uint32_t id);

#endif /* CONFIG_HAVE_HSMCI */

#ifdef CONFIG_HAVE_MCAN

/**
 * \brief retrieve MCAN ID from its base address
 * \return MCAN ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_mcan_id_from_addr(const Mcan* addr, uint8_t int_idx);

/**
 * \brief retrieve MCAN base address from its ID
 * \return MCAN base address on success, 0 otherwise
 */
extern Mcan* get_mcan_addr_from_id(const uint32_t id);

#endif /* CONFIG_HAVE_MCAN */

#ifdef CONFIG_HAVE_PDMIC

/**
 * \brief retrieve PDMIC ID from its base address
 * \return PDMIC ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_pdmic_id_from_addr(const Pdmic* addr);

#endif /* CONFIG_HAVE_PDMIC */

/**
 * \brief retrieve PWM ID from its base address
 * \return TC ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_pwm_id_from_addr(const Pwm* addr);

/**
 * \brief retrieve PWM base address from its ID
 * \return TC base address on success, 0 otherwise
 */
extern Pwm* get_pwm_addr_from_id(uint32_t id);

#ifdef CONFIG_HAVE_QSPI

/**
 * \brief retrieve QSPI ID from its base address
 * \return QSPI ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_qspi_id_from_addr(const Qspi* addr);

/**
 * \brief retrieve QSPI memory start from its base address
 * \return QSPI memory start on success, NULL otherwise
 */
extern void *get_qspi_mem_from_addr(const Qspi* addr);

#ifdef CONFIG_HAVE_AESB

/**
 * \brief retrieve QSPI AESB memory start from its base address
 * \return QSPI memory start on success, NULL otherwise
 */
extern void *get_qspi_aesb_mem_from_addr(const Qspi* addr);

#endif /* CONFIG_HAVE_AESB */

#endif /* CONFIG_HAVE_QSPI */

#ifdef CONFIG_HAVE_SDMMC

/**
 * \brief retrieve SDMMC ID from its base address
 * \return SDMMC ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_sdmmc_id_from_addr(const Sdmmc* addr);

/**
 * \brief retrieve SDMMC base address from its ID
 * \return SDMMC base address on success, 0 otherwise
 */
extern Sdmmc* get_sdmmc_addr_from_id(uint32_t id);

#endif /* CONFIG_HAVE_SDMMC */

/**
 * \brief retrieve SPI ID from its base address
 * \return SPI ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_spi_id_from_addr(const Spi* addr);

/**
 * \brief retrieve SPI base address from its ID
 * \return SPI base address on success, 0 otherwise
 */
extern Spi* get_spi_addr_from_id(uint32_t id);

#ifdef CONFIG_HAVE_SSC

/**
 * \brief retrieve SSC ID from its base address
 * \return SSC ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_ssc_id_from_addr(const Ssc* addr);

#endif /* CONFIG_HAVE_SSC */

/**
 * \brief retrieve Timer/Counter ID from its base address
 * \return TC ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_tc_id_from_addr(const Tc* addr, uint8_t channel);

/**
 * \brief retrieve Timer/Counter base address from its ID
 * \return TC base address on success, 0 otherwise
 */
extern Tc* get_tc_addr_from_id(uint32_t id);

/**
 * \brief retrieve TWI ID from its base address
 * \return TWI ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_twi_id_from_addr(const Twi* addr);

/**
 * \brief retrieve TWI base address from its ID
 * \return TWI base address on success, 0 otherwise
 */
extern Twi* get_twi_addr_from_id(uint32_t id);

#ifdef CONFIG_HAVE_UART

/**
 * \brief retrieve UART ID from its base address
 * \return UART ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_uart_id_from_addr(const Uart* addr);

/**
 * \brief retrieve UART base address from its ID
 * \return UART base address on success, 0 otherwise
 */
extern Uart* get_uart_addr_from_id(uint32_t id);

#endif /* CONFIG_HAVE_UART */

/**
 * \brief retrieve USART ID from its base address
 * \return USART ID on success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_usart_id_from_addr(const Usart* addr);

/**
 * \brief retrieve USART base address from its ID
 * \return USART base address on success, 0 otherwise
 */
extern Usart* get_usart_addr_from_id(uint32_t id);

#ifdef CONFIG_HAVE_XDMAC

/**
 * \brief retrieve XDMAC ID from its base address
 * \return XDMAC ID upon success, ID_PERIPH_COUNT otherwise
 */
extern uint32_t get_xdmac_id_from_addr(const Xdmac* addr);

/**
 * \brief retrieve XDMAC base address from its ID
 * \return XDMAC base address on success, 0 otherwise
 */
extern Xdmac* get_xdmac_addr_from_id(uint32_t id);

#endif /* CONFIG_HAVE_XDMAC */

#endif /* _CHIP_COMMON_H_ */
