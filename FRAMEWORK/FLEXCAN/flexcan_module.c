/*
 * flexcan_module.c
 *
 *  Created on: 18/08/2017
 *      Author: Patricio Gomez
 */


#include "flexcan_module.h"

volatile bool txComplete = true;
volatile bool rxComplete = false;

flexcan_handle_t flexcanHandle;
flexcan_mb_transfer_t txXfer, rxXfer;
flexcan_frame_t txFrame, rxFrame;
flexcan_rx_mb_config_t mbConfig;

/*!
 * @brief FlexCAN Call Back function
 */
static void flexcan_callback(CAN_Type *base, flexcan_handle_t *handle, status_t status, uint32_t result, void *userData)
{

	switch (status)
	{
	case kStatus_FLEXCAN_RxIdle:
		if (RX_MESSAGE_BUFFER_NUM == result)
		{
			rxComplete = true;
		}
		break;

	case kStatus_FLEXCAN_TxIdle:
		if (TX_MESSAGE_BUFFER_NUM == result)
		{
			txComplete = true;
		}
		break;
	default:
		break;
	}

}

uint8_t flexcan_module_init(){

	flexcan_config_t flexcanConfig;

	FLEXCAN_GetDefaultConfig(&flexcanConfig);
	flexcanConfig.clkSrc = kFLEXCAN_ClkSrcPeri;
	FLEXCAN_Init(EXAMPLE_CAN, &flexcanConfig, CLOCK_GetFreq(EXAMPLE_CAN_CLKSRC));

	/* Setup Rx Message Buffer. */
	mbConfig.format = kFLEXCAN_FrameFormatStandard;
	mbConfig.type = kFLEXCAN_FrameTypeData;
	mbConfig.id = FLEXCAN_ID_STD(CAN_TESTER_ID);
	FLEXCAN_SetRxMbConfig(EXAMPLE_CAN, RX_MESSAGE_BUFFER_NUM, &mbConfig, true);

	/* Setup Tx Message Buffer. */
	FLEXCAN_SetTxMbConfig(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, true);

	/* Create FlexCAN handle structure and set call back function. */
	FLEXCAN_TransferCreateHandle(EXAMPLE_CAN, &flexcanHandle, flexcan_callback, NULL);

	/* Start receive data through Rx Message Buffer. */
	rxXfer.frame = &rxFrame;
	rxXfer.mbIdx = RX_MESSAGE_BUFFER_NUM;


	FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer);


}

uint8_t flexcan_module_send(uint32_t ID, FlexCAN_frame_t FlexCAN_frame){
	/* Prepare Tx Frame for sending. */
	txFrame.format = kFLEXCAN_FrameFormatStandard;
	txFrame.type = kFLEXCAN_FrameTypeData;
	txFrame.id = FLEXCAN_ID_STD(ID);
	txFrame.length = 8;
	txFrame.dataWord0 = CAN_WORD0_DATA_BYTE_0(FlexCAN_frame.txFram_8bits[0]) |
			CAN_WORD0_DATA_BYTE_1(FlexCAN_frame.txFram_8bits[1]) |
			CAN_WORD0_DATA_BYTE_2(FlexCAN_frame.txFram_8bits[2]) |
			CAN_WORD0_DATA_BYTE_3(FlexCAN_frame.txFram_8bits[3]);

	txFrame.dataWord1 = CAN_WORD1_DATA_BYTE_4(FlexCAN_frame.txFram_8bits[4]) |
			CAN_WORD1_DATA_BYTE_5(FlexCAN_frame.txFram_8bits[5]) |
			CAN_WORD1_DATA_BYTE_6(FlexCAN_frame.txFram_8bits[6]) |
			CAN_WORD1_DATA_BYTE_7(FlexCAN_frame.txFram_8bits[7]);

	FLEXCAN_TransferSendBlocking(EXAMPLE_CAN, TX_MESSAGE_BUFFER_NUM, &txFrame);

}

uint16_t flexcan_module_receive(FlexCAN_frame_t *FlexCAN_frame){

	/*Receive from each mailbox*/
	FlexCAN_frame->txFrame_32bits[0] = rxFrame.dataWord0;
	FlexCAN_frame->txFrame_32bits[1] = rxFrame.dataWord1;
	FLEXCAN_TransferReceiveNonBlocking(EXAMPLE_CAN, &flexcanHandle, &rxXfer);

}
