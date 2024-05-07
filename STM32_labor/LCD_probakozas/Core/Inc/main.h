/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32f7xx_hal.h"

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
#define KB_PC0_IN_LEFT_Pin GPIO_PIN_13
#define KB_PC0_IN_LEFT_GPIO_Port GPIOF
#define KB_PC3_OUT_ROW1_Pin GPIO_PIN_14
#define KB_PC3_OUT_ROW1_GPIO_Port GPIOF
#define KB_PC5_OUT_ROW3_Pin GPIO_PIN_15
#define KB_PC5_OUT_ROW3_GPIO_Port GPIOF
#define LCD_RS_Pin GPIO_PIN_7
#define LCD_RS_GPIO_Port GPIOE
#define KB_PC1_IN_CENTER_Pin GPIO_PIN_9
#define KB_PC1_IN_CENTER_GPIO_Port GPIOE
#define LCD_E_Pin GPIO_PIN_10
#define LCD_E_GPIO_Port GPIOE
#define KB_PC2_IN_RIGHT_Pin GPIO_PIN_11
#define KB_PC2_IN_RIGHT_GPIO_Port GPIOE
#define LCD_DATA_4_Pin GPIO_PIN_12
#define LCD_DATA_4_GPIO_Port GPIOE
#define KB_PC4_OUT_ROW2_Pin GPIO_PIN_13
#define KB_PC4_OUT_ROW2_GPIO_Port GPIOE
#define LCD_DATA_5_Pin GPIO_PIN_14
#define LCD_DATA_5_GPIO_Port GPIOE
#define LCD_DATA_6_Pin GPIO_PIN_15
#define LCD_DATA_6_GPIO_Port GPIOE
#define LCD_DATA_7_Pin GPIO_PIN_10
#define LCD_DATA_7_GPIO_Port GPIOB
#define KB_PC6_OUT_ROW4_Pin GPIO_PIN_14
#define KB_PC6_OUT_ROW4_GPIO_Port GPIOG
#define led_blue_Pin GPIO_PIN_7
#define led_blue_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
