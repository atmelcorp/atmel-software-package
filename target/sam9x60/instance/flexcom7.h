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

#ifndef _SAM9X_FLEXCOM7_INSTANCE_
#define _SAM9X_FLEXCOM7_INSTANCE_

/* ========== Register definition for FLEXCOM7 peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_FLEXCOM7_MR                           (0xF8014000U) /**< \brief (FLEXCOM7) FLEXCOM Mode Register */
  #define REG_FLEXCOM7_RHR                          (0xF8014010U) /**< \brief (FLEXCOM7) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM7_THR                          (0xF8014020U) /**< \brief (FLEXCOM7) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM7_US_CR                        (0xF8014200U) /**< \brief (FLEXCOM7) USART Control Register */
  #define REG_FLEXCOM7_US_MR                        (0xF8014204U) /**< \brief (FLEXCOM7) USART Mode Register */
  #define REG_FLEXCOM7_US_IER                       (0xF8014208U) /**< \brief (FLEXCOM7) USART Interrupt Enable Register */
  #define REG_FLEXCOM7_US_IDR                       (0xF801420CU) /**< \brief (FLEXCOM7) USART Interrupt Disable Register */
  #define REG_FLEXCOM7_US_IMR                       (0xF8014210U) /**< \brief (FLEXCOM7) USART Interrupt Mask Register */
  #define REG_FLEXCOM7_US_CSR                       (0xF8014214U) /**< \brief (FLEXCOM7) USART Channel Status Register */
  #define REG_FLEXCOM7_US_RHR                       (0xF8014218U) /**< \brief (FLEXCOM7) USART Receive Holding Register */
  #define REG_FLEXCOM7_US_THR                       (0xF801421CU) /**< \brief (FLEXCOM7) USART Transmit Holding Register */
  #define REG_FLEXCOM7_US_BRGR                      (0xF8014220U) /**< \brief (FLEXCOM7) USART Baud Rate Generator Register */
  #define REG_FLEXCOM7_US_RTOR                      (0xF8014224U) /**< \brief (FLEXCOM7) USART Receiver Timeout Register */
  #define REG_FLEXCOM7_US_TTGR                      (0xF8014228U) /**< \brief (FLEXCOM7) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM7_US_FIDI                      (0xF8014240U) /**< \brief (FLEXCOM7) USART FI DI Ratio Register */
  #define REG_FLEXCOM7_US_NER                       (0xF8014244U) /**< \brief (FLEXCOM7) USART Number of Errors Register */
  #define REG_FLEXCOM7_US_IF                        (0xF801424CU) /**< \brief (FLEXCOM7) USART IrDA Filter Register */
  #define REG_FLEXCOM7_US_MAN                       (0xF8014250U) /**< \brief (FLEXCOM7) USART Manchester Configuration Register */
  #define REG_FLEXCOM7_US_LINMR                     (0xF8014254U) /**< \brief (FLEXCOM7) USART LIN Mode Register */
  #define REG_FLEXCOM7_US_LINIR                     (0xF8014258U) /**< \brief (FLEXCOM7) USART LIN Identifier Register */
  #define REG_FLEXCOM7_US_LINBRR                    (0xF801425CU) /**< \brief (FLEXCOM7) USART LIN Baud Rate Register */
  #define REG_FLEXCOM7_US_LONMR                     (0xF8014260U) /**< \brief (FLEXCOM7) USART LON Mode Register */
  #define REG_FLEXCOM7_US_LONPR                     (0xF8014264U) /**< \brief (FLEXCOM7) USART LON Preamble Register */
  #define REG_FLEXCOM7_US_LONDL                     (0xF8014268U) /**< \brief (FLEXCOM7) USART LON Data Length Register */
  #define REG_FLEXCOM7_US_LONL2HDR                  (0xF801426CU) /**< \brief (FLEXCOM7) USART LON L2HDR Register */
  #define REG_FLEXCOM7_US_LONBL                     (0xF8014270U) /**< \brief (FLEXCOM7) USART LON Backlog Register */
  #define REG_FLEXCOM7_US_LONB1TX                   (0xF8014274U) /**< \brief (FLEXCOM7) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM7_US_LONB1RX                   (0xF8014278U) /**< \brief (FLEXCOM7) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM7_US_LONPRIO                   (0xF801427CU) /**< \brief (FLEXCOM7) USART LON Priority Register */
  #define REG_FLEXCOM7_US_IDTTX                     (0xF8014280U) /**< \brief (FLEXCOM7) USART LON IDT Tx Register */
  #define REG_FLEXCOM7_US_IDTRX                     (0xF8014284U) /**< \brief (FLEXCOM7) USART LON IDT Rx Register */
  #define REG_FLEXCOM7_US_ICDIFF                    (0xF8014288U) /**< \brief (FLEXCOM7) USART IC DIFF Register */
  #define REG_FLEXCOM7_US_CMPR                      (0xF8014290U) /**< \brief (FLEXCOM7) USART Comparison Register */
  #define REG_FLEXCOM7_US_FMR                       (0xF80142A0U) /**< \brief (FLEXCOM7) USART FIFO Mode Register */
  #define REG_FLEXCOM7_US_FLR                       (0xF80142A4U) /**< \brief (FLEXCOM7) USART FIFO Level Register */
  #define REG_FLEXCOM7_US_FIER                      (0xF80142A8U) /**< \brief (FLEXCOM7) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM7_US_FIDR                      (0xF80142ACU) /**< \brief (FLEXCOM7) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM7_US_FIMR                      (0xF80142B0U) /**< \brief (FLEXCOM7) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM7_US_FESR                      (0xF80142B4U) /**< \brief (FLEXCOM7) USART FIFO Event Status Register */
  #define REG_FLEXCOM7_US_WPMR                      (0xF80142E4U) /**< \brief (FLEXCOM7) USART Write Protection Mode Register */
  #define REG_FLEXCOM7_US_WPSR                      (0xF80142E8U) /**< \brief (FLEXCOM7) USART Write Protection Status Register */
  #define REG_FLEXCOM7_SPI_CR                       (0xF8014400U) /**< \brief (FLEXCOM7) SPI Control Register */
  #define REG_FLEXCOM7_SPI_MR                       (0xF8014404U) /**< \brief (FLEXCOM7) SPI Mode Register */
  #define REG_FLEXCOM7_SPI_RDR                      (0xF8014408U) /**< \brief (FLEXCOM7) SPI Receive Data Register */
  #define REG_FLEXCOM7_SPI_TDR                      (0xF801440CU) /**< \brief (FLEXCOM7) SPI Transmit Data Register */
  #define REG_FLEXCOM7_SPI_SR                       (0xF8014410U) /**< \brief (FLEXCOM7) SPI Status Register */
  #define REG_FLEXCOM7_SPI_IER                      (0xF8014414U) /**< \brief (FLEXCOM7) SPI Interrupt Enable Register */
  #define REG_FLEXCOM7_SPI_IDR                      (0xF8014418U) /**< \brief (FLEXCOM7) SPI Interrupt Disable Register */
  #define REG_FLEXCOM7_SPI_IMR                      (0xF801441CU) /**< \brief (FLEXCOM7) SPI Interrupt Mask Register */
  #define REG_FLEXCOM7_SPI_CSR                      (0xF8014430U) /**< \brief (FLEXCOM7) SPI Chip Select Register */
  #define REG_FLEXCOM7_SPI_FMR                      (0xF8014440U) /**< \brief (FLEXCOM7) SPI FIFO Mode Register */
  #define REG_FLEXCOM7_SPI_FLR                      (0xF8014444U) /**< \brief (FLEXCOM7) SPI FIFO Level Register */
  #define REG_FLEXCOM7_SPI_CMPR                     (0xF8014448U) /**< \brief (FLEXCOM7) SPI Comparison Register */
  #define REG_FLEXCOM7_SPI_WPMR                     (0xF80144E4U) /**< \brief (FLEXCOM7) SPI Write Protection Mode Register */
  #define REG_FLEXCOM7_SPI_WPSR                     (0xF80144E8U) /**< \brief (FLEXCOM7) SPI Write Protection Status Register */
  #define REG_FLEXCOM7_TWI_CR                       (0xF8014600U) /**< \brief (FLEXCOM7) TWI Control Register */
  #define REG_FLEXCOM7_TWI_MMR                      (0xF8014604U) /**< \brief (FLEXCOM7) TWI Master Mode Register */
  #define REG_FLEXCOM7_TWI_SMR                      (0xF8014608U) /**< \brief (FLEXCOM7) TWI Slave Mode Register */
  #define REG_FLEXCOM7_TWI_IADR                     (0xF801460CU) /**< \brief (FLEXCOM7) TWI Internal Address Register */
  #define REG_FLEXCOM7_TWI_CWGR                     (0xF8014610U) /**< \brief (FLEXCOM7) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM7_TWI_SR                       (0xF8014620U) /**< \brief (FLEXCOM7) TWI Status Register */
  #define REG_FLEXCOM7_TWI_IER                      (0xF8014624U) /**< \brief (FLEXCOM7) TWI Interrupt Enable Register */
  #define REG_FLEXCOM7_TWI_IDR                      (0xF8014628U) /**< \brief (FLEXCOM7) TWI Interrupt Disable Register */
  #define REG_FLEXCOM7_TWI_IMR                      (0xF801462CU) /**< \brief (FLEXCOM7) TWI Interrupt Mask Register */
  #define REG_FLEXCOM7_TWI_RHR                      (0xF8014630U) /**< \brief (FLEXCOM7) TWI Receive Holding Register */
  #define REG_FLEXCOM7_TWI_THR                      (0xF8014634U) /**< \brief (FLEXCOM7) TWI Transmit Holding Register */
  #define REG_FLEXCOM7_TWI_SMBTR                    (0xF8014638U) /**< \brief (FLEXCOM7) TWI SMBus Timing Register */
  #define REG_FLEXCOM7_TWI_ACR                      (0xF8014640U) /**< \brief (FLEXCOM7) TWI Alternative Command Register */
  #define REG_FLEXCOM7_TWI_FILTR                    (0xF8014644U) /**< \brief (FLEXCOM7) TWI Filter Register */
  #define REG_FLEXCOM7_TWI_FMR                      (0xF8014650U) /**< \brief (FLEXCOM7) TWI FIFO Mode Register */
  #define REG_FLEXCOM7_TWI_FLR                      (0xF8014654U) /**< \brief (FLEXCOM7) TWI FIFO Level Register */
  #define REG_FLEXCOM7_TWI_FSR                      (0xF8014660U) /**< \brief (FLEXCOM7) TWI FIFO Status Register */
  #define REG_FLEXCOM7_TWI_FIER                     (0xF8014664U) /**< \brief (FLEXCOM7) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM7_TWI_FIDR                     (0xF8014668U) /**< \brief (FLEXCOM7) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM7_TWI_FIMR                     (0xF801466CU) /**< \brief (FLEXCOM7) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM7_TWI_WPMR                     (0xF80146E4U) /**< \brief (FLEXCOM7) TWI Write Protection Mode Register */
  #define REG_FLEXCOM7_TWI_WPSR                     (0xF80146E8U) /**< \brief (FLEXCOM7) TWI Write Protection Status Register */
#else
  #define REG_FLEXCOM7_MR          (*(__IO uint32_t*)0xF8014000U) /**< \brief (FLEXCOM7) FLEXCOM Mode Register */
  #define REG_FLEXCOM7_RHR         (*(__I  uint32_t*)0xF8014010U) /**< \brief (FLEXCOM7) FLEXCOM Receive Holding Register */
  #define REG_FLEXCOM7_THR         (*(__IO uint32_t*)0xF8014020U) /**< \brief (FLEXCOM7) FLEXCOM Transmit Holding Register */
  #define REG_FLEXCOM7_US_CR       (*(__O  uint32_t*)0xF8014200U) /**< \brief (FLEXCOM7) USART Control Register */
  #define REG_FLEXCOM7_US_MR       (*(__IO uint32_t*)0xF8014204U) /**< \brief (FLEXCOM7) USART Mode Register */
  #define REG_FLEXCOM7_US_IER      (*(__O  uint32_t*)0xF8014208U) /**< \brief (FLEXCOM7) USART Interrupt Enable Register */
  #define REG_FLEXCOM7_US_IDR      (*(__O  uint32_t*)0xF801420CU) /**< \brief (FLEXCOM7) USART Interrupt Disable Register */
  #define REG_FLEXCOM7_US_IMR      (*(__I  uint32_t*)0xF8014210U) /**< \brief (FLEXCOM7) USART Interrupt Mask Register */
  #define REG_FLEXCOM7_US_CSR      (*(__I  uint32_t*)0xF8014214U) /**< \brief (FLEXCOM7) USART Channel Status Register */
  #define REG_FLEXCOM7_US_RHR      (*(__I  uint32_t*)0xF8014218U) /**< \brief (FLEXCOM7) USART Receive Holding Register */
  #define REG_FLEXCOM7_US_THR      (*(__O  uint32_t*)0xF801421CU) /**< \brief (FLEXCOM7) USART Transmit Holding Register */
  #define REG_FLEXCOM7_US_BRGR     (*(__IO uint32_t*)0xF8014220U) /**< \brief (FLEXCOM7) USART Baud Rate Generator Register */
  #define REG_FLEXCOM7_US_RTOR     (*(__IO uint32_t*)0xF8014224U) /**< \brief (FLEXCOM7) USART Receiver Timeout Register */
  #define REG_FLEXCOM7_US_TTGR     (*(__IO uint32_t*)0xF8014228U) /**< \brief (FLEXCOM7) USART Transmitter Timeguard Register */
  #define REG_FLEXCOM7_US_FIDI     (*(__IO uint32_t*)0xF8014240U) /**< \brief (FLEXCOM7) USART FI DI Ratio Register */
  #define REG_FLEXCOM7_US_NER      (*(__I  uint32_t*)0xF8014244U) /**< \brief (FLEXCOM7) USART Number of Errors Register */
  #define REG_FLEXCOM7_US_IF       (*(__IO uint32_t*)0xF801424CU) /**< \brief (FLEXCOM7) USART IrDA Filter Register */
  #define REG_FLEXCOM7_US_MAN      (*(__IO uint32_t*)0xF8014250U) /**< \brief (FLEXCOM7) USART Manchester Configuration Register */
  #define REG_FLEXCOM7_US_LINMR    (*(__IO uint32_t*)0xF8014254U) /**< \brief (FLEXCOM7) USART LIN Mode Register */
  #define REG_FLEXCOM7_US_LINIR    (*(__IO uint32_t*)0xF8014258U) /**< \brief (FLEXCOM7) USART LIN Identifier Register */
  #define REG_FLEXCOM7_US_LINBRR   (*(__I  uint32_t*)0xF801425CU) /**< \brief (FLEXCOM7) USART LIN Baud Rate Register */
  #define REG_FLEXCOM7_US_LONMR    (*(__IO uint32_t*)0xF8014260U) /**< \brief (FLEXCOM7) USART LON Mode Register */
  #define REG_FLEXCOM7_US_LONPR    (*(__IO uint32_t*)0xF8014264U) /**< \brief (FLEXCOM7) USART LON Preamble Register */
  #define REG_FLEXCOM7_US_LONDL    (*(__IO uint32_t*)0xF8014268U) /**< \brief (FLEXCOM7) USART LON Data Length Register */
  #define REG_FLEXCOM7_US_LONL2HDR (*(__IO uint32_t*)0xF801426CU) /**< \brief (FLEXCOM7) USART LON L2HDR Register */
  #define REG_FLEXCOM7_US_LONBL    (*(__I  uint32_t*)0xF8014270U) /**< \brief (FLEXCOM7) USART LON Backlog Register */
  #define REG_FLEXCOM7_US_LONB1TX  (*(__IO uint32_t*)0xF8014274U) /**< \brief (FLEXCOM7) USART LON Beta1 Tx Register */
  #define REG_FLEXCOM7_US_LONB1RX  (*(__IO uint32_t*)0xF8014278U) /**< \brief (FLEXCOM7) USART LON Beta1 Rx Register */
  #define REG_FLEXCOM7_US_LONPRIO  (*(__IO uint32_t*)0xF801427CU) /**< \brief (FLEXCOM7) USART LON Priority Register */
  #define REG_FLEXCOM7_US_IDTTX    (*(__IO uint32_t*)0xF8014280U) /**< \brief (FLEXCOM7) USART LON IDT Tx Register */
  #define REG_FLEXCOM7_US_IDTRX    (*(__IO uint32_t*)0xF8014284U) /**< \brief (FLEXCOM7) USART LON IDT Rx Register */
  #define REG_FLEXCOM7_US_ICDIFF   (*(__IO uint32_t*)0xF8014288U) /**< \brief (FLEXCOM7) USART IC DIFF Register */
  #define REG_FLEXCOM7_US_CMPR     (*(__IO uint32_t*)0xF8014290U) /**< \brief (FLEXCOM7) USART Comparison Register */
  #define REG_FLEXCOM7_US_FMR      (*(__IO uint32_t*)0xF80142A0U) /**< \brief (FLEXCOM7) USART FIFO Mode Register */
  #define REG_FLEXCOM7_US_FLR      (*(__I  uint32_t*)0xF80142A4U) /**< \brief (FLEXCOM7) USART FIFO Level Register */
  #define REG_FLEXCOM7_US_FIER     (*(__O  uint32_t*)0xF80142A8U) /**< \brief (FLEXCOM7) USART FIFO Interrupt Enable Register */
  #define REG_FLEXCOM7_US_FIDR     (*(__O  uint32_t*)0xF80142ACU) /**< \brief (FLEXCOM7) USART FIFO Interrupt Disable Register */
  #define REG_FLEXCOM7_US_FIMR     (*(__I  uint32_t*)0xF80142B0U) /**< \brief (FLEXCOM7) USART FIFO Interrupt Mask Register */
  #define REG_FLEXCOM7_US_FESR     (*(__I  uint32_t*)0xF80142B4U) /**< \brief (FLEXCOM7) USART FIFO Event Status Register */
  #define REG_FLEXCOM7_US_WPMR     (*(__IO uint32_t*)0xF80142E4U) /**< \brief (FLEXCOM7) USART Write Protection Mode Register */
  #define REG_FLEXCOM7_US_WPSR     (*(__I  uint32_t*)0xF80142E8U) /**< \brief (FLEXCOM7) USART Write Protection Status Register */
  #define REG_FLEXCOM7_SPI_CR      (*(__O  uint32_t*)0xF8014400U) /**< \brief (FLEXCOM7) SPI Control Register */
  #define REG_FLEXCOM7_SPI_MR      (*(__IO uint32_t*)0xF8014404U) /**< \brief (FLEXCOM7) SPI Mode Register */
  #define REG_FLEXCOM7_SPI_RDR     (*(__I  uint32_t*)0xF8014408U) /**< \brief (FLEXCOM7) SPI Receive Data Register */
  #define REG_FLEXCOM7_SPI_TDR     (*(__O  uint32_t*)0xF801440CU) /**< \brief (FLEXCOM7) SPI Transmit Data Register */
  #define REG_FLEXCOM7_SPI_SR      (*(__I  uint32_t*)0xF8014410U) /**< \brief (FLEXCOM7) SPI Status Register */
  #define REG_FLEXCOM7_SPI_IER     (*(__O  uint32_t*)0xF8014414U) /**< \brief (FLEXCOM7) SPI Interrupt Enable Register */
  #define REG_FLEXCOM7_SPI_IDR     (*(__O  uint32_t*)0xF8014418U) /**< \brief (FLEXCOM7) SPI Interrupt Disable Register */
  #define REG_FLEXCOM7_SPI_IMR     (*(__I  uint32_t*)0xF801441CU) /**< \brief (FLEXCOM7) SPI Interrupt Mask Register */
  #define REG_FLEXCOM7_SPI_CSR     (*(__IO uint32_t*)0xF8014430U) /**< \brief (FLEXCOM7) SPI Chip Select Register */
  #define REG_FLEXCOM7_SPI_FMR     (*(__IO uint32_t*)0xF8014440U) /**< \brief (FLEXCOM7) SPI FIFO Mode Register */
  #define REG_FLEXCOM7_SPI_FLR     (*(__I  uint32_t*)0xF8014444U) /**< \brief (FLEXCOM7) SPI FIFO Level Register */
  #define REG_FLEXCOM7_SPI_CMPR    (*(__IO uint32_t*)0xF8014448U) /**< \brief (FLEXCOM7) SPI Comparison Register */
  #define REG_FLEXCOM7_SPI_WPMR    (*(__IO uint32_t*)0xF80144E4U) /**< \brief (FLEXCOM7) SPI Write Protection Mode Register */
  #define REG_FLEXCOM7_SPI_WPSR    (*(__I  uint32_t*)0xF80144E8U) /**< \brief (FLEXCOM7) SPI Write Protection Status Register */
  #define REG_FLEXCOM7_TWI_CR      (*(__O  uint32_t*)0xF8014600U) /**< \brief (FLEXCOM7) TWI Control Register */
  #define REG_FLEXCOM7_TWI_MMR     (*(__IO uint32_t*)0xF8014604U) /**< \brief (FLEXCOM7) TWI Master Mode Register */
  #define REG_FLEXCOM7_TWI_SMR     (*(__IO uint32_t*)0xF8014608U) /**< \brief (FLEXCOM7) TWI Slave Mode Register */
  #define REG_FLEXCOM7_TWI_IADR    (*(__IO uint32_t*)0xF801460CU) /**< \brief (FLEXCOM7) TWI Internal Address Register */
  #define REG_FLEXCOM7_TWI_CWGR    (*(__IO uint32_t*)0xF8014610U) /**< \brief (FLEXCOM7) TWI Clock Waveform Generator Register */
  #define REG_FLEXCOM7_TWI_SR      (*(__I  uint32_t*)0xF8014620U) /**< \brief (FLEXCOM7) TWI Status Register */
  #define REG_FLEXCOM7_TWI_IER     (*(__O  uint32_t*)0xF8014624U) /**< \brief (FLEXCOM7) TWI Interrupt Enable Register */
  #define REG_FLEXCOM7_TWI_IDR     (*(__O  uint32_t*)0xF8014628U) /**< \brief (FLEXCOM7) TWI Interrupt Disable Register */
  #define REG_FLEXCOM7_TWI_IMR     (*(__I  uint32_t*)0xF801462CU) /**< \brief (FLEXCOM7) TWI Interrupt Mask Register */
  #define REG_FLEXCOM7_TWI_RHR     (*(__I  uint32_t*)0xF8014630U) /**< \brief (FLEXCOM7) TWI Receive Holding Register */
  #define REG_FLEXCOM7_TWI_THR     (*(__O  uint32_t*)0xF8014634U) /**< \brief (FLEXCOM7) TWI Transmit Holding Register */
  #define REG_FLEXCOM7_TWI_SMBTR   (*(__IO uint32_t*)0xF8014638U) /**< \brief (FLEXCOM7) TWI SMBus Timing Register */
  #define REG_FLEXCOM7_TWI_ACR     (*(__IO uint32_t*)0xF8014640U) /**< \brief (FLEXCOM7) TWI Alternative Command Register */
  #define REG_FLEXCOM7_TWI_FILTR   (*(__IO uint32_t*)0xF8014644U) /**< \brief (FLEXCOM7) TWI Filter Register */
  #define REG_FLEXCOM7_TWI_FMR     (*(__IO uint32_t*)0xF8014650U) /**< \brief (FLEXCOM7) TWI FIFO Mode Register */
  #define REG_FLEXCOM7_TWI_FLR     (*(__I  uint32_t*)0xF8014654U) /**< \brief (FLEXCOM7) TWI FIFO Level Register */
  #define REG_FLEXCOM7_TWI_FSR     (*(__I  uint32_t*)0xF8014660U) /**< \brief (FLEXCOM7) TWI FIFO Status Register */
  #define REG_FLEXCOM7_TWI_FIER    (*(__O  uint32_t*)0xF8014664U) /**< \brief (FLEXCOM7) TWI FIFO Interrupt Enable Register */
  #define REG_FLEXCOM7_TWI_FIDR    (*(__O  uint32_t*)0xF8014668U) /**< \brief (FLEXCOM7) TWI FIFO Interrupt Disable Register */
  #define REG_FLEXCOM7_TWI_FIMR    (*(__I  uint32_t*)0xF801466CU) /**< \brief (FLEXCOM7) TWI FIFO Interrupt Mask Register */
  #define REG_FLEXCOM7_TWI_WPMR    (*(__IO uint32_t*)0xF80146E4U) /**< \brief (FLEXCOM7) TWI Write Protection Mode Register */
  #define REG_FLEXCOM7_TWI_WPSR    (*(__I  uint32_t*)0xF80146E8U) /**< \brief (FLEXCOM7) TWI Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAM9X_FLEXCOM7_INSTANCE_ */
