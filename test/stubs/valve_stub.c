/*
 * valve_stub.c
 *
 * Stub for the valves
 */

#include "valve_stub.h"

int inspiratory_valve_status;
int expiratory_valve_status;
int tank_valve_status;

/*
 * Opens the inspiratory valve
 * Updates the expected inspiratory valve status
 *
 */
void open_inspiratory_valve(){
  inspiratory_valve_status = VALVE_OPEN;
}

/*
 * Opens the expiratory valve
 * Updates the expected expiratory valve status
 * Updates
 */
void open_expiratory_valve(){
  expiratory_valve_status = VALVE_OPEN;
}

/*
 * Opens the tank valve
 * Updates the expected tank valve status
 *
 */
void open_tank_valve(){
  tank_valve_status = VALVE_OPEN;
}

/*
 * Closes the inspiratory valve
 * Updates the expected inspiratory valve status
 *
 */
void close_inspiratory_valve(){
  inspiratory_valve_status = VALVE_CLOSE;
}

/*
 * Closes the expiratory valve
 * Updates the expected expiratory valve status
 *
 */
void close_expiratory_valve(){
  expiratory_valve_status = VALVE_CLOSE;
}

/*
 * Closes the tank valve
 *Updates the expected tank valve status
 *
 */
void close_tank_valve(){
  tank_valve_status = VALVE_CLOSE;
}

/*
 * Getters
 */
int get_inspiratory_valve_status(){
 return inspiratory_valve_status;
}

int get_expiratory_valve_status(){
 return expiratory_valve_status;
}

int get_tank_valve_status(){
 return tank_valve_status;
}

