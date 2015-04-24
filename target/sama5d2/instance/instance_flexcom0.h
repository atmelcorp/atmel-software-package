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

#ifndef _SAMA5D2_FLEXCOM0_INSTANCE_
#define _SAMA5D2_FLEXCOM0_INSTANCE_

/* ========== Register definition for FLEXCOM0 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM0_MR                           (0xF8034000U) /**< \brief (FLEXCOM0) FLEXCOM Mode Register */
  #define REG_FLEXCOM0_RHR                          (0xF8034010U) /**< \brief (FLEXCOM0) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM0_THR                          (0xF8034020U) /**< \brief (FLEXCOM0) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM0_VERSION                      (0xF80340FCU) /**< \brief (FLEXCOM0) FLEXCOM Version Register */
  #define REG_FLEXCOM0_US_CR                        (0xF8034200U) /**< \brief (FLEXCOM0) USART Control Register */
  #define REG_FLEXCOM0_US_MR                        (0xF8034204U) /**< \brief (FLEXCOM0) USART Mode Register */
  #define REG_FLEXCOM0_US_IER                       (0xF8034208U) /**< \brief (FLEXCOM0) USART Interrupt Enable Register */
  #define REG_FLEXCOM0_US_IDR                       (0xF803420CU) /**< \brief (FLEXCOM0) USART Interrupt Disable Register */
  #define REG_FLEXCOM0_US_IMR                       (0xF8034210U) /**< \brief (FLEXCOM0) USART Interrupt Mask Register */
  #define REG_FLEXCOM0_US_CSR                       (0xF8034214U) /**< \brief (FLEXCOM0) USART Channel Status Register */
  #define REG_FLEXCOM0_US_RHR                       (0xF8034218U) /**< \brief (FLEXCOM0) USART Receive Holding Register */
  #define REG_FLEXCOM0_US_THR                       (0xF803421CU) /**< \brief (FLEXCOM0) USART Transmit Holding Register */
  #define REG_FLEXCOM0_US_BRGR                      (0xF8034220U) /**< \brief (FLEXCOM0) USART Baud Rate Generator Register */
  #define REG_FLEXCOM0_US_RTOR                      (0xF8034224U) /**< \brief (FLEXCOM0) USART Receiver Timeout Register */
  #define REG_FLEXCOM0_US_TTGR                      (0xF8034228U) /**< \brief (FLEXCOM0) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM0_US_FIDI                      (0xF8034240U) /**< \brief (FLEXCOM0) USART FI DI Ratio Register */
  #define REG_FLEXCOM0_US_NER                       (0xF8034244U) /**< \brief (FLEXCOM0) USART Number of Errors Register */
  #define REG_FLEXCOM0_US_IF                        (0xF803424CU) /**< \brief (FLEXCOM0) USART IrDA Filter Register */
  #define REG_FLEXCOM0_US_MAN                       (0xF8034250U) /**< \brief (FLEXCOM0) USART Manchester Configuration Register */
  #define REG_FLEXCOM0_US_LINMR                     (0xF8034254U) /**< \brief (FLEXCOM0) USART LIN Mode Register */
  #define REG_FLEXCOM0_US_LINIR                     (0xF8034258U) /**< \brief (FLEXCOM0) USART LIN Identifier Register */
  #define REG_FLEXCOM0_US_LINBRR                    (0xF803425CU) /**< \brief (FLEXCOM0) USART LIN Baud Rate Register */
  #define REG_FLEXCOM0_US_CMPR                      (0xF8034290U) /**< \brief (FLEXCOM0) USART Comparison Register */
  #define REG_FLEXCOM0_US_FMR                       (0xF80342A0U) /**< \brief (FLEXCOM0) USART FIFO Mode Register */
  #define REG_FLEXCOM0_US_FESR                      (0xF80342A4U) /**< \brief (FLEXCOM0) USART FIFO Level Register */
  #define REG_FLEXCOM0_US_FIER                      (0xF80342A8U) /**< \brief (FLEXCOM0) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM0_US_FIDR                      (0xF80342ACU) /**< \brief (FLEXCOM0) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM0_US_FIMR                      (0xF80342B0U) /**< \brief (FLEXCOM0) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM0_US_FLR                       (0xF80342B4U) /**< \brief (FLEXCOM0) USART FIFO Event Status Register */
  #define REG_FLEXCOM0_US_WPMR                      (0xF80342E4U) /**< \brief (FLEXCOM0) USART Write Protection Mode Register */
  #define REG_FLEXCOM0_US_WPSR                      (0xF80342E8U) /**< \brief (FLEXCOM0) USART Write Protection Status Register */
  #define REG_FLEXCOM0_US_VERSION                   (0xF80342FCU) /**< \brief (FLEXCOM0) USART Version Register */
  #define REG_FLEXCOM0_SPI_CR                       (0xF8034400U) /**< \brief (FLEXCOM0) SPI Control Register */
  #define REG_FLEXCOM0_SPI_MR                       (0xF8034404U) /**< \brief (FLEXCOM0) SPI Mode Register */
  #define REG_FLEXCOM0_SPI_RDR                      (0xF8034408U) /**< \brief (FLEXCOM0) SPI Receive Data Register */
  #define REG_FLEXCOM0_SPI_TDR                      (0xF803440CU) /**< \brief (FLEXCOM0) SPI Transmit Data Register */
  #define REG_FLEXCOM0_SPI_SR                       (0xF8034410U) /**< \brief (FLEXCOM0) SPI Status Register */
  #define REG_FLEXCOM0_SPI_IER                      (0xF8034414U) /**< \brief (FLEXCOM0) SPI Interrupt Enable Register */
  #define REG_FLEXCOM0_SPI_IDR                      (0xF8034418U) /**< \brief (FLEXCOM0) SPI Interrupt Disable Register */
  #define REG_FLEXCOM0_SPI_IMR                      (0xF803441CU) /**< \brief (FLEXCOM0) SPI Interrupt Mask Register */
  #define REG_FLEXCOM0_SPI_CSR                      (0xF8034430U) /**< \brief (FLEXCOM0) SPI Chip Select Register */
  #define REG_FLEXCOM0_SPI_FMR                      (0xF8034440U) /**< \brief (FLEXCOM0) SPI FIFO Mode Register */
  #define REG_FLEXCOM0_SPI_FLR                      (0xF8034444U) /**< \brief (FLEXCOM0) SPI FIFO Level Register */
  #define REG_FLEXCOM0_SPI_CMPR                     (0xF8034448U) /**< \brief (FLEXCOM0) SPI Comparison Register */
  #define REG_FLEXCOM0_SPI_WPMR                     (0xF80344E4U) /**< \brief (FLEXCOM0) SPI Write Protection Mode Register */
  #define REG_FLEXCOM0_SPI_WPSR                     (0xF80344E8U) /**< \brief (FLEXCOM0) SPI Write Protection Status Register */
  #define REG_FLEXCOM0_SPI_VERSION                  (0xF80344FCU) /**< \brief (FLEXCOM0) SPI Version Register */
  #define REG_FLEXCOM0_TWI_CR                       (0xF8034600U) /**< \brief (FLEXCOM0) TWI Control Register */
  #define REG_FLEXCOM0_TWI_MMR                      (0xF8034604U) /**< \brief (FLEXCOM0) TWI Master Mode Register */
  #define REG_FLEXCOM0_TWI_SMR                      (0xF8034608U) /**< \brief (FLEXCOM0) TWI Slave Mode Register */
  #define REG_FLEXCOM0_TWI_IADR                     (0xF803460CU) /**< \brief (FLEXCOM0) TWI Internal Address Register */
  #define REG_FLEXCOM0_TWI_CWGR                     (0xF8034610U) /**< \brief (FLEXCOM0) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM0_TWI_SR                       (0xF8034620U) /**< \brief (FLEXCOM0) TWI Status Register */
  #define REG_FLEXCOM0_TWI_IER                      (0xF8034624U) /**< \brief (FLEXCOM0) TWI Interrupt Enable Register */
  #define REG_FLEXCOM0_TWI_IDR                      (0xF8034628U) /**< \brief (FLEXCOM0) TWI Interrupt Disable Register */
  #define REG_FLEXCOM0_TWI_IMR                      (0xF803462CU) /**< \brief (FLEXCOM0) TWI Interrupt Mask Register */
  #define REG_FLEXCOM0_TWI_RHR                      (0xF8034630U) /**< \brief (FLEXCOM0) TWI Receive Holding Register */
  #define REG_FLEXCOM0_TWI_THR                      (0xF8034634U) /**< \brief (FLEXCOM0) TWI Transmit Holding Register */
  #define REG_FLEXCOM0_TWI_SMBTR                    (0xF8034638U) /**< \brief (FLEXCOM0) TWI SMBus Timing Register */
  #define REG_FLEXCOM0_TWI_ACR                      (0xF8034640U) /**< \brief (FLEXCOM0) TWI Alternative Command Register */
  #define REG_FLEXCOM0_TWI_FILTR                    (0xF8034644U) /**< \brief (FLEXCOM0) TWI Filter Register */
  #define REG_FLEXCOM0_TWI_SWMR                     (0xF803464CU) /**< \brief (FLEXCOM0) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM0_TWI_FMR                      (0xF8034650U) /**< \brief (FLEXCOM0) TWI FIFO Mode Register */
  #define REG_FLEXCOM0_TWI_FLR                      (0xF8034654U) /**< \brief (FLEXCOM0) TWI FIFO Level Register */
  #define REG_FLEXCOM0_TWI_FSR                      (0xF8034660U) /**< \brief (FLEXCOM0) TWI FIFO Status Register */
  #define REG_FLEXCOM0_TWI_FIER                     (0xF8034664U) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM0_TWI_FIDR                     (0xF8034668U) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM0_TWI_FIMR                     (0xF803466CU) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM0_TWI_DR                       (0xF80346D0U) /**< \brief (FLEXCOM0) TWI Debug Register */
  #define REG_FLEXCOM0_TWI_WPMR                     (0xF80346E4U) /**< \brief (FLEXCOM0) TWI Protection Mode Register */
  #define REG_FLEXCOM0_TWI_WPSR                     (0xF80346E8U) /**< \brief (FLEXCOM0) TWI Protection Status Register */
  #define REG_FLEXCOM0_TWI_VER                      (0xF80346FCU) /**< \brief (FLEXCOM0) TWI Version Register */
#else
  #define REG_FLEXCOM0_MR          (*(__IO uint32_t*)0xF8034000U) /**< \brief (FLEXCOM0) FLEXCOM Mode Register */
  #define REG_FLEXCOM0_RHR         (*(__I  uint32_t*)0xF8034010U) /**< \brief (FLEXCOM0) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM0_THR         (*(__IO uint32_t*)0xF8034020U) /**< \brief (FLEXCOM0) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM0_VERSION     (*(__I  uint32_t*)0xF80340FCU) /**< \brief (FLEXCOM0) FLEXCOM Version Register */
  #define REG_FLEXCOM0_US_CR       (*(__O  uint32_t*)0xF8034200U) /**< \brief (FLEXCOM0) USART Control Register */
  #define REG_FLEXCOM0_US_MR       (*(__IO uint32_t*)0xF8034204U) /**< \brief (FLEXCOM0) USART Mode Register */
  #define REG_FLEXCOM0_US_IER      (*(__O  uint32_t*)0xF8034208U) /**< \brief (FLEXCOM0) USART Interrupt Enable Register */
  #define REG_FLEXCOM0_US_IDR      (*(__O  uint32_t*)0xF803420CU) /**< \brief (FLEXCOM0) USART Interrupt Disable Register */
  #define REG_FLEXCOM0_US_IMR      (*(__I  uint32_t*)0xF8034210U) /**< \brief (FLEXCOM0) USART Interrupt Mask Register */
  #define REG_FLEXCOM0_US_CSR      (*(__I  uint32_t*)0xF8034214U) /**< \brief (FLEXCOM0) USART Channel Status Register */
  #define REG_FLEXCOM0_US_RHR      (*(__I  uint32_t*)0xF8034218U) /**< \brief (FLEXCOM0) USART Receive Holding Register */
  #define REG_FLEXCOM0_US_THR      (*(__O  uint32_t*)0xF803421CU) /**< \brief (FLEXCOM0) USART Transmit Holding Register */
  #define REG_FLEXCOM0_US_BRGR     (*(__IO uint32_t*)0xF8034220U) /**< \brief (FLEXCOM0) USART Baud Rate Generator Register */
  #define REG_FLEXCOM0_US_RTOR     (*(__IO uint32_t*)0xF8034224U) /**< \brief (FLEXCOM0) USART Receiver Timeout Register */
  #define REG_FLEXCOM0_US_TTGR     (*(__IO uint32_t*)0xF8034228U) /**< \brief (FLEXCOM0) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM0_US_FIDI     (*(__IO uint32_t*)0xF8034240U) /**< \brief (FLEXCOM0) USART FI DI Ratio Register */
  #define REG_FLEXCOM0_US_NER      (*(__I  uint32_t*)0xF8034244U) /**< \brief (FLEXCOM0) USART Number of Errors Register */
  #define REG_FLEXCOM0_US_IF       (*(__IO uint32_t*)0xF803424CU) /**< \brief (FLEXCOM0) USART IrDA Filter Register */
  #define REG_FLEXCOM0_US_MAN      (*(__IO uint32_t*)0xF8034250U) /**< \brief (FLEXCOM0) USART Manchester Configuration Register */
  #define REG_FLEXCOM0_US_LINMR    (*(__IO uint32_t*)0xF8034254U) /**< \brief (FLEXCOM0) USART LIN Mode Register */
  #define REG_FLEXCOM0_US_LINIR    (*(__IO uint32_t*)0xF8034258U) /**< \brief (FLEXCOM0) USART LIN Identifier Register */
  #define REG_FLEXCOM0_US_LINBRR   (*(__I  uint32_t*)0xF803425CU) /**< \brief (FLEXCOM0) USART LIN Baud Rate Register */
  #define REG_FLEXCOM0_US_CMPR     (*(__IO uint32_t*)0xF8034290U) /**< \brief (FLEXCOM0) USART Comparison Register */
  #define REG_FLEXCOM0_US_FMR      (*(__IO uint32_t*)0xF80342A0U) /**< \brief (FLEXCOM0) USART FIFO Mode Register */
  #define REG_FLEXCOM0_US_FESR     (*(__I  uint32_t*)0xF80342A4U) /**< \brief (FLEXCOM0) USART FIFO Level Register */
  #define REG_FLEXCOM0_US_FIER     (*(__O  uint32_t*)0xF80342A8U) /**< \brief (FLEXCOM0) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM0_US_FIDR     (*(__O  uint32_t*)0xF80342ACU) /**< \brief (FLEXCOM0) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM0_US_FIMR     (*(__I  uint32_t*)0xF80342B0U) /**< \brief (FLEXCOM0) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM0_US_FLR      (*(__I  uint32_t*)0xF80342B4U) /**< \brief (FLEXCOM0) USART FIFO Event Status Register */
  #define REG_FLEXCOM0_US_WPMR     (*(__IO uint32_t*)0xF80342E4U) /**< \brief (FLEXCOM0) USART Write Protection Mode Register */
  #define REG_FLEXCOM0_US_WPSR     (*(__I  uint32_t*)0xF80342E8U) /**< \brief (FLEXCOM0) USART Write Protection Status Register */
  #define REG_FLEXCOM0_US_VERSION  (*(__I  uint32_t*)0xF80342FCU) /**< \brief (FLEXCOM0) USART Version Register */
  #define REG_FLEXCOM0_SPI_CR      (*(__O  uint32_t*)0xF8034400U) /**< \brief (FLEXCOM0) SPI Control Register */
  #define REG_FLEXCOM0_SPI_MR      (*(__IO uint32_t*)0xF8034404U) /**< \brief (FLEXCOM0) SPI Mode Register */
  #define REG_FLEXCOM0_SPI_RDR     (*(__I  uint32_t*)0xF8034408U) /**< \brief (FLEXCOM0) SPI Receive Data Register */
  #define REG_FLEXCOM0_SPI_TDR     (*(__O  uint32_t*)0xF803440CU) /**< \brief (FLEXCOM0) SPI Transmit Data Register */
  #define REG_FLEXCOM0_SPI_SR      (*(__I  uint32_t*)0xF8034410U) /**< \brief (FLEXCOM0) SPI Status Register */
  #define REG_FLEXCOM0_SPI_IER     (*(__O  uint32_t*)0xF8034414U) /**< \brief (FLEXCOM0) SPI Interrupt Enable Register */
  #define REG_FLEXCOM0_SPI_IDR     (*(__O  uint32_t*)0xF8034418U) /**< \brief (FLEXCOM0) SPI Interrupt Disable Register */
  #define REG_FLEXCOM0_SPI_IMR     (*(__I  uint32_t*)0xF803441CU) /**< \brief (FLEXCOM0) SPI Interrupt Mask Register */
  #define REG_FLEXCOM0_SPI_CSR     (*(__IO uint32_t*)0xF8034430U) /**< \brief (FLEXCOM0) SPI Chip Select Register */
  #define REG_FLEXCOM0_SPI_FMR     (*(__IO uint32_t*)0xF8034440U) /**< \brief (FLEXCOM0) SPI FIFO Mode Register */
  #define REG_FLEXCOM0_SPI_FLR     (*(__I  uint32_t*)0xF8034444U) /**< \brief (FLEXCOM0) SPI FIFO Level Register */
  #define REG_FLEXCOM0_SPI_CMPR    (*(__IO uint32_t*)0xF8034448U) /**< \brief (FLEXCOM0) SPI Comparison Register */
  #define REG_FLEXCOM0_SPI_WPMR    (*(__IO uint32_t*)0xF80344E4U) /**< \brief (FLEXCOM0) SPI Write Protection Mode Register */
  #define REG_FLEXCOM0_SPI_WPSR    (*(__I  uint32_t*)0xF80344E8U) /**< \brief (FLEXCOM0) SPI Write Protection Status Register */
  #define REG_FLEXCOM0_SPI_VERSION (*(__I  uint32_t*)0xF80344FCU) /**< \brief (FLEXCOM0) SPI Version Register */
  #define REG_FLEXCOM0_TWI_CR      (*(__O  uint32_t*)0xF8034600U) /**< \brief (FLEXCOM0) TWI Control Register */
  #define REG_FLEXCOM0_TWI_MMR     (*(__IO uint32_t*)0xF8034604U) /**< \brief (FLEXCOM0) TWI Master Mode Register */
  #define REG_FLEXCOM0_TWI_SMR     (*(__IO uint32_t*)0xF8034608U) /**< \brief (FLEXCOM0) TWI Slave Mode Register */
  #define REG_FLEXCOM0_TWI_IADR    (*(__IO uint32_t*)0xF803460CU) /**< \brief (FLEXCOM0) TWI Internal Address Register */
  #define REG_FLEXCOM0_TWI_CWGR    (*(__IO uint32_t*)0xF8034610U) /**< \brief (FLEXCOM0) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM0_TWI_SR      (*(__I  uint32_t*)0xF8034620U) /**< \brief (FLEXCOM0) TWI Status Register */
  #define REG_FLEXCOM0_TWI_IER     (*(__O  uint32_t*)0xF8034624U) /**< \brief (FLEXCOM0) TWI Interrupt Enable Register */
  #define REG_FLEXCOM0_TWI_IDR     (*(__O  uint32_t*)0xF8034628U) /**< \brief (FLEXCOM0) TWI Interrupt Disable Register */
  #define REG_FLEXCOM0_TWI_IMR     (*(__I  uint32_t*)0xF803462CU) /**< \brief (FLEXCOM0) TWI Interrupt Mask Register */
  #define REG_FLEXCOM0_TWI_RHR     (*(__I  uint32_t*)0xF8034630U) /**< \brief (FLEXCOM0) TWI Receive Holding Register */
  #define REG_FLEXCOM0_TWI_THR     (*(__O  uint32_t*)0xF8034634U) /**< \brief (FLEXCOM0) TWI Transmit Holding Register */
  #define REG_FLEXCOM0_TWI_SMBTR   (*(__IO uint32_t*)0xF8034638U) /**< \brief (FLEXCOM0) TWI SMBus Timing Register */
  #define REG_FLEXCOM0_TWI_ACR     (*(__IO uint32_t*)0xF8034640U) /**< \brief (FLEXCOM0) TWI Alternative Command Register */
  #define REG_FLEXCOM0_TWI_FILTR   (*(__IO uint32_t*)0xF8034644U) /**< \brief (FLEXCOM0) TWI Filter Register */
  #define REG_FLEXCOM0_TWI_SWMR    (*(__IO uint32_t*)0xF803464CU) /**< \brief (FLEXCOM0) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM0_TWI_FMR     (*(__IO uint32_t*)0xF8034650U) /**< \brief (FLEXCOM0) TWI FIFO Mode Register */
  #define REG_FLEXCOM0_TWI_FLR     (*(__I  uint32_t*)0xF8034654U) /**< \brief (FLEXCOM0) TWI FIFO Level Register */
  #define REG_FLEXCOM0_TWI_FSR     (*(__I  uint32_t*)0xF8034660U) /**< \brief (FLEXCOM0) TWI FIFO Status Register */
  #define REG_FLEXCOM0_TWI_FIER    (*(__O  uint32_t*)0xF8034664U) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM0_TWI_FIDR    (*(__O  uint32_t*)0xF8034668U) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM0_TWI_FIMR    (*(__I  uint32_t*)0xF803466CU) /**< \brief (FLEXCOM0) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM0_TWI_DR      (*(__I  uint32_t*)0xF80346D0U) /**< \brief (FLEXCOM0) TWI Debug Register */
  #define REG_FLEXCOM0_TWI_WPMR    (*(__IO uint32_t*)0xF80346E4U) /**< \brief (FLEXCOM0) TWI Protection Mode Register */
  #define REG_FLEXCOM0_TWI_WPSR    (*(__I  uint32_t*)0xF80346E8U) /**< \brief (FLEXCOM0) TWI Protection Status Register */
  #define REG_FLEXCOM0_TWI_VER     (*(__I  uint32_t*)0xF80346FCU) /**< \brief (FLEXCOM0) TWI Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_FLEXCOM0_INSTANCE_ */
