/*
 * application.h
 *
 */

#ifndef INC_APPLICATION_H_
#define INC_APPLICATION_H_


/**
 * initialize the application
 *
 * used by application developers to:
 * register tasks to the platform using the scheduler register_task function
 * add initialization routines
 *
 * Called by the main startup routine after hardware and
 * platform initialization but before platform is started/running.
 */
void init_application();


#endif /* INC_APPLICATION_H_ */
