/*
 * swtimer.h
 *
 *  Created on: Sep 24, 2024
 *      Author: 차용선
 */

#ifndef SRC_HW_SWTIMER_H_
#define SRC_HW_SWTIMER_H_

#ifdef __cplusplus
extern "C" {
#endif


#include "hw.h"

#ifdef _USE_HW_SWTIMER

#ifndef ON
#define ON 1
#endif

#ifndef OFF
#define OFF 0
#endif

#ifndef NULL
#define NULL 0
#endif


#define _HW_DEF_SW_TIMER_MAX        HW_SWTIMER_MAX_CH


#define ONE_TIME            1
#define LOOP_TIME           2


typedef int16_t             swtimer_handle_t;


bool swtimerInit(void);
void swtimerSet  (swtimer_handle_t TmrNum, uint32_t TmrData, uint8_t TmrMode, void (*Fnct)(void *),void *arg);
void swtimerStart(swtimer_handle_t TmrNum);
void swtimerStop (swtimer_handle_t TmrNum);
void swtimerReset(swtimer_handle_t TmrNum);
void swtimerISR(void);


swtimer_handle_t swtimerGetHandle(void);
uint32_t swtimerGetCounter(void);

#endif

#ifdef __cplusplus
}
#endif



#endif /* SRC_HW_SWTIMER_H_ */
