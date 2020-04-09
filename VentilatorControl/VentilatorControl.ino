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

//placeholders
byte sensor = 0xAA;


//correct values
int valve = 2;
int modeSwitch = 3;
int startButton = 4;
int pots[] = {A0, A1, A2}; // bpm/[max time before inhale], ratio/[pressure threshold], [exhale time]
int potValues[] = {0, 0, 0};
byte disp = 0x27;


//Constants
#define NUM_POTS 3
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




//Control variables
int pThreshold = -2; //cmH2O
double ratio = 1;
boolean mode = true; //false = timed, true = triggered
double BPM = 30;

//other
int exhale = HIGH; //HIGH = exhale, LOW = inhale
unsigned long halfTime = 60000.0 / (BPM); // ms per inhale/exhale = 2x cycle time
unsigned long currStart = 0; // for timekeeping
unsigned long lastPress = 0; // for button debouncing
boolean started = false;
unsigned long inTime = halfTime;
unsigned long outTime = halfTime;
unsigned long tidal_volume = 0.0;
unsigned long time_inverval = 10.0; // interval which loop checks itself
unsigned long tidal_volumes[100]; // array storing tidal volumes for inhale/exhale
int count = 0; //determining the full cycle for the tidal volume function
int n = 0; // array spot for storing tidal volumes

//I2C devices
fs6122 fs = fs6122();
LiquidCrystal_I2C lcd(disp, 16, 2);

void setup() {

  if (! fs.begin(sensor)) {
    Serial.println("Couldnt start");
    while (1);
  }

  lcd.init();
  lcd.backlight();
  pinMode(modeSwitch, INPUT_PULLUP);
  pinMode(startButton, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  digitalWrite(valve, HIGH);

  for (int i = 0; i < NUM_POTS; i++) {
    potValues[i] = analogRead(pots[i]);
  }
  calcTimes();
  Serial.begin(9600);
}

void calcTimes() {
  halfTime = 60000.0 / (BPM);
  inTime = halfTime / (1 + ratio);
  outTime = halfTime / (1.0 / ratio + 1);
}

void reset() {
  exhale = HIGH;
  currStart = 0;
  started = false;
  refreshScreen(false);
}

void showStart() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Starting.");
  lcd.setCursor(9, 0);
  delay(500);
  lcd.print(".");
  lcd.setCursor(10, 0);
  lcd.print(".");
  refreshScreen(true);
}

void checkSwitches() {
  //switch priority: on/off, mode
  if (digitalRead(startButton) == LOW && (millis() - lastPress) > DEBOUNCE_DELAY) {
    Serial.println("starting");
    if (started) {
      reset();
    } else { //start everything up
      Serial.println("started");
      started = true;
      showStart();
      currStart = millis();
    }
    lastPress = millis();
  }

  if (digitalRead(modeSwitch) != mode) { //state change
    mode = digitalRead(modeSwitch);
    reset();
  }

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
        Serial.println("change in bpm");
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
        Serial.println("change in ratio");
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
      double tempOutTime = map(potValues[0], 0, 1024, MIN_OUT_TIME, MAX_OUT_TIME);
      double tempThreshold = map(potValues[0], 0, 1024, MIN_THRESHOLD, MAX_THRESHOLD);
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
      if (tempThreshold != pThreshold) {
        pThreshold = tempThreshold;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Threshold: ");
        lcd.setCursor(11, 0);
        lcd.print(pThreshold);
      }

    }
  }
}

void refreshScreen(boolean on) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VENTILATOR " + on ? "ON" : "OFF");
  if (on) {
    lcd.blink();
  }
}

void checkAlarms() {

}

// this function stores the tidal volume by taking the instantaneous flowrate at 10ms time intervals
void tidalVolume() {
  if (count > 2) { // ** when the count reaches 2 it indicates that the system has hit inhale and exhale
    tidal_volumes[n] = tidal_volume;
    tidal_volume = 0; //resets tidal volume
    n++; //move onto next spot
  }
  fs.read_flowrate_pressure();
  tidal_volume += fs.flow_rate_cmh2o*time_interval;
}

void loop() {
  checkSwitches();
  checkPots();
  fs.read_flowrate_pressure();
  if (started) {
    if (mode) {
      unsigned long tempTime = exhale ? outTime : inTime;
      if ((millis() - currStart) >= tempTime) {
        count++;
        digitalWrite(valve, exhale = exhale ? LOW : HIGH);
        currStart = millis();
      }
    } else {//in triggered mode, we have a minimum BPM timer that is overridden by patient breathing
      if (exhale) { //during exhale, we wait for a pressure drop below threshold
        if (fs.pressure_cmh2o <= pThreshold || (millis() - currStart) >= outTime) { //if below the threshold or the timer has expired
          count++;
          digitalWrite(valve, HIGH);
          currStart = millis();
        }
      } else { //on inhale we use timing
        if ((millis() - currStart) >= inTime) {
          count++;
          digitalWrite(valve, LOW);
          currStart = millis();
        }
      }
    }
    tidalVolume();
    delay(10);
  }
}
