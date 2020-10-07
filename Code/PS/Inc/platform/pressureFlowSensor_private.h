/*
 * pressureFlowSensor_private.h
 *
 * private to the platform
 */

#ifndef INC_PLATFORM_MEASURED_INPUTS_H_
#define INC_PLATFORM_MEASURED_INPUTS_H_

/*
* The worstcase tolerable latency (in ms) for which the sensed inputs are valid
*/
#define PRESSURE_MAXIMUM_LATENCY 1000
#define FLOW_MAXIMUM_LATENCY 1000

/*
* The minimum latency (in ms) for the sensed inputs under which read are not necessary
*/
#define PRESSURE_MINIMUM_LATENCY 1
#define FLOW_MINIMUM_LATENCY 1

/*
 * The lower and upper bounds of validity for the sensed inputs
 * pressure bounds are given in cmH2O
 * flow  bounds are given in ???
 */
#define PRESSURE_LOWER_BOUND 0
#define PRESSURE_UPPER_BOUND 100
#define FLOW_LOWER_BOUND 0
#define FLOW_UPPER_BOUND 100

/*
 * The maximum change rate
 * pressure change rate given in cmH2O per second
 * flow change rate given in ???
 */
#define PRESSURE_MAX_CHANGE_RATE 10
#define FLOW_MAX_CHANGE_RATE 10

/**
 * Definition of the measured inputs data structure
 */
typedef struct MeasurementsStatus {
	/**
	 * The last read value for the inspiratory pressure
	 */
	int inspiratory_pressure;
	/*
	 * the time at which the above inspiratory pressure was read
	 */
	int last_inspiratory_pressure_read_time;

	/*
	 * The last read value for the expiratory pressure
	 */
	int expiratory_pressure;
	/*
	* the time at which the above expiratory pressure was read
	*/
	int last_expiratory_pressure_read_time;

	/*
	* The last read value for the inspiratory flow
	*/
	int inspiratory_flow;
	/*
	* the time at which the above inspiratory flow was read
	*/
	int last_inspiratory_flow_read_time;

	/*
	* The last read value for the expiratory flow
	*/
	int expiratory_flow;
	/*
	 * the time at which the above expiratory flow was read
	*/
	int last_expiratory_flow_read_time;
} measurements_status_t;

#endif /* INC_PLATFORM_MEASURED_INPUTS_H_ */


