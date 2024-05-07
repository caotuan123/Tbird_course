/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  ***-
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim4;

/* USER CODE BEGIN PV */
typedef struct allapotok
{
	uint8_t led_a_p;
	uint8_t led_a_s;
	uint8_t led_a_z;

	uint8_t led_b_p;
	uint8_t led_b_s;
	uint8_t led_b_z;
	uint8_t led_b_z2;

	uint8_t led_c_p;
	uint8_t led_c_s;
	uint8_t led_c_z;

	uint8_t led_d_p;
	uint8_t led_d_s;
	uint8_t led_d_z;

	uint8_t led_e_p;
	uint8_t led_e_s;
	uint8_t led_e_z;
	uint8_t led_e_z2;

	uint8_t led_g1_p;
	uint8_t led_g1_z;

	uint8_t led_g2_p;
	uint8_t led_g2_z;

	uint8_t led_v_p1;
	uint8_t led_v_p2;
	uint8_t led_v_f;

	uint8_t szamlalo;
	uint8_t szamlalo_tmp;

}allapot;

typedef struct pwm_allapotok
{
	uint8_t led_g1_z;
	uint8_t led_g2_z;
	uint8_t led_v_p1;
	uint8_t led_v_p2;
	uint8_t led_v_f;

}pwm_allapot;

pwm_allapot led_pwm_allapot={0,0,0,0,1};

//     		a_p,a_s,a_z,b_p,b_s,b_z,b_z2,c_p,c_s,c_z,d_p,d_s,d_z,e_p,e_s,e_z,e_z2,g1_p,g1_z,g2_p,g2_z,v_p1,v_p2,v_f
allapot nappali[10]={
	 /*0*/ {1,  0,  0,  1,  0,  0,  0,   1,  0,  0,  1,  0,  0,  1,  0,  0,  0,   1,   0,   1,   0,   0,   0,   0,  4,  0 },
	 /*9*/ {1,  1,  0,  0,  1,  0,  0,   1,  0,  0,  0,  1,  0,  1,  0,  0,  0,   1,   0,   1,   0,   0,   0,   0,  2,  0 },
	 /*1*/ {0,  0,  1,  1,  0,  0,  0,   1,  0,  0,  1,  0,  0,  1,  0,  0,  0,   0,   1,   1,   0,   0,   0,   0,  10,  0 },
	 /*2*/ {0,  1,  0,  1,  0,  0,  0,   1,  0,  0,  1,  0,  0,  1,  0,  0,  0,   0,   2,   1,   0,   0,   0,   0,  2,  0 },
	 /*3*/ {0,  1,  0,  1,  0,  0,  0,   1,  1,  0,  1,  0,  0,  1,  1,  0,  0,   0,   2,   1,   0,   0,   0,   0,  2,  0 },
	 /*4*/ {1,  0,  0,  1,  0,  0,  0,   0,  0,  1,  1,  0,  0,  0,  0,  1,  1,   1,   0,   0,   1,   0,   0,   0,  10,  0 },
	 /*5*/ {1,  0,  0,  1,  0,  0,  0,   0,  1,  0,  1,  0,  0,  0,  1,  0,  0,   1,   0,   0,   2,   0,   0,   0,  2,  0 },
	 /*6*/ {1,  0,  0,  1,  1,  0,  0,   0,  1,  0,  1,  1,  0,  0,  1,  0,  0,   1,   0,   0,   2,   0,   0,   0,  2,  0 },
	 /*7*/ {1,  0,  0,  0,  0,  1,  1,   1,  0,  0,  0,  0,  1,  1,  0,  0,  0,   1,   0,   1,   0,   0,   0,   0,  10,  0 },
	 /*8*/ {1,  0,  0,  0,  1,  0,  0,   1,  0,  0,  0,  1,  0,  1,  0,  0,  0,   1,   0,   1,   0,   0,   0,   0,  2,  0 }


};

allapot nappali_v[10]={
				/*0*/ {1,  0,  0,  1,  0,  0,  0,   1,  0,  0,  1,  0,  0,  1,  0,  0,  0,   1,   0,   1,   0,   0,   0,   0,  4,  0 },
				/*9*/ {1,  1,  0,  0,  1,  0,  0,   1,  0,  0,  0,  1,  0,  1,  0,  0,  0,   1,   0,   1,   0,   0,   0,   0,  2,  0 },
				/*1*/ {0,  0,  1,  1,  0,  0,  0,   1,  0,  0,  1,  0,  0,  1,  0,  0,  0,   0,   1,   1,   0,   0,   0,   0,  10,  0 },
				/*2*/ {0,  1,  0,  1,  0,  0,  0,   1,  0,  0,  1,  0,  0,  1,  0,  0,  0,   0,   2,   1,   0,   0,   0,   0,  2,  0 },
				/*3*/ {0,  1,  0,  1,  0,  0,  0,   1,  1,  0,  1,  0,  0,  1,  1,  0,  0,   0,   2,   1,   0,   0,   0,   0,  2,  0 },
				/*4*/ {1,  0,  0,  1,  0,  0,  0,   0,  0,  1,  1,  0,  0,  0,  0,  1,  0,   1,   0,   0,   1,   0,   0,   0,  10,  0 },
				/*5*/ {1,  0,  0,  1,  0,  0,  0,   0,  1,  0,  1,  0,  0,  0,  1,  0,  0,   1,   0,   0,   2,   0,   0,   0,  2,  0 },
				/*6*/ {1,  0,  0,  1,  1,  0,  0,   0,  1,  0,  1,  1,  0,  0,  1,  0,  0,   1,   0,   0,   2,   0,   0,   0,  2,  0 },
				/*7*/ {1,  0,  0,  0,  0,  0,  1,   1,  0,  0,  0,  0,  1,  1,  0,  0,  0,   1,   0,   1,   0,   0,   0,   0,  10,  0 },
				/*8*/ {1,  0,  0,  0,  1,  0,  0,   1,  0,  0,  0,  1,  0,  1,  0,  0,  0,   1,   0,   1,   0,   0,   0,   0,  2,  0 }


				 };
int i=0;
uint8_t pwm1=0;
uint8_t pwm2=0;
uint16_t timer0_counter=0;
uint8_t timer0_counter_1=0;
uint8_t timer0_counter_2=0;
uint8_t regi_gomb=0;
uint8_t Jon_a_vonat=0;;//1-> jon a vonat, 0->nincs vonat
uint8_t mod_valasztas=1;//1-> nappali, 0->ejszakasi

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MPU_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM4_Init(void);
/* USER CODE BEGIN PFP */
void do_traffic(allapot *mod);
void nappali_mod(void);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */









 if(htim->Instance == htim4.Instance)
  {
	timer0_counter++;
	if(timer0_counter==10000)
		{
			pwm1=0;
			timer0_counter=0;
		}
	if(timer0_counter>5000)
	{
		timer0_counter_1++;
		if(timer0_counter_1==100)
		{
			pwm1++;
			if(pwm1==50) pwm1=0;
			timer0_counter_1=0;
		}
		if(pwm1>timer0_counter_1)
			{
				if(!mod_valasztas)//ejszaka
				{
					HAL_GPIO_WritePin(LA_S_GPIO_Port,LA_S_Pin,1);
					HAL_GPIO_WritePin(LB_S_GPIO_Port,LB_S_Pin,1);
					HAL_GPIO_WritePin(LC_S_GPIO_Port,LC_S_Pin,1);
					HAL_GPIO_WritePin(LD_S_GPIO_Port,LD_S_Pin,1);
					HAL_GPIO_WritePin(LE_S_GPIO_Port,LE_S_Pin,1);
				}
				if (led_pwm_allapot.led_g1_z)
					HAL_GPIO_WritePin(LG1_Z_GPIO_Port,LG1_Z_Pin,1);
				if(led_pwm_allapot.led_g2_z)
					HAL_GPIO_WritePin(LG2_Z_GPIO_Port,LG2_Z_Pin,1);
				if(led_pwm_allapot.led_v_f)
					HAL_GPIO_WritePin(LV_F_GPIO_Port,LV_F_Pin,1);
				if (Jon_a_vonat)
					HAL_GPIO_WritePin(LV_P1_GPIO_Port,LV_P1_Pin,1);
			}
		else
			{
				if(!mod_valasztas)//ejszaka
				{
					HAL_GPIO_WritePin(LA_S_GPIO_Port,LA_S_Pin,0);
					HAL_GPIO_WritePin(LB_S_GPIO_Port,LB_S_Pin,0);
					HAL_GPIO_WritePin(LC_S_GPIO_Port,LC_S_Pin,0);
					HAL_GPIO_WritePin(LD_S_GPIO_Port,LD_S_Pin,0);
					HAL_GPIO_WritePin(LE_S_GPIO_Port,LE_S_Pin,0);
				}
				if (led_pwm_allapot.led_g1_z)
					HAL_GPIO_WritePin(LG1_Z_GPIO_Port,LG1_Z_Pin,0);
				if(led_pwm_allapot.led_g2_z)
					HAL_GPIO_WritePin(LG2_Z_GPIO_Port,LG2_Z_Pin,0);
				if(led_pwm_allapot.led_v_f)
					HAL_GPIO_WritePin(LV_F_GPIO_Port,LV_F_Pin,0);
				if (Jon_a_vonat)
					HAL_GPIO_WritePin(LV_P1_GPIO_Port,LV_P1_Pin,0);
			}

	}
	else
	{
				timer0_counter_2++;
				if(timer0_counter_2==100)
				{
					pwm2++;
					if(pwm2==50) pwm2=0;
					timer0_counter_2=0;
				}
				if(pwm2>timer0_counter_2)
				{
					if(Jon_a_vonat)
					HAL_GPIO_WritePin(LV_P2_GPIO_Port,LV_P2_Pin,1);
				}
				else
				{
					if(Jon_a_vonat)
					HAL_GPIO_WritePin(LV_P2_GPIO_Port,LV_P2_Pin,0);
				}
	}
  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MPU Configuration--------------------------------------------------------*/
  MPU_Config();

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
  MX_TIM2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  HAL_TIM_Base_Start_IT(&htim4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  uint8_t button_tmp;

  uint8_t regi_vonat_gomb1=0;
  uint8_t vonat_but=0;
  while (1)
  {

	  vonat_but=0;
	  if(!HAL_GPIO_ReadPin(Button1_GPIO_Port,Button1_Pin))
	  {
		  while(!HAL_GPIO_ReadPin(Button1_GPIO_Port,Button1_Pin));
		  vonat_but=1;
	  }

	  if(!HAL_GPIO_ReadPin(Button2_GPIO_Port,Button2_Pin))
	  {
	  	  while(!HAL_GPIO_ReadPin(Button2_GPIO_Port,Button2_Pin));
	  	  vonat_but=2;
	  }
	  if(HAL_GPIO_ReadPin(OnBoard_but_GPIO_Port,OnBoard_but_Pin))
	  {
		  while(HAL_GPIO_ReadPin(OnBoard_but_GPIO_Port,OnBoard_but_Pin));
		  button_tmp=(button_tmp+1)%2;
		  switch(button_tmp)
		  			{
		  				case 0: mod_valasztas=1; i=0; break;
		  				case 1:


		  				HAL_GPIO_WritePin(LA_P_GPIO_Port, LA_P_Pin, 0);
		  				HAL_GPIO_WritePin(LA_S_GPIO_Port, LA_S_Pin, 0);
		  				HAL_GPIO_WritePin(LA_Z_GPIO_Port, LA_Z_Pin, 0);
		  				HAL_GPIO_WritePin(LB_P_GPIO_Port, LB_P_Pin, 0);
		  				HAL_GPIO_WritePin(LB_S_GPIO_Port, LB_S_Pin, 0);
		  				HAL_GPIO_WritePin(LB_Z_GPIO_Port, LB_Z_Pin, 0);
		  				HAL_GPIO_WritePin(LB_Z2_GPIO_Port,LB_Z2_Pin, 0);
		  				HAL_GPIO_WritePin(LD_P_GPIO_Port, LD_P_Pin, 0);
		  				HAL_GPIO_WritePin(LD_S_GPIO_Port, LD_S_Pin, 0);
		  				HAL_GPIO_WritePin(LD_Z_GPIO_Port, LD_Z_Pin, 0);
		  				HAL_GPIO_WritePin(LC_P_GPIO_Port, LC_P_Pin, 0);
		  				HAL_GPIO_WritePin(LC_S_GPIO_Port, LC_S_Pin, 0);
		  				HAL_GPIO_WritePin(LC_Z_GPIO_Port, LC_Z_Pin, 0);
		  				HAL_GPIO_WritePin(LE_P_GPIO_Port, LE_P_Pin, 0);
		  				HAL_GPIO_WritePin(LE_S_GPIO_Port, LE_S_Pin, 0);
		  				HAL_GPIO_WritePin(LE_Z_GPIO_Port, LE_Z_Pin, 0);
		  				HAL_GPIO_WritePin(LE_Z2_GPIO_Port, LE_Z2_Pin, 0);
		  				HAL_GPIO_WritePin(LG1_P_GPIO_Port, LG1_P_Pin, 0);
		  				HAL_GPIO_WritePin(LG2_P_GPIO_Port, LG2_P_Pin, 0);
		  				HAL_GPIO_WritePin(LG1_Z_GPIO_Port, LG1_Z_Pin, 0);
		  				HAL_GPIO_WritePin(LG2_Z_GPIO_Port, LG2_Z_Pin, 0);
		  				mod_valasztas=0; i=0; break;
		  				default: break;
		  			}

	  }



		if(vonat_but)
		{
			if((!Jon_a_vonat)&&(!regi_vonat_gomb1))
			{
				regi_vonat_gomb1=vonat_but;
				Jon_a_vonat=1;
				HAL_GPIO_WritePin(LV_F_GPIO_Port,LV_F_Pin,0);
				led_pwm_allapot.led_v_f=0;
			}
			if(Jon_a_vonat&&(regi_vonat_gomb1!=vonat_but))
			{
				regi_vonat_gomb1=0;
				Jon_a_vonat=0;
				HAL_GPIO_WritePin(LV_P1_GPIO_Port,LV_P1_Pin,0);
				HAL_GPIO_WritePin(LV_P2_GPIO_Port,LV_P2_Pin,0);
				led_pwm_allapot.led_v_f=1;
			}

		}


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1599;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 4999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief TIM4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM4_Init(void)
{

  /* USER CODE BEGIN TIM4_Init 0 */

  /* USER CODE END TIM4_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM4_Init 1 */

  /* USER CODE END TIM4_Init 1 */
  htim4.Instance = TIM4;
  htim4.Init.Prescaler = 1599;
  htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim4.Init.Period = 1;
  htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim4) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim4, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM4_Init 2 */

  /* USER CODE END TIM4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LE_Z_Pin|LD_Z_Pin|LC_S_Pin|LE_P_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, LE_S_Pin|LC_Z_Pin|LC_P_Pin|LB_Z2_Pin
                          |LG1_Z_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LA_Z_Pin|LB_S_Pin|LE_Z2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LA_P_Pin|LG2_P_Pin|LV_F_Pin|LV_P1_Pin
                          |LD_S_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LEDgreen_Pin|LEDred_Pin|LG1_P_Pin|LV_P2_Pin
                          |LEDblue_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, LG2_Z_Pin|LD_P_Pin|LB_Z_Pin|LB_P_Pin
                          |LA_S_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LE_Z_Pin LD_Z_Pin LC_S_Pin LE_P_Pin */
  GPIO_InitStruct.Pin = LE_Z_Pin|LD_Z_Pin|LC_S_Pin|LE_P_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : OnBoard_but_Pin */
  GPIO_InitStruct.Pin = OnBoard_but_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(OnBoard_but_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LE_S_Pin LC_Z_Pin LC_P_Pin LB_Z2_Pin
                           LG1_Z_Pin */
  GPIO_InitStruct.Pin = LE_S_Pin|LC_Z_Pin|LC_P_Pin|LB_Z2_Pin
                          |LG1_Z_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : LA_Z_Pin LB_S_Pin LE_Z2_Pin */
  GPIO_InitStruct.Pin = LA_Z_Pin|LB_S_Pin|LE_Z2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : LA_P_Pin LG2_P_Pin LV_F_Pin LV_P1_Pin
                           LD_S_Pin */
  GPIO_InitStruct.Pin = LA_P_Pin|LG2_P_Pin|LV_F_Pin|LV_P1_Pin
                          |LD_S_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LEDgreen_Pin LEDred_Pin LG1_P_Pin LV_P2_Pin
                           LEDblue_Pin */
  GPIO_InitStruct.Pin = LEDgreen_Pin|LEDred_Pin|LG1_P_Pin|LV_P2_Pin
                          |LEDblue_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : Button1_Pin */
  GPIO_InitStruct.Pin = Button1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Button1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : Button2_Pin */
  GPIO_InitStruct.Pin = Button2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(Button2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : BTNV2_Pin */
  GPIO_InitStruct.Pin = BTNV2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BTNV2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LG2_Z_Pin LD_P_Pin LB_Z_Pin LB_P_Pin
                           LA_S_Pin */
  GPIO_InitStruct.Pin = LG2_Z_Pin|LD_P_Pin|LB_Z_Pin|LB_P_Pin
                          |LA_S_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : BTNV1_Pin */
  GPIO_InitStruct.Pin = BTNV1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(BTNV1_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void do_traffic(allapot *mod)
{
	HAL_GPIO_WritePin(LA_P_GPIO_Port, LA_P_Pin, mod[i].led_a_p);
	HAL_GPIO_WritePin(LA_S_GPIO_Port, LA_S_Pin, mod[i].led_a_s);
	HAL_GPIO_WritePin(LA_Z_GPIO_Port, LA_Z_Pin, mod[i].led_a_z);
	HAL_GPIO_WritePin(LB_P_GPIO_Port, LB_P_Pin, mod[i].led_b_p);
	HAL_GPIO_WritePin(LB_S_GPIO_Port, LB_S_Pin, mod[i].led_b_s);
	HAL_GPIO_WritePin(LB_Z_GPIO_Port, LB_Z_Pin, mod[i].led_b_z);
	HAL_GPIO_WritePin(LB_Z2_GPIO_Port,LB_Z2_Pin, mod[i].led_b_z2);
	HAL_GPIO_WritePin(LD_P_GPIO_Port, LD_P_Pin, mod[i].led_d_p);
	/*
	PORTA=(mod[i].led_a_p<<LA_P)|
	(mod[i].led_a_s<<LA_S)|
	(mod[i].led_a_z<<LA_Z)|
	(mod[i].led_b_p<<LB_P)|
	(mod[i].led_b_s<<LB_S)|
	(mod[i].led_b_z<<LB_Z)|
	(mod[i].led_b_z2<<LB_Z2)|
	(mod[i].led_d_p<<LD_P);
	*/

	HAL_GPIO_WritePin(LD_S_GPIO_Port, LD_S_Pin, mod[i].led_d_s);
	HAL_GPIO_WritePin(LD_Z_GPIO_Port, LD_Z_Pin, mod[i].led_d_z);
	HAL_GPIO_WritePin(LC_P_GPIO_Port, LC_P_Pin, mod[i].led_c_p);
	HAL_GPIO_WritePin(LC_S_GPIO_Port, LC_S_Pin, mod[i].led_c_s);
	HAL_GPIO_WritePin(LC_Z_GPIO_Port, LC_Z_Pin, mod[i].led_c_z);
	HAL_GPIO_WritePin(LE_P_GPIO_Port, LE_P_Pin, mod[i].led_e_p);
	HAL_GPIO_WritePin(LE_S_GPIO_Port, LE_S_Pin, mod[i].led_e_s);
	HAL_GPIO_WritePin(LE_Z_GPIO_Port, LE_Z_Pin, mod[i].led_e_z);
	HAL_GPIO_WritePin(LE_Z2_GPIO_Port, LE_Z2_Pin, mod[i].led_e_z2);
	HAL_GPIO_WritePin(LG1_P_GPIO_Port, LG1_P_Pin, mod[i].led_g1_p);
	HAL_GPIO_WritePin(LG2_P_GPIO_Port, LG2_P_Pin, mod[i].led_g2_p);
	/*
	PORTC=(mod[i].led_d_s<<LD_S)|
	(mod[i].led_d_z<<LD_Z)|
	(mod[i].led_c_p<<LC_P)|
	(mod[i].led_c_s<<LC_S)|
	(mod[i].led_c_z<<LC_Z)|
	(mod[i].led_e_p<<LE_P)|
	(mod[i].led_e_s<<LE_S)|
	(mod[i].led_e_z<<LE_Z);
	*/
}


void nappali_mod(void)
{

	if(i==0)
	{
		if(Jon_a_vonat)
			do_traffic(nappali_v);
		else
			do_traffic(nappali);
	}
	if(nappali[i].szamlalo_tmp<nappali[i].szamlalo)
	{
		nappali[i].szamlalo_tmp++;
	}

	else
	{
		nappali[i].szamlalo_tmp=0;
		i++;
		if(i==10)i=1;

		if(Jon_a_vonat)
			do_traffic(nappali_v);
		else
			do_traffic(nappali);
	}


	if(nappali[i].led_g1_z==2)led_pwm_allapot.led_g1_z=1;
	else if(nappali[i].led_g1_z==1) HAL_GPIO_WritePin(LG1_Z_GPIO_Port,LG1_Z_Pin,1);
	else
	{
      led_pwm_allapot.led_g1_z=0;

      HAL_GPIO_WritePin(LG1_Z_GPIO_Port,LG1_Z_Pin,0);
	}
	if(nappali[i].led_g2_z==2)led_pwm_allapot.led_g2_z=1;
	else if(nappali[i].led_g2_z==1)HAL_GPIO_WritePin(LG2_Z_GPIO_Port,LG2_Z_Pin,1);
	else
	{
		led_pwm_allapot.led_g2_z=0;
		HAL_GPIO_WritePin(LG2_Z_GPIO_Port,LG2_Z_Pin,0);
	}
}

/* USER CODE END 4 */

/* MPU Configuration */

void MPU_Config(void)
{
  MPU_Region_InitTypeDef MPU_InitStruct = {0};

  /* Disables the MPU */
  HAL_MPU_Disable();

  /** Initializes and configures the Region and the memory to be protected
  */
  MPU_InitStruct.Enable = MPU_REGION_ENABLE;
  MPU_InitStruct.Number = MPU_REGION_NUMBER0;
  MPU_InitStruct.BaseAddress = 0x0;
  MPU_InitStruct.Size = MPU_REGION_SIZE_4GB;
  MPU_InitStruct.SubRegionDisable = 0x87;
  MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
  MPU_InitStruct.AccessPermission = MPU_REGION_NO_ACCESS;
  MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_DISABLE;
  MPU_InitStruct.IsShareable = MPU_ACCESS_SHAREABLE;
  MPU_InitStruct.IsCacheable = MPU_ACCESS_NOT_CACHEABLE;
  MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

  HAL_MPU_ConfigRegion(&MPU_InitStruct);
  /* Enables the MPU */
  HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);

}

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
