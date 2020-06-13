#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define AVG_PRESSURE_ARR_SECONDS 10
#define AVG_PRESSURE_PER_SECOND 1
#define AVG_PRESSURE_ARR_LENGTH AVG_PRESSURE_ARR_SECONDS*AVG_PRESSURE_PER_SECOND

#define AVG_FR_ARR_SECONDS 10
#define AVG_FR_PER_SECOND 1
#define AVG_FR_ARR_LENGTH AVG_FR_ARR_SECONDS*AVG_FR_PER_SECOND

void assert(float val1, float val2){
  static unsigned int success = 0;
  static unsigned int fail = 0;
  float diff = val2 - val1;
  diff = diff < 0? diff : -1*diff;
  if(diff < 0.00001){
    success++;
  }
  else{
    fail++;
    printf("%f doesn't equal %f\n", val1, val2);
  }
  printf("%u successes, %u failures\n", success, fail);
}

unsigned int millis(){
  return int(1000*clock()/(1.0*CLOCKS_PER_SEC));
}

void wait(unsigned wait_time){
  unsigned int start = millis();
  while(millis()-start < wait_time){}
}

float update_rolling_avg(float new_val, float arr[], unsigned int* arr_index,
  unsigned int arr_length, bool* arr_filled, float* avg_sum, unsigned int* avg_count,
  unsigned int period, unsigned long* last_compute){
  if(!(*last_compute)){ // adjust for wait before first value
    *last_compute = millis();
  }
  *avg_sum += new_val;
  (*avg_count)++;

  // add new entry to array every second
  if (millis() - *last_compute >= period){
    *last_compute += period;
    arr[*arr_index] = *avg_sum/(*avg_count);

    // the following block of code backfills the array to compensate for very long missed periods
    while(millis() - *last_compute >= period){
      *arr_index = (*arr_index + 1) % arr_length;
      arr[*arr_index] = *avg_sum/(*avg_count);
      *last_compute += period;
    }

    *avg_sum = 0;
    *avg_count = 0;
    (*arr_index)++;

    if (*arr_index == arr_length){ // restart array and raise flag tat array has been populated
      *arr_filled = true;
      *arr_index = 0;
    }

    // calculate average of last 60s (or since start of measurements if it's been less than 60s)
    float total_avg; // the average of the values in the array
    if(*arr_filled){
      float total_sum = 0;
      for(int i = 0; i < arr_length; i++){
        total_sum += arr[i];
      }
      total_avg = total_sum/arr_length;
    }
    else{
      float total_sum = 0;
      for(int i = 0; i < *arr_index; i++){
        total_sum += arr[i];
      }
      total_avg = total_sum/(*arr_index);
    }
    return total_avg;
  }
  float ret_val;
  if(!(*arr_filled)&&(*arr_index==0)){
    return (*avg_sum/float(*avg_count));
  }
  return -1.0;
}

float update_rolling_avg_pressure(float new_val){
  static float avg_pressure_arr[AVG_PRESSURE_ARR_LENGTH]; // circular array containing pressure values
  static unsigned int arr_index = 0; // the index of the array head
  static bool arr_filled = false; // whether or not the array has been fully populated

  static float avg_sum = 0;
  static unsigned int avg_count = 0;
  static float avg_pressure = 0;
  static unsigned long* last_compute = (unsigned long*) calloc(0, sizeof(unsigned long));

  float ret_val = update_rolling_avg(new_val, avg_pressure_arr, &arr_index, AVG_PRESSURE_ARR_LENGTH, &arr_filled, &avg_sum, &avg_count, AVG_PRESSURE_PER_SECOND*1000, last_compute);
  if (ret_val > 0.0){
    avg_pressure = ret_val;
  }
  return avg_pressure;
}

float update_rolling_avg_flowrate(float new_val){
  static float avg_fr_arr[AVG_FR_ARR_LENGTH]; // circular array containing flow rate values
  static unsigned int arr_index = 0; // the index of the array head
  static bool arr_filled = false; // whether or not the array has been fully populated

  static float avg_sum = 0;
  static unsigned int avg_count = 0;
  static float avg_fr = 0;
  static unsigned long* last_compute = (unsigned long*) calloc(0, sizeof(unsigned long));

  float ret_val = update_rolling_avg(new_val, avg_fr_arr, &arr_index, AVG_FR_ARR_LENGTH, &arr_filled, &avg_sum, &avg_count, AVG_FR_PER_SECOND*1000, last_compute);
  if (ret_val > 0.0){
    avg_fr = ret_val;
  }
  return avg_fr;
}

int main(){
  float avg_pressure;
  avg_pressure = update_rolling_avg_pressure(1.0);
  assert(avg_pressure, 1.0);
  avg_pressure = update_rolling_avg_pressure(2.5);
  assert(avg_pressure, 1.75);
  wait(1000);
  avg_pressure = update_rolling_avg_pressure(2.5); // 2/1
  assert(avg_pressure, 2.0);
  wait(1000);
  avg_pressure = update_rolling_avg_pressure(3); // 5/2
  assert(avg_pressure, 2.5);
  wait(2000);
  avg_pressure = update_rolling_avg_pressure(3.5); // 12/4
  assert(avg_pressure, 3.0);
  wait(500);
  avg_pressure = update_rolling_avg_pressure(6);
  assert(avg_pressure, 3.0);
  wait(500);
  avg_pressure = update_rolling_avg_pressure(4); // 17/5
  assert(avg_pressure, 17.0/5);
  wait(500);
  avg_pressure = update_rolling_avg_pressure(0.5);
  assert(avg_pressure, 17.0/5);
  wait(600);
  avg_pressure = update_rolling_avg_pressure(1.5); // 18/6
  assert(avg_pressure, 3.0);
  wait(900);
  avg_pressure = update_rolling_avg_pressure(6.5); // 24.5/7
  assert(avg_pressure, 3.5);
  wait(1000);
  avg_pressure = update_rolling_avg_pressure(3.5); // 28/8
  assert(avg_pressure, 3.5);
  wait(1000);
  avg_pressure = update_rolling_avg_pressure(3.5); // 31.5/9
  assert(avg_pressure, 3.5);
  wait(1000);
  avg_pressure = update_rolling_avg_pressure(3.5); // 35/10
  assert(avg_pressure, 3.5);
  wait(1000);
  avg_pressure = update_rolling_avg_pressure(3.5); // 36.5/10
  assert(avg_pressure, 3.65);
  wait(1000);
  avg_pressure = update_rolling_avg_pressure(1.5); // 35/10
  assert(avg_pressure, 3.5);
  wait(1000);
  avg_pressure = update_rolling_avg_pressure(4.0); // 35.5/10
  assert(avg_pressure, 3.55);
  wait(9000);
  avg_pressure = update_rolling_avg_pressure(4.1); // 40.9/10
  assert(avg_pressure, 4.09);

  float avg_fr;
  avg_fr = update_rolling_avg_flowrate(1.0);
  assert(avg_fr, 1.0);
  avg_fr = update_rolling_avg_flowrate(2.5);
  assert(avg_fr, 1.75);
  wait(1000);
  avg_fr = update_rolling_avg_flowrate(2.5); // 2/1
  assert(avg_fr, 2.0);
  wait(1000);
  avg_fr = update_rolling_avg_flowrate(3); // 5/2
  assert(avg_fr, 2.5);
  wait(2000);
  avg_fr = update_rolling_avg_flowrate(3.5); // 12/4
  assert(avg_fr, 3.0);
  wait(500);
  avg_fr = update_rolling_avg_flowrate(6);
  assert(avg_fr, 3.0);
  wait(500);
  avg_fr = update_rolling_avg_flowrate(4); // 17/5
  assert(avg_fr, 17.0/5);
  wait(500);
  avg_fr = update_rolling_avg_flowrate(0.5);
  assert(avg_fr, 17.0/5);
  wait(600);
  avg_fr = update_rolling_avg_flowrate(1.5); // 18/6
  assert(avg_fr, 3.0);
  wait(900);
  avg_fr = update_rolling_avg_flowrate(6.5); // 24.5/7
  assert(avg_fr, 3.5);
  wait(1000);
  avg_fr = update_rolling_avg_flowrate(3.5); // 28/8
  assert(avg_fr, 3.5);
  wait(1000);
  avg_fr = update_rolling_avg_flowrate(3.5); // 31.5/9
  assert(avg_fr, 3.5);
  wait(1000);
  avg_fr = update_rolling_avg_flowrate(3.5); // 35/10
  assert(avg_fr, 3.5);
  wait(1000);
  avg_fr = update_rolling_avg_flowrate(3.5); // 36.5/10
  assert(avg_fr, 3.65);
  wait(1000);
  avg_fr = update_rolling_avg_flowrate(1.5); // 35/10
  assert(avg_fr, 3.5);
  wait(1000);
  avg_fr = update_rolling_avg_flowrate(4.0); // 35.5/10
  assert(avg_fr, 3.55);
  wait(9000);
  avg_fr = update_rolling_avg_flowrate(4.1); // 40.9/10
  assert(avg_fr, 4.09);

  printf("test\n");
}
