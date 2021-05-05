/**
 * This is a toy task that drives the alarm devices
 * through several states. The purpose is to demonstrate
 * how to use the alarm platform API and to facilate
 * hardware/software integration testing.
 * 
 * The task does the following:
 * 
 *  1. Turns off the alarm.
 *  2. Waits 5 seconds.
 *  3. Turns on the alarm (both buzzer and LED).
 *  4. Waits 5 seconds.
 *  5. Mutes the alarm (buzzer off and LED still on).
 *  6. Waits 5 seconds.
 *  7. Unmutes the alarm (buzzer and LED on)
 *  8. Waits 5 seconds.
 *  9. Repeats from (1).
 * 
 * This task should eventually be removed from the application.
 */
void task_alarm_demo();