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

// firmware-set i2c addresses for the 16x2 LCD  display
#define LCD_ADDR            0x27    

#endif /* INC_PLATFORM_CONFIGURATION_PRIVATE_H_ */



