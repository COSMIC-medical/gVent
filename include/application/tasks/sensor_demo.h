/**
 * This is a toy task for reading a sensor and demonstrating
 * the platform's sensor management functionality. The purpose
 * is to faciliate testing of the sensor reading via i2c and the 
 * associated electronics.
 * 
 * This task does the following:
 *  1. Closes all valves.
 *  2. Waits for 5 seconds.
 *  3. Opens the inspiratory valve.
 *  4. Waits 5 seconds
 *  5. Closes the inspiratory valve.
 *  6. Opens the expiratory valve.
 *  7. Waits 5 seconds
 *  8. Closes the expiratory valve.
 *  9. Opens the tank valve.
 *  10. Waits 5 seconds
 *  11. Closes the tank valve.
 *  12. Repeat from step (1) 
 * 
 * This task should eventually be removed from the application.
 */
void task_sensor_demo();