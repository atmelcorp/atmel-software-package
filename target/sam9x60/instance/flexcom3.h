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

#ifndef _SAM9X_FLEXCOM3_INSTANCE_
#define _SAM9X_FLEXCOM3_INSTANCE_

/* ========== Register definition for FLEXCOM3 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM3_MR                           (0xF8028000U) /**< \brief (FLEXCOM3) FLEXCOM Mode Register */
  #define REG_FLEXCOM3_RHR                          (0xF8028010U) /**< \brief (FLEXCOM3) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM3_THR                          (0xF8028020U) /**< \brief (FLEXCOM3) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM3_US_CR                        (0xF8028200U) /**< \brief (FLEXCOM3) USART Control Register */
  #define REG_FLEXCOM3_US_MR                        (0xF8028204U) /**< \brief (FLEXCOM3) USART Mode Register */
  #define REG_FLEXCOM3_US_IER                       (0xF8028208U) /**< \brief (FLEXCOM3) USART Interrupt Enable Register */
  #define REG_FLEXCOM3_US_IDR                       (0xF802820CU) /**< \brief (FLEXCOM3) USART Interrupt Disable Register */
  #define REG_FLEXCOM3_US_IMR                       (0xF8028210U) /**< \brief (FLEXCOM3) USART Interrupt Mask Register */
  #define REG_FLEXCOM3_US_CSR                       (0xF8028214U) /**< \brief (FLEXCOM3) USART Channel Status Register */
  #define REG_FLEXCOM3_US_RHR                       (0xF8028218U) /**< \brief (FLEXCOM3) USART Receive Holding Register */
  #define REG_FLEXCOM3_US_THR                       (0xF802821CU) /**< \brief (FLEXCOM3) USART Transmit Holding Register */
  #define REG_FLEXCOM3_US_BRGR                      (0xF8028220U) /**< \brief (FLEXCOM3) USART Baud Rate Generator Register */
  #define REG_FLEXCOM3_US_RTOR                      (0xF8028224U) /**< \brief (FLEXCOM3) USART Receiver Timeout Register */
  #define REG_FLEXCOM3_US_TTGR                      (0xF8028228U) /**< \brief (FLEXCOM3) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM3_US_FIDI                      (0xF8028240U) /**< \brief (FLEXCOM3) USART FI DI Ratio Register */
  #define REG_FLEXCOM3_US_NER                       (0xF8028244U) /**< \brief (FLEXCOM3) USART Number of Errors Register */
  #define REG_FLEXCOM3_US_IF                        (0xF802824CU) /**< \brief (FLEXCOM3) USART IrDA Filter Register */
  #define REG_FLEXCOM3_US_MAN                       (0xF8028250U) /**< \brief (FLEXCOM3) USART Manchester Configuration Register */
  #define REG_FLEXCOM3_US_LINMR                     (0xF8028254U) /**< \brief (FLEXCOM3) USART LIN Mode Register */
  #define REG_FLEXCOM3_US_LINIR                     (0xF8028258U) /**< \brief (FLEXCOM3) USART LIN Identifier Register */
  #define REG_FLEXCOM3_US_LINBRR                    (0xF802825CU) /**< \brief (FLEXCOM3) USART LIN Baud Rate Register */
  #define REG_FLEXCOM3_US_LONMR                     (0xF8028260U) /**< \brief (FLEXCOM3) USART LON Mode Register */
  #define REG_FLEXCOM3_US_LONPR                     (0xF8028264U) /**< \brief (FLEXCOM3) USART LON Preamble Register */
  #define REG_FLEXCOM3_US_LONDL                     (0xF8028268U) /**< \brief (FLEXCOM3) USART LON Data Length Register */
  #define REG_FLEXCOM3_US_LONL2HDR                  (0xF802826CU) /**< \brief (FLEXCOM3) USART LON L2HDR Register */
  #define REG_FLEXCOM3_US_LONBL                     (0xF8028270U) /**< \brief (FLEXCOM3) USART LON Backlog Register */
  #define REG_FLEXCOM3_US_LONB1TX                   (0xF8028274U) /**< \brief (FLEXCOM3) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM3_US_LONB1RX                   (0xF8028278U) /**< \brief (FLEXCOM3) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM3_US_LONPRIO                   (0xF802827CU) /**< \brief (FLEXCOM3) USART LON Priority Register */
  #define REG_FLEXCOM3_US_IDTTX                     (0xF8028280U) /**< \brief (FLEXCOM3) USART LON IDT Tx Register */
  #define REG_FLEXCOM3_US_IDTRX                     (0xF8028284U) /**< \brief (FLEXCOM3) USART LON IDT Rx Register */
  #define REG_FLEXCOM3_US_ICDIFF                    (0xF8028288U) /**< \brief (FLEXCOM3) USART IC DIFF Register */
  #define REG_FLEXCOM3_US_CMPR                      (0xF8028290U) /**< \brief (FLEXCOM3) USART Comparison Register */
  #define REG_FLEXCOM3_US_FMR                       (0xF80282A0U) /**< \brief (FLEXCOM3) USART FIFO Mode Register */
  #define REG_FLEXCOM3_US_FLR                       (0xF80282A4U) /**< \brief (FLEXCOM3) USART FIFO Level Register */
  #define REG_FLEXCOM3_US_FIER                      (0xF80282A8U) /**< \brief (FLEXCOM3) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM3_US_FIDR                      (0xF80282ACU) /**< \brief (FLEXCOM3) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM3_US_FIMR                      (0xF80282B0U) /**< \brief (FLEXCOM3) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM3_US_FESR                      (0xF80282B4U) /**< \brief (FLEXCOM3) USART FIFO Event Status Register */
  #define REG_FLEXCOM3_US_WPMR                      (0xF80282E4U) /**< \brief (FLEXCOM3) USART Write Protection Mode Register */
  #define REG_FLEXCOM3_US_WPSR                      (0xF80282E8U) /**< \brief (FLEXCOM3) USART Write Protection Status Register */
  #define REG_FLEXCOM3_SPI_CR                       (0xF8028400U) /**< \brief (FLEXCOM3) SPI Control Register */
  #define REG_FLEXCOM3_SPI_MR                       (0xF8028404U) /**< \brief (FLEXCOM3) SPI Mode Register */
  #define REG_FLEXCOM3_SPI_RDR                      (0xF8028408U) /**< \brief (FLEXCOM3) SPI Receive Data Register */
  #define REG_FLEXCOM3_SPI_TDR                      (0xF802840CU) /**< \brief (FLEXCOM3) SPI Transmit Data Register */
  #define REG_FLEXCOM3_SPI_SR                       (0xF8028410U) /**< \brief (FLEXCOM3) SPI Status Register */
  #define REG_FLEXCOM3_SPI_IER                      (0xF8028414U) /**< \brief (FLEXCOM3) SPI Interrupt Enable Register */
  #define REG_FLEXCOM3_SPI_IDR                      (0xF8028418U) /**< \brief (FLEXCOM3) SPI Interrupt Disable Register */
  #define REG_FLEXCOM3_SPI_IMR                      (0xF802841CU) /**< \brief (FLEXCOM3) SPI Interrupt Mask Register */
  #define REG_FLEXCOM3_SPI_CSR                      (0xF8028430U) /**< \brief (FLEXCOM3) SPI Chip Select Register */
  #define REG_FLEXCOM3_SPI_FMR                      (0xF8028440U) /**< \brief (FLEXCOM3) SPI FIFO Mode Register */
  #define REG_FLEXCOM3_SPI_FLR                      (0xF8028444U) /**< \brief (FLEXCOM3) SPI FIFO Level Register */
  #define REG_FLEXCOM3_SPI_CMPR                     (0xF8028448U) /**< \brief (FLEXCOM3) SPI Comparison Register */
  #define REG_FLEXCOM3_SPI_WPMR                     (0xF80284E4U) /**< \brief (FLEXCOM3) SPI Write Protection Mode Register */
  #define REG_FLEXCOM3_SPI_WPSR                     (0xF80284E8U) /**< \brief (FLEXCOM3) SPI Write Protection Status Register */
  #define REG_FLEXCOM3_TWI_CR                       (0xF8028600U) /**< \brief (FLEXCOM3) TWI Control Register */
  #define REG_FLEXCOM3_TWI_MMR                      (0xF8028604U) /**< \brief (FLEXCOM3) TWI Master Mode Register */
  #define REG_FLEXCOM3_TWI_SMR                      (0xF8028608U) /**< \brief (FLEXCOM3) TWI Slave Mode Register */
  #define REG_FLEXCOM3_TWI_IADR                     (0xF802860CU) /**< \brief (FLEXCOM3) TWI Internal Address Register */
  #define REG_FLEXCOM3_TWI_CWGR                     (0xF8028610U) /**< \brief (FLEXCOM3) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM3_TWI_SR                       (0xF8028620U) /**< \brief (FLEXCOM3) TWI Status Register */
  #define REG_FLEXCOM3_TWI_IER                      (0xF8028624U) /**< \brief (FLEXCOM3) TWI Interrupt Enable Register */
  #define REG_FLEXCOM3_TWI_IDR                      (0xF8028628U) /**< \brief (FLEXCOM3) TWI Interrupt Disable Register */
  #define REG_FLEXCOM3_TWI_IMR                      (0xF802862CU) /**< \brief (FLEXCOM3) TWI Interrupt Mask Register */
  #define REG_FLEXCOM3_TWI_RHR                      (0xF8028630U) /**< \brief (FLEXCOM3) TWI Receive Holding Register */
  #define REG_FLEXCOM3_TWI_THR                      (0xF8028634U) /**< \brief (FLEXCOM3) TWI Transmit Holding Register */
  #define REG_FLEXCOM3_TWI_SMBTR                    (0xF8028638U) /**< \brief (FLEXCOM3) TWI SMBus Timing Register */
  #define REG_FLEXCOM3_TWI_ACR                      (0xF8028640U) /**< \brief (FLEXCOM3) TWI Alternative Command Register */
  #define REG_FLEXCOM3_TWI_FILTR                    (0xF8028644U) /**< \brief (FLEXCOM3) TWI Filter Register */
  #define REG_FLEXCOM3_TWI_FMR                      (0xF8028650U) /**< \brief (FLEXCOM3) TWI FIFO Mode Register */
  #define REG_FLEXCOM3_TWI_FLR                      (0xF8028654U) /**< \brief (FLEXCOM3) TWI FIFO Level Register */
  #define REG_FLEXCOM3_TWI_FSR                      (0xF8028660U) /**< \brief (FLEXCOM3) TWI FIFO Status Register */
  #define REG_FLEXCOM3_TWI_FIER                     (0xF8028664U) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM3_TWI_FIDR                     (0xF8028668U) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM3_TWI_FIMR                     (0xF802866CU) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM3_TWI_WPMR                     (0xF80286E4U) /**< \brief (FLEXCOM3) TWI Write Protection Mode Register */
  #define REG_FLEXCOM3_TWI_WPSR                     (0xF80286E8U) /**< \brief (FLEXCOM3) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM3_MR          (*(__IO uint32_t*)0xF8028000U) /**< \brief (FLEXCOM3) FLEXCOM Mode Register */
  #define REG_FLEXCOM3_RHR         (*(__I  uint32_t*)0xF8028010U) /**< \brief (FLEXCOM3) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM3_THR         (*(__IO uint32_t*)0xF8028020U) /**< \brief (FLEXCOM3) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM3_US_CR       (*(__O  uint32_t*)0xF8028200U) /**< \brief (FLEXCOM3) USART Control Register */
  #define REG_FLEXCOM3_US_MR       (*(__IO uint32_t*)0xF8028204U) /**< \brief (FLEXCOM3) USART Mode Register */
  #define REG_FLEXCOM3_US_IER      (*(__O  uint32_t*)0xF8028208U) /**< \brief (FLEXCOM3) USART Interrupt Enable Register */
  #define REG_FLEXCOM3_US_IDR      (*(__O  uint32_t*)0xF802820CU) /**< \brief (FLEXCOM3) USART Interrupt Disable Register */
  #define REG_FLEXCOM3_US_IMR      (*(__I  uint32_t*)0xF8028210U) /**< \brief (FLEXCOM3) USART Interrupt Mask Register */
  #define REG_FLEXCOM3_US_CSR      (*(__I  uint32_t*)0xF8028214U) /**< \brief (FLEXCOM3) USART Channel Status Register */
  #define REG_FLEXCOM3_US_RHR      (*(__I  uint32_t*)0xF8028218U) /**< \brief (FLEXCOM3) USART Receive Holding Register */
  #define REG_FLEXCOM3_US_THR      (*(__O  uint32_t*)0xF802821CU) /**< \brief (FLEXCOM3) USART Transmit Holding Register */
  #define REG_FLEXCOM3_US_BRGR     (*(__IO uint32_t*)0xF8028220U) /**< \brief (FLEXCOM3) USART Baud Rate Generator Register */
  #define REG_FLEXCOM3_US_RTOR     (*(__IO uint32_t*)0xF8028224U) /**< \brief (FLEXCOM3) USART Receiver Timeout Register */
  #define REG_FLEXCOM3_US_TTGR     (*(__IO uint32_t*)0xF8028228U) /**< \brief (FLEXCOM3) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM3_US_FIDI     (*(__IO uint32_t*)0xF8028240U) /**< \brief (FLEXCOM3) USART FI DI Ratio Register */
  #define REG_FLEXCOM3_US_NER      (*(__I  uint32_t*)0xF8028244U) /**< \brief (FLEXCOM3) USART Number of Errors Register */
  #define REG_FLEXCOM3_US_IF       (*(__IO uint32_t*)0xF802824CU) /**< \brief (FLEXCOM3) USART IrDA Filter Register */
  #define REG_FLEXCOM3_US_MAN      (*(__IO uint32_t*)0xF8028250U) /**< \brief (FLEXCOM3) USART Manchester Configuration Register */
  #define REG_FLEXCOM3_US_LINMR    (*(__IO uint32_t*)0xF8028254U) /**< \brief (FLEXCOM3) USART LIN Mode Register */
  #define REG_FLEXCOM3_US_LINIR    (*(__IO uint32_t*)0xF8028258U) /**< \brief (FLEXCOM3) USART LIN Identifier Register */
  #define REG_FLEXCOM3_US_LINBRR   (*(__I  uint32_t*)0xF802825CU) /**< \brief (FLEXCOM3) USART LIN Baud Rate Register */
  #define REG_FLEXCOM3_US_LONMR    (*(__IO uint32_t*)0xF8028260U) /**< \brief (FLEXCOM3) USART LON Mode Register */
  #define REG_FLEXCOM3_US_LONPR    (*(__IO uint32_t*)0xF8028264U) /**< \brief (FLEXCOM3) USART LON Preamble Register */
  #define REG_FLEXCOM3_US_LONDL    (*(__IO uint32_t*)0xF8028268U) /**< \brief (FLEXCOM3) USART LON Data Length Register */
  #define REG_FLEXCOM3_US_LONL2HDR (*(__IO uint32_t*)0xF802826CU) /**< \brief (FLEXCOM3) USART LON L2HDR Register */
  #define REG_FLEXCOM3_US_LONBL    (*(__I  uint32_t*)0xF8028270U) /**< \brief (FLEXCOM3) USART LON Backlog Register */
  #define REG_FLEXCOM3_US_LONB1TX  (*(__IO uint32_t*)0xF8028274U) /**< \brief (FLEXCOM3) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM3_US_LONB1RX  (*(__IO uint32_t*)0xF8028278U) /**< \brief (FLEXCOM3) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM3_US_LONPRIO  (*(__IO uint32_t*)0xF802827CU) /**< \brief (FLEXCOM3) USART LON Priority Register */
  #define REG_FLEXCOM3_US_IDTTX    (*(__IO uint32_t*)0xF8028280U) /**< \brief (FLEXCOM3) USART LON IDT Tx Register */
  #define REG_FLEXCOM3_US_IDTRX    (*(__IO uint32_t*)0xF8028284U) /**< \brief (FLEXCOM3) USART LON IDT Rx Register */
  #define REG_FLEXCOM3_US_ICDIFF   (*(__IO uint32_t*)0xF8028288U) /**< \brief (FLEXCOM3) USART IC DIFF Register */
  #define REG_FLEXCOM3_US_CMPR     (*(__IO uint32_t*)0xF8028290U) /**< \brief (FLEXCOM3) USART Comparison Register */
  #define REG_FLEXCOM3_US_FMR      (*(__IO uint32_t*)0xF80282A0U) /**< \brief (FLEXCOM3) USART FIFO Mode Register */
  #define REG_FLEXCOM3_US_FLR      (*(__I  uint32_t*)0xF80282A4U) /**< \brief (FLEXCOM3) USART FIFO Level Register */
  #define REG_FLEXCOM3_US_FIER     (*(__O  uint32_t*)0xF80282A8U) /**< \brief (FLEXCOM3) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM3_US_FIDR     (*(__O  uint32_t*)0xF80282ACU) /**< \brief (FLEXCOM3) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM3_US_FIMR     (*(__I  uint32_t*)0xF80282B0U) /**< \brief (FLEXCOM3) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM3_US_FESR     (*(__I  uint32_t*)0xF80282B4U) /**< \brief (FLEXCOM3) USART FIFO Event Status Register */
  #define REG_FLEXCOM3_US_WPMR     (*(__IO uint32_t*)0xF80282E4U) /**< \brief (FLEXCOM3) USART Write Protection Mode Register */
  #define REG_FLEXCOM3_US_WPSR     (*(__I  uint32_t*)0xF80282E8U) /**< \brief (FLEXCOM3) USART Write Protection Status Register */
  #define REG_FLEXCOM3_SPI_CR      (*(__O  uint32_t*)0xF8028400U) /**< \brief (FLEXCOM3) SPI Control Register */
  #define REG_FLEXCOM3_SPI_MR      (*(__IO uint32_t*)0xF8028404U) /**< \brief (FLEXCOM3) SPI Mode Register */
  #define REG_FLEXCOM3_SPI_RDR     (*(__I  uint32_t*)0xF8028408U) /**< \brief (FLEXCOM3) SPI Receive Data Register */
  #define REG_FLEXCOM3_SPI_TDR     (*(__O  uint32_t*)0xF802840CU) /**< \brief (FLEXCOM3) SPI Transmit Data Register */
  #define REG_FLEXCOM3_SPI_SR      (*(__I  uint32_t*)0xF8028410U) /**< \brief (FLEXCOM3) SPI Status Register */
  #define REG_FLEXCOM3_SPI_IER     (*(__O  uint32_t*)0xF8028414U) /**< \brief (FLEXCOM3) SPI Interrupt Enable Register */
  #define REG_FLEXCOM3_SPI_IDR     (*(__O  uint32_t*)0xF8028418U) /**< \brief (FLEXCOM3) SPI Interrupt Disable Register */
  #define REG_FLEXCOM3_SPI_IMR     (*(__I  uint32_t*)0xF802841CU) /**< \brief (FLEXCOM3) SPI Interrupt Mask Register */
  #define REG_FLEXCOM3_SPI_CSR     (*(__IO uint32_t*)0xF8028430U) /**< \brief (FLEXCOM3) SPI Chip Select Register */
  #define REG_FLEXCOM3_SPI_FMR     (*(__IO uint32_t*)0xF8028440U) /**< \brief (FLEXCOM3) SPI FIFO Mode Register */
  #define REG_FLEXCOM3_SPI_FLR     (*(__I  uint32_t*)0xF8028444U) /**< \brief (FLEXCOM3) SPI FIFO Level Register */
  #define REG_FLEXCOM3_SPI_CMPR    (*(__IO uint32_t*)0xF8028448U) /**< \brief (FLEXCOM3) SPI Comparison Register */
  #define REG_FLEXCOM3_SPI_WPMR    (*(__IO uint32_t*)0xF80284E4U) /**< \brief (FLEXCOM3) SPI Write Protection Mode Register */
  #define REG_FLEXCOM3_SPI_WPSR    (*(__I  uint32_t*)0xF80284E8U) /**< \brief (FLEXCOM3) SPI Write Protection Status Register */
  #define REG_FLEXCOM3_TWI_CR      (*(__O  uint32_t*)0xF8028600U) /**< \brief (FLEXCOM3) TWI Control Register */
  #define REG_FLEXCOM3_TWI_MMR     (*(__IO uint32_t*)0xF8028604U) /**< \brief (FLEXCOM3) TWI Master Mode Register */
  #define REG_FLEXCOM3_TWI_SMR     (*(__IO uint32_t*)0xF8028608U) /**< \brief (FLEXCOM3) TWI Slave Mode Register */
  #define REG_FLEXCOM3_TWI_IADR    (*(__IO uint32_t*)0xF802860CU) /**< \brief (FLEXCOM3) TWI Internal Address Register */
  #define REG_FLEXCOM3_TWI_CWGR    (*(__IO uint32_t*)0xF8028610U) /**< \brief (FLEXCOM3) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM3_TWI_SR      (*(__I  uint32_t*)0xF8028620U) /**< \brief (FLEXCOM3) TWI Status Register */
  #define REG_FLEXCOM3_TWI_IER     (*(__O  uint32_t*)0xF8028624U) /**< \brief (FLEXCOM3) TWI Interrupt Enable Register */
  #define REG_FLEXCOM3_TWI_IDR     (*(__O  uint32_t*)0xF8028628U) /**< \brief (FLEXCOM3) TWI Interrupt Disable Register */
  #define REG_FLEXCOM3_TWI_IMR     (*(__I  uint32_t*)0xF802862CU) /**< \brief (FLEXCOM3) TWI Interrupt Mask Register */
  #define REG_FLEXCOM3_TWI_RHR     (*(__I  uint32_t*)0xF8028630U) /**< \brief (FLEXCOM3) TWI Receive Holding Register */
  #define REG_FLEXCOM3_TWI_THR     (*(__O  uint32_t*)0xF8028634U) /**< \brief (FLEXCOM3) TWI Transmit Holding Register */
  #define REG_FLEXCOM3_TWI_SMBTR   (*(__IO uint32_t*)0xF8028638U) /**< \brief (FLEXCOM3) TWI SMBus Timing Register */
  #define REG_FLEXCOM3_TWI_ACR     (*(__IO uint32_t*)0xF8028640U) /**< \brief (FLEXCOM3) TWI Alternative Command Register */
  #define REG_FLEXCOM3_TWI_FILTR   (*(__IO uint32_t*)0xF8028644U) /**< \brief (FLEXCOM3) TWI Filter Register */
  #define REG_FLEXCOM3_TWI_FMR     (*(__IO uint32_t*)0xF8028650U) /**< \brief (FLEXCOM3) TWI FIFO Mode Register */
  #define REG_FLEXCOM3_TWI_FLR     (*(__I  uint32_t*)0xF8028654U) /**< \brief (FLEXCOM3) TWI FIFO Level Register */
  #define REG_FLEXCOM3_TWI_FSR     (*(__I  uint32_t*)0xF8028660U) /**< \brief (FLEXCOM3) TWI FIFO Status Register */
  #define REG_FLEXCOM3_TWI_FIER    (*(__O  uint32_t*)0xF8028664U) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM3_TWI_FIDR    (*(__O  uint32_t*)0xF8028668U) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM3_TWI_FIMR    (*(__I  uint32_t*)0xF802866CU) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM3_TWI_WPMR    (*(__IO uint32_t*)0xF80286E4U) /**< \brief (FLEXCOM3) TWI Write Protection Mode Register */
  #define REG_FLEXCOM3_TWI_WPSR    (*(__I  uint32_t*)0xF80286E8U) /**< \brief (FLEXCOM3) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM3_INSTANCE_ */
