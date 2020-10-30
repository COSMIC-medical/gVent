/*
 * valve.h
 *
 */

#ifndef INC_PLATFORM_VALVE_H_
#define INC_PLATFORM_VALVE_H_

#define VALVE_OPEN 1
#define VALVE_CLOSE 0

/*
 * Opens the inspiratory valve
 * Updates the expected inspiratory valve status
 *
 */
void open_inspiratory_valve();

/*
 * Opens the expiratory valve
 * Updates the expected expiratory valve status
 * Updates
 */
void open_expiratory_valve();

/*
 * Opens the tank valve
 * Updates the expected tank valve status
 *
 */
void open_tank_valve();

/*
 * Closes the inspiratory valve
 * Updates the expected inspiratory valve status
 *
 */
void close_inspiratory_valve();

/*
 * Closes the expiratory valve
 * Updates the expected expiratory valve status
 *
 */
void close_expiratory_valve();

/*
 * Closes the tank valve
 *Updates the expected tank valve status
 *
 */
void close_tank_valve();

/*
 * Getters
 */

int get_inspiratory_valve_status();

int get_expiratory_valve_status();

int get_tank_valve_status();


#endif /* INC_PLATFORM_VALVE_H_ */
