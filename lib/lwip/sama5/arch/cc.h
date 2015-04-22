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

#ifndef _CC_H
#define _CC_H

/* Define platform endianness */
#define BYTE_ORDER LITTLE_ENDIAN

/* The unsigned data types */
typedef unsigned char   u8_t;
typedef unsigned short  u16_t;
typedef unsigned int    u32_t;

/* The signed counterparts */
typedef signed char     s8_t;
typedef signed short    s16_t;
typedef signed int      s32_t;

/* A generic pointer type */
typedef u32_t mem_ptr_t;

/* Display name of types */
#define U16_F           "hu"
#define S16_F           "hd"
#define X16_F           "hx"
#define U32_F           "u"
#define S32_F           "d"
#define X32_F           "x"

/* Compiler hints for packing lwip's structures */
#if defined(__CC_ARM)
    /* Setup PACKing macros for MDK Tools */
    #define PACK_STRUCT_BEGIN
    #define PACK_STRUCT_STRUCT __attribute__ ((packed))
    #define PACK_STRUCT_END
    #define PACK_STRUCT_FIELD(x) x
#elif defined (__ICCARM__)
    /* Setup PACKing macros for EWARM Tools */
    #define PACK_STRUCT_BEGIN __packed
    #define PACK_STRUCT_STRUCT
    #define PACK_STRUCT_END
    #define PACK_STRUCT_FIELD(x) x
#elif defined (__GNUC__)
    /* Setup PACKing macros for GCC Tools */
    #define PACK_STRUCT_BEGIN
    #define PACK_STRUCT_STRUCT __attribute__ ((packed))
    #define PACK_STRUCT_END
    #define PACK_STRUCT_FIELD(x) x
#else
    #error "This compiler does not support."
#endif

#endif  /* _CC_H */

