/*
 * platform.c
 *
 */

#include <platform/scheduler_private.h>
#include <platform/scheduler.h>
#include <platform/system_status.h>
#include <application/dss.h>

// module level private variables
task_t tasks[MAX_TASKS];
uint32_t num_tasks = 0;
TIM_HandleTypeDef * ticker;
TIM_HandleTypeDef * watcher;

// module private functions
void scheduler_dispatch();
uint32_t check_task(uint32_t t);
uint32_t check_schedule();

status_t init_platform(platform_config_t * config) {

	// store module level variables from configuration
	ticker = config->ticker;
	watcher = config->watcher;

	// start timer
	HAL_TIM_Base_Start(ticker);

	// if nothing went wrong, return OK
	return STATUS_OK;
}

status_t register_task(const char * name,
		task_func func,
		uint32_t period,
		uint32_t delay,
		uint32_t duration){

	// confirm there is space to make the task
	if (num_tasks >= MAX_TASKS) {
		return STATUS_ERR;
	}

	// associate parameters with a task
	tasks[num_tasks].name = name;
	tasks[num_tasks].function = func;
	tasks[num_tasks].period = period * 1000;
	tasks[num_tasks].delay = delay * 1000;
	tasks[num_tasks].duration = duration * 1000;

	// set internal state variables
	tasks[num_tasks].__last = tasks[num_tasks].delay;
	tasks[num_tasks].__runs = 0;

	// confirm the provided task has valid parameters
	if (!check_task(num_tasks)) {
		// invalid task, return error
		return STATUS_ERR;
	}

	if (check_schedule()) {
		// task is valid, increment counter
		num_tasks++;
		return STATUS_OK;
	} else {
		return STATUS_ERR;
	}

}

/**
 * @return 1 if the schedule is valid, 0 otherwise.
 */
uint32_t check_schedule() {
	// TODO - implement schedule verification.
	return 1;

}

/**
 * @param t - index into the tasks array to check.
 *
 * @return 1 if the task parameters are valid, 0 otherwise.
 */
uint32_t check_task(uint32_t t) {
	// TODO - what other criteria are there for a valid task?
	return tasks[t].name != NULL
			&& tasks[t].function != NULL
			&& tasks[t].period > 0
			&& tasks[t].delay >= 0
			&& tasks[t].duration > 0;
}

void run_platform() {

	// start scheduler timer counting from zero (delays are referenced from zero)
	__HAL_TIM_SetCounter(ticker, 0);

	// indicate the platform has started running with the LED
	set_system_status_on();

	// infinitely call scheduling dispatch function
	while(1) {
		scheduler_dispatch();
	}

}

/**
 * The main worker function for the scheduler.
 *
 * Loops through the registered tasks and, if a task has
 * waited for at least its period microseconds, then invokes the task.
 *
 * Only invokes one task at a time.
 *
 * Once a task is invoked, does not schedule another until it is called again.
 */
void scheduler_dispatch() {

	// stop running watch timer
	HAL_TIM_Base_Stop_IT(watcher);

	// initialize local variables
	uint32_t prev = 0;
	uint32_t now = 0;
	uint32_t elapsed = 0;

	// loop over tasks
	for(uint32_t i = 0; i < num_tasks; i++) {

		__HAL_TIM_SET_COUNTER(watcher, tasks[i].duration);

		// use a temporary variable to save the task's last run time
		// this strategy helps reduce the latency between when we find a task
		// to run and when the task is actually run.
		prev = tasks[i].__last;

		// get the current time (microseconds)
		now =  __HAL_TIM_GET_COUNTER(ticker);

		// store the current time as if the task had run now (revert this later)
		tasks[i].__last = now;

		if (now >= prev) {
			// normal case, where elapsed time is positive
			elapsed = now - prev;
		} else if (tasks[i].__runs > 0 && now < prev) {

			// case where timer overflows

			// also need to check for special case where the
			// the task has not yet run once, but the delay
			// is non-zero and therefore bigger than the current
			// timer value (__runs > 0)

			elapsed = now + (UINT32_MAX - prev);
		}

		// check if the minimum period has elapsed
		if (elapsed >= tasks[i].period) {

			HAL_TIM_Base_Start_IT(watcher);

			// actually run the task
			tasks[i].function();

			// disable the timer
			HAL_TIM_Base_Stop_IT(watcher);

			// increment run counter
			tasks[i].__runs++;

			// done with this function
			return;

		} else {
			// nothing scheduled, restore last run time from temporary variable
			tasks[i].__last = prev;
		}
	}

}

/**
 * This is intentionally a light wrapper around the HAL delay
 * function. To be used with extreme care since it is a blocking
 * delay. Other tasks will not be able to proceed while this delay.
 */ 
void delay_ms(uint32_t ms) {
	HAL_Delay(ms);
}

/**
 * This function is called by the HAL when any timer interrupt is
 * is called. The handle to the timer that triggered the interrupt
 * is passed.
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {

	// ensure that the watcher timer is what triggered this interrupt
	// we are currently servicing.
	if (htim == watcher) {
		// since the watcher fired the interrupt, we know that the
		// currently running task has overrun its duration: go to
		// the DSS defined by the application.
		dss();
	}
}
