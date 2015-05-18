#include "core/cpsr.h"

uint32_t v_arm_get_status_Icache(void)
{
	uint32_t ctl;
	ctl = v_arm_read_control();
	if  ((ctl & (1 << 12)) == (1 << 12))
		return 1;
	else
		return 0;
}

/**
 * \brief Enable I Cache
 */
void v_arm_enable_Icache(void)
{
	unsigned int ctl;
	ctl = v_arm_read_control();
	ctl |= (1 << 12);
	v_arm_write_control(ctl);
}
/**
 * \brief Disable I Cache
 */
void v_arm_disable_Icache(void)
{
	unsigned int ctl;
	ctl = v_arm_read_control();
	ctl &= ~(1 << 12);
	v_arm_write_control(ctl);
}
