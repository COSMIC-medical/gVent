#include "ventilation_test.h"
#include "test_util.h"

int main(int argc, char **argv) {
  test(startInspiration_afterOneInspiration_openInspiratoryValve,
   "startInspiration_afterOneInspiration_openInspiratoryValve");
  test(startInspiration_afterOneInspiration_setsVentilationPhaseToInspiration,
  "startInspiration_afterOneInspiration_setsVentilationPhaseToInspiration");
  test(startInspiration_afterTwoInspirations_updatesStartCurrentBreathCycle,
  "startInspiration_afterTwoInspirations_updatesStartCurrentBreathCycle");
  test(startInspiration_duringInspiration_doesNotUpdateStartOfcurrentBreathCycle,
  "startInspiration_duringInspiration_doesNotUpdateStartOfcurrentBreathCycle");
  test(startInspiration_duringInspiration_doesNotChangeVentilationPhase,
  "startInspiration_duringInspiration_doesNotChangeVentilationPhase"),
  test(startInspiration_duringInspiration_doesNotopenInspiratoryValve, 
  "startInspiration_duringInspiration_doesNotopenInspiratoryValve");
  test(getCircuitPressure_validValues_returnsMeanPressure,
      "getCircuitPressure_validValues_returnsMeanPressure");

  int result = print_result();
  return !result;
}
