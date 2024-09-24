/*
 * eeprom.h
 *
 *  Created on: Sep 24, 2024
 *      Author: 차용선
 */

#ifndef SRC_HW_EEPROM_H_
#define SRC_HW_EEPROM_H_

#ifdef __cplusplus
 extern "C" {
#endif



#include "hw.h"

#ifdef _USE_HW_EEPROM


bool     eepromInit();
bool     eepromIsInit(void);
bool     eepromValid(uint32_t addr);
bool     eepromReadByte(uint32_t addr, uint8_t *p_data);
bool     eepromWriteByte(uint32_t addr, uint8_t data_in);
bool     eepromRead(uint32_t addr, uint8_t *p_data, uint32_t length);
bool     eepromWrite(uint32_t addr, uint8_t *p_data, uint32_t length);
uint32_t eepromGetLength(void);
bool     eepromFormat(void);


#endif


#ifdef __cplusplus
}
#endif


#endif /* SRC_HW_EEPROM_H_ */
