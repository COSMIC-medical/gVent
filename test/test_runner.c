#include "ventilation_test.h"
#include "test_util.h"

int main(int argc, char **argv) {
  test(startVentilation_afterOneInspiration_openInspiratoryValve,
   "startVentilation_afterOneInspiration_openInspiratoryValve");
  test(startVentilation_afterOneInspiration_setsVentilationPhaseToInspiration,
  "startVentilation_afterOneInspiration_setsVentilationPhaseToInspiration");
  test(startVentilation_afterTwoInspirations_updatesStartCurrentBreathCycle,
  "startVentilation_afterTwoInspirations_updatesStartCurrentBreathCycle");
  test(startVentilation_duringInspiration_doesNotUpdatesStartOfcurrentBreathCycle,"startVentilation_duringInspiration_doesNotUpdatesStartOfcurrentBreathCycle");
  test(startVentilation_duringInspiration_doesNotChangeVentilationPhase,
  "startVentilation_duringInspiration_doesNotChangeVentilationPhase"),
  test(startVentilation_duringInspiration_doesNotopenInspiratoryValve, 
  "startVentilation_duringInspiration_doesNotopenInspiratoryValve");
  test(getCircuitPressure_validValues_returnsMeanPressure,
      "getCircuitPressure_validValues_returnsMeanPressure");


  int result = print_result();
  return !result;
}
