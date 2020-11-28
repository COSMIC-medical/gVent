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
 * Computes the circuit pressure
 * SRS-0002
 */
uint32_t get_circuit_pressure();

/*
 * Starts an inspiration at the beginning of each breath cycle
 * SRS-0010
 */
void start_inspiration();

#endif /* INC_PLATFORM_VENTILATION_H_ */
