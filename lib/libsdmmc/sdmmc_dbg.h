/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2010, Atmel Corporation
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

/** \file */

#ifndef _SDMMC_HAL_H
#define _SDMMC_HAL_H

/*------------------------------------------------------------------------------
 *      Includes
 *----------------------------------------------------------------------------*/

#include <stdint.h>
#include "sdmmc_cmd.h"

/*------------------------------------------------------------------------------
 *      Definitions
 *----------------------------------------------------------------------------*/

/* Define WEAK attribute */
#ifndef WEAK
#if defined   ( __CC_ARM   )
#define WEAK __attribute__ ((weak))
#elif defined ( __ICCARM__ )
#define WEAK __weak
#elif defined (  __GNUC__  )
#define WEAK __attribute__ ((weak))
#endif
#endif

/*----------------------------------------------------------------------------
 *      Functions
 *----------------------------------------------------------------------------*/

/** Initialize the SD/MMC card driver struct */
void SDD_Initialize(sSdCard * pSd,
			   const void *pDrv, uint8_t bSlot,
			   const sSdHalFunctions * pHalFunctions);

/** Initialize the SD/MMC card driver struct for SD/MMC bus mode
 *  \note defined in SD/MMC bus mode low level
 */
extern WEAK void SDD_InitializeSdmmcMode(sSdCard * pSd,
					 void *pDrv, uint8_t bSlot);

/** Initialize the SD/MMC card driver struct for SPI bus mode
 *  \note defined in SD/MMC SPI bus mode low level
 */
extern WEAK void SDD_InitializeSpiMode(sSdCard * pSd,
				       void *pDrv, uint8_t bSlot);

#endif				/* #define _SDMMC_HAL_H */
