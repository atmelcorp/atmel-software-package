/**
 * \page sama5d2_generic_board_desc sama5d2-generic - Board Description
 *
 * \section Purpose
 *
 * This file is dedicated to describe a generic sama5d2 board.
 *
 * \section Contents
 *
 *  - sama5d2-generic
 *  - For sama5d2-generic information, see \subpage sama5d2_generic_board_info.
 *  - For operating frequency information, see \subpage sama5d2_generic_opfreq.
 *  - For using portable PIO definitions, see \subpage sama5d2_generic_piodef.
 *  - For on-board memories, see \subpage sama5d2_generic_mem.
 *  - Several USB definitions are included here, see \subpage sama5d2_generic_usb.
 *  - For External components, see \subpage sama5d2_generic_extcomp.
 *  - For Individual chip definition, see \subpage sama5d2_generic_chipdef.
 *
 * To get more software details and the full list of parameters related to the
 * sama5d2-generic board configuration, please have a look at the source file:
 * \ref board.h\n
 *
 * \section Usage
 *
 *  - The code for booting the board is provided by board_cstartup_xxx.c and
 *    board_lowlevel.c.
 *  - For using board PIOs, board characteristics (clock, etc.) and external
 *    components, see board.h.
 *  - For manipulating memories, see board_memories.h.
 *
 * This file can be used as a template and modified to fit a custom board, with
 * specific PIOs usage or memory connections.
 */

/**
 *  \file board.h
 *
 *  Definition of sama5d2-generic
 *  characteristics, sama5d4-dependant PIOs and external components interfacing.
 */

#ifndef _BOARD_D2_H
#define _BOARD_D2_H

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

#include "board_support.h"

/*----------------------------------------------------------------------------
 *        HW BOARD Definitions
 *----------------------------------------------------------------------------*/

/**
 * \page sama5d2_generic_board_info "sama5d2-generic - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "sama5d2-generic"

/*----------------------------------------------------------------------------*/

/** Frequency of the board main clock oscillator (autodetect) */
#define BOARD_MAIN_CLOCK_EXT_OSC 0

/** \def Board System timer */
#define BOARD_TIMER_TC      TC1
#define BOARD_TIMER_CHANNEL 0

#endif /* #ifndef _BOARD_D2_H */
