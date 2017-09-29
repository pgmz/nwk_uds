/*
 * can_node.c
 *
 *  Created on: 30/08/2017
 *      Author: Patricio Gomez
 */

#include "can_node.h"
#include "UDS/uds_db.h"

/*Tx frame*/
FlexCAN_frame_t FlexCAN_frame_Tx;

/*Rx frame*/
FlexCAN_frame_t FlexCAN_frame_Rx;

uint8_t NRC_msg = 0x00;

/*State machine*/
void can_answer(){


}


void can_transmit(){

	/*Transmit what is the NWK table for this node*/
	FlexCAN_frame_Tx.txFram_8bits[0];
	FlexCAN_frame_Tx.txFram_8bits[1];

	flexcan_module_send(CAN_SERVER_ID, FlexCAN_frame_Tx);

}

void can_receive(){

	/*Receive from a Mail Box*/
	flexcan_module_receive(&FlexCAN_frame_Rx);

	uint8_t status = can_control_check_rx(FlexCAN_frame_Rx.txFram_8bits[2],
			FlexCAN_frame_Rx.txFram_8bits[1],
			FlexCAN_frame_Rx.txFram_8bits[3]);

	/*If so, store the result*/
	if(status == true){

	}
}

void can_node_get_xdata(uint16_t *ptr_xSub){

	uint16_t temp;

	temp = FlexCAN_frame_Rx.txFram_8bits[0] << 8;
	temp = temp | FlexCAN_frame_Rx.txFram_8bits[7];

	*(ptr_xSub) = temp;

}


