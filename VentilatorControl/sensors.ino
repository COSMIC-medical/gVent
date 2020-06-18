/*
 * This acts as a wrapper for the flow sensors by 
 * reading data from sensors into output data. 
*/
#include <fs6122.h>

//Constants
#define MS_PER_MINUTE 60000.0

// sensor addresses 
byte inspiratorySensor = 0x01;
byte expiratorySensor = 0x02;

//I2C devices
fs6122 inspiratoryFs = fs6122();
fs6122 expiratoryFs = fs6122();

/* 
 * This function initializes both the inspiratory and
 * expiratory flow sensors and outputs an error if a problem 
 * is encountered
 */
void initSensors(){ 

    // if begin method fails, output error 
    if (! inspiratoryFs.begin(inspiratorySensor)) {
        Serial.println("Couldnt start inspiratory arm sensor");
        while (1); // halts process if either sensor is down 
    }
    if (! expiratoryFs.begin(expiratorySensor)) {
        Serial.println("Couldnt start expiratory arm sensor");
        while (1);
    }
}

/* 
 * Reads sensor data into signals used for state transitions 
 * and alarms. 
 */
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

/* 
 *  Calculates flow volume per inhale or per exhale 
 *  by summing net flow over a time interval. 
 */
void calcTidalVolume() {
    if (exhale) {
        expiratoryTidalVolume += expiratoryFs.flow_rate_slpm * (intervalTime / MS_PER_MINUTE);
    } else {
        inspiratoryTidalVolume += expiratoryFs.flow_rate_slpm * (intervalTime / MS_PER_MINUTE);
    }
}

/*
 * This function performs inhale/exhale state transition 
 */ 
void switchState(int currState) { //currState = true if exhaling, false if inhaling
  digitalWrite(valve, !currState);
  if (currState) { //If transitioning from inhale to exhale
    expiratoryTidalVolume = 0;
  } else {
    inspiratoryTidalVolume = 0;
  }
}
	
