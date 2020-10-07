/*
 * configuration_private.h
 *
 * This file contains mappings of hardware pins/addresses
 * to specific devices used by the gVent system.
 *
 * Should map, for example, the pins controlling a valve
 * to a constant like INSP_VALVE_OPEN.
 *
 *  Created on: Sep 25, 2020
 *      Author: sdiemert
 */

#ifndef INC_PLATFORM_CONFIGURATION_PRIVATE_H_
#define INC_PLATFORM_CONFIGURATION_PRIVATE_H_

#include "stm32f4xx_hal.h"

#define GPIO_PERIPHERAL GPIOA
#define ALARM_LED_PIN GPIO_PIN_5

#endif /* INC_PLATFORM_CONFIGURATION_PRIVATE_H_ */
