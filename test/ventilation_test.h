/*
 * ventilation_test.h
 *
 */

int startVentilation_afterOneInspiration_openInspiratoryValve();

int startVentilation_duringInspiration_doesNotopenInspiratoryValve();

int startVentilation_afterOneInspiration_setsVentilationPhaseToInspiration();

int startVentilation_duringInspiration_doesNotChangeVentilationPhase();

int startVentilation_afterTwoInspirations_updatesStartCurrentBreathCycle();

int startVentilation_duringInspiration_doesNotUpdatesStartOfcurrentBreathCycle();

int getCircuitPressure_validValues_returnsMeanPressure();
