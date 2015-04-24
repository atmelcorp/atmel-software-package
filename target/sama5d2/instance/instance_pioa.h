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

#ifndef _SAMA5D2_PIOA_INSTANCE_
#define _SAMA5D2_PIOA_INSTANCE_

/* ========== Register definition for PIOA peripheral ========== */
#if (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
  #define REG_PIO_MSKR0                      (0xFC038000U) /**< \brief (PIOA) PIO Mask Register (io_group = 0) */
  #define REG_PIO_CFGR0                      (0xFC038004U) /**< \brief (PIOA) PIO Configuration Register (io_group = 0) */
  #define REG_PIO_PDSR0                      (0xFC038008U) /**< \brief (PIOA) PIO Pin Data Status Register (io_group = 0) */
  #define REG_PIO_LOCKSR0                    (0xFC03800CU) /**< \brief (PIOA) PIO Lock Status Register (io_group = 0) */
  #define REG_PIO_SODR0                      (0xFC038010U) /**< \brief (PIOA) PIO Set Output Data Register (io_group = 0) */
  #define REG_PIO_CODR0                      (0xFC038014U) /**< \brief (PIOA) PIO Clear Output Data Register (io_group = 0) */
  #define REG_PIO_ODSR0                      (0xFC038018U) /**< \brief (PIOA) PIO Output Data Status Register (io_group = 0) */
  #define REG_PIO_IER0                       (0xFC038020U) /**< \brief (PIOA) PIO Interrupt Enable Register (io_group = 0) */
  #define REG_PIO_IDR0                       (0xFC038024U) /**< \brief (PIOA) PIO Interrupt Disable Register (io_group = 0) */
  #define REG_PIO_IMR0                       (0xFC038028U) /**< \brief (PIOA) PIO Interrupt Mask Register (io_group = 0) */
  #define REG_PIO_ISR0                       (0xFC03802CU) /**< \brief (PIOA) PIO Interrupt Status Register (io_group = 0) */
  #define REG_PIO_IOFR0                      (0xFC03803CU) /**< \brief (PIOA) PIO I/O Freeze Register (io_group = 0) */
  #define REG_PIO_MSKR1                      (0xFC038040U) /**< \brief (PIOA) PIO Mask Register (io_group = 1) */
  #define REG_PIO_CFGR1                      (0xFC038044U) /**< \brief (PIOA) PIO Configuration Register (io_group = 1) */
  #define REG_PIO_PDSR1                      (0xFC038048U) /**< \brief (PIOA) PIO Pin Data Status Register (io_group = 1) */
  #define REG_PIO_LOCKSR1                    (0xFC03804CU) /**< \brief (PIOA) PIO Lock Status Register (io_group = 1) */
  #define REG_PIO_SODR1                      (0xFC038050U) /**< \brief (PIOA) PIO Set Output Data Register (io_group = 1) */
  #define REG_PIO_CODR1                      (0xFC038054U) /**< \brief (PIOA) PIO Clear Output Data Register (io_group = 1) */
  #define REG_PIO_ODSR1                      (0xFC038058U) /**< \brief (PIOA) PIO Output Data Status Register (io_group = 1) */
  #define REG_PIO_IER1                       (0xFC038060U) /**< \brief (PIOA) PIO Interrupt Enable Register (io_group = 1) */
  #define REG_PIO_IDR1                       (0xFC038064U) /**< \brief (PIOA) PIO Interrupt Disable Register (io_group = 1) */
  #define REG_PIO_IMR1                       (0xFC038068U) /**< \brief (PIOA) PIO Interrupt Mask Register (io_group = 1) */
  #define REG_PIO_ISR1                       (0xFC03806CU) /**< \brief (PIOA) PIO Interrupt Status Register (io_group = 1) */
  #define REG_PIO_IOFR1                      (0xFC03807CU) /**< \brief (PIOA) PIO I/O Freeze Register (io_group = 1) */
  #define REG_PIO_MSKR2                      (0xFC038080U) /**< \brief (PIOA) PIO Mask Register (io_group = 2) */
  #define REG_PIO_CFGR2                      (0xFC038084U) /**< \brief (PIOA) PIO Configuration Register (io_group = 2) */
  #define REG_PIO_PDSR2                      (0xFC038088U) /**< \brief (PIOA) PIO Pin Data Status Register (io_group = 2) */
  #define REG_PIO_LOCKSR2                    (0xFC03808CU) /**< \brief (PIOA) PIO Lock Status Register (io_group = 2) */
  #define REG_PIO_SODR2                      (0xFC038090U) /**< \brief (PIOA) PIO Set Output Data Register (io_group = 2) */
  #define REG_PIO_CODR2                      (0xFC038094U) /**< \brief (PIOA) PIO Clear Output Data Register (io_group = 2) */
  #define REG_PIO_ODSR2                      (0xFC038098U) /**< \brief (PIOA) PIO Output Data Status Register (io_group = 2) */
  #define REG_PIO_IER2                       (0xFC0380A0U) /**< \brief (PIOA) PIO Interrupt Enable Register (io_group = 2) */
  #define REG_PIO_IDR2                       (0xFC0380A4U) /**< \brief (PIOA) PIO Interrupt Disable Register (io_group = 2) */
  #define REG_PIO_IMR2                       (0xFC0380A8U) /**< \brief (PIOA) PIO Interrupt Mask Register (io_group = 2) */
  #define REG_PIO_ISR2                       (0xFC0380ACU) /**< \brief (PIOA) PIO Interrupt Status Register (io_group = 2) */
  #define REG_PIO_IOFR2                      (0xFC0380BCU) /**< \brief (PIOA) PIO I/O Freeze Register (io_group = 2) */
  #define REG_PIO_MSKR3                      (0xFC0380C0U) /**< \brief (PIOA) PIO Mask Register (io_group = 3) */
  #define REG_PIO_CFGR3                      (0xFC0380C4U) /**< \brief (PIOA) PIO Configuration Register (io_group = 3) */
  #define REG_PIO_PDSR3                      (0xFC0380C8U) /**< \brief (PIOA) PIO Pin Data Status Register (io_group = 3) */
  #define REG_PIO_LOCKSR3                    (0xFC0380CCU) /**< \brief (PIOA) PIO Lock Status Register (io_group = 3) */
  #define REG_PIO_SODR3                      (0xFC0380D0U) /**< \brief (PIOA) PIO Set Output Data Register (io_group = 3) */
  #define REG_PIO_CODR3                      (0xFC0380D4U) /**< \brief (PIOA) PIO Clear Output Data Register (io_group = 3) */
  #define REG_PIO_ODSR3                      (0xFC0380D8U) /**< \brief (PIOA) PIO Output Data Status Register (io_group = 3) */
  #define REG_PIO_IER3                       (0xFC0380E0U) /**< \brief (PIOA) PIO Interrupt Enable Register (io_group = 3) */
  #define REG_PIO_IDR3                       (0xFC0380E4U) /**< \brief (PIOA) PIO Interrupt Disable Register (io_group = 3) */
  #define REG_PIO_IMR3                       (0xFC0380E8U) /**< \brief (PIOA) PIO Interrupt Mask Register (io_group = 3) */
  #define REG_PIO_ISR3                       (0xFC0380ECU) /**< \brief (PIOA) PIO Interrupt Status Register (io_group = 3) */
  #define REG_PIO_IOFR3                      (0xFC0380FCU) /**< \brief (PIOA) PIO I/O Freeze Register (io_group = 3) */
  #define REG_PIO_WPMR                       (0xFC0385E0U) /**< \brief (PIOA) PIO Write Protection Mode Register */
  #define REG_PIO_WPSR                       (0xFC0385E4U) /**< \brief (PIOA) PIO Write Protection Status Register */
  #define REG_PIO_VERSION                    (0xFC0385FCU) /**< \brief (PIOA) Version Register */
  #define REG_S_PIO_MSKR0                    (0xFC039000U) /**< \brief (PIOA) Secure PIO Mask Register (io_group = 0) */
  #define REG_S_PIO_CFGR0                    (0xFC039004U) /**< \brief (PIOA) Secure PIO Configuration Register (io_group = 0) */
  #define REG_S_PIO_PDSR0                    (0xFC039008U) /**< \brief (PIOA) Secure PIO Pin Data Status Register (io_group = 0) */
  #define REG_S_PIO_LOCKSR0                  (0xFC03900CU) /**< \brief (PIOA) Secure PIO Lock Status Register (io_group = 0) */
  #define REG_S_PIO_SODR0                    (0xFC039010U) /**< \brief (PIOA) Secure PIO Set Output Data Register (io_group = 0) */
  #define REG_S_PIO_CODR0                    (0xFC039014U) /**< \brief (PIOA) Secure PIO Clear Output Data Register (io_group = 0) */
  #define REG_S_PIO_ODSR0                    (0xFC039018U) /**< \brief (PIOA) Secure PIO Output Data Status Register (io_group = 0) */
  #define REG_S_PIO_IER0                     (0xFC039020U) /**< \brief (PIOA) Secure PIO Interrupt Enable Register (io_group = 0) */
  #define REG_S_PIO_IDR0                     (0xFC039024U) /**< \brief (PIOA) Secure PIO Interrupt Disable Register (io_group = 0) */
  #define REG_S_PIO_IMR0                     (0xFC039028U) /**< \brief (PIOA) Secure PIO Interrupt Mask Register (io_group = 0) */
  #define REG_S_PIO_ISR0                     (0xFC03902CU) /**< \brief (PIOA) Secure PIO Interrupt Status Register (io_group = 0) */
  #define REG_S_PIO_SIONR0                   (0xFC039030U) /**< \brief (PIOA) Secure PIO Set I/O Non-Secure Register (io_group = 0) */
  #define REG_S_PIO_SIOSR0                   (0xFC039034U) /**< \brief (PIOA) Secure PIO Set I/O Secure Register (io_group = 0) */
  #define REG_S_PIO_IOSSR0                   (0xFC039038U) /**< \brief (PIOA) Secure PIO I/O Security Status Register (io_group = 0) */
  #define REG_S_PIO_IOFR0                    (0xFC03903CU) /**< \brief (PIOA) Secure PIO I/O Freeze Register (io_group = 0) */
  #define REG_S_PIO_MSKR1                    (0xFC039040U) /**< \brief (PIOA) Secure PIO Mask Register (io_group = 1) */
  #define REG_S_PIO_CFGR1                    (0xFC039044U) /**< \brief (PIOA) Secure PIO Configuration Register (io_group = 1) */
  #define REG_S_PIO_PDSR1                    (0xFC039048U) /**< \brief (PIOA) Secure PIO Pin Data Status Register (io_group = 1) */
  #define REG_S_PIO_LOCKSR1                  (0xFC03904CU) /**< \brief (PIOA) Secure PIO Lock Status Register (io_group = 1) */
  #define REG_S_PIO_SODR1                    (0xFC039050U) /**< \brief (PIOA) Secure PIO Set Output Data Register (io_group = 1) */
  #define REG_S_PIO_CODR1                    (0xFC039054U) /**< \brief (PIOA) Secure PIO Clear Output Data Register (io_group = 1) */
  #define REG_S_PIO_ODSR1                    (0xFC039058U) /**< \brief (PIOA) Secure PIO Output Data Status Register (io_group = 1) */
  #define REG_S_PIO_IER1                     (0xFC039060U) /**< \brief (PIOA) Secure PIO Interrupt Enable Register (io_group = 1) */
  #define REG_S_PIO_IDR1                     (0xFC039064U) /**< \brief (PIOA) Secure PIO Interrupt Disable Register (io_group = 1) */
  #define REG_S_PIO_IMR1                     (0xFC039068U) /**< \brief (PIOA) Secure PIO Interrupt Mask Register (io_group = 1) */
  #define REG_S_PIO_ISR1                     (0xFC03906CU) /**< \brief (PIOA) Secure PIO Interrupt Status Register (io_group = 1) */
  #define REG_S_PIO_SIONR1                   (0xFC039070U) /**< \brief (PIOA) Secure PIO Set I/O Non-Secure Register (io_group = 1) */
  #define REG_S_PIO_SIOSR1                   (0xFC039074U) /**< \brief (PIOA) Secure PIO Set I/O Secure Register (io_group = 1) */
  #define REG_S_PIO_IOSSR1                   (0xFC039078U) /**< \brief (PIOA) Secure PIO I/O Security Status Register (io_group = 1) */
  #define REG_S_PIO_IOFR1                    (0xFC03907CU) /**< \brief (PIOA) Secure PIO I/O Freeze Register (io_group = 1) */
  #define REG_S_PIO_MSKR2                    (0xFC039080U) /**< \brief (PIOA) Secure PIO Mask Register (io_group = 2) */
  #define REG_S_PIO_CFGR2                    (0xFC039084U) /**< \brief (PIOA) Secure PIO Configuration Register (io_group = 2) */
  #define REG_S_PIO_PDSR2                    (0xFC039088U) /**< \brief (PIOA) Secure PIO Pin Data Status Register (io_group = 2) */
  #define REG_S_PIO_LOCKSR2                  (0xFC03908CU) /**< \brief (PIOA) Secure PIO Lock Status Register (io_group = 2) */
  #define REG_S_PIO_SODR2                    (0xFC039090U) /**< \brief (PIOA) Secure PIO Set Output Data Register (io_group = 2) */
  #define REG_S_PIO_CODR2                    (0xFC039094U) /**< \brief (PIOA) Secure PIO Clear Output Data Register (io_group = 2) */
  #define REG_S_PIO_ODSR2                    (0xFC039098U) /**< \brief (PIOA) Secure PIO Output Data Status Register (io_group = 2) */
  #define REG_S_PIO_IER2                     (0xFC0390A0U) /**< \brief (PIOA) Secure PIO Interrupt Enable Register (io_group = 2) */
  #define REG_S_PIO_IDR2                     (0xFC0390A4U) /**< \brief (PIOA) Secure PIO Interrupt Disable Register (io_group = 2) */
  #define REG_S_PIO_IMR2                     (0xFC0390A8U) /**< \brief (PIOA) Secure PIO Interrupt Mask Register (io_group = 2) */
  #define REG_S_PIO_ISR2                     (0xFC0390ACU) /**< \brief (PIOA) Secure PIO Interrupt Status Register (io_group = 2) */
  #define REG_S_PIO_SIONR2                   (0xFC0390B0U) /**< \brief (PIOA) Secure PIO Set I/O Non-Secure Register (io_group = 2) */
  #define REG_S_PIO_SIOSR2                   (0xFC0390B4U) /**< \brief (PIOA) Secure PIO Set I/O Secure Register (io_group = 2) */
  #define REG_S_PIO_IOSSR2                   (0xFC0390B8U) /**< \brief (PIOA) Secure PIO I/O Security Status Register (io_group = 2) */
  #define REG_S_PIO_IOFR2                    (0xFC0390BCU) /**< \brief (PIOA) Secure PIO I/O Freeze Register (io_group = 2) */
  #define REG_S_PIO_MSKR3                    (0xFC0390C0U) /**< \brief (PIOA) Secure PIO Mask Register (io_group = 3) */
  #define REG_S_PIO_CFGR3                    (0xFC0390C4U) /**< \brief (PIOA) Secure PIO Configuration Register (io_group = 3) */
  #define REG_S_PIO_PDSR3                    (0xFC0390C8U) /**< \brief (PIOA) Secure PIO Pin Data Status Register (io_group = 3) */
  #define REG_S_PIO_LOCKSR3                  (0xFC0390CCU) /**< \brief (PIOA) Secure PIO Lock Status Register (io_group = 3) */
  #define REG_S_PIO_SODR3                    (0xFC0390D0U) /**< \brief (PIOA) Secure PIO Set Output Data Register (io_group = 3) */
  #define REG_S_PIO_CODR3                    (0xFC0390D4U) /**< \brief (PIOA) Secure PIO Clear Output Data Register (io_group = 3) */
  #define REG_S_PIO_ODSR3                    (0xFC0390D8U) /**< \brief (PIOA) Secure PIO Output Data Status Register (io_group = 3) */
  #define REG_S_PIO_IER3                     (0xFC0390E0U) /**< \brief (PIOA) Secure PIO Interrupt Enable Register (io_group = 3) */
  #define REG_S_PIO_IDR3                     (0xFC0390E4U) /**< \brief (PIOA) Secure PIO Interrupt Disable Register (io_group = 3) */
  #define REG_S_PIO_IMR3                     (0xFC0390E8U) /**< \brief (PIOA) Secure PIO Interrupt Mask Register (io_group = 3) */
  #define REG_S_PIO_ISR3                     (0xFC0390ECU) /**< \brief (PIOA) Secure PIO Interrupt Status Register (io_group = 3) */
  #define REG_S_PIO_SIONR3                   (0xFC0390F0U) /**< \brief (PIOA) Secure PIO Set I/O Non-Secure Register (io_group = 3) */
  #define REG_S_PIO_SIOSR3                   (0xFC0390F4U) /**< \brief (PIOA) Secure PIO Set I/O Secure Register (io_group = 3) */
  #define REG_S_PIO_IOSSR3                   (0xFC0390F8U) /**< \brief (PIOA) Secure PIO I/O Security Status Register (io_group = 3) */
  #define REG_S_PIO_IOFR3                    (0xFC0390FCU) /**< \brief (PIOA) Secure PIO I/O Freeze Register (io_group = 3) */
  #define REG_S_PIO_SCDR                     (0xFC039500U) /**< \brief (PIOA) Secure PIO Slow Clock Divider Debouncing Register */
  #define REG_S_PIO_WPMR                     (0xFC0395E0U) /**< \brief (PIOA) Secure PIO Write Protection Mode Register */
  #define REG_S_PIO_WPSR                     (0xFC0395E4U) /**< \brief (PIOA) Secure PIO Write Protection Status Register */
#else
  #define REG_PIO_MSKR0     (*(__IO uint32_t*)0xFC038000U) /**< \brief (PIOA) PIO Mask Register (io_group = 0) */
  #define REG_PIO_CFGR0     (*(__IO uint32_t*)0xFC038004U) /**< \brief (PIOA) PIO Configuration Register (io_group = 0) */
  #define REG_PIO_PDSR0     (*(__I  uint32_t*)0xFC038008U) /**< \brief (PIOA) PIO Pin Data Status Register (io_group = 0) */
  #define REG_PIO_LOCKSR0   (*(__I  uint32_t*)0xFC03800CU) /**< \brief (PIOA) PIO Lock Status Register (io_group = 0) */
  #define REG_PIO_SODR0     (*(__O  uint32_t*)0xFC038010U) /**< \brief (PIOA) PIO Set Output Data Register (io_group = 0) */
  #define REG_PIO_CODR0     (*(__O  uint32_t*)0xFC038014U) /**< \brief (PIOA) PIO Clear Output Data Register (io_group = 0) */
  #define REG_PIO_ODSR0     (*(__IO uint32_t*)0xFC038018U) /**< \brief (PIOA) PIO Output Data Status Register (io_group = 0) */
  #define REG_PIO_IER0      (*(__O  uint32_t*)0xFC038020U) /**< \brief (PIOA) PIO Interrupt Enable Register (io_group = 0) */
  #define REG_PIO_IDR0      (*(__O  uint32_t*)0xFC038024U) /**< \brief (PIOA) PIO Interrupt Disable Register (io_group = 0) */
  #define REG_PIO_IMR0      (*(__I  uint32_t*)0xFC038028U) /**< \brief (PIOA) PIO Interrupt Mask Register (io_group = 0) */
  #define REG_PIO_ISR0      (*(__I  uint32_t*)0xFC03802CU) /**< \brief (PIOA) PIO Interrupt Status Register (io_group = 0) */
  #define REG_PIO_IOFR0     (*(__O  uint32_t*)0xFC03803CU) /**< \brief (PIOA) PIO I/O Freeze Register (io_group = 0) */
  #define REG_PIO_MSKR1     (*(__IO uint32_t*)0xFC038040U) /**< \brief (PIOA) PIO Mask Register (io_group = 1) */
  #define REG_PIO_CFGR1     (*(__IO uint32_t*)0xFC038044U) /**< \brief (PIOA) PIO Configuration Register (io_group = 1) */
  #define REG_PIO_PDSR1     (*(__I  uint32_t*)0xFC038048U) /**< \brief (PIOA) PIO Pin Data Status Register (io_group = 1) */
  #define REG_PIO_LOCKSR1   (*(__I  uint32_t*)0xFC03804CU) /**< \brief (PIOA) PIO Lock Status Register (io_group = 1) */
  #define REG_PIO_SODR1     (*(__O  uint32_t*)0xFC038050U) /**< \brief (PIOA) PIO Set Output Data Register (io_group = 1) */
  #define REG_PIO_CODR1     (*(__O  uint32_t*)0xFC038054U) /**< \brief (PIOA) PIO Clear Output Data Register (io_group = 1) */
  #define REG_PIO_ODSR1     (*(__IO uint32_t*)0xFC038058U) /**< \brief (PIOA) PIO Output Data Status Register (io_group = 1) */
  #define REG_PIO_IER1      (*(__O  uint32_t*)0xFC038060U) /**< \brief (PIOA) PIO Interrupt Enable Register (io_group = 1) */
  #define REG_PIO_IDR1      (*(__O  uint32_t*)0xFC038064U) /**< \brief (PIOA) PIO Interrupt Disable Register (io_group = 1) */
  #define REG_PIO_IMR1      (*(__I  uint32_t*)0xFC038068U) /**< \brief (PIOA) PIO Interrupt Mask Register (io_group = 1) */
  #define REG_PIO_ISR1      (*(__I  uint32_t*)0xFC03806CU) /**< \brief (PIOA) PIO Interrupt Status Register (io_group = 1) */
  #define REG_PIO_IOFR1     (*(__O  uint32_t*)0xFC03807CU) /**< \brief (PIOA) PIO I/O Freeze Register (io_group = 1) */
  #define REG_PIO_MSKR2     (*(__IO uint32_t*)0xFC038080U) /**< \brief (PIOA) PIO Mask Register (io_group = 2) */
  #define REG_PIO_CFGR2     (*(__IO uint32_t*)0xFC038084U) /**< \brief (PIOA) PIO Configuration Register (io_group = 2) */
  #define REG_PIO_PDSR2     (*(__I  uint32_t*)0xFC038088U) /**< \brief (PIOA) PIO Pin Data Status Register (io_group = 2) */
  #define REG_PIO_LOCKSR2   (*(__I  uint32_t*)0xFC03808CU) /**< \brief (PIOA) PIO Lock Status Register (io_group = 2) */
  #define REG_PIO_SODR2     (*(__O  uint32_t*)0xFC038090U) /**< \brief (PIOA) PIO Set Output Data Register (io_group = 2) */
  #define REG_PIO_CODR2     (*(__O  uint32_t*)0xFC038094U) /**< \brief (PIOA) PIO Clear Output Data Register (io_group = 2) */
  #define REG_PIO_ODSR2     (*(__IO uint32_t*)0xFC038098U) /**< \brief (PIOA) PIO Output Data Status Register (io_group = 2) */
  #define REG_PIO_IER2      (*(__O  uint32_t*)0xFC0380A0U) /**< \brief (PIOA) PIO Interrupt Enable Register (io_group = 2) */
  #define REG_PIO_IDR2      (*(__O  uint32_t*)0xFC0380A4U) /**< \brief (PIOA) PIO Interrupt Disable Register (io_group = 2) */
  #define REG_PIO_IMR2      (*(__I  uint32_t*)0xFC0380A8U) /**< \brief (PIOA) PIO Interrupt Mask Register (io_group = 2) */
  #define REG_PIO_ISR2      (*(__I  uint32_t*)0xFC0380ACU) /**< \brief (PIOA) PIO Interrupt Status Register (io_group = 2) */
  #define REG_PIO_IOFR2     (*(__O  uint32_t*)0xFC0380BCU) /**< \brief (PIOA) PIO I/O Freeze Register (io_group = 2) */
  #define REG_PIO_MSKR3     (*(__IO uint32_t*)0xFC0380C0U) /**< \brief (PIOA) PIO Mask Register (io_group = 3) */
  #define REG_PIO_CFGR3     (*(__IO uint32_t*)0xFC0380C4U) /**< \brief (PIOA) PIO Configuration Register (io_group = 3) */
  #define REG_PIO_PDSR3     (*(__I  uint32_t*)0xFC0380C8U) /**< \brief (PIOA) PIO Pin Data Status Register (io_group = 3) */
  #define REG_PIO_LOCKSR3   (*(__I  uint32_t*)0xFC0380CCU) /**< \brief (PIOA) PIO Lock Status Register (io_group = 3) */
  #define REG_PIO_SODR3     (*(__O  uint32_t*)0xFC0380D0U) /**< \brief (PIOA) PIO Set Output Data Register (io_group = 3) */
  #define REG_PIO_CODR3     (*(__O  uint32_t*)0xFC0380D4U) /**< \brief (PIOA) PIO Clear Output Data Register (io_group = 3) */
  #define REG_PIO_ODSR3     (*(__IO uint32_t*)0xFC0380D8U) /**< \brief (PIOA) PIO Output Data Status Register (io_group = 3) */
  #define REG_PIO_IER3      (*(__O  uint32_t*)0xFC0380E0U) /**< \brief (PIOA) PIO Interrupt Enable Register (io_group = 3) */
  #define REG_PIO_IDR3      (*(__O  uint32_t*)0xFC0380E4U) /**< \brief (PIOA) PIO Interrupt Disable Register (io_group = 3) */
  #define REG_PIO_IMR3      (*(__I  uint32_t*)0xFC0380E8U) /**< \brief (PIOA) PIO Interrupt Mask Register (io_group = 3) */
  #define REG_PIO_ISR3      (*(__I  uint32_t*)0xFC0380ECU) /**< \brief (PIOA) PIO Interrupt Status Register (io_group = 3) */
  #define REG_PIO_IOFR3     (*(__O  uint32_t*)0xFC0380FCU) /**< \brief (PIOA) PIO I/O Freeze Register (io_group = 3) */
  #define REG_PIO_WPMR      (*(__IO uint32_t*)0xFC0385E0U) /**< \brief (PIOA) PIO Write Protection Mode Register */
  #define REG_PIO_WPSR      (*(__I  uint32_t*)0xFC0385E4U) /**< \brief (PIOA) PIO Write Protection Status Register */
  #define REG_PIO_VERSION   (*(__I  uint32_t*)0xFC0385FCU) /**< \brief (PIOA) Version Register */
  #define REG_S_PIO_MSKR0   (*(__IO uint32_t*)0xFC039000U) /**< \brief (PIOA) Secure PIO Mask Register (io_group = 0) */
  #define REG_S_PIO_CFGR0   (*(__IO uint32_t*)0xFC039004U) /**< \brief (PIOA) Secure PIO Configuration Register (io_group = 0) */
  #define REG_S_PIO_PDSR0   (*(__I  uint32_t*)0xFC039008U) /**< \brief (PIOA) Secure PIO Pin Data Status Register (io_group = 0) */
  #define REG_S_PIO_LOCKSR0 (*(__I  uint32_t*)0xFC03900CU) /**< \brief (PIOA) Secure PIO Lock Status Register (io_group = 0) */
  #define REG_S_PIO_SODR0   (*(__O  uint32_t*)0xFC039010U) /**< \brief (PIOA) Secure PIO Set Output Data Register (io_group = 0) */
  #define REG_S_PIO_CODR0   (*(__O  uint32_t*)0xFC039014U) /**< \brief (PIOA) Secure PIO Clear Output Data Register (io_group = 0) */
  #define REG_S_PIO_ODSR0   (*(__IO uint32_t*)0xFC039018U) /**< \brief (PIOA) Secure PIO Output Data Status Register (io_group = 0) */
  #define REG_S_PIO_IER0    (*(__O  uint32_t*)0xFC039020U) /**< \brief (PIOA) Secure PIO Interrupt Enable Register (io_group = 0) */
  #define REG_S_PIO_IDR0    (*(__O  uint32_t*)0xFC039024U) /**< \brief (PIOA) Secure PIO Interrupt Disable Register (io_group = 0) */
  #define REG_S_PIO_IMR0    (*(__I  uint32_t*)0xFC039028U) /**< \brief (PIOA) Secure PIO Interrupt Mask Register (io_group = 0) */
  #define REG_S_PIO_ISR0    (*(__I  uint32_t*)0xFC03902CU) /**< \brief (PIOA) Secure PIO Interrupt Status Register (io_group = 0) */
  #define REG_S_PIO_SIONR0  (*(__O  uint32_t*)0xFC039030U) /**< \brief (PIOA) Secure PIO Set I/O Non-Secure Register (io_group = 0) */
  #define REG_S_PIO_SIOSR0  (*(__O  uint32_t*)0xFC039034U) /**< \brief (PIOA) Secure PIO Set I/O Secure Register (io_group = 0) */
  #define REG_S_PIO_IOSSR0  (*(__I  uint32_t*)0xFC039038U) /**< \brief (PIOA) Secure PIO I/O Security Status Register (io_group = 0) */
  #define REG_S_PIO_IOFR0   (*(__O  uint32_t*)0xFC03903CU) /**< \brief (PIOA) Secure PIO I/O Freeze Register (io_group = 0) */
  #define REG_S_PIO_MSKR1   (*(__IO uint32_t*)0xFC039040U) /**< \brief (PIOA) Secure PIO Mask Register (io_group = 1) */
  #define REG_S_PIO_CFGR1   (*(__IO uint32_t*)0xFC039044U) /**< \brief (PIOA) Secure PIO Configuration Register (io_group = 1) */
  #define REG_S_PIO_PDSR1   (*(__I  uint32_t*)0xFC039048U) /**< \brief (PIOA) Secure PIO Pin Data Status Register (io_group = 1) */
  #define REG_S_PIO_LOCKSR1 (*(__I  uint32_t*)0xFC03904CU) /**< \brief (PIOA) Secure PIO Lock Status Register (io_group = 1) */
  #define REG_S_PIO_SODR1   (*(__O  uint32_t*)0xFC039050U) /**< \brief (PIOA) Secure PIO Set Output Data Register (io_group = 1) */
  #define REG_S_PIO_CODR1   (*(__O  uint32_t*)0xFC039054U) /**< \brief (PIOA) Secure PIO Clear Output Data Register (io_group = 1) */
  #define REG_S_PIO_ODSR1   (*(__IO uint32_t*)0xFC039058U) /**< \brief (PIOA) Secure PIO Output Data Status Register (io_group = 1) */
  #define REG_S_PIO_IER1    (*(__O  uint32_t*)0xFC039060U) /**< \brief (PIOA) Secure PIO Interrupt Enable Register (io_group = 1) */
  #define REG_S_PIO_IDR1    (*(__O  uint32_t*)0xFC039064U) /**< \brief (PIOA) Secure PIO Interrupt Disable Register (io_group = 1) */
  #define REG_S_PIO_IMR1    (*(__I  uint32_t*)0xFC039068U) /**< \brief (PIOA) Secure PIO Interrupt Mask Register (io_group = 1) */
  #define REG_S_PIO_ISR1    (*(__I  uint32_t*)0xFC03906CU) /**< \brief (PIOA) Secure PIO Interrupt Status Register (io_group = 1) */
  #define REG_S_PIO_SIONR1  (*(__O  uint32_t*)0xFC039070U) /**< \brief (PIOA) Secure PIO Set I/O Non-Secure Register (io_group = 1) */
  #define REG_S_PIO_SIOSR1  (*(__O  uint32_t*)0xFC039074U) /**< \brief (PIOA) Secure PIO Set I/O Secure Register (io_group = 1) */
  #define REG_S_PIO_IOSSR1  (*(__I  uint32_t*)0xFC039078U) /**< \brief (PIOA) Secure PIO I/O Security Status Register (io_group = 1) */
  #define REG_S_PIO_IOFR1   (*(__O  uint32_t*)0xFC03907CU) /**< \brief (PIOA) Secure PIO I/O Freeze Register (io_group = 1) */
  #define REG_S_PIO_MSKR2   (*(__IO uint32_t*)0xFC039080U) /**< \brief (PIOA) Secure PIO Mask Register (io_group = 2) */
  #define REG_S_PIO_CFGR2   (*(__IO uint32_t*)0xFC039084U) /**< \brief (PIOA) Secure PIO Configuration Register (io_group = 2) */
  #define REG_S_PIO_PDSR2   (*(__I  uint32_t*)0xFC039088U) /**< \brief (PIOA) Secure PIO Pin Data Status Register (io_group = 2) */
  #define REG_S_PIO_LOCKSR2 (*(__I  uint32_t*)0xFC03908CU) /**< \brief (PIOA) Secure PIO Lock Status Register (io_group = 2) */
  #define REG_S_PIO_SODR2   (*(__O  uint32_t*)0xFC039090U) /**< \brief (PIOA) Secure PIO Set Output Data Register (io_group = 2) */
  #define REG_S_PIO_CODR2   (*(__O  uint32_t*)0xFC039094U) /**< \brief (PIOA) Secure PIO Clear Output Data Register (io_group = 2) */
  #define REG_S_PIO_ODSR2   (*(__IO uint32_t*)0xFC039098U) /**< \brief (PIOA) Secure PIO Output Data Status Register (io_group = 2) */
  #define REG_S_PIO_IER2    (*(__O  uint32_t*)0xFC0390A0U) /**< \brief (PIOA) Secure PIO Interrupt Enable Register (io_group = 2) */
  #define REG_S_PIO_IDR2    (*(__O  uint32_t*)0xFC0390A4U) /**< \brief (PIOA) Secure PIO Interrupt Disable Register (io_group = 2) */
  #define REG_S_PIO_IMR2    (*(__I  uint32_t*)0xFC0390A8U) /**< \brief (PIOA) Secure PIO Interrupt Mask Register (io_group = 2) */
  #define REG_S_PIO_ISR2    (*(__I  uint32_t*)0xFC0390ACU) /**< \brief (PIOA) Secure PIO Interrupt Status Register (io_group = 2) */
  #define REG_S_PIO_SIONR2  (*(__O  uint32_t*)0xFC0390B0U) /**< \brief (PIOA) Secure PIO Set I/O Non-Secure Register (io_group = 2) */
  #define REG_S_PIO_SIOSR2  (*(__O  uint32_t*)0xFC0390B4U) /**< \brief (PIOA) Secure PIO Set I/O Secure Register (io_group = 2) */
  #define REG_S_PIO_IOSSR2  (*(__I  uint32_t*)0xFC0390B8U) /**< \brief (PIOA) Secure PIO I/O Security Status Register (io_group = 2) */
  #define REG_S_PIO_IOFR2   (*(__O  uint32_t*)0xFC0390BCU) /**< \brief (PIOA) Secure PIO I/O Freeze Register (io_group = 2) */
  #define REG_S_PIO_MSKR3   (*(__IO uint32_t*)0xFC0390C0U) /**< \brief (PIOA) Secure PIO Mask Register (io_group = 3) */
  #define REG_S_PIO_CFGR3   (*(__IO uint32_t*)0xFC0390C4U) /**< \brief (PIOA) Secure PIO Configuration Register (io_group = 3) */
  #define REG_S_PIO_PDSR3   (*(__I  uint32_t*)0xFC0390C8U) /**< \brief (PIOA) Secure PIO Pin Data Status Register (io_group = 3) */
  #define REG_S_PIO_LOCKSR3 (*(__I  uint32_t*)0xFC0390CCU) /**< \brief (PIOA) Secure PIO Lock Status Register (io_group = 3) */
  #define REG_S_PIO_SODR3   (*(__O  uint32_t*)0xFC0390D0U) /**< \brief (PIOA) Secure PIO Set Output Data Register (io_group = 3) */
  #define REG_S_PIO_CODR3   (*(__O  uint32_t*)0xFC0390D4U) /**< \brief (PIOA) Secure PIO Clear Output Data Register (io_group = 3) */
  #define REG_S_PIO_ODSR3   (*(__IO uint32_t*)0xFC0390D8U) /**< \brief (PIOA) Secure PIO Output Data Status Register (io_group = 3) */
  #define REG_S_PIO_IER3    (*(__O  uint32_t*)0xFC0390E0U) /**< \brief (PIOA) Secure PIO Interrupt Enable Register (io_group = 3) */
  #define REG_S_PIO_IDR3    (*(__O  uint32_t*)0xFC0390E4U) /**< \brief (PIOA) Secure PIO Interrupt Disable Register (io_group = 3) */
  #define REG_S_PIO_IMR3    (*(__I  uint32_t*)0xFC0390E8U) /**< \brief (PIOA) Secure PIO Interrupt Mask Register (io_group = 3) */
  #define REG_S_PIO_ISR3    (*(__I  uint32_t*)0xFC0390ECU) /**< \brief (PIOA) Secure PIO Interrupt Status Register (io_group = 3) */
  #define REG_S_PIO_SIONR3  (*(__O  uint32_t*)0xFC0390F0U) /**< \brief (PIOA) Secure PIO Set I/O Non-Secure Register (io_group = 3) */
  #define REG_S_PIO_SIOSR3  (*(__O  uint32_t*)0xFC0390F4U) /**< \brief (PIOA) Secure PIO Set I/O Secure Register (io_group = 3) */
  #define REG_S_PIO_IOSSR3  (*(__I  uint32_t*)0xFC0390F8U) /**< \brief (PIOA) Secure PIO I/O Security Status Register (io_group = 3) */
  #define REG_S_PIO_IOFR3   (*(__O  uint32_t*)0xFC0390FCU) /**< \brief (PIOA) Secure PIO I/O Freeze Register (io_group = 3) */
  #define REG_S_PIO_SCDR    (*(__IO uint32_t*)0xFC039500U) /**< \brief (PIOA) Secure PIO Slow Clock Divider Debouncing Register */
  #define REG_S_PIO_WPMR    (*(__IO uint32_t*)0xFC0395E0U) /**< \brief (PIOA) Secure PIO Write Protection Mode Register */
  #define REG_S_PIO_WPSR    (*(__I  uint32_t*)0xFC0395E4U) /**< \brief (PIOA) Secure PIO Write Protection Status Register */
#endif /* (defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

#endif /* _SAMA5D2_PIOA_INSTANCE_ */
