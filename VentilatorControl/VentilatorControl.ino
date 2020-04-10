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
int pots[] = {
  A0,  // bpm/[max time before inhale]
  A1,  // ratio/[pressure threshold]
  A2}; // [exhale time]
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

void loop() {
  checkSwitches();
  checkPots();
  fs.read_flowrate_pressure(); // reads to flow_rate_slpm, pressure_cmh2o
  if (started) {
    if (mode) {
      unsigned long tempTime = exhale ? outTime : inTime;
      if ((millis() - currStart) >= tempTime) {
        digitalWrite(valve, exhale = exhale ? LOW : HIGH);
        currStart = millis();
      }
    } else {//in triggered mode, we have a minimum BPM timer that is overridden by patient breathing
      if (exhale) { //during exhale, we wait for a pressure drop below threshold
        if (fs.pressure_cmh2o <= pThreshold || (millis() - currStart) >= outTime) { //if below the threshold or the timer has expired
          digitalWrite(valve, HIGH);
          currStart = millis();
        }
      } else { //on inhale we use timing
        if ((millis() - currStart) >= inTime) {
          digitalWrite(valve, LOW);
          currStart = millis();
        }
      }
    }
    delay(10);
  }
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

// Issue #6
void checkAlarms() {
  // 1. High/low peak pressure: Highest pressure measured in one breath cycle exceeds x.
  if (fs.pressure_cmh2o > MAX_THRESHOLD || fs.pressure_cmh2o < MIN_THRESHOLD){
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

void soundAlarm(){
  // flashLED()
  // refreshScreen(alarmMode)
  // buzzer()
}
