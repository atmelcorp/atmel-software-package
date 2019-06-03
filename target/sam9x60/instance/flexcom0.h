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

#ifndef _SAM9X_FLEXCOM0_INSTANCE_
#define _SAM9X_FLEXCOM0_INSTANCE_

/* ========== Register definition for FLEXCOM0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM0_MR                           (0xF801C000U) /**< \brief (FLEXCOM0) FLEXCOM Mode Register */
  #define REG_FLEXCOM0_RHR                          (0xF801C010U) /**< \brief (FLEXCOM0) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM0_THR                          (0xF801C020U) /**< \brief (FLEXCOM0) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM0_US_CR                        (0xF801C200U) /**< \brief (FLEXCOM0) USART Control Register */
  #define REG_FLEXCOM0_US_MR                        (0xF801C204U) /**< \brief (FLEXCOM0) USART Mode Register */
  #define REG_FLEXCOM0_US_IER                       (0xF801C208U) /**< \brief (FLEXCOM0) USART Interrupt Enable Register */
  #define REG_FLEXCOM0_US_IDR                       (0xF801C20CU) /**< \brief (FLEXCOM0) USART Interrupt Disable Register */
  #define REG_FLEXCOM0_US_IMR                       (0xF801C210U) /**< \brief (FLEXCOM0) USART Interrupt Mask Register */
  #define REG_FLEXCOM0_US_CSR                       (0xF801C214U) /**< \brief (FLEXCOM0) USART Channel Status Register */
  #define REG_FLEXCOM0_US_RHR                       (0xF801C218U) /**< \brief (FLEXCOM0) USART Receive Holding Register */
  #define REG_FLEXCOM0_US_THR                       (0xF801C21CU) /**< \brief (FLEXCOM0) USART Transmit Holding Register */
  #define REG_FLEXCOM0_US_BRGR                      (0xF801C220U) /**< \brief (FLEXCOM0) USART Baud Rate Generator Register */
  #define REG_FLEXCOM0_US_RTOR                      (0xF801C224U) /**< \brief (FLEXCOM0) USART Receiver Timeout Register */
  #define REG_FLEXCOM0_US_TTGR                      (0xF801C228U) /**< \brief (FLEXCOM0) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM0_US_FIDI                      (0xF801C240U) /**< \brief (FLEXCOM0) USART FI DI Ratio Register */
  #define REG_FLEXCOM0_US_NER                       (0xF801C244U) /**< \brief (FLEXCOM0) USART Number of Errors Register */
  #define REG_FLEXCOM0_US_IF                        (0xF801C24CU) /**< \brief (FLEXCOM0) USART IrDA Filter Register */
  #define REG_FLEXCOM0_US_MAN                       (0xF801C250U) /**< \brief (FLEXCOM0) USART Manchester Configuration Register */
  #define REG_FLEXCOM0_US_LINMR                     (0xF801C254U) /**< \brief (FLEXCOM0) USART LIN Mode Register */
  #define REG_FLEXCOM0_US_LINIR                     (0xF801C258U) /**< \brief (FLEXCOM0) USART LIN Identifier Register */
  #define REG_FLEXCOM0_US_LINBRR                    (0xF801C25CU) /**< \brief (FLEXCOM0) USART LIN Baud Rate Register */
  #define REG_FLEXCOM0_US_LONMR                     (0xF801C260U) /**< \brief (FLEXCOM0) USART LON Mode Register */
  #define REG_FLEXCOM0_US_LONPR                     (0xF801C264U) /**< \brief (FLEXCOM0) USART LON Preamble Register */
  #define REG_FLEXCOM0_US_LONDL                     (0xF801C268U) /**< \brief (FLEXCOM0) USART LON Data Length Register */
  #define REG_FLEXCOM0_US_LONL2HDR                  (0xF801C26CU) /**< \brief (FLEXCOM0) USART LON L2HDR Register */
  #define REG_FLEXCOM0_US_LONBL                     (0xF801C270U) /**< \brief (FLEXCOM0) USART LON Backlog Register */
  #define REG_FLEXCOM0_US_LONB1TX                   (0xF801C274U) /**< \brief (FLEXCOM0) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM0_US_LONB1RX                   (0xF801C278U) /**< \brief (FLEXCOM0) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM0_US_LONPRIO                   (0xF801C27CU) /**< \brief (FLEXCOM0) USART LON Priority Register */
  #define REG_FLEXCOM0_US_IDTTX                     (0xF801C280U) /**< \brief (FLEXCOM0) USART LON IDT Tx Register */
  #define REG_FLEXCOM0_US_IDTRX                     (0xF801C284U) /**< \brief (FLEXCOM0) USART LON IDT Rx Register */
  #define REG_FLEXCOM0_US_ICDIFF                    (0xF801C288U) /**< \brief (FLEXCOM0) USART IC DIFF Register */
  #define REG_FLEXCOM0_US_CMPR                      (0xF801C290U) /**< \brief (FLEXCOM0) USART Comparison Register */
  #define REG_FLEXCOM0_US_FMR                       (0xF801C2A0U) /**< \brief (FLEXCOM0) USART FIFO Mode Register */
  #define REG_FLEXCOM0_US_FLR                       (0xF801C2A4U) /**< \brief (FLEXCOM0) USART FIFO Level Register */
  #define REG_FLEXCOM0_US_FIER                      (0xF801C2A8U) /**< \brief (FLEXCOM0) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM0_US_FIDR                      (0xF801C2ACU) /**< \brief (FLEXCOM0) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM0_US_FIMR                      (0xF801C2B0U) /**< \brief (FLEXCOM0) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM0_US_FESR                      (0xF801C2B4U) /**< \brief (FLEXCOM0) USART FIFO Event Status Register */
  #define REG_FLEXCOM0_US_WPMR                      (0xF801C2E4U) /**< \brief (FLEXCOM0) USART Write Protection Mode Register */
  #define REG_FLEXCOM0_US_WPSR                      (0xF801C2E8U) /**< \brief (FLEXCOM0) USART Write Protection Status Register */
  #define REG_FLEXCOM0_SPI_CR                       (0xF801C400U) /**< \brief (FLEXCOM0) SPI Control Register */
  #define REG_FLEXCOM0_SPI_MR                       (0xF801C404U) /**< \brief (FLEXCOM0) SPI Mode Register */
  #define REG_FLEXCOM0_SPI_RDR                      (0xF801C408U) /**< \brief (FLEXCOM0) SPI Receive Data Register */
  #define REG_FLEXCOM0_SPI_TDR                      (0xF801C40CU) /**< \brief (FLEXCOM0) SPI Transmit Data Register */
  #define REG_FLEXCOM0_SPI_SR                       (0xF801C410U) /**< \brief (FLEXCOM0) SPI Status Register */
  #define REG_FLEXCOM0_SPI_IER                      (0xF801C414U) /**< \brief (FLEXCOM0) SPI Interrupt Enable Register */
  #define REG_FLEXCOM0_SPI_IDR                      (0xF801C418U) /**< \brief (FLEXCOM0) SPI Interrupt Disable Register */
  #define REG_FLEXCOM0_SPI_IMR                      (0xF801C41CU) /**< \brief (FLEXCOM0) SPI Interrupt Mask Register */
  #define REG_FLEXCOM0_SPI_CSR                      (0xF801C430U) /**< \brief (FLEXCOM0) SPI Chip Select Register */
  #define REG_FLEXCOM0_SPI_FMR                      (0xF801C440U) /**< \brief (FLEXCOM0) SPI FIFO Mode Register */
  #define REG_FLEXCOM0_SPI_FLR                      (0xF801C444U) /**< \brief (FLEXCOM0) SPI FIFO Level Register */
  #define REG_FLEXCOM0_SPI_CMPR                     (0xF801C448U) /**< \brief (FLEXCOM0) SPI Comparison Register */
  #define REG_FLEXCOM0_SPI_WPMR                     (0xF801C4E4U) /**< \brief (FLEXCOM0) SPI Write Protection Mode Register */
  #define REG_FLEXCOM0_SPI_WPSR                     (0xF801C4E8U) /**< \brief (FLEXCOM0) SPI Write Protection Status Register */
  #define REG_FLEXCOM0_TWI_CR                       (0xF801C600U) /**< \brief (FLEXCOM0) TWI Control Register */
  #define REG_FLEXCOM0_TWI_MMR                      (0xF801C604U) /**< \brief (FLEXCOM0) TWI Master Mode Register */
  #define REG_FLEXCOM0_TWI_SMR                      (0xF801C608U) /**< \brief (FLEXCOM0) TWI Slave Mode Register */
  #define REG_FLEXCOM0_TWI_IADR                     (0xF801C60CU) /**< \brief (FLEXCOM0) TWI Internal Address Register */
  #define REG_FLEXCOM0_TWI_CWGR                     (0xF801C610U) /**< \brief (FLEXCOM0) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM0_TWI_SR                       (0xF801C620U) /**< \brief (FLEXCOM0) TWI Status Register */
  #define REG_FLEXCOM0_TWI_IER                      (0xF801C624U) /**< \brief (FLEXCOM0) TWI Interrupt Enable Register */
  #define REG_FLEXCOM0_TWI_IDR                      (0xF801C628U) /**< \brief (FLEXCOM0) TWI Interrupt Disable Register */
  #define REG_FLEXCOM0_TWI_IMR                      (0xF801C62CU) /**< \brief (FLEXCOM0) TWI Interrupt Mask Register */
  #define REG_FLEXCOM0_TWI_RHR                      (0xF801C630U) /**< \brief (FLEXCOM0) TWI Receive Holding Register */
  #define REG_FLEXCOM0_TWI_THR                      (0xF801C634U) /**< \brief (FLEXCOM0) TWI Transmit Holding Register */
  #define REG_FLEXCOM0_TWI_SMBTR                    (0xF801C638U) /**< \brief (FLEXCOM0) TWI SMBus Timing Register */
  #define REG_FLEXCOM0_TWI_ACR                      (0xF801C640U) /**< \brief (FLEXCOM0) TWI Alternative Command Register */
  #define REG_FLEXCOM0_TWI_FILTR                    (0xF801C644U) /**< \brief (FLEXCOM0) TWI Filter Register */
  #define REG_FLEXCOM0_TWI_FMR                      (0xF801C650U) /**< \brief (FLEXCOM0) TWI FIFO Mode Register */
  #define REG_FLEXCOM0_TWI_FLR                      (0xF801C654U) /**< \brief (FLEXCOM0) TWI FIFO Level Register */
  #define REG_FLEXCOM0_TWI_FSR                      (0xF801C660U) /**< \brief (FLEXCOM0) TWI FIFO Status Register */
  #define REG_FLEXCOM0_TWI_FIER                     (0xF801C664U) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM0_TWI_FIDR                     (0xF801C668U) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM0_TWI_FIMR                     (0xF801C66CU) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM0_TWI_WPMR                     (0xF801C6E4U) /**< \brief (FLEXCOM0) TWI Write Protection Mode Register */
  #define REG_FLEXCOM0_TWI_WPSR                     (0xF801C6E8U) /**< \brief (FLEXCOM0) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM0_MR          (*(__IO uint32_t*)0xF801C000U) /**< \brief (FLEXCOM0) FLEXCOM Mode Register */
  #define REG_FLEXCOM0_RHR         (*(__I  uint32_t*)0xF801C010U) /**< \brief (FLEXCOM0) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM0_THR         (*(__IO uint32_t*)0xF801C020U) /**< \brief (FLEXCOM0) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM0_US_CR       (*(__O  uint32_t*)0xF801C200U) /**< \brief (FLEXCOM0) USART Control Register */
  #define REG_FLEXCOM0_US_MR       (*(__IO uint32_t*)0xF801C204U) /**< \brief (FLEXCOM0) USART Mode Register */
  #define REG_FLEXCOM0_US_IER      (*(__O  uint32_t*)0xF801C208U) /**< \brief (FLEXCOM0) USART Interrupt Enable Register */
  #define REG_FLEXCOM0_US_IDR      (*(__O  uint32_t*)0xF801C20CU) /**< \brief (FLEXCOM0) USART Interrupt Disable Register */
  #define REG_FLEXCOM0_US_IMR      (*(__I  uint32_t*)0xF801C210U) /**< \brief (FLEXCOM0) USART Interrupt Mask Register */
  #define REG_FLEXCOM0_US_CSR      (*(__I  uint32_t*)0xF801C214U) /**< \brief (FLEXCOM0) USART Channel Status Register */
  #define REG_FLEXCOM0_US_RHR      (*(__I  uint32_t*)0xF801C218U) /**< \brief (FLEXCOM0) USART Receive Holding Register */
  #define REG_FLEXCOM0_US_THR      (*(__O  uint32_t*)0xF801C21CU) /**< \brief (FLEXCOM0) USART Transmit Holding Register */
  #define REG_FLEXCOM0_US_BRGR     (*(__IO uint32_t*)0xF801C220U) /**< \brief (FLEXCOM0) USART Baud Rate Generator Register */
  #define REG_FLEXCOM0_US_RTOR     (*(__IO uint32_t*)0xF801C224U) /**< \brief (FLEXCOM0) USART Receiver Timeout Register */
  #define REG_FLEXCOM0_US_TTGR     (*(__IO uint32_t*)0xF801C228U) /**< \brief (FLEXCOM0) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM0_US_FIDI     (*(__IO uint32_t*)0xF801C240U) /**< \brief (FLEXCOM0) USART FI DI Ratio Register */
  #define REG_FLEXCOM0_US_NER      (*(__I  uint32_t*)0xF801C244U) /**< \brief (FLEXCOM0) USART Number of Errors Register */
  #define REG_FLEXCOM0_US_IF       (*(__IO uint32_t*)0xF801C24CU) /**< \brief (FLEXCOM0) USART IrDA Filter Register */
  #define REG_FLEXCOM0_US_MAN      (*(__IO uint32_t*)0xF801C250U) /**< \brief (FLEXCOM0) USART Manchester Configuration Register */
  #define REG_FLEXCOM0_US_LINMR    (*(__IO uint32_t*)0xF801C254U) /**< \brief (FLEXCOM0) USART LIN Mode Register */
  #define REG_FLEXCOM0_US_LINIR    (*(__IO uint32_t*)0xF801C258U) /**< \brief (FLEXCOM0) USART LIN Identifier Register */
  #define REG_FLEXCOM0_US_LINBRR   (*(__I  uint32_t*)0xF801C25CU) /**< \brief (FLEXCOM0) USART LIN Baud Rate Register */
  #define REG_FLEXCOM0_US_LONMR    (*(__IO uint32_t*)0xF801C260U) /**< \brief (FLEXCOM0) USART LON Mode Register */
  #define REG_FLEXCOM0_US_LONPR    (*(__IO uint32_t*)0xF801C264U) /**< \brief (FLEXCOM0) USART LON Preamble Register */
  #define REG_FLEXCOM0_US_LONDL    (*(__IO uint32_t*)0xF801C268U) /**< \brief (FLEXCOM0) USART LON Data Length Register */
  #define REG_FLEXCOM0_US_LONL2HDR (*(__IO uint32_t*)0xF801C26CU) /**< \brief (FLEXCOM0) USART LON L2HDR Register */
  #define REG_FLEXCOM0_US_LONBL    (*(__I  uint32_t*)0xF801C270U) /**< \brief (FLEXCOM0) USART LON Backlog Register */
  #define REG_FLEXCOM0_US_LONB1TX  (*(__IO uint32_t*)0xF801C274U) /**< \brief (FLEXCOM0) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM0_US_LONB1RX  (*(__IO uint32_t*)0xF801C278U) /**< \brief (FLEXCOM0) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM0_US_LONPRIO  (*(__IO uint32_t*)0xF801C27CU) /**< \brief (FLEXCOM0) USART LON Priority Register */
  #define REG_FLEXCOM0_US_IDTTX    (*(__IO uint32_t*)0xF801C280U) /**< \brief (FLEXCOM0) USART LON IDT Tx Register */
  #define REG_FLEXCOM0_US_IDTRX    (*(__IO uint32_t*)0xF801C284U) /**< \brief (FLEXCOM0) USART LON IDT Rx Register */
  #define REG_FLEXCOM0_US_ICDIFF   (*(__IO uint32_t*)0xF801C288U) /**< \brief (FLEXCOM0) USART IC DIFF Register */
  #define REG_FLEXCOM0_US_CMPR     (*(__IO uint32_t*)0xF801C290U) /**< \brief (FLEXCOM0) USART Comparison Register */
  #define REG_FLEXCOM0_US_FMR      (*(__IO uint32_t*)0xF801C2A0U) /**< \brief (FLEXCOM0) USART FIFO Mode Register */
  #define REG_FLEXCOM0_US_FLR      (*(__I  uint32_t*)0xF801C2A4U) /**< \brief (FLEXCOM0) USART FIFO Level Register */
  #define REG_FLEXCOM0_US_FIER     (*(__O  uint32_t*)0xF801C2A8U) /**< \brief (FLEXCOM0) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM0_US_FIDR     (*(__O  uint32_t*)0xF801C2ACU) /**< \brief (FLEXCOM0) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM0_US_FIMR     (*(__I  uint32_t*)0xF801C2B0U) /**< \brief (FLEXCOM0) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM0_US_FESR     (*(__I  uint32_t*)0xF801C2B4U) /**< \brief (FLEXCOM0) USART FIFO Event Status Register */
  #define REG_FLEXCOM0_US_WPMR     (*(__IO uint32_t*)0xF801C2E4U) /**< \brief (FLEXCOM0) USART Write Protection Mode Register */
  #define REG_FLEXCOM0_US_WPSR     (*(__I  uint32_t*)0xF801C2E8U) /**< \brief (FLEXCOM0) USART Write Protection Status Register */
  #define REG_FLEXCOM0_SPI_CR      (*(__O  uint32_t*)0xF801C400U) /**< \brief (FLEXCOM0) SPI Control Register */
  #define REG_FLEXCOM0_SPI_MR      (*(__IO uint32_t*)0xF801C404U) /**< \brief (FLEXCOM0) SPI Mode Register */
  #define REG_FLEXCOM0_SPI_RDR     (*(__I  uint32_t*)0xF801C408U) /**< \brief (FLEXCOM0) SPI Receive Data Register */
  #define REG_FLEXCOM0_SPI_TDR     (*(__O  uint32_t*)0xF801C40CU) /**< \brief (FLEXCOM0) SPI Transmit Data Register */
  #define REG_FLEXCOM0_SPI_SR      (*(__I  uint32_t*)0xF801C410U) /**< \brief (FLEXCOM0) SPI Status Register */
  #define REG_FLEXCOM0_SPI_IER     (*(__O  uint32_t*)0xF801C414U) /**< \brief (FLEXCOM0) SPI Interrupt Enable Register */
  #define REG_FLEXCOM0_SPI_IDR     (*(__O  uint32_t*)0xF801C418U) /**< \brief (FLEXCOM0) SPI Interrupt Disable Register */
  #define REG_FLEXCOM0_SPI_IMR     (*(__I  uint32_t*)0xF801C41CU) /**< \brief (FLEXCOM0) SPI Interrupt Mask Register */
  #define REG_FLEXCOM0_SPI_CSR     (*(__IO uint32_t*)0xF801C430U) /**< \brief (FLEXCOM0) SPI Chip Select Register */
  #define REG_FLEXCOM0_SPI_FMR     (*(__IO uint32_t*)0xF801C440U) /**< \brief (FLEXCOM0) SPI FIFO Mode Register */
  #define REG_FLEXCOM0_SPI_FLR     (*(__I  uint32_t*)0xF801C444U) /**< \brief (FLEXCOM0) SPI FIFO Level Register */
  #define REG_FLEXCOM0_SPI_CMPR    (*(__IO uint32_t*)0xF801C448U) /**< \brief (FLEXCOM0) SPI Comparison Register */
  #define REG_FLEXCOM0_SPI_WPMR    (*(__IO uint32_t*)0xF801C4E4U) /**< \brief (FLEXCOM0) SPI Write Protection Mode Register */
  #define REG_FLEXCOM0_SPI_WPSR    (*(__I  uint32_t*)0xF801C4E8U) /**< \brief (FLEXCOM0) SPI Write Protection Status Register */
  #define REG_FLEXCOM0_TWI_CR      (*(__O  uint32_t*)0xF801C600U) /**< \brief (FLEXCOM0) TWI Control Register */
  #define REG_FLEXCOM0_TWI_MMR     (*(__IO uint32_t*)0xF801C604U) /**< \brief (FLEXCOM0) TWI Master Mode Register */
  #define REG_FLEXCOM0_TWI_SMR     (*(__IO uint32_t*)0xF801C608U) /**< \brief (FLEXCOM0) TWI Slave Mode Register */
  #define REG_FLEXCOM0_TWI_IADR    (*(__IO uint32_t*)0xF801C60CU) /**< \brief (FLEXCOM0) TWI Internal Address Register */
  #define REG_FLEXCOM0_TWI_CWGR    (*(__IO uint32_t*)0xF801C610U) /**< \brief (FLEXCOM0) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM0_TWI_SR      (*(__I  uint32_t*)0xF801C620U) /**< \brief (FLEXCOM0) TWI Status Register */
  #define REG_FLEXCOM0_TWI_IER     (*(__O  uint32_t*)0xF801C624U) /**< \brief (FLEXCOM0) TWI Interrupt Enable Register */
  #define REG_FLEXCOM0_TWI_IDR     (*(__O  uint32_t*)0xF801C628U) /**< \brief (FLEXCOM0) TWI Interrupt Disable Register */
  #define REG_FLEXCOM0_TWI_IMR     (*(__I  uint32_t*)0xF801C62CU) /**< \brief (FLEXCOM0) TWI Interrupt Mask Register */
  #define REG_FLEXCOM0_TWI_RHR     (*(__I  uint32_t*)0xF801C630U) /**< \brief (FLEXCOM0) TWI Receive Holding Register */
  #define REG_FLEXCOM0_TWI_THR     (*(__O  uint32_t*)0xF801C634U) /**< \brief (FLEXCOM0) TWI Transmit Holding Register */
  #define REG_FLEXCOM0_TWI_SMBTR   (*(__IO uint32_t*)0xF801C638U) /**< \brief (FLEXCOM0) TWI SMBus Timing Register */
  #define REG_FLEXCOM0_TWI_ACR     (*(__IO uint32_t*)0xF801C640U) /**< \brief (FLEXCOM0) TWI Alternative Command Register */
  #define REG_FLEXCOM0_TWI_FILTR   (*(__IO uint32_t*)0xF801C644U) /**< \brief (FLEXCOM0) TWI Filter Register */
  #define REG_FLEXCOM0_TWI_FMR     (*(__IO uint32_t*)0xF801C650U) /**< \brief (FLEXCOM0) TWI FIFO Mode Register */
  #define REG_FLEXCOM0_TWI_FLR     (*(__I  uint32_t*)0xF801C654U) /**< \brief (FLEXCOM0) TWI FIFO Level Register */
  #define REG_FLEXCOM0_TWI_FSR     (*(__I  uint32_t*)0xF801C660U) /**< \brief (FLEXCOM0) TWI FIFO Status Register */
  #define REG_FLEXCOM0_TWI_FIER    (*(__O  uint32_t*)0xF801C664U) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM0_TWI_FIDR    (*(__O  uint32_t*)0xF801C668U) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM0_TWI_FIMR    (*(__I  uint32_t*)0xF801C66CU) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM0_TWI_WPMR    (*(__IO uint32_t*)0xF801C6E4U) /**< \brief (FLEXCOM0) TWI Write Protection Mode Register */
  #define REG_FLEXCOM0_TWI_WPSR    (*(__I  uint32_t*)0xF801C6E8U) /**< \brief (FLEXCOM0) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM0_INSTANCE_ */
