/*
 * leds_app.h
 *
 *  Created on: 03/09/2017
 *      Author: Patricio Gomez
 */

#ifndef SOURCE_FRAMEWORK_LEDS_LEDS_APP_H_
#define SOURCE_FRAMEWORK_LEDS_LEDS_APP_H_

#include "fsl_gpio.h"
#include "board.h"

/*Init everything related to the LEDS*/
void leds_app_init();

/*Update the status of green led*/
void leds_green_led(uint8_t status);

/*Update the status of red led*/
void leds_red_led(uint8_t status);

/*Update the status of blue led*/
void leds_blue_led(uint8_t status);



#endif /* SOURCE_FRAMEWORK_LEDS_LEDS_APP_H_ */
