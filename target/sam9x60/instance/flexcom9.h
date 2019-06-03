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

#ifndef _SAM9X_FLEXCOM9_INSTANCE_
#define _SAM9X_FLEXCOM9_INSTANCE_

/* ========== Register definition for FLEXCOM9 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM9_MR                           (0xF8040000U) /**< \brief (FLEXCOM9) FLEXCOM Mode Register */
  #define REG_FLEXCOM9_RHR                          (0xF8040010U) /**< \brief (FLEXCOM9) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM9_THR                          (0xF8040020U) /**< \brief (FLEXCOM9) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM9_US_CR                        (0xF8040200U) /**< \brief (FLEXCOM9) USART Control Register */
  #define REG_FLEXCOM9_US_MR                        (0xF8040204U) /**< \brief (FLEXCOM9) USART Mode Register */
  #define REG_FLEXCOM9_US_IER                       (0xF8040208U) /**< \brief (FLEXCOM9) USART Interrupt Enable Register */
  #define REG_FLEXCOM9_US_IDR                       (0xF804020CU) /**< \brief (FLEXCOM9) USART Interrupt Disable Register */
  #define REG_FLEXCOM9_US_IMR                       (0xF8040210U) /**< \brief (FLEXCOM9) USART Interrupt Mask Register */
  #define REG_FLEXCOM9_US_CSR                       (0xF8040214U) /**< \brief (FLEXCOM9) USART Channel Status Register */
  #define REG_FLEXCOM9_US_RHR                       (0xF8040218U) /**< \brief (FLEXCOM9) USART Receive Holding Register */
  #define REG_FLEXCOM9_US_THR                       (0xF804021CU) /**< \brief (FLEXCOM9) USART Transmit Holding Register */
  #define REG_FLEXCOM9_US_BRGR                      (0xF8040220U) /**< \brief (FLEXCOM9) USART Baud Rate Generator Register */
  #define REG_FLEXCOM9_US_RTOR                      (0xF8040224U) /**< \brief (FLEXCOM9) USART Receiver Timeout Register */
  #define REG_FLEXCOM9_US_TTGR                      (0xF8040228U) /**< \brief (FLEXCOM9) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM9_US_FIDI                      (0xF8040240U) /**< \brief (FLEXCOM9) USART FI DI Ratio Register */
  #define REG_FLEXCOM9_US_NER                       (0xF8040244U) /**< \brief (FLEXCOM9) USART Number of Errors Register */
  #define REG_FLEXCOM9_US_IF                        (0xF804024CU) /**< \brief (FLEXCOM9) USART IrDA Filter Register */
  #define REG_FLEXCOM9_US_MAN                       (0xF8040250U) /**< \brief (FLEXCOM9) USART Manchester Configuration Register */
  #define REG_FLEXCOM9_US_LINMR                     (0xF8040254U) /**< \brief (FLEXCOM9) USART LIN Mode Register */
  #define REG_FLEXCOM9_US_LINIR                     (0xF8040258U) /**< \brief (FLEXCOM9) USART LIN Identifier Register */
  #define REG_FLEXCOM9_US_LINBRR                    (0xF804025CU) /**< \brief (FLEXCOM9) USART LIN Baud Rate Register */
  #define REG_FLEXCOM9_US_LONMR                     (0xF8040260U) /**< \brief (FLEXCOM9) USART LON Mode Register */
  #define REG_FLEXCOM9_US_LONPR                     (0xF8040264U) /**< \brief (FLEXCOM9) USART LON Preamble Register */
  #define REG_FLEXCOM9_US_LONDL                     (0xF8040268U) /**< \brief (FLEXCOM9) USART LON Data Length Register */
  #define REG_FLEXCOM9_US_LONL2HDR                  (0xF804026CU) /**< \brief (FLEXCOM9) USART LON L2HDR Register */
  #define REG_FLEXCOM9_US_LONBL                     (0xF8040270U) /**< \brief (FLEXCOM9) USART LON Backlog Register */
  #define REG_FLEXCOM9_US_LONB1TX                   (0xF8040274U) /**< \brief (FLEXCOM9) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM9_US_LONB1RX                   (0xF8040278U) /**< \brief (FLEXCOM9) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM9_US_LONPRIO                   (0xF804027CU) /**< \brief (FLEXCOM9) USART LON Priority Register */
  #define REG_FLEXCOM9_US_IDTTX                     (0xF8040280U) /**< \brief (FLEXCOM9) USART LON IDT Tx Register */
  #define REG_FLEXCOM9_US_IDTRX                     (0xF8040284U) /**< \brief (FLEXCOM9) USART LON IDT Rx Register */
  #define REG_FLEXCOM9_US_ICDIFF                    (0xF8040288U) /**< \brief (FLEXCOM9) USART IC DIFF Register */
  #define REG_FLEXCOM9_US_CMPR                      (0xF8040290U) /**< \brief (FLEXCOM9) USART Comparison Register */
  #define REG_FLEXCOM9_US_FMR                       (0xF80402A0U) /**< \brief (FLEXCOM9) USART FIFO Mode Register */
  #define REG_FLEXCOM9_US_FLR                       (0xF80402A4U) /**< \brief (FLEXCOM9) USART FIFO Level Register */
  #define REG_FLEXCOM9_US_FIER                      (0xF80402A8U) /**< \brief (FLEXCOM9) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM9_US_FIDR                      (0xF80402ACU) /**< \brief (FLEXCOM9) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM9_US_FIMR                      (0xF80402B0U) /**< \brief (FLEXCOM9) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM9_US_FESR                      (0xF80402B4U) /**< \brief (FLEXCOM9) USART FIFO Event Status Register */
  #define REG_FLEXCOM9_US_WPMR                      (0xF80402E4U) /**< \brief (FLEXCOM9) USART Write Protection Mode Register */
  #define REG_FLEXCOM9_US_WPSR                      (0xF80402E8U) /**< \brief (FLEXCOM9) USART Write Protection Status Register */
  #define REG_FLEXCOM9_SPI_CR                       (0xF8040400U) /**< \brief (FLEXCOM9) SPI Control Register */
  #define REG_FLEXCOM9_SPI_MR                       (0xF8040404U) /**< \brief (FLEXCOM9) SPI Mode Register */
  #define REG_FLEXCOM9_SPI_RDR                      (0xF8040408U) /**< \brief (FLEXCOM9) SPI Receive Data Register */
  #define REG_FLEXCOM9_SPI_TDR                      (0xF804040CU) /**< \brief (FLEXCOM9) SPI Transmit Data Register */
  #define REG_FLEXCOM9_SPI_SR                       (0xF8040410U) /**< \brief (FLEXCOM9) SPI Status Register */
  #define REG_FLEXCOM9_SPI_IER                      (0xF8040414U) /**< \brief (FLEXCOM9) SPI Interrupt Enable Register */
  #define REG_FLEXCOM9_SPI_IDR                      (0xF8040418U) /**< \brief (FLEXCOM9) SPI Interrupt Disable Register */
  #define REG_FLEXCOM9_SPI_IMR                      (0xF804041CU) /**< \brief (FLEXCOM9) SPI Interrupt Mask Register */
  #define REG_FLEXCOM9_SPI_CSR                      (0xF8040430U) /**< \brief (FLEXCOM9) SPI Chip Select Register */
  #define REG_FLEXCOM9_SPI_FMR                      (0xF8040440U) /**< \brief (FLEXCOM9) SPI FIFO Mode Register */
  #define REG_FLEXCOM9_SPI_FLR                      (0xF8040444U) /**< \brief (FLEXCOM9) SPI FIFO Level Register */
  #define REG_FLEXCOM9_SPI_CMPR                     (0xF8040448U) /**< \brief (FLEXCOM9) SPI Comparison Register */
  #define REG_FLEXCOM9_SPI_WPMR                     (0xF80404E4U) /**< \brief (FLEXCOM9) SPI Write Protection Mode Register */
  #define REG_FLEXCOM9_SPI_WPSR                     (0xF80404E8U) /**< \brief (FLEXCOM9) SPI Write Protection Status Register */
  #define REG_FLEXCOM9_TWI_CR                       (0xF8040600U) /**< \brief (FLEXCOM9) TWI Control Register */
  #define REG_FLEXCOM9_TWI_MMR                      (0xF8040604U) /**< \brief (FLEXCOM9) TWI Master Mode Register */
  #define REG_FLEXCOM9_TWI_SMR                      (0xF8040608U) /**< \brief (FLEXCOM9) TWI Slave Mode Register */
  #define REG_FLEXCOM9_TWI_IADR                     (0xF804060CU) /**< \brief (FLEXCOM9) TWI Internal Address Register */
  #define REG_FLEXCOM9_TWI_CWGR                     (0xF8040610U) /**< \brief (FLEXCOM9) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM9_TWI_SR                       (0xF8040620U) /**< \brief (FLEXCOM9) TWI Status Register */
  #define REG_FLEXCOM9_TWI_IER                      (0xF8040624U) /**< \brief (FLEXCOM9) TWI Interrupt Enable Register */
  #define REG_FLEXCOM9_TWI_IDR                      (0xF8040628U) /**< \brief (FLEXCOM9) TWI Interrupt Disable Register */
  #define REG_FLEXCOM9_TWI_IMR                      (0xF804062CU) /**< \brief (FLEXCOM9) TWI Interrupt Mask Register */
  #define REG_FLEXCOM9_TWI_RHR                      (0xF8040630U) /**< \brief (FLEXCOM9) TWI Receive Holding Register */
  #define REG_FLEXCOM9_TWI_THR                      (0xF8040634U) /**< \brief (FLEXCOM9) TWI Transmit Holding Register */
  #define REG_FLEXCOM9_TWI_SMBTR                    (0xF8040638U) /**< \brief (FLEXCOM9) TWI SMBus Timing Register */
  #define REG_FLEXCOM9_TWI_ACR                      (0xF8040640U) /**< \brief (FLEXCOM9) TWI Alternative Command Register */
  #define REG_FLEXCOM9_TWI_FILTR                    (0xF8040644U) /**< \brief (FLEXCOM9) TWI Filter Register */
  #define REG_FLEXCOM9_TWI_FMR                      (0xF8040650U) /**< \brief (FLEXCOM9) TWI FIFO Mode Register */
  #define REG_FLEXCOM9_TWI_FLR                      (0xF8040654U) /**< \brief (FLEXCOM9) TWI FIFO Level Register */
  #define REG_FLEXCOM9_TWI_FSR                      (0xF8040660U) /**< \brief (FLEXCOM9) TWI FIFO Status Register */
  #define REG_FLEXCOM9_TWI_FIER                     (0xF8040664U) /**< \brief (FLEXCOM9) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM9_TWI_FIDR                     (0xF8040668U) /**< \brief (FLEXCOM9) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM9_TWI_FIMR                     (0xF804066CU) /**< \brief (FLEXCOM9) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM9_TWI_WPMR                     (0xF80406E4U) /**< \brief (FLEXCOM9) TWI Write Protection Mode Register */
  #define REG_FLEXCOM9_TWI_WPSR                     (0xF80406E8U) /**< \brief (FLEXCOM9) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM9_MR          (*(__IO uint32_t*)0xF8040000U) /**< \brief (FLEXCOM9) FLEXCOM Mode Register */
  #define REG_FLEXCOM9_RHR         (*(__I  uint32_t*)0xF8040010U) /**< \brief (FLEXCOM9) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM9_THR         (*(__IO uint32_t*)0xF8040020U) /**< \brief (FLEXCOM9) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM9_US_CR       (*(__O  uint32_t*)0xF8040200U) /**< \brief (FLEXCOM9) USART Control Register */
  #define REG_FLEXCOM9_US_MR       (*(__IO uint32_t*)0xF8040204U) /**< \brief (FLEXCOM9) USART Mode Register */
  #define REG_FLEXCOM9_US_IER      (*(__O  uint32_t*)0xF8040208U) /**< \brief (FLEXCOM9) USART Interrupt Enable Register */
  #define REG_FLEXCOM9_US_IDR      (*(__O  uint32_t*)0xF804020CU) /**< \brief (FLEXCOM9) USART Interrupt Disable Register */
  #define REG_FLEXCOM9_US_IMR      (*(__I  uint32_t*)0xF8040210U) /**< \brief (FLEXCOM9) USART Interrupt Mask Register */
  #define REG_FLEXCOM9_US_CSR      (*(__I  uint32_t*)0xF8040214U) /**< \brief (FLEXCOM9) USART Channel Status Register */
  #define REG_FLEXCOM9_US_RHR      (*(__I  uint32_t*)0xF8040218U) /**< \brief (FLEXCOM9) USART Receive Holding Register */
  #define REG_FLEXCOM9_US_THR      (*(__O  uint32_t*)0xF804021CU) /**< \brief (FLEXCOM9) USART Transmit Holding Register */
  #define REG_FLEXCOM9_US_BRGR     (*(__IO uint32_t*)0xF8040220U) /**< \brief (FLEXCOM9) USART Baud Rate Generator Register */
  #define REG_FLEXCOM9_US_RTOR     (*(__IO uint32_t*)0xF8040224U) /**< \brief (FLEXCOM9) USART Receiver Timeout Register */
  #define REG_FLEXCOM9_US_TTGR     (*(__IO uint32_t*)0xF8040228U) /**< \brief (FLEXCOM9) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM9_US_FIDI     (*(__IO uint32_t*)0xF8040240U) /**< \brief (FLEXCOM9) USART FI DI Ratio Register */
  #define REG_FLEXCOM9_US_NER      (*(__I  uint32_t*)0xF8040244U) /**< \brief (FLEXCOM9) USART Number of Errors Register */
  #define REG_FLEXCOM9_US_IF       (*(__IO uint32_t*)0xF804024CU) /**< \brief (FLEXCOM9) USART IrDA Filter Register */
  #define REG_FLEXCOM9_US_MAN      (*(__IO uint32_t*)0xF8040250U) /**< \brief (FLEXCOM9) USART Manchester Configuration Register */
  #define REG_FLEXCOM9_US_LINMR    (*(__IO uint32_t*)0xF8040254U) /**< \brief (FLEXCOM9) USART LIN Mode Register */
  #define REG_FLEXCOM9_US_LINIR    (*(__IO uint32_t*)0xF8040258U) /**< \brief (FLEXCOM9) USART LIN Identifier Register */
  #define REG_FLEXCOM9_US_LINBRR   (*(__I  uint32_t*)0xF804025CU) /**< \brief (FLEXCOM9) USART LIN Baud Rate Register */
  #define REG_FLEXCOM9_US_LONMR    (*(__IO uint32_t*)0xF8040260U) /**< \brief (FLEXCOM9) USART LON Mode Register */
  #define REG_FLEXCOM9_US_LONPR    (*(__IO uint32_t*)0xF8040264U) /**< \brief (FLEXCOM9) USART LON Preamble Register */
  #define REG_FLEXCOM9_US_LONDL    (*(__IO uint32_t*)0xF8040268U) /**< \brief (FLEXCOM9) USART LON Data Length Register */
  #define REG_FLEXCOM9_US_LONL2HDR (*(__IO uint32_t*)0xF804026CU) /**< \brief (FLEXCOM9) USART LON L2HDR Register */
  #define REG_FLEXCOM9_US_LONBL    (*(__I  uint32_t*)0xF8040270U) /**< \brief (FLEXCOM9) USART LON Backlog Register */
  #define REG_FLEXCOM9_US_LONB1TX  (*(__IO uint32_t*)0xF8040274U) /**< \brief (FLEXCOM9) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM9_US_LONB1RX  (*(__IO uint32_t*)0xF8040278U) /**< \brief (FLEXCOM9) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM9_US_LONPRIO  (*(__IO uint32_t*)0xF804027CU) /**< \brief (FLEXCOM9) USART LON Priority Register */
  #define REG_FLEXCOM9_US_IDTTX    (*(__IO uint32_t*)0xF8040280U) /**< \brief (FLEXCOM9) USART LON IDT Tx Register */
  #define REG_FLEXCOM9_US_IDTRX    (*(__IO uint32_t*)0xF8040284U) /**< \brief (FLEXCOM9) USART LON IDT Rx Register */
  #define REG_FLEXCOM9_US_ICDIFF   (*(__IO uint32_t*)0xF8040288U) /**< \brief (FLEXCOM9) USART IC DIFF Register */
  #define REG_FLEXCOM9_US_CMPR     (*(__IO uint32_t*)0xF8040290U) /**< \brief (FLEXCOM9) USART Comparison Register */
  #define REG_FLEXCOM9_US_FMR      (*(__IO uint32_t*)0xF80402A0U) /**< \brief (FLEXCOM9) USART FIFO Mode Register */
  #define REG_FLEXCOM9_US_FLR      (*(__I  uint32_t*)0xF80402A4U) /**< \brief (FLEXCOM9) USART FIFO Level Register */
  #define REG_FLEXCOM9_US_FIER     (*(__O  uint32_t*)0xF80402A8U) /**< \brief (FLEXCOM9) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM9_US_FIDR     (*(__O  uint32_t*)0xF80402ACU) /**< \brief (FLEXCOM9) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM9_US_FIMR     (*(__I  uint32_t*)0xF80402B0U) /**< \brief (FLEXCOM9) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM9_US_FESR     (*(__I  uint32_t*)0xF80402B4U) /**< \brief (FLEXCOM9) USART FIFO Event Status Register */
  #define REG_FLEXCOM9_US_WPMR     (*(__IO uint32_t*)0xF80402E4U) /**< \brief (FLEXCOM9) USART Write Protection Mode Register */
  #define REG_FLEXCOM9_US_WPSR     (*(__I  uint32_t*)0xF80402E8U) /**< \brief (FLEXCOM9) USART Write Protection Status Register */
  #define REG_FLEXCOM9_SPI_CR      (*(__O  uint32_t*)0xF8040400U) /**< \brief (FLEXCOM9) SPI Control Register */
  #define REG_FLEXCOM9_SPI_MR      (*(__IO uint32_t*)0xF8040404U) /**< \brief (FLEXCOM9) SPI Mode Register */
  #define REG_FLEXCOM9_SPI_RDR     (*(__I  uint32_t*)0xF8040408U) /**< \brief (FLEXCOM9) SPI Receive Data Register */
  #define REG_FLEXCOM9_SPI_TDR     (*(__O  uint32_t*)0xF804040CU) /**< \brief (FLEXCOM9) SPI Transmit Data Register */
  #define REG_FLEXCOM9_SPI_SR      (*(__I  uint32_t*)0xF8040410U) /**< \brief (FLEXCOM9) SPI Status Register */
  #define REG_FLEXCOM9_SPI_IER     (*(__O  uint32_t*)0xF8040414U) /**< \brief (FLEXCOM9) SPI Interrupt Enable Register */
  #define REG_FLEXCOM9_SPI_IDR     (*(__O  uint32_t*)0xF8040418U) /**< \brief (FLEXCOM9) SPI Interrupt Disable Register */
  #define REG_FLEXCOM9_SPI_IMR     (*(__I  uint32_t*)0xF804041CU) /**< \brief (FLEXCOM9) SPI Interrupt Mask Register */
  #define REG_FLEXCOM9_SPI_CSR     (*(__IO uint32_t*)0xF8040430U) /**< \brief (FLEXCOM9) SPI Chip Select Register */
  #define REG_FLEXCOM9_SPI_FMR     (*(__IO uint32_t*)0xF8040440U) /**< \brief (FLEXCOM9) SPI FIFO Mode Register */
  #define REG_FLEXCOM9_SPI_FLR     (*(__I  uint32_t*)0xF8040444U) /**< \brief (FLEXCOM9) SPI FIFO Level Register */
  #define REG_FLEXCOM9_SPI_CMPR    (*(__IO uint32_t*)0xF8040448U) /**< \brief (FLEXCOM9) SPI Comparison Register */
  #define REG_FLEXCOM9_SPI_WPMR    (*(__IO uint32_t*)0xF80404E4U) /**< \brief (FLEXCOM9) SPI Write Protection Mode Register */
  #define REG_FLEXCOM9_SPI_WPSR    (*(__I  uint32_t*)0xF80404E8U) /**< \brief (FLEXCOM9) SPI Write Protection Status Register */
  #define REG_FLEXCOM9_TWI_CR      (*(__O  uint32_t*)0xF8040600U) /**< \brief (FLEXCOM9) TWI Control Register */
  #define REG_FLEXCOM9_TWI_MMR     (*(__IO uint32_t*)0xF8040604U) /**< \brief (FLEXCOM9) TWI Master Mode Register */
  #define REG_FLEXCOM9_TWI_SMR     (*(__IO uint32_t*)0xF8040608U) /**< \brief (FLEXCOM9) TWI Slave Mode Register */
  #define REG_FLEXCOM9_TWI_IADR    (*(__IO uint32_t*)0xF804060CU) /**< \brief (FLEXCOM9) TWI Internal Address Register */
  #define REG_FLEXCOM9_TWI_CWGR    (*(__IO uint32_t*)0xF8040610U) /**< \brief (FLEXCOM9) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM9_TWI_SR      (*(__I  uint32_t*)0xF8040620U) /**< \brief (FLEXCOM9) TWI Status Register */
  #define REG_FLEXCOM9_TWI_IER     (*(__O  uint32_t*)0xF8040624U) /**< \brief (FLEXCOM9) TWI Interrupt Enable Register */
  #define REG_FLEXCOM9_TWI_IDR     (*(__O  uint32_t*)0xF8040628U) /**< \brief (FLEXCOM9) TWI Interrupt Disable Register */
  #define REG_FLEXCOM9_TWI_IMR     (*(__I  uint32_t*)0xF804062CU) /**< \brief (FLEXCOM9) TWI Interrupt Mask Register */
  #define REG_FLEXCOM9_TWI_RHR     (*(__I  uint32_t*)0xF8040630U) /**< \brief (FLEXCOM9) TWI Receive Holding Register */
  #define REG_FLEXCOM9_TWI_THR     (*(__O  uint32_t*)0xF8040634U) /**< \brief (FLEXCOM9) TWI Transmit Holding Register */
  #define REG_FLEXCOM9_TWI_SMBTR   (*(__IO uint32_t*)0xF8040638U) /**< \brief (FLEXCOM9) TWI SMBus Timing Register */
  #define REG_FLEXCOM9_TWI_ACR     (*(__IO uint32_t*)0xF8040640U) /**< \brief (FLEXCOM9) TWI Alternative Command Register */
  #define REG_FLEXCOM9_TWI_FILTR   (*(__IO uint32_t*)0xF8040644U) /**< \brief (FLEXCOM9) TWI Filter Register */
  #define REG_FLEXCOM9_TWI_FMR     (*(__IO uint32_t*)0xF8040650U) /**< \brief (FLEXCOM9) TWI FIFO Mode Register */
  #define REG_FLEXCOM9_TWI_FLR     (*(__I  uint32_t*)0xF8040654U) /**< \brief (FLEXCOM9) TWI FIFO Level Register */
  #define REG_FLEXCOM9_TWI_FSR     (*(__I  uint32_t*)0xF8040660U) /**< \brief (FLEXCOM9) TWI FIFO Status Register */
  #define REG_FLEXCOM9_TWI_FIER    (*(__O  uint32_t*)0xF8040664U) /**< \brief (FLEXCOM9) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM9_TWI_FIDR    (*(__O  uint32_t*)0xF8040668U) /**< \brief (FLEXCOM9) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM9_TWI_FIMR    (*(__I  uint32_t*)0xF804066CU) /**< \brief (FLEXCOM9) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM9_TWI_WPMR    (*(__IO uint32_t*)0xF80406E4U) /**< \brief (FLEXCOM9) TWI Write Protection Mode Register */
  #define REG_FLEXCOM9_TWI_WPSR    (*(__I  uint32_t*)0xF80406E8U) /**< \brief (FLEXCOM9) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM9_INSTANCE_ */
