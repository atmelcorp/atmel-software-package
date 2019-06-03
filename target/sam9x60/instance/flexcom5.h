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

#ifndef _SAM9X_FLEXCOM5_INSTANCE_
#define _SAM9X_FLEXCOM5_INSTANCE_

/* ========== Register definition for FLEXCOM5 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM5_MR                           (0xF0004000U) /**< \brief (FLEXCOM5) FLEXCOM Mode Register */
  #define REG_FLEXCOM5_RHR                          (0xF0004010U) /**< \brief (FLEXCOM5) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM5_THR                          (0xF0004020U) /**< \brief (FLEXCOM5) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM5_US_CR                        (0xF0004200U) /**< \brief (FLEXCOM5) USART Control Register */
  #define REG_FLEXCOM5_US_MR                        (0xF0004204U) /**< \brief (FLEXCOM5) USART Mode Register */
  #define REG_FLEXCOM5_US_IER                       (0xF0004208U) /**< \brief (FLEXCOM5) USART Interrupt Enable Register */
  #define REG_FLEXCOM5_US_IDR                       (0xF000420CU) /**< \brief (FLEXCOM5) USART Interrupt Disable Register */
  #define REG_FLEXCOM5_US_IMR                       (0xF0004210U) /**< \brief (FLEXCOM5) USART Interrupt Mask Register */
  #define REG_FLEXCOM5_US_CSR                       (0xF0004214U) /**< \brief (FLEXCOM5) USART Channel Status Register */
  #define REG_FLEXCOM5_US_RHR                       (0xF0004218U) /**< \brief (FLEXCOM5) USART Receive Holding Register */
  #define REG_FLEXCOM5_US_THR                       (0xF000421CU) /**< \brief (FLEXCOM5) USART Transmit Holding Register */
  #define REG_FLEXCOM5_US_BRGR                      (0xF0004220U) /**< \brief (FLEXCOM5) USART Baud Rate Generator Register */
  #define REG_FLEXCOM5_US_RTOR                      (0xF0004224U) /**< \brief (FLEXCOM5) USART Receiver Timeout Register */
  #define REG_FLEXCOM5_US_TTGR                      (0xF0004228U) /**< \brief (FLEXCOM5) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM5_US_FIDI                      (0xF0004240U) /**< \brief (FLEXCOM5) USART FI DI Ratio Register */
  #define REG_FLEXCOM5_US_NER                       (0xF0004244U) /**< \brief (FLEXCOM5) USART Number of Errors Register */
  #define REG_FLEXCOM5_US_IF                        (0xF000424CU) /**< \brief (FLEXCOM5) USART IrDA Filter Register */
  #define REG_FLEXCOM5_US_MAN                       (0xF0004250U) /**< \brief (FLEXCOM5) USART Manchester Configuration Register */
  #define REG_FLEXCOM5_US_LINMR                     (0xF0004254U) /**< \brief (FLEXCOM5) USART LIN Mode Register */
  #define REG_FLEXCOM5_US_LINIR                     (0xF0004258U) /**< \brief (FLEXCOM5) USART LIN Identifier Register */
  #define REG_FLEXCOM5_US_LINBRR                    (0xF000425CU) /**< \brief (FLEXCOM5) USART LIN Baud Rate Register */
  #define REG_FLEXCOM5_US_LONMR                     (0xF0004260U) /**< \brief (FLEXCOM5) USART LON Mode Register */
  #define REG_FLEXCOM5_US_LONPR                     (0xF0004264U) /**< \brief (FLEXCOM5) USART LON Preamble Register */
  #define REG_FLEXCOM5_US_LONDL                     (0xF0004268U) /**< \brief (FLEXCOM5) USART LON Data Length Register */
  #define REG_FLEXCOM5_US_LONL2HDR                  (0xF000426CU) /**< \brief (FLEXCOM5) USART LON L2HDR Register */
  #define REG_FLEXCOM5_US_LONBL                     (0xF0004270U) /**< \brief (FLEXCOM5) USART LON Backlog Register */
  #define REG_FLEXCOM5_US_LONB1TX                   (0xF0004274U) /**< \brief (FLEXCOM5) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM5_US_LONB1RX                   (0xF0004278U) /**< \brief (FLEXCOM5) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM5_US_LONPRIO                   (0xF000427CU) /**< \brief (FLEXCOM5) USART LON Priority Register */
  #define REG_FLEXCOM5_US_IDTTX                     (0xF0004280U) /**< \brief (FLEXCOM5) USART LON IDT Tx Register */
  #define REG_FLEXCOM5_US_IDTRX                     (0xF0004284U) /**< \brief (FLEXCOM5) USART LON IDT Rx Register */
  #define REG_FLEXCOM5_US_ICDIFF                    (0xF0004288U) /**< \brief (FLEXCOM5) USART IC DIFF Register */
  #define REG_FLEXCOM5_US_CMPR                      (0xF0004290U) /**< \brief (FLEXCOM5) USART Comparison Register */
  #define REG_FLEXCOM5_US_FMR                       (0xF00042A0U) /**< \brief (FLEXCOM5) USART FIFO Mode Register */
  #define REG_FLEXCOM5_US_FLR                       (0xF00042A4U) /**< \brief (FLEXCOM5) USART FIFO Level Register */
  #define REG_FLEXCOM5_US_FIER                      (0xF00042A8U) /**< \brief (FLEXCOM5) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM5_US_FIDR                      (0xF00042ACU) /**< \brief (FLEXCOM5) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM5_US_FIMR                      (0xF00042B0U) /**< \brief (FLEXCOM5) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM5_US_FESR                      (0xF00042B4U) /**< \brief (FLEXCOM5) USART FIFO Event Status Register */
  #define REG_FLEXCOM5_US_WPMR                      (0xF00042E4U) /**< \brief (FLEXCOM5) USART Write Protection Mode Register */
  #define REG_FLEXCOM5_US_WPSR                      (0xF00042E8U) /**< \brief (FLEXCOM5) USART Write Protection Status Register */
  #define REG_FLEXCOM5_SPI_CR                       (0xF0004400U) /**< \brief (FLEXCOM5) SPI Control Register */
  #define REG_FLEXCOM5_SPI_MR                       (0xF0004404U) /**< \brief (FLEXCOM5) SPI Mode Register */
  #define REG_FLEXCOM5_SPI_RDR                      (0xF0004408U) /**< \brief (FLEXCOM5) SPI Receive Data Register */
  #define REG_FLEXCOM5_SPI_TDR                      (0xF000440CU) /**< \brief (FLEXCOM5) SPI Transmit Data Register */
  #define REG_FLEXCOM5_SPI_SR                       (0xF0004410U) /**< \brief (FLEXCOM5) SPI Status Register */
  #define REG_FLEXCOM5_SPI_IER                      (0xF0004414U) /**< \brief (FLEXCOM5) SPI Interrupt Enable Register */
  #define REG_FLEXCOM5_SPI_IDR                      (0xF0004418U) /**< \brief (FLEXCOM5) SPI Interrupt Disable Register */
  #define REG_FLEXCOM5_SPI_IMR                      (0xF000441CU) /**< \brief (FLEXCOM5) SPI Interrupt Mask Register */
  #define REG_FLEXCOM5_SPI_CSR                      (0xF0004430U) /**< \brief (FLEXCOM5) SPI Chip Select Register */
  #define REG_FLEXCOM5_SPI_FMR                      (0xF0004440U) /**< \brief (FLEXCOM5) SPI FIFO Mode Register */
  #define REG_FLEXCOM5_SPI_FLR                      (0xF0004444U) /**< \brief (FLEXCOM5) SPI FIFO Level Register */
  #define REG_FLEXCOM5_SPI_CMPR                     (0xF0004448U) /**< \brief (FLEXCOM5) SPI Comparison Register */
  #define REG_FLEXCOM5_SPI_WPMR                     (0xF00044E4U) /**< \brief (FLEXCOM5) SPI Write Protection Mode Register */
  #define REG_FLEXCOM5_SPI_WPSR                     (0xF00044E8U) /**< \brief (FLEXCOM5) SPI Write Protection Status Register */
  #define REG_FLEXCOM5_TWI_CR                       (0xF0004600U) /**< \brief (FLEXCOM5) TWI Control Register */
  #define REG_FLEXCOM5_TWI_MMR                      (0xF0004604U) /**< \brief (FLEXCOM5) TWI Master Mode Register */
  #define REG_FLEXCOM5_TWI_SMR                      (0xF0004608U) /**< \brief (FLEXCOM5) TWI Slave Mode Register */
  #define REG_FLEXCOM5_TWI_IADR                     (0xF000460CU) /**< \brief (FLEXCOM5) TWI Internal Address Register */
  #define REG_FLEXCOM5_TWI_CWGR                     (0xF0004610U) /**< \brief (FLEXCOM5) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM5_TWI_SR                       (0xF0004620U) /**< \brief (FLEXCOM5) TWI Status Register */
  #define REG_FLEXCOM5_TWI_IER                      (0xF0004624U) /**< \brief (FLEXCOM5) TWI Interrupt Enable Register */
  #define REG_FLEXCOM5_TWI_IDR                      (0xF0004628U) /**< \brief (FLEXCOM5) TWI Interrupt Disable Register */
  #define REG_FLEXCOM5_TWI_IMR                      (0xF000462CU) /**< \brief (FLEXCOM5) TWI Interrupt Mask Register */
  #define REG_FLEXCOM5_TWI_RHR                      (0xF0004630U) /**< \brief (FLEXCOM5) TWI Receive Holding Register */
  #define REG_FLEXCOM5_TWI_THR                      (0xF0004634U) /**< \brief (FLEXCOM5) TWI Transmit Holding Register */
  #define REG_FLEXCOM5_TWI_SMBTR                    (0xF0004638U) /**< \brief (FLEXCOM5) TWI SMBus Timing Register */
  #define REG_FLEXCOM5_TWI_ACR                      (0xF0004640U) /**< \brief (FLEXCOM5) TWI Alternative Command Register */
  #define REG_FLEXCOM5_TWI_FILTR                    (0xF0004644U) /**< \brief (FLEXCOM5) TWI Filter Register */
  #define REG_FLEXCOM5_TWI_FMR                      (0xF0004650U) /**< \brief (FLEXCOM5) TWI FIFO Mode Register */
  #define REG_FLEXCOM5_TWI_FLR                      (0xF0004654U) /**< \brief (FLEXCOM5) TWI FIFO Level Register */
  #define REG_FLEXCOM5_TWI_FSR                      (0xF0004660U) /**< \brief (FLEXCOM5) TWI FIFO Status Register */
  #define REG_FLEXCOM5_TWI_FIER                     (0xF0004664U) /**< \brief (FLEXCOM5) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM5_TWI_FIDR                     (0xF0004668U) /**< \brief (FLEXCOM5) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM5_TWI_FIMR                     (0xF000466CU) /**< \brief (FLEXCOM5) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM5_TWI_WPMR                     (0xF00046E4U) /**< \brief (FLEXCOM5) TWI Write Protection Mode Register */
  #define REG_FLEXCOM5_TWI_WPSR                     (0xF00046E8U) /**< \brief (FLEXCOM5) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM5_MR          (*(__IO uint32_t*)0xF0004000U) /**< \brief (FLEXCOM5) FLEXCOM Mode Register */
  #define REG_FLEXCOM5_RHR         (*(__I  uint32_t*)0xF0004010U) /**< \brief (FLEXCOM5) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM5_THR         (*(__IO uint32_t*)0xF0004020U) /**< \brief (FLEXCOM5) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM5_US_CR       (*(__O  uint32_t*)0xF0004200U) /**< \brief (FLEXCOM5) USART Control Register */
  #define REG_FLEXCOM5_US_MR       (*(__IO uint32_t*)0xF0004204U) /**< \brief (FLEXCOM5) USART Mode Register */
  #define REG_FLEXCOM5_US_IER      (*(__O  uint32_t*)0xF0004208U) /**< \brief (FLEXCOM5) USART Interrupt Enable Register */
  #define REG_FLEXCOM5_US_IDR      (*(__O  uint32_t*)0xF000420CU) /**< \brief (FLEXCOM5) USART Interrupt Disable Register */
  #define REG_FLEXCOM5_US_IMR      (*(__I  uint32_t*)0xF0004210U) /**< \brief (FLEXCOM5) USART Interrupt Mask Register */
  #define REG_FLEXCOM5_US_CSR      (*(__I  uint32_t*)0xF0004214U) /**< \brief (FLEXCOM5) USART Channel Status Register */
  #define REG_FLEXCOM5_US_RHR      (*(__I  uint32_t*)0xF0004218U) /**< \brief (FLEXCOM5) USART Receive Holding Register */
  #define REG_FLEXCOM5_US_THR      (*(__O  uint32_t*)0xF000421CU) /**< \brief (FLEXCOM5) USART Transmit Holding Register */
  #define REG_FLEXCOM5_US_BRGR     (*(__IO uint32_t*)0xF0004220U) /**< \brief (FLEXCOM5) USART Baud Rate Generator Register */
  #define REG_FLEXCOM5_US_RTOR     (*(__IO uint32_t*)0xF0004224U) /**< \brief (FLEXCOM5) USART Receiver Timeout Register */
  #define REG_FLEXCOM5_US_TTGR     (*(__IO uint32_t*)0xF0004228U) /**< \brief (FLEXCOM5) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM5_US_FIDI     (*(__IO uint32_t*)0xF0004240U) /**< \brief (FLEXCOM5) USART FI DI Ratio Register */
  #define REG_FLEXCOM5_US_NER      (*(__I  uint32_t*)0xF0004244U) /**< \brief (FLEXCOM5) USART Number of Errors Register */
  #define REG_FLEXCOM5_US_IF       (*(__IO uint32_t*)0xF000424CU) /**< \brief (FLEXCOM5) USART IrDA Filter Register */
  #define REG_FLEXCOM5_US_MAN      (*(__IO uint32_t*)0xF0004250U) /**< \brief (FLEXCOM5) USART Manchester Configuration Register */
  #define REG_FLEXCOM5_US_LINMR    (*(__IO uint32_t*)0xF0004254U) /**< \brief (FLEXCOM5) USART LIN Mode Register */
  #define REG_FLEXCOM5_US_LINIR    (*(__IO uint32_t*)0xF0004258U) /**< \brief (FLEXCOM5) USART LIN Identifier Register */
  #define REG_FLEXCOM5_US_LINBRR   (*(__I  uint32_t*)0xF000425CU) /**< \brief (FLEXCOM5) USART LIN Baud Rate Register */
  #define REG_FLEXCOM5_US_LONMR    (*(__IO uint32_t*)0xF0004260U) /**< \brief (FLEXCOM5) USART LON Mode Register */
  #define REG_FLEXCOM5_US_LONPR    (*(__IO uint32_t*)0xF0004264U) /**< \brief (FLEXCOM5) USART LON Preamble Register */
  #define REG_FLEXCOM5_US_LONDL    (*(__IO uint32_t*)0xF0004268U) /**< \brief (FLEXCOM5) USART LON Data Length Register */
  #define REG_FLEXCOM5_US_LONL2HDR (*(__IO uint32_t*)0xF000426CU) /**< \brief (FLEXCOM5) USART LON L2HDR Register */
  #define REG_FLEXCOM5_US_LONBL    (*(__I  uint32_t*)0xF0004270U) /**< \brief (FLEXCOM5) USART LON Backlog Register */
  #define REG_FLEXCOM5_US_LONB1TX  (*(__IO uint32_t*)0xF0004274U) /**< \brief (FLEXCOM5) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM5_US_LONB1RX  (*(__IO uint32_t*)0xF0004278U) /**< \brief (FLEXCOM5) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM5_US_LONPRIO  (*(__IO uint32_t*)0xF000427CU) /**< \brief (FLEXCOM5) USART LON Priority Register */
  #define REG_FLEXCOM5_US_IDTTX    (*(__IO uint32_t*)0xF0004280U) /**< \brief (FLEXCOM5) USART LON IDT Tx Register */
  #define REG_FLEXCOM5_US_IDTRX    (*(__IO uint32_t*)0xF0004284U) /**< \brief (FLEXCOM5) USART LON IDT Rx Register */
  #define REG_FLEXCOM5_US_ICDIFF   (*(__IO uint32_t*)0xF0004288U) /**< \brief (FLEXCOM5) USART IC DIFF Register */
  #define REG_FLEXCOM5_US_CMPR     (*(__IO uint32_t*)0xF0004290U) /**< \brief (FLEXCOM5) USART Comparison Register */
  #define REG_FLEXCOM5_US_FMR      (*(__IO uint32_t*)0xF00042A0U) /**< \brief (FLEXCOM5) USART FIFO Mode Register */
  #define REG_FLEXCOM5_US_FLR      (*(__I  uint32_t*)0xF00042A4U) /**< \brief (FLEXCOM5) USART FIFO Level Register */
  #define REG_FLEXCOM5_US_FIER     (*(__O  uint32_t*)0xF00042A8U) /**< \brief (FLEXCOM5) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM5_US_FIDR     (*(__O  uint32_t*)0xF00042ACU) /**< \brief (FLEXCOM5) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM5_US_FIMR     (*(__I  uint32_t*)0xF00042B0U) /**< \brief (FLEXCOM5) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM5_US_FESR     (*(__I  uint32_t*)0xF00042B4U) /**< \brief (FLEXCOM5) USART FIFO Event Status Register */
  #define REG_FLEXCOM5_US_WPMR     (*(__IO uint32_t*)0xF00042E4U) /**< \brief (FLEXCOM5) USART Write Protection Mode Register */
  #define REG_FLEXCOM5_US_WPSR     (*(__I  uint32_t*)0xF00042E8U) /**< \brief (FLEXCOM5) USART Write Protection Status Register */
  #define REG_FLEXCOM5_SPI_CR      (*(__O  uint32_t*)0xF0004400U) /**< \brief (FLEXCOM5) SPI Control Register */
  #define REG_FLEXCOM5_SPI_MR      (*(__IO uint32_t*)0xF0004404U) /**< \brief (FLEXCOM5) SPI Mode Register */
  #define REG_FLEXCOM5_SPI_RDR     (*(__I  uint32_t*)0xF0004408U) /**< \brief (FLEXCOM5) SPI Receive Data Register */
  #define REG_FLEXCOM5_SPI_TDR     (*(__O  uint32_t*)0xF000440CU) /**< \brief (FLEXCOM5) SPI Transmit Data Register */
  #define REG_FLEXCOM5_SPI_SR      (*(__I  uint32_t*)0xF0004410U) /**< \brief (FLEXCOM5) SPI Status Register */
  #define REG_FLEXCOM5_SPI_IER     (*(__O  uint32_t*)0xF0004414U) /**< \brief (FLEXCOM5) SPI Interrupt Enable Register */
  #define REG_FLEXCOM5_SPI_IDR     (*(__O  uint32_t*)0xF0004418U) /**< \brief (FLEXCOM5) SPI Interrupt Disable Register */
  #define REG_FLEXCOM5_SPI_IMR     (*(__I  uint32_t*)0xF000441CU) /**< \brief (FLEXCOM5) SPI Interrupt Mask Register */
  #define REG_FLEXCOM5_SPI_CSR     (*(__IO uint32_t*)0xF0004430U) /**< \brief (FLEXCOM5) SPI Chip Select Register */
  #define REG_FLEXCOM5_SPI_FMR     (*(__IO uint32_t*)0xF0004440U) /**< \brief (FLEXCOM5) SPI FIFO Mode Register */
  #define REG_FLEXCOM5_SPI_FLR     (*(__I  uint32_t*)0xF0004444U) /**< \brief (FLEXCOM5) SPI FIFO Level Register */
  #define REG_FLEXCOM5_SPI_CMPR    (*(__IO uint32_t*)0xF0004448U) /**< \brief (FLEXCOM5) SPI Comparison Register */
  #define REG_FLEXCOM5_SPI_WPMR    (*(__IO uint32_t*)0xF00044E4U) /**< \brief (FLEXCOM5) SPI Write Protection Mode Register */
  #define REG_FLEXCOM5_SPI_WPSR    (*(__I  uint32_t*)0xF00044E8U) /**< \brief (FLEXCOM5) SPI Write Protection Status Register */
  #define REG_FLEXCOM5_TWI_CR      (*(__O  uint32_t*)0xF0004600U) /**< \brief (FLEXCOM5) TWI Control Register */
  #define REG_FLEXCOM5_TWI_MMR     (*(__IO uint32_t*)0xF0004604U) /**< \brief (FLEXCOM5) TWI Master Mode Register */
  #define REG_FLEXCOM5_TWI_SMR     (*(__IO uint32_t*)0xF0004608U) /**< \brief (FLEXCOM5) TWI Slave Mode Register */
  #define REG_FLEXCOM5_TWI_IADR    (*(__IO uint32_t*)0xF000460CU) /**< \brief (FLEXCOM5) TWI Internal Address Register */
  #define REG_FLEXCOM5_TWI_CWGR    (*(__IO uint32_t*)0xF0004610U) /**< \brief (FLEXCOM5) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM5_TWI_SR      (*(__I  uint32_t*)0xF0004620U) /**< \brief (FLEXCOM5) TWI Status Register */
  #define REG_FLEXCOM5_TWI_IER     (*(__O  uint32_t*)0xF0004624U) /**< \brief (FLEXCOM5) TWI Interrupt Enable Register */
  #define REG_FLEXCOM5_TWI_IDR     (*(__O  uint32_t*)0xF0004628U) /**< \brief (FLEXCOM5) TWI Interrupt Disable Register */
  #define REG_FLEXCOM5_TWI_IMR     (*(__I  uint32_t*)0xF000462CU) /**< \brief (FLEXCOM5) TWI Interrupt Mask Register */
  #define REG_FLEXCOM5_TWI_RHR     (*(__I  uint32_t*)0xF0004630U) /**< \brief (FLEXCOM5) TWI Receive Holding Register */
  #define REG_FLEXCOM5_TWI_THR     (*(__O  uint32_t*)0xF0004634U) /**< \brief (FLEXCOM5) TWI Transmit Holding Register */
  #define REG_FLEXCOM5_TWI_SMBTR   (*(__IO uint32_t*)0xF0004638U) /**< \brief (FLEXCOM5) TWI SMBus Timing Register */
  #define REG_FLEXCOM5_TWI_ACR     (*(__IO uint32_t*)0xF0004640U) /**< \brief (FLEXCOM5) TWI Alternative Command Register */
  #define REG_FLEXCOM5_TWI_FILTR   (*(__IO uint32_t*)0xF0004644U) /**< \brief (FLEXCOM5) TWI Filter Register */
  #define REG_FLEXCOM5_TWI_FMR     (*(__IO uint32_t*)0xF0004650U) /**< \brief (FLEXCOM5) TWI FIFO Mode Register */
  #define REG_FLEXCOM5_TWI_FLR     (*(__I  uint32_t*)0xF0004654U) /**< \brief (FLEXCOM5) TWI FIFO Level Register */
  #define REG_FLEXCOM5_TWI_FSR     (*(__I  uint32_t*)0xF0004660U) /**< \brief (FLEXCOM5) TWI FIFO Status Register */
  #define REG_FLEXCOM5_TWI_FIER    (*(__O  uint32_t*)0xF0004664U) /**< \brief (FLEXCOM5) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM5_TWI_FIDR    (*(__O  uint32_t*)0xF0004668U) /**< \brief (FLEXCOM5) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM5_TWI_FIMR    (*(__I  uint32_t*)0xF000466CU) /**< \brief (FLEXCOM5) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM5_TWI_WPMR    (*(__IO uint32_t*)0xF00046E4U) /**< \brief (FLEXCOM5) TWI Write Protection Mode Register */
  #define REG_FLEXCOM5_TWI_WPSR    (*(__I  uint32_t*)0xF00046E8U) /**< \brief (FLEXCOM5) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM5_INSTANCE_ */
