/*
 * led.h
 *
 *  Created on: Sep 24, 2024
 *      Author: 차용선
 */

#ifndef SRC_HW_LED_H_
#define SRC_HW_LED_H_


#ifdef __cplusplus
extern "C" {
#endif

#include "hw.h"


#define LED_MAX_CH  HW_LED_MAX_CH


bool ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint8_t ch);

#ifdef __cplusplus
}
#endif


#endif /* SRC_HW_LED_H_ */
