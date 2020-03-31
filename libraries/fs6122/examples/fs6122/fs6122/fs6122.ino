// FS6122 Test Sketch
// by Patrick Wilkie <http://github.com/patchworquill>

// Created March 30, 2020

// This example code is in the public domain.


#include <Wire.h>
#include <fs6122.h>

fs6122 fs = fs6122();

void setup() {
  //Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output

  Serial.println("FS6122 test!");
  
  if (! fs.begin()) {
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("FS6122 found!");
  
}

void loop() {

  fs.read_flowrate_pressure();
  fs.read_temperature();
  fs.read_humidity();

  Serial.print("Flow Rate:\t"); Serial.print(fs.flow_rate_slpm); Serial.print(" SLPM");
  Serial.print("Pressure:\t"); Serial.print(fs.pressure_cmh2o); Serial.print(" cmH2O");
  Serial.print("Temperature:\t"); Serial.print(fs.temperature_c); Serial.print(" •C");
  Serial.print("Humidity:\t"); Serial.print(fs.humidity_prh); Serial.print(" %RH");
  Serial.println();
  
  delay(500);
}
