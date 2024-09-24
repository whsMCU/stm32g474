/*
 * uart.h
 *
 *  Created on: Sep 5, 2024
 *      Author: 차용선
 */

#ifndef SRC_HW_UART_H_
#define SRC_HW_UART_H_

#include "hw.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _USE_HW_UART

#define UART_MAX_CH         HW_UART_MAX_CH


	bool     uartInit(void);
	bool     uartDeInit(void);
	bool     uartIsInit(void);
	bool     uartOpen(uint8_t ch, uint32_t baud);
	bool     uartIsOpen(uint8_t ch);
	bool     uartClose(uint8_t ch);
	uint32_t uartAvailable(uint8_t ch);
	bool     uartFlush(uint8_t ch);
	uint8_t  uartRead(uint8_t ch);
	uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length);
	uint32_t uartPrintf(uint8_t ch, const char *fmt, ...);
	uint32_t uartVPrintf(uint8_t ch, const char *fmt, va_list arg);
	uint32_t uartGetBaud(uint8_t ch);
	uint32_t uartGetRxCnt(uint8_t ch);
	uint32_t uartGetTxCnt(uint8_t ch);

#ifdef __cplusplus
}
#endif

#endif



#endif /* SRC_HW_UART_H_ */
