#include "stm32f4xx_hal.h"
#include "platform/sensor.h"
#include "platform/sensor_private.h"
#include "platform/configuration_private.h"
#include "platform/common.h"
#include "platform/system_info.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Declare and initialize structure variable
struct MeasurementsStatus sensor_struct = {0,0, 0,0, 0,0, 0,0,};

sensor_status_t read_FS6122_sensor(uint8_t i2c_addr, uint8_t reg_addr, uint32_t* sensor_value_ptr){
    HAL_StatusTypeDef ret;
    uint8_t buf[20]; // i2c buffer
    uint32_t val; 
    uint32_t I2C_TIMEOUT_DELAY = 100; // Return after 1/10 s if no data transmitted/received
    
    // Tell FS6122 which register to read from (pressure, flow, temp, RH)
    buf[0] = reg_addr;

    ret = HAL_I2C_Master_Transmit(&i2c1_bus, i2c_addr, buf, 1, I2C_TIMEOUT_DELAY);
    if ( ret != HAL_OK ) {
      return TRANSMIT_ERROR;
    } 
    else {
      // Read 4 bytes from the pressure register
      ret = HAL_I2C_Master_Receive(&i2c1_bus, i2c_addr, buf, 4, I2C_TIMEOUT_DELAY);
      if ( ret != HAL_OK ) {
        return RECEIVE_ERROR;
      } 
      else {
        /* 
         * Combine the bytes returned via I2C. 
         *    
         */ 
        val = ((int16_t)buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | (buf[3]) >> 2; // value is 14 bit, so shift by 2
        *sensor_value_ptr = val; // Write the value read from the sensor to the temporary pointer 
        return I2C_OK;
      }
    }

    return I2C_ERROR; // We should never get here, but if we do there's a special error
}

/*
 * Reads and validates the read inspiratory pressure
 * Updates the measurement inputs
 * 
 * Validation: 
 *      -5 ~ +40 [cmH2O]
 *
 * returns the inspiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 *
 */
status_t get_inspiratory_pressure(uint32_t * result){
    status_t sensor_status = STATUS_ERR;
    sensor_status_t i2c_read_status = I2C_ERROR;

    i2c_read_status = read_FS6122_sensor(INSPIRATORY_ADDR, FS6122_READ_PRESSURE, result);

    // write inspiratory pressure to MeasurementsStatus struct
    sensor_struct.inspiratory_pressure = *result;
    sensor_struct.last_inspiratory_pressure_read_time = get_current_time();

    if ((*result < PRESSURE_LOWER_BOUND) && (*result > PRESSURE_UPPER_BOUND) && (i2c_read_status == I2C_OK)){
      sensor_status = STATUS_OK;
    }
    return sensor_status;
}

/*
 * Reads and validates the read expiratory pressure
 * Updates the measurement inputs
 *
 * returns the expiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 */
status_t get_expiratory_pressure(uint32_t * result){
    status_t sensor_status = STATUS_ERR;
    sensor_status_t i2c_read_status = I2C_ERROR;

    i2c_read_status = read_FS6122_sensor(EXPIRATORY_ADDR, FS6122_READ_PRESSURE, result);

    sensor_struct.expiratory_pressure = *result;
    sensor_struct.last_expiratory_pressure_read_time = get_current_time();

    if ((*result > PRESSURE_LOWER_BOUND) && (*result < PRESSURE_UPPER_BOUND) && (i2c_read_status == I2C_OK))
    {
      sensor_status = STATUS_OK;
    }
    return sensor_status;
}

/*
 * Reads and validates the read inspiratory flow
 * Updates the measurement inputs
 *
 * returns the inspiratory flow in SLPM when it is valid
 * returns SLPM when no valid flow is available
 */
status_t get_inspiratory_flow(uint32_t * result){
    status_t sensor_status = STATUS_ERR;
    sensor_status_t i2c_read_status = I2C_ERROR;

    i2c_read_status = read_FS6122_sensor(INSPIRATORY_ADDR, FS6122_READ_FLOWRATE, result);

    sensor_struct.inspiratory_flow = *result;
    sensor_struct.last_inspiratory_flow_read_time = get_current_time();

    if ((*result > FLOW_LOWER_BOUND) && (*result < FLOW_UPPER_BOUND) && (i2c_read_status == I2C_OK))
    {
      sensor_status = STATUS_OK;
    }
    return sensor_status;
}

/*
 * Reads and validates the read expiratory flow
 * Updates the measurement inputs
 *
 * returns the expiratory flow in SLPM when it is valid
 * returns SLPM  when no valid flow is available
 */
status_t get_expiratory_flow(uint32_t * result){
    status_t sensor_status = STATUS_ERR;
    sensor_status_t i2c_read_status = I2C_ERROR;

    i2c_read_status = read_FS6122_sensor(EXPIRATORY_ADDR, FS6122_READ_FLOWRATE, result);

    sensor_struct.expiratory_flow = *result;
    sensor_struct.last_expiratory_flow_read_time = get_current_time();

    if ((*result > FLOW_LOWER_BOUND) && (*result < FLOW_UPPER_BOUND) && (i2c_read_status == I2C_OK))
    {
      sensor_status = STATUS_OK;
    }
    return sensor_status;
}