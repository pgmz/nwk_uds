/*
 * accel_api.c
 *
 *  Created on: 30/08/2017
 *      Author: Patricio Gomez
 */

#include "accel_api.h"

uint8_t databyte = 0;
uint8_t write_reg = 0;
uint8_t readBuff[7];
int16_t x, y, z;
uint8_t status0_value = 0;
uint32_t i = 0U;

void accel_init(){

    bool isThereAccel = false;

	I2C_MasterTransferCreateHandle(BOARD_ACCEL_I2C_BASEADDR, &g_m_handle, i2c_master_callback, NULL);
	isThereAccel = I2C_ReadAccelWhoAmI();

    write_reg = ACCEL_CTRL_REG1;
    databyte = 0;
    I2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);

    write_reg = ACCEL_XYZ_DATA_CFG;
    databyte = 0x01;
    I2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);

    write_reg = ACCEL_CTRL_REG1;
    databyte = 0x0d;
    I2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);

}

void accel_read(int16_t accel_data[3]){

    status0_value = 0;
    /*  wait for new data are ready. */
    while (status0_value != 0xff)
    {
        I2C_ReadAccelRegs(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, ACCEL_STATUS, &status0_value, 1);
    }

    /*  Multiple-byte Read from STATUS (0x00) register */
    I2C_ReadAccelRegs(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, ACCEL_STATUS, readBuff, 7);

    status0_value = readBuff[0];
    x = ((int16_t)(((readBuff[1] * 256U) | readBuff[2]))) / 4U;
    y = ((int16_t)(((readBuff[3] * 256U) | readBuff[4]))) / 4U;
    z = ((int16_t)(((readBuff[5] * 256U) | readBuff[6]))) / 4U;

    accel_data[0] = x;
    accel_data[1] = y;
    accel_data[2] = z;
}
