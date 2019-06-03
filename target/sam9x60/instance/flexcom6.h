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

#ifndef _SAM9X_FLEXCOM6_INSTANCE_
#define _SAM9X_FLEXCOM6_INSTANCE_

/* ========== Register definition for FLEXCOM6 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM6_MR                           (0xF8010000U) /**< \brief (FLEXCOM6) FLEXCOM Mode Register */
  #define REG_FLEXCOM6_RHR                          (0xF8010010U) /**< \brief (FLEXCOM6) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM6_THR                          (0xF8010020U) /**< \brief (FLEXCOM6) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM6_US_CR                        (0xF8010200U) /**< \brief (FLEXCOM6) USART Control Register */
  #define REG_FLEXCOM6_US_MR                        (0xF8010204U) /**< \brief (FLEXCOM6) USART Mode Register */
  #define REG_FLEXCOM6_US_IER                       (0xF8010208U) /**< \brief (FLEXCOM6) USART Interrupt Enable Register */
  #define REG_FLEXCOM6_US_IDR                       (0xF801020CU) /**< \brief (FLEXCOM6) USART Interrupt Disable Register */
  #define REG_FLEXCOM6_US_IMR                       (0xF8010210U) /**< \brief (FLEXCOM6) USART Interrupt Mask Register */
  #define REG_FLEXCOM6_US_CSR                       (0xF8010214U) /**< \brief (FLEXCOM6) USART Channel Status Register */
  #define REG_FLEXCOM6_US_RHR                       (0xF8010218U) /**< \brief (FLEXCOM6) USART Receive Holding Register */
  #define REG_FLEXCOM6_US_THR                       (0xF801021CU) /**< \brief (FLEXCOM6) USART Transmit Holding Register */
  #define REG_FLEXCOM6_US_BRGR                      (0xF8010220U) /**< \brief (FLEXCOM6) USART Baud Rate Generator Register */
  #define REG_FLEXCOM6_US_RTOR                      (0xF8010224U) /**< \brief (FLEXCOM6) USART Receiver Timeout Register */
  #define REG_FLEXCOM6_US_TTGR                      (0xF8010228U) /**< \brief (FLEXCOM6) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM6_US_FIDI                      (0xF8010240U) /**< \brief (FLEXCOM6) USART FI DI Ratio Register */
  #define REG_FLEXCOM6_US_NER                       (0xF8010244U) /**< \brief (FLEXCOM6) USART Number of Errors Register */
  #define REG_FLEXCOM6_US_IF                        (0xF801024CU) /**< \brief (FLEXCOM6) USART IrDA Filter Register */
  #define REG_FLEXCOM6_US_MAN                       (0xF8010250U) /**< \brief (FLEXCOM6) USART Manchester Configuration Register */
  #define REG_FLEXCOM6_US_LINMR                     (0xF8010254U) /**< \brief (FLEXCOM6) USART LIN Mode Register */
  #define REG_FLEXCOM6_US_LINIR                     (0xF8010258U) /**< \brief (FLEXCOM6) USART LIN Identifier Register */
  #define REG_FLEXCOM6_US_LINBRR                    (0xF801025CU) /**< \brief (FLEXCOM6) USART LIN Baud Rate Register */
  #define REG_FLEXCOM6_US_LONMR                     (0xF8010260U) /**< \brief (FLEXCOM6) USART LON Mode Register */
  #define REG_FLEXCOM6_US_LONPR                     (0xF8010264U) /**< \brief (FLEXCOM6) USART LON Preamble Register */
  #define REG_FLEXCOM6_US_LONDL                     (0xF8010268U) /**< \brief (FLEXCOM6) USART LON Data Length Register */
  #define REG_FLEXCOM6_US_LONL2HDR                  (0xF801026CU) /**< \brief (FLEXCOM6) USART LON L2HDR Register */
  #define REG_FLEXCOM6_US_LONBL                     (0xF8010270U) /**< \brief (FLEXCOM6) USART LON Backlog Register */
  #define REG_FLEXCOM6_US_LONB1TX                   (0xF8010274U) /**< \brief (FLEXCOM6) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM6_US_LONB1RX                   (0xF8010278U) /**< \brief (FLEXCOM6) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM6_US_LONPRIO                   (0xF801027CU) /**< \brief (FLEXCOM6) USART LON Priority Register */
  #define REG_FLEXCOM6_US_IDTTX                     (0xF8010280U) /**< \brief (FLEXCOM6) USART LON IDT Tx Register */
  #define REG_FLEXCOM6_US_IDTRX                     (0xF8010284U) /**< \brief (FLEXCOM6) USART LON IDT Rx Register */
  #define REG_FLEXCOM6_US_ICDIFF                    (0xF8010288U) /**< \brief (FLEXCOM6) USART IC DIFF Register */
  #define REG_FLEXCOM6_US_CMPR                      (0xF8010290U) /**< \brief (FLEXCOM6) USART Comparison Register */
  #define REG_FLEXCOM6_US_FMR                       (0xF80102A0U) /**< \brief (FLEXCOM6) USART FIFO Mode Register */
  #define REG_FLEXCOM6_US_FLR                       (0xF80102A4U) /**< \brief (FLEXCOM6) USART FIFO Level Register */
  #define REG_FLEXCOM6_US_FIER                      (0xF80102A8U) /**< \brief (FLEXCOM6) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM6_US_FIDR                      (0xF80102ACU) /**< \brief (FLEXCOM6) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM6_US_FIMR                      (0xF80102B0U) /**< \brief (FLEXCOM6) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM6_US_FESR                      (0xF80102B4U) /**< \brief (FLEXCOM6) USART FIFO Event Status Register */
  #define REG_FLEXCOM6_US_WPMR                      (0xF80102E4U) /**< \brief (FLEXCOM6) USART Write Protection Mode Register */
  #define REG_FLEXCOM6_US_WPSR                      (0xF80102E8U) /**< \brief (FLEXCOM6) USART Write Protection Status Register */
  #define REG_FLEXCOM6_SPI_CR                       (0xF8010400U) /**< \brief (FLEXCOM6) SPI Control Register */
  #define REG_FLEXCOM6_SPI_MR                       (0xF8010404U) /**< \brief (FLEXCOM6) SPI Mode Register */
  #define REG_FLEXCOM6_SPI_RDR                      (0xF8010408U) /**< \brief (FLEXCOM6) SPI Receive Data Register */
  #define REG_FLEXCOM6_SPI_TDR                      (0xF801040CU) /**< \brief (FLEXCOM6) SPI Transmit Data Register */
  #define REG_FLEXCOM6_SPI_SR                       (0xF8010410U) /**< \brief (FLEXCOM6) SPI Status Register */
  #define REG_FLEXCOM6_SPI_IER                      (0xF8010414U) /**< \brief (FLEXCOM6) SPI Interrupt Enable Register */
  #define REG_FLEXCOM6_SPI_IDR                      (0xF8010418U) /**< \brief (FLEXCOM6) SPI Interrupt Disable Register */
  #define REG_FLEXCOM6_SPI_IMR                      (0xF801041CU) /**< \brief (FLEXCOM6) SPI Interrupt Mask Register */
  #define REG_FLEXCOM6_SPI_CSR                      (0xF8010430U) /**< \brief (FLEXCOM6) SPI Chip Select Register */
  #define REG_FLEXCOM6_SPI_FMR                      (0xF8010440U) /**< \brief (FLEXCOM6) SPI FIFO Mode Register */
  #define REG_FLEXCOM6_SPI_FLR                      (0xF8010444U) /**< \brief (FLEXCOM6) SPI FIFO Level Register */
  #define REG_FLEXCOM6_SPI_CMPR                     (0xF8010448U) /**< \brief (FLEXCOM6) SPI Comparison Register */
  #define REG_FLEXCOM6_SPI_WPMR                     (0xF80104E4U) /**< \brief (FLEXCOM6) SPI Write Protection Mode Register */
  #define REG_FLEXCOM6_SPI_WPSR                     (0xF80104E8U) /**< \brief (FLEXCOM6) SPI Write Protection Status Register */
  #define REG_FLEXCOM6_TWI_CR                       (0xF8010600U) /**< \brief (FLEXCOM6) TWI Control Register */
  #define REG_FLEXCOM6_TWI_MMR                      (0xF8010604U) /**< \brief (FLEXCOM6) TWI Master Mode Register */
  #define REG_FLEXCOM6_TWI_SMR                      (0xF8010608U) /**< \brief (FLEXCOM6) TWI Slave Mode Register */
  #define REG_FLEXCOM6_TWI_IADR                     (0xF801060CU) /**< \brief (FLEXCOM6) TWI Internal Address Register */
  #define REG_FLEXCOM6_TWI_CWGR                     (0xF8010610U) /**< \brief (FLEXCOM6) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM6_TWI_SR                       (0xF8010620U) /**< \brief (FLEXCOM6) TWI Status Register */
  #define REG_FLEXCOM6_TWI_IER                      (0xF8010624U) /**< \brief (FLEXCOM6) TWI Interrupt Enable Register */
  #define REG_FLEXCOM6_TWI_IDR                      (0xF8010628U) /**< \brief (FLEXCOM6) TWI Interrupt Disable Register */
  #define REG_FLEXCOM6_TWI_IMR                      (0xF801062CU) /**< \brief (FLEXCOM6) TWI Interrupt Mask Register */
  #define REG_FLEXCOM6_TWI_RHR                      (0xF8010630U) /**< \brief (FLEXCOM6) TWI Receive Holding Register */
  #define REG_FLEXCOM6_TWI_THR                      (0xF8010634U) /**< \brief (FLEXCOM6) TWI Transmit Holding Register */
  #define REG_FLEXCOM6_TWI_SMBTR                    (0xF8010638U) /**< \brief (FLEXCOM6) TWI SMBus Timing Register */
  #define REG_FLEXCOM6_TWI_ACR                      (0xF8010640U) /**< \brief (FLEXCOM6) TWI Alternative Command Register */
  #define REG_FLEXCOM6_TWI_FILTR                    (0xF8010644U) /**< \brief (FLEXCOM6) TWI Filter Register */
  #define REG_FLEXCOM6_TWI_FMR                      (0xF8010650U) /**< \brief (FLEXCOM6) TWI FIFO Mode Register */
  #define REG_FLEXCOM6_TWI_FLR                      (0xF8010654U) /**< \brief (FLEXCOM6) TWI FIFO Level Register */
  #define REG_FLEXCOM6_TWI_FSR                      (0xF8010660U) /**< \brief (FLEXCOM6) TWI FIFO Status Register */
  #define REG_FLEXCOM6_TWI_FIER                     (0xF8010664U) /**< \brief (FLEXCOM6) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM6_TWI_FIDR                     (0xF8010668U) /**< \brief (FLEXCOM6) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM6_TWI_FIMR                     (0xF801066CU) /**< \brief (FLEXCOM6) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM6_TWI_WPMR                     (0xF80106E4U) /**< \brief (FLEXCOM6) TWI Write Protection Mode Register */
  #define REG_FLEXCOM6_TWI_WPSR                     (0xF80106E8U) /**< \brief (FLEXCOM6) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM6_MR          (*(__IO uint32_t*)0xF8010000U) /**< \brief (FLEXCOM6) FLEXCOM Mode Register */
  #define REG_FLEXCOM6_RHR         (*(__I  uint32_t*)0xF8010010U) /**< \brief (FLEXCOM6) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM6_THR         (*(__IO uint32_t*)0xF8010020U) /**< \brief (FLEXCOM6) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM6_US_CR       (*(__O  uint32_t*)0xF8010200U) /**< \brief (FLEXCOM6) USART Control Register */
  #define REG_FLEXCOM6_US_MR       (*(__IO uint32_t*)0xF8010204U) /**< \brief (FLEXCOM6) USART Mode Register */
  #define REG_FLEXCOM6_US_IER      (*(__O  uint32_t*)0xF8010208U) /**< \brief (FLEXCOM6) USART Interrupt Enable Register */
  #define REG_FLEXCOM6_US_IDR      (*(__O  uint32_t*)0xF801020CU) /**< \brief (FLEXCOM6) USART Interrupt Disable Register */
  #define REG_FLEXCOM6_US_IMR      (*(__I  uint32_t*)0xF8010210U) /**< \brief (FLEXCOM6) USART Interrupt Mask Register */
  #define REG_FLEXCOM6_US_CSR      (*(__I  uint32_t*)0xF8010214U) /**< \brief (FLEXCOM6) USART Channel Status Register */
  #define REG_FLEXCOM6_US_RHR      (*(__I  uint32_t*)0xF8010218U) /**< \brief (FLEXCOM6) USART Receive Holding Register */
  #define REG_FLEXCOM6_US_THR      (*(__O  uint32_t*)0xF801021CU) /**< \brief (FLEXCOM6) USART Transmit Holding Register */
  #define REG_FLEXCOM6_US_BRGR     (*(__IO uint32_t*)0xF8010220U) /**< \brief (FLEXCOM6) USART Baud Rate Generator Register */
  #define REG_FLEXCOM6_US_RTOR     (*(__IO uint32_t*)0xF8010224U) /**< \brief (FLEXCOM6) USART Receiver Timeout Register */
  #define REG_FLEXCOM6_US_TTGR     (*(__IO uint32_t*)0xF8010228U) /**< \brief (FLEXCOM6) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM6_US_FIDI     (*(__IO uint32_t*)0xF8010240U) /**< \brief (FLEXCOM6) USART FI DI Ratio Register */
  #define REG_FLEXCOM6_US_NER      (*(__I  uint32_t*)0xF8010244U) /**< \brief (FLEXCOM6) USART Number of Errors Register */
  #define REG_FLEXCOM6_US_IF       (*(__IO uint32_t*)0xF801024CU) /**< \brief (FLEXCOM6) USART IrDA Filter Register */
  #define REG_FLEXCOM6_US_MAN      (*(__IO uint32_t*)0xF8010250U) /**< \brief (FLEXCOM6) USART Manchester Configuration Register */
  #define REG_FLEXCOM6_US_LINMR    (*(__IO uint32_t*)0xF8010254U) /**< \brief (FLEXCOM6) USART LIN Mode Register */
  #define REG_FLEXCOM6_US_LINIR    (*(__IO uint32_t*)0xF8010258U) /**< \brief (FLEXCOM6) USART LIN Identifier Register */
  #define REG_FLEXCOM6_US_LINBRR   (*(__I  uint32_t*)0xF801025CU) /**< \brief (FLEXCOM6) USART LIN Baud Rate Register */
  #define REG_FLEXCOM6_US_LONMR    (*(__IO uint32_t*)0xF8010260U) /**< \brief (FLEXCOM6) USART LON Mode Register */
  #define REG_FLEXCOM6_US_LONPR    (*(__IO uint32_t*)0xF8010264U) /**< \brief (FLEXCOM6) USART LON Preamble Register */
  #define REG_FLEXCOM6_US_LONDL    (*(__IO uint32_t*)0xF8010268U) /**< \brief (FLEXCOM6) USART LON Data Length Register */
  #define REG_FLEXCOM6_US_LONL2HDR (*(__IO uint32_t*)0xF801026CU) /**< \brief (FLEXCOM6) USART LON L2HDR Register */
  #define REG_FLEXCOM6_US_LONBL    (*(__I  uint32_t*)0xF8010270U) /**< \brief (FLEXCOM6) USART LON Backlog Register */
  #define REG_FLEXCOM6_US_LONB1TX  (*(__IO uint32_t*)0xF8010274U) /**< \brief (FLEXCOM6) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM6_US_LONB1RX  (*(__IO uint32_t*)0xF8010278U) /**< \brief (FLEXCOM6) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM6_US_LONPRIO  (*(__IO uint32_t*)0xF801027CU) /**< \brief (FLEXCOM6) USART LON Priority Register */
  #define REG_FLEXCOM6_US_IDTTX    (*(__IO uint32_t*)0xF8010280U) /**< \brief (FLEXCOM6) USART LON IDT Tx Register */
  #define REG_FLEXCOM6_US_IDTRX    (*(__IO uint32_t*)0xF8010284U) /**< \brief (FLEXCOM6) USART LON IDT Rx Register */
  #define REG_FLEXCOM6_US_ICDIFF   (*(__IO uint32_t*)0xF8010288U) /**< \brief (FLEXCOM6) USART IC DIFF Register */
  #define REG_FLEXCOM6_US_CMPR     (*(__IO uint32_t*)0xF8010290U) /**< \brief (FLEXCOM6) USART Comparison Register */
  #define REG_FLEXCOM6_US_FMR      (*(__IO uint32_t*)0xF80102A0U) /**< \brief (FLEXCOM6) USART FIFO Mode Register */
  #define REG_FLEXCOM6_US_FLR      (*(__I  uint32_t*)0xF80102A4U) /**< \brief (FLEXCOM6) USART FIFO Level Register */
  #define REG_FLEXCOM6_US_FIER     (*(__O  uint32_t*)0xF80102A8U) /**< \brief (FLEXCOM6) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM6_US_FIDR     (*(__O  uint32_t*)0xF80102ACU) /**< \brief (FLEXCOM6) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM6_US_FIMR     (*(__I  uint32_t*)0xF80102B0U) /**< \brief (FLEXCOM6) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM6_US_FESR     (*(__I  uint32_t*)0xF80102B4U) /**< \brief (FLEXCOM6) USART FIFO Event Status Register */
  #define REG_FLEXCOM6_US_WPMR     (*(__IO uint32_t*)0xF80102E4U) /**< \brief (FLEXCOM6) USART Write Protection Mode Register */
  #define REG_FLEXCOM6_US_WPSR     (*(__I  uint32_t*)0xF80102E8U) /**< \brief (FLEXCOM6) USART Write Protection Status Register */
  #define REG_FLEXCOM6_SPI_CR      (*(__O  uint32_t*)0xF8010400U) /**< \brief (FLEXCOM6) SPI Control Register */
  #define REG_FLEXCOM6_SPI_MR      (*(__IO uint32_t*)0xF8010404U) /**< \brief (FLEXCOM6) SPI Mode Register */
  #define REG_FLEXCOM6_SPI_RDR     (*(__I  uint32_t*)0xF8010408U) /**< \brief (FLEXCOM6) SPI Receive Data Register */
  #define REG_FLEXCOM6_SPI_TDR     (*(__O  uint32_t*)0xF801040CU) /**< \brief (FLEXCOM6) SPI Transmit Data Register */
  #define REG_FLEXCOM6_SPI_SR      (*(__I  uint32_t*)0xF8010410U) /**< \brief (FLEXCOM6) SPI Status Register */
  #define REG_FLEXCOM6_SPI_IER     (*(__O  uint32_t*)0xF8010414U) /**< \brief (FLEXCOM6) SPI Interrupt Enable Register */
  #define REG_FLEXCOM6_SPI_IDR     (*(__O  uint32_t*)0xF8010418U) /**< \brief (FLEXCOM6) SPI Interrupt Disable Register */
  #define REG_FLEXCOM6_SPI_IMR     (*(__I  uint32_t*)0xF801041CU) /**< \brief (FLEXCOM6) SPI Interrupt Mask Register */
  #define REG_FLEXCOM6_SPI_CSR     (*(__IO uint32_t*)0xF8010430U) /**< \brief (FLEXCOM6) SPI Chip Select Register */
  #define REG_FLEXCOM6_SPI_FMR     (*(__IO uint32_t*)0xF8010440U) /**< \brief (FLEXCOM6) SPI FIFO Mode Register */
  #define REG_FLEXCOM6_SPI_FLR     (*(__I  uint32_t*)0xF8010444U) /**< \brief (FLEXCOM6) SPI FIFO Level Register */
  #define REG_FLEXCOM6_SPI_CMPR    (*(__IO uint32_t*)0xF8010448U) /**< \brief (FLEXCOM6) SPI Comparison Register */
  #define REG_FLEXCOM6_SPI_WPMR    (*(__IO uint32_t*)0xF80104E4U) /**< \brief (FLEXCOM6) SPI Write Protection Mode Register */
  #define REG_FLEXCOM6_SPI_WPSR    (*(__I  uint32_t*)0xF80104E8U) /**< \brief (FLEXCOM6) SPI Write Protection Status Register */
  #define REG_FLEXCOM6_TWI_CR      (*(__O  uint32_t*)0xF8010600U) /**< \brief (FLEXCOM6) TWI Control Register */
  #define REG_FLEXCOM6_TWI_MMR     (*(__IO uint32_t*)0xF8010604U) /**< \brief (FLEXCOM6) TWI Master Mode Register */
  #define REG_FLEXCOM6_TWI_SMR     (*(__IO uint32_t*)0xF8010608U) /**< \brief (FLEXCOM6) TWI Slave Mode Register */
  #define REG_FLEXCOM6_TWI_IADR    (*(__IO uint32_t*)0xF801060CU) /**< \brief (FLEXCOM6) TWI Internal Address Register */
  #define REG_FLEXCOM6_TWI_CWGR    (*(__IO uint32_t*)0xF8010610U) /**< \brief (FLEXCOM6) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM6_TWI_SR      (*(__I  uint32_t*)0xF8010620U) /**< \brief (FLEXCOM6) TWI Status Register */
  #define REG_FLEXCOM6_TWI_IER     (*(__O  uint32_t*)0xF8010624U) /**< \brief (FLEXCOM6) TWI Interrupt Enable Register */
  #define REG_FLEXCOM6_TWI_IDR     (*(__O  uint32_t*)0xF8010628U) /**< \brief (FLEXCOM6) TWI Interrupt Disable Register */
  #define REG_FLEXCOM6_TWI_IMR     (*(__I  uint32_t*)0xF801062CU) /**< \brief (FLEXCOM6) TWI Interrupt Mask Register */
  #define REG_FLEXCOM6_TWI_RHR     (*(__I  uint32_t*)0xF8010630U) /**< \brief (FLEXCOM6) TWI Receive Holding Register */
  #define REG_FLEXCOM6_TWI_THR     (*(__O  uint32_t*)0xF8010634U) /**< \brief (FLEXCOM6) TWI Transmit Holding Register */
  #define REG_FLEXCOM6_TWI_SMBTR   (*(__IO uint32_t*)0xF8010638U) /**< \brief (FLEXCOM6) TWI SMBus Timing Register */
  #define REG_FLEXCOM6_TWI_ACR     (*(__IO uint32_t*)0xF8010640U) /**< \brief (FLEXCOM6) TWI Alternative Command Register */
  #define REG_FLEXCOM6_TWI_FILTR   (*(__IO uint32_t*)0xF8010644U) /**< \brief (FLEXCOM6) TWI Filter Register */
  #define REG_FLEXCOM6_TWI_FMR     (*(__IO uint32_t*)0xF8010650U) /**< \brief (FLEXCOM6) TWI FIFO Mode Register */
  #define REG_FLEXCOM6_TWI_FLR     (*(__I  uint32_t*)0xF8010654U) /**< \brief (FLEXCOM6) TWI FIFO Level Register */
  #define REG_FLEXCOM6_TWI_FSR     (*(__I  uint32_t*)0xF8010660U) /**< \brief (FLEXCOM6) TWI FIFO Status Register */
  #define REG_FLEXCOM6_TWI_FIER    (*(__O  uint32_t*)0xF8010664U) /**< \brief (FLEXCOM6) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM6_TWI_FIDR    (*(__O  uint32_t*)0xF8010668U) /**< \brief (FLEXCOM6) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM6_TWI_FIMR    (*(__I  uint32_t*)0xF801066CU) /**< \brief (FLEXCOM6) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM6_TWI_WPMR    (*(__IO uint32_t*)0xF80106E4U) /**< \brief (FLEXCOM6) TWI Write Protection Mode Register */
  #define REG_FLEXCOM6_TWI_WPSR    (*(__I  uint32_t*)0xF80106E8U) /**< \brief (FLEXCOM6) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM6_INSTANCE_ */
