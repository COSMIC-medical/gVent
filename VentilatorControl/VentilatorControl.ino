#include <Wire.h>
#include <fs6122.h>
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
float actualMinuteVentilation = 0; //volume expired over last 60s

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
  
 PressureSensorErrorAlarm() ;  //New => Date: 05/31/2020
}

  void soundAlarm() {
    // flashLED()
    // refreshScreen(alarmMode)
    // buzzer()
  }
  */
/* Date:05/31/2020 
=>Pressure Sensor Error Alarm Function
Notes: Not sure if I am reading both sensors A and B correctly. 
       Maybe I should use avgPressure for the readings value? 
*/
/*
void PressureSensorErrorAlarm(){   //issue#34
  //Pressure readings in sensor a >1.2 or <0.8 pressure readings in sensor b 
  //- excluding parameters meeting criteria for another alarm below.
//read Sensor A and Sensor B
  checkSensors(); //Check Sensors (Same with reading sensors)
  checkPots();  //now we got the potValues[1] which should contain A1 pressure threshold value
  double readings= potValues[1]; 
if(readings>1.2 || readings <0.8) 
  soundAlarm();
}
*/
