/*
 * uds_server.h
 *
 *  Created on: 28/09/2017
 *      Author: Patricio Gomez
 */

#include "..\..\LED_IO\leds_app.h"

#ifndef SOURCE_FRAMEWORK_APP_SERVER_UDS_SERVER_H_
#define SOURCE_FRAMEWORK_APP_SERVER_UDS_SERVER_H_

#define SERVER_ACCESS_KEY(seed)			(seed+1)

typedef enum{
	default_session = 0,
	programming_session,
	extended_session,
	service_session
}server_session_t;

typedef enum{
	led_red = 0x01,
	led_green,
	led_blue,
	led_none
}server_led_color_t;

typedef enum{
	led_on = 0x01,
	lef_off
}server_led_status_t;

typedef struct{
	server_session_t server_session;
	server_led_color_t server_led_color;
	server_led_status_t server_led_status;

}server_status_struct_t;

uint8_t f_DSC_D();
uint8_t f_DSC_P();
uint8_t f_DSC_E();
uint8_t f_ECUR_HR();
uint8_t f_WDID_LC(uint8_t data);


#endif /* SOURCE_FRAMEWORK_APP_SERVER_UDS_SERVER_H_ */
