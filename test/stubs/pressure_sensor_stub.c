/*
 * pressure_sensor_stub.c
 *
 * Stub for the function get_inspiratory_pressure() and get_expiratory_pressure()
 */

#include <stdlib.h>
#include <string.h>


static int* ins_pressure_to_return;
static int* exp_pressure_to_return;
static int ins_current_call = 0;
static int exp_current_call = 0;


void set_inspiratory_pressure(int* values) {
	ins_pressure_to_return = values;
	ins_current_call = 0;
}

int get_inspiratory_pressure() {
	ins_current_call++;
	return ins_pressure_to_return[ins_current_call - 1];
}

void set_expiratory_pressure(int* values) {
	exp_pressure_to_return = values;
	exp_current_call = 0;
}

int get_expiratory_pressure() {
	exp_current_call++;
	return exp_pressure_to_return[exp_current_call - 1];
}