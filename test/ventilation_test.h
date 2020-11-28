/*
 * ventilation_test.h
 *
 */

int startVentilation_afterOneInspiration_openInspiratoryValve();

int startVentilation_duringInspiration_doesNotopenInspiratoryValve();

int getCircuitPressure_validValues_returnsMeanPressure();
