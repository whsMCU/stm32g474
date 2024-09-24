/*
 * cdc.h
 *
 *  Created on: Sep 22, 2024
 *      Author: WANG
 */

#ifndef SRC_HW_CDC_H_
#define SRC_HW_CDC_H_

#include "hw.h"


#ifdef _USE_HW_CDC



bool     cdcInit(void);
bool     cdcIsInit(void);
bool     cdcIsConnect(void);
uint32_t cdcAvailable(void);
uint8_t  cdcRead(void);
uint32_t cdcWrite(uint8_t *p_data, uint32_t length);
uint32_t cdcGetBaud(void);


#endif

#endif /* SRC_HW_CDC_H_ */
