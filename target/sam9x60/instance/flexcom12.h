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

#ifndef _SAM9X_FLEXCOM12_INSTANCE_
#define _SAM9X_FLEXCOM12_INSTANCE_

/* ========== Register definition for FLEXCOM12 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM12_MR                           (0xF0024000U) /**< \brief (FLEXCOM12) FLEXCOM Mode Register */
  #define REG_FLEXCOM12_RHR                          (0xF0024010U) /**< \brief (FLEXCOM12) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM12_THR                          (0xF0024020U) /**< \brief (FLEXCOM12) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM12_US_CR                        (0xF0024200U) /**< \brief (FLEXCOM12) USART Control Register */
  #define REG_FLEXCOM12_US_MR                        (0xF0024204U) /**< \brief (FLEXCOM12) USART Mode Register */
  #define REG_FLEXCOM12_US_IER                       (0xF0024208U) /**< \brief (FLEXCOM12) USART Interrupt Enable Register */
  #define REG_FLEXCOM12_US_IDR                       (0xF002420CU) /**< \brief (FLEXCOM12) USART Interrupt Disable Register */
  #define REG_FLEXCOM12_US_IMR                       (0xF0024210U) /**< \brief (FLEXCOM12) USART Interrupt Mask Register */
  #define REG_FLEXCOM12_US_CSR                       (0xF0024214U) /**< \brief (FLEXCOM12) USART Channel Status Register */
  #define REG_FLEXCOM12_US_RHR                       (0xF0024218U) /**< \brief (FLEXCOM12) USART Receive Holding Register */
  #define REG_FLEXCOM12_US_THR                       (0xF002421CU) /**< \brief (FLEXCOM12) USART Transmit Holding Register */
  #define REG_FLEXCOM12_US_BRGR                      (0xF0024220U) /**< \brief (FLEXCOM12) USART Baud Rate Generator Register */
  #define REG_FLEXCOM12_US_RTOR                      (0xF0024224U) /**< \brief (FLEXCOM12) USART Receiver Timeout Register */
  #define REG_FLEXCOM12_US_TTGR                      (0xF0024228U) /**< \brief (FLEXCOM12) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM12_US_FIDI                      (0xF0024240U) /**< \brief (FLEXCOM12) USART FI DI Ratio Register */
  #define REG_FLEXCOM12_US_NER                       (0xF0024244U) /**< \brief (FLEXCOM12) USART Number of Errors Register */
  #define REG_FLEXCOM12_US_IF                        (0xF002424CU) /**< \brief (FLEXCOM12) USART IrDA Filter Register */
  #define REG_FLEXCOM12_US_MAN                       (0xF0024250U) /**< \brief (FLEXCOM12) USART Manchester Configuration Register */
  #define REG_FLEXCOM12_US_LINMR                     (0xF0024254U) /**< \brief (FLEXCOM12) USART LIN Mode Register */
  #define REG_FLEXCOM12_US_LINIR                     (0xF0024258U) /**< \brief (FLEXCOM12) USART LIN Identifier Register */
  #define REG_FLEXCOM12_US_LINBRR                    (0xF002425CU) /**< \brief (FLEXCOM12) USART LIN Baud Rate Register */
  #define REG_FLEXCOM12_US_LONMR                     (0xF0024260U) /**< \brief (FLEXCOM12) USART LON Mode Register */
  #define REG_FLEXCOM12_US_LONPR                     (0xF0024264U) /**< \brief (FLEXCOM12) USART LON Preamble Register */
  #define REG_FLEXCOM12_US_LONDL                     (0xF0024268U) /**< \brief (FLEXCOM12) USART LON Data Length Register */
  #define REG_FLEXCOM12_US_LONL2HDR                  (0xF002426CU) /**< \brief (FLEXCOM12) USART LON L2HDR Register */
  #define REG_FLEXCOM12_US_LONBL                     (0xF0024270U) /**< \brief (FLEXCOM12) USART LON Backlog Register */
  #define REG_FLEXCOM12_US_LONB1TX                   (0xF0024274U) /**< \brief (FLEXCOM12) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM12_US_LONB1RX                   (0xF0024278U) /**< \brief (FLEXCOM12) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM12_US_LONPRIO                   (0xF002427CU) /**< \brief (FLEXCOM12) USART LON Priority Register */
  #define REG_FLEXCOM12_US_IDTTX                     (0xF0024280U) /**< \brief (FLEXCOM12) USART LON IDT Tx Register */
  #define REG_FLEXCOM12_US_IDTRX                     (0xF0024284U) /**< \brief (FLEXCOM12) USART LON IDT Rx Register */
  #define REG_FLEXCOM12_US_ICDIFF                    (0xF0024288U) /**< \brief (FLEXCOM12) USART IC DIFF Register */
  #define REG_FLEXCOM12_US_CMPR                      (0xF0024290U) /**< \brief (FLEXCOM12) USART Comparison Register */
  #define REG_FLEXCOM12_US_FMR                       (0xF00242A0U) /**< \brief (FLEXCOM12) USART FIFO Mode Register */
  #define REG_FLEXCOM12_US_FLR                       (0xF00242A4U) /**< \brief (FLEXCOM12) USART FIFO Level Register */
  #define REG_FLEXCOM12_US_FIER                      (0xF00242A8U) /**< \brief (FLEXCOM12) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM12_US_FIDR                      (0xF00242ACU) /**< \brief (FLEXCOM12) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM12_US_FIMR                      (0xF00242B0U) /**< \brief (FLEXCOM12) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM12_US_FESR                      (0xF00242B4U) /**< \brief (FLEXCOM12) USART FIFO Event Status Register */
  #define REG_FLEXCOM12_US_WPMR                      (0xF00242E4U) /**< \brief (FLEXCOM12) USART Write Protection Mode Register */
  #define REG_FLEXCOM12_US_WPSR                      (0xF00242E8U) /**< \brief (FLEXCOM12) USART Write Protection Status Register */
  #define REG_FLEXCOM12_SPI_CR                       (0xF0024400U) /**< \brief (FLEXCOM12) SPI Control Register */
  #define REG_FLEXCOM12_SPI_MR                       (0xF0024404U) /**< \brief (FLEXCOM12) SPI Mode Register */
  #define REG_FLEXCOM12_SPI_RDR                      (0xF0024408U) /**< \brief (FLEXCOM12) SPI Receive Data Register */
  #define REG_FLEXCOM12_SPI_TDR                      (0xF002440CU) /**< \brief (FLEXCOM12) SPI Transmit Data Register */
  #define REG_FLEXCOM12_SPI_SR                       (0xF0024410U) /**< \brief (FLEXCOM12) SPI Status Register */
  #define REG_FLEXCOM12_SPI_IER                      (0xF0024414U) /**< \brief (FLEXCOM12) SPI Interrupt Enable Register */
  #define REG_FLEXCOM12_SPI_IDR                      (0xF0024418U) /**< \brief (FLEXCOM12) SPI Interrupt Disable Register */
  #define REG_FLEXCOM12_SPI_IMR                      (0xF002441CU) /**< \brief (FLEXCOM12) SPI Interrupt Mask Register */
  #define REG_FLEXCOM12_SPI_CSR                      (0xF0024430U) /**< \brief (FLEXCOM12) SPI Chip Select Register */
  #define REG_FLEXCOM12_SPI_FMR                      (0xF0024440U) /**< \brief (FLEXCOM12) SPI FIFO Mode Register */
  #define REG_FLEXCOM12_SPI_FLR                      (0xF0024444U) /**< \brief (FLEXCOM12) SPI FIFO Level Register */
  #define REG_FLEXCOM12_SPI_CMPR                     (0xF0024448U) /**< \brief (FLEXCOM12) SPI Comparison Register */
  #define REG_FLEXCOM12_SPI_WPMR                     (0xF00244E4U) /**< \brief (FLEXCOM12) SPI Write Protection Mode Register */
  #define REG_FLEXCOM12_SPI_WPSR                     (0xF00244E8U) /**< \brief (FLEXCOM12) SPI Write Protection Status Register */
  #define REG_FLEXCOM12_TWI_CR                       (0xF0024600U) /**< \brief (FLEXCOM12) TWI Control Register */
  #define REG_FLEXCOM12_TWI_MMR                      (0xF0024604U) /**< \brief (FLEXCOM12) TWI Master Mode Register */
  #define REG_FLEXCOM12_TWI_SMR                      (0xF0024608U) /**< \brief (FLEXCOM12) TWI Slave Mode Register */
  #define REG_FLEXCOM12_TWI_IADR                     (0xF002460CU) /**< \brief (FLEXCOM12) TWI Internal Address Register */
  #define REG_FLEXCOM12_TWI_CWGR                     (0xF0024610U) /**< \brief (FLEXCOM12) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM12_TWI_SR                       (0xF0024620U) /**< \brief (FLEXCOM12) TWI Status Register */
  #define REG_FLEXCOM12_TWI_IER                      (0xF0024624U) /**< \brief (FLEXCOM12) TWI Interrupt Enable Register */
  #define REG_FLEXCOM12_TWI_IDR                      (0xF0024628U) /**< \brief (FLEXCOM12) TWI Interrupt Disable Register */
  #define REG_FLEXCOM12_TWI_IMR                      (0xF002462CU) /**< \brief (FLEXCOM12) TWI Interrupt Mask Register */
  #define REG_FLEXCOM12_TWI_RHR                      (0xF0024630U) /**< \brief (FLEXCOM12) TWI Receive Holding Register */
  #define REG_FLEXCOM12_TWI_THR                      (0xF0024634U) /**< \brief (FLEXCOM12) TWI Transmit Holding Register */
  #define REG_FLEXCOM12_TWI_SMBTR                    (0xF0024638U) /**< \brief (FLEXCOM12) TWI SMBus Timing Register */
  #define REG_FLEXCOM12_TWI_ACR                      (0xF0024640U) /**< \brief (FLEXCOM12) TWI Alternative Command Register */
  #define REG_FLEXCOM12_TWI_FILTR                    (0xF0024644U) /**< \brief (FLEXCOM12) TWI Filter Register */
  #define REG_FLEXCOM12_TWI_FMR                      (0xF0024650U) /**< \brief (FLEXCOM12) TWI FIFO Mode Register */
  #define REG_FLEXCOM12_TWI_FLR                      (0xF0024654U) /**< \brief (FLEXCOM12) TWI FIFO Level Register */
  #define REG_FLEXCOM12_TWI_FSR                      (0xF0024660U) /**< \brief (FLEXCOM12) TWI FIFO Status Register */
  #define REG_FLEXCOM12_TWI_FIER                     (0xF0024664U) /**< \brief (FLEXCOM12) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM12_TWI_FIDR                     (0xF0024668U) /**< \brief (FLEXCOM12) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM12_TWI_FIMR                     (0xF002466CU) /**< \brief (FLEXCOM12) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM12_TWI_WPMR                     (0xF00246E4U) /**< \brief (FLEXCOM12) TWI Write Protection Mode Register */
  #define REG_FLEXCOM12_TWI_WPSR                     (0xF00246E8U) /**< \brief (FLEXCOM12) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM12_MR          (*(__IO uint32_t*)0xF0024000U) /**< \brief (FLEXCOM12) FLEXCOM Mode Register */
  #define REG_FLEXCOM12_RHR         (*(__I  uint32_t*)0xF0024010U) /**< \brief (FLEXCOM12) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM12_THR         (*(__IO uint32_t*)0xF0024020U) /**< \brief (FLEXCOM12) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM12_US_CR       (*(__O  uint32_t*)0xF0024200U) /**< \brief (FLEXCOM12) USART Control Register */
  #define REG_FLEXCOM12_US_MR       (*(__IO uint32_t*)0xF0024204U) /**< \brief (FLEXCOM12) USART Mode Register */
  #define REG_FLEXCOM12_US_IER      (*(__O  uint32_t*)0xF0024208U) /**< \brief (FLEXCOM12) USART Interrupt Enable Register */
  #define REG_FLEXCOM12_US_IDR      (*(__O  uint32_t*)0xF002420CU) /**< \brief (FLEXCOM12) USART Interrupt Disable Register */
  #define REG_FLEXCOM12_US_IMR      (*(__I  uint32_t*)0xF0024210U) /**< \brief (FLEXCOM12) USART Interrupt Mask Register */
  #define REG_FLEXCOM12_US_CSR      (*(__I  uint32_t*)0xF0024214U) /**< \brief (FLEXCOM12) USART Channel Status Register */
  #define REG_FLEXCOM12_US_RHR      (*(__I  uint32_t*)0xF0024218U) /**< \brief (FLEXCOM12) USART Receive Holding Register */
  #define REG_FLEXCOM12_US_THR      (*(__O  uint32_t*)0xF002421CU) /**< \brief (FLEXCOM12) USART Transmit Holding Register */
  #define REG_FLEXCOM12_US_BRGR     (*(__IO uint32_t*)0xF0024220U) /**< \brief (FLEXCOM12) USART Baud Rate Generator Register */
  #define REG_FLEXCOM12_US_RTOR     (*(__IO uint32_t*)0xF0024224U) /**< \brief (FLEXCOM12) USART Receiver Timeout Register */
  #define REG_FLEXCOM12_US_TTGR     (*(__IO uint32_t*)0xF0024228U) /**< \brief (FLEXCOM12) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM12_US_FIDI     (*(__IO uint32_t*)0xF0024240U) /**< \brief (FLEXCOM12) USART FI DI Ratio Register */
  #define REG_FLEXCOM12_US_NER      (*(__I  uint32_t*)0xF0024244U) /**< \brief (FLEXCOM12) USART Number of Errors Register */
  #define REG_FLEXCOM12_US_IF       (*(__IO uint32_t*)0xF002424CU) /**< \brief (FLEXCOM12) USART IrDA Filter Register */
  #define REG_FLEXCOM12_US_MAN      (*(__IO uint32_t*)0xF0024250U) /**< \brief (FLEXCOM12) USART Manchester Configuration Register */
  #define REG_FLEXCOM12_US_LINMR    (*(__IO uint32_t*)0xF0024254U) /**< \brief (FLEXCOM12) USART LIN Mode Register */
  #define REG_FLEXCOM12_US_LINIR    (*(__IO uint32_t*)0xF0024258U) /**< \brief (FLEXCOM12) USART LIN Identifier Register */
  #define REG_FLEXCOM12_US_LINBRR   (*(__I  uint32_t*)0xF002425CU) /**< \brief (FLEXCOM12) USART LIN Baud Rate Register */
  #define REG_FLEXCOM12_US_LONMR    (*(__IO uint32_t*)0xF0024260U) /**< \brief (FLEXCOM12) USART LON Mode Register */
  #define REG_FLEXCOM12_US_LONPR    (*(__IO uint32_t*)0xF0024264U) /**< \brief (FLEXCOM12) USART LON Preamble Register */
  #define REG_FLEXCOM12_US_LONDL    (*(__IO uint32_t*)0xF0024268U) /**< \brief (FLEXCOM12) USART LON Data Length Register */
  #define REG_FLEXCOM12_US_LONL2HDR (*(__IO uint32_t*)0xF002426CU) /**< \brief (FLEXCOM12) USART LON L2HDR Register */
  #define REG_FLEXCOM12_US_LONBL    (*(__I  uint32_t*)0xF0024270U) /**< \brief (FLEXCOM12) USART LON Backlog Register */
  #define REG_FLEXCOM12_US_LONB1TX  (*(__IO uint32_t*)0xF0024274U) /**< \brief (FLEXCOM12) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM12_US_LONB1RX  (*(__IO uint32_t*)0xF0024278U) /**< \brief (FLEXCOM12) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM12_US_LONPRIO  (*(__IO uint32_t*)0xF002427CU) /**< \brief (FLEXCOM12) USART LON Priority Register */
  #define REG_FLEXCOM12_US_IDTTX    (*(__IO uint32_t*)0xF0024280U) /**< \brief (FLEXCOM12) USART LON IDT Tx Register */
  #define REG_FLEXCOM12_US_IDTRX    (*(__IO uint32_t*)0xF0024284U) /**< \brief (FLEXCOM12) USART LON IDT Rx Register */
  #define REG_FLEXCOM12_US_ICDIFF   (*(__IO uint32_t*)0xF0024288U) /**< \brief (FLEXCOM12) USART IC DIFF Register */
  #define REG_FLEXCOM12_US_CMPR     (*(__IO uint32_t*)0xF0024290U) /**< \brief (FLEXCOM12) USART Comparison Register */
  #define REG_FLEXCOM12_US_FMR      (*(__IO uint32_t*)0xF00242A0U) /**< \brief (FLEXCOM12) USART FIFO Mode Register */
  #define REG_FLEXCOM12_US_FLR      (*(__I  uint32_t*)0xF00242A4U) /**< \brief (FLEXCOM12) USART FIFO Level Register */
  #define REG_FLEXCOM12_US_FIER     (*(__O  uint32_t*)0xF00242A8U) /**< \brief (FLEXCOM12) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM12_US_FIDR     (*(__O  uint32_t*)0xF00242ACU) /**< \brief (FLEXCOM12) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM12_US_FIMR     (*(__I  uint32_t*)0xF00242B0U) /**< \brief (FLEXCOM12) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM12_US_FESR     (*(__I  uint32_t*)0xF00242B4U) /**< \brief (FLEXCOM12) USART FIFO Event Status Register */
  #define REG_FLEXCOM12_US_WPMR     (*(__IO uint32_t*)0xF00242E4U) /**< \brief (FLEXCOM12) USART Write Protection Mode Register */
  #define REG_FLEXCOM12_US_WPSR     (*(__I  uint32_t*)0xF00242E8U) /**< \brief (FLEXCOM12) USART Write Protection Status Register */
  #define REG_FLEXCOM12_SPI_CR      (*(__O  uint32_t*)0xF0024400U) /**< \brief (FLEXCOM12) SPI Control Register */
  #define REG_FLEXCOM12_SPI_MR      (*(__IO uint32_t*)0xF0024404U) /**< \brief (FLEXCOM12) SPI Mode Register */
  #define REG_FLEXCOM12_SPI_RDR     (*(__I  uint32_t*)0xF0024408U) /**< \brief (FLEXCOM12) SPI Receive Data Register */
  #define REG_FLEXCOM12_SPI_TDR     (*(__O  uint32_t*)0xF002440CU) /**< \brief (FLEXCOM12) SPI Transmit Data Register */
  #define REG_FLEXCOM12_SPI_SR      (*(__I  uint32_t*)0xF0024410U) /**< \brief (FLEXCOM12) SPI Status Register */
  #define REG_FLEXCOM12_SPI_IER     (*(__O  uint32_t*)0xF0024414U) /**< \brief (FLEXCOM12) SPI Interrupt Enable Register */
  #define REG_FLEXCOM12_SPI_IDR     (*(__O  uint32_t*)0xF0024418U) /**< \brief (FLEXCOM12) SPI Interrupt Disable Register */
  #define REG_FLEXCOM12_SPI_IMR     (*(__I  uint32_t*)0xF002441CU) /**< \brief (FLEXCOM12) SPI Interrupt Mask Register */
  #define REG_FLEXCOM12_SPI_CSR     (*(__IO uint32_t*)0xF0024430U) /**< \brief (FLEXCOM12) SPI Chip Select Register */
  #define REG_FLEXCOM12_SPI_FMR     (*(__IO uint32_t*)0xF0024440U) /**< \brief (FLEXCOM12) SPI FIFO Mode Register */
  #define REG_FLEXCOM12_SPI_FLR     (*(__I  uint32_t*)0xF0024444U) /**< \brief (FLEXCOM12) SPI FIFO Level Register */
  #define REG_FLEXCOM12_SPI_CMPR    (*(__IO uint32_t*)0xF0024448U) /**< \brief (FLEXCOM12) SPI Comparison Register */
  #define REG_FLEXCOM12_SPI_WPMR    (*(__IO uint32_t*)0xF00244E4U) /**< \brief (FLEXCOM12) SPI Write Protection Mode Register */
  #define REG_FLEXCOM12_SPI_WPSR    (*(__I  uint32_t*)0xF00244E8U) /**< \brief (FLEXCOM12) SPI Write Protection Status Register */
  #define REG_FLEXCOM12_TWI_CR      (*(__O  uint32_t*)0xF0024600U) /**< \brief (FLEXCOM12) TWI Control Register */
  #define REG_FLEXCOM12_TWI_MMR     (*(__IO uint32_t*)0xF0024604U) /**< \brief (FLEXCOM12) TWI Master Mode Register */
  #define REG_FLEXCOM12_TWI_SMR     (*(__IO uint32_t*)0xF0024608U) /**< \brief (FLEXCOM12) TWI Slave Mode Register */
  #define REG_FLEXCOM12_TWI_IADR    (*(__IO uint32_t*)0xF002460CU) /**< \brief (FLEXCOM12) TWI Internal Address Register */
  #define REG_FLEXCOM12_TWI_CWGR    (*(__IO uint32_t*)0xF0024610U) /**< \brief (FLEXCOM12) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM12_TWI_SR      (*(__I  uint32_t*)0xF0024620U) /**< \brief (FLEXCOM12) TWI Status Register */
  #define REG_FLEXCOM12_TWI_IER     (*(__O  uint32_t*)0xF0024624U) /**< \brief (FLEXCOM12) TWI Interrupt Enable Register */
  #define REG_FLEXCOM12_TWI_IDR     (*(__O  uint32_t*)0xF0024628U) /**< \brief (FLEXCOM12) TWI Interrupt Disable Register */
  #define REG_FLEXCOM12_TWI_IMR     (*(__I  uint32_t*)0xF002462CU) /**< \brief (FLEXCOM12) TWI Interrupt Mask Register */
  #define REG_FLEXCOM12_TWI_RHR     (*(__I  uint32_t*)0xF0024630U) /**< \brief (FLEXCOM12) TWI Receive Holding Register */
  #define REG_FLEXCOM12_TWI_THR     (*(__O  uint32_t*)0xF0024634U) /**< \brief (FLEXCOM12) TWI Transmit Holding Register */
  #define REG_FLEXCOM12_TWI_SMBTR   (*(__IO uint32_t*)0xF0024638U) /**< \brief (FLEXCOM12) TWI SMBus Timing Register */
  #define REG_FLEXCOM12_TWI_ACR     (*(__IO uint32_t*)0xF0024640U) /**< \brief (FLEXCOM12) TWI Alternative Command Register */
  #define REG_FLEXCOM12_TWI_FILTR   (*(__IO uint32_t*)0xF0024644U) /**< \brief (FLEXCOM12) TWI Filter Register */
  #define REG_FLEXCOM12_TWI_FMR     (*(__IO uint32_t*)0xF0024650U) /**< \brief (FLEXCOM12) TWI FIFO Mode Register */
  #define REG_FLEXCOM12_TWI_FLR     (*(__I  uint32_t*)0xF0024654U) /**< \brief (FLEXCOM12) TWI FIFO Level Register */
  #define REG_FLEXCOM12_TWI_FSR     (*(__I  uint32_t*)0xF0024660U) /**< \brief (FLEXCOM12) TWI FIFO Status Register */
  #define REG_FLEXCOM12_TWI_FIER    (*(__O  uint32_t*)0xF0024664U) /**< \brief (FLEXCOM12) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM12_TWI_FIDR    (*(__O  uint32_t*)0xF0024668U) /**< \brief (FLEXCOM12) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM12_TWI_FIMR    (*(__I  uint32_t*)0xF002466CU) /**< \brief (FLEXCOM12) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM12_TWI_WPMR    (*(__IO uint32_t*)0xF00246E4U) /**< \brief (FLEXCOM12) TWI Write Protection Mode Register */
  #define REG_FLEXCOM12_TWI_WPSR    (*(__I  uint32_t*)0xF00246E8U) /**< \brief (FLEXCOM12) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM12_INSTANCE_ */
