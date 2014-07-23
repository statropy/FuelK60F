/*
 * ldd_i2c_master.h
 *
 *  Created on: Jul 22, 2014
 *      Author: erik
 */

#ifndef LDD_I2C_MASTER_H_
#define LDD_I2C_MASTER_H_

#include "PE_Types.h"
#include "PE_LDD.h"

typedef LDD_TError (*I2C_MasterSendBlock)(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, LDD_I2C_TSize Size, LDD_I2C_TSendStop SendStop);
typedef LDD_TError (*I2C_MasterReceiveBlock)(LDD_TDeviceData *DeviceDataPtr, LDD_TData *BufferPtr, LDD_I2C_TSize Size, LDD_I2C_TSendStop SendStop);

typedef struct {
	volatile bool rxFlag;
	volatile bool txFlag;
}LDD_RxTxFlags;

typedef struct {
  LDD_RxTxFlags flags;
  LDD_TDeviceData *handle;
  I2C_MasterSendBlock send;
  I2C_MasterSendBlock receive;
} LDD_I2C_MASTER;

#endif /* LDD_I2C_MASTER_H_ */
