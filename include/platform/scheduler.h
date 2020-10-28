/*
 * platform.h
 *
 */

#ifndef INC_PLATFORM_SCHEDULER_H_
#define INC_PLATFORM_SCHEDULER_H_

#include "stm32f4xx_hal.h"
#include <platform/scheduler_private.h>

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


#endif /* INC_PLATFORM_SCHEDULER_H_ */
