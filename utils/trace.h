/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2014, Atmel Corporation
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

/**
 *  \file
 *
 *  \par Purpose
 *
 *  Standard output methods for reporting debug information, warnings and
 *  errors, which can be easily be turned on/off.
 *
 *  \par Usage
 *  -# Initialize the DBGU using TRACE_CONFIGURE() if you intend to eventually
 *     disable ALL traces; otherwise use console_configure().
 *  -# Uses the trace_debug(), trace_info(), trace_warning(), trace_error()
 *     trace_fatal() macros to output traces throughout the program.
 *  -# Each type of trace has a level : Debug 5, Info 4, Warning 3, Error 2
 *     and Fatal 1. Disable a group of traces by changing the value of
 *     TRACE_LEVEL during compilation; traces with a level bigger than TRACE_LEVEL
 *     are not generated. To generate no trace, use the reserved value 0.
 *  -# Trace disabling can be static or dynamic. If dynamic disabling is selected
 *     the trace level can be modified in runtime. If static disabling is selected
 *     the disabled traces are not compiled.
 *
 *  \par traceLevels Trace level description
 *  -# trace_debug (5): Traces whose only purpose is for debugging the program,
 *     and which do not produce meaningful information otherwise.
 *  -# trace_info (4): Informational trace about the program execution. Should
 *     enable the user to see the execution flow.
 *  -# trace_warning (3): Indicates that a minor error has happened. In most case
 *     it can be discarded safely; it may even be expected.
 *  -# trace_error (2): Indicates an error which may not stop the program execution,
 *     but which indicates there is a problem with the code.
 *  -# trace_fatal (1): Indicates a major error which prevents the program from going
 *     any further.
 */

#ifndef _TRACE_
#define _TRACE_

/*
 *         Headers
 */

#include "resources/compiler_defines.h"

#include <stdio.h>

/*
 *         Global Definitions
 */

#define TRACE_LEVEL_DEBUG      5
#define TRACE_LEVEL_INFO       4
#define TRACE_LEVEL_WARNING    3
#define TRACE_LEVEL_ERROR      2
#define TRACE_LEVEL_FATAL      1
#define TRACE_LEVEL_NO_TRACE   0

/* By default, all traces are output except the debug one. */
#if !defined(TRACE_LEVEL)
#define TRACE_LEVEL TRACE_LEVEL_INFO
#endif

/* By default, trace level is static (not dynamic) */
#if !defined(DYN_TRACES)
#define DYN_TRACES 0
#endif

#if defined(NOTRACE)
#error "Error: NOTRACE has to be not defined !"
#endif

#undef NOTRACE
#if (DYN_TRACES==0)
#if (TRACE_LEVEL == TRACE_LEVEL_NO_TRACE)
#define NOTRACE
#endif
#endif

/* ------------------------------------------------------------------------------
 *         Global Macros
 * ------------------------------------------------------------------------------
 */

void trace_configure(uint32_t baudrate);

/**
 *  Initializes the DBGU for ISP project
 *  \param mode  CONSOLE mode.
 *  \param baudrate  CONSOLE baudrate.
 *  \param mck  Master clock frequency.
 */
#ifndef DYNTRACE
#define DYNTRACE 0
#endif

#if (TRACE_LEVEL==0) && (DYNTRACE==0)
#define TRACE_CONFIGURE_ISP(mode, baudrate) {}
#else
#define TRACE_CONFIGURE_ISP(mode, baudrate) {			       \
		const struct _pin pinsCONSOLE[] = PINS_CONSOLE;	       \
		pio_configure(pinsCONSOLE, PIO_LISTSIZE(pinsCONSOLE)); \
		console_configure(baudrate);			       \
	}
#endif

/**
 *  Outputs a formatted string using 'printf' if the log level is high
 *  enough. Can be disabled by defining TRACE_LEVEL=0 during compilation.
 *  \param ...  Additional parameters depending on formatted string.
 */
#if defined(NOTRACE)

/* Empty macro */
#define trace_debug(...)      { }
#define trace_info(...)       { }
#define trace_warning(...)    { }
#define trace_error(...)      { }
#define trace_fatal(...)      { while(1); }

#define trace_debug_wp(...)   { }
#define trace_info_wp(...)    { }
#define trace_warning_wp(...) { }
#define trace_error_wp(...)   { }
#define trace_fatal_wp(...)   { while(1); }

#elif (DYN_TRACES == 1)

/* Trace output depends on dwTraceLevel value */
#define trace_debug(...)      { if (dwTraceLevel >= TRACE_LEVEL_DEBUG)   { printf("-D- " __VA_ARGS__); } }
#define trace_info(...)       { if (dwTraceLevel >= TRACE_LEVEL_INFO)    { printf("-I- " __VA_ARGS__); } }
#define trace_warning(...)    { if (dwTraceLevel >= TRACE_LEVEL_WARNING) { printf("-W- " __VA_ARGS__); } }
#define trace_error(...)      { if (dwTraceLevel >= TRACE_LEVEL_ERROR)   { printf("-E- " __VA_ARGS__); } }
#define trace_fatal(...)      { if (dwTraceLevel >= TRACE_LEVEL_FATAL)   { printf("-F- " __VA_ARGS__); while(1); } }

#define trace_debug_wp(...)   { if (dwTraceLevel >= TRACE_LEVEL_DEBUG)   { printf(__VA_ARGS__); } }
#define trace_info_wp(...)    { if (dwTraceLevel >= TRACE_LEVEL_INFO)    { printf(__VA_ARGS__); } }
#define trace_warning_wp(...) { if (dwTraceLevel >= TRACE_LEVEL_WARNING) { printf(__VA_ARGS__); } }
#define trace_error_wp(...)   { if (dwTraceLevel >= TRACE_LEVEL_ERROR)   { printf(__VA_ARGS__); } }
#define trace_fatal_wp(...)   { if (dwTraceLevel >= TRACE_LEVEL_FATAL)   { printf(__VA_ARGS__); while(1); } }

#else

/* Trace compilation depends on TRACE_LEVEL value */
#if (TRACE_LEVEL >= TRACE_LEVEL_DEBUG)
#define trace_debug(...)      { printf(__FILE__":"STRINGIFY(__LINE__)\
				       " -D- " __VA_ARGS__); }
#define trace_debug_wp(...)   { printf(__VA_ARGS__); }
#else
#define trace_debug(...)      { }
#define trace_debug_wp(...)   { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_INFO)
#define trace_info(...)       { printf("-I- " __VA_ARGS__); }
#define trace_info_wp(...)    { printf(__VA_ARGS__); }
#else
#define trace_info(...)       { }
#define trace_info_wp(...)    { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_WARNING)
#define trace_warning(...)    { printf("-W- " __VA_ARGS__); }
#define trace_warning_wp(...) { printf(__VA_ARGS__); }
#else
#define trace_warning(...)    { }
#define trace_warning_wp(...) { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_ERROR)
#define trace_error(...)      { printf("-E- " __VA_ARGS__); }
#define trace_error_wp(...)   { printf(__VA_ARGS__); }
#else
#define trace_error(...)      { }
#define trace_error_wp(...)   { }
#endif

#if (TRACE_LEVEL >= TRACE_LEVEL_FATAL)
#define trace_fatal(...)      { printf("-F- " __VA_ARGS__); while(1); }
#define trace_fatal_wp(...)   { printf(__VA_ARGS__); while(1); }
#else
#define trace_fatal(...)      { while(1); }
#define trace_fatal_wp(...)   { while(1); }
#endif

#endif

/* ------------------------------------------------------------------------------
 *         Exported variables
 * ----------------------------------------------------------------------------*/

/** Depending on DYN_TRACES, dwTraceLevel is a modifable runtime variable or a define */
#if !defined(NOTRACE) && (DYN_TRACES == 1)
extern uint32_t dwTraceLevel;
#endif

#endif	//#ifndef _TRACE_H
