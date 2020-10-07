/*
 * alarm.c
 *
 */
#include <platform/alarm_private.h>
#include <platform/configuration_private.h>

void set_alarm_on(){
  // power on the alarm's led
  HAL_GPIO_WritePin(GPIO_PERIPHERAL, ALARM_LED_PIN, SET);
  // power on the buzzer if not alarm is not muted
}

void set_alarm_off(){
  //power off the alarm's led
  HAL_GPIO_WritePin(GPIO_PERIPHERAL, ALARM_LED_PIN, RESET);
  // power off the buzzer
}

void mute_alarm(){
  // power off the buzzer
}

void unmute_alarm(){
  //power on the buzzer if alarm is on
}


