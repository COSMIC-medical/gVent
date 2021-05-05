/*
 * system_info.c
 *
 */

#include "stm32f4xx_hal.h"

int get_current_time(){
  return HAL_GetTick();
}
