/**
 * \page sama5d2_xult_board_desc sama5d2-XULT - Board Description
 *
 * \section Purpose
 *
 * This file is dedicated to describe the sama5d2-XULT board.
 *
 * \section Contents
 *
 *  - sama5d2-XULT 
 *  - For sama5d2-XULT information, see \subpage sama5d2_xult_board_info.
 *  - For operating frequency information, see \subpage sama5d2_xult_opfreq.
 *  - For using portable PIO definitions, see \subpage sama5d2_xult_piodef.
 *  - For on-board memories, see \subpage sama5d2_xult_mem.
 *  - Several USB definitions are included here, see \subpage sama5d2_xult_usb.
 *  - For External components, see \subpage sama5d2_xult_extcomp.
 *  - For Individual chip definition, see \subpage sama5d2_xult_chipdef.
 *
 * To get more software details and the full list of parameters related to the
 * sama5d2-XULT board configuration, please have a look at the source file:
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
 *  Definition of sama5d2-XULT 
 *  characteristics, sama5d4-dependant PIOs and external components interfacing.
 */

#ifndef _BOARD_
#define _BOARD_

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "chip.h"

/*----------------------------------------------------------------------------
 *        HW BOARD Definitions
 *----------------------------------------------------------------------------*/

/**
 * \page sama5d2_xult_board_info "sama5d2-XULT - Board informations"
 * This page lists several definition related to the board description.
 *
 * \section Definitions
 * - \ref BOARD_NAME
 */

/** Name of the board */
#define BOARD_NAME "sama5d2-xult"

/** Family definition */
#if !defined sama5d2
  #define sama5d2
#endif

/** Board definition */
#define sama5d2xult
/** Core definition */
#define cortexa5

#define BOARD_REV_A_XULT

/*----------------------------------------------------------------------------*/
/**
 *  \page sama5d2_xult_opfreq "sama5d2-XULT - Operating frequencies"
 *  This page lists several definition related to the board operating frequency
 *  (when using the initialization done by board_lowlevel.c).
 */

/** Frequency of the board main oscillator */
#define BOARD_MAINOSC           12000000
#define BOARD_MAINOSC_MHZ       BOARD_MAINOSC/1000000


/* =================== PIN CONSOLE definition ================== */

/** CONSOLE pin definition, Use only UART */   
#define PINS_CONSOLE            PINS_UART1_IOS1
#define CONSOLE_PER_ADD         UART1    
#define CONSOLE_ID              ID_UART1 
#define CONSOLE_BAUDRATE        115200   
   
/* =================== PIN LED definition ====================== */

/* RGB LED index */
#define LED_RED       0
#define LED_GREEN     1 
#define LED_BLUE      2 /* led blue shared with SDHC0 card detect (eMMC) */

#define PIO_CFGR_LED  (PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_OUTPUT | PIO_CFGR_PUEN_DISABLED | PIO_CFGR_PDEN_DISABLED)

/** LED #0 pin definition (LED_RED). */
#define PIN_LED_RED     {\
  { ID_PIOA, PIO_PA13, PIO_CFGR_FUNC_A, PIO_CFGR_LED },\
}    
#define PIN_LED_0       PIN_LED_RED

/** LED #1 pin definition (LED_GREEN). */
#define PIN_LED_GREEN   {\
  { ID_PIOB, PIO_PB5, PIO_CFGR_FUNC_A, PIO_CFGR_LED },\
}    
#define PIN_LED_1       PIN_LED_GREEN

/** LED #2 pin definition (LED_BLUE). */
#define PIN_LED_BLUE    [\
  { ID_PIOB, PIO_PB0, PIO_CFGR_FUNC_A, PIO_CFGR_LED },\
}    
#define PIN_LED_2       PIN_LED_BLUE

/** List of all LEDs definitions. */
#define PINS_LEDS       PIN_LED_0, PIN_LED_1, PIN_LED_2

/* =================== PIN PUSH BUTTON definition ============== */

#define PIO_CFGR_PB  (PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_INPUT | PIO_CFGR_PUEN_ENABLED | \
                      PIO_CFGR_IFEN_ENABLED | PIO_CFGR_EVTSEL_FALLING )

#define PIN_PUSHBUTTON_1 {\
  { ID_PIOB, PIO_PB6, PIO_CFGR_FUNC_A, PIO_CFGR_PB },\
}    
#define PIN_PUSHBUTTON_2 {\
  { ID_PIOB, PIO_PB6, PIO_CFGR_FUNC_A, PIO_CFGR_PB },\
} 

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS    PIN_PUSHBUTTON_1, PIN_PUSHBUTTON_2 

/** Push button index. */
#define PUSHBUTTON_BP1   0
#define PUSHBUTTON_BP2   1

/* ================== PIN PMIC definition ====================== */

#define PIO_CFGR_CHGLEV  (PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_OUTPUT | PIO_CFGR_PUEN_ENABLED)    
#define PIN_PMIC_CHGLEV  {\
  { ID_PIOA, PIO_PA12, PIO_CFGR_FUNC_A, PIO_CFGR_CHGLEV },\
}    

#define PIO_CFGR_PMIC_IRQ  PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_INPUT | PIO_CFGR_PUEN_ENABLED | PIO_CFGR_EVTSEL_FALLING )
#define PIN_PMIC_IRQ     {\
  { ID_PIOB, PIO_PB13, PIO_CFGR_FUNC_A, PIO_CFGR_PMIC_IRQ },\
}    

/* ================== PIN USB definition ======================= */

#define PIO_CFGR_OVCUR  (PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_INPUT | PIO_CFGR_PUEN_ENABLED)
#define PIO_CFGR_VBUS   (PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_INPUT | PIO_CFGR_PUEN_DISABLED | PIO_CFGR_PDEN_DISABLED)
#define PIO_CFGR_PWREN  (PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_OUTPUT | PIO_CFGR_PUEN_ENABLED)

/** USB VBus pin */
#define PIN_USB_VBUS      {\
  { ID_PIOA, PIO_PA31, PIO_CFGR_FUNC_A, PIO_CFGR_VBUS },\
}    
/** USB OverCurrent detection*/
#define PIN_USB_OVCUR     {\
  { ID_PIOA, PIO_PA29, PIO_CFGR_FUNC_A, PIO_CFGR_OVCUR },\
}    
/** USB Power Enable A, Active high */
#define PIN_USB_POWER_ENA {\
  { ID_PIOB, PIO_PB9, PIO_CFGR_FUNC_A, PIO_CFGR_PEN },\
}    
/** USB Power Enable B, Active high  */
#define PIN_USB_POWER_ENB {\
  { ID_PIOB, PIO_PB10, PIO_CFGR_FUNC_A, PIO_CFGR_PWREN },\
}    

/* ================= PIN GMAC IRQ definition ==================== */

#define PIO_CFGR_GMAC_IRQ  (PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_INPUT | PIO_CFGR_PUEN_ENABLED | PIO_CFGR_EVTSEL_FALLING )
#define PIN_GMAC_IRQ     {\
  { ID_PIOC, PIO_PC9, PIO_CFGR_FUNC_A, PIO_CFGR_GMAC_IRQ },\
}    

/* ================= PIN LCD IRQ definition ===================== */

#define PIO_CFGR_LCD_IRQ  (PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_INPUT | PIO_CFGR_PUEN_ENABLED | PIO_CFGR_EVTSEL_FALLING )

#define PIN_QT1070_IRQ  {\
  { ID_PIOB, PIO_PB7, PIO_CFGR_FUNC_A, PIO_CFGR_LCD_IRQ },\
}    
#define PIN_MXT336S_IRQ {\
  { ID_PIOB, PIO_PB8, PIO_CFGR_FUNC_A, PIO_CFGR_LCD_IRQ },\
}    
#define PIN_MXT768E_IRQ {\
  { ID_PIOB, PIO_PB8, PIO_CFGR_FUNC_A, PIO_CFGR_LCD_IRQ },\
}    

/* =================== PIN ISC definition ======================= */

#define PIN_ISC_RST     {\
  { ID_PIOB, PIO_PB11, PIO_CFGR_FUNC_A, PIO_CFGR_RESET },\
}    
#define PIN_ISC_PWD     {\
  { ID_PIOB, PIO_PB12, PIO_CFGR_FUNC_A, PIO_CFGR_RESET },\
}  

/* =================== PIN HSDHC definition ======================= */

/* Card detect, input, pull-up */
#define PIO_CFGR_HSDHC1 (PIO_CFGR_FUNC_GPIO | PIO_CFGR_DIR_INPUT | PIO_CFGR_PUEN_ENABLED )
#define PIN_HSDHC1_CD   {\
  { ID_PIOA, PIO_PA30, PIO_CFGR_FUNC_A, PIO_CFGR_HSDHC },\
}    


#define swap(a, b) { uint16_t t = a; a = b; b = t; }


/*----------------------------------------------------------------------------
 *        Headers for board
 *----------------------------------------------------------------------------*/
 


#endif /* #ifndef _BOARD_ */

