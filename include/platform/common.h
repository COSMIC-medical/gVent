/**
 * platform.h
 * 
 * Includes basic libraries that are required across the entire
 * application, e.g., basic type definitions (e.g., uint16_t).
 */

#ifndef SRC_PLATFORM_PLATFORM_H_
#define SRC_PLATFORM_PLATFORM_H

#include <stdint.h>

/**
 * Status type used by the platform, both internally and to
 * communicate with the application layer. 
 * 
 * For example, reading a sensor might return STATUS_OK to
 * indicate that the sensor was successfully read or STATUS_ERR
 * to indicate a read failure.
 */
typedef enum {
    STATUS_OK = 0x00,
    STATUS_ERR = 0xFF
} status_t;

#endif /* SRC_PLATFORM_PLATFORM_H_ */