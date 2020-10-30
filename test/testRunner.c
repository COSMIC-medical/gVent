#include "ventilation-test.h"
#include "testUtil.h"

int main(int argc, char **argv) {
  //test(addition, "addition");
  test(startVentilation_openInspiratoryValve, "startVentilation_openInspiratoryValve");
  test(startVentilation_doesNotopenInspiratoryValve, "startVentilation_doesNotopenInspiratoryValve");
    
}


