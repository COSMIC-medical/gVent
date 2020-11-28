/*
 * sensor_stub.c
 *
 * Stub for the function get_inspiratory_pressure() and get_expiratory_pressure()
 */

#include <stddef.h>

void set_inspiratory_pressure(int* values, status_t* status);
status_t get_inspiratory_pressure(uint32_t *insp_pressure);
void set_expiratory_pressure(int* values, status_t* status);
status_t get_expiratory_pressure(uint32_t *exp_pressure);

