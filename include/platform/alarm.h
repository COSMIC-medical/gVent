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
    MUTED, // buzzer off and alarm LED on.
    ERR // an error occured trying to set the alarm.
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
 */
void set_alarm_on();

/*
 * Turn off the alarm. 
 * 
 * Powers off the alarm's LED and turns off the alarm's
 * buzzer.
 */
void set_alarm_off();

/*
 * Updates the alarm status to muted
 * 
 * If the alarm is on powers off the alarm's buzzer
 */
void mute_alarm();

/*
 * Updates the alarm status to not muted
 * 
 * If the alarm is on powers on the alarm's buzzer.
 */
void unmute_alarm();

#endif /* SRC_PLATFORM_ALARM_H_ */
