#include "ventilation_test.h"
#include "test_util.h"

int main(int argc, char **argv) {
  test(getCircuitPressure_validValues_returnsMeanPressure,
       "getCircuitPressure_validValues_returnsMeanPressure");
  test(compute_breath_cycle_duration_RRInvalid_ReturnDefault,
       "compute_breath_cycle_duration_RRInvalid_ReturnDefault");
  test(compute_breath_cycle_duration_RRValid_ReturnCorrectValue,
       "compute_breath_cycle_duration_RRValid_ReturnCorrectValue");
  test(startInspiration_afterOneInspiration_openInspiratoryValve,
       "startInspiration_afterOneInspiration_openInspiratoryValve");
  test(startInspiration_afterOneInspiration_setsVentilationPhaseToInspiration,
       "startInspiration_afterOneInspiration_setsVentilationPhaseToInspiration");
  test(startInspiration_afterTwoInspirations_updatesStartCurrentBreathCycle,
       "startInspiration_afterTwoInspirations_updatesStartCurrentBreathCycle");
  test(startInspiration_duringInspiration_doesNotUpdateStartOfcurrentBreathCycle,
       "startInspiration_duringInspiration_doesNotUpdateStartOfcurrentBreathCycle");
  test(startInspiration_duringInspiration_doesNotChangeVentilationPhase,
       "startInspiration_duringInspiration_doesNotChangeVentilationPhase");
  test(startInspiration_duringInspiration_doesNotopenInspiratoryValve,
       "startInspiration_duringInspiration_doesNotopenInspiratoryValve");
  test(startInspiration_circuitPressureTooHigh_DoesNotStartCurrentBreathCycle,
       "startInspiration_circuitPressureToHigh_DoesNotStartCurrentBreathCycle");

  int result = print_result();
  return !result;
}
