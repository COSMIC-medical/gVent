/*
 * platform.h
 *
 * private to the platform
 *
 */

#ifndef INC_PLATFORM_SCHEDULER_PRIVATE_H_
#define INC_PLATFORM_SCHEDULER_PRIVATE_H_

#include "stm32f4xx_hal.h"

/**
 * Maximum number of application level tasks supported by the
 * scheduler.
 */
#define MAX_TASKS 10

typedef enum {
    STATUS_OK = 0x00,
    STATUS_ERR = 0xFF
} status_t;

/**
 * Definition of a task callback function. Used by
 * applications to define the main "worker" function
 * for each task.
 *
 * The task function takes zero arguments and does
 * not return any values.
 */
typedef void (*task_func)();

/**
 * Definition of an application level task.
 */
typedef struct Task {

	// public definitions:

	/**
	 * The name of the application task (for human reading purposes only).
	 */
	const char * name;

	/**
	 * Callback function invoked for the task. Invoked each time the
	 * task is scheduled/run the by the platform's scheduler.
	 */
	task_func function;

	/**
	 * Time between invocations of the task in milliseconds
	 */
	uint32_t period;

	/**
	 * Delay first task invocation by this number of milliseconds
	 */
	uint32_t delay;

	/**
	 * The expected (maximum) duration of the task in milliseconds.
	 *
	 * After this duration an error will be raised by the platform if the
	 * task has not terminated.
	 */
	uint32_t duration;

	// private definitions (used/modified by scheduler):

	/**
	 * Last time (value of the ticker) that the task ran.
	 */
	uint32_t __last;

	/**
	 * Indicates if the task has been run at least once
	 */
	uint32_t __runs;

} task_t;


/**
 * Wrapper around hardware elements used by the platform.
 */
typedef struct PlatformConfiguration{

	/**
	 * Timer used by the platform's scheduler to measure time
	 * since the last time an application task was executed.
	 *
	 * Has the following requirements:
	 * 	- Must be a 32 bit timer with maximum value of 2^32 - 1.
     *  - Must be configured to increment/tick once per microsecond.
     *  - Must be configured in polling mode (no interrupts).
	 */
	TIM_HandleTypeDef * ticker;

	/**
	 * Timer used to ensure that each application task does not overrun
	 * its specified duration (task.duration).
	 *
	 * Has the following requirements:
	 *  - Maximum value of timer must be sufficient to accommodate longest
	 *    task duration (in microseconds).
	 *  - Must be configured to increment/tick once per microsecond.
	 *  - Must be configured in interrupt mode with the corresponding
	 *    service routine implementation provided in platform/platform.c.
	 */
	TIM_HandleTypeDef * watcher;

} platform_config_t;

/**
 * Initialize the platform with references to hardware elements.
 *
 * This function should be called first as part of booting the
 * platform.
 *
 * @param config - hardware configuration to be used by the platform.
 *
 * @return STATUS_OK if initialized successfully, STATUS_ERR otherwise.
 */
status_t init_platform(platform_config_t * config);

/**
 * Run the platform. Kicks of the scheduler and begins running the registered
 * application tasks based on their scheduling parameters.
 *
 * This function should never return.
 */
void run_platform();


#endif /* INC_PLATFORM_SCHEDULER_PRIVATE_H_ */
