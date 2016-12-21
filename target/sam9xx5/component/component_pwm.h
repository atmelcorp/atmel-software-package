/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2014, Atmel Corporation                                        */
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

#ifndef _SAM9X_PWM_COMPONENT_
#define _SAM9X_PWM_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Pulse Width Modulation Controller */
/* ============================================================================= */
/** \addtogroup SAM9X_PWM Pulse Width Modulation Controller */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief PwmCh hardware registers */
typedef struct {
	__IO uint32_t PWM_CMR;     /**< \brief (PwmCh Offset: 0x0) PWM Channel Mode Register */
	__IO uint32_t PWM_CDTY;    /**< \brief (PwmCh Offset: 0x4) PWM Channel Duty Cycle Register */
	__IO uint32_t PWM_CPRD;    /**< \brief (PwmCh Offset: 0x8) PWM Channel Period Register */
	__I  uint32_t PWM_CCNT;    /**< \brief (PwmCh Offset: 0xC) PWM Channel Counter Register */
	__O  uint32_t PWM_CUPD;    /**< \brief (PwmCh Offset: 0x10) PWM Channel Update Register */
	__I  uint32_t Reserved1[3];
} PwmCh;
/** \brief Pwm hardware registers */
typedef struct {
	__IO uint32_t PWM_CLK;       /**< \brief (Pwm Offset: 0x00) PWM Clock Register */
	__O  uint32_t PWM_ENA;       /**< \brief (Pwm Offset: 0x04) PWM Enable Register */
	__O  uint32_t PWM_DIS;       /**< \brief (Pwm Offset: 0x08) PWM Disable Register */
	__I  uint32_t PWM_SR;        /**< \brief (Pwm Offset: 0x0C) PWM Status Register */
	__O  uint32_t PWM_IER1;      /**< \brief (Pwm Offset: 0x10) PWM Interrupt Enable Register 1 */
	__O  uint32_t PWM_IDR1;      /**< \brief (Pwm Offset: 0x14) PWM Interrupt Disable Register 1 */
	__I  uint32_t PWM_IMR1;      /**< \brief (Pwm Offset: 0x18) PWM Interrupt Mask Register 1 */
	__I  uint32_t PWM_ISR1;      /**< \brief (Pwm Offset: 0x1C) PWM Interrupt Status Register 1 */
	__I  uint32_t Reserved1[120];
	     PwmCh    PWM_CH[4];     /**< \brief (Pwm Offset: 0x200) ch_num = 0 .. 3 */
} Pwm;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- PWM_CLK : (PWM Offset: 0x00) PWM Clock Register -------- */
#define PWM_CLK_DIVA_Pos 0
#define PWM_CLK_DIVA_Msk (0xffu << PWM_CLK_DIVA_Pos) /**< \brief (PWM_CLK) CLKA Divide Factor */
#define PWM_CLK_DIVA(value) ((PWM_CLK_DIVA_Msk & ((value) << PWM_CLK_DIVA_Pos)))
#define   PWM_CLK_DIVA_CLKA_OFF (0x0u << 0) /**< \brief (PWM_CLK) CLKA clock is turned off */
#define   PWM_CLK_DIVA_CLKA_PREA (0x1u << 0) /**< \brief (PWM_CLK) CLKA clock is clock selected by PREA */
#define PWM_CLK_PREA_Pos 8
#define PWM_CLK_PREA_Msk (0xfu << PWM_CLK_PREA_Pos) /**< \brief (PWM_CLK) CLKA Source Clock Selection */
#define PWM_CLK_PREA(value) ((PWM_CLK_PREA_Msk & ((value) << PWM_CLK_PREA_Pos)))
#define   PWM_CLK_PREA_CLK (0x0u << 8) /**< \brief (PWM_CLK) Peripheral Clock */
#define   PWM_CLK_PREA_CLK_DIV2 (0x1u << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 2 */
#define   PWM_CLK_PREA_CLK_DIV4 (0x2u << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 4 */
#define   PWM_CLK_PREA_CLK_DIV8 (0x3u << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 8 */
#define   PWM_CLK_PREA_CLK_DIV16 (0x4u << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 16 */
#define   PWM_CLK_PREA_CLK_DIV32 (0x5u << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 32 */
#define   PWM_CLK_PREA_CLK_DIV64 (0x6u << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 64 */
#define   PWM_CLK_PREA_CLK_DIV128 (0x7u << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 128 */
#define   PWM_CLK_PREA_CLK_DIV256 (0x8u << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 256 */
#define   PWM_CLK_PREA_CLK_DIV512 (0x9u << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 512 */
#define   PWM_CLK_PREA_CLK_DIV1024 (0xAu << 8) /**< \brief (PWM_CLK) Peripheral Clock divided by 1024 */
#define PWM_CLK_DIVB_Pos 16
#define PWM_CLK_DIVB_Msk (0xffu << PWM_CLK_DIVB_Pos) /**< \brief (PWM_CLK) CLKB Divide Factor */
#define PWM_CLK_DIVB(value) ((PWM_CLK_DIVB_Msk & ((value) << PWM_CLK_DIVB_Pos)))
#define   PWM_CLK_DIVB_CLKB_OFF (0x0u << 16) /**< \brief (PWM_CLK) CLKB clock is turned off */
#define   PWM_CLK_DIVB_CLKB_PREB (0x1u << 16) /**< \brief (PWM_CLK) CLKB clock is clock selected by PREB */
#define PWM_CLK_PREB_Pos 24
#define PWM_CLK_PREB_Msk (0xfu << PWM_CLK_PREB_Pos) /**< \brief (PWM_CLK) CLKB Source Clock Selection */
#define PWM_CLK_PREB(value) ((PWM_CLK_PREB_Msk & ((value) << PWM_CLK_PREB_Pos)))
#define   PWM_CLK_PREB_CLK (0x0u << 24) /**< \brief (PWM_CLK) Peripheral Clock */
#define   PWM_CLK_PREB_CLK_DIV2 (0x1u << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 2 */
#define   PWM_CLK_PREB_CLK_DIV4 (0x2u << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 4 */
#define   PWM_CLK_PREB_CLK_DIV8 (0x3u << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 8 */
#define   PWM_CLK_PREB_CLK_DIV16 (0x4u << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 16 */
#define   PWM_CLK_PREB_CLK_DIV32 (0x5u << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 32 */
#define   PWM_CLK_PREB_CLK_DIV64 (0x6u << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 64 */
#define   PWM_CLK_PREB_CLK_DIV128 (0x7u << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 128 */
#define   PWM_CLK_PREB_CLK_DIV256 (0x8u << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 256 */
#define   PWM_CLK_PREB_CLK_DIV512 (0x9u << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 512 */
#define   PWM_CLK_PREB_CLK_DIV1024 (0xAu << 24) /**< \brief (PWM_CLK) Peripheral Clock divided by 1024 */
/* -------- PWM_ENA : (PWM Offset: 0x04) PWM Enable Register -------- */
#define PWM_ENA_CHID0 (0x1u << 0) /**< \brief (PWM_ENA) Channel ID */
#define PWM_ENA_CHID1 (0x1u << 1) /**< \brief (PWM_ENA) Channel ID */
#define PWM_ENA_CHID2 (0x1u << 2) /**< \brief (PWM_ENA) Channel ID */
#define PWM_ENA_CHID3 (0x1u << 3) /**< \brief (PWM_ENA) Channel ID */
/* -------- PWM_DIS : (PWM Offset: 0x08) PWM Disable Register -------- */
#define PWM_DIS_CHID0 (0x1u << 0) /**< \brief (PWM_DIS) Channel ID */
#define PWM_DIS_CHID1 (0x1u << 1) /**< \brief (PWM_DIS) Channel ID */
#define PWM_DIS_CHID2 (0x1u << 2) /**< \brief (PWM_DIS) Channel ID */
#define PWM_DIS_CHID3 (0x1u << 3) /**< \brief (PWM_DIS) Channel ID */
/* -------- PWM_SR : (PWM Offset: 0x0C) PWM Status Register -------- */
#define PWM_SR_CHID0 (0x1u << 0) /**< \brief (PWM_SR) Channel ID */
#define PWM_SR_CHID1 (0x1u << 1) /**< \brief (PWM_SR) Channel ID */
#define PWM_SR_CHID2 (0x1u << 2) /**< \brief (PWM_SR) Channel ID */
#define PWM_SR_CHID3 (0x1u << 3) /**< \brief (PWM_SR) Channel ID */
/* -------- PWM_IER1 : (PWM Offset: 0x10) PWM Interrupt Enable Register 1 -------- */
#define PWM_IER1_CHID0 (0x1u << 0) /**< \brief (PWM_IER1) Counter Event on Channel 0 Interrupt Enable */
#define PWM_IER1_CHID1 (0x1u << 1) /**< \brief (PWM_IER1) Counter Event on Channel 1 Interrupt Enable */
#define PWM_IER1_CHID2 (0x1u << 2) /**< \brief (PWM_IER1) Counter Event on Channel 2 Interrupt Enable */
#define PWM_IER1_CHID3 (0x1u << 3) /**< \brief (PWM_IER1) Counter Event on Channel 3 Interrupt Enable */
/* -------- PWM_IDR1 : (PWM Offset: 0x14) PWM Interrupt Disable Register 1 -------- */
#define PWM_IDR1_CHID0 (0x1u << 0) /**< \brief (PWM_IDR1) Counter Event on Channel 0 Interrupt Disable */
#define PWM_IDR1_CHID1 (0x1u << 1) /**< \brief (PWM_IDR1) Counter Event on Channel 1 Interrupt Disable */
#define PWM_IDR1_CHID2 (0x1u << 2) /**< \brief (PWM_IDR1) Counter Event on Channel 2 Interrupt Disable */
#define PWM_IDR1_CHID3 (0x1u << 3) /**< \brief (PWM_IDR1) Counter Event on Channel 3 Interrupt Disable */
/* -------- PWM_IMR1 : (PWM Offset: 0x18) PWM Interrupt Mask Register 1 -------- */
#define PWM_IMR1_CHID0 (0x1u << 0) /**< \brief (PWM_IMR1) Counter Event on Channel 0 Interrupt Mask */
#define PWM_IMR1_CHID1 (0x1u << 1) /**< \brief (PWM_IMR1) Counter Event on Channel 1 Interrupt Mask */
#define PWM_IMR1_CHID2 (0x1u << 2) /**< \brief (PWM_IMR1) Counter Event on Channel 2 Interrupt Mask */
#define PWM_IMR1_CHID3 (0x1u << 3) /**< \brief (PWM_IMR1) Counter Event on Channel 3 Interrupt Mask */
/* -------- PWM_ISR1 : (PWM Offset: 0x1C) PWM Interrupt Status Register 1 -------- */
#define PWM_ISR1_CHID0 (0x1u << 0) /**< \brief (PWM_ISR1) Counter Event on Channel 0 */
#define PWM_ISR1_CHID1 (0x1u << 1) /**< \brief (PWM_ISR1) Counter Event on Channel 1 */
#define PWM_ISR1_CHID2 (0x1u << 2) /**< \brief (PWM_ISR1) Counter Event on Channel 2 */
#define PWM_ISR1_CHID3 (0x1u << 3) /**< \brief (PWM_ISR1) Counter Event on Channel 3 */
/* -------- PWM_CMR : (PWM Offset: N/A) PWM Channel Mode Register -------- */
#define PWM_CMR_CPRE_Pos 0
#define PWM_CMR_CPRE_Msk (0xfu << PWM_CMR_CPRE_Pos) /**< \brief (PWM_CMR) Channel Prescaler */
#define PWM_CMR_CPRE(value) ((PWM_CMR_CPRE_Msk & ((value) << PWM_CMR_CPRE_Pos)))
#define   PWM_CMR_CPRE_MCK (0x0u << 0) /**< \brief (PWM_CMR) Peripheral clock */
#define   PWM_CMR_CPRE_MCK_DIV2 (0x1u << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 2 */
#define   PWM_CMR_CPRE_MCK_DIV4 (0x2u << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 4 */
#define   PWM_CMR_CPRE_MCK_DIV8 (0x3u << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 8 */
#define   PWM_CMR_CPRE_MCK_DIV16 (0x4u << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 16 */
#define   PWM_CMR_CPRE_MCK_DIV32 (0x5u << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 32 */
#define   PWM_CMR_CPRE_MCK_DIV64 (0x6u << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 64 */
#define   PWM_CMR_CPRE_MCK_DIV128 (0x7u << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 128 */
#define   PWM_CMR_CPRE_MCK_DIV256 (0x8u << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 256 */
#define   PWM_CMR_CPRE_MCK_DIV512 (0x9u << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 512 */
#define   PWM_CMR_CPRE_MCK_DIV1024 (0xAu << 0) /**< \brief (PWM_CMR) Peripheral clock divided by 1024 */
#define   PWM_CMR_CPRE_CLKA (0xBu << 0) /**< \brief (PWM_CMR) Clock A */
#define   PWM_CMR_CPRE_CLKB (0xCu << 0) /**< \brief (PWM_CMR) Clock B */
#define PWM_CMR_CALG (0x1u << 8) /**< \brief (PWM_CMR) Channel Alignment */
#define PWM_CMR_CPOL (0x1u << 9) /**< \brief (PWM_CMR) Channel Polarity */
#define PWM_CMR_CPD (0x1u << 10) /**< \brief (PWM_CMR) Channel Update Period */
/* -------- PWM_CDTY : (PWM Offset: N/A) PWM Channel Duty Cycle Register -------- */
#define PWM_CDTY_CDTY_Pos 0
#define PWM_CDTY_CDTY_Msk (0xffffffffu << PWM_CDTY_CDTY_Pos) /**< \brief (PWM_CDTY) Channel Duty Cycle */
#define PWM_CDTY_CDTY(value) ((PWM_CDTY_CDTY_Msk & ((value) << PWM_CDTY_CDTY_Pos)))
/* -------- PWM_CPRD : (PWM Offset: N/A) PWM Channel Period Register -------- */
#define PWM_CPRD_CPRD_Pos 0
#define PWM_CPRD_CPRD_Msk (0xffffffffu << PWM_CPRD_CPRD_Pos) /**< \brief (PWM_CPRD) Channel Period */
#define PWM_CPRD_CPRD(value) ((PWM_CPRD_CPRD_Msk & ((value) << PWM_CPRD_CPRD_Pos)))
/* -------- PWM_CCNT : (PWM Offset: N/A) PWM Channel Counter Register -------- */
#define PWM_CCNT_CNT_Pos 0
#define PWM_CCNT_CNT_Msk (0xffffffffu << PWM_CCNT_CNT_Pos) /**< \brief (PWM_CCNT) Channel Counter Register */
/* -------- PWM_CUPD : (PWM Offset: N/A) PWM Channel Update Register -------- */
#define PWM_CUPD_CUPD_Pos 0
#define PWM_CUPD_CUPD_Msk (0xffffffffu << PWM_CUPD_CUPD_Pos) /**< \brief (PWM_CUPD)  */
#define PWM_CUPD_CUPD(value) ((PWM_CUPD_CUPD_Msk & ((value) << PWM_CUPD_CUPD_Pos)))

/*@}*/

#endif /* _SAM9X_PWM_COMPONENT_ */
