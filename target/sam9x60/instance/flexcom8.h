/* ---------------------------------------------------------------------------- */
/*                Microchip Microcontroller Software Support                    */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) %copyright_year%, Microchip Technology Inc.                    */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Microchip's name may not be used to endorse or promote products derived from */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY MICROCHIP "AS IS" AND ANY EXPRESS  */
/* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES */
/* OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT    */
/* ARE DISCLAIMED. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY DIRECT,        */
/* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES           */
/* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; */
/* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND  */
/* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF     */
/* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.            */
/* ---------------------------------------------------------------------------- */

#ifndef _SAM9X_FLEXCOM8_INSTANCE_
#define _SAM9X_FLEXCOM8_INSTANCE_

/* ========== Register definition for FLEXCOM8 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM8_MR                           (0xF8018000U) /**< \brief (FLEXCOM8) FLEXCOM Mode Register */
  #define REG_FLEXCOM8_RHR                          (0xF8018010U) /**< \brief (FLEXCOM8) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM8_THR                          (0xF8018020U) /**< \brief (FLEXCOM8) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM8_US_CR                        (0xF8018200U) /**< \brief (FLEXCOM8) USART Control Register */
  #define REG_FLEXCOM8_US_MR                        (0xF8018204U) /**< \brief (FLEXCOM8) USART Mode Register */
  #define REG_FLEXCOM8_US_IER                       (0xF8018208U) /**< \brief (FLEXCOM8) USART Interrupt Enable Register */
  #define REG_FLEXCOM8_US_IDR                       (0xF801820CU) /**< \brief (FLEXCOM8) USART Interrupt Disable Register */
  #define REG_FLEXCOM8_US_IMR                       (0xF8018210U) /**< \brief (FLEXCOM8) USART Interrupt Mask Register */
  #define REG_FLEXCOM8_US_CSR                       (0xF8018214U) /**< \brief (FLEXCOM8) USART Channel Status Register */
  #define REG_FLEXCOM8_US_RHR                       (0xF8018218U) /**< \brief (FLEXCOM8) USART Receive Holding Register */
  #define REG_FLEXCOM8_US_THR                       (0xF801821CU) /**< \brief (FLEXCOM8) USART Transmit Holding Register */
  #define REG_FLEXCOM8_US_BRGR                      (0xF8018220U) /**< \brief (FLEXCOM8) USART Baud Rate Generator Register */
  #define REG_FLEXCOM8_US_RTOR                      (0xF8018224U) /**< \brief (FLEXCOM8) USART Receiver Timeout Register */
  #define REG_FLEXCOM8_US_TTGR                      (0xF8018228U) /**< \brief (FLEXCOM8) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM8_US_FIDI                      (0xF8018240U) /**< \brief (FLEXCOM8) USART FI DI Ratio Register */
  #define REG_FLEXCOM8_US_NER                       (0xF8018244U) /**< \brief (FLEXCOM8) USART Number of Errors Register */
  #define REG_FLEXCOM8_US_IF                        (0xF801824CU) /**< \brief (FLEXCOM8) USART IrDA Filter Register */
  #define REG_FLEXCOM8_US_MAN                       (0xF8018250U) /**< \brief (FLEXCOM8) USART Manchester Configuration Register */
  #define REG_FLEXCOM8_US_LINMR                     (0xF8018254U) /**< \brief (FLEXCOM8) USART LIN Mode Register */
  #define REG_FLEXCOM8_US_LINIR                     (0xF8018258U) /**< \brief (FLEXCOM8) USART LIN Identifier Register */
  #define REG_FLEXCOM8_US_LINBRR                    (0xF801825CU) /**< \brief (FLEXCOM8) USART LIN Baud Rate Register */
  #define REG_FLEXCOM8_US_LONMR                     (0xF8018260U) /**< \brief (FLEXCOM8) USART LON Mode Register */
  #define REG_FLEXCOM8_US_LONPR                     (0xF8018264U) /**< \brief (FLEXCOM8) USART LON Preamble Register */
  #define REG_FLEXCOM8_US_LONDL                     (0xF8018268U) /**< \brief (FLEXCOM8) USART LON Data Length Register */
  #define REG_FLEXCOM8_US_LONL2HDR                  (0xF801826CU) /**< \brief (FLEXCOM8) USART LON L2HDR Register */
  #define REG_FLEXCOM8_US_LONBL                     (0xF8018270U) /**< \brief (FLEXCOM8) USART LON Backlog Register */
  #define REG_FLEXCOM8_US_LONB1TX                   (0xF8018274U) /**< \brief (FLEXCOM8) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM8_US_LONB1RX                   (0xF8018278U) /**< \brief (FLEXCOM8) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM8_US_LONPRIO                   (0xF801827CU) /**< \brief (FLEXCOM8) USART LON Priority Register */
  #define REG_FLEXCOM8_US_IDTTX                     (0xF8018280U) /**< \brief (FLEXCOM8) USART LON IDT Tx Register */
  #define REG_FLEXCOM8_US_IDTRX                     (0xF8018284U) /**< \brief (FLEXCOM8) USART LON IDT Rx Register */
  #define REG_FLEXCOM8_US_ICDIFF                    (0xF8018288U) /**< \brief (FLEXCOM8) USART IC DIFF Register */
  #define REG_FLEXCOM8_US_CMPR                      (0xF8018290U) /**< \brief (FLEXCOM8) USART Comparison Register */
  #define REG_FLEXCOM8_US_FMR                       (0xF80182A0U) /**< \brief (FLEXCOM8) USART FIFO Mode Register */
  #define REG_FLEXCOM8_US_FLR                       (0xF80182A4U) /**< \brief (FLEXCOM8) USART FIFO Level Register */
  #define REG_FLEXCOM8_US_FIER                      (0xF80182A8U) /**< \brief (FLEXCOM8) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM8_US_FIDR                      (0xF80182ACU) /**< \brief (FLEXCOM8) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM8_US_FIMR                      (0xF80182B0U) /**< \brief (FLEXCOM8) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM8_US_FESR                      (0xF80182B4U) /**< \brief (FLEXCOM8) USART FIFO Event Status Register */
  #define REG_FLEXCOM8_US_WPMR                      (0xF80182E4U) /**< \brief (FLEXCOM8) USART Write Protection Mode Register */
  #define REG_FLEXCOM8_US_WPSR                      (0xF80182E8U) /**< \brief (FLEXCOM8) USART Write Protection Status Register */
  #define REG_FLEXCOM8_SPI_CR                       (0xF8018400U) /**< \brief (FLEXCOM8) SPI Control Register */
  #define REG_FLEXCOM8_SPI_MR                       (0xF8018404U) /**< \brief (FLEXCOM8) SPI Mode Register */
  #define REG_FLEXCOM8_SPI_RDR                      (0xF8018408U) /**< \brief (FLEXCOM8) SPI Receive Data Register */
  #define REG_FLEXCOM8_SPI_TDR                      (0xF801840CU) /**< \brief (FLEXCOM8) SPI Transmit Data Register */
  #define REG_FLEXCOM8_SPI_SR                       (0xF8018410U) /**< \brief (FLEXCOM8) SPI Status Register */
  #define REG_FLEXCOM8_SPI_IER                      (0xF8018414U) /**< \brief (FLEXCOM8) SPI Interrupt Enable Register */
  #define REG_FLEXCOM8_SPI_IDR                      (0xF8018418U) /**< \brief (FLEXCOM8) SPI Interrupt Disable Register */
  #define REG_FLEXCOM8_SPI_IMR                      (0xF801841CU) /**< \brief (FLEXCOM8) SPI Interrupt Mask Register */
  #define REG_FLEXCOM8_SPI_CSR                      (0xF8018430U) /**< \brief (FLEXCOM8) SPI Chip Select Register */
  #define REG_FLEXCOM8_SPI_FMR                      (0xF8018440U) /**< \brief (FLEXCOM8) SPI FIFO Mode Register */
  #define REG_FLEXCOM8_SPI_FLR                      (0xF8018444U) /**< \brief (FLEXCOM8) SPI FIFO Level Register */
  #define REG_FLEXCOM8_SPI_CMPR                     (0xF8018448U) /**< \brief (FLEXCOM8) SPI Comparison Register */
  #define REG_FLEXCOM8_SPI_WPMR                     (0xF80184E4U) /**< \brief (FLEXCOM8) SPI Write Protection Mode Register */
  #define REG_FLEXCOM8_SPI_WPSR                     (0xF80184E8U) /**< \brief (FLEXCOM8) SPI Write Protection Status Register */
  #define REG_FLEXCOM8_TWI_CR                       (0xF8018600U) /**< \brief (FLEXCOM8) TWI Control Register */
  #define REG_FLEXCOM8_TWI_MMR                      (0xF8018604U) /**< \brief (FLEXCOM8) TWI Master Mode Register */
  #define REG_FLEXCOM8_TWI_SMR                      (0xF8018608U) /**< \brief (FLEXCOM8) TWI Slave Mode Register */
  #define REG_FLEXCOM8_TWI_IADR                     (0xF801860CU) /**< \brief (FLEXCOM8) TWI Internal Address Register */
  #define REG_FLEXCOM8_TWI_CWGR                     (0xF8018610U) /**< \brief (FLEXCOM8) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM8_TWI_SR                       (0xF8018620U) /**< \brief (FLEXCOM8) TWI Status Register */
  #define REG_FLEXCOM8_TWI_IER                      (0xF8018624U) /**< \brief (FLEXCOM8) TWI Interrupt Enable Register */
  #define REG_FLEXCOM8_TWI_IDR                      (0xF8018628U) /**< \brief (FLEXCOM8) TWI Interrupt Disable Register */
  #define REG_FLEXCOM8_TWI_IMR                      (0xF801862CU) /**< \brief (FLEXCOM8) TWI Interrupt Mask Register */
  #define REG_FLEXCOM8_TWI_RHR                      (0xF8018630U) /**< \brief (FLEXCOM8) TWI Receive Holding Register */
  #define REG_FLEXCOM8_TWI_THR                      (0xF8018634U) /**< \brief (FLEXCOM8) TWI Transmit Holding Register */
  #define REG_FLEXCOM8_TWI_SMBTR                    (0xF8018638U) /**< \brief (FLEXCOM8) TWI SMBus Timing Register */
  #define REG_FLEXCOM8_TWI_ACR                      (0xF8018640U) /**< \brief (FLEXCOM8) TWI Alternative Command Register */
  #define REG_FLEXCOM8_TWI_FILTR                    (0xF8018644U) /**< \brief (FLEXCOM8) TWI Filter Register */
  #define REG_FLEXCOM8_TWI_FMR                      (0xF8018650U) /**< \brief (FLEXCOM8) TWI FIFO Mode Register */
  #define REG_FLEXCOM8_TWI_FLR                      (0xF8018654U) /**< \brief (FLEXCOM8) TWI FIFO Level Register */
  #define REG_FLEXCOM8_TWI_FSR                      (0xF8018660U) /**< \brief (FLEXCOM8) TWI FIFO Status Register */
  #define REG_FLEXCOM8_TWI_FIER                     (0xF8018664U) /**< \brief (FLEXCOM8) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM8_TWI_FIDR                     (0xF8018668U) /**< \brief (FLEXCOM8) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM8_TWI_FIMR                     (0xF801866CU) /**< \brief (FLEXCOM8) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM8_TWI_WPMR                     (0xF80186E4U) /**< \brief (FLEXCOM8) TWI Write Protection Mode Register */
  #define REG_FLEXCOM8_TWI_WPSR                     (0xF80186E8U) /**< \brief (FLEXCOM8) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM8_MR          (*(__IO uint32_t*)0xF8018000U) /**< \brief (FLEXCOM8) FLEXCOM Mode Register */
  #define REG_FLEXCOM8_RHR         (*(__I  uint32_t*)0xF8018010U) /**< \brief (FLEXCOM8) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM8_THR         (*(__IO uint32_t*)0xF8018020U) /**< \brief (FLEXCOM8) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM8_US_CR       (*(__O  uint32_t*)0xF8018200U) /**< \brief (FLEXCOM8) USART Control Register */
  #define REG_FLEXCOM8_US_MR       (*(__IO uint32_t*)0xF8018204U) /**< \brief (FLEXCOM8) USART Mode Register */
  #define REG_FLEXCOM8_US_IER      (*(__O  uint32_t*)0xF8018208U) /**< \brief (FLEXCOM8) USART Interrupt Enable Register */
  #define REG_FLEXCOM8_US_IDR      (*(__O  uint32_t*)0xF801820CU) /**< \brief (FLEXCOM8) USART Interrupt Disable Register */
  #define REG_FLEXCOM8_US_IMR      (*(__I  uint32_t*)0xF8018210U) /**< \brief (FLEXCOM8) USART Interrupt Mask Register */
  #define REG_FLEXCOM8_US_CSR      (*(__I  uint32_t*)0xF8018214U) /**< \brief (FLEXCOM8) USART Channel Status Register */
  #define REG_FLEXCOM8_US_RHR      (*(__I  uint32_t*)0xF8018218U) /**< \brief (FLEXCOM8) USART Receive Holding Register */
  #define REG_FLEXCOM8_US_THR      (*(__O  uint32_t*)0xF801821CU) /**< \brief (FLEXCOM8) USART Transmit Holding Register */
  #define REG_FLEXCOM8_US_BRGR     (*(__IO uint32_t*)0xF8018220U) /**< \brief (FLEXCOM8) USART Baud Rate Generator Register */
  #define REG_FLEXCOM8_US_RTOR     (*(__IO uint32_t*)0xF8018224U) /**< \brief (FLEXCOM8) USART Receiver Timeout Register */
  #define REG_FLEXCOM8_US_TTGR     (*(__IO uint32_t*)0xF8018228U) /**< \brief (FLEXCOM8) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM8_US_FIDI     (*(__IO uint32_t*)0xF8018240U) /**< \brief (FLEXCOM8) USART FI DI Ratio Register */
  #define REG_FLEXCOM8_US_NER      (*(__I  uint32_t*)0xF8018244U) /**< \brief (FLEXCOM8) USART Number of Errors Register */
  #define REG_FLEXCOM8_US_IF       (*(__IO uint32_t*)0xF801824CU) /**< \brief (FLEXCOM8) USART IrDA Filter Register */
  #define REG_FLEXCOM8_US_MAN      (*(__IO uint32_t*)0xF8018250U) /**< \brief (FLEXCOM8) USART Manchester Configuration Register */
  #define REG_FLEXCOM8_US_LINMR    (*(__IO uint32_t*)0xF8018254U) /**< \brief (FLEXCOM8) USART LIN Mode Register */
  #define REG_FLEXCOM8_US_LINIR    (*(__IO uint32_t*)0xF8018258U) /**< \brief (FLEXCOM8) USART LIN Identifier Register */
  #define REG_FLEXCOM8_US_LINBRR   (*(__I  uint32_t*)0xF801825CU) /**< \brief (FLEXCOM8) USART LIN Baud Rate Register */
  #define REG_FLEXCOM8_US_LONMR    (*(__IO uint32_t*)0xF8018260U) /**< \brief (FLEXCOM8) USART LON Mode Register */
  #define REG_FLEXCOM8_US_LONPR    (*(__IO uint32_t*)0xF8018264U) /**< \brief (FLEXCOM8) USART LON Preamble Register */
  #define REG_FLEXCOM8_US_LONDL    (*(__IO uint32_t*)0xF8018268U) /**< \brief (FLEXCOM8) USART LON Data Length Register */
  #define REG_FLEXCOM8_US_LONL2HDR (*(__IO uint32_t*)0xF801826CU) /**< \brief (FLEXCOM8) USART LON L2HDR Register */
  #define REG_FLEXCOM8_US_LONBL    (*(__I  uint32_t*)0xF8018270U) /**< \brief (FLEXCOM8) USART LON Backlog Register */
  #define REG_FLEXCOM8_US_LONB1TX  (*(__IO uint32_t*)0xF8018274U) /**< \brief (FLEXCOM8) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM8_US_LONB1RX  (*(__IO uint32_t*)0xF8018278U) /**< \brief (FLEXCOM8) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM8_US_LONPRIO  (*(__IO uint32_t*)0xF801827CU) /**< \brief (FLEXCOM8) USART LON Priority Register */
  #define REG_FLEXCOM8_US_IDTTX    (*(__IO uint32_t*)0xF8018280U) /**< \brief (FLEXCOM8) USART LON IDT Tx Register */
  #define REG_FLEXCOM8_US_IDTRX    (*(__IO uint32_t*)0xF8018284U) /**< \brief (FLEXCOM8) USART LON IDT Rx Register */
  #define REG_FLEXCOM8_US_ICDIFF   (*(__IO uint32_t*)0xF8018288U) /**< \brief (FLEXCOM8) USART IC DIFF Register */
  #define REG_FLEXCOM8_US_CMPR     (*(__IO uint32_t*)0xF8018290U) /**< \brief (FLEXCOM8) USART Comparison Register */
  #define REG_FLEXCOM8_US_FMR      (*(__IO uint32_t*)0xF80182A0U) /**< \brief (FLEXCOM8) USART FIFO Mode Register */
  #define REG_FLEXCOM8_US_FLR      (*(__I  uint32_t*)0xF80182A4U) /**< \brief (FLEXCOM8) USART FIFO Level Register */
  #define REG_FLEXCOM8_US_FIER     (*(__O  uint32_t*)0xF80182A8U) /**< \brief (FLEXCOM8) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM8_US_FIDR     (*(__O  uint32_t*)0xF80182ACU) /**< \brief (FLEXCOM8) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM8_US_FIMR     (*(__I  uint32_t*)0xF80182B0U) /**< \brief (FLEXCOM8) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM8_US_FESR     (*(__I  uint32_t*)0xF80182B4U) /**< \brief (FLEXCOM8) USART FIFO Event Status Register */
  #define REG_FLEXCOM8_US_WPMR     (*(__IO uint32_t*)0xF80182E4U) /**< \brief (FLEXCOM8) USART Write Protection Mode Register */
  #define REG_FLEXCOM8_US_WPSR     (*(__I  uint32_t*)0xF80182E8U) /**< \brief (FLEXCOM8) USART Write Protection Status Register */
  #define REG_FLEXCOM8_SPI_CR      (*(__O  uint32_t*)0xF8018400U) /**< \brief (FLEXCOM8) SPI Control Register */
  #define REG_FLEXCOM8_SPI_MR      (*(__IO uint32_t*)0xF8018404U) /**< \brief (FLEXCOM8) SPI Mode Register */
  #define REG_FLEXCOM8_SPI_RDR     (*(__I  uint32_t*)0xF8018408U) /**< \brief (FLEXCOM8) SPI Receive Data Register */
  #define REG_FLEXCOM8_SPI_TDR     (*(__O  uint32_t*)0xF801840CU) /**< \brief (FLEXCOM8) SPI Transmit Data Register */
  #define REG_FLEXCOM8_SPI_SR      (*(__I  uint32_t*)0xF8018410U) /**< \brief (FLEXCOM8) SPI Status Register */
  #define REG_FLEXCOM8_SPI_IER     (*(__O  uint32_t*)0xF8018414U) /**< \brief (FLEXCOM8) SPI Interrupt Enable Register */
  #define REG_FLEXCOM8_SPI_IDR     (*(__O  uint32_t*)0xF8018418U) /**< \brief (FLEXCOM8) SPI Interrupt Disable Register */
  #define REG_FLEXCOM8_SPI_IMR     (*(__I  uint32_t*)0xF801841CU) /**< \brief (FLEXCOM8) SPI Interrupt Mask Register */
  #define REG_FLEXCOM8_SPI_CSR     (*(__IO uint32_t*)0xF8018430U) /**< \brief (FLEXCOM8) SPI Chip Select Register */
  #define REG_FLEXCOM8_SPI_FMR     (*(__IO uint32_t*)0xF8018440U) /**< \brief (FLEXCOM8) SPI FIFO Mode Register */
  #define REG_FLEXCOM8_SPI_FLR     (*(__I  uint32_t*)0xF8018444U) /**< \brief (FLEXCOM8) SPI FIFO Level Register */
  #define REG_FLEXCOM8_SPI_CMPR    (*(__IO uint32_t*)0xF8018448U) /**< \brief (FLEXCOM8) SPI Comparison Register */
  #define REG_FLEXCOM8_SPI_WPMR    (*(__IO uint32_t*)0xF80184E4U) /**< \brief (FLEXCOM8) SPI Write Protection Mode Register */
  #define REG_FLEXCOM8_SPI_WPSR    (*(__I  uint32_t*)0xF80184E8U) /**< \brief (FLEXCOM8) SPI Write Protection Status Register */
  #define REG_FLEXCOM8_TWI_CR      (*(__O  uint32_t*)0xF8018600U) /**< \brief (FLEXCOM8) TWI Control Register */
  #define REG_FLEXCOM8_TWI_MMR     (*(__IO uint32_t*)0xF8018604U) /**< \brief (FLEXCOM8) TWI Master Mode Register */
  #define REG_FLEXCOM8_TWI_SMR     (*(__IO uint32_t*)0xF8018608U) /**< \brief (FLEXCOM8) TWI Slave Mode Register */
  #define REG_FLEXCOM8_TWI_IADR    (*(__IO uint32_t*)0xF801860CU) /**< \brief (FLEXCOM8) TWI Internal Address Register */
  #define REG_FLEXCOM8_TWI_CWGR    (*(__IO uint32_t*)0xF8018610U) /**< \brief (FLEXCOM8) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM8_TWI_SR      (*(__I  uint32_t*)0xF8018620U) /**< \brief (FLEXCOM8) TWI Status Register */
  #define REG_FLEXCOM8_TWI_IER     (*(__O  uint32_t*)0xF8018624U) /**< \brief (FLEXCOM8) TWI Interrupt Enable Register */
  #define REG_FLEXCOM8_TWI_IDR     (*(__O  uint32_t*)0xF8018628U) /**< \brief (FLEXCOM8) TWI Interrupt Disable Register */
  #define REG_FLEXCOM8_TWI_IMR     (*(__I  uint32_t*)0xF801862CU) /**< \brief (FLEXCOM8) TWI Interrupt Mask Register */
  #define REG_FLEXCOM8_TWI_RHR     (*(__I  uint32_t*)0xF8018630U) /**< \brief (FLEXCOM8) TWI Receive Holding Register */
  #define REG_FLEXCOM8_TWI_THR     (*(__O  uint32_t*)0xF8018634U) /**< \brief (FLEXCOM8) TWI Transmit Holding Register */
  #define REG_FLEXCOM8_TWI_SMBTR   (*(__IO uint32_t*)0xF8018638U) /**< \brief (FLEXCOM8) TWI SMBus Timing Register */
  #define REG_FLEXCOM8_TWI_ACR     (*(__IO uint32_t*)0xF8018640U) /**< \brief (FLEXCOM8) TWI Alternative Command Register */
  #define REG_FLEXCOM8_TWI_FILTR   (*(__IO uint32_t*)0xF8018644U) /**< \brief (FLEXCOM8) TWI Filter Register */
  #define REG_FLEXCOM8_TWI_FMR     (*(__IO uint32_t*)0xF8018650U) /**< \brief (FLEXCOM8) TWI FIFO Mode Register */
  #define REG_FLEXCOM8_TWI_FLR     (*(__I  uint32_t*)0xF8018654U) /**< \brief (FLEXCOM8) TWI FIFO Level Register */
  #define REG_FLEXCOM8_TWI_FSR     (*(__I  uint32_t*)0xF8018660U) /**< \brief (FLEXCOM8) TWI FIFO Status Register */
  #define REG_FLEXCOM8_TWI_FIER    (*(__O  uint32_t*)0xF8018664U) /**< \brief (FLEXCOM8) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM8_TWI_FIDR    (*(__O  uint32_t*)0xF8018668U) /**< \brief (FLEXCOM8) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM8_TWI_FIMR    (*(__I  uint32_t*)0xF801866CU) /**< \brief (FLEXCOM8) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM8_TWI_WPMR    (*(__IO uint32_t*)0xF80186E4U) /**< \brief (FLEXCOM8) TWI Write Protection Mode Register */
  #define REG_FLEXCOM8_TWI_WPSR    (*(__I  uint32_t*)0xF80186E8U) /**< \brief (FLEXCOM8) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM8_INSTANCE_ */
