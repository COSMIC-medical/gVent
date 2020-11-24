/*
 * display.h
 *
 * Functions to interact with the LCD display via I2C.
 */

#ifndef SRC_PLATFORM_DISPLAY_H_
#define SRC_PLATFORM_DISPLAY_H_

#include "platform/common.h"

void lcd_send_cmd (char cmd);

void lcd_send_data (char data);

void lcd_init (void);

void lcd_send_string (char *str);


#endif /* SRC_PLATFORM_DISPLAY_H_ */