/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

void hwInit(void);
void SystemClock_Config(void);

uint32_t pre_time = 0;
uint32_t dt = 0;
uint32_t dt_tmp = 0;
can_msg_t tx_msg;
can_msg_t rx_msg =
		{
				.id = 0,
				.length = 0,
				.data = {0,},
				.dlc = CAN_DLC_0,
				.id_type = CAN_EXT,
				.frame = CAN_CLASSIC
		};

int main(void)
{
  HAL_Init();

  SystemClock_Config();

  hwInit();

  pre_time = micros();
  dt = micros();

  while (1)
  {
	  if(micros()-pre_time >= 500000)
	  {
	    pre_time = micros();
	    ledToggle(0);

	    tx_msg.frame   = CAN_CLASSIC;
	    tx_msg.id_type = CAN_EXT;
	    tx_msg.dlc     = CAN_DLC_3;
	    tx_msg.id      = 0x314;
	    tx_msg.length  = 3;
	    tx_msg.data[0] = 1;
	    tx_msg.data[1] = 2;
	    tx_msg.data[2] = 3;
      canMsgWrite(_DEF_CAN2, &tx_msg, 10);

      if (canUpdate())
      {
        cliPrintf("BusOff Recovery\n");
      }
      if (canMsgAvailable(_DEF_CAN2))
      {
        canMsgRead(_DEF_CAN2, &rx_msg);
      }
	  }
	  if (lcdDrawAvailable() == true)
	  {
	    lcdSetFont(LCD_FONT_HAN);
	    lcdDrawFillRect(0, 0, LCD_WIDTH, LCD_HEIGHT, black);
	    lcdPrintf(0,16*0, white, "[CAN 통신 하자!]");
	    lcdPrintf(0,16*1, white, "ID : 0x%08X", rx_msg.id);
	    lcdPrintf(0,16*2, white, "DLC : %d", rx_msg.length);
	    lcdPrintf(0,16*3, white, "DATA : %d %d", rx_msg.data[0], rx_msg.data[1]);
	    lcdRequestDraw();
	  }
    cliMain();
  }

}

void hwInit(void)
{
  #ifdef _USE_HW_RTC
    rtcInit();
  #endif
#ifdef _USE_HW_RESET
    resetInit();
#endif

  cliInit();
  tim_Begin(_DEF_TIM5);

  logInit();
  gpioInit();
  ledInit();
  spiInit();
  //buttonInit();

  i2cInit();
  lcdInit();

  uartInit();
//  for (int i=0; i<HW_UART_MAX_CH; i++)
//  {
//    uartOpen(i, 115200);
//  }
  uartOpen(_DEF_UART2, 115200);

//  logOpen(HW_LOG_CH, 115200);
//  logPrintf("\r\n[ Firmware Begin... ]\r\n");
//  logPrintf("Booting..Name \t\t: %s\r\n", _DEF_BOARD_NAME);
//  logPrintf("Booting..Ver  \t\t: %s\r\n", _DEF_FIRMWATRE_VERSION);
//  logPrintf("Booting..Clock\t\t: %d Mhz\r\n", (int)HAL_RCC_GetSysClockFreq()/1000000);
//  logPrintf("\n");

  spiFlashInit();
  //flashInit();
  //eepromInit();

	#ifdef _USE_HW_WS2812
		ws2812Init();
	#endif

  usbInit();
  usbBegin(USB_CDC_MODE);

  canInit();
  //canOpen(_DEF_CAN2, CAN_LOOPBACK, CAN_CLASSIC, CAN_500K, CAN_500K);
  canOpen(_DEF_CAN2, CAN_NORMAL, CAN_CLASSIC, CAN_500K, CAN_2M);

  cliOpen(_DEF_USB, 115200);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Configure LSE Drive Capability
  */
  HAL_PWR_EnableBkUpAccess();
  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI48|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSI48State = RCC_HSI48_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV2;
  RCC_OscInitStruct.PLL.PLLN = 75;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
