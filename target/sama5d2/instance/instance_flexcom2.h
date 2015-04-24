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

#ifndef _SAMA5D2_FLEXCOM2_INSTANCE_
#define _SAMA5D2_FLEXCOM2_INSTANCE_

/* ========== Register definition for FLEXCOM2 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM2_MR                           (0xFC010000U) /**< \brief (FLEXCOM2) FLEXCOM Mode Register */
  #define REG_FLEXCOM2_RHR                          (0xFC010010U) /**< \brief (FLEXCOM2) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM2_THR                          (0xFC010020U) /**< \brief (FLEXCOM2) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM2_VERSION                      (0xFC0100FCU) /**< \brief (FLEXCOM2) FLEXCOM Version Register */
  #define REG_FLEXCOM2_US_CR                        (0xFC010200U) /**< \brief (FLEXCOM2) USART Control Register */
  #define REG_FLEXCOM2_US_MR                        (0xFC010204U) /**< \brief (FLEXCOM2) USART Mode Register */
  #define REG_FLEXCOM2_US_IER                       (0xFC010208U) /**< \brief (FLEXCOM2) USART Interrupt Enable Register */
  #define REG_FLEXCOM2_US_IDR                       (0xFC01020CU) /**< \brief (FLEXCOM2) USART Interrupt Disable Register */
  #define REG_FLEXCOM2_US_IMR                       (0xFC010210U) /**< \brief (FLEXCOM2) USART Interrupt Mask Register */
  #define REG_FLEXCOM2_US_CSR                       (0xFC010214U) /**< \brief (FLEXCOM2) USART Channel Status Register */
  #define REG_FLEXCOM2_US_RHR                       (0xFC010218U) /**< \brief (FLEXCOM2) USART Receive Holding Register */
  #define REG_FLEXCOM2_US_THR                       (0xFC01021CU) /**< \brief (FLEXCOM2) USART Transmit Holding Register */
  #define REG_FLEXCOM2_US_BRGR                      (0xFC010220U) /**< \brief (FLEXCOM2) USART Baud Rate Generator Register */
  #define REG_FLEXCOM2_US_RTOR                      (0xFC010224U) /**< \brief (FLEXCOM2) USART Receiver Timeout Register */
  #define REG_FLEXCOM2_US_TTGR                      (0xFC010228U) /**< \brief (FLEXCOM2) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM2_US_FIDI                      (0xFC010240U) /**< \brief (FLEXCOM2) USART FI DI Ratio Register */
  #define REG_FLEXCOM2_US_NER                       (0xFC010244U) /**< \brief (FLEXCOM2) USART Number of Errors Register */
  #define REG_FLEXCOM2_US_IF                        (0xFC01024CU) /**< \brief (FLEXCOM2) USART IrDA Filter Register */
  #define REG_FLEXCOM2_US_MAN                       (0xFC010250U) /**< \brief (FLEXCOM2) USART Manchester Configuration Register */
  #define REG_FLEXCOM2_US_LINMR                     (0xFC010254U) /**< \brief (FLEXCOM2) USART LIN Mode Register */
  #define REG_FLEXCOM2_US_LINIR                     (0xFC010258U) /**< \brief (FLEXCOM2) USART LIN Identifier Register */
  #define REG_FLEXCOM2_US_LINBRR                    (0xFC01025CU) /**< \brief (FLEXCOM2) USART LIN Baud Rate Register */
  #define REG_FLEXCOM2_US_CMPR                      (0xFC010290U) /**< \brief (FLEXCOM2) USART Comparison Register */
  #define REG_FLEXCOM2_US_FMR                       (0xFC0102A0U) /**< \brief (FLEXCOM2) USART FIFO Mode Register */
  #define REG_FLEXCOM2_US_FESR                      (0xFC0102A4U) /**< \brief (FLEXCOM2) USART FIFO Level Register */
  #define REG_FLEXCOM2_US_FIER                      (0xFC0102A8U) /**< \brief (FLEXCOM2) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM2_US_FIDR                      (0xFC0102ACU) /**< \brief (FLEXCOM2) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM2_US_FIMR                      (0xFC0102B0U) /**< \brief (FLEXCOM2) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM2_US_FLR                       (0xFC0102B4U) /**< \brief (FLEXCOM2) USART FIFO Event Status Register */
  #define REG_FLEXCOM2_US_WPMR                      (0xFC0102E4U) /**< \brief (FLEXCOM2) USART Write Protection Mode Register */
  #define REG_FLEXCOM2_US_WPSR                      (0xFC0102E8U) /**< \brief (FLEXCOM2) USART Write Protection Status Register */
  #define REG_FLEXCOM2_US_VERSION                   (0xFC0102FCU) /**< \brief (FLEXCOM2) USART Version Register */
  #define REG_FLEXCOM2_SPI_CR                       (0xFC010400U) /**< \brief (FLEXCOM2) SPI Control Register */
  #define REG_FLEXCOM2_SPI_MR                       (0xFC010404U) /**< \brief (FLEXCOM2) SPI Mode Register */
  #define REG_FLEXCOM2_SPI_RDR                      (0xFC010408U) /**< \brief (FLEXCOM2) SPI Receive Data Register */
  #define REG_FLEXCOM2_SPI_TDR                      (0xFC01040CU) /**< \brief (FLEXCOM2) SPI Transmit Data Register */
  #define REG_FLEXCOM2_SPI_SR                       (0xFC010410U) /**< \brief (FLEXCOM2) SPI Status Register */
  #define REG_FLEXCOM2_SPI_IER                      (0xFC010414U) /**< \brief (FLEXCOM2) SPI Interrupt Enable Register */
  #define REG_FLEXCOM2_SPI_IDR                      (0xFC010418U) /**< \brief (FLEXCOM2) SPI Interrupt Disable Register */
  #define REG_FLEXCOM2_SPI_IMR                      (0xFC01041CU) /**< \brief (FLEXCOM2) SPI Interrupt Mask Register */
  #define REG_FLEXCOM2_SPI_CSR                      (0xFC010430U) /**< \brief (FLEXCOM2) SPI Chip Select Register */
  #define REG_FLEXCOM2_SPI_FMR                      (0xFC010440U) /**< \brief (FLEXCOM2) SPI FIFO Mode Register */
  #define REG_FLEXCOM2_SPI_FLR                      (0xFC010444U) /**< \brief (FLEXCOM2) SPI FIFO Level Register */
  #define REG_FLEXCOM2_SPI_CMPR                     (0xFC010448U) /**< \brief (FLEXCOM2) SPI Comparison Register */
  #define REG_FLEXCOM2_SPI_WPMR                     (0xFC0104E4U) /**< \brief (FLEXCOM2) SPI Write Protection Mode Register */
  #define REG_FLEXCOM2_SPI_WPSR                     (0xFC0104E8U) /**< \brief (FLEXCOM2) SPI Write Protection Status Register */
  #define REG_FLEXCOM2_SPI_VERSION                  (0xFC0104FCU) /**< \brief (FLEXCOM2) SPI Version Register */
  #define REG_FLEXCOM2_TWI_CR                       (0xFC010600U) /**< \brief (FLEXCOM2) TWI Control Register */
  #define REG_FLEXCOM2_TWI_MMR                      (0xFC010604U) /**< \brief (FLEXCOM2) TWI Master Mode Register */
  #define REG_FLEXCOM2_TWI_SMR                      (0xFC010608U) /**< \brief (FLEXCOM2) TWI Slave Mode Register */
  #define REG_FLEXCOM2_TWI_IADR                     (0xFC01060CU) /**< \brief (FLEXCOM2) TWI Internal Address Register */
  #define REG_FLEXCOM2_TWI_CWGR                     (0xFC010610U) /**< \brief (FLEXCOM2) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM2_TWI_SR                       (0xFC010620U) /**< \brief (FLEXCOM2) TWI Status Register */
  #define REG_FLEXCOM2_TWI_IER                      (0xFC010624U) /**< \brief (FLEXCOM2) TWI Interrupt Enable Register */
  #define REG_FLEXCOM2_TWI_IDR                      (0xFC010628U) /**< \brief (FLEXCOM2) TWI Interrupt Disable Register */
  #define REG_FLEXCOM2_TWI_IMR                      (0xFC01062CU) /**< \brief (FLEXCOM2) TWI Interrupt Mask Register */
  #define REG_FLEXCOM2_TWI_RHR                      (0xFC010630U) /**< \brief (FLEXCOM2) TWI Receive Holding Register */
  #define REG_FLEXCOM2_TWI_THR                      (0xFC010634U) /**< \brief (FLEXCOM2) TWI Transmit Holding Register */
  #define REG_FLEXCOM2_TWI_SMBTR                    (0xFC010638U) /**< \brief (FLEXCOM2) TWI SMBus Timing Register */
  #define REG_FLEXCOM2_TWI_ACR                      (0xFC010640U) /**< \brief (FLEXCOM2) TWI Alternative Command Register */
  #define REG_FLEXCOM2_TWI_FILTR                    (0xFC010644U) /**< \brief (FLEXCOM2) TWI Filter Register */
  #define REG_FLEXCOM2_TWI_SWMR                     (0xFC01064CU) /**< \brief (FLEXCOM2) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM2_TWI_FMR                      (0xFC010650U) /**< \brief (FLEXCOM2) TWI FIFO Mode Register */
  #define REG_FLEXCOM2_TWI_FLR                      (0xFC010654U) /**< \brief (FLEXCOM2) TWI FIFO Level Register */
  #define REG_FLEXCOM2_TWI_FSR                      (0xFC010660U) /**< \brief (FLEXCOM2) TWI FIFO Status Register */
  #define REG_FLEXCOM2_TWI_FIER                     (0xFC010664U) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM2_TWI_FIDR                     (0xFC010668U) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM2_TWI_FIMR                     (0xFC01066CU) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM2_TWI_DR                       (0xFC0106D0U) /**< \brief (FLEXCOM2) TWI Debug Register */
  #define REG_FLEXCOM2_TWI_WPMR                     (0xFC0106E4U) /**< \brief (FLEXCOM2) TWI Protection Mode Register */
  #define REG_FLEXCOM2_TWI_WPSR                     (0xFC0106E8U) /**< \brief (FLEXCOM2) TWI Protection Status Register */
  #define REG_FLEXCOM2_TWI_VER                      (0xFC0106FCU) /**< \brief (FLEXCOM2) TWI Version Register */
#else
  #define REG_FLEXCOM2_MR          (*(__IO uint32_t*)0xFC010000U) /**< \brief (FLEXCOM2) FLEXCOM Mode Register */
  #define REG_FLEXCOM2_RHR         (*(__I  uint32_t*)0xFC010010U) /**< \brief (FLEXCOM2) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM2_THR         (*(__IO uint32_t*)0xFC010020U) /**< \brief (FLEXCOM2) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM2_VERSION     (*(__I  uint32_t*)0xFC0100FCU) /**< \brief (FLEXCOM2) FLEXCOM Version Register */
  #define REG_FLEXCOM2_US_CR       (*(__O  uint32_t*)0xFC010200U) /**< \brief (FLEXCOM2) USART Control Register */
  #define REG_FLEXCOM2_US_MR       (*(__IO uint32_t*)0xFC010204U) /**< \brief (FLEXCOM2) USART Mode Register */
  #define REG_FLEXCOM2_US_IER      (*(__O  uint32_t*)0xFC010208U) /**< \brief (FLEXCOM2) USART Interrupt Enable Register */
  #define REG_FLEXCOM2_US_IDR      (*(__O  uint32_t*)0xFC01020CU) /**< \brief (FLEXCOM2) USART Interrupt Disable Register */
  #define REG_FLEXCOM2_US_IMR      (*(__I  uint32_t*)0xFC010210U) /**< \brief (FLEXCOM2) USART Interrupt Mask Register */
  #define REG_FLEXCOM2_US_CSR      (*(__I  uint32_t*)0xFC010214U) /**< \brief (FLEXCOM2) USART Channel Status Register */
  #define REG_FLEXCOM2_US_RHR      (*(__I  uint32_t*)0xFC010218U) /**< \brief (FLEXCOM2) USART Receive Holding Register */
  #define REG_FLEXCOM2_US_THR      (*(__O  uint32_t*)0xFC01021CU) /**< \brief (FLEXCOM2) USART Transmit Holding Register */
  #define REG_FLEXCOM2_US_BRGR     (*(__IO uint32_t*)0xFC010220U) /**< \brief (FLEXCOM2) USART Baud Rate Generator Register */
  #define REG_FLEXCOM2_US_RTOR     (*(__IO uint32_t*)0xFC010224U) /**< \brief (FLEXCOM2) USART Receiver Timeout Register */
  #define REG_FLEXCOM2_US_TTGR     (*(__IO uint32_t*)0xFC010228U) /**< \brief (FLEXCOM2) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM2_US_FIDI     (*(__IO uint32_t*)0xFC010240U) /**< \brief (FLEXCOM2) USART FI DI Ratio Register */
  #define REG_FLEXCOM2_US_NER      (*(__I  uint32_t*)0xFC010244U) /**< \brief (FLEXCOM2) USART Number of Errors Register */
  #define REG_FLEXCOM2_US_IF       (*(__IO uint32_t*)0xFC01024CU) /**< \brief (FLEXCOM2) USART IrDA Filter Register */
  #define REG_FLEXCOM2_US_MAN      (*(__IO uint32_t*)0xFC010250U) /**< \brief (FLEXCOM2) USART Manchester Configuration Register */
  #define REG_FLEXCOM2_US_LINMR    (*(__IO uint32_t*)0xFC010254U) /**< \brief (FLEXCOM2) USART LIN Mode Register */
  #define REG_FLEXCOM2_US_LINIR    (*(__IO uint32_t*)0xFC010258U) /**< \brief (FLEXCOM2) USART LIN Identifier Register */
  #define REG_FLEXCOM2_US_LINBRR   (*(__I  uint32_t*)0xFC01025CU) /**< \brief (FLEXCOM2) USART LIN Baud Rate Register */
  #define REG_FLEXCOM2_US_CMPR     (*(__IO uint32_t*)0xFC010290U) /**< \brief (FLEXCOM2) USART Comparison Register */
  #define REG_FLEXCOM2_US_FMR      (*(__IO uint32_t*)0xFC0102A0U) /**< \brief (FLEXCOM2) USART FIFO Mode Register */
  #define REG_FLEXCOM2_US_FESR     (*(__I  uint32_t*)0xFC0102A4U) /**< \brief (FLEXCOM2) USART FIFO Level Register */
  #define REG_FLEXCOM2_US_FIER     (*(__O  uint32_t*)0xFC0102A8U) /**< \brief (FLEXCOM2) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM2_US_FIDR     (*(__O  uint32_t*)0xFC0102ACU) /**< \brief (FLEXCOM2) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM2_US_FIMR     (*(__I  uint32_t*)0xFC0102B0U) /**< \brief (FLEXCOM2) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM2_US_FLR      (*(__I  uint32_t*)0xFC0102B4U) /**< \brief (FLEXCOM2) USART FIFO Event Status Register */
  #define REG_FLEXCOM2_US_WPMR     (*(__IO uint32_t*)0xFC0102E4U) /**< \brief (FLEXCOM2) USART Write Protection Mode Register */
  #define REG_FLEXCOM2_US_WPSR     (*(__I  uint32_t*)0xFC0102E8U) /**< \brief (FLEXCOM2) USART Write Protection Status Register */
  #define REG_FLEXCOM2_US_VERSION  (*(__I  uint32_t*)0xFC0102FCU) /**< \brief (FLEXCOM2) USART Version Register */
  #define REG_FLEXCOM2_SPI_CR      (*(__O  uint32_t*)0xFC010400U) /**< \brief (FLEXCOM2) SPI Control Register */
  #define REG_FLEXCOM2_SPI_MR      (*(__IO uint32_t*)0xFC010404U) /**< \brief (FLEXCOM2) SPI Mode Register */
  #define REG_FLEXCOM2_SPI_RDR     (*(__I  uint32_t*)0xFC010408U) /**< \brief (FLEXCOM2) SPI Receive Data Register */
  #define REG_FLEXCOM2_SPI_TDR     (*(__O  uint32_t*)0xFC01040CU) /**< \brief (FLEXCOM2) SPI Transmit Data Register */
  #define REG_FLEXCOM2_SPI_SR      (*(__I  uint32_t*)0xFC010410U) /**< \brief (FLEXCOM2) SPI Status Register */
  #define REG_FLEXCOM2_SPI_IER     (*(__O  uint32_t*)0xFC010414U) /**< \brief (FLEXCOM2) SPI Interrupt Enable Register */
  #define REG_FLEXCOM2_SPI_IDR     (*(__O  uint32_t*)0xFC010418U) /**< \brief (FLEXCOM2) SPI Interrupt Disable Register */
  #define REG_FLEXCOM2_SPI_IMR     (*(__I  uint32_t*)0xFC01041CU) /**< \brief (FLEXCOM2) SPI Interrupt Mask Register */
  #define REG_FLEXCOM2_SPI_CSR     (*(__IO uint32_t*)0xFC010430U) /**< \brief (FLEXCOM2) SPI Chip Select Register */
  #define REG_FLEXCOM2_SPI_FMR     (*(__IO uint32_t*)0xFC010440U) /**< \brief (FLEXCOM2) SPI FIFO Mode Register */
  #define REG_FLEXCOM2_SPI_FLR     (*(__I  uint32_t*)0xFC010444U) /**< \brief (FLEXCOM2) SPI FIFO Level Register */
  #define REG_FLEXCOM2_SPI_CMPR    (*(__IO uint32_t*)0xFC010448U) /**< \brief (FLEXCOM2) SPI Comparison Register */
  #define REG_FLEXCOM2_SPI_WPMR    (*(__IO uint32_t*)0xFC0104E4U) /**< \brief (FLEXCOM2) SPI Write Protection Mode Register */
  #define REG_FLEXCOM2_SPI_WPSR    (*(__I  uint32_t*)0xFC0104E8U) /**< \brief (FLEXCOM2) SPI Write Protection Status Register */
  #define REG_FLEXCOM2_SPI_VERSION (*(__I  uint32_t*)0xFC0104FCU) /**< \brief (FLEXCOM2) SPI Version Register */
  #define REG_FLEXCOM2_TWI_CR      (*(__O  uint32_t*)0xFC010600U) /**< \brief (FLEXCOM2) TWI Control Register */
  #define REG_FLEXCOM2_TWI_MMR     (*(__IO uint32_t*)0xFC010604U) /**< \brief (FLEXCOM2) TWI Master Mode Register */
  #define REG_FLEXCOM2_TWI_SMR     (*(__IO uint32_t*)0xFC010608U) /**< \brief (FLEXCOM2) TWI Slave Mode Register */
  #define REG_FLEXCOM2_TWI_IADR    (*(__IO uint32_t*)0xFC01060CU) /**< \brief (FLEXCOM2) TWI Internal Address Register */
  #define REG_FLEXCOM2_TWI_CWGR    (*(__IO uint32_t*)0xFC010610U) /**< \brief (FLEXCOM2) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM2_TWI_SR      (*(__I  uint32_t*)0xFC010620U) /**< \brief (FLEXCOM2) TWI Status Register */
  #define REG_FLEXCOM2_TWI_IER     (*(__O  uint32_t*)0xFC010624U) /**< \brief (FLEXCOM2) TWI Interrupt Enable Register */
  #define REG_FLEXCOM2_TWI_IDR     (*(__O  uint32_t*)0xFC010628U) /**< \brief (FLEXCOM2) TWI Interrupt Disable Register */
  #define REG_FLEXCOM2_TWI_IMR     (*(__I  uint32_t*)0xFC01062CU) /**< \brief (FLEXCOM2) TWI Interrupt Mask Register */
  #define REG_FLEXCOM2_TWI_RHR     (*(__I  uint32_t*)0xFC010630U) /**< \brief (FLEXCOM2) TWI Receive Holding Register */
  #define REG_FLEXCOM2_TWI_THR     (*(__O  uint32_t*)0xFC010634U) /**< \brief (FLEXCOM2) TWI Transmit Holding Register */
  #define REG_FLEXCOM2_TWI_SMBTR   (*(__IO uint32_t*)0xFC010638U) /**< \brief (FLEXCOM2) TWI SMBus Timing Register */
  #define REG_FLEXCOM2_TWI_ACR     (*(__IO uint32_t*)0xFC010640U) /**< \brief (FLEXCOM2) TWI Alternative Command Register */
  #define REG_FLEXCOM2_TWI_FILTR   (*(__IO uint32_t*)0xFC010644U) /**< \brief (FLEXCOM2) TWI Filter Register */
  #define REG_FLEXCOM2_TWI_SWMR    (*(__IO uint32_t*)0xFC01064CU) /**< \brief (FLEXCOM2) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM2_TWI_FMR     (*(__IO uint32_t*)0xFC010650U) /**< \brief (FLEXCOM2) TWI FIFO Mode Register */
  #define REG_FLEXCOM2_TWI_FLR     (*(__I  uint32_t*)0xFC010654U) /**< \brief (FLEXCOM2) TWI FIFO Level Register */
  #define REG_FLEXCOM2_TWI_FSR     (*(__I  uint32_t*)0xFC010660U) /**< \brief (FLEXCOM2) TWI FIFO Status Register */
  #define REG_FLEXCOM2_TWI_FIER    (*(__O  uint32_t*)0xFC010664U) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM2_TWI_FIDR    (*(__O  uint32_t*)0xFC010668U) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM2_TWI_FIMR    (*(__I  uint32_t*)0xFC01066CU) /**< \brief (FLEXCOM2) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM2_TWI_DR      (*(__I  uint32_t*)0xFC0106D0U) /**< \brief (FLEXCOM2) TWI Debug Register */
  #define REG_FLEXCOM2_TWI_WPMR    (*(__IO uint32_t*)0xFC0106E4U) /**< \brief (FLEXCOM2) TWI Protection Mode Register */
  #define REG_FLEXCOM2_TWI_WPSR    (*(__I  uint32_t*)0xFC0106E8U) /**< \brief (FLEXCOM2) TWI Protection Status Register */
  #define REG_FLEXCOM2_TWI_VER     (*(__I  uint32_t*)0xFC0106FCU) /**< \brief (FLEXCOM2) TWI Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_FLEXCOM2_INSTANCE_ */
