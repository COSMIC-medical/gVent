/**
 * init.h 
 * 
 * Definitions of hardware initialization routines for the 
 * STM32F401RE microprocessor.
 */

#ifndef INC_PLATFORM_INIT_H_
#define INC_PLATFORM_INIT_H_

/**
 * Initialize general purpose output port of the 
 * microprocessor for the purpose of indicating the
 * system status. 
 * 
 * The status is indicated on the LED on the Nucleo
 * board.
 */
void init_status_gpio(void);

/**
 * Initialize the general purpose input/output ports
 * of the microprocessor for the purpose of actuating
 * valves. 
 * 
 * When this function completes all of the hardware
 * peripherals for the valve control have been initialized.
 */
void init_valve_gpio(void);

/**
 * Initialize the hardware peripherals used to actuate
 * the alarms. Includes setting up the alarm LED and
 * also setting up the buzzer output in PWM mode.
 * 
 * When this function completes the GPIO for the LED
 * is setup.
 * 
 * When the this function completes a timer and GPIO 
 * are setup for the alarm buzzer.
 */

/**
 * Initialize the I2C peripheral
 * of the microprocessor. When this function completes
 * the I2C bus for the platform has been initialized.
 */
void init_i2c(void);

/**
 * Initialize the uart peripheral
 * of the microprocessor. When this function completes
 * the uart (used for serial monitoring during build and 
 * debug stages) for the platform has been initialized.
 */
void init_uart(void);

void init_alarm(void);

#endif /* INC_PLATFORM_INIT_H_ */
