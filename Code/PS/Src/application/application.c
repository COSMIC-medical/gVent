/*
 * application.c
 *
 */

#include <application/alarmMonitoring.h>
#include <application/dss.h>
#include <application/ventilation.h>
#include <platform/scheduler.h>
#include <platform/alarm.h>

void init_application() {
  status_t reg_suc = STATUS_OK;
  //reg_suc |= register_task("health checks", health_check, X, X, X);
  reg_suc |= register_task("alarm", alarm_monitoring, 50, 0, 5);
  reg_suc |= register_task("ventilation", ventilation, 100, 5, 10);
  //reg_suc |= register_task("clinician inputs", clinician_inputs_monitoring, X, X, X);
  if (reg_suc == STATUS_ERR) {
      dss();
  }
}
