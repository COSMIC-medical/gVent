/*
 * platform.h
 *
 */

#ifndef INC_PLATFORM_SCHEDULER_H_
#define INC_PLATFORM_SCHEDULER_H_

#include "stm32f4xx_hal.h"
#include "platform/scheduler_private.h"

/**
 * Register a new task to the platform.
 *
 * This function does not start the task! It only registers it.
 * Tasks are started/run when run_platform() is called.
 *
 * @param name - human-readable name for the task.
 * @param func - the callback for the task.
 * @param period - duration in milliseconds between task invocations.
 * @param delay - offset for starting the task in milliseconds.
 * @param duration - maximum anticipated runtime of the task.
 *
 * @return STATUS_OK if registration was successful, STATUS_ERR otherwise.
 */
status_t register_task(const char * name,
		task_func func,
		uint32_t period,
		uint32_t delay,
		uint32_t duration);

/**
 * Delay the current execution by the specified number of
 * milliseconds. 
 * 
 * This is a busy/blocking delay. The scheduler will *not*
 * substitute/yeild control to the next task. To be used
 * with extreme care.
 * 
 * This function is implemented as a wrapper around the
 * STM32 HAL_Delay() function.
 * 
 * @param ms - number of milliseoncds to delay.
 */
void delay_ms(uint32_t ms);


#endif /* INC_PLATFORM_SCHEDULER_H_ */
