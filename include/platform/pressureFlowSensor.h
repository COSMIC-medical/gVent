/*
 * pressure_flow_sensor.h
 *
 * This file contains the functions
 * for an application developer
 * to read the pressure and flow sensors
 *
 */

#ifndef INC_PLATFORM_PRESSURE_FLOW_SENSOR_H_
#define INC_PLATFORM_PRESSURE_FLOW_SENSOR_H_

/*
 * Reads and validates the read inspiratory pressure
 * Updates the measurement inputs
 *
 * returns the inspiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 *
 */
int get_inspiratory_pressure();

/*
 * Reads and validates the read expiratory pressure
 * Updates the measurement inputs
 *
 * returns the expiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 */
int get_expiratory_pressure();

/*
 * Reads and validates the read inspiratory flow
 * Updates the measurement inputs
 *
 * returns the inspiratory flow in SLPM when it is valid
 * returns SLPM when no valid flow is available
 */
int get_inspiratory_flow();

/*
 * Reads and validates the read expiratory flow
 * Updates the measurement inputs
 *
 * returns the expiratory flow in SLPM when it is valid
 * returns SLPM  when no valid flow is available
 */
int get_expiratory_flow();


#endif /* INC_PLATFORM_PRESSURE_FLOW_SENSOR_H_ */
