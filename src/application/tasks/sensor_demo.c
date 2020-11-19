#include "application/dss.h"
#include "application/tasks/sensor_demo.h"
#include "platform/common.h"
#include "platform/pressureFlowSensor.h"
#include "platform/pressureFlowSensor_private.h"
#include "platform/system_info.h"

// current state of our internal task state machine
uint32_t sensor_state = 0;

/**
 * This is a toy task for reading a sensor and demonstrating
 * the platform's sensor management functionality. The purpose
 * is to faciliate testing of the sensor reading via I2C and the 
 * associated electronics.
 * 
 * This task does the following:
 *  1. Reads inpiratory sensor for flow and pressure.
 *  2. Writes the value thru UART to the terminal
 *  3. Waits for 1 second.
 *  4. Reads expiratory sensor for flow and pressure
 *  5. Writes the value thru UART to the terminal
 *  6. Waits for 1 second.
 * 
 * This task should eventually be removed from the application.
 */
void task_sensor_demo() {
    /* fetch the current time in milliseconds
     *
     * in this demo implementation, we do not account for timer overflow
     * which would occur in a long running application after approximately 
     * (2^32)/(1000*60*60*24) = ~49 days of continous operation without
     * a syste reset.
     */ 
    // number of milliseconds to wait between state changes
    static uint32_t wait_time_ms = 1000;
    
    int* expiratory_flow;
    int* inspiratory_flow;
    int* expiratory_pressure;
    int* inspiratory_pressure;

    status_t status = STATUS_ERR;


    switch(sensor_state) {

        case 0:
            // initial state, read inspiratory pressure and flow
            status = get_inspiratory_pressure(*inspiratory_pressure);
            status = get_inspiratory_flow(*inspiratory_flow);
            sensor_state = 1;
            break;

        case 1:
            // wait 1 second
            // once elapsed advance state machine.
            wait(wait_time_ms);
            sensor_state = 2;
            // }
            break;

        case 2:
            // read expiratory pressure and flow
            // a timer variable
            status = get_expiratory_pressure(*expiratory_pressure);
            status = get_expiratory_flow(*expiratory_flow);
            sensor_state = 3;
            break;

        case 3:
            // wait for 1 second
            wait(wait_time_ms);
            sensor_state = 0;
            // }
            break;


        default:
            // should never reach this state, if we do something
            // bad has happened; transition to DSS.
            dss();
            break;

    }
}