/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "board_info.h"
#include "test_mem.h"

#include <stdio.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

// Define NULL pointer value.
#ifndef NULL
#define NULL  (void *)0
#endif

#define TEST_MEM_RET_OK		0
#define TEST_MEM_RET_NOK	1

/*----------------------------------------------------------------------------
 *        Function prototype
 *----------------------------------------------------------------------------*/

uint32_t _mem_test_data_bus (volatile uint32_t* pAddress);
uint32_t* _mem_test_addr_bus (volatile uint32_t* baseAddress, uint64_t nBytes);
uint32_t* _mem_test_device (volatile uint32_t* baseAddress, uint64_t nBytes);


/*----------------------------------------------------------------------------
 *        Function
 *----------------------------------------------------------------------------*/

/**********************************************************************
 *
 * Function:    memTestDataBus()
 *
 * Description: Test the data bus wiring in a memory region by
 *              performing a walking 1's test at a fixed address
 *              within that region.  The address (and hence the
 *              memory region) is selected by the caller.
 *
 * Notes:
 *
 * Returns:     0 if the test succeeds.
 *              A non-zero result is the first pattern that failed.
 *
 **********************************************************************/

uint32_t _mem_test_data_bus (volatile uint32_t* pAddress)
{
    uint32_t pattern;

    // Perform a walking 1's test at the given address.
    for (pattern=1; pattern!=0; pattern<<=1)
    {
        *pAddress = pattern; //Write the test pattern.
        //  Read it back (immediately is okay for this test).
        if (*pAddress != pattern) return (pattern);
    }
    return (0);
}

/**********************************************************************
 *
 * Function:    memTestAddressBus()
 *
 * Description: Test the address bus wiring in a memory region by
 *              performing a walking 1's test on the relevant bits
 *              of the address and checking for aliasing. This test
 *              will find single-bit address failures such as stuck
 *              -high, stuck-low, and shorted pins.  The base address
 *              and size of the region are selected by the caller.
 *
 * Notes:       For best results, the selected base address should
 *              have enough LSB 0's to guarantee single address bit
 *              changes.  For example, to test a 64-Kbyte region,
 *              select a base address on a 64-Kbyte boundary.  Also,
 *              select the region size as a power-of-two--if at all
 *              possible.
 *
 * Returns:     NULL if the test succeeds.
 *              A non-zero result is the first address at which an
 *              aliasing problem was uncovered.  By examining the
 *              contents of memory, it may be possible to gather
 *              additional information about the problem.
 *
 **********************************************************************/
uint32_t* _mem_test_addr_bus(volatile uint32_t* baseAddress, uint64_t nBytes)
{
    uint64_t addressMask = (nBytes/sizeof(uint32_t) - 1);
    uint64_t offset;
    uint64_t testOffset;

    uint32_t pattern     = (uint32_t)0xAAAAAAAA;
    uint32_t antipattern = (uint32_t)0x55555555;

    // Write the default pattern at each of the power-of-two offsets.
    for (offset = 1; (offset & addressMask) != 0; offset <<= 1)
      baseAddress[offset] = pattern;

    // Check for address bits stuck high.
    printf(" Test1: Check for address bits stuck high\n\r");
    testOffset = 0;
    baseAddress[testOffset] = antipattern;
    for (offset = 1; (offset & addressMask) != 0; offset <<= 1)
    {
        if (baseAddress[offset]!=pattern) return ((uint32_t*)&baseAddress[offset]);
    }
    baseAddress[testOffset] = pattern;

    // Check for address bits stuck low or shorted.
    printf(" Test2: Check for address bits stuck low or shorted ");
    for (testOffset = 1; (testOffset & addressMask) != 0; testOffset <<= 1)
    {
        baseAddress[testOffset] = antipattern;
		if (baseAddress[0] != pattern) return ((uint32_t *) &baseAddress[testOffset]);
		for (offset = 1; (offset & addressMask) != 0; offset <<= 1)
        {
          if(offset%65536==0) printf(".");
          if ((baseAddress[offset]!=pattern) && (offset!=testOffset)) return ((uint32_t*)&baseAddress[testOffset]);
        }
        baseAddress[testOffset] = pattern;
    }
    return (NULL);
}

/**********************************************************************
 *
 * Function:    memTestDevice()
 *
 * Description: Test the integrity of a physical memory device by
 *              performing an increment/decrement test over the
 *              entire region.  In the process every storage bit
 *              in the device is tested as a zero and a one.  The
 *              base address and the size of the region are
 *              selected by the caller.
 *
 * Notes:
 *
 * Returns:     NULL if the test succeeds.
 *
 *              A non-zero result is the first address at which an
 *              incorrect value was read back.  By examining the
 *              contents of memory, it may be possible to gather
 *              additional information about the problem.
 *
 **********************************************************************/
uint32_t* _mem_test_device (volatile uint32_t* baseAddress, uint64_t nBytes)
{
    uint64_t offset;
    uint64_t nWords = nBytes / sizeof(uint32_t);
    uint32_t pattern;
    uint32_t antipattern;

    // Fill memory with a known pattern.
    for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
      baseAddress[offset] = pattern;

    // Check each location and invert it for the second pass.
    printf("\n\r");
    printf(" Test3: Check pattern each location and invert it for the second pass ");
    for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
    {
        if(offset%65536==0) printf(".");
        if (baseAddress[offset] != pattern) return ((uint32_t *) &baseAddress[offset]);
        antipattern = ~pattern;
        baseAddress[offset] = antipattern;
    }

    // Check each location for the inverted pattern and zero it.
    printf("\n\r");
    printf(" Test4: Check each location for the inverted pattern and zero it");
    for (pattern = 1, offset = 0; offset < nWords; pattern++, offset++)
    {
        if(offset%65536==0) printf(".");
        antipattern = ~pattern;
        if (baseAddress[offset] != antipattern) return ((uint32_t*) &baseAddress[offset]);
    }
    return (NULL);
}

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

uint8_t test_ddr_sdram(uint32_t* addr_start,
		       uint32_t* addr_end, uint64_t nBytes)
{
	uint32_t pattern;
	uint32_t* pMem = NULL;

	printf(" --T-- from 0x%x to 0x%x \n\r",
	       (unsigned int)addr_start,
	       (unsigned int)(addr_start+nBytes));
	pattern = _mem_test_data_bus (addr_start);
	if ( pattern != 0) {
		printf(" --E-- Error walking bit: 0x%X \n\r",
		       (unsigned int)pattern);
		return TEST_MEM_RET_NOK;
	}
	pMem = _mem_test_addr_bus(addr_start, nBytes);
	if ( pMem != NULL) {
		printf(" --E-- Error adress bus: 0x%X \n\r",
		       (unsigned int)pMem);
		return TEST_MEM_RET_NOK;
	}
	pMem = _mem_test_device(addr_start, nBytes);
	if (pMem != NULL) {
		printf(" --E-- Error r/w adress: 0x%X \n\r",
		       (unsigned int)pMem);
		return TEST_MEM_RET_NOK;
	}
	return TEST_MEM_RET_OK;
}
