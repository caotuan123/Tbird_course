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
#define LE_Z_Pin GPIO_PIN_3
#define LE_Z_GPIO_Port GPIOE
#define LD_Z_Pin GPIO_PIN_4
#define LD_Z_GPIO_Port GPIOE
#define LC_S_Pin GPIO_PIN_5
#define LC_S_GPIO_Port GPIOE
#define LE_P_Pin GPIO_PIN_6
#define LE_P_GPIO_Port GPIOE
#define OnBoard_but_Pin GPIO_PIN_13
#define OnBoard_but_GPIO_Port GPIOC
#define LE_S_Pin GPIO_PIN_0
#define LE_S_GPIO_Port GPIOF
#define LC_Z_Pin GPIO_PIN_1
#define LC_Z_GPIO_Port GPIOF
#define LC_P_Pin GPIO_PIN_2
#define LC_P_GPIO_Port GPIOF
#define LB_Z2_Pin GPIO_PIN_3
#define LB_Z2_GPIO_Port GPIOF
#define LA_Z_Pin GPIO_PIN_0
#define LA_Z_GPIO_Port GPIOC
#define LB_S_Pin GPIO_PIN_3
#define LB_S_GPIO_Port GPIOC
#define LA_P_Pin GPIO_PIN_3
#define LA_P_GPIO_Port GPIOA
#define LG2_P_Pin GPIO_PIN_4
#define LG2_P_GPIO_Port GPIOA
#define LV_F_Pin GPIO_PIN_5
#define LV_F_GPIO_Port GPIOA
#define LV_P1_Pin GPIO_PIN_6
#define LV_P1_GPIO_Port GPIOA
#define LD_S_Pin GPIO_PIN_7
#define LD_S_GPIO_Port GPIOA
#define LEDgreen_Pin GPIO_PIN_0
#define LEDgreen_GPIO_Port GPIOB
#define LG1_Z_Pin GPIO_PIN_12
#define LG1_Z_GPIO_Port GPIOF
#define Button1_Pin GPIO_PIN_13
#define Button1_GPIO_Port GPIOF
#define Button2_Pin GPIO_PIN_9
#define Button2_GPIO_Port GPIOE
#define LEDred_Pin GPIO_PIN_14
#define LEDred_GPIO_Port GPIOB
#define BTNV2_Pin GPIO_PIN_14
#define BTNV2_GPIO_Port GPIOD
#define LG2_Z_Pin GPIO_PIN_15
#define LG2_Z_GPIO_Port GPIOD
#define LE_Z2_Pin GPIO_PIN_7
#define LE_Z2_GPIO_Port GPIOC
#define LD_P_Pin GPIO_PIN_4
#define LD_P_GPIO_Port GPIOD
#define LB_Z_Pin GPIO_PIN_5
#define LB_Z_GPIO_Port GPIOD
#define LB_P_Pin GPIO_PIN_6
#define LB_P_GPIO_Port GPIOD
#define LA_S_Pin GPIO_PIN_7
#define LA_S_GPIO_Port GPIOD
#define BTNV1_Pin GPIO_PIN_3
#define BTNV1_GPIO_Port GPIOB
#define LG1_P_Pin GPIO_PIN_4
#define LG1_P_GPIO_Port GPIOB
#define LV_P2_Pin GPIO_PIN_5
#define LV_P2_GPIO_Port GPIOB
#define LEDblue_Pin GPIO_PIN_7
#define LEDblue_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
