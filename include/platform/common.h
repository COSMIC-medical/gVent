/**
 * platform.h
 * 
 * Includes basic libraries that are required across the entire
 * application, e.g., basic type definitions (e.g., uint16_t).
 */

#ifndef SRC_PLATFORM_COMMON_H_
#define SRC_PLATFORM_COMMON_H_

#include <stdint.h>

/**
 * Status type used by the platform, both internally and to
 * communicate the outcome of an operation with the 
 * application layer.
 */
typedef enum {
    STATUS_OK = 0x00,   // operation complete without error.
    STATUS_ERR = 0xFF   // operation failed.
} status_t;

#endif /* SRC_PLATFORM_COMMON_H_ */