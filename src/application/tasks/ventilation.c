/*
 * ventilation.c
 *
 * Provides the ventilation functionality of the ventilator as per SLS-0055
 */

#include <stdbool.h>
#include <stdint.h>

#include "platform/system_info.h"
#include "platform/sensor.h"
#include "platform/valve.h"
#include "application/tasks/ventilation.h"
#include "application/dss.h"
#include "platform/clinician_input.h"

//todo rename this so that it does not look like they are time
#define INSPIRATION         1
#define INSPIRATORY_PAUSE   2
#define EXPIRATION          3
#define EXPIRATORY_PAUSE    4

/*
 * the time the current breath cycle was supposed to start
 */
static int start_current_breath_cycle = 0;

/*
 * the time the current breath cycle was supposed to start
 */
//static int breath_cycle_duration = 125; //to do replace this value by the real one

/*
 * Phase of the ventilation
 * This should always be one of
 *  INSPIRATION | INSPIRATORY_PAUSE
 *  | EXPIRATION | EXPIRATORY_PAUSE
 */

static int ventilation_phase = EXPIRATORY_PAUSE;


int get_circuit_pressure() { return 0; } //to do implement this function

void ventilation(){
  switch (ventilation_phase) {
    case EXPIRATORY_PAUSE:
      start_inspiration();
      break;

    case INSPIRATION:
      // statements
      break;

    case INSPIRATORY_PAUSE:
      // statements
      break;

    case EXPIRATION:
      // statements
      break;

    default:
      dss();
  }
}

void start_inspiration(){
  uint32_t current_time = get_current_time();
  uint32_t RR = 0;
  uint32_t breath_cycle_duration = 125;
  if (get_respiratory_rate(& RR) == STATUS_OK) {
    breath_cycle_duration = RR / 60000;
  }
  if (current_time >= start_current_breath_cycle + breath_cycle_duration) {
      start_current_breath_cycle = current_time;
    if (get_circuit_pressure() > MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP) {
      dss();
    } else {
      open_inspiratory_valve();
      ventilation_phase = INSPIRATION;
    }
  }
}

/*
 * function for test only
 */ 
void reset_to_inspiration_start(){
   ventilation_phase = EXPIRATORY_PAUSE;
}
