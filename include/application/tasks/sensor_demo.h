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
void task_sensor_demo();