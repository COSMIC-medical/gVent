/*
 * ventilation_test.c
 *
 * test the function contain in ventilation.c
 */

#include "application/tasks/ventilation.h"
#include "stubs/system_info_stub.h"
#include "stubs/valve_stub.h"
#include "stubs/clinician_input_stub.h"
#include "stubs/sensor_stub.h"
#include "test_util.h"
#include "platform/common.h"
#include <stdio.h>

//test functions defined in ventilation.c only
void reset_to_inspiration_start();
int get_ventilation_phase();
int get_start_current_breath_cycle();

int startVentilation_afterOneInspiration_openInspiratoryValve() {
  //initialize the function get_current_time
  int* times = (int*) malloc(1*sizeof(int)); 
  times[0] = 130;
  set_current_time(times, 1);

  //initialize the function get_respiratory_rate
  uint32_t RR[1] = {7500000}; 
  status_t status[1] = {STATUS_OK};
  set_respiratory_rate(RR, status, 1);

  //initialize the function to get circuit pressure
  uint32_t inspiratory[2] = {12, 53};
  uint32_t expiratory[2] = {14, 53};
  status_t status_pressure[2] = {STATUS_OK, STATUS_OK};
	set_inspiratory_pressure(inspiratory, status_pressure);
	set_expiratory_pressure(expiratory, status_pressure);

  //reinitialize the system to be sure that the valve wasn't previously open
  close_inspiratory_valve();
  reset_to_inspiration_start();
  
  start_inspiration();

  int inspiratory_valve_status = get_inspiratory_valve_status();
  assertTrue(inspiratory_valve_status == VALVE_OPEN);
}

int startVentilation_afterOneInspiration_setsVentilationPhaseToInspiration() {
  //initialize the function get_current_time
  int* times = (int*) malloc(1*sizeof(int)); 
  times[0] = 260;
  set_current_time(times, 1);

  //initialize the function get_respiratory_rate
  uint32_t* RR = (uint32_t*) malloc(1*sizeof(uint32_t)); 
  RR[0] = 7500000;
  status_t* status= (status_t*) malloc(1*sizeof(status_t));
  status[0] = STATUS_OK;
  set_respiratory_rate(RR, status, 1);

  //initialize the function to get circuit pressure
  uint32_t inspiratory[2] = {12, 53};
  uint32_t expiratory[2] = {14, 53};
  status_t status_pressure[2] = {STATUS_OK, STATUS_OK};
	set_inspiratory_pressure(inspiratory, status_pressure);
	set_expiratory_pressure(expiratory, status_pressure);

  reset_to_inspiration_start();

  start_inspiration();

  int ventilation_phase = get_ventilation_phase();
  assertTrue(ventilation_phase == 1);
}

int startVentilation_afterTwoInspirations_updatesStartCurrentBreathCycle() {
  //initialize the function get_current_time
  int* times = (int*) malloc(1*sizeof(int)); 
  int time = 390;
  times[0] = time;
  set_current_time(times, 1);

  //initialize the function get_respiratory_rate
  uint32_t* RR = (uint32_t*) malloc(1*sizeof(uint32_t)); 
  RR[0] = 7500000;
  status_t* status= (status_t*) malloc(1*sizeof(status_t));
  status[0] = STATUS_OK;
  set_respiratory_rate(RR, status, 1);

  reset_to_inspiration_start();

  start_inspiration();

  int time_of_start_current_breath_cycle = get_start_current_breath_cycle();
  assertTrue(time_of_start_current_breath_cycle == time);
}

int startVentilation_duringInspiration_doesNotopenInspiratoryValve() {
  int* times = (int*) malloc(1*sizeof(int)); 
  times[0] = 150;
  set_current_time (times, 1);

  //initialize the function get_respiratory_rate
  uint32_t RR[1] = {7500000}; 
  status_t status[1] = {STATUS_OK};
  set_respiratory_rate(RR, status, 1);

  //initialize the function to get circuit pressure
  uint32_t inspiratory[2] = {35, 53};
  uint32_t expiratory[2] = {40, 53};
  status_t status_pressure[2] = {STATUS_OK, STATUS_OK};
	set_inspiratory_pressure(inspiratory, status_pressure);
	set_expiratory_pressure(expiratory, status_pressure);

  close_inspiratory_valve();
  reset_to_inspiration_start();
  
  start_inspiration();

  int inspiratory_valve_status = get_inspiratory_valve_status();
  assertTrue(inspiratory_valve_status == VALVE_CLOSE);
}

int getCircuitPressure_validValues_returnsMeanPressure() {
  uint32_t inspiratory[2] = {35, 53};
  uint32_t expiratory[2] = {40, 53};

  status_t status[2] = {STATUS_OK, STATUS_OK};

	set_inspiratory_pressure(inspiratory, status);
	set_expiratory_pressure(expiratory, status);

	uint32_t circuit_pressure = get_circuit_pressure();
	assertTrue(circuit_pressure == 37);

  circuit_pressure = get_circuit_pressure();
	assertTrue(circuit_pressure == 53);

}

int startVentilation_duringInspiration_doesNotChangeVentilationPhase() {
  int* times = (int*) malloc(1*sizeof(int)); 
  times[0] = 150;
  set_current_time (times, 1);

  reset_to_inspiration_start();
  
  start_inspiration();

  int ventilation_phase = get_ventilation_phase();
  assertTrue(ventilation_phase == 4);
}

int startVentilation_duringInspiration_doesNotUpdatesStartOfcurrentBreathCycle() {
  int* times = (int*) malloc(1*sizeof(int));
  int time = 150;
  times[0] = time;
  set_current_time (times, 1);

  reset_to_inspiration_start();
  
  start_inspiration();

  int time_of_start_current_breath_cycle = get_start_current_breath_cycle();
  assertTrue(time_of_start_current_breath_cycle != time);
}
