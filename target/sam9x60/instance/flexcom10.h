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

#ifndef _SAM9X_FLEXCOM10_INSTANCE_
#define _SAM9X_FLEXCOM10_INSTANCE_

/* ========== Register definition for FLEXCOM10 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM10_MR                           (0xF8044000U) /**< \brief (FLEXCOM10) FLEXCOM Mode Register */
  #define REG_FLEXCOM10_RHR                          (0xF8044010U) /**< \brief (FLEXCOM10) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM10_THR                          (0xF8044020U) /**< \brief (FLEXCOM10) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM10_US_CR                        (0xF8044200U) /**< \brief (FLEXCOM10) USART Control Register */
  #define REG_FLEXCOM10_US_MR                        (0xF8044204U) /**< \brief (FLEXCOM10) USART Mode Register */
  #define REG_FLEXCOM10_US_IER                       (0xF8044208U) /**< \brief (FLEXCOM10) USART Interrupt Enable Register */
  #define REG_FLEXCOM10_US_IDR                       (0xF804420CU) /**< \brief (FLEXCOM10) USART Interrupt Disable Register */
  #define REG_FLEXCOM10_US_IMR                       (0xF8044210U) /**< \brief (FLEXCOM10) USART Interrupt Mask Register */
  #define REG_FLEXCOM10_US_CSR                       (0xF8044214U) /**< \brief (FLEXCOM10) USART Channel Status Register */
  #define REG_FLEXCOM10_US_RHR                       (0xF8044218U) /**< \brief (FLEXCOM10) USART Receive Holding Register */
  #define REG_FLEXCOM10_US_THR                       (0xF804421CU) /**< \brief (FLEXCOM10) USART Transmit Holding Register */
  #define REG_FLEXCOM10_US_BRGR                      (0xF8044220U) /**< \brief (FLEXCOM10) USART Baud Rate Generator Register */
  #define REG_FLEXCOM10_US_RTOR                      (0xF8044224U) /**< \brief (FLEXCOM10) USART Receiver Timeout Register */
  #define REG_FLEXCOM10_US_TTGR                      (0xF8044228U) /**< \brief (FLEXCOM10) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM10_US_FIDI                      (0xF8044240U) /**< \brief (FLEXCOM10) USART FI DI Ratio Register */
  #define REG_FLEXCOM10_US_NER                       (0xF8044244U) /**< \brief (FLEXCOM10) USART Number of Errors Register */
  #define REG_FLEXCOM10_US_IF                        (0xF804424CU) /**< \brief (FLEXCOM10) USART IrDA Filter Register */
  #define REG_FLEXCOM10_US_MAN                       (0xF8044250U) /**< \brief (FLEXCOM10) USART Manchester Configuration Register */
  #define REG_FLEXCOM10_US_LINMR                     (0xF8044254U) /**< \brief (FLEXCOM10) USART LIN Mode Register */
  #define REG_FLEXCOM10_US_LINIR                     (0xF8044258U) /**< \brief (FLEXCOM10) USART LIN Identifier Register */
  #define REG_FLEXCOM10_US_LINBRR                    (0xF804425CU) /**< \brief (FLEXCOM10) USART LIN Baud Rate Register */
  #define REG_FLEXCOM10_US_LONMR                     (0xF8044260U) /**< \brief (FLEXCOM10) USART LON Mode Register */
  #define REG_FLEXCOM10_US_LONPR                     (0xF8044264U) /**< \brief (FLEXCOM10) USART LON Preamble Register */
  #define REG_FLEXCOM10_US_LONDL                     (0xF8044268U) /**< \brief (FLEXCOM10) USART LON Data Length Register */
  #define REG_FLEXCOM10_US_LONL2HDR                  (0xF804426CU) /**< \brief (FLEXCOM10) USART LON L2HDR Register */
  #define REG_FLEXCOM10_US_LONBL                     (0xF8044270U) /**< \brief (FLEXCOM10) USART LON Backlog Register */
  #define REG_FLEXCOM10_US_LONB1TX                   (0xF8044274U) /**< \brief (FLEXCOM10) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM10_US_LONB1RX                   (0xF8044278U) /**< \brief (FLEXCOM10) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM10_US_LONPRIO                   (0xF804427CU) /**< \brief (FLEXCOM10) USART LON Priority Register */
  #define REG_FLEXCOM10_US_IDTTX                     (0xF8044280U) /**< \brief (FLEXCOM10) USART LON IDT Tx Register */
  #define REG_FLEXCOM10_US_IDTRX                     (0xF8044284U) /**< \brief (FLEXCOM10) USART LON IDT Rx Register */
  #define REG_FLEXCOM10_US_ICDIFF                    (0xF8044288U) /**< \brief (FLEXCOM10) USART IC DIFF Register */
  #define REG_FLEXCOM10_US_CMPR                      (0xF8044290U) /**< \brief (FLEXCOM10) USART Comparison Register */
  #define REG_FLEXCOM10_US_FMR                       (0xF80442A0U) /**< \brief (FLEXCOM10) USART FIFO Mode Register */
  #define REG_FLEXCOM10_US_FLR                       (0xF80442A4U) /**< \brief (FLEXCOM10) USART FIFO Level Register */
  #define REG_FLEXCOM10_US_FIER                      (0xF80442A8U) /**< \brief (FLEXCOM10) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM10_US_FIDR                      (0xF80442ACU) /**< \brief (FLEXCOM10) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM10_US_FIMR                      (0xF80442B0U) /**< \brief (FLEXCOM10) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM10_US_FESR                      (0xF80442B4U) /**< \brief (FLEXCOM10) USART FIFO Event Status Register */
  #define REG_FLEXCOM10_US_WPMR                      (0xF80442E4U) /**< \brief (FLEXCOM10) USART Write Protection Mode Register */
  #define REG_FLEXCOM10_US_WPSR                      (0xF80442E8U) /**< \brief (FLEXCOM10) USART Write Protection Status Register */
  #define REG_FLEXCOM10_SPI_CR                       (0xF8044400U) /**< \brief (FLEXCOM10) SPI Control Register */
  #define REG_FLEXCOM10_SPI_MR                       (0xF8044404U) /**< \brief (FLEXCOM10) SPI Mode Register */
  #define REG_FLEXCOM10_SPI_RDR                      (0xF8044408U) /**< \brief (FLEXCOM10) SPI Receive Data Register */
  #define REG_FLEXCOM10_SPI_TDR                      (0xF804440CU) /**< \brief (FLEXCOM10) SPI Transmit Data Register */
  #define REG_FLEXCOM10_SPI_SR                       (0xF8044410U) /**< \brief (FLEXCOM10) SPI Status Register */
  #define REG_FLEXCOM10_SPI_IER                      (0xF8044414U) /**< \brief (FLEXCOM10) SPI Interrupt Enable Register */
  #define REG_FLEXCOM10_SPI_IDR                      (0xF8044418U) /**< \brief (FLEXCOM10) SPI Interrupt Disable Register */
  #define REG_FLEXCOM10_SPI_IMR                      (0xF804441CU) /**< \brief (FLEXCOM10) SPI Interrupt Mask Register */
  #define REG_FLEXCOM10_SPI_CSR                      (0xF8044430U) /**< \brief (FLEXCOM10) SPI Chip Select Register */
  #define REG_FLEXCOM10_SPI_FMR                      (0xF8044440U) /**< \brief (FLEXCOM10) SPI FIFO Mode Register */
  #define REG_FLEXCOM10_SPI_FLR                      (0xF8044444U) /**< \brief (FLEXCOM10) SPI FIFO Level Register */
  #define REG_FLEXCOM10_SPI_CMPR                     (0xF8044448U) /**< \brief (FLEXCOM10) SPI Comparison Register */
  #define REG_FLEXCOM10_SPI_WPMR                     (0xF80444E4U) /**< \brief (FLEXCOM10) SPI Write Protection Mode Register */
  #define REG_FLEXCOM10_SPI_WPSR                     (0xF80444E8U) /**< \brief (FLEXCOM10) SPI Write Protection Status Register */
  #define REG_FLEXCOM10_TWI_CR                       (0xF8044600U) /**< \brief (FLEXCOM10) TWI Control Register */
  #define REG_FLEXCOM10_TWI_MMR                      (0xF8044604U) /**< \brief (FLEXCOM10) TWI Master Mode Register */
  #define REG_FLEXCOM10_TWI_SMR                      (0xF8044608U) /**< \brief (FLEXCOM10) TWI Slave Mode Register */
  #define REG_FLEXCOM10_TWI_IADR                     (0xF804460CU) /**< \brief (FLEXCOM10) TWI Internal Address Register */
  #define REG_FLEXCOM10_TWI_CWGR                     (0xF8044610U) /**< \brief (FLEXCOM10) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM10_TWI_SR                       (0xF8044620U) /**< \brief (FLEXCOM10) TWI Status Register */
  #define REG_FLEXCOM10_TWI_IER                      (0xF8044624U) /**< \brief (FLEXCOM10) TWI Interrupt Enable Register */
  #define REG_FLEXCOM10_TWI_IDR                      (0xF8044628U) /**< \brief (FLEXCOM10) TWI Interrupt Disable Register */
  #define REG_FLEXCOM10_TWI_IMR                      (0xF804462CU) /**< \brief (FLEXCOM10) TWI Interrupt Mask Register */
  #define REG_FLEXCOM10_TWI_RHR                      (0xF8044630U) /**< \brief (FLEXCOM10) TWI Receive Holding Register */
  #define REG_FLEXCOM10_TWI_THR                      (0xF8044634U) /**< \brief (FLEXCOM10) TWI Transmit Holding Register */
  #define REG_FLEXCOM10_TWI_SMBTR                    (0xF8044638U) /**< \brief (FLEXCOM10) TWI SMBus Timing Register */
  #define REG_FLEXCOM10_TWI_ACR                      (0xF8044640U) /**< \brief (FLEXCOM10) TWI Alternative Command Register */
  #define REG_FLEXCOM10_TWI_FILTR                    (0xF8044644U) /**< \brief (FLEXCOM10) TWI Filter Register */
  #define REG_FLEXCOM10_TWI_FMR                      (0xF8044650U) /**< \brief (FLEXCOM10) TWI FIFO Mode Register */
  #define REG_FLEXCOM10_TWI_FLR                      (0xF8044654U) /**< \brief (FLEXCOM10) TWI FIFO Level Register */
  #define REG_FLEXCOM10_TWI_FSR                      (0xF8044660U) /**< \brief (FLEXCOM10) TWI FIFO Status Register */
  #define REG_FLEXCOM10_TWI_FIER                     (0xF8044664U) /**< \brief (FLEXCOM10) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM10_TWI_FIDR                     (0xF8044668U) /**< \brief (FLEXCOM10) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM10_TWI_FIMR                     (0xF804466CU) /**< \brief (FLEXCOM10) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM10_TWI_WPMR                     (0xF80446E4U) /**< \brief (FLEXCOM10) TWI Write Protection Mode Register */
  #define REG_FLEXCOM10_TWI_WPSR                     (0xF80446E8U) /**< \brief (FLEXCOM10) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM10_MR          (*(__IO uint32_t*)0xF8044000U) /**< \brief (FLEXCOM10) FLEXCOM Mode Register */
  #define REG_FLEXCOM10_RHR         (*(__I  uint32_t*)0xF8044010U) /**< \brief (FLEXCOM10) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM10_THR         (*(__IO uint32_t*)0xF8044020U) /**< \brief (FLEXCOM10) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM10_US_CR       (*(__O  uint32_t*)0xF8044200U) /**< \brief (FLEXCOM10) USART Control Register */
  #define REG_FLEXCOM10_US_MR       (*(__IO uint32_t*)0xF8044204U) /**< \brief (FLEXCOM10) USART Mode Register */
  #define REG_FLEXCOM10_US_IER      (*(__O  uint32_t*)0xF8044208U) /**< \brief (FLEXCOM10) USART Interrupt Enable Register */
  #define REG_FLEXCOM10_US_IDR      (*(__O  uint32_t*)0xF804420CU) /**< \brief (FLEXCOM10) USART Interrupt Disable Register */
  #define REG_FLEXCOM10_US_IMR      (*(__I  uint32_t*)0xF8044210U) /**< \brief (FLEXCOM10) USART Interrupt Mask Register */
  #define REG_FLEXCOM10_US_CSR      (*(__I  uint32_t*)0xF8044214U) /**< \brief (FLEXCOM10) USART Channel Status Register */
  #define REG_FLEXCOM10_US_RHR      (*(__I  uint32_t*)0xF8044218U) /**< \brief (FLEXCOM10) USART Receive Holding Register */
  #define REG_FLEXCOM10_US_THR      (*(__O  uint32_t*)0xF804421CU) /**< \brief (FLEXCOM10) USART Transmit Holding Register */
  #define REG_FLEXCOM10_US_BRGR     (*(__IO uint32_t*)0xF8044220U) /**< \brief (FLEXCOM10) USART Baud Rate Generator Register */
  #define REG_FLEXCOM10_US_RTOR     (*(__IO uint32_t*)0xF8044224U) /**< \brief (FLEXCOM10) USART Receiver Timeout Register */
  #define REG_FLEXCOM10_US_TTGR     (*(__IO uint32_t*)0xF8044228U) /**< \brief (FLEXCOM10) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM10_US_FIDI     (*(__IO uint32_t*)0xF8044240U) /**< \brief (FLEXCOM10) USART FI DI Ratio Register */
  #define REG_FLEXCOM10_US_NER      (*(__I  uint32_t*)0xF8044244U) /**< \brief (FLEXCOM10) USART Number of Errors Register */
  #define REG_FLEXCOM10_US_IF       (*(__IO uint32_t*)0xF804424CU) /**< \brief (FLEXCOM10) USART IrDA Filter Register */
  #define REG_FLEXCOM10_US_MAN      (*(__IO uint32_t*)0xF8044250U) /**< \brief (FLEXCOM10) USART Manchester Configuration Register */
  #define REG_FLEXCOM10_US_LINMR    (*(__IO uint32_t*)0xF8044254U) /**< \brief (FLEXCOM10) USART LIN Mode Register */
  #define REG_FLEXCOM10_US_LINIR    (*(__IO uint32_t*)0xF8044258U) /**< \brief (FLEXCOM10) USART LIN Identifier Register */
  #define REG_FLEXCOM10_US_LINBRR   (*(__I  uint32_t*)0xF804425CU) /**< \brief (FLEXCOM10) USART LIN Baud Rate Register */
  #define REG_FLEXCOM10_US_LONMR    (*(__IO uint32_t*)0xF8044260U) /**< \brief (FLEXCOM10) USART LON Mode Register */
  #define REG_FLEXCOM10_US_LONPR    (*(__IO uint32_t*)0xF8044264U) /**< \brief (FLEXCOM10) USART LON Preamble Register */
  #define REG_FLEXCOM10_US_LONDL    (*(__IO uint32_t*)0xF8044268U) /**< \brief (FLEXCOM10) USART LON Data Length Register */
  #define REG_FLEXCOM10_US_LONL2HDR (*(__IO uint32_t*)0xF804426CU) /**< \brief (FLEXCOM10) USART LON L2HDR Register */
  #define REG_FLEXCOM10_US_LONBL    (*(__I  uint32_t*)0xF8044270U) /**< \brief (FLEXCOM10) USART LON Backlog Register */
  #define REG_FLEXCOM10_US_LONB1TX  (*(__IO uint32_t*)0xF8044274U) /**< \brief (FLEXCOM10) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM10_US_LONB1RX  (*(__IO uint32_t*)0xF8044278U) /**< \brief (FLEXCOM10) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM10_US_LONPRIO  (*(__IO uint32_t*)0xF804427CU) /**< \brief (FLEXCOM10) USART LON Priority Register */
  #define REG_FLEXCOM10_US_IDTTX    (*(__IO uint32_t*)0xF8044280U) /**< \brief (FLEXCOM10) USART LON IDT Tx Register */
  #define REG_FLEXCOM10_US_IDTRX    (*(__IO uint32_t*)0xF8044284U) /**< \brief (FLEXCOM10) USART LON IDT Rx Register */
  #define REG_FLEXCOM10_US_ICDIFF   (*(__IO uint32_t*)0xF8044288U) /**< \brief (FLEXCOM10) USART IC DIFF Register */
  #define REG_FLEXCOM10_US_CMPR     (*(__IO uint32_t*)0xF8044290U) /**< \brief (FLEXCOM10) USART Comparison Register */
  #define REG_FLEXCOM10_US_FMR      (*(__IO uint32_t*)0xF80442A0U) /**< \brief (FLEXCOM10) USART FIFO Mode Register */
  #define REG_FLEXCOM10_US_FLR      (*(__I  uint32_t*)0xF80442A4U) /**< \brief (FLEXCOM10) USART FIFO Level Register */
  #define REG_FLEXCOM10_US_FIER     (*(__O  uint32_t*)0xF80442A8U) /**< \brief (FLEXCOM10) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM10_US_FIDR     (*(__O  uint32_t*)0xF80442ACU) /**< \brief (FLEXCOM10) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM10_US_FIMR     (*(__I  uint32_t*)0xF80442B0U) /**< \brief (FLEXCOM10) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM10_US_FESR     (*(__I  uint32_t*)0xF80442B4U) /**< \brief (FLEXCOM10) USART FIFO Event Status Register */
  #define REG_FLEXCOM10_US_WPMR     (*(__IO uint32_t*)0xF80442E4U) /**< \brief (FLEXCOM10) USART Write Protection Mode Register */
  #define REG_FLEXCOM10_US_WPSR     (*(__I  uint32_t*)0xF80442E8U) /**< \brief (FLEXCOM10) USART Write Protection Status Register */
  #define REG_FLEXCOM10_SPI_CR      (*(__O  uint32_t*)0xF8044400U) /**< \brief (FLEXCOM10) SPI Control Register */
  #define REG_FLEXCOM10_SPI_MR      (*(__IO uint32_t*)0xF8044404U) /**< \brief (FLEXCOM10) SPI Mode Register */
  #define REG_FLEXCOM10_SPI_RDR     (*(__I  uint32_t*)0xF8044408U) /**< \brief (FLEXCOM10) SPI Receive Data Register */
  #define REG_FLEXCOM10_SPI_TDR     (*(__O  uint32_t*)0xF804440CU) /**< \brief (FLEXCOM10) SPI Transmit Data Register */
  #define REG_FLEXCOM10_SPI_SR      (*(__I  uint32_t*)0xF8044410U) /**< \brief (FLEXCOM10) SPI Status Register */
  #define REG_FLEXCOM10_SPI_IER     (*(__O  uint32_t*)0xF8044414U) /**< \brief (FLEXCOM10) SPI Interrupt Enable Register */
  #define REG_FLEXCOM10_SPI_IDR     (*(__O  uint32_t*)0xF8044418U) /**< \brief (FLEXCOM10) SPI Interrupt Disable Register */
  #define REG_FLEXCOM10_SPI_IMR     (*(__I  uint32_t*)0xF804441CU) /**< \brief (FLEXCOM10) SPI Interrupt Mask Register */
  #define REG_FLEXCOM10_SPI_CSR     (*(__IO uint32_t*)0xF8044430U) /**< \brief (FLEXCOM10) SPI Chip Select Register */
  #define REG_FLEXCOM10_SPI_FMR     (*(__IO uint32_t*)0xF8044440U) /**< \brief (FLEXCOM10) SPI FIFO Mode Register */
  #define REG_FLEXCOM10_SPI_FLR     (*(__I  uint32_t*)0xF8044444U) /**< \brief (FLEXCOM10) SPI FIFO Level Register */
  #define REG_FLEXCOM10_SPI_CMPR    (*(__IO uint32_t*)0xF8044448U) /**< \brief (FLEXCOM10) SPI Comparison Register */
  #define REG_FLEXCOM10_SPI_WPMR    (*(__IO uint32_t*)0xF80444E4U) /**< \brief (FLEXCOM10) SPI Write Protection Mode Register */
  #define REG_FLEXCOM10_SPI_WPSR    (*(__I  uint32_t*)0xF80444E8U) /**< \brief (FLEXCOM10) SPI Write Protection Status Register */
  #define REG_FLEXCOM10_TWI_CR      (*(__O  uint32_t*)0xF8044600U) /**< \brief (FLEXCOM10) TWI Control Register */
  #define REG_FLEXCOM10_TWI_MMR     (*(__IO uint32_t*)0xF8044604U) /**< \brief (FLEXCOM10) TWI Master Mode Register */
  #define REG_FLEXCOM10_TWI_SMR     (*(__IO uint32_t*)0xF8044608U) /**< \brief (FLEXCOM10) TWI Slave Mode Register */
  #define REG_FLEXCOM10_TWI_IADR    (*(__IO uint32_t*)0xF804460CU) /**< \brief (FLEXCOM10) TWI Internal Address Register */
  #define REG_FLEXCOM10_TWI_CWGR    (*(__IO uint32_t*)0xF8044610U) /**< \brief (FLEXCOM10) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM10_TWI_SR      (*(__I  uint32_t*)0xF8044620U) /**< \brief (FLEXCOM10) TWI Status Register */
  #define REG_FLEXCOM10_TWI_IER     (*(__O  uint32_t*)0xF8044624U) /**< \brief (FLEXCOM10) TWI Interrupt Enable Register */
  #define REG_FLEXCOM10_TWI_IDR     (*(__O  uint32_t*)0xF8044628U) /**< \brief (FLEXCOM10) TWI Interrupt Disable Register */
  #define REG_FLEXCOM10_TWI_IMR     (*(__I  uint32_t*)0xF804462CU) /**< \brief (FLEXCOM10) TWI Interrupt Mask Register */
  #define REG_FLEXCOM10_TWI_RHR     (*(__I  uint32_t*)0xF8044630U) /**< \brief (FLEXCOM10) TWI Receive Holding Register */
  #define REG_FLEXCOM10_TWI_THR     (*(__O  uint32_t*)0xF8044634U) /**< \brief (FLEXCOM10) TWI Transmit Holding Register */
  #define REG_FLEXCOM10_TWI_SMBTR   (*(__IO uint32_t*)0xF8044638U) /**< \brief (FLEXCOM10) TWI SMBus Timing Register */
  #define REG_FLEXCOM10_TWI_ACR     (*(__IO uint32_t*)0xF8044640U) /**< \brief (FLEXCOM10) TWI Alternative Command Register */
  #define REG_FLEXCOM10_TWI_FILTR   (*(__IO uint32_t*)0xF8044644U) /**< \brief (FLEXCOM10) TWI Filter Register */
  #define REG_FLEXCOM10_TWI_FMR     (*(__IO uint32_t*)0xF8044650U) /**< \brief (FLEXCOM10) TWI FIFO Mode Register */
  #define REG_FLEXCOM10_TWI_FLR     (*(__I  uint32_t*)0xF8044654U) /**< \brief (FLEXCOM10) TWI FIFO Level Register */
  #define REG_FLEXCOM10_TWI_FSR     (*(__I  uint32_t*)0xF8044660U) /**< \brief (FLEXCOM10) TWI FIFO Status Register */
  #define REG_FLEXCOM10_TWI_FIER    (*(__O  uint32_t*)0xF8044664U) /**< \brief (FLEXCOM10) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM10_TWI_FIDR    (*(__O  uint32_t*)0xF8044668U) /**< \brief (FLEXCOM10) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM10_TWI_FIMR    (*(__I  uint32_t*)0xF804466CU) /**< \brief (FLEXCOM10) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM10_TWI_WPMR    (*(__IO uint32_t*)0xF80446E4U) /**< \brief (FLEXCOM10) TWI Write Protection Mode Register */
  #define REG_FLEXCOM10_TWI_WPSR    (*(__I  uint32_t*)0xF80446E8U) /**< \brief (FLEXCOM10) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM10_INSTANCE_ */
