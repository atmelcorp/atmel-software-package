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

#ifndef _SAM9X_FLEXCOM4_INSTANCE_
#define _SAM9X_FLEXCOM4_INSTANCE_

/* ========== Register definition for FLEXCOM4 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM4_MR                           (0xF0000000U) /**< \brief (FLEXCOM4) FLEXCOM Mode Register */
  #define REG_FLEXCOM4_RHR                          (0xF0000010U) /**< \brief (FLEXCOM4) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM4_THR                          (0xF0000020U) /**< \brief (FLEXCOM4) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM4_US_CR                        (0xF0000200U) /**< \brief (FLEXCOM4) USART Control Register */
  #define REG_FLEXCOM4_US_MR                        (0xF0000204U) /**< \brief (FLEXCOM4) USART Mode Register */
  #define REG_FLEXCOM4_US_IER                       (0xF0000208U) /**< \brief (FLEXCOM4) USART Interrupt Enable Register */
  #define REG_FLEXCOM4_US_IDR                       (0xF000020CU) /**< \brief (FLEXCOM4) USART Interrupt Disable Register */
  #define REG_FLEXCOM4_US_IMR                       (0xF0000210U) /**< \brief (FLEXCOM4) USART Interrupt Mask Register */
  #define REG_FLEXCOM4_US_CSR                       (0xF0000214U) /**< \brief (FLEXCOM4) USART Channel Status Register */
  #define REG_FLEXCOM4_US_RHR                       (0xF0000218U) /**< \brief (FLEXCOM4) USART Receive Holding Register */
  #define REG_FLEXCOM4_US_THR                       (0xF000021CU) /**< \brief (FLEXCOM4) USART Transmit Holding Register */
  #define REG_FLEXCOM4_US_BRGR                      (0xF0000220U) /**< \brief (FLEXCOM4) USART Baud Rate Generator Register */
  #define REG_FLEXCOM4_US_RTOR                      (0xF0000224U) /**< \brief (FLEXCOM4) USART Receiver Timeout Register */
  #define REG_FLEXCOM4_US_TTGR                      (0xF0000228U) /**< \brief (FLEXCOM4) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM4_US_FIDI                      (0xF0000240U) /**< \brief (FLEXCOM4) USART FI DI Ratio Register */
  #define REG_FLEXCOM4_US_NER                       (0xF0000244U) /**< \brief (FLEXCOM4) USART Number of Errors Register */
  #define REG_FLEXCOM4_US_IF                        (0xF000024CU) /**< \brief (FLEXCOM4) USART IrDA Filter Register */
  #define REG_FLEXCOM4_US_MAN                       (0xF0000250U) /**< \brief (FLEXCOM4) USART Manchester Configuration Register */
  #define REG_FLEXCOM4_US_LINMR                     (0xF0000254U) /**< \brief (FLEXCOM4) USART LIN Mode Register */
  #define REG_FLEXCOM4_US_LINIR                     (0xF0000258U) /**< \brief (FLEXCOM4) USART LIN Identifier Register */
  #define REG_FLEXCOM4_US_LINBRR                    (0xF000025CU) /**< \brief (FLEXCOM4) USART LIN Baud Rate Register */
  #define REG_FLEXCOM4_US_LONMR                     (0xF0000260U) /**< \brief (FLEXCOM4) USART LON Mode Register */
  #define REG_FLEXCOM4_US_LONPR                     (0xF0000264U) /**< \brief (FLEXCOM4) USART LON Preamble Register */
  #define REG_FLEXCOM4_US_LONDL                     (0xF0000268U) /**< \brief (FLEXCOM4) USART LON Data Length Register */
  #define REG_FLEXCOM4_US_LONL2HDR                  (0xF000026CU) /**< \brief (FLEXCOM4) USART LON L2HDR Register */
  #define REG_FLEXCOM4_US_LONBL                     (0xF0000270U) /**< \brief (FLEXCOM4) USART LON Backlog Register */
  #define REG_FLEXCOM4_US_LONB1TX                   (0xF0000274U) /**< \brief (FLEXCOM4) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM4_US_LONB1RX                   (0xF0000278U) /**< \brief (FLEXCOM4) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM4_US_LONPRIO                   (0xF000027CU) /**< \brief (FLEXCOM4) USART LON Priority Register */
  #define REG_FLEXCOM4_US_IDTTX                     (0xF0000280U) /**< \brief (FLEXCOM4) USART LON IDT Tx Register */
  #define REG_FLEXCOM4_US_IDTRX                     (0xF0000284U) /**< \brief (FLEXCOM4) USART LON IDT Rx Register */
  #define REG_FLEXCOM4_US_ICDIFF                    (0xF0000288U) /**< \brief (FLEXCOM4) USART IC DIFF Register */
  #define REG_FLEXCOM4_US_CMPR                      (0xF0000290U) /**< \brief (FLEXCOM4) USART Comparison Register */
  #define REG_FLEXCOM4_US_FMR                       (0xF00002A0U) /**< \brief (FLEXCOM4) USART FIFO Mode Register */
  #define REG_FLEXCOM4_US_FLR                       (0xF00002A4U) /**< \brief (FLEXCOM4) USART FIFO Level Register */
  #define REG_FLEXCOM4_US_FIER                      (0xF00002A8U) /**< \brief (FLEXCOM4) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM4_US_FIDR                      (0xF00002ACU) /**< \brief (FLEXCOM4) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM4_US_FIMR                      (0xF00002B0U) /**< \brief (FLEXCOM4) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM4_US_FESR                      (0xF00002B4U) /**< \brief (FLEXCOM4) USART FIFO Event Status Register */
  #define REG_FLEXCOM4_US_WPMR                      (0xF00002E4U) /**< \brief (FLEXCOM4) USART Write Protection Mode Register */
  #define REG_FLEXCOM4_US_WPSR                      (0xF00002E8U) /**< \brief (FLEXCOM4) USART Write Protection Status Register */
  #define REG_FLEXCOM4_SPI_CR                       (0xF0000400U) /**< \brief (FLEXCOM4) SPI Control Register */
  #define REG_FLEXCOM4_SPI_MR                       (0xF0000404U) /**< \brief (FLEXCOM4) SPI Mode Register */
  #define REG_FLEXCOM4_SPI_RDR                      (0xF0000408U) /**< \brief (FLEXCOM4) SPI Receive Data Register */
  #define REG_FLEXCOM4_SPI_TDR                      (0xF000040CU) /**< \brief (FLEXCOM4) SPI Transmit Data Register */
  #define REG_FLEXCOM4_SPI_SR                       (0xF0000410U) /**< \brief (FLEXCOM4) SPI Status Register */
  #define REG_FLEXCOM4_SPI_IER                      (0xF0000414U) /**< \brief (FLEXCOM4) SPI Interrupt Enable Register */
  #define REG_FLEXCOM4_SPI_IDR                      (0xF0000418U) /**< \brief (FLEXCOM4) SPI Interrupt Disable Register */
  #define REG_FLEXCOM4_SPI_IMR                      (0xF000041CU) /**< \brief (FLEXCOM4) SPI Interrupt Mask Register */
  #define REG_FLEXCOM4_SPI_CSR                      (0xF0000430U) /**< \brief (FLEXCOM4) SPI Chip Select Register */
  #define REG_FLEXCOM4_SPI_FMR                      (0xF0000440U) /**< \brief (FLEXCOM4) SPI FIFO Mode Register */
  #define REG_FLEXCOM4_SPI_FLR                      (0xF0000444U) /**< \brief (FLEXCOM4) SPI FIFO Level Register */
  #define REG_FLEXCOM4_SPI_CMPR                     (0xF0000448U) /**< \brief (FLEXCOM4) SPI Comparison Register */
  #define REG_FLEXCOM4_SPI_WPMR                     (0xF00004E4U) /**< \brief (FLEXCOM4) SPI Write Protection Mode Register */
  #define REG_FLEXCOM4_SPI_WPSR                     (0xF00004E8U) /**< \brief (FLEXCOM4) SPI Write Protection Status Register */
  #define REG_FLEXCOM4_TWI_CR                       (0xF0000600U) /**< \brief (FLEXCOM4) TWI Control Register */
  #define REG_FLEXCOM4_TWI_MMR                      (0xF0000604U) /**< \brief (FLEXCOM4) TWI Master Mode Register */
  #define REG_FLEXCOM4_TWI_SMR                      (0xF0000608U) /**< \brief (FLEXCOM4) TWI Slave Mode Register */
  #define REG_FLEXCOM4_TWI_IADR                     (0xF000060CU) /**< \brief (FLEXCOM4) TWI Internal Address Register */
  #define REG_FLEXCOM4_TWI_CWGR                     (0xF0000610U) /**< \brief (FLEXCOM4) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM4_TWI_SR                       (0xF0000620U) /**< \brief (FLEXCOM4) TWI Status Register */
  #define REG_FLEXCOM4_TWI_IER                      (0xF0000624U) /**< \brief (FLEXCOM4) TWI Interrupt Enable Register */
  #define REG_FLEXCOM4_TWI_IDR                      (0xF0000628U) /**< \brief (FLEXCOM4) TWI Interrupt Disable Register */
  #define REG_FLEXCOM4_TWI_IMR                      (0xF000062CU) /**< \brief (FLEXCOM4) TWI Interrupt Mask Register */
  #define REG_FLEXCOM4_TWI_RHR                      (0xF0000630U) /**< \brief (FLEXCOM4) TWI Receive Holding Register */
  #define REG_FLEXCOM4_TWI_THR                      (0xF0000634U) /**< \brief (FLEXCOM4) TWI Transmit Holding Register */
  #define REG_FLEXCOM4_TWI_SMBTR                    (0xF0000638U) /**< \brief (FLEXCOM4) TWI SMBus Timing Register */
  #define REG_FLEXCOM4_TWI_ACR                      (0xF0000640U) /**< \brief (FLEXCOM4) TWI Alternative Command Register */
  #define REG_FLEXCOM4_TWI_FILTR                    (0xF0000644U) /**< \brief (FLEXCOM4) TWI Filter Register */
  #define REG_FLEXCOM4_TWI_FMR                      (0xF0000650U) /**< \brief (FLEXCOM4) TWI FIFO Mode Register */
  #define REG_FLEXCOM4_TWI_FLR                      (0xF0000654U) /**< \brief (FLEXCOM4) TWI FIFO Level Register */
  #define REG_FLEXCOM4_TWI_FSR                      (0xF0000660U) /**< \brief (FLEXCOM4) TWI FIFO Status Register */
  #define REG_FLEXCOM4_TWI_FIER                     (0xF0000664U) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM4_TWI_FIDR                     (0xF0000668U) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM4_TWI_FIMR                     (0xF000066CU) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM4_TWI_WPMR                     (0xF00006E4U) /**< \brief (FLEXCOM4) TWI Write Protection Mode Register */
  #define REG_FLEXCOM4_TWI_WPSR                     (0xF00006E8U) /**< \brief (FLEXCOM4) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM4_MR          (*(__IO uint32_t*)0xF0000000U) /**< \brief (FLEXCOM4) FLEXCOM Mode Register */
  #define REG_FLEXCOM4_RHR         (*(__I  uint32_t*)0xF0000010U) /**< \brief (FLEXCOM4) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM4_THR         (*(__IO uint32_t*)0xF0000020U) /**< \brief (FLEXCOM4) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM4_US_CR       (*(__O  uint32_t*)0xF0000200U) /**< \brief (FLEXCOM4) USART Control Register */
  #define REG_FLEXCOM4_US_MR       (*(__IO uint32_t*)0xF0000204U) /**< \brief (FLEXCOM4) USART Mode Register */
  #define REG_FLEXCOM4_US_IER      (*(__O  uint32_t*)0xF0000208U) /**< \brief (FLEXCOM4) USART Interrupt Enable Register */
  #define REG_FLEXCOM4_US_IDR      (*(__O  uint32_t*)0xF000020CU) /**< \brief (FLEXCOM4) USART Interrupt Disable Register */
  #define REG_FLEXCOM4_US_IMR      (*(__I  uint32_t*)0xF0000210U) /**< \brief (FLEXCOM4) USART Interrupt Mask Register */
  #define REG_FLEXCOM4_US_CSR      (*(__I  uint32_t*)0xF0000214U) /**< \brief (FLEXCOM4) USART Channel Status Register */
  #define REG_FLEXCOM4_US_RHR      (*(__I  uint32_t*)0xF0000218U) /**< \brief (FLEXCOM4) USART Receive Holding Register */
  #define REG_FLEXCOM4_US_THR      (*(__O  uint32_t*)0xF000021CU) /**< \brief (FLEXCOM4) USART Transmit Holding Register */
  #define REG_FLEXCOM4_US_BRGR     (*(__IO uint32_t*)0xF0000220U) /**< \brief (FLEXCOM4) USART Baud Rate Generator Register */
  #define REG_FLEXCOM4_US_RTOR     (*(__IO uint32_t*)0xF0000224U) /**< \brief (FLEXCOM4) USART Receiver Timeout Register */
  #define REG_FLEXCOM4_US_TTGR     (*(__IO uint32_t*)0xF0000228U) /**< \brief (FLEXCOM4) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM4_US_FIDI     (*(__IO uint32_t*)0xF0000240U) /**< \brief (FLEXCOM4) USART FI DI Ratio Register */
  #define REG_FLEXCOM4_US_NER      (*(__I  uint32_t*)0xF0000244U) /**< \brief (FLEXCOM4) USART Number of Errors Register */
  #define REG_FLEXCOM4_US_IF       (*(__IO uint32_t*)0xF000024CU) /**< \brief (FLEXCOM4) USART IrDA Filter Register */
  #define REG_FLEXCOM4_US_MAN      (*(__IO uint32_t*)0xF0000250U) /**< \brief (FLEXCOM4) USART Manchester Configuration Register */
  #define REG_FLEXCOM4_US_LINMR    (*(__IO uint32_t*)0xF0000254U) /**< \brief (FLEXCOM4) USART LIN Mode Register */
  #define REG_FLEXCOM4_US_LINIR    (*(__IO uint32_t*)0xF0000258U) /**< \brief (FLEXCOM4) USART LIN Identifier Register */
  #define REG_FLEXCOM4_US_LINBRR   (*(__I  uint32_t*)0xF000025CU) /**< \brief (FLEXCOM4) USART LIN Baud Rate Register */
  #define REG_FLEXCOM4_US_LONMR    (*(__IO uint32_t*)0xF0000260U) /**< \brief (FLEXCOM4) USART LON Mode Register */
  #define REG_FLEXCOM4_US_LONPR    (*(__IO uint32_t*)0xF0000264U) /**< \brief (FLEXCOM4) USART LON Preamble Register */
  #define REG_FLEXCOM4_US_LONDL    (*(__IO uint32_t*)0xF0000268U) /**< \brief (FLEXCOM4) USART LON Data Length Register */
  #define REG_FLEXCOM4_US_LONL2HDR (*(__IO uint32_t*)0xF000026CU) /**< \brief (FLEXCOM4) USART LON L2HDR Register */
  #define REG_FLEXCOM4_US_LONBL    (*(__I  uint32_t*)0xF0000270U) /**< \brief (FLEXCOM4) USART LON Backlog Register */
  #define REG_FLEXCOM4_US_LONB1TX  (*(__IO uint32_t*)0xF0000274U) /**< \brief (FLEXCOM4) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM4_US_LONB1RX  (*(__IO uint32_t*)0xF0000278U) /**< \brief (FLEXCOM4) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM4_US_LONPRIO  (*(__IO uint32_t*)0xF000027CU) /**< \brief (FLEXCOM4) USART LON Priority Register */
  #define REG_FLEXCOM4_US_IDTTX    (*(__IO uint32_t*)0xF0000280U) /**< \brief (FLEXCOM4) USART LON IDT Tx Register */
  #define REG_FLEXCOM4_US_IDTRX    (*(__IO uint32_t*)0xF0000284U) /**< \brief (FLEXCOM4) USART LON IDT Rx Register */
  #define REG_FLEXCOM4_US_ICDIFF   (*(__IO uint32_t*)0xF0000288U) /**< \brief (FLEXCOM4) USART IC DIFF Register */
  #define REG_FLEXCOM4_US_CMPR     (*(__IO uint32_t*)0xF0000290U) /**< \brief (FLEXCOM4) USART Comparison Register */
  #define REG_FLEXCOM4_US_FMR      (*(__IO uint32_t*)0xF00002A0U) /**< \brief (FLEXCOM4) USART FIFO Mode Register */
  #define REG_FLEXCOM4_US_FLR      (*(__I  uint32_t*)0xF00002A4U) /**< \brief (FLEXCOM4) USART FIFO Level Register */
  #define REG_FLEXCOM4_US_FIER     (*(__O  uint32_t*)0xF00002A8U) /**< \brief (FLEXCOM4) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM4_US_FIDR     (*(__O  uint32_t*)0xF00002ACU) /**< \brief (FLEXCOM4) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM4_US_FIMR     (*(__I  uint32_t*)0xF00002B0U) /**< \brief (FLEXCOM4) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM4_US_FESR     (*(__I  uint32_t*)0xF00002B4U) /**< \brief (FLEXCOM4) USART FIFO Event Status Register */
  #define REG_FLEXCOM4_US_WPMR     (*(__IO uint32_t*)0xF00002E4U) /**< \brief (FLEXCOM4) USART Write Protection Mode Register */
  #define REG_FLEXCOM4_US_WPSR     (*(__I  uint32_t*)0xF00002E8U) /**< \brief (FLEXCOM4) USART Write Protection Status Register */
  #define REG_FLEXCOM4_SPI_CR      (*(__O  uint32_t*)0xF0000400U) /**< \brief (FLEXCOM4) SPI Control Register */
  #define REG_FLEXCOM4_SPI_MR      (*(__IO uint32_t*)0xF0000404U) /**< \brief (FLEXCOM4) SPI Mode Register */
  #define REG_FLEXCOM4_SPI_RDR     (*(__I  uint32_t*)0xF0000408U) /**< \brief (FLEXCOM4) SPI Receive Data Register */
  #define REG_FLEXCOM4_SPI_TDR     (*(__O  uint32_t*)0xF000040CU) /**< \brief (FLEXCOM4) SPI Transmit Data Register */
  #define REG_FLEXCOM4_SPI_SR      (*(__I  uint32_t*)0xF0000410U) /**< \brief (FLEXCOM4) SPI Status Register */
  #define REG_FLEXCOM4_SPI_IER     (*(__O  uint32_t*)0xF0000414U) /**< \brief (FLEXCOM4) SPI Interrupt Enable Register */
  #define REG_FLEXCOM4_SPI_IDR     (*(__O  uint32_t*)0xF0000418U) /**< \brief (FLEXCOM4) SPI Interrupt Disable Register */
  #define REG_FLEXCOM4_SPI_IMR     (*(__I  uint32_t*)0xF000041CU) /**< \brief (FLEXCOM4) SPI Interrupt Mask Register */
  #define REG_FLEXCOM4_SPI_CSR     (*(__IO uint32_t*)0xF0000430U) /**< \brief (FLEXCOM4) SPI Chip Select Register */
  #define REG_FLEXCOM4_SPI_FMR     (*(__IO uint32_t*)0xF0000440U) /**< \brief (FLEXCOM4) SPI FIFO Mode Register */
  #define REG_FLEXCOM4_SPI_FLR     (*(__I  uint32_t*)0xF0000444U) /**< \brief (FLEXCOM4) SPI FIFO Level Register */
  #define REG_FLEXCOM4_SPI_CMPR    (*(__IO uint32_t*)0xF0000448U) /**< \brief (FLEXCOM4) SPI Comparison Register */
  #define REG_FLEXCOM4_SPI_WPMR    (*(__IO uint32_t*)0xF00004E4U) /**< \brief (FLEXCOM4) SPI Write Protection Mode Register */
  #define REG_FLEXCOM4_SPI_WPSR    (*(__I  uint32_t*)0xF00004E8U) /**< \brief (FLEXCOM4) SPI Write Protection Status Register */
  #define REG_FLEXCOM4_TWI_CR      (*(__O  uint32_t*)0xF0000600U) /**< \brief (FLEXCOM4) TWI Control Register */
  #define REG_FLEXCOM4_TWI_MMR     (*(__IO uint32_t*)0xF0000604U) /**< \brief (FLEXCOM4) TWI Master Mode Register */
  #define REG_FLEXCOM4_TWI_SMR     (*(__IO uint32_t*)0xF0000608U) /**< \brief (FLEXCOM4) TWI Slave Mode Register */
  #define REG_FLEXCOM4_TWI_IADR    (*(__IO uint32_t*)0xF000060CU) /**< \brief (FLEXCOM4) TWI Internal Address Register */
  #define REG_FLEXCOM4_TWI_CWGR    (*(__IO uint32_t*)0xF0000610U) /**< \brief (FLEXCOM4) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM4_TWI_SR      (*(__I  uint32_t*)0xF0000620U) /**< \brief (FLEXCOM4) TWI Status Register */
  #define REG_FLEXCOM4_TWI_IER     (*(__O  uint32_t*)0xF0000624U) /**< \brief (FLEXCOM4) TWI Interrupt Enable Register */
  #define REG_FLEXCOM4_TWI_IDR     (*(__O  uint32_t*)0xF0000628U) /**< \brief (FLEXCOM4) TWI Interrupt Disable Register */
  #define REG_FLEXCOM4_TWI_IMR     (*(__I  uint32_t*)0xF000062CU) /**< \brief (FLEXCOM4) TWI Interrupt Mask Register */
  #define REG_FLEXCOM4_TWI_RHR     (*(__I  uint32_t*)0xF0000630U) /**< \brief (FLEXCOM4) TWI Receive Holding Register */
  #define REG_FLEXCOM4_TWI_THR     (*(__O  uint32_t*)0xF0000634U) /**< \brief (FLEXCOM4) TWI Transmit Holding Register */
  #define REG_FLEXCOM4_TWI_SMBTR   (*(__IO uint32_t*)0xF0000638U) /**< \brief (FLEXCOM4) TWI SMBus Timing Register */
  #define REG_FLEXCOM4_TWI_ACR     (*(__IO uint32_t*)0xF0000640U) /**< \brief (FLEXCOM4) TWI Alternative Command Register */
  #define REG_FLEXCOM4_TWI_FILTR   (*(__IO uint32_t*)0xF0000644U) /**< \brief (FLEXCOM4) TWI Filter Register */
  #define REG_FLEXCOM4_TWI_FMR     (*(__IO uint32_t*)0xF0000650U) /**< \brief (FLEXCOM4) TWI FIFO Mode Register */
  #define REG_FLEXCOM4_TWI_FLR     (*(__I  uint32_t*)0xF0000654U) /**< \brief (FLEXCOM4) TWI FIFO Level Register */
  #define REG_FLEXCOM4_TWI_FSR     (*(__I  uint32_t*)0xF0000660U) /**< \brief (FLEXCOM4) TWI FIFO Status Register */
  #define REG_FLEXCOM4_TWI_FIER    (*(__O  uint32_t*)0xF0000664U) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM4_TWI_FIDR    (*(__O  uint32_t*)0xF0000668U) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM4_TWI_FIMR    (*(__I  uint32_t*)0xF000066CU) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM4_TWI_WPMR    (*(__IO uint32_t*)0xF00006E4U) /**< \brief (FLEXCOM4) TWI Write Protection Mode Register */
  #define REG_FLEXCOM4_TWI_WPSR    (*(__I  uint32_t*)0xF00006E8U) /**< \brief (FLEXCOM4) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM4_INSTANCE_ */
