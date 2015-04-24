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

#ifndef _SAMA5D2_FLEXCOM3_INSTANCE_
#define _SAMA5D2_FLEXCOM3_INSTANCE_

/* ========== Register definition for FLEXCOM3 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM3_MR                           (0xFC014000U) /**< \brief (FLEXCOM3) FLEXCOM Mode Register */
  #define REG_FLEXCOM3_RHR                          (0xFC014010U) /**< \brief (FLEXCOM3) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM3_THR                          (0xFC014020U) /**< \brief (FLEXCOM3) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM3_VERSION                      (0xFC0140FCU) /**< \brief (FLEXCOM3) FLEXCOM Version Register */
  #define REG_FLEXCOM3_US_CR                        (0xFC014200U) /**< \brief (FLEXCOM3) USART Control Register */
  #define REG_FLEXCOM3_US_MR                        (0xFC014204U) /**< \brief (FLEXCOM3) USART Mode Register */
  #define REG_FLEXCOM3_US_IER                       (0xFC014208U) /**< \brief (FLEXCOM3) USART Interrupt Enable Register */
  #define REG_FLEXCOM3_US_IDR                       (0xFC01420CU) /**< \brief (FLEXCOM3) USART Interrupt Disable Register */
  #define REG_FLEXCOM3_US_IMR                       (0xFC014210U) /**< \brief (FLEXCOM3) USART Interrupt Mask Register */
  #define REG_FLEXCOM3_US_CSR                       (0xFC014214U) /**< \brief (FLEXCOM3) USART Channel Status Register */
  #define REG_FLEXCOM3_US_RHR                       (0xFC014218U) /**< \brief (FLEXCOM3) USART Receive Holding Register */
  #define REG_FLEXCOM3_US_THR                       (0xFC01421CU) /**< \brief (FLEXCOM3) USART Transmit Holding Register */
  #define REG_FLEXCOM3_US_BRGR                      (0xFC014220U) /**< \brief (FLEXCOM3) USART Baud Rate Generator Register */
  #define REG_FLEXCOM3_US_RTOR                      (0xFC014224U) /**< \brief (FLEXCOM3) USART Receiver Timeout Register */
  #define REG_FLEXCOM3_US_TTGR                      (0xFC014228U) /**< \brief (FLEXCOM3) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM3_US_FIDI                      (0xFC014240U) /**< \brief (FLEXCOM3) USART FI DI Ratio Register */
  #define REG_FLEXCOM3_US_NER                       (0xFC014244U) /**< \brief (FLEXCOM3) USART Number of Errors Register */
  #define REG_FLEXCOM3_US_IF                        (0xFC01424CU) /**< \brief (FLEXCOM3) USART IrDA Filter Register */
  #define REG_FLEXCOM3_US_MAN                       (0xFC014250U) /**< \brief (FLEXCOM3) USART Manchester Configuration Register */
  #define REG_FLEXCOM3_US_LINMR                     (0xFC014254U) /**< \brief (FLEXCOM3) USART LIN Mode Register */
  #define REG_FLEXCOM3_US_LINIR                     (0xFC014258U) /**< \brief (FLEXCOM3) USART LIN Identifier Register */
  #define REG_FLEXCOM3_US_LINBRR                    (0xFC01425CU) /**< \brief (FLEXCOM3) USART LIN Baud Rate Register */
  #define REG_FLEXCOM3_US_CMPR                      (0xFC014290U) /**< \brief (FLEXCOM3) USART Comparison Register */
  #define REG_FLEXCOM3_US_FMR                       (0xFC0142A0U) /**< \brief (FLEXCOM3) USART FIFO Mode Register */
  #define REG_FLEXCOM3_US_FESR                      (0xFC0142A4U) /**< \brief (FLEXCOM3) USART FIFO Level Register */
  #define REG_FLEXCOM3_US_FIER                      (0xFC0142A8U) /**< \brief (FLEXCOM3) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM3_US_FIDR                      (0xFC0142ACU) /**< \brief (FLEXCOM3) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM3_US_FIMR                      (0xFC0142B0U) /**< \brief (FLEXCOM3) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM3_US_FLR                       (0xFC0142B4U) /**< \brief (FLEXCOM3) USART FIFO Event Status Register */
  #define REG_FLEXCOM3_US_WPMR                      (0xFC0142E4U) /**< \brief (FLEXCOM3) USART Write Protection Mode Register */
  #define REG_FLEXCOM3_US_WPSR                      (0xFC0142E8U) /**< \brief (FLEXCOM3) USART Write Protection Status Register */
  #define REG_FLEXCOM3_US_VERSION                   (0xFC0142FCU) /**< \brief (FLEXCOM3) USART Version Register */
  #define REG_FLEXCOM3_SPI_CR                       (0xFC014400U) /**< \brief (FLEXCOM3) SPI Control Register */
  #define REG_FLEXCOM3_SPI_MR                       (0xFC014404U) /**< \brief (FLEXCOM3) SPI Mode Register */
  #define REG_FLEXCOM3_SPI_RDR                      (0xFC014408U) /**< \brief (FLEXCOM3) SPI Receive Data Register */
  #define REG_FLEXCOM3_SPI_TDR                      (0xFC01440CU) /**< \brief (FLEXCOM3) SPI Transmit Data Register */
  #define REG_FLEXCOM3_SPI_SR                       (0xFC014410U) /**< \brief (FLEXCOM3) SPI Status Register */
  #define REG_FLEXCOM3_SPI_IER                      (0xFC014414U) /**< \brief (FLEXCOM3) SPI Interrupt Enable Register */
  #define REG_FLEXCOM3_SPI_IDR                      (0xFC014418U) /**< \brief (FLEXCOM3) SPI Interrupt Disable Register */
  #define REG_FLEXCOM3_SPI_IMR                      (0xFC01441CU) /**< \brief (FLEXCOM3) SPI Interrupt Mask Register */
  #define REG_FLEXCOM3_SPI_CSR                      (0xFC014430U) /**< \brief (FLEXCOM3) SPI Chip Select Register */
  #define REG_FLEXCOM3_SPI_FMR                      (0xFC014440U) /**< \brief (FLEXCOM3) SPI FIFO Mode Register */
  #define REG_FLEXCOM3_SPI_FLR                      (0xFC014444U) /**< \brief (FLEXCOM3) SPI FIFO Level Register */
  #define REG_FLEXCOM3_SPI_CMPR                     (0xFC014448U) /**< \brief (FLEXCOM3) SPI Comparison Register */
  #define REG_FLEXCOM3_SPI_WPMR                     (0xFC0144E4U) /**< \brief (FLEXCOM3) SPI Write Protection Mode Register */
  #define REG_FLEXCOM3_SPI_WPSR                     (0xFC0144E8U) /**< \brief (FLEXCOM3) SPI Write Protection Status Register */
  #define REG_FLEXCOM3_SPI_VERSION                  (0xFC0144FCU) /**< \brief (FLEXCOM3) SPI Version Register */
  #define REG_FLEXCOM3_TWI_CR                       (0xFC014600U) /**< \brief (FLEXCOM3) TWI Control Register */
  #define REG_FLEXCOM3_TWI_MMR                      (0xFC014604U) /**< \brief (FLEXCOM3) TWI Master Mode Register */
  #define REG_FLEXCOM3_TWI_SMR                      (0xFC014608U) /**< \brief (FLEXCOM3) TWI Slave Mode Register */
  #define REG_FLEXCOM3_TWI_IADR                     (0xFC01460CU) /**< \brief (FLEXCOM3) TWI Internal Address Register */
  #define REG_FLEXCOM3_TWI_CWGR                     (0xFC014610U) /**< \brief (FLEXCOM3) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM3_TWI_SR                       (0xFC014620U) /**< \brief (FLEXCOM3) TWI Status Register */
  #define REG_FLEXCOM3_TWI_IER                      (0xFC014624U) /**< \brief (FLEXCOM3) TWI Interrupt Enable Register */
  #define REG_FLEXCOM3_TWI_IDR                      (0xFC014628U) /**< \brief (FLEXCOM3) TWI Interrupt Disable Register */
  #define REG_FLEXCOM3_TWI_IMR                      (0xFC01462CU) /**< \brief (FLEXCOM3) TWI Interrupt Mask Register */
  #define REG_FLEXCOM3_TWI_RHR                      (0xFC014630U) /**< \brief (FLEXCOM3) TWI Receive Holding Register */
  #define REG_FLEXCOM3_TWI_THR                      (0xFC014634U) /**< \brief (FLEXCOM3) TWI Transmit Holding Register */
  #define REG_FLEXCOM3_TWI_SMBTR                    (0xFC014638U) /**< \brief (FLEXCOM3) TWI SMBus Timing Register */
  #define REG_FLEXCOM3_TWI_ACR                      (0xFC014640U) /**< \brief (FLEXCOM3) TWI Alternative Command Register */
  #define REG_FLEXCOM3_TWI_FILTR                    (0xFC014644U) /**< \brief (FLEXCOM3) TWI Filter Register */
  #define REG_FLEXCOM3_TWI_SWMR                     (0xFC01464CU) /**< \brief (FLEXCOM3) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM3_TWI_FMR                      (0xFC014650U) /**< \brief (FLEXCOM3) TWI FIFO Mode Register */
  #define REG_FLEXCOM3_TWI_FLR                      (0xFC014654U) /**< \brief (FLEXCOM3) TWI FIFO Level Register */
  #define REG_FLEXCOM3_TWI_FSR                      (0xFC014660U) /**< \brief (FLEXCOM3) TWI FIFO Status Register */
  #define REG_FLEXCOM3_TWI_FIER                     (0xFC014664U) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM3_TWI_FIDR                     (0xFC014668U) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM3_TWI_FIMR                     (0xFC01466CU) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM3_TWI_DR                       (0xFC0146D0U) /**< \brief (FLEXCOM3) TWI Debug Register */
  #define REG_FLEXCOM3_TWI_WPMR                     (0xFC0146E4U) /**< \brief (FLEXCOM3) TWI Protection Mode Register */
  #define REG_FLEXCOM3_TWI_WPSR                     (0xFC0146E8U) /**< \brief (FLEXCOM3) TWI Protection Status Register */
  #define REG_FLEXCOM3_TWI_VER                      (0xFC0146FCU) /**< \brief (FLEXCOM3) TWI Version Register */
#else
  #define REG_FLEXCOM3_MR          (*(__IO uint32_t*)0xFC014000U) /**< \brief (FLEXCOM3) FLEXCOM Mode Register */
  #define REG_FLEXCOM3_RHR         (*(__I  uint32_t*)0xFC014010U) /**< \brief (FLEXCOM3) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM3_THR         (*(__IO uint32_t*)0xFC014020U) /**< \brief (FLEXCOM3) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM3_VERSION     (*(__I  uint32_t*)0xFC0140FCU) /**< \brief (FLEXCOM3) FLEXCOM Version Register */
  #define REG_FLEXCOM3_US_CR       (*(__O  uint32_t*)0xFC014200U) /**< \brief (FLEXCOM3) USART Control Register */
  #define REG_FLEXCOM3_US_MR       (*(__IO uint32_t*)0xFC014204U) /**< \brief (FLEXCOM3) USART Mode Register */
  #define REG_FLEXCOM3_US_IER      (*(__O  uint32_t*)0xFC014208U) /**< \brief (FLEXCOM3) USART Interrupt Enable Register */
  #define REG_FLEXCOM3_US_IDR      (*(__O  uint32_t*)0xFC01420CU) /**< \brief (FLEXCOM3) USART Interrupt Disable Register */
  #define REG_FLEXCOM3_US_IMR      (*(__I  uint32_t*)0xFC014210U) /**< \brief (FLEXCOM3) USART Interrupt Mask Register */
  #define REG_FLEXCOM3_US_CSR      (*(__I  uint32_t*)0xFC014214U) /**< \brief (FLEXCOM3) USART Channel Status Register */
  #define REG_FLEXCOM3_US_RHR      (*(__I  uint32_t*)0xFC014218U) /**< \brief (FLEXCOM3) USART Receive Holding Register */
  #define REG_FLEXCOM3_US_THR      (*(__O  uint32_t*)0xFC01421CU) /**< \brief (FLEXCOM3) USART Transmit Holding Register */
  #define REG_FLEXCOM3_US_BRGR     (*(__IO uint32_t*)0xFC014220U) /**< \brief (FLEXCOM3) USART Baud Rate Generator Register */
  #define REG_FLEXCOM3_US_RTOR     (*(__IO uint32_t*)0xFC014224U) /**< \brief (FLEXCOM3) USART Receiver Timeout Register */
  #define REG_FLEXCOM3_US_TTGR     (*(__IO uint32_t*)0xFC014228U) /**< \brief (FLEXCOM3) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM3_US_FIDI     (*(__IO uint32_t*)0xFC014240U) /**< \brief (FLEXCOM3) USART FI DI Ratio Register */
  #define REG_FLEXCOM3_US_NER      (*(__I  uint32_t*)0xFC014244U) /**< \brief (FLEXCOM3) USART Number of Errors Register */
  #define REG_FLEXCOM3_US_IF       (*(__IO uint32_t*)0xFC01424CU) /**< \brief (FLEXCOM3) USART IrDA Filter Register */
  #define REG_FLEXCOM3_US_MAN      (*(__IO uint32_t*)0xFC014250U) /**< \brief (FLEXCOM3) USART Manchester Configuration Register */
  #define REG_FLEXCOM3_US_LINMR    (*(__IO uint32_t*)0xFC014254U) /**< \brief (FLEXCOM3) USART LIN Mode Register */
  #define REG_FLEXCOM3_US_LINIR    (*(__IO uint32_t*)0xFC014258U) /**< \brief (FLEXCOM3) USART LIN Identifier Register */
  #define REG_FLEXCOM3_US_LINBRR   (*(__I  uint32_t*)0xFC01425CU) /**< \brief (FLEXCOM3) USART LIN Baud Rate Register */
  #define REG_FLEXCOM3_US_CMPR     (*(__IO uint32_t*)0xFC014290U) /**< \brief (FLEXCOM3) USART Comparison Register */
  #define REG_FLEXCOM3_US_FMR      (*(__IO uint32_t*)0xFC0142A0U) /**< \brief (FLEXCOM3) USART FIFO Mode Register */
  #define REG_FLEXCOM3_US_FESR     (*(__I  uint32_t*)0xFC0142A4U) /**< \brief (FLEXCOM3) USART FIFO Level Register */
  #define REG_FLEXCOM3_US_FIER     (*(__O  uint32_t*)0xFC0142A8U) /**< \brief (FLEXCOM3) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM3_US_FIDR     (*(__O  uint32_t*)0xFC0142ACU) /**< \brief (FLEXCOM3) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM3_US_FIMR     (*(__I  uint32_t*)0xFC0142B0U) /**< \brief (FLEXCOM3) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM3_US_FLR      (*(__I  uint32_t*)0xFC0142B4U) /**< \brief (FLEXCOM3) USART FIFO Event Status Register */
  #define REG_FLEXCOM3_US_WPMR     (*(__IO uint32_t*)0xFC0142E4U) /**< \brief (FLEXCOM3) USART Write Protection Mode Register */
  #define REG_FLEXCOM3_US_WPSR     (*(__I  uint32_t*)0xFC0142E8U) /**< \brief (FLEXCOM3) USART Write Protection Status Register */
  #define REG_FLEXCOM3_US_VERSION  (*(__I  uint32_t*)0xFC0142FCU) /**< \brief (FLEXCOM3) USART Version Register */
  #define REG_FLEXCOM3_SPI_CR      (*(__O  uint32_t*)0xFC014400U) /**< \brief (FLEXCOM3) SPI Control Register */
  #define REG_FLEXCOM3_SPI_MR      (*(__IO uint32_t*)0xFC014404U) /**< \brief (FLEXCOM3) SPI Mode Register */
  #define REG_FLEXCOM3_SPI_RDR     (*(__I  uint32_t*)0xFC014408U) /**< \brief (FLEXCOM3) SPI Receive Data Register */
  #define REG_FLEXCOM3_SPI_TDR     (*(__O  uint32_t*)0xFC01440CU) /**< \brief (FLEXCOM3) SPI Transmit Data Register */
  #define REG_FLEXCOM3_SPI_SR      (*(__I  uint32_t*)0xFC014410U) /**< \brief (FLEXCOM3) SPI Status Register */
  #define REG_FLEXCOM3_SPI_IER     (*(__O  uint32_t*)0xFC014414U) /**< \brief (FLEXCOM3) SPI Interrupt Enable Register */
  #define REG_FLEXCOM3_SPI_IDR     (*(__O  uint32_t*)0xFC014418U) /**< \brief (FLEXCOM3) SPI Interrupt Disable Register */
  #define REG_FLEXCOM3_SPI_IMR     (*(__I  uint32_t*)0xFC01441CU) /**< \brief (FLEXCOM3) SPI Interrupt Mask Register */
  #define REG_FLEXCOM3_SPI_CSR     (*(__IO uint32_t*)0xFC014430U) /**< \brief (FLEXCOM3) SPI Chip Select Register */
  #define REG_FLEXCOM3_SPI_FMR     (*(__IO uint32_t*)0xFC014440U) /**< \brief (FLEXCOM3) SPI FIFO Mode Register */
  #define REG_FLEXCOM3_SPI_FLR     (*(__I  uint32_t*)0xFC014444U) /**< \brief (FLEXCOM3) SPI FIFO Level Register */
  #define REG_FLEXCOM3_SPI_CMPR    (*(__IO uint32_t*)0xFC014448U) /**< \brief (FLEXCOM3) SPI Comparison Register */
  #define REG_FLEXCOM3_SPI_WPMR    (*(__IO uint32_t*)0xFC0144E4U) /**< \brief (FLEXCOM3) SPI Write Protection Mode Register */
  #define REG_FLEXCOM3_SPI_WPSR    (*(__I  uint32_t*)0xFC0144E8U) /**< \brief (FLEXCOM3) SPI Write Protection Status Register */
  #define REG_FLEXCOM3_SPI_VERSION (*(__I  uint32_t*)0xFC0144FCU) /**< \brief (FLEXCOM3) SPI Version Register */
  #define REG_FLEXCOM3_TWI_CR      (*(__O  uint32_t*)0xFC014600U) /**< \brief (FLEXCOM3) TWI Control Register */
  #define REG_FLEXCOM3_TWI_MMR     (*(__IO uint32_t*)0xFC014604U) /**< \brief (FLEXCOM3) TWI Master Mode Register */
  #define REG_FLEXCOM3_TWI_SMR     (*(__IO uint32_t*)0xFC014608U) /**< \brief (FLEXCOM3) TWI Slave Mode Register */
  #define REG_FLEXCOM3_TWI_IADR    (*(__IO uint32_t*)0xFC01460CU) /**< \brief (FLEXCOM3) TWI Internal Address Register */
  #define REG_FLEXCOM3_TWI_CWGR    (*(__IO uint32_t*)0xFC014610U) /**< \brief (FLEXCOM3) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM3_TWI_SR      (*(__I  uint32_t*)0xFC014620U) /**< \brief (FLEXCOM3) TWI Status Register */
  #define REG_FLEXCOM3_TWI_IER     (*(__O  uint32_t*)0xFC014624U) /**< \brief (FLEXCOM3) TWI Interrupt Enable Register */
  #define REG_FLEXCOM3_TWI_IDR     (*(__O  uint32_t*)0xFC014628U) /**< \brief (FLEXCOM3) TWI Interrupt Disable Register */
  #define REG_FLEXCOM3_TWI_IMR     (*(__I  uint32_t*)0xFC01462CU) /**< \brief (FLEXCOM3) TWI Interrupt Mask Register */
  #define REG_FLEXCOM3_TWI_RHR     (*(__I  uint32_t*)0xFC014630U) /**< \brief (FLEXCOM3) TWI Receive Holding Register */
  #define REG_FLEXCOM3_TWI_THR     (*(__O  uint32_t*)0xFC014634U) /**< \brief (FLEXCOM3) TWI Transmit Holding Register */
  #define REG_FLEXCOM3_TWI_SMBTR   (*(__IO uint32_t*)0xFC014638U) /**< \brief (FLEXCOM3) TWI SMBus Timing Register */
  #define REG_FLEXCOM3_TWI_ACR     (*(__IO uint32_t*)0xFC014640U) /**< \brief (FLEXCOM3) TWI Alternative Command Register */
  #define REG_FLEXCOM3_TWI_FILTR   (*(__IO uint32_t*)0xFC014644U) /**< \brief (FLEXCOM3) TWI Filter Register */
  #define REG_FLEXCOM3_TWI_SWMR    (*(__IO uint32_t*)0xFC01464CU) /**< \brief (FLEXCOM3) TWI SleepWalking Matching Register */
  #define REG_FLEXCOM3_TWI_FMR     (*(__IO uint32_t*)0xFC014650U) /**< \brief (FLEXCOM3) TWI FIFO Mode Register */
  #define REG_FLEXCOM3_TWI_FLR     (*(__I  uint32_t*)0xFC014654U) /**< \brief (FLEXCOM3) TWI FIFO Level Register */
  #define REG_FLEXCOM3_TWI_FSR     (*(__I  uint32_t*)0xFC014660U) /**< \brief (FLEXCOM3) TWI FIFO Status Register */
  #define REG_FLEXCOM3_TWI_FIER    (*(__O  uint32_t*)0xFC014664U) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM3_TWI_FIDR    (*(__O  uint32_t*)0xFC014668U) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM3_TWI_FIMR    (*(__I  uint32_t*)0xFC01466CU) /**< \brief (FLEXCOM3) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM3_TWI_DR      (*(__I  uint32_t*)0xFC0146D0U) /**< \brief (FLEXCOM3) TWI Debug Register */
  #define REG_FLEXCOM3_TWI_WPMR    (*(__IO uint32_t*)0xFC0146E4U) /**< \brief (FLEXCOM3) TWI Protection Mode Register */
  #define REG_FLEXCOM3_TWI_WPSR    (*(__I  uint32_t*)0xFC0146E8U) /**< \brief (FLEXCOM3) TWI Protection Status Register */
  #define REG_FLEXCOM3_TWI_VER     (*(__I  uint32_t*)0xFC0146FCU) /**< \brief (FLEXCOM3) TWI Version Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_FLEXCOM3_INSTANCE_ */
