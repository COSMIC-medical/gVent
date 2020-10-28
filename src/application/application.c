/*
 * application.c
 *
 */

#include <platform/scheduler.h>
#include <platform/valve.h>
#include <application/application.h>
#include <application/dss.h>

void task_1();
void task_2();
void task_3();

void init_application() {

	status_t reg_suc = STATUS_OK;
	reg_suc |= register_task("task 1", task_1, 50, 0, 5);

	if (reg_suc == STATUS_ERR) {
		dss();
	}
}

void task_1() {
	open_inspiratory_valve();
	close_inspiratory_valve();
}
