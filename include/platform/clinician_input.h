/*
* This file contains the getter for the clinicina inputs
*/

#include "platform/common.h"

/*
 * Updates respiratory rate variable RR 
 * when a valid value was read from the clinician inputs
 * 
 * @return STATUS_OK if respiratory rate is valid 
 *         STATUS_ERR if the respiratory rate is invalid
 *
 */
status_t get_respiratory_rate(uint32_t * RR);
