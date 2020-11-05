#include "stm32f4xx_hal.h"
#include <platform/alarm.h>
#include <platform/configuration_private.h>
#include <platform/common.h>

static alarm_status_t current_status = OFF;

alarm_status_t get_alarm_status() {
    return current_status;
}

status_t set_alarm_on() {
    HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, SET);
    if (HAL_TIM_PWM_Start(&alarm_timer, ALARM_BUZZ_CHL) != HAL_OK) {
        return STATUS_ERR;
    }
    current_status = ON;
    return STATUS_OK;
}

status_t set_alarm_off() {
    HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, RESET);
    if (HAL_TIM_PWM_Stop(&alarm_timer, ALARM_BUZZ_CHL) != STATUS_OK) {
        return STATUS_ERR;
    }
    current_status = OFF;
    return STATUS_OK;
}

status_t mute_alarm() {
    if (HAL_TIM_PWM_Stop(&alarm_timer, ALARM_BUZZ_CHL) != STATUS_OK) {
        return STATUS_ERR;
    }
    current_status = MUTED;
    return STATUS_OK;
}

status_t unmute_alarm() {
    if (HAL_TIM_PWM_Start(&alarm_timer, ALARM_BUZZ_CHL) != HAL_OK) {
        return STATUS_ERR;
    }
    current_status = ON;
    return STATUS_OK;
}