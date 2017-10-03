/*
 * accel_api.h
 *
 *  Created on: 30/08/2017
 *      Author: Patricio Gomez
 */

#ifndef FRAMEWORK_ACCELEROMETER_ACCEL_API_H_
#define FRAMEWORK_ACCELEROMETER_ACCEL_API_H_


#include "i2c_read_accel_value_transfer.c"

/* init everything related to accelerometer */
void accel_init();

/* read the accelerometer and put data in accel_data array */
void accel_read(int16_t accel_data[3]);

#endif /* FRAMEWORK_ACCELEROMETER_ACCEL_API_H_ */
