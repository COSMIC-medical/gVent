/*
 * ventilation_test.h
 *
 */

int getCircuitPressure_validValues_returnsMeanPressure();

int startInspiration_afterOneInspiration_openInspiratoryValve();

int startInspiration_duringInspiration_doesNotopenInspiratoryValve();

int startInspiration_afterOneInspiration_setsVentilationPhaseToInspiration();

int startInspiration_duringInspiration_doesNotChangeVentilationPhase();

int startInspiration_afterTwoInspirations_updatesStartCurrentBreathCycle();

int startInspiration_duringInspiration_doesNotUpdateStartOfcurrentBreathCycle();

int startInspiration_circuitPressureTooHigh_DoesNotStartCurrentBreathCycle();
