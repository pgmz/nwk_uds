/*
 * uds_server.c
 *
 *  Created on: 28/09/2017
 *      Author: Patricio Gomez
 */

#include "uds_server.h"

server_status_struct_t server_status_struct;

uint8_t f_DSC_D(){
	server_status_struct.server_session = default_session;
}

uint8_t f_DSC_P(){
	server_status_struct.server_session = programming_session;
}

uint8_t f_DSC_E(){
	server_status_struct.server_session = extended_session;
}

uint8_t f_ECUR_HR(){
	//go to reset
}

uint8_t f_WDID_LC(uint8_t data){



}
