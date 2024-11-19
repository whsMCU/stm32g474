/*
 * ws2812.c
 *
 *  Created on: Nov 19, 2024
 *      Author: WANG
 */


#include "ws2812.h"



#ifdef _USE_HW_WS2812
#include "cli.h"

#define BIT_PERIOD (130) // 1300ns, 80Mhz
#define BIT_HIGH   (70)  // 700ns
#define BIT_LOW    (35)  // 350ns
#define BIT_ZERO   (50)

bool is_init = false;


typedef struct
{
  TIM_HandleTypeDef *h_timer;
  uint32_t channel;
  uint16_t led_cnt;
} ws2812_t;

static uint8_t bit_buf[BIT_ZERO + 24*(HW_WS2812_MAX_CH+1)];


ws2812_t ws2812;
TIM_HandleTypeDef htim2;
DMA_HandleTypeDef hdma_tim2_ch1;

static void cliCmd(cli_args_t *args);

static bool ws2812InitHw(void);

bool ws2812Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  memset(bit_buf, 0, sizeof(bit_buf));

  ws2812.h_timer = &htim2;
  ws2812.channel = TIM_CHANNEL_1;

  // Timer
  //
  htim2.Instance 							 = TIM2;
  htim2.Init.Prescaler 				 = 2; // 300MHz / (2+1) = 100Mhz -> 10ns
  htim2.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim2.Init.Period            = BIT_PERIOD-1;
  htim2.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.RepetitionCounter = 0;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  HAL_TIM_Base_Init(&htim2);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig);

  HAL_TIM_PWM_Init(&htim2);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode     = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

  sConfigOC.OCMode 			= TIM_OCMODE_PWM1;
  sConfigOC.Pulse				= 0;
  sConfigOC.OCPolarity 	= TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode 	= TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);

  ws2812InitHw();

  ws2812.led_cnt = WS2812_MAX_CH;
  is_init = true;

  for (int i=0; i<WS2812_MAX_CH; i++)
  {
    ws2812SetColor(i, WS2812_COLOR_OFF);
  }
  ws2812Refresh();

  cliAdd("ws2812", cliCmd);

  return true;
}

bool ws2812InitHw(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOA_CLK_ENABLE();
  /**TIM2 GPIO Configuration
  PA15     ------> TIM2_CH1
  */
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM2;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* TIM2 clock enable */
  __HAL_RCC_TIM2_CLK_ENABLE();

  /* TIM2 DMA Init */
  /* TIM2_CH1 Init */
  hdma_tim2_ch1.Instance = DMA1_Channel4;
  hdma_tim2_ch1.Init.Request = DMA_REQUEST_TIM2_CH1;
  hdma_tim2_ch1.Init.Direction = DMA_MEMORY_TO_PERIPH;
  hdma_tim2_ch1.Init.PeriphInc = DMA_PINC_DISABLE;
  hdma_tim2_ch1.Init.MemInc = DMA_MINC_ENABLE;
  hdma_tim2_ch1.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
  hdma_tim2_ch1.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
  hdma_tim2_ch1.Init.Mode = DMA_NORMAL;
  hdma_tim2_ch1.Init.Priority = DMA_PRIORITY_LOW;
  HAL_DMA_Init(&hdma_tim2_ch1);

  __HAL_LINKDMA(&htim2, hdma[TIM_DMA_ID_CC1], hdma_tim2_ch1);

  /* DMA1_Channel4_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel4_IRQn);

  /* TIM2 interrupt Init */
  HAL_NVIC_SetPriority(TIM2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIM2_IRQn);

  return true;
}

bool ws2812Refresh(void)
{
  HAL_TIM_PWM_Stop_DMA(ws2812.h_timer, ws2812.channel);
  HAL_TIM_PWM_Start_DMA(ws2812.h_timer, ws2812.channel,  (const uint32_t *)bit_buf, sizeof(bit_buf));
  return true;
}

void ws2812SetColor(uint32_t ch, uint32_t color)
{
  uint8_t r_bit[8];
  uint8_t g_bit[8];
  uint8_t b_bit[8];
  uint8_t red;
  uint8_t green;
  uint8_t blue;
  uint32_t offset;

  if (ch >= WS2812_MAX_CH)
    return;

  red   = (color >> 16) & 0xFF;
  green = (color >> 8) & 0xFF;
  blue  = (color >> 0) & 0xFF;


  for (int i=0; i<8; i++)
  {
    if (red & (1<<7))
    {
      r_bit[i] = BIT_HIGH;
    }
    else
    {
      r_bit[i] = BIT_LOW;
    }
    red <<= 1;

    if (green & (1<<7))
    {
      g_bit[i] = BIT_HIGH;
    }
    else
    {
      g_bit[i] = BIT_LOW;
    }
    green <<= 1;

    if (blue & (1<<7))
    {
      b_bit[i] = BIT_HIGH;
    }
    else
    {
      b_bit[i] = BIT_LOW;
    }
    blue <<= 1;
  }

  offset = BIT_ZERO;

  memcpy(&bit_buf[offset + ch*24 + 8*0], g_bit, 8*1);
  memcpy(&bit_buf[offset + ch*24 + 8*1], r_bit, 8*1);
  memcpy(&bit_buf[offset + ch*24 + 8*2], b_bit, 8*1);
}


void cliCmd(cli_args_t *args)
{
  bool ret = false;


  if (args->argc == 1 && args->isStr(0, "info"))
  {
    cliPrintf("ws2812 led cnt : %d\n", WS2812_MAX_CH);
    ret = true;
  }

  if (args->argc == 1 && args->isStr(0, "test"))
  {
    uint32_t color[6] = {WS2812_COLOR_RED,
                         WS2812_COLOR_OFF,
                         WS2812_COLOR_GREEN,
                         WS2812_COLOR_OFF,
                         WS2812_COLOR_BLUE,
                         WS2812_COLOR_OFF};

    uint8_t color_idx = 0;
    uint32_t pre_time;


    pre_time = millis();
    while(cliKeepLoop())
    {
      if (millis()-pre_time >= 500)
      {
        pre_time = millis();

        for (int i=0; i<WS2812_MAX_CH; i++)
        {
          ws2812SetColor(i, color[color_idx]);
        }
        ws2812Refresh();
        color_idx = (color_idx + 1) % 6;
      }

    }

    for (int i=0; i<WS2812_MAX_CH; i++)
    {
      ws2812SetColor(i, WS2812_COLOR_OFF);
    }
    ws2812Refresh();

    ret = true;
  }


  if (args->argc == 5 && args->isStr(0, "color"))
  {
    uint8_t  ch;
    uint8_t red;
    uint8_t green;
    uint8_t blue;

    ch    = (uint8_t)args->getData(1);
    red   = (uint8_t)args->getData(2);
    green = (uint8_t)args->getData(3);
    blue  = (uint8_t)args->getData(4);

    ws2812SetColor(ch, WS2812_COLOR(red, green, blue));
    ws2812Refresh();

    while(cliKeepLoop())
    {
    }
    ws2812SetColor(0, 0);
    ws2812Refresh();
    ret = true;
  }

  if (ret == false)
  {
    cliPrintf("ws2812 info\n");
    cliPrintf("ws2812 test\n");
    cliPrintf("ws2812 color ch r g b\n");
  }
}

#endif
