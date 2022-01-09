/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
TIM_HandleTypeDef htim1;

/* USER CODE BEGIN PV */
uint8_t difficulty = 0;
int symCounter = 0;
bool shiftMode = SHIFT_LEFT;
char diffMessage[] = "Choose difficulty from 1 to 3";

int value_1 = 0;
int value_2 = 0;
int value_3 = 0;

int action_1 = 0;
int action_2 = 0;
uint16_t adr_cnt = 0x00;
int ex_cnt = 0;
char string[2];
int result = 0;
int answer = 0;
int sum = 0;
int temp = 0;
int degree = 1;
int sign = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

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
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
	DWT_Init();
	HAL_Delay(100);
	mt_LCD_init();
	mt_lcd_clear_display();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if(keyboardScan() == SHARP_BUTTON)
		{
			difficulty = 0;
			mt_lcd_clear_display();
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		if(difficulty == 0)
		{
			for(int i = 0; i < 30; i++)
			{
				mt_lcd_write_byte(diffMessage[i], i);
				
				if((i >= 8))
				{
					mt_lcd_write_byte(diffMessage[i], 56 + i);
				}
			}
			symCounter = 10;
			HAL_Delay(1000);
			HAL_TIM_Base_Start_IT(&htim1);
			
			do
			{
				difficulty = keyboardScan();
			}
			while(!((difficulty == ONE_BUTTON) ^ (difficulty == TWO_BUTTON) ^ (difficulty == THREE_BUTTON)));	
			temp = difficulty;
			do
			{
				difficulty = keyboardScan();
				if(difficulty == STAR_BUTTON)
				{
					difficulty = 0;
					break;
				}
			}
			while(!(difficulty == SHARP_BUTTON));	
			difficulty = temp;
			HAL_TIM_Base_Stop_IT(&htim1);
			mt_lcd_clear_display();
			HAL_Delay(1000);
			
			if(difficulty != 0)
			{
				switch(difficulty)
				{
					case 1:
						while(ex_cnt != 10)
						{
							mt_lcd_clear_display();
							value_1 = rand() % 100;
							value_2 = rand() % 100;
							action_1 = rand() % 100;
							sprintf(string, "%d", value_1);
							adr_cnt = 0x00;
							for (int i = 0; i < strlen(string); i++)
							{
								mt_lcd_write_byte(string[i], adr_cnt);
								adr_cnt++;								
							}
							if(action_1 > 49)
							{
								result = value_1 - value_2;
								mt_lcd_write_byte('-', adr_cnt);
							}
							else 
							{
								result = value_1 + value_2;
								mt_lcd_write_byte('+', adr_cnt);
							}
							adr_cnt++;
							sprintf(string, "%d", value_2);
							for (int i = 0; i < strlen(string); i++)
							{
								mt_lcd_write_byte(string[i], adr_cnt);
								adr_cnt++;
							}
							mt_lcd_write_byte('=', adr_cnt);
							adr_cnt++;
							temp = 0;		
							do
							{
								answer = 0;
								do
								{
									answer = keyboardScan();
								}
								while(answer == 0);
								if(answer == SHARP_BUTTON)
									break;
								if(answer != 0x0A)
								{
									if(answer == 0x0B)
										answer = 0;
									if(temp != 0)
									{
										temp *= 10;
									}
									temp += answer;
									degree++;
									sprintf(string, "%d", answer);
									mt_lcd_write_byte(string[0], adr_cnt);
									adr_cnt++;
									if(adr_cnt == 8)
									{
										adr_cnt = 0x40;
									}
									HAL_Delay(1000);									
								}
								else
								{
									if(degree == 1)
									{
										answer = '-';
										degree++;
										sprintf(string, "%c", answer);
										sign = 1;
										mt_lcd_write_byte(string[0], adr_cnt);
										adr_cnt++;
										if(adr_cnt == 8)
										{
											adr_cnt = 0x40;
										}
										HAL_Delay(1000);	
									}								
								}
							}
							while(!(degree == 4));								
							answer = temp;
							if(sign == 1)
								answer *= -1;
							
							if(answer == result)
								sum++;	
							degree = 1;
							answer = 0;
							do
							{
								answer = keyboardScan();
							}
							while(!(answer == STAR_BUTTON));	
							HAL_Delay(1000);							
							answer = 0;	
							sign = 0;
							ex_cnt++;
					  }
						mt_lcd_clear_display();
						memset(string, 0, 2);
						sprintf(string, "%d", sum);
						mt_lcd_write_byte(string[1], 0x00);
						mt_lcd_write_byte(string[0], 0x01);
						break;
					case 2:
						value_1 = rand() % 100;
						value_2 = rand() % 100;
					  action_1 = rand() % 100;
						sprintf(string, "%d", value_1);
					  adr_cnt = 0x00;
					  for (int i = 0; i < strlen(string); i++)
						{
							mt_lcd_write_byte(string[i], adr_cnt);
							adr_cnt++;
						}
						if(action_1 > 49)
						{
							mt_lcd_write_byte('/', adr_cnt);
						}
						else 
						{
							mt_lcd_write_byte('*', adr_cnt);
						}
						adr_cnt++;
						sprintf(string, "%d", value_2);
						for (int i = 0; i < strlen(string); i++)
						{
							mt_lcd_write_byte(string[i], adr_cnt);
							adr_cnt++;
						}	
						break;
					case 3:
						value_1 = rand() % 100;
						value_2 = rand() % 100;			
						value_3 = rand() % 100;
					  action_1 = rand() % 100;
					  action_2 = rand() % 100;
						sprintf(string, "%d", value_1);
						mt_lcd_write_byte('(', 0x00);
					  adr_cnt = 0x01;
						for (int i = 0; i < strlen(string); i++)
						{
							mt_lcd_write_byte(string[i], adr_cnt);
							adr_cnt++;
						}
						if(action_1 > 49)
						{
							mt_lcd_write_byte('-', adr_cnt);
						}
						else 
						{
							mt_lcd_write_byte('+', adr_cnt);
						}
						adr_cnt++;
						sprintf(string, "%d", value_2);
						for (int i = 0; i < strlen(string); i++)
						{
							mt_lcd_write_byte(string[i], adr_cnt);
							adr_cnt++;
						}
						mt_lcd_write_byte(')', adr_cnt);
						adr_cnt++;
						if(action_2 > 49)
						{
							mt_lcd_write_byte('/', adr_cnt);
						}
						else 
						{
							mt_lcd_write_byte('*', adr_cnt);
						}
						adr_cnt++;
						sprintf(string, "%d", value_1);
						for (int i = 0; i < strlen(string); i++)
						{
							mt_lcd_write_byte(string[i], adr_cnt);
							adr_cnt++;
						}
					default:
						//error!
						break;									
				}
			}
		}
		/*HAL_Delay(1000);
		HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);*/
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 549;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 65535;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, E_Pin|R_W_Pin|A0_Pin|DB4_Pin
                          |DB5_Pin|DB6_Pin|DB7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, R0_Pin|R1_Pin|R2_Pin|R3_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LED_Pin */
  GPIO_InitStruct.Pin = LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : E_Pin R_W_Pin A0_Pin DB4_Pin
                           DB5_Pin DB6_Pin DB7_Pin */
  GPIO_InitStruct.Pin = E_Pin|R_W_Pin|A0_Pin|DB4_Pin
                          |DB5_Pin|DB6_Pin|DB7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : R0_Pin R1_Pin R2_Pin R3_Pin */
  GPIO_InitStruct.Pin = R0_Pin|R1_Pin|R2_Pin|R3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : C0_Pin C1_Pin C2_Pin */
  GPIO_InitStruct.Pin = C0_Pin|C1_Pin|C2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
uint16_t keyboardScan(void)
{
	uint16_t result = 0;
	
	for(int t = 0; t < 4; t++)
	{
		HAL_GPIO_WritePin(R0_GPIO_Port, R0_Pin << t, GPIO_PIN_SET);
		for(int i = 0; i < 3; i++)
		{
			if(HAL_GPIO_ReadPin(C0_GPIO_Port, C0_Pin << i))
			{
				result += ONE_BUTTON + i + t * 3;
			}
		}		
		HAL_GPIO_WritePin(R0_GPIO_Port, R0_Pin << t, GPIO_PIN_RESET);
	}
	return result;
}

void startDiffMessage(void)
{
	for(int i = 0; i < 10; i++)
	{
		if(i == 8)
		{
			mt_lcd_write_byte(diffMessage[i], 0x40);
		}
		else if(i == 9)
		{
			mt_lcd_write_byte(diffMessage[i], 0x41);
		}
		else
		{
			mt_lcd_write_byte(diffMessage[i], i);
		}
	}
	symCounter += 10;
	
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
