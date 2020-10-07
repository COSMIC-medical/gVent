/*
 * valveStatus.h
 *
 */

#ifndef INC_PLATFORM_VALVE_PRIVATE_H_
#define INC_PLATFORM_VALVE_PRIVATE_H_

typedef struct ValveStatus {
	/**
	 * Boolean that indicates if inspiratory valve is expected to be open
	 */
	bool inspiratory_valve_expected_open;

	/**
	 * Boolean that indicates if expiratory valve is expected to be open
	 */
	bool expiratory_valve_expected_open;

	/**
	 * Boolean that indicates if tank valve is expected to be open
	*/
	bool tank_valve_expected_open;

} valve_status_t;

#endif /* INC_PLATFORM_VALVE_PRIVATE_H_ */
