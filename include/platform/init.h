/**
 * init.h 
 * 
 * Definitions of hardware initialization routines for the 
 * STM32F401RE microprocessor.
 */

#ifndef INC_PLATFORM_INIT_H_
#define INC_PLATFORM_INIT_H_

/**
 * Initialize the general purpose input/output ports
 * of the microprocessor. When this function completes
 * all of the required GPIO for the platform has been
 * initialized.
 */
void init_valve_gpio(void);
void init_gpio_clk();

void init_alarm_led();
void init_alarm_buzzer();
void init_alarm(void);

/**
 * Initialize the I2C peripheral
 * of the microprocessor. When this function completes
 * all of the the I2C bus for the platform has been
 * initialized.
 */
void init_i2c(void);
/**
 * Initialize an ADC (1) peripheral
 * of the microprocessor. When this function completes
 * an ADC for the platform has been initialized.
 */
void init_adc1(void);
/**
 * Initialize the uart peripheral
 * of the microprocessor. When this function completes
 * the uart (used for serial monitoring during build and 
 * debug stages) for the platform has been initialized.
 */
void init_uart(void);

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void);


#endif /* INC_PLATFORM_INIT_H_ */
