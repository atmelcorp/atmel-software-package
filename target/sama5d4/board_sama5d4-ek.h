#ifndef _BOARD_SAMA5D4_EK_HEADER_
#define _BOARD_SAMA5D4_EK_HEADER_

#include "board_sama5d4-common.h"

/** USB OverCurrent detection*/
#define PIN_USB_OVCUR     {PIO_PD9, PIOD, ID_PIOD, PIO_INPUT, PIO_PULLUP}
/** USB Power Enable A:MicroAB:Active low */
#define PIN_USB_POWER_ENA {PIO_PE10, PIOE, ID_PIOE, PIO_OUTPUT_1, PIO_DEFAULT}
/** USB Power Enable B:A:Active low  */
#define PIN_USB_POWER_ENB {PIO_PE11, PIOE, ID_PIOE, PIO_OUTPUT_1, PIO_DEFAULT}
/** USB Power Enable C:A:Active low  */
#define PIN_USB_POWER_ENC {PIO_PE12, PIOE, ID_PIOE, PIO_OUTPUT_1, PIO_DEFAULT}

/** /def Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE      DDRAM_MT47H128M8CF

/** MCI0 Card detect pin definition. (PE5) */
#define BOARD_MCI0_PIN_CD       {PIO_PE5, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP}
/** MCI0 power control: none, always powered on */
//#define BOARD_MCI0_PIN_POWER    {PIO_PE15, PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_PULLUP}

/** MCI1 Card detect pin definition. (PE14) */
#define BOARD_MCI1_PIN_CD       {PIO_PE6, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP}
/** MCI1 power control */
#define BOARD_MCI1_PIN_POWER    {PIO_PE15, PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_PULLUP}

/** Display width in pixels. */
#define BOARD_LCD_WIDTH             800
/** Display height in pixels. */
#define BOARD_LCD_HEIGHT            480

/** LED #0 pin definition (LED_BLUE). */
#define PIN_LED_0   {(PIO_PE8), PIOE, ID_PIOE, PIO_OUTPUT_1, PIO_DEFAULT}
/** LED #1 pin definition (LED_RED). */
#define PIN_LED_1   {(PIO_PE9), PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_DEFAULT}
/** LED #2 pin definition (LED_GREEN). */
#define PIN_LED_2   {(PIO_PE28), PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_DEFAULT}

/** List of all LEDs definitions. */
#define PINS_LEDS   PIN_LED_0, PIN_LED_1,PIN_LED_2

/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PIN_PUSHBUTTON_1    {PIO_PE13, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}
#define PIN_PUSHBUTTON_2    {PIO_PE13, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}

/*----------------------------------------------------------------------------
 *        Relative definitions of Softpack Example
 *----------------------------------------------------------------------------*/

/* lcd example */
/** LCD image's scale */
#define EXAMPLE_LCD_SCALE   2

/* pwm example */
/** index of the first PWM channel used to light the LED*/
#define EXAMPLE_PWM_CHANNEL_INDEX0  1
/** index of the second PWM channel used to light the LED*/
#define EXAMPLE_PWM_CHANNEL_INDEX1  3
/** Pins of the first PWM channel used to light the LED*/
#define EXAMPLE_PWM_CHANNEL_PINS0   {PIO_PB28C_PWMH1,  PIOB, ID_PIOB, PIO_PERIPH_C, PIO_DEFAULT}
/** Pins of the second PWM channel used to light the LED*/
#define EXAMPLE_PWM_CHANNEL_PINS1   {PIO_PE14C_PWMH3,  PIOE, ID_PIOE, PIO_PERIPH_C, PIO_DEFAULT}

/* spi_slave example */
/** pin for SPI CS signal */
#define EXAMPLE_SPI_SLAVE_CS_PIN    PIN_SPI1_NPCS2
/** SPI CS index */
#define EXAMPLE_SPI_SLAVE_CS_IDX    2

/* twi_slave example */
/** Eeprom Pins definition */
#define EXAMPLE_TWI_SLAVE_PINS  PINS_TWI0
/** TWI peripheral ID for eeprom device*/
#define EXAMPLE_TWI_SLAVE_ID    ID_TWI0
/** TWI base address for eeprom device */
#define EXAMPLE_TWI_SLAVE_BASE  TWI0

/* hsmci_multimedia_card example, hsmci_sdcard example */
/** SD card Power control pin instance */
#define EXAMPLE_MCI_POWER_PINS  BOARD_MCI1_PIN_POWER

#endif				/* _BOARD_SAMA5D4_EK_HEADER_ */
