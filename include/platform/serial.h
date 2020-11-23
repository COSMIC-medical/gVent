/*
 * serial.h
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

#ifndef INC_PLATFORM_SERIAL_H_
#define INC_PLATFORM_SERIAL_H_

#include "platform/common.h"

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
status_t print_pressure(uint32_t val)