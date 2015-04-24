/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2015, Atmel Corporation                                        */
/*                                                                              */
/* All rights reserved.                                                         */
/*                                                                              */
/* Redistribution and use in source and binary forms, with or without           */
/* modification, are permitted provided that the following condition is met:    */
/*                                                                              */
/* - Redistributions of source code must retain the above copyright notice,     */
/* this list of conditions and the disclaimer below.                            */
/*                                                                              */
/* Atmel's name may not be used to endorse or promote products derived from     */
/* this software without specific prior written permission.                     */
/*                                                                              */
/* DISCLAIMER:  THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR   */
/* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE   */
/* DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,      */
/* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,  */
/* OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF    */
/* LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING         */
/* NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, */
/* EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.                           */
/* ---------------------------------------------------------------------------- */

#ifndef _SAMA5D2_FLEXCOM4_INSTANCE_
#define _SAMA5D2_FLEXCOM4_INSTANCE_

/* ========== Register definition for FLEXCOM4 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM4_MR                           (0xFC018000U) /**< \brief (FLEXCOM4) FLEXCOM Mode Register */
  #define REG_FLEXCOM4_RHR                          (0xFC018010U) /**< \brief (FLEXCOM4) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM4_THR                          (0xFC018020U) /**< \brief (FLEXCOM4) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM4_VERSION                      (0xFC0180FCU) /**< \brief (FLEXCOM4) FLEXCOM Version Register */
  #define REG_FLEXCOM4_US_CR                        (0xFC018200U) /**< \brief (FLEXCOM4) USART Control Register */
  #define REG_FLEXCOM4_US_MR                        (0xFC018204U) /**< \brief (FLEXCOM4) USART Mode Register */
  #define REG_FLEXCOM4_US_IER                       (0xFC018208U) /**< \brief (FLEXCOM4) USART Interrupt Enable Register */
  #define REG_FLEXCOM4_US_IDR                       (0xFC01820CU) /**< \brief (FLEXCOM4) USART Interrupt Disable Register */
  #define REG_FLEXCOM4_US_IMR                       (0xFC018210U) /**< \brief (FLEXCOM4) USART Interrupt Mask Register */
  #define REG_FLEXCOM4_US_CSR                       (0xFC018214U) /**< \brief (FLEXCOM4) USART Channel Status Register */
  #define REG_FLEXCOM4_US_RHR                       (0xFC018218U) /**< \brief (FLEXCOM4) USART Receive Holding Register */
  #define REG_FLEXCOM4_US_THR                       (0xFC01821CU) /**< \brief (FLEXCOM4) USART Transmit Holding Register */
  #define REG_FLEXCOM4_US_BRGR                      (0xFC018220U) /**< \brief (FLEXCOM4) USART Baud Rate Generator Register */
  #define REG_FLEXCOM4_US_RTOR                      (0xFC018224U) /**< \brief (FLEXCOM4) USART Receiver Timeout Register */
  #define REG_FLEXCOM4_US_TTGR                      (0xFC018228U) /**< \brief (FLEXCOM4) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM4_US_FIDI                      (0xFC018240U) /**< \brief (FLEXCOM4) USART FI DI Ratio Register */
  #define REG_FLEXCOM4_US_NER                       (0xFC018244U) /**< \brief (FLEXCOM4) USART Number of Errors Register */
  #define REG_FLEXCOM4_US_IF                        (0xFC01824CU) /**< \brief (FLEXCOM4) USART IrDA Filter Register */
  #define REG_FLEXCOM4_US_MAN                       (0xFC018250U) /**< \brief (FLEXCOM4) USART Manchester Configuration Register */
  #define REG_FLEXCOM4_US_LINMR                     (0xFC018254U) /**< \brief (FLEXCOM4) USART LIN Mode Register */
  #define REG_FLEXCOM4_US_LINIR                     (0xFC018258U) /**< \brief (FLEXCOM4) USART LIN Identifier Register */
  #define REG_FLEXCOM4_US_LINBRR                    (0xFC01825CU) /**< \brief (FLEXCOM4) USART LIN Baud Rate Register */
  #define REG_FLEXCOM4_US_CMPR                      (0xFC018290U) /**< \brief (FLEXCOM4) USART Comparison Register */
  #define REG_FLEXCOM4_US_FMR                       (0xFC0182A0U) /**< \brief (FLEXCOM4) USART FIFO Mode Register */
  #define REG_FLEXCOM4_US_FESR                      (0xFC0182A4U) /**< \brief (FLEXCOM4) USART FIFO Level Register */
  #define REG_FLEXCOM4_US_FIER                      (0xFC0182A8U) /**< \brief (FLEXCOM4) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM4_US_FIDR                      (0xFC0182ACU) /**< \brief (FLEXCOM4) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM4_US_FIMR                      (0xFC0182B0U) /**< \brief (FLEXCOM4) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM4_US_FLR                       (0xFC0182B4U) /**< \brief (FLEXCOM4) USART FIFO Event Status Register */
  #define REG_FLEXCOM4_US_WPMR                      (0xFC0182E4U) /**< \brief (FLEXCOM4) USART Write Protection Mode Register */
  #define REG_FLEXCOM4_US_WPSR                      (0xFC0182E8U) /**< \brief (FLEXCOM4) USART Write Protection Status Register */
  #define REG_FLEXCOM4_US_VERSION                   (0xFC0182FCU) /**< \brief (FLEXCOM4) USART Version Register */
  #define REG_FLEXCOM4_SPI_CR                       (0xFC018400U) /**< \brief (FLEXCOM4) SPI Control Register */
  #define REG_FLEXCOM4_SPI_MR                       (0xFC018404U) /**< \brief (FLEXCOM4) SPI Mode Register */
  #define REG_FLEXCOM4_SPI_RDR                      (0xFC018408U) /**< \brief (FLEXCOM4) SPI Receive Data Register */
  #define REG_FLEXCOM4_SPI_TDR                      (0xFC01840CU) /**< \brief (FLEXCOM4) SPI Transmit Data Register */
  #define REG_FLEXCOM4_SPI_SR                       (0xFC018410U) /**< \brief (FLEXCOM4) SPI Status Register */
  #define REG_FLEXCOM4_SPI_IER                      (0xFC018414U) /**< \brief (FLEXCOM4) SPI Interrupt Enable Register */
  #define REG_FLEXCOM4_SPI_IDR                      (0xFC018418U) /**< \brief (FLEXCOM4) SPI Interrupt Disable Register */
  #define REG_FLEXCOM4_SPI_IMR                      (0xFC01841CU) /**< \brief (FLEXCOM4) SPI Interrupt Mask Register */
  #define REG_FLEXCOM4_SPI_CSR                      (0xFC018430U) /**< \brief (FLEXCOM4) SPI Chip Select Register */
  #define REG_FLEXCOM4_SPI_FMR                      (0xFC018440U) /**< \brief (FLEXCOM4) SPI FIFO Mode Register */
  #define REG_FLEXCOM4_SPI_FLR                      (0xFC018444U) /**< \brief (FLEXCOM4) SPI FIFO Level Register */
  #define REG_FLEXCOM4_SPI_CMPR                     (0xFC018448U) /**< \brief (FLEXCOM4) SPI Comparison Register */
  #define REG_FLEXCOM4_SPI_WPMR                     (0xFC0184E4U) /**< \brief (FLEXCOM4) SPI Write Protection Mode Register */
  #define REG_FLEXCOM4_SPI_WPSR                     (0xFC0184E8U) /**< \brief (FLEXCOM4) SPI Write Protection Status Register */
  #define REG_FLEXCOM4_SPI_VERSION                  (0xFC0184FCU) /**< \brief (FLEXCOM4) SPI Version Register */
  #define REG_FLEXCOM4_TWI_CR                       (0xFC018600U) /**< \brief (FLEXCOM4) TWI Control Register */
  #define REG_FLEXCOM4_TWI_MMR                      (0xFC018604U) /**< \brief (FLEXCOM4) TWI Master Mode Register */
  #define REG_FLEXCOM4_TWI_SMR                      (0xFC018608U) /**< \brief (FLEXCOM4) TWI Slave Mode Register */
  #define REG_FLEXCOM4_TWI_IADR                     (0xFC01860CU) /**< \brief (FLEXCOM4) TWI Internal Address Register */
  #define REG_FLEXCOM4_TWI_CWGR                     (0xFC018610U) /**< \brief (FLEXCOM4) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM4_TWI_SR                       (0xFC018620U) /**< \brief (FLEXCOM4) TWI Status Register */
  #define REG_FLEXCOM4_TWI_IER                      (0xFC018624U) /**< \brief (FLEXCOM4) TWI Interrupt Enable Register */
  #define REG_FLEXCOM4_TWI_IDR                      (0xFC018628U) /**< \brief (FLEXCOM4) TWI Interrupt Disable Register */
  #define REG_FLEXCOM4_TWI_IMR                      (0xFC01862CU) /**< \brief (FLEXCOM4) TWI Interrupt Mask Register */
  #define REG_FLEXCOM4_TWI_RHR                      (0xFC018630U) /**< \brief (FLEXCOM4) TWI Receive Holding Register */
  #define REG_FLEXCOM4_TWI_THR                      (0xFC018634U) /**< \brief (FLEXCOM4) TWI Transmit Holding Register */
  #define REG_FLEXCOM4_TWI_SMBTR                    (0xFC018638U) /**< \brief (FLEXCOM4) TWI SMBus Timing Register */
  #define REG_FLEXCOM4_TWI_ACR                      (0xFC018640U) /**< \brief (FLEXCOM4) TWI Alternative Command Register */
  #define REG_FLEXCOM4_TWI_FILTR                    (0xFC018644U) /**< \brief (FLEXCOM4) TWI Filter Register */
  #define REG_FLEXCOM4_TWI_SWMR                     (0xFC01864CU) /**< \brief (FLEXCOM4) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM4_TWI_FMR                      (0xFC018650U) /**< \brief (FLEXCOM4) TWI FIFO Mode Register */
  #define REG_FLEXCOM4_TWI_FLR                      (0xFC018654U) /**< \brief (FLEXCOM4) TWI FIFO Level Register */
  #define REG_FLEXCOM4_TWI_FSR                      (0xFC018660U) /**< \brief (FLEXCOM4) TWI FIFO Status Register */
  #define REG_FLEXCOM4_TWI_FIER                     (0xFC018664U) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM4_TWI_FIDR                     (0xFC018668U) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM4_TWI_FIMR                     (0xFC01866CU) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM4_TWI_DR                       (0xFC0186D0U) /**< \brief (FLEXCOM4) TWI Debug Register */
  #define REG_FLEXCOM4_TWI_WPMR                     (0xFC0186E4U) /**< \brief (FLEXCOM4) TWI Protection Mode Register */
  #define REG_FLEXCOM4_TWI_WPSR                     (0xFC0186E8U) /**< \brief (FLEXCOM4) TWI Protection Status Register */
  #define REG_FLEXCOM4_TWI_VER                      (0xFC0186FCU) /**< \brief (FLEXCOM4) TWI Version Register */
#else
  #define REG_FLEXCOM4_MR          (*(__IO uint32_t*)0xFC018000U) /**< \brief (FLEXCOM4) FLEXCOM Mode Register */
  #define REG_FLEXCOM4_RHR         (*(__I  uint32_t*)0xFC018010U) /**< \brief (FLEXCOM4) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM4_THR         (*(__IO uint32_t*)0xFC018020U) /**< \brief (FLEXCOM4) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM4_VERSION     (*(__I  uint32_t*)0xFC0180FCU) /**< \brief (FLEXCOM4) FLEXCOM Version Register */
  #define REG_FLEXCOM4_US_CR       (*(__O  uint32_t*)0xFC018200U) /**< \brief (FLEXCOM4) USART Control Register */
  #define REG_FLEXCOM4_US_MR       (*(__IO uint32_t*)0xFC018204U) /**< \brief (FLEXCOM4) USART Mode Register */
  #define REG_FLEXCOM4_US_IER      (*(__O  uint32_t*)0xFC018208U) /**< \brief (FLEXCOM4) USART Interrupt Enable Register */
  #define REG_FLEXCOM4_US_IDR      (*(__O  uint32_t*)0xFC01820CU) /**< \brief (FLEXCOM4) USART Interrupt Disable Register */
  #define REG_FLEXCOM4_US_IMR      (*(__I  uint32_t*)0xFC018210U) /**< \brief (FLEXCOM4) USART Interrupt Mask Register */
  #define REG_FLEXCOM4_US_CSR      (*(__I  uint32_t*)0xFC018214U) /**< \brief (FLEXCOM4) USART Channel Status Register */
  #define REG_FLEXCOM4_US_RHR      (*(__I  uint32_t*)0xFC018218U) /**< \brief (FLEXCOM4) USART Receive Holding Register */
  #define REG_FLEXCOM4_US_THR      (*(__O  uint32_t*)0xFC01821CU) /**< \brief (FLEXCOM4) USART Transmit Holding Register */
  #define REG_FLEXCOM4_US_BRGR     (*(__IO uint32_t*)0xFC018220U) /**< \brief (FLEXCOM4) USART Baud Rate Generator Register */
  #define REG_FLEXCOM4_US_RTOR     (*(__IO uint32_t*)0xFC018224U) /**< \brief (FLEXCOM4) USART Receiver Timeout Register */
  #define REG_FLEXCOM4_US_TTGR     (*(__IO uint32_t*)0xFC018228U) /**< \brief (FLEXCOM4) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM4_US_FIDI     (*(__IO uint32_t*)0xFC018240U) /**< \brief (FLEXCOM4) USART FI DI Ratio Register */
  #define REG_FLEXCOM4_US_NER      (*(__I  uint32_t*)0xFC018244U) /**< \brief (FLEXCOM4) USART Number of Errors Register */
  #define REG_FLEXCOM4_US_IF       (*(__IO uint32_t*)0xFC01824CU) /**< \brief (FLEXCOM4) USART IrDA Filter Register */
  #define REG_FLEXCOM4_US_MAN      (*(__IO uint32_t*)0xFC018250U) /**< \brief (FLEXCOM4) USART Manchester Configuration Register */
  #define REG_FLEXCOM4_US_LINMR    (*(__IO uint32_t*)0xFC018254U) /**< \brief (FLEXCOM4) USART LIN Mode Register */
  #define REG_FLEXCOM4_US_LINIR    (*(__IO uint32_t*)0xFC018258U) /**< \brief (FLEXCOM4) USART LIN Identifier Register */
  #define REG_FLEXCOM4_US_LINBRR   (*(__I  uint32_t*)0xFC01825CU) /**< \brief (FLEXCOM4) USART LIN Baud Rate Register */
  #define REG_FLEXCOM4_US_CMPR     (*(__IO uint32_t*)0xFC018290U) /**< \brief (FLEXCOM4) USART Comparison Register */
  #define REG_FLEXCOM4_US_FMR      (*(__IO uint32_t*)0xFC0182A0U) /**< \brief (FLEXCOM4) USART FIFO Mode Register */
  #define REG_FLEXCOM4_US_FESR     (*(__I  uint32_t*)0xFC0182A4U) /**< \brief (FLEXCOM4) USART FIFO Level Register */
  #define REG_FLEXCOM4_US_FIER     (*(__O  uint32_t*)0xFC0182A8U) /**< \brief (FLEXCOM4) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM4_US_FIDR     (*(__O  uint32_t*)0xFC0182ACU) /**< \brief (FLEXCOM4) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM4_US_FIMR     (*(__I  uint32_t*)0xFC0182B0U) /**< \brief (FLEXCOM4) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM4_US_FLR      (*(__I  uint32_t*)0xFC0182B4U) /**< \brief (FLEXCOM4) USART FIFO Event Status Register */
  #define REG_FLEXCOM4_US_WPMR     (*(__IO uint32_t*)0xFC0182E4U) /**< \brief (FLEXCOM4) USART Write Protection Mode Register */
  #define REG_FLEXCOM4_US_WPSR     (*(__I  uint32_t*)0xFC0182E8U) /**< \brief (FLEXCOM4) USART Write Protection Status Register */
  #define REG_FLEXCOM4_US_VERSION  (*(__I  uint32_t*)0xFC0182FCU) /**< \brief (FLEXCOM4) USART Version Register */
  #define REG_FLEXCOM4_SPI_CR      (*(__O  uint32_t*)0xFC018400U) /**< \brief (FLEXCOM4) SPI Control Register */
  #define REG_FLEXCOM4_SPI_MR      (*(__IO uint32_t*)0xFC018404U) /**< \brief (FLEXCOM4) SPI Mode Register */
  #define REG_FLEXCOM4_SPI_RDR     (*(__I  uint32_t*)0xFC018408U) /**< \brief (FLEXCOM4) SPI Receive Data Register */
  #define REG_FLEXCOM4_SPI_TDR     (*(__O  uint32_t*)0xFC01840CU) /**< \brief (FLEXCOM4) SPI Transmit Data Register */
  #define REG_FLEXCOM4_SPI_SR      (*(__I  uint32_t*)0xFC018410U) /**< \brief (FLEXCOM4) SPI Status Register */
  #define REG_FLEXCOM4_SPI_IER     (*(__O  uint32_t*)0xFC018414U) /**< \brief (FLEXCOM4) SPI Interrupt Enable Register */
  #define REG_FLEXCOM4_SPI_IDR     (*(__O  uint32_t*)0xFC018418U) /**< \brief (FLEXCOM4) SPI Interrupt Disable Register */
  #define REG_FLEXCOM4_SPI_IMR     (*(__I  uint32_t*)0xFC01841CU) /**< \brief (FLEXCOM4) SPI Interrupt Mask Register */
  #define REG_FLEXCOM4_SPI_CSR     (*(__IO uint32_t*)0xFC018430U) /**< \brief (FLEXCOM4) SPI Chip Select Register */
  #define REG_FLEXCOM4_SPI_FMR     (*(__IO uint32_t*)0xFC018440U) /**< \brief (FLEXCOM4) SPI FIFO Mode Register */
  #define REG_FLEXCOM4_SPI_FLR     (*(__I  uint32_t*)0xFC018444U) /**< \brief (FLEXCOM4) SPI FIFO Level Register */
  #define REG_FLEXCOM4_SPI_CMPR    (*(__IO uint32_t*)0xFC018448U) /**< \brief (FLEXCOM4) SPI Comparison Register */
  #define REG_FLEXCOM4_SPI_WPMR    (*(__IO uint32_t*)0xFC0184E4U) /**< \brief (FLEXCOM4) SPI Write Protection Mode Register */
  #define REG_FLEXCOM4_SPI_WPSR    (*(__I  uint32_t*)0xFC0184E8U) /**< \brief (FLEXCOM4) SPI Write Protection Status Register */
  #define REG_FLEXCOM4_SPI_VERSION (*(__I  uint32_t*)0xFC0184FCU) /**< \brief (FLEXCOM4) SPI Version Register */
  #define REG_FLEXCOM4_TWI_CR      (*(__O  uint32_t*)0xFC018600U) /**< \brief (FLEXCOM4) TWI Control Register */
  #define REG_FLEXCOM4_TWI_MMR     (*(__IO uint32_t*)0xFC018604U) /**< \brief (FLEXCOM4) TWI Master Mode Register */
  #define REG_FLEXCOM4_TWI_SMR     (*(__IO uint32_t*)0xFC018608U) /**< \brief (FLEXCOM4) TWI Slave Mode Register */
  #define REG_FLEXCOM4_TWI_IADR    (*(__IO uint32_t*)0xFC01860CU) /**< \brief (FLEXCOM4) TWI Internal Address Register */
  #define REG_FLEXCOM4_TWI_CWGR    (*(__IO uint32_t*)0xFC018610U) /**< \brief (FLEXCOM4) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM4_TWI_SR      (*(__I  uint32_t*)0xFC018620U) /**< \brief (FLEXCOM4) TWI Status Register */
  #define REG_FLEXCOM4_TWI_IER     (*(__O  uint32_t*)0xFC018624U) /**< \brief (FLEXCOM4) TWI Interrupt Enable Register */
  #define REG_FLEXCOM4_TWI_IDR     (*(__O  uint32_t*)0xFC018628U) /**< \brief (FLEXCOM4) TWI Interrupt Disable Register */
  #define REG_FLEXCOM4_TWI_IMR     (*(__I  uint32_t*)0xFC01862CU) /**< \brief (FLEXCOM4) TWI Interrupt Mask Register */
  #define REG_FLEXCOM4_TWI_RHR     (*(__I  uint32_t*)0xFC018630U) /**< \brief (FLEXCOM4) TWI Receive Holding Register */
  #define REG_FLEXCOM4_TWI_THR     (*(__O  uint32_t*)0xFC018634U) /**< \brief (FLEXCOM4) TWI Transmit Holding Register */
  #define REG_FLEXCOM4_TWI_SMBTR   (*(__IO uint32_t*)0xFC018638U) /**< \brief (FLEXCOM4) TWI SMBus Timing Register */
  #define REG_FLEXCOM4_TWI_ACR     (*(__IO uint32_t*)0xFC018640U) /**< \brief (FLEXCOM4) TWI Alternative Command Register */
  #define REG_FLEXCOM4_TWI_FILTR   (*(__IO uint32_t*)0xFC018644U) /**< \brief (FLEXCOM4) TWI Filter Register */
  #define REG_FLEXCOM4_TWI_SWMR    (*(__IO uint32_t*)0xFC01864CU) /**< \brief (FLEXCOM4) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM4_TWI_FMR     (*(__IO uint32_t*)0xFC018650U) /**< \brief (FLEXCOM4) TWI FIFO Mode Register */
  #define REG_FLEXCOM4_TWI_FLR     (*(__I  uint32_t*)0xFC018654U) /**< \brief (FLEXCOM4) TWI FIFO Level Register */
  #define REG_FLEXCOM4_TWI_FSR     (*(__I  uint32_t*)0xFC018660U) /**< \brief (FLEXCOM4) TWI FIFO Status Register */
  #define REG_FLEXCOM4_TWI_FIER    (*(__O  uint32_t*)0xFC018664U) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM4_TWI_FIDR    (*(__O  uint32_t*)0xFC018668U) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM4_TWI_FIMR    (*(__I  uint32_t*)0xFC01866CU) /**< \brief (FLEXCOM4) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM4_TWI_DR      (*(__I  uint32_t*)0xFC0186D0U) /**< \brief (FLEXCOM4) TWI Debug Register */
  #define REG_FLEXCOM4_TWI_WPMR    (*(__IO uint32_t*)0xFC0186E4U) /**< \brief (FLEXCOM4) TWI Protection Mode Register */
  #define REG_FLEXCOM4_TWI_WPSR    (*(__I  uint32_t*)0xFC0186E8U) /**< \brief (FLEXCOM4) TWI Protection Status Register */
  #define REG_FLEXCOM4_TWI_VER     (*(__I  uint32_t*)0xFC0186FCU) /**< \brief (FLEXCOM4) TWI Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_FLEXCOM4_INSTANCE_ */
