/*
* This file contains the getter for the clinicina inputs
*/

#include "platform/common.h"

/*
 * todo add a comment here
 *
 */
enum Validity_Status get_respiratory_rate(uint32_t * RR); // Victor: Should this be something like respiratory_rate_validity? Or should the check and the value retrieval be in the same function? 

int retrieve_RR(){
    return 15;
};