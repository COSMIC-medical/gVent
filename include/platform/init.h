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
void  init_gpio(void);

#endif /* INC_PLATFORM_INIT_H_ */
