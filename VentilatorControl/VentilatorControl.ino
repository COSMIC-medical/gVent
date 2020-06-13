#include <Wire.h>
#include "fs6122.h"
#include <LiquidCrystal_I2C.h>

//pinout:
//D2 = valve
//D3 = Mode switch, low = time, high = trigger
//D4 = start switch
//A0 = breaths per minute in time mode, maximum time before inhale in triggered mode
//A1 = ratio in time mode, pressure threshold for starting inhale in triggered mode
//A2 = disabled in time mode, exhale time in triggered mode


//note: Solenoid valve is normally closed i.e when unpowered air flows inlet -> outlet
//and when powered flows outlet -> exhaust


//correct values
int valve = 2;
int modeSwitch = 3;
int startButton = 4;
int pots[] = {
  A0,  // bpm/[max time before inhale]
  A1  // ratio/[pressure threshold]
  
}; // [exhale time]
int potValues[] = {0, 0, 0};
byte disp = 0x27;
byte inspiratorySensor = 0x01;
byte expiratorySensor = 0x02;


//Constants
#define MS_PER_MINUTE 60000.0
#define NUM_POTS 2
#define MIN_BPM  5
#define MAX_BPM  41
#define MIN_RATIO  1
#define MAX_RATIO 6
#define MIN_THRESHOLD  -4
#define MAX_THRESHOLD  -1
#define MIN_OUT_TIME  750
#define MAX_OUT_TIME  6000
#define MIN_IN_TIME  750
#define MAX_IN_TIME  6000
#define DEBOUNCE_DELAY 250
#define INSPIRATORY_HIGH_PRESSURE_MULTIPLIER 1.1
#define INSPIRATORY_LOW_PRESSURE_MULTIPLIER 0.9

#define AVG_PRESSURE_ARR_SECONDS 60
#define AVG_PRESSURE_PER_SECOND 1
#define AVG_PRESSURE_ARR_LENGTH AVG_PRESSURE_ARR_SECONDS*AVG_PRESSURE_PER_SECOND
#define AVG_FR_ARR_SECONDS 60
#define AVG_FR_PER_SECOND 1
#define AVG_FR_ARR_LENGTH AVG_FR_ARR_SECONDS*AVG_FR_PER_SECOND


//Control variables
int pThreshold = -2; //cmH2O
double ratio = 1;
boolean mode = false; //false = triggered, true = timed
double BPM = 5;
double targetPressure = 15;

//other
int exhale = HIGH; //HIGH = exhale, LOW = inhale
unsigned long halfTime = MS_PER_MINUTE / (BPM); // ms per inhale/exhale = 2x cycle time
unsigned long currStart = 0; // for timekeeping
unsigned long lastPress = 0; // for button debouncing
unsigned long intervalTime = 0; // for tidal volume calculation
boolean started = false;
unsigned long inTime = halfTime;
unsigned long outTime = halfTime;

//Inspiratory Arm
float inspiratoryPressure = 0;
float inspiratoryFlowRate = 0;

//Expiratory Arm
float expiratoryPressure = 0;
float expiratoryFlowRate = 0;
float inspiratoryTidalVolume = 0.0;
float expiratoryTidalVolume = 0.0;

//Combination values
float iFlow = 0; //inspiratory flow - expiratory flow
float eFlow = 0; //expiratory flow - inspiratory flow
float avgPressure = 0; // avg(inspiratory pressure, expiratory pressure);

//Rolling averages
float rolling_avg_pressure = 0; //avg pressure over the past 60s
float rolling_avg_expiratory_fr = 0; //avg expiratory flow rate over the past 60s
float actualMinuteVentilation = 0; //volume expired over last 60s

//I2C devices
fs6122 inspiratoryFs = fs6122();
fs6122 expiratoryFs = fs6122();
LiquidCrystal_I2C lcd(disp, 16, 2);

void setup() {

  if (! inspiratoryFs.begin(inspiratorySensor)) {
    Serial.println("Couldnt start inspiratory arm sensor");
    while (1);
  }
  if (! expiratoryFs.begin(expiratorySensor)) {
    Serial.println("Couldnt start expiratory arm sensor");
    while (1);
  }
  lcd.init();
  lcd.backlight();
  pinMode(modeSwitch, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(valve, OUTPUT);
  digitalWrite(valve, HIGH);

  for (int i = 0; i < NUM_POTS; i++) {
    potValues[i] = analogRead(pots[i]);
  }
  calcTimes();
  Serial.begin(9600);
}

void loop() {
  checkSwitches();
  checkPots();
  checkSensors();
  if (started) {
    calcTidalVolume();
    intervalTime = millis();
    if (mode) {
      unsigned long tempTime = exhale ? outTime : inTime;
      if ((millis() - currStart) >= tempTime) {
        switchState(exhale = exhale ? LOW : HIGH);
        currStart = millis();
      }
    } else {//in triggered mode, we have a minimum BPM timer that is overridden by patient breathing
      if (exhale) { //during exhale, we wait for a pressure drop below threshold
        if (expiratoryPressure <= pThreshold || (millis() - currStart) >= outTime) { //if below the threshold or the timer has expired
          exhale = LOW;
          switchState(exhale);
          currStart = millis();
        }
      } else { //on inhale we use timing
        if ((millis() - currStart) >= inTime) {
          exhale = HIGH;
          switchState(exhale);
          currStart = millis();
        }
      }
    }
    delay(10);
  }
}

void switchState(int currState) { //currState = true if exhaling, false if inhaling
  digitalWrite(valve, !currState);
  if (currState) { //If transitioning from inhale to exhale
    expiratoryTidalVolume = 0;
  } else {
    inspiratoryTidalVolume = 0;
  }
}

void calcTidalVolume() {
  if (exhale) {
    expiratoryTidalVolume += expiratoryFs.flow_rate_slpm * (intervalTime / MS_PER_MINUTE);
  } else {
    inspiratoryTidalVolume += expiratoryFs.flow_rate_slpm * (intervalTime / MS_PER_MINUTE);
  }
}

void calcTimes() {
  halfTime = MS_PER_MINUTE / (BPM);
  inTime = halfTime / (1 + ratio);
  outTime = halfTime / (1.0 / ratio + 1);
}

void reset() {
  exhale = HIGH;
  currStart = 0;
  intervalTime = 0;
  started = false;
}

void showStart() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting.");
  lcd.setCursor(9, 0);
  delay(1000);
  lcd.print(".");
  lcd.setCursor(10, 0);
  lcd.print(".");
  refreshScreen(true);
}

void checkSwitches() {
  //switch priority: on/off, mode
  if (digitalRead(startButton) == LOW && (millis() - lastPress) > DEBOUNCE_DELAY) {
    Serial.println("switch");
    if (started) {
      reset();
      refreshScreen(false);
    } else { //start everything up
      Serial.println("started");
      started = true;
      showStart();
      currStart = millis();
      intervalTime = currStart;
    }
    lastPress = millis();
  }

  //if (digitalRead(modeSwitch) != mode) { //state change
  //  mode = digitalRead(modeSwitch);
   // reset();
 // }

}

void checkSensors() {
  inspiratoryFs.read_flowrate_pressure();
  expiratoryFs.read_flowrate_pressure();
  inspiratoryPressure = inspiratoryFs.pressure_cmh2o;
  inspiratoryFlowRate = inspiratoryFs.flow_rate_slpm;
  expiratoryPressure = expiratoryFs.pressure_cmh2o;
  expiratoryFlowRate = expiratoryFs.flow_rate_slpm;
  iFlow = inspiratoryFlowRate - expiratoryFlowRate;
  eFlow = expiratoryFlowRate - inspiratoryFlowRate;
  avgPressure = (inspiratoryPressure + expiratoryPressure) / 2.0;
  rolling_avg_pressure = update_rolling_avg_pressure(avgPressure);
  rolling_avg_expiratory_fr = update_rolling_avg_pressure(expiratoryFlowRate);
  actualMinuteVentilation = rolling_avg_expiratory_fr;
  Serial.println(expiratoryPressure);
}

void checkPots() {
  if (!started) {
    for (int i = 0; i < NUM_POTS; i++) {
      potValues[i] = analogRead(pots[i]);
    }
    
    if (mode) {
      double tempBPM = map(potValues[0], 0, 1024, MIN_BPM, MAX_BPM);
      double tempRatio = map(potValues[1], 0, 1024, MIN_RATIO, MAX_RATIO);
      if (tempBPM != BPM) {
        BPM = tempBPM;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BPM: ");
        lcd.setCursor(5, 0);
        lcd.print(BPM);
        calcTimes();
        return;
      }
      if (tempRatio != ratio) {
        ratio = tempRatio;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("I:E Ratio: 1:");
        lcd.setCursor(13, 0);
        lcd.print(ratio);
        calcTimes();
        return;
      }
    } else {
      double tempInTime = map(potValues[0], 0, 1024, MIN_IN_TIME, MAX_IN_TIME);
      double tempOutTime = map(potValues[1], 0, 1024, MIN_OUT_TIME, MAX_OUT_TIME);
      //double tempThreshold = map(potValues[0], 0, 1024, MIN_THRESHOLD, MAX_THRESHOLD);
      if (tempInTime != inTime) {
        inTime = tempInTime;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("In Time: ");
        lcd.setCursor(9, 0);
        lcd.print(inTime);
      }
      if (tempOutTime != outTime) {
        inTime = tempInTime;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Out Time: ");
        lcd.setCursor(10, 0);
        lcd.print(outTime);
      }
      /*
      if (tempThreshold != pThreshold) {
        pThreshold = tempThreshold;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Threshold: ");
        lcd.setCursor(11, 0);
        lcd.print(pThreshold);
      }
      */

    }
  }
}

/*
 * updates a rolling average array and calculates a new rolling average
 */
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

/*
 * updates the average pressure rolling array and value
 */
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

/*
 * updates the average flowrate rolling array and value
 */
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

void refreshScreen(boolean on) {
  delay(50);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VENTILATOR ");
  lcd.print(on ? "ON" : "OFF");
  if (on) {
    lcd.blink();
  }
}

// Issue #6
/*
void checkAlarms() {
  //I'm using MAX_THRESHOLD as a placeholder for the maximum threshold for each alarm. I'm not sure what these values are.
  //Fi02/peep - not sure where these are calculated.
  // 1. High/low peak pressure: Highest pressure measured in one breath cycle exceeds x.
  if (fs.pressure_cmh2o > MAX_THRESHOLD || fs.pressure_cmh2o < MIN_THRESHOLD) {
    soundAlarm();
  }
  if (tidal_volume > MAX_THRESHOLD || tidal_volume < MIN_THRESHOLD) {
    soundAlarm();
  }
  if (tidal_volume * BPM > MAX_THRESHOLD || tidal_volume * BPM < MIN_THRESHOLD) {
    soundAlarm();
  }
  if (Fi02 > MAX_THRESHOLD || Fi02 < MIN_THRESHOLD) {
    soundAlarm();
  }
  if (peep > MAX_THRESHOLD || peep < MIN_THRESHOLD) {
    soundAlarm();
  }

  // TODO: need volume.value to make these alarms
  // 2. High/low VT: Total exhaled volume in one breath is under/over x
  // 3. High/low Minute Ventilation: Total exhaled volume in one minute is overunder x

  // 4. Low RR: I wouldnt worry about this
  // 5. High/low Fi02: The oxygen concentration measured at the sensor is above/below x
  // 6. High/low PEEP:
  // 7. Apnea alarm with backup rate and tidal volume: We already have this coded for I believe. If the patient is on patient triggeredventilation and doesn't breathe on their own in longer than x, the ventilator gives an automatic breath.
  // 8. Disconnection alarm

}

  void soundAlarm() {
    // flashLED()
    // refreshScreen(alarmMode)
    // buzzer()
  }
  */
