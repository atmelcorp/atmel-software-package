/* ============================================================================= */
/*  SOFTWARE API DEFINITION FOR PPP                                              */
/*    Stephane GALEA - 06/12/2014                                                */
/*    ATMEL ROUSSET                                                              */
/* ============================================================================= */
#ifndef _COMPONENT_PPP_H
#define _COMPONENT_PPP_H

#if !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__))
/** \brief HSDHC hardware registers */
typedef struct {
  __IO uint32_t Reserved1[8];
  __IO uint32_t PPP_CONFIG;      /**< \brief (Ppp Offset: 0x20) CONFIG Register */
  __IO uint32_t PPP_CTRL;        /**< \brief (Ppp Offset: 0x24) CTRL Register */
  union {
    __I uint32_t PPP_STATE;      /**< \brief (Ppp Offset: 0x28) STATE Register */
    __O uint32_t PPP_CMD;        /**< \brief (Ppp Offset: 0x28) CMD Register */
  };
  __IO uint8_t  Reserved2[7];
  union {
    __I uint8_t  PPP_ISR;        /**< \brief (Ppp Offset: 0x33) Interrupt Status Register */
    __O uint8_t  PPP_ICR;        /**< \brief (Ppp Offset: 0x33) Interupt Command Register */
  };
  __O  uint8_t  PPP_IDR;         /**< \brief (Ppp Offset: 0x34) Interrupt Enable Register */
  __O  uint8_t  PPP_IER;         /**< \brief (Ppp Offset: 0x35) Interrupt Disable Register */
  __IO uint8_t  Reserved3[9];
} Ppp;
#endif /* !(defined(__ASSEMBLY__) || defined(__IAR_SYSTEMS_ASM__)) */

/* CONFIG: CPU configuration */
#define PPP_CONFIG_ISA_Msk               0x00000003
#define PPP_CONFIG_ISA_Pos               0
#define   PPP_CONFIG_ISA_AVR8            0x0
#define   PPP_CONFIG_ISA_AVR16C          0x1
#define   PPP_CONFIG_ISA_AVR16E          0x2
#define   PPP_CONFIG_ISA_AVR16           0x3
#define PPP_CONFIG_ISA(avr) ((avr << PPP_CONFIG_ISA_Pos) & PPP_OCNFIG_Msk)
#define PPP_CONFIG_MARRET_Msk            0x00000008
#define PPP_CONFIG_MARRET_Pos            3
#define PPP_CONFIG_MARRET                0x00000008
#define PPP_CONFIG_RRET_Msk              0x000000F0
#define PPP_CONFIG_RRET_Pos              4
#define PPP_CONFIG_RRET(rret)    ((rret << PPP_CONFIG_RRET_Pos) & PPP_CONFIG_RRET_Msk)
#define PPP_CONFIG_PCEXEN_Msk            0x00000100
#define PPP_CONFIG_PCEXEN_Pos            8
#define PPP_CONFIG_PCEXEN                0x00000100

/* CTRL: CPU Control */
#define PPP_CTRL_MAPU_EXCEPT_Msk         0x00000001
#define PPP_CTRL_MAPU_EXCEPT_Pos         0
#define PPP_CTRL_MAPU_EXCEPT             0x00000001
#define PPP_CTRL_WP_ICACHE_Msk           0x00000002
#define PPP_CTRL_WP_ICACHE_Pos           1
#define PPP_CTRL_WP_ICACHE               0x00000002
#define PPP_CTRL_WP_VEC_Msk              0x0000000C
#define PPP_CTRL_WP_VEC_Pos              2
#define   PPP_CTRL_WP_VEC_NONE           (0x0 << PPP_CTRL_WP_VEC_Pos)
#define   PPP_CTRL_WP_VEC_RST_NMI        (0x1 << PPP_CTRL_WP_VEC_Pos)
#define   PPP_CTRL_WP_VEC_ALL            (0x2 << PPP_CTRL_WP_VEC_Pos)
#define   PPP_CTRL_WP_VEC_ALL3           (0x3 << PPP_CTRL_WP_VEC_Pos)
#define PPP_CTRL_WP_VEC(vec) ((vec << PPP_CTRL_WP_VEC_Pos) & PPP_CTRL_WP_VEC_Msk)
#define PPP_CTRL_WP_CTX_Msk              0x00000004
#define PPP_CTRL_WP_CTX_Pos              4
#define   PPP_CTRL_WP_CTX_NONE           (0x0 << PPP_CTRL_WP_CTX_Pos)
#define   PPP_CTRL_WP_CTX_CTX0           (0x1 << PPP_CTRL_WP_CTX_Pos)
#define   PPP_CTRL_WP_CTX_CTX0_CTX1      (0x2 << PPP_CTRL_WP_CTX_Pos)
#define   PPP_CTRL_WP_CTX_CTX0_CTX1_CTX2 (0x3 << PPP_CTRL_WP_CTX_Pos)
#define PPP_CTRL_WP_CTX(ctx) ((ctx << PPP_CTRL_WP_CTX_Pos) & PPP_CTRL_WP_CTX_Msk)
#define PPP_CTRL_WP_CODE_Msk             0x000003C0
#define PPP_CTRL_WP_CODE_Pos             6
#define   PPP_CTRL_WP_CODE_DISABLED      0x0
#define PPP_CTRL_WP_CODE(wp) ((wp << PPP_CTRL_WP_CODE_Pos) & PPP_CTRL_WP_CODE_Msk)

/* STATE (Read Only) */
#define PPP_STATE_IL0EX_Msk              0x00000002
#define PPP_STATE_IL0EX_Pos              1
#define PPP_STATE_IL0EX                  0x00000002
#define PPP_STATE_IL1EX_Msk              0x00000004
#define PPP_STATE_IL1EX_Pos              2
#define PPP_STATE_IL1EX                  0x00000004
#define PPP_STATE_IL2EX_Msk              0x00000008
#define PPP_STATE_IL2EX_Pos              3
#define PPP_STATE_IL2EX                  0x00000008
#define PPP_STATE_IL3EX_Msk              0x00000001
#define PPP_STATE_IL3EX_Pos              4
#define PPP_STATE_IL3EX                  0x00000001
#define PPP_STATE_IL4EX_Msk              0x00000002
#define PPP_STATE_IL4EX_Pos              5
#define PPP_STATE_IL4EX                  0x00000002
#define PPP_STATE_NMIEX_Msk              0x00000004
#define PPP_STATE_NMIEX_Pos              6
#define PPP_STATE_NMIEX                  0x00000004
#define PPP_STATE_EXCEPT_Msk             0x00000100
#define PPP_STATE_EXCEPT_Pos             8
#define PPP_STATE_EXCEPT                 0x00000100
#define PPP_STATE_AVR16_Msk              0x00000200
#define PPP_STATE_AVR16_Pos              9
#define PPP_STATE_AVR16                  0x00000200
#define PPP_STATE_OCD_COF_Msk            0x00000400
#define PPP_STATE_OCD_COF_Pos            10
#define PPP_STATE_OCD_COF                0x00000400
#define PPP_STATE_UPC_Msk                0x00FF0000
#define PPP_STATE_UPC_Pos                16
#define PPP_STATE_SYSSTATE_Msk           0xF8000000
#define PPP_STATE_SYSSTATE_Pos           27

/* CMD: Write Only */
#define PPP_CMD_Msk                      0x0000000F
#define PPP_CMD_Pos                      0
#define PPP_CMD_NONE                     0x0
#define PPP_CMD_STOP                     0x1
#define PPP_CMD_RESET                    0x2
#define PPP_CMD_RESTART                  0x3
#define PPP_CMD_ABORT                    0x4
#define PPP_CMD_RUN                      0x5
#define PPP_CMD_RUN_LOCKED               0x6
#define PPP_CMD_RUN_OCD                  0x7
#define PPP_CMD_UNLOCK                   0x8
#define PPP_CMD_NMI                      0x9
#define PPP_CMD_HOST_OCD                 0xB
#define PPP_CMD(cmd)                     ((cmd << PPP_CMD_Pos) & PPP_CMD_Msk)
#define PPP_CMD_UNLOCK_Msk               0xFFFF0000
#define PPP_CMD_UNLOCK_Pos               16

#define PPP_ISR_Msk                      0xFF
#define PPP_ISR_Pos                      0
#define PPP_ISR_IRQ_Msk                  0xF0
#define PPP_ISR_IRQ_Pos                  0
#define PPP_ISR_IRQ0                     0x10
#define PPP_ISR_IRQ1                     0x20
#define PPP_ISR_IRQ2                     0x40
#define PPP_ISR_IRQ3                     0x80
#define PPP_ISR_NOTIFY_Msk               0x0F
#define PPP_ISR_NOTIFY_Offset            0
#define PPP_ISR_NOTIFY0                  0x01
#define PPP_ISR_NOTIFY1                  0x02
#define PPP_ISR_NOTIFY2                  0x04
#define PPP_ISR_NOTIFY3                  0x08

#define PPP_ICR_Msk                      0xFF
#define PPP_ICR_Pos                      0
#define PPP_ICR_IRQ_Msk                  0xF0
#define PPP_ICR_IRQ_Pos                  0
#define PPP_ICR_IRQ0                     0x10
#define PPP_ICR_IRQ1                     0x20
#define PPP_ICR_IRQ2                     0x40
#define PPP_ICR_IRQ3                     0x80
#define PPP_ICR_NOTIFY_Msk               0x0F
#define PPP_ICR_NOTIFY_Offset            0
#define PPP_ICR_NOTIFY0                  0x01
#define PPP_ICR_NOTIFY1                  0x02
#define PPP_ICR_NOTIFY2                  0x04
#define PPP_ICR_NOTIFY3                  0x08

#define PPP_IDR_Msk                      0xF0
#define PPP_IDR_Pos                      0
#define PPP_IDR_IRQ0                     0x10
#define PPP_IDR_IRQ1                     0x20
#define PPP_IDR_IRQ2                     0x40
#define PPP_IDR_IRQ3                     0x80

#define PPP_IER_Msk                      0xF0
#define PPP_IER_Pos                      0
#define PPP_IER_IRQ0                     0x10
#define PPP_IER_IRQ1                     0x20
#define PPP_IER_IRQ2                     0x40
#define PPP_IER_IRQ3                     0x80


#endif /* ! _COMPONENT_PPP_H */
