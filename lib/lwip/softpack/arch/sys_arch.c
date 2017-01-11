#include "arch/cc.h"
#include "arch/sys_arch.h"
#include "timer.h"

u32_t sys_now(void)
{
	return timer_get_tick();
}
