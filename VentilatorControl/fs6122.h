#ifndef _FS6122_H_
#define _FS6122_H_

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>

/*=========================================================================
    I2C ADDRESS/BITS
    -----------------------------------------------------------------------*/
    #define FS6122_DEFAULT_ADDRESS                 (0x1D)
/*=========================================================================*/

/////////////////////////////////////
// Hex Byte Commands for fs6122
// WRITE COMMANDS
#define FS6122_WRITE_ADDRESS            0x05 // write the i2c address, Bit7 ~ Bit1 can be set in hex (0x08 means address of 4)
#define FS6122_WRITE_FILTERDEPTH        0x0B // write the filter depth Int8, 0-254
#define FS6122_CAL_FLOWRATE_OFFSET      0x1C // calibration the offset of the flow rate, 1 byte, any value, ensure NO flow in the pipe
#define FS6122_CAL_PRESSURE_OFFSET      0x24 // calibration of offset of pressure, 1 byte, any value, ensure NO flow in the pipe

// READ COMMANDS
#define FS6122_READ_SENSOR_SN           0x82 // ASCII
#define FS6122_READ_FLOWRATE            0x83 // Int32/1000 SLPM
#define FS6122_READ_FLOWRATE_PRESSURE   0x84 // Int32/1000 SLPM, int32/1000 cmH20

#define FS6122_READ_ADDRESS             0x85 // Bit7 ~ Bit1
#define FS6122_READ_FILTERDEPTH         0x8B // Int8, 0~254
#define FS6122_READ_PRESSURE            0xA3 // Int32/1000 cmH20
#define FS6122_READ_TEMPERATURE         0x82  // Int16/100 deg celcius
#define FS6122_READ_HUMIDITY            0x83  // Int16/100 %RH


class fs6122
{
 public:
  fs6122(int64_t sensorID = -1);

  bool begin(uint8_t addr = FS6122_DEFAULT_ADDRESS);

  void read_flowrate_pressure();
  void read_temperature();
  void read_humidity();

  // void setFilterDepth(fs6122_filterdepth_t filterdepth);
  // fs6122_filterdepth_t readFilterDepth(void);

  int16_t temperature, humidity;
  int32_t flow_rate, pressure;
  float flow_rate_slpm, pressure_cmh2o, temperature_c, humidity_prh;

  void writeRegister8(uint8_t reg, uint8_t value);
 protected:
  uint8_t readRegister8(uint8_t reg);
 private:
  int64_t _sensorID; // SN is 12 bytes... need int64?
  int8_t  _i2caddr;
};

#endif
