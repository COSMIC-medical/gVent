#include "platform/init.h"
#include "platform/configuration_private.h"
#include "application/dss.h"
#include "stm32f4xx_hal.h"

void init_gpio_clk(GPIO_TypeDef * port) 
{
  if (port == GPIOA) {
    __HAL_RCC_GPIOA_CLK_ENABLE();
  } else if (port == GPIOB) {
    __HAL_RCC_GPIOB_CLK_ENABLE();
  } else if (port == GPIOC) {
    __HAL_RCC_GPIOC_CLK_ENABLE();
  }
}

void init_valve_gpio(void)
{

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

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
void init_uart()
{
  // serial1 = {0};
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
void init_i2c()
{
  // i2c1_bus = {0};
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

void init_status_gpio(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  // GPIO port clock enable 
  init_gpio_clk(STATUS_LED_PORT);

  // Setup status pin
  HAL_GPIO_WritePin(STATUS_LED_PORT, STATUS_LED_PIN, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = STATUS_LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(STATUS_LED_PORT, &GPIO_InitStruct);

}

/**
 * Initialize the alarm buzzer.
 * 
 * The alarm buzzer is driven by a Pulse-Width Modulation (PWM)
 * signal generated by a timer peripheral. This timer must be
 * configured to count at the desired frequency and then the 
 * compare and capture channel must be set to match the desired
 * pulse width. 
 * 
 * Note that timer channels on the STM32F4 are mapped directly
 * to alternative functions of GPIO pins. E.g., TIM3.CH2 -> PC7.
 * This requires that the GPIO be configured in an "alternative
 * function" (AF) mode.
 */ 
void init_alarm_buzzer()
{

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  // STEP 0: Compute the timer values
  // -----------------------------

  /*
   * The STM32F401RE has a 84 MHz clock. For convience,
   * we will divide this down into a 1 MHz clock using
   * the pre-scaler for the timer.
   */
  uint32_t prescalar = 84;

  /*
   * We want the timer period to equal the specified ALARM_BUZZ_FREQ.
   * 
   * Suppose ALARM_BUZZ_FREQ = 1000. We are using a 1 MHz (scaled) 
   * timer clock. Then we can compute the period as:
   * 
   *    10^3 Hz = 10^6 Hz / period 
   * 
   * So, we need a timer period of 1000 ticks. This generalizes to:
   * 
   *    period = 10^6 Hz / ALARM_BUZZ_FREQ
   */
  uint32_t period = ((84000000 / (prescalar))/ ALARM_BUZZ_FREQ) - 1;

  /*
   * For the buzzer we want a nice even square wave, so we use a 50%
   * duty cycle for the PWM signal. Obtain this as half of the period.
   */
  uint32_t duty = period / 2;

  // STEP 1: Initialize the timer.
  // -----------------------------

  /*
   * When setting the timer's prescalar and period, there
   * is a convention where you must subtract 1 from the desired
   * values. This is because the internal hardware of these
   * peripherals count up from zero. So to get a period of N
   * timer ticks, you must actually load N-1 into the timer's
   * configuration regstier.
   */

  alarm_timer.Instance = ALARM_BUZZ_TIM;
  alarm_timer.Init.Prescaler = prescalar - 1;
  alarm_timer.Init.CounterMode = TIM_COUNTERMODE_UP;
  alarm_timer.Init.Period = period - 1;
  alarm_timer.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  alarm_timer.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&alarm_timer) != HAL_OK) {
    dss();
  }

  // STEP 2: Set clock source for timer to internal clock (84MHz)
  // -----------------------------
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&alarm_timer, &sClockSourceConfig) != HAL_OK) {
    dss();
  }

  // STEP 3: Initialize timer in PWM mode.
  // -----------------------------
  if (HAL_TIM_PWM_Init(&alarm_timer) != HAL_OK) {
    dss();
  }

  // STEP 4: We don't require clock syncrohnization.
  // -----------------------------
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&alarm_timer, &sMasterConfig) != HAL_OK) {
    dss();
  }

  // STEP 5: Initialize channel in PWM mode for timer.
  // -----------------------------
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = duty - 1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&alarm_timer, &sConfigOC, ALARM_BUZZ_CHL) != HAL_OK) {
    dss();
  }

  // STEP 6: Initialize GPIO pin in alternative function mode for PWM
  // -----------------------------
  init_gpio_clk(ALARM_BUZZ_PORT);
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  GPIO_InitStruct.Pin = ALARM_BUZZ_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = ALARM_BUZZ_AF2;
  HAL_GPIO_Init(ALARM_BUZZ_PORT, &GPIO_InitStruct);

}

/**
 * Initialize the LED used for the alarm.
 */
void init_alarm_led()
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  init_gpio_clk(ALARM_LED_PORT);

  HAL_GPIO_WritePin(ALARM_LED_PORT, ALARM_LED_PIN, GPIO_PIN_RESET);
  GPIO_InitStruct.Pin = ALARM_LED_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(ALARM_LED_PORT, &GPIO_InitStruct);

}

void init_alarm()
{
  init_alarm_led();
  init_alarm_buzzer();
}
