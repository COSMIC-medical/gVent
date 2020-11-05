#include "stm32f4xx_hal.h"
#include <platform/common.h>
#include <platform/system_status.h>
#include <platform/configuration_private.h>

void set_system_status_on() {
    HAL_GPIO_WritePin(STATUS_LED_PORT, STATUS_LED_PIN, SET);
}

void set_system_status_off() {
    HAL_GPIO_WritePin(STATUS_LED_PORT, STATUS_LED_PIN, RESET);
}