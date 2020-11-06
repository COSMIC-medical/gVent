#include <platform/init.h>
#include <platform/configuration_private.h>
#include "stm32f4xx_hal.h"
void init_gpio_clk(GPIO_TypeDef * port) {
  if (port == GPIOA) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  } else if (port == GPIOB) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
  } else if (port == GPIOC) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
  }
}
void init_valve_gpio(void) {
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* GPIO Ports Clock Enable */
  init_gpio_clk(INSP_VALVE_PORT);
  init_gpio_clk(EXP_VALVE_PORT);
  init_gpio_clk(TANK_VALVE_PORT);
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

void init_alarm(void){
  TIM_HandleTypeDef alarm_timer = {0};
}

/**
  * @brief ADC1 Initialization Function
  * @param None
  * @retval None
  */
void init_adc1(void)
{
  ADC_ChannelConfTypeDef sConfig = {0};

  ADC_HandleTypeDef potentiometer_1 = {0};

  /* USER CODE BEGIN ADC1_Init 1 */

  /* USER CODE END ADC1_Init 1 */
  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  potentiometer_1.Instance = ADC1;
  potentiometer_1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  potentiometer_1.Init.Resolution = ADC_RESOLUTION_12B;
  potentiometer_1.Init.ScanConvMode = DISABLE;
  potentiometer_1.Init.ContinuousConvMode = DISABLE;
  potentiometer_1.Init.DiscontinuousConvMode = DISABLE;
  potentiometer_1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  potentiometer_1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  potentiometer_1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  potentiometer_1.Init.NbrOfConversion = 1;
  potentiometer_1.Init.DMAContinuousRequests = DISABLE;
  potentiometer_1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&potentiometer_1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_1;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&potentiometer_1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void init_uart(void)
{
  UART_HandleTypeDef serial1 = {0};

  serial1.Instance = USART2;
  serial1.Init.BaudRate = 115200;
  serial1.Init.WordLength = UART_WORDLENGTH_8B;
  serial1.Init.StopBits = UART_STOPBITS_1;
  serial1.Init.Parity = UART_PARITY_NONE;
  serial1.Init.Mode = UART_MODE_TX_RX;
  serial1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  serial1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&serial1) != HAL_OK)
  {
    Error_Handler();
  }

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void init_i2c(void){
  I2C_HandleTypeDef i2c1_bus = {0};
  i2c1_bus.Instance = I2C1;
  i2c1_bus.Init.ClockSpeed = 100000;
  i2c1_bus.Init.DutyCycle = I2C_DUTYCYCLE_2;
  i2c1_bus.Init.OwnAddress1 = 0;
  i2c1_bus.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  i2c1_bus.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  i2c1_bus.Init.OwnAddress2 = 0;
  i2c1_bus.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  i2c1_bus.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&i2c1_bus) != HAL_OK)
  {
    Error_Handler();
  }
}

