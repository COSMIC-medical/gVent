/*
 * sensor_stub.c
 *
 * Stub for the function get_inspiratory_pressure() and get_expiratory_pressure()
 */

#include <stdlib.h>
#include <string.h>
#include "platform/common.h"


static uint32_t* ins_pressure_to_return;
static status_t* ins_status_to_return;
static uint32_t* exp_pressure_to_return;
static status_t* exp_status_to_return;
static int ins_current_call = 0;
static int exp_current_call = 0;


void set_inspiratory_pressure(uint32_t* values, status_t* status) {
	ins_pressure_to_return = values;
	ins_status_to_return = status;
	ins_current_call = 0;
}

status_t get_inspiratory_pressure(uint32_t *insp_pressure) {
	ins_current_call++;
	*insp_pressure = ins_pressure_to_return[ins_current_call-1];
	return ins_status_to_return[ins_current_call - 1];
}

void set_expiratory_pressure(uint32_t* values, status_t* status) {
	exp_pressure_to_return = values;
	exp_status_to_return = status;
	exp_current_call = 0;
}

status_t get_expiratory_pressure(uint32_t *exp_pressure) {
	exp_current_call++;
	*exp_pressure = exp_pressure_to_return[exp_current_call-1];
	return exp_status_to_return[exp_current_call - 1];
}