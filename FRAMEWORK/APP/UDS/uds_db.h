/*
 * uds_db.h
 *
 *  Created on: 28/09/2017
 *      Author: Patricio Gomez
 */

#ifndef SOURCE_FRAMEWORK_APP_UDS_UDS_DB_H_
#define SOURCE_FRAMEWORK_APP_UDS_UDS_DB_H_

#include "../can_node.h"

#define GET_EXTRA_DID(xdata)		((xdata&0xFF00) >> 8)
#define GET_DATA(xdata)				(xdata&0x00FF)
#define JOIN_DID(DID1, DID2)		((DID1 << 8)|(DID2))

typedef enum{
	DiagnosticSessionControl = 0x10,
	ECUReset = 0x11,
	ReadDataByIdentifier = 0x22,
	SecurityAccess = 0x27,
	WriteDataByIdentifier = 0x2E,
	InputOutputControlByIdentifier = 0x2F
}uds_sid_db_t;

typedef enum{
	sub_Default = 0x01,
	sub_Programming = 0x02,
	sub_Extended = 0x03
}Session_sub_db_t;

typedef enum{
	sub_HardReset = 0x01
}ECUR_sub_db_t;

typedef enum{
	sub_x_axis = 0xFD40,
	sub_y_axis = 0xFD41,
	sub_z_axis = 0xFD42,
	sub_R_led_color = 0xFE50
}RDID_sub_db_t;

typedef enum{
	sub_level_1 = 0x01,
	sub_level_2 = 0x02
}SA_sub_db_t;

typedef enum{
	sub_W_led_color = 0xFE50
}WDID_sub_db_t;

typedef enum{
	sub_led_status = 0xFE51
}IOCID_sub_db_t;

typedef enum{
	serviceNotSupported = 0x11,
	subFunctionNotSupported = 0x12,
	incorrectMessageLengthOrInvalidFormat = 0x13,
	serviceNotSupportedInActiveSession = 0x7F
}nrc_db_t;


/**
 * @brief Check if RX data is correct
 *
 * Check through the possible scenarios the NWK
 * has, if the received message if valid
 *
 * @return @c NULL is always returned.
 */
uint8_t can_control_check_rx(uint8_t SID, uint8_t SUB, uint8_t Length);
uint8_t f_DSC(uint8_t SUB, uint8_t Length);
uint8_t f_ECUR(uint8_t SUB, uint8_t Length);
uint8_t f_RDID(uint8_t SUB, uint8_t Length);
uint8_t f_SA(uint8_t SUB, uint8_t Length);
uint8_t f_WDID(uint8_t SUB, uint8_t Length);
uint8_t f_IOCID(uint8_t SUB, uint8_t Length);


#endif /* SOURCE_FRAMEWORK_APP_UDS_UDS_DB_H_ */
