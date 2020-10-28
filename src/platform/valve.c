#include "stm32f4xx_hal.h"
#include <platform/valve.h>

void open_inspiratory_valve() {
    // TODO - replace with a proper implementation, this is for testing only
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, SET);
}

void close_inspiratory_valve() {
    // TODO - replace with a proper implementation, this is for testing only
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, RESET);
}