/*
 * Copyright (c) 2013 - 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * This is template for main module created by New Kinetis SDK 2.x Project Wizard. Enjoy!
 **/

#include <string.h>

#include "board.h"
#include "pin_mux.h"
#include "clock_config.h"
/*#include "fsl_debug_console.h"*/

/* FreeRTOS kernel includes. */
#include "FRAMEWORK/FLEXCAN/flexcan_module.h"
#include "FRAMEWORK/APP/can_node.h"
#include "FRAMEWORK/ACCELEROMETER/accel_api.h"
#include "FRAMEWORK/LED_IO/leds_app.h"
#include "FRAMEWORK/APP/SERVER/uds_server.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* Task priorities. */
#define hello_task_PRIORITY (configMAX_PRIORITIES - 1)

extern bool restart_me;

extern volatile bool txComplete;
extern volatile bool rxComplete;

volatile bool txFromInterrupt;
volatile bool firstReading = true;

/*!
 * @brief Task responsible for printing of "Hello world." message.
 */
void flexcan_task(void *pvParameters) {

	FlexCAN_frame_t FlexCAN_frame;
	flexcan_module_init();

	TickType_t xLastWakeTime;
	const TickType_t xFrequency = 100;
	xLastWakeTime = xTaskGetTickCount();

	for (;;) {

		if(rxComplete == true){

			can_receive();
			can_answer();
			rxComplete = false;
		}

		cheat_seed();

		if(restart_me){
			NVIC_SystemReset();
		}
		vTaskDelayUntil( &xLastWakeTime, xFrequency);

	}
}

/*!
 * @brief Application entry point.
 */
int main(void) {
	/* Init board hardware. */
	BOARD_InitPins();
	BOARD_BootClockRUN();
	BOARD_InitDebugConsole();
	BOARD_I2C_ReleaseBus();
	BOARD_I2C_ConfigurePins();

	leds_app_init();
	accel_init();


	/* Create RTOS task */
	xTaskCreate(flexcan_task, "Flexcan_task", configMINIMAL_STACK_SIZE, NULL, hello_task_PRIORITY, NULL);
	vTaskStartScheduler();

	for(;;) { /* Infinite loop to avoid leaving the main function */
		__asm("NOP"); /* something to use as a breakpoint stop while looping */
	}
}


