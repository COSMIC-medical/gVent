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
#define EXPIRATION          2

/*
 * the time the current breath cycle was supposed to start
 */
static int start_current_breath_cycle = 0;

/*
 * Phase of the ventilation
 * This should always be one of
 *  INSPIRATION | EXPIRATION 
 * The pauses are obtained through the mechanical parts of the system
 * and not the software parts.
 * The inspiration pause is obtained through the maximal pressure
 * The expiration pause is obtained through the PEEP valve
 */

static int ventilation_phase = EXPIRATION;


uint32_t get_circuit_pressure() {
    uint32_t inspiratory_pressure = 0;
    uint32_t expiratory_pressure = 0;
    get_inspiratory_pressure(&inspiratory_pressure);
    get_expiratory_pressure(&expiratory_pressure);

    return (inspiratory_pressure + expiratory_pressure) / 2;
}


void ventilation(){
  /*Attention there is no initialisation of start_current_breath_cycle for the
  * ventilation to start as soon as the code is called this will lead to a 
  * a waiting period of breath_cycle_duration for the first ventilation preiod
  */
  switch (ventilation_phase) {
    case EXPIRATION:
      start_inspiration();
      break;

    case INSPIRATION:
      start_expiration();
      break;

    default:
      dss();
  }
}

void start_inspiration(){
  uint32_t current_time = get_current_time();
  uint32_t RR = 15;
  uint32_t breath_cycle_duration;
  get_respiratory_rate(&RR);
  breath_cycle_duration = 60000 / RR;
  if (current_time >= start_current_breath_cycle + breath_cycle_duration) {
    if (get_circuit_pressure() < MAX_CIRCUIT_PRESSURE_FOR_OPENING_INS_VALVE_CSP) {
      start_current_breath_cycle = current_time;
      open_inspiratory_valve();
      ventilation_phase = INSPIRATION;
    }
  }
}

void start_expiration(){
  uint32_t current_time = get_current_time();
  uint32_t selected_inspiratory_time;
  get_selected_inspiratory_time(&selected_inspiratory_time);
   if (current_time >= start_current_breath_cycle + selected_inspiratory_time) {
     if (get_circuit_pressure() > MIN_CIRCUIT_PRESSURE_FOR_OPENING_EXP_VALVE_CSP){
      close_inspiratory_valve();
      open_expiratory_valve();
      ventilation_phase = EXPIRATION;
     }
   }
}



/*
 * function for test only
 */ 
void reset_to_inspiration_start(){
   ventilation_phase = EXPIRATION;
}

int get_ventilation_phase() {
  return ventilation_phase;
}

int get_start_current_breath_cycle() {
  return start_current_breath_cycle;
}
