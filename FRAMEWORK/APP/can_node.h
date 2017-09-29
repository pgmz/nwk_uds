/*
 * can_node.h
 *
 *  Created on: 30/08/2017
 *      Author: Patricio Gomez
 */

#ifndef FRAMEWORK_APP_CAN_NODE_H_
#define FRAMEWORK_APP_CAN_NODE_H_

#include "FRAMEWORK/FLEXCAN/flexcan_module.h"
#include "app_messages.h"

/**
 * @brief State machine of the logic of NWK
 *
 * State machine that calls a function depending of the
 * current state of this node.
 *
 * @return @c NULL is always returned.
 */
void can_answer();

/**
 * @brief CAN transmission
 *
 * Transmit through CAN
 *
 * @return @c NULL is always returned.
 */
void can_transmit();

/**
 * @brief CAN reception
 *
 * Receive the data in a specified mail box of the flexcan
 * driver.
 *
 * @return @c NULL is always returned.
 */
void can_receive();

void can_node_get_xdata(uint16_t *ptr_xSub);


#endif /* FRAMEWORK_APP_CAN_NODE_H_ */
