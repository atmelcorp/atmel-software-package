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

#ifndef _SAM9X_FLEXCOM2_INSTANCE_
#define _SAM9X_FLEXCOM2_INSTANCE_

/* ========== Register definition for FLEXCOM2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM2_MR                           (0xF8024000U) /**< \brief (FLEXCOM2) FLEXCOM Mode Register */
  #define REG_FLEXCOM2_RHR                          (0xF8024010U) /**< \brief (FLEXCOM2) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM2_THR                          (0xF8024020U) /**< \brief (FLEXCOM2) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM2_US_CR                        (0xF8024200U) /**< \brief (FLEXCOM2) USART Control Register */
  #define REG_FLEXCOM2_US_MR                        (0xF8024204U) /**< \brief (FLEXCOM2) USART Mode Register */
  #define REG_FLEXCOM2_US_IER                       (0xF8024208U) /**< \brief (FLEXCOM2) USART Interrupt Enable Register */
  #define REG_FLEXCOM2_US_IDR                       (0xF802420CU) /**< \brief (FLEXCOM2) USART Interrupt Disable Register */
  #define REG_FLEXCOM2_US_IMR                       (0xF8024210U) /**< \brief (FLEXCOM2) USART Interrupt Mask Register */
  #define REG_FLEXCOM2_US_CSR                       (0xF8024214U) /**< \brief (FLEXCOM2) USART Channel Status Register */
  #define REG_FLEXCOM2_US_RHR                       (0xF8024218U) /**< \brief (FLEXCOM2) USART Receive Holding Register */
  #define REG_FLEXCOM2_US_THR                       (0xF802421CU) /**< \brief (FLEXCOM2) USART Transmit Holding Register */
  #define REG_FLEXCOM2_US_BRGR                      (0xF8024220U) /**< \brief (FLEXCOM2) USART Baud Rate Generator Register */
  #define REG_FLEXCOM2_US_RTOR                      (0xF8024224U) /**< \brief (FLEXCOM2) USART Receiver Timeout Register */
  #define REG_FLEXCOM2_US_TTGR                      (0xF8024228U) /**< \brief (FLEXCOM2) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM2_US_FIDI                      (0xF8024240U) /**< \brief (FLEXCOM2) USART FI DI Ratio Register */
  #define REG_FLEXCOM2_US_NER                       (0xF8024244U) /**< \brief (FLEXCOM2) USART Number of Errors Register */
  #define REG_FLEXCOM2_US_IF                        (0xF802424CU) /**< \brief (FLEXCOM2) USART IrDA Filter Register */
  #define REG_FLEXCOM2_US_MAN                       (0xF8024250U) /**< \brief (FLEXCOM2) USART Manchester Configuration Register */
  #define REG_FLEXCOM2_US_LINMR                     (0xF8024254U) /**< \brief (FLEXCOM2) USART LIN Mode Register */
  #define REG_FLEXCOM2_US_LINIR                     (0xF8024258U) /**< \brief (FLEXCOM2) USART LIN Identifier Register */
  #define REG_FLEXCOM2_US_LINBRR                    (0xF802425CU) /**< \brief (FLEXCOM2) USART LIN Baud Rate Register */
  #define REG_FLEXCOM2_US_LONMR                     (0xF8024260U) /**< \brief (FLEXCOM2) USART LON Mode Register */
  #define REG_FLEXCOM2_US_LONPR                     (0xF8024264U) /**< \brief (FLEXCOM2) USART LON Preamble Register */
  #define REG_FLEXCOM2_US_LONDL                     (0xF8024268U) /**< \brief (FLEXCOM2) USART LON Data Length Register */
  #define REG_FLEXCOM2_US_LONL2HDR                  (0xF802426CU) /**< \brief (FLEXCOM2) USART LON L2HDR Register */
  #define REG_FLEXCOM2_US_LONBL                     (0xF8024270U) /**< \brief (FLEXCOM2) USART LON Backlog Register */
  #define REG_FLEXCOM2_US_LONB1TX                   (0xF8024274U) /**< \brief (FLEXCOM2) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM2_US_LONB1RX                   (0xF8024278U) /**< \brief (FLEXCOM2) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM2_US_LONPRIO                   (0xF802427CU) /**< \brief (FLEXCOM2) USART LON Priority Register */
  #define REG_FLEXCOM2_US_IDTTX                     (0xF8024280U) /**< \brief (FLEXCOM2) USART LON IDT Tx Register */
  #define REG_FLEXCOM2_US_IDTRX                     (0xF8024284U) /**< \brief (FLEXCOM2) USART LON IDT Rx Register */
  #define REG_FLEXCOM2_US_ICDIFF                    (0xF8024288U) /**< \brief (FLEXCOM2) USART IC DIFF Register */
  #define REG_FLEXCOM2_US_CMPR                      (0xF8024290U) /**< \brief (FLEXCOM2) USART Comparison Register */
  #define REG_FLEXCOM2_US_FMR                       (0xF80242A0U) /**< \brief (FLEXCOM2) USART FIFO Mode Register */
  #define REG_FLEXCOM2_US_FLR                       (0xF80242A4U) /**< \brief (FLEXCOM2) USART FIFO Level Register */
  #define REG_FLEXCOM2_US_FIER                      (0xF80242A8U) /**< \brief (FLEXCOM2) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM2_US_FIDR                      (0xF80242ACU) /**< \brief (FLEXCOM2) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM2_US_FIMR                      (0xF80242B0U) /**< \brief (FLEXCOM2) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM2_US_FESR                      (0xF80242B4U) /**< \brief (FLEXCOM2) USART FIFO Event Status Register */
  #define REG_FLEXCOM2_US_WPMR                      (0xF80242E4U) /**< \brief (FLEXCOM2) USART Write Protection Mode Register */
  #define REG_FLEXCOM2_US_WPSR                      (0xF80242E8U) /**< \brief (FLEXCOM2) USART Write Protection Status Register */
  #define REG_FLEXCOM2_SPI_CR                       (0xF8024400U) /**< \brief (FLEXCOM2) SPI Control Register */
  #define REG_FLEXCOM2_SPI_MR                       (0xF8024404U) /**< \brief (FLEXCOM2) SPI Mode Register */
  #define REG_FLEXCOM2_SPI_RDR                      (0xF8024408U) /**< \brief (FLEXCOM2) SPI Receive Data Register */
  #define REG_FLEXCOM2_SPI_TDR                      (0xF802440CU) /**< \brief (FLEXCOM2) SPI Transmit Data Register */
  #define REG_FLEXCOM2_SPI_SR                       (0xF8024410U) /**< \brief (FLEXCOM2) SPI Status Register */
  #define REG_FLEXCOM2_SPI_IER                      (0xF8024414U) /**< \brief (FLEXCOM2) SPI Interrupt Enable Register */
  #define REG_FLEXCOM2_SPI_IDR                      (0xF8024418U) /**< \brief (FLEXCOM2) SPI Interrupt Disable Register */
  #define REG_FLEXCOM2_SPI_IMR                      (0xF802441CU) /**< \brief (FLEXCOM2) SPI Interrupt Mask Register */
  #define REG_FLEXCOM2_SPI_CSR                      (0xF8024430U) /**< \brief (FLEXCOM2) SPI Chip Select Register */
  #define REG_FLEXCOM2_SPI_FMR                      (0xF8024440U) /**< \brief (FLEXCOM2) SPI FIFO Mode Register */
  #define REG_FLEXCOM2_SPI_FLR                      (0xF8024444U) /**< \brief (FLEXCOM2) SPI FIFO Level Register */
  #define REG_FLEXCOM2_SPI_CMPR                     (0xF8024448U) /**< \brief (FLEXCOM2) SPI Comparison Register */
  #define REG_FLEXCOM2_SPI_WPMR                     (0xF80244E4U) /**< \brief (FLEXCOM2) SPI Write Protection Mode Register */
  #define REG_FLEXCOM2_SPI_WPSR                     (0xF80244E8U) /**< \brief (FLEXCOM2) SPI Write Protection Status Register */
  #define REG_FLEXCOM2_TWI_CR                       (0xF8024600U) /**< \brief (FLEXCOM2) TWI Control Register */
  #define REG_FLEXCOM2_TWI_MMR                      (0xF8024604U) /**< \brief (FLEXCOM2) TWI Master Mode Register */
  #define REG_FLEXCOM2_TWI_SMR                      (0xF8024608U) /**< \brief (FLEXCOM2) TWI Slave Mode Register */
  #define REG_FLEXCOM2_TWI_IADR                     (0xF802460CU) /**< \brief (FLEXCOM2) TWI Internal Address Register */
  #define REG_FLEXCOM2_TWI_CWGR                     (0xF8024610U) /**< \brief (FLEXCOM2) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM2_TWI_SR                       (0xF8024620U) /**< \brief (FLEXCOM2) TWI Status Register */
  #define REG_FLEXCOM2_TWI_IER                      (0xF8024624U) /**< \brief (FLEXCOM2) TWI Interrupt Enable Register */
  #define REG_FLEXCOM2_TWI_IDR                      (0xF8024628U) /**< \brief (FLEXCOM2) TWI Interrupt Disable Register */
  #define REG_FLEXCOM2_TWI_IMR                      (0xF802462CU) /**< \brief (FLEXCOM2) TWI Interrupt Mask Register */
  #define REG_FLEXCOM2_TWI_RHR                      (0xF8024630U) /**< \brief (FLEXCOM2) TWI Receive Holding Register */
  #define REG_FLEXCOM2_TWI_THR                      (0xF8024634U) /**< \brief (FLEXCOM2) TWI Transmit Holding Register */
  #define REG_FLEXCOM2_TWI_SMBTR                    (0xF8024638U) /**< \brief (FLEXCOM2) TWI SMBus Timing Register */
  #define REG_FLEXCOM2_TWI_ACR                      (0xF8024640U) /**< \brief (FLEXCOM2) TWI Alternative Command Register */
  #define REG_FLEXCOM2_TWI_FILTR                    (0xF8024644U) /**< \brief (FLEXCOM2) TWI Filter Register */
  #define REG_FLEXCOM2_TWI_FMR                      (0xF8024650U) /**< \brief (FLEXCOM2) TWI FIFO Mode Register */
  #define REG_FLEXCOM2_TWI_FLR                      (0xF8024654U) /**< \brief (FLEXCOM2) TWI FIFO Level Register */
  #define REG_FLEXCOM2_TWI_FSR                      (0xF8024660U) /**< \brief (FLEXCOM2) TWI FIFO Status Register */
  #define REG_FLEXCOM2_TWI_FIER                     (0xF8024664U) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM2_TWI_FIDR                     (0xF8024668U) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM2_TWI_FIMR                     (0xF802466CU) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM2_TWI_WPMR                     (0xF80246E4U) /**< \brief (FLEXCOM2) TWI Write Protection Mode Register */
  #define REG_FLEXCOM2_TWI_WPSR                     (0xF80246E8U) /**< \brief (FLEXCOM2) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM2_MR          (*(__IO uint32_t*)0xF8024000U) /**< \brief (FLEXCOM2) FLEXCOM Mode Register */
  #define REG_FLEXCOM2_RHR         (*(__I  uint32_t*)0xF8024010U) /**< \brief (FLEXCOM2) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM2_THR         (*(__IO uint32_t*)0xF8024020U) /**< \brief (FLEXCOM2) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM2_US_CR       (*(__O  uint32_t*)0xF8024200U) /**< \brief (FLEXCOM2) USART Control Register */
  #define REG_FLEXCOM2_US_MR       (*(__IO uint32_t*)0xF8024204U) /**< \brief (FLEXCOM2) USART Mode Register */
  #define REG_FLEXCOM2_US_IER      (*(__O  uint32_t*)0xF8024208U) /**< \brief (FLEXCOM2) USART Interrupt Enable Register */
  #define REG_FLEXCOM2_US_IDR      (*(__O  uint32_t*)0xF802420CU) /**< \brief (FLEXCOM2) USART Interrupt Disable Register */
  #define REG_FLEXCOM2_US_IMR      (*(__I  uint32_t*)0xF8024210U) /**< \brief (FLEXCOM2) USART Interrupt Mask Register */
  #define REG_FLEXCOM2_US_CSR      (*(__I  uint32_t*)0xF8024214U) /**< \brief (FLEXCOM2) USART Channel Status Register */
  #define REG_FLEXCOM2_US_RHR      (*(__I  uint32_t*)0xF8024218U) /**< \brief (FLEXCOM2) USART Receive Holding Register */
  #define REG_FLEXCOM2_US_THR      (*(__O  uint32_t*)0xF802421CU) /**< \brief (FLEXCOM2) USART Transmit Holding Register */
  #define REG_FLEXCOM2_US_BRGR     (*(__IO uint32_t*)0xF8024220U) /**< \brief (FLEXCOM2) USART Baud Rate Generator Register */
  #define REG_FLEXCOM2_US_RTOR     (*(__IO uint32_t*)0xF8024224U) /**< \brief (FLEXCOM2) USART Receiver Timeout Register */
  #define REG_FLEXCOM2_US_TTGR     (*(__IO uint32_t*)0xF8024228U) /**< \brief (FLEXCOM2) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM2_US_FIDI     (*(__IO uint32_t*)0xF8024240U) /**< \brief (FLEXCOM2) USART FI DI Ratio Register */
  #define REG_FLEXCOM2_US_NER      (*(__I  uint32_t*)0xF8024244U) /**< \brief (FLEXCOM2) USART Number of Errors Register */
  #define REG_FLEXCOM2_US_IF       (*(__IO uint32_t*)0xF802424CU) /**< \brief (FLEXCOM2) USART IrDA Filter Register */
  #define REG_FLEXCOM2_US_MAN      (*(__IO uint32_t*)0xF8024250U) /**< \brief (FLEXCOM2) USART Manchester Configuration Register */
  #define REG_FLEXCOM2_US_LINMR    (*(__IO uint32_t*)0xF8024254U) /**< \brief (FLEXCOM2) USART LIN Mode Register */
  #define REG_FLEXCOM2_US_LINIR    (*(__IO uint32_t*)0xF8024258U) /**< \brief (FLEXCOM2) USART LIN Identifier Register */
  #define REG_FLEXCOM2_US_LINBRR   (*(__I  uint32_t*)0xF802425CU) /**< \brief (FLEXCOM2) USART LIN Baud Rate Register */
  #define REG_FLEXCOM2_US_LONMR    (*(__IO uint32_t*)0xF8024260U) /**< \brief (FLEXCOM2) USART LON Mode Register */
  #define REG_FLEXCOM2_US_LONPR    (*(__IO uint32_t*)0xF8024264U) /**< \brief (FLEXCOM2) USART LON Preamble Register */
  #define REG_FLEXCOM2_US_LONDL    (*(__IO uint32_t*)0xF8024268U) /**< \brief (FLEXCOM2) USART LON Data Length Register */
  #define REG_FLEXCOM2_US_LONL2HDR (*(__IO uint32_t*)0xF802426CU) /**< \brief (FLEXCOM2) USART LON L2HDR Register */
  #define REG_FLEXCOM2_US_LONBL    (*(__I  uint32_t*)0xF8024270U) /**< \brief (FLEXCOM2) USART LON Backlog Register */
  #define REG_FLEXCOM2_US_LONB1TX  (*(__IO uint32_t*)0xF8024274U) /**< \brief (FLEXCOM2) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM2_US_LONB1RX  (*(__IO uint32_t*)0xF8024278U) /**< \brief (FLEXCOM2) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM2_US_LONPRIO  (*(__IO uint32_t*)0xF802427CU) /**< \brief (FLEXCOM2) USART LON Priority Register */
  #define REG_FLEXCOM2_US_IDTTX    (*(__IO uint32_t*)0xF8024280U) /**< \brief (FLEXCOM2) USART LON IDT Tx Register */
  #define REG_FLEXCOM2_US_IDTRX    (*(__IO uint32_t*)0xF8024284U) /**< \brief (FLEXCOM2) USART LON IDT Rx Register */
  #define REG_FLEXCOM2_US_ICDIFF   (*(__IO uint32_t*)0xF8024288U) /**< \brief (FLEXCOM2) USART IC DIFF Register */
  #define REG_FLEXCOM2_US_CMPR     (*(__IO uint32_t*)0xF8024290U) /**< \brief (FLEXCOM2) USART Comparison Register */
  #define REG_FLEXCOM2_US_FMR      (*(__IO uint32_t*)0xF80242A0U) /**< \brief (FLEXCOM2) USART FIFO Mode Register */
  #define REG_FLEXCOM2_US_FLR      (*(__I  uint32_t*)0xF80242A4U) /**< \brief (FLEXCOM2) USART FIFO Level Register */
  #define REG_FLEXCOM2_US_FIER     (*(__O  uint32_t*)0xF80242A8U) /**< \brief (FLEXCOM2) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM2_US_FIDR     (*(__O  uint32_t*)0xF80242ACU) /**< \brief (FLEXCOM2) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM2_US_FIMR     (*(__I  uint32_t*)0xF80242B0U) /**< \brief (FLEXCOM2) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM2_US_FESR     (*(__I  uint32_t*)0xF80242B4U) /**< \brief (FLEXCOM2) USART FIFO Event Status Register */
  #define REG_FLEXCOM2_US_WPMR     (*(__IO uint32_t*)0xF80242E4U) /**< \brief (FLEXCOM2) USART Write Protection Mode Register */
  #define REG_FLEXCOM2_US_WPSR     (*(__I  uint32_t*)0xF80242E8U) /**< \brief (FLEXCOM2) USART Write Protection Status Register */
  #define REG_FLEXCOM2_SPI_CR      (*(__O  uint32_t*)0xF8024400U) /**< \brief (FLEXCOM2) SPI Control Register */
  #define REG_FLEXCOM2_SPI_MR      (*(__IO uint32_t*)0xF8024404U) /**< \brief (FLEXCOM2) SPI Mode Register */
  #define REG_FLEXCOM2_SPI_RDR     (*(__I  uint32_t*)0xF8024408U) /**< \brief (FLEXCOM2) SPI Receive Data Register */
  #define REG_FLEXCOM2_SPI_TDR     (*(__O  uint32_t*)0xF802440CU) /**< \brief (FLEXCOM2) SPI Transmit Data Register */
  #define REG_FLEXCOM2_SPI_SR      (*(__I  uint32_t*)0xF8024410U) /**< \brief (FLEXCOM2) SPI Status Register */
  #define REG_FLEXCOM2_SPI_IER     (*(__O  uint32_t*)0xF8024414U) /**< \brief (FLEXCOM2) SPI Interrupt Enable Register */
  #define REG_FLEXCOM2_SPI_IDR     (*(__O  uint32_t*)0xF8024418U) /**< \brief (FLEXCOM2) SPI Interrupt Disable Register */
  #define REG_FLEXCOM2_SPI_IMR     (*(__I  uint32_t*)0xF802441CU) /**< \brief (FLEXCOM2) SPI Interrupt Mask Register */
  #define REG_FLEXCOM2_SPI_CSR     (*(__IO uint32_t*)0xF8024430U) /**< \brief (FLEXCOM2) SPI Chip Select Register */
  #define REG_FLEXCOM2_SPI_FMR     (*(__IO uint32_t*)0xF8024440U) /**< \brief (FLEXCOM2) SPI FIFO Mode Register */
  #define REG_FLEXCOM2_SPI_FLR     (*(__I  uint32_t*)0xF8024444U) /**< \brief (FLEXCOM2) SPI FIFO Level Register */
  #define REG_FLEXCOM2_SPI_CMPR    (*(__IO uint32_t*)0xF8024448U) /**< \brief (FLEXCOM2) SPI Comparison Register */
  #define REG_FLEXCOM2_SPI_WPMR    (*(__IO uint32_t*)0xF80244E4U) /**< \brief (FLEXCOM2) SPI Write Protection Mode Register */
  #define REG_FLEXCOM2_SPI_WPSR    (*(__I  uint32_t*)0xF80244E8U) /**< \brief (FLEXCOM2) SPI Write Protection Status Register */
  #define REG_FLEXCOM2_TWI_CR      (*(__O  uint32_t*)0xF8024600U) /**< \brief (FLEXCOM2) TWI Control Register */
  #define REG_FLEXCOM2_TWI_MMR     (*(__IO uint32_t*)0xF8024604U) /**< \brief (FLEXCOM2) TWI Master Mode Register */
  #define REG_FLEXCOM2_TWI_SMR     (*(__IO uint32_t*)0xF8024608U) /**< \brief (FLEXCOM2) TWI Slave Mode Register */
  #define REG_FLEXCOM2_TWI_IADR    (*(__IO uint32_t*)0xF802460CU) /**< \brief (FLEXCOM2) TWI Internal Address Register */
  #define REG_FLEXCOM2_TWI_CWGR    (*(__IO uint32_t*)0xF8024610U) /**< \brief (FLEXCOM2) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM2_TWI_SR      (*(__I  uint32_t*)0xF8024620U) /**< \brief (FLEXCOM2) TWI Status Register */
  #define REG_FLEXCOM2_TWI_IER     (*(__O  uint32_t*)0xF8024624U) /**< \brief (FLEXCOM2) TWI Interrupt Enable Register */
  #define REG_FLEXCOM2_TWI_IDR     (*(__O  uint32_t*)0xF8024628U) /**< \brief (FLEXCOM2) TWI Interrupt Disable Register */
  #define REG_FLEXCOM2_TWI_IMR     (*(__I  uint32_t*)0xF802462CU) /**< \brief (FLEXCOM2) TWI Interrupt Mask Register */
  #define REG_FLEXCOM2_TWI_RHR     (*(__I  uint32_t*)0xF8024630U) /**< \brief (FLEXCOM2) TWI Receive Holding Register */
  #define REG_FLEXCOM2_TWI_THR     (*(__O  uint32_t*)0xF8024634U) /**< \brief (FLEXCOM2) TWI Transmit Holding Register */
  #define REG_FLEXCOM2_TWI_SMBTR   (*(__IO uint32_t*)0xF8024638U) /**< \brief (FLEXCOM2) TWI SMBus Timing Register */
  #define REG_FLEXCOM2_TWI_ACR     (*(__IO uint32_t*)0xF8024640U) /**< \brief (FLEXCOM2) TWI Alternative Command Register */
  #define REG_FLEXCOM2_TWI_FILTR   (*(__IO uint32_t*)0xF8024644U) /**< \brief (FLEXCOM2) TWI Filter Register */
  #define REG_FLEXCOM2_TWI_FMR     (*(__IO uint32_t*)0xF8024650U) /**< \brief (FLEXCOM2) TWI FIFO Mode Register */
  #define REG_FLEXCOM2_TWI_FLR     (*(__I  uint32_t*)0xF8024654U) /**< \brief (FLEXCOM2) TWI FIFO Level Register */
  #define REG_FLEXCOM2_TWI_FSR     (*(__I  uint32_t*)0xF8024660U) /**< \brief (FLEXCOM2) TWI FIFO Status Register */
  #define REG_FLEXCOM2_TWI_FIER    (*(__O  uint32_t*)0xF8024664U) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM2_TWI_FIDR    (*(__O  uint32_t*)0xF8024668U) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM2_TWI_FIMR    (*(__I  uint32_t*)0xF802466CU) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM2_TWI_WPMR    (*(__IO uint32_t*)0xF80246E4U) /**< \brief (FLEXCOM2) TWI Write Protection Mode Register */
  #define REG_FLEXCOM2_TWI_WPSR    (*(__I  uint32_t*)0xF80246E8U) /**< \brief (FLEXCOM2) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM2_INSTANCE_ */
