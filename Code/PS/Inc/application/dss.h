/*
 * dss.h
 */

#ifndef INC_APPLICATION_DSS_H_
#define INC_APPLICATION_DSS_H_

/**
 * Transition to the Software Design Safe State
 *
 * Implementation is application specific, but should generally involve
 * emitting persistent/continuous warnings to the user.
 *
 * Called when an unrecoverable error is encountered.
 */
void dss();

#endif /* INC_APPLICATION_DSS_H_ */
