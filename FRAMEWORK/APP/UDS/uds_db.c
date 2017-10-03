/*
 * uds_db.c
 *
 *  Created on: 28/09/2017
 *      Author: Patricio Gomez
 */
#include "uds_db.h"
#include "../SERVER/uds_server.h"


uint8_t can_control_check_rx(uint8_t SID, uint8_t SUB, uint8_t Length){

	uint8_t status;

	switch(SID){

	case DiagnosticSessionControl:			status = f_DSC(SUB, Length);			break;
	case ECUReset:							status = f_ECUR(SUB, Length);			break;
	case ReadDataByIdentifier:				status = f_RDID(SUB, Length);			break;
	case SecurityAccess:					status = f_SA(SUB, Length);				break;
	case WriteDataByIdentifier:				status = f_WDID(SUB, Length);			break;
	case InputOutputControlByIdentifier:	status = f_IOCID(SUB, Length);			break;

	default:
		status = serviceNotSupported;
		break;
	}

	return status;

}

uint8_t f_DSC(uint8_t SUB, uint8_t Length){
	uint8_t status;

	switch(SUB){

	case sub_Default:						status = f_DSC_D();						break;
	case sub_Programming:					status = f_DSC_P();						break;
	case sub_Extended:						status = f_DSC_E();						break;

	default:
		status = subFunctionNotSupported;
		break;

	}

}

uint8_t f_ECUR(uint8_t SUB, uint8_t Length){
	uint8_t status;

	switch(SUB){

	case sub_HardReset:						status = f_ECUR_HR();					break;

	default:
		status = subFunctionNotSupported;
		break;

	}

}

uint8_t f_RDID(uint8_t SUB, uint8_t Length){
	uint8_t status;

	uint16_t xdata;
	can_node_get_xdata(&xdata);

	uint16_t DID = JOIN_DID(SUB, GET_EXTRA_DID(xdata));

	switch(DID){
	case sub_x_axis:						status = f_RDID_ACCEL(sub_x_axis);		break;
	case sub_y_axis:						status = f_RDID_ACCEL(sub_y_axis);		break;
	case sub_z_axis:						status = f_RDID_ACCEL(sub_z_axis);		break;
	case sub_R_led_color:					status = f_RDID_LED();					break;

	default:
		status = subFunctionNotSupported;
		break;
	}

}

uint8_t f_SA(uint8_t SUB, uint8_t Length){
	uint8_t status;

	uint16_t xdata;
	uint16_t key;
	can_node_get_xdata(&xdata);

	key = (xdata);


	switch(SUB){

	case sub_level_1:						status = f_SA_REQ_SEED(); 				break;
	case sub_level_2:						status = f_SA_VERI_KEY(key);			break;
	default:
		status = subFunctionNotSupported;
		break;
	}
}

uint8_t f_WDID(uint8_t SUB, uint8_t Length){
	uint8_t status;

	uint16_t xdata;
	can_node_get_xdata(&xdata);

	uint16_t DID = JOIN_DID(SUB, GET_EXTRA_DID(xdata));

	switch(DID){
	case sub_W_led_color:					status = f_WDID_LC(GET_DATA(xdata));	break;

	default:
		status = subFunctionNotSupported;
		break;
	}
}

uint8_t f_IOCID(uint8_t SUB, uint8_t Length){
	uint8_t status;

	uint16_t xdata;
	can_node_get_xdata(&xdata);

	uint16_t DID = JOIN_DID(SUB, GET_EXTRA_DID(xdata));

	switch(DID){
	case sub_led_status:					status = f_IOCID_SET(GET_DATA(xdata));	break;

	default:
		status = subFunctionNotSupported;
		break;
	}
}

uint8_t can_control_set_error_answer(uint8_t status, uint8_t SID){
	f_ERROR(status, SID);
}
