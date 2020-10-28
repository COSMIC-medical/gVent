/*
 * application.c
 *
 */

#include <platform/scheduler.h>
#include <application/application.h>
#include <application/dss.h>

void task_1();
void task_2();
void task_3();

void init_application() {

	status_t reg_suc = STATUS_OK;

	/*
	 * Register new tasks to the time-triggered scheduler
	 * here and record the status result.
	 * 
	 * See platform/scheduler.h for details of task registration.
	 */
	// reg_suc |= register_task("my task name", task_function, 50, 0, 5);

	if (reg_suc == STATUS_ERR) {
		dss();
	}
}
