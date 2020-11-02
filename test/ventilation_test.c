/*
 * ventilation_test.c
 *
 * test the function contain in ventilation.c
 */

#include "application/tasks/ventilation.h"
#include "stubs/system_info_stub.h"
#include "stubs/valve_stub.h"
#include "test_util.h"


void reset_to_inspiration_start();

int startVentilation_afterOneInspiration_openInspiratoryValve() {
  int* times = (int*) malloc(1*sizeof(int)); 
  times[0] = 130;
  set_current_time(times, 1);

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