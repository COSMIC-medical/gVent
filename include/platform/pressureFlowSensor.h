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

uint32_t read_FS6122_sensor(uint8_t, uint8_t);

/*
 * Reads and validates the read inspiratory pressure
 * Updates the measurement inputs
 *
 *  Validation: 
 *      -5 ~ +40 [cmH2O]
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
 * Validation: 
 *      -5 ~ +40 [cmH2O]
 *
 * returns the expiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 */
int get_expiratory_pressure();

/*
 * Reads and validates the read inspiratory flow
 * Updates the measurement inputs
 *
 * Validation: 
 *      flow between -250 ~ +250 SLPM
 * 
 * returns the inspiratory flow in SLPM when it is valid
 * returns SLPM when no valid flow is available
 */
int get_inspiratory_flow();

/*
 * Reads and validates the read expiratory flow
 * Updates the measurement inputs
 * 
 * Validation: 
 *      flow between -250 ~ +250 SLPM
 *
 * returns the expiratory flow in SLPM when it is valid
 * returns SLPM when no valid flow is available
 */
int get_expiratory_flow();


#endif /* INC_PLATFORM_PRESSURE_FLOW_SENSOR_H_ */
