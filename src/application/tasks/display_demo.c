#include "application/dss.h"
#include "application/tasks/display_demo.h"
#include "platform/common.h"
#include "platform/display.h"
#include "platform/system_info.h"
#include "platform/configuration_private.h"

// number of milliseconds to wait between state changes
static uint32_t wait_time_ms = 1000;

// current internal state of the alarm demo task
static uint32_t state = 0;

// last time we changed state
static uint32_t last = 0;

/**
 * This is a toy task that writes the LCD display
 * through several states. The purpose is to demonstrate
 * how to use the display platform API and to facilate
 * hardware/software integration testing.
 * 
 * The task does the following:
 * 
 *  1. Initializes the display.
 *  2. Waits 5 seconds.
 *  3. Turns on+off+on the display.
 *  4. Waits 5 seconds.
 *  5. Write "Hello World!" to the display.
 *  6. Waits 5 seconds.
 *  7. Clear the display.
 *  8. Waits 5 seconds.
 *  9. Repeats from (1).
 * 
 * This task should eventually be removed from the application.
 */
void task_display_demo(){

    // get the current time this iteration the task is running.
    uint32_t now = get_current_time();

    switch(state) { 

        case 0: 
            lcd_init();
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
            lcd_send_cmd(LCD_CMD_DISPLAY);
            last = get_current_time();
            state = 3;
            break;

        case 3:
            if (now - last > wait_time_ms) {
                state = 4;
            }
            break;
        
        case 4:
            lcd_send_string("Hello\n World!");
            last = get_current_time();
            state = 5;
            break;
        
        case 5:
            if (now - last > wait_time_ms) {
                state = 6;
            }
            break;

        case 6: 
            lcd_send_cmd(LCD_CMD_CLEAR);
            last = get_current_time();
            state = 7;
            break;

        case 7:
            if (now - last > wait_time_ms) {
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

        
    }
}