#include "stm32f4xx_hal.h"
#include <platform/pressureFlowSensor.h>
#include <platform/pressureFlowSensor_private.h>
#include <platform/configuration_private.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint32_t read_FS6122_sensor(uint8_t i2c_addr, uint8_t reg_addr){
    HAL_StatusTypeDef ret;
    uint8_t buf[20];
    uint32_t val; 
    uint32_t I2C_TIMEOUT_DELAY = 1000; // Return after 1s if no data transmitted/received

    // Tell FS6122 which register to read from (pressure, flow, temp, RH)
    buf[0] = reg_addr;

    ret = HAL_I2C_Master_Transmit(&i2c1_bus, i2c_addr, buf, 1, I2C_TIMEOUT_DELAY);
    if ( ret != HAL_OK ) {
      strcpy((char*)buf, "Error Tx\r\n");
      val = 128;
    } 
    else {
      // Read 4 bytes from the pressure register
      ret = HAL_I2C_Master_Receive(&i2c1_bus, i2c_addr, buf, 4, I2C_TIMEOUT_DELAY);
      if ( ret != HAL_OK ) {
        strcpy((char*)buf, "Error Rx\r\n");
        val = 256;
      } 
      else {

        //Combine the bytes
        val = ((int16_t)buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | (buf[3]) >> 2; // value is 14 bit, so shift by 2
        
        // Convert pressure & flow
        // pressure_cmh2o /= 1000;
        // flow_slpm /= 1000;
        sprintf((char*)buf,
              "%li cmH2O\r\n",
              (val)
              );
      }
    }

    // Send out buffer (sensor reading or error message)
    HAL_UART_Transmit(&serial1, buf, strlen((char*)buf), HAL_MAX_DELAY);

    return val;
}

/*
 * Reads and validates the read inspiratory pressure
 * Updates the measurement inputs
 *
 * returns the inspiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 *
 */
int get_inspiratory_pressure(){
    return read_FS6122_sensor(INSPIRATORY_ADDR, FS6122_READ_PRESSURE);
    // return pressureFlowSensor.MeasurementStatus.
}

/*
 * Reads and validates the read expiratory pressure
 * Updates the measurement inputs
 *
 * returns the expiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 */
int get_expiratory_pressure(){
    return read_FS6122_sensor(EXPIRATORY_ADDR, FS6122_READ_PRESSURE);
}

/*
 * Reads and validates the read inspiratory flow
 * Updates the measurement inputs
 *
 * returns the inspiratory flow in SLPM when it is valid
 * returns SLPM when no valid flow is available
 */
int get_inspiratory_flow(){
    return read_FS6122_sensor(INSPIRATORY_ADDR, FS6122_READ_FLOWRATE);
}

/*
 * Reads and validates the read expiratory flow
 * Updates the measurement inputs
 *
 * returns the expiratory flow in SLPM when it is valid
 * returns SLPM  when no valid flow is available
 */
int get_expiratory_flow(){
    return read_FS6122_sensor(EXPIRATORY_ADDR, FS6122_READ_FLOWRATE);
}