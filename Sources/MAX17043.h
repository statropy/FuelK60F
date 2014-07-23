/*
 * MAX17043.h
 *
 *  Created on: Jul 22, 2014
 *      Author: erik
 */

#ifndef MAX17043_H_
#define MAX17043_H_

#include "ldd_i2c_master.h"

bool MAX17043_PowerUp(LDD_I2C_MASTER *master);
bool MAX17043_Config(LDD_I2C_MASTER *master);
bool MAX17043_ReadPercent(LDD_I2C_MASTER *master, uint8_t *percent);
bool MAX17043_ReadVersion(LDD_I2C_MASTER *master, uint16_t *version);

#endif /* MAX17043_H_ */
