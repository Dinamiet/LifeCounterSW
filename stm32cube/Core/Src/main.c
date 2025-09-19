/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void dispClear()
{
  HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Disp1CLR_GPIO_Port, Disp1CLR_Pin, GPIO_PIN_RESET);
  HAL_GPIO_WritePin(Disp2CLR_GPIO_Port, Disp2CLR_Pin, GPIO_PIN_RESET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(Disp1CLR_GPIO_Port, Disp1CLR_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Disp2CLR_GPIO_Port, Disp2CLR_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_SET);
}

void dispEnabled(bool enable)
{
  HAL_GPIO_WritePin(DispOE_GPIO_Port, DispOE_Pin, !enable);
}

void disp1Write(uint8_t number, uint8_t digit, uint8_t status, uint8_t dp)
{
  static uint8_t lookup[16] = {
      0x3F, // 0
      0x06, // 1
      0x5B, // 2
      0x4F, // 3
      0x66, // 4
      0x6D, // 5
      0x7D, // 6
      0x07, // 7
      0x7F, // 8
      0x67, // 9
      0x77, // A
      0x7C, // B
      0x39, // C
      0x5E, // D
      0x79, // E
      0x71, // F
  };
  struct
  {
    uint8_t ActiveDigit : 4;
    uint8_t StatusLEDs : 4;
    uint8_t Value : 7;
    uint8_t Point : 1;
  } data;

  if (digit >= 4)
    return;
  if (number >= sizeof(lookup))
    return;

  data.StatusLEDs = status;
  data.ActiveDigit = 1 << digit;
  data.Value = ~lookup[number];
  data.Point = !dp;

  HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_RESET);
  HAL_StatusTypeDef transStatus = HAL_SPI_Transmit(&hspi1, (void *)&data, sizeof(data), 1);
  if (transStatus != HAL_OK)
  {
    HAL_GPIO_WritePin(Heartbeat_GPIO_Port, Heartbeat_Pin, GPIO_PIN_SET);
    while (1)
      ;
  }
  HAL_GPIO_WritePin(Disp1LAT_GPIO_Port, Disp1LAT_Pin, GPIO_PIN_SET);
}

void disp2Write(uint8_t number, uint8_t digit, uint8_t status, uint8_t dp)
{
  static uint8_t lookup[16] = {
      0x3F, // 0
      0x06, // 1
      0x5B, // 2
      0x4F, // 3
      0x66, // 4
      0x6D, // 5
      0x7D, // 6
      0x07, // 7
      0x7F, // 8
      0x67, // 9
      0x77, // A
      0x7C, // B
      0x39, // C
      0x5E, // D
      0x79, // E
      0x71, // F
  };
  struct
  {
    uint8_t ActiveDigit : 4;
    uint8_t StatusLEDs : 4;
    uint8_t Value : 7;
    uint8_t Point : 1;
  } data;

  if (digit >= 4)
    return;
  if (number >= sizeof(lookup))
    return;

  data.StatusLEDs = status;
  data.ActiveDigit = 1 << digit;
  data.Value = ~lookup[number];
  data.Point = !dp;

  HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_RESET);
  HAL_StatusTypeDef transStatus = HAL_SPI_Transmit(&hspi1, (void *)&data, sizeof(data), 1);
  if (transStatus != HAL_OK)
  {
    HAL_GPIO_WritePin(Heartbeat_GPIO_Port, Heartbeat_Pin, GPIO_PIN_SET);
    while (1)
      ;
  }
  HAL_GPIO_WritePin(Disp2LAT_GPIO_Port, Disp2LAT_Pin, GPIO_PIN_SET);
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int _main_(void)
{

  /* USER CODE BEGIN 1 */

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
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM16_Init();
  /* USER CODE BEGIN 2 */
  dispClear();
  dispEnabled(true);
  const int timing = 1;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    disp1Write(1, 0, 0, 0);
    HAL_Delay(timing);
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

  __HAL_FLASH_SET_LATENCY(FLASH_LATENCY_0);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
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
#ifdef USE_FULL_ASSERT
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
