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

#include "platform/common.h"
/*
 * Reads and validates the read inspiratory pressure
 * Updates the measurement inputs
 *
 *  Validation: 
 *      -5 ~ +40 [cmH2O]
 * A valid sensor reading should be between -5 cmH2O, and +40 cmH2O
 * for our model of the FS6122 sensor. That is the min/max pressure range. 
 * Since we are not dividing the raw reading by a factor of 1000 (which would 
 * turn the int32_t into a floating point value) we therefore check whether the reading is
 * in the range: 
 *      -5000 ~ +40000
 * 
 * returns the inspiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 *
 */
status_t get_inspiratory_pressure(int *);

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
status_t get_expiratory_pressure(int *);

/*
 * Reads and validates the read inspiratory flow
 * Updates the measurement inputs
 *
 * Validation: 
 *      flow between -250 ~ +250 SLPM
 * 
 * A valid sensor reading should be between -250 SLPM, and +250 SLPM
 * for our model of the FS6122 sensor. That is the min/max flow range. 
 * Since we are not dividing the raw reading by a factor of 1000 (which would 
 * turn the int32_t into a floating point value) we therefore check whether the reading is
 * in the range: 
 *      -250000 ~ +250000
 * 
 * returns the inspiratory flow in SLPM when it is valid
 * returns SLPM when no valid flow is available
 */
status_t get_inspiratory_flow(int *);

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
status_t get_expiratory_flow(int *);


#endif /* INC_PLATFORM_PRESSURE_FLOW_SENSOR_H_ */
