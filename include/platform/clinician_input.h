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

/*
 * Updates I:E ratio (inspiratory-expiratory) variable IE 
 * when a valid value was read from the clinician inputs
 * 
 * @return STATUS_OK if I:E ratio is valid 
 *         STATUS_ERR if the I:E ratio is invalid
 *
 */
status_t get_ie_ratio(uint32_t * IE);

/*
 * Updates breaths per minute variable BPM 
 * when a valid value was read from the clinician inputs
 * 
 * @return STATUS_OK if breaths per minute value is valid 
 *         STATUS_ERR if the breaths per minute value is invalid
 *
 */
status_t get_breaths_per_minute(uint32_t * BPM);

/*
 * Updates acceptable exhaled tidal volume variable ML 
 * when a valid value was read from the clinician inputs
 * 
 * @return STATUS_OK if acceptable exhaled tidal volume is valid 
 *         STATUS_ERR if the acceptable exhaled tidal volume is invalid
 *
 */
status_t get_acceptable_exhaled_tidal_volume(uint32_t * ML);

/*
 * Updates ventilation mode variable VM 
 * when a valid value was read from the clinician inputs
 * 
 * @return STATUS_OK if ventilation mode is valid 
 *         STATUS_ERR if the ventilation mode is invalid
 *
 */
status_t get_ventilation_mode(enum VM);


