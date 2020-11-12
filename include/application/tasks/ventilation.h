/*
 * ventilation.h
 *
 * Main file for the ventilation task
 */

#ifndef INC_PLATFORM_VENTILATION_H_
#define INC_PLATFORM_VENTILATION_H_

#define MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP 32 //todo replace this value by the real value

/*
 * SLS-0055
 */
void ventilation();

/*
 * Gets the respiratory rate inputted by clinician
 * Step 1: Get clinician selected inspitory rate (SRS-0001) OR default inspiratory rate (SRS-0004)
 * Step 2: Calculate duration of a breath cycle in milliseconds
 * Step 3: Assign new inspiratory rate to breath_cycle_duration
 */
uint32_t calculate_breath_cycle_duration();

/*
 * Computes the circuit pressure
 * SRS-0002
 */
int get_circuit_pressure();

/*
 * Starts an inspiration at the beginning of each breath cycle
 * SRS-0010
 */
void start_inspiration();

#endif /* INC_PLATFORM_VENTILATION_H_ */
