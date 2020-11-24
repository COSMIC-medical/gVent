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
void task_display_demo();