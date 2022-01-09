/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "melt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

typedef enum{
	ONE_BUTTON = 1,
	TWO_BUTTON,
	THREE_BUTTON,
	FOUR_BUTTON,
	FIVE_BUTTON,
	SIX_BUTTON,
	SEVEN_BUTTON,
	EIGHT_BUTTON,
	NINE_BUTTON,
	STAR_BUTTON,
	ZERO_BUTTON,
	SHARP_BUTTON
}keyboard;

extern uint8_t difficulty;
extern uint8_t difficulty;
extern int symCounter;
extern bool	shiftMode;
extern char diffMessage[];

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
extern uint16_t keyboardScan(void);
extern void DWT_Delay(uint32_t us);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#define E_Pin GPIO_PIN_1
#define E_GPIO_Port GPIOA
#define R_W_Pin GPIO_PIN_2
#define R_W_GPIO_Port GPIOA
#define A0_Pin GPIO_PIN_3
#define A0_GPIO_Port GPIOA
#define DB4_Pin GPIO_PIN_4
#define DB4_GPIO_Port GPIOA
#define DB5_Pin GPIO_PIN_5
#define DB5_GPIO_Port GPIOA
#define DB6_Pin GPIO_PIN_6
#define DB6_GPIO_Port GPIOA
#define DB7_Pin GPIO_PIN_7
#define DB7_GPIO_Port GPIOA
#define R0_Pin GPIO_PIN_12
#define R0_GPIO_Port GPIOB
#define R1_Pin GPIO_PIN_13
#define R1_GPIO_Port GPIOB
#define R2_Pin GPIO_PIN_14
#define R2_GPIO_Port GPIOB
#define R3_Pin GPIO_PIN_15
#define R3_GPIO_Port GPIOB
#define C0_Pin GPIO_PIN_4
#define C0_GPIO_Port GPIOB
#define C1_Pin GPIO_PIN_5
#define C1_GPIO_Port GPIOB
#define C2_Pin GPIO_PIN_6
#define C2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */
#define SHIFT_LEFT		false
#define	SHIFT_RIGHT		true
	
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
