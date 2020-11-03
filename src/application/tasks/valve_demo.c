#include <application/dss.h>
#include <application/tasks/valve_demo.h>
#include <platform/common.h>
#include <platform/valve.h>
#include <platform/system_info.h>

// number of milliseconds to wait between valve actuations
uint32_t wait_time_ms = 5000;

// current state of our internal task state machine
uint32_t state = 0;

// last time a valve state was changed
uint32_t last = 0;

/**
 * This task runs every 50 ms. However, the requirements
 * for this task are to control the valves on the order
 * of seconds. So we must use a state machine that is updated
 * between invocations of this task. 
 * 
 * Note that this is a demo implementation only. Only to be
 * used for testing valve actuation/hookup.
 */
void task_valve_demo() {

    /* fetch the current time in milliseconds
     *
     * in this demo implementation, we do not account for timer overflow
     * which would occur in a long running application after approximately 
     * (2^32)/(1000*60*60*24) = ~49 days of continous operation without
     * a syste reset.
     */ 
    uint32_t now = get_current_time();

    switch(state) {

        case 0:
            // initial state, all valves closed, start timer
            // to keep valves closed for 5 seconds.
            close_inspiratory_valve();
            close_expiratory_valve();
            close_tank_valve();
            last = get_current_time();
            state = 1;
            break;

        case 1:
            // wait 5 seconds while all valves are closed,
            // once elapsed advance state machine.
            if (now - last > wait_time_ms) {
                state = 2;
            }
            break;

        case 2:
            // open the inspiratory valve and set
            // a timer variable
            open_inspiratory_valve();
            last = get_current_time();
            state = 3;
            break;

        case 3:
            // wait for 5 seconds while inspiratory valve is open
            // once elapsed, close inspiratory valve and advance
            if (now - last > wait_time_ms) {
                close_inspiratory_valve();
                state = 4;
            }
            break;

        case 4:
            // close inspiratory valve and open expiratory valve
            // also reset timer variable
            open_expiratory_valve();
            last = get_current_time();
            state = 5;
            break;

        case 5:
            // wait for 5 seconds while the expiratory valve is open
            // once elapsed, close expiratory valve and advance
            if (now - last > wait_time_ms) {
                close_expiratory_valve();
                state = 6;
            }
            break;

        case 6:
            // open tank valve and set a timer variable
            open_tank_valve();
            last = get_current_time();
            state = 7;
            break;

        case 7:
            // wait 5 seconds while tank valve is open
            // once elapsed, then close tank valve and
            // loop back to initial state.
            if (now - last > wait_time_ms) {
                close_tank_valve();
                state = 0;
            }
            break;

        default:
            // should never reach this state, if we do something
            // bad has happened; transition to DSS.
            dss();
            break;

    }

}
