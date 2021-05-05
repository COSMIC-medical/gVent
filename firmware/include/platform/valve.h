/*
 * valve.h
 * 
 * Functions to actuate the valves that control flow of air through
 * the ventilator's breath circuit. There are three controlled valves:
 */

#ifndef INC_PLATFORM_VALVE_H_
#define INC_PLATFORM_VALVE_H_

/*
 * Opens the inspiratory valve
 */
void open_inspiratory_valve();

/*
 * Opens the expiratory valve
 */
void open_expiratory_valve();

/*
 * Opens the tank valve
 */
void open_tank_valve();

/*
 * Closes the inspiratory valve
 */
void close_inspiratory_valve();

/*
 * Closes the expiratory valve
 */
void close_expiratory_valve();

/*
 * Closes the tank valve
 */
void close_tank_valve();

#endif /* INC_PLATFORM_VALVE_H_ */
