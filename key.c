/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    key.h
  * @brief   This file contains all the function prototypes for
  *          the rtc.c file
  ******************************************************************************
  */
/* USER CODE END Header */
#include "main.h"
#include "gpio.h"
#include "stdlib.h"	
#include "stm32f1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include "oled.h"
extern int ms;
int key(int flag){
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET||HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET||HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET){
		HAL_Delay(10);
	if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET) {
			OLED_Clear();
			flag = 1;
			HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
		}
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET) {
			OLED_Clear();
			flag = 0;
		}
		if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15) == GPIO_PIN_RESET) {
			OLED_Clear();
			flag = 2;
			ms=0;
		}
		if (HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5) == GPIO_PIN_RESET &&HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4) == GPIO_PIN_RESET) {
			OLED_Clear();
			flag = 6;
		}
	}

return flag;
}
