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

#ifndef _SAM9X_FLEXCOM1_INSTANCE_
#define _SAM9X_FLEXCOM1_INSTANCE_

/* ========== Register definition for FLEXCOM1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM1_MR                           (0xF8020000U) /**< \brief (FLEXCOM1) FLEXCOM Mode Register */
  #define REG_FLEXCOM1_RHR                          (0xF8020010U) /**< \brief (FLEXCOM1) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM1_THR                          (0xF8020020U) /**< \brief (FLEXCOM1) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM1_US_CR                        (0xF8020200U) /**< \brief (FLEXCOM1) USART Control Register */
  #define REG_FLEXCOM1_US_MR                        (0xF8020204U) /**< \brief (FLEXCOM1) USART Mode Register */
  #define REG_FLEXCOM1_US_IER                       (0xF8020208U) /**< \brief (FLEXCOM1) USART Interrupt Enable Register */
  #define REG_FLEXCOM1_US_IDR                       (0xF802020CU) /**< \brief (FLEXCOM1) USART Interrupt Disable Register */
  #define REG_FLEXCOM1_US_IMR                       (0xF8020210U) /**< \brief (FLEXCOM1) USART Interrupt Mask Register */
  #define REG_FLEXCOM1_US_CSR                       (0xF8020214U) /**< \brief (FLEXCOM1) USART Channel Status Register */
  #define REG_FLEXCOM1_US_RHR                       (0xF8020218U) /**< \brief (FLEXCOM1) USART Receive Holding Register */
  #define REG_FLEXCOM1_US_THR                       (0xF802021CU) /**< \brief (FLEXCOM1) USART Transmit Holding Register */
  #define REG_FLEXCOM1_US_BRGR                      (0xF8020220U) /**< \brief (FLEXCOM1) USART Baud Rate Generator Register */
  #define REG_FLEXCOM1_US_RTOR                      (0xF8020224U) /**< \brief (FLEXCOM1) USART Receiver Timeout Register */
  #define REG_FLEXCOM1_US_TTGR                      (0xF8020228U) /**< \brief (FLEXCOM1) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM1_US_FIDI                      (0xF8020240U) /**< \brief (FLEXCOM1) USART FI DI Ratio Register */
  #define REG_FLEXCOM1_US_NER                       (0xF8020244U) /**< \brief (FLEXCOM1) USART Number of Errors Register */
  #define REG_FLEXCOM1_US_IF                        (0xF802024CU) /**< \brief (FLEXCOM1) USART IrDA Filter Register */
  #define REG_FLEXCOM1_US_MAN                       (0xF8020250U) /**< \brief (FLEXCOM1) USART Manchester Configuration Register */
  #define REG_FLEXCOM1_US_LINMR                     (0xF8020254U) /**< \brief (FLEXCOM1) USART LIN Mode Register */
  #define REG_FLEXCOM1_US_LINIR                     (0xF8020258U) /**< \brief (FLEXCOM1) USART LIN Identifier Register */
  #define REG_FLEXCOM1_US_LINBRR                    (0xF802025CU) /**< \brief (FLEXCOM1) USART LIN Baud Rate Register */
  #define REG_FLEXCOM1_US_LONMR                     (0xF8020260U) /**< \brief (FLEXCOM1) USART LON Mode Register */
  #define REG_FLEXCOM1_US_LONPR                     (0xF8020264U) /**< \brief (FLEXCOM1) USART LON Preamble Register */
  #define REG_FLEXCOM1_US_LONDL                     (0xF8020268U) /**< \brief (FLEXCOM1) USART LON Data Length Register */
  #define REG_FLEXCOM1_US_LONL2HDR                  (0xF802026CU) /**< \brief (FLEXCOM1) USART LON L2HDR Register */
  #define REG_FLEXCOM1_US_LONBL                     (0xF8020270U) /**< \brief (FLEXCOM1) USART LON Backlog Register */
  #define REG_FLEXCOM1_US_LONB1TX                   (0xF8020274U) /**< \brief (FLEXCOM1) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM1_US_LONB1RX                   (0xF8020278U) /**< \brief (FLEXCOM1) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM1_US_LONPRIO                   (0xF802027CU) /**< \brief (FLEXCOM1) USART LON Priority Register */
  #define REG_FLEXCOM1_US_IDTTX                     (0xF8020280U) /**< \brief (FLEXCOM1) USART LON IDT Tx Register */
  #define REG_FLEXCOM1_US_IDTRX                     (0xF8020284U) /**< \brief (FLEXCOM1) USART LON IDT Rx Register */
  #define REG_FLEXCOM1_US_ICDIFF                    (0xF8020288U) /**< \brief (FLEXCOM1) USART IC DIFF Register */
  #define REG_FLEXCOM1_US_CMPR                      (0xF8020290U) /**< \brief (FLEXCOM1) USART Comparison Register */
  #define REG_FLEXCOM1_US_FMR                       (0xF80202A0U) /**< \brief (FLEXCOM1) USART FIFO Mode Register */
  #define REG_FLEXCOM1_US_FLR                       (0xF80202A4U) /**< \brief (FLEXCOM1) USART FIFO Level Register */
  #define REG_FLEXCOM1_US_FIER                      (0xF80202A8U) /**< \brief (FLEXCOM1) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM1_US_FIDR                      (0xF80202ACU) /**< \brief (FLEXCOM1) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM1_US_FIMR                      (0xF80202B0U) /**< \brief (FLEXCOM1) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM1_US_FESR                      (0xF80202B4U) /**< \brief (FLEXCOM1) USART FIFO Event Status Register */
  #define REG_FLEXCOM1_US_WPMR                      (0xF80202E4U) /**< \brief (FLEXCOM1) USART Write Protection Mode Register */
  #define REG_FLEXCOM1_US_WPSR                      (0xF80202E8U) /**< \brief (FLEXCOM1) USART Write Protection Status Register */
  #define REG_FLEXCOM1_SPI_CR                       (0xF8020400U) /**< \brief (FLEXCOM1) SPI Control Register */
  #define REG_FLEXCOM1_SPI_MR                       (0xF8020404U) /**< \brief (FLEXCOM1) SPI Mode Register */
  #define REG_FLEXCOM1_SPI_RDR                      (0xF8020408U) /**< \brief (FLEXCOM1) SPI Receive Data Register */
  #define REG_FLEXCOM1_SPI_TDR                      (0xF802040CU) /**< \brief (FLEXCOM1) SPI Transmit Data Register */
  #define REG_FLEXCOM1_SPI_SR                       (0xF8020410U) /**< \brief (FLEXCOM1) SPI Status Register */
  #define REG_FLEXCOM1_SPI_IER                      (0xF8020414U) /**< \brief (FLEXCOM1) SPI Interrupt Enable Register */
  #define REG_FLEXCOM1_SPI_IDR                      (0xF8020418U) /**< \brief (FLEXCOM1) SPI Interrupt Disable Register */
  #define REG_FLEXCOM1_SPI_IMR                      (0xF802041CU) /**< \brief (FLEXCOM1) SPI Interrupt Mask Register */
  #define REG_FLEXCOM1_SPI_CSR                      (0xF8020430U) /**< \brief (FLEXCOM1) SPI Chip Select Register */
  #define REG_FLEXCOM1_SPI_FMR                      (0xF8020440U) /**< \brief (FLEXCOM1) SPI FIFO Mode Register */
  #define REG_FLEXCOM1_SPI_FLR                      (0xF8020444U) /**< \brief (FLEXCOM1) SPI FIFO Level Register */
  #define REG_FLEXCOM1_SPI_CMPR                     (0xF8020448U) /**< \brief (FLEXCOM1) SPI Comparison Register */
  #define REG_FLEXCOM1_SPI_WPMR                     (0xF80204E4U) /**< \brief (FLEXCOM1) SPI Write Protection Mode Register */
  #define REG_FLEXCOM1_SPI_WPSR                     (0xF80204E8U) /**< \brief (FLEXCOM1) SPI Write Protection Status Register */
  #define REG_FLEXCOM1_TWI_CR                       (0xF8020600U) /**< \brief (FLEXCOM1) TWI Control Register */
  #define REG_FLEXCOM1_TWI_MMR                      (0xF8020604U) /**< \brief (FLEXCOM1) TWI Master Mode Register */
  #define REG_FLEXCOM1_TWI_SMR                      (0xF8020608U) /**< \brief (FLEXCOM1) TWI Slave Mode Register */
  #define REG_FLEXCOM1_TWI_IADR                     (0xF802060CU) /**< \brief (FLEXCOM1) TWI Internal Address Register */
  #define REG_FLEXCOM1_TWI_CWGR                     (0xF8020610U) /**< \brief (FLEXCOM1) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM1_TWI_SR                       (0xF8020620U) /**< \brief (FLEXCOM1) TWI Status Register */
  #define REG_FLEXCOM1_TWI_IER                      (0xF8020624U) /**< \brief (FLEXCOM1) TWI Interrupt Enable Register */
  #define REG_FLEXCOM1_TWI_IDR                      (0xF8020628U) /**< \brief (FLEXCOM1) TWI Interrupt Disable Register */
  #define REG_FLEXCOM1_TWI_IMR                      (0xF802062CU) /**< \brief (FLEXCOM1) TWI Interrupt Mask Register */
  #define REG_FLEXCOM1_TWI_RHR                      (0xF8020630U) /**< \brief (FLEXCOM1) TWI Receive Holding Register */
  #define REG_FLEXCOM1_TWI_THR                      (0xF8020634U) /**< \brief (FLEXCOM1) TWI Transmit Holding Register */
  #define REG_FLEXCOM1_TWI_SMBTR                    (0xF8020638U) /**< \brief (FLEXCOM1) TWI SMBus Timing Register */
  #define REG_FLEXCOM1_TWI_ACR                      (0xF8020640U) /**< \brief (FLEXCOM1) TWI Alternative Command Register */
  #define REG_FLEXCOM1_TWI_FILTR                    (0xF8020644U) /**< \brief (FLEXCOM1) TWI Filter Register */
  #define REG_FLEXCOM1_TWI_FMR                      (0xF8020650U) /**< \brief (FLEXCOM1) TWI FIFO Mode Register */
  #define REG_FLEXCOM1_TWI_FLR                      (0xF8020654U) /**< \brief (FLEXCOM1) TWI FIFO Level Register */
  #define REG_FLEXCOM1_TWI_FSR                      (0xF8020660U) /**< \brief (FLEXCOM1) TWI FIFO Status Register */
  #define REG_FLEXCOM1_TWI_FIER                     (0xF8020664U) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM1_TWI_FIDR                     (0xF8020668U) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM1_TWI_FIMR                     (0xF802066CU) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM1_TWI_WPMR                     (0xF80206E4U) /**< \brief (FLEXCOM1) TWI Write Protection Mode Register */
  #define REG_FLEXCOM1_TWI_WPSR                     (0xF80206E8U) /**< \brief (FLEXCOM1) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM1_MR          (*(__IO uint32_t*)0xF8020000U) /**< \brief (FLEXCOM1) FLEXCOM Mode Register */
  #define REG_FLEXCOM1_RHR         (*(__I  uint32_t*)0xF8020010U) /**< \brief (FLEXCOM1) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM1_THR         (*(__IO uint32_t*)0xF8020020U) /**< \brief (FLEXCOM1) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM1_US_CR       (*(__O  uint32_t*)0xF8020200U) /**< \brief (FLEXCOM1) USART Control Register */
  #define REG_FLEXCOM1_US_MR       (*(__IO uint32_t*)0xF8020204U) /**< \brief (FLEXCOM1) USART Mode Register */
  #define REG_FLEXCOM1_US_IER      (*(__O  uint32_t*)0xF8020208U) /**< \brief (FLEXCOM1) USART Interrupt Enable Register */
  #define REG_FLEXCOM1_US_IDR      (*(__O  uint32_t*)0xF802020CU) /**< \brief (FLEXCOM1) USART Interrupt Disable Register */
  #define REG_FLEXCOM1_US_IMR      (*(__I  uint32_t*)0xF8020210U) /**< \brief (FLEXCOM1) USART Interrupt Mask Register */
  #define REG_FLEXCOM1_US_CSR      (*(__I  uint32_t*)0xF8020214U) /**< \brief (FLEXCOM1) USART Channel Status Register */
  #define REG_FLEXCOM1_US_RHR      (*(__I  uint32_t*)0xF8020218U) /**< \brief (FLEXCOM1) USART Receive Holding Register */
  #define REG_FLEXCOM1_US_THR      (*(__O  uint32_t*)0xF802021CU) /**< \brief (FLEXCOM1) USART Transmit Holding Register */
  #define REG_FLEXCOM1_US_BRGR     (*(__IO uint32_t*)0xF8020220U) /**< \brief (FLEXCOM1) USART Baud Rate Generator Register */
  #define REG_FLEXCOM1_US_RTOR     (*(__IO uint32_t*)0xF8020224U) /**< \brief (FLEXCOM1) USART Receiver Timeout Register */
  #define REG_FLEXCOM1_US_TTGR     (*(__IO uint32_t*)0xF8020228U) /**< \brief (FLEXCOM1) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM1_US_FIDI     (*(__IO uint32_t*)0xF8020240U) /**< \brief (FLEXCOM1) USART FI DI Ratio Register */
  #define REG_FLEXCOM1_US_NER      (*(__I  uint32_t*)0xF8020244U) /**< \brief (FLEXCOM1) USART Number of Errors Register */
  #define REG_FLEXCOM1_US_IF       (*(__IO uint32_t*)0xF802024CU) /**< \brief (FLEXCOM1) USART IrDA Filter Register */
  #define REG_FLEXCOM1_US_MAN      (*(__IO uint32_t*)0xF8020250U) /**< \brief (FLEXCOM1) USART Manchester Configuration Register */
  #define REG_FLEXCOM1_US_LINMR    (*(__IO uint32_t*)0xF8020254U) /**< \brief (FLEXCOM1) USART LIN Mode Register */
  #define REG_FLEXCOM1_US_LINIR    (*(__IO uint32_t*)0xF8020258U) /**< \brief (FLEXCOM1) USART LIN Identifier Register */
  #define REG_FLEXCOM1_US_LINBRR   (*(__I  uint32_t*)0xF802025CU) /**< \brief (FLEXCOM1) USART LIN Baud Rate Register */
  #define REG_FLEXCOM1_US_LONMR    (*(__IO uint32_t*)0xF8020260U) /**< \brief (FLEXCOM1) USART LON Mode Register */
  #define REG_FLEXCOM1_US_LONPR    (*(__IO uint32_t*)0xF8020264U) /**< \brief (FLEXCOM1) USART LON Preamble Register */
  #define REG_FLEXCOM1_US_LONDL    (*(__IO uint32_t*)0xF8020268U) /**< \brief (FLEXCOM1) USART LON Data Length Register */
  #define REG_FLEXCOM1_US_LONL2HDR (*(__IO uint32_t*)0xF802026CU) /**< \brief (FLEXCOM1) USART LON L2HDR Register */
  #define REG_FLEXCOM1_US_LONBL    (*(__I  uint32_t*)0xF8020270U) /**< \brief (FLEXCOM1) USART LON Backlog Register */
  #define REG_FLEXCOM1_US_LONB1TX  (*(__IO uint32_t*)0xF8020274U) /**< \brief (FLEXCOM1) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM1_US_LONB1RX  (*(__IO uint32_t*)0xF8020278U) /**< \brief (FLEXCOM1) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM1_US_LONPRIO  (*(__IO uint32_t*)0xF802027CU) /**< \brief (FLEXCOM1) USART LON Priority Register */
  #define REG_FLEXCOM1_US_IDTTX    (*(__IO uint32_t*)0xF8020280U) /**< \brief (FLEXCOM1) USART LON IDT Tx Register */
  #define REG_FLEXCOM1_US_IDTRX    (*(__IO uint32_t*)0xF8020284U) /**< \brief (FLEXCOM1) USART LON IDT Rx Register */
  #define REG_FLEXCOM1_US_ICDIFF   (*(__IO uint32_t*)0xF8020288U) /**< \brief (FLEXCOM1) USART IC DIFF Register */
  #define REG_FLEXCOM1_US_CMPR     (*(__IO uint32_t*)0xF8020290U) /**< \brief (FLEXCOM1) USART Comparison Register */
  #define REG_FLEXCOM1_US_FMR      (*(__IO uint32_t*)0xF80202A0U) /**< \brief (FLEXCOM1) USART FIFO Mode Register */
  #define REG_FLEXCOM1_US_FLR      (*(__I  uint32_t*)0xF80202A4U) /**< \brief (FLEXCOM1) USART FIFO Level Register */
  #define REG_FLEXCOM1_US_FIER     (*(__O  uint32_t*)0xF80202A8U) /**< \brief (FLEXCOM1) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM1_US_FIDR     (*(__O  uint32_t*)0xF80202ACU) /**< \brief (FLEXCOM1) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM1_US_FIMR     (*(__I  uint32_t*)0xF80202B0U) /**< \brief (FLEXCOM1) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM1_US_FESR     (*(__I  uint32_t*)0xF80202B4U) /**< \brief (FLEXCOM1) USART FIFO Event Status Register */
  #define REG_FLEXCOM1_US_WPMR     (*(__IO uint32_t*)0xF80202E4U) /**< \brief (FLEXCOM1) USART Write Protection Mode Register */
  #define REG_FLEXCOM1_US_WPSR     (*(__I  uint32_t*)0xF80202E8U) /**< \brief (FLEXCOM1) USART Write Protection Status Register */
  #define REG_FLEXCOM1_SPI_CR      (*(__O  uint32_t*)0xF8020400U) /**< \brief (FLEXCOM1) SPI Control Register */
  #define REG_FLEXCOM1_SPI_MR      (*(__IO uint32_t*)0xF8020404U) /**< \brief (FLEXCOM1) SPI Mode Register */
  #define REG_FLEXCOM1_SPI_RDR     (*(__I  uint32_t*)0xF8020408U) /**< \brief (FLEXCOM1) SPI Receive Data Register */
  #define REG_FLEXCOM1_SPI_TDR     (*(__O  uint32_t*)0xF802040CU) /**< \brief (FLEXCOM1) SPI Transmit Data Register */
  #define REG_FLEXCOM1_SPI_SR      (*(__I  uint32_t*)0xF8020410U) /**< \brief (FLEXCOM1) SPI Status Register */
  #define REG_FLEXCOM1_SPI_IER     (*(__O  uint32_t*)0xF8020414U) /**< \brief (FLEXCOM1) SPI Interrupt Enable Register */
  #define REG_FLEXCOM1_SPI_IDR     (*(__O  uint32_t*)0xF8020418U) /**< \brief (FLEXCOM1) SPI Interrupt Disable Register */
  #define REG_FLEXCOM1_SPI_IMR     (*(__I  uint32_t*)0xF802041CU) /**< \brief (FLEXCOM1) SPI Interrupt Mask Register */
  #define REG_FLEXCOM1_SPI_CSR     (*(__IO uint32_t*)0xF8020430U) /**< \brief (FLEXCOM1) SPI Chip Select Register */
  #define REG_FLEXCOM1_SPI_FMR     (*(__IO uint32_t*)0xF8020440U) /**< \brief (FLEXCOM1) SPI FIFO Mode Register */
  #define REG_FLEXCOM1_SPI_FLR     (*(__I  uint32_t*)0xF8020444U) /**< \brief (FLEXCOM1) SPI FIFO Level Register */
  #define REG_FLEXCOM1_SPI_CMPR    (*(__IO uint32_t*)0xF8020448U) /**< \brief (FLEXCOM1) SPI Comparison Register */
  #define REG_FLEXCOM1_SPI_WPMR    (*(__IO uint32_t*)0xF80204E4U) /**< \brief (FLEXCOM1) SPI Write Protection Mode Register */
  #define REG_FLEXCOM1_SPI_WPSR    (*(__I  uint32_t*)0xF80204E8U) /**< \brief (FLEXCOM1) SPI Write Protection Status Register */
  #define REG_FLEXCOM1_TWI_CR      (*(__O  uint32_t*)0xF8020600U) /**< \brief (FLEXCOM1) TWI Control Register */
  #define REG_FLEXCOM1_TWI_MMR     (*(__IO uint32_t*)0xF8020604U) /**< \brief (FLEXCOM1) TWI Master Mode Register */
  #define REG_FLEXCOM1_TWI_SMR     (*(__IO uint32_t*)0xF8020608U) /**< \brief (FLEXCOM1) TWI Slave Mode Register */
  #define REG_FLEXCOM1_TWI_IADR    (*(__IO uint32_t*)0xF802060CU) /**< \brief (FLEXCOM1) TWI Internal Address Register */
  #define REG_FLEXCOM1_TWI_CWGR    (*(__IO uint32_t*)0xF8020610U) /**< \brief (FLEXCOM1) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM1_TWI_SR      (*(__I  uint32_t*)0xF8020620U) /**< \brief (FLEXCOM1) TWI Status Register */
  #define REG_FLEXCOM1_TWI_IER     (*(__O  uint32_t*)0xF8020624U) /**< \brief (FLEXCOM1) TWI Interrupt Enable Register */
  #define REG_FLEXCOM1_TWI_IDR     (*(__O  uint32_t*)0xF8020628U) /**< \brief (FLEXCOM1) TWI Interrupt Disable Register */
  #define REG_FLEXCOM1_TWI_IMR     (*(__I  uint32_t*)0xF802062CU) /**< \brief (FLEXCOM1) TWI Interrupt Mask Register */
  #define REG_FLEXCOM1_TWI_RHR     (*(__I  uint32_t*)0xF8020630U) /**< \brief (FLEXCOM1) TWI Receive Holding Register */
  #define REG_FLEXCOM1_TWI_THR     (*(__O  uint32_t*)0xF8020634U) /**< \brief (FLEXCOM1) TWI Transmit Holding Register */
  #define REG_FLEXCOM1_TWI_SMBTR   (*(__IO uint32_t*)0xF8020638U) /**< \brief (FLEXCOM1) TWI SMBus Timing Register */
  #define REG_FLEXCOM1_TWI_ACR     (*(__IO uint32_t*)0xF8020640U) /**< \brief (FLEXCOM1) TWI Alternative Command Register */
  #define REG_FLEXCOM1_TWI_FILTR   (*(__IO uint32_t*)0xF8020644U) /**< \brief (FLEXCOM1) TWI Filter Register */
  #define REG_FLEXCOM1_TWI_FMR     (*(__IO uint32_t*)0xF8020650U) /**< \brief (FLEXCOM1) TWI FIFO Mode Register */
  #define REG_FLEXCOM1_TWI_FLR     (*(__I  uint32_t*)0xF8020654U) /**< \brief (FLEXCOM1) TWI FIFO Level Register */
  #define REG_FLEXCOM1_TWI_FSR     (*(__I  uint32_t*)0xF8020660U) /**< \brief (FLEXCOM1) TWI FIFO Status Register */
  #define REG_FLEXCOM1_TWI_FIER    (*(__O  uint32_t*)0xF8020664U) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM1_TWI_FIDR    (*(__O  uint32_t*)0xF8020668U) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM1_TWI_FIMR    (*(__I  uint32_t*)0xF802066CU) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM1_TWI_WPMR    (*(__IO uint32_t*)0xF80206E4U) /**< \brief (FLEXCOM1) TWI Write Protection Mode Register */
  #define REG_FLEXCOM1_TWI_WPSR    (*(__I  uint32_t*)0xF80206E8U) /**< \brief (FLEXCOM1) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM1_INSTANCE_ */
