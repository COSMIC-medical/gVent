/*
 * pressure_flow_sensor_private.h
 *
 * private to the platform
 */

#ifndef INC_PLATFORM_MEASURED_INPUTS_H_
#define INC_PLATFORM_MEASURED_INPUTS_H_

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


/*=========================================================================
    SENSOR PHYSICAL BOUNDS
    -----------------------------------------------------------------------
	Defines the upper and lower bounds for the FS6122 pressure and 
	flow sensor, based on the specification sheet available at 
	https://www.servoflo.com/download-archive/data-sheets/254-mass-flow-vacuum-sensors/1220-fs6122-datasheet
	or at 
	https://github.com/patchworquill/fs6122/blob/master/fs6122_datasheet.pdf

	### FS6122
	| Pin | Color | Definition | 
	| :-- | :-- | :-- |
	| 1 | White | P_out, Pressure analog sensor output
	| 2 | Green | F_out, Flow analog sensor output 
	| 3 | Black | GND, Ground
	| 4 | Red | VCC, Power supply
	| 5 | Yellow | SCL 
	| 6 | Blue | SDA 
	
=========================================================================*/

/*
* The worstcase tolerable latency (in ms) for which the sensed inputs are valid
*/
#define PRESSURE_MAXIMUM_LATENCY 1000
#define FLOW_MAXIMUM_LATENCY 1000

/*
* The minimum latency (in ms) for the sensed inputs under which read are not necessary
*/
#define PRESSURE_MINIMUM_LATENCY 1
#define FLOW_MINIMUM_LATENCY 1

/*
 * The lower and upper bounds of validity for the sensed inputs
 * pressure bounds are given in cmH2O
 * flow  bounds are given in SLPM
 */
#define PRESSURE_LOWER_BOUND -5000
#define PRESSURE_UPPER_BOUND 40000
#define FLOW_LOWER_BOUND -250000
#define FLOW_UPPER_BOUND 250000

/*
 * The maximum change rate
 * pressure change rate given in cmH2O per second
 * flow change rate given in SLPM
 */
#define PRESSURE_MAX_CHANGE_RATE 10
#define FLOW_MAX_CHANGE_RATE 10

/* 
 * Private i2c read function for the FS6122 sensor
 * first byte is the i2c sensor address
 * second byte is the flow/pressure/temp/RH select byte
 */

uint32_t read_FS6122_sensor(uint8_t, uint8_t);

/**
 * Definition of the measured inputs data structure
 */
typedef struct MeasurementsStatus {
	/**
	 * The last read value for the inspiratory pressure
	 */
	int inspiratory_pressure;
	/*
	 * the time at which the above inspiratory pressure was read
	 */
	int last_inspiratory_pressure_read_time;

	/*
	 * The last read value for the expiratory pressure
	 */
	int expiratory_pressure;
	/*
	* the time at which the above expiratory pressure was read
	*/
	int last_expiratory_pressure_read_time;

	/*
	* The last read value for the inspiratory flow
	*/
	int inspiratory_flow;
	/*
	* the time at which the above inspiratory flow was read
	*/
	int last_inspiratory_flow_read_time;

	/*
	* The last read value for the expiratory flow
	*/
	int expiratory_flow;
	/*
	 * the time at which the above expiratory flow was read
	*/
	int last_expiratory_flow_read_time;
} measurements_status_t;


#endif /* INC_PLATFORM_MEASURED_INPUTS_H_ */
