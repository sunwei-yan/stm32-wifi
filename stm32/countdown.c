/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    key.h
  * @brief   This file contains all the function prototypes for
  *          the rtc.c file
  ******************************************************************************
  */
/* USER CODE END Header */
#include "oled.h"
#include "countdown.h"
#include "beep.h"
extern int hour,ms,minu,sec,press_sign,key_interruption,countdown_sign;
void countdown(){
hour = (ms / 10) / 3600;
				minu = (ms / 10) % 3600 / 60;
				sec = (ms / 10) % 60;
				OLED_ShowNum(0, 0, minu, 2, 16);
				OLED_ShowString(16, 0, (unsigned char *)":", 16);
				OLED_ShowNum(20, 0, sec, 2, 16);
				OLED_DrawLine(0, 60, 127, 60);
				if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {
					HAL_Delay(1);
					press_sign = 1;
					while (press_sign == 1) {
						if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_SET) {
							ms = ms + 10;
							key_interruption = 10;
							press_sign = 0;
						}
						if (key_interruption <= 0 && HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) {
							countdown_sign = 1;
							press_sign = 0;
							fs(250);
						}
					}

				}
				if (ms == 0) {
					countdown_sign = 0;
					fs(250);
					ms = 10;
				}}
