/*
 * alarm_private.h
 *
 */

#ifndef INC_PLATFORM_ALARM_PRIVATE_H_
#define INC_PLATFORM_ALARM_PRIVATE_H_

#include <stdbool.h>

/**
 * Definition of the alarm data structure
 */
typedef struct AlarmStatus {
	/**
	 * Boolean that indicates if the alarm is on
	 */
	bool alarm_on;

	/**
	 * Boolean that indicates if the alarm is off
	 */
	bool alarm_muted;

} alarm_status_t;

#endif /* INC_PLATFORM_ALARM_PRIVATE_H_ */
