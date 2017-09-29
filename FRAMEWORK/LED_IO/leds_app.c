/*
 * leds_app.c
 *
 *  Created on: 03/09/2017
 *      Author: Patricio Gomez
 */

#include "leds_app.h"

/* Init LEDs */
void leds_app_init(){

	gpio_pin_config_t led_config = {
			kGPIO_DigitalOutput, 1,
	};

	GPIO_PinInit(BOARD_LED_RED_GPIO, BOARD_LED_RED_GPIO_PIN, &led_config);
	GPIO_PinInit(BOARD_LED_BLUE_GPIO, BOARD_LED_BLUE_GPIO_PIN, &led_config);
	GPIO_PinInit(BOARD_LED_GREEN_GPIO, BOARD_LED_GREEN_GPIO_PIN, &led_config);

}

/* Set green status*/
void leds_green_led(uint8_t status){
	if(status){
		GPIO_ClearPinsOutput(BOARD_LED_GREEN_GPIO, 1 << BOARD_LED_GREEN_GPIO_PIN);
	} else {
		GPIO_SetPinsOutput(BOARD_LED_GREEN_GPIO, 1 << BOARD_LED_GREEN_GPIO_PIN);

	}
}

/* Set red status*/
void leds_red_led(uint8_t status){
	if(status){
		GPIO_ClearPinsOutput(BOARD_LED_RED_GPIO, (1) << BOARD_LED_RED_GPIO_PIN);
	} else {
		GPIO_SetPinsOutput(BOARD_LED_RED_GPIO, (1) << BOARD_LED_RED_GPIO_PIN);

	}

}

/* Set blue status*/
void leds_blue_led(uint8_t status){
	if(status){
		GPIO_ClearPinsOutput(BOARD_LED_BLUE_GPIO, (1) << BOARD_LED_BLUE_GPIO_PIN);
	} else {
		GPIO_SetPinsOutput(BOARD_LED_BLUE_GPIO, (1) << BOARD_LED_BLUE_GPIO_PIN);

	}

}
