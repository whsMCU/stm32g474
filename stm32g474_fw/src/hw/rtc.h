/*
 * rtc.h
 *
 *  Created on: Sep 22, 2024
 *      Author: WANG
 */

#ifndef SRC_HW_RTC_H_
#define SRC_HW_RTC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "hw.h"


#ifdef _USE_HW_RTC

typedef struct
{
  uint8_t hours;
  uint8_t minutes;
  uint8_t seconds;
} rtc_time_t;

typedef struct
{
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t week;
} rtc_date_t;

typedef struct
{
  rtc_time_t time;
  rtc_date_t date;
} rtc_info_t;


bool rtcInit(void);
bool rtcGetInfo(rtc_info_t *rtc_info);
bool rtcGetTime(rtc_time_t *rtc_time);
bool rtcGetDate(rtc_date_t *rtc_date);
bool rtcSetTime(rtc_time_t *rtc_time);
bool rtcSetDate(rtc_date_t *rtc_date);

bool rtcSetReg(uint32_t index, uint32_t data);
bool rtcGetReg(uint32_t index, uint32_t *p_data);

#endif

#ifdef __cplusplus
}
#endif

#endif /* SRC_HW_RTC_H_ */
