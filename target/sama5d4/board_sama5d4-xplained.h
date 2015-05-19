#ifndef _BOARD_SAMA5D4_XPLAINED_HEADER_
#define _BOARD_SAMA5D4_XPLAINED_HEADER_

#include "board_sama5d4-common.h"

/** USB OverCurrent detection*/
#define PIN_USB_OVCUR     {PIO_PE0, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP}
/** USB Power Enable A:MicroAB:Active low */
//#define PIN_USB_POWER_ENA {PIO_PE10, PIOE, ID_PIOE, PIO_OUTPUT_1, PIO_DEFAULT}
/** USB Power Enable B:A:Active High  */
#define PIN_USB_POWER_ENB {PIO_PE11, PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_DEFAULT}
/** USB Power Enable C:A:Active High  */
#define PIN_USB_POWER_ENC {PIO_PE14, PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_DEFAULT}

/** /def Definition of DDRAM's type */
#define BOARD_DDRAM_TYPE      DDRAM_MT47H128M16

/** MCI0 Card detect pin definition. (PE2) */
#define BOARD_MCI0_PIN_CD       {PIO_PE2, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP}
/** MCI0 power control. */
#define BOARD_MCI0_PIN_POWER    {PIO_PE4, PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_PULLUP}

/** MCI1 Card detect pin definition. (PE3) */
#define BOARD_MCI1_PIN_CD       {PIO_PE3, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP}
/** MCI1 power control: none, always powered on */
//#define BOARD_MCI1_PIN_POWER    {PIO_PE15, PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_PULLUP}

/** Display width in pixels. */
#define BOARD_LCD_WIDTH             480
/** Display height in pixels. */
#define BOARD_LCD_HEIGHT            272

/** LED #0 pin definition (LED_BLUE). */
#define PIN_LED_0   {(PIO_PE15), PIOE, ID_PIOE, PIO_OUTPUT_1, PIO_DEFAULT}
/** LED #1 pin definition (LED_RED). */
#define PIN_LED_1   {(PIO_PD30), PIOD, ID_PIOD, PIO_OUTPUT_0, PIO_DEFAULT}

/** List of all LEDs definitions. */
#define PINS_LEDS   {PIN_LED_0, PIN_LED_1}

/** BLUE LED index definition. */
#define LED_BLUE      0
/** RED LED index definition. */
#define LED_RED       1

/** Push button #1 definition. Attributes = pull-up + debounce + interrupt on rising edge. */
#define PIN_PUSHBUTTON_1    {PIO_PE8, PIOE, ID_PIOE, PIO_INPUT, PIO_PULLUP | PIO_DEBOUNCE | PIO_IT_FALL_EDGE}

/** List of all push button definitions. */
#define PINS_PUSHBUTTONS    {PIN_PUSHBUTTON_1}

/** Push button #1 index. */
#define PUSHBUTTON_BP1   0

/** LCD image's scale */
#define EXAMPLE_LCD_SCALE   1

/** index of the first PWM channel used to light the LED*/
#define EXAMPLE_PWM_CHANNEL_INDEX0  0
/** index of the second PWM channel used to light the LED*/
#define EXAMPLE_PWM_CHANNEL_INDEX1  2
/** Pins of the first PWM channel used to light the LED*/
#define EXAMPLE_PWM_CHANNEL_PINS0   {PIO_PB26C_PWMH0,  PIOB, ID_PIOB, PIO_PERIPH_C, PIO_DEFAULT}
/** Pins of the second PWM channel used to light the LED*/
#define EXAMPLE_PWM_CHANNEL_PINS1   {PIO_PC0B_PWMH2,   PIOC, ID_PIOE, PIO_PERIPH_B, PIO_DEFAULT}

/** pin for SPI CS signal */
#define EXAMPLE_SPI_SLAVE_CS_PIN    PIN_SPI1_NPCS0
/** SPI CS index */
#define EXAMPLE_SPI_SLAVE_CS_IDX    0

/** Eeprom Pins definition */
#define EXAMPLE_TWI_SLAVE_PINS  PINS_TWI2
/** TWI peripheral ID for eeprom device*/
#define EXAMPLE_TWI_SLAVE_ID    ID_TWI2
/** TWI base address for eeprom device */
#define EXAMPLE_TWI_SLAVE_BASE  TWI2

/** SD card Power control pin instance */
#define EXAMPLE_MCI_POWER_PINS  BOARD_MCI0_PIN_POWER

#endif				/* _BOARD_SAMA5D4_XPLAINED_HEADER_ */
