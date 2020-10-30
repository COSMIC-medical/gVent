/*
 * systemInfo_stub.c
 *Stub for the function get_current_time
 *
 */

#include <stdlib.h>
#include <string.h>

int* time_to_return;
int current_call = 0;

void set_current_time(int* times){
  time_to_return = (int*) malloc(sizeof(times));
  memcpy(time_to_return, times, sizeof(times));
  int current_call = 0;
}

int get_current_time(){
  current_call ++;
  return time_to_return[current_call-1];
}

