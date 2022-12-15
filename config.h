// Copyright 2022 HriyKun (@HriyKun)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

// #define CH_CFG_ST_RESOLUTION 16

/* Layer states */
#define LAYER_STATE_8BIT

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1D81
#define PRODUCT_ID      0x002A
#define DEVICE_VER      0x0001
#define MANUFACTURER    HiryKun
#define PRODUCT         RHODES 75
#define USB_POLLING_INTERVAL_MS 1

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 15

// ROWS: Top to bottom, COLS: Left to right
#define MATRIX_ROW_PINS { B5, B4, B3, A15, A2, A1 }
#define MATRIX_COL_PINS { A8, B15, B14, B13, B12, B11, B10, B1, B0, A7, A6, A5, A4, A3, A0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* RGB lights */
#define RGB_DI_PIN B8
#define DRIVER_LED_TOTAL 94
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Encoders */
#define ENCODERS_PAD_A { A10 }
#define ENCODERS_PAD_B { A9 }
#define ENCODER_RESOLUTION 4

/*OLED*/
#define I2C_DRIVER I2CD1
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define OLED_BRIGHTNESS 255
#define OLED_TIMEOUT 80000
#define OLED_FADE_OUT
#define OLED_FADE_OUT_INTERVAL 5
#define OLED_SCROLL_TIMEOUT 40000
// #define OLED_UPDATE_INTERVAL 20

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT