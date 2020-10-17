/*
 * application.c
 *
 *  Created on: Sep. 22, 2020
 *      Author: sdiemert
 */

#include <platform/scheduler.h>
#include <platform/pin.h>
#include <application/application.h>

void task_1();
void task_2();
void task_3();

void init_application() {

	status_t reg_suc = STATUS_OK;
	reg_suc |= register_task("task 1", task_1, 50, 0, 5);
	reg_suc |= register_task("task 2", task_2, 100, 10, 5);
	reg_suc |= register_task("task 3", task_3, 50, 45, 5);

	if (reg_suc == STATUS_ERR) {
		dss();
	}
}

void dss() {
	while (1) {
		// pin 13 is connected to the green LED 3 on the nucleo-64 STM32F4 board.
		pin13_up();
	}
}

void task_1() {
	pin12_up();

	wait(1);

	pin12_down();
}

void task_2() {
	pin11_up();
	wait(1);
	pin11_down();
}

void task_3() {
	pin10_up();
	wait(1);
	pin10_down();
}
