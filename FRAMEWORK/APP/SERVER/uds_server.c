/*
 * uds_server.c
 *
 *  Created on: 28/09/2017
 *      Author: Patricio Gomez
 */

#include "uds_server.h"

uds_db_answer_t uds_db_answer;
server_status_struct_t server_status_struct;
uint16_t accel_data[3];

bool restart_me = false;

uint8_t f_DSC_D(){
	server_status_struct.server_session = default_session;
	uds_db_answer.SID_status = DiagnosticSessionControl + 0x40;
	uds_db_answer.SUB_or_DID1 = sub_Default;
	uds_db_answer.answer_length = 2;

	return SUCESSFUL;

}
uint8_t f_DSC_P(){
	server_status_struct.server_session = programming_session;
	uds_db_answer.SID_status = DiagnosticSessionControl + 0x40;
	uds_db_answer.SUB_or_DID1 = sub_Programming;
	uds_db_answer.answer_length = 2;

	return SUCESSFUL;

}
uint8_t f_DSC_E(){
	server_status_struct.server_session = extended_session;
	uds_db_answer.SID_status = DiagnosticSessionControl + 0x40;
	uds_db_answer.SUB_or_DID1 = sub_Extended;
	uds_db_answer.answer_length = 2;

	return SUCESSFUL;

}
uint8_t f_ECUR_HR(){
	//go to reset
	uds_db_answer.SID_status = ECUReset + 0x40;
	uds_db_answer.SUB_or_DID1 = sub_HardReset;
	uds_db_answer.answer_length = 2;
	restart_me = true;

	return SUCESSFUL;

}
uint8_t f_WDID_LC(uint8_t data){

	if(server_status_struct.server_session != extended_session){

		return serviceNotSupportedInActiveSession;

	}

	server_status_struct.server_led_color = data;

	uds_db_answer.SID_status = WriteDataByIdentifier + 0x40;
	uds_db_answer.SUB_or_DID1 = sub_W_led_color&(0xFF00) >> 8;
	uds_db_answer.DID2 = sub_W_led_color&(0x00FF);
	uds_db_answer.answer_length = 3;

	if(server_status_struct.server_led_status == led_on){

		leds_only_one(server_status_struct.server_led_color);

	}

	return SUCESSFUL;

}
uint8_t f_RDID_ACCEL(RDID_sub_db_t RDID_sub_db){

	accel_read(accel_data);


	uds_db_answer.SID_status = ReadDataByIdentifier + 0x40;
	uds_db_answer.SUB_or_DID1 = sub_x_axis&(0xFF00) >> 8;
	uds_db_answer.answer_length = 5;

	switch(RDID_sub_db){

	case sub_x_axis:
		uds_db_answer.DID2 = sub_x_axis&(0x00FF);
		uds_db_answer.DATA1 = ((accel_data[0])&(0xFF00)) >> 8;
		uds_db_answer.DATA2 = ((accel_data[0])&(0x00FF));

		break;

	case sub_y_axis:
		uds_db_answer.DID2 = sub_y_axis&(0x00FF);
		uds_db_answer.DATA1 = ((accel_data[1])&(0xFF00)) >> 8;
		uds_db_answer.DATA2 = ((accel_data[1])&(0x00FF));

		break;

	case sub_z_axis:
		uds_db_answer.DID2 = sub_z_axis&(0x00FF);
		uds_db_answer.DATA1 = ((accel_data[2])&(0xFF00)) >> 8;
		uds_db_answer.DATA2 = ((accel_data[2])&(0x00FF));

		break;

	default:
		return incorrectMessageLengthOrInvalidFormat;

		break;

	}

	return SUCESSFUL;

}
uint8_t f_RDID_LED(){

	uds_db_answer.SUB_or_DID1 = sub_R_led_color&(0xFF00) >> 8;
	uds_db_answer.DID2 = sub_R_led_color&(0x00FF);
	uds_db_answer.answer_length = 4;
	uds_db_answer.DATA1 = server_status_struct.server_led_color;

	return SUCESSFUL;

}
uint8_t f_IOCID_SET(uint8_t data){

	if((server_status_struct.server_session != extended_session) ||
			(server_status_struct.server_session != service_session)){

		return serviceNotSupportedInActiveSession;

	}

	server_status_struct.server_led_status = data;

	uds_db_answer.SID_status = InputOutputControlByIdentifier + 0x40;
	uds_db_answer.SUB_or_DID1 = sub_led_status&(0xFF00) >> 8;
	uds_db_answer.DID2 = sub_led_status&(0x00FF);
	uds_db_answer.answer_length = 3;

	if(server_status_struct.server_led_status == led_on){

		leds_only_one(server_status_struct.server_led_color);

	}

	return SUCESSFUL;

}

uint8_t f_SA_REQ_SEED(){

	if(server_status_struct.server_session != extended_session){

		return serviceNotSupportedInActiveSession;

	}

	uds_db_answer.SID_status = SecurityAccess + 0x40;
	uds_db_answer.SUB_or_DID1 = sub_level_1;
	uds_db_answer.DID2 = (server_status_struct.server_seed >> 8)&(0x00FF);
	uds_db_answer.DATA1 = (server_status_struct.server_seed)&(0x00FF);

	server_status_struct.server_key = SERVER_ACCESS_KEY(server_status_struct.server_seed);

	uds_db_answer.answer_length = 4;

	return SUCESSFUL;
}

uint8_t f_SA_VERI_KEY(uint16_t key){
	uds_db_answer.SID_status = SecurityAccess + 0x40;
	uds_db_answer.SUB_or_DID1 = sub_level_2;
	uds_db_answer.answer_length = 2;

	return SUCESSFUL;
}

uint8_t f_ERROR(uint8_t status, uint8_t SID){

	uds_db_answer.answer_length = 3;
	uds_db_answer.SID_status = 0x7F;
	uds_db_answer.SUB_or_DID1 = SID;
	uds_db_answer.DID2 = status;

}

uint8_t cheat_seed(){
	server_status_struct.server_seed++;
}
