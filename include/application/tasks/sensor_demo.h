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
void task_sensor_demo();