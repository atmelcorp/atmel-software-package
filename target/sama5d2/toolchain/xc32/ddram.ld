/*******************************************************************************
* Copyright (C) 2021 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/

/*------------------------------------------------------------------------------
 *      Linker script for running in internal DDRAM on the SAMA5D2
 *----------------------------------------------------------------------------*/

OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(entry)
SEARCH_DIR(.)

/* Memory Spaces Definitions */
MEMORY
{
	sram        (!RWX) : ORIGIN = 0x200000,   LENGTH = 128K /* sram */
	ram         (RWX) : ORIGIN = 0x20000000, LENGTH = 64M  /* ram */
	ram_nocache  (!RWX) : ORIGIN = 0x24000000, LENGTH = 16M  /* ram (non-cached) */
	rom         (LRX) : ORIGIN = 0, LENGTH = 0
}

/* Sizes of the stacks used by the application. NOTE: you need to adjust */
C_STACK_SIZE   = 0x800;
IRQ_STACK_SIZE = 0x60;
FIQ_STACK_SIZE = 0x60;
SYS_STACK_SIZE = 0x40;
ABT_STACK_SIZE = 0x40;
UND_STACK_SIZE = 0x40;
HEAP_SIZE      = 0x200;

/* Section Definitions */
SECTIONS
{
	.text 0x20000000 :
	{
		. = ALIGN(4);
		_sfixed = .;
		*(.textEntry)
		*(.text .text.* .gnu.linkonce.t.*)
		*(.rodata .rodata* .gnu.linkonce.r.*)
		*(.ARM.extab* .gnu.linkonce.armextab.*)

		. = ALIGN(4);
		KEEP(*(.init))
		. = ALIGN(4);
		__preinit_array_start = .;
		KEEP(*(.preinit_array))
		__preinit_array_end = .;

		. = ALIGN(4);
		__init_array_start = .;
		KEEP(*(SORT(.init_array.*)))
		KEEP(*(.init_array))
		__init_array_end = .;

		. = ALIGN(0x4);
		KEEP(*crtbegin.o(.ctors))
		KEEP(*(EXCLUDE_FILE (*crtend.o) .ctors))
		KEEP(*(SORT(.ctors.*)))
		KEEP(*crtend.o(.ctors))

		. = ALIGN(4);
		KEEP(*(.fini))

		. = ALIGN(4);
		__fini_array_start = .;
		KEEP(*(.fini_array))
		KEEP(*(SORT(.fini_array.*)))
		__fini_array_end = .;

		KEEP(*crtbegin.o(.dtors))
		KEEP(*(EXCLUDE_FILE (*crtend.o) .dtors))
		KEEP(*(SORT(.dtors.*)))
		KEEP(*crtend.o(.dtors))

	    *(.dinit*)
		. = ALIGN(4);
	} >ram

	.data :
    {
		*(.data .data.*);
		. = ALIGN(4);
		_efixed = .;            /* End of text section */
	} >ram

	/* .ARM.exidx is sorted, so has to go in its own output section.  */
	PROVIDE_HIDDEN (__exidx_start = .);
	.ARM.exidx :
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} >ram
	PROVIDE_HIDDEN (__exidx_end = .);

	/* _etext must be just before .relocate section */
	. = ALIGN(4);
	_etext = .;

	.relocate :
	{
		. = ALIGN(4);
		_srelocate = .;
		KEEP(*(.vectors .vectors.*))
		*(.ramfunc)
		. = ALIGN(4);
		_erelocate = .;
	} >sram AT>ram

	.region_cache_aligned_const :
	{
		. = ALIGN(32);
		*(.region_cache_aligned_const*)
		. = ALIGN(32);
	} >ram

	.region_sram (NOLOAD) :
	{
		. = ALIGN(4);
		*(.region_sram*)
		. += IRQ_STACK_SIZE;
		. = ALIGN(8);
		_irqstack = .;
	} >sram

	.region_ddr (NOLOAD) :
	{
		. = ALIGN(4);
		*(.region_ddr*)
	} >ram

	.region_nocache (NOLOAD) :
	{
		. = ALIGN(4);
		*(.region_nocache*)
	} >ram_nocache

	/* .bss section which is used for uninitialized data */
	.bss (NOLOAD) :
	{
		. = ALIGN(4);
		_szero = .;
		*(.bss .bss.*)
		*(COMMON)
		. = ALIGN(4);
		_ezero = .;
	} >ram

	.region_cache_aligned (NOLOAD) :
	{
		. = ALIGN(32);
		*(.region_cache_aligned*)
		. = ALIGN(32);
	} >ram

	.heap (NOLOAD) :
	{
		. = ALIGN(4);
		__heap_start__ = .;
		. += HEAP_SIZE;
		__heap_end__ = .;
	} >ram

	.stacks (NOLOAD) :
	{
		. += FIQ_STACK_SIZE;
		. = ALIGN(8);
		_fiqstack = .;

		. += ABT_STACK_SIZE;
		. = ALIGN(8);
		_abtstack = .;

		. += UND_STACK_SIZE;
		. = ALIGN(8);
		_undstack = .;

		. += SYS_STACK_SIZE;
		. = ALIGN(8);
		_sysstack = .;

		. += C_STACK_SIZE;
		. = ALIGN(8);
		_cstack = .;
	} >ram
	_end = .;
	_ramcode_lma = _end;
	.ramcode :
	AT ( _ramcode_lma )
	{
		_sramcode = .; *(.ramcode_section*); _eramcode = .;
	} > sram
	_ramdata_lma = _end + _eramcode - _sramcode;
	.ramdata :
	AT ( _ramdata_lma )
	{
		_sramdata = .; *(.ramdata_section*); _eramdata = .;
	} > sram
}
