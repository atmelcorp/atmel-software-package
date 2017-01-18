/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include <string.h>

#include "barriers.h"
#include "board.h"
#include "irq/nvic.h"

/*----------------------------------------------------------------------------
 *        Imported variables / functions
 *----------------------------------------------------------------------------*/

extern void main(void);

#if defined(__GNUC__)

/* from LIBC */
extern void __libc_init_array(void);

/* from linker script */
extern uint32_t _cstack;
extern uint32_t _etext;
extern uint32_t _srelocate;
extern uint32_t _erelocate;
extern uint32_t _szero;
extern uint32_t _ezero;

#define CSTACK_TOP (&_cstack)

#elif defined(__ICCARM__)

void __iar_data_init3(void);

#pragma section="CSTACK"
#define CSTACK_TOP __section_end("CSTACK")

#endif

/*----------------------------------------------------------------------------
 *        Forward function declarations
 *----------------------------------------------------------------------------*/

void reset_handler(void);
static void _default_nmi_handler(void);
static void _default_hardfault_handler(void);
static void _default_memmanage_handler(void);
static void _default_busfault_handler(void);
static void _default_usagefault_handler(void);
static void _default_svc_handler(void);
static void _default_debugmon_handler(void);
static void _default_pendsv_handler(void);
static void _dummy_handler(void);

/*----------------------------------------------------------------------------
 *        Local constants
 *----------------------------------------------------------------------------*/

SECTION(".vectors") USED
static const struct {
	void*          stack;
	nvic_handler_t handlers[15];
} __vector_table = {
	.stack = CSTACK_TOP,
	.handlers = {
		reset_handler,
		_default_nmi_handler,
		_default_hardfault_handler,
		_default_memmanage_handler,
		_default_busfault_handler,
		_default_usagefault_handler,
		0, /* reserved */
		0, /* reserved */
		0, /* reserved */
		0, /* reserved */
		_default_svc_handler,
		_default_debugmon_handler,
		0, /* reserved */
		_default_pendsv_handler,
		_dummy_handler, /* systick */
	}
};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

static void _default_nmi_handler(void)
{
#ifndef NDEBUG
	asm("bkpt #2":::"memory");
#endif

	/* halt CPU */
	while (1) { }
}

static void _default_hardfault_handler(void)
{
#ifndef NDEBUG
	asm("bkpt #3":::"memory");
#endif

	/* halt CPU */
	while (1) { }
}

static void _default_memmanage_handler(void)
{
#ifndef NDEBUG
	asm("bkpt #4":::"memory");
#endif

	/* halt CPU */
	while (1) { }
}

static void _default_busfault_handler(void)
{
#ifndef NDEBUG
	asm("bkpt #5":::"memory");
#endif

	/* halt CPU */
	while (1) { }
}

static void _default_usagefault_handler(void)
{
#ifndef NDEBUG
	asm("bkpt #6":::"memory");
#endif

	/* halt CPU */
	while (1) { }
}

static void _default_svc_handler(void)
{
#ifndef NDEBUG
	asm("bkpt #11":::"memory");
#endif

	/* halt CPU */
	while (1) { }
}

static void _default_debugmon_handler(void)
{
#ifndef NDEBUG
	asm("bkpt #12":::"memory");
#endif

	/* halt CPU */
	while (1) { }
}

static void _default_pendsv_handler(void)
{
#ifndef NDEBUG
	asm("bkpt #14":::"memory");
#endif

	/* halt CPU */
	while (1) { }
}

static void _dummy_handler(void)
{
	/* do nothing */
}

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief This is the code that gets called on processor reset.
 * To initialize the device, and call the main() routine.
 */
SECTION(".cstartup") USED
void reset_handler(void)
{
	/* enable FPU */
	SCB->SCB_CPACR |= SCB_CPACR_CP10_FULL | SCB_CPACR_CP11_FULL;
	dsb();
	isb();

#if defined(__GNUC__)

	uint32_t *src, *dst;

	/* zero BSS */
	for (dst = (uint32_t*)&_szero; dst < (uint32_t*)&_ezero; dst++)
		*dst = 0;

	/* copy data */
	for (dst = (uint32_t*)&_srelocate, src = (uint32_t*)&_etext; dst < (uint32_t*)&_erelocate; dst++, src++)
		*dst = *src;

	/* initialize the C library */
	__libc_init_array();

#elif defined(__ICCARM__)

	/* Execute relocations & zero BSS */
	__iar_data_init3();

#endif

	/* initialize SoC / board */
	board_init();

	/* branch to main function */
	main();

	/* program done, block in infinite loop */
	while (1);
}
