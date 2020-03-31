// Wire Master Writer
// by Nicholas Zambetti <http://www.zambetti.com>

// Demonstrates use of the Wire library
// Writes data to an I2C/TWI slave device
// Refer to the "Wire Slave Receiver" example for use with this

// Created 29 March 2006

// This example code is in the public domain.


#include <Wire.h>

/////////////////////////////////////
// Command Bytes Hex for fs6122
// WRITE COMMANDS
#define cmd_write_address       0x05 // write the i2c address, Bit7 ~ Bit1 can be set in hex (0x08 means address of 4)
#define cmd_write_filterDepth   0x0B // write the filter depth Int8, 0-254
#define cmd_cal_offset_flowRate 0x1C // calibration the offset of the flow rate, 1 byte, any value, ensure NO flow in the pipe
#define cmd_cal_offset_pressure 0x24 // calibration of offset of pressure, 1 byte, any value, ensure NO flow in the pipe

// READ COMMANDS
#define cmd_read_sensor_SN      0x82 // ASCII
#define cmd_read_flowRate       0x83 // Int32/1000 SLPM
#define cmd_read_flowRate_pressure 0x84 // Int32/1000 SLPM, int32/1000 cmH20
#define cmd_read_i2c_address    0x85 // Bit7 ~ Bit1
#define cmd_read_filterDepth    0x8B // Int8, 0~254
#define cmd_read_pressure       0xA3 // Int32/1000 cmH20
#define cmd_read_temperature    0x82  // Int16/100 deg celcius
#define cmd_read_humidity       0x83  // Int16/100 %RH

void setup() {
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);  // start serial for output
}

byte x = 0;

void loop() {
  // WRITE
  Wire.beginTransmission(8); // transmit to device #8
  Wire.write("x is ");        // sends five bytes
  Wire.write(x);              // sends one byte
  Wire.endTransmission();    // stop transmitting

  x++;
  delay(500);

  // READ
  Wire.requestFrom(8, 6);    // request 6 bytes from slave device #8

  while (Wire.available()) { // slave may send less than requested
    char c = Wire.read(); // receive a byte as character
    Serial.print(c);         // print the character
  }

  delay(500);
}

void read_flowRate_pressure(addr) {
  Wire.beginTransmission(addr);
  // Ask for particular registers of data
//  Wire.write(cmd_read_flowRate_pressure);
  Wire.requestFrom(addr, 2);

  // read 2 bytes from
  if(Wire.available()<=2){
    X0 = Wire.read();
    X1 = Wire.read();
  }  
}
