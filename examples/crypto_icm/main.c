/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2016, Atmel Corporation
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
 * DISCLAIMED. IN NO EVENT ICMLL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */

/**
 *  \page ICM Integrity Check Monitor Example with sama5 Microcontrollers
 *
 *  \section Purpose
 *  This application demonstrates The Integrity Check Monitor (ICM)
 *  peripheral integrated in some SAMA5 microcontrollers. The ICM controller integrates
 *  two modes of operation. The first one is used to hash a list of memory regions and save
 *  the digests to memory (ICM Hash Area). The second operation mode is an active monitoring
 *  of the memory.
 *
 * \section Requirements
 *
 * This package can be used with SAMA5 evaluation kits.
 *
 * \section Description
 * This example shows how to configure ICM to performs SHA-based memory hashing ober memory
 * regions. When the ICM module is enabled, it sequentially retrieves a circular 
 * list of region descriptors from the memory. Up to 4 regions may be monitored.
 *
 *  \section Usage
 *
 *  -# Build the program and download it inside the evaluation board. Please
 *     refer to the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/6421B.pdf">
 *     SAM-BA User Guide</a>, the
 *     <a href="http://www.atmel.com/dyn/resources/prod_documents/doc6310.pdf">
 *     GNU-Based Software Development</a>
 *     application note or to the
 *     <a href="ftp://ftp.iar.se/WWWfiles/arm/Guides/EWARM_UserGuide.ENU.pdf">
 *     IAR EWARM User Guide</a>,
 *     depending on your chosen solution.
 *  -# On the computer, open and configure a terminal application
 *     (e.g. HyperTerminal on Microsoft Windows) with these settings:
 *    - 115200 bauds
 *    - 8 bits of data
 *    - No parity
 *    - 1 stop bit
 *    - No flow control
 *  -# In the terminal window, the
 *     following text should appear (values depend on the board and chip used):
 *     \code
 *      -- ICM Example xxx --
 *      -- SAMxxxxxx-xx
 *      -- Compiled: xxx xx xxxx xx:xx:xx --
 *      \endcode
 *  -# Input command according to the menu.
 *
 * \section References
 * - icm/main.c
 * - icm.h
 * - icm.h
 */

/** \file
 *
 *  This file contains all the specific code for the ICM
 */

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/
#include "board.h"
#include "chip.h"
#include "trace.h"
#include "compiler.h"

#include "mm/cache.h"
#include "irq/irq.h"
#include "peripherals/pmc.h"
#include "crypto/icm.h"
#include "serial/console.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
#define ID_REGION0      0x01
#define ID_REGION1      0x02
#define ID_REGION2      0x04
#define ID_REGION3      0x08

#define HASH_REGION1_OFFSET 8

#define MSG_LEN_WORDS   16
/*----------------------------------------------------------------------------
 *        Local variables
 *----------------------------------------------------------------------------*/
/* Hash memory location. The address must be a multiple of 128 bytes*/
ALIGNED(128) static uint32_t hash_addr[64];

/* ICM region descriptor, the start address is a multiple of the total size of
    the data structure (64 bytes).*/
ALIGNED(64) static struct _icm_region_desc mainlist[4];

static const uint32_t message_ref0[MSG_LEN_WORDS] =
	{ 0x11111111, 0x22222222, 0x33333333, 0x44444444,
	  0x55555555, 0x66666666, 0x77777777, 0x88888888,
	  0x99999999, 0xaaaaaaaa, 0xbbbbbbbb, 0xcccccccc,
	  0xdddddddd, 0xeeeeeeee, 0xffffffff, 0x00000000
	};

/* 512 bits Message Memory Mapping for region 0 sha1 */
CACHE_ALIGNED static uint32_t message_region0_sha1[MSG_LEN_WORDS];

static const uint32_t message_ref1[MSG_LEN_WORDS] =
	{ 0x80636261, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x00000000,
	  0x00000000, 0x00000000, 0x00000000, 0x18000000
	};

/* 512 bits Message Memory Mapping for region 1 sha1 */
CACHE_ALIGNED static uint32_t message_region1_sha1[MSG_LEN_WORDS];

/* Result of  SHA-160 Message Digest Memory Mapping */
const uint32_t hash_sha1[] =
	{ 0x363e99a9, 0x6a810647, 0x71253eba, 0x6cc25078,
	  0x9dd8d09c, 0x00000000, 0x00000000, 0x00000000
	};

/* 512 bits Message Memory Mapping for region 2 sha224 */
CACHE_ALIGNED static uint32_t message_region2_sha224[MSG_LEN_WORDS];

/* Result of  SHA-224 Message Digest Memory Mapping */
const uint32_t hash_sha224[] =
	{ 0x227d0923, 0x22d80534, 0x77a44286, 0xb355a2bd,
	  0xe4bcad2a, 0xf7b3a0bd, 0xa79d6ce3, 0x00000000 };

/* 512 bits Message Memory Mapping for region 3 sha256 */
CACHE_ALIGNED static uint32_t message_region3_sha256[MSG_LEN_WORDS];

/* Result of  SHA-256 Message Digest Memory Mapping */
const uint32_t hash_sha256[] =
	{ 0xbf1678ba, 0xeacf018f, 0xde404141, 0x2322ae5d,
	  0xa36103b0, 0x9c7a1796, 0x61ff10b4, 0xad1500f2
	};

static volatile uint32_t region_hash_comp, region_mismatch;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/**
 * \brief ICM interrupt hander.
 */
static void ICM_IrqHandler(uint32_t source, void* user_arg)
{
	uint32_t status;
	assert(source == ID_ICM);
	status = icm_get_int_status();
	region_hash_comp |= (status & ICM_IMR_RHC_Msk);
	region_mismatch |= (status & ICM_IMR_RDM_Msk);
}

static void check_hash(uint8_t region)
{
	uint8_t i;
	printf("Check Hash result for region %x...\n\r", region);
	for (i = 0; i < 8; i++) {
		if (region == 1) {
			if (hash_addr[HASH_REGION1_OFFSET * region + i] != hash_sha1[i])
				break;
		}
		if (region == 2) {
			if (hash_addr[HASH_REGION1_OFFSET * region + i] != hash_sha224[i])
				break;
		}
		if (region == 3) {
			if (hash_addr[HASH_REGION1_OFFSET * region + i] != hash_sha256[i])
				break;
		}
	}
	if (i == 8)
		printf("Hash correct (see Datasheet 52.5.3.1 Message Digest Example \n\r");
}

int main( void )
{
	uint8_t i;

	/* Output example information */
	console_example_info("ICM Example");

	/* Enable ICM peripheral clock */
	pmc_configure_peripheral(ID_ICM, NULL, true);

	printf("\n\r-I- Configure region 0 with SHA1 algorithm (free message)\n\r");
	memcpy((uint8_t*)message_region0_sha1, message_ref0,
		sizeof message_region0_sha1);
	mainlist[0].icm_raddr = (uint32_t)message_region0_sha1;
	mainlist[0].icm_rcfg =  ICM_RCFG_ALGO_SHA1;
	mainlist[0].icm_rctrl = 0; /* The formula is : (TRSIZE+1) blocks of 512 bits. */
	mainlist[0].icm_rnext = 0;

	printf("-I- Configure region 1 with SHA1 algorithm (example message in DataSheet) \n\r");
	memcpy((uint8_t*)message_region1_sha1, message_ref1,
		sizeof message_region1_sha1);
	mainlist[1].icm_raddr = (uint32_t)message_region1_sha1;
	mainlist[1].icm_rcfg = ICM_RCFG_ALGO_SHA1;
	mainlist[1].icm_rctrl = 0; /* The formula is : (TRSIZE+1) blocks of 512 bits. */
	mainlist[1].icm_rnext = 0;

	printf("-I- Configure region 2 with SHA224 algorithm (example message in DataSheet)\n\r");
	memcpy((uint8_t*)message_region2_sha224, message_ref1,
		sizeof message_region2_sha224);
	mainlist[2].icm_raddr = (uint32_t)message_region2_sha224;
	mainlist[2].icm_rcfg = ICM_RCFG_ALGO_SHA224;
	mainlist[2].icm_rctrl = 0; /* The formula is : (TRSIZE+1) blocks of 512 bits. */
	mainlist[2].icm_rnext = 0;

	printf("-I- Configure region 3 with SHA256 algorithm (example message in DataSheet)\n\r");
	memcpy((uint8_t*)message_region3_sha256, message_ref1,
		sizeof message_region3_sha256);
	mainlist[3].icm_raddr = (uint32_t)message_region3_sha256;
	mainlist[3].icm_rcfg = ICM_RCFG_EOM | ICM_RCFG_ALGO_SHA256;
	mainlist[3].icm_rctrl = 0; /* The formula is : (TRSIZE+1) blocks of 512 bits. */
	mainlist[3].icm_rnext = 0;
	cache_clean_region(mainlist, sizeof(mainlist));

	/* A software triggered hardware reset of the ICM interface is performed */
	icm_swrst();
	irq_add_handler(ID_ICM, ICM_IrqHandler, NULL);
	irq_enable(ID_ICM);

	printf("\n\r-I CDWBN enable, digest is written to the hash area \n\r");
	icm_configure(ICM_CFG_UALGO_SHA1|ICM_CFG_SLBDIS);
	icm_set_desc_address((uint32_t)mainlist);
	icm_set_hash_address((uint32_t)hash_addr);

	region_hash_comp = 0;
	icm_enable_it(ICM_IER_RHC(ID_REGION0 | ID_REGION1 | ID_REGION2 | ID_REGION3));

	/* Enable ICM */
	icm_enable();

	/* Wait for all region hash completed */
	while (region_hash_comp != ICM_IMR_RHC_Msk);

	/* Check the SHA result (example SHA result in DataSheet) */
	for (i = 1; i < 4; i++) {
		check_hash(i);
	}

	icm_disable();
	printf("\n\r-I Monitor enable, digest value is compared to the digest stored in hash area\n\r");
	mainlist[0].icm_raddr = (uint32_t)message_region0_sha1;
	mainlist[0].icm_rcfg =  ICM_RCFG_ALGO_SHA1 | ICM_RCFG_CDWBN;
	mainlist[0].icm_rctrl = 0; /* The formula is : (TRSIZE+1) blocks of 512 bits. */
	mainlist[0].icm_rnext = 0;

	mainlist[1].icm_raddr = (uint32_t)message_region1_sha1;
	mainlist[1].icm_rcfg = ICM_RCFG_ALGO_SHA1| ICM_RCFG_CDWBN;
	mainlist[1].icm_rctrl = 0; /* The formula is : (TRSIZE+1) blocks of 512 bits. */
	mainlist[1].icm_rnext = 0;

	mainlist[2].icm_raddr = (uint32_t)message_region2_sha224;
	mainlist[2].icm_rcfg = ICM_RCFG_ALGO_SHA224 | ICM_RCFG_CDWBN;
	mainlist[2].icm_rctrl = 0; /* The formula is : (TRSIZE+1) blocks of 512 bits. */
	mainlist[2].icm_rnext = 0;

	mainlist[3].icm_raddr = (uint32_t)message_region3_sha256;
	mainlist[3].icm_rcfg =  ICM_RCFG_ALGO_SHA256 | ICM_RCFG_CDWBN | ICM_RCFG_WRAP;
	mainlist[3].icm_rctrl = 0; /* The formula is : (TRSIZE+1) blocks of 512 bits. */
	mainlist[3].icm_rnext = 0;

	cache_clean_region(mainlist, sizeof(mainlist));
	icm_disable_it(-1);
	icm_enable_monitor(ID_REGION0 | ID_REGION1 | ID_REGION2 | ID_REGION3);
	icm_enable_it(ICM_IER_RDM(ID_REGION0 | ID_REGION1 | ID_REGION2 | ID_REGION3));
	printf("Change context in region 0, expect region 0 digest mismatch...\n\r");
	message_region0_sha1[3] = 0xFFFFFFFF;
	printf("Change context in region 1, expect region 1 digest mismatch...\n\r");
	message_region1_sha1[4] = 0xFFFFFFFF;
	printf("Change context in region 2, expect region 2 digest mismatch...\n\r");
	message_region2_sha224[5] = 0xFFFFFFFF;
	printf("Change context in region 3, expect region 3 digest mismatch...\n\r");
	message_region3_sha256[6] = 0xFFFFFFFF;

	cache_clean_region(message_region0_sha1, 64);
	cache_clean_region(message_region1_sha1, 64);
	cache_clean_region(message_region2_sha224, 64);
	cache_clean_region(message_region3_sha256, 64);

	icm_enable();
	region_mismatch = 0;
	while (region_mismatch != ICM_IMR_RDM_Msk);
	printf("Hit digests mismatch, done.\n\r");
	while(1);
}

