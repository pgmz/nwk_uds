/*
 * flexcan_module.h
 *
 *  Created on: 18/08/2017
 *      Author: Patricio Gomez
 */

#ifndef SOURCE_FLEXCAN_FLEXCAN_MODULE_H_
#define SOURCE_FLEXCAN_FLEXCAN_MODULE_H_

#include "fsl_flexcan.h"
#include "fsl_gpio.h"
#include "FRAMEWORK/APP/app_messages.h"
#include "fsl_port.h"

/* Task priorities. */
#define FLEXCAN_task_PRIORITY (configMAX_PRIORITIES - 1)

#define EXAMPLE_CAN CAN0
#define EXAMPLE_CAN_CLKSRC kCLOCK_BusClk

#define RX_MESSAGE_BUFFER_NUM (8)
#define TX_MESSAGE_BUFFER_NUM (9)

typedef union FlexCAN_frame_union_t{
	uint64_t txFrame_64bits;
	uint32_t txFrame_32bits[2];
	uint8_t txFram_8bits[8];
}FlexCAN_frame_t;

uint8_t flexcan_module_init();
uint8_t flexcan_module_send(uint32_t ID, FlexCAN_frame_t FlexCAN_frame);
uint16_t flexcan_module_receive(FlexCAN_frame_t *FlexCAN_frame);
void flexcan_task(void *pvParameters);

#endif /* SOURCE_FLEXCAN_FLEXCAN_MODULE_H_ */
