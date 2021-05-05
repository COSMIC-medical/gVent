/*
 * systemInfo_stub.c
 *
 * Stub for the function get_current_time
 */

#include <stdlib.h>
#include <string.h>

static int* time_to_return;
static int current_call = 0;

void set_current_time(int* times){
  time_to_return = times;
  current_call = 0;
}

int get_current_time(){
  current_call ++;
  return time_to_return[current_call-1];
}

