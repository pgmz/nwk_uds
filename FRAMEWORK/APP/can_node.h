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

#define PADD_VAL		0x55	//Padding data

/**
 * @brief Build answer depending on the UDS database
 *
 * Function that sets in the tx frame of flexcan, the answer to the
 * tester, depending on the uds database
 *
 * @return @c NULL is always returned.
 */
void can_answer();

/**
 * @brief CAN reception
 *
 * Receive the data of the flexcan driver.
 *
 * @return @c NULL is always returned.
 */
void can_receive();

/**
 * @brief Get more data from RX Frame
 *
 * Set to the pointer, the extra data in the
 * RX Frame that may be needed to perform the uds
 * service
 *
 *	param[out] ptr_xSub: pointer to where to store the
 *	extra data
 *
 * @return @c NULL is always returned.
 */
void can_node_get_xdata(uint16_t *ptr_xSub);


#endif /* FRAMEWORK_APP_CAN_NODE_H_ */
