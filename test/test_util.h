/*
 * test_util.c
 *
 * contains the functions necessary for the testing framework
 */

#ifndef TEST_UTIL_H_
#define TEST_UTIL_H_

#include <stdlib.h>
#include <stdio.h>

#define assertTrue(cond) \
    do { \
        if (!(cond)) { \
            printf("%s:%s:%d: assert FAIL\n", __FILE__, __func__, __LINE__); \
            return 0; \
        } else { \
	        printf("%s:%s:%d: SUCESS \n", __FILE__, __func__, __LINE__); \
            return 1; \
	    } \
    } while (0);


/*
 * Function that run a test function
 */
void test(int (* func)(), char* func_name);

/*
 * Function that print the coverage of test passed
 * and return 0 if tat least one test failed and 1 otherwise
 */
int print_result();


#endif /* TEST_UTIL_H_ */
