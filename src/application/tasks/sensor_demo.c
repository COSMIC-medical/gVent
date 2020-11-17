#include <application/dss.h>
#include <application/tasks/sensor_demo.h>
#include <platform/common.h>
#include <platform/pressureFlowSensor.h>
#include <platform/pressureFlowSensor_private.h>
#include <platform/system_info.h>

// current state of our internal task state machine
uint32_t sensor_state = 0;

/**
 * This is a toy task for reading a sensor and demonstrating
 * the platform's sensor management functionality. The purpose
 * is to faciliate testing of the sensor reading via i2c and the 
 * associated electronics.
 * 
 * This task does the following:
 *  1. Read a sensor.
 *  2. Write the value thru uart to the terminal
 *  3. Waits for 5 seconds.
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
    // uint32_t rn = get_current_time();
    
    // MeasurementsStatus.expiratory_flow = 0;
    // MeasurementsStatus.inspiratory_flow = 0;
    // MeasurementsStatus.expiratory_pressure = 0;
    // MeasurementsStatus.inspiratory_pressure = 0;
    int* expiratory_flow;
    int* inspiratory_flow;
    int* expiratory_pressure;
    int* inspiratory_pressure;

    status_t status = STATUS_ERR;


    switch(sensor_state) {

        case 0:
            // initial state, all valves closed, start timer
            // to keep valves closed for 5 seconds.
            status = get_inspiratory_pressure(*inspiratory_pressure);
            status = get_inspiratory_flow(*inspiratory_flow);
            // last = get_current_time();
            sensor_state = 1;
            break;

        case 1:
            // wait 5 seconds while all valves are closed,
            // once elapsed advance state machine.
            // if (now - last > wait_time_ms) {
            sensor_state = 2;
            // }
            break;

        case 2:
            // open the inspiratory valve and set
            // a timer variable
            status = get_expiratory_pressure(*expiratory_pressure);
            // if (status == STATUS_ERR){
                
            // }
            status = get_expiratory_flow(*expiratory_flow);
            // TODO add UART serial print
            // last = get_current_time();
            sensor_state = 3;
            break;

        case 3:
            // wait for 5 seconds while inspiratory valve is open
            // once elapsed, close inspiratory valve and advance
            // if (now - last > wait_time_ms) {
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