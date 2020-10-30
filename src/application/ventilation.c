/*
 * ventilation.c
 *
 */

#include <stdbool.h>
#include <platform/systemInfo.h>
#include <platform/pressureFlowSensor.h>
#include <platform/valve.h>
#include <application/ventilation.h>
#include <application/dss.h>

#define INSPIRATORY_FLOW_TIME 	1
#define INSPIRATORY_PAUSE	2
#define EXPIRATORY_FLOW_TIME 	3
#define EXPIRATORY_PAUSE	4

/*
 * the time the current breath cycle was supposed to start
 */
static int start_current_breath_cycle = 0;

/*
 * the time the current breath cycle was supposed to start
 */
static int breath_cycle_duration = 125; //to do replace this calue by the real one

/*
 * Phase of the ventilation
 * This should always be one of
 *  INSPIRATORY_FLOW_TIME | INSPIRATORY_PAUSE
 *  | EXPIRATORY_FLOW_TIME | EXPIRATORY_PAUSE
 */

int get_circuit_pressure() { return 0; }

static int ventilation_phase = EXPIRATORY_PAUSE;

void ventilation(){
  switch (ventilation_phase) {
    case INSPIRATORY_FLOW_TIME:
      start_inspiration();
      break;

    case INSPIRATORY_PAUSE:
      // statements
      break;

    case EXPIRATORY_FLOW_TIME:
      // statements
      break;

    case EXPIRATORY_PAUSE:
      // statements
      break;

    default:
      dss();
  }
}

void start_inspiration(){
  int current_time = get_current_time();
  if (ventilation_phase ==  EXPIRATORY_PAUSE
      && current_time >= start_current_breath_cycle + breath_cycle_duration) {
     start_current_breath_cycle = current_time;
     if (get_circuit_pressure() > MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP ) {
      dss();
     }
     open_inspiratory_valve();
     ventilation_phase = INSPIRATORY_FLOW_TIME;
  }
}

/*
 * function for test only
 */ 
void reset_to_inspiration_start(){
   ventilation_phase = EXPIRATORY_PAUSE;
}
