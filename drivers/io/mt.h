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


//------------------------------------------------------------------------------
/// \unit
///
/// !!!Purpose
///
/// Specific configuration for Omnivision OV6555 captor
///
/// !!!Usage
///
/// -# Different files are been provided by Omnivision:
///     - 9655_yuv_cif.h
///     - 9655_yuv_qcif.h
///     - 9655_yuv_qqcif.h
///     - 9655_yuv_qqvga.h
///     - 9655_yuv_qvga.h
///     - 9655_yuv_sxga.h
///     - 9655_yuv_vga.h
/// -# Configure the captor using theses files
//------------------------------------------------------------------------------

#ifndef MT_H
#define MT_H

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** Captor capture size */
struct capture_size1 {
	unsigned long width;
	unsigned long height;
};

/*----------------------------------------------------------------------------
 *       Exported functions
 *----------------------------------------------------------------------------*/
extern void mt_configure(Twid *pTwid, uint32_t width, uint32_t heigth);
#endif

