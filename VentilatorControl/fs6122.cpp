/**************************************************************************/
/*!
    @file     fs6122.cpp
    @author   Patrick Wilkie (Melt Collective)
    @license  BSD (see license.txt)

    This is a library for the FS6122 Bi-Directional Medical Respiratory Sensor
    ----> http://www.siargo.us/fs6122-mass-flow-sensor.html

    Melt Collective invests time and resources providing this open
    source code.  Please support Melt Collective and open-source
    hardware development, either directly through your contributions,
    or by buying our products and sharing our creations.

    Some code adapted from Adafruit_MMA8451 library!!! Thank you to Adafruit :)

    @section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>
#include <fs6122.h>

/**************************************************************************/
/*!
    @brief  Abstract away platform differences in Arduino wire library
*/
/**************************************************************************/
static inline uint8_t i2cread(void) {
  #if ARDUINO >= 100
  return Wire.read();
  #else
  return Wire.receive();
  #endif
}

static inline void i2cwrite(uint8_t x) {
  #if ARDUINO >= 100
  Wire.write((uint8_t)x);
  #else
  Wire.send(x);
  #endif
}

/**************************************************************************/
/*!
    @brief  Writes 8-bits to the specified destination register
*/
/**************************************************************************/
void fs6122::writeRegister8(uint8_t reg, uint8_t value) {
  Wire.beginTransmission(_i2caddr);
  i2cwrite((uint8_t)reg);
  i2cwrite((uint8_t)(value));
  Wire.endTransmission();
}


/**************************************************************************/
/*!
    @brief  Reads 8-bits from the specified register
*/
/**************************************************************************/
uint8_t fs6122::readRegister8(uint8_t reg) {

//undocumented version of requestFrom handles repeated starts on Arduino Due
#ifdef __SAM3X8E__
    Wire.requestFrom(_i2caddr, 1, reg, 1, true);
#else
    //I don't know - maybe the other verion of requestFrom works on all platforms.
    //  honestly, I don't want to go through and test them all.  Doing it this way
    //  is already known to work on everything else
    Wire.beginTransmission(_i2caddr);
    i2cwrite(reg);
    Wire.endTransmission(false); // MMA8451 + friends uses repeated start!!
    Wire.requestFrom(_i2caddr, 1); // requests 1 byte from i2c device register.
#endif

    if (! Wire.available()) return -1;
    return (i2cread());
}

/**************************************************************************/
/*!
    @brief  Instantiates a new fs6122 class in I2C mode
*/
/**************************************************************************/
fs6122::fs6122(int64_t sensorID) {
  _sensorID = sensorID;
}

/**************************************************************************/
/*!
    @brief  Setups the HW (reads coefficients values, etc.)
*/
/**************************************************************************/
bool fs6122::begin(uint8_t i2caddr) {
  Wire.begin();
  _i2caddr = i2caddr;

  writeRegister8(FS6122_WRITE_FILTERDEPTH, 0xFE); // set filter depth to maximum (254)

  return true;
}

/**************************************************************************/
/*!
    @brief  Reads flow rate and pressure
*/
/**************************************************************************/

void fs6122::read_flowrate_pressure(void) {
  // read flow rate and pressure at once
  Wire.beginTransmission(_i2caddr);
  i2cwrite(FS6122_READ_FLOWRATE_PRESSURE);
  Wire.endTransmission(false); // many devices use repeated start!!

  Wire.requestFrom(_i2caddr, 8); // request 8 bytes of data
  flow_rate = Wire.read(); flow_rate <<= 8; // shift by byte each read
  flow_rate |= Wire.read(); flow_rate <<= 8;
  flow_rate |= Wire.read(); flow_rate <<= 8;
  flow_rate |= Wire.read(); flow_rate >>= 2; // value is 14 bit, so shift by 2
  pressure = Wire.read(); pressure <<= 8;
  pressure |= Wire.read(); pressure <<= 8;
  pressure |= Wire.read(); pressure <<= 8;
  pressure |= Wire.read(); pressure >>= 2; // value is 14 bit, so shift by 2

  uint32_t divider = 1000; // divide both values by 1000 (TODO: CHECK: is this a problem, using 1024 instead?!)

  flow_rate_slpm = (float)flow_rate / divider;
  pressure_cmh2o = (float)pressure / divider;

}

void fs6122::read_temperature(void) {
  // read flow rate and pressure at once
  Wire.beginTransmission(_i2caddr);
  i2cwrite(FS6122_READ_TEMPERATURE);
  Wire.endTransmission(false); // many devices use repeated start!!

  Wire.requestFrom(_i2caddr, 2); // request 2 bytes of data
  temperature = Wire.read(); temperature <<= 8; // shift by byte each read
  temperature |= Wire.read();

  uint16_t divider = 100; // divide both values by 1000

  temperature_c = (float)temperature / divider;

}

void fs6122::read_humidity(void) {
  // read flow rate and pressure at once
  Wire.beginTransmission(_i2caddr);
  i2cwrite(FS6122_READ_HUMIDITY);
  Wire.endTransmission(false); // many devices use repeated start!!

  Wire.requestFrom(_i2caddr, 2); // request 2 bytes of data
  humidity = Wire.read(); humidity <<= 8; // shift by byte each read
  humidity |= Wire.read();

  uint16_t divider = 100; // divide both values by 1000

  humidity_prh = (float)humidity / divider;

}
