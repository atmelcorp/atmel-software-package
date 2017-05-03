#include "arch/cc.h"
#include "arch/sys_arch.h"
#include "timer.h"

unsigned int sys_now(void)
{
	return timer_get_tick();
}
