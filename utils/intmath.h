/* ----------------------------------------------------------------------------
 *         ATMEL Microcontroller Software Support
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
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

#ifndef _INTMATH_H_
#define _INTMATH_H_

/**
 * \brief Compute the absolute value of the difference between two integers.
 * \param a  The first integer.
 * \param b  The second integer.
 * \return  The absolute difference.
 */
#define ABS_DIFF(a,b) ((a) < (b) ? (b) - (a) : (a) - (b))

/**
 * \brief Compute the ceiling of the quotient of two integers.
 * \param n  The dividend.
 * \param d  The divisor.
 * \note The two integers shall have the same sign.
 * \return  The ceiling of the quotient.
 */
#define CEIL_INT_DIV(n,d) (((n) + (d) - 1) / (d))

/*------------------------------------------------------------------------------
 *         Exported functions
 *------------------------------------------------------------------------------*/

#include <stdint.h>

/** Check possible extensions of the C library being used, and find out if
 *  visible ones provide bit-string functions, including ffs() and fls().
 *  These functions are not part of ANSI C.
 *  Newlib 3.0.0, notably, provides BSD extensions that include fls().
 */
#if defined(__NEWLIB__) && \
		(__NEWLIB__ > 1 || (__NEWLIB__ == 1 && __NEWLIB_MINOR__ > 18))
#include <strings.h>
#if defined(_DEFAULT_SOURCE) && (__NEWLIB__ > 2)
#define HAVE_BSD_FLS
#endif
#endif /* __NEWLIB__ */

/**
 *  Returns the minimum value between two integers.
 *  \param a First integer to compare
 *  \param b Second integer to compare
 */
static inline uint32_t min_u32(uint32_t a, uint32_t b)
{
	return a < b ? a : b;
}

/**
 *  Returns the maximum value between two integers.
 *  \param a First integer to compare
 *  \param b Second integer to compare
 */
static inline uint32_t max_u32(uint32_t a, uint32_t b)
{
	return a > b ? a : b;
}

/**
 *  Returns the absolute value of an integer.
 *  \param value Integer value
 */
static inline uint32_t abs_u32(int32_t value)
{
	return value > 0 ? value : -value;
}

/**
 *  Computes and returns x to the power of y.
 *  \param x Value
 *  \param y Power
 */
static inline uint32_t power_u32(uint32_t x, uint32_t y)
{
        uint32_t result = 1;
        while (y > 0) {
                result *= x;
                y--;
        }
        return result;
}

/** ISO/IEC 14882:2003(E) - 5.6 Multiplicative operators:
 * The binary / operator yields the quotient, and the binary % operator yields the remainder
 * from the division of the first expression by the second.
 * If the second operand of / or % is zero the behavior is undefined; otherwise (a/b)*b + a%b is equal to a.
 * If both operands are nonnegative then the remainder is nonnegative;
 * if not, the sign of the remainder is implementation-defined 74).
 */
static inline int fixed_mod(int a, int b)
{
	int rem = a % b;
	while (rem < 0)
		rem += b;

	return rem;
}

#ifndef HAVE_BSD_FLS
/**
 *  Find last bit set in a word
 *  \param value Integer value
 *  \return 1-indexed position of the most significant bit set; 0 if none
 */
extern int fls(int value);
#endif

#endif /* _INTMATH_H_ */
