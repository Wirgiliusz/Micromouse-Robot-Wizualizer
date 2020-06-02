/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma2d.h"
#include "i2c.h"
#include "ltdc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "fmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f429i_discovery_lcd.h"
#include "robot.h"
#include "funkcje_rysujace.h"
#include <stdlib.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define OPOZNIENIE_SYMULUJACE_RUCH 200
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int szerokoscSygnalu = 0; 	// Szerokosc sygnalu PWM (0-1000)
int narysowano = 0; 		// Zmienna pomocnicza zapobiegajaca cyklicznemu rysowaniu sie na wyswietlaczu
Robot robot; 	// Obiekt robota (pozycja x, pozycja y, orientacja)
uint8_t odebraneDane; 		// Dane odebrane od modulu Bluetooth
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
// Przerwanie dla nacisniecia przycisku USER
/*
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if(GPIO_Pin == BUTTON_Pin) {
		HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
		if(szerokoscSygnalu > 1000) {
			szerokoscSygnalu = 0;
		}
		szerokoscSygnalu += 10;
		__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, szerokoscSygnalu);
		__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, szerokoscSygnalu);

		rysujPredkosc(szerokoscSygnalu);
	}
}
*/

// Przerwanie dla odebrania danych z modulu BT
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	switch(atoi(&odebraneDane)) {
	case 1:
		rysujDebug(1);
		HAL_UART_Transmit(&huart1, "elo1", 4, 100);
	break;
	case 2:
		rysujDebug(2);
		HAL_UART_Transmit(&huart1, "elo2", 4, 100);
	break;
	case 3:
		rysujDebug(3);
		HAL_UART_Transmit(&huart1, "elo3", 4, 100);
	break;
	}
	HAL_UART_Receive_IT(&huart1, &odebraneDane, 1);
}


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	robot = konstruktorRobota(0, 0, Wschod);
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM4_Init();
  MX_ADC1_Init();
  MX_DMA2D_Init();
  MX_FMC_Init();
  MX_I2C3_Init();
  MX_LTDC_Init();
  MX_SPI5_Init();
  MX_TIM2_Init();
  MX_TIM9_Init();
  MX_USART1_UART_Init();
  MX_TIM5_Init();
  MX_TIM3_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1, &odebraneDane, 1); // odebieranie danych z BT o wielkosci 1

  // Inicjalizacja LCD
  BSP_LCD_Init();
  BSP_LCD_LayerDefaultInit(LCD_BACKGROUND_LAYER, LCD_FRAME_BUFFER);
  BSP_LCD_LayerDefaultInit(LCD_FOREGROUND_LAYER, LCD_FRAME_BUFFER);
  BSP_LCD_SelectLayer(LCD_FOREGROUND_LAYER);
  BSP_LCD_DisplayOn();
  BSP_LCD_Clear(LCD_COLOR_WHITE);

  // Inicjalizacja PWM
  __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_1, 0);
  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);

  __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 0);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

  __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_1, 0);
  HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);

  __HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, 0);
  HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);

  // Inicjalizacja ADC
  HAL_ADC_Start(&hadc1);

  // Inicjalizacja licznika enkodera
  HAL_TIM_Base_Start(&htim5);	// Enkoder R (PA0)
  HAL_TIM_Base_Start(&htim3);	// Enkoder L (P14)

  inicjalizujRysowanie();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	skanujObszar(&robot);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	// Symulacja ruchu robota przez labirynt //

	if(!narysowano) {
		//HAL_Delay(3000);
		//przeszukajLabirynt(&robot);
		/*
		jedzProsto(&robot);
		jedzProsto(&robot);
		jedzPrawo(&robot);
		jedzLewo(&robot);
		jedzLewo(&robot);
		jedzTyl(&robot);
		*/

		narysowano = 1;
    }

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Activate the Over-Drive mode 
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV8;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV8;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
  PeriphClkInitStruct.PLLSAI.PLLSAIN = 216;
  PeriphClkInitStruct.PLLSAI.PLLSAIR = 2;
  PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
