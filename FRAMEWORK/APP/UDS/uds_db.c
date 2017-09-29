/*
 * uds_db.c
 *
 *  Created on: 28/09/2017
 *      Author: Patricio Gomez
 */
#include "uds_db.h"

uint8_t can_control_check_rx(uint8_t SID, uint8_t SUB, uint8_t Length){

	switch(SID){

	case DiagnosticSessionControl:			f_DSC(SUB, Length);			break;
	case ECUReset:							f_ECUR(SUB, Length);		break;
	case ReadDataByIdentifier:				f_RDID(SUB, Length);		break;
	case SecurityAccess:					f_SA(SUB, Length);			break;
	case WriteDataByIdentifier:				f_WDID(SUB, Length);		break;
	case InputOutputControlByIdentifier:	f_IOCID(SUB, Length);		break;

	default:
		//NRC_msg = serviceNotSupported;
		break;
	}

}

uint8_t f_DSC(uint8_t SUB, uint8_t Length){

	switch(SUB){

	case sub_Default:						f_DSC_D();					break;
	case sub_Programming:					f_DSC_P();					break;
	case sub_Extended:						f_DSC_E();					break;

	default:

		break;

	}

}

uint8_t f_ECUR(uint8_t SUB, uint8_t Length){

	switch(SUB){

	case sub_HardReset:						f_ECUR_HR();				break;

	default:

		break;

	}

}

uint8_t f_RDID(uint8_t SUB, uint8_t Length){

	uint16_t xSUB;

	switch(xSUB){
	case sub_x_axis:break;
	case sub_y_axis:break;
	case sub_z_axis:break;
	case sub_R_led_color:break;

	default:

		break;
	}

}

uint8_t f_SA(uint8_t SUB, uint8_t Length){

	switch(SUB){

	case sub_level_1:break;
	case sub_level_2:break;
	default:

		break;
	}
}

uint8_t f_WDID(uint8_t SUB, uint8_t Length){

	uint16_t xdata;
	can_node_get_xdata(&xdata);

	uint16_t DID = JOIN_DID(SUB, GET_EXTRA_DID(xdata));

	switch(DID){
	case sub_W_led_color:				f_WDID_LC(GET_DATA(xdata));break;

	default:

		break;
	}
}

uint8_t f_IOCID(uint8_t SUB, uint8_t Length){

	uint16_t xdata;
	can_node_get_xdata(&xdata);

	uint16_t DID = JOIN_DID(SUB, GET_EXTRA_DID(xdata));

	switch(DID){
	case sub_led_status:break;

	default:

		break;
	}
}


