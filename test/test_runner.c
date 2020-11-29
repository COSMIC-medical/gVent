#include "ventilation_test.h"
#include "test_util.h"

int main(int argc, char **argv) {
  test(getCircuitPressure_validValues_returnsMeanPressure,
       "getCircuitPressure_validValues_returnsMeanPressure");
  test(startInspiration_afterOneInspiration_openInspiratoryValve,
       "startInspiration_afterOneInspiration_openInspiratoryValve");
  test(startExpiration_afterOneInspiration_closeInspiratoryValve,
       "startExpiration_afterOneInspiration_closeInspiratoryValve");
  test(startInspiration_afterOneInspiration_setsVentilationPhaseToInspiration,
       "startInspiration_afterOneInspiration_setsVentilationPhaseToInspiration");
  test(startExpiration_afterOneInspiration_opensExpiratoryValve,
       "startExpiration_afterOneInspiration_opensExpiratoryValve");
  test(startInspiration_afterTwoInspirations_updatesStartCurrentBreathCycle,
       "startInspiration_afterTwoInspirations_updatesStartCurrentBreathCycle");
  test(startExpiration_afterThreeInspiration_updatesVentilationPhase,
       "startExpiration_afterThreeInspiration_updatesVentilationPhase");
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
