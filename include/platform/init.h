/**
 * init.h 
 * 
 * Definitions of hardware initialization routines for the 
 * STM32F401RE microprocessor.
 */

#ifndef INC_PLATFORM_INIT_H_
#define INC_PLATFORM_INIT_H_

void init_status_gpio(void);

/**
 * Initialize the general purpose input/output ports
 * of the microprocessor for the purpose of actuating
 * valves. 
 * 
 * When this function completes all of the hardware
 * peripherals for the valve control has initialized.
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
 * is setup for the alarm buzzer.
 */
void init_alarm(void);

#endif /* INC_PLATFORM_INIT_H_ */
