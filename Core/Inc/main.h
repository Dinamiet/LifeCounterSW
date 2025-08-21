/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32c0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define PWR_Ctrl_Pin GPIO_PIN_9
#define PWR_Ctrl_GPIO_Port GPIOB
#define PWR_OK_Pin GPIO_PIN_15
#define PWR_OK_GPIO_Port GPIOC
#define Encoder2CLK_Pin GPIO_PIN_0
#define Encoder2CLK_GPIO_Port GPIOA
#define Encoder2DAT_Pin GPIO_PIN_1
#define Encoder2DAT_GPIO_Port GPIOA
#define Encoder2BTN_Pin GPIO_PIN_2
#define Encoder2BTN_GPIO_Port GPIOA
#define Disp2LAT_Pin GPIO_PIN_3
#define Disp2LAT_GPIO_Port GPIOA
#define Disp2CLR_Pin GPIO_PIN_4
#define Disp2CLR_GPIO_Port GPIOA
#define DispOE_Pin GPIO_PIN_6
#define DispOE_GPIO_Port GPIOA
#define Buzzer_Pin GPIO_PIN_7
#define Buzzer_GPIO_Port GPIOA
#define Encoder1CLK_Pin GPIO_PIN_0
#define Encoder1CLK_GPIO_Port GPIOB
#define Encoder1DAT_Pin GPIO_PIN_1
#define Encoder1DAT_GPIO_Port GPIOB
#define Encoder1BTN_Pin GPIO_PIN_2
#define Encoder1BTN_GPIO_Port GPIOB
#define Heartbeat_Pin GPIO_PIN_6
#define Heartbeat_GPIO_Port GPIOC
#define Disp1LAT_Pin GPIO_PIN_3
#define Disp1LAT_GPIO_Port GPIOB
#define Disp1CLR_Pin GPIO_PIN_4
#define Disp1CLR_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
