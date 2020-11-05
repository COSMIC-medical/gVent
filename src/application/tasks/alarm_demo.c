#include <application/dss.h>
#include <application/tasks/alarm_demo.h>
#include <platform/common.h>
#include <platform/alarm.h>
#include <platform/system_info.h>

// number of milliseconds to wait between state changes
static uint32_t wait_time_ms = 1000;

// current internal state of the alarm demo task
static uint32_t state = 0;

// last time we changed state
static uint32_t last = 0;

/**
 * This task runs every ~50 milliseconds. However, the
 * requirements for this task are to control the alarm on
 * the order of seconds. So, we must use a state machine
 * and internal time tracker to decide when to change the
 * alarm state. 
 * 
 * Note that this is a demo implementation. Only to be used
 * for testing alarm actutation and hardware hookup.
 */
void task_alarm_demo() {

    // get the current time this iteration the task is running.
    uint32_t now = get_current_time();

    switch(state) { 

        case 0: 
            set_alarm_off();
            last = get_current_time();
            state = 1;
            break;

        case 1: 
            // wait 5 seconds while alarm is off
            if (now - last > wait_time_ms) {
                state = 2;
            }
            break;

        case 2:
            if (set_alarm_on() != STATUS_OK) {
                // if the alarm could not be turned on, then
                // something wrong happened, transition to DSS
                dss();
            } else {
                last = get_current_time();
                state = 3;
            }
            break;

        case 3:
            // wait 5 seconds while alarm is on
            if (now - last > wait_time_ms) {
                state = 4;
            }
            break;

        case 4:
            mute_alarm();
            last = get_current_time();
            state = 5;
            break;

        case 5:
            // wait 5 seconds while alarm is muted
            if (now - last > wait_time_ms) {
                state = 6;
            }
            break;

        case 6:
            unmute_alarm();
            last = get_current_time();
            state = 7;
            break;

        case 7:
            // wait 5 seconds while alarm is on
            if (now - last > wait_time_ms) {
                // back to initial state
                state = 0;
            }
            break;

        default:
            // should never happen, if we get here something
            // bad occured, go to DSS.
            dss();
            break;
    }
}