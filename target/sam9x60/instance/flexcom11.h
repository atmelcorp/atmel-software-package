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

#ifndef _SAM9X_FLEXCOM11_INSTANCE_
#define _SAM9X_FLEXCOM11_INSTANCE_

/* ========== Register definition for FLEXCOM11 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM11_MR                           (0xF0020000U) /**< \brief (FLEXCOM11) FLEXCOM Mode Register */
  #define REG_FLEXCOM11_RHR                          (0xF0020010U) /**< \brief (FLEXCOM11) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM11_THR                          (0xF0020020U) /**< \brief (FLEXCOM11) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM11_US_CR                        (0xF0020200U) /**< \brief (FLEXCOM11) USART Control Register */
  #define REG_FLEXCOM11_US_MR                        (0xF0020204U) /**< \brief (FLEXCOM11) USART Mode Register */
  #define REG_FLEXCOM11_US_IER                       (0xF0020208U) /**< \brief (FLEXCOM11) USART Interrupt Enable Register */
  #define REG_FLEXCOM11_US_IDR                       (0xF002020CU) /**< \brief (FLEXCOM11) USART Interrupt Disable Register */
  #define REG_FLEXCOM11_US_IMR                       (0xF0020210U) /**< \brief (FLEXCOM11) USART Interrupt Mask Register */
  #define REG_FLEXCOM11_US_CSR                       (0xF0020214U) /**< \brief (FLEXCOM11) USART Channel Status Register */
  #define REG_FLEXCOM11_US_RHR                       (0xF0020218U) /**< \brief (FLEXCOM11) USART Receive Holding Register */
  #define REG_FLEXCOM11_US_THR                       (0xF002021CU) /**< \brief (FLEXCOM11) USART Transmit Holding Register */
  #define REG_FLEXCOM11_US_BRGR                      (0xF0020220U) /**< \brief (FLEXCOM11) USART Baud Rate Generator Register */
  #define REG_FLEXCOM11_US_RTOR                      (0xF0020224U) /**< \brief (FLEXCOM11) USART Receiver Timeout Register */
  #define REG_FLEXCOM11_US_TTGR                      (0xF0020228U) /**< \brief (FLEXCOM11) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM11_US_FIDI                      (0xF0020240U) /**< \brief (FLEXCOM11) USART FI DI Ratio Register */
  #define REG_FLEXCOM11_US_NER                       (0xF0020244U) /**< \brief (FLEXCOM11) USART Number of Errors Register */
  #define REG_FLEXCOM11_US_IF                        (0xF002024CU) /**< \brief (FLEXCOM11) USART IrDA Filter Register */
  #define REG_FLEXCOM11_US_MAN                       (0xF0020250U) /**< \brief (FLEXCOM11) USART Manchester Configuration Register */
  #define REG_FLEXCOM11_US_LINMR                     (0xF0020254U) /**< \brief (FLEXCOM11) USART LIN Mode Register */
  #define REG_FLEXCOM11_US_LINIR                     (0xF0020258U) /**< \brief (FLEXCOM11) USART LIN Identifier Register */
  #define REG_FLEXCOM11_US_LINBRR                    (0xF002025CU) /**< \brief (FLEXCOM11) USART LIN Baud Rate Register */
  #define REG_FLEXCOM11_US_LONMR                     (0xF0020260U) /**< \brief (FLEXCOM11) USART LON Mode Register */
  #define REG_FLEXCOM11_US_LONPR                     (0xF0020264U) /**< \brief (FLEXCOM11) USART LON Preamble Register */
  #define REG_FLEXCOM11_US_LONDL                     (0xF0020268U) /**< \brief (FLEXCOM11) USART LON Data Length Register */
  #define REG_FLEXCOM11_US_LONL2HDR                  (0xF002026CU) /**< \brief (FLEXCOM11) USART LON L2HDR Register */
  #define REG_FLEXCOM11_US_LONBL                     (0xF0020270U) /**< \brief (FLEXCOM11) USART LON Backlog Register */
  #define REG_FLEXCOM11_US_LONB1TX                   (0xF0020274U) /**< \brief (FLEXCOM11) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM11_US_LONB1RX                   (0xF0020278U) /**< \brief (FLEXCOM11) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM11_US_LONPRIO                   (0xF002027CU) /**< \brief (FLEXCOM11) USART LON Priority Register */
  #define REG_FLEXCOM11_US_IDTTX                     (0xF0020280U) /**< \brief (FLEXCOM11) USART LON IDT Tx Register */
  #define REG_FLEXCOM11_US_IDTRX                     (0xF0020284U) /**< \brief (FLEXCOM11) USART LON IDT Rx Register */
  #define REG_FLEXCOM11_US_ICDIFF                    (0xF0020288U) /**< \brief (FLEXCOM11) USART IC DIFF Register */
  #define REG_FLEXCOM11_US_CMPR                      (0xF0020290U) /**< \brief (FLEXCOM11) USART Comparison Register */
  #define REG_FLEXCOM11_US_FMR                       (0xF00202A0U) /**< \brief (FLEXCOM11) USART FIFO Mode Register */
  #define REG_FLEXCOM11_US_FLR                       (0xF00202A4U) /**< \brief (FLEXCOM11) USART FIFO Level Register */
  #define REG_FLEXCOM11_US_FIER                      (0xF00202A8U) /**< \brief (FLEXCOM11) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM11_US_FIDR                      (0xF00202ACU) /**< \brief (FLEXCOM11) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM11_US_FIMR                      (0xF00202B0U) /**< \brief (FLEXCOM11) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM11_US_FESR                      (0xF00202B4U) /**< \brief (FLEXCOM11) USART FIFO Event Status Register */
  #define REG_FLEXCOM11_US_WPMR                      (0xF00202E4U) /**< \brief (FLEXCOM11) USART Write Protection Mode Register */
  #define REG_FLEXCOM11_US_WPSR                      (0xF00202E8U) /**< \brief (FLEXCOM11) USART Write Protection Status Register */
  #define REG_FLEXCOM11_SPI_CR                       (0xF0020400U) /**< \brief (FLEXCOM11) SPI Control Register */
  #define REG_FLEXCOM11_SPI_MR                       (0xF0020404U) /**< \brief (FLEXCOM11) SPI Mode Register */
  #define REG_FLEXCOM11_SPI_RDR                      (0xF0020408U) /**< \brief (FLEXCOM11) SPI Receive Data Register */
  #define REG_FLEXCOM11_SPI_TDR                      (0xF002040CU) /**< \brief (FLEXCOM11) SPI Transmit Data Register */
  #define REG_FLEXCOM11_SPI_SR                       (0xF0020410U) /**< \brief (FLEXCOM11) SPI Status Register */
  #define REG_FLEXCOM11_SPI_IER                      (0xF0020414U) /**< \brief (FLEXCOM11) SPI Interrupt Enable Register */
  #define REG_FLEXCOM11_SPI_IDR                      (0xF0020418U) /**< \brief (FLEXCOM11) SPI Interrupt Disable Register */
  #define REG_FLEXCOM11_SPI_IMR                      (0xF002041CU) /**< \brief (FLEXCOM11) SPI Interrupt Mask Register */
  #define REG_FLEXCOM11_SPI_CSR                      (0xF0020430U) /**< \brief (FLEXCOM11) SPI Chip Select Register */
  #define REG_FLEXCOM11_SPI_FMR                      (0xF0020440U) /**< \brief (FLEXCOM11) SPI FIFO Mode Register */
  #define REG_FLEXCOM11_SPI_FLR                      (0xF0020444U) /**< \brief (FLEXCOM11) SPI FIFO Level Register */
  #define REG_FLEXCOM11_SPI_CMPR                     (0xF0020448U) /**< \brief (FLEXCOM11) SPI Comparison Register */
  #define REG_FLEXCOM11_SPI_WPMR                     (0xF00204E4U) /**< \brief (FLEXCOM11) SPI Write Protection Mode Register */
  #define REG_FLEXCOM11_SPI_WPSR                     (0xF00204E8U) /**< \brief (FLEXCOM11) SPI Write Protection Status Register */
  #define REG_FLEXCOM11_TWI_CR                       (0xF0020600U) /**< \brief (FLEXCOM11) TWI Control Register */
  #define REG_FLEXCOM11_TWI_MMR                      (0xF0020604U) /**< \brief (FLEXCOM11) TWI Master Mode Register */
  #define REG_FLEXCOM11_TWI_SMR                      (0xF0020608U) /**< \brief (FLEXCOM11) TWI Slave Mode Register */
  #define REG_FLEXCOM11_TWI_IADR                     (0xF002060CU) /**< \brief (FLEXCOM11) TWI Internal Address Register */
  #define REG_FLEXCOM11_TWI_CWGR                     (0xF0020610U) /**< \brief (FLEXCOM11) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM11_TWI_SR                       (0xF0020620U) /**< \brief (FLEXCOM11) TWI Status Register */
  #define REG_FLEXCOM11_TWI_IER                      (0xF0020624U) /**< \brief (FLEXCOM11) TWI Interrupt Enable Register */
  #define REG_FLEXCOM11_TWI_IDR                      (0xF0020628U) /**< \brief (FLEXCOM11) TWI Interrupt Disable Register */
  #define REG_FLEXCOM11_TWI_IMR                      (0xF002062CU) /**< \brief (FLEXCOM11) TWI Interrupt Mask Register */
  #define REG_FLEXCOM11_TWI_RHR                      (0xF0020630U) /**< \brief (FLEXCOM11) TWI Receive Holding Register */
  #define REG_FLEXCOM11_TWI_THR                      (0xF0020634U) /**< \brief (FLEXCOM11) TWI Transmit Holding Register */
  #define REG_FLEXCOM11_TWI_SMBTR                    (0xF0020638U) /**< \brief (FLEXCOM11) TWI SMBus Timing Register */
  #define REG_FLEXCOM11_TWI_ACR                      (0xF0020640U) /**< \brief (FLEXCOM11) TWI Alternative Command Register */
  #define REG_FLEXCOM11_TWI_FILTR                    (0xF0020644U) /**< \brief (FLEXCOM11) TWI Filter Register */
  #define REG_FLEXCOM11_TWI_FMR                      (0xF0020650U) /**< \brief (FLEXCOM11) TWI FIFO Mode Register */
  #define REG_FLEXCOM11_TWI_FLR                      (0xF0020654U) /**< \brief (FLEXCOM11) TWI FIFO Level Register */
  #define REG_FLEXCOM11_TWI_FSR                      (0xF0020660U) /**< \brief (FLEXCOM11) TWI FIFO Status Register */
  #define REG_FLEXCOM11_TWI_FIER                     (0xF0020664U) /**< \brief (FLEXCOM11) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM11_TWI_FIDR                     (0xF0020668U) /**< \brief (FLEXCOM11) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM11_TWI_FIMR                     (0xF002066CU) /**< \brief (FLEXCOM11) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM11_TWI_WPMR                     (0xF00206E4U) /**< \brief (FLEXCOM11) TWI Write Protection Mode Register */
  #define REG_FLEXCOM11_TWI_WPSR                     (0xF00206E8U) /**< \brief (FLEXCOM11) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM11_MR          (*(__IO uint32_t*)0xF0020000U) /**< \brief (FLEXCOM11) FLEXCOM Mode Register */
  #define REG_FLEXCOM11_RHR         (*(__I  uint32_t*)0xF0020010U) /**< \brief (FLEXCOM11) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM11_THR         (*(__IO uint32_t*)0xF0020020U) /**< \brief (FLEXCOM11) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM11_US_CR       (*(__O  uint32_t*)0xF0020200U) /**< \brief (FLEXCOM11) USART Control Register */
  #define REG_FLEXCOM11_US_MR       (*(__IO uint32_t*)0xF0020204U) /**< \brief (FLEXCOM11) USART Mode Register */
  #define REG_FLEXCOM11_US_IER      (*(__O  uint32_t*)0xF0020208U) /**< \brief (FLEXCOM11) USART Interrupt Enable Register */
  #define REG_FLEXCOM11_US_IDR      (*(__O  uint32_t*)0xF002020CU) /**< \brief (FLEXCOM11) USART Interrupt Disable Register */
  #define REG_FLEXCOM11_US_IMR      (*(__I  uint32_t*)0xF0020210U) /**< \brief (FLEXCOM11) USART Interrupt Mask Register */
  #define REG_FLEXCOM11_US_CSR      (*(__I  uint32_t*)0xF0020214U) /**< \brief (FLEXCOM11) USART Channel Status Register */
  #define REG_FLEXCOM11_US_RHR      (*(__I  uint32_t*)0xF0020218U) /**< \brief (FLEXCOM11) USART Receive Holding Register */
  #define REG_FLEXCOM11_US_THR      (*(__O  uint32_t*)0xF002021CU) /**< \brief (FLEXCOM11) USART Transmit Holding Register */
  #define REG_FLEXCOM11_US_BRGR     (*(__IO uint32_t*)0xF0020220U) /**< \brief (FLEXCOM11) USART Baud Rate Generator Register */
  #define REG_FLEXCOM11_US_RTOR     (*(__IO uint32_t*)0xF0020224U) /**< \brief (FLEXCOM11) USART Receiver Timeout Register */
  #define REG_FLEXCOM11_US_TTGR     (*(__IO uint32_t*)0xF0020228U) /**< \brief (FLEXCOM11) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM11_US_FIDI     (*(__IO uint32_t*)0xF0020240U) /**< \brief (FLEXCOM11) USART FI DI Ratio Register */
  #define REG_FLEXCOM11_US_NER      (*(__I  uint32_t*)0xF0020244U) /**< \brief (FLEXCOM11) USART Number of Errors Register */
  #define REG_FLEXCOM11_US_IF       (*(__IO uint32_t*)0xF002024CU) /**< \brief (FLEXCOM11) USART IrDA Filter Register */
  #define REG_FLEXCOM11_US_MAN      (*(__IO uint32_t*)0xF0020250U) /**< \brief (FLEXCOM11) USART Manchester Configuration Register */
  #define REG_FLEXCOM11_US_LINMR    (*(__IO uint32_t*)0xF0020254U) /**< \brief (FLEXCOM11) USART LIN Mode Register */
  #define REG_FLEXCOM11_US_LINIR    (*(__IO uint32_t*)0xF0020258U) /**< \brief (FLEXCOM11) USART LIN Identifier Register */
  #define REG_FLEXCOM11_US_LINBRR   (*(__I  uint32_t*)0xF002025CU) /**< \brief (FLEXCOM11) USART LIN Baud Rate Register */
  #define REG_FLEXCOM11_US_LONMR    (*(__IO uint32_t*)0xF0020260U) /**< \brief (FLEXCOM11) USART LON Mode Register */
  #define REG_FLEXCOM11_US_LONPR    (*(__IO uint32_t*)0xF0020264U) /**< \brief (FLEXCOM11) USART LON Preamble Register */
  #define REG_FLEXCOM11_US_LONDL    (*(__IO uint32_t*)0xF0020268U) /**< \brief (FLEXCOM11) USART LON Data Length Register */
  #define REG_FLEXCOM11_US_LONL2HDR (*(__IO uint32_t*)0xF002026CU) /**< \brief (FLEXCOM11) USART LON L2HDR Register */
  #define REG_FLEXCOM11_US_LONBL    (*(__I  uint32_t*)0xF0020270U) /**< \brief (FLEXCOM11) USART LON Backlog Register */
  #define REG_FLEXCOM11_US_LONB1TX  (*(__IO uint32_t*)0xF0020274U) /**< \brief (FLEXCOM11) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM11_US_LONB1RX  (*(__IO uint32_t*)0xF0020278U) /**< \brief (FLEXCOM11) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM11_US_LONPRIO  (*(__IO uint32_t*)0xF002027CU) /**< \brief (FLEXCOM11) USART LON Priority Register */
  #define REG_FLEXCOM11_US_IDTTX    (*(__IO uint32_t*)0xF0020280U) /**< \brief (FLEXCOM11) USART LON IDT Tx Register */
  #define REG_FLEXCOM11_US_IDTRX    (*(__IO uint32_t*)0xF0020284U) /**< \brief (FLEXCOM11) USART LON IDT Rx Register */
  #define REG_FLEXCOM11_US_ICDIFF   (*(__IO uint32_t*)0xF0020288U) /**< \brief (FLEXCOM11) USART IC DIFF Register */
  #define REG_FLEXCOM11_US_CMPR     (*(__IO uint32_t*)0xF0020290U) /**< \brief (FLEXCOM11) USART Comparison Register */
  #define REG_FLEXCOM11_US_FMR      (*(__IO uint32_t*)0xF00202A0U) /**< \brief (FLEXCOM11) USART FIFO Mode Register */
  #define REG_FLEXCOM11_US_FLR      (*(__I  uint32_t*)0xF00202A4U) /**< \brief (FLEXCOM11) USART FIFO Level Register */
  #define REG_FLEXCOM11_US_FIER     (*(__O  uint32_t*)0xF00202A8U) /**< \brief (FLEXCOM11) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM11_US_FIDR     (*(__O  uint32_t*)0xF00202ACU) /**< \brief (FLEXCOM11) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM11_US_FIMR     (*(__I  uint32_t*)0xF00202B0U) /**< \brief (FLEXCOM11) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM11_US_FESR     (*(__I  uint32_t*)0xF00202B4U) /**< \brief (FLEXCOM11) USART FIFO Event Status Register */
  #define REG_FLEXCOM11_US_WPMR     (*(__IO uint32_t*)0xF00202E4U) /**< \brief (FLEXCOM11) USART Write Protection Mode Register */
  #define REG_FLEXCOM11_US_WPSR     (*(__I  uint32_t*)0xF00202E8U) /**< \brief (FLEXCOM11) USART Write Protection Status Register */
  #define REG_FLEXCOM11_SPI_CR      (*(__O  uint32_t*)0xF0020400U) /**< \brief (FLEXCOM11) SPI Control Register */
  #define REG_FLEXCOM11_SPI_MR      (*(__IO uint32_t*)0xF0020404U) /**< \brief (FLEXCOM11) SPI Mode Register */
  #define REG_FLEXCOM11_SPI_RDR     (*(__I  uint32_t*)0xF0020408U) /**< \brief (FLEXCOM11) SPI Receive Data Register */
  #define REG_FLEXCOM11_SPI_TDR     (*(__O  uint32_t*)0xF002040CU) /**< \brief (FLEXCOM11) SPI Transmit Data Register */
  #define REG_FLEXCOM11_SPI_SR      (*(__I  uint32_t*)0xF0020410U) /**< \brief (FLEXCOM11) SPI Status Register */
  #define REG_FLEXCOM11_SPI_IER     (*(__O  uint32_t*)0xF0020414U) /**< \brief (FLEXCOM11) SPI Interrupt Enable Register */
  #define REG_FLEXCOM11_SPI_IDR     (*(__O  uint32_t*)0xF0020418U) /**< \brief (FLEXCOM11) SPI Interrupt Disable Register */
  #define REG_FLEXCOM11_SPI_IMR     (*(__I  uint32_t*)0xF002041CU) /**< \brief (FLEXCOM11) SPI Interrupt Mask Register */
  #define REG_FLEXCOM11_SPI_CSR     (*(__IO uint32_t*)0xF0020430U) /**< \brief (FLEXCOM11) SPI Chip Select Register */
  #define REG_FLEXCOM11_SPI_FMR     (*(__IO uint32_t*)0xF0020440U) /**< \brief (FLEXCOM11) SPI FIFO Mode Register */
  #define REG_FLEXCOM11_SPI_FLR     (*(__I  uint32_t*)0xF0020444U) /**< \brief (FLEXCOM11) SPI FIFO Level Register */
  #define REG_FLEXCOM11_SPI_CMPR    (*(__IO uint32_t*)0xF0020448U) /**< \brief (FLEXCOM11) SPI Comparison Register */
  #define REG_FLEXCOM11_SPI_WPMR    (*(__IO uint32_t*)0xF00204E4U) /**< \brief (FLEXCOM11) SPI Write Protection Mode Register */
  #define REG_FLEXCOM11_SPI_WPSR    (*(__I  uint32_t*)0xF00204E8U) /**< \brief (FLEXCOM11) SPI Write Protection Status Register */
  #define REG_FLEXCOM11_TWI_CR      (*(__O  uint32_t*)0xF0020600U) /**< \brief (FLEXCOM11) TWI Control Register */
  #define REG_FLEXCOM11_TWI_MMR     (*(__IO uint32_t*)0xF0020604U) /**< \brief (FLEXCOM11) TWI Master Mode Register */
  #define REG_FLEXCOM11_TWI_SMR     (*(__IO uint32_t*)0xF0020608U) /**< \brief (FLEXCOM11) TWI Slave Mode Register */
  #define REG_FLEXCOM11_TWI_IADR    (*(__IO uint32_t*)0xF002060CU) /**< \brief (FLEXCOM11) TWI Internal Address Register */
  #define REG_FLEXCOM11_TWI_CWGR    (*(__IO uint32_t*)0xF0020610U) /**< \brief (FLEXCOM11) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM11_TWI_SR      (*(__I  uint32_t*)0xF0020620U) /**< \brief (FLEXCOM11) TWI Status Register */
  #define REG_FLEXCOM11_TWI_IER     (*(__O  uint32_t*)0xF0020624U) /**< \brief (FLEXCOM11) TWI Interrupt Enable Register */
  #define REG_FLEXCOM11_TWI_IDR     (*(__O  uint32_t*)0xF0020628U) /**< \brief (FLEXCOM11) TWI Interrupt Disable Register */
  #define REG_FLEXCOM11_TWI_IMR     (*(__I  uint32_t*)0xF002062CU) /**< \brief (FLEXCOM11) TWI Interrupt Mask Register */
  #define REG_FLEXCOM11_TWI_RHR     (*(__I  uint32_t*)0xF0020630U) /**< \brief (FLEXCOM11) TWI Receive Holding Register */
  #define REG_FLEXCOM11_TWI_THR     (*(__O  uint32_t*)0xF0020634U) /**< \brief (FLEXCOM11) TWI Transmit Holding Register */
  #define REG_FLEXCOM11_TWI_SMBTR   (*(__IO uint32_t*)0xF0020638U) /**< \brief (FLEXCOM11) TWI SMBus Timing Register */
  #define REG_FLEXCOM11_TWI_ACR     (*(__IO uint32_t*)0xF0020640U) /**< \brief (FLEXCOM11) TWI Alternative Command Register */
  #define REG_FLEXCOM11_TWI_FILTR   (*(__IO uint32_t*)0xF0020644U) /**< \brief (FLEXCOM11) TWI Filter Register */
  #define REG_FLEXCOM11_TWI_FMR     (*(__IO uint32_t*)0xF0020650U) /**< \brief (FLEXCOM11) TWI FIFO Mode Register */
  #define REG_FLEXCOM11_TWI_FLR     (*(__I  uint32_t*)0xF0020654U) /**< \brief (FLEXCOM11) TWI FIFO Level Register */
  #define REG_FLEXCOM11_TWI_FSR     (*(__I  uint32_t*)0xF0020660U) /**< \brief (FLEXCOM11) TWI FIFO Status Register */
  #define REG_FLEXCOM11_TWI_FIER    (*(__O  uint32_t*)0xF0020664U) /**< \brief (FLEXCOM11) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM11_TWI_FIDR    (*(__O  uint32_t*)0xF0020668U) /**< \brief (FLEXCOM11) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM11_TWI_FIMR    (*(__I  uint32_t*)0xF002066CU) /**< \brief (FLEXCOM11) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM11_TWI_WPMR    (*(__IO uint32_t*)0xF00206E4U) /**< \brief (FLEXCOM11) TWI Write Protection Mode Register */
  #define REG_FLEXCOM11_TWI_WPSR    (*(__I  uint32_t*)0xF00206E8U) /**< \brief (FLEXCOM11) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM11_INSTANCE_ */
