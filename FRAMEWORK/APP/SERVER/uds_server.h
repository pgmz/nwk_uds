/*
 * uds_server.h
 *
 *  Created on: 28/09/2017
 *      Author: Patricio Gomez
 */

#include "..\..\LED_IO\leds_app.h"
#include "..\UDS\uds_db.h"
#include "..\..\ACCELEROMETER\accel_api.h"

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
	uint16_t server_seed;
	uint16_t server_key;
}server_status_struct_t;

uint8_t f_DSC_D();
uint8_t f_DSC_P();
uint8_t f_DSC_E();
uint8_t f_ECUR_HR();
uint8_t f_WDID_LC(uint8_t data);
uint8_t f_RDID_LED();
uint8_t f_RDID_ACCEL(RDID_sub_db_t RDID_sub_db);
uint8_t f_IOCID_SET(uint8_t data);

uint8_t f_SA_REQ_SEED();
uint8_t f_SA_VERI_KEY(uint16_t key);

uint8_t f_ERROR(uint8_t status, uint8_t SID);

uint8_t cheat_seed();

#endif /* SOURCE_FRAMEWORK_APP_SERVER_UDS_SERVER_H_ */
