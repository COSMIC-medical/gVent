/*
 * clinician_info_stub.h
 *
 * Stub for the function that retreive the clinician inputs
 */

#include <stddef.h>
#include <stdint.h>
#include "platform/common.h"

void set_respiratory_rate(uint32_t* RR, status_t* status, size_t size);

status_t get_respiratory_rate(uint32_t * RR);

void set_selected_inspiratory_time(uint32_t* insp_times, status_t* status);

status_t get_selected_inspiratory_time(uint32_t* insp_time);
