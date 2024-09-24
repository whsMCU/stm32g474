/*
 * uart.c
 *
 *  Created on: Sep 5, 2024
 *      Author: 차용선
 */




#include "uart.h"
//#include "cdc.h"
#include "qbuffer.h"

#ifdef _USE_HW_UART

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_rx;


#define UART_RX_BUF_LENGTH      1024

static qbuffer_t qbuffer[UART_MAX_CH];
static uint8_t rx_buf[256];

typedef enum
{
  UART_HW_TYPE_STM32,
  UART_HW_TYPE_USB,
  UART_HW_TYPE_BT_SPP,
} UartHwType_t;


typedef struct
{
  bool     is_open;
  uint32_t baud;
  UartHwType_t type;

  uint8_t  rx_buf[UART_RX_BUF_LENGTH];
  qbuffer_t qbuffer;
  UART_HandleTypeDef *p_huart;
  DMA_HandleTypeDef  *p_hdma_rx;

} uart_tbl_t;


static uart_tbl_t uart_tbl[UART_MAX_CH];

bool uartInit(void)
{
  for (int i=0; i<UART_MAX_CH; i++)
  {
    uart_tbl[i].is_open = false;
    uart_tbl[i].baud = 57600;
  }

  return true;
}

bool uartOpen(uint8_t ch, uint32_t baud)
{
  bool ret = false;


  switch(ch)
  {
    case _DEF_USB:
      uart_tbl[ch].type    = UART_HW_TYPE_USB;
      uart_tbl[ch].baud    = baud;
      uart_tbl[ch].is_open = true;

      ret = true;
      break;

    case _DEF_UART2:
    	uart_tbl[ch].p_huart = &huart2;
    	uart_tbl[ch].p_huart->Instance = USART2;
    	uart_tbl[ch].p_huart->Init.BaudRate = baud;
    	uart_tbl[ch].p_huart->Init.WordLength = UART_WORDLENGTH_8B;
    	uart_tbl[ch].p_huart->Init.StopBits = UART_STOPBITS_1;
    	uart_tbl[ch].p_huart->Init.Parity = UART_PARITY_NONE;
    	uart_tbl[ch].p_huart->Init.Mode = UART_MODE_TX_RX;
    	uart_tbl[ch].p_huart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
    	uart_tbl[ch].p_huart->Init.OverSampling = UART_OVERSAMPLING_16;
    	uart_tbl[ch].p_huart->Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    	uart_tbl[ch].p_huart->Init.ClockPrescaler = UART_PRESCALER_DIV1;
    	uart_tbl[ch].p_huart->AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

      qbufferCreate(&qbuffer[ch], (uint8_t *)&rx_buf[0], 256);

      __HAL_RCC_DMAMUX1_CLK_ENABLE();
      __HAL_RCC_DMA1_CLK_ENABLE();
      HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
      HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

      if (HAL_UART_Init(&huart2) != HAL_OK)
      {
        ret = false;
      }else
      {
        ret = true;
        uart_tbl[ch].is_open = true;

        if(HAL_UART_Receive_DMA(&huart2, (uint8_t *)&rx_buf[0], 256) != HAL_OK)
        {
          ret = false;
        }
        qbuffer[ch].in  = qbuffer[ch].len - hdma_usart2_rx.Instance->CNDTR;
        qbuffer[ch].out = qbuffer[ch].in;
      }
      HAL_UARTEx_SetTxFifoThreshold(&huart2, UART_TXFIFO_THRESHOLD_1_8);
      HAL_UARTEx_SetRxFifoThreshold(&huart2, UART_RXFIFO_THRESHOLD_1_8);
      HAL_UARTEx_DisableFifoMode(&huart2);
      break;

    default:
      ret = false;
      break;
  }

  return ret;
}

bool uartClose(uint8_t ch)
{
  return true;
}

uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret = 0;

  switch(ch)
  {
    case _DEF_USB:
      ret = cdcAvailable();
      break;

    case _DEF_UART2:
      qbuffer[ch].in = (qbuffer[ch].len - hdma_usart2_rx.Instance->CNDTR);
      ret = qbufferAvailable(&qbuffer[ch]);
      break;
  }

  return ret;
}

bool uartFlush(uint8_t ch)
{
  uint32_t pre_time;

  pre_time = millis();
  while(uartAvailable(ch))
  {
    if (millis()-pre_time >= 10)
    {
      break;
    }
    uartRead(ch);
  }

  return true;
}

uint8_t uartRead(uint8_t ch)
{
  uint8_t ret = 0;

  switch(ch)
  {
    case _DEF_USB:
      ret = cdcRead();
      break;

    case _DEF_UART2:
      qbufferRead(&qbuffer[_DEF_UART2], &ret, 1);
      break;
  }

  return ret;
}

uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  uint32_t ret = 0;
  HAL_StatusTypeDef status;


  switch(ch)
  {
    case _DEF_USB:
      ret = cdcWrite(p_data, length);
      break;

    case _DEF_UART2:
      status = HAL_UART_Transmit(&huart2, p_data, length, 100);
      if (status == HAL_OK)
      {
        ret = length;
      }
      break;
  }

  return ret;
}

uint32_t uartPrintf(uint8_t ch, char *fmt, ...)
{
  char buf[256];
  va_list args;
  int len;
  uint32_t ret;

  va_start(args, fmt);
  len = vsnprintf(buf, 256, fmt, args);

  ret = uartWrite(ch, (uint8_t *)buf, len);

  va_end(args);


  return ret;
}

uint32_t uartGetBaud(uint8_t ch)
{
  uint32_t ret = 0;


  switch(ch)
  {
    case _DEF_USB:
      ret = cdcGetBaud();
      break;

    case _DEF_UART2:
      ret = huart2.Init.BaudRate;
      break;
  }

  return ret;
}




void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART2)
  {
  }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if 0
  if (huart->Instance == USART2)
  {
    qbufferWrite(&qbuffer[_DEF_UART1], &rx_buf, 1);

    HAL_UART_Receive_IT(&huart1, (uint8_t *)&rx_buf, 1);
  }
#endif
}




void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */

  /** Initializes the peripherals clocks
  */
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
    PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit);

    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 DMA Init */
    /* USART2_RX Init */
    hdma_usart2_rx.Instance = DMA1_Channel1;
    hdma_usart2_rx.Init.Request = DMA_REQUEST_USART2_RX;
    hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
    hdma_usart2_rx.Init.Mode = DMA_CIRCULAR;
    hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
    HAL_DMA_Init(&hdma_usart2_rx);

    __HAL_LINKDMA(uartHandle,hdmarx,hdma_usart2_rx);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{
  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 DMA DeInit */
    HAL_DMA_DeInit(uartHandle->hdmarx);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
}
#endif
