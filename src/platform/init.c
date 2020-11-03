#include <platform/init.h>
#include <platform/configuration_private.h>
#include "stm32f4xx_hal.h"

void init_gpio(void) {

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Set default output level and configure each pin */

  // inspratory valve
  HAL_GPIO_WritePin(INSP_VALVE_PORT, INSP_VALVE_PIN, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = INSP_VALVE_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(INSP_VALVE_PORT, &GPIO_InitStruct);

  // expiratory valve
  HAL_GPIO_WritePin(EXP_VALVE_PORT, EXP_VALVE_PIN, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = EXP_VALVE_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(EXP_VALVE_PORT, &GPIO_InitStruct);

  // tank valve
  HAL_GPIO_WritePin(TANK_VALVE_PORT, TANK_VALVE_PIN, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = TANK_VALVE_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(TANK_VALVE_PORT, &GPIO_InitStruct);

}