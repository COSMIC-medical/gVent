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

// GPIO PC7 maps to Pin D9 on the Nucleo-64 board.
#define ALARM_LED_PORT      GPIOC
#define ALARM_LED_PIN       GPIO_PIN_7

// GPIO PA9 maps to Pin D8 on the Nucleo-64 board.
#define ALARM_BUZZ_PORT     GPIOA
#define ALARM_BUZZ_PIN      GPIO_PIN_8

#endif /* INC_PLATFORM_CONFIGURATION_PRIVATE_H_ */
