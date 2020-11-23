/*
 * clinician_info_stub.c
 *
 * Stub for the function that retreive the clinician inputs
 */

#include <stdlib.h>
#include <string.h>
#include "platform/common.h"

static uint32_t* RR_to_return;
static status_t* status_RR_to_return;
static int RR_current_call = 0;

void set_respiratory_rate(uint32_t* RR, status_t* status, size_t size){
  free(RR_to_return);
  free(status_RR_to_return);
  RR_to_return = (uint32_t*) malloc(sizeof(*RR) * size);
  status_RR_to_return = (status_t*) malloc(sizeof(*status) * size);
  memcpy(RR_to_return, RR, sizeof(*RR) * size);
  memcpy(status_RR_to_return, status, sizeof(*status) * size);
  RR_current_call = 0;
}

status_t get_respiratory_rate(uint32_t * RR) {
  RR_current_call ++;
  *RR = RR_to_return[RR_current_call-1];
  return status_RR_to_return[RR_current_call-1];
}


static uint32_t* insp_time_to_return;
static status_t* status_insp_time_to_return;
static int insp_time_current_call = 0;

void set_selected_inspiratory_time(uint32_t* insp_times, status_t* status) {
  insp_time_to_return = insp_times;
  status_insp_time_to_return = status;
  insp_time_current_call = 0;
}

status_t get_selected_inspiratory_time(uint32_t* insp_time) {
  insp_time_current_call ++;
  *insp_time = insp_time_to_return[insp_time_current_call-1];
  return status_insp_time_to_return[insp_time_current_call-1];
}

