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


void reset_to_inspiration_start();

int startVentilation_afterOneInspiration_openInspiratoryValve() {
  //initialize the function get_current_time
  int* times = (int*) malloc(1*sizeof(int)); 
  times[0] = 130;
  set_current_time(times, 1);

  //initialize the function get_respiratory_rate
  uint32_t RR[1] = {7500000}; 
  status_t status[1] = {STATUS_OK};
  set_respiratory_rate(RR, status, 1);

  //reinitialize the system to be sure that the valve wasn't previously open
  close_inspiratory_valve();
  
  start_inspiration();

  int inspiratory_valve_status = get_inspiratory_valve_status();
  assertTrue(inspiratory_valve_status == VALVE_OPEN);
}

int startVentilation_duringInspiration_doesNotopenInspiratoryValve() {
  int* times = (int*) malloc(1*sizeof(int)); 
  times[0] = 0;
  set_current_time (times, 1);

  close_inspiratory_valve();
  reset_to_inspiration_start();
  
  start_inspiration();

  int inspiratory_valve_status = get_inspiratory_valve_status();
  assertTrue(inspiratory_valve_status == VALVE_CLOSE);
}

int getCircuitPressure_validValues_returnsMeanPressure() {
	int* values = (int*)malloc(2 * sizeof(int));
	values[0] = 35;
	values[1] = 60;
	set_inspiratory_pressure(values, 2);

	values[0] = 40;
	values[1] = 53;
	set_expiratory_pressure(values, 2);

	int circuit_pressure = get_circuit_pressure();
	assertTrue(circuit_pressure == 37);
}
