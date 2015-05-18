#ifndef CPSR_HEARDER_
#define CPSR_HEARDER_

#include <stdint.h>

#define CPSR_MASK_IRQ 0x00000080
#define CPSR_MASK_FIQ 0x00000040

void v_arm_clr_cpsr_bits(uint32_t mask);

void v_arm_set_cpsr_bits(uint32_t mask);

uint32_t v_arm_read_control(void);

void v_arm_write_control(uint32_t mask);

uint32_t v_arm_get_status_Icache(void);

/**
 * \brief Enable I Cache
 */
void v_arm_enable_Icache(void);

/**
 * \brief Disable I Cache
 */
void v_arm_disable_Icache(void);

#endif
