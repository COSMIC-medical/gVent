/*
 * serial.c
 *
 * This file contains the functions
 * for an platform developer
 * to write values via UART to a 
 * serial port on a host computer
 * 
 * Purpose: to be used for debugging purposes
 * Should be removed from the final firmware
 * once deployed.
 *
 */

#include "stm32f4xx_hal.h"
#include "platform/configuration_private.h"
#include "platform/common.h"
#include <stdio.h>
#include <string.h>
#include <stdint.h>

/*
 * Formats and writes a pressure value into a string buffer
 * then outputs that buffer to a UART port connected to a host
 * computer. 
 * 
 * Returns the status as either
 *  STATUS_OK, if the UART write command worked, or 
 *  STATUS_ERR, if the UART write command failed
 * 
 * INPUTS: 
 *  uint32_t val -- a pressure reading from the sensor
 *  stored in program memory.
 *
 */
status_t print_pressure(uint32_t val){
    
    uint8_t serial_buf[20] = {0}; // uart buffer
    uint32_t UART_TIMEOUT_DELAY = 100; // Performance requirements for task require this function to return in < 100ms
   
    sprintf((char*)serial_buf, "%li cmH2O\r\n", (val));

    // Send out buffer (sensor reading or error message)
    HAL_UART_Transmit(&serial1, serial_buf, strlen((char*)serial_buf), UART_TIMEOUT_DELAY);
}