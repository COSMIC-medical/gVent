#include "stm32f4xx_hal.h"
#include <platform/pressureFlowSensor.h>
#include <platform/pressureFlowSensor_private.h>
#include <platform/configuration_private.h>

/*
 * Reads and validates the read inspiratory pressure
 * Updates the measurement inputs
 *
 * returns the inspiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 *
 */
int get_inspiratory_pressure(){
    
}

/*
 * Reads and validates the read expiratory pressure
 * Updates the measurement inputs
 *
 * returns the expiratory pressure in cmH2O when it is valid
 * returns cmH2O when no valid pressure is available
 */
int get_expiratory_pressure(){

}

/*
 * Reads and validates the read inspiratory flow
 * Updates the measurement inputs
 *
 * returns the inspiratory flow in SLPM when it is valid
 * returns SLPM when no valid flow is available
 */
int get_inspiratory_flow(){

}

/*
 * Reads and validates the read expiratory flow
 * Updates the measurement inputs
 *
 * returns the expiratory flow in SLPM when it is valid
 * returns SLPM  when no valid flow is available
 */
int get_expiratory_flow(){

}

/*
* Read i2c value 
* 
* Inputs: SENSOR_ADDR
*/
int read_pressure(uint8_t i2c_addr, uint8_t reg_addr){
    HAL_StatusTypeDef ret;
    uint8_t buf[20];
    // uint32_t flow_slpm;
    uint32_t val; 

    // Tell FS6122 that we want to read from the pressure register
    buf[0] = FS6122_READ_FLOWRATE_PRESSURE;
    ret = HAL_I2C_Master_Transmit(&hi2c1, i2c_addr, buf, 1, HAL_MAX_DELAY);
    if ( ret != HAL_OK ) {
      strcpy((char*)buf, "Error Tx\r\n");
    } 
    else {

      // Read 4 bytes from the pressure register
      ret = HAL_I2C_Master_Receive(&hi2c1, i2c_addr, buf, 4, HAL_MAX_DELAY);
      if ( ret != HAL_OK ) {
        strcpy((char*)buf, "Error Rx\r\n");
      } 
      else {

        //Combine the bytes
        val = ((int16_t)buf[0] << 24) | (buf[1] << 16) | (buf[2] << 8) | (buf[3]) >> 2;
        // val >>= 2; // value is 14 bit, so shift by 2
        
        // Convert temperature to decimal format
        // pressure_cmh2o *= 100;
        sprintf((char*)buf,
              "%li cmH2O\r\n",
              (val)
              );
      }
    }

    // Send out buffer (temperature or error message)
    HAL_UART_Transmit(&huart2, buf, strlen((char*)buf), HAL_MAX_DELAY);

    // Wait
    HAL_Delay(500);

}