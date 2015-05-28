/* ----------------------------------------------------------------------------
 *         SAM Software Package License 
 * ----------------------------------------------------------------------------
 * Copyright (c) 2013, Atmel Corporation
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

/** \addtogroup isc_module
 * @{
 * \section isc_usage Usage
 * - ISC_StartCapture: Send Capture Input Stream Command to start a single 
 *						shot capture or a multiple frame
 */
/**@}*/

#ifndef ISC_H
#define ISC_H


/*----------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/
extern void ISC_StartCapture(void);
extern void ISC_StopCapture(void);
extern uint32_t ISC_GetCtrlStatus(void);
extern void ISC_UpdateProfile(void);
extern void ISC_UpdateHistogram(void);
extern void ISC_ClearHistogram(void);
extern void ISC_Reset(void);
extern void ISC_PFE_SetCroppingArea( 
			uint32_t Hstart, uint32_t Hend, uint32_t Vstart, uint32_t Vend)
extern void ISC_ConfigureIspClock(
			uint32_t ispClockDiv, uint32_t ispClockSelection);
extern void ISC_EnableIspClock(void);
extern void ISC_DisableIspClock(void);
extern void ISC_ResetIspClock(void);
extern void ISC_ConfigureMasterClock(
			uint32_t masterClockDiv, uint32_t masterClockSelection);
extern void ISC_EnableMasterClock(void);
extern void ISC_DisableMasterClock(void);
extern void ISC_ResetMasterClock(void);
extern uint32_t ISC_GetClockStatus(void);
extern void ISC_EnableInterrupt(uint32_t flag);
extern void ISC_DisableInterrupt(uint32_t flag);
extern uint32_t ISC_StatusRegister(void);

#endif //#ifndef ISC_H

