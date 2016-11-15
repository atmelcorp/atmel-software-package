/* ---------------------------------------------------------------------------- */
/*                  Atmel Microcontroller Software Support                      */
/*                       SAM Software Package License                           */
/* ---------------------------------------------------------------------------- */
/* Copyright (c) 2016, Atmel Corporation                                        */
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

#ifndef _CORTEXM7_SCB_COMPONENT_
#define _CORTEXM7_SCB_COMPONENT_

/* ============================================================================= */
/**  SOFTWARE API DEFINITION FOR Cortex-M7 System Control Block */
/* ============================================================================= */
/** \addtogroup Cortex-M7 System Control Block */
/*@{*/

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
typedef struct {
	__I  uint32_t SCB_CPUID;    /**< \brief (Scb Offset: 0x000) CPUID Base Register */
	__IO uint32_t SCB_ICSR;     /**< \brief (Scb Offset: 0x004) Interrupt Control and State Register */
	__IO uint32_t SCB_VTOR;     /**< \brief (Scb Offset: 0x008) Vector Table Offset Register */
	__IO uint32_t SCB_AIRCR;    /**< \brief (Scb Offset: 0x00C) Application Interrupt and Reset Control Register */
	__IO uint32_t SCB_SCR;      /**< \brief (Scb Offset: 0x010) System Control Register */
	__IO uint32_t SCB_CCR;      /**< \brief (Scb Offset: 0x014) Configuration and Control Register */
	__IO uint32_t SCB_SHPR1;    /**< \brief (Scb Offset: 0x018) System Handler Priority Register 1 */
	__IO uint32_t SCB_SHPR2;    /**< \brief (Scb Offset: 0x01C) System Handler Priority Register 2 */
	__IO uint32_t SCB_SHPR3;    /**< \brief (Scb Offset: 0x020) System Handler Priority Register 3 */
	__IO uint32_t SCB_SHCSR;    /**< \brief (Scb Offset: 0x024) System Handler Control and State Register */
	__IO uint32_t SCB_CFSR;     /**< \brief (Scb Offset: 0x028) Configurable Fault Status Register */
	__IO uint32_t SCB_HFSR;     /**< \brief (Scb Offset: 0x02C) Hard Fault Status Register */
	__IO uint32_t SCB_DFSR;     /**< \brief (Scb Offset: 0x030) Debug Fault Status Register */
	__IO uint32_t SCB_MMFAR;    /**< \brief (Scb Offset: 0x034) MemManage Fault Address Register */
	__IO uint32_t SCB_BFAR;     /**< \brief (Scb Offset: 0x038) Bus Fault Address Register */
	__I  uint32_t Reserved10[15];
	__I  uint32_t SCB_CLIDR;    /**< \brief (Scb Offset: 0x078) Cache Level ID Register */
	__I  uint32_t SCB_CTR;      /**< \brief (Scb Offset: 0x07C) Cache Type Register */
	__I  uint32_t SCB_CCSIDR;   /**< \brief (Scb Offset: 0x080) Cache Size ID Register */
	__I  uint32_t SCB_CSSELR;   /**< \brief (Scb Offset: 0x084) Cache Size Selection Register */
	__IO uint32_t SCB_CPACR;    /**< \brief (Scb Offset: 0x088) Coprocessor Access Control Register */
	__I  uint32_t Reserved11[106];
	__IO uint32_t SCB_FPCCR;    /**< \brief (Scb Offset: 0x234) FP Context Control Register */
	__IO uint32_t SCB_FPCAR;    /**< \brief (Scb Offset: 0x238) FP Context Address Register */
	__IO uint32_t SCB_FPDSCR;   /**< \brief (Scb Offset: 0x23C) FP Default Status Control Register */
	__I  uint32_t Reserved13[4];
	__O  uint32_t SCB_ICIALLU;  /**< \brief (Scb Offset: 0x250) Instruction cache invalidate all to PoU */
	__I  uint32_t Reserved14[1];
	__O  uint32_t SCB_ICIMVAU;  /**< \brief (Scb Offset: 0x258) Instruction cache invalidate by VA to PoU */
	__O  uint32_t SCB_DCIMVAC;  /**< \brief (Scb Offset: 0x25C) Data cache invalidate by VA to PoC */
	__O  uint32_t SCB_DCISW;    /**< \brief (Scb Offset: 0x260) Data cache invalidate by set/way */
	__O  uint32_t SCB_DCCMVAU;  /**< \brief (Scb Offset: 0x264) Data cache clean by VA to PoU */
	__O  uint32_t SCB_DCCMVAC;  /**< \brief (Scb Offset: 0x268) Data cache clean by VA to PoC */
	__O  uint32_t SCB_DCCSW;    /**< \brief (Scb Offset: 0x26C) Data cache clean by set/way */
	__O  uint32_t SCB_DCCIMVAC; /**< \brief (Scb Offset: 0x270) Data cache clean and invalidate by VA to PoC */
	__O  uint32_t SCB_DCCISW;   /**< \brief (Scb Offset: 0x274) Data cache clean and invalidate by set/way */
	__I  uint32_t Reserved15[6];
	__IO uint32_t SCB_ITCMCR;   /**< \brief (Scb Offset: 0x290) Instruction Tightly-Coupled Memory Control Register */
	__IO uint32_t SCB_DTCMCR;   /**< \brief (Scb Offset: 0x294) Data Tightly-Coupled Memory Control Register */
	__IO uint32_t SCB_AHBPCR;   /**< \brief (Scb Offset: 0x298) AHBP Control Register */
	__IO uint32_t SCB_CACR;     /**< \brief (Scb Offset: 0x29C) L1 Cache Control Register */
	__IO uint32_t SCB_AHBSCR;   /**< \brief (Scb Offset: 0x2A0) AHBS control register */
	__I  uint32_t Reserved16[1];
	__IO uint32_t SCB_ABFSR;    /**< \brief (Scb Offset: 0x2A8) Asynchronous Bus Fault Status Register */
} Scb;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */
/* -------- SCB_CPUID : (SCB Offset: 0x000) CPUID Base Register -------- */
#define SCB_CPUID_REVISION_Pos 0
#define SCB_CPUID_REVISION_Msk (0xfu << 0)
#define SCB_CPUID_PARTNO_Pos 4
#define SCB_CPUID_PARTNO_Msk (0xfffu << 4)
#define SCB_CPUID_ARCHITECTURE_Pos 16
#define SCB_CPUID_ARCHITECTURE_Msk (0xfu << 16)
#define SCB_CPUID_VARIANT_Pos 20
#define SCB_CPUID_VARIANT_Msk (0xfu << 20)
#define SCB_CPUID_IMPLEMENTER_Pos 24
#define SCB_CPUID_IMPLEMENTER_Msk (0xffu << 24)
/* -------- SCB_ICSR : (SCB Offset: 0x004) Interrupt Control and State Register -------- */
#define SCB_ICSR_VECTACTIVE_Pos 0
#define SCB_ICSR_VECTACTIVE_Msk (0x1ffu << 0)
#define SCB_ICSR_RETTOBASE (0x1u << 11)
#define SCB_ICSR_VECTPENDING_Pos 12
#define SCB_ICSR_VECTPENDING_Msk (0x1ffu << 12)
#define SCB_ICSR_ISRPENDING (0x1u << 22)
#define SCB_ICSR_PENDSTCLR (0x1u << 25)
#define SCB_ICSR_PENDSTSET (0x1u << 26)
#define SCB_ICSR_PENDSVCLR (0x1u << 27)
#define SCB_ICSR_PENDSVSET (0x1u << 28)
#define SCB_ICSR_NMIPENDSET (0x1u << 31)
/* -------- SCB_VTOR : (SCB Offset: 0x008) Vector Table Offset Register -------- */
#define SCB_VTOR_TBLOFF_Pos 7
#define SCB_VTOR_TBLOFF_Msk (0x1ffffffu << 7)
#define SCB_VTOR_TBLOFF(value) ((SCB_VTOR_TBLOFF_Msk & ((value) << SCB_VTOR_TBLOFF_Pos)))
/* -------- SCB_AIRCR : (SCB Offset: 0x00C) Application Interrupt and Reset Control Register -------- */
#define SCB_AIRCR_SYSRESETREQ (0x1u << 2)
#define SCB_AIRCR_PRIGROUP_Pos 8
#define SCB_AIRCR_PRIGROUP_Msk (0x7u << 8)
#define SCB_AIRCR_PRIGROUP(value) ((SCB_AIRCR_PRIGROUP_Msk & ((value) << SCB_AIRCR_PRIGROUP_Pos)))
#define SCB_AIRCR_ENDIANESS_Pos 15
#define SCB_AIRCR_ENDIANESS_Msk (0x1u << 15)
#define   SCB_AIRCR_ENDIANESS_LITTLE (0x0u << 15)
#define   SCB_AIRCR_ENDIANESS_BIG (0x1u << 15)
#define SCB_AIRCR_VECTKEY_Pos 16
#define SCB_AIRCR_VECTKEY_Msk (0xffffu << 16)
#define   SCB_AIRCR_VECTKEY_PASSWD (0x05fau << 16)
/* -------- SCB_SCR : (SCB Offset: 0x010) System Control Register -------- */
#define SCB_SCR_SEVONPEND (0x1u << 4)
#define SCB_SCR_SLEEPDEEP (0x1u << 2)
#define SCB_SCR_SLEEPONEXIT (0x1u << 1)
/* -------- SCB_CCR : (SCB Offset: 0x014) Configuration and Control Register -------- */
#define SCB_CCR_NONBASETHRDENA_Pos 0
#define SCB_CCR_NONBASETHRDENA_Msk (0x1u << 0)
#define   SCB_CCR_NONBASETHRDENA_NOEXC (0x0u << 0)
#define   SCB_CCR_NONBASETHRDENA_ANYLEVEL (0x1u << 0)
#define SCB_CCR_USERSETMPEND (0x1u << 1)
#define SCB_CCR_UNALIGN_TRP (0x1u << 3)
#define SCB_CCR_DIV0_TRP (0x1u << 4)
#define SCB_CCR_DC (0x1u << 16)
#define SCB_CCR_IC (0x1u << 17)
/* -------- SCB_SHPR1 : (SCB Offset: 0x018) System Handler Priority Register 1 -------- */
#define SCB_SHPR1_PRI4_Pos 0
#define SCB_SHPR1_PRI4_Msk (0xffffu << 0)
#define SCB_SHPR1_PRI4(value) ((SCB_SHPR1_PRI4_Msk & ((value) << SCB_SHPR1_PRI4_Pos)))
#define SCB_SHPR1_PRI5_Pos 8
#define SCB_SHPR1_PRI5_Msk (0xffffu << 0)
#define SCB_SHPR1_PRI5(value) ((SCB_SHPR1_PRI5_Msk & ((value) << SCB_SHPR1_PRI5_Pos)))
#define SCB_SHPR1_PRI6_Pos 16
#define SCB_SHPR1_PRI6_Msk (0xffffu << 0)
#define SCB_SHPR1_PRI6(value) ((SCB_SHPR1_PRI6_Msk & ((value) << SCB_SHPR1_PRI6_Pos)))
/* -------- SCB_SHPR2 : (SCB Offset: 0x01C) System Handler Priority Register 2 -------- */
#define SCB_SHPR2_PRI11_Pos 24
#define SCB_SHPR2_PRI11_Msk (0xffffu << 0)
#define SCB_SHPR2_PRI11(value) ((SCB_SHPR2_PRI11_Msk & ((value) << SCB_SHPR2_PRI11_Pos)))
/* -------- SCB_SHPR3 : (SCB Offset: 0x020) System Handler Priority Register 3 -------- */
#define SCB_SHPR3_PRI14_Pos 16
#define SCB_SHPR3_PRI14_Msk (0xffffu << 0)
#define SCB_SHPR3_PRI14(value) ((SCB_SHPR3_PRI14_Msk & ((value) << SCB_SHPR3_PRI14_Pos)))
#define SCB_SHPR3_PRI15_Pos 24
#define SCB_SHPR3_PRI15_Msk (0xffffu << 0)
#define SCB_SHPR3_PRI15(value) ((SCB_SHPR3_PRI15_Msk & ((value) << SCB_SHPR3_PRI15_Pos)))
/* -------- SCB_SHCSR : (SCB Offset: 0x024) System Handler Control and State Register -------- */
#define SCB_SHCSR_MEMFAULTACT (0x1u << 0)
#define SCB_SHCSR_BUSFAULTACT (0x1u << 1)
#define SCB_SHCSR_USGFAULTACT (0x1u << 3)
#define SCB_SHCSR_SVCALLACT (0x1u << 7)
#define SCB_SHCSR_MONITORACT (0x1u << 8)
#define SCB_SHCSR_PENDSVACT (0x1u << 10)
#define SCB_SHCSR_SYSTICKACT (0x1u << 11)
#define SCB_SHCSR_USGFAULTPENDED (0x1u << 12)
#define SCB_SHCSR_MEMFAULTPENDED (0x1u << 13)
#define SCB_SHCSR_BUSFAULTPENDED (0x1u << 14)
#define SCB_SHCSR_SVCALLPENDED (0x1u << 15)
#define SCB_SHCSR_MEMFAULTENA (0x1u << 16)
#define SCB_SHCSR_BUSFAULTENA (0x1u << 17)
#define SCB_SHCSR_USGFAULTENA (0x1u << 18)
/* -------- SCB_CFSR : (SCB Offset: 0x028) Configurable Fault Status Register -------- */
#define SCB_CFSR_MEMFAULT_IACCVIOL (0x1u << 0)
#define SCB_CFSR_MEMFAULT_DACCVIOL (0x1u << 1)
#define SCB_CFSR_MEMFAULT_MUNSTKERR (0x1u << 3)
#define SCB_CFSR_MEMFAULT_MSTKERR (0x1u << 4)
#define SCB_CFSR_MEMFAULT_MLSPERR (0x1u << 5)
#define SCB_CFSR_MEMFAULT_MMARVALID (0x1u << 6)
#define SCB_CFSR_BUSFAULT_IBUSERR (0x1u << 8)
#define SCB_CFSR_BUSFAULT_PRECISERR (0x1u << 9)
#define SCB_CFSR_BUSFAULT_IMPRECISERR (0x1u << 10)
#define SCB_CFSR_BUSFAULT_UNSTKERR (0x1u << 11)
#define SCB_CFSR_BUSFAULT_STKERR (0x1u << 12)
#define SCB_CFSR_BUSFAULT_LSPERR (0x1u << 13)
#define SCB_CFSR_BUSFAULT_BFARVALID (0x1u << 15)
#define SCB_CFSR_USGFAULT_UNDEFINSTR (0x1u << 16)
#define SCB_CFSR_USGFAULT_INVSTATE (0x1u << 17)
#define SCB_CFSR_USGFAULT_INVPC (0x1u << 18)
#define SCB_CFSR_USGFAULT_NOCP (0x1u << 19)
#define SCB_CFSR_USGFAULT_UNALIGNED (0x1u << 24)
#define SCB_CFSR_USGFAULT_DIVBYZERO (0x1u << 25)
/* -------- SCB_HFSR : (SCB Offset: 0x02C) Hard Fault Status Register -------- */
#define SCB_HFSR_VECTTBL (0x1u << 1)
#define SCB_HFSR_FORCED (0x1u << 30)
#define SCB_HFSR_DEBUGEVT (0x1u << 31)
/* -------- SCB_DFSR : (SCB Offset: 0x030) Debug Fault Status Register -------- */
#define SCB_DFSR_HALTED (0x1u << 0)
#define SCB_DFSR_BKPT (0x1u << 1)
#define SCB_DFSR_DWTTRAP (0x1u << 2)
#define SCB_DFSR_VCATCH (0x1u << 3)
#define SCB_DFSR_EXTERNAL (0x1u << 4)
/* -------- SCB_MMFAR : (Scb Offset: 0x034) MemManage Fault Address Register -------- */
#define SCB_MMFAR_ADDR_Pos 0
#define SCB_MMFAR_ADDR_Msk (0xffffffffu << 0)
#define SCB_MMFAR_ADDR(value) ((SCB_MMFAR_ADDR_Msk & ((value) << SCB_MMFAR_ADDR_Pos)))
/* -------- SCB_BFAR : (Scb Offset: 0x038) Bus Fault Address Register -------- */
#define SCB_BFAR_ADDR_Pos 0
#define SCB_BFAR_ADDR_Msk (0xffffffffu << 0)
#define SCB_BFAR_ADDR(value) ((SCB_BFAR_ADDR_Msk & ((value) << SCB_BFAR_ADDR_Pos)))
/* -------- SCB_CLIDR : (SCB Offset: 0x078) Cache Level ID Register -------- */
#define SCB_CLIDR_ICACHE (0x1u << 0)
#define SCB_CLIDR_DCACHE (0x1u << 1)
#define SCB_CLIDR_LOC_Pos 24
#define SCB_CLIDR_LOC_Msk (0x7u << 24)
#define   SCB_CLIDR_LOC_LEVEL1 (0x0u << 24)
#define   SCB_CLIDR_LOC_LEVEL2 (0x1u << 24)
#define SCB_CLIDR_LOU_Pos 27
#define SCB_CLIDR_LOU_Msk (0x7u << 27)
#define   SCB_CLIDR_LOU_LEVEL1 (0x0u << 27)
#define   SCB_CLIDR_LOU_LEVEL2 (0x1u << 27)
/* -------- SCB_CTR : (SCB Offset: 0x07C) Cache Type Register -------- */
#define SCB_CTR_IMINLINE_Pos 0
#define SCB_CTR_IMINLINE_Msk (0xfu << 0)
#define   SCB_CTR_IMINLINE_8WORD (0x3u << 0)
#define SCB_CTR_DMINLINE_Pos 16
#define SCB_CTR_DMINLINE_Msk (0xfu << 16)
#define   SCB_CTR_DMINLINE_8WORD (0x3u << 16)
#define SCB_CTR_ERG_Pos 20
#define SCB_CTR_ERG_Msk (0xfu << 20)
#define SCB_CTR_CWG_Pos 24
#define SCB_CTR_CWG_Msk (0xfu << 24)
#define   SCB_CTR_CWG_8WORD (0x3u << 24)
#define SCB_CTR_FORMAT_Pos 29
#define SCB_CTR_FORMAT_Msk (0x7u << 29)
#define   SCB_CTR_FORMAT_ARMV7 (0x4u << 29)
/* -------- SCB_CCSIDR : (SCB Offset: 0x080) Cache Size ID Register -------- */
#define SCB_CCSIDR_LINESIZE_Pos 0
#define SCB_CCSIDR_LINESIZE_Msk (0x7u << 0)
#define SCB_CCSIDR_ASSOCIATIVITY_Pos 3
#define SCB_CCSIDR_ASSOCIATIVITY_Msk (0x3ffu << 3)
#define SCB_CCSIDR_NUMSETS_Pos 13
#define SCB_CCSIDR_NUMSETS_Msk (0x7fffu << 13)
#define SCB_CCSIDR_WA (0x1u << 28)
#define SCB_CCSIDR_RA (0x1u << 29)
#define SCB_CCSIDR_WB (0x1u << 30)
#define SCB_CCSIDR_WT (0x1u << 31)
/* -------- SCB_CSSELR : (SCB Offset: 0x084) Cache Size Selection Register -------- */
#define SCB_CSSELR_IND_Pos 0
#define SCB_CSSELR_IND_Msk (0x1u << 0)
#define   SCB_CSSELR_IND_DCACHE (0x0u << 0)
#define   SCB_CSSELR_IND_ICACHE (0x1u << 0)
#define SCB_CSSELR_LEVEL_Pos 1
#define SCB_CSSELR_LEVEL_Msk (0x7u << 1)
#define   SCB_CSSELR_LEVEL_LEVEL1 (0x0u << 1)
/* -------- SCB_CPACR : (SCB Offset: 0x088) Coprocessor Access Control Register -------- */
#define SCB_CPACR_CP10_Pos 20
#define SCB_CPACR_CP10_Msk (0x3u << 20)
#define   SCB_CPACR_CP10_NONE (0x0u << 20)
#define   SCB_CPACR_CP10_PRIV (0x1u << 20)
#define   SCB_CPACR_CP10_FULL (0x3u << 20)
#define SCB_CPACR_CP11_Pos 22
#define SCB_CPACR_CP11_Msk (0x3u << 22)
#define   SCB_CPACR_CP11_NONE (0x0u << 22)
#define   SCB_CPACR_CP11_PRIV (0x1u << 22)
#define   SCB_CPACR_CP11_FULL (0x3u << 22)
/* -------- SCB_FPCCR : (SCB Offset: 0x234) FP Context Control Register -------- */
#define SCB_FPCCR_LSPACT (0x1u << 0)
#define SCB_FPCCR_USER (0x1u << 1)
#define SCB_FPCCR_THREAD (0x1u << 3)
#define SCB_FPCCR_HFRDY (0x1u << 4)
#define SCB_FPCCR_MMRDY (0x1u << 5)
#define SCB_FPCCR_BFRDY (0x1u << 6)
#define SCB_FPCCR_MONRDY (0x1u << 8)
#define SCB_FPCCR_LSPEN (0x1u << 30)
#define SCB_FPCCR_ASPEN (0x1u << 31)
/* -------- SCB_FPCAR : (SCB Offset: 0x238) FP Context Address Register -------- */
#define SCB_FPCAR_ADDR_Pos 3
#define SCB_FPCAR_ADDR_Msk (0x1fffffffu << 3)
#define SCB_FPCAR_ADDR(value) ((SCB_FPCAR_ADDR_Msk & ((value) << SCB_FPCAR_ADDR_Pos)))
/* -------- SCB_FPDSCR : (SCB Offset: 0x23C) FP Default Status Control Register -------- */
#define SCB_FPDSCR_RMODE_Pos 22
#define SCB_FPDSCR_RMODE_Msk (0x3u << 22)
#define SCB_FPDSCR_RMODE(value) ((SCB_FPDSCR_RMODE_Msk & ((value) << SCB_FPDSCR_RMODE_Pos)))
#define SCB_FPDSCR_FZ (0x1u << 24)
#define SCB_FPDSCR_DN (0x1u << 25)
#define SCB_FPDSCR_AHP (0x1u << 26)
/* -------- SCB_ICIMVAU : (SCB Offset: 0x258) Instruction cache invalidate by VA to PoU -------- */
#define SCB_ICIMVAU_MVA_Pos 0
#define SCB_ICIMVAU_MVA_Msk (0xffffffffu << 0)
#define SCB_ICIMVAU_MVA(value) ((SCB_ICIMVAU_MVA_Msk & ((value) << SCB_ICIMVAU_MVA_Pos)))
/* -------- SCB_DCIMVAC : (SCB Offset: 0x25C) Data cache invalidate by VA to PoC -------- */
#define SCB_DCIMVAC_MVA_Pos 0
#define SCB_DCIMVAC_MVA_Msk (0xffffffffu << 0)
#define SCB_DCIMVAC_MVA(value) ((SCB_DCIMVAC_MVA_Msk & ((value) << SCB_DCIMVAC_MVA_Pos)))
/* -------- SCB_DCISW : (SCB Offset: 0x260) Data cache invalidate by set/way -------- */
#define SCB_DCISW_SET_Pos 5
#define SCB_DCISW_SET_Msk (0x3ffu << 5)
#define SCB_DCISW_SET(value) ((SCB_DCISW_SET_Msk & ((value) << SCB_DCISW_SET_Pos)))
#define SCB_DCISW_WAY_Pos 30
#define SCB_DCISW_WAY_Msk (0x3u << 20)
#define SCB_DCISW_WAY(value) ((SCB_DCISW_WAY_Msk & ((value) << SCB_DCISW_WAY_Pos)))
/* -------- SCB_DCCMVAU : (SCB Offset: 0x264) Data cache clean by VA to PoU -------- */
#define SCB_DCCMVAU_MVA_Pos 0
#define SCB_DCCMVAU_MVA_Msk (0xffffffffu << 0)
#define SCB_DCCMVAU_MVA(value) ((SCB_DCCMVAU_MVA_Msk & ((value) << SCB_DCCMVAU_MVA_Pos)))
/* -------- SCB_DCCMVAC : (SCB Offset: 0x268) Data cache clean by VA to PoC -------- */
#define SCB_DCCMVAC_MVA_Pos 0
#define SCB_DCCMVAC_MVA_Msk (0xffffffffu << 0)
#define SCB_DCCMVAC_MVA(value) ((SCB_DCCMVAC_MVA_Msk & ((value) << SCB_DCCMVAC_MVA_Pos)))
/* -------- SCB_DCCSW : (SCB Offset: 0x26C) Data cache clean by set/way -------- */
#define SCB_DCCSW_SET_Pos 5
#define SCB_DCCSW_SET_Msk (0x3ffu << 5)
#define SCB_DCCSW_SET(value) ((SCB_DCCSW_SET_Msk & ((value) << SCB_DCCSW_SET_Pos)))
#define SCB_DCCSW_WAY_Pos 30
#define SCB_DCCSW_WAY_Msk (0x3u << 20)
#define SCB_DCCSW_WAY(value) ((SCB_DCCSW_WAY_Msk & ((value) << SCB_DCCSW_WAY_Pos)))
/* -------- SCB_DCCIMVAC : (SCB Offset: 0x270) Data cache clean and invalidate by VA to PoC -------- */
#define SCB_DCCIMVAC_MVA_Pos 0
#define SCB_DCCIMVAC_MVA_Msk (0xffffffffu << 0)
#define SCB_DCCIMVAC_MVA(value) ((SCB_DCCIMVAC_MVA_Msk & ((value) << SCB_DCCIMVAC_MVA_Pos)))
/* -------- SCB_DCCISW : (SCB Offset: 0x274) Data cache clean and invalidate by set/way -------- */
#define SCB_DCCISW_SET_Pos 5
#define SCB_DCCISW_SET_Msk (0x3ffu << 5)
#define SCB_DCCISW_SET(value) ((SCB_DCCISW_SET_Msk & ((value) << SCB_DCCISW_SET_Pos)))
#define SCB_DCCISW_WAY_Pos 30
#define SCB_DCCISW_WAY_Msk (0x3u << 20)
#define SCB_DCCISW_WAY(value) ((SCB_DCCISW_WAY_Msk & ((value) << SCB_DCCISW_WAY_Pos)))
/* -------- SCB_ITCMCR : (SCB Offset: 0x290) Instruction Tightly-Coupled Memory Control Register -------- */
#define SCB_ITCMCR_EN (0x1u << 0)
#define SCB_ITCMCR_RMW (0x1u << 1)
#define SCB_ITCMCR_RETEN (0x1u << 2)
#define SCB_ITCMCR_SZ_Pos 3
#define SCB_ITCMCR_SZ_Msk (0xfu << 3)
#define SCB_ITCMCR_SZ(value) ((SCB_ITCMCR_SZ_Msk & ((value) << SCB_ITCMCR_SZ_Pos)))
#define   SCB_ITCMCR_SZ_NOTCM (0x0u << 3)
#define   SCB_ITCMCR_SZ_4KB (0x3u << 3)
#define   SCB_ITCMCR_SZ_8KB (0x4u << 3)
#define   SCB_ITCMCR_SZ_16KB (0x5u << 3)
#define   SCB_ITCMCR_SZ_32KB (0x6u << 3)
#define   SCB_ITCMCR_SZ_64KB (0x7u << 3)
#define   SCB_ITCMCR_SZ_128KB (0x8u << 3)
#define   SCB_ITCMCR_SZ_256KB (0x9u << 3)
#define   SCB_ITCMCR_SZ_512KB (0xau << 3)
#define   SCB_ITCMCR_SZ_1MB (0xbu << 3)
#define   SCB_ITCMCR_SZ_2MB (0xcu << 3)
#define   SCB_ITCMCR_SZ_4MB (0xdu << 3)
#define   SCB_ITCMCR_SZ_8MB (0xeu << 3)
#define   SCB_ITCMCR_SZ_16MB (0xfu << 3)
/* -------- SCB_DTCMCR : (SCB Offset: 0x294) Data Tightly-Coupled Memory Control Register -------- */
#define SCB_DTCMCR_EN (0x1u << 0)
#define SCB_DTCMCR_RMW (0x1u << 1)
#define SCB_DTCMCR_RETEN (0x1u << 2)
#define SCB_DTCMCR_SZ_Pos 3
#define SCB_DTCMCR_SZ_Msk (0xfu << 3)
#define SCB_DTCMCR_SZ(value) ((SCB_DTCMCR_SZ_Msk & ((value) << SCB_DTCMCR_SZ_Pos)))
#define   SCB_DTCMCR_SZ_NOTCM (0x0u << 3)
#define   SCB_DTCMCR_SZ_4KB (0x3u << 3)
#define   SCB_DTCMCR_SZ_8KB (0x4u << 3)
#define   SCB_DTCMCR_SZ_16KB (0x5u << 3)
#define   SCB_DTCMCR_SZ_32KB (0x6u << 3)
#define   SCB_DTCMCR_SZ_64KB (0x7u << 3)
#define   SCB_DTCMCR_SZ_128KB (0x8u << 3)
#define   SCB_DTCMCR_SZ_256KB (0x9u << 3)
#define   SCB_DTCMCR_SZ_512KB (0xau << 3)
#define   SCB_DTCMCR_SZ_1MB (0xbu << 3)
#define   SCB_DTCMCR_SZ_2MB (0xcu << 3)
#define   SCB_DTCMCR_SZ_4MB (0xdu << 3)
#define   SCB_DTCMCR_SZ_8MB (0xeu << 3)
#define   SCB_DTCMCR_SZ_16MB (0xfu << 3)
/* -------- SCB_AHBPCR : (SCB Offset: 0x298) AHBP Control Register -------- */
#define SCB_AHBPCR_EN (0x1u << 0)
#define SCB_AHBPCR_SZ_Pos 1
#define SCB_AHBPCR_SZ_Msk (0x7u << 1)
#define SCB_AHBPCR_SZ(value) ((SCB_AHBPCR_SZ_Msk & ((value) << SCB_AHBPCR_SZ_Pos)))
#define   SCB_AHBPCR_SZ_64MB (0x1u << 1)
#define   SCB_AHBPCR_SZ_128MB (0x2u << 1)
#define   SCB_AHBPCR_SZ_256MB (0x3u << 1)
#define   SCB_AHBPCR_SZ_512MB (0x4u << 1)
/* -------- SCB_CACR : (SCB Offset: 0x29C) L1 Cache Control Register -------- */
#define SCB_CACR_SIWT (0x1u << 0)
#define SCB_CACR_ECCEN (0x1u << 1)
#define SCB_CACR_FORCEWT (0x1u << 2)
/* -------- SCB_AHBSCR : (SCB Offset: 0x2A0) AHBS control register -------- */
#define SCB_AHBSCR_CTL_Pos 0
#define SCB_AHBSCR_CTL_Msk (0x3u << 0)
#define SCB_AHBSCR_TPRI_Pos 2
#define SCB_AHBSCR_TPRI_Msk (0x1ffu << 2)
#define SCB_AHBSCR_INITCOUNT_Pos 11
#define SCB_AHBSCR_INITCOUNT_Msk (0x1fu << 11)
/* -------- SCB_ABFSR : (SCB Offset: 0x2A8) Asynchronous Bus Fault Status Register -------- */
#define SCB_ABFSR_ITCM (0x1u << 0)
#define SCB_ABFSR_DTCM (0x1u << 1)
#define SCB_ABFSR_AHBP (0x1u << 2)
#define SCB_ABFSR_AXIM (0x1u << 3)
#define SCB_ABFSR_EPPB (0x1u << 4)
#define SCB_ABFSR_AXIMTYPE_Pos 8
#define SCB_ABFSR_AXIMTYPE_Msk (0x3u << 8)
#define   SCB_ABFSR_AXIMTYPE_OKAY (0x0u << 8)
#define   SCB_ABFSR_AXIMTYPE_EXOKAY (0x1u << 8)
#define   SCB_ABFSR_AXIMTYPE_SLVERR (0x2u << 8)
#define   SCB_ABFSR_AXIMTYPE_DECERR (0x3u << 8)

/*@}*/

#endif /* _CORTEXM7_SCB_COMPONENT_ */
