/*
 * rtc.h
 *
 *  Created on: Sep 22, 2024
 *      Author: WANG
 */

#ifndef SRC_HW_RTC_H_
#define SRC_HW_RTC_H_

#include "hw.h"


#ifdef _USE_HW_RTC


bool rtcInit(void);

uint32_t rtcBackupRegRead(uint32_t index);
void     rtcBackupRegWrite(uint32_t index, uint32_t data);


#endif

#endif /* SRC_HW_RTC_H_ */
