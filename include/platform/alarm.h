/*
 * alarm.h
 *
 * Functions an application developer will used to interact with the alarm.
 *
 * To be re-implemented on COSMIC hooks up devices.
 */

#ifndef SRC_PLATFORM_ALARM_H_
#define SRC_PLATFORM_ALARM_H_

/*
 * Update the alarm status to on
 * Powers on the alarm's led
 * If the alarm is not muted powers on the alarm buzzer
 */
void set_alarm_on();

/*
 * Update the alarm status to on
 * Powers off the alarm's led
 * Powers off the alarm's buzzer
 */
void set_alarm_off();

/*
 * Updates the alarm status to muted
 * If the alarm is on powers off the alarm's buzzer
 */
void mute_alarm();

/*
 * Updates the alarm status to not muted
 * If the alarm is on powers on the alarm's buzzer
 */
void unmute_alarm();

#endif /* SRC_PLATFORM_ALARM_H_ */
