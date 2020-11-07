/*
 * ventilation.c
 *
 * Provides the ventilation functionality of the ventilator as per SLS-0055
 */

#include <stdbool.h>
#include <stdint.h>
#include <platform/system_info.h>
#include <platform/pressureFlowSensor.h>
#include <platform/valve.h>
#include "platform/clinician_input.h" // Added to use get_respiratory_rate in breath cycle duration calc
#include <application/tasks/ventilation.h>
#include <application/dss.h>

//todo rename this so that it does not look like they are time
#define INSPIRATION         1
#define INSPIRATORY_PAUSE   2
#define EXPIRATION          3
#define EXPIRATORY_PAUSE    4

/*
 * the time the current breath cycle was supposed to start
 */
static int start_current_breath_cycle = 0;

static int calculate_breath_cycle_duration(){
  int breath_cycle_duration = 0; // Variable initialization
  int respiratory_rate = get_respiratory_rate(); // Retrieve clinician respiratory rate
  return breath_cycle_duration = 60000/respiratory_rate; // Calculate cycle duration
}
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
  uint32_t breath_cycle_duration = calculate_breath_cycle_duration(); //Added this line to calculate breath cycle (not sure if compatible with int variable)
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
