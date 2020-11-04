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
 * Status used by the platform associated to clinician and measured inputs
 *   VALID means the input was available and valid
 *   INVALID means the input is either unavailable or invalid 
 * 
 * where validity of an input is defined by some vality bounds
 */
enum Validity_Status {VALID = 1, INVALID = 0}; 

#endif /* SRC_PLATFORM_PLATFORM_H_ */