/*
 * dss.c
 *
 */

#include "application/dss.h"
#include "platform/system_status.h"
#include "platform/scheduler.h"

void dss() {

  // TODO - implement valve control for DSS based on SRS.

  // TODO - enable required alarms for DSS based on the SRS.

  while (1) {
    // Spin in a loop while rapidly blinking the status LED 
    // to indicate that the system is in DSS.
    set_system_status_on();
    delay_ms(200);
    set_system_status_off();
    delay_ms(200);
  }

}
