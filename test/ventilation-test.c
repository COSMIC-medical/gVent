/*
 * ventilation-test.c
 *
 * test the function contain in ventilation.c
 */

#include "application/ventilation.h"
#include "stubs/systemInfo_stub.h"
#include "stubs/valve_stub.h"
#include "testUtil.h"


void reset_to_inspiration_start();

void startVentilation_openInspiratoryValve() {
  int* times = (int*) malloc(2*sizeof(int)); 
  times[0] = 130;
  times[1] = 290;
  set_current_time(times);

  close_inspiratory_valve();
  
  start_inspiration();

  int inspiratory_valve_status = get_inspiratory_valve_status();
  assertTrue(inspiratory_valve_status == VALVE_OPEN);

  close_inspiratory_valve();
  reset_to_inspiration_start();

  start_inspiration();

  inspiratory_valve_status = get_inspiratory_valve_status();
  assertTrue(inspiratory_valve_status == VALVE_OPEN);
}

void startVentilation_doesNotopenInspiratoryValve() {
  int* times = (int*) malloc(1*sizeof(int)); 
  times[0] = 125;
  set_current_time (times);

  close_inspiratory_valve();
  reset_to_inspiration_start();
  
  start_inspiration();

  int inspiratory_valve_status = get_inspiratory_valve_status();
  assertTrue(inspiratory_valve_status == VALVE_CLOSE);
}
