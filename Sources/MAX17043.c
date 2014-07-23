/*
 * MAX17043.c
 *
 *  Created on: Jul 22, 2014
 *      Author: erik
 */


#include "MAX17043.h"
#include "CI2C1.h"

static uint8_t write_reg(LDD_I2C_MASTER *master, uint8_t *buffer, uint8_t len)
{
	
	uint8_t result  =ERR_OK;
	do {
		result = master->send(master->handle, buffer, len, LDD_I2C_SEND_STOP);
	} while(result == ERR_BUSY);
	if (result != ERR_OK) { printf("write fail @%02X: %d\r\n", buffer[0], result); return result; }

	while (!master->flags.txFlag);
	master->flags.txFlag = FALSE;
	return ERR_OK;
}

static uint8_t read_reg(LDD_I2C_MASTER *master, uint8_t address, uint8_t *buffer, uint8_t len)
{
	uint8_t result = ERR_OK;
	do {
		master->send(master->handle, &address, 1U, LDD_I2C_NO_SEND_STOP);
	}while(result == ERR_BUSY);
	if (result!=ERR_OK) { printf("addr write fail: %d", result); return result; }

	while (!master->flags.txFlag) {}
	master->flags.txFlag = FALSE;
	
	do {
		result = master->receive(master->handle, buffer, len, LDD_I2C_SEND_STOP);
	}while(result == ERR_BUSY);
	if (result!=ERR_OK)  { printf("read fail: %d", result); return result; }

	while (!master->flags.rxFlag);
	master->flags.rxFlag = FALSE;
	return ERR_OK;
}

bool MAX17043_PowerUp(LDD_I2C_MASTER *master)
{
	uint8_t buffer[3] = {0xFE, 0x54, 0x00};
	return write_reg(master, buffer, 3) == ERR_OK;
}

bool MAX17043_Config(LDD_I2C_MASTER *master)
{
	uint8_t buffer[3] = {0x0C, 0x97, 0x00};
	return write_reg(master, buffer, 3) == ERR_OK;
}

bool MAX17043_ReadPercent(LDD_I2C_MASTER *master, uint8_t *percent)
{
	return read_reg(master, 0x04, percent, 1) == ERR_OK;
}

bool MAX17043_ReadVersion(LDD_I2C_MASTER *master, uint16_t *version)
{
	uint8_t buffer[2];
	if(read_reg(master, 0x08, buffer, 2) == ERR_OK)
	{
		*version = (buffer[0] << 8) | buffer[1];
		return TRUE;
	}
	return FALSE;
}
