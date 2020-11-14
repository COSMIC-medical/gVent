/*
 * clinician_info_stub.c
 *
 * Stub for the function that retreive the clinician inputs
 */

#include <stdlib.h>
#include <string.h>
#include "platform/common.h"

static uint32_t* RR_to_return;
static status_t* status_to_return;
static int current_call = 0;



void set_respiratory_rate(uint32_t* RR, status_t* status, size_t size){
  free(RR_to_return);
  free(status_to_return);
  RR_to_return = (uint32_t*) malloc(sizeof(*RR) * size);
  status_to_return = (status_t*) malloc(sizeof(*status) * size);
  memcpy(RR_to_return, RR, sizeof(*RR) * size);
  memcpy(status_to_return, status, sizeof(*status) * size);
  current_call = 0;
}

status_t get_respiratory_rate(uint32_t * RR) {
  current_call ++;
  *RR = RR_to_return[current_call-1];
  return status_to_return[current_call-1];
}

