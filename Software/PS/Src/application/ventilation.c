/*
 * ventilation.c
 *
 */

#include <stdbool.h>
#include <platform/systemInfo.h>
#include <platform/pressureFlowSensor.h>
#include <application/ventilation.h>
#include <application/dss.h>

#define INSPIRATORY_FLOW_TIME 	1
#define INSPIRATORY_PAUSE	2
#define EXPIRATORY_FLOW_TIME 	3
#define EXPIRATORY_PAUSE	4

/*
 * the time the current breath cycle was supposed to start
 */
static int start_current_breath_cycle;

/*
 * the time the current breath cycle was supposed to start
 */
static int breath_cycle_duration;

/*
 * Phase of the ventilation
 * This should always be one of
 *  INSPIRATORY_FLOW_TIME | INSPIRATORY_PAUSE
 *  | EXPIRATORY_FLOW_TIME | EXPIRATORY_PAUSE
 */
static int ventilation_phase;

void ventilation(){
  start_inspiration();
}

int get_circuit_pressure(){
  int inspiratory_pressure = get_inspiratory_pressure();
  int expiratory_pressure = get_expiratory_pressure();
  //todo computation
}

void start_inspiration(){
  int current_time = get_current_time();
  if (ventilation_phase ==  EXPIRATORY_PAUSE
      && current_time >= start_current_breath_cycle + breath_cycle_duration) {
     start_current_breath_cycle = current_time;
     if (get_circuit_pressure() > MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP ) {
      dss(); //SRS???
     }
     open_inspiratory_valve();
     ventilation_phase = INSPIRATORY_FLOW_TIME;
  }
}
