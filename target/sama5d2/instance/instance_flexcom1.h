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

#ifndef _SAMA5D2_FLEXCOM1_INSTANCE_
#define _SAMA5D2_FLEXCOM1_INSTANCE_

/* ========== Register definition for FLEXCOM1 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM1_MR                           (0xF8038000U) /**< \brief (FLEXCOM1) FLEXCOM Mode Register */
  #define REG_FLEXCOM1_RHR                          (0xF8038010U) /**< \brief (FLEXCOM1) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM1_THR                          (0xF8038020U) /**< \brief (FLEXCOM1) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM1_VERSION                      (0xF80380FCU) /**< \brief (FLEXCOM1) FLEXCOM Version Register */
  #define REG_FLEXCOM1_US_CR                        (0xF8038200U) /**< \brief (FLEXCOM1) USART Control Register */
  #define REG_FLEXCOM1_US_MR                        (0xF8038204U) /**< \brief (FLEXCOM1) USART Mode Register */
  #define REG_FLEXCOM1_US_IER                       (0xF8038208U) /**< \brief (FLEXCOM1) USART Interrupt Enable Register */
  #define REG_FLEXCOM1_US_IDR                       (0xF803820CU) /**< \brief (FLEXCOM1) USART Interrupt Disable Register */
  #define REG_FLEXCOM1_US_IMR                       (0xF8038210U) /**< \brief (FLEXCOM1) USART Interrupt Mask Register */
  #define REG_FLEXCOM1_US_CSR                       (0xF8038214U) /**< \brief (FLEXCOM1) USART Channel Status Register */
  #define REG_FLEXCOM1_US_RHR                       (0xF8038218U) /**< \brief (FLEXCOM1) USART Receive Holding Register */
  #define REG_FLEXCOM1_US_THR                       (0xF803821CU) /**< \brief (FLEXCOM1) USART Transmit Holding Register */
  #define REG_FLEXCOM1_US_BRGR                      (0xF8038220U) /**< \brief (FLEXCOM1) USART Baud Rate Generator Register */
  #define REG_FLEXCOM1_US_RTOR                      (0xF8038224U) /**< \brief (FLEXCOM1) USART Receiver Timeout Register */
  #define REG_FLEXCOM1_US_TTGR                      (0xF8038228U) /**< \brief (FLEXCOM1) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM1_US_FIDI                      (0xF8038240U) /**< \brief (FLEXCOM1) USART FI DI Ratio Register */
  #define REG_FLEXCOM1_US_NER                       (0xF8038244U) /**< \brief (FLEXCOM1) USART Number of Errors Register */
  #define REG_FLEXCOM1_US_IF                        (0xF803824CU) /**< \brief (FLEXCOM1) USART IrDA Filter Register */
  #define REG_FLEXCOM1_US_MAN                       (0xF8038250U) /**< \brief (FLEXCOM1) USART Manchester Configuration Register */
  #define REG_FLEXCOM1_US_LINMR                     (0xF8038254U) /**< \brief (FLEXCOM1) USART LIN Mode Register */
  #define REG_FLEXCOM1_US_LINIR                     (0xF8038258U) /**< \brief (FLEXCOM1) USART LIN Identifier Register */
  #define REG_FLEXCOM1_US_LINBRR                    (0xF803825CU) /**< \brief (FLEXCOM1) USART LIN Baud Rate Register */
  #define REG_FLEXCOM1_US_CMPR                      (0xF8038290U) /**< \brief (FLEXCOM1) USART Comparison Register */
  #define REG_FLEXCOM1_US_FMR                       (0xF80382A0U) /**< \brief (FLEXCOM1) USART FIFO Mode Register */
  #define REG_FLEXCOM1_US_FESR                      (0xF80382A4U) /**< \brief (FLEXCOM1) USART FIFO Level Register */
  #define REG_FLEXCOM1_US_FIER                      (0xF80382A8U) /**< \brief (FLEXCOM1) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM1_US_FIDR                      (0xF80382ACU) /**< \brief (FLEXCOM1) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM1_US_FIMR                      (0xF80382B0U) /**< \brief (FLEXCOM1) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM1_US_FLR                       (0xF80382B4U) /**< \brief (FLEXCOM1) USART FIFO Event Status Register */
  #define REG_FLEXCOM1_US_WPMR                      (0xF80382E4U) /**< \brief (FLEXCOM1) USART Write Protection Mode Register */
  #define REG_FLEXCOM1_US_WPSR                      (0xF80382E8U) /**< \brief (FLEXCOM1) USART Write Protection Status Register */
  #define REG_FLEXCOM1_US_VERSION                   (0xF80382FCU) /**< \brief (FLEXCOM1) USART Version Register */
  #define REG_FLEXCOM1_SPI_CR                       (0xF8038400U) /**< \brief (FLEXCOM1) SPI Control Register */
  #define REG_FLEXCOM1_SPI_MR                       (0xF8038404U) /**< \brief (FLEXCOM1) SPI Mode Register */
  #define REG_FLEXCOM1_SPI_RDR                      (0xF8038408U) /**< \brief (FLEXCOM1) SPI Receive Data Register */
  #define REG_FLEXCOM1_SPI_TDR                      (0xF803840CU) /**< \brief (FLEXCOM1) SPI Transmit Data Register */
  #define REG_FLEXCOM1_SPI_SR                       (0xF8038410U) /**< \brief (FLEXCOM1) SPI Status Register */
  #define REG_FLEXCOM1_SPI_IER                      (0xF8038414U) /**< \brief (FLEXCOM1) SPI Interrupt Enable Register */
  #define REG_FLEXCOM1_SPI_IDR                      (0xF8038418U) /**< \brief (FLEXCOM1) SPI Interrupt Disable Register */
  #define REG_FLEXCOM1_SPI_IMR                      (0xF803841CU) /**< \brief (FLEXCOM1) SPI Interrupt Mask Register */
  #define REG_FLEXCOM1_SPI_CSR                      (0xF8038430U) /**< \brief (FLEXCOM1) SPI Chip Select Register */
  #define REG_FLEXCOM1_SPI_FMR                      (0xF8038440U) /**< \brief (FLEXCOM1) SPI FIFO Mode Register */
  #define REG_FLEXCOM1_SPI_FLR                      (0xF8038444U) /**< \brief (FLEXCOM1) SPI FIFO Level Register */
  #define REG_FLEXCOM1_SPI_CMPR                     (0xF8038448U) /**< \brief (FLEXCOM1) SPI Comparison Register */
  #define REG_FLEXCOM1_SPI_WPMR                     (0xF80384E4U) /**< \brief (FLEXCOM1) SPI Write Protection Mode Register */
  #define REG_FLEXCOM1_SPI_WPSR                     (0xF80384E8U) /**< \brief (FLEXCOM1) SPI Write Protection Status Register */
  #define REG_FLEXCOM1_SPI_VERSION                  (0xF80384FCU) /**< \brief (FLEXCOM1) SPI Version Register */
  #define REG_FLEXCOM1_TWI_CR                       (0xF8038600U) /**< \brief (FLEXCOM1) TWI Control Register */
  #define REG_FLEXCOM1_TWI_MMR                      (0xF8038604U) /**< \brief (FLEXCOM1) TWI Master Mode Register */
  #define REG_FLEXCOM1_TWI_SMR                      (0xF8038608U) /**< \brief (FLEXCOM1) TWI Slave Mode Register */
  #define REG_FLEXCOM1_TWI_IADR                     (0xF803860CU) /**< \brief (FLEXCOM1) TWI Internal Address Register */
  #define REG_FLEXCOM1_TWI_CWGR                     (0xF8038610U) /**< \brief (FLEXCOM1) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM1_TWI_SR                       (0xF8038620U) /**< \brief (FLEXCOM1) TWI Status Register */
  #define REG_FLEXCOM1_TWI_IER                      (0xF8038624U) /**< \brief (FLEXCOM1) TWI Interrupt Enable Register */
  #define REG_FLEXCOM1_TWI_IDR                      (0xF8038628U) /**< \brief (FLEXCOM1) TWI Interrupt Disable Register */
  #define REG_FLEXCOM1_TWI_IMR                      (0xF803862CU) /**< \brief (FLEXCOM1) TWI Interrupt Mask Register */
  #define REG_FLEXCOM1_TWI_RHR                      (0xF8038630U) /**< \brief (FLEXCOM1) TWI Receive Holding Register */
  #define REG_FLEXCOM1_TWI_THR                      (0xF8038634U) /**< \brief (FLEXCOM1) TWI Transmit Holding Register */
  #define REG_FLEXCOM1_TWI_SMBTR                    (0xF8038638U) /**< \brief (FLEXCOM1) TWI SMBus Timing Register */
  #define REG_FLEXCOM1_TWI_ACR                      (0xF8038640U) /**< \brief (FLEXCOM1) TWI Alternative Command Register */
  #define REG_FLEXCOM1_TWI_FILTR                    (0xF8038644U) /**< \brief (FLEXCOM1) TWI Filter Register */
  #define REG_FLEXCOM1_TWI_SWMR                     (0xF803864CU) /**< \brief (FLEXCOM1) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM1_TWI_FMR                      (0xF8038650U) /**< \brief (FLEXCOM1) TWI FIFO Mode Register */
  #define REG_FLEXCOM1_TWI_FLR                      (0xF8038654U) /**< \brief (FLEXCOM1) TWI FIFO Level Register */
  #define REG_FLEXCOM1_TWI_FSR                      (0xF8038660U) /**< \brief (FLEXCOM1) TWI FIFO Status Register */
  #define REG_FLEXCOM1_TWI_FIER                     (0xF8038664U) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM1_TWI_FIDR                     (0xF8038668U) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM1_TWI_FIMR                     (0xF803866CU) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM1_TWI_DR                       (0xF80386D0U) /**< \brief (FLEXCOM1) TWI Debug Register */
  #define REG_FLEXCOM1_TWI_WPMR                     (0xF80386E4U) /**< \brief (FLEXCOM1) TWI Protection Mode Register */
  #define REG_FLEXCOM1_TWI_WPSR                     (0xF80386E8U) /**< \brief (FLEXCOM1) TWI Protection Status Register */
  #define REG_FLEXCOM1_TWI_VER                      (0xF80386FCU) /**< \brief (FLEXCOM1) TWI Version Register */
#else
  #define REG_FLEXCOM1_MR          (*(__IO uint32_t*)0xF8038000U) /**< \brief (FLEXCOM1) FLEXCOM Mode Register */
  #define REG_FLEXCOM1_RHR         (*(__I  uint32_t*)0xF8038010U) /**< \brief (FLEXCOM1) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM1_THR         (*(__IO uint32_t*)0xF8038020U) /**< \brief (FLEXCOM1) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM1_VERSION     (*(__I  uint32_t*)0xF80380FCU) /**< \brief (FLEXCOM1) FLEXCOM Version Register */
  #define REG_FLEXCOM1_US_CR       (*(__O  uint32_t*)0xF8038200U) /**< \brief (FLEXCOM1) USART Control Register */
  #define REG_FLEXCOM1_US_MR       (*(__IO uint32_t*)0xF8038204U) /**< \brief (FLEXCOM1) USART Mode Register */
  #define REG_FLEXCOM1_US_IER      (*(__O  uint32_t*)0xF8038208U) /**< \brief (FLEXCOM1) USART Interrupt Enable Register */
  #define REG_FLEXCOM1_US_IDR      (*(__O  uint32_t*)0xF803820CU) /**< \brief (FLEXCOM1) USART Interrupt Disable Register */
  #define REG_FLEXCOM1_US_IMR      (*(__I  uint32_t*)0xF8038210U) /**< \brief (FLEXCOM1) USART Interrupt Mask Register */
  #define REG_FLEXCOM1_US_CSR      (*(__I  uint32_t*)0xF8038214U) /**< \brief (FLEXCOM1) USART Channel Status Register */
  #define REG_FLEXCOM1_US_RHR      (*(__I  uint32_t*)0xF8038218U) /**< \brief (FLEXCOM1) USART Receive Holding Register */
  #define REG_FLEXCOM1_US_THR      (*(__O  uint32_t*)0xF803821CU) /**< \brief (FLEXCOM1) USART Transmit Holding Register */
  #define REG_FLEXCOM1_US_BRGR     (*(__IO uint32_t*)0xF8038220U) /**< \brief (FLEXCOM1) USART Baud Rate Generator Register */
  #define REG_FLEXCOM1_US_RTOR     (*(__IO uint32_t*)0xF8038224U) /**< \brief (FLEXCOM1) USART Receiver Timeout Register */
  #define REG_FLEXCOM1_US_TTGR     (*(__IO uint32_t*)0xF8038228U) /**< \brief (FLEXCOM1) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM1_US_FIDI     (*(__IO uint32_t*)0xF8038240U) /**< \brief (FLEXCOM1) USART FI DI Ratio Register */
  #define REG_FLEXCOM1_US_NER      (*(__I  uint32_t*)0xF8038244U) /**< \brief (FLEXCOM1) USART Number of Errors Register */
  #define REG_FLEXCOM1_US_IF       (*(__IO uint32_t*)0xF803824CU) /**< \brief (FLEXCOM1) USART IrDA Filter Register */
  #define REG_FLEXCOM1_US_MAN      (*(__IO uint32_t*)0xF8038250U) /**< \brief (FLEXCOM1) USART Manchester Configuration Register */
  #define REG_FLEXCOM1_US_LINMR    (*(__IO uint32_t*)0xF8038254U) /**< \brief (FLEXCOM1) USART LIN Mode Register */
  #define REG_FLEXCOM1_US_LINIR    (*(__IO uint32_t*)0xF8038258U) /**< \brief (FLEXCOM1) USART LIN Identifier Register */
  #define REG_FLEXCOM1_US_LINBRR   (*(__I  uint32_t*)0xF803825CU) /**< \brief (FLEXCOM1) USART LIN Baud Rate Register */
  #define REG_FLEXCOM1_US_CMPR     (*(__IO uint32_t*)0xF8038290U) /**< \brief (FLEXCOM1) USART Comparison Register */
  #define REG_FLEXCOM1_US_FMR      (*(__IO uint32_t*)0xF80382A0U) /**< \brief (FLEXCOM1) USART FIFO Mode Register */
  #define REG_FLEXCOM1_US_FESR     (*(__I  uint32_t*)0xF80382A4U) /**< \brief (FLEXCOM1) USART FIFO Level Register */
  #define REG_FLEXCOM1_US_FIER     (*(__O  uint32_t*)0xF80382A8U) /**< \brief (FLEXCOM1) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM1_US_FIDR     (*(__O  uint32_t*)0xF80382ACU) /**< \brief (FLEXCOM1) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM1_US_FIMR     (*(__I  uint32_t*)0xF80382B0U) /**< \brief (FLEXCOM1) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM1_US_FLR      (*(__I  uint32_t*)0xF80382B4U) /**< \brief (FLEXCOM1) USART FIFO Event Status Register */
  #define REG_FLEXCOM1_US_WPMR     (*(__IO uint32_t*)0xF80382E4U) /**< \brief (FLEXCOM1) USART Write Protection Mode Register */
  #define REG_FLEXCOM1_US_WPSR     (*(__I  uint32_t*)0xF80382E8U) /**< \brief (FLEXCOM1) USART Write Protection Status Register */
  #define REG_FLEXCOM1_US_VERSION  (*(__I  uint32_t*)0xF80382FCU) /**< \brief (FLEXCOM1) USART Version Register */
  #define REG_FLEXCOM1_SPI_CR      (*(__O  uint32_t*)0xF8038400U) /**< \brief (FLEXCOM1) SPI Control Register */
  #define REG_FLEXCOM1_SPI_MR      (*(__IO uint32_t*)0xF8038404U) /**< \brief (FLEXCOM1) SPI Mode Register */
  #define REG_FLEXCOM1_SPI_RDR     (*(__I  uint32_t*)0xF8038408U) /**< \brief (FLEXCOM1) SPI Receive Data Register */
  #define REG_FLEXCOM1_SPI_TDR     (*(__O  uint32_t*)0xF803840CU) /**< \brief (FLEXCOM1) SPI Transmit Data Register */
  #define REG_FLEXCOM1_SPI_SR      (*(__I  uint32_t*)0xF8038410U) /**< \brief (FLEXCOM1) SPI Status Register */
  #define REG_FLEXCOM1_SPI_IER     (*(__O  uint32_t*)0xF8038414U) /**< \brief (FLEXCOM1) SPI Interrupt Enable Register */
  #define REG_FLEXCOM1_SPI_IDR     (*(__O  uint32_t*)0xF8038418U) /**< \brief (FLEXCOM1) SPI Interrupt Disable Register */
  #define REG_FLEXCOM1_SPI_IMR     (*(__I  uint32_t*)0xF803841CU) /**< \brief (FLEXCOM1) SPI Interrupt Mask Register */
  #define REG_FLEXCOM1_SPI_CSR     (*(__IO uint32_t*)0xF8038430U) /**< \brief (FLEXCOM1) SPI Chip Select Register */
  #define REG_FLEXCOM1_SPI_FMR     (*(__IO uint32_t*)0xF8038440U) /**< \brief (FLEXCOM1) SPI FIFO Mode Register */
  #define REG_FLEXCOM1_SPI_FLR     (*(__I  uint32_t*)0xF8038444U) /**< \brief (FLEXCOM1) SPI FIFO Level Register */
  #define REG_FLEXCOM1_SPI_CMPR    (*(__IO uint32_t*)0xF8038448U) /**< \brief (FLEXCOM1) SPI Comparison Register */
  #define REG_FLEXCOM1_SPI_WPMR    (*(__IO uint32_t*)0xF80384E4U) /**< \brief (FLEXCOM1) SPI Write Protection Mode Register */
  #define REG_FLEXCOM1_SPI_WPSR    (*(__I  uint32_t*)0xF80384E8U) /**< \brief (FLEXCOM1) SPI Write Protection Status Register */
  #define REG_FLEXCOM1_SPI_VERSION (*(__I  uint32_t*)0xF80384FCU) /**< \brief (FLEXCOM1) SPI Version Register */
  #define REG_FLEXCOM1_TWI_CR      (*(__O  uint32_t*)0xF8038600U) /**< \brief (FLEXCOM1) TWI Control Register */
  #define REG_FLEXCOM1_TWI_MMR     (*(__IO uint32_t*)0xF8038604U) /**< \brief (FLEXCOM1) TWI Master Mode Register */
  #define REG_FLEXCOM1_TWI_SMR     (*(__IO uint32_t*)0xF8038608U) /**< \brief (FLEXCOM1) TWI Slave Mode Register */
  #define REG_FLEXCOM1_TWI_IADR    (*(__IO uint32_t*)0xF803860CU) /**< \brief (FLEXCOM1) TWI Internal Address Register */
  #define REG_FLEXCOM1_TWI_CWGR    (*(__IO uint32_t*)0xF8038610U) /**< \brief (FLEXCOM1) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM1_TWI_SR      (*(__I  uint32_t*)0xF8038620U) /**< \brief (FLEXCOM1) TWI Status Register */
  #define REG_FLEXCOM1_TWI_IER     (*(__O  uint32_t*)0xF8038624U) /**< \brief (FLEXCOM1) TWI Interrupt Enable Register */
  #define REG_FLEXCOM1_TWI_IDR     (*(__O  uint32_t*)0xF8038628U) /**< \brief (FLEXCOM1) TWI Interrupt Disable Register */
  #define REG_FLEXCOM1_TWI_IMR     (*(__I  uint32_t*)0xF803862CU) /**< \brief (FLEXCOM1) TWI Interrupt Mask Register */
  #define REG_FLEXCOM1_TWI_RHR     (*(__I  uint32_t*)0xF8038630U) /**< \brief (FLEXCOM1) TWI Receive Holding Register */
  #define REG_FLEXCOM1_TWI_THR     (*(__O  uint32_t*)0xF8038634U) /**< \brief (FLEXCOM1) TWI Transmit Holding Register */
  #define REG_FLEXCOM1_TWI_SMBTR   (*(__IO uint32_t*)0xF8038638U) /**< \brief (FLEXCOM1) TWI SMBus Timing Register */
  #define REG_FLEXCOM1_TWI_ACR     (*(__IO uint32_t*)0xF8038640U) /**< \brief (FLEXCOM1) TWI Alternative Command Register */
  #define REG_FLEXCOM1_TWI_FILTR   (*(__IO uint32_t*)0xF8038644U) /**< \brief (FLEXCOM1) TWI Filter Register */
  #define REG_FLEXCOM1_TWI_SWMR    (*(__IO uint32_t*)0xF803864CU) /**< \brief (FLEXCOM1) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM1_TWI_FMR     (*(__IO uint32_t*)0xF8038650U) /**< \brief (FLEXCOM1) TWI FIFO Mode Register */
  #define REG_FLEXCOM1_TWI_FLR     (*(__I  uint32_t*)0xF8038654U) /**< \brief (FLEXCOM1) TWI FIFO Level Register */
  #define REG_FLEXCOM1_TWI_FSR     (*(__I  uint32_t*)0xF8038660U) /**< \brief (FLEXCOM1) TWI FIFO Status Register */
  #define REG_FLEXCOM1_TWI_FIER    (*(__O  uint32_t*)0xF8038664U) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM1_TWI_FIDR    (*(__O  uint32_t*)0xF8038668U) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM1_TWI_FIMR    (*(__I  uint32_t*)0xF803866CU) /**< \brief (FLEXCOM1) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM1_TWI_DR      (*(__I  uint32_t*)0xF80386D0U) /**< \brief (FLEXCOM1) TWI Debug Register */
  #define REG_FLEXCOM1_TWI_WPMR    (*(__IO uint32_t*)0xF80386E4U) /**< \brief (FLEXCOM1) TWI Protection Mode Register */
  #define REG_FLEXCOM1_TWI_WPSR    (*(__I  uint32_t*)0xF80386E8U) /**< \brief (FLEXCOM1) TWI Protection Status Register */
  #define REG_FLEXCOM1_TWI_VER     (*(__I  uint32_t*)0xF80386FCU) /**< \brief (FLEXCOM1) TWI Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_FLEXCOM1_INSTANCE_ */
