/*
 * application.c
 *
 */


#include <platform/scheduler.h>
#include <application/application.h>
#include <application/dss.h>
#include <application/tasks/valve_demo.h>
#include <application/tasks/sensor_demo.h>
#include "application/tasks/alarm_demo.h"

void init_application() {

	status_t reg_suc = STATUS_OK;

	/*
	 * Register new tasks to the time-triggered scheduler
	 * here and record the status result.
	 * 
	 * See platform/scheduler.h for details of task registration.
	 */

	/*
	 * The valve demo tasks runs every 50 ms starting
	 * at offset 0 ms. If the tasks runs longer than 5 ms
	 * then the scheduler intervenes.
	 */ 
	reg_suc |= register_task("valve_demo", task_valve_demo, 50, 0, 5);

	/*

	 * The sensor demo tasks runs every 50 ms starting
	 * at offset 5 ms. If the tasks runs longer than 10 ms
	 * then the scheduler intervenes.
	 */ 
	reg_suc |= register_task("sensor_demo", task_sensor_demo, 50, 5, 10);

	/* 
	 * The alarm demo task runs every 50 ms starting
	 * at offset 10 ms. if the task runs longer than 5 ms
	 * then teh scheduler intervenes.
	 */
	reg_suc |= register_task("alarm_demo", task_alarm_demo, 50, 10, 5);

	if (reg_suc == STATUS_ERR) {
		dss();
	}
}

