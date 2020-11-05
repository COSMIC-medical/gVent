/*
 * alarm.h
 *
 * Functions to interact with the alarm.
 */

#ifndef SRC_PLATFORM_ALARM_H_
#define SRC_PLATFORM_ALARM_H_

/**
 * Status of the alarm. 
 */
typedef enum {
    OFF, // buzzer and alarm LED off. 
    ON, // buzzer and alarm LED both on.
    MUTED // buzzer off and alarm LED on.
} alarm_status_t;

/**
 * @return the current alarm status.
 */
alarm_status_t get_alarm_status();

/*
 * Turn on the alarm. 
 * 
 * Powers on the alarm's LED, and if the alarm is not 
 * muted, powers on the alarm buzzer
 * 
 * @return STATUS_OK if the alarm was turned on or
 *         STATUS_ERR if alarm was not turned off.
 */
status_t set_alarm_on();

/*
 * Turn off the alarm. 
 * 
 * Powers off the alarm's LED and turns off the alarm's
 * buzzer.
 * 
 * @return STATUS_OK if the alarm was turned off and
 *         STATUS_ERR if the alarm was not turned off.
 */
status_t set_alarm_off();

/*
 * Updates the alarm status to muted
 * 
 * If the alarm is on powers off the alarm's buzzer
 * 
 * @return STATUS_OK if the alarm was muted and
 *         STATUS_ERR if the alarm was not muted.
 */
status_t mute_alarm();

/*
 * Updates the alarm status to not muted
 * 
 * If the alarm is on powers on the alarm's buzzer.
 * 
 * @return STATUS_OK if the alarm was unmuted and
 *         STATUS_ERR if the alarm was not unmuted. 
 */
status_t unmute_alarm();

#endif /* SRC_PLATFORM_ALARM_H_ */
