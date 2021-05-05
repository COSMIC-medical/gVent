#include "stm32f4xx_hal.h"
#include "platform/valve.h"
#include "platform/configuration_private.h"

void open_inspiratory_valve() {
    HAL_GPIO_WritePin(INSP_VALVE_PORT, INSP_VALVE_PIN, SET);
}

void open_expiratory_valve() {
    HAL_GPIO_WritePin(EXP_VALVE_PORT, EXP_VALVE_PIN, SET);
}

void open_tank_valve() {
    HAL_GPIO_WritePin(TANK_VALVE_PORT, TANK_VALVE_PIN, SET);
}

void close_inspiratory_valve() {
    HAL_GPIO_WritePin(INSP_VALVE_PORT, INSP_VALVE_PIN, RESET);
}

void close_expiratory_valve() {
    HAL_GPIO_WritePin(EXP_VALVE_PORT, EXP_VALVE_PIN, RESET);
}

void close_tank_valve() {
    HAL_GPIO_WritePin(TANK_VALVE_PORT, TANK_VALVE_PIN, RESET);
}

