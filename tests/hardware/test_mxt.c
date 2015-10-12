/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2015, Atmel Corporation
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

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "chip.h"

#include "peripherals/pio.h"
#include "peripherals/pmc.h"
#include "peripherals/flexcom.h"
#include "peripherals/twi.h"
#include "peripherals/twid.h"

#include "utils/timer.h"
#include "utils/widget.h"
#include "mxt_device.h"

#include "trace.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>

/*----------------------------------------------------------------------------
 *        Types
 *----------------------------------------------------------------------------*/

/** Address of the mXT336S on TWI bus */
#define MXT_TWI_ADDRESS 	0x4A
//#define MXT_TWI_ADDRESS 	0x4B

/** Background color of display */
#define DISPLAY_COLOR        COLOR_BLACK

/** Minimum size of touch squares to draw */
#define MIN_SQUARE_SIZE      20

/** Maximum number of touches to track */
#define MAX_TOUCHES          8

/** Define to enable resizing of the touch square based on the touch size */
#define ENABLE_TOUCH_SIZE_DISPLAY

/** Define to enable display of touch coordinates with each square */
#define ENABLE_COORDINATE_DISPLAY

/** Struct for touch visualization data */
struct finger {
	bool enable;   			/**< Enable drawing */
	uint8_t size;  			/**< Size of the detected touch */
	struct _point coord; 	/**< coordinate on display */
};

// TWI pin for MXT device */
const struct _pin mxt_pins[] = PINS_TWI1_IOS2;
/* CGH pin for MXT device */
//const struct _pin chg_pin[] = PIN_MXT_IRQ;


struct mxt_device device = {
	.twid = NULL,
	.chip_id = 0x00,
	.firmware_version = 0x00,
	.info_object = NULL,
	.object_list = NULL,
	.report_id_map = NULL,
	.multitouch_report_offset = 0x00,
	.chg_pin = PIN_MXT_IRQ,
};

struct mxt_device* pdevice = &device;

/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Draw square around a finger
 *
 * This function draws an unfilled square around the specified finger.
 *
 * \param draw_finger Pointer to finger struct
 * \param color Color to draw with
 */
static void draw_finger_square(const struct finger *draw_finger, const color_t color)
{
	uint8_t square_size = MIN_SQUARE_SIZE;

#ifdef ENABLE_TOUCH_SIZE_DISPLAY
	/* Increase the size of the touch square based on the touch size */
	square_size += draw_finger->size;
#endif

	/* Calculate upper-left X/Y coordinates for the touch bounding box */
	struct _point upper ;

	upper.x = (draw_finger->coord.x - (square_size / 2));
	upper.y = (draw_finger->coord.y - (square_size / 2));

	if( upper.x >= 0x80000000  )
		upper.x = 1;
	if( upper.x >= BOARD_LCD_WIDTH - square_size )
		upper.x = BOARD_LCD_WIDTH - square_size;
	if( upper.y >= 0x80000000 )
		upper.y = 1;
	if( upper.y >= BOARD_LCD_HEIGHT - square_size )
		upper.y = BOARD_LCD_HEIGHT - square_size;

#ifdef ENABLE_COORDINATE_DISPLAY
	char str_buffer[10];
	uint32_t str_width, str_height;

	/* Print the formatted touch coordinates into the temporary buffer */
	sprintf(str_buffer, "%03d, %03d", draw_finger->coord.x, draw_finger->coord.y);

	/* Calculate the bounding box of the coordinate text on the display */
	lcdd_get_string_size(str_buffer, &str_width, &str_height);

	/* Write touch coordinates to the display above the finger touch box */
	struct _point pt = {
		.x = BOARD_LCD_WIDTH - 120,
		.y = BOARD_LCD_HEIGHT - 20,
	};
	lcdd_draw_filled_rectangle(pt.x, pt.y, pt.x+str_width, pt.y+str_height, COLOR_WHITE);
	lcdd_draw_string(pt.x, pt.y, str_buffer, color);
#endif

	if ( color != DISPLAY_COLOR )
		/* Draw a box around the touch point */
		lcdd_draw_rectangle (upper.x, upper.y, square_size, square_size, color);
	else
		lcdd_draw_rounded_rect (upper.x, upper.y, square_size, square_size, square_size/3, color);
}

/**
 * \brief Compute display coordinates for touch
 *
 * This function computes the display coordinates for a given touch event,
 * and stores it in the specified X- and Y-coordinate containers.
 *
 * \param touch_event Pointer to touch event
 * \param finger_data Pointer to finger struct
 */
static void get_finger_display_coordinates(const struct mxt_touch_event *touch_event, struct finger *finger_data)
{
	/* Display X-coordinate: rescale from 4k touch X-coordinate to the display's width */
	finger_data->coord.x = ((uint32_t)(BOARD_LCD_WIDTH * touch_event->x) / 4096);
	/* Display Y-coordinate: rescale from 4k touch Y-coordinate to the display's height,
	and flip to get the right direction */
	finger_data->coord.y = ((uint32_t)(BOARD_LCD_HEIGHT * touch_event->y) / 4096);
	/* Save the scaled size of the touch */
	finger_data->size = (touch_event->size * 4);
}

/**
 * \brief Set maXTouch configuration
 *
 * This function writes a set of predefined, optimal maXTouch configuration data
 * to the mXT143E Xplained.
 *
 * \param device Pointer to mxt_device struct
 */
static enum status_code mxt_init(struct mxt_device *device)
{
	uint16_t add ;
	uint8_t buf[128];

	enum status_code status = STATUS_OK;
	UNUSED(status);

#ifdef NEED_TO_PROGRAM
	/* T8 configuration object data */
	uint8_t t8_object[] = {
		0x10, 0x05, 0x0a, 0x14, 0x64, 0x00, 0x05,
		0x0a, 0x00, 0x00,
	};

	/* T9 configuration object data */
	uint8_t t9_object[] = {
		0x8f, 0x00, 0x00, 0x0d, 0x0b, 0x00, 0x21,
		0x3c, 0x0f, 0x00, 0x32, 0x01, 0x01, 0x00,
		0x08, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x1c, 0x1c, 0x37, 0x37, 0x8f, 0x50,
		0xcf, 0x6e, 0x00, 0x02, 0x2f, 0x2c, 0x00
	};

	/* T48 configuration object data */
	uint8_t t48_object[] = {
		0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00
	};
#endif

	/* Initialize the maXTouch device */
	status = mxt_init_device(device);
	if (status != STATUS_OK) return status ;

	/* Issue soft reset of maXTouch device by writing a non-zero value to
	 * the reset register */
	add = mxt_get_object_address(device, MXT_GEN_COMMANDPROCESSOR_T6, 0);
	mxt_write_config_reg(device, add + MXT_GEN_COMMANDPROCESSOR_RESET, 0x01);

	/* Wait for the reset of the device to complete */
	timer_wait(MXT_RESET_TIME);

	add = mxt_get_object_address(device, MXT_TOUCH_MULTITOUCHSCREEN_T9, 0);
	mxt_read_config_object(device, add, &buf);

#ifdef NEED_TO_PROGRAM
	/* Write data to configuration registers in T7 configuration object */
	add = mxt_get_object_address(device, MXT_GEN_POWERCONFIG_T7, 0);
	mxt_write_config_reg(device, add + 0, 0xFF);
	add = mxt_get_object_address(device, MXT_GEN_POWERCONFIG_T7, 0);
	mxt_write_config_reg(device, add + 1, 0xFF);
	add = mxt_get_object_address(device, MXT_GEN_POWERCONFIG_T7, 0);
	mxt_write_config_reg(device, add + 2, 0x32);


	/* Write predefined configuration data to configuration objects */
	add = mxt_get_object_address(device, MXT_GEN_ACQUISITIONCONFIG_T8, 0);
	mxt_write_config_object(device, add , &t8_object);
	add = mxt_get_object_address(device, MXT_TOUCH_MULTITOUCHSCREEN_T9, 0);
	mxt_write_config_object(device, add, &t9_object);
	add = mxt_get_object_address(device, MXT_PROCG_TOUCHSUPPRESSION_T48, 0);
	if (add)
		mxt_write_config_object(device, add, &t48_object);

	/* Issue recalibration command to maXTouch device by writing a non-zero
	 * value to the calibrate register */
	add = mxt_get_object_address(device, MXT_GEN_COMMANDPROCESSOR_T6, 0);
	mxt_write_config_reg(device,  add + MXT_GEN_COMMANDPROCESSOR_CALIBRATE, 0x01);
#endif
	return STATUS_OK;
}

/**
 * \brief Handle maXTouch messages
 *
 * This function handles the maXTouch messages, triggering the drawing of
 * squares around new or moved touches, and removing the squares around
 * released touches.
 *
 * \param device Pointer to mxt_device struct
 */
void mxt_handler (uint32_t mask, uint32_t status, void* user_arg)
{
	static struct finger fingers[MAX_TOUCHES];
	static const color_t finger_colors[MAX_TOUCHES] = {
		COLOR_RED, COLOR_GREEN, COLOR_BLUE, COLOR_CYAN,
		COLOR_YELLOW, COLOR_MAGENTA, COLOR_WHITE, COLOR_GRAY,
	};
	struct mxt_touch_event touch_event;
	struct finger *curr_finger;
	uint8_t finger_index;

	(void)user_arg;

	do{
		/* Get the first touch event in queue */
		if (mxt_read_touch_event(&device, &touch_event) != STATUS_OK) {
			continue;
		}

		/* Discard non press, movement or release events */
		if (!(touch_event.status & (MXT_PRESS_EVENT | MXT_MOVE_EVENT | MXT_RELEASE_EVENT))) {
			continue;
		}

		/* Use the touch ID as finger index */
		finger_index = touch_event.id;

		/* Skip if touch ID is out of bounds */
		if (!(finger_index < MAX_TOUCHES)) {
			continue;
		}

		/* Get address of current finger info struct */
		curr_finger = &fingers[finger_index];

		/* If finger already registered (and thus drawn), clear it on the display */
		if (curr_finger->enable) {
			draw_finger_square(curr_finger, DISPLAY_COLOR);
		}

		/* Update finger info - finger is enabled unless it was released */
		curr_finger->enable = !(touch_event.status & MXT_RELEASE_EVENT);

		/* If the finger is now enabled, we need to update its position and redraw */
		if (curr_finger->enable) {
			/* Compute new display coordinates from touch coordinates */
			get_finger_display_coordinates(&touch_event, curr_finger);

			lcdd_select_canvas(LCDD_BASE);

			/* Draw updated representation on the display */
			draw_finger_square(curr_finger, finger_colors[finger_index]);
		}
	} while (!mxt_is_message_pending(&device)); /* Check if CHG pin low level */
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

enum status_code launch_mxt_device (void)
{
	enum status_code status = STATUS_OK;

	struct _twi_desc mxt_twid = {
		.addr = MXT_ADDR,
		.freq = MXT_FREQ,
		.slave_addr = MXT_TWI_ADDRESS,
		.transfert_mode = TWID_MODE_POLLING,
	};
	device.twid = &mxt_twid;

	/* TWI configuration */
	pio_configure(mxt_pins, ARRAY_SIZE(mxt_pins));
	twid_configure(device.twid);

	/* MXT basic init routines */
	status = mxt_init(&device);
	if (status != STATUS_OK) return status ;

	/* Init Pio CHG level IRQ */
	pio_configure(&device.chg_pin, 1);
	pio_configure_it(&device.chg_pin);
	pio_add_handler_to_group(device.chg_pin.group, device.chg_pin.mask, mxt_handler, NULL);
	pio_enable_it(&device.chg_pin);


	do { lcd_app_qtouch(); } while(1);

	return status;
}

