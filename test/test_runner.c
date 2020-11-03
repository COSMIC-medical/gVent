#include "ventilation_test.h"
#include "test_util.h"

int main(int argc, char **argv) {
  test(startVentilation_afterOneInspiration_openInspiratoryValve,
   "startVentilation_afterOneInspiration_openInspiratoryValve");
  test(startVentilation_duringInspiration_doesNotopenInspiratoryValve, 
  "startVentilation_duringInspiration_doesNotopenInspiratoryValve");

  int result = print_result();
  return !result;
}
