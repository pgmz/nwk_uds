/*
 * can_node.c
 *
 *  Created on: 30/08/2017
 *      Author: Patricio Gomez
 */

#include "can_node.h"
#include "UDS/uds_db.h"


extern uds_db_answer_t uds_db_answer;

/*Tx frame*/
FlexCAN_frame_t FlexCAN_frame_Tx;

/*Rx frame*/
FlexCAN_frame_t FlexCAN_frame_Rx;

/*State machine*/
void can_answer(){

	memset(&FlexCAN_frame_Tx, PADD_VAL, sizeof(FlexCAN_frame_Tx));

	FlexCAN_frame_Tx.txFram_8bits[0] = uds_db_answer.answer_length;
	FlexCAN_frame_Tx.txFram_8bits[1] = uds_db_answer.SID_status;
	FlexCAN_frame_Tx.txFram_8bits[2] = uds_db_answer.SUB_or_DID1;
	FlexCAN_frame_Tx.txFram_8bits[3] = uds_db_answer.DID2;
	FlexCAN_frame_Tx.txFram_8bits[4] = uds_db_answer.DATA1;
	FlexCAN_frame_Tx.txFram_8bits[5] = uds_db_answer.DATA2;

	flexcan_module_send(CAN_SERVER_ID, FlexCAN_frame_Tx);

}

void can_receive(){

	/*Receive from a Mail Box*/
	flexcan_module_receive(&FlexCAN_frame_Rx);

	uint8_t status = can_control_check_rx(FlexCAN_frame_Rx.txFram_8bits[2],
			FlexCAN_frame_Rx.txFram_8bits[1],
			FlexCAN_frame_Rx.txFram_8bits[3]);

	/*If so, store the result*/
	if(status != SUCESSFUL){
		can_control_set_error_answer(status, FlexCAN_frame_Rx.txFram_8bits[2]);
	}
}

void can_node_get_xdata(uint16_t *ptr_xSub){

	uint16_t temp;

	temp = FlexCAN_frame_Rx.txFram_8bits[0] << 8;
	temp = temp | FlexCAN_frame_Rx.txFram_8bits[7];

	*(ptr_xSub) = temp;

}


