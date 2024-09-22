/*
 * rtc.c
 *
 *  Created on: Sep 22, 2024
 *      Author: WANG
 */


#include "hw.h"


#ifdef _USE_HW_RESET

#define RESET_REG_PARAM         0
#define RESET_REG_COUNT         1

bool resetInit(void);

uint32_t resetGetCount(void);
void resetToBoot(uint32_t timeout);
void resetToSysBoot(void);

#endif
