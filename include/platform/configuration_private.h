/*
 * configuration_private.h
 *
 * This file contains mappings of hardware pins/addresses
 * to specific devices used by the gVent system.
 *
 * Should map, for example, the pins controlling a valve
 * to a constant like INSP_VALVE_OPEN.
 *
 */
#ifndef INC_PLATFORM_CONFIGURATION_PRIVATE_H_
#define INC_PLATFORM_CONFIGURATION_PRIVATE_H_
#include "stm32f4xx_hal.h"

#define STATUS_LED_PORT     GPIOA
#define STATUS_LED_PIN      GPIO_PIN_5

/************************************************
 * VALVE CONTROL DEFINITIONS
 ************************************************/
// GPIO PA6 maps to Pin D12 on the Nucleo-64 board.
#define INSP_VALVE_PORT     GPIOA
#define INSP_VALVE_PIN      GPIO_PIN_6
// Pin PA7 maps to Pin D11 on the Nucleo-64 board.
#define EXP_VALVE_PORT      GPIOA
#define EXP_VALVE_PIN       GPIO_PIN_7
// GPIO PB6 maps to Pin D10 on the Nucleo-64 board.
#define TANK_VALVE_PORT     GPIOB
#define TANK_VALVE_PIN      GPIO_PIN_6

/************************************************
 * ALARM CONTROL DEFINITIONS
 ************************************************/

// GPIO PA9 maps to Pin D8 on the Nucleo-64 board.
#define ALARM_LED_PORT      GPIOA
#define ALARM_LED_PIN       GPIO_PIN_9

// GPIO PC7 maps to Pin D9 (PWM) on the Nucleo-64 board.

// Note that timer channels directly map to alternative
// functions of GPIO pins. TIM3.ch2 maps to PC7 on the 
// STM32F401RE microprocessor.
#define ALARM_BUZZ_PORT     GPIOC
#define ALARM_BUZZ_PIN      GPIO_PIN_7
#define ALARM_BUZZ_TIM      TIM3
#define ALARM_BUZZ_CHL      TIM_CHANNEL_2
#define ALARM_BUZZ_AF2      GPIO_AF2_TIM3

// frequency of the alarm buzzer in Hz.
#define ALARM_BUZZ_FREQ     1000

// globally available handle for the alarm timer.
TIM_HandleTypeDef alarm_timer;

/************************************************
 * I2C CONTROL DEFINITIONS
 ************************************************/

// GPIO PB9 maps to Pin D14 (I2C1_SDA) on the Nucleo-64 board.
#define I2C_PORT            GPIOB
#define I2C_SDA_PIN         GPIO_PIN_9

// GPIO PB8 maps to Pin D15 (I2C1_SCL) on the Nucleo-64 board.
#define I2C_PORT            GPIOB
#define I2C_SCL_PIN         GPIO_PIN_8

// globally available handle for the i2c peripheral.
I2C_HandleTypeDef i2c1_bus;

// firmware-set i2c addresses for the FS6122 sensors 
#define INSPIRATORY_ADDR    0x1D << 1       // sensor 1
#define EXPIRATORY_ADDR     0x02 << 1       // sensor 2

/************************************************
 * LCD CONTROL DEFINITIONS
 ***********************************************/
// firmware-set i2c addresses for the 16x2 LCD  display
#define LCD_ADDR                0x27 // Change this according to specific LCD address (default is 0x27)
#define LCD_CMD_CLEAR           0x01 // Clear display
#define LCD_CMD_ENTRY_MODE      0x06 // Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
#define LCD_CMD_DISPLAY_CONTROL 0x08 // Display on/off control --> D=0,C=0, B=0  ---> display off
#define LCD_CMD_BLINKER         0x09 // Display on/off control --> D=0,C=0, B=1  ---> display off
#define LCD_CMD_CURSOR          0x0A // Display on/off control --> D=0,C=1, B=0  ---> display off
#define LCD_CMD_CURSOR_BLINKER  0x0B // Display on/off control --> D=0,C=1, B=1  ---> display off
#define LCD_CMD_DISPLAY         0x0C // Display on/off control --> D=1,C=0, B=0  ---> display ON
#define LCD_CMD_DISPLAY_CURSOR  0x0E // Display on/off control --> D=1,C=1, B=0  ---> display ON
#define LCD_CMD_DISPLAY_CURSOR_BLINKER  0x0F // Display on/off control --> D=1,C=1, B=1  ---> display ON

#define LCD_CMD_BIT_MODE        0x20 // 4bit mode
#define LCD_cmd3                0x28 // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
#define LCD_cmd1                0x30 // 

#endif /* INC_PLATFORM_CONFIGURATION_PRIVATE_H_ */



