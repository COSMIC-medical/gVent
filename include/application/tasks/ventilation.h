/*
 * ventilation.h
 *
 * Main file for the ventilation task
 */

#ifndef INC_PLATFORM_VENTILATION_H_
#define INC_PLATFORM_VENTILATION_H_

#include "platform/common.h"
#define MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP 32 //todo replace this value by the real value
#define MIN_CIRCUIT_PRESSURE_FOR_OPENING_EXP_VALVE_CSP 8 //todo replace this value by the real value

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

/**
 * Ends inspiration and Start Expiration
 * 
 * Verify that the pressure is acceptable to start an expiration
 *   Ends the inspiration by closing the inspiratory valve
 *   Starts the expiration by opening the expiratory valve 
 * SRS-0015 and SRS-0020
 */
void start_expiration();

#endif /* INC_PLATFORM_VENTILATION_H_ */
