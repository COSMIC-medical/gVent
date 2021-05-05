#include "application/dss.h"
#include "application/tasks/sensor_demo.h"
#include "platform/common.h"
#include "platform/sensor.h"
#include "platform/sensor_private.h"
#include "platform/system_info.h"
#include "platform/scheduler.h"

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
    
    uint32_t expiratory_flow = 0;
    uint32_t inspiratory_flow = 0;
    uint32_t expiratory_pressure = 0;
    uint32_t inspiratory_pressure = 0;

    switch(sensor_state) {

        case 0:
            // initial state, read inspiratory pressure and flow
            get_inspiratory_pressure(&inspiratory_pressure);
            get_inspiratory_flow(&inspiratory_flow);
            sensor_state = 1;
            break;

        case 1:
            // read expiratory pressure and flow
            // a timer variable
            get_expiratory_pressure(&expiratory_pressure);
            get_expiratory_flow(&expiratory_flow);
            sensor_state = 0;
            break;


        default:
            // should never reach this state, if we do something
            // bad has happened; transition to DSS.
            dss();
            break;

    }
}